//Header for Algorithm strategy
//Matthew Guidry March 2018
//
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "abstract.h"
#include <string>

//class Algorithm;
//Algorithm strategy models an algorithm
class Algorithm {
public:
    Algorithm();
    Algorithm(AlgorithmInterface *algorithm);

    void runAlgorithm();
    std::string getName();
    double getTime();
private:
    void setTime(double t);
    AlgorithmInterface *algorithm_;
    double m_cpuTime;
};

#endif /* ALGORITHM_H */
