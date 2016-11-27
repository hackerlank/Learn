#include "baseTaskThread.h"
TaskThread::TaskThread(const char *name,bool joinable):Thread(name,joinable)
{
}
TaskThread::~TaskThread()
{
}

