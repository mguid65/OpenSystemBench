#include "headers/runninglog.h"

RunningLog::RunningLog(QWidget*parent):QPlainTextEdit(parent) {

}
void RunningLog::textUpdate(const QString& text)
{
    this->appendPlainText(text);
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());
}
