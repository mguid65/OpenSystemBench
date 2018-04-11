#include "submitwindow.h"
#include "ui_submitwindow.h"

SubmitWindow::SubmitWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubmitWindow)
{
    ui->setupUi(this);
}

SubmitWindow::~SubmitWindow()
{
    delete ui;
}

void SubmitWindow::on_cancelButton_clicked()
{
    this->close();
}

