#include "runningwindow.h"
#include "ui_runningwindow.h"

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
