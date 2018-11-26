#include "headers/runninglog.h"

/* contructor extends QPlainTextEdit object */
RunningLog::RunningLog(QWidget*parent):QPlainTextEdit(parent) {}

/* running log function to append text and auto scroll window*/
void RunningLog::textUpdate(const QString& text)
{
    this->appendPlainText(text);
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());
}
