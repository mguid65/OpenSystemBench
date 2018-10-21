#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include <QString>
#include "Algorithms/headers/algorithm.h"
#include "headers/runningwindow.h"

class Thread : public QThread
{
    Q_OBJECT

public:
    Thread(bool * config, RunningWindow * runningWindow);
    ~Thread();
signals:
    void finished(QStringList);
    void signalResult(double);
    void signalText(QString);
    void signalCPUText(QString);

protected:
    virtual void run();

private:
    RunningWindow * runningWindow;
    bool * config;
};

#endif // THREAD_H
