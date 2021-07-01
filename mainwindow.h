#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtNetwork/QNetworkRequest>
#include<QtNetwork/QNetworkReply>
#include<QtNetwork/QNetworkAccessManager>
#include <QTextCodec>
#include<QLabel>
#include<QDesktopWidget>
#include<QPushButton>
#include<QResizeEvent>
#include<QVBoxLayout>
#include<QFileDialog>
#include<QApplication>
#include<QClipboard>

#include<math.h>
#include<iostream>
#include<cstdlib>

#include"./data.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum Error
{
    ERROR1,
    ERROR2,
    ERROR3,
    ERROR4,
    ERROR5
};

class ErrorWindow :public QWidget
{
    public:
        ErrorWindow();
        void setText(QString text);
        void setLocation(int main_x,int main_y,int main_w,int main_h);
        ~ErrorWindow();

        void error1();//can't find server;
        void error2();//can't find server or share secret is erro;
        void error3();//can't not open file;
        void error4();//no meeting
        void error5();
    private:
        QDesktopWidget desk_widget_;
        QLabel *label_=new QLabel;
        QLabel *error_content_=new QLabel;
        int widget_height_;
        int widget_width_;
};

class MeetingButtonSlot:public QObject
{
   Q_OBJECT

    public:
        void setIndex(const int index);
        void print();

    signals:
        void getIndex(int index);
    public slots:
        void getSignal();

    private:
        int index_;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void requestFinished(QNetworkReply* reply);
    void setTableWidget();
    void meetingsButton();
    void getShareSecret();

    void errorWindowShow();
    void error(Error err);



private slots:
    void on_pushButton_get_info_clicked();
    void on_pushButton_browse_clicked();
    void on_pushButton_copy_clicked();
    void managerFinished(QNetworkReply *reply);
    void getCurrentMeetingIndex(int index);

    //void do_meeting_button_clicked(int index);
private:

    vector<QPushButton*> meetings_button_;
    vector<MeetingButtonSlot*> meetings_button_slot_;

    QPoint location_;
    Ui::MainWindow *ui;
    void moveEvent(QMoveEvent *e);
    QNetworkAccessManager *manager;
    QNetworkRequest request;

    Server server_;
    MeetingData current_meeting_data_;

    bool error_;

    ErrorWindow error_window_;
};




#endif // MAINWINDOW_H
