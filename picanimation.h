#ifndef PICANIMATION_H
#define PICANIMATION_H
#include<QWidget>
#include"qtreewidget.h"
#include<QTreeWidgetItem>
class PicAnimation : public QWidget
{
    Q_OBJECT
public:
    explicit PicAnimation(QWidget *parent = nullptr);
    ~PicAnimation();
    void SetPixmap(QTreeWidgetItem * item);
    void Start();
    void Stop();
protected:
     virtual void paintEvent(QPaintEvent *event);
private:
    //动画的浮动因子
    float _factor;
    //定时器控制因子
    QTimer * _timer;

    //双缓冲绘图
    QPixmap _pixmap1;
    QPixmap _pixmap2;
    //当前播放到的图片
    QTreeWidgetItem * _cur_item;

    //存储播放过的图片
    QMap<QString,QTreeWidgetItem *> _map_items;
    //是否播放
    bool _b_start;
signals:
    void  SigUpPreList(QTreeWidgetItem *);
    void  SigSelectItem(QTreeWidgetItem *);
private slots:
    void TimeOut();
public slots:
};

#endif // PICANIMATION_H
