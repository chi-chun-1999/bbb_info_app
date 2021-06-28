#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtNetwork/QNetworkRequest>
#include<QtNetwork/QNetworkReply>
#include<QtNetwork/QNetworkAccessManager>
#include <QTextCodec>
#include<QLabel>
#include<QDesktopWidget>
#include<math.h>
#include<iostream>
#include<cstdlib>

#include"./data.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ErrorWindow :public QWidget
{
    public:
        ErrorWindow();
        void setText(QString text);
        void setLocation(int main_x,int main_y,int main_w,int main_h);
        ~ErrorWindow();
    private:
        QDesktopWidget desk_widget_;
        QLabel *label_=new QLabel;
        int widget_height_;
        int widget_width_;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void requestFinished(QNetworkReply* reply);


private slots:
    void on_pushButton_get_info_clicked();
    void managerFinished(QNetworkReply *reply);
private:

    QPoint location_;
    Ui::MainWindow *ui;
    void moveEvent(QMoveEvent *e);
    QNetworkAccessManager *manager;
    QNetworkRequest request;

    Server server_;

    ErrorWindow error_window_;
};




#endif // MAINWINDOW_H
