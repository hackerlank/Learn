#include "ShipManager.h"
#include "CenterConfig.h"
#include "Protocols.h"
#include "Random.h"
#include "UserMgr.h"
#include "SysMsgDefine.h"
#include "GuildUserMgr.h"
CShipManager g_ShipManager;

bool RunShip::Lock()
{
    if(_dwLockTimer > 0  && time(NULL) < _dwLockTimer +  LockTime)
    {
        return false;
    }
    if( time(NULL) >= sRunShip.dwEndTimer)
    {
        return false;
    }
    _dwLockTimer = time(NULL);
    return true;
}
bool RunShip::HasLock()
{
    if(_dwLockTimer > 0  && time(NULL) < _dwLockTimer +  LockTime)
    {
        return true;
    }
    return false;

}

void RunShip::UnLock()
{
    _dwLockTimer = 0;
}
CShipManager::CShipManager()
{
    memset(ArryChannel,0,sizeof(ArryChannel));
    _dwAwardRate = 10000;
}

bool CShipManager::Load()
{
    CShipLoader oLoader;
    string strPath = Config._strConfigDir + "Conf/Table/Ship.xml";
    if(!oLoader.LoadData(strPath))
        return false;
    _mapFlush.clear();
    _mapConfig.clear();
    for (auto iter = oLoader._vecData.begin();iter != oLoader._vecData.end();iter++)
    {
        SShipCFG &rConfig = *(*iter);
        if(!_mapConfig.insert(make_pair(rConfig._ID,rConfig)).second)
        {
            LOG_CRI << "Repeat Config";
            return false;
        }

        SShipRate sRate;
        sRate.wShip = rConfig._ID;
        sRate.wRate = rConfig._FreeChance;
        _mapFlush[rConfig._Number].vecFree.push_back(sRate); 
        sRate.wRate = rConfig._MoneyChance;
        _mapFlush[rConfig._Number].vecCost.push_back(sRate);
    }
    return true;

}
bool CShipManager::Init()//加载配置，向数据库发消息请求加载数据
{
    return Load();
}
void CShipManager::LoadFromDB()
{
    UINT32 dwsize =TAKE_ARRAY_LENGTH(PlayerShip);
    g_Center2DBCommC.Send_GetAllShip(dwsize);

}

void CShipManager::ReciveDBShip(UINT32 dwPageSize,UINT32 dwTotalSize,const TVecPlayerShip &vecShip)//数据库加载来的运船信息
{
    if(dwPageSize >= dwTotalSize)
    {
        Config.SetInited(eDBShip);
    }
    for(auto it = vecShip.begin(); it != vecShip.end();it++)
    {
        AddShipToList(*it);
    }

}
void CShipManager::AddShipToList(const PlayerShip& sRunShip)
{
    RunShip rShip;
    rShip.sRunShip = sRunShip;
    _mapAllShip[rShip.sRunShip.qwInsID] = rShip;
    if(rShip.sRunShip.byChannel >= TotalChannel)
    {
        ArryChannel[0]++;
    }
    else
    {
        ArryChannel[rShip.sRunShip.byChannel]++;
    }
    _mapTimerShip.insert(make_pair(rShip.sRunShip.dwEndTimer,rShip.sRunShip.qwInsID));
    _mapPlayerShip[rShip.sRunShip.qwOwer] = rShip.sRunShip.qwInsID;
    if(rShip.sRunShip.qwDefense > 0)
    {
        _mapDefenseShip[rShip.sRunShip.qwDefense] = rShip.sRunShip.qwInsID;
    }


}

