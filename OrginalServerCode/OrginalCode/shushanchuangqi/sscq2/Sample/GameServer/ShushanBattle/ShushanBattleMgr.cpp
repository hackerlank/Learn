#include "ShushanBattleMgr.h"
#include "ShushanBattle.h"
#include "Version.h"
#include "RTime.h"
#include "Protocols.h"
#include "Tokenizer.h"
#include "SysMsgDefine.h"
#include "CommonDef.h"
#include "Random.h"
#include "GameNetMgr.h"

UINT64 CShushanBattleMgr::_qwVersion = VERSION_INIT;
std::map<UINT8, SBattleSkillCFGEx> CShushanBattleMgr::_mapID2BattleSkillCFG;
std::vector<TVecTaskData> CShushanBattleMgr::_vecBattleTaskCFG[3];
std::map<UINT8, SBattleAwardCFGEx> CShushanBattleMgr::_mapID2BattleAwardCFG;
std::map<UINT8, SBattleExpCFGEx> CShushanBattleMgr::_mapID2BattleExpCFG;

CShushanBattleMgr::CShushanBattleMgr() : CDayActivity(NDayActProt::eActTypeShushanBattle),
	_byPrepareStep(0), _dwPrepareTime(0), _dwStartTime(0), _dwEndedTime(0), _bGMCheck(false)
{}

CShushanBattleMgr::~CShushanBattleMgr()
{}

bool CShushanBattleMgr::Init()
{
    return LoadConfig();
}

