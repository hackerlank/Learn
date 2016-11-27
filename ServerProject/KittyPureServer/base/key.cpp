#include "key.h"

QWORD hashKey(const DWORD key1,const DWORD key2)
{
    return (key1 << 8) + key2;
}
DWORD hashKey(const WORD key1,const WORD key2)
{
    return (key1 << 8) + key2;
}

bool randKey(const std::set<DWORD>& randSet,DWORD &ret)
{
    DWORD randVal = zMisc::randBetween(1,randSet.size());
    DWORD num = 1;
    for(auto iter = randSet.begin();iter != randSet.end();++iter,++num)
    {
        if(num == randVal)
        {
            ret = *iter;
            return true;
        }
    }
    return false;
}
            
