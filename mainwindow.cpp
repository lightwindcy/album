#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMenu>
#include<QAction>
#include<QDebug>
#include"wizard.h"
#include"protree.h"
#include<QFileDialog>
#include"protreewidget.h"
#include"picshow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setMinimumSize(1629,869);
    ui->setupUi(this);
    //创建菜单
    QMenu * menu_file = menuBar()->addMenu(tr("文件(&F)"));
    //创建项目的动作
    QAction *act_create_pro= new QAction(QIcon(":/icon/createpro.png"),tr("创建项目"),this);
    act_create_pro->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_N));
    menu_file->addAction(act_create_pro);
    //创建打开项目的动作
    QAction *act_open_pro = new QAction(QIcon(":/icon/openpro.png"),tr("打开项目"),this);
    act_open_pro->setShortcut(QKeySequence( Qt::CTRL+ Qt::Key_O));
    menu_file->addAction(act_open_pro);

    //创建设置菜单
    QMenu *menu_set = menuBar()->addMenu(tr("设置(&S)"));
    QAction * act_music = new QAction(QIcon(":/icon/music.png"),tr("背景音乐"),this);
    act_music->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_M));
    menu_set->addAction(act_music);
    //连接信号和槽
    connect(act_create_pro,&QAction::triggered,this,&MainWindow::createWindowSlot);
     connect(act_open_pro,&QAction::triggered,this,&MainWindow::openWindowSlot);
    //添加左侧的目录树
    _protree = new ProTree();
    ui->proLayout->addWidget(_protree);
    QTreeWidget *tree_widget =  dynamic_cast<ProTree*>(_protree)->GetTreeWidget();
    auto * pro_tree_widget = dynamic_cast<ProTreeWidget*>(tree_widget);


    //调用MainWindow::openWindowSlot槽函数时会触发该函数
    connect(this,&MainWindow::SigOpenPro,pro_tree_widget,&ProTreeWidget::SlotOpenPro);
    //创建右侧显示图片
    _pic_show = new PicShow();
    ui->picLayout->addWidget(_pic_show);
    auto *pro_pic_show = dynamic_cast<PicShow*>(_pic_show);
    //当树结构内部的选择项被切换了，右侧的图片显示也要切换
    connect(pro_tree_widget,&ProTreeWidget::SigUpdateSelected,pro_pic_show,PicShow::SlotSelectItem);

    connect(pro_tree_widget, &ProTreeWidget::SigClearSelected,pro_pic_show,
            &PicShow::SlotDeleteItem );
    //捕获点击的上一张，下一张信号
    connect(pro_pic_show,&PicShow::SigNextClicked,pro_tree_widget,&ProTreeWidget::SlotNextShow);
    connect(pro_pic_show,&PicShow::SigPreClicked,pro_tree_widget,&ProTreeWidget::SlotPreShow);
    //ProTreeWidget通过右侧图片显示传来的切换项，设置好切换项的高亮，并且把切换项的路径给picshow
    connect(pro_tree_widget,&ProTreeWidget::SigUpdatePic,pro_pic_show,&PicShow::SlotUpdatePic);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createWindowSlot(bool b)
{
    qDebug()<<"slot create ";
    Wizard w(this);
    w.setWindowTitle(tr("创建项目"));
    auto * page = w.page(0);
    page->setTitle(tr("设置项目配置"));
    //把wizard配置好的信号信息穿回
    connect(&w,&Wizard::SigProSettings,dynamic_cast<ProTree*>(_protree),&ProTree::AddProToTree);
    w.show();
    w.exec();
    disconnect(&w);
}

void MainWindow::openWindowSlot(bool b)
{
    QFileDialog file_dialog;
    file_dialog.setFileMode(QFileDialog::Directory);
    file_dialog.setWindowTitle(tr("选择导入的文件加"));
    file_dialog.setDirectory(QDir::currentPath());
    file_dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if(file_dialog.exec()){
        fileNames = file_dialog.selectedFiles();
    }else{
        return;
    }
    //直接把文件路径读入
    QString import_path = fileNames.at(0);
    emit SigOpenPro(import_path);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    auto * pro_pic_show = dynamic_cast<PicShow *>(_pic_show);
    pro_pic_show->ReloadPic();
    QMainWindow::resizeEvent(event);
}
