#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qnamespace.h>

//ErrorWindow lib
ErrorWindow::ErrorWindow()
{
    widget_width_=400;
    widget_height_=300;
    this->resize(widget_width_,widget_height_);
    this->setWindowTitle("Error");
    label_=new QLabel(this);
    //label_->setGeometry(0,0,400,300);
    label_->setText("Error");
    label_->setAlignment(Qt::AlignCenter);
    label_->setStyleSheet("font-size:25px;color:red;");
    error_content_=new QLabel(this);
    error_content_->setText("error content");
    error_content_->setAlignment(Qt::AlignCenter);
    QVBoxLayout* v_layout=new QVBoxLayout;
    v_layout->addWidget(label_);
    v_layout->addWidget(error_content_);
    v_layout->setSpacing(0);
    v_layout->setMargin(100);
    this->setLayout(v_layout);

}

void ErrorWindow::error1()
//can't not find server;
{
    setText("Error 1");
    error_content_->setText("Can't Find Server");

}

void ErrorWindow::error2()
//can't not find server or share secret is error
{
    setText("Error 2");
    error_content_->setText("Share Serect is Error");

}

void ErrorWindow::error3()
//can't not open file
{
    setText("Error 3");
    error_content_->setText("Can't Open File");

}

void ErrorWindow::error4()
//no meeting
{
    setText("No Meeting");
    error_content_->setText("");

}
void ErrorWindow::error5()
//Please input domain name and share secret file
{
    setText("Error 5");
    error_content_->setText("Please input domain name and share sercret file");

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

//MeetingButtonSlot lib
void MeetingButtonSlot::setIndex(const int index)
{
    index_=index;
    //qDebug()<<index_;

}
void MeetingButtonSlot::print()
{
    //qDebug()<<this->index_;
}
void MeetingButtonSlot::getSignal()
{
    //print();
    emit getIndex(index_);
}

//MainWindow lib
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

    //setTableWidget();
}

void MainWindow::setTableWidget()
{

    int table_widget_width=ui->tableWidget_attend->geometry().width()-ui->tableWidget_attend->verticalHeader()->width()-5;
    //qDebug()<<table_widget_width;
    ui->tableWidget_attend->setColumnWidth(0,table_widget_width/3);
    ui->tableWidget_attend->setColumnWidth(1,table_widget_width/3*2);
    int people_num=current_meeting_data_.attendees.size();
    ui->tableWidget_attend->setRowCount(people_num);
    ui->tableWidget_attend->setStyleSheet("QTableWidget::item{color:gray;}");
    //qDebug()<<current_meeting_data_.attendees.size();

    int i=0;
    for(auto &iter:current_meeting_data_.attendees)
    {
        auto model = ui->tableWidget_attend->model();
        model->setData(model->index(i,0),iter.role);
        model->setData(model->index(i,1),iter.name);
        auto item=ui->tableWidget_attend->item(i,0);
        item->setTextAlignment(Qt::AlignRight);
        item=ui->tableWidget_attend->item(i,1);
        item->setTextAlignment(Qt::AlignRight);
        i++;
    }

}

void MainWindow::meetingsButton()
{
    for(auto iter:meetings_button_)
    {
        iter->close();
    }
    meetings_button_.clear();
    QPushButton *tmp_button;
    MeetingButtonSlot *tmp_button_slot;
    int button_x=ui->groupBox_meeting->x();
    int button_y=ui->groupBox_meeting->y();
    int button_w=ui->groupBox_meeting->width()-10;
    int button_h=100;
    int meeting_num=server_.getMeetingNum();
    vector<QString> meeting_names=server_.getMeetingsName();
    for(int i=0;i<meeting_num;i++)
    {
        QString meeting_name=meeting_names[i];

        tmp_button=new QPushButton(meeting_name,this->ui->groupBox_meeting);
        tmp_button_slot=new MeetingButtonSlot();

    tmp_button->setGeometry((ui->groupBox_meeting->width()-button_w)/2,30+i*(button_h+5),button_w,button_h);

        //tmp_button->setStyleSheet("background:white;");
        //``qDebug()<<i;
        tmp_button_slot->setIndex(i);
        meetings_button_.push_back(tmp_button);
        meetings_button_slot_.push_back(tmp_button_slot);
        meetings_button_.back()->show();
        connect(meetings_button_.back(),SIGNAL(clicked()),meetings_button_slot_.back(),SLOT(getSignal()));
        connect(meetings_button_slot_.back(),SIGNAL(getIndex(int)),this,SLOT(getCurrentMeetingIndex(int)));
    }
}

