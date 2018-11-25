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

    void display_results();
    void get_cpu_info();

private slots:
    void on_quit_button_clicked();
    void on_reset_button_clicked();
    void on_save_result_button_clicked();
    void on_submit_button_clicked();
    void quit();
    double time_to_score(double time);

private:
    Ui::ResultWindow *ui;

    QStringList m_names;

    std::vector<double> m_results;
    std::vector<std::string> m_sys_info;
    std::vector<std::string> m_sys_info_labels {"vendor", "model", "speed", "threads",
                                              "byte_order", "physical", "virtual", "swap"};
    double m_total_time = 0;
    double m_total_score = 0;

    bool m_ocflag;
    bool m_standard_flag;
};

#endif // RESULTWINDOW_H
