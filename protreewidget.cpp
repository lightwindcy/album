#include "protreewidget.h"
#include<QDir>
#include<protreeitem.h>
#include"const.h"
#include<QHeaderView>
#include<QGuiApplication>
#include <QMenu>
#include<QFileDialog>
#include<QDebug>
#include"protreethread.h"
#include"removeprodialog.h"
#include"slideshowdlg.h"

ProTreeWidget::ProTreeWidget(QWidget *parent)
    :QTreeWidget(parent), _active_item(nullptr),_right_btn_item(nullptr),_dialog_progress(nullptr),_selected_item(nullptr),
      _thread_create_pro(nullptr),_thread_open_pro(nullptr),_open_dialog_progress(nullptr)
{
    //传递该参数需要在构造函数中注册
    qRegisterMetaType<QVector<int> >("QVector<int>");

    this->header()->hide();
    //接受任何点击函数都会触发该事件
    connect(this,&ProTreeWidget::itemPressed,this,&ProTreeWidget::SlotItemPressed);
    _action_import = new QAction(QIcon(":/icon/import.png"),tr("导入项目"),this);
    _action_setstart = new QAction(QIcon(":/icon/core.png"),tr("设置活动项目"),this);
    _action_closepro = new QAction(QIcon(":/icon/close.png"),tr("关闭项目"),this);
    _action_slideshow = new QAction(QIcon(":/icon/slideshow.png"),tr("轮播图播放"),this);
    connect(_action_import,&QAction::triggered,this,&ProTreeWidget::SlotImport);
    connect(_action_setstart,&QAction::triggered,this,&ProTreeWidget::SlotSetActive);
    connect(_action_closepro,&QAction::triggered,this,&ProTreeWidget::SlotClosePro);
    connect(_action_slideshow ,&QAction::triggered,this,&ProTreeWidget::SlotSlideShow);
    connect(this,&ProTreeWidget::itemDoubleClicked,this,&ProTreeWidget::SlotDoubleClickItem);
}

void ProTreeWidget::AddProToTree(const QString name, const QString path)
{
    //创建文件夹，并把文件夹显示在左侧目录上
    QDir dir(path);
    QString file_path = dir.absoluteFilePath(name);
    QDir pro_dir(file_path);
    if(!pro_dir.exists()){
        bool enable = pro_dir.mkpath(file_path);
        if(!enable){
            return ;
        }
    }
    _set_path.insert(file_path);
    auto * item = new ProTreeItem(this,name,file_path,TreeItemPro);
    item->setData(0,Qt::DisplayRole,name);
    item->setData(0,Qt::DecorationRole,QIcon(":/icon/dir.png"));
    item->setData(0,Qt::ToolTipRole,file_path);
}

void ProTreeWidget::SlotItemPressed(QTreeWidgetItem * pressedItem, int column)
{
    if(QGuiApplication::mouseButtons() == Qt::RightButton){
        QMenu menu(this);
        int itemtype = pressedItem->type();
        if(itemtype ==TreeItemPro){
            _right_btn_item = pressedItem;
            menu.addAction(_action_import);
            menu.addAction(_action_setstart);
            menu.addAction(_action_closepro);
            menu.addAction(_action_slideshow);
            menu.exec(QCursor::pos());
        }
    }
}

