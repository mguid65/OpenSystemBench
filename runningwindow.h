#ifndef RUNNINGWINDOW_H
#define RUNNINGWINDOW_H

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
    Ui::RunningWindow *ui;
};

#endif // RUNNINGWINDOW_H
