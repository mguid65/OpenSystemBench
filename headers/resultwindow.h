#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QFile>
namespace Ui {
class ResultWindow;
}

class ResultWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ResultWindow(std::vector<double> results, const QStringList& names, QWidget *parent = 0 );
    ~ResultWindow();
    void displayResults();

private slots:
    void on_quit_button_clicked();
    void quit();
    void on_reset_button_clicked();
    double convertTimeToScore(double time);

    void on_save_result_button_clicked();

private:
    Ui::ResultWindow *ui;
    QStringList names;
    std::vector<double> results;
    //ConfigWindow * configWindow;
};

#endif // RESULTWINDOW_H
