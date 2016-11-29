
#ifndef PREPAIDMANAGER_H_
#define PREPAIDMANAGER_H_

#include "stdafx.h"

class CPrepaidManager : public Singleton<CPrepaidManager>
{
    public:
        void LoadPrepaidFromDB();
        void PushRecharge(UINT64 qwRoleID, UINT32 dwValue);
        UINT32 PopRecharge(UINT64 qwRoleID);

    private:
        map<UINT64, UINT32> _mapPrepaid;    //玩家预充值仙石
};

#endif // PREPAIDMANAGER_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

