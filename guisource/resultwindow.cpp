#include "headers/resultwindow.h"
#include "ui_resultwindow.h"

ResultWindow::ResultWindow(QWidget *parent, double result[]) :
    QMainWindow(parent),
    ui(new Ui::ResultWindow)
{
    this->result = result;
    ui->setupUi(this);
}

ResultWindow::~ResultWindow()
{
    delete ui;
}

void ResultWindow::displayResults() {
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(3);
}
