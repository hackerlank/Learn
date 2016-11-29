#include "stdafx.h"
#include "BattleArrayMgr.h"
#include "Player.h"
#include "User.h"
//#include "Protocols.h"
#include "SysMsgDefine.h"
//#include "GetCondMgr.h"
#include "ItemMgr.h"
#include "Tokenizer.h"
#include "AutoStoreMgr.h"
#include "Battle.h"
#include "Monster.h"
#include "MonsterMgr.h"
#include "BattleArrayS.h"
#include "VIPMgr.h"
#include "Loot.h"
#include "HeroFighter.h"
#include "GUIDMgr.h"

TMapBattleArrayCFGExPtr CBattleArrayMgr::_mapBattleArrayCFGExPtr;
TMapBattleArrayLevelCFGExPtr CBattleArrayMgr::_mapBattleArrayLevelCFGExPtr;
TVecBattleArrayPriceCFG CBattleArrayMgr::_vecBattleArrayPriceCFG;

UINT16 GetIDByLevelID(UINT32 dwBattleArrayLevelID)
{
    return dwBattleArrayLevelID/100;
}

bool IsInitLevelID(UINT32 dwBattleArrayLevelID)
{
    return ((dwBattleArrayLevelID%100) == 1);
}

void GetItemFromString(TVecItemGenInfo& vecItem, const string strItem)
{
        Tokenizer tk(strItem, "|"); // XXX: itemID,count|ItemID,count
        for (size_t i = 0; i < tk.size(); ++i)
        {
            Tokenizer yatk(tk[i], ",");
            UINT16 wItemID = atoi(yatk[0].c_str());
            if (wItemID)
            {
                UINT32 dwCount = 0;
                if (yatk.size() > 1)
                {
                    dwCount = atoi(yatk[1].c_str());
                    SItemGenInfo oItemGenInfo;
                    oItemGenInfo.wItemID = wItemID;
                    oItemGenInfo.dwCount = dwCount;
                    oItemGenInfo.eBindType = eBindGet;
                    vecItem.push_back(oItemGenInfo);
                }
            }
        }
}

void GetStarFromString(TVecUINT16& vecStar,const string strItem)
{
    Tokenizer tk(strItem, ",");
    for (size_t i = 0; i < tk.size(); ++i)
    {
        UINT16 wMinTurns = atoi(tk[i].c_str());
        vecStar.push_back(wMinTurns);
    }
}

void PushItemFromRes(TVecItemGenInfo& oVecToItemGenInfo,TVecResource& vecFromRes)
{

    for(size_t i=0; i < vecFromRes.size(); i++)
    {
        SItemGenInfo oItemGenInfo;
        oItemGenInfo.wItemID = vecFromRes[i]._eRes;
        oItemGenInfo.dwCount = vecFromRes[i]._dwValue; 
        oVecToItemGenInfo.push_back(oItemGenInfo);
    }

}

bool CBattleArrayMgr::BattleArrayInit()
{
    
    string strBattleArrayPath = Config._strConfigDir + "Conf/Table/BattleArray.xml";
    CBattleArrayLoader oBattleArrayLoader;
    if(!oBattleArrayLoader.LoadData(strBattleArrayPath))
    {
        LOG_CRI << "CBattleArrayLoaderLoader fails! Path: " << strBattleArrayPath;
        return false;
    }

    for(size_t i  = 0; i < oBattleArrayLoader._vecData.size(); ++i)
    {
        SBattleArrayCFGExPtr pBattleArrayCFG(new SBattleArrayCFGEx);
        pBattleArrayCFG->CopyFrom(*oBattleArrayLoader._vecData[i]);
        GetItemFromString(pBattleArrayCFG->vecPassPrize,pBattleArrayCFG->_PassPrize);
        _mapBattleArrayCFGExPtr[pBattleArrayCFG->_ID] = pBattleArrayCFG;
    }
 
    string strBattleArrayLevelPath = Config._strConfigDir + "Conf/Table/BattleArrayLevel.xml";
    CBattleArrayLevelLoader oBattleArrayLevelLoader;
    if(!oBattleArrayLevelLoader.LoadData(strBattleArrayLevelPath))
    {
        LOG_CRI << "oBattleArrayLevelLoader fails! Path: " << strBattleArrayPath;
        return false;
    }

    for(size_t i  = 0; i < oBattleArrayLevelLoader._vecData.size(); ++i)
    {
        SBattleArrayLevelCFGExPtr pBattleArrayLevelCFG(new SBattleArrayLevelCFGEx);
        pBattleArrayLevelCFG->CopyFrom(*oBattleArrayLevelLoader._vecData[i]);
        GetStarFromString(pBattleArrayLevelCFG->vecStar,pBattleArrayLevelCFG->_Access);
        _mapBattleArrayLevelCFGExPtr[pBattleArrayLevelCFG->_ID] = pBattleArrayLevelCFG;
    }

    string strBattleArrayPricePath = Config._strConfigDir + "Conf/Table/BattleArrayPrice.xml";
    CBattleArrayPriceLoader oBattleArrayPriceLoader;
    if(!oBattleArrayPriceLoader.LoadData(strBattleArrayPricePath))
    {
        LOG_CRI << "oBattleArrayPriceLoader fails! Path: " << strBattleArrayPricePath;
        return false;
    }

    for(size_t i  = 0; i < oBattleArrayPriceLoader._vecData.size(); ++i)
    {
        _vecBattleArrayPriceCFG.push_back(*(oBattleArrayPriceLoader._vecData[i]));
    }

    return true;
}

CBattleArrayMgr::CBattleArrayMgr(CPlayer& rPlayer):
    _rPlayer(rPlayer),
    _dwAttackCd(0)
{
    _dwAttackCd = time(NULL);
    
}

bool CBattleArrayMgr::LoadFromDB(const RoleDataInfo& rRoleDataInfo)
{
    LOG_DBG<<"CBattleArrayMgr::LoadFromDB:"<<rRoleDataInfo.vecBattleArrayDBInfo.size();
    for(size_t i=0; i < rRoleDataInfo.vecBattleArrayDBInfo.size(); i++)
    {
        SBattleArrayDBInfoPtr pBattleArrayDBInfo(new SBattleArrayDBInfo);
        *pBattleArrayDBInfo = rRoleDataInfo.vecBattleArrayDBInfo[i];
        _mapBattleArrayPtr.insert(make_pair(pBattleArrayDBInfo->wBattleArrayID,pBattleArrayDBInfo));
    }

    return true;
}

