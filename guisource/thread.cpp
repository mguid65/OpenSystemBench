#include "headers/thread.h"
#include "benchbuilder.h"

Thread::Thread(bool * config, RunningWindow * runningWindow){
    this->config = config;
    this->runningWindow = runningWindow;
}
Thread::~Thread(){}
void Thread::run() {
    BenchBuilder b(config ,runningWindow, this);
    b.runBench();
}
