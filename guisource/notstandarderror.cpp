#include "headers/notstandarderror.h"
#include "ui_notstandarderror.h"

NotStandardError::NotStandardError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotStandardError)
{
    ui->setupUi(this);
}

NotStandardError::~NotStandardError()
{
    delete ui;
}

void NotStandardError::quit() {
    this->close();
}
void NotStandardError::on_pushButton_clicked()
{
    quit();
}
