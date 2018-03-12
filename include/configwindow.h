#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QMainWindow>
#include "runningwindow.h"

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
    void createRunWindow();

private:
    RunningWindow *runningWindow;

private slots:
    void on_cust_radio_toggled(bool checked);

    void on_quit_button_clicked();

    void on_run_button_clicked();

    void quit();

private:
    Ui::ConfigWindow *ui;
};

#endif // CONFIGWINDOW_H
