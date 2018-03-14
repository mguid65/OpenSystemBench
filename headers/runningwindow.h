#ifndef RUNNINGWINDOW_H
#define RUNNINGWINDOW_H
#include "headers/runninglog.h"
#include "headers/resultwindow.h"
#include <QMainWindow>

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
    void handleFinished(double* result);
private slots:
    void on_quit_button2_clicked();
    void quit();
private:
    Ui::RunningWindow *ui;
};

#endif // RUNNINGWINDOW_H
