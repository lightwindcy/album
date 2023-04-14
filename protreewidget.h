#ifndef PROTREEWIDGET_H
#define PROTREEWIDGET_H

#include<QTreeWidget>
#include <QAction>
#include<QProgressDialog>
#include"protreethread.h"
#include <memory>
#include"openprothread.h"
class SlideShowdlg;
class ProTreeWidget : public QTreeWidget
{
      Q_OBJECT
public:
    ProTreeWidget(QWidget *parent = Q_NULLPTR);
    void AddProToTree(const QString name,const QString path);

private :
    QSet<QString> _set_path;
    QTreeWidgetItem * _right_btn_item;
    //保存当前的激活项目
    QTreeWidgetItem * _active_item;
    QTreeWidgetItem * _selected_item;
    QAction * _action_import;
    QAction * _action_setstart;
    QAction * _action_closepro;
    QAction * _action_slideshow;
    QProgressDialog *_dialog_progress;
    QProgressDialog *_open_dialog_progress;
    std::shared_ptr<ProTreeThread> _thread_create_pro;
    std::shared_ptr<OpenproThread> _thread_open_pro;
    std::shared_ptr<SlideShowdlg> _slide_show_dlg;
private slots:
    void SlotItemPressed(QTreeWidgetItem * item ,int column);
    void SlotDoubleClickItem(QTreeWidgetItem * item, int column);
    void SlotImport();
    void SlotSetActive();
    void SlotSlideShow();
    void SlotClosePro();
    void SlotUpdateProgress(int count);
    void SlotFinishProgress();
    void SlotCancelProgress();


    void SlotOpenUpdateProgress(int count);
    void SlotOpenFinishProgress();
    void SlotOpenCancelProgress();
public slots:
    void SlotOpenPro(const QString & path);
    void SlotNextShow();
    void SlotPreShow();
signals:
    void SigCancelProgress();
    void SigOpenCancelProgress();
    void SigUpdateSelected(const QString &);
    void SigUpdatePic(const QString &);
    void SigClearSelected();
};

#endif // PROTREEWIDGET_H