bool CShushanBattleMgr::LoadConfig(bool bReload /*= false*/)
{
    string strPath = Config._strConfigDir + "Conf/Table/ShushanBattleTask.xml";
    CShushanBattleTaskLoader oBattleTaskLoader;
    if (!oBattleTaskLoader.LoadData(strPath))
    {
        LOG_CRI << "oBattleTaskLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(UINT8 i=0 ; i<3 ; ++i)
        if(!_vecBattleTaskCFG[i].empty())
            _vecBattleTaskCFG[i].clear();
    TVecTaskData vecTaskData[3];
    for(size_t i = 0; i < oBattleTaskLoader._vecData.size(); ++i)
    {
        SShushanBattleTaskCFG* pBattleTaskCFG = oBattleTaskLoader._vecData[i];
        if (!pBattleTaskCFG || pBattleTaskCFG->_ID == 0 || pBattleTaskCFG->_Degree >= 3)
            continue;
        SBattleTaskData stTaskData;
        stTaskData.byTaskID   = pBattleTaskCFG->_ID;
        stTaskData.byAward    = pBattleTaskCFG->_Award;
        stTaskData.byComplete = 0;
        if (!pBattleTaskCFG->_Gradation)
        {
            TVecTaskData vecTmp;
            vecTmp.push_back(stTaskData);
            _vecBattleTaskCFG[pBattleTaskCFG->_Degree].push_back(vecTmp);
        }
        else
            vecTaskData[pBattleTaskCFG->_Degree].push_back(stTaskData);
    }
    for (int i = 0; i < 3; ++ i)
    {
        if (vecTaskData[i].size() > 1)
            _vecBattleTaskCFG[i].push_back(vecTaskData[i]);
    }

    strPath = Config._strConfigDir + "Conf/Table/ShushanBattleAward.xml";
    CShushanBattleAwardLoader oBattleAwardLoader;
    if (!oBattleAwardLoader.LoadData(strPath))
    {
        LOG_CRI << "oBattleAwardLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oBattleAwardLoader._vecData.size(); ++i)
    {
        SShushanBattleAwardCFG* pBattleAwardCFG = oBattleAwardLoader._vecData[i];
        if (!pBattleAwardCFG || pBattleAwardCFG->_HonorLevel == 0)
            continue;
        SBattleAwardCFGEx& rBattleAwardCFGEx = _mapID2BattleAwardCFG[pBattleAwardCFG->_HonorLevel];
        rBattleAwardCFGEx.SetConfig(*pBattleAwardCFG);

        Tokenizer tk(rBattleAwardCFGEx._Award, "|"); // XXX: instinctID
        for (size_t j = 0; j < tk.size(); ++ j)
        {
            Tokenizer yatk(tk[j], ",");
            UINT32 dwItemID = atoi(yatk[0].c_str());
            if (dwItemID)
            {
               UINT32 dwItemCount = 0;
                if (yatk.size() > 1)
                    dwItemCount = atoi(yatk[1].c_str());
                SItemGenInfo stItemGen;
                stItemGen.wItemID = dwItemID;
                stItemGen.dwCount = dwItemCount;
                stItemGen.eBindType = eBindGet;
                rBattleAwardCFGEx._vecItemGenInfo.push_back(stItemGen);
            }
        }
    }

    strPath = Config._strConfigDir + "Conf/Table/ShuShanLunJianExp.xml";
    CShuShanLunJianExpLoader oBattleExpLoader;
    if (!oBattleExpLoader.LoadData(strPath))
    {
        LOG_CRI << "oBattleExpLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oBattleExpLoader._vecData.size(); ++i)
    {
        SShuShanLunJianExpCFG* pBattleExpCFG = oBattleExpLoader._vecData[i];
        if (!pBattleExpCFG)
            continue;
        SBattleExpCFGEx& rBattleExpCFGEx = _mapID2BattleExpCFG[pBattleExpCFG->_Level];
        rBattleExpCFGEx.SetConfig(*pBattleExpCFG);
    }

    strPath = Config._strConfigDir + "Conf/Table/ShushanBattleSkill.xml";
    CShushanBattleSkillLoader oBattleSkillLoader;
    if (!oBattleSkillLoader.LoadData(strPath))
    {
        LOG_CRI << "oBattleSkillLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oBattleSkillLoader._vecData.size(); ++i)
    {
        SShushanBattleSkillCFG* pBattleSkillCFG = oBattleSkillLoader._vecData[i];
        if (!pBattleSkillCFG || pBattleSkillCFG->_ID == 0)
            continue;
        SBattleSkillCFGEx& rBattleSkillCFGEx = _mapID2BattleSkillCFG[pBattleSkillCFG->_ID];
        rBattleSkillCFGEx.SetConfig(*pBattleSkillCFG);

        VECATTR_RESET(rBattleSkillCFGEx._vecAddAttr);
        PHYATK_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        MGCATK_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        PHYDEF_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        MGCDEF_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        PHYRDC_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        MGCRDC_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        MAXHP_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        SPEED_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        HIT_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        HITRATE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        DODGE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        DODGERATE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        CRITICAL_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        CRTRATE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        ANTICRITCAL_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        ANTICRTRATE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        BLOCK_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        BLOCKRATE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        PIERCE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        PIERCERATE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        COUNTER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        COUNTERRATE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        RESIST_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        RESISTRATE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        INITAURA_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        MAXAURA_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        CRIEXTRAADD_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        CRIEXTRARDC_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        METALATK_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        WOODATK_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        WATERATK_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        FIREATK_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        EARTHATK_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        METALDEF_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        WOODDEF_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        WATERDEF_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        FIREDEF_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        EARTHDEF_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        PHYATK_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        MGCATK_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        PHYDEF_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        MGCDEF_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        MAXHP_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        SPEED_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        HIT_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        DODGE_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        CRITICAL_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        ANTICRITCAL_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        BLOCK_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        PIERCE_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        COUNTER_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        RESIST_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        ANTIEFFECT_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        COUTEREXTRAADD_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        COUTEREXTRARDC_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
    }
    return true;
}

bool CShushanBattleMgr::ReLoadConfig(const string& strFile)
{
    string strPath;
    if("ShushanBattleTask.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/ShushanBattleTask.xml";
        CShushanBattleTaskLoader oBattleTaskLoader;
        if (!oBattleTaskLoader.LoadData(strPath))
        {
            LOG_CRI << "oBattleTaskLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        TVecTaskData vecTaskData[3];
        for(size_t i = 0; i < oBattleTaskLoader._vecData.size(); ++i)
        {
            SShushanBattleTaskCFG* pBattleTaskCFG = oBattleTaskLoader._vecData[i];
            if (!pBattleTaskCFG || pBattleTaskCFG->_ID == 0 || pBattleTaskCFG->_Degree >= 3)
                continue;
            SBattleTaskData stTaskData;
            stTaskData.byTaskID   = pBattleTaskCFG->_ID;
            stTaskData.byAward    = pBattleTaskCFG->_Award;
            stTaskData.byComplete = 0;
            if (!pBattleTaskCFG->_Gradation)
            {
                TVecTaskData vecTmp;
                vecTmp.push_back(stTaskData);
                _vecBattleTaskCFG[pBattleTaskCFG->_Degree].push_back(vecTmp);
            }
            else
                vecTaskData[pBattleTaskCFG->_Degree].push_back(stTaskData);
        }
        for (int i = 0; i < 3; ++ i)
        {
            if (vecTaskData[i].size() > 1)
                _vecBattleTaskCFG[i].push_back(vecTaskData[i]);
        }
    }else if("ShushanBattleAward.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/ShushanBattleAward.xml";
        CShushanBattleAwardLoader oBattleAwardLoader;
        if (!oBattleAwardLoader.LoadData(strPath))
        {
            LOG_CRI << "oBattleAwardLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oBattleAwardLoader._vecData.size(); ++i)
        {
            SShushanBattleAwardCFG* pBattleAwardCFG = oBattleAwardLoader._vecData[i];
            if (!pBattleAwardCFG || pBattleAwardCFG->_HonorLevel == 0)
                continue;
            SBattleAwardCFGEx& rBattleAwardCFGEx = _mapID2BattleAwardCFG[pBattleAwardCFG->_HonorLevel];
            rBattleAwardCFGEx.SetConfig(*pBattleAwardCFG);

            Tokenizer tk(rBattleAwardCFGEx._Award, "|"); // XXX: instinctID
            for (size_t j = 0; j < tk.size(); ++ j)
            {
                Tokenizer yatk(tk[j], ",");
                UINT32 dwItemID = atoi(yatk[0].c_str());
                if (dwItemID)
                {
                   UINT32 dwItemCount = 0;
                    if (yatk.size() > 1)
                        dwItemCount = atoi(yatk[1].c_str());
                    SItemGenInfo stItemGen;
                    stItemGen.wItemID = dwItemID;
                    stItemGen.dwCount = dwItemCount;
                    stItemGen.eBindType = eBindGet;
                    rBattleAwardCFGEx._vecItemGenInfo.push_back(stItemGen);
                }
            }
        }
    }else if("ShuShanLunJianExp.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/ShuShanLunJianExp.xml";
        CShuShanLunJianExpLoader oBattleExpLoader;
        if (!oBattleExpLoader.LoadData(strPath))
        {
            LOG_CRI << "oBattleExpLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oBattleExpLoader._vecData.size(); ++i)
        {
            SShuShanLunJianExpCFG* pBattleExpCFG = oBattleExpLoader._vecData[i];
            if (!pBattleExpCFG)
                continue;
            SBattleExpCFGEx& rBattleExpCFGEx = _mapID2BattleExpCFG[pBattleExpCFG->_Level];
            rBattleExpCFGEx.SetConfig(*pBattleExpCFG);
        }
    }else if("ShushanBattleSkill.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/ShushanBattleSkill.xml";
        CShushanBattleSkillLoader oBattleSkillLoader;
        if (!oBattleSkillLoader.LoadData(strPath))
        {
            LOG_CRI << "oBattleSkillLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oBattleSkillLoader._vecData.size(); ++i)
        {
            SShushanBattleSkillCFG* pBattleSkillCFG = oBattleSkillLoader._vecData[i];
            if (!pBattleSkillCFG || pBattleSkillCFG->_ID == 0)
                continue;
            SBattleSkillCFGEx& rBattleSkillCFGEx = _mapID2BattleSkillCFG[pBattleSkillCFG->_ID];
            rBattleSkillCFGEx.SetConfig(*pBattleSkillCFG);

            VECATTR_RESET(rBattleSkillCFGEx._vecAddAttr);
            PHYATK_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            MGCATK_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            PHYDEF_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            MGCDEF_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            PHYRDC_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            MGCRDC_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            MAXHP_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            SPEED_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            HIT_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            HITRATE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            DODGE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            DODGERATE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            CRITICAL_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            CRTRATE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            ANTICRITCAL_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            ANTICRTRATE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            BLOCK_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            BLOCKRATE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            PIERCE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            PIERCERATE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            COUNTER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            COUNTERRATE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            RESIST_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            RESISTRATE_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            INITAURA_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            MAXAURA_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            CRIEXTRAADD_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            CRIEXTRARDC_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            METALATK_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            WOODATK_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            WATERATK_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            FIREATK_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            EARTHATK_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            METALDEF_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            WOODDEF_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            WATERDEF_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            FIREDEF_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            EARTHDEF_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            PHYATK_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            MGCATK_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            PHYDEF_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            MGCDEF_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            MAXHP_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            SPEED_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            HIT_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            DODGE_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            CRITICAL_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            ANTICRITCAL_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            BLOCK_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            PIERCE_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            COUNTER_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            RESIST_PER_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            ANTIEFFECT_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            COUTEREXTRAADD_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
            COUTEREXTRARDC_ADD(rBattleSkillCFGEx._vecAddAttr, pBattleSkillCFG);
        }
    }
    return true;
}

bool CShushanBattleMgr::GMOpen()
{
    time_t tNow = time(NULL);
    _dwAlarmTime = tNow;
    _dwReadyTime = tNow;
    _dwBeginTime = tNow + 1*60;  //30s
    _dwEndTime   = _dwBeginTime + 15*60; //15minute

    ClearEvent();
    _dwPrepareTime = _dwReadyTime;
    _dwStartTime   = _dwBeginTime;
    _dwEndedTime   = _dwEndTime;

    SetStatus(eDayActivityStatusAlarm);
    AddEvent(eShushanBattleEvent_10Tip,_dwReadyTime,10);
    AddEvent(eShushanBattleEvent_5Tip,_dwReadyTime+5*60,5);

    //AddPeriodEvent(eShushanBattleEvent_NPC_ATTACK,_dwBeginTime,100,GetParam());
    return true;
}

bool CShushanBattleMgr::OnAlarm()
{
    bool bRet = CDayActivity::OnAlarm();
    if(!bRet)
    {
        return false;
    }

    ClearEvent();
    _dwPrepareTime = _dwReadyTime;
    _dwStartTime   = _dwBeginTime;
    _dwEndedTime   = _dwEndTime;

    AddEvent(eShushanBattleEvent_10Tip,_dwReadyTime,10);
    AddEvent(eShushanBattleEvent_5Tip,_dwReadyTime+5*60,5);

    //AddPeriodEvent(eShushanBattleEvent_NPC_ATTACK,_dwBeginTime,100,GetParam());
    return true;
}

void CShushanBattleMgr::OnReady()
{
    CDayActivity::OnReady();

    //g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgLunJianSignIn);
}

void CShushanBattleMgr::OnBegin()
{
    CDayActivity::OnBegin();
    //g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgLunJianBegin);
}

void CShushanBattleMgr::OnEnd()
{
    CDayActivity::OnEnd();
    ClearEvent();
    //g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgLangHuanBlessEnd);

    //ClearEvent(eShushanBattleEvent_NPC_ATTACK);

    /*
    UINT32 dwKickTime = 30;
    AddEvent(eShushanBattleEvent_KickPlayer,time(NULL)+dwKickTime);
    */
}

void CShushanBattleMgr::OnEvent(SActEventData& oSActEventData)
{
    switch(oSActEventData.dwEventID)
    {
        case eShushanBattleEvent_10Tip:
        case eShushanBattleEvent_5Tip:
            {
                //g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgLunJianStart,BuildStrVec(oSActEventData.dwParam));
            }
            break;
        case eShushanBattleEvent_NPC_ATTACK:
            break;
        case eShushanBattleEvent_KickPlayer:
            break;
        default:
            break;
    }
}

SBattleSkillCFGEx* CShushanBattleMgr::GetBattleSkillCfg(UINT8 bySkillID)
{
    auto it = _mapID2BattleSkillCFG.find(bySkillID);
    if (it != _mapID2BattleSkillCFG.end())
        return &it->second;
    return NULL;
}

SBattleAwardCFGEx* CShushanBattleMgr::GetBattleAwardCfg(UINT8 byLevel)
{
    auto it = _mapID2BattleAwardCFG.find(byLevel);
    if (it != _mapID2BattleAwardCFG.end())
        return &it->second;
    return NULL;
}

SBattleExpCFGEx* CShushanBattleMgr::GetBattleExpCfg(UINT8 byLevel)
{
    auto it = _mapID2BattleExpCFG.find(byLevel);
    if (it != _mapID2BattleExpCFG.end())
        return &it->second;
    return NULL;
}

UINT8 CShushanBattleMgr::CalcHonorLevel(UINT16 wHonor)
{
    for (auto it = _mapID2BattleAwardCFG.begin(); it != _mapID2BattleAwardCFG.end(); ++ it)
    {
        if (wHonor < it->second._Honor)
            return it->first;
    }
    return _mapID2BattleAwardCFG.size();
}

void CShushanBattleMgr::GetBattleTaskCfg(TVecTaskData& vecTask_)
{
    //取普通任务2个  取中等任务2个  取困难任务1个
    vecTask_.clear();
    for (int idx = 0; idx < 3; ++ idx)
    {
        std::vector<TVecTaskData> vecTaskDataCFG = _vecBattleTaskCFG[idx];
        if (!vecTaskDataCFG.size())
            continue;
        int iMax = idx < 2 ? 2 : 1;
        for (int j = 0; j < iMax; ++ j)
        {
            UINT32 dwRand = CRandom::RandInt(0, vecTaskDataCFG.size()-1);
            TVecTaskData& vecTaskData = vecTaskDataCFG[dwRand];
            if (vecTaskData.size() > 1)
            {
                UINT32 dwTmp = CRandom::RandInt(0, vecTaskData.size()-1);
                vecTask_.push_back(vecTaskData[dwTmp]);
                vecTaskData.erase(vecTaskData.begin()+dwTmp);
            }
            else if (vecTaskData.size() == 1)
            {
                vecTask_.push_back(vecTaskData[0]);
                vecTaskDataCFG.erase(vecTaskDataCFG.begin()+dwRand);
            }
        }
    }
}


void CShushanBattleMgr::Prepare(UINT32 dwCurTime)
{
    int timeLeft = GetStartTime() - dwCurTime;
    timeLeft = timeLeft > 0 ? timeLeft : 0;
    string strPkg = g_ShushanBattleProtS.BuildPkg_BattleStartInfo(0, timeLeft);
    NetMgr.GetGateHandler()->SendClt(NULL, 0, &strPkg[0], (UINT32)strPkg.size());
}

void CShushanBattleMgr::Start(UINT32 dwCurTime)
{
    int timeLeft = GetEndedTime() - dwCurTime;
    timeLeft = timeLeft > 0 ? timeLeft : 0;
    string strPkg = g_ShushanBattleProtS.BuildPkg_BattleStartInfo(1, timeLeft);
    NetMgr.GetGateHandler()->SendClt(NULL, 0, &strPkg[0], (UINT32)strPkg.size());
}

void CShushanBattleMgr::CalcNext(UINT32 dwCurTime)
{
    if (!_bGMCheck)
    {
        _dwPrepareTime = Time::TheDay(0, dwCurTime) + 11 * 60 * 60 + 45 * 60;
        if (_dwPrepareTime + 45 * 60 < dwCurTime)
            _dwPrepareTime += 24 * 60 * 60;

        _dwStartTime = _dwPrepareTime + 15 * 60;
        _dwEndedTime = _dwStartTime + 30 * 60;
    }
    else
    {
        _dwPrepareTime = dwCurTime + 2*60;
        _dwStartTime = _dwPrepareTime + 2 * 60;
        _dwEndedTime = _dwStartTime + 30 * 60;
    }
}

void CShushanBattleMgr::BroadcastTV(UINT32 dwCurTime)
{
    if (dwCurTime >= _dwPrepareTime && !_byPrepareStep)
        _byPrepareStep = 1;

    string strPkg;
    switch (_byPrepareStep)
    {
    case 1:
        //广播     //15分钟
        _byPrepareStep = 2;
        Prepare(dwCurTime);
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgLunJianSignIn);
        ShushanBattle.Prepare();
        break;
    case 2:
        if (dwCurTime < _dwStartTime - 10 * 60) //10分钟
            return;
        strPkg = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgLunJianStart, BuildStrVec(10));
        _byPrepareStep = 3;
        break;
    case 3:
        if (dwCurTime < _dwStartTime - 5 * 60) //5分钟
            return;
        strPkg = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgLunJianStart, BuildStrVec(5));
        _byPrepareStep = 4;
        break;
    case 4:
        if (dwCurTime < _dwStartTime)
            return;
        //广播     //开始
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgLunJianBegin);
        _byPrepareStep = 5;
        Start(dwCurTime);
        break;
    default:
        return;
    }
    NetMgr.GetGateHandler()->SendClt(NULL, 0, &strPkg[0], (UINT32)strPkg.size());
}

void CShushanBattleMgr::End(UINT32 dwCurTime)
{
	_byPrepareStep = 0;
    CalcNext(dwCurTime);

    string strPkg = g_ShushanBattleProtS.BuildPkg_BattleStartInfo(2, GetPrepareTime() - dwCurTime);
    NetMgr.GetGateHandler()->SendClt(NULL, 0, &strPkg[0], (UINT32)strPkg.size());
}

bool CShushanBattleMgr::TimerCheck(UINT32 dwCurTime)
{
	if (_dwPrepareTime == 0)
		CalcNext(dwCurTime);
	if (dwCurTime < _dwPrepareTime)
		return false;
    BroadcastTV(dwCurTime);

    if (dwCurTime >= _dwStartTime)
        ShushanBattle.Process(dwCurTime);
	if (dwCurTime >= _dwEndedTime)
	{
		End(dwCurTime);
		return true;
	}
	return false;
}

void CShushanBattleMgr::SendBattleStatusInLogin(CPlayerPtr pPlayer)
{
    if (!pPlayer) return;
    UINT8 byStatus = 0xFF;
    UINT32 dwTimeLeft = 0;
    UINT32 dwCurTime = time(NULL);
    if (dwCurTime >= GetPrepareTime() && dwCurTime < GetStartTime())
    {
        byStatus   = 0;
        dwTimeLeft = GetStartTime() - dwCurTime;
    }
    else if (dwCurTime >= GetStartTime() && dwCurTime <= GetEndedTime())
    {
        byStatus   = 1;
        dwTimeLeft = GetEndedTime() - dwCurTime;
    }
    else
    {
        byStatus   = 2;
        dwTimeLeft = GetPrepareTime() - dwCurTime;
    }
    pPlayer->SendPkg(g_ShushanBattleProtS.BuildPkg_BattleStartInfo(byStatus, dwTimeLeft));

    if(IsRunning())
    {
        SSBPlayerDataPtr pPlayerData = ShushanBattle.FindSSBPlayerData(pPlayer->GetRoleID());
        if (pPlayerData && !pPlayerData->IsQuit())
            ShushanBattle.PlayerEnter(pPlayer);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

