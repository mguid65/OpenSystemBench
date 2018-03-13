#include "benchbuilder.h"
#include <string>
#include <sstream>

BenchBuilder::BenchBuilder(){}
BenchBuilder::BenchBuilder(bool *config_, RunningWindow *running_) {
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
double* BenchBuilder::runBench() {

    double results[algList.size()];
    int i=0;

    for (Algorithm &alg : algList ) {
        running->repaint();
        string name = alg.getName();
        QString qstr = QString::fromStdString(name);
        running->updateText(qstr);

        alg.runAlgorithm();

        double time_ = alg.getTime();

        string strtime = to_string(time_);
        QString qstrtime = QString::fromStdString(strtime);
        running->updateText(qstrtime);
        running->repaint();
        results[i] = time_;
        i++;
    }
    return results;
}

void BenchBuilder::createStandardBench() {
    algList.push_back(new NBody());
}
