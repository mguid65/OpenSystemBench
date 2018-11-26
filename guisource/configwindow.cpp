#include "headers/configwindow.h"
#include "headers/thread.h"
#include "ui_configwindow.h"
#include <QThread>
#include <memory>

ConfigWindow::ConfigWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);
    m_ocflag=0;
    m_standard_flag=0;
}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}
void ConfigWindow::quit()
{
    this->close();
}

void ConfigWindow::createRunWindow(bool config[])
{
    runningWindow = new RunningWindow(m_standard_flag, m_ocflag);
    runningWindow->show();

    auto thread = new QThread;
    auto worker = new Thread(config, runningWindow);

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
}

void ConfigWindow::on_quit_button_clicked()
{
    quit();
}

/* I fixed these functions and then all my changes vanished
 */
void ConfigWindow::on_run_button_clicked()
{
    m_standard_flag = ui->stan_radio->isChecked();

    if(m_config[0]) {
        createRunWindow(m_config);
    } else {
        if(m_config[2] || m_config[3] || m_config[4] || m_config[5] || m_config[6]) {
            createRunWindow(m_config);
        }
        else {
            genericDialog errDialog("No Options Selected", "OK", "Error", this);
            errDialog.exec();
        }
    }
}

void ConfigWindow::on_CPU_check_toggled(bool checked)
{
    m_config[0] = false;
    m_config[1] = true;

    ui->nbody->setEnabled(checked & true);
    ui->pidigits->setEnabled(checked & true);
    ui->mandelbrot->setEnabled(checked & true);
    ui->single->setEnabled(checked & true);
    ui->multi->setEnabled(checked & true);
    ui->spectral->setEnabled(checked & true);
}


void ConfigWindow::on_stan_radio_toggled()
{
    m_config[0] = true;
    m_config[1] = false;

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
    m_ocflag = ui->ocbutton->isChecked();
}

//these functions set array positions in the config array
void ConfigWindow::on_nbody_clicked(bool checked)
{
    m_config[2] = checked;
}

void ConfigWindow::on_pidigits_clicked(bool checked)
{
    m_config[3] = checked;
}

void ConfigWindow::on_mandelbrot_clicked(bool checked)
{
    m_config[4] = checked;
}

void ConfigWindow::on_spectral_clicked(bool checked)
{
    m_config[5] = checked;
}

void ConfigWindow::on_binarytrees_clicked(bool checked)
{
    m_config[6] = checked;
}
