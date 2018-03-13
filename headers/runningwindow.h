#ifndef RUNNINGWINDOW_H
#define RUNNINGWINDOW_H
#include "headers/runninglog.h"

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
public slots:
    void updateText(const QString& text);
private slots:
    void on_quit_button2_clicked();

private:
    Ui::RunningWindow *ui;
};

#endif // RUNNINGWINDOW_H
