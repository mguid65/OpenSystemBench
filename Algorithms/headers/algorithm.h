//Header for Algorithm strategy
//Matthew Guidry March 2018
//
#include "nbody.h"

class Algorithm;

class Algorithm {
    public:
        Algorithm();
        Algorithm(AlgorithmInterface *algorithm);
        void runAlgorithm();
        string getName();
        double getTime();
    private:
        AlgorithmInterface *algorithm_;
        double cpuTime;
        void setTime(double t);
};
