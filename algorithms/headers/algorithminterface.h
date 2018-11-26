//Abstract Algorithm Strategy
//Matthew Guidry March 2018
//
#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H

#include <string>

//Algorithm Interface models the interface methods to a concrete algorithm
class AlgorithmInterface {
public:
    virtual std::string getName() = 0;
    virtual double runAlgorithm() = 0;
    virtual ~AlgorithmInterface(){}
};

#endif /* ALGORITHMINTERFACE_H */
