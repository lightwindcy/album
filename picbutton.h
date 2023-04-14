#ifndef PICBUTTON_H
#define PICBUTTON_H

#include<QPushButton>
class PicButton : public QPushButton
{
public:
    PicButton(QWidget *parent = Q_NULLPTR);
    void setIcons(const QString & normal,const QString & hover,const QString & pressed);
protected:
    bool event(QEvent *e);
private:
    void setNormalIcon();
    void SetHoverIcon();
    void SetPressIcon();
    QString _normal;
    QString _hover;
    QString _pressed;
};

#endif // PICBUTTON_H
