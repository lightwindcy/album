#ifndef SLIDESHOWDLG_H
#define SLIDESHOWDLG_H

#include <QDialog>
#include<QTreeWidgetItem>
namespace Ui {
class SlideShowdlg;
}

class SlideShowdlg : public QDialog
{
    Q_OBJECT

public:
    SlideShowdlg(QWidget *parent = nullptr,QTreeWidgetItem * first_item=nullptr,QTreeWidgetItem * last_item= nullptr);
    ~SlideShowdlg();

private:
    Ui::SlideShowdlg *ui;
    QTreeWidgetItem * _first_item;
    QTreeWidgetItem * _last_item;
};

#endif // SLIDESHOWDLG_H
