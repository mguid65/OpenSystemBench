//Tester for Algorithm Strategy
//Matthew Guidry March 2018
//
#include "Algorithms/headers/algorithm.h"
#include <iostream>

using namespace std;
int main() {
    Algorithm alg(new NBody());
    alg.runAlgorithm();
    double nbodytime = alg.getTime();
    cout << nbodytime << "\n";
    return 0;
}
