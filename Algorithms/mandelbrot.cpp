/* The Computer Language Benchmarks Game
 https://salsa.debian.org/benchmarksgame-team/benchmarksgame/
 contributed by Ralph Ganszky
 modified for Swift 3.0 by Daniel Muellenborn
 modified for C & gcc by Dominic Letz

 Compile with: gcc -O3 -mno-fma -march=native -fopenmp main.c
 */

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include "../Algorithms/headers/abstract.h"

int Iter = 50;

typedef double Vec __attribute__ ((vector_size(16)));
const int Vec__size = sizeof(Vec)/sizeof(double);
typedef unsigned char Byte;

int bt(Vec lhs, double rhs) {
  for (int i = 0; i < Vec__size; i++)
    if (lhs[i] <= rhs)
      return 0;
  return 1;
}

// Calculate mandelbrot set for one Vec into one byte
Byte mand(Vec cr, Vec ci) {
  Vec Zr = {0.0};
  Vec Zi = {0.0};
  Vec Tr = {0.0};
  Vec Ti = {0.0};

  for (int i = 0; i < Iter/5; i++) {
    for (int j = 0; j < 5; j++) {
      Zi = (Zr + Zr) * Zi + ci;
      Zr = Tr - Ti + cr;
      Tr = Zr * Zr;
      Ti = Zi * Zi;
    }
    if (bt(Tr + Ti, 4.0)) {
       return 0;
    }
  }
  Byte byte = 0;
  Vec t = Tr + Ti;
  for (int i = 0; i < Vec__size; i++) {
    byte |= t[i] <= 4.0 ? (0x80 >> i) : 0;
  }
  return byte;
}

Mandelbrot::Mandelbrot() {}
double Mandelbrot::runAlgorithm()
{

    // calculate initial x values, store in r0
    auto begin = std::chrono::high_resolution_clock::now();

    int n = 16000;
    int N = (n + Vec__size - 1) & ~(Vec__size - 1);
    double inv = 2.0 / ((double)n);
    Vec xvals[N/Vec__size];
    Vec yvals[N];
    Byte *rows = (Byte *)malloc(n*N/8);

    for (int i = 0; i < N; i++) {
      xvals[i/Vec__size][i%Vec__size] = ((double)i) * inv - 1.5;
      for (int j = 0; j < Vec__size; j++) {
        yvals[i][j] = ((double)i) * inv - 1.0;
      }
    }

    #pragma omp parallel for schedule(guided)
    for (int y = 0; y < n; y++) {
      for (int x = 0; x < N/Vec__size; x+=8/Vec__size) {
        Byte b = 0;
        for (int v = 0; v < 8/Vec__size; v++) {
          b |= mand(xvals[x + v], yvals[y]) >> (v*Vec__size);
        }
        rows[y*N/8+x/(8/Vec__size)] = b;
      }
    }

    free(rows);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    return duration / 1E9;
}

string Mandelbrot::getName() {
    return "Mandelbrot";
}
