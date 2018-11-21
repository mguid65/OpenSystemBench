#include "headers/resultwindow.h"
#include "headers/configwindow.h"
#include "headers/submitwindow.h"
#include "headers/genericdialog.h"
#include "sysinfo/cpuinfo.h"

#include "ui_resultwindow.h"

#include <QString>
#include <QVariant>
#include <QFileDialog>
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdio>

/* parameterized constructor generated by qt creator with initializer list*/
ResultWindow::ResultWindow(bool standard_flag, bool ocflag, std::vector<double> results, const QStringList& names, QWidget *parent) :
     QMainWindow(parent), ui(new Ui::ResultWindow),
     m_names(names), m_results(results),
     m_ocflag(ocflag), m_standard_flag(standard_flag) {
    ui->setupUi(this);
}

/* destructor generated by qt creator */
ResultWindow::~ResultWindow() {
    delete ui;
}
/* method to convert time to score */
double ResultWindow::time_to_score(double time) {
    m_total_time +=time;
    double score = (.001/(time/1E9))*10000000;
    m_total_score +=score;
    return score;
}
/* iterate through vectors and put results in table */
void ResultWindow::display_results() {
    QStringList table_list;

    table_list << "Algorithm" << "Time" << "Score";

    ui->result_table->setColumnCount(3);
    ui->result_table->setHorizontalHeaderLabels(table_list);

    int row {0};

    foreach(const QString str, m_names) {
        ui->result_table->insertRow(row);
        QTableWidgetItem *newItem = ui->result_table->item(row,0);

        if(!newItem) {
            newItem = new QTableWidgetItem;
            ui->result_table->setItem(row,0,newItem);
        }
        newItem->setText(str);
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        newItem->setTextAlignment( Qt::AlignCenter);

        row++;
    }
    row = 0;
    for(unsigned int i = 0; i < m_results.size(); i++) {
        QTableWidgetItem *newItem = ui->result_table->item(row,1);
        QTableWidgetItem *newScore = ui->result_table->item(row,2);

        if(!newItem) {
            newItem = new QTableWidgetItem;
            ui->result_table->setItem(row,1,newItem);
        }
        if(!newScore) {
            newScore = new QTableWidgetItem;
            ui->result_table->setItem(row,2,newScore);
        }
        newItem->setData(Qt::DisplayRole, QVariant(m_results[i]/1E9));
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        newItem->setTextAlignment( Qt::AlignCenter);

        double score = time_to_score(m_results[i]);

        newScore->setData(Qt::DisplayRole, QVariant(score));
        newScore->setFlags(newScore->flags() ^ Qt::ItemIsEditable);
        newScore->setTextAlignment( Qt::AlignCenter);

        row++;
    }
    QString total {"Totals:"};
    ui->result_table->insertRow(row);
    QTableWidgetItem *totalStr = ui->result_table->item(row,0);
    QTableWidgetItem *totTime = ui->result_table->item(row,1);
    QTableWidgetItem *totScore = ui->result_table->item(row,2);

    if(!totalStr) {
        totalStr = new QTableWidgetItem;
        ui->result_table->setItem(row, 0, totalStr);
    }
    if(!totTime) {
        totTime = new QTableWidgetItem;
        ui->result_table->setItem(row, 1, totTime);
    }
    if(!totScore) {
        totScore = new QTableWidgetItem;
        ui->result_table->setItem(row, 2, totScore);
    }
    totalStr->setText(total);
    totalStr->setFlags(totalStr->flags() ^ Qt::ItemIsEditable);
    totalStr->setTextAlignment( Qt::AlignCenter);

    totTime->setData(Qt::DisplayRole, QVariant(m_total_time/1E9));
    totTime->setFlags(totTime->flags() ^ Qt::ItemIsEditable);
    totTime->setTextAlignment( Qt::AlignCenter);

    totScore->setData(Qt::DisplayRole, QVariant(m_total_score));
    totScore->setFlags(totScore->flags() ^ Qt::ItemIsEditable);
    totScore->setTextAlignment( Qt::AlignCenter);

    ui->result_table->resizeColumnsToContents();
    get_cpu_info();
}

