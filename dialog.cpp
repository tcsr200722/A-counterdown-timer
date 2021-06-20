#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label_background->setVisible(false);
    ui->label_logo->setStyleSheet("image: url(logo.png);");
    ui->label_logo->setVisible(false);
    INIT();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::clock_calibration()
{
    ntpIP = "ntp1.aliyun.com";
    udpSocket = new QUdpSocket(this);
    QObject::connect(udpSocket, &QUdpSocket::connected, this, &Dialog::sendData);
    QObject::connect(udpSocket, &QUdpSocket::readyRead, this, &Dialog::readDate);
    udpSocket->connectToHost(ntpIP, 123);
    udpSocket->waitForConnected();
}

void Dialog::sendData()
{
    qint8 LI = 0;
    qint8 VN = 3;
    qint8 MODE = 3;
    qint8 STRATUM = 0;
    qint8 POLL = 4;
    qint8 PREC = -6;
    QDateTime epoch(QDate(1900, 1, 1), QTime(0, 0, 0));
    qint32 second = quint32(epoch.secsTo(QDateTime::currentDateTime()));

    qint32 temp = 0;
    QByteArray timeRequest(48, 0);
    timeRequest[0] = (LI << 6) | (VN << 3) | (MODE);
    timeRequest[1] = STRATUM;
    timeRequest[2] = POLL;
    timeRequest[3] = PREC & 0xff;
    timeRequest[5] = 1;
    timeRequest[9] = 1;
    timeRequest[40] = (temp = (second & 0xff000000) >> 24);
    temp = 0;
    timeRequest[41] = (temp = (second & 0x00ff0000) >> 16);
    temp = 0;
    timeRequest[42] = (temp = (second & 0x0000ff00) >> 8);
    temp = 0;
    timeRequest[43] = ((second & 0x000000ff));

    udpSocket->write(timeRequest);
}

void Dialog::readDate()
{
    QByteArray newTime;
    QDateTime epoch(QDate(1900, 1, 1), QTime(0, 0, 0));
    QDateTime unixStart(QDate(1970, 1, 1), QTime(0, 0, 0));

    while (udpSocket->hasPendingDatagrams())
    {
        newTime.resize(udpSocket->pendingDatagramSize());
        udpSocket->read(newTime.data(), newTime.size());
    };

    QByteArray transmitTimeStamp ;
    transmitTimeStamp = newTime.right(8);
    quint32 seconds = transmitTimeStamp.at(0);
    quint8 temp = 0;

    for (int i = 1; i <= 3; i++)
    {
        seconds = (seconds << 8);
        temp = transmitTimeStamp.at(i);
        seconds = seconds + temp;
    }
    time_error = seconds - epoch.secsTo(unixStart) - QDateTime::currentDateTime().toSecsSinceEpoch();
    udpSocket->disconnectFromHost();
}


