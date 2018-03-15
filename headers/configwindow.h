#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include "headers/runningwindow.h"
#include "headers/nooptionsselected.h"
#include <QMainWindow>

namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigWindow(QWidget *parent = 0);
    ~ConfigWindow();

public slots:
    void createRunWindow(bool *config_);

private:
    RunningWindow *runningWindow;

private slots:
    void on_cust_radio_toggled(bool checked);

    void on_quit_button_clicked();

    void on_run_button_clicked();

    void quit();

    void on_CPU_check_toggled(bool checked);

private:
    Ui::ConfigWindow *ui;
};

#endif // CONFIGWINDOW_H