bool CShipManager::FinishShip(UINT64 qwShipID)
{
    RunShip * pShip = GetShipByID(qwShipID);
    if(!pShip || pShip->HasLock())
    {
        return false;
    }
    ArriveShip(pShip->sRunShip);
    _mapPlayerShip.erase(pShip->sRunShip.qwOwer);
    if(pShip->sRunShip.qwDefense > 0)
    {
        _mapDefenseShip.erase(pShip->sRunShip.qwDefense);
    }
    if(pShip->sRunShip.byChannel < TotalChannel && ArryChannel[pShip->sRunShip.byChannel] > 0)
    {
        ArryChannel[pShip->sRunShip.byChannel]--;
    }
    auto range = _mapTimerShip.equal_range(pShip->sRunShip.dwEndTimer);
    for(auto iter = range.first; iter != range.second;iter++)
    {
        if(iter->second == qwShipID)
        {
            _mapTimerShip.erase(iter);
            break;
        }
    }
    _mapAllShip.erase(qwShipID);
    for(auto it = _setNoticeShipPlayer.begin();it != _setNoticeShipPlayer.end();)
    {
        CUserPtr pUser = CUserMgr::GetUserByUserID(*it);
        if(!pUser || !pUser->IsOnLine())
        {
            it = _setNoticeShipPlayer.erase(it);
            continue;
        }
        pUser->SendPkg(g_ShipProtS.BuildPkg_UpDateShipDel(qwShipID));
        it++; 
    }
    return true;
}

void CShipManager::TimerCheck()//计时器，监控船到岸消息
{
    if(!Config.AllServerIsReady())
    {
        return ;
    }
    UINT32 dwNow = time(NULL);
    TVecUINT64 vecAriveShip;
    for(auto it = _mapTimerShip.begin();it != _mapTimerShip.end();it++)
    {
        if(it->first <= dwNow)
        {
            RunShip * pShip = GetShipByID(it->second);
            if(pShip && pShip->HasLock())
            {
                continue;
            }
            else
            {
                vecAriveShip.push_back(it->second);
            }
        }
        else
        {
            break;
        }
    }
    if(vecAriveShip.empty())
    {
        return;
    }
    for(auto iter = vecAriveShip.begin();iter != vecAriveShip.end();iter++)
    {
        FinishShip(*iter);
    }


}

RunShip * CShipManager::GetShipByID(UINT64 qwShipID)//获得一条船信息
{
    auto iter= _mapAllShip.find(qwShipID);
    if(iter == _mapAllShip.end())
        return NULL;
    return &iter->second;
}
UINT64 CShipManager::GetShipByOwer(UINT64 qwRoleID)
{
    auto iter = _mapPlayerShip.find(qwRoleID);
    if(iter == _mapPlayerShip.end())
    {
        return 0;
    }
    return (iter->second);
}
UINT64 CShipManager::GetShipByDefense(UINT64 qwRoleID)
{
    auto iter = _mapDefenseShip.find(qwRoleID);
    if(iter == _mapDefenseShip.end())
    {
        return 0;
    }
    return (iter->second);
}

UINT16 CShipManager::ReFlushShipByVip(CUser& rUser,UINT8 byColor)
{
    if(_mapFlush.empty() || byColor == 0)
    {
        return 0;
    }
    UINT8 byLevel = rUser.GetLevel();
    SShipFlush *pFlush = NULL;
    for(auto it = _mapFlush.begin();it != _mapFlush.end();it++)
    {
        if(byLevel <= it->first)
        {
            pFlush = &(it->second);
            break;

        }
    }
    if(pFlush == NULL)
    {
        pFlush = &((_mapFlush.rbegin())->second);
    }
    if( pFlush->vecCost.size() < byColor)
    {
        return 0;
    }
    return pFlush->vecCost[byColor-1].wShip;
}