void Dialog::INIT()
{
    QApplication::setQuitOnLastWindowClosed(false);
    timer =  new QTimer();
    timer2 = new QTimer();
    timer3 = new QTimer();
    time_error = 0;
    dir_path = QApplication::applicationDirPath() + "/config.ini";
    file_path = QApplication::applicationFilePath();
    app_name = QApplication::applicationName();

    //设置托盘
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIconMenu = new QMenu;
    m_start = new QAction(tr("开机启动"),this);
    m_clock_calibration = new QAction(tr("校准时间"), this);
    m_quit = new QAction(tr("退出"),this);

    m_trayIconMenu->addSeparator();
    m_trayIconMenu->addAction(m_start);
    m_trayIconMenu->addAction(m_clock_calibration);
    m_trayIconMenu->addAction(m_quit);

    m_trayIcon->setToolTip(tr("托盘菜单"));
    m_trayIcon->setIcon(QIcon("://Resource/tray.png"));
    m_trayIcon->setContextMenu(m_trayIconMenu);     //设置托盘上下文菜单
    m_trayIcon->show();
    connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(tray_double_click_left(QSystemTrayIcon::ActivationReason)));
    connect(m_quit,SIGNAL(triggered()),this,SLOT(m_exit()));
    connect(m_clock_calibration,SIGNAL(triggered()),this,SLOT(clock_calibration()));
    connect(m_start,SIGNAL(triggered()),this,SLOT(boot_at_power_on()));

    //查询开机启动
    boot();

    //读取配置文件
    write_ini();
    reg_ini();
    read_ini();

    //设置窗口透明镂空和总在最前
    setWindowFlags(Qt::Tool|Qt::FramelessWindowHint);
    if(top_hint)
        setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowFlags(this->windowFlags());
    setWindowOpacity(1);
    setAttribute(Qt::WA_TranslucentBackground);

    //设置显示的文本
    font.setFamily(font_family);
    font.setPointSize(font_size);
    font.setBold(font_bold);
    ui->label->setText(word);
    ui->label->setFont(font);

    ui->label->setStyleSheet("color:" + font_color);

    //连接信号与槽
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(UpdateTime()));
    QObject::connect(timer2, SIGNAL(timeout()), this, SLOT(shine()));
    QObject::connect(timer3, SIGNAL(timeout()), this, SLOT(move_logo()));

    //启动timer
    timer->start(100);
    timer2->start(500);
    timer3->setInterval(3000);
    screen = QGuiApplication::primaryScreen ();
    this->move(0, 0);

    //last_position = new QPoint;
}
void Dialog::SetTime(int Days,int Hours,int Minutes,int Seconds)
{
    //获取日期的每一位数
    int Days1,Days2,Days3;
    Days3=Days%10;
    Days/=10;
    Days2=Days%10;
    Days/=10;
    Days1=Days%10;
    //获取小时的每一位数
    int Hours1,Hours2;
    Hours2=Hours%10;
    Hours/=10;
    Hours1=Hours%10;
    //获取分钟的每一位数
    int Minutes1,Minutes2;
    Minutes2=Minutes%10;
    Minutes/=10;
    Minutes1=Minutes%10;
    //获取秒的每一位数
    int Seconds1,Seconds2;
    Seconds2=Seconds%10;
    Seconds/=10;
    Seconds1=Seconds%10;
    //设置时间标签
    this->ui->label_Days1->setText(QString::number(Days1));
    this->ui->label_Days2->setText(QString::number(Days2));
    this->ui->label_Days3->setText(QString::number(Days3));

    this->ui->label_Hours1->setText(QString::number(Hours1));
    this->ui->label_Hours2->setText(QString::number(Hours2));

    this->ui->label_Minutes1->setText(QString::number(Minutes1));
    this->ui->label_Minutes2->setText(QString::number(Minutes2));

    this->ui->label_Seconds1->setText(QString::number(Seconds1));
    this->ui->label_Seconds2->setText(QString::number(Seconds2));

}

void Dialog::UpdateTime()
{
    //计算时间差
    qint64 machine_time = QDateTime::currentDateTime().toSecsSinceEpoch();
    QDateTime begin_time = QDateTime::fromSecsSinceEpoch(machine_time + time_error);
    QDateTime end_time = QDateTime::fromString(deadline,"yyyy.MM.dd HH:mm:ss");
    QTime time;
    time.setHMS(0, 0, 0, 0);
    int LeftSeconds=begin_time.secsTo(end_time);
    int Days,Hours,Minutes,Seconds;
    int _LeftSeconds = LeftSeconds;

    //获取秒
    Seconds=LeftSeconds%60;

    LeftSeconds-=Seconds;
    //转化成分钟
    LeftSeconds/=60;
    //获取分钟
    Minutes=LeftSeconds%60;

    LeftSeconds-=Minutes;
    //转化成小时
    LeftSeconds/=60;
    //获取小时
    Hours=LeftSeconds%24;

    //获取天
    Days=(LeftSeconds-Hours)/24;
    this->SetTime(Days,Hours,Minutes,Seconds);
    if(_LeftSeconds <= 0)
    {
        this->SetTime(0,0,0,0);
        shining = false;
        timer->disconnect();
        play_music();
        return;
    }
}

