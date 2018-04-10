/* The Computer Language Benchmarks Game
 * http://benchmarksgame.alioth.debian.org/
 *
 * contributed by Jon Harrop
 * modified by Alex Mizrahi
 * modified by Andreas Schäfer
 * very minor omp tweak by The Anh Tran
 * Jeff Wofford: replaced omp dependency with C++11 threading and load-based job distribution.
 *  *reset*
 * Modified for opensystembench by matthew guidry 2018
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <vector>
#include "Algorithms/headers/abstract.h"

#include <boost/pool/object_pool.hpp>


const size_t   LINE_SIZE = 64;


struct Node
{
   Node *l, *r;

   Node() : l(0), r(0)
   {}
   Node(Node *l2, Node *r2) : l(l2), r(r2)
   {}

   int check() const
   {
      if (l)
         return l->check() + 1 + r->check();
      else return 1;
   }
};

typedef boost::object_pool<Node> NodePool;


Node *make(int d, NodePool &store)
{
   if (d > 0)
      return store.construct(   make(d-1, store),
                        make(d-1, store)   );
   return store.construct();
}

const unsigned THREADS_TO_USE = std::max( 1U, std::min( 4U, std::thread::hardware_concurrency() ));

double BinaryTrees::runAlgorithm()
{
   const int min_depth = 4;
   const int max_depth = 23;
   const int stretch_depth = max_depth+1;
   auto begin = std::chrono::high_resolution_clock::now();
   // Alloc then dealloc stretchdepth tree
   {
      NodePool store;
      Node *c = make(stretch_depth, store);
      //std::cout << "stretch tree of depth " << stretch_depth << "\t "
              //<< "check: " <<
      c->check(); //<< std::endl;
   }

   NodePool long_lived_store;
   Node *long_lived_tree = make(max_depth, long_lived_store);

   // buffer to store output of each thread
   std::unique_ptr< char > outputstr{ new char[ LINE_SIZE * (max_depth + 1)] };

   std::mutex mutex;
   int nextDepthToProcess = min_depth;

   const auto work = [&]()
   {
      while(true)
      {
         std::unique_lock< decltype(mutex) > lock(mutex);
         const int d = nextDepthToProcess;
         if(d > max_depth)
         {
            return;
         }
         nextDepthToProcess += 2;
         lock.unlock();

         const int iterations = 1 << (max_depth - d + min_depth);
         int checksum = 0;

         for(int i = 1; i <= iterations; ++i)
         {
            NodePool store;
            Node *a = make(d, store);
            checksum += a->check();
         }

         // each thread write to separate location
         sprintf(outputstr.get() + LINE_SIZE * d, "%d\t trees of depth %d\t check: %d\n", iterations, d, checksum);
      }
   };

   std::vector< std::thread > threads(THREADS_TO_USE - 1);
   for(auto& thread : threads)
   {
      thread = std::thread{ work };
   }

   work();

   for(auto& thread : threads)
   {
      thread.join();
   }


   long_lived_tree->check();

   auto end = std::chrono::high_resolution_clock::now();
   auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
   return duration / 1E9;
}
BinaryTrees::BinaryTrees(){}
string BinaryTrees::getName() {
    return "Binary Trees";
}
