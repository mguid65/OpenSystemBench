#ifndef NOTSTANDARDERROR_H
#define NOTSTANDARDERROR_H

#include <QDialog>

namespace Ui {
class NotStandardError;
}

class NotStandardError : public QDialog
{
    Q_OBJECT

public:
    explicit NotStandardError(QWidget *parent = 0);
    ~NotStandardError();

private slots:
    void on_pushButton_clicked();
    void quit();
private:
    Ui::NotStandardError *ui;
};

#endif // NOTSTANDARDERROR_H
