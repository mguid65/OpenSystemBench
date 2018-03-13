//Abstract Algorithm Strategy
//Matthew Guidry March 2018
//
#include <string>
using namespace std;

class AlgorithmInterface {
    public:
        virtual string getName() = 0;
        virtual double runAlgorithm() = 0;

};
