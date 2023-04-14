#include "picshow.h"
#include "ui_picshow.h"

PicShow::PicShow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PicShow)
{
    ui->setupUi(this);
    ui->pre_btn->setIcons(":/icon/previous.png",":/icon/previous_hover.png",":/icon/previous_press.png");
    ui->next_btn->setIcons(":/icon/next.png",":/icon/next_hover.png",":/icon/next_press.png");
    QGraphicsOpacityEffect * opacity_pre = new QGraphicsOpacityEffect(this);
    opacity_pre ->setOpacity(0);
    ui->pre_btn->setGraphicsEffect(opacity_pre);
    QGraphicsOpacityEffect * opacity_next = new QGraphicsOpacityEffect(this);
    opacity_next->setOpacity(0);
    ui->next_btn->setGraphicsEffect(opacity_next);
    _anime_pre_btn = new QPropertyAnimation(opacity_pre,"opacity",this);
    _anime_pre_btn->setEasingCurve(QEasingCurve::Linear);
    _anime_pre_btn->setDuration(500);

    _anime_next_btn = new QPropertyAnimation(opacity_next,"opacity",this);
    _anime_next_btn->setEasingCurve(QEasingCurve::Linear);
    _anime_next_btn->setDuration(500);

    //连接信号，通知mainwindow响应按下左侧按钮和右侧按钮的事件
    connect(ui->next_btn,&PicButton::clicked,this,&PicShow::SigNextClicked);
    connect(ui->pre_btn,&PicButton::clicked,this,&PicShow::SigPreClicked);
}

PicShow::~PicShow()
{
    delete ui;
}

void PicShow::ReloadPic()
{
    if(_selected_path!=""){
        const auto &width = ui->gridLayout->geometry().width();
        const auto &height = ui->gridLayout->geometry().height();
        _pix_map.load(_selected_path);
        _pix_map = _pix_map.scaled(width,height,Qt::KeepAspectRatio);
        ui->label->setPixmap(_pix_map);
    }
}

bool PicShow::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::Enter:
        ShowPreNextBtns(true);
        break;
    case QEvent::Leave:
         ShowPreNextBtns(false);
        break;
     default:
        break;
    }
    return QDialog::event(event);
}

void PicShow::ShowPreNextBtns(bool b_show)
{
    //b_show 是要求显示还是隐藏
    //_btn_IsVisible 判断当前按钮的状态
    if(!b_show&& _btn_IsVisible){
        _anime_pre_btn->stop();
        _anime_pre_btn->setStartValue(1);
        _anime_pre_btn->setEndValue(0);
        _anime_pre_btn->start();

        _anime_next_btn->stop();
        _anime_next_btn->setStartValue(1);
        _anime_next_btn->setEndValue(0);
        _anime_next_btn->start();
        _btn_IsVisible=false;
    }
    //=显示
    if(b_show&& !_btn_IsVisible){
        _anime_pre_btn->stop();
        _anime_pre_btn->setStartValue(0);
        _anime_pre_btn->setEndValue(1);
        _anime_pre_btn->start();

        _anime_next_btn->stop();
        _anime_next_btn->setStartValue(0);
        _anime_next_btn->setEndValue(1);
        _anime_next_btn->start();

        _btn_IsVisible=true;
    }
}

void PicShow::SlotSelectItem(const QString &path)
{
     _selected_path=path;
     _pix_map.load(path);
     auto width = this->width()-20;
     auto height = this->height()-20;
     _pix_map = _pix_map.scaled(width,height,Qt::KeepAspectRatio);
     ui->label->setPixmap(_pix_map);
}

void PicShow::SlotUpdatePic(const QString &path)
{
    _selected_path = path;
    if(_selected_path!=""){
        const auto &width = ui->gridLayout->geometry().width();
        const auto &height = ui->gridLayout->geometry().height();
        _pix_map.load(_selected_path);
        _pix_map = _pix_map.scaled(width,height,Qt::KeepAspectRatio);
        ui->label->setPixmap(_pix_map);
    }

}

void PicShow::SlotDeleteItem()
{
   _selected_path="";
    ui->label->clear();
}
