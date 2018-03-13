#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include <QString>

class Thread : public QThread
{
 Q_OBJECT

signals:
 void signalText(QString);

protected:
 virtual void run();
};

#endif // THREAD_H
