#include "configwindow.h"
#include "ui_configwindow.h"

ConfigWindow::ConfigWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);
}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}
void ConfigWindow::quit()
{
    this->close();
}

void ConfigWindow::createRunWindow()
{
    runningWindow = new RunningWindow();

    runningWindow->show();
}

void ConfigWindow::on_cust_radio_toggled(bool checked)
{
    ui->GPU_check->setEnabled(checked & true);
    ui->CPU_check->setEnabled(checked & true);
    ui->IO_check->setEnabled(checked & true);
}

void ConfigWindow::on_quit_button_clicked()
{
    quit();
}

void ConfigWindow::on_run_button_clicked()
{
    createRunWindow();
    quit();
}
