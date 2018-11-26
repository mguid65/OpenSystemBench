//Header for Concrete Algorithm Strategies
//Matthew Guidry March 2018
//
#ifndef ABSTRACT_H
#define ABSTRACT_H

#include "algorithminterface.h"

//Subclass NBody implements AlgorithmInterface
class NBody: public AlgorithmInterface {
public:
    NBody() {}
    std::string getName();
    double runAlgorithm();
    ~NBody(){}
};

//Subclass PiDigits implements AlgorithmInterface
class PiDigits: public AlgorithmInterface {
public:
    PiDigits() {}
    std::string getName();
    double runAlgorithm();
    ~PiDigits(){}
};

//Subclass Mandelbrot implements AlgorithmInterface
class Mandelbrot: public AlgorithmInterface {
public:
    Mandelbrot() {}
    std::string getName();
    double runAlgorithm();
    ~Mandelbrot(){}
};

//Subclass SpectralNorm implements AlgorithmInterface
class SpectralNorm: public AlgorithmInterface {
public:
    SpectralNorm() {}
    std::string getName();
    double runAlgorithm();
    ~SpectralNorm(){}
};

//Subclass BinaryTrees implements AlgorithmInterface
class BinaryTrees: public AlgorithmInterface {
public:
    BinaryTrees() {}
    std::string getName();
    double runAlgorithm();
    ~BinaryTrees(){}
};

#endif /*ABSTRACT_H*/