UINT16 CShipManager::ReFlushShip(CUser& rUser,UINT8 byColor)
{
    if(_mapFlush.empty())
    {
        return 0;
    }
    UINT8 byLevel = rUser.GetLevel();
    SShipFlush *pFlush = NULL;
    for(auto it = _mapFlush.begin();it != _mapFlush.end();it++)
    {
        if(byLevel <= it->first)
        {
            pFlush = &(it->second);
            break;

        }
    }
    if(pFlush == NULL)
    {
        pFlush = &((_mapFlush.rbegin())->second);
    }
    TVecShipRate *pvec = NULL;
    if(byColor == 0)
    {
        pvec = &(pFlush->vecFree);
    }
    else
    {
        pvec = &(pFlush->vecCost);
    }
    if(pvec->empty())
    {
        return 0;
    }
    UINT16 wShip = 0;
    if(byColor == 0 )
    {
        //
        UINT16 wRate = CRandom::RandInt(0,10000);
        for(auto iter = pvec->begin(); iter != pvec->end();iter++)
        {
            SShipRate& sRate = *iter;
            if(sRate.wRate >= wRate)
            {
                wShip = sRate.wShip;
                break;
            }
        }
    }
    else if(byColor <= pvec->size())
    {
        UINT16 wUseRate = 0;
        if(byColor != 1)
        {
           wUseRate = ((*pvec)[byColor-2]).wRate + 1;
        }
        UINT16 wRate = CRandom::RandInt(wUseRate,10000);
        for(auto iter = pvec->begin() + byColor - 1; iter != pvec->end();iter++)
        {
            SShipRate& sRate = *iter;
            if(sRate.wRate >= wRate)
            {
                wShip = sRate.wShip;
                break;
            }
        }
    }
    return wShip;
}

const SShipCFG * CShipManager::GetConfigById(UINT16 wShip)
{
    auto it = _mapConfig.find(wShip);
    if(it == _mapConfig.end())
    {
        return NULL;
    }
    return &(it->second);
}

bool CShipManager::OpenShip(CUser& rUser)//请求开船
{
    //创建一条船
    UINT8 byMinChannel = 0;
    UINT32 dwMinCount  = ArryChannel[0];
    for(UINT8 it = 1; it < TotalChannel ;it++)
    {
        if(ArryChannel[it] < dwMinCount)
        {
            dwMinCount = ArryChannel[it];
            byMinChannel = it;
        }

    }
    PlayerShip sShip;
    sShip.qwInsID = GET_GUID(GUID_SHIP); 
    sShip.byChannel = byMinChannel;
    PlayerSelfShipData& sData = rUser.GetShipPkg().GetSelfData();
    sShip.wShipId = sData.wReflushShip;
    //填充船主信息
    sShip.qwOwer = rUser.GetUserID();
    sShip.dwOwerPoint = rUser.GetFighterPower();
    sShip.byOwerLevel = rUser.GetLevel();//拥有者等级
    sShip.byOwerColor = rUser.GetColor();
     sShip.dwAwardRate = _dwAwardRate;
    //填充护卫者信息
    if(sData.qwInviteDefense > 0 && time(NULL) <= dwAgreeTime + sData.dwInviteDefenseAgreeTime)
    {
        sShip.qwDefense = sData.qwInviteDefense;
        sShip.dwDefensePoint = sData.dwInviteDefensePoint;
        sShip.byDefenseLevel = sData.byInviteDefenseLevel;//拥有者等级
        sShip.byDefenseColor = sData.byInviteDefenseColor;
    }
    //船开始和结束时间
    const SShipCFG * pConfig = GetConfigById(sShip.wShipId);
    if(pConfig == NULL)
    {
        return false;
    }
    sShip.dwBeginTimer = time(NULL);
    sShip.dwEndTimer = time(NULL) + pConfig->_Time;

    //加入列表
    AddShipToList(sShip);
    //发到数据库
    g_Center2DBCommC.Send_UpdateShip(sShip);
    //生成记录
    CreateReport(sShip,EBS_OPENSHIP);
    PlayerShipForList rItem ;
    GetListItem(sShip,rItem);
    for(auto it = _setNoticeShipPlayer.begin();it != _setNoticeShipPlayer.end();)
    {
        CUserPtr pUser = CUserMgr::GetUserByUserID(*it);
        if(!pUser || !pUser->IsOnLine())
        {
            it = _setNoticeShipPlayer.erase(it);
            continue;
        }
        pUser->SendPkg(g_ShipProtS.BuildPkg_UpDateShipAdd(rItem));
        it++; 
    }

    {
        TVecINT32 vecParam;
        vecParam.push_back(1);
        rUser.OnEvent(eEventType_BoatBegin,vecParam);
    }
    return true;

}

