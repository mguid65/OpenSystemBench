#include "headers/runningwindow.h"
#include "ui_runningwindow.h"
#include <chrono>
#include <thread>

/* parameterized constructor generated by qt creator
 * added standard_flag and ocflag
 */
RunningWindow::RunningWindow(bool standard_flag, bool ocflag, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RunningWindow)
{
    this->ocflag = ocflag;
    this->standard_flag = standard_flag;
    ui->setupUi(this);
}
/* destructor generated by qt creator */
RunningWindow::~RunningWindow()
{
    delete ui;
}
/* function to update the text in the running log*/
void RunningWindow::updateText(const QString& text) {
    ui->run_status_viewer->textUpdate(text);
}
/* quit button*/
void RunningWindow::on_quit_button2_clicked()
{
    quit();
}
/* quit function closes the app */
void RunningWindow::quit() {
    this->close();
}
/*handle a result by putting it in the list*/
void RunningWindow::handleResult(double result){
    results.push_back(result);
}
/*handle finished by closing the running window and creating a result window */
void RunningWindow::handleFinished(QStringList names) {
    names_ = names;
    this->close();
    resultWindow = new ResultWindow(standard_flag, ocflag,results, names_, nullptr);
    resultWindow->show();
    resultWindow->display_results();
}
