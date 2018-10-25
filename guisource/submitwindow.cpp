#include "submitwindow.h"
#include "ui_submitwindow.h"
#include <curl/curl.h>

/* parameterized constructor grenerated by qt creator
 * takes a parent window
 * modified to take a name string
 */
SubmitWindow::SubmitWindow(std::string json_str, QWidget *parent) :
                           QDialog(parent), ui(new Ui::SubmitWindow),
                           json_str(json_str) {
  ui->setupUi(this);
  ui->password_val->setEchoMode(QLineEdit::Password);
}
/* destructor generated by qt */
SubmitWindow::~SubmitWindow() {
    delete ui;
}

/* cancel button clicked event closed this window and whole application */
void SubmitWindow::on_cancelButton_clicked() {
    this->close();
}

/* submit button appends results to a name string and opens a tcp socket
   directly based on example from libcurl
*/

void SubmitWindow::on_submitButton_clicked() {
  CURL *curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://opensystembench.com/submit");
#ifdef SKIP_PEER_VERIFICATION
    /*
     * If you want to connect to a site who isn't using a certificate that is
     * signed by one of the certs in the CA bundle you have, you can skip the
     * verification of the server's certificate. This makes the connection
     * A LOT LESS SECURE.
     *
     * If you have a CA cert for the server stored someplace else than in the
     * default bundle, then the CURLOPT_CAPATH option might come handy for
     * you.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    /*
     * If the site you're connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl will refuse to connect. You can skip
     * this check, but this will make the connection less secure.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
    curl_easy_setopt(curl, CURLOPT_USERNAME, ui->username_val->text().toStdString().c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, ui->password_val->text().toStdString().c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_str.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, -1L);
    //curl_easy_setopt(curl, CURLOPT_AB);
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      ui->responseLabel->setText("HTTPS Post Request failed: " + QString(curl_easy_strerror(res)) + '\n');

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
    /*QString qname = ui->nameInput->text();
    if(qname.length() < 1 || qname.length() > 40) {
        QString no = "Invalid Name!";
        ui->responseLabel->setText(no);
    }
    else {
        std::string name = qname.toStdString();
        //append the str field to the name
        name.append(";");
        name.append(str);
        //create a TCPClient object
        TCPClient tcp;
        //this is the server address and port hosting the listener
        //if setup returns false, connection failed
        if(tcp.setup("72.219.21.177", 47002) != true ) {
            QString fail = "Connection Failure";
            ui->responseLabel->setText(fail);
            this->close();
        }

        srand(time(nullptr));

        //send the string
        tcp.Send(name);

        //recieve server reply
        string rec = tcp.receive();

        //if reply is not null, exit
        if( rec != "" )
        {
            //this should set status label to upload success and disable the submit button in future
            tcp.exit();
            this->close();
        }
        else {
            //if response is empty, set status label
            tcp.exit();
            QString empty = "Empty Response";

            ui->responseLabel->setText(empty);
        }
    }
    */
    this->close();
}