void CBattleArrayMgr::Update2DB(const SBattleArrayDBInfo& rInfo, EDataChange eDataChange/* = eOpUpdate*/)
{
    string strData;
    COutArchive iar(strData);
    iar << rInfo;
    
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(),eTypeBattleArray, eDataChange, strData);
}

//获取阵配置
SBattleArrayCFGExPtr CBattleArrayMgr::GetBattleArrayCFG(UINT16 wBattleArrayID)
{
    auto itr = CBattleArrayMgr::_mapBattleArrayCFGExPtr.find(wBattleArrayID);
    if(itr != CBattleArrayMgr::_mapBattleArrayCFGExPtr.end())
    {
        return itr->second;
    }

    return NULL;
}

//获取阵图配置
SBattleArrayLevelCFGExPtr CBattleArrayMgr::GetBattleArrayLevelCFG(UINT32 dwBattleArrayLevelID)
{
    auto itr = CBattleArrayMgr::_mapBattleArrayLevelCFGExPtr.find(dwBattleArrayLevelID);
    if(itr != CBattleArrayMgr::_mapBattleArrayLevelCFGExPtr.end())
    {
        return itr->second;
    }

    return NULL;
}


void CBattleArrayMgr::OnGetBattleArray(shared_func<CBattleArraySvr::SGetBattleArrayAck>& fnAck)
{
    for(auto itr = _mapBattleArrayPtr.begin(); itr != _mapBattleArrayPtr.end(); itr++)
    {
        fnAck->vecBattleArray.emplace_back(itr->second->wBattleArrayID,itr->second->dwBattleArrayLevelID,(EBattleArrayStatus)(itr->second->byBattleArrayStatus));
    }

    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        LOG_CRI<<"NULL == pAutoStoreMgr";
        return;
    }

    TSetUINT32 setBattleArrayID;
    TVecAutoStoreDBInfo vecAutoStoreDBInfo;
    pAutoStoreMgr->GetListByType(eAutoStore_BattleArray,vecAutoStoreDBInfo);
    for(size_t i=0;i < vecAutoStoreDBInfo.size(); i++)
    {
        if(vecAutoStoreDBInfo[i].dwClassID > 10)
        {
            setBattleArrayID.insert(vecAutoStoreDBInfo[i].dwClassID);
        }
        //fnAck->vecBattleArrayAttackCnt.emplace_back(vecAutoStoreDBInfo[i].dwClassID,vecAutoStoreDBInfo[i].dwValue);
    }

    vecAutoStoreDBInfo.clear();
    pAutoStoreMgr->GetListByType(eAutoStore_BattleArray_MinTurns,vecAutoStoreDBInfo);
    for(size_t i=0;i < vecAutoStoreDBInfo.size(); i++)
    {
        if(vecAutoStoreDBInfo[i].dwClassID > 10)
        {
            setBattleArrayID.insert(vecAutoStoreDBInfo[i].dwClassID);
        }
    }

    for(auto itr = setBattleArrayID.begin(); itr != setBattleArrayID.end(); itr++)
    {
        UINT32 dwBattleArrayID = *itr;
        SBattleArrayAttackCnt oBattleArrayAttackCnt;
        oBattleArrayAttackCnt.dwBattleArrayLevelID = dwBattleArrayID;
        oBattleArrayAttackCnt.wCount = GetAttackCnt(dwBattleArrayID);
        oBattleArrayAttackCnt.wMinTurn = GetMinTurns(dwBattleArrayID);
        fnAck->vecBattleArrayAttackCnt.push_back(oBattleArrayAttackCnt);
    }


    fnAck->dwBuyCnt = GetTotleBuyCnt();
    fnAck->dwDayBuyCnt = GetDayTotleBuyCnt();
    fnAck->dwFailCd  = GetFailCD();


    _rPlayer.SendPkg(g_BattleArrayS.BuildPkg_TotleAttackCntNotify(GetTotleAtkCnt(),GetTotleBuyCnt()));

    LOG_DBG<<"roleId:"<<_rPlayer.GetRoleID()<<"OnGetBattleArray: vecBattleArray.size():"<<fnAck->vecBattleArray.size()<<"vecBattleArrayAt.size():"<<fnAck->vecBattleArrayAttackCnt.size();
}

bool CBattleArrayMgr::IsFinish(UINT16 wBattleArrayID)
{
    SBattleArrayDBInfoPtr pBattleArrayDBInfo = GetBattleArray(wBattleArrayID);
    if(NULL == pBattleArrayDBInfo)
    {
        return false;
    }

    return pBattleArrayDBInfo->byBattleArrayStatus >= eBattleArrayStatus_End;
}

SBattleArrayDBInfoPtr CBattleArrayMgr::GetBattleArray(UINT16 wBattleArrayID)
{
    auto itr = _mapBattleArrayPtr.find(wBattleArrayID);
    if(itr != _mapBattleArrayPtr.end())
    {
        return itr->second;
    }

    return NULL;
}

bool  AttackMonster(CPlayer& rPlayer,UINT32 dwEnemyID,EBattleResult& eBattleResult,UINT32& dwRounds,std::string& strReport)
{
    TVecBattleFighterPtr vecBattleFighter;
    rPlayer.GetBattleFighterList(vecBattleFighter);

    IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
    if(NULL == pBS)
    {
        return false;
    }

    vector<TVecBattleFighterPtr> vecvecBattleFighter2;
    UINT64 qwTmpInstID =  1;
    qwTmpInstID = CMonster::GetBattleFighterListByGroupID(vecvecBattleFighter2, dwEnemyID, qwTmpInstID, vecBattleFighter);
    if (!qwTmpInstID)
    {
        return false;
    }
    pBS->PutFighters(0, rPlayer.GetMainFighter()->GetInstID(), rPlayer.GetLevel(), vecBattleFighter, rPlayer.GetRoleID());
    pBS->PutFighters(1, qwTmpInstID, CMonsterMgr::GetMonsterLevel(dwEnemyID), vecvecBattleFighter2[0], 1);

    IBattleFighterPtr pFighter = CMonster::GetSceneFighter(dwEnemyID);
    if (!pFighter)
        pFighter = rPlayer.GetSceneFighter();
    pBS->PutScene(pFighter);
    pBS->Start(EBTMonster);

    //std::string strReport;
    pBS->GetReport(strReport);

    //std::string strData = g_BattleGSS.BuildPkg_BattleReportData(strReport, rPlayer.GetRoleID(), rPlayer.GetMainFighter()->GetID());
    //rPlayer.SendPkg(strData);
    eBattleResult = pBS->GetFinalWinner(); //== EBResultAttackWin;

    dwRounds = pBS->GetRounds();

    return true;
}

