#include "RTime.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "QQAlarm.h"
#include "Loot.h"
#include "Player.h"

CQQAlarmMgr g_QQAlarmMgr;

ELevelActStatus CQQAlarmMgr::TakePrize(CUser &rUser,UINT16 wActID)
{
     UINT64 qwRoleID = rUser.GetRoleID();
     ELevelActStatus eResult = eLevleActStatus_Error;
     UINT32 qwVar = rUser.GetVars().GetVar(NVarDefine::ePlayerQQAlarm);
     bool bCheck = qwVar & 1;
     if(!bCheck)
     {
        LOG_INF <<" NotFix QQAlarm";
        eResult = eLevleActStatus_Init;
        rUser.GetPlayer()->SendPkg(g_LevelPrizeSvrS.BuildPkg_SendStateForQQAlarm(wActID,eResult));
        return eResult;
     }else
     {
        bCheck = qwVar & (1 << 1);
        if(bCheck)
        {
            LOG_INF <<" qwRoleID(" <<qwRoleID<<") TakePrize twice!";
            eResult = eLevleActStatus_GetPrize;
            rUser.GetPlayer()->SendPkg(g_LevelPrizeSvrS.BuildPkg_SendStateForQQAlarm(wActID,eResult));
            return  eResult;
        }
        if(_setUser.count(qwRoleID))
        {
            LOG_INF <<" TakePrize processing...";
            rUser.GetPlayer()->SendPkg(g_LevelPrizeSvrS.BuildPkg_SendStateForQQAlarm(wActID,eResult));
            return eResult;
        }
        _setUser.insert(qwRoleID);
        UINT32 dwLootID = SParamConfig::wQqRemind; 
        if(dwLootID == 0)
        {
            LOG_INF <<" dwLootID 0";
            _setUser.erase(qwRoleID);
            rUser.GetPlayer()->SendPkg(g_LevelPrizeSvrS.BuildPkg_SendStateForQQAlarm(wActID,eResult));
            return eResult;
        }
        TVecItemGenInfo vecItems;
        TVecResource vecRes;
        LOOT.Roll(dwLootID, vecItems,vecRes);
        for(auto it=vecRes.begin(); it!=vecRes.end(); ++it)
        {
            SItemGenInfo tepInfo;
            SResource &rRes = *it;
            tepInfo.wItemID = rRes._eRes;
            tepInfo.dwCount = rRes._dwValue;
            vecItems.push_back(tepInfo);
        }
        if(!vecItems.empty())
        {
            CPack& oPack = rUser.GetPack();
            if(!oPack.CanAddItem(vecItems))
            {
                _setUser.erase(qwRoleID);
                eResult = eLevleActStatus_FullPack;
            }
            else
            {
                oPack.AddItem(vecItems,NLogDataDefine::ItemFrom_QQAlarm);
                qwVar = qwVar | (1 << 1);
                rUser.GetVars().SetVar(NVarDefine::ePlayerQQAlarm, qwVar);
                eResult = eLevleActStatus_Success;
                rUser.GetPlayer()->SendPkg(g_LevelPrizeSvrS.BuildPkg_SendStateForQQAlarm(wActID,eResult));
                
                {
                    TVecINT32 vecParam;
                    INT32 dwEvent = 1;
                    vecParam.push_back(dwEvent);
                    CEventMgrPtr pEventMgr = rUser.GetPlayer()->GetEventMgr();
                    if(pEventMgr)
                        pEventMgr->OnEvent(eEventType_QQAlarmGift,vecParam);
                }
            }
        }
        else 
            _setUser.erase(qwRoleID);
     }
     return eResult;
}

void CQQAlarmMgr::GetState(CUser &rUser,UINT16 wActID)
{
    ELevelActStatus eResult = eLevleActStatus_Init;
    UINT32 qwVar = rUser.GetVars().GetVar(NVarDefine::ePlayerQQAlarm);
    bool bCheck = qwVar & (1 << 1);
    if(bCheck)
        eResult = eLevleActStatus_GetPrize;
    rUser.GetPlayer()->SendPkg(g_LevelPrizeSvrS.BuildPkg_SendStateForQQAlarm(wActID,eResult));
}
