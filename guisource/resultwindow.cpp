#include "headers/resultwindow.h"
#include "ui_resultwindow.h"
#include "headers/configwindow.h"
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
    ui->result_table->setRowCount(10);
    ui->result_table->setColumnCount(3);
}
void ResultWindow::quit() {
    this->close();
}

void ResultWindow::on_quit_button_clicked()
{
    quit();
}

void ResultWindow::on_reset_button_clicked()
{
    quit();
    ConfigWindow * configWindow = new ConfigWindow();
    configWindow->show();
}
