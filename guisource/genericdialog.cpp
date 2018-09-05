#include "genericdialog.h"
#include "ui_genericdialog.h"

genericDialog::genericDialog(QString label_text, QString ok_text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::genericDialog)
{
    ui->setupUi(this);
    ui->ph_label->setText(label_text);
    ui->ph_ok->setText(ok_text);
}

genericDialog::~genericDialog()
{
    delete ui;
}

void genericDialog::on_ph_ok_clicked()
{

}
