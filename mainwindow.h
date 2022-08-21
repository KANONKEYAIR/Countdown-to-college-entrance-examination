#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDateTime>
#include <QTimer>
#include <QMessageBox>
#include <QProcess>
#include <QFile>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int day_num;
    int get_day();
    int second_num;
    int hour;
    int minute;
    int second;
    int get_second();
    bool CheckAppRunningStatus(const QString &appName);
    void KillAppProcess(const QString &appName);
    QString Config_Time;
    QString Config_Label;
    QStringList Config_Blacklist;
    void Config_Iintial();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
public slots:
    void timeout();
};

#endif // MAINWINDOW_H
