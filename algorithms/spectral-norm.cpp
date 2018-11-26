/* The Computer Language Benchmarks Game
 http://benchmarksgame.alioth.debian.org/
 Original C contributed by Sebastien Loisel
 Conversion to C++ by Jon Harrop
 OpenMP parallelize by The Anh Tran
 Add SSE by The Anh Tran
 Additional SSE optimization by Krzysztof Jakubowski
 Modified for OpenSystemBench by Matthew Guidry 2018
*/


/* The Computer Language Benchmarks Game
 * https://salsa.debian.org/benchmarksgame-team/benchmarksgame/
 *
 * Contributed by Mr Ledrug
 *
 * Algorithm lifted from Intel Fortran #2 code by Steve Decker et al.
*/

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <omp.h>
#include <chrono>
#include "../algorithms/headers/abstract.h"


inline int A(int i, int j) {
   return ((i+j) * (i+j+1) / 2 + i + 1);
}

double dot(double * v, double * u, int n) {
   int i;
   double sum = 0;
   for (i = 0; i < n; i++)
      sum += v[i] * u[i];
   return sum;
}

void mult_Av(double * v, double * out, const int n) {
   int i, j;
   double sum;
#   pragma omp parallel for private(sum,j)
   for (i = 0; i < n; i++) {
      for (sum = j = 0; j < n; j++)
         sum += v[j] / A(i,j);
      out[i] = sum;
   }
}

void mult_Atv(double * v, double * out, const int n) {
   int i, j;
   double sum;
#   pragma omp parallel for private(sum,j)
   for (i = 0; i < n; i++) {
      for (sum = j = 0; j < n; j++)
         sum += v[j] / A(j,i);
      out[i] = sum;
   }
}

double *tmp;
void mult_AtAv(double *v, double *out, const int n) {
   mult_Av(v, tmp, n);
   mult_Atv(tmp, out, n);
}

void spec_norm() {
   int n = 9500;

   double *u, *v;
   u = (double *)malloc(n * sizeof(double));
   v = (double *)malloc(n * sizeof(double));
   tmp = (double *)malloc(n * sizeof(double));

   int i;
   for (i = 0; i < n; i++) u[i] = 1;
   for (i = 0; i < 10; i++) {
      mult_AtAv(u, v, n);
      mult_AtAv(v, u, n);
   }

}

//implements the runAlgorithm method of AlgorithmInterface
//returns a runtime
double SpectralNorm::runAlgorithm() {

    auto begin = std::chrono::high_resolution_clock::now();

    spec_norm();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    return duration;

}

//implements the getName mehtod of AlgorithmInterface
//get the name of the algorithm
std::string SpectralNorm::getName() {
    return "Spectral-Norm";
}
