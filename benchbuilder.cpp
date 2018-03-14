#include "benchbuilder.h"
#include <string>
#include <sstream>
#include <QThread>

BenchBuilder::BenchBuilder(){}
BenchBuilder::BenchBuilder(bool *config_, RunningWindow *running_,Thread *pass_) {
    pass=pass_;
    running = running_;
    if(config_[0]) {
        createStandardBench();
    }
    else {
        if(config_[2]) {
            algList.push_back(new NBody());
        }
        if(config_[3]) {
            //temporary
            algList.push_back(nullptr);
        }
    }
}
void BenchBuilder::runBench() {

    double results[algList.size()];
    int i=0;

    for (Algorithm &alg : algList ) {
        string name = alg.getName();
        emit pass->signalText(QString::fromStdString(name));

        alg.runAlgorithm();

        double time_ = alg.getTime();

        string strtime = to_string(time_);
        emit pass->signalText(QString::fromStdString(strtime));

        results[i] = time_;
        i++;
    }

    emit pass->finished(results);
}

void BenchBuilder::createStandardBench() {
    algList.push_back(new NBody());
}
