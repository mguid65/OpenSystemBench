//Header for Concrete Algorithm Strategies
//Matthew Guidry March 2018
//
#include "algorithminterface.h"

class NBody: public AlgorithmInterface {
    public:
        NBody();
        std::__cxx11::string getName();
        double runAlgorithm();
};

class PiDigits: public AlgorithmInterface {
    public:
        PiDigits();
        std::__cxx11::string getName();
        double runAlgorithm();
};

class Mandelbrot: public AlgorithmInterface {
    public:
        Mandelbrot();
        std::__cxx11::string getName();
        double runAlgorithm();
};
