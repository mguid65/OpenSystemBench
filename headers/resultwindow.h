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
    explicit ResultWindow(bool standard_flag, bool ocflag, std::vector<double> results, const QStringList& names, QWidget *parent = nullptr );
    ~ResultWindow();
    void displayResults();
    void getCpuInfo();

private slots:
    void on_quit_button_clicked();
    void quit();
    void on_reset_button_clicked();
    double convertTimeToScore(double time);
    void on_save_result_button_clicked();
    void on_submit_button_clicked();

private:
    Ui::ResultWindow *ui;
    QStringList names;
    std::vector<double> results;
    double totalTime = 0;
    double totalScore = 0;
    bool ocflag;
    bool standard_flag;
};

#endif // RESULTWINDOW_H
