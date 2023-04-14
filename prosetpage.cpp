#include "prosetpage.h"
#include "ui_prosetpage.h"
#include<QLineEdit>
#include<QDir>
#include<QDebug>
#include<QFileDialog>
prosetPage::prosetPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::prosetPage)
{
    ui->setupUi(this);
    //把内容和域绑定
    registerField("path",ui->pathEdit);
    registerField("name",ui->nameEdit);
    //触发信号，发送信号，基类中带有iscomplete函数判断是否完成
    connect(ui->nameEdit,&QLineEdit::textEdited,this,&prosetPage::completeChanged);
    connect(ui->pathEdit,&QLineEdit::textEdited,this,&prosetPage::completeChanged);
    QString curpath=QDir::currentPath();
    ui->pathEdit->setText(curpath);
    ui->pathEdit->setCursorPosition(ui->pathEdit->text().size());
    ui->pathEdit->setClearButtonEnabled(true);
    ui->nameEdit->setClearButtonEnabled(true);
}

prosetPage::~prosetPage()
{
    delete ui;
}

void prosetPage::GetProSettings(QString &name, QString &path)
{
    name = ui->nameEdit->text();
    path = ui->pathEdit->text();
}


bool prosetPage::isComplete() const
{
    if(ui->nameEdit->text() == "" || ui->pathEdit->text() == ""){
        return false;
    }
    //判断是否文件夹是否合理
    QDir dir(ui->pathEdit->text());
    if(!dir.exists())
    {
      qDebug()<<"file path is not exists" << endl;
      ui->tips->setText("project path is not exists");
      return false;
    }
    //判断路径是否存在
    QString absFilePath = dir.absoluteFilePath(ui->nameEdit->text());
    qDebug() << "absFilePath is " <<absFilePath;
   QDir dist_dir(absFilePath);
    if(dist_dir.exists()){
        ui->tips->setText("project has exists, change path or name!");
        return false;
    }
   ui->tips->setText("");
    //QWizardPage
   return QWizardPage::isComplete();
}

void prosetPage::on_browse_clicked()
{
    QFileDialog file_dialog;
    //设置读取模式，读取的是文件目录
    file_dialog.setFileMode(QFileDialog::Directory);
    file_dialog.setWindowTitle("选择导入的文件夹");
    auto path = QDir::current();
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
    qDebug() << "import_path is " << import_path << endl;
    ui->pathEdit->setText(import_path);
}
