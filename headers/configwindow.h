#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include "headers/runningwindow.h"
#include "headers/genericdialog.h"
#include <QMainWindow>

namespace Ui {
class ConfigWindow;
}

//ConfigWindow models the configuration window
class ConfigWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigWindow(QWidget *parent = nullptr);
    ~ConfigWindow();

private:
    RunningWindow *runningWindow;
    Ui::ConfigWindow *ui;
    bool m_ocflag;
    bool m_standard_flag;
    bool m_config[7] { true, false, false, false, false, false, false};

public slots:
    void createRunWindow(bool config[]);

private slots:
    void on_cust_radio_toggled(bool checked);
    void on_quit_button_clicked();
    void on_run_button_clicked();
    void quit();
    //functions to set positions in m_config
    void on_CPU_check_toggled(bool checked);
    void on_stan_radio_toggled();
    void on_IO_check_toggled(bool checked);
    void on_ocbutton_toggled();
    void on_nbody_clicked(bool checked);
    void on_pidigits_clicked(bool checked);
    void on_mandelbrot_clicked(bool checked);
    void on_spectral_clicked(bool checked);
    void on_binarytrees_clicked(bool checked);
};

#endif // CONFIGWINDOW_H