void CShipManager::CreateReport(const PlayerShip& rShip,EShipBattleSource eSource,UINT64 qwOtherID,NBattleGS::EBattleResult eResult,UINT64  qwBattleID,UINT8 byOtherColor )
{
    ShipReport sRePort;
    sRePort.eSource = eSource;
    sRePort.qwInsID = rShip.qwInsID;
    sRePort.qwOwer = rShip.qwOwer;
    sRePort.byOwerColor = rShip.byOwerColor;
    sRePort.wShipId = rShip.wShipId;
    sRePort.qwDefense = rShip.qwDefense;
    sRePort.byDefenseColor = rShip.byDefenseColor;
    sRePort.dwFinishTimer = rShip.dwEndTimer;
    sRePort.dwTimer = time(NULL);
    sRePort.dwAwardRate = rShip.dwAwardRate;
    TSetUINT64 setRoB;
    GetRobID(rShip,setRoB);
    sRePort.byRobTimes = setRoB.size();
    bool bNeedSave = true;
    TVecUINT64 vecRoleID;
    switch(sRePort.eSource)
    {
        case EBS_OPENSHIP: //开船
            {
                vecRoleID.push_back(sRePort.qwOwer);
                if(sRePort.qwDefense > 0)
                    vecRoleID.push_back(sRePort.qwDefense);
            }
            break;
        case EBS_ROBWITHOWER: //打劫与船主战斗
        case EBS_ROBWITHDEFENSE: //返抢与船主战斗
        case EBS_GRABBYOWER: //打劫与护卫战斗
        case EBS_GRABBYDEFENSE: //返抢与护卫战斗
            {
                if(NBattleGS::EBResultAttackWin != eResult)
                {
                    bNeedSave = false;
                }
                sRePort.qwRoBId = qwOtherID;
                sRePort.qwBattleID = qwBattleID;
                sRePort.byRoBColor = byOtherColor;
                vecRoleID.push_back(sRePort.qwOwer);
                if(sRePort.qwDefense > 0)
                    vecRoleID.push_back(sRePort.qwDefense);
                vecRoleID.push_back(qwOtherID);
                if(NBattleGS::EBResultAttackWin == eResult)
                {
                    if(sRePort.eSource == EBS_ROBWITHOWER)
                    {
                        //给船主一个泡
                        CUserPtr pOwerUser = CUserMgr::GetUserByUserID(rShip.qwOwer);
                        if(pOwerUser && pOwerUser->IsOnline())
                        {
                            UINT32 dwServerID = pOwerUser->GetGameSvrID();
                            TVecINT64 vecID;
                            vecID.push_back(rShip.qwInsID);
                            vecID.push_back(qwOtherID);
                            TVecString vecString;
                            string strRobName;
                            g_PHPProtS.GetNameByID(qwOtherID,strRobName);
                            vecString.push_back(strRobName);
                            const SShipCFG *  pCfg = g_ShipManager.GetConfigById(rShip.wShipId);
                            if(pCfg)
                                vecString.push_back(pCfg->_Name);
                            g_Game2CenterCommS.SendSvr_BubbleNotify(&dwServerID,1,rShip.qwOwer,NProtoCommon::eOpAdd,11,vecID,vecString);
                        }
                    }
                    else if(sRePort.eSource == EBS_ROBWITHDEFENSE)
                    {
                        //给船主一个泡
                        CUserPtr pOwerUser = CUserMgr::GetUserByUserID(rShip.qwOwer);
                        if(pOwerUser && pOwerUser->IsOnline())
                        {
                            UINT32 dwServerID = pOwerUser->GetGameSvrID();
                            TVecINT64 vecID;
                            vecID.push_back(rShip.qwInsID);
                            vecID.push_back(qwOtherID);
                            TVecString vecString;
                            string strRobName;
                            g_PHPProtS.GetNameByID(qwOtherID,strRobName);
                            vecString.push_back(strRobName);
                            const SShipCFG *  pCfg = g_ShipManager.GetConfigById(rShip.wShipId);
                            if(pCfg)
                                vecString.push_back(pCfg->_Name);
                            g_Game2CenterCommS.SendSvr_BubbleNotify(&dwServerID,1,rShip.qwOwer,NProtoCommon::eOpAdd,11,vecID,vecString);
                        }

                        //给护卫一个泡
                        CUserPtr pDefenseUser = CUserMgr::GetUserByUserID(rShip.qwDefense);
                        if(pDefenseUser && pDefenseUser->IsOnline())
                        {
                            UINT32 dwServerID = pDefenseUser->GetGameSvrID();
                            TVecINT64 vecID;
                            vecID.push_back(rShip.qwInsID);
                            vecID.push_back(qwOtherID);
                            TVecString vecString;
                            string strRobName;
                            g_PHPProtS.GetNameByID(qwOtherID,strRobName);
                            vecString.push_back(strRobName);
                            const SShipCFG *  pCfg = g_ShipManager.GetConfigById(rShip.wShipId);
                            if(pCfg)
                                vecString.push_back(pCfg->_Name);
                            g_Game2CenterCommS.SendSvr_BubbleNotify(&dwServerID,1,rShip.qwDefense,NProtoCommon::eOpAdd,12,vecID,vecString);
                        }
                    }
                }
            }
            break;
        case EBS_CLOSESHIP: //结束航运
            {
                vecRoleID.push_back(sRePort.qwOwer);
                if(sRePort.qwDefense > 0)
                    vecRoleID.push_back(sRePort.qwDefense);
                if(rShip.qwRoBId1 > 0)
                {
                    vecRoleID.push_back(rShip.qwRoBId1);
                }
                if(rShip.qwRoBId2 > 0)
                {
                    vecRoleID.push_back(rShip.qwRoBId2);
                }
                if(rShip.qwRoBId3 > 0)
                {
                    vecRoleID.push_back(rShip.qwRoBId3);
                } 
            }
            break;
    }
    if(vecRoleID.empty())
        return ;
    if(bNeedSave)
    {
        for(auto it = vecRoleID.begin(); it != vecRoleID.end();it++)
        {  
            g_Center2DBCommC.Send_AddShipReport(*it,sRePort);
            CUserPtr pUser = CUserMgr::GetUserByUserID(*it);
            if(pUser)
            {
                pUser->GetShipPkg().AddReport(sRePort);
            }

        }

    }

    for(auto it = vecRoleID.begin(); it != vecRoleID.end();it++)
    {  

        CUserPtr pUser = CUserMgr::GetUserByUserID(*it);
        if(pUser && pUser->IsOnline())
        {
            ShipReportForClient rClientPort;
            CreateClientShipReport(rClientPort,sRePort,eResult);
            pUser->SendPkg(g_ShipProtS.BuildPkg_UpDateShipReportAdd(rClientPort));

        }
    }

}

