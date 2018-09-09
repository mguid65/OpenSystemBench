//Context for algorithm strategy
//Matthew Guidry March 2018
//

#include "../Algorithms/headers/algorithm.h"

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
double Algorithm::getTime() { //calculated at the bottom of each algorithm 
    return cpuTime;
}
void Algorithm::setTime(double t) { //calculated at the bottom of each algorithm 
    cpuTime = t;
}