void Dialog::m_exit()
{
    exit(0);
}

void Dialog::m_hide_show_slot()
{
    if(ui->label->isVisible())
    {
        //隐藏
        shine_ = false;
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label->setVisible(false);
        ui->label_background->setVisible(false);
        ui->label_logo->setVisible(false);
        ui->label_num_background->setVisible(false);
        ui->label_Days1->setVisible(false);
        ui->label_Days2->setVisible(false);
        ui->label_Days3->setVisible(false);
        ui->label_Hours1->setVisible(false);
        ui->label_Hours2->setVisible(false);
        ui->label_Minutes1->setVisible(false);
        ui->label_Minutes2->setVisible(false);
        ui->label_Seconds1->setVisible(false);
        ui->label_Seconds2->setVisible(false);
    }
    else
    {
        //显示
        shine_ = true;
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label->setVisible(true);
        ui->label_num_background->setVisible(true);
        ui->label_Days1->setVisible(true);
        ui->label_Days2->setVisible(true);
        ui->label_Days3->setVisible(true);
        ui->label_Hours1->setVisible(true);
        ui->label_Hours2->setVisible(true);
        ui->label_Minutes1->setVisible(true);
        ui->label_Minutes2->setVisible(true);
        ui->label_Seconds1->setVisible(true);
        ui->label_Seconds2->setVisible(true);
    }
}

void Dialog::shine()
{
    if(!shine_ || !shining)
        return;
    if(ui->label_2->isVisible())
    {
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
    }
    else
    {
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
    }
}

void Dialog::write_ini()
{
    QFileInfo ini_file(dir_path);
    if(!ini_file.exists())
    {
        QSettings settings(dir_path, QSettings::IniFormat);
        settings.setIniCodec("UTF-8");
        settings.setValue("/settings/word", "距离考研时间还有");
        settings.setValue("/settings/deadline", "2021.12.25 00:00:00");
        settings.setValue("/settings/font_size", "20");
        settings.setValue("/settings/font_color", "#000000");
        settings.setValue("/settings/font_family", "微软雅黑");
        settings.setValue("/settings/font_bold", "true");
        settings.setValue("/settings/shining", "true");
        settings.setValue("settings/music_volume", "30");
        settings.setValue("settings/top_hint", "true");
    }
}

void Dialog::read_ini()
{
    QSettings *reg=new QSettings(INI_POS, QSettings::Registry64Format);
    QVariant value = reg->value(app_name);
    iniFilePath = value.toString();

    QSettings settings(iniFilePath,QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    word = settings.value("settings/word").toString().toUtf8();
    deadline = settings.value("settings/deadline").toString();
    font_size = settings.value("settings/font_size").toInt();
    font_color = settings.value("settings/font_color").toString();
    font_family = settings.value("settings/font_family").toString().toUtf8();
    font_bold = settings.value("settings/font_bold").toBool();
    shining = settings.value("settings/shining").toBool();
    music_volume = settings.value("settings/music_volume").toInt();
    top_hint = settings.value("settings/top_hint").toBool();
    delete  reg;
}

void Dialog::boot()
{
    QSettings *reg=new QSettings(AUTO_RUN, QSettings::Registry64Format);
    QVariant value = reg->value(app_name);
    QString tmp = value.toString();

    if(tmp.compare(file_path.replace("/", "\\"))==0)
    {
        m_start->setText("√ 开机启动");
    }
    else
    {
        m_start->setText("开机启动");
    }
    delete reg;
}
void Dialog::boot_at_power_on()
{
    QSettings *reg=new QSettings(AUTO_RUN, QSettings::Registry64Format);
    QVariant value = reg->value(app_name);
    QString tmp = value.toString();
    //开机自动运行
    if (tmp.compare(file_path.replace("/", "\\")) != 0)
    {
        reg->setValue(app_name,file_path.replace("/", "\\"));
    }
    else
    {
        reg->setValue(app_name,"");
    }
    delete reg;
    boot();
}
void Dialog::reg_ini()
{
    QSettings *reg=new QSettings(INI_POS, QSettings::Registry64Format);
    reg->setValue(app_name, dir_path);
    delete reg;
}

void Dialog::play_music()
{
    player = new QMediaPlayer;
    QString music_file_path = QApplication::applicationDirPath() + "/music.mp3";
    QFileInfo music_file(music_file_path);
    if(music_file.exists())
    {
        player->setMedia(QUrl::fromLocalFile(music_file_path));
    }
    else
    {
        player->setMedia(QUrl("qrc:/Resource/music.mp3"));
    }
    player->setVolume(music_volume);
    player->play();
}

void Dialog::set_full_screen()
{
    timer3->start();
    ui->label_background->setVisible(true);
    ui->label_logo->setVisible(true);
    ui->label->setStyleSheet("color:#ffffff");
    this->setCursor(Qt::BlankCursor);
    if(!ui->label->isVisible())
        m_hide_show_slot();
    move_logo();
}

void Dialog::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Escape)
    {
        quit_full_screen();
    }
}