void CShipManager::CreateClientShipReport(ShipReportForClient & rClient,const ShipReport & sData,NBattleGS::EBattleResult eResult)
{
    rClient.stInfo = sData;
    if(eResult == NBattleGS::EBResultNone && rClient.stInfo.qwBattleID > 0)
    {
        eResult = NBattleGS::EBResultAttackWin;
    }
    rClient.eResult = eResult;
    g_PHPProtS.GetNameByID(sData.qwOwer,rClient.strOwerName);
    if(rClient.stInfo.qwDefense > 0)
    {
        g_PHPProtS.GetNameByID(sData.qwDefense,rClient.strDefenseName);
    }
    if(rClient.stInfo.qwRoBId > 0)
    {
        g_PHPProtS.GetNameByID(sData.qwRoBId,rClient.strRoBIdName);

    }

}


void CShipManager::ArriveShip(const PlayerShip& rShip)//船到站
{
    //发消息删除
    g_Center2DBCommC.Send_DelShip(rShip.qwInsID);
    //生成记录
    CreateReport(rShip,EBS_CLOSESHIP);
    //发送奖励
    const SShipCFG * pConfig = GetConfigById(rShip.wShipId);
    if(pConfig == NULL)
    {
        return ;
    }
    TSetUINT64 setRoB;
    GetRobID(rShip,setRoB);
    UINT8 byROBTimes = setRoB.size();
    UINT32 dwOwerLoot = 0;
    //船主
    switch (byROBTimes)
    {
        case 0:
            {

                dwOwerLoot =  pConfig->_Award;
            }
            break;
        case 1:
            {
                dwOwerLoot =  pConfig->_Award1;
            }
            break;
        case 2:
            {
                dwOwerLoot =  pConfig->_Award2; 
            }
            break;
        case 3:
            {
                dwOwerLoot =  pConfig->_Award3; 
            }
            break;
        default:
            break;
    }

    CUserPtr pUser = CUserMgr::GetUserByUserID(rShip.qwOwer);
    TVecINT32 vecParam;
    vecParam.push_back(1);
    if(pUser && pUser->IsOnLine())
    {
        pUser->OnEvent(eEventType_BoatFinish,vecParam);
    }
    else
    {

        CUser::AddOffLineEvent(rShip.qwOwer,eEventType_BoatFinish,vecParam);
    }

    if(dwOwerLoot >0)
    {
        //船主奖励qwOwer
        TVecString vecParam;
        const SShipCFG *pCfg =  GetConfigById(rShip.wShipId);
        if(pCfg)
        {
            vecParam.push_back(pCfg->_Name);
        }
        vecParam.push_back(NumberToString(byROBTimes));
        UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
        g_Game2CenterCommS.SendSvr_SendSysMailByLootId(&dwGameSvrIdx,1,rShip.qwOwer,514,515,vecParam,dwOwerLoot,rShip.dwAwardRate);
    }
    //护送者奖励
    if(rShip.qwDefense > 0)
    {
        //eEventType_BoatProtect
        CUserPtr pGuardUser = CUserMgr::GetUserByUserID(rShip.qwDefense);
        TVecINT32 vecParam;
        vecParam.push_back(1);
        if(pGuardUser && pGuardUser->IsOnLine())
        {
            pGuardUser->OnEvent(eEventType_BoatProtect,vecParam);
        }
        else
        {

            CUser::AddOffLineEvent(rShip.qwDefense,eEventType_BoatProtect,vecParam);
        }

        if(byROBTimes == 0 )
        {
            UINT32 dwDefLoot = pConfig->_ProtectAward;
            if(dwDefLoot > 0)
            {
                TVecString vecParam;
                const SShipCFG *pCfg =  GetConfigById(rShip.wShipId);
                if(pCfg)
                {
                    vecParam.push_back(pCfg->_Name);
                }
                UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
                g_Game2CenterCommS.SendSvr_SendSysMailByLootId(&dwGameSvrIdx,1,rShip.qwDefense,516,517,vecParam,dwDefLoot,rShip.dwAwardRate);

            }
        }
    }

    UINT32 dwROBLoot = pConfig->_RobAward;
    if(dwROBLoot > 0)
    {
        for(auto it = setRoB.begin();it != setRoB.end();it++)
        {
            TVecString vecParam;
            const SShipCFG *pCfg =  GetConfigById(rShip.wShipId);
            if(pCfg)
            {
                vecParam.push_back(pCfg->_Name);
            }
            UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
            g_Game2CenterCommS.SendSvr_SendSysMailByLootId(&dwGameSvrIdx,1,*it,518,519,vecParam,dwROBLoot,rShip.dwAwardRate);

        }
    }

}

