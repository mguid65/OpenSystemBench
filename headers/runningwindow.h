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
    explicit RunningWindow(QWidget *parent = 0);
    ~RunningWindow();
private:
    ResultWindow * resultWindow;
public slots:
    void updateText(const QString& text);
    void handleResult(double result);
    void handleFinished(QStringList names);
private slots:
    void on_quit_button2_clicked();
    void quit();
private:
    std::vector<double> results;
    Ui::RunningWindow *ui;
};

#endif // RUNNINGWINDOW_H
