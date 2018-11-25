
/* The Computer Language Benchmarks Game
 * https://salsa.debian.org/benchmarksgame-team/benchmarksgame/
 *
 * Contributed by Jon Harrop
 * Modified by Alex Mizrahi
 *  *reset*
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include "../algorithms/headers/abstract.h"

struct Node {
  Node *l, *r;
  Node() : l(0), r(0) {}
  Node(Node *l2, Node *r2) : l(l2), r(r2) {}
  ~Node() { delete l; delete r; }
  int check() const {
      if (l)
        return l->check() + 1 + r->check();
      else return 1;
  }
};

Node *make(int d) {
  if (d == 0) return new Node();
  return new Node(make(d-1), make(d-1));
}

int bin_tree() {
  int min_depth = 4,
    max_depth = std::max(min_depth+2,
             (18)),
    stretch_depth = max_depth+1;

  {
    Node *c = make(stretch_depth);
    delete c;
  }

  Node *long_lived_tree=make(max_depth);

  for (int d=min_depth; d<=max_depth; d+=2) {
    int iterations = 1 << (max_depth - d + min_depth), c=0;
    for (int i=1; i<=iterations; ++i) {
      Node *a = make(d);
      c += a->check();
      delete a;
    }
  }

  delete long_lived_tree;

  return 0;
}

double BinaryTrees::runAlgorithm()
{
    auto begin = std::chrono::high_resolution_clock::now();

    volatile int result = bin_tree();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    return duration;
}
BinaryTrees::BinaryTrees(){}
string BinaryTrees::getName() {
    return "Binary-Trees";
}
