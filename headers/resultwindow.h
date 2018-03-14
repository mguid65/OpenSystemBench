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

private:
    Ui::ResultWindow *ui;
    double *result;
};

#endif // RESULTWINDOW_H
