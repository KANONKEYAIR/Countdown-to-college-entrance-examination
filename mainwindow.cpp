#include "mainwindow.h"
#include "ui_mainwindow.h"
#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->start(1000);
    this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    ui->setupUi(this);
    MainWindow::timeout();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::get_day()
{
    QDateTime time1 = QDateTime::currentDateTime();
    QDateTime time2 = QDateTime::fromString("2023-06-07 09:00:00", "yyyy-MM-dd HH:mm:ss");
    return time1.daysTo(time2);
}
int MainWindow::get_second()
{
    QDateTime time1 = QDateTime::currentDateTime();
    QDateTime time2 = QDateTime::fromString("2023-06-07 09:00:00", "yyyy-MM-dd HH:mm:ss");
    return time1.secsTo(time2);
}

void MainWindow::timeout()
{
    // ³õÊ¼»¯
    bool status = CheckAppRunningStatus("ßÙÁ¨ßÙÁ¨.exe") || CheckAppRunningStatus("msedge.exe") || CheckAppRunningStatus("steam.exe");
    //this->day_num = get_day();
    //ui->leftday->setText(QString::number(day_num));
    this->second_num = get_second();
    this->day_num = second_num / 3600 / 24;
    this->hour = second_num / 3600 - day_num*24;
    this->minute = second_num / 60 - hour*60 - day_num*60*24;
    this->second = second_num - minute*60 - hour*3600 - day_num*3600*24;
    ui->leftday->setText(QString::number(day_num));
    ui->lefthour->setText(QString::number(hour));
    ui->leftminute->setText(QString::number(minute));
    ui->leftsecond->setText(QString::number(second));
    if (CheckAppRunningStatus("ßÙÁ¨ßÙÁ¨.exe"))
        KillAppProcess("ßÙÁ¨ßÙÁ¨.exe");
    if (CheckAppRunningStatus("msedge.exe"))
        KillAppProcess("msedge.exe");
    if (CheckAppRunningStatus("steam.exe"))
        KillAppProcess("steam.exe");
    if (status)
        QMessageBox::warning(NULL, "¾¯¸æ","±ðÍæÁË£¬ºÃºÃÑ§Ï°£¡");

}

bool MainWindow::CheckAppRunningStatus(const QString &appName)
{
#ifdef Q_OS_WIN
    QProcess* process = new QProcess;
    process->start("tasklist" ,QStringList()<<"/FI"<<"imagename eq " +appName);
    process->waitForFinished();
    QString outputStr = QString::fromLocal8Bit(process->readAllStandardOutput());
    if(outputStr.contains(appName)){
        return true;
    }
    else{
        return false;
    }
#endif
}
void MainWindow::KillAppProcess(const QString &appName)
{
#ifdef Q_OS_WIN
    QProcess p;
    QString c = "taskkill /im " + appName + " /f";
    p.execute(c);
    p.close();
#endif
}