EBattleArrayRet CBattleArrayMgr::OnAttackBattleArray(UINT32 dwBattleArrayLevelID)
{
    if(_dwAttackCd > time(NULL))
    {
        _rPlayer.SendSysMsg(eMsgCooldownErr);
        return eBattleArrayRet_AttackCd;
    }

    if(GetFailCD() > time(NULL))
    {
        return eBattleArrayRet_AttackCd;
    }

    UINT16 wBattleArrayID = GetIDByLevelID(dwBattleArrayLevelID);

    SBattleArrayCFGExPtr pBattleArrayCFGEx = GetBattleArrayCFG(wBattleArrayID);
    if(NULL == pBattleArrayCFGEx)
    {
        LOG_CRI<<"error wBattleArrayID: "<<wBattleArrayID;
        _rPlayer.SendSysMsg(eMsgBattleArrayErrorCFG);
        return eBattleArrayRet_ErrorCFG;
    }

    //等级限制
    if(_rPlayer.GetLevel()< pBattleArrayCFGEx->_RequiredLevel)
    {
        LOG_INF<<"eBattleArrayRet_LevelLimit "<<_rPlayer.GetLevel()<<"|"<<pBattleArrayCFGEx->_RequiredLevel;
        _rPlayer.SendSysMsg(eMsgBattleArrayLevelLimit);
        return eBattleArrayRet_LevelLimit;
    }

    //前置阵限制
    if( pBattleArrayCFGEx->_PreID)
    {
        if(!IsFinish(pBattleArrayCFGEx->_PreID))
        {
            LOG_INF<<"eBattleArrayRet_PreID:"<<pBattleArrayCFGEx->_PreID;
            _rPlayer.SendSysMsg(eMsgBattleArrayPreID);
            return eBattleArrayRet_PreID;
        }
    }

    SBattleArrayLevelCFGExPtr pBattleArrayLevelCFGEx = GetBattleArrayLevelCFG(dwBattleArrayLevelID);
    if(NULL == pBattleArrayLevelCFGEx)
    {
        LOG_CRI<<"error BattleArrayLevelCFG: "<<dwBattleArrayLevelID;
        _rPlayer.SendSysMsg(eMsgBattleArrayErrorCFG);
        return eBattleArrayRet_ErrorCFG;
    }
    
    CUser& rUser = _rPlayer.GetUser();
    CPack& rPack = rUser.GetPack();
 
    if(rPack.GetEmptyCount() < pBattleArrayLevelCFGEx->_RequiredPackage)
    {
        _rPlayer.SendSysMsg(eMsgBattleArrayPackError);
        return eBattleArrayRet_PackError;
    }
    
    if(pBattleArrayLevelCFGEx->_CostEnergy)
    {
        if(!rUser.CanSubMoney(EMONEY_ACTION,pBattleArrayLevelCFGEx->_CostEnergy))
        {
            _rPlayer.SendSysMsg(eMsgDungeonPowerErr);
            return eBattleArrayRet_MoneyError;
        }
    }


    bool bIsEye = true; //是否是阵眼

    if(pBattleArrayLevelCFGEx->_SpotType == eBattleArrayLevelType_positon)
    {
        bIsEye = false;
    }

   
    //最大次数限制
    UINT32 dwTotleAckCnt = GetTotleAtkCnt();

    bool bIsSubBuyCnt = false;

    //阵眼非第一次破阵眼
    if(bIsEye && GetBattleArray(wBattleArrayID))
    {
        if( dwTotleAckCnt >= GetMaxTotleAtkCnt())
        {
            bIsSubBuyCnt = true;
            //没有购买次数了
            if(0 == GetTotleBuyCnt())
            {
                _rPlayer.SendSysMsg(eMsgBattleArrayTotalAttackLimit);
                return eBattleArrayRet_TotalAttackLimit;
            }
        }
    }

    //单阵图次数限制
    if(bIsEye)
    if(GetAttackCnt(dwBattleArrayLevelID)>=SParamConfig::wBattleArrayTimes)
    {
        LOG_INF<<"AttackCnt limit: "<<GetAttackCnt(dwBattleArrayLevelID);
        _rPlayer.SendSysMsg(eMsgBattleArrayAttackLimit);
        return eBattleArrayRet_AttackLimit;
    }


    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        LOG_CRI<<"NULL == pAutoStoreMgr";
        _rPlayer.SendSysMsg(eMsgBattleArrayErrorCFG);
        return eBattleArrayRet_ErrorCFG;
    }

    SBattleArrayDBInfoPtr pBattleArrayDBInfo = GetBattleArray(wBattleArrayID); 
    if(NULL== pBattleArrayDBInfo )
    {
        if(!IsInitLevelID(dwBattleArrayLevelID))
        {
            _rPlayer.SendSysMsg(eMsgBattleArrayPreLevel);
            return eBattleArrayRet_PreLevel;
        }
    }
    else
    {
        if(dwBattleArrayLevelID > pBattleArrayDBInfo->dwBattleArrayLevelID + 1 )
        {
            _rPlayer.SendSysMsg(eMsgBattleArrayPreLevel);
            return eBattleArrayRet_PreLevel;
        }

        //阵位只能攻击一次
        if((!bIsEye) && dwBattleArrayLevelID<= pBattleArrayDBInfo->dwBattleArrayLevelID )
        {
            //阵位
            _rPlayer.SendSysMsg(eMsgBattleArrayPosLimit);
            return eBattleArrayRet_PosLimit;
        }
        //new
        else if(dwBattleArrayLevelID == pBattleArrayDBInfo->dwBattleArrayLevelID + 1)
        {

        }

    }

    _dwAttackCd = time(NULL) + 2;

    //atk monster
    EBattleResult eBattleResult;
    UINT32 dwRounds = 0;
    std::string strReport;
    bool bRet =  AttackMonster(_rPlayer,pBattleArrayLevelCFGEx->_MonsterGroupID,eBattleResult,dwRounds,strReport);
    if(!bRet)
    {
        LOG_CRI << "AttackMonster failed!! MonsterGroupID:" << pBattleArrayLevelCFGEx->_MonsterGroupID;
        _rPlayer.SendSysMsg(eMsgBattleArrayErrorCFG); 
        return eBattleArrayRet_ErrorCFG;
    }

    //非胜利
    if(EBResultAttackWin != eBattleResult)
    {
        _rPlayer.SendPkg(g_BattleGSS.BuildPkg_BattleReportData(strReport, _rPlayer.GetRoleID(), _rPlayer.GetMainFighter()->GetID()));

        SetFailCD(time(NULL) + SParamConfig::wBattleArrayFailCD);
        return eBattleArrayRet_Sucess;
    }

    LOG_INF << "AttackMonster ret: " << eBattleResult << ", "
        << "wBattleArrayID: " << wBattleArrayID << ", "
        << "dwBattleArrayLevelID: "<< dwBattleArrayLevelID << ".";

    string &strPreBattle = strReport;
    CInArchive iar(strPreBattle);
    SBattleReport stPreBattle;
    iar >> stPreBattle;
   
    TVecItemGenInfo& oVecItemGenInfo = stPreBattle.vecItem;
    TVecResource& vecRes = stPreBattle.vecResSource;

    bool bNewAtk = false;

    //攻击胜利
    if(EBResultAttackWin == eBattleResult)
    {
        if(NULL== pBattleArrayDBInfo)
        {
            SBattleArrayDBInfoPtr pBattleArray(new SBattleArrayDBInfo);
            pBattleArray->qwRoleID = _rPlayer.GetRoleID();
            pBattleArray->wBattleArrayID = wBattleArrayID;
            pBattleArray->dwBattleArrayLevelID = dwBattleArrayLevelID;
            pBattleArray->byBattleArrayStatus = eBattleArrayStatus_Init;
            _mapBattleArrayPtr.insert(make_pair(wBattleArrayID,pBattleArray));
            Update2DB(*pBattleArray);
            
            SBattleArray oBattleArray;
            oBattleArray.wBattleArrayID = wBattleArrayID;
            oBattleArray.dwBattleArrayLevelID = dwBattleArrayLevelID;
            oBattleArray.eBattleArrayStatus = eBattleArrayStatus_Init;
            _rPlayer.SendPkg(g_BattleArrayS.BuildPkg_BattleArrayNotify(oBattleArray));

            rPack.AddItemByLootID(pBattleArrayLevelCFGEx->_FirstPassLootId,NLogDataDefine::ItemFrom_BattleArrayItem,true,&oVecItemGenInfo,&vecRes);
            rPack.AddItemByLootID(pBattleArrayLevelCFGEx->_PassLootId,NLogDataDefine::ItemFrom_BattleArrayItem,true,&oVecItemGenInfo,&vecRes);

            LOG_DBG<<" NEW ..."<<wBattleArrayID;

            bNewAtk = true;

        }
        else
        {
            if(dwBattleArrayLevelID == pBattleArrayDBInfo->dwBattleArrayLevelID + 1)
            {
                //破阵标志
                if(pBattleArrayLevelCFGEx->_PassTag)
                {
                    pBattleArrayDBInfo->byBattleArrayStatus = eBattleArrayStatus_End;
                }
                 pBattleArrayDBInfo->dwBattleArrayLevelID = dwBattleArrayLevelID;
                 Update2DB(*pBattleArrayDBInfo);
                
                SBattleArray oBattleArray;
                oBattleArray.wBattleArrayID = wBattleArrayID;
                oBattleArray.dwBattleArrayLevelID = dwBattleArrayLevelID;
                oBattleArray.eBattleArrayStatus = (EBattleArrayStatus)pBattleArrayDBInfo->byBattleArrayStatus;
                _rPlayer.SendPkg(g_BattleArrayS.BuildPkg_BattleArrayNotify(oBattleArray));
                rPack.AddItemByLootID(pBattleArrayLevelCFGEx->_FirstPassLootId,NLogDataDefine::ItemFrom_BattleArrayItem,true,&oVecItemGenInfo,&vecRes);

                rPack.AddItemByLootID(pBattleArrayLevelCFGEx->_PassLootId,NLogDataDefine::ItemFrom_BattleArrayItem,true,&oVecItemGenInfo,&vecRes);
                LOG_DBG<<" NEW ..."<<dwBattleArrayLevelID;

                bNewAtk = true; 
            }
            else
            {
                rPack.AddItemByLootID(pBattleArrayLevelCFGEx->_PassLootId,true,NLogDataDefine::ItemFrom_BattleArrayItem,&oVecItemGenInfo,&vecRes);
                LOG_DBG<<" old ..."<<dwBattleArrayLevelID;
            }
        }

   }

    strPreBattle.clear();
    COutArchive oar(strPreBattle);
    oar << stPreBattle;
    _rPlayer.SendPkg(g_BattleGSS.BuildPkg_BattleReportData(strPreBattle, _rPlayer.GetRoleID(), _rPlayer.GetMainFighter()->GetID()));
 
    _rPlayer.PendDrop(oVecItemGenInfo,vecRes,PendBattle);

    _oPendVecItemGenInfo.clear();
    _oPendVecItemGenInfo = oVecItemGenInfo;
    PushItemFromRes(_oPendVecItemGenInfo,vecRes);

    if(pBattleArrayLevelCFGEx->_CostEnergy)
    {
        rUser.SubMoney(EMONEY_ACTION,pBattleArrayLevelCFGEx->_CostEnergy,NLogDataDefine::ItemTo_BattleArrayItem);
    }

    if(bNewAtk)
    {
        TVecINT32 vecParam;
        vecParam.push_back(dwBattleArrayLevelID);
        vecParam.push_back(_rPlayer.GetBattlePoint());
        _rPlayer.OnEvent(eEventType_BattleArraySuccessInfo,vecParam);
    }

    {
        TVecINT32 vecParam;
        vecParam.push_back(dwBattleArrayLevelID);
        vecParam.push_back(1);
        _rPlayer.OnEvent(eEventType_BattleArraySuccess,vecParam);
    }

    if(bIsEye) 
    {
        if(bNewAtk)
        {

        }
        else
        {
            if(bIsSubBuyCnt)
            {
                UINT32 dwBuyCnt = GetTotleBuyCnt();
                if(dwBuyCnt)
                    SetTotleBuyCnt(dwBuyCnt-1);
            }
            else
            {
               SetTotleAtkCnt(dwTotleAckCnt + 1);
            }
         
            //增加单阵图次数
            AddAttackCnt(dwBattleArrayLevelID,1);
        }

        SetMinTurns(dwBattleArrayLevelID,dwRounds,pBattleArrayLevelCFGEx);
        _rPlayer.GetUser().GetTaskPkg().OnAction(_rPlayer,  eProcessAction_BrockenBattleArrayEyeSuc);

    }

    UINT32 dwCnt = GetAttackCnt(dwBattleArrayLevelID);

    LOG_INF<<"roleId:"<<_rPlayer.GetRoleID()<<" AddAttackCnt dwBattleArrayLevelID:"<<dwBattleArrayLevelID<<" count:"<<dwCnt<<" totleAtkCnt:"<<GetTotleAtkCnt()<<" totleBuyCnt:"<<GetTotleBuyCnt();
    SBattleArrayAttackCnt oBattleArrayAttackCnt;
    oBattleArrayAttackCnt.dwBattleArrayLevelID = dwBattleArrayLevelID;
    oBattleArrayAttackCnt.wCount = dwCnt;
    oBattleArrayAttackCnt.wMinTurn = GetMinTurns(dwBattleArrayLevelID); 
    _rPlayer.SendPkg(g_BattleArrayS.BuildPkg_SBattleArrayAttackCntNotify(oBattleArrayAttackCnt));
    if(bIsEye)
        _rPlayer.SendPkg(g_BattleArrayS.BuildPkg_TotleAttackCntNotify(GetTotleAtkCnt(),GetTotleBuyCnt()));
    return eBattleArrayRet_Sucess;
}

