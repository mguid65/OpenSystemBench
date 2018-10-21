#include "headers/cpulog.h"
/* contructor extends QPlainTextEdit object */
CPULog::CPULog(QWidget*parent):QPlainTextEdit(parent) {}
/* cpu log function to append text and auto scroll window*/
void CPULog::textUpdate(const QString& text)
{
    this->appendPlainText(text);
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());
}
