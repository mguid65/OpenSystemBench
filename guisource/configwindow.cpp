#include "headers/configwindow.h"
#include "headers/thread.h"
#include "ui_configwindow.h"
#include <QThread>

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
    runningWindow = new RunningWindow();
    runningWindow->show();

    QThread* thread = new QThread;
    Thread* worker = new Thread(config_, runningWindow);

    worker->moveToThread(thread);

    connect(worker, SIGNAL(signalText(QString)), runningWindow, SLOT(updateText(QString)));
    connect(worker, SIGNAL(signalResult(double)), runningWindow, SLOT(handleResult(double)));
    connect(worker, SIGNAL(finished(QStringList)), runningWindow, SLOT(handleFinished(QStringList)));

    worker->start();

    runningWindow->updateText(QString::fromStdString("Running..."));
    quit();
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
    bool config [6] = { false, false, false, false, false, false };
    if(ui->stan_radio->isChecked()) {
        config[0] = true;
        createRunWindow(config);
    }
    else {
        config [1] = true;
        if(ui->CPU_check->isChecked() || ui->IO_check->isChecked()){
            if (ui->CPU_check->isChecked()) {
                config[2] = true;
                if(ui->nbody->isChecked() || ui->pidigits->isChecked()) {
                    if(ui->nbody->isChecked()) {
                        config[3] = true;
                    }
                    if(ui->pidigits->isChecked()) {
                        config[4] = true;
                    }
                    createRunWindow(config);
                }
                else {
                    NoOptionsSelected errDialog;
                    errDialog.exec();
                }
                if (ui->IO_check->isChecked()) {
                    config[5] = true;
                    createRunWindow(config);
                }
            }
            else {
                NoOptionsSelected errDialog;
                errDialog.exec();
            }

        }
    }
}

void ConfigWindow::on_CPU_check_toggled(bool checked){
    ui->nbody->setEnabled(checked & true);
    ui->pidigits->setEnabled(checked & true);
}