EBattleArrayRet CBattleArrayMgr::OnSweepBattleArray(UINT32 dwBattleArrayLevelID)
{
    UINT16 wBattleArrayID = GetIDByLevelID(dwBattleArrayLevelID);
    SBattleArrayDBInfoPtr pBattleArrayDBInfo = GetBattleArray(wBattleArrayID);
    if(NULL == pBattleArrayDBInfo)
    {
        LOG_CRI<<"eBattleArrayRet_NoPass";
        _rPlayer.SendSysMsg(eMsgBattleArrayNoPass);
        return eBattleArrayRet_NoPass;
    }

    if(dwBattleArrayLevelID > pBattleArrayDBInfo->dwBattleArrayLevelID)
    {
        LOG_CRI<<"dwBattleArrayLevelID > pBattleArrayDBInfo->dwBattleArrayLevelID";
        _rPlayer.SendSysMsg(eMsgBattleArrayNoPass);
        return eBattleArrayRet_NoPass;
    }

    SBattleArrayLevelCFGExPtr pBattleArrayLevelCFGEx = GetBattleArrayLevelCFG(dwBattleArrayLevelID);
    if(NULL == pBattleArrayLevelCFGEx)
    {
        LOG_CRI<<"error BattleArrayLevelCFG: "<<dwBattleArrayLevelID;
        _rPlayer.SendSysMsg(eMsgBattleArrayErrorCFG);
        return eBattleArrayRet_ErrorCFG;
    }
    
    //阵位不能扫荡
    if(pBattleArrayLevelCFGEx->_SpotType == eBattleArrayLevelType_positon)
    {
       //阵位
       _rPlayer.SendSysMsg(eMsgBattleArrayPosLimit);
       return eBattleArrayRet_PosLimit;
    }

    CUser& rUser = _rPlayer.GetUser();
    CPack& rPack = rUser.GetPack();
 
    if(pBattleArrayLevelCFGEx->_CostEnergy)
    {
        if(!rUser.CanSubMoney(EMONEY_ACTION,pBattleArrayLevelCFGEx->_CostEnergy))
        {
            _rPlayer.SendSysMsg(eMsgDungeonPowerErr);
            return eBattleArrayRet_MoneyError;
        }
    }


   
    if(rPack.GetEmptyCount() < pBattleArrayLevelCFGEx->_RequiredPackage)
    {
        _rPlayer.SendSysMsg(eMsgBattleArrayPackError);
        return eBattleArrayRet_PackError;
    }


    UINT32 dwCnt = GetAttackCnt(dwBattleArrayLevelID);
    if(dwCnt>=SParamConfig::wBattleArrayTimes)
    {
        _rPlayer.SendSysMsg(eMsgBattleArrayAttackLimit);
        return eBattleArrayRet_TotalAttackLimit;
    }

    UINT32 dwSeepCount = SParamConfig::wBattleArrayTimes - dwCnt;
   
    //策划改称1次
    dwSeepCount = 1;
    
    bool bIsUserBuyCnt = false;
    
    UINT32 dwNowTotle = GetTotleAtkCnt();
    if(dwNowTotle >= GetMaxTotleAtkCnt())
    {
        bIsUserBuyCnt = true;

        if(GetTotleBuyCnt()<dwSeepCount)
        {
            _rPlayer.SendSysMsg(eMsgBattleArrayTotalAttackLimit);
            return eBattleArrayRet_TotalAttackLimit;
        }
    }

    if(pBattleArrayLevelCFGEx->_CostEnergy)
    {
        rUser.SubMoney(EMONEY_ACTION,pBattleArrayLevelCFGEx->_CostEnergy,NLogDataDefine::ItemTo_BattleArrayItem);
    }


    TVecItemGenInfo vecItems;
    TVecResource vecRes;

    for(UINT32 i = 0; i < dwSeepCount; i++)
    {
        LOOT.Roll(pBattleArrayLevelCFGEx->_PassLootId, vecItems,vecRes);
        //rPack.AddItemByLootID(pBattleArrayLevelCFGEx->_PassLootId,NLogDataDefine::ItemFrom_BattleArrayItem);
    }

    PushItemFromRes(vecItems,vecRes);
    rPack.AddItem(vecItems,NLogDataDefine::ItemFrom_BattleArrayItem);

    if(bIsUserBuyCnt)
    {
        UINT32 dwBuyCnt = GetTotleBuyCnt();
        if(dwBuyCnt)
            SetTotleBuyCnt(dwBuyCnt-dwSeepCount);
    }
    else
    {

        SetTotleAtkCnt(dwNowTotle + dwSeepCount);
    }
    
    //事件
    TVecINT32 vecParam;
    vecParam.push_back(dwBattleArrayLevelID);
    vecParam.push_back(1);
    _rPlayer.OnEvent(eEventType_BattleArraySuccess,vecParam);
 
    //单阵图次数
    AddAttackCnt(dwBattleArrayLevelID,dwSeepCount);

    UINT32 dwCount = dwCnt + dwSeepCount;
    SBattleArrayAttackCnt oBattleArrayAttackCnt;
    oBattleArrayAttackCnt.dwBattleArrayLevelID = dwBattleArrayLevelID;
    oBattleArrayAttackCnt.wCount = dwCount;
    _rPlayer.SendPkg(g_BattleArrayS.BuildPkg_SBattleArrayAttackCntNotify(oBattleArrayAttackCnt));
    _rPlayer.SendPkg(g_BattleArrayS.BuildPkg_TotleAttackCntNotify(GetTotleAtkCnt(),GetTotleBuyCnt()));
    _rPlayer.SendPkg(g_BattleArrayS.BuildPkg_GainNotify(eBattleArrayGain_Sweep,vecItems));
    _rPlayer.GetUser().GetTaskPkg().OnAction(_rPlayer,  eProcessAction_BrockenBattleArrayEyeSuc);
    LOG_INF<<"roleId:"<<_rPlayer.GetRoleID()<<" AddAttackCnt dwBattleArrayLevelID:"<<dwBattleArrayLevelID<<" count:"<<dwCount<<" totleAtkCnt:"<<GetTotleAtkCnt()<<" totleBuyCnt:"<<GetTotleBuyCnt();
    return eBattleArrayRet_Sucess;

}

