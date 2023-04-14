#ifndef PICSHOW_H
#define PICSHOW_H

#include <QDialog>
#include<QGraphicsOpacityEffect>
#include<QPropertyAnimation>
namespace Ui {
class PicShow;
}

class PicShow : public QDialog
{
    Q_OBJECT

public:
    explicit PicShow(QWidget *parent = 0);
    ~PicShow();
    void ReloadPic();
protected:
    bool event(QEvent *event) override;
private:
    void ShowPreNextBtns(bool b_show);
    Ui::PicShow *ui;
    QPropertyAnimation * _anime_pre_btn;
    QPropertyAnimation * _anime_next_btn;
    bool _btn_IsVisible;
    QString _selected_path;
    QPixmap _pix_map;
public slots:
    void SlotSelectItem(const QString & path);
    void SlotUpdatePic(const QString & path);
    void SlotDeleteItem();
signals:
   void SigNextClicked();
   void SigPreClicked();
};

#endif // PICSHOW_H
