#include "genericdialog.h"
#include "ui_genericdialog.h"

genericDialog::genericDialog(QString label_text, QString ok_text, QString window_title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::genericDialog)
{
    ui->setupUi(this);
    ui->ph_label->setText(label_text);
    ui->ph_ok->setText(ok_text);
    this->setWindowTitle(window_title);
}

genericDialog::~genericDialog()
{
    delete ui;
}

void genericDialog::quit()
{
    this->close();
}

void genericDialog::on_ph_ok_clicked()
{
    quit();
}
