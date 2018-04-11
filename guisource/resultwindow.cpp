#include "headers/resultwindow.h"
#include "headers/configwindow.h"
#include "ui_resultwindow.h"
#include <QString>
#include <iostream>
#include <QVariant>
#include <QFileDialog>
#include <vector>
#include <string>
#include <iostream>

ResultWindow::ResultWindow(std::vector<double> results, const QStringList& names, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ResultWindow)
{
    this->results = results;
    this->names = names;
    ui->setupUi(this);
}

ResultWindow::~ResultWindow()
{
    delete ui;
}

double ResultWindow::convertTimeToScore(double time) {
    return (.001/time)*10000000;
}

void ResultWindow::displayResults() {
    QStringList table_list;

    table_list << "Algorithm" << "Time" << "Score";

    //ui->result_table->setRowCount(12);
    ui->result_table->setColumnCount(3);

    ui->result_table->setHorizontalHeaderLabels(table_list);

    int row = 0;

    foreach(const QString str, names) {
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
    for(unsigned int i = 0; i < results.size(); i++) {
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
        newItem->setData(Qt::DisplayRole, QVariant(results[i]));
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        newItem->setTextAlignment( Qt::AlignCenter);

        double score = convertTimeToScore(results[i]);

        newScore->setData(Qt::DisplayRole, QVariant(score));
        newScore->setFlags(newScore->flags() ^ Qt::ItemIsEditable);
        newScore->setTextAlignment( Qt::AlignCenter);

        row++;
    }
}
void ResultWindow::quit() {
    this->close();
}

void ResultWindow::on_quit_button_clicked()
{
    quit();
}

void ResultWindow::on_reset_button_clicked()
{
    quit();
    ConfigWindow * configWindow = new ConfigWindow();
    configWindow->show();
}

void ResultWindow::on_save_result_button_clicked()
{
     QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), ".csv");
     QFile f(fileName);
     f.open(QIODevice::WriteOnly);
     char comma[] = ",";
     char end[] = ",\n";
     char headers[] = "Algorithm,Time,Score,\n";
     f.write(headers);
     for(int i = 0; i < names.length(); ++i) {
        f.write(ui->result_table->item(i,0)->text().toLocal8Bit());
        f.write(comma);
        f.write(ui->result_table->item(i,1)->text().toLocal8Bit());
        f.write(comma);
        f.write(ui->result_table->item(i,2)->text().toLocal8Bit());
        f.write(end);
     }
     f.close();

}

void ResultWindow::on_submit_button_clicked()
{
    std::string str;
    for(int i = 0; i < names.length(); i++) {
        for(int j = 0; j < 3; j++) {
            str.append(ui->result_table->item(i,j)->text().toLocal8Bit());
        }
    }
    std::cout << str;
}
