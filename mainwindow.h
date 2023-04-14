#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QResizeEvent>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    //带上信号内的参数
    void createWindowSlot(bool b);
    void openWindowSlot(bool b);
signals:
    void SigOpenPro(const QString &path);
private:
    Ui::MainWindow *ui;
    QWidget *_protree;
    QWidget * _pic_show;
protected:
    virtual void resizeEvent(QResizeEvent * event);
};

#endif // MAINWINDOW_H