void ProTreeWidget::SlotImport()
{
      QFileDialog file_dialog;
      file_dialog.setFileMode(QFileDialog::Directory);
      file_dialog.setWindowTitle(tr("选择导入的文件夹"));
      QString path = "";
      if(!_right_btn_item){
          qDebug()<<"_right_btn_item is empty"<<endl;
      }
      path = dynamic_cast<ProTreeItem *>(_right_btn_item)->Getpath();
      //文件对话框的默认路径
      file_dialog.setDirectory(path);
      file_dialog.setViewMode(QFileDialog::Detail);
      QStringList fileNames;
      if(file_dialog.exec()){
          fileNames = file_dialog.selectedFiles();
      }
      if(fileNames.size()<=0){
          return ;
      }
      QString import_path = fileNames.at(0);
      int file_count =0;
      _dialog_progress = new QProgressDialog(this);
       //线程传递参数是右值引用,加上引用变成左值
      qDebug()<<"线程";
      _thread_create_pro = std::make_shared<ProTreeThread>(std::ref(import_path),std::ref(path),
                                                           _right_btn_item,file_count,this,_right_btn_item,
                                                           nullptr);
      //连接更新进度框操作
      connect(_thread_create_pro.get(), &ProTreeThread::SigUpdateProgress,
              this, &ProTreeWidget::SlotUpdateProgress);

      connect(_thread_create_pro.get(), &ProTreeThread::SigFinishProgress, this,
              &ProTreeWidget::SlotFinishProgress);

      connect(_dialog_progress, &QProgressDialog::canceled, this, &ProTreeWidget::SlotCancelProgress);
      //通知线程停止
      connect(this, &ProTreeWidget::SigCancelProgress, _thread_create_pro.get(),
              &ProTreeThread::SlotCancelProgress);


      _thread_create_pro->start();
      _dialog_progress->setWindowTitle("please wait...");
      _dialog_progress->setRange(0,PROGRESS_WIDTH);
      _dialog_progress->exec();
}

void ProTreeWidget::SlotSetActive()
{
    if(!_dialog_progress){
        return ;
    }
    QFont nullFont;
    nullFont.setBold(false);
    if(_active_item){
        _active_item->setFont(0,nullFont);
    }
     _active_item=_right_btn_item;
     nullFont.setBold(true);
     _active_item->setFont(0,nullFont);

}

void ProTreeWidget::SlotSlideShow()
{
    if(!_right_btn_item){
        return;
    }
    auto *right_pro_item = dynamic_cast<ProTreeItem*>(_right_btn_item);

    auto * last_child_item = right_pro_item->GetLastPicChild();
    if(!last_child_item){
        return;
    }

    qDebug()<< "last child item name is " << last_child_item->Getpath()<< endl;

    auto * first_child_item = right_pro_item->GetFirstPicChild();
    if(!first_child_item){
        return;
    }

    qDebug()<< "first child item name is " << first_child_item->Getpath()<< endl;

    _slide_show_dlg = std::make_shared<SlideShowdlg>(this, first_child_item, last_child_item);
    _slide_show_dlg->setModal(true);
    _slide_show_dlg->showMaximized();
}

void ProTreeWidget::SlotClosePro()
{
    RemoveProDialog remove_pro_dialog;
    auto res=remove_pro_dialog.exec();
    //点击了取消
    if(res!=QDialog::Accepted){
        return;
    }
    //判断是否点击删除文件
    bool b_remove = remove_pro_dialog.IsRemoved();
    //找到该项目
    auto index_right_btn = this->indexOfTopLevelItem(_right_btn_item);
    auto * protreeItem = dynamic_cast<ProTreeItem*>(_right_btn_item);
    auto * selecteditem = dynamic_cast<ProTreeItem*>(_selected_item);
    auto delete_path = protreeItem->Getpath();
    _set_path.remove(delete_path);
    if(b_remove){
        QDir delete_dir(delete_path);
        delete_dir.removeRecursively();
    }
    if(protreeItem == _active_item){
        _active_item = nullptr;
    }
    if(selecteditem && protreeItem  == selecteditem->GetRoot()){
        selecteditem = nullptr;
         _selected_item = nullptr;
        emit SigClearSelected();
    }
    delete this->takeTopLevelItem(index_right_btn);
    _right_btn_item=nullptr;

}

void ProTreeWidget::SlotUpdateProgress(int count)
{
    qDebug() << "count is " << count;
    if(!_dialog_progress){
        qDebug() << "dialog_progress is empty!!!" << endl;
        return;
    }

    if(count >= PROGRESS_MAX){
         _dialog_progress->setValue(count%PROGRESS_MAX);
    }else{
         _dialog_progress->setValue(count%PROGRESS_MAX);
    }
}