EBattleArrayRet CBattleArrayMgr::OnBattleArrayTakePrize(UINT16 wBattleArrayID)
{
    SBattleArrayDBInfoPtr pBattleArrayDBInfo = GetBattleArray(wBattleArrayID);
    if(NULL == pBattleArrayDBInfo)
    {
        LOG_INF<<"eBattleArrayRet_NoPass";
        _rPlayer.SendSysMsg(eMsgBattleArrayNoPass);
        return eBattleArrayRet_NoPass;
    }

    if(pBattleArrayDBInfo->byBattleArrayStatus == eBattleArrayStatus_Init)
    {
        LOG_INF<<"eBattleArrayRet_NoPass";
        _rPlayer.SendSysMsg(eMsgBattleArrayNoPass);
        return eBattleArrayRet_NoPass;
    }

    if(pBattleArrayDBInfo->byBattleArrayStatus == eBattleArrayStatus_TakePrized)
    {
        LOG_INF<<"eBattleArrayRet_TakePrized";
        _rPlayer.SendSysMsg(eMsgBattleArrayTakePrized);
        return eBattleArrayRet_TakePrized;
    }
    
    SBattleArrayCFGExPtr pBattleArrayCFGEx = GetBattleArrayCFG(wBattleArrayID);
    if(NULL == pBattleArrayCFGEx)
    {
        LOG_CRI<<"error wBattleArrayID: "<<wBattleArrayID;
        _rPlayer.SendSysMsg(eMsgBattleArrayErrorCFG);
        return eBattleArrayRet_ErrorCFG;
    }

    CUser& rUser = _rPlayer.GetUser();
    CPack& rPack = rUser.GetPack();
    if (!rPack.CanAddItem(pBattleArrayCFGEx->vecPassPrize))
    {
        rUser.SendSysMsg(eMsgPackFullErr);
        _rPlayer.SendSysMsg(eMsgBattleArrayPackError);
        return eBattleArrayRet_PackError;
    }
    
    if (!rPack.AddItem(pBattleArrayCFGEx->vecPassPrize, NLogDataDefine::ItemFrom_BattleArrayItem))
    {
        _rPlayer.SendSysMsg(eMsgBattleArrayPackError);
        return eBattleArrayRet_PackError;
    }


    pBattleArrayDBInfo->byBattleArrayStatus = eBattleArrayStatus_TakePrized;
    Update2DB(*pBattleArrayDBInfo);

    SBattleArray oBattleArray;
    oBattleArray.wBattleArrayID = wBattleArrayID;
    oBattleArray.dwBattleArrayLevelID = pBattleArrayDBInfo->dwBattleArrayLevelID;
    oBattleArray.eBattleArrayStatus = (EBattleArrayStatus)pBattleArrayDBInfo->byBattleArrayStatus;
    _rPlayer.SendPkg(g_BattleArrayS.BuildPkg_BattleArrayNotify(oBattleArray));

    LOG_INF<<" OnBattleArrayTakePrize roleID:"<<_rPlayer.GetRoleID()<<" wBattleArrayID"<<wBattleArrayID;


    return eBattleArrayRet_Sucess;

}