void MainWindow::managerFinished(QNetworkReply *reply) {
    if (reply->error()&&error_!=1) {
        //qDebug() << reply->errorString();
        //error_window_.error1();
        //ui->centralwidget->pos().rx();
        //error_window_.setLocation(location_.x(),location_.y(),ui->centralwidget->width(),ui->centralwidget->height());
        //error_window_.show();
        error(ERROR1);
    errorWindowShow();
        return;
    }

    QString answer=QString::fromUtf8("Encoding");
    answer = reply->readAll();
    server_.setData(answer);

    if(server_.errorReadXml()==RETURN_FAIL&&error_!=1)
    {
        //qDebug() << reply->errorString();
        //error_window_.error2();
        //ui->centralwidget->pos().rx();
        //error_window_.setLocation(location_.x(),location_.y(),ui->centralwidget->width(),ui->centralwidget->height());
        //error_window_.show();
        error(ERROR2);
    errorWindowShow();
        return;

    }

    if(server_.errorReadXml()==NO_MEETING&&error_!=1)
    {
        //error_window_.error4();
        //ui->centralwidget->pos().rx();
        //error_window_.setLocation(location_.x(),location_.y(),ui->centralwidget->width(),ui->centralwidget->height());
        //error_window_.show();
        //qDebug()<<"hello";
        error(ERROR4);
    errorWindowShow();
        return;

    }
    this->meetingsButton();
}

void MainWindow::getCurrentMeetingIndex(int index)
{
    on_pushButton_get_info_clicked();
    current_meeting_data_=server_.getCurrentMeetingData(index);


    ui->label_meeting_name_info->setText(current_meeting_data_.meeting_name);
    ui->label_creat_date_info->setText(current_meeting_data_.create_date);
    ui->lineEdit_attend_meeting_info->setText(current_meeting_data_.attending_URL);
    setTableWidget();

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


        //get domain and share secret
        error_=0;

        if(ui->lineEdit_domain_name->text()=="" || ui->lineEdit_share_secret_file->text()=="")
        {
            error(ERROR5);
            errorWindowShow();
            return;
        }

        server_.setGetMeetingsURL(ui->lineEdit_domain_name->text());
        getShareSecret();


        QString request_url=server_.getMeetings();
        request.setUrl(QUrl(request_url));
        QNetworkReply* reply = naManager->get(request);
}

void MainWindow::on_pushButton_browse_clicked()
{
   QString file_name=QFileDialog::getOpenFileName(this,"Open a file","..",tr("SH3 Log files (*.secret)"));
   //qDebug()<<file_name;
   ui->lineEdit_share_secret_file->setText(file_name);
    getShareSecret();

}

void MainWindow::on_pushButton_copy_clicked()
{
    QClipboard *clip=QApplication::clipboard();
    QString copy_text=ui->lineEdit_attend_meeting_info->text();
    clip->setText(copy_text);
}

void MainWindow::getShareSecret()
{
    QString file_name=ui->lineEdit_share_secret_file->text();

    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly)&&error_!=1)
    {
        //qDebug()<<"error open file"<<file.error();
        //error_window_.error3();
        //ui->centralwidget->pos().rx();
        //error_window_.setLocation(location_.x(),location_.y(),ui->centralwidget->width(),ui->centralwidget->height());
        //error_window_.show();
        error(ERROR3);
    errorWindowShow();
        return;
    }
    QTextStream instream(&file);
    QString share_secret=instream.readLine();
    server_.setShareSecret(share_secret);
    file.close();
    return;

}

void MainWindow::error(Error err)
{
    switch(err)
    {
        case ERROR1:
            error_window_.error1();
            break;
        case ERROR2:
            error_window_.error2();
            break;
        case ERROR3:
            error_window_.error3();
            break;
        case ERROR4:
            error_window_.error4();
            break;
        case ERROR5:
            error_window_.error5();
            break;
    }
    error_=1;
}
void MainWindow::errorWindowShow()
{
        ui->centralwidget->pos().rx();
        error_window_.setLocation(location_.x(),location_.y(),ui->centralwidget->width(),ui->centralwidget->height());
        error_window_.show();

}

void MainWindow::moveEvent(QMoveEvent *e)
{
    QMainWindow::moveEvent(e);
    QRect r=geometry();
    location_.setX(r.x());
    location_.setY(r.y());
}


