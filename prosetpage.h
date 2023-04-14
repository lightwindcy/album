#ifndef PROSETPAGE_H
#define PROSETPAGE_H

#include <QWizardPage>

namespace Ui {
class prosetPage;
}

class prosetPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit prosetPage(QWidget *parent = 0);
    ~prosetPage();
    void GetProSettings(QString &name, QString &path);
protected:
    virtual bool isComplete() const;
private slots:
    void on_browse_clicked();

private:
    Ui::prosetPage *ui;
};

#endif // PROSETPAGE_H