//获取攻击阵图次数
UINT32 CBattleArrayMgr::GetAttackCnt(UINT32 dwBattleArrayLevelID)
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        LOG_CRI<<"NULL == pAutoStoreMgr";
        return 0;
    }

    return pAutoStoreMgr->GetValue(eAutoStore_BattleArray,dwBattleArrayLevelID);
}

//增加攻击阵图次数
void   CBattleArrayMgr::AddAttackCnt(UINT32 dwBattleArrayLevelID,UINT32 dwAdd )
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        LOG_CRI<<"NULL == pAutoStoreMgr";
        return;
    }

    pAutoStoreMgr->AddValue(eAutoStore_BattleArray,dwBattleArrayLevelID,dwAdd);
}

//设置攻击阵图次数
void   CBattleArrayMgr::SetAttackCnt(UINT32 dwBattleArrayLevelID,UINT32 dwValue)
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        LOG_CRI<<"NULL == pAutoStoreMgr";
        return;
    }

    pAutoStoreMgr->SetValue(eAutoStore_BattleArray,dwBattleArrayLevelID,dwValue);

}

//设置攻击阵图最小轮数
void   CBattleArrayMgr::SetMinTurns(UINT32 dwBattleArrayLevelID,UINT32 dwMinTurns,SBattleArrayLevelCFGExPtr pBattleArrayLevelCFGEx)
{
    if(NULL == pBattleArrayLevelCFGEx)
    {
        LOG_CRI<<"NULL == pBattleArrayLevelCFGEx";
        return;
    }
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        LOG_CRI<<"NULL == pAutoStoreMgr";
        return;
    }

    UINT32 dwOldMinTurns = GetMinTurns(dwBattleArrayLevelID);
    if(dwOldMinTurns)
    {
        if(dwOldMinTurns <= dwMinTurns)
            return;
    }

    if(!pBattleArrayLevelCFGEx->vecStar.empty())
    {
        UINT32 dwCount = 0;
        for(size_t i = pBattleArrayLevelCFGEx->vecStar.size(); i > 0; i-- )
        {
            UINT16 wStar = pBattleArrayLevelCFGEx->vecStar[i-1];
            if(dwOldMinTurns && dwOldMinTurns <= wStar)
                continue;
            if(dwMinTurns <= wStar)
            {
                dwCount++;
            }
            else
            {
                break;
            }
        }

        if(dwCount)
        {
            CUser& rUser = _rPlayer.GetUser();
            rUser.AddMoney(EMONEY_REIKI,dwCount,NLogDataDefine::ItemFrom_BattleArrayItem);
        }
        LOG_INF<<"roleId:"<<_rPlayer.GetUserID()<<" SetMinTurns: "<<dwOldMinTurns<<" -> "<<dwMinTurns<<" res:"<<dwCount;
    }

    pAutoStoreMgr->SetValue(eAutoStore_BattleArray_MinTurns,dwBattleArrayLevelID,dwMinTurns);

}

