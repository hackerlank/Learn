#include "PrepaidManager.h"
#include "RoleInfoDefine.h"
#include "Protocols.h"

void CPrepaidManager::LoadPrepaidFromDB()
{
    g_Center2DBCommC.Send_LoadPrepaid([this](UINT8 byRet_ /*0为成功，1为失败，2为超时*/, const NRoleInfoDefine::TVecPrepaid& vecPrepaid)
        {
            if(0 != byRet_)
            {
                LOG_CRI<<"LoadPrepaidFromDB fail!!";
                return;
            }
            _mapPrepaid.clear();
            for (size_t i = 0; i < vecPrepaid.size(); ++ i)
            {
                _mapPrepaid.insert(make_pair(vecPrepaid[i].qwRoleID, vecPrepaid[i].dwGold));
            }
        });
}

void CPrepaidManager::PushRecharge(UINT64 qwRoleID, UINT32 dwValue)
{
    if (!qwRoleID || !dwValue)
        return;
    UINT32& dwAllGold = _mapPrepaid[qwRoleID];
    dwAllGold += dwValue;

    g_Center2DBCommC.Send_UpdatePrepaid(eOpUpdate, qwRoleID, dwAllGold);
}

UINT32 CPrepaidManager::PopRecharge(UINT64 qwRoleID)
{
    UINT32 dwAllGold = 0;
    if (!qwRoleID)
        return dwAllGold;
    auto iter = _mapPrepaid.find(qwRoleID);
    if (iter == _mapPrepaid.end())
        return dwAllGold;

    dwAllGold = iter->second;
    _mapPrepaid.erase(iter);
    g_Center2DBCommC.Send_UpdatePrepaid(eOpDel, qwRoleID, dwAllGold);
    return dwAllGold;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