void Dialog::move_logo()
{
    int x = QRandomGenerator::global()->bounded(0, QApplication::desktop()->width() - ui->label_logo->geometry().width());
    int y = QRandomGenerator::global()->bounded(0, QApplication::desktop()->height() - ui->label_logo->geometry().height());
    while(x>1098-130 && y < 50)
    {
        x = QRandomGenerator::global()->bounded(0, QApplication::desktop()->width() - ui->label_logo->geometry().width());
        y = QRandomGenerator::global()->bounded(0, QApplication::desktop()->height() - ui->label_logo->geometry().height());
    }
    ui->label_logo->move(x, y);
}
/*
void Dialog::check_collision()
{
    //设定移动轨迹有逆时针移动
    QPoint p = ui->label_logo->pos();
    //轨迹为右上或者左上
    if(up_move)
    {
        //检查上边线碰撞，轨迹为向左上
        //与上边线的距离小于5px认为碰撞
        if(p.y()<5)
        {
            //向左下移动，夹角90
            down_move = true;
            up_move = false;
            //计算当前轨迹与上边线夹角
            double a = last_position->y() / (1440 - p.x());
            double angle = 90 - qTan(a) * 180 / M_PI;


        }
        //检查右边线碰撞，轨迹为向右上
        else if(1440 - p.x() < 5)
        {
            //向左上移动，夹角90
        }
    }
    //轨迹为左下或者右下
    else if(down_move)
    {
        //检查左边线碰撞
        if(p.x()<5)
        {
            //向原本移动方向的对角线方向移动，夹角90
        }
        //检查下边线碰撞
        else if(900 - p.y() < 5)
        {
            //向原本移动方向的对角线方向移动，夹角90
        }
    }


}
*/
void Dialog::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton && ui->label_background->isHidden())
        set_full_screen();
    else if(ev->button() == Qt::RightButton)
    {
        if(ui->label_background->isVisible())
            quit_full_screen();
        else
            m_hide_show_slot();
    }

}

void Dialog::quit_full_screen()
{
    if(ui->label_background->isVisible())
    {
        timer3->stop();
        ui->label_background->setVisible(false);
        ui->label_logo->setVisible(false);
        ui->label->setStyleSheet("color:" + font_color);
        this->setCursor(Qt::ArrowCursor);
    }
}
/*
void Dialog::wheelEvent(QWheelEvent *ev)
{
    if(ev->delta()>0)
    {
        font_size += 1;
    }
    else
    {
        font_size -= 1;
    }
    font.setPointSize(font_size);
    ui->label->setFont(font);

}
*/

void Dialog::tray_double_click_left(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::DoubleClick)
    {
        m_hide_show_slot();
    }
}
