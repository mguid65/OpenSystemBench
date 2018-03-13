#include "headers/configwindow.h"
#include "ui_configwindow.h"
#include "benchbuilder.h"
#include "thread.h"

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

void ConfigWindow::createRunWindow(bool *config_)
{
    quit();
    runningWindow = new RunningWindow();

    runningWindow->show();

    runningWindow->updateText(QString::fromStdString("Running..."));

    BenchBuilder b(config_ ,runningWindow);
    double *results = b.runBench();
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
    //this needs to be put inside a Thread so it doesnt interrupt the main event loop
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

    createRunWindow(config);
}
