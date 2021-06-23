#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDateTime>
#include <QTimer>
#include <QRect>
#include <QDesktopWidget>
#include <QSystemTrayIcon>
#include <QDebug>
#include <QAction>
#include <QMenu>
#include <QSettings>
#include <QFont>
#include <QFileInfo>
#include <QDir>
#include <QScreen>
#include <QUdpSocket>
#include <QHostInfo>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QtMath>
#include <QRandomGenerator>
#include <QSqlDatabase>
#include <QSqlQuery>

#ifdef Q_OS_WIN32
#include <windows.h>
#endif

#define AUTO_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define INI_POS "HKEY_CURRENT_USER\\Software\\CountDownTimer"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void INIT();




private:
    Ui::Dialog *ui;

    void SetTime(int,int,int,int);
    qint64 time_error;
    QTimer *timer;
    QTimer *timer2;
    QTimer *timer3;
    QTimer *timer4;

    QSystemTrayIcon *m_trayIcon;
    QMenu *m_trayIconMenu;
    QAction *m_quit;
    QAction *m_start;
    QAction *m_clock_calibration;

    QString word;
    QString deadline;
    int font_size;
    QString font_family;
    QString font_color;
    bool font_bold;
    int music_volume;
    bool top_hint;
    bool eng_ch = false;
    int word_start;
    int word_end;

    QScreen *screen;
    QFont font;

    bool shine_ = true;
    bool shining;

    QString ini_path;
    QString file_path;
    QString app_name;
    QString iniFilePath;

    QString ntpIP;
    QUdpSocket *udpSocket;

    QMediaPlayer *player;

    void check_valid();
    bool create_datebase_connection();
    void read_datebase();
    bool _setsystemtime();
    void write_ini();
    void read_ini();
    void reg_ini();
    QString tranfer_week(QString);

private slots:
    void UpdateTime();
    void m_exit();
    void m_hide_show_slot();
    void shine();
    void boot_at_power_on();
    void boot();
    void sendData();
    void readDate();
    void clock_calibration();
    void play_music();
    void set_full_screen();
    void quit_full_screen();
    void move_logo();
    void tray_double_click_left(QSystemTrayIcon::ActivationReason reason);
    void update_lock_screen_time();

protected:
    virtual void keyPressEvent(QKeyEvent *);
    virtual void mouseDoubleClickEvent(QMouseEvent *);
//    virtual void wheelEvent(QWheelEvent *);
};

#endif // DIALOG_H
