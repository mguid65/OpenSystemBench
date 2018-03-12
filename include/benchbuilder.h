#include "Algorithms/algorithm.h"

class BenchBuilder {
    public:
        BenchBuilder();
        BenchBuilder(bool *config_);
        void createAlgObjects();
        vector<Algorithm> getAlgList();
        void runBench();
    private:
        vector<Algorithm> algList;
};
