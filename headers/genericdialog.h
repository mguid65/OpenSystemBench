#ifndef GENERICDIALOG_H
#define GENERICDIALOG_H

#include <QDialog>

namespace Ui {
class genericDialog;
}

class genericDialog : public QDialog
{
    Q_OBJECT

public:
    explicit genericDialog(QString label_text, QString ok_text, QWidget *parent = nullptr);
    ~genericDialog();

private slots:

    void on_ph_ok_clicked();

private:
    Ui::genericDialog *ui;
};

#endif // GENERICDIALOG_H
