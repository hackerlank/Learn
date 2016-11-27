#ifndef KEY_H
#define KEY_H

#include "zType.h"
#include "zMisc.h"
#include <set>

//两个DWORD合成一个key
QWORD hashKey(const DWORD key1,const DWORD key2);

DWORD hashKey(const WORD key1,const WORD key2);

//从容器中随机出一个建
bool randKey(const std::set<DWORD>& randSet,DWORD &ret);

#endif
