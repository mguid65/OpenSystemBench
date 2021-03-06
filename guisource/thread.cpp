#include "headers/thread.h"
#include "headers/benchbuilder.h"

/* Implementation of the thread class which overrides QThread */
Thread::Thread(bool * config, RunningWindow * runningWindow, QWidget *parent) :
    QThread(parent){
    this->config = config;
    this->runningWindow = runningWindow;
}

Thread::~Thread(){}
void Thread::run() {
    BenchBuilder b(config, runningWindow, this);
    b.runBench();
}
