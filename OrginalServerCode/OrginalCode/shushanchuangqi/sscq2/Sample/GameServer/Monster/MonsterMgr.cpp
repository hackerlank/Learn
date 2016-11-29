#include "stdafx.h"
#include "MonsterMgr.h"
#include "TaskConfMgr.h"
#include "FighterMgr.h"
#include "Tokenizer.h"
#include "WorldBoss.h"
#include "GUIDMgr.h"

map<UINT16, SAICFGEx> CMonsterMgr::_mapID2AICfg;
map<UINT64, CMonsterPtr> CMonsterMgr::_mapID2Monster;
map<UINT16, SMonsterGroupCFGEx> CMonsterMgr::_mapID2MonsterGroup;
map<UINT16, TMapTask2Drop> CMonsterMgr::_mapID2TaskDrop;
map<UINT16, SWorldBossCFGEx> CMonsterMgr::_mapWorldBoss;

bool CMonsterMgr::_bPrintLog = false;

bool CMonsterMgr::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/MonsterGroup.xml";
    CMonsterGroupLoader oMonsterGroupLoader;
    if(!oMonsterGroupLoader.LoadData(strPath))
    {
        LOG_CRI << "oMonsterGroupLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oMonsterGroupLoader._vecData.size(); ++i)
    {
        SMonsterGroupCFG* pMonsterGroupCFG = oMonsterGroupLoader._vecData[i];
        SMonsterGroupCFGEx stConfig(*pMonsterGroupCFG);
        buf::Tokenizer tkDrop(pMonsterGroupCFG->_strDropID,',');
        for(size_t i = 0; i < tkDrop.size() ;i++)
        {
            UINT32 dwDropID = atoi(tkDrop[i].c_str());
            stConfig.vecDropID.push_back(dwDropID);
        }
        buf::Tokenizer tkFighters(pMonsterGroupCFG->_strFighters, '|');
        TSetUINT8 setPos;
        for (size_t i = 0 ; i< tkFighters.size();++i)
        {
            string strFigter = tkFighters[i];
            buf::Tokenizer tkFighter(strFigter, ',');
            if(tkFighter.size() < 2)
            {
                LOG_CRI <<"Number:"<<i<< " :Fighters Need 2 Params GroupID :" << stConfig._ID;
                return false;
            }
            SMonsterGroupCFGEx::SFighterPos stFighterPos;
            stFighterPos.byPos = atoi(tkFighter[0].c_str());
            stFighterPos.wMonsterID = atoi(tkFighter[1].c_str());

            if (setPos.find(stFighterPos.byPos) != setPos.end())
            {
                LOG_CRI <<"Number:"<<i<< " :Fighters Pos Conflict :" << stConfig._ID;
                return false;
            }
            setPos.insert(stFighterPos.byPos);

            if(CFighterMgr::GetFighterPropCfg(stFighterPos.wMonsterID) == NULL)
            {
                LOG_CRI <<"Number:"<<i<< " :Fighter ID Err :"<<stFighterPos.wMonsterID<<" GroupID :" << stConfig._ID;
                return false;
            }
            stConfig.vecFighters.push_back(stFighterPos);
        }
        buf::Tokenizer tkMonsterClass(pMonsterGroupCFG->_MonsterClass, '|');
        for (size_t i = 0 ; i< tkMonsterClass.size();++i)
        {
            UINT16 wMonsterID = atoi(tkMonsterClass[i].c_str());
            if (wMonsterID)
                stConfig.vecMonsterID.push_back(wMonsterID);
        }
        buf::Tokenizer tkFighters2(pMonsterGroupCFG->_addNPC, '|');
        for (size_t i = 0 ; i< tkFighters2.size();++i)
        {
            string strFigter = tkFighters2[i];
            buf::Tokenizer tkFighter(strFigter, ',');
            if(tkFighter.size() < 2)
                break;
            SMonsterGroupCFGEx::SFighterPos stFighterPos;
            stFighterPos.byPos = atoi(tkFighter[0].c_str());
            stFighterPos.wMonsterID = atoi(tkFighter[1].c_str());
            if(CFighterMgr::GetFighterPropCfg(stFighterPos.wMonsterID) == NULL)
            {
                LOG_CRI <<"Number:"<<i<< " :Fighter ID Err :"<<stFighterPos.wMonsterID<<" GroupID :" << stConfig._ID;
                return false;
            }
            stConfig.vecAddFighters.push_back(stFighterPos);
        }

        buf::Tokenizer tkAddSkills(pMonsterGroupCFG->_AddSkill, '|');
        for (size_t i = 0; i < tkAddSkills.size(); ++i)
        {
            string strAddSkill = tkAddSkills[i];
            buf::Tokenizer tkSkill(strAddSkill, ',');
            if (tkSkill.size() < 3)
                break;
            SMonsterGroupCFGEx::SAddSkill stAddSkill;
            stAddSkill.wFighterID = atoi(tkSkill[0].c_str());
            stAddSkill.dwSkillID = atoi(tkSkill[1].c_str());
            stAddSkill.dwSkillLevel = atoi(tkSkill[2].c_str());
            stConfig.vecAddSkills.push_back(stAddSkill);
        }

        if(CFighterMgr::GetFighterPropCfg(pMonsterGroupCFG->_addPet))
            stConfig.wPetID = pMonsterGroupCFG->_addPet;
        else
            stConfig.wPetID = pMonsterGroupCFG->_addPet;

        if(stConfig.vecFighters.empty())
        {
            LOG_CRI << "Fighters empty GroupID :" << stConfig._ID;
            return false;

        }
        _mapID2MonsterGroup[pMonsterGroupCFG->_ID] = stConfig;
    }

    strPath = Config._strConfigDir + "Conf/Table/TaskDrop.xml";
    CTaskDropLoader oTaskDropLoader;
    if(!oTaskDropLoader.LoadData(strPath))
    {
        LOG_CRI << "oTaskDropLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    _mapID2TaskDrop.clear();
    for(size_t i = 0; i < oTaskDropLoader._vecData.size(); ++i)
    {
        STaskDropCFG* pTaskDropCFG = oTaskDropLoader._vecData[i];
        if(pTaskDropCFG->_ID != 0 && pTaskDropCFG->_TaskID != 0)
            _mapID2TaskDrop[pTaskDropCFG->_ID][pTaskDropCFG->_TaskID].push_back(*pTaskDropCFG);
    }
    strPath = Config._strConfigDir + "Conf/Table/AI.xml";
    CAILoader oAILoader;
    if(!oAILoader.LoadData(strPath))
    {
        LOG_CRI << "oAILoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oAILoader._vecData.size(); ++i)
    {
        SAICFG* pAICFG = oAILoader._vecData[i];
        if(pAICFG->_ID != 0)
        {
            SAICFGEx sCfg(*pAICFG);
            buf::Tokenizer tkSight(sCfg._SightRadius, ',');
            if(tkSight.size() != 2)
            {
                LOG_CRI << "oAILoader.LoadData fails! ID: " << pAICFG->_ID;
                return false;

            }

            sCfg.SightAngle = atoi(tkSight[0].c_str());
            sCfg.SightRadius =  atoi(tkSight[1].c_str());
            if(pAICFG->_Move > 2)
            {
                LOG_CRI <<"oAILoader.LoadData fails! ID: " <<pAICFG->_ID;
            }
            sCfg._eMoveType = static_cast<SAICFGEx::EMoveType>(pAICFG->_Move);
            _mapID2AICfg[pAICFG->_ID] = sCfg;
        }
    }
    strPath = Config._strConfigDir + "Conf/Table/WorldBoss.xml";
    CWorldBossLoader oWorldBossLoader;
    if(!oWorldBossLoader.LoadData(strPath))
    {
        LOG_CRI << "oWorldBossLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oWorldBossLoader._vecData.size(); ++i)
    {
        SWorldBossCFG* pCfg = oWorldBossLoader._vecData[i];
        SWorldBossCFGEx& rCfg = _mapWorldBoss[pCfg->_BossId];
        rCfg.SetConfig(*pCfg);
        {
            Tokenizer tk(rCfg._BossPosition, ",");
            if (tk.size() < 2)
                return false;
            rCfg.pos.fX = atoi(tk[0].c_str());
            rCfg.pos.fY = atoi(tk[1].c_str());
        }
        {
            Tokenizer tk(rCfg._BirthPlace, "|");
            if (tk.size() < 4)
                return false;

            for (size_t i = 0; i < tk.size(); ++i)
            {
                Tokenizer yatk(tk[i], ",");
                if (yatk.size() < 2)
                    return false;
                rCfg.vecBirthPlace.push_back(SPoint(atoi(yatk[0].c_str()), atoi(yatk[1].c_str())));
            }
        }
    }
    return true;
}

bool CMonsterMgr::LoadConfig(const string &strFile)
{
    string strPath;
    if("MonsterGroup.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/MonsterGroup.xml";
        CMonsterGroupLoader oMonsterGroupLoader;
        if(!oMonsterGroupLoader.LoadData(strPath))
        {
            LOG_CRI << "oMonsterGroupLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oMonsterGroupLoader._vecData.size(); ++i)
        {
            SMonsterGroupCFG* pMonsterGroupCFG = oMonsterGroupLoader._vecData[i];
            SMonsterGroupCFGEx stConfig(*pMonsterGroupCFG);
            buf::Tokenizer tkDrop(pMonsterGroupCFG->_strDropID,',');
            for(size_t i = 0; i < tkDrop.size() ;i++)
            {
                UINT32 dwDropID = atoi(tkDrop[i].c_str());
                stConfig.vecDropID.push_back(dwDropID);
            }
            buf::Tokenizer tkFighters(pMonsterGroupCFG->_strFighters, '|');
            TSetUINT8 setPos;
            for (size_t i = 0 ; i< tkFighters.size();++i)
            {
                string strFigter = tkFighters[i];
                buf::Tokenizer tkFighter(strFigter, ',');
                if(tkFighter.size() < 2)
                {
                    LOG_CRI <<"Number:"<<i<< " :Fighters Need 2 Params GroupID :" << stConfig._ID;
                    return false;
                }
                SMonsterGroupCFGEx::SFighterPos stFighterPos;
                stFighterPos.byPos = atoi(tkFighter[0].c_str());
                stFighterPos.wMonsterID = atoi(tkFighter[1].c_str());

                if (setPos.find(stFighterPos.byPos) != setPos.end())
                {
                    LOG_CRI <<"Number:"<<i<< " :Fighters Pos Conflict :" << stConfig._ID;
                    return false;
                }
                setPos.insert(stFighterPos.byPos);

                if(CFighterMgr::GetFighterPropCfg(stFighterPos.wMonsterID) == NULL)
                {
                    LOG_CRI <<"Number:"<<i<< " :Fighter ID Err :"<<stFighterPos.wMonsterID<<" GroupID :" << stConfig._ID;
                    return false;
                }
                stConfig.vecFighters.push_back(stFighterPos);
            }
            buf::Tokenizer tkMonsterClass(pMonsterGroupCFG->_MonsterClass, '|');
            for (size_t i = 0 ; i< tkMonsterClass.size();++i)
            {
                UINT16 wMonsterID = atoi(tkMonsterClass[i].c_str());
                if (wMonsterID)
                    stConfig.vecMonsterID.push_back(wMonsterID);
            }
            buf::Tokenizer tkFighters2(pMonsterGroupCFG->_addNPC, '|');
            for (size_t i = 0 ; i< tkFighters2.size();++i)
            {
                string strFigter = tkFighters2[i];
                buf::Tokenizer tkFighter(strFigter, ',');
                if(tkFighter.size() < 2)
                    break;
                SMonsterGroupCFGEx::SFighterPos stFighterPos;
                stFighterPos.byPos = atoi(tkFighter[0].c_str());
                stFighterPos.wMonsterID = atoi(tkFighter[1].c_str());
                if(CFighterMgr::GetFighterPropCfg(stFighterPos.wMonsterID) == NULL)
                {
                    LOG_CRI <<"Number:"<<i<< " :Fighter ID Err :"<<stFighterPos.wMonsterID<<" GroupID :" << stConfig._ID;
                    return false;
                }
                stConfig.vecAddFighters.push_back(stFighterPos);
            }

            buf::Tokenizer tkAddSkills(pMonsterGroupCFG->_AddSkill, '|');
            for (size_t i = 0; i < tkAddSkills.size(); ++i)
            {
                string strAddSkill = tkAddSkills[i];
                buf::Tokenizer tkSkill(strAddSkill, ',');
                if (tkSkill.size() < 3)
                    break;
                SMonsterGroupCFGEx::SAddSkill stAddSkill;
                stAddSkill.wFighterID = atoi(tkSkill[0].c_str());
                stAddSkill.dwSkillID = atoi(tkSkill[1].c_str());
                stAddSkill.dwSkillLevel = atoi(tkSkill[2].c_str());
                stConfig.vecAddSkills.push_back(stAddSkill);
            }

            if(stConfig.vecFighters.empty())
            {
                LOG_CRI << "Fighters empty GroupID :" << stConfig._ID;
                return false;
            }
            _mapID2MonsterGroup[pMonsterGroupCFG->_ID] = stConfig;
        }
    }else if("TaskDrop.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/TaskDrop.xml";
        CTaskDropLoader oTaskDropLoader;
        if(!oTaskDropLoader.LoadData(strPath))
        {
            LOG_CRI << "oTaskDropLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        _mapID2TaskDrop.clear();
        for(size_t i = 0; i < oTaskDropLoader._vecData.size(); ++i)
        {
            STaskDropCFG* pTaskDropCFG = oTaskDropLoader._vecData[i];
            if(pTaskDropCFG->_ID != 0 && pTaskDropCFG->_TaskID != 0)
                _mapID2TaskDrop[pTaskDropCFG->_ID][pTaskDropCFG->_TaskID].push_back(*pTaskDropCFG);
        }
    }else if("AI.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/AI.xml";
        CAILoader oAILoader;
        if(!oAILoader.LoadData(strPath))
        {
            LOG_CRI << "oAILoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oAILoader._vecData.size(); ++i)
        {
            SAICFG* pAICFG = oAILoader._vecData[i];
            if(pAICFG->_ID != 0)
            {
                SAICFGEx sCfg(*pAICFG);
                buf::Tokenizer tkSight(sCfg._SightRadius, ',');
                if(tkSight.size() != 2)
                {
                    LOG_CRI << "oAILoader.LoadData fails! ID: " << pAICFG->_ID;
                    return false;

                }

                sCfg.SightAngle = atoi(tkSight[0].c_str());
                sCfg.SightRadius =  atoi(tkSight[1].c_str());
                if(pAICFG->_Move > 2)
                {
                    LOG_CRI <<"oAILoader.LoadData fails! ID: " <<pAICFG->_ID;
                }
                sCfg._eMoveType = static_cast<SAICFGEx::EMoveType>(pAICFG->_Move);
                _mapID2AICfg[pAICFG->_ID] = sCfg;
            }
        }
    }else if("WorldBoss.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/WorldBoss.xml";
        CWorldBossLoader oWorldBossLoader;
        if(!oWorldBossLoader.LoadData(strPath))
        {
            LOG_CRI << "oWorldBossLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oWorldBossLoader._vecData.size(); ++i)
        {
            SWorldBossCFG* pCfg = oWorldBossLoader._vecData[i];
            SWorldBossCFGEx& rCfg = _mapWorldBoss[pCfg->_BossId];
            rCfg.SetConfig(*pCfg);
            {
                Tokenizer tk(rCfg._BossPosition, ",");
                if (tk.size() < 2)
                    return false;
                rCfg.pos.fX = atoi(tk[0].c_str());
                rCfg.pos.fY = atoi(tk[1].c_str());
            }
            {
                Tokenizer tk(rCfg._BirthPlace, "|");
                if (tk.size() < 4)
                    return false;

                for (size_t i = 0; i < tk.size(); ++i)
                {
                    Tokenizer yatk(tk[i], ",");
                    if (yatk.size() < 2)
                        return false;
                    rCfg.vecBirthPlace.push_back(SPoint(atoi(yatk[0].c_str()), atoi(yatk[1].c_str())));
                }
            }
        }
    }
    return true;

}

void CMonsterMgr::Destroy()
{
    _mapID2Monster.clear();
}

SAICFGEx* CMonsterMgr::GetAIConfig(UINT16 wAIID)
{
    auto it = _mapID2AICfg.find(wAIID);
    if(it != _mapID2AICfg.end())
        return &it->second;
    return NULL;
}

CMonsterPtr CMonsterMgr::CreateMonster(UINT16 wMonsterID,const string & strName)
{
    SFighterPropCFG* pFighterPropCFG = CFighterMgr::GetFighterPropCfg(wMonsterID);
    if(pFighterPropCFG == NULL)
        return NULL;
    CMonsterPtr pMonster;
    if(CFighterMgr::IsWorldBossFighter(*pFighterPropCFG)) // XXX: 或者还会有其他BOSS
        pMonster.reset(new CWorldBoss);
    else
        pMonster.reset(new CMonster);
    if(pMonster == NULL)
        return NULL;

    pMonster->SetLevel(pFighterPropCFG->_Level);
    pMonster->SetName(strName);
    pMonster->SetMonsterID(wMonsterID);
    pMonster->SetCreatureID(GET_GUID(GUID_MONSTER));
    PrintMonsterLog("Create RealMonster,", *pMonster);
    _mapID2Monster[pMonster->GetCreatureID()] = pMonster;

    return pMonster;
}

void CMonsterMgr::DestroyMonster(const CMonsterPtr& pMonster)
{
    assert(pMonster != NULL);
    CMonsterPtr pRealMonster = dynamic_pointer_cast<CMonster>(pMonster);
    if(pRealMonster != NULL)
        PrintMonsterLog("Destory RealMonster,", *pMonster);
    CMonsterAIPtr  pAI = pMonster->GetAI();
    if(pAI && pAI->GetMonsterState() != eMonsterDead)
    {
        pAI->SetMonsterState(eMonsterDead);
    }
    _mapID2Monster.erase(pMonster->GetCreatureID());
}

CMonsterPtr CMonsterMgr::GetMonster(UINT64 qwCreatureID)
{
    EGUIDType eType = CGUIDMgr::GetType(qwCreatureID);
    switch(eType)
    {
        case GUID_MONSTER:
            {
                auto it = _mapID2Monster.find(qwCreatureID);
                if(it != _mapID2Monster.end())
                    return it->second;
            }
            break;
        default:
            break;
    }
    return NULL;
}

const SMonsterGroupCFGEx* CMonsterMgr::GetMonsterGroup(UINT16 wGroupID)
{
    auto itrf = _mapID2MonsterGroup.find(wGroupID);
    if(itrf != _mapID2MonsterGroup.end())
        return &itrf->second;

    return NULL;
}

UINT16 CMonsterMgr::GetMonsterLevel(UINT16 wGroupID)
{
    const SMonsterGroupCFGEx* pGroup = GetMonsterGroup(wGroupID);
    if( NULL == pGroup )
        return 0;
    return pGroup->_wLevel;
}

TMapTask2Drop* CMonsterMgr::GetTaskDropMap(UINT32 dwMonsterIdx)
{
    auto it = _mapID2TaskDrop.find(dwMonsterIdx);
    if(it != _mapID2TaskDrop.end())
        return &it->second;
    return NULL;
}

void CMonsterMgr::PrintMonsterLog(const char* pMsg, CMonster& rMonster)
{
    if(_bPrintLog)
        LOG_DBG << pMsg << "Monster ID:" << rMonster.GetMonsterID() << "Creature ID:" << rMonster.GetCreatureID();
}

SWorldBossCFGEx* CMonsterMgr::GetWorldBossCfg(UINT16 wBossID)
{
    auto it = _mapWorldBoss.find(wBossID);
    if(it != _mapWorldBoss.end())
        return &it->second;
    return NULL;
}

