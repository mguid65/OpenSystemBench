//Header for Nbody concrete Algorithm Strategy
//Matthew Guidry March 2018
//
#include "algorithminterface.h"

class NBody: public AlgorithmInterface {
    public:
        NBody();
        std::__cxx11::string getName();
        double runAlgorithm();
};
