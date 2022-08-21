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
    MainWindow::Config_Iintial();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::get_day()
{
    QDateTime time1 = QDateTime::currentDateTime();
    QDateTime time2 = QDateTime::fromString(Config_Time, "yyyy-MM-dd HH:mm:ss");
    return time1.daysTo(time2);
}
int MainWindow::get_second()
{
    QDateTime time1 = QDateTime::currentDateTime();
    QDateTime time2 = QDateTime::fromString(Config_Time, "yyyy-MM-dd HH:mm:ss");
    return time1.secsTo(time2);
}

void MainWindow::timeout()
{
    // 初始化
    for (int i=0; i<Config_Blacklist.length(); i++)
    {
        if (CheckAppRunningStatus(Config_Blacklist[i]))
        {
            KillAppProcess(Config_Blacklist[i]);
            QMessageBox::warning(NULL, "警告","别玩了，好好学习！");
        }
    }
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

void MainWindow::Config_Iintial()
{
    QFile file("Config.ini");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream File(&file);
    File.setCodec("UTF-8");
    QString temp,temp2;
    while(!File.atEnd())
    {
        temp = File.readLine();
        if (temp == "[TimeSetting]")
        {
            Config_Time = File.readLine();
            continue;
        }
        if (temp == "[Label]")
        {
            Config_Label = File.readLine();
            ui->STRINGLABEL->setText(Config_Label);
            continue;
        }
        if (temp == "[Blacklist]")
        {
            while(1)
            {
                temp2 = File.readLine();
                if (temp2 == "[/Blacklist]")
                    break;
                Config_Blacklist << temp2;
            }
        }
    }
}
