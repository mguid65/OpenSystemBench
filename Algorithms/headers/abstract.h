//Header for Concrete Algorithm Strategies
//Matthew Guidry March 2018
//
#ifndef ABSTRACT_H
#define ABSTRACT_H

#include "algorithminterface.h"

class NBody: public AlgorithmInterface {
    public:
        NBody();
        std::string getName();
        double runAlgorithm();
};

class PiDigits: public AlgorithmInterface {
    public:
        PiDigits();
        std::string getName();
        double runAlgorithm();
};

class Mandelbrot: public AlgorithmInterface {
    public:
        Mandelbrot();
        std::string getName();
        double runAlgorithm();
};

class SpectralNorm: public AlgorithmInterface {
    public:
        SpectralNorm();
        std::string getName();
        double runAlgorithm();
};

class BinaryTrees: public AlgorithmInterface {
    public:
        BinaryTrees();
        std::string getName();
        double runAlgorithm();
};

#endif /*ABSTRACT_H*/
