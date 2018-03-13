#ifndef RUNNINGLOG_H
#define RUNNINGLOG_H

#include <QPlainTextEdit>
#include <QScrollBar>

class RunningLog;

class RunningLog : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit RunningLog(QWidget*parent);
    void textUpdate(const QString& text);
};

#endif // RUNNINGLOG_H
