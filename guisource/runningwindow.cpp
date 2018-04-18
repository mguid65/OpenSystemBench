#include "headers/runningwindow.h"
#include "ui_runningwindow.h"
#include <chrono>
#include <thread>

RunningWindow::RunningWindow(bool standard_flag, bool ocflag, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RunningWindow)
{
    this->ocflag = ocflag;
    this->standard_flag = standard_flag;
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
void RunningWindow::handleResult(double result){
    results.push_back(result);
}
void RunningWindow::handleFinished(QStringList names) {
    this->close();
    resultWindow = new ResultWindow(standard_flag, ocflag,results, names,0);
    resultWindow->show();
    resultWindow->displayResults();
}
