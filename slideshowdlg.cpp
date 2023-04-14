#include "slideshowdlg.h"
#include "ui_slideshowdlg.h"

SlideShowdlg::SlideShowdlg(QWidget *parent ,QTreeWidgetItem * first_item,QTreeWidgetItem * last_item) :
    QDialog(parent),_first_item(first_item),_last_item(last_item),
    ui(new Ui::SlideShowdlg)
{
    ui->setupUi(this);
    //隐藏幻灯片播放的头
    this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    ui->slidepreBtn ->setIcons(":/icon/previous.png",
                              ":/icon/previous_hover.png",
                              ":/icon/previous_press.png");

    ui->slidenextBtn->setIcons(":/icon/next.png",
                              ":/icon/next_hover.png",
                              ":/icon/next_press.png");
    ui->closeBtn->setIcons(":/icon/closeshow.png",":/icon/closeshow_hover.png",
                           ":/icon/closeshow_press.png");

    ui->playBtn->SetIcons(":/icon/play.png",":/icon/play_hover.png",":/icon/play_press.png",
                          ":/icon/pause.png",":/icon/pause_hover.png",":/icon/pause_press.png");


    //连接幻灯片播放和缩略图预览的信号
    connect(ui->picanimation,&PicAnimation::SigUpPreList,ui->preListWidget,&PreListWid::SlotUpPreList);
    connect(ui->picanimation, &PicAnimation::SigSelectItem, ui->preListWidget, &PreListWid::SlotUpSelect);

    ui->picanimation->SetPixmap(_first_item);
    ui->picanimation->Start();
}

SlideShowdlg::~SlideShowdlg()
{
    delete ui;
}