//获取攻击阵图次数最小轮数
UINT32 CBattleArrayMgr::GetMinTurns(UINT32 dwBattleArrayLevelID)
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        LOG_CRI<<"NULL == pAutoStoreMgr";
        return 0;
    }

    return pAutoStoreMgr->GetValue(eAutoStore_BattleArray_MinTurns,dwBattleArrayLevelID);
}


//获取总次数
UINT32 CBattleArrayMgr::GetTotleAtkCnt()
{
    return GetAttackCnt(0);
    //屏蔽总次数限制
    //return 0;
}

//设置总次数
void   CBattleArrayMgr::SetTotleAtkCnt(UINT32 dwCount)
{
    SetAttackCnt(0,dwCount);
}

UINT32 CBattleArrayMgr::GetMaxTotleAtkCnt()
{
    const SVIPLevelCFGEx* pCfgVip = VIPMgr.GetVIPLevelCfg(_rPlayer.GetUser().GetVIPLevel());
    if(NULL == pCfgVip)
    {
        return 0;
    }

    return pCfgVip->_BattleArrayTimes;
}

UINT32 CBattleArrayMgr::GetMaxBuyCnt()
{
    const SVIPLevelCFGEx* pCfgVip = VIPMgr.GetVIPLevelCfg(_rPlayer.GetUser().GetVIPLevel());
    if(NULL == pCfgVip)
    {
        return 0;
    }

    return pCfgVip->_BattleArrayBoughtTimes;
}



//获取购买次数
UINT32 CBattleArrayMgr::GetTotleBuyCnt()
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        LOG_CRI<<"NULL == pAutoStoreMgr";
        return 0;
    }

    return pAutoStoreMgr->GetValue(eAutoStore_BattleArray_BuyAtkCnt,eBattleArraySave_TotleCnt);
}

//设置购买次数
void   CBattleArrayMgr::SetTotleBuyCnt(UINT32 dwCount)
{
    //eAutoStore_BattleArray_BuyAtkCnt
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        LOG_CRI<<"NULL == pAutoStoreMgr";
        return ;
    }

    pAutoStoreMgr->SetValue(eAutoStore_BattleArray_BuyAtkCnt,eBattleArraySave_TotleCnt,dwCount);

}

//获取当天购买次数
UINT32 CBattleArrayMgr::GetDayTotleBuyCnt()
{
    return GetAttackCnt(1); 
}

//设置当天购买次数
void   CBattleArrayMgr::SetDayTotleBuyCnt(UINT32 dwCount)
{
    SetAttackCnt(1,dwCount);
}

//
UINT32 CBattleArrayMgr::GetFailCD()
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        LOG_CRI<<"NULL == pAutoStoreMgr";
        return 0;
    }

    return pAutoStoreMgr->GetValue(eAutoStore_BattleArray_BuyAtkCnt,eBattleArraySave_FailCd);

}
void   CBattleArrayMgr::SetFailCD(UINT32 dwFailCD)
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        LOG_CRI<<"NULL == pAutoStoreMgr";
        return ;
    }

    pAutoStoreMgr->SetValue(eAutoStore_BattleArray_BuyAtkCnt,eBattleArraySave_FailCd,dwFailCD);

}

//第一次破阵眼
bool CBattleArrayMgr::IsFirstAttack()
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        LOG_CRI<<"NULL == pAutoStoreMgr";
        return 0;
    }
    return 0 == pAutoStoreMgr->GetValue(eAutoStore_BattleArray_BuyAtkCnt,eBattleArraySave_FirstAttack);
}

void CBattleArrayMgr::SetFirstAttack()
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        LOG_CRI<<"NULL == pAutoStoreMgr";
        return ;
    }

    pAutoStoreMgr->SetValue(eAutoStore_BattleArray_BuyAtkCnt,eBattleArraySave_FirstAttack,1);
}


UINT32 GetPrice(UINT32 dwDayNowCnt)
{
    if(CBattleArrayMgr::_vecBattleArrayPriceCFG.empty())
    {
        LOG_CRI<<"error BattleArrayPrice empty!!!";
        return 100;
    }

    UINT32 dwPriceSize = CBattleArrayMgr::_vecBattleArrayPriceCFG.size();

    if(dwDayNowCnt < dwPriceSize)
    {
        return CBattleArrayMgr::_vecBattleArrayPriceCFG[dwDayNowCnt]._BattleArrayPrice;
    }

    return CBattleArrayMgr::_vecBattleArrayPriceCFG[dwPriceSize-1]._BattleArrayPrice;
}

