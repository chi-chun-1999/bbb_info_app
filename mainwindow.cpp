#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qnamespace.h>

ErrorWindow::ErrorWindow()
{
    widget_width_=400;
    widget_height_=300;
    this->resize(widget_width_,widget_height_);
    this->setWindowTitle("Error");
    label_=new QLabel(this);
    label_->setGeometry(0,0,400,300);
    label_->setText("Error");
    label_->setAlignment(Qt::AlignCenter);
    label_->setStyleSheet("font-size:20px;color:red;");
}
void ErrorWindow::setText(QString text)
{
    label_->setText(text);
}
void ErrorWindow::setLocation(int main_x,int main_y,int main_w,int main_h)
{
    int x=abs(this->width()-main_w)/2.0+main_x;
    int y=abs(this->height()-main_h)/2.0+main_y;
    this->setGeometry(x,y,widget_width_,widget_height_);

}
ErrorWindow::~ErrorWindow()
{

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager();
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(managerFinished(QNetworkReply*)));

    ui->label_meeting_name_info->setStyleSheet("color:gray");
    ui->label_creat_date_info->setStyleSheet("color:gray");


}

void MainWindow::managerFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        error_window_.setText("Cannot Find Sever");
        ui->centralwidget->pos().rx();
        error_window_.setLocation(location_.x(),location_.y(),ui->centralwidget->width(),ui->centralwidget->height());
        error_window_.show();
        return;
    }

    QString answer=QString::fromUtf8("Encoding");
           answer = reply->readAll();
           server_.getData(answer);
    //qDebug() << answer;
           //QStringList lines=answer.split("\n",QString::SkipEmptyParts);
           //foreach(QString line,lines)
           //{
           //    qDebug()<<line;
           //}
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

        server_.setGetMeetingsURL(ui->lineEdit_domain_name->text());
        QString request_url=server_.getMeetings();
        request.setUrl(QUrl(request_url));
        QNetworkReply* reply = naManager->get(request);
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    //QString qStr="sadfdfa \n ddasdf";

    /*QStringList lines=qStr.split("\n",QString::SkipEmptyParts);
    foreach(QString line,lines)
    {
        qDebug()<<line;
    }*/
    //qDebug()<<qStr;
}


void MainWindow::moveEvent(QMoveEvent *e)
{
    QMainWindow::moveEvent(e);
    QRect r=geometry();
    location_.setX(r.x());
    location_.setY(r.y());
}



