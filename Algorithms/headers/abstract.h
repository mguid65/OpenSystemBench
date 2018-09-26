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
        ~NBody(){}
};

class PiDigits: public AlgorithmInterface {
    public:
        PiDigits();
        std::string getName();
        double runAlgorithm();
        ~PiDigits(){}
};

class Mandelbrot: public AlgorithmInterface {
    public:
        Mandelbrot();
        std::string getName();
        double runAlgorithm();
        ~Mandelbrot(){}
};

class SpectralNorm: public AlgorithmInterface {
    public:
        SpectralNorm();
        std::string getName();
        double runAlgorithm();
        ~SpectralNorm(){}
};

class BinaryTrees: public AlgorithmInterface {
    public:
        BinaryTrees();
        std::string getName();
        double runAlgorithm();
        ~BinaryTrees(){}
};

#endif /*ABSTRACT_H*/
