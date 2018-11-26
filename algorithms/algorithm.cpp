//Context for algorithm strategy
//Matthew Guidry March 2018
//

#include "../algorithms/headers/algorithm.h"

Algorithm::Algorithm(AlgorithmInterface *algorithm) {
    algorithm_ = algorithm;
}
void Algorithm::runAlgorithm() {
    double time_ = algorithm_->runAlgorithm();
    setTime(time_);
}
std::string Algorithm::getName() {
    return algorithm_->getName();
}
double Algorithm::getTime() { //calculated at the bottom of each algorithm 
    return m_cpuTime;
}
void Algorithm::setTime(double t) { //calculated at the bottom of each algorithm 
    m_cpuTime = t;
}
