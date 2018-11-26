#include <vector>
#include "headers/runningwindow.h"
#include "headers/thread.h"
#include <memory>

//Benchbuilder creates a list of algorithms and runs them
class BenchBuilder {
    public:
        BenchBuilder();
        BenchBuilder(bool config[], RunningWindow* running, Thread *pass);
        void runBench();
        void createStandardBench();
    private:
        RunningWindow *m_running;
        Thread *m_pass;
        std::vector <std::unique_ptr<Algorithm>> m_algList;
};
