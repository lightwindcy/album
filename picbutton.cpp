#include "picbutton.h"
#include<QEvent>
PicButton::PicButton(QWidget *parent)
{

}

void PicButton::setIcons(const QString &normal, const QString &hover, const QString &pressed)
{
    _normal= normal;
    _hover = hover;
    _pressed=pressed;
    QPixmap pixtemp;
    pixtemp.load(_normal);
    this->resize(pixtemp.size());
    this->setIcon(pixtemp);
    this->setIconSize(pixtemp.size());
}

bool PicButton::event(QEvent *e)
{
    switch (e->type()) {
    case QEvent::Enter:
        SetHoverIcon();
        break;
    case QEvent::Leave:
        setNormalIcon();
        break;
    case QEvent::MouseButtonPress:
        SetPressIcon();
        break;
    case QEvent::MouseButtonRelease:
        SetHoverIcon();
        break;
    default:
        break;
    }
    return QPushButton::event(e);
}

void PicButton::setNormalIcon()
{
    QPixmap pixtemp;
   pixtemp.load(_normal);
   this->setIcon(pixtemp);
}

void PicButton::SetHoverIcon()
{
    QPixmap pixtemp;
   pixtemp.load(_hover);
   this->setIcon(pixtemp);
}

void PicButton::SetPressIcon()
{
    QPixmap pixtemp;
   pixtemp.load(_pressed);
   this->setIcon(pixtemp);
}