void CShipManager::RobShip(UINT64 qwShip,CUser& rUser,NBattleGS::EBattleResult eResult,UINT64 qwBattleID)
{

    RunShip *pShip =  GetShipByID(qwShip);
    if(!pShip)
    {
        return;
    }
    PlayerShip& rShip = pShip->sRunShip;
    if(NBattleGS::EBResultAttackWin == eResult)
    {
        bool bDoCase = false;
        do{
            if(rShip.qwRoBId1 == 0)
            {
                bDoCase = true;
                rShip.qwRoBId1 = rUser.GetUserID();
                rShip.dwRoB1Point = rUser.GetFighterPower();
                rShip.byRoB1Level = rUser.GetLevel();//拥有者等级
                rShip.byRoB1Color = rUser.GetColor();
                break;
            }
            if(rShip.qwRoBId2 == 0)
            {
                bDoCase = true;
                rShip.qwRoBId2 = rUser.GetUserID();
                rShip.dwRoB2Point = rUser.GetFighterPower();
                rShip.byRoB2Level = rUser.GetLevel();//拥有者等级
                rShip.byRoB2Color = rUser.GetColor();

                break;
            } 
            if(rShip.qwRoBId3 == 0)
            {
                bDoCase = true;
                rShip.qwRoBId3 = rUser.GetUserID();
                rShip.dwRoB3Point = rUser.GetFighterPower();
                rShip.byRoB3Level = rUser.GetLevel();//拥有者等级
                rShip.byRoB3Color = rUser.GetColor();
                break;
            }

        }while(0);
        if(!bDoCase)
        {
            return ;
        }
        g_Center2DBCommC.Send_UpdateShip(rShip);  
        const SShipCFG *  pCfg = g_ShipManager.GetConfigById(rShip.wShipId);
        if(pCfg)
        {
            TVecString vecStr;
            vecStr.push_back(NumberToString(rUser.GetColor()));
            vecStr.push_back(rUser.GetUserName());
            vecStr.push_back(NumberToString(rShip.byOwerColor));
            string strOwerName;
            g_PHPProtS.GetNameByID(rShip.qwOwer,strOwerName);
            vecStr.push_back(strOwerName);
            vecStr.push_back(NumberToString(pCfg->_Color));
            vecStr.push_back(pCfg->_Name);
            for(auto it = _setNoticeShipPlayer.begin();it != _setNoticeShipPlayer.end();)
            {
                CUserPtr pUser = CUserMgr::GetUserByUserID(*it);
                if(!pUser || !pUser->IsOnLine())
                {
                    it = _setNoticeShipPlayer.erase(it);
                    continue;
                }
                pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgRobBoardCast,vecStr));
                it++; 
            }
        }
    }
    EShipBattleSource eSource = EBS_ROBWITHOWER;
    if(rShip.qwDefense > 0 )
    {
        eSource = EBS_ROBWITHDEFENSE;
    }
    CreateReport(rShip,eSource,rUser.GetUserID(),eResult,qwBattleID,rUser.GetColor());
}

