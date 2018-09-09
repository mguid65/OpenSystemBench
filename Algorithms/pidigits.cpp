/* The Computer Language Benchmarks Game
 * http://benchmarksgame.alioth.debian.org/
 *
 * contributed by Alessandro Power
 * modified for use as concrete strategy for OpenSystemBench, by Matthew Guidry
 */

#include <iostream>
#include <chrono>
#include "../Algorithms/headers/abstract.h"

#define SCALE 10000
#define ARRINIT 2000

double pi_digits(long digits) {
    double sum = 0.0;
    int sign = 1;
    for (long i = 0; i < digits; ++i) {
        sum += sign/(2.0*i+1.0);
        sign *= -1;
    }
    return 4.0*sum;
}

double PiDigits::runAlgorithm() {

    auto begin = std::chrono::high_resolution_clock::now();

    double result = pi_digits(5000000000);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    return duration / 1E9;
}

PiDigits::PiDigits() {}
string PiDigits::getName() {
    return "PiDigits";
}
