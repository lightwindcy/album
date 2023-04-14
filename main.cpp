#include "mainwindow.h"
#include <QApplication>
#include<QFile>
#include<QDebug>
int main(int argc, char *argv[])
{
    //qss全局加载
    QApplication a(argc, argv);
    QFile qss(":/style/style.qss");
    if(qss.open(QFile::ReadOnly)){
        qDebug()<<"读取成功"<<endl;
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }else{
        qDebug("open qss fail");
        return  0;
    }
    MainWindow w;
    w.setWindowTitle(("相册"));
    w.showMaximized();

    return a.exec();
}