void ProTreeWidget::SlotFinishProgress()
{
    _dialog_progress->setValue(PROGRESS_MAX);
    _dialog_progress->deleteLater();
}

void ProTreeWidget::SlotCancelProgress()
{
    //通知线程停止
    emit SigCancelProgress();
    delete _dialog_progress;
    _dialog_progress =nullptr;
}

void ProTreeWidget::SlotOpenUpdateProgress(int count)
{
    if(!_open_dialog_progress){
        qDebug() << "_open_dialog_progress is empty!!!" << endl;
        return;
    }

    if(count >= PROGRESS_MAX){
         _open_dialog_progress->setValue(count%PROGRESS_MAX);
    }else{
         _open_dialog_progress->setValue(count%PROGRESS_MAX);
    }
}

void ProTreeWidget::SlotOpenFinishProgress()
{
    _open_dialog_progress->setValue(PROGRESS_MAX);
    _open_dialog_progress->deleteLater();
}

void ProTreeWidget::SlotOpenCancelProgress()
{
    emit SigOpenCancelProgress();
    delete _open_dialog_progress;
    _open_dialog_progress =nullptr;
}

void ProTreeWidget::SlotDoubleClickItem(QTreeWidgetItem *item, int column)
{
    if(QGuiApplication::mouseButtons()== Qt::LeftButton){
        auto * tree_doubleItem = dynamic_cast<ProTreeItem*>(item);
        if(!tree_doubleItem){
            return;
        }
        int itemtype =  tree_doubleItem->type();
        if(itemtype == TreeItemPic){
            emit SigUpdateSelected( tree_doubleItem->Getpath());
            _selected_item=tree_doubleItem;
        }
    }
}

void ProTreeWidget::SlotOpenPro(const QString &path)
{
    if(_set_path.find(path)!=_set_path.end()){
        return;
    }
    _set_path.insert(path);
    int file_count = 0;
    QDir pro_dir(path);
    QString proname = pro_dir.dirName();
    _thread_open_pro = std::make_shared<OpenproThread>(path,file_count,this,nullptr);

    _open_dialog_progress = new QProgressDialog(this);
    connect(_thread_open_pro.get(), &OpenproThread::SigUpdateProgress,
            this, &ProTreeWidget::SlotOpenUpdateProgress);

    connect(_thread_open_pro.get(), &OpenproThread::SigFinishProgress, this,
            &ProTreeWidget::SlotOpenFinishProgress);

    connect(_open_dialog_progress, &QProgressDialog::canceled, this, &ProTreeWidget::SlotOpenCancelProgress);
    //通知线程停止
    connect(this, &ProTreeWidget::SigOpenCancelProgress, _thread_open_pro.get(),
            &OpenproThread::SlotCancelProgress);

    qDebug()<<"ppp?";
    _thread_open_pro->start();
    _open_dialog_progress->setWindowTitle("please wait...");
    _open_dialog_progress->setRange(0,PROGRESS_WIDTH);
    _open_dialog_progress->exec();

}

void ProTreeWidget::SlotNextShow()
{
    if(!_selected_item){
        return ;
    }
    auto * curItem = dynamic_cast<ProTreeItem*>(_selected_item)->GetNextItem();
    if(!curItem){
        return ;
    }
    emit SigUpdatePic(curItem->Getpath());
    _selected_item=curItem;
    this->setCurrentItem(curItem);
}

void ProTreeWidget::SlotPreShow()
{

    if(!_selected_item){
        return ;
    }
    auto * curItem = dynamic_cast<ProTreeItem*>(_selected_item)->GetPreItem();
    if(!curItem){
        return ;
    }
    emit SigUpdatePic(curItem->Getpath());
    _selected_item=curItem;
    this->setCurrentItem(curItem);
}
