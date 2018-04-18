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
    explicit SubmitWindow(std::string str,QWidget *parent = 0);
    ~SubmitWindow();

private slots:
    void on_cancelButton_clicked();

    void on_submitButton_clicked();

private:
    Ui::SubmitWindow *ui;
    std::string str;
};

#endif // SUBMITWINDOW_H
