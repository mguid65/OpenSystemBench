#include "headers/configwindow.h"
#include "headers/thread.h"
#include "ui_configwindow.h"
#include <QThread>

ConfigWindow::ConfigWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);
    ocflag=0;
    standard_flag=0;
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
    runningWindow = new RunningWindow(standard_flag, ocflag);
    runningWindow->show();

    QThread* thread = new QThread;
    Thread* worker = new Thread(config_, runningWindow);

    worker->moveToThread(thread);

    connect(worker, SIGNAL(signalText(QString)), runningWindow, SLOT(updateText(QString)));
    connect(worker, SIGNAL(signalCPUText(QString)), runningWindow, SLOT(updateCPUInfo(QString)));
    connect(worker, SIGNAL(signalResult(double)), runningWindow, SLOT(handleResult(double)));
    connect(worker, SIGNAL(finished(QStringList)), runningWindow, SLOT(handleFinished(QStringList)));

    worker->start();

    runningWindow->updateText(QString::fromStdString("Running..."));
    runningWindow->updateCPUInfo(QString::fromStdString("CPU Info:"));

    quit();
}

void ConfigWindow::on_cust_radio_toggled(bool checked)
{
    ui->CPU_check->setEnabled(checked & true);
    ui->IO_check->setEnabled(checked & true);

    if(ui->CPU_check->isChecked()) {
        ui->nbody->setEnabled(true);
        ui->pidigits->setEnabled(true);
        ui->mandelbrot->setEnabled(true);
        ui->single->setEnabled(true);
        ui->multi->setEnabled(true);
        ui->spectral->setEnabled(true);
    }
    if(ui->IO_check->isChecked()) {
        ui->binarytrees->setEnabled(true);
    }

    //ui->IO_check->setEnabled(checked & true);
}

void ConfigWindow::on_quit_button_clicked()
{
    quit();
}

/* I want to split this function to make it easier to understand and maintain
 * There should be a private field with a config array within the config window
 * Each checkbox slot should only set its own array value
 * A seperate function will check if no configurations are set
 * the run function will just run this check function then pass its config to the builder
 *
 * also these classes should not be calling each other, they should have get methods to return data to the next window
 */
void ConfigWindow::on_run_button_clicked()
{
    standard_flag = ui->stan_radio->isChecked();
    //remove this array and make a map
    bool config [9] = { false, false, false, false, false, false, false, false, false };
    //standard test
    if(ui->stan_radio->isChecked()) {
        config[0] = true;
        createRunWindow(config);
    } // custom test
    else {
        config [1] = true;
        if(ui->CPU_check->isChecked() || ui->IO_check->isChecked()) {

            config[2] = ui->CPU_check->isChecked();
            config[7] = ui->IO_check->isChecked();

            if(ui->nbody->isChecked() ||
               ui->pidigits->isChecked() ||
               ui->mandelbrot->isChecked() ||
               ui->spectral->isChecked() ||
               ui->binarytrees->isChecked()) {

                //single core
                config[3] = ui->nbody->isChecked();
                //single core
                config[4] = ui->pidigits->isChecked();
                //multi core
                config[5] = ui->mandelbrot->isChecked();
                //multi-core
                config[6] = ui->spectral->isChecked();
                //IO
                config[8] = ui->binarytrees->isChecked();
                createRunWindow(config);

            }
            else {
                NoOptionsSelected errDialog;
                errDialog.exec();
            }
        }
        else {
            NoOptionsSelected errDialog;
            errDialog.exec();
        }
    }
}

void ConfigWindow::on_CPU_check_toggled(bool checked){
    ui->nbody->setEnabled(checked & true);
    ui->pidigits->setEnabled(checked & true);
    ui->mandelbrot->setEnabled(checked & true);
    ui->single->setEnabled(checked & true);
    ui->multi->setEnabled(checked & true);
    ui->spectral->setEnabled(checked & true);
}


void ConfigWindow::on_stan_radio_toggled()
{
    ui->nbody->setEnabled(false);
    ui->pidigits->setEnabled(false);
    ui->mandelbrot->setEnabled(false);
    ui->single->setEnabled(false);
    ui->multi->setEnabled(false);
    ui->spectral->setEnabled(false);
    ui->binarytrees->setEnabled(false);
}


void ConfigWindow::on_IO_check_toggled(bool checked)
{
    ui->binarytrees->setEnabled(checked & true);
}


void ConfigWindow::on_ocbutton_toggled()
{
    ocflag = ui->ocbutton->isChecked();
}