void CShipManager::GrabShip(UINT64 qwShip,CUser& rUser,UINT64 qwROBID,NBattleGS::EBattleResult eResult,UINT64 qwBattleID)
{
    RunShip *pShip =  GetShipByID(qwShip);
    if(!pShip)
    {
        return;
    }
    PlayerShip& rShip = pShip->sRunShip;
    UINT8 byColor = 0;
    if(1)
    {
        bool bDoCase = false;
        do{
            if(rShip.qwRoBId1 == qwROBID)
            {
                bDoCase = true;
                byColor = rShip.byRoB1Color ;
                break;
            }
            if(rShip.qwRoBId2 == qwROBID)
            {
                bDoCase = true;
                byColor = rShip.byRoB2Color ;
                break;
            } 
            if(rShip.qwRoBId3 == qwROBID)
            {
                bDoCase = true;
                byColor = rShip.byRoB3Color ;    
                break;
            }

        }while(0);
        if(!bDoCase)
        {
            return ;
        }
    }
    if(NBattleGS::EBResultAttackWin == eResult)
    {
        do{
            if(rShip.qwRoBId1 == qwROBID)
            {
                rShip.qwRoBId1 = 0;
                rShip.dwRoB1Point = 0;
                rShip.byRoB1Level = 0;//拥有者等级
                rShip.byRoB1Color = 0;
                break;
            }
            if(rShip.qwRoBId2 == qwROBID)
            {
                rShip.qwRoBId2 = 0;
                rShip.dwRoB2Point = 0;
                rShip.byRoB2Level = 0;//拥有者等级
                rShip.byRoB2Color = 0;
                break;
            } 
            if(rShip.qwRoBId3 == qwROBID)
            {
                rShip.qwRoBId3 = 0;
                rShip.dwRoB3Point = 0;
                rShip.byRoB3Level = 0;//拥有者等级
                rShip.byRoB3Color = 0;
                break;
            }

        }while(0);
        g_Center2DBCommC.Send_UpdateShip(rShip);
    }
    EShipBattleSource eSource;
    if(rShip.qwDefense == rUser.GetUserID())
    {
        eSource = EBS_GRABBYDEFENSE;
    }
    if(rShip.qwOwer == rUser.GetUserID())
    {
        eSource = EBS_GRABBYOWER;
    }
    if(eSource != EBS_GRABBYDEFENSE && eSource != EBS_GRABBYOWER)
    {
        return;
    }
    CreateReport(rShip,eSource,qwROBID,eResult,qwBattleID,byColor);
}

