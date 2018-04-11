#ifndef SUBMITWINDOW_H
#define SUBMITWINDOW_H

#include <QDialog>

namespace Ui {
class SubmitWindow;
}

class SubmitWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SubmitWindow(QWidget *parent = 0);
    ~SubmitWindow();

private slots:
    void on_cancelButton_clicked();

private:
    Ui::SubmitWindow *ui;
};

#endif // SUBMITWINDOW_H
