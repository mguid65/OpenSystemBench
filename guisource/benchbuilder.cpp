#include "headers/benchbuilder.h"
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <QThread>
#include <QStringList>

/* empty constructor does nothing */
BenchBuilder::BenchBuilder(){}

/* parameterized constructor takes a config array an instance of a running window to perform operations on
 * and a thread to run algorithms in
 */
BenchBuilder::BenchBuilder(bool config[], RunningWindow *running,Thread *pass) {
    m_pass = pass;
    m_running = running;

    if(config[0]) {
        createStandardBench();
    } else {
        if(config[2]) m_algList.push_back(std::make_unique<Algorithm>(new NBody()));
        if(config[3]) m_algList.push_back(std::make_unique<Algorithm>(new PiDigits()));
        if(config[4]) m_algList.push_back(std::make_unique<Algorithm>(new Mandelbrot()));
        if(config[5]) m_algList.push_back(std::make_unique<Algorithm>(new SpectralNorm()));
        if(config[6]) m_algList.push_back(std::make_unique<Algorithm>(new BinaryTrees()));
    }
}
/* this method runs all algorithms in the vector m_algList */
void BenchBuilder::runBench() {
    QStringList names;

    for (auto &alg : m_algList ) {
        std::string name = alg->getName();
        QString qname = QString::fromStdString(name);
        names << qname;
        emit m_pass->signalText(qname);

        alg->runAlgorithm();

        double time = alg->getTime();

        std::string strtime = std::to_string(time/1E9);
        emit m_pass->signalText(QString::fromStdString(strtime));

        emit m_pass->signalResult(time);
    }
    //the next few lines are only for user experience
    emit m_pass->signalText(QString::fromStdString("Finished!"));
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    emit m_pass->finished(names);
}
/* if standard option in config just create a vector with all available algorithms */
void BenchBuilder::createStandardBench() {
    m_algList.push_back(std::make_unique<Algorithm>(new NBody()));
    m_algList.push_back(std::make_unique<Algorithm>(new PiDigits()));
    m_algList.push_back(std::make_unique<Algorithm>(new Mandelbrot()));
    m_algList.push_back(std::make_unique<Algorithm>(new SpectralNorm()));
    m_algList.push_back(std::make_unique<Algorithm>(new BinaryTrees()));
}
