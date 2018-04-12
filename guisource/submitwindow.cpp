#include "submitwindow.h"
#include "ui_submitwindow.h"

SubmitWindow::SubmitWindow(std::string str, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubmitWindow)
{
    ui->setupUi(this);
    this->str = str;
}

SubmitWindow::~SubmitWindow()
{
    delete ui;
}

void SubmitWindow::on_cancelButton_clicked()
{
    this->close();
}


void SubmitWindow::on_submitButton_clicked()
{
    QString qname = ui->nameInput->text();
    std::string name = qname.toLocal8Bit();
    name.append(";");
    name.append(str);

}
