#ifndef NOOPTIONSSELECTED_H
#define NOOPTIONSSELECTED_H

#include <QDialog>

namespace Ui {
class NoOptionsSelected;
}

class NoOptionsSelected : public QDialog
{
    Q_OBJECT

public:
    explicit NoOptionsSelected(QWidget *parent = 0);
    ~NoOptionsSelected();

private slots:
    void on_pushButton_clicked();
    void quit();
private:
    Ui::NoOptionsSelected *ui;
};

#endif // NOOPTIONSSELECTED_H
