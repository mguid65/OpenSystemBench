#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QMainWindow>

namespace Ui {
class ResultWindow;
}

class ResultWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ResultWindow(QWidget *parent = 0, double *result=0);
    ~ResultWindow();
    void displayResults();

private slots:
    void on_quit_button_clicked();
    void quit();
    void on_reset_button_clicked();

private:
    Ui::ResultWindow *ui;
    double *result;
    //ConfigWindow * configWindow;
};

#endif // RESULTWINDOW_H
