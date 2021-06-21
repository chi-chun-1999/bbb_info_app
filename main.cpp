#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    #ifdef Q_OS_WIN
        system("chcp 936 > nul");
        system("chcp 65001 >　nul");
    #endif

    QApplication a(argc, argv);
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    MainWindow w;

qDebug() << "OpenSSL support condition:" << QSslSocket::supportsSsl();
    w.show();
    return a.exec();
}
