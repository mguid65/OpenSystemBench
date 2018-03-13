#include "Algorithms/headers/algorithm.h"
#include <vector>
#include "headers/runningwindow.h"


class BenchBuilder {
    public:
        BenchBuilder();
        BenchBuilder(bool *config_, RunningWindow* running_);
        double *runBench();
        void createStandardBench();
        std::vector <Algorithm> algList;
    private:
        RunningWindow *running;
};