void ResultWindow::get_cpu_info() {
  CPUInfo cpu;

  m_sys_info.push_back(cpu.vendor());
  m_sys_info.push_back(cpu.model());
  m_sys_info.push_back(cpu.speed());
  //m_sys_info.push_back(cpu.frequencies());
  m_sys_info.push_back(cpu.threads());
  m_sys_info.push_back(cpu.byte_ordering());
  m_sys_info.push_back(cpu.physical_mem());
  m_sys_info.push_back(cpu.virtual_mem());
  m_sys_info.push_back(cpu.swap_mem());

  for(size_t i = 0; i < m_sys_info.size(); i++) {
    if((m_sys_info[i].find('\n') != string::npos))
      m_sys_info[i].erase(m_sys_info[i].find(EOF));
  }

  ui->vendor_val->setText(QString::fromStdString(m_sys_info[0]));
  ui->model_val->setText(QString::fromStdString(m_sys_info[1]));
  ui->speed_val->setText(QString::fromStdString(m_sys_info[2]));
  //ui->freq_val->setText(QString::fromStdString(m_sys_info[3]));
  ui->thread_val->setText(QString::fromStdString(m_sys_info[3]));
  ui->byte_order_val->setText(QString::fromStdString(m_sys_info[4]));
  ui->phy_mem_val->setText(QString::fromStdString(m_sys_info[5]));
  ui->virt_mem_val->setText(QString::fromStdString(m_sys_info[6]));
  ui->swap_mem_val->setText(QString::fromStdString(m_sys_info[7]));
}


/* quit function */
void ResultWindow::quit() {
    this->close();
}
/* button slot calls quit */
void ResultWindow::on_quit_button_clicked()
{
    quit();
}
/* quits the result window and runs a new config window */
void ResultWindow::on_reset_button_clicked()
{
    quit();
    ConfigWindow * configWindow = new ConfigWindow();
    configWindow->show();
}
/* opens a file save dialog,  generates a csv string, saves to file */
void ResultWindow::on_save_result_button_clicked()
{
     QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), ".csv");
     QFile f(fileName);
     f.open(QIODevice::WriteOnly);
     char comma[] = ",";
     char end[] = ",\n";
     char headers[] = "Algorithm,Time,Score,\n";
     f.write(headers);
     for(int i = 0; i < m_names.length(); ++i) {
      f.write(ui->result_table->item(i,0)->text().toLocal8Bit());
      f.write(comma);
      f.write(ui->result_table->item(i,1)->text().toLocal8Bit());
      f.write(comma);
      f.write(ui->result_table->item(i,2)->text().toLocal8Bit());
      f.write(end);
     }
     f.close();
}
/* desc: Manually generate a json string for submission
   ret: void
   param: none
   error_handling:
     check standard flag: Executes NotStandardError dialog
*/
void ResultWindow::on_submit_button_clicked()
{
    if(m_standard_flag) {
        //start json string manually
        std::string json_str = "{ \"scores\" : [ ";

        for(int i = 0; i < m_names.length(); i++) {
          json_str.append("{ \"name\" : \"" + m_names[i].toLocal8Bit() + "\", ");
          json_str.append(" \"time\" : ");
          json_str.append(std::to_string(m_results[static_cast<unsigned long>(i)]) + ", ");
          json_str.append("\"score\" : " + ui->result_table->item(i,2)->text().toLocal8Bit() + " }, ");
        }
        json_str.append(" { \"name\" : \"Total\",");
        json_str.append("\"time\" : " + std::to_string(m_total_time) + ", ");
        json_str.append("\"score\" : " + std::to_string(m_total_score) + " ");

        json_str.append("} ],");
        if(m_ocflag)
          json_str.append("\"specs\" : { \"overclocked\" : true, ");
        else
          json_str.append("\"specs\" : { \"overclocked\" : false, ");

        for(size_t i = 0; i < m_sys_info.size(); i++) {
          //create tmp string to strip unexpected characters ie \0 EOF from string
          string tmp_info = m_sys_info[i];
          tmp_info.erase(std::remove(tmp_info.begin(), tmp_info.end(), '\0'), tmp_info.end());
          json_str.append("\"" + m_sys_info_labels[i] + "\" : \"" + tmp_info + "\"");
          if(i + 1 < m_sys_info.size()) {
              json_str.append(", ");
          }
        }
        json_str.append(" } }");
        std::cout << json_str << '\n';
        SubmitWindow submitWindow(json_str);
        submitWindow.exec();
    }
    else {
      genericDialog notStandard("Non-standard benchmark!", "OK", "Error");
      notStandard.exec();
    }
}
