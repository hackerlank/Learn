#ifndef HEAD_H
#define HEAD_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//主要是通过管道的读写阻塞来达到进程间的同步
int initPipe();

void waitPipe();

void notifyPipe();

void destroyPipe();

#endif
