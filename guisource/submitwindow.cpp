#include "submitwindow.h"
#include "ui_submitwindow.h"
#include "client/src/TCPClient.h"

SubmitWindow::SubmitWindow(std::string str, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubmitWindow)
{
    ui->setupUi(this);
    this->str = str;
}

SubmitWindow::~SubmitWindow()
{
    delete ui;
}

void SubmitWindow::on_cancelButton_clicked()
{
    this->close();
}

void SubmitWindow::on_submitButton_clicked()
{
    QString qname = ui->nameInput->text();
    if(qname.length() < 1 || qname.length() > 40) {
        QString no = "Invalid Name!";
        ui->responseLabel->setText(no);
    }
    else {
        std::string name = qname.toStdString();

        name.append(";");
        name.append(str);

        TCPClient tcp;
        if(tcp.setup("72.219.21.177", 47002) != true ) {
            QString fail = "Connection Failure";
            ui->responseLabel->setText(fail);
            this->close();
        }

        srand(time(NULL));
        //std::cout << name;
        tcp.Send(name);

        string rec = tcp.receive();

        if( rec != "" )
        {
            tcp.exit();
            this->close();
        }
        else {
            tcp.exit();
            QString empty = "Empty Response";

            ui->responseLabel->setText(empty);
        }
    }
}
