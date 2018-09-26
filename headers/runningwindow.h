#ifndef RUNNINGWINDOW_H
#define RUNNINGWINDOW_H
#include "headers/runninglog.h"
#include "headers/resultwindow.h"
#include <QMainWindow>
#include <vector>

namespace Ui {
class RunningWindow;
}

class RunningWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RunningWindow(bool standard_flag, bool ocflag, QWidget *parent = 0);
    ~RunningWindow();
private:
    ResultWindow * resultWindow;
    std::vector<double> results;
    Ui::RunningWindow *ui;
    bool ocflag;
    bool standard_flag;
    QStringList names_;
public slots:
    void updateText(const QString& text);
    void handleResult(double result);
    void handleFinished(QStringList names);
private slots:
    void on_quit_button2_clicked();
    void quit();

    void on_cont_button_clicked();
};

#endif // RUNNINGWINDOW_H
