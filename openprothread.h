#ifndef OPENPROTHREAD_H
#define OPENPROTHREAD_H

#include<QThread>
#include<QTreeWidget>
class OpenproThread : public QThread
{
    Q_OBJECT
public:
    OpenproThread(const QString & src_path,int file_count,QTreeWidget * self,QObject * parent=nullptr);
    void OpenProTree(const QString &src_path,int & file_count,QTreeWidget * self);
protected:
    virtual void run();
private:
    void RecursiveProTree(const QString &src_path,
                          int &file_count, QTreeWidget *self,
                          QTreeWidgetItem* root, QTreeWidgetItem* parent, QTreeWidgetItem* preitem);
    QString _src_path;
    int _file_count;
    QTreeWidget* _self;
    bool _bstop;
    QTreeWidgetItem* _root;
signals:
     void SigFinishProgress();
     void SigUpdateProgress(int);
public slots:
     void SlotCancelProgress();
};

#endif // OPENPROTHREAD_H
