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

    QTimer *timer;
    QTimer *timer2;
    QTimer *timer3;

    QSystemTrayIcon *m_trayIcon;
    QMenu *m_trayIconMenu;
    QAction *m_quit;
    QAction *m_start;
    QAction *m_clock_calibration;

    void write_ini();
    void read_ini();
    void reg_ini();

    QString word;
    QString deadline;
    int font_size;
    QString font_family;
    QString font_color;
    bool font_bold;
    QScreen *screen;
    QFont font;

    bool shine_ = true;
    bool shining;

    QString dir_path;
    QString file_path;
    QString app_name;
    QString iniFilePath;


    QString ntpIP;
    QUdpSocket *udpSocket;

    qint64 time_error;
    bool _setsystemtime();

    QMediaPlayer *player;

    int music_volume;

    bool top_hint;
/*
    void check_collision();
    bool up_move = false;
    bool down_move = false;

    QPoint *last_position;
*/

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

protected:
    virtual void keyPressEvent(QKeyEvent *);
    virtual void mouseDoubleClickEvent(QMouseEvent *);
//    virtual void wheelEvent(QWheelEvent *);
};

#endif // DIALOG_H
