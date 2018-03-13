//Context for algorithm strategy
//Matthew Guidry March 2018
//
#include "Algorithms/headers/algorithm.h"

Algorithm::Algorithm(AlgorithmInterface *algorithm) {
    algorithm_ = algorithm;
}
void Algorithm::runAlgorithm() {
    double time_ = algorithm_->runAlgorithm();
    setTime(time_);
}
string Algorithm::getName() {
    return algorithm_->getName();
}
double Algorithm::getTime() {
    return cpuTime;
}
void Algorithm::setTime(double t) {
    cpuTime = t;
}
