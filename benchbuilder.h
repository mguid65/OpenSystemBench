#include <vector>
#include "headers/runningwindow.h"
#include "headers/thread.h"

class BenchBuilder {
    public:
        BenchBuilder();
        BenchBuilder(bool *config_, RunningWindow* running_, Thread * pass);
        void runBench();
        void createStandardBench();
        std::vector <Algorithm> algList;
    private:
        RunningWindow *running;
        Thread * pass;
};
