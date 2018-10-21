#ifndef CPULOG_H
#define CPULOG_H

#include <QPlainTextEdit>
#include <QScrollBar>

class CPULog;

class CPULog : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit CPULog(QWidget*parent);
    void textUpdate(const QString& text);
};


#endif // CPULOG_H
