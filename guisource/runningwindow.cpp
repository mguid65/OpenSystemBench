#include "headers/runningwindow.h"
#include "ui_runningwindow.h"
#include <chrono>
#include <thread>

RunningWindow::RunningWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RunningWindow)
{
    ui->setupUi(this);
}

RunningWindow::~RunningWindow()
{
    delete ui;
}

void RunningWindow::updateText(const QString& text) {
    ui->run_status_viewer->textUpdate(text);
}

void RunningWindow::on_quit_button2_clicked()
{
    quit();
}
void RunningWindow::quit() {
    this->close();
}
void RunningWindow::handleFinished(double *result) {
    this->close();
    resultWindow = new ResultWindow(0,result);
    resultWindow->show();
}