UINT32 GetTotlePrice(UINT32 dwDayNowCnt, UINT32 dwBuyCnt)
{
    UINT32 dwTotle = 0;
    for(UINT32 i = 0; i < dwBuyCnt; i++)
    {
        dwTotle += GetPrice(dwDayNowCnt+i);
    }

    return dwTotle;
}

//查询价格
EBattleArrayRet CBattleArrayMgr::OnGetBuyAtkCountPrice(UINT32 dwCount,shared_func<CBattleArraySvr::SGetBuyAtkCountPriceAck>& fnAck)
{
    UINT32 dwDayNowCnt = GetDayTotleBuyCnt();
    UINT32 dwTotlePrice = GetTotlePrice(dwDayNowCnt,dwCount);
    fnAck->dwPrice = dwTotlePrice;
    fnAck->dwBuyCount = dwDayNowCnt;

    return eBattleArrayRet_Sucess;
}

//购买攻击次数
EBattleArrayRet CBattleArrayMgr::OnBuyAtkCount(UINT32 dwCount,shared_func<CBattleArraySvr::SBuyAtkCountAck>& fnAck)
{

    UINT32 dwDayNowCnt = GetDayTotleBuyCnt();

    fnAck->dwDayBuyCnt = GetDayTotleBuyCnt();
    fnAck->dwBuyCount = GetTotleBuyCnt();


    UINT32 dwTotlePrice = GetTotlePrice(dwDayNowCnt,dwCount);


    LOG_INF<<"roleId:"<<_rPlayer.GetRoleID()<<"OnBuyAtkCount:"<<dwCount<<"dwDayNowCnt:"<<dwDayNowCnt<<"dwTotlePrice:"<<dwTotlePrice;
    if(dwDayNowCnt>= GetMaxBuyCnt())
    {
        _rPlayer.SendSysMsg(eMsgBattleArrayMaxBuyCnt);
        return eBattleArrayRet_MaxBuyCnt;
    }
    if(!_rPlayer.GetUser().SubMoney(EMONEY_GOLD,dwTotlePrice,NLogDataDefine::ItemTo_BattleArrayItem))
    {
        _rPlayer.SendSysMsg(eMsgGoldErr);
        return eBattleArrayRet_MoneyError;
    }

    UINT32 dwDayTotleCnt = dwDayNowCnt+dwCount;
    SetDayTotleBuyCnt(dwDayTotleCnt);

    UINT32 dwTotleCnt = GetTotleBuyCnt() + dwCount;

    SetTotleBuyCnt(dwTotleCnt);

    fnAck->dwDayBuyCnt = GetDayTotleBuyCnt();
    fnAck->dwBuyCount = GetTotleBuyCnt();

    return eBattleArrayRet_Sucess;
}

//客户端发送战斗结束消息
void CBattleArrayMgr::OnFighterEnd()
{
    if(!_oPendVecItemGenInfo.empty())
    {
       // LOG_INF<<"OnFighterEnd";
        //_rPlayer.SendPkg(g_BattleArrayS.BuildPkg_GainNotify(eBattleArrayGain_Attack,_oPendVecItemGenInfo));
        _oPendVecItemGenInfo.clear();
        //LOG_CRI<<"OnFighterEnd()"; 
    }
    else
    {
        //LOG_CRI<<"_oPendVecItemGenInfo.empty()";
    }
}

//零点在线推送消息
void CBattleArrayMgr::OnMidNight()
{
    TVecBattleArray vecBattleArray;
    TVecBattleArrayAttackCnt vecBattleArrayAttackCnt;

    for(auto itr = _mapBattleArrayPtr.begin(); itr != _mapBattleArrayPtr.end(); itr++)
    {
        vecBattleArray.emplace_back(itr->second->wBattleArrayID,itr->second->dwBattleArrayLevelID,(EBattleArrayStatus)(itr->second->byBattleArrayStatus));
    }

    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        LOG_CRI<<"NULL == pAutoStoreMgr";
        return;
    }
   TSetUINT32 setBattleArrayID;
    TVecAutoStoreDBInfo vecAutoStoreDBInfo;
    pAutoStoreMgr->GetListByType(eAutoStore_BattleArray,vecAutoStoreDBInfo);
    for(size_t i=0;i < vecAutoStoreDBInfo.size(); i++)
    {
        if(vecAutoStoreDBInfo[i].dwClassID > 10)
        {
            setBattleArrayID.insert(vecAutoStoreDBInfo[i].dwClassID);
        }
        //fnAck->vecBattleArrayAttackCnt.emplace_back(vecAutoStoreDBInfo[i].dwClassID,vecAutoStoreDBInfo[i].dwValue);
    }

    vecAutoStoreDBInfo.clear();
    pAutoStoreMgr->GetListByType(eAutoStore_BattleArray_MinTurns,vecAutoStoreDBInfo);
    for(size_t i=0;i < vecAutoStoreDBInfo.size(); i++)
    {
        if(vecAutoStoreDBInfo[i].dwClassID > 10)
        {
            setBattleArrayID.insert(vecAutoStoreDBInfo[i].dwClassID);
        }
    }

    for(auto itr = setBattleArrayID.begin(); itr != setBattleArrayID.end(); itr++)
    {
        UINT32 dwBattleArrayID = *itr;
        SBattleArrayAttackCnt oBattleArrayAttackCnt;
        oBattleArrayAttackCnt.dwBattleArrayLevelID = dwBattleArrayID;
        oBattleArrayAttackCnt.wCount = GetAttackCnt(dwBattleArrayID);
        oBattleArrayAttackCnt.wMinTurn = GetMinTurns(dwBattleArrayID);
        vecBattleArrayAttackCnt.push_back(oBattleArrayAttackCnt);
    }

    UINT32 dwBuyCnt = GetTotleBuyCnt();
    UINT32 dwDayBuyCnt = GetDayTotleBuyCnt();


    _rPlayer.SendPkg(g_BattleArrayS.BuildPkg_GetBattleArrayNotify(vecBattleArray,vecBattleArrayAttackCnt,dwBuyCnt,dwDayBuyCnt));
    _rPlayer.SendPkg(g_BattleArrayS.BuildPkg_TotleAttackCntNotify(GetTotleAtkCnt(),GetTotleBuyCnt()));

 
}


