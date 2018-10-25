//Abstract Algorithm Strategy
//Matthew Guidry March 2018
//
#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H

#include <string>
using namespace std;

class AlgorithmInterface {
    public:
        virtual string getName() = 0;
        virtual double runAlgorithm() = 0;
        virtual ~AlgorithmInterface(){}
};

#endif /* ALGORITHMINTERFACE_H */
