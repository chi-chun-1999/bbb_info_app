#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager();
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(managerFinished(QNetworkReply*)));

}
void MainWindow::managerFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QString answer=QString::fromUtf8("Encoding");
           answer = reply->readAll();

    //qDebug() << answer;
           QStringList lines=answer.split("\n",QString::SkipEmptyParts);
           foreach(QString line,lines)
           {
               qDebug()<<line;
           }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_get_info_clicked()
{

    QNetworkRequest request;
        QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
        QMetaObject::Connection connRet = QObject::connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));
        Q_ASSERT(connRet);

        request.setUrl(QUrl("https://bbb2.ical.tw/bigbluebutton/api/getMeetings?checksum=b2f3e005ff665505815084b10070d557289d0f13"));
        QNetworkReply* reply = naManager->get(request);
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
        QString qStr=QString::fromUtf8("我好帥 \n 邱繼群");
    qDebug()<<qStr;
    //QString qStr="sadfdfa \n ddasdf";

    /*QStringList lines=qStr.split("\n",QString::SkipEmptyParts);
    foreach(QString line,lines)
    {
        qDebug()<<line;
    }*/
    //qDebug()<<qStr;
}
