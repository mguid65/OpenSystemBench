#include "headers/runningwindow.h"
#include "ui_runningwindow.h"
#include <chrono>
#include <thread>

RunningWindow::RunningWindow(bool STANDARD_FLAG, bool OCFLAG, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RunningWindow)
{
    this->OCFLAG = OCFLAG;
    this->STANDARD_FLAG = STANDARD_FLAG;
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
    resultWindow = new ResultWindow(STANDARD_FLAG, OCFLAG,results, names,0);
    resultWindow->show();
    resultWindow->displayResults();
}
