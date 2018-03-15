#include "headers/nooptionsselected.h"
#include "ui_nooptionsselected.h"

NoOptionsSelected::NoOptionsSelected(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoOptionsSelected)
{
    ui->setupUi(this);
}

NoOptionsSelected::~NoOptionsSelected()
{
    delete ui;
}
void NoOptionsSelected::quit() {
    this->close();
}
void NoOptionsSelected::on_pushButton_clicked()
{
    quit();
}
