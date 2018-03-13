#include "headers/runningwindow.h"
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

void RunningWindow::updateText(const QString& text) {
    ui->plainTextEdit->textUpdate(text);
}

void RunningWindow::on_quit_button2_clicked()
{
    this->close();
}
