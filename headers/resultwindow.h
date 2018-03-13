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
    explicit ResultWindow(QWidget *parent = 0);
    ~ResultWindow();

private:
    Ui::ResultWindow *ui;
};

#endif // RESULTWINDOW_H
