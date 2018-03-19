#include "benchbuilder.h"
#include <string>
#include <sstream>
#include <QThread>
#include <QStringList>

BenchBuilder::BenchBuilder(){}
BenchBuilder::BenchBuilder(bool *config_, RunningWindow *running_,Thread *pass_) {
    pass=pass_;
    running = running_;
    if(config_[0]) {
        createStandardBench();
    }
    else {
        if(config_[2]) {
            if(config_[3]){
                algList.push_back(new NBody());
            }
            if(config_[4]) {
                algList.push_back(new PiDigits());
            }
            if(config_[5]) {
                algList.push_back(new Mandelbrot());
            }
        }
        if(config_[6]) {
            //temporary
            algList.push_back(nullptr);
        }
    }
}
void BenchBuilder::runBench() {
    QStringList names;
    for (Algorithm &alg : algList ) {
        string name = alg.getName();
        QString qname = QString::fromStdString(name);
        names<<qname;
        emit pass->signalText(qname);

        alg.runAlgorithm();

        double time_ = alg.getTime();

        string strtime = to_string(time_);
        emit pass->signalText(QString::fromStdString(strtime));

        emit pass->signalResult(time_);
    }
    //the next few lines are only for user experience
    emit pass->signalText(QString::fromStdString("Preparing Results..."));
    //give a status update and wait so a user can read it before jumping to results window
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));

    emit pass->finished(names);
}

void BenchBuilder::createStandardBench() {
    algList.push_back(new NBody());
    algList.push_back(new PiDigits());
    algList.push_back(new Mandelbrot());
}
