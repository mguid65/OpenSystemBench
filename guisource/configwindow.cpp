#include "configwindow.h"
#include "ui_configwindow.h"
#include ""
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
    ui->CPU_check->setEnabled(checked & true);
    ui->IO_check->setEnabled(checked & true);
}

void ConfigWindow::on_quit_button_clicked()
{
    quit();
}

void ConfigWindow::on_run_button_clicked()
{
    bool config [4] = { false, false, false, false };
    if(ui->stan_radio->isChecked()) {
        config[0] = true;
    }
    else {
        config [1] = true;
        if (ui->CPU_check->isChecked()) {
            config[2] = true;
        }
        if (ui->IO_check->isChecked()) {
            config[3] = true;
        }
    }
    createRunWindow();
    quit();
}
