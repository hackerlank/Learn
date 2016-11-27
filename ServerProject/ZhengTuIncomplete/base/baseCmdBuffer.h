#ifndef BASE_CMD_BUFFER_H
#define BASE_CMD_BUFFER_H 

#include "baseConstruct.h"

#ifndef BUFFER_CMD
#define BUFFER_CMD(cmd,name,len) char buffer##name[len]={0};cmd *name=(cmd*)buffer##name;constructInPlace(name)
#endif

#endif