void CShipManager::GetRobID(const PlayerShip& rShip,TSetUINT64& setRoB) const
{
    if(rShip.qwRoBId1 > 0)
    {
        setRoB.insert(rShip.qwRoBId1);
    }
    if(rShip.qwRoBId2 > 0)
    {
        setRoB.insert(rShip.qwRoBId2);
    }
    if(rShip.qwRoBId3 > 0)
    {
        setRoB.insert(rShip.qwRoBId3);
    }
}
void  CShipManager::GetAllShipForList(UINT64 qwRoleID,TVecPlayerShipForList &rVec)
{
    _setNoticeShipPlayer.insert(qwRoleID);
    UINT64 qwSelfShipID = GetShipByOwer(qwRoleID);
    UINT64 qwDefenseShipID = GetShipByDefense(qwRoleID);
    if(qwSelfShipID > 0)
    {
        RunShip * pSelfShip = GetShipByID(qwSelfShipID);
        if(pSelfShip)
        {
            PlayerShipForList rItem ;
            GetListItem(pSelfShip->sRunShip,rItem);
            rVec.push_back(rItem);

        }

    }
    if(qwDefenseShipID > 0)
    {
        RunShip * pDefenseShip = GetShipByID(qwDefenseShipID);
        if(pDefenseShip)
        {
            PlayerShipForList rItem ;
            GetListItem(pDefenseShip->sRunShip,rItem);
            rVec.push_back(rItem);

        }

    }

    for(auto it = _mapAllShip.begin();it != _mapAllShip.end();it++)
    {
        if(it->first == qwSelfShipID || it->first == qwDefenseShipID)
        {
            continue;
        }
        RunShip * pShip = &(it->second);
        PlayerShipForList rItem ;
        GetListItem(pShip->sRunShip,rItem);
        rVec.push_back(rItem);
        if(rVec.size() >= wShowShip)
        {
            break;
        }

    }

}

void CShipManager::CloseNoticeShip(UINT64 qwRoleID)
{
    _setNoticeShipPlayer.erase(qwRoleID);
}

void CShipManager::GetListItem(const PlayerShip& rShip,PlayerShipForList & rItem)
{
    rItem.qwInsID = rShip.qwInsID;
    rItem.qwOwer =  rShip.qwOwer;
    rItem.wShipId = rShip.wShipId;
    rItem.byChannel =  rShip.byChannel;
    rItem.dwBeginTimer = rShip.dwBeginTimer;
    rItem.dwEndTimer = rShip.dwEndTimer;
}

void CShipManager::GetPlayerShipForClient(const PlayerShip& rShip,PlayerShipForClient &rClient)
{
    rClient.stInfo = rShip;
    g_PHPProtS.GetNameByID(rShip.qwOwer,rClient.strOwerName);
    CGuildUserMgr::Instance().GetGuildName(rShip.qwOwer,rClient.strGuipName);
    
    if(rShip.qwDefense > 0)
    {
        g_PHPProtS.GetNameByID(rShip.qwDefense,rClient.strDefenseName);
    }
    if(rShip.qwRoBId1 > 0)
    {
        g_PHPProtS.GetNameByID(rShip.qwRoBId1,rClient.strRoBIdName1);

    }
    if(rShip.qwRoBId2 > 0)
    {
        g_PHPProtS.GetNameByID(rShip.qwRoBId2,rClient.strRoBIdName2);
    }
    if(rShip.qwRoBId3 > 0)
    {
        g_PHPProtS.GetNameByID(rShip.qwRoBId3,rClient.strRoBIdName3);
    }
}
void CShipManager::SetAwardRate(UINT32 dwRate)
{
    _dwAwardRate = dwRate;
}
