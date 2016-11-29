#include "ArenaManager.h"
#include "CenterConfig.h"
#include "tinyxml.h"
#include "Tokenizer.h"
#include "CenterGameVar.h"
#include "VarDefine.h"
#include <algorithm>
#include "Protocols.h"
#include "UserMgr.h"
#include "Parameter.h"
#include "LadderCFG.h"
#include "SysMsgDefine.h"
#include "VIPMgr.h"
#include "TimerPriceManager.h"
#include "Tokenizer.h"
#include "SystemMail.h"
using std::random_shuffle;
unordered_map<UINT64,SArenaPlayerData> CArenaManager::_mapAllPlayer;
map<EArenaLevel, CRankData> CArenaManager::_mapAllRank;
ArenaConfig  CArenaManager::_stConfig;
bool CArenaManager::_bLoadFromDB = false;
bool CArenaManager::_bInitCase = false;
UINT8 CArenaManager::_byLoadOver = 0; 
TVecArenaRank2Client CArenaManager::_vecWirship;
NArenaGS::TVecArenaPlayerData CArenaManager::_vecErr;
TVecUINT64 CArenaManager::_vecLadderRank;//前2000名玩家
map<UINT16,UINT32 > CArenaManager::_mapLadder;
map<UINT16,TVecUINT64> CArenaManager::_mapErrForLadder;
map<UINT16,vector<LadderRankAward> > CArenaManager::_mapLadderAward;

TVecLadderRobot CArenaManager::_vecRobot;
map<UINT16,UINT16> CArenaManager::_mapLadderRobotIDIDFirst;
map<UINT16,UINT16> CArenaManager::_mapLadderRobotIDRankFirst;
map<UINT64,UINT32> CArenaManager::_mapLadderEnemyLock;
UINT32 CArenaManager::LadderRankNoRank ;
UINT32 CArenaManager::LadderRankInit ;
void CArenaManager::InsertPlayer(const TVecArenaPlayerData& vecData)
{
    for(auto iter = vecData.begin();iter != vecData.end();iter++)
    {
        const SArenaPlayerData &rData = *iter;
        _mapAllPlayer[rData.qwRoleID] = rData;
        CRankData *pRank = GetRankData(rData.stBaseData.eLevel);
        if(NULL != pRank)//处理同排名
        {
            if(!pRank->InsertPlayerForDB(&rData))
            {
                _vecErr.push_back(rData);
                LOG_CRI <<"DB DATA ERR";
            }
        }
        //处理天梯
        if(rData.stBaseData.dwLadderRank < LadderRankNoRank )
        {
            _mapErrForLadder[rData.stBaseData.dwLadderRank-1].push_back(rData.qwRoleID);

        }
        if(EArenaLevel_DIAMOND == rData.stBaseData.eLastLevel && rData.stBaseData.dwLastRank <  _stConfig.stWorship.byShowworshipNum)
        {
            if( _vecWirship.size() < rData.stBaseData.dwLastRank+1)
            {
                _vecWirship.resize(rData.stBaseData.dwLastRank+1);
            }
            SArenaRank2Client& stSArenaRank = _vecWirship[rData.stBaseData.dwLastRank];
            stSArenaRank.qwRoleID = rData.qwRoleID;
            stSArenaRank.dwRank = rData.stBaseData.dwLastRank;
            stSArenaRank.dwScore =  rData.stBaseData.dwScore;
            stSArenaRank.stFighter = rData.stFighter;
            stSArenaRank.byQuality = rData.stBaseData.byQuality;
            stSArenaRank.byVIPLevel = rData.stBaseData.byVIPLevel;
            stSArenaRank.dwLadderRank = rData.stBaseData.dwLadderRank;
        }
    }
}


void CArenaManager::InsertErrPlayer()
{
    TSetUINT64 setUpdate;
    for(auto iter = _vecErr.begin();iter != _vecErr.end();iter++)
    {
        const SArenaPlayerData &rData = *iter;
        CRankData *pRank = GetRankData(rData.stBaseData.eLevel);
        if(NULL != pRank)
        {
            UINT32 dwRanking = pRank->InsertErrPlayerForDB(&rData);
            SArenaPlayerData * pPlayer = GetPlayer(rData.qwRoleID);
            if(NULL != pPlayer)
            {
                pPlayer->stBaseData.dwRanking = dwRanking;
            }
            else
            {
                LOG_CRI << "INFO NULL";
            }
            setUpdate.insert(rData.qwRoleID);
        }
    }
    if(_vecRobot.empty())//未合服初始化
    {
        LOG_CRI << "_vecRobot empty";
        if(_mapErrForLadder.empty())//未合服初始
        {
            TVecLadderRobot vecRobot;
            for(auto iter = _mapLadderRobotIDRankFirst.begin();iter != _mapLadderRobotIDRankFirst.end();iter++)
            {
                SLadderRobot sRobot;
                sRobot.wMonsterID = iter->second;
                sRobot.wRank = iter->first;
                vecRobot.push_back(sRobot);
                _vecLadderRank[iter->first -1] = iter->second;
                _mapLadderRobotIDIDFirst[sRobot.wMonsterID] = sRobot.wRank;
            }
            g_Center2DBCommC.Send_AddLadderRobot(vecRobot);
            LOG_CRI << "_vecLadderRank  size" <<_vecLadderRank.size();

        }
        else//合服初始化
        {
            UINT16 wBase = 0;
            UINT16 wPreRank = 0;
            bool bEnd = false;
            for(auto iter = _mapErrForLadder.begin();iter != _mapErrForLadder.end();iter++)
            {
                if(!bEnd)
                {
                    UINT16 wDiff = iter->first - wPreRank;
                    if(wBase <= wDiff -1)
                    {
                        wBase = 0;
                    }
                    else
                    {
                        wBase = wBase + 1 - wDiff;
                    }
                    wBase = iter->first - wPreRank;
                    TVecUINT64 &rvec = iter->second;
                    for(size_t pos = 0 ;pos != rvec.size();pos++)
                    {
                        SArenaPlayerData *pPlayer = GetPlayer(rvec[pos]);
                        if(!bEnd)
                        {
                            if(pos == 0)
                            {
                                if(wBase > 0 )
                                {
                                    setUpdate.insert(rvec[pos]);
                                }
                            }
                            else
                            {
                                wBase++;
                                setUpdate.insert(rvec[pos]);
                            }
                        }
                        else
                        {
                            setUpdate.insert(rvec[pos]);
                            if(pPlayer)
                                pPlayer->stBaseData.dwLadderRank = LadderRankNoRank;
                            continue;
                        }
                        UINT16 wCurrentRank = iter->first + wBase;

                        if( !bEnd && wCurrentRank >= SParamConfig::wSwordFightingLadderMaxPlayerNum)
                        {
                            bEnd = true;
                        }
                        if(bEnd)
                        {
                            if(pPlayer)
                                pPlayer->stBaseData.dwLadderRank = LadderRankNoRank;

                        }
                        else
                        {
                            if(pPlayer)
                                pPlayer->stBaseData.dwLadderRank = wCurrentRank + 1;
                            _vecLadderRank[wCurrentRank] = rvec[pos];
                        }

                    }
                    wPreRank = iter->first;
                }
                else
                {
                    TVecUINT64 &rvec = iter->second;
                    for(size_t pos = 0 ;pos != rvec.size();pos++)
                    {
                        setUpdate.insert(rvec[pos]);
                        SArenaPlayerData *pPlayer = GetPlayer(rvec[pos]);
                        if(pPlayer)
                            pPlayer->stBaseData.dwLadderRank = LadderRankNoRank;
                    }


                }
            }
            //剩余部分用机器人填
            TVecLadderRobot vecRobot;
            for(size_t iter = 0 ; iter != _vecLadderRank.size();iter++)
            {
                if(_vecLadderRank[iter] != 0)
                    continue;
                if(_mapLadderRobotIDRankFirst.find(iter+1) == _mapLadderRobotIDRankFirst.end())
                {
                    LOG_CRI << "Cannot find robot";
                    continue;

                }
                else
                {

                    _vecLadderRank[iter] = _mapLadderRobotIDRankFirst[iter+1];
                    SLadderRobot sRobot;
                    sRobot.wMonsterID = _vecLadderRank[iter];
                    sRobot.wRank = iter+1;
                    _mapLadderRobotIDIDFirst[sRobot.wMonsterID] = sRobot.wRank;
                    vecRobot.push_back(sRobot);
                }
            }
            if(!vecRobot.empty())
                g_Center2DBCommC.Send_AddLadderRobot(vecRobot);

        }

    }
    else 
    {

        if(_mapErrForLadder.empty())//开服无人登陆
        {
            for(auto iter = _vecRobot.begin();iter != _vecRobot.end();iter++)
            {
                SLadderRobot &sRobot = *iter;
                if(sRobot.wRank >= LadderRankNoRank)
                {
                    LOG_CRI << "ERR RNK;";
                    continue;
                }

                if(_vecLadderRank[sRobot.wRank-1] != 0)
                {
                    LOG_CRI << "ERR RNK;";
                    continue;
                }
                _vecLadderRank[sRobot.wRank-1] = sRobot.wMonsterID;
                _mapLadderRobotIDIDFirst[sRobot.wMonsterID] = sRobot.wRank;

            }

        }
        else//数据加载
        {
            for(auto iter = _vecRobot.begin();iter != _vecRobot.end();iter++)
            {

                SLadderRobot &sRobot = *iter;
                if(sRobot.wRank >= LadderRankNoRank)
                {
                    continue;
                }
                if(_vecLadderRank[sRobot.wRank-1] != 0)
                {
                    LOG_CRI << "ERR RNK;";
                    continue;
                }
                _vecLadderRank[sRobot.wRank-1] = sRobot.wMonsterID;
                _mapLadderRobotIDIDFirst[sRobot.wMonsterID] = sRobot.wRank;
            }
            for(auto iter =  _mapErrForLadder.begin();iter !=  _mapErrForLadder.end();iter++)
            {
                if(_vecLadderRank[iter->first] != 0)
                {
                    LOG_CRI << "ERR RNK;";
                    continue;
                }
                TVecUINT64 &rvec = iter->second;
                if(rvec.size() != 1)
                {
                    LOG_CRI << "ERR RNK;";
                    continue;

                }
                _vecLadderRank[iter->first] = rvec[0];
            }

        }
        //剩余部分用机器人填
        TVecLadderRobot vecRobot;
        TVecUINT16 vecFreeRank;
        for(size_t iter = 0 ; iter != _vecLadderRank.size();iter++)
        {
            if(_vecLadderRank[iter] != 0)
                continue;
             vecFreeRank.push_back(iter);
        }
        //对应位置已有排名处理
        if(!vecFreeRank.empty())
        {
            for(auto it = _mapLadderRobotIDRankFirst.begin();it != _mapLadderRobotIDRankFirst.end() && !vecFreeRank.empty();it++)
            {
                if(_mapLadderRobotIDIDFirst.find(it->second) != _mapLadderRobotIDIDFirst.end())
                {
                    continue;
                }
                UINT16 wRank = *(vecFreeRank.begin());
                _vecLadderRank[wRank] = it->second;
                SLadderRobot sRobot;
                sRobot.wMonsterID = it->second;
                sRobot.wRank = wRank + 1;
                _mapLadderRobotIDIDFirst[sRobot.wMonsterID] = sRobot.wRank;
                vecRobot.push_back(sRobot);
                vecFreeRank.erase(vecFreeRank.begin());
            }

        }
        if(!vecRobot.empty())
            g_Center2DBCommC.Send_AddLadderRobot(vecRobot);



    }
    UpadateBaseToDB(setUpdate);
    _vecErr.clear();
}
bool CArenaManager::ReloadTable(const string& strFile)
{
    if( "Arena.xml" == strFile)
    { 
        CArenaLoader _oArenaLoader;
        string strPath = Config._strConfigDir + "Conf/Table/Arena.xml";
        if(!_oArenaLoader.LoadData(strPath))
        {
            LOG_CRI << "_oArenaLoader fails! Path: " << strPath;
            return false;
        }
        std::vector<SArenaCFG*> &rVec = _oArenaLoader._vecData;
        for(auto iter =rVec.begin();iter != rVec.end();iter++)
        {
            SArenaCFG* pConfig = *iter;
            if(pConfig->_id <= EArenaLevel_NONE || pConfig->_id >= EArenaLevel_END)
            {
                LOG_CRI<<"_oArenaLoader Level fails!" << strPath; 
                return false;
            }
            EArenaLevel eLevel = static_cast<EArenaLevel>(pConfig->_id);
            CRankData * pRank = CArenaManager::GetRankData(eLevel);
            if(pRank ==NULL)
            {
                LOG_CRI<<"No Rank for Level" << strPath; 
                return false;
            }

        }
        for(auto iter =rVec.begin();iter != rVec.end();iter++)
        {
            SArenaCFG* pConfig = *iter;
            if(pConfig->_id <= EArenaLevel_NONE || pConfig->_id >= EArenaLevel_END)
            {
                LOG_CRI<<"_oArenaLoader Level fails!" << strPath; 
                return false;
            }
            EArenaLevel eLevel = static_cast<EArenaLevel>(pConfig->_id);
            CRankData * pRank = CArenaManager::GetRankData(eLevel);
            pRank->ResetConfig(pConfig);
        }
        return true;
    }
    else if("ArenaConfig.xml" == strFile)
    {
        string strConfigFile = Config._strConfigDir + "Conf/Misc/ArenaConfig.xml";
        if(!LoadArenaConfig(strConfigFile))
        {
            LOG_CRI <<"LoadArenaConfig Err path is " << strConfigFile;
            return false;
        }
        return true;

    }
    else if("Ladder.xml" == strFile)
    {
        CLadderLoader _oLoader; 
        string strPath = Config._strConfigDir + "Conf/Table/Ladder.xml";

        if(!_oLoader.LoadData(strPath))
        {
            LOG_CRI << "_oArenaLoader fails! Path: " << strPath;
            return false;
        }
        _mapLadder.clear();
        _mapLadderAward.clear();
        _mapLadderRobotIDRankFirst.clear();
        set<UINT16> setRobotMonster;
        if(_oLoader._vecData.size() != LadderRankNoRank)
        {
            LOG_CRI << "_oArenaLoader file size is not " << LadderRankNoRank;
            return false;

        }
        for(size_t it = 0; it != _oLoader._vecData.size();it++)
        {
            SLadderCFG &rConfig = *(_oLoader._vecData[it]);
            _mapLadder[rConfig._RankId] = rConfig._RankLootId;
            buf::Tokenizer tkAward(rConfig._RankHighestAward,'|');
            if(tkAward.size() != 0 )
            {
                for(size_t i = 0; i < tkAward.size() ;i++)
                {
                    buf::Tokenizer tkItem(tkAward[i],';');
                    if (tkItem.size() != 2)
                    {
                        LOG_CRI<< "ERR RankHighestAward";
                        return false;
                    }
                    LadderRankAward ItemAward;
                    ItemAward.wItemId = atoi(tkItem[0].c_str());
                    ItemAward.dwItenNum = atoi(tkItem[1].c_str());
                    if(ItemAward.wItemId == 0 || ItemAward.dwItenNum == 0)
                    {
                        LOG_CRI<< "ERR RankHighestAward";   
                        return false;
                    }

                    _mapLadderAward[rConfig._RankId].push_back(ItemAward);



                }
            }
            if(rConfig._RobotMonsterId == 0)
            {
                LOG_CRI<< "Zero _RobotMonsterId";
                return false;
            }
            if(setRobotMonster.find(rConfig._RobotMonsterId) != setRobotMonster.end())
            {
                LOG_CRI<< "Repeat _RobotMonsterId";
                return false;
            }
            setRobotMonster.insert(rConfig._RobotMonsterId);
            if(_mapLadderRobotIDRankFirst.find(rConfig._RankId) != _mapLadderRobotIDRankFirst.end())
            {
                LOG_CRI<< "Repeat RankId"; 
                return false;
            }
            if(rConfig._RankId < LadderRankNoRank)
            {
                _mapLadderRobotIDRankFirst[rConfig._RankId] = rConfig._RobotMonsterId;
            }


        }

        return true;
    }
    return false;
}
bool CArenaManager::Init()
{
    LadderRankNoRank = SParamConfig::wSwordFightingLadderMaxPlayerNum +1;
    LadderRankInit = SParamConfig::wSwordFightingLadderMaxPlayerNum + 4;
    CArenaLoader _oArenaLoader;
    string strPath = Config._strConfigDir + "Conf/Table/Arena.xml";
    if(!_oArenaLoader.LoadData(strPath))
    {
        LOG_CRI << "_oArenaLoader fails! Path: " << strPath;
        return false;
    }
    std::vector<SArenaCFG*> &rVec = _oArenaLoader._vecData;
    for(auto iter =rVec.begin();iter != rVec.end();iter++)
    {
        SArenaCFG* pConfig = *iter;
        if(pConfig->_id <= EArenaLevel_NONE || pConfig->_id >= EArenaLevel_END)
        {
            LOG_CRI<<"_oArenaLoader Level fails!" << strPath; 
            return false;
        }
        EArenaLevel eLevel = static_cast<EArenaLevel>(pConfig->_id);
        CRankData RankData(pConfig);
        _mapAllRank[eLevel]  = RankData;
    }
    string strConfigFile = Config._strConfigDir + "Conf/Misc/ArenaConfig.xml";
    if(!LoadArenaConfig(strConfigFile))
    {
        LOG_CRI <<"LoadArenaConfig Err path is " << strConfigFile;
        return false;
    }
    CLadderLoader _oLoader; 
    strPath = Config._strConfigDir + "Conf/Table/Ladder.xml";

    if(!_oLoader.LoadData(strPath))
    {
        LOG_CRI << "_oArenaLoader fails! Path: " << strPath;
        return false;
    }
    set<UINT16> setRobotMonster;
    if(_oLoader._vecData.size() != LadderRankNoRank)
    {
        LOG_CRI << "_oArenaLoader file size is not " << LadderRankNoRank;
        return false;

    }
    for(size_t it = 0; it != _oLoader._vecData.size();it++)
    {
        SLadderCFG &rConfig = *(_oLoader._vecData[it]);
        _mapLadder[rConfig._RankId] = rConfig._RankLootId;
        buf::Tokenizer tkAward(rConfig._RankHighestAward,'|');
        if(tkAward.size() != 0 )
        {
            for(size_t i = 0; i < tkAward.size() ;i++)
            {
                buf::Tokenizer tkItem(tkAward[i],';');
                if (tkItem.size() != 2)
                {
                    LOG_CRI<< "ERR RankHighestAward";
                    return false;
                }
                LadderRankAward ItemAward;
                ItemAward.wItemId = atoi(tkItem[0].c_str());
                ItemAward.dwItenNum = atoi(tkItem[1].c_str());
                if(ItemAward.wItemId == 0 || ItemAward.dwItenNum == 0)
                {
                    LOG_CRI<< "ERR RankHighestAward";   
                    return false;
                }
                _mapLadderAward[rConfig._RankId].push_back(ItemAward);



            }
        }
        if(rConfig._RobotMonsterId == 0)
        {
            LOG_CRI<< "Zero _RobotMonsterId";
            return false;
        }
        if (setRobotMonster.find(rConfig._RobotMonsterId) != setRobotMonster.end())
        {
            LOG_CRI<< "Repeat _RobotMonsterId";
            return false;
        }
        setRobotMonster.insert(rConfig._RobotMonsterId);
        if(_mapLadderRobotIDRankFirst.find(rConfig._RankId) != _mapLadderRobotIDRankFirst.end())
        {
            LOG_CRI<< "Repeat RankId"; 
            return false;
        }
        if(rConfig._RankId < LadderRankNoRank)
        {
            _mapLadderRobotIDRankFirst[rConfig._RankId] = rConfig._RobotMonsterId;
        }

    }
    _vecLadderRank.resize(SParamConfig::wSwordFightingLadderMaxPlayerNum,0);

    return true;
}


UINT32  CArenaManager::GetLadderAwardByRank(UINT32 dwLadderRank)
{
    auto iter =  _mapLadder.find(dwLadderRank);
    if(iter == _mapLadder.end())
    {
        return 0;
    }
    return iter->second;
}
SArenaPlayerData *CArenaManager::GetPlayer(UINT64 qwRoleID)
{
    auto iter = _mapAllPlayer.find(qwRoleID);
    if(iter == _mapAllPlayer.end())
    {
        return NULL;
    }
    return &(iter->second);
}

CRankData *CArenaManager::GetRankData(EArenaLevel eLevel)
{
    auto iter = _mapAllRank.find(eLevel);
    if(iter == _mapAllRank.end())
    {
        return NULL;
    }
    return &(iter->second);
}

bool CArenaManager::LoadArenaConfig(const string& strFile)
{
    TiXmlDocument doc;
    if(!doc.LoadFile(strFile.c_str()))
    {
        LOG_CRI << "LoadFile fails! File: " << strFile;
        return false;
    }
    TiXmlElement* pElemRoot = doc.RootElement();
    if(pElemRoot == NULL)
        return false;
    TiXmlElement* pElemCalTimer = pElemRoot->FirstChildElement("CalTimer");
    if(pElemCalTimer == NULL)
        return false;
    const char* pstr_CalTimer = pElemCalTimer->Attribute("val");

    if(NULL ==  pstr_CalTimer)
    {
        LOG_CRI << "Can Not find CalTimer";
        return false;
    }
    _stConfig.byCalTimer = atoi(pstr_CalTimer);
    //renaNum
    {
        TiXmlElement* pElemArena = pElemRoot->FirstChildElement("ArenaNum");
        if(pElemArena == NULL)
        {
            LOG_CRI << "can Not find ArenaNum";
            return false;
        }
        const char* pstr_freeVal = pElemArena->Attribute("freeVal");
        if(NULL ==  pstr_freeVal)
        {
            LOG_CRI << "Can find freeVal";
            return false;
        }
        _stConfig.stArenaNum.byFreeTimes = atoi(pstr_freeVal);
        const char* pstr_ExtraVal = pElemArena->Attribute("ExtraVal");
        if(NULL ==  pstr_ExtraVal)
        {
            LOG_CRI << "Can find ExtraVal";
            return false;
        }
        _stConfig.stArenaNum.byExtraTimes = atoi(pstr_ExtraVal);

        const char* pstr_ExtraVip = pElemArena->Attribute("ExtraVip");
        if(NULL ==  pstr_ExtraVip)
        {
            LOG_CRI << "Can find ExtraVip";
            return false;
        }
        _stConfig.stArenaNum.byExtraVip = atoi(pstr_ExtraVip);

        const char* pstr_Extracost = pElemArena->Attribute("Extracost");
        if(NULL ==  pstr_Extracost)
        {
            LOG_CRI << "Can find Extracost";
            return false;
        }
        _stConfig.stArenaNum.dwExtraCost = atoi(pstr_Extracost);

        const char* pstr_reflushtime = pElemArena->Attribute("reflushtime");
        if(NULL ==  pstr_reflushtime)
        {
            LOG_CRI << "Can find reflushtime";
            return false;
        }
        _stConfig.stArenaNum.byReflushTimer = atoi(pstr_reflushtime);

        const char* pstr_CDTimer = pElemArena->Attribute("CDTimer");
        if(NULL ==  pstr_CDTimer)
        {
            LOG_CRI << "Can find CDTimer";
            return false;
        }
        _stConfig.stArenaNum.dwCDTimer= atoi(pstr_CDTimer);

        const char* pstr_CLearCDCost = pElemArena->Attribute("CLearCDCost");
        if(NULL ==  pstr_CLearCDCost)
        {
            LOG_CRI << "Can find CLearCDCost";
            return false;
        }

        _stConfig.stArenaNum.dwClearCDCost = atoi(pstr_CLearCDCost);

        const char* pstr_DouJianWinResourse1Type = pElemArena->Attribute("DouJianWinResourse1Type");
        if(NULL ==  pstr_DouJianWinResourse1Type)
        {
            LOG_CRI << "Can find DouJianWinResourse1Type";
            return false;
        }
        _stConfig.stArenaNum.byWinLadderMoneyType1 = atoi(pstr_DouJianWinResourse1Type);
        const char* pstr_DouJianWinResourse1Value = pElemArena->Attribute("DouJianWinResourse1Value");
        if(NULL ==  pstr_DouJianWinResourse1Value)
        {
            LOG_CRI << "Can find DouJianWinResourse1Value";
            return false;
        }
        _stConfig.stArenaNum.dwWinLadderMoneyValue1 = atoi(pstr_DouJianWinResourse1Value);
        const char* pstr_DouJianWinResourse2Type = pElemArena->Attribute("DouJianWinResourse2Type");
        if(NULL ==  pstr_DouJianWinResourse2Type)
        {
            LOG_CRI << "Can find DouJianWinResourse2Type";
            return false;
        }
        _stConfig.stArenaNum.byWinLadderMoneyType2 = atoi(pstr_DouJianWinResourse2Type);
        const char* pstr_DouJianWinResourse2Value = pElemArena->Attribute("DouJianWinResourse2Value");
        if(NULL ==  pstr_DouJianWinResourse2Value)
        {
            LOG_CRI << "Can find DouJianWinResourse2Value";
            return false;
        }
        _stConfig.stArenaNum.dwWinLadderMoneyValue2 = atoi(pstr_DouJianWinResourse2Value);

        const char* pstr_DouJianFailResourse1Type = pElemArena->Attribute("DouJianFailResourse1Type");
        if(NULL ==  pstr_DouJianFailResourse1Type)
        {
            LOG_CRI << "Can find DouJianFailResourse1Type";
            return false;
        }
        _stConfig.stArenaNum.byFailLadderMoneyType1 = atoi(pstr_DouJianFailResourse1Type);
        const char* pstr_DouJianFailResourse1Value = pElemArena->Attribute("DouJianFailResourse1Value");
        if(NULL ==  pstr_DouJianFailResourse1Value)
        {
            LOG_CRI << "Can find DouJianFailResourse1Value";
            return false;
        }
        _stConfig.stArenaNum.dwFailLadderMoneyValue1 = atoi(pstr_DouJianFailResourse1Value);
        const char* pstr_DouJianFailResourse2Type = pElemArena->Attribute("DouJianFailResourse2Type");
        if(NULL ==  pstr_DouJianFailResourse2Type)
        {
            LOG_CRI << "Can find DouJianFailResourse2Type";
            return false;
        }
        _stConfig.stArenaNum.byFailLadderMoneyType2 = atoi(pstr_DouJianFailResourse2Type);
        const char* pstr_DouJianFailResourse2Value = pElemArena->Attribute("DouJianFailResourse2Value");
        if(NULL ==  pstr_DouJianFailResourse2Value)
        {
            LOG_CRI << "Can find DouJianFailResourse2Value";
            return false;
        }
        _stConfig.stArenaNum.dwFailLadderMoneyValue2 = atoi(pstr_DouJianFailResourse2Value);


    }
    //FlushChallenger
    {
        TiXmlElement* pElemChallenger = pElemRoot->FirstChildElement("FlushChallenger");
        if(pElemChallenger == NULL)
        {
            LOG_CRI << "can Not find FlushChallenger";
            return false;
        }
        const char* pstr_FlushChallengerTimer = pElemChallenger->Attribute("timer");
        if(NULL == pstr_FlushChallengerTimer)
        {
            LOG_CRI << "Can find timer";
            return false;
        }
        buf::Tokenizer FlushChallengerTimertk(pstr_FlushChallengerTimer, ',');
        if(FlushChallengerTimertk.size() == 0)
        {
            LOG_CRI << "FlushChallengerTimertk.empty()"; 
            return false; 
        }
        for (size_t i = 0 ; i < FlushChallengerTimertk.size();++i)
        {
            UINT8 byTimer = atoi(FlushChallengerTimertk[i].c_str());
            _stConfig.stFlushChallenger.vecFlushTimer.push_back(byTimer);

        }

        const char* pstr_FlushChallengerNumber = pElemChallenger->Attribute("Number");
        if(NULL == pstr_FlushChallengerNumber)
        {
            LOG_CRI << "Can find Number";
            return false;
        }
        buf::Tokenizer FlushChallengerNumbertk(pstr_FlushChallengerNumber, ',');
        if(FlushChallengerNumbertk.size() ==0)
        {
            LOG_CRI << "FlushChallengerNumbertk.empty()"; 
            return false; 
        }
        for (size_t i = 0 ; i < FlushChallengerNumbertk.size();++i)
        {
            UINT8 byNum = atoi(FlushChallengerNumbertk[i].c_str());
            _stConfig.stFlushChallenger.vecFlushLevel.push_back(byNum);

        }

        const char* pstr_FlushChallengerCost = pElemChallenger->Attribute("selfFlushCost");
        if(NULL ==  pstr_FlushChallengerCost)
        {
            LOG_CRI << "Can find selfFlushCost";
            return false;
        }
        _stConfig.stFlushChallenger.dwBaseFlushCost = atoi(pstr_FlushChallengerCost);
        const char* pstr_FlushChallengerAddCost = pElemChallenger->Attribute("selfFlushAddcost");
        if(NULL ==  pstr_FlushChallengerAddCost)
        {
            LOG_CRI << "Can find selfFlushCost";
            return false;
        }
        _stConfig.stFlushChallenger.dwAddFlushCost = atoi(pstr_FlushChallengerAddCost);
        const char* pstr_FlushChallengerReflushTimer = pElemChallenger->Attribute("reflushtime");
        if(NULL ==  pstr_FlushChallengerReflushTimer)
        {
            LOG_CRI << "Can find selfFlushCost";
            return false;
        }
        _stConfig.stFlushChallenger.byReflushTimer = atoi(pstr_FlushChallengerReflushTimer);
    }
    //Robot
    {
        //---
        TiXmlElement* pElemRobot = pElemRoot->FirstChildElement("Robot");
        if(pElemRobot == NULL)
        {
            LOG_CRI << "can Not find FlushRobot";
            return false;
        }
        const char* pstr_Robot = pElemRobot->Attribute("Range");
        if(NULL == pstr_Robot)
        {
            LOG_CRI << "Can find timer";
            return false;
        }
        buf::Tokenizer Robottk(pstr_Robot, ',');
        if(Robottk.size() < 5 )
        {
            LOG_CRI << "Robottk Need 5"; 
            return false; 
        }
        _stConfig.vecRobot.clear();
        for (size_t i = 0 ; i < Robottk.size();++i)
        {
            _stConfig.vecRobot.push_back(atoi(Robottk[i].c_str()));

        }
    }
    //worship
    {
        //--
        TiXmlElement* pElemworship = pElemRoot->FirstChildElement("worship");
        if(pElemworship == NULL)
        {
            LOG_CRI << "can Not find worship";
            return false;
        }
        const char* pstr_worshipmaxnum = pElemworship->Attribute("MaxNum");
        if(NULL ==  pstr_worshipmaxnum)
        {
            LOG_CRI << "Can find MaxNum";
            return false;
        }
        _stConfig.stWorship.byMaxNum = atoi(pstr_worshipmaxnum);

        const char* pstr_worshipShowworshipNum = pElemworship->Attribute("ShowworshipNum");
        if(NULL ==  pstr_worshipShowworshipNum)
        {
            LOG_CRI << "Can find ShowworshipNum";
            return false;
        }
        _stConfig.stWorship.byShowworshipNum = atoi(pstr_worshipShowworshipNum);
        const char* pstr_worshipLootId = pElemworship->Attribute("worshipId");
        if(NULL ==  pstr_worshipLootId)
        {
            LOG_CRI << "Can find worshipId";
            return false;
        }
        _stConfig.stWorship.dwLootId = atoi(pstr_worshipLootId);
        const char* pstr_worshipreflushtime = pElemworship->Attribute("reflushtime");
        if(NULL ==  pstr_worshipreflushtime)
        {
            LOG_CRI << "Can find reflushtime";
            return false;
        }
        _stConfig.stWorship.byReflushTimer = atoi(pstr_worshipreflushtime);
    }
    //DelCondition
    {
        //-
        TiXmlElement* pElemDelCondition = pElemRoot->FirstChildElement("DelCondition");
        if(pElemDelCondition == NULL)
        {
            LOG_CRI << "can Not find DelCondition";
            return false;
        }
        const char* pstr_DelConditionLevel = pElemDelCondition->Attribute("Level");
        if(NULL ==  pstr_DelConditionLevel)
        {
            LOG_CRI << "Can find Level";
            return false;
        }
        _stConfig.stDelCon.byDelLevel= atoi(pstr_DelConditionLevel);

        const char* pstr_DelConditionDays = pElemDelCondition->Attribute("Days");
        if(NULL ==  pstr_DelConditionDays)
        {
            LOG_CRI << "Can find Days";
            return false;
        }
        _stConfig.stDelCon.byDays= atoi(pstr_DelConditionDays);
    }
    return true;
}

void CArenaManager::LoadFromDB()
{
    if (_bLoadFromDB)
        return ;
    UINT32 dwsize =TAKE_ARRAY_LENGTH(SArenaPlayerData);
    g_Center2DBCommC.Send_GetAllArena(dwsize);
    _bLoadFromDB = true;
    return ;

}

void CArenaManager::DoInitCase()
{
    if(_bInitCase)
        return;
    if(_byLoadOver != 2)
        return;
    if(!g_CenterGameVar.IsLoad())
        return;
    _bInitCase = true;
    Config.SetInited(eDBInitArena);
    CalRank();
}

void CArenaManager::CalRank()
{  
    if(!_bInitCase)
    {
        return ;
    }
    if(g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena) != 0)
    {
        return ;
    }
    LOG_CRI << "Now Cal begin";
    //记录上次结算时间
    g_CenterGameVar.SetVar(NVarDefine::eSystemVarArena,time(NULL), _stConfig.byCalTimer*3600);
    for(auto iter = _mapAllPlayer.begin(); iter != _mapAllPlayer.end();iter++)
    {
        SArenaPlayerData *pPlayer = &(iter->second);
        pPlayer->stBaseData.dwLastLadderRank = pPlayer->stBaseData.dwLadderRank;
    }
    vector<UINT64> vecDel;  
//#ifdef CLOSEARENA 
//    UpAllDataToDB(vecDel); 
//    return;
//#endif
    ResetWirship();
    //各个段位计算自己的升降名额WW
    map<EArenaLevel,vector<UINT64> > rmapUpdate;
    UINT32 dwNow = time(NULL);
    set<UINT64> setSame;
    map<UINT64,EArenaLevel> mapOldLevel;
    for(auto iter = _mapAllRank.begin();iter != _mapAllRank.end();iter++)
    {
        iter->second.UpdateForCal(rmapUpdate,dwNow,setSame);
    }
    for(auto pos =rmapUpdate.begin();pos != rmapUpdate.end();pos ++)
    {
        if( pos->first == EArenaLevel_NONE )
        {
            vecDel = move(pos->second);
            for(auto it = vecDel.begin();it != vecDel.end();it++)
            {
                _mapAllPlayer.erase(*it);
            }
        }
        else
        {
            //乱序
            random_shuffle(pos->second.begin(),pos->second.end());
            //插入
            CRankData* pRank = GetRankData(pos->first);
            if(pRank != NULL)
            {
                pRank->InsertPlayerForCal(pos->second);
            }


        }
    }
    UpAllDataToDB(vecDel);
    for(size_t i = 0; i < vecDel.size() ;i++)
    {
        CUserPtr pUser = CUserMgr::GetUserByUserID(vecDel[i]);
        TVecINT32 vecParam;
        vecParam.push_back(0);

        if(!pUser || (pUser->GetState() != eUserInGame && pUser->GetState() != eUserReplace))
        {
            CUser::AddOffLineEvent(vecDel[i],eEventType_ExperienceSectionChanging,vecParam);
        }
        else
        {
            pUser->OnEvent(eEventType_ExperienceSectionChanging,vecParam);
        }
    }
    for(auto iter =_mapAllPlayer.begin();iter != _mapAllPlayer.end();iter++)
    {
        /*if(setSame.find(iter->first) == setSame.end())
          continue;
          */
        TVecINT32 vecParam;
        vecParam.push_back(iter->second.stBaseData.eLevel);

        CUserPtr pUser = CUserMgr::GetUserByUserID(iter->first);
        if(!pUser || (pUser->GetState() != eUserInGame && pUser->GetState() != eUserReplace))
        {
            CUser::AddOffLineEvent(iter->first,eEventType_ExperienceSectionChanging,vecParam);
        }
        else
        {
            pUser->OnEvent(eEventType_ExperienceSectionChanging,vecParam);
        }



    }

    LOG_CRI << "Now Cal End";
}

void CArenaManager::RecieveDBData(UINT32 dwCurPage,UINT32 dwTotalPage,const NArenaGS::TVecArenaPlayerData& vecSendData)
{

    InsertPlayer(vecSendData);
    if(dwCurPage == dwTotalPage)
    {
        _byLoadOver++;
    }
    if(_byLoadOver == 2 )
    {
        for(auto iter= _mapAllRank.begin();iter != _mapAllRank.end();iter++)
        {
            iter->second.SetPreNumAllForDB();
        }
        InsertErrPlayer();
        DoInitCase();
    }
}

void CArenaManager::UpAllDataToDB(const vector<UINT64> &rvecDel)
{
    //先发送删除
    UINT32 dwdelsize = TAKE_ARRAY_LENGTH(UINT64);
    for(size_t i = 0; i < rvecDel.size() ;)
    {
        auto iend = (i + dwdelsize) >= rvecDel.size() ? rvecDel.size():(i + dwdelsize);
        vector<UINT64> sDel(rvecDel.begin()+i ,rvecDel.begin() + iend);
        g_Center2DBCommC.Send_DelPlayerArena(sDel);
        i = iend;
    }

    g_Center2DBCommC.Send_DelPlayerArena(rvecDel);
    //发送更新
    UINT32 dwsize = TAKE_ARRAY_LENGTH(SArenaPlayerBaseDataUpdate);
    NArenaGS::TVecArenaPlayerBaseDataUpdate vecUpdate;
    for(auto iter =_mapAllPlayer.begin();iter != _mapAllPlayer.end();iter++)
    {
        SArenaPlayerBaseDataUpdate stUpdate;
        stUpdate.qwRoleID = iter->first;
        stUpdate.stBaseData = iter->second.stBaseData;
        vecUpdate.push_back(stUpdate);
        if(vecUpdate.size() == dwsize)
        {
            g_Center2DBCommC.Send_UpdateAllArena(vecUpdate);
            //发送
            vecUpdate.clear();
        }

    }
    if(!vecUpdate.empty())
    {
        g_Center2DBCommC.Send_UpdateAllArena(vecUpdate);
    }
}

void CArenaManager::UpdatePlayerDataToDB(UINT64 qwRoleID)
{
    NRoleInfoDefine::SRoleArenaInfo *pPlayerInfo = GetPlayerInfo(qwRoleID);
    if(pPlayerInfo == NULL)
    {
        return ;
    }
    string strData;
    COutArchive iar(strData);
    iar << *pPlayerInfo;
    g_Center2DBCommC.Send_RoleDataUpdate(qwRoleID, NRoleInfoDefine::eTypeArena, eOpUpdate, strData);
}

void CArenaManager::PlayerEnter(UINT64 qwRoleID,UINT32 dwCalTimer,CreateFun fun)
{
    SArenaPlayerData *pPlayer = GetPlayer(qwRoleID);
    if(pPlayer != NULL)
    {
        fun(pPlayer);
        return ;
    }
    g_Center2DBCommC.Send_GetArenaFighterByID(qwRoleID,[fun,qwRoleID,dwCalTimer](UINT8 byRet_,const NArenaGS::SArenaFighter& stFighter){
            if(byRet_!= 0)
            {
            fun(NULL);
            return;
            }
            SArenaPlayerData *pPlayer = GetPlayer(qwRoleID);
            if(pPlayer != NULL)
            {
            fun(pPlayer);
            return ;
            }
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            if(NULL == pUser)
            {
            LOG_CRI <<"Player NOT ONLINE";
            fun(NULL);
            return ;
            }
            SArenaPlayerData stNewPlayer;
            stNewPlayer.qwRoleID = qwRoleID;
            SArenaPlayerBaseData& stData= stNewPlayer.stBaseData;
            stData.dwScore = 0;
            stData.eLevel  = EArenaLevel_IRON; 
            //stData.dwSameDays = 0;
            stData.dwLastFlushTime = time(NULL);
            stData.dwLastRank = EArenaLevel_NONE;
            CCenterVar& rVar = pUser->GetCenterVar();
            if(rVar.GetVar(NVarDefine::ePlayerMinLadderRank) == 0)
            {
                rVar.SetVar(NVarDefine::ePlayerMinLadderRank,LadderRankInit);
            }
            if(rVar.GetVar(NVarDefine::ePlayerMinLadderRank) == LadderRankInit)
            {
                stData.dwLastLadderRank = LadderRankInit;
                stData.dwLadderRank = LadderRankInit;
            }
            else
            {
                stData.dwLastLadderRank = LadderRankNoRank;
                stData.dwLadderRank = LadderRankNoRank;
            }
            stData.eLastLevel = EArenaLevel_NONE;
            stData.dwFighterPower = pUser->GetFighterPower();
            stData.byQuality = pUser->GetQuality();
            stData.byVIPLevel = pUser->GetVIPLevel();
            CRankData *pRankData = GetRankData(EArenaLevel_IRON);
            if(pRankData == NULL)
            {
                LOG_CRI<<"Rank is NULL";
                return ;
            }
            stData.dwRanking = pRankData->NewPlayerEnter(qwRoleID);
            //fighter
            SArenaFighter& stFighter_ = stNewPlayer.stFighter;
            stFighter_   = stFighter;
            _mapAllPlayer[qwRoleID] = stNewPlayer;
            UpadateBaseToDB(qwRoleID);
            TVecINT32 vecParam;
            vecParam.push_back(EArenaLevel_IRON);
            pUser->OnEvent(eEventType_ExperienceSectionChanging,vecParam);

            //处理自己的信息
            NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
            bool bAdd = true;
            if(!rSelfInfo.empty())//删除原来的信息
            {
                bAdd = false;
                rSelfInfo.clear();
            }
            NRoleInfoDefine::SRoleArenaInfo stPlayerInfo;
            stPlayerInfo.dwCDTime = 0;
            stPlayerInfo.dwLadderCDTime = 0;
            //奖励已刷vecFlushFigter
            stPlayerInfo.dwLastAwardTimer =   dwCalTimer;  
            //刷对手：5个机器人
            TVecFlushFither &rVecFigther = stPlayerInfo.vecFlushFigter;
            //得到机器人库
            vector<UINT16> tepVec =  _stConfig.vecRobot;
            for(int i = 0 ; i< 5 && !tepVec.empty(); i++)
            {
                SFlushFighter stFighter;
                stFighter.bySuc = 0;
                UINT32 dwPos = rand()%tepVec.size();
                stFighter.qwFighterID = tepVec[dwPos];
                rVecFigther.push_back(stFighter);
                tepVec.erase(tepVec.begin()+dwPos);
            }
            //设置变量
            ResetFlushChallengerVar(pUser->GetCenterVar());
            //同步玩家数据库
            string strData;
            COutArchive iar(strData);
            iar << stPlayerInfo;
            NProtoCommon::EDataChange eUpdateType= eOpAdd;
            if(!bAdd)
            {
                eUpdateType = eOpUpdate;
            }
            g_Center2DBCommC.Send_RoleDataUpdate(qwRoleID, NRoleInfoDefine::eTypeArena, eUpdateType, strData);
            rSelfInfo.push_back(stPlayerInfo);
            pPlayer = GetPlayer(qwRoleID);
            fun(pPlayer);
    });

}

bool CArenaManager::GetFlushChallengerVar(CCenterVar& rVar)
{
    return rVar.GetVar(NVarDefine::ePlayerVarArenaChallenge0) == 0
        ||rVar.GetVar(NVarDefine::ePlayerVarArenaChallenge12) == 0
        ||rVar.GetVar(NVarDefine::ePlayerVarArenaChallenge18) == 0;
}

void CArenaManager::ResetFlushChallengerVar(CCenterVar& rVar)
{
    for(size_t pos = 0;pos != _stConfig.stFlushChallenger.vecFlushTimer.size();pos++)
    {
        UINT8 byHour = _stConfig.stFlushChallenger.vecFlushTimer[pos];
        UINT32 dwDelay = byHour*3600;
        switch(pos)
        {
            case 0:
                {
                    if(rVar.GetVar(NVarDefine::ePlayerVarArenaChallenge0) ==0)
                    {
                        rVar.SetVar(NVarDefine::ePlayerVarArenaChallenge0,1,dwDelay);
                    }
                }
                break;
            case 1:
                {
                    if(rVar.GetVar(NVarDefine::ePlayerVarArenaChallenge12)==0)
                    {

                        rVar.SetVar(NVarDefine::ePlayerVarArenaChallenge12,1, dwDelay);
                    }
                }
                break;
            case 2:
                {
                    if(rVar.GetVar(NVarDefine::ePlayerVarArenaChallenge18)==0)

                    {
                        rVar.SetVar(NVarDefine::ePlayerVarArenaChallenge18,1, dwDelay);
                    }
                }
                break;
        }
    }

}
void  CArenaManager::GetAward(EArenaLevel eCurLevel,UINT32 dwLastLadderRank,EArenaLevel eLastLevel,UINT32 dwLastRank,TVecArenaAward &vecAwards)
{
    //本段位包
    UINT32 dwLoot = 0;
    CRankData* pRank = GetRankData(eCurLevel);
    if(pRank != NULL)
    {
        dwLoot = pRank->GetLevelAward();
    }
    if(dwLoot > 0 )
    {
        NArenaGS::SArenaAward stAward;
        stAward.byDraw =0 ;
        stAward.dwDrawID = dwLoot;
        stAward.eType = Type_Level;
        vecAwards.push_back(stAward);
    }
    //本段位保级包
    /*
       dwLoot = 0;
       if(pRank != NULL)
       {
       dwLoot = pRank->GetSameDaysAward(dwSameDays);
       }
       if(dwLoot > 0 )
       {
       NArenaGS::SArenaAward stAward;
       stAward.byDraw =0 ;
       stAward.eType = Type_Keep;
       stAward.dwDrawID = dwLoot;
       vecAwards.push_back(stAward);
       }
       */
    //天梯奖励包
    dwLoot = GetLadderAwardByRank(dwLastLadderRank);
    if(dwLoot > 0 )
    {
        NArenaGS::SArenaAward stAward;
        stAward.byDraw =0 ;
        stAward.eType = Type_LadderRank;
        stAward.dwDrawID = dwLoot;
        vecAwards.push_back(stAward);
    }

    //前段位排名包
    dwLoot = 0;
    pRank = GetRankData(eLastLevel);
    if(pRank != NULL)
    {
        dwLoot = pRank->GetRankAward(dwLastRank);
    }
    if(dwLoot > 0 )
    {
        NArenaGS::SArenaAward stAward;
        stAward.byDraw =0 ;
        stAward.dwDrawID = dwLoot;
        stAward.eType = Type_Rank;
        vecAwards.push_back(stAward);
    }
}

bool CArenaManager::CheckAward(NRoleInfoDefine::SRoleArenaInfo &rInfo,SArenaPlayerData *pPlayer,UINT32 dwCalTimer)
{
    if( dwCalTimer == rInfo.dwLastAwardTimer)
    {
        return false;
    }
    rInfo.dwLastAwardTimer =   dwCalTimer;  
    rInfo.vecAwards.clear();
    //根据最近结算掉落包
    GetAward(pPlayer->stBaseData.eLevel,pPlayer->stBaseData.dwLastLadderRank,pPlayer->stBaseData.eLastLevel,pPlayer->stBaseData.dwLastRank,rInfo.vecAwards);
    return true;
}
void CArenaManager::PlayerGetInfo(UINT64 qwRoleID,UINT32 dwCalTimer,FunInfo fun)
{


    PlayerEnter(qwRoleID,dwCalTimer,[qwRoleID,dwCalTimer,fun](SArenaPlayerData *pPlayer){
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            if(NULL == pUser)
            {
            LOG_CRI <<"Player NOT ONLINE";
            fun(NULL);
            return ;
            }
            if(NULL == pPlayer)
            {
            LOG_CRI<<"Player Is NULL";
            fun(NULL);
            return ;
            }
            Data2ClientPtr pClient(new SArenaPlayerBaseData2Client);
            if(pClient ==NULL)
            {
            LOG_CRI<<"New Is NULL";
            fun(NULL);
            return ;
            }
            SArenaPlayerBaseData2Client&  stReturn = *pClient;
            CRankData* pData = GetRankData(pPlayer->stBaseData.eLevel);
            if(NULL != pData)
            {
                stReturn.dwRanking = pData->GetPreNumByScore(pPlayer->stBaseData.dwScore)+pPlayer->stBaseData.dwRanking;
            }
            else
            {
                LOG_CRI<<"Can no t find Rank";
                fun(NULL);
                return ;

            }
            //基本信息
            stReturn.dwScore = pPlayer->stBaseData.dwScore;
            stReturn.eLevel = pPlayer->stBaseData.eLevel;
            /*
               stReturn.dwSameDays = pPlayer->stBaseData.dwSameDays;
               */
            CCenterVar& rVar = pUser->GetCenterVar();
            stReturn.wChallenge = rVar.GetVar(NVarDefine::ePlayerVarArenaChallengeFree);
            stReturn.wChallengeBuyTimes = rVar.GetVar(NVarDefine::ePlayerVarBuyArenaChallengeTimes);
            stReturn.ePreLevel= pPlayer->stBaseData.eLastLevel;
            stReturn.dwPreRank = pPlayer->stBaseData.dwLastRank;
            stReturn.dwTotalSize = pData->GetPlayerSize();
            stReturn.dwLadderRank = pPlayer->stBaseData.dwLadderRank;
            stReturn.wSelfReflush = rVar.GetVar(NVarDefine::ePlayerVarArenaChallengeFlush);
            stReturn.wSelfFreeReflush = rVar.GetVar(NVarDefine::ePlayerVarArenaChallengeFreeFlush);
            stReturn.byArenaWirship =rVar.GetVar(NVarDefine::ePlayerVarArenaWirship);
            stReturn.dwFighterPower  = pPlayer->stBaseData.dwFighterPower;
            stReturn.dwArenaAward = rVar.GetVar(NVarDefine::ePlayerVarChallegeAward);
            stReturn.wLadderChallenge = rVar.GetVar(NVarDefine::ePlayerVarLadderChallenge);
            stReturn.dwLastLadderRank = pPlayer->stBaseData.dwLastLadderRank; //上次结算天梯排名，0表示排名
            stReturn.dwMinLadderRank = rVar.GetVar(NVarDefine::ePlayerMinLadderRank); //天梯最好排名,0表示无排名

            stReturn.dwLadderBuyTimes = rVar.GetVar(NVarDefine::ePlayerVarBuyLadderTimes);
            stReturn.dwLadderBuyTimesToday = rVar.GetVar(NVarDefine::ePlayerVarBuyLadderTimesToday);

            //奖励包
            NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
            if(rSelfInfo.empty())
            {
                LOG_CRI <<"NO SELF INFO";
                fun(NULL);
                return ;
            }
            NRoleInfoDefine::SRoleArenaInfo &rInfo = rSelfInfo[0];
            stReturn.dwArenaCDTime = rInfo.dwCDTime;
            stReturn.dwLadderCDTime = rInfo.dwLadderCDTime;
            bool bUpdate = CheckAward(rInfo,pPlayer,dwCalTimer);
            stReturn.vecAwards = rInfo.vecAwards;
            //Top3
            TVecArenaRank2Client &rVecTop = stReturn.vecWirshipFigter;
            rVecTop = GetWirship();
            //先将对手刷出来
            if(CheckFlush(qwRoleID) || bUpdate)
            {
                CArenaManager::UpdatePlayerDataToDB(qwRoleID);
            }
            GetFlushClient(qwRoleID,[pClient,fun,qwRoleID](FlushClientVecPtr vecPtr)
                    {
                    pClient->vecFlushFigter = *vecPtr;
                    fun(pClient);
                    });


    });
}

UINT32 CArenaManager::GetPlayerSizeByRank(EArenaLevel eLevel)
{
    CRankData* pData = GetRankData(eLevel);
    if(NULL != pData)
    {
        return pData->GetPlayerSize(); 
    }
    return 0;
}

void CArenaManager::GetPlayerListByRank(TVecArenaRank2Client &rVec,EArenaLevel eLevel,UINT32 dwFrom,UINT8 byNum)
{
    CRankData* pRank = GetRankData(eLevel);
    if(pRank == NULL)
    {
        return ;
    }
    TVecUINT64 vecPlayer;
    pRank->GetPlayerListByRank(vecPlayer,dwFrom,byNum);
    for(size_t iter = 0;iter != vecPlayer.size();iter++)
    {
        UINT64 qwRoleID = vecPlayer[iter];
        SArenaRank2Client stSArenaRank;
        if(!GetRankClient(qwRoleID,stSArenaRank,dwFrom + iter,false))
        {
            continue;
        }

        rVec.push_back(stSArenaRank);
    }

}
UINT16  CArenaManager::GetRobotRankById(UINT16 wMonsterId)
{
    if( _mapLadderRobotIDIDFirst.find(wMonsterId) == _mapLadderRobotIDIDFirst.end())
    {
        return 0;
    }
    return _mapLadderRobotIDIDFirst[wMonsterId];

}
bool  CArenaManager::GetRankClient(UINT64 qwRoleID,SArenaRank2Client &stSArenaRank,UINT32 dwRank,bool bforLadder )
{
    SArenaPlayerData * pPlayer = GetPlayer(qwRoleID);

    if(pPlayer == NULL) // 机器人数据
    {
        if(!IsRobot(qwRoleID,bforLadder))
        {
            return false;
        }
        stSArenaRank.qwRoleID = qwRoleID;
        stSArenaRank.dwRank =  dwRank;
    }
    else // 真实玩家数据
    {
        stSArenaRank.qwRoleID = qwRoleID;
        stSArenaRank.dwRank = dwRank;
        stSArenaRank.dwScore = pPlayer->stBaseData.dwScore;
        stSArenaRank.stFighter = pPlayer->stFighter;
        stSArenaRank.dwFighterPower = pPlayer->stBaseData.dwFighterPower;
        stSArenaRank.byQuality = pPlayer->stBaseData.byQuality;
        stSArenaRank.byVIPLevel = pPlayer->stBaseData.byVIPLevel;
        stSArenaRank.dwLadderRank = pPlayer->stBaseData.dwLadderRank;
    }
    return true;

}

void CArenaManager::UpadateBaseToDB(UINT64 qwRoleID)
{
    SArenaPlayerData *pPlayer = GetPlayer(qwRoleID);
    if(NULL == pPlayer)
    {
        return ;
    }
    NArenaGS::TVecArenaPlayerBaseDataUpdate vecUpdate;
    SArenaPlayerBaseDataUpdate stUpdate;
    stUpdate.qwRoleID = qwRoleID;
    stUpdate.stBaseData = pPlayer->stBaseData;
    vecUpdate.push_back(stUpdate);
    g_Center2DBCommC.Send_UpdateAllArena(vecUpdate);

}

void CArenaManager::UpadateBaseToDB(const TSetUINT64& setRoleID)
{
    //for  Debug
#ifdef  _DEBUG
    for( auto it = setRoleID.begin(); it != setRoleID.end(); ++it)
    {
        SArenaPlayerData *pPlayer = GetPlayer(*it);
        if(NULL == pPlayer)
        {
            LOG_CRI << "NOPLayer";
            continue ;
        }
        CRankData* pRank = GetRankData(pPlayer->stBaseData.eLevel);
        if(pRank == NULL)
        {
            LOG_CRI << "NO RANK";
            continue;
        }
        if(!pRank->CheckPlayer(pPlayer))
        {
            LOG_CRI << "Data EER";
        }
    }
#endif
    UINT32 dwsize = TAKE_ARRAY_LENGTH(SArenaPlayerBaseDataUpdate); 
    NArenaGS::TVecArenaPlayerBaseDataUpdate vecUpdate;
    for (auto iter = setRoleID.begin();iter != setRoleID.end();iter++)
    {
        UINT64 qwRoleID = *iter;
        SArenaPlayerData *pPlayer = GetPlayer(qwRoleID);
        if(NULL == pPlayer)
        {
            continue ;
        }
        SArenaPlayerBaseDataUpdate stUpdate;
        stUpdate.qwRoleID = qwRoleID;
        stUpdate.stBaseData = pPlayer->stBaseData;
        vecUpdate.push_back(stUpdate);
        if(vecUpdate.size() > dwsize)
        {
            g_Center2DBCommC.Send_UpdateAllArena(vecUpdate);
            vecUpdate.clear();
        }
    }
    if(!vecUpdate.empty())
    {
        g_Center2DBCommC.Send_UpdateAllArena(vecUpdate);
    }
}

//对手

//刷对手，如果有更新返回true,否则返回false,更新的数据放到Player身上
bool CArenaManager::CheckFlush(UINT64 qwRoleID)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        LOG_CRI <<"Player NOT ONLINE";
        return false;
    }

    CCenterVar& rVar = pUser->GetCenterVar();
    if(!GetFlushChallengerVar(rVar))
    {
        return false;
    }
    //刷将
    ResetFlushChallengerVar(rVar);
    //如果5个都是机器人，那么不刷将
    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        LOG_CRI <<"NO SELF INFO";
        return false;
    }
    //原来的将全部是机器人，不刷将
    NRoleInfoDefine::SRoleArenaInfo &rInfo = rSelfInfo[0];
    bool bAllRobot = true;
    for(auto iter= rInfo.vecFlushFigter.begin();iter != rInfo.vecFlushFigter.end();iter++)
    {
        SFlushFighter &rFighter = *iter;
        if(!IsRobot(rFighter.qwFighterID,false))
        {
            bAllRobot = false;
            break;
        }
    }
    if(bAllRobot)
    {
        return false;

    }
    //否则刷将
    DoFlush(qwRoleID);
    return true;
}

void CArenaManager::DoFlushSel(UINT64 qwRoleID,TVecUINT64 &vecSel)
{   
    SArenaPlayerData *pPlayer = GetPlayer(qwRoleID);
    if(NULL == pPlayer)
    {
        LOG_CRI<<"Player Is NULL";
        return ;
    }
    const TVecUINT8 &rvecNum =_stConfig.stFlushChallenger.vecFlushLevel;
    EArenaLevel eUperLevel = (EArenaLevel)(pPlayer->stBaseData.eLevel+1);
    CRankData* pUperRank = GetRankData(eUperLevel);
    bool bUperAdd = false;
    if(pUperRank == NULL)
    {
        bUperAdd = true;     
    }
    else
    {
        pUperRank->FindRandom(vecSel,0,rvecNum[1]);
    }

    EArenaLevel eLowLevel = (EArenaLevel)(pPlayer->stBaseData.eLevel-1);
    CRankData* pLowRank = GetRankData(eLowLevel);
    bool bLowAdd = false;
    if(pLowRank == NULL)
    {
        bLowAdd = true;     
    }
    else
    {
        pLowRank->FindRandom(vecSel,0,rvecNum[2]);
    }

    CRankData* pRank = GetRankData(pPlayer->stBaseData.eLevel); 
    if(pRank == NULL)
    {
        LOG_CRI<<"pRank Is NULL";
        return ;
    }
    UINT8 byNum = rvecNum[0];
    if(bUperAdd)
    {
        byNum += rvecNum[1];
    }
    if(bLowAdd)
    {
        byNum += rvecNum[2];
    }
    pRank->FindRandom(vecSel,qwRoleID,byNum);
    if(vecSel.size() == 5)
    {
        return ;
    }
    //全局查找，所有斗剑玩家
    set<UINT64> setExp(vecSel.begin(),vecSel.end());
    setExp.insert(qwRoleID);
    GetRandRomPlayer(vecSel,setExp);
    if(vecSel.size() == 5)
    {
        return ;
    }
    //如果还找不到，机器人填
    vector<UINT16> tepVec =  _stConfig.vecRobot;
    for(;vecSel.size() != 5 && !tepVec.empty();)
    {
        UINT32 Pos = rand()%tepVec.size();
        vecSel.push_back(tepVec[Pos]);
        tepVec.erase(tepVec.begin()+Pos);
    }

}

void CArenaManager::GetRandRomPlayer(TVecUINT64 &vecSel,const set<UINT64> &setExp)
{
    UINT32 dwCount = _mapAllPlayer.size();
    if(dwCount <= setExp.size())
    {
        return ;
    }
    TVecUINT64 vecSource;
    for(auto iter = _mapAllPlayer.begin();iter != _mapAllPlayer.end();iter++)
    {
        if(setExp.find(iter->first) == setExp.end())
        {
            vecSource.push_back(iter->first);
        }
        if(vecSource.size() > 1000)
        {
            break;
        }

    }
    while(!vecSource.empty() &&  vecSel.size() < 5 ) 
    {
        auto pos = rand()%vecSource.size();
        vecSel.push_back(vecSource[pos]);
        vecSource.erase(vecSource.begin()+pos);
    }

}


void CArenaManager::DoFlush(UINT64 qwRoleID)
{

    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        LOG_CRI <<"Player NOT ONLINE";
        return ;
    }
    TVecUINT64 vecSel;
    DoFlushSel(qwRoleID,vecSel);
    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        LOG_CRI <<"NO SELF INFO";
        return ;
    }
    NRoleInfoDefine::SRoleArenaInfo &rInfo = rSelfInfo[0];
    rInfo.vecFlushFigter.clear();
    for(size_t i = 0; i != vecSel.size();i++)
    {
        SFlushFighter stFighter;
        stFighter.bySuc = 0;
        stFighter.qwFighterID = vecSel[i];
        rInfo.vecFlushFigter.push_back(stFighter);
    }
}

//根据玩家数据完善展示数据
void CArenaManager::GetFlushClient(UINT64 qwRoleID,FunFlushClientInfo fun)
{
    NRoleInfoDefine::SRoleArenaInfo *pPlayerInfo = GetPlayerInfo(qwRoleID);
    if(pPlayerInfo ==NULL)
    {
        LOG_CRI <<"NO SELF INFO";
        fun(NULL);
        return ;
    }
    NRoleInfoDefine::SRoleArenaInfo &rInfo = *pPlayerInfo;
    FlushClientVecPtr pClient(new TVecSFlushFitherForClient);
    if(pClient == NULL)
    {
        LOG_CRI <<"New Err";
        fun(NULL);
        return ;
    }
    UINT8 bySize =rInfo.vecFlushFigter.size();
    for(auto i = 0; i != bySize;i++)
    {
        SFlushFighter &stFighter = rInfo.vecFlushFigter[i];
        SFlushFitherForClient stForClient;
        if(GetFlushFitherByID(stFighter.qwFighterID,stForClient,false,stFighter.bySuc))
        {
            pClient->push_back(stForClient);
        }
    }
    fun(pClient);
    return ;

}

void CArenaManager::UpdatePlayerLevel(UINT64 qwRoleID,UINT8 byLevel)
{
    SArenaPlayerData *pPlayer = GetPlayer(qwRoleID);
    if(pPlayer != NULL)
    {
        pPlayer->stFighter.wLevel = byLevel;
    }
}

void CArenaManager::UpdatePlayerQuality(UINT64 qwRoleID, UINT8 byQuality)
{
    SArenaPlayerData *pPlayer = GetPlayer(qwRoleID);
    if(pPlayer != NULL)
    {
        pPlayer->stBaseData.byQuality = byQuality;
    }
}

void CArenaManager::UpdatePlayerVIPLevel(UINT64 qwRoleID, UINT8 byVIPLevel)
{
    SArenaPlayerData *pPlayer = GetPlayer(qwRoleID);
    if(pPlayer != NULL)
    {
        pPlayer->stBaseData.byVIPLevel = byVIPLevel;
    }
}
void  CArenaManager::DoBuyLadderTimes(SArenaPlayerData *pPlayer,shared_func<CArenaGSSvr::SArenaBuyLadderTimesAck>& fnAck)
{
    UINT64 qwRoleID = pPlayer->qwRoleID;
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        fnAck->eResult = EArenaR_OtherErr;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return ;
    }
    const SVIPLevelCFGEx* pCfgVip = VIPMgr.GetVIPLevelCfg(pUser->GetVIPLevel());
    if(pCfgVip == NULL)
    {
        fnAck->eResult = EArenaR_OtherErr;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return ;
    }

    CCenterVar& rVar = pUser->GetCenterVar();
    if(rVar.GetVar(NVarDefine::ePlayerVarBuyLadderTimesToday) >= pCfgVip->_ArenaBoughtTimes)
    {
        fnAck->eResult = EArenaR_LadderBuyTimesUp;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return;
    }
    const STimesPriceCFG* pCfg =  g_TimesPriceManager.GetConfigByTimes(rVar.GetVar(NVarDefine::ePlayerVarBuyLadderTimesToday) + 1);
    if(!pCfg)
    {
        fnAck->eResult = EArenaR_OtherErr;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return;
    }
    if(pUser->GetGold() < pCfg->_Arena)
    {
        fnAck->eResult = EArenaR_LackMoney;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return ;
    }
    //扣钱
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID,1,qwRoleID,NLogDataDefine::ItemTo_BuyLadderTimes,NProtoCommon::EMONEY_GOLD,pCfg->_Arena);
    rVar.AddVar(NVarDefine::ePlayerVarBuyLadderTimes,1);
    rVar.AddVar(NVarDefine::ePlayerVarBuyLadderTimesToday,1); 
    /*
       TVecINT32 vecParam;
    //vecParam.push_back(rVar.GetVar(NVarDefine::ePlayerVarBuyArenaChallengeTimesOneDay));
    vecParam.push_back(1);
    pUser->OnEvent(eEventType_ExperienceTimesBought,vecParam);
    */

    fnAck->eResult = EArenaR_Suc;
    fnAck->dwLadderBuyTimesToday =  rVar.GetVar(NVarDefine::ePlayerVarBuyLadderTimesToday);
    fnAck->dwLadderBuyTimes = rVar.GetVar(NVarDefine::ePlayerVarBuyLadderTimes);
    fnAck(true);

}

void  CArenaManager::DoBuyArenaChallengeTimes(SArenaPlayerData *pPlayer,shared_func<CArenaGSSvr::SArenaByChallengeTimesAck>& fnAck)
{
    UINT64 qwRoleID = pPlayer->qwRoleID;
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        fnAck->eResult = EArenaR_OtherErr;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return ;
    }
    /*if(pUser->GetVIPLevel() < _stConfig.stArenaNum.byExtraVip)
      {
      fnAck->eResult = EArenaR_VIPLevel;
      g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
      fnAck(true);
      return ;
      }
      CCenterVar& rVar = pUser->GetCenterVar();
      if(rVar.GetVar(NVarDefine::ePlayerVarBuyArenaChallengeTimesOneDay) >= _stConfig.stArenaNum.byExtraTimes)
      {
      fnAck->eResult = EArenaR_BuyTimesChanllengeTimes;
      g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
      fnAck(true);
      return;
      }*/
    const SVIPLevelCFGEx* pCfgVip = VIPMgr.GetVIPLevelCfg(pUser->GetVIPLevel());
    if(pCfgVip == NULL)
    {
        fnAck->eResult = EArenaR_OtherErr;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return ;
    }

    CCenterVar& rVar = pUser->GetCenterVar();
    if(rVar.GetVar(NVarDefine::ePlayerVarBuyArenaChallengeTimesOneDay) >= pCfgVip->_ArenaBoughtTimes)
    {
        fnAck->eResult = EArenaR_LadderBuyTimesUp;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return;
    }
    const STimesPriceCFG* pCfg =  g_TimesPriceManager.GetConfigByTimes(rVar.GetVar(NVarDefine::ePlayerVarBuyArenaChallengeTimesOneDay) + 1);
    if(!pCfg)
    {
        fnAck->eResult = EArenaR_OtherErr;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return;
    }
    if(pUser->GetGold() < pCfg->_Arena)
    {
        fnAck->eResult = EArenaR_LackMoney;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return ;
    }
    //扣钱
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID,1,qwRoleID,NLogDataDefine::ItemTo_BuyLadderTimes,NProtoCommon::EMONEY_GOLD,pCfg->_Arena);
    rVar.AddVar(NVarDefine::ePlayerVarBuyArenaChallengeTimes,1);
    rVar.AddVar(NVarDefine::ePlayerVarBuyArenaChallengeTimesOneDay,1); 

    TVecINT32 vecParam;
    vecParam.push_back(1);
    pUser->OnEvent(eEventType_ExperienceTimesBought,vecParam);

    fnAck->eResult = EArenaR_Suc;
    fnAck->wChallenge =  rVar.GetVar(NVarDefine::ePlayerVarArenaChallengeFree);
    fnAck->wChallengeBuyTimes = rVar.GetVar(NVarDefine::ePlayerVarBuyArenaChallengeTimes);
    fnAck(true);
}

void  CArenaManager::DoArenaChallenge(UINT64 qwRoleID,UINT64 qwEnemyID,shared_func<CArenaGSSvr::SArenaChallengeReqAck>& fnAck)
{
    SArenaPlayerData *pPlayer = GetPlayer(qwRoleID);
    if(NULL == pPlayer)
    {
        fnAck->eResult = EArenaR_NoEnter;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return ;
    }
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        fnAck->eResult = EArenaR_OtherErr;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);

        fnAck(true);
        return ;
    }

    const SVIPLevelCFGEx* pCfgVip = VIPMgr.GetVIPLevelCfg(pUser->GetVIPLevel());
    if(pCfgVip == NULL)
    {
        fnAck->eResult = EArenaR_OtherErr;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);

        fnAck(true);
        return ;
    }

    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        fnAck->eResult = EArenaR_NoEnter;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);

        fnAck(true);
        return ;
    }
    NRoleInfoDefine::SRoleArenaInfo &rInfo = rSelfInfo[0];
    UINT32 dwNow = time(NULL);
    //if(pUser->GetVIPLevel() < 3 && (rInfo.dwCDTime != 0 && dwNow < rInfo.dwCDTime))
    if(!pCfgVip->_LilianCD && (rInfo.dwCDTime != 0 && dwNow < rInfo.dwCDTime))
    {
        fnAck->eResult = EArenaR_CDTime;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);

        fnAck(true);
        return ;
    }
    //挑战次数
    CCenterVar& rVar = pUser->GetCenterVar();
    UINT16 wChallenge = rVar.GetVar(NVarDefine::ePlayerVarArenaChallengeFree);
    UINT16 wChallengeBuyTimes = rVar.GetVar(NVarDefine::ePlayerVarBuyArenaChallengeTimes);

    UINT32 dwCost = 0;
    if (wChallenge >=  _stConfig.stArenaNum.byFreeTimes && wChallengeBuyTimes == 0)
    {

        fnAck->eResult = EArenaR_NoChanllengeTimes;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);

        fnAck(true);
        return ;

    }
    bool bUpdate = CheckFlush(qwRoleID);
    if(bUpdate)
    {
        UpdatePlayerDataToDB(qwRoleID);
        fnAck->eResult =  EArenaR_EnemyTimeOut;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);

        fnAck(true);
        return ;
    }

    UINT8 bySize =rInfo.vecFlushFigter.size();
    bool bFind = false;
    for(auto i = 0; i != bySize;i++)
    {
        SFlushFighter &stFighter = rInfo.vecFlushFigter[i];
        if(stFighter.qwFighterID == qwEnemyID)
        {
            if(stFighter.bySuc > 0)
            {
                fnAck->eResult = EArenaR_EnemyIsSuc;
                g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);

                fnAck(true);
                return ;
            }
            bFind = true;
        }
    }
    if(!bFind)
    {
        fnAck->eResult = EArenaR_EnemyNoExist;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);

        fnAck(true);
        return ;
    }
    if(!pUser->GetOpLock().AddLock(eLock_Arena))
    {
        fnAck(false);
        return ;

    }

    //加上挑战次数
    rVar.AddVar(NVarDefine::ePlayerVarArenaChallengeFree,1,_stConfig.stArenaNum.byReflushTimer*3600);
    if (wChallenge >=  _stConfig.stArenaNum.byFreeTimes )
    {
        rVar.SetVar(NVarDefine::ePlayerVarBuyArenaChallengeTimes,wChallengeBuyTimes==0 ? 0: wChallengeBuyTimes-1);
    }

    //设置CD
    rInfo.dwCDTime = pCfgVip->_LilianCD ? 0 : dwNow +_stConfig.stArenaNum.dwCDTimer;
    TVecINT32 vecParam;
    vecParam.push_back(rVar.GetVar(NVarDefine::ePlayerVarArenaChallengeFree));
    pUser->OnEvent(eEventType_ExperienceChallenge,vecParam);
    //rInfo.dwCDTime = pUser->GetVIPLevel() < 3 ?  dwNow +_stConfig.stArenaNum.dwCDTimer : 0;
    //操作时间
    pPlayer->stBaseData.dwLastFlushTime = time(NULL);
    fnAck->dwCDTimer = rInfo.dwCDTime; 
    fnAck->wChallenge =  rVar.GetVar(NVarDefine::ePlayerVarArenaChallengeFree);
    fnAck->wChallengeBuyTimes = rVar.GetVar(NVarDefine::ePlayerVarBuyArenaChallengeTimes);
    DoFighterToEnemy(qwRoleID,qwEnemyID,dwCost,[fnAck,qwRoleID,qwEnemyID](UINT8 byRet,UINT8 bySuc,UINT64 qwBattleID){
            if(byRet != 0)
            {
            LOG_CRI << "Battle ERR";
            fnAck->eResult = EArenaR_OtherErr;
            g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            fnAck(true);
            return;
            }
            fnAck->eResult = EArenaR_Suc;
            fnAck->bySuc = bySuc;
            fnAck->qwBattleID = qwBattleID;
            //加积分重排序
            UINT32 dwScore =0;
            UINT32 dwRepute = 0;
            SArenaPlayerData *pPlayer = GetPlayer(qwRoleID);
            if(pPlayer ==NULL)
            {
            LOG_CRI <<" CAN NOT FIND Player";
            fnAck->eResult = EArenaR_OtherErr;
            g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            fnAck(true);
            return ;
            }
            CRankData *pRank = GetRankData(pPlayer->stBaseData.eLevel);
            if(pRank ==NULL)
            {
                LOG_CRI <<" CAN NOT FIND RANK ";
                fnAck->eResult = EArenaR_OtherErr;
                g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return ;
            }
            const SArenaCFG *pCfg = pRank-> GetConfig();
            if(NULL == pCfg)
            {
                fnAck->eResult = EArenaR_OtherErr;
                fnAck(true);
                return ;
            }
            if(bySuc > 0)
            {
                dwScore = pCfg->_wVictorScore;
                dwRepute = pCfg->_wVictorFame;
                //额外积分
                UINT8 byOtherLevel = 0;
                SArenaPlayerData *pOtherPlayer = GetPlayer(qwEnemyID);
                if(NULL != pOtherPlayer)
                {
                    byOtherLevel = pOtherPlayer->stBaseData.eLevel;
                }
                dwScore += pRank->GetExtraScore(byOtherLevel);

            }
            else
            {
                dwScore = pCfg->_wFailScore;
                dwRepute =pCfg->_wFailFame;
            }

            TSetUINT64 vecUpdate;
            if(dwScore > 0 )
            {
                pRank->PlayerAddScore(dwScore,pPlayer,vecUpdate);
            }
            fnAck->dwScore = pPlayer->stBaseData.dwScore;
            fnAck->dwRanking = pRank->GetPreNumByScore(pPlayer->stBaseData.dwScore)+pPlayer->stBaseData.dwRanking;
            //将整体推到服务器
            UpadateBaseToDB(vecUpdate);
            //如果胜利，标记已经改变状态1
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            if(NULL == pUser)
            {
                LOG_CRI << "Battle ERR";
                fnAck->eResult = EArenaR_OtherErr;
                g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return;

            }
            pUser->GetOpLock().UnLock(eLock_Arena);
            if(dwRepute >0 )
            {
                SUserItem sItem;
                sItem.dwTypeID = NProtoCommon::EMONEY_PRESTIGE;
                sItem.dwCount = dwRepute;
                TVecUserItem vecItem;
                vecItem.push_back(sItem);
                UINT32 dwServerID = pUser->GetGameSvrID();
                g_Game2CenterCommS.SendSvr_UserAddItem(&dwServerID,1,qwRoleID,NLogDataDefine::ItemFrom_ArenaBattle,vecItem,NULL);
            }
            NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
            if(rSelfInfo.empty())
            {
                LOG_CRI << "Battle ERR";
                fnAck->eResult = EArenaR_OtherErr;
                g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return;
            }
            NRoleInfoDefine::SRoleArenaInfo &rInfo = rSelfInfo[0];
            //将玩家数据推倒数据库
            UINT8 bySize =rInfo.vecFlushFigter.size();
            UINT8 bySucNum = 0;
            if(bySuc >0 )
            {
                for(auto i = 0; i != bySize;i++)
                {
                    SFlushFighter &stFighter = rInfo.vecFlushFigter[i];
                    if(stFighter.qwFighterID == qwEnemyID)
                    {
                        stFighter.bySuc  = 1;
                    }
                    if(stFighter.bySuc > 0)
                    {
                        bySucNum++;
                    }
                }
                //rInfo.dwCDTime = 0;
                fnAck->dwCDTimer = rInfo.dwCDTime; 
                if(pUser)
                {
                    TVecINT32 vecParam;
                    vecParam.push_back(1);
                    pUser->OnEvent(eEventType_ExperienceGetVictory,vecParam);
                }

            }
            if(bySize ==  bySucNum)
            {
                DoFlush(qwRoleID);
            }
            UpdatePlayerDataToDB(qwRoleID);
            fnAck(true);


    });

}

void CArenaManager::DoFighterToEnemy(UINT64 qwRoleID,UINT64 qwEnemyID,UINT32 dwCost, FunBattle fun)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        fun(1,0,0);
        return ;
    }
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_FigtherToOther(&dwServerID, 1, qwRoleID, qwEnemyID,dwCost,NBattleGS::EBArena,0,0,0,
            [fun,qwRoleID,qwEnemyID](UINT8 byRet_,UINT8 byRet,UINT8 bySuc, UINT64 qwBattleID, UINT32 dwSelfFighterPower, UINT8 bySelfQuality, UINT32 dwOtherFighterPower, UINT8 byOtherQuality, UINT32  wRetuns )
            {
            if(byRet_ != 0)
            {
            byRet = byRet_;
            }
            if(!IsRobot(qwEnemyID,false) && !IsRobot(qwEnemyID,true))
            {
            SArenaPlayerData * pOther = GetPlayer(qwEnemyID);
            if(pOther && pOther->stBaseData.dwFighterPower != dwOtherFighterPower)
            {
            pOther->stBaseData.dwFighterPower = dwOtherFighterPower;
            UpadateBaseToDB(qwEnemyID);
            }
            CUserPtr pOtherUser = CUserMgr::GetUserByUserID(qwEnemyID);
            if(pOtherUser)
            {
            if(pOtherUser->GetFighterPower() != dwOtherFighterPower)
            {
            pOtherUser->SetFighterPower(dwOtherFighterPower);
            pOtherUser->SetQuality(byOtherQuality);
            }
            }

            }
    SArenaPlayerData * pSelf = GetPlayer(qwRoleID);
    if(pSelf)
    {
        pSelf->stBaseData.dwFighterPower = dwSelfFighterPower;
        CUserPtr pSelfUser = CUserMgr::GetUserByUserID(qwRoleID);
        if(pSelfUser)
        {
            if(pSelfUser->GetFighterPower() != dwSelfFighterPower)
            {
                pSelfUser->SetFighterPower(dwSelfFighterPower);
                pSelfUser->SetQuality(bySelfQuality);
            }
        }
    }
    fun(byRet,bySuc,qwBattleID);
            });

}

void CArenaManager::ResetWirship()
{
    _vecWirship.clear();
    if(_stConfig.stWorship.byShowworshipNum > 0)
    {
        GetPlayerListByRank(_vecWirship,EArenaLevel_DIAMOND,0,_stConfig.stWorship.byShowworshipNum);
    }

}

void CArenaManager::CalAwardInfo(SArenaPlayerData *pPlayer,TVecArenaAward &vecAwards)
{
    //
    if(pPlayer == NULL)
    {
        return ;
    }
    EArenaLevel eCurLevel = pPlayer->stBaseData.eLevel;
    CRankData* pRank = GetRankData(eCurLevel);
    if(pRank == NULL)
    {
        return ;
    }
    /*UINT32 dwSameDays = pPlayer->stBaseData.dwSameDays;*/
    UINT32 dwCurRank = 0;
    EArenaLevel eNewLevel = pRank->CalPlayerNewLevel(pPlayer,/*dwSameDays,*/dwCurRank);
    GetAward(eNewLevel,pPlayer->stBaseData.dwLastLadderRank,eCurLevel,dwCurRank,vecAwards);
}
void  CArenaManager::GetArenaAward(CUserPtr pUser,SArenaPlayerData *pPlayer,shared_func<CArenaGSSvr::SGetArenaAwardAck>& fnAck)
{
    UINT64 qwRoleID = pUser->GetUserID();
    CCenterVar& rVar = pUser->GetCenterVar();
    if(rVar.GetVar(NVarDefine::ePlayerVarArenaChallengeFree) < SParamConfig::byLilianActiveTimes)
    {
        fnAck->eResult = EArenaR_ArenaTimesLimit;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return;
    }
    //如果奖励已经领掉
    UINT32 dwAward = rVar.GetVar(NVarDefine::ePlayerVarChallegeAward);
    if((dwAward & Award_Arena) > 0)
    {
        fnAck->eResult = EArenaR_ArenaAwardHasGet;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return;
    }
    if(!pUser->GetOpLock().AddLock(eLock_Arena))
    {
        fnAck(false);
        return ;
    }
    UINT32 dwServerID = pUser->GetGameSvrID();
    UINT32 dwLootId = SParamConfig::dwLilianActiveReward;
    g_Game2CenterCommS.SendSvr_CanPushLoot(&dwServerID, 1,qwRoleID,dwLootId,[qwRoleID,dwLootId,fnAck](UINT8 byRet_,UINT8 byRet){
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            if(NULL == pUser)
            {
            fnAck(false);
            return ;
            }
            else
            pUser->GetOpLock().UnLock(eLock_Arena);

            if(byRet_ != 0 || byRet != 0)
            {
            fnAck->eResult = EArenaR_PackageFull;
            g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            fnAck(true);
            return ;
            }
            //////////////////////////////
            UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
            if(dwCalTimer == 0)
            {
                fnAck(false);//等待结算
                return ;
            }
            SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
            if(pPlayer == NULL)
            {
                fnAck->eResult = EArenaR_NoEnter;
                g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return ;
            }
            CCenterVar& rVar = pUser->GetCenterVar();
            if(rVar.GetVar(NVarDefine::ePlayerVarArenaChallengeFree) < SParamConfig::byLilianActiveTimes)
            {
                fnAck->eResult = EArenaR_ArenaTimesLimit;
                g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return;
            }
            //如果奖励已经领掉
            UINT32 dwAward = rVar.GetVar(NVarDefine::ePlayerVarChallegeAward);
            if((dwAward & Award_Arena) > 0)
            {
                fnAck->eResult = EArenaR_ArenaAwardHasGet;
                g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return;
            }
            dwAward |= Award_Arena;
            UINT32 dwServerID = pUser->GetGameSvrID();
            g_Game2CenterCommS.SendSvr_PushLoot(&dwServerID,1,qwRoleID,eOpAreaAwardDays,NLogDataDefine::ItemFrom_ArenaAward,dwLootId);
            rVar.SetVar(NVarDefine::ePlayerVarChallegeAward,dwAward);
            TVecINT32 vecParam;
            vecParam.push_back(100);  //这是数字仅做成就用活跃度领奖类型
            pUser->OnEvent(eEventType_ExperienceGetPrize,vecParam);

            fnAck(true);
    });
}
void  CArenaManager::GetLadderAward(CUserPtr pUser,SArenaPlayerData *pPlayer,shared_func<CArenaGSSvr::SGetLadderAwardAck>& fnAck)
{
    //如果天梯未开启
    UINT64 qwRoleID = pUser->GetUserID();
    if(!pUser->HasIcon(Type_Ladder))
    {
        fnAck->eResult = EArenaR_LadderNOOpen;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return;
    }
    CCenterVar& rVar = pUser->GetCenterVar();
    if(rVar.GetVar(NVarDefine::ePlayerVarLadderChallenge) < SParamConfig::byLadderActiveTimes)
    {
        fnAck->eResult = EArenaR_LadderTimesLimit;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return;
    }
    //如果奖励已经领掉
    UINT32 dwAward = rVar.GetVar(NVarDefine::ePlayerVarChallegeAward);
    if((dwAward & Award_Ladder) > 0)
    {
        fnAck->eResult = EArenaR_LadderAwardHasGet;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return;
    }
    UINT32 dwServerID = pUser->GetGameSvrID();
    UINT32 dwLootId = SParamConfig::dwSwordFightingActiveReward;
    if(!pUser->GetOpLock().AddLock(eLock_Arena))
    {
        fnAck(false);
        return ;
    }
    g_Game2CenterCommS.SendSvr_CanPushLoot(&dwServerID, 1,qwRoleID,dwLootId,[qwRoleID,dwLootId,fnAck](UINT8 byRet_,UINT8 byRet){
            if(byRet_ != 0 || byRet != 0)
            {
            fnAck->eResult = EArenaR_PackageFull;
            g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            fnAck(true);
            return ;
            }
            //////////////////////////////
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            if(NULL == pUser)
            {
            fnAck(false);
            return ;
            }
            else
            {
            pUser->GetOpLock().UnLock(eLock_Arena);
            }
            UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
            if(dwCalTimer == 0)
            {
                fnAck(false);//等待结算
                return ;
            }
            SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
            if(pPlayer == NULL)
            {
                fnAck->eResult = EArenaR_NoEnter;
                g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return ;
            }
            CCenterVar& rVar = pUser->GetCenterVar();
            if(rVar.GetVar(NVarDefine::ePlayerVarLadderChallenge) < SParamConfig::byLadderActiveTimes)
            {
                fnAck->eResult = EArenaR_LadderTimesLimit;
                g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return;
            }
            //如果奖励已经领掉
            UINT32 dwAward = rVar.GetVar(NVarDefine::ePlayerVarChallegeAward);
            if((dwAward & Award_Ladder) > 0)
            {
                fnAck->eResult = EArenaR_LadderAwardHasGet;
                g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return;
            }
            dwAward |= Award_Ladder;
            UINT32 dwServerID = pUser->GetGameSvrID();
            g_Game2CenterCommS.SendSvr_PushLoot(&dwServerID,1,qwRoleID,eOpAreaAwardDays,NLogDataDefine::ItemFrom_ArenaAward,dwLootId);
            rVar.SetVar(NVarDefine::ePlayerVarChallegeAward,dwAward);
            TVecINT32 vecParam;
            vecParam.push_back(100);
            pUser->OnEvent(eEventType_ArenaGetPrize,vecParam);

            fnAck(true);
    });
}
void CArenaManager::GetLadderReport(CUserPtr pUser,SArenaPlayerData *pPlayer,shared_func<CArenaGSSvr::SGetLadderReportAck>& fnAck)
{
    UINT64 qwRoleID = pUser->GetUserID();
    if(!pUser->HasIcon(Type_Ladder))
    {
        fnAck->eResult = EArenaR_LadderNOOpen;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return;
    }
    pUser->GetLadderReport([fnAck,qwRoleID](INT8 byRet,NRoleInfoDefine::TVecBattleRePort& vecReport){
            if(byRet != 0)
            {
            fnAck->eResult = EArenaR_OtherErr;
            g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            fnAck(true);
            return;
            }
            for(auto pos = vecReport.begin();pos != vecReport.end();pos++)
            {
            const NRoleInfoDefine::SBattleRePort &rReport = *(pos);
            SLadderReport sClient;
            sClient.qwBattleID = rReport.qwBattleID;
            sClient.qwEmemyID = rReport.qwAttackID < MaxRobotID   ? 0 : rReport.qwAttackID;
            sClient.strName = rReport.strAttackID;
            sClient.dwMonsterId = rReport.qwAttackID < MaxRobotID ? rReport.qwAttackID : 0;
            sClient.byAttack = rReport.eActionType == NRoleInfoDefine::eTypeAttack ? 0: 1;
            if(rReport.eActionType == NRoleInfoDefine::eTypeAttack)
            {
            if(rReport.eSuc == NRoleInfoDefine::eTypeAttack)
            {
                sClient.bySuc = 1;
            }
            else
            {
                sClient.bySuc  = 0;
            }
            }
            else
            {
                if(rReport.eSuc == NRoleInfoDefine::eTypeAttack)
                {
                    sClient.bySuc = 0;
                }
                else
                {
                    sClient.bySuc  = 1;
                }
            }
            sClient.dwPreRank = rReport.dwParam1;
            sClient.dwNowRank = rReport.dwParam2;
            sClient.dwTimer = rReport.dwTime;
            fnAck->vecReport.push_back(sClient);

            }
    fnAck(true);
    });

}
void CArenaManager::LadderBattle(CUserPtr pUser,SArenaPlayerData *pPlayer,UINT64 qwEnemyID,UINT32 dwEnemyRank, shared_func<CArenaGSSvr::SLadderBattleAck>& fnAck)
{
    UINT64 qwRoleID = pUser->GetUserID();
    if(!pUser->HasIcon(Type_Ladder))
    {
        fnAck->eResult = EArenaR_LadderNOOpen;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return;
    }
    //如果未战机器人，那么检查机器人
    NRoleInfoDefine::SRoleArenaInfo * pPlayerInfo = GetPlayerInfo(qwRoleID);
    if(pPlayerInfo == NULL)
    {
        fnAck->eResult = EArenaR_LadderNOOpen;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return;
    }
    if(!IsRobot(qwEnemyID,false) && !IsRobot(qwEnemyID,true))//初始化机器人
    {
        SArenaPlayerData *pOtherPlayer = CArenaManager::GetPlayer(qwEnemyID);
        //验证对手排名
        if(!pOtherPlayer || pOtherPlayer->stBaseData.dwLadderRank !=dwEnemyRank || pOtherPlayer->stBaseData.dwLadderRank > SParamConfig::wSwordFightingLadderMaxPlayerNum)
        {
            fnAck->eResult = EArenaR_LadderRankErr;
            g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            fnAck(true);
            return ;


        }
    }
    //挑战资格
    if(!CanLadderByRank(qwRoleID,pPlayer->stBaseData.dwLadderRank,qwEnemyID))
    {
        fnAck->eResult = EArenaR_LadderRankLimit;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return ;
    }

    UINT32 dwNow = time(NULL);
    pPlayer->stBaseData.dwLastFlushTime = dwNow;
    //冷却
    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        LOG_CRI <<"RoleArenaInfo is empty";
        return ;
    }
    NRoleInfoDefine::SRoleArenaInfo &stPlayerInfo = rSelfInfo[0];

    if(stPlayerInfo.dwLadderCDTime > dwNow)
    {
        fnAck->eResult = EArenaR_CDTime;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return ;
    }

    const SVIPLevelCFGEx* pCfgVip = VIPMgr.GetVIPLevelCfg(pUser->GetVIPLevel());
    if(pCfgVip == NULL)
    {
        fnAck->eResult = EArenaR_OtherErr;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);

        fnAck(true);
        return ;
    }
    //挑战次数
    CCenterVar& rVar = pUser->GetCenterVar();
    if( rVar.GetVar(NVarDefine::ePlayerVarLadderChallenge) >= pCfgVip->_ArenaTimes)
    {
        if(rVar.GetVar(NVarDefine::ePlayerVarBuyLadderTimes) == 0)
        {
            fnAck->eResult = EArenaR_LadderTimesZero;
            g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);

            fnAck(true);
            return ;
        }
    }
    bool bIsNoCD = (pCfgVip->_ArenaNoCd || pUser->CheckGameBuffValid(SParamConfig::wTempVIPPrivilege)) ? true : false;
    stPlayerInfo.dwLadderCDTime = bIsNoCD ? 0 : dwNow + SParamConfig::wLadderColdTime;
    if(!pUser->GetOpLock().AddLock(eLock_Arena))
    {
        fnAck(false);
        return ;

    }
    if(!CArenaManager::LockEnemy(qwRoleID))
    {
        fnAck(false);
        return ;
    }
    if(IsRobot(qwEnemyID,true) && !CArenaManager::LockEnemy(qwEnemyID))
    {
        fnAck(false);
        return ;

    }
    DoFighterToEnemy(qwRoleID,qwEnemyID,0,[fnAck,qwRoleID,qwEnemyID](UINT8 byRet,UINT8 bySuc,UINT64 qwBattleID){
            UnLockEnemy(qwRoleID);
            if(IsRobot(qwEnemyID,true))
            {
            UnLockEnemy(qwEnemyID);
            }
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            if(pUser)
            {
            pUser->GetOpLock().UnLock(eLock_Arena);
            }
            else
            {
            fnAck(false);
            return ;
            }
            CCenterVar& rVar = pUser->GetCenterVar();
            if(byRet != 0)
            {
            fnAck->eResult = EArenaR_OtherErr;
            g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            fnAck(true);
            return ;

            }
            NRoleInfoDefine::SRoleArenaInfo *pPlayerInfo =GetPlayerInfo(qwRoleID);
            if(pPlayerInfo == NULL)
            {
                fnAck->eResult = EArenaR_OtherErr;
                g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return ;

            }
            SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
            SArenaPlayerData *pOtherPlayer =NULL;
            if(!pPlayer)
            {
                fnAck->eResult = EArenaR_OtherErr;
                g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return ;
            }
            UINT32 dwOldRank = pPlayer->stBaseData.dwLadderRank;
            UINT32 dwOtherOldRank = 0;
            TSetUINT64 rsetUpdate;
            bool bNotice= false;

            bool bMinRankChange = false; //
            if(IsRobot(qwEnemyID,false))//初始化战斗
            {
                dwOtherOldRank =   LadderRankNoRank; 
                bNotice = (bySuc>0 && dwOldRank > dwOtherOldRank);
                if(bNotice)//低攻高胜利或高攻低失败
                {
                    pPlayer->stBaseData.dwLadderRank = dwOtherOldRank;
                    UINT32 dwMinRank =  rVar.GetVar(NVarDefine::ePlayerMinLadderRank);
                    if(dwOtherOldRank < dwMinRank)
                    {
                        SendLadderRankAward(qwRoleID,dwMinRank,dwOtherOldRank);
                        rVar.SetVar(NVarDefine::ePlayerMinLadderRank,dwOtherOldRank);
                        TVecINT32 vecParam;
                        vecParam.push_back(dwOtherOldRank);
                        pUser->OnEvent(eEventType_ArenaRankChanging,vecParam);

                        bMinRankChange = true;

                    }

                    rsetUpdate.insert(qwRoleID);
                }


            }
            else if(IsRobot(qwEnemyID,true))//与机器人战斗，有资格进入SParamConfig::wSwordFightingLadderMaxPlayerNum
            {
                dwOtherOldRank =   GetRobotRankById(qwEnemyID); 
                bNotice = (bySuc>0 && dwOldRank > dwOtherOldRank)/*||(bySuc==0 && dwOldRank < dwOtherOldRank )*/;

                if(bNotice)//低攻高胜利或高攻低失败
                {
                    pPlayer->stBaseData.dwLadderRank = dwOtherOldRank;
                    _vecLadderRank[dwOtherOldRank-1] = qwRoleID;
                    SLadderRobot SData;
                    SData.wMonsterID = qwEnemyID;
                    if(dwOldRank == LadderRankNoRank)//机器人出局
                    {
                        _mapLadderRobotIDIDFirst.erase(qwEnemyID);
                        SData.wRank = LadderRankNoRank;

                    }
                    else//与机器人交换位置
                    {
                        _vecLadderRank[dwOldRank -1] = qwEnemyID;
                        _mapLadderRobotIDIDFirst[qwEnemyID] = dwOldRank;
                        SData.wRank = dwOldRank;
                    }
                    g_Center2DBCommC.Send_UpdateLadderRobot(SData);

                    UINT32 dwMinRank =  rVar.GetVar(NVarDefine::ePlayerMinLadderRank);
                    if(dwOtherOldRank < dwMinRank)
                    {
                        SendLadderRankAward(qwRoleID,dwMinRank,dwOtherOldRank);
                        rVar.SetVar(NVarDefine::ePlayerMinLadderRank,dwOtherOldRank);

                        TVecINT32 vecParam;
                        vecParam.push_back(dwOtherOldRank);
                        pUser->OnEvent(eEventType_ArenaRankChanging,vecParam);

                        bMinRankChange = true;

                    }

                    rsetUpdate.insert(qwRoleID);
                }

            }
            else
            {
                pOtherPlayer = CArenaManager::GetPlayer(qwEnemyID);
                dwOtherOldRank =   pOtherPlayer->stBaseData.dwLadderRank;
                if(!pOtherPlayer)
                {
                    fnAck->eResult = EArenaR_OtherErr;
                    g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                    fnAck(true);
                    return ;
                }
                bNotice = (bySuc>0 && dwOldRank > dwOtherOldRank)/*||(bySuc==0 && dwOldRank < dwOtherOldRank )*/;

                if(bNotice)//低攻高胜利或高攻低失败
                {
                    pPlayer->stBaseData.dwLadderRank = pOtherPlayer->stBaseData.dwLadderRank;
                    pOtherPlayer->stBaseData.dwLadderRank = dwOldRank;
                    _vecLadderRank[pPlayer->stBaseData.dwLadderRank-1] = qwRoleID;
                    if(dwOldRank != LadderRankNoRank)
                    {
                        _vecLadderRank[pOtherPlayer->stBaseData.dwLadderRank-1] = qwEnemyID;
                    }
                    UINT32 dwMinLadderRank =  rVar.GetVar(NVarDefine::ePlayerMinLadderRank);
                    if(dwOtherOldRank < dwMinLadderRank)
                    {
                        SendLadderRankAward(qwRoleID,dwMinLadderRank,dwOtherOldRank);
                        rVar.SetVar(NVarDefine::ePlayerMinLadderRank,dwOtherOldRank);

                        TVecINT32 vecParam;
                        vecParam.push_back(dwOtherOldRank);
                        pUser->OnEvent(eEventType_ArenaRankChanging,vecParam);
                        bMinRankChange = true;



                    }

                    rsetUpdate.insert(qwEnemyID);
                    rsetUpdate.insert(qwRoleID);
                    CUserPtr pOtherUser = CUserMgr::GetUserByUserID(qwEnemyID);
                    TVecINT32 vecParam;
                    vecParam.push_back(dwOldRank);

                    if(pOtherUser && pOtherUser->IsOnline())
                    {
                        pOtherUser->OnEvent(eEventType_ArenaRankDwon,vecParam);

                    }
                    else
                    {
                        CUser::AddOffLineEvent(qwEnemyID,eEventType_ArenaRankDwon,vecParam); 
                    }

                }
            }
            UpadateBaseToDB(rsetUpdate); 
            if(bNotice)
            {
                LadderNoticeServer(qwRoleID,pPlayer,dwOldRank);
                if(!IsRobot(qwEnemyID,true) && !IsRobot(qwEnemyID,false))
                    LadderNoticeServer(qwEnemyID,pOtherPlayer,dwOtherOldRank);
            }
            //战报
            NRoleInfoDefine::SBattleRePort sReport;
            sReport.qwRoleID = qwRoleID;
            sReport.qwBattleID = qwBattleID;
            sReport.qwAttackID = qwEnemyID;
            sReport.eActionType = NRoleInfoDefine::eTypeAttack;
            sReport.eType = NRoleInfoDefine::eTypeLadder;
            sReport.eSuc = bySuc > 0 ? NRoleInfoDefine::eTypeAttack : NRoleInfoDefine::eTypeDefense;
            sReport.dwTime =time(NULL);
            sReport.dwParam1 = dwOldRank;
            sReport.dwParam2 = pPlayer->stBaseData.dwLadderRank;
            if(pOtherPlayer != NULL)
            {
                sReport.strAttackID = pOtherPlayer->stFighter.strName;
            }
            pUser->AddLadderReport(sReport);
            if(pOtherPlayer != NULL)
            {
                NRoleInfoDefine::SBattleRePort sOtherReport;
                sOtherReport.qwRoleID = qwEnemyID;
                sOtherReport.qwBattleID = qwBattleID;
                sOtherReport.qwAttackID = qwRoleID;
                sOtherReport.eActionType = NRoleInfoDefine::eTypeDefense;
                sOtherReport.eType = NRoleInfoDefine::eTypeLadder;
                sOtherReport.eSuc = bySuc > 0 ? NRoleInfoDefine::eTypeAttack : NRoleInfoDefine::eTypeDefense;
                sOtherReport.dwTime =time(NULL);
                sOtherReport.dwParam1 = dwOtherOldRank;
                sOtherReport.dwParam2 = pOtherPlayer->stBaseData.dwLadderRank;
                sOtherReport.strAttackID = pPlayer->stFighter.strName;

                CUserPtr pOtherUser = CUserMgr::GetUserByUserID(qwEnemyID);
                if(pOtherUser)
                {
                    pOtherUser->AddLadderReport(sOtherReport);
                }
                else
                {
                    g_Center2DBCommC.Send_AddBattleReport(qwEnemyID,sOtherReport,10,NULL);
                }
            }
            //战斗次数
            const SVIPLevelCFGEx* pCfgVip = VIPMgr.GetVIPLevelCfg(pUser->GetVIPLevel());
            if(pCfgVip != NULL)
            {
                CCenterVar& rVar = pUser->GetCenterVar();
                rVar.AddVar(NVarDefine::ePlayerVarLadderChallenge,1);
                if( rVar.GetVar(NVarDefine::ePlayerVarLadderChallenge) > pCfgVip->_ArenaTimes)
                {
                    if(rVar.GetVar(NVarDefine::ePlayerVarBuyLadderTimes) > 0)
                    {
                        rVar.SetVar(NVarDefine::ePlayerVarBuyLadderTimes,rVar.GetVar(NVarDefine::ePlayerVarBuyLadderTimes) -1);
                    }
                }
            }


            TVecUserItem vecItem;
            if(bySuc)
            {
                //重新刷的将
                GetFlushFitherLadder(fnAck->vecFlushFigter,pPlayer);
                pPlayerInfo->dwLadderCDTime = 0;
                TVecINT32 vecParam;
                vecParam.push_back(1);
                pUser->OnEvent(eEventType_ArenaGetVictory,vecParam);
                //奖励钱
                if(_stConfig.stArenaNum.byWinLadderMoneyType1 > NProtoCommon::EMONEY_NONE && _stConfig.stArenaNum.byWinLadderMoneyType1 < NProtoCommon::EMONEY_END && _stConfig.stArenaNum.dwWinLadderMoneyValue1 > 0)
                {
                    SUserItem sItem;
                    sItem.dwTypeID = static_cast<NProtoCommon::EMoneyType>(_stConfig.stArenaNum.byWinLadderMoneyType1);
                    sItem.dwCount =  _stConfig.stArenaNum.dwWinLadderMoneyValue1;
                    vecItem.push_back(sItem);

                }
                if(_stConfig.stArenaNum.byWinLadderMoneyType2 > NProtoCommon::EMONEY_NONE && _stConfig.stArenaNum.byWinLadderMoneyType2 < NProtoCommon::EMONEY_END && _stConfig.stArenaNum.dwWinLadderMoneyValue2 > 0)
                {
                    SUserItem sItem;
                    sItem.dwTypeID = static_cast<NProtoCommon::EMoneyType>(_stConfig.stArenaNum.byWinLadderMoneyType2);
                    sItem.dwCount =  _stConfig.stArenaNum.dwWinLadderMoneyValue2;
                    vecItem.push_back(sItem);

                }

            }
            else
            {
                //奖励钱
                if(_stConfig.stArenaNum.byFailLadderMoneyType1 > NProtoCommon::EMONEY_NONE && _stConfig.stArenaNum.byFailLadderMoneyType1 < NProtoCommon::EMONEY_END && _stConfig.stArenaNum.dwFailLadderMoneyValue1 > 0)
                {
                    SUserItem sItem;
                    sItem.dwTypeID = static_cast<NProtoCommon::EMoneyType>(_stConfig.stArenaNum.byFailLadderMoneyType1);
                    sItem.dwCount =  _stConfig.stArenaNum.dwFailLadderMoneyValue1;
                    vecItem.push_back(sItem);

                }
                if(_stConfig.stArenaNum.byFailLadderMoneyType2 > NProtoCommon::EMONEY_NONE && _stConfig.stArenaNum.byFailLadderMoneyType2 < NProtoCommon::EMONEY_END && _stConfig.stArenaNum.dwFailLadderMoneyValue2 > 0)
                {
                    SUserItem sItem;
                    sItem.dwTypeID = static_cast<NProtoCommon::EMoneyType>(_stConfig.stArenaNum.byFailLadderMoneyType2);
                    sItem.dwCount =  _stConfig.stArenaNum.dwFailLadderMoneyValue2;
                    vecItem.push_back(sItem);

                }


            }
            if(!vecItem.empty() )
            {
                UINT32 dwServerID = pUser->GetGameSvrID();
                g_Game2CenterCommS.SendSvr_UserAddItem(&dwServerID,1,qwRoleID,NLogDataDefine::ItemFrom_LadderBattle,vecItem,NULL);
            }
            fnAck->dwLadderCDTimer = pPlayerInfo->dwLadderCDTime;
            fnAck->dwMinLadderRank = rVar.GetVar(NVarDefine::ePlayerMinLadderRank);
            UpdatePlayerDataToDB(qwRoleID);
            fnAck->bySuc = bySuc;
            fnAck->dwSelfRank = pPlayer->stBaseData.dwLadderRank;
            fnAck->dwLadderBuyTimes = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarBuyLadderTimes);
            fnAck->dwLadderTimes = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarLadderChallenge);
            {
                TVecINT32 vecParam;
                vecParam.push_back(fnAck->dwLadderTimes);
                pUser->OnEvent(eEventType_ArenaChallenge,vecParam);
            }
            {
                TVecINT32 vecParam;
                vecParam.push_back(fnAck->dwLadderTimes);
                vecParam.push_back(fnAck->dwSelfRank);
                pUser->OnEvent(eEventType_ArenaRank,vecParam);
            }

            if(bMinRankChange)
            {
                TVecINT32 vecParam;
                vecParam.push_back(fnAck->dwLadderTimes);
                vecParam.push_back(fnAck->dwMinLadderRank);
                pUser->OnEvent(eEventType_ArenaBestRank,vecParam); 
            }

            fnAck(true);


    });
}
bool    CArenaManager::GetFlushFitherByID(UINT64 qwRoleID,SFlushFitherForClient &stForClient,bool bLadder,UINT8 bySuc)
{
    stForClient.stFlushFighter.qwFighterID = qwRoleID;
    stForClient.stFlushFighter.bySuc = bySuc;
    if(bLadder)
    {
        stForClient.wGroup = IsRobot(qwRoleID,true) ||IsRobot(qwRoleID,false)  ? qwRoleID : 0;
    }
    else
    {
        stForClient.wGroup = !IsRobot(qwRoleID,false) ? 0 : qwRoleID;
    }
    if (IsRobot(qwRoleID,false))
    {   
        return true;

    }
    else if(IsRobot(qwRoleID,true))
    {
        if(bLadder)
        {
            stForClient.dwLadderRank = GetRobotRankById(qwRoleID);
            return true;
        }
    }
    else
    {
        SArenaPlayerData *pPlayer = GetPlayer(qwRoleID);
        if(NULL != pPlayer)
        {
            stForClient.eLevel =  pPlayer->stBaseData.eLevel;
            stForClient.stFighter = pPlayer->stFighter;
            stForClient.dwLadderRank = pPlayer->stBaseData.dwLadderRank;
            stForClient.dwFighterPower = pPlayer->stBaseData.dwFighterPower;
            CRankData* pData = GetRankData(pPlayer->stBaseData.eLevel);
            if(NULL != pData)
            {
                stForClient.dwArenaRank = pData->GetPreNumByScore(pPlayer->stBaseData.dwScore)+pPlayer->stBaseData.dwRanking +1;
            }
            return true;
        }

    }
    return false;


}
void    CArenaManager::GetFlushFitherLadder(TVecSFlushFitherForClient &rVec,SArenaPlayerData *pPlayer,UINT8 byType)
{ //刷对手
    TVecUINT64 rvecEnemy;
    SelectLadderEnemyByType(pPlayer->qwRoleID,rvecEnemy,pPlayer->stBaseData.dwLadderRank,byType);           
    rvecEnemy.push_back(pPlayer->qwRoleID);
    NRoleInfoDefine::SRoleArenaInfo *pPlayerInfo = GetPlayerInfo(pPlayer->qwRoleID);
    if(pPlayerInfo ==NULL)
    {
        LOG_CRI << "INFO ERR";
        return ;
    }
    if((pPlayer->stBaseData.dwLadderRank > 8)   && !_vecLadderRank.empty())
    {
        rvecEnemy.push_back(_vecLadderRank[0]);

    } 
    for(size_t i = 0; i != rvecEnemy.size();i++)
    {
        SFlushFitherForClient stForClient;
        if(GetFlushFitherByID(rvecEnemy[i],stForClient,true))
        {
            if(pPlayer->stBaseData.dwLadderRank == LadderRankInit &&  i < 6)
            {
                stForClient.dwLadderRank = LadderRankInit - i - 1;
            }
            rVec.push_back(stForClient);
        }
    }

}

void CArenaManager::LadderNoticeServer(UINT64 qwRoleID,SArenaPlayerData * pPlayer,UINT32 dwOldRank)
{
    if(pPlayer == NULL)
    {
        return;
    }
    if(pPlayer->stBaseData.dwLadderRank == 1)
    {
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if(pUser)
        {
            TVecString vecStr;
            vecStr.push_back(NumberToString(pUser->GetColor()));
            vecStr.push_back(pPlayer->stFighter.strName);
            g_GlobalChatProtS. SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgLadderTop,vecStr);
        }
    }
    else 
    {//提升100
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if(pUser != NULL)
        {
            CCenterVar& rVar = pUser->GetCenterVar();
            INT16 byUpdate  = rVar.GetVar(NVarDefine::ePlayerVarLadderUpdate);
            if(byUpdate < 100)
            {
                byUpdate += INT32(dwOldRank) - INT32(pPlayer->stBaseData.dwLadderRank);
                rVar.SetVar(NVarDefine::ePlayerVarLadderUpdate,byUpdate);
                if(byUpdate >100)
                {
                    //TODO:全服公告提升100
                    TVecString vecStr;
                    vecStr.push_back(NumberToString(pUser->GetColor()));
                    vecStr.push_back(pPlayer->stFighter.strName);
                    g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgLadderHundredMove,vecStr);


                }

            }
        }
    }

}

void  CArenaManager::ReFluseLadderEnemy(CUserPtr pUser,SArenaPlayerData *pPlayer,UINT8 byType,shared_func<CArenaGSSvr::SReFluseLadderEnemyAck>& fnAck)
{
    UINT64 qwRoleID = pUser->GetUserID();
    if(!pUser->HasIcon(Type_Ladder))
    {
        fnAck->eResult = EArenaR_LadderNOOpen;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return;
    }
    GetFlushFitherLadder(fnAck->vecFlushFigter,pPlayer,byType);
    fnAck(true);

}

void CArenaManager::LadderPageUpReq(CUserPtr pUser,UINT32 dwRank,UINT8 byNum,shared_func<CArenaGSSvr::SLadderPageUpReqAck>& fnAck)
{
    UINT64 qwRoleID = pUser->GetUserID();
    if(!pUser->HasIcon(Type_Ladder))
    {
        fnAck->eResult = EArenaR_LadderNOOpen;
        g_ArenaGSS.SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        fnAck(true);
        return;
    }
    for(auto i = dwRank -1;i <  _vecLadderRank.size() && fnAck->vecRankData.size() < byNum  ;i++)
    {
        SArenaRank2Client stClient;
        if(!GetRankClient(_vecLadderRank[i],stClient,i+1,true))
        {
            continue;
        }
        fnAck->vecRankData.push_back(stClient);
    }
    fnAck(true);
}

bool CArenaManager::GetRankInfo (UINT64 qwRoleID, UINT32 dwIndex, UINT32 dwCount,
        UINT32& dwMaxCount, UINT32& dwCurIndex, UINT32& dwSelfRank, 
        TVecArenaRank2Client& vecRankInfo, SArenaRank2Client& stSArenaRank)
{
    if (!dwIndex)
        dwIndex = 1;
    dwCurIndex = dwIndex;
    for(auto i = dwIndex - 1;i <  _vecLadderRank.size() && vecRankInfo.size() < dwCount  ;i++)
    {
        SArenaRank2Client stClient;
        if(!GetRankClient(_vecLadderRank[i],stClient,i + 1,true))
            continue;
        vecRankInfo.push_back(stClient);
    }
    dwMaxCount = _vecLadderRank.size();
    SArenaPlayerData *pPlayer = GetPlayer(qwRoleID);
    if(pPlayer == NULL)
        dwSelfRank = 0;
    else
        dwSelfRank = pPlayer->stBaseData.dwLadderRank;
    return GetRankClient(qwRoleID, stSArenaRank,dwSelfRank,true);
}



bool CArenaManager::IsRobot(UINT64 qwRobot,bool bIsLadderRobot)
{
    if(qwRobot >= MaxRobotID)
    {
        return false;
    }
    if(!bIsLadderRobot)
    {
        for (auto it = _stConfig.vecRobot.begin();it !=  _stConfig.vecRobot.end();it++)
        {
            if(qwRobot == *it)
            {
                return true;
            }
        }
    }
    else
    {
        if(GetRobotRankById(qwRobot) != 0)
        {
            return true;
        }
    }
    return false;
}

bool CArenaManager::CanLadderByRank(UINT64 qwRoleID,UINT32 dwAttackRank,UINT64 qwDeFense)
{
    TVecUINT64 rvecEnemy;
    SelectLadderEnemyByType(qwRoleID,rvecEnemy,dwAttackRank,0);
    for(auto it = rvecEnemy.begin();it != rvecEnemy.end();it++)
    {
        if(*it == qwDeFense)
        {
            return true;            
        }

    }
    rvecEnemy.clear();
    SelectLadderEnemyByType(qwRoleID,rvecEnemy,dwAttackRank,1);
    for(auto it = rvecEnemy.begin();it != rvecEnemy.end();it++)
    {
        if(*it == qwDeFense)
        {
            return true;            
        }

    }
    return false;

}
void CArenaManager::SelectLadderEnemyByType(UINT64 qwRoleID,TVecUINT64 &rvecEnemy,UINT32 dwRank,UINT8 byType )
{
    NRoleInfoDefine::SRoleArenaInfo * pPlayerInfo = GetPlayerInfo(qwRoleID);
    if(pPlayerInfo == NULL)
    {
        LOG_CRI <<"Self info ERR";
        return ;
    }
    SArenaPlayerData *pPlayer= GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        LOG_CRI <<"Err Info ERR";
    }
    UINT8 byStep = 1;
    if(dwRank <= 8)
    {
        for(size_t it = 0; it != 8 && it != _vecLadderRank.size();it++)
        {
            if(it+1 != dwRank)
            {
                rvecEnemy.push_back(_vecLadderRank[it]);
            }
        }
        return ;
    }
    else if(dwRank == LadderRankInit)
    {
        //初始化只刷机器人
        vector<UINT16> tepVec =  _stConfig.vecRobot;
        for(;rvecEnemy.size() != 6 && !tepVec.empty();)
        {
            UINT32 Pos = rand()%tepVec.size();
            rvecEnemy.push_back(tepVec[Pos]);
            tepVec.erase(tepVec.begin()+Pos);
        }
        return ;


    }
    if(byType == 0)
    {
        if(dwRank <= 20 )
        {
            byStep = 1;
        }
        else if(dwRank > 20 && dwRank <= 50 )
        {
            byStep = 2;
        }
        else if(dwRank <= 500 && dwRank > 50)
        {
            byStep = dwRank/50 + 2;
        }
        else if(dwRank <= 1000 && dwRank > 500)
        {
            byStep = dwRank/25 + 2;
        }
        else if(dwRank <= SParamConfig::wSwordFightingLadderMaxPlayerNum && dwRank > 1000)
        {
            byStep = dwRank/15 +2;
        }
        else if(dwRank > SParamConfig::wSwordFightingLadderMaxPlayerNum)
        {
            byStep = dwRank/15 +2;
        }

    }
    else
    {

        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if(pUser)
        {
            TVecINT32 vecParam;
            vecParam.push_back(1);
            pUser->OnEvent(eEventType_ArenaCancelRankBridge,vecParam);
        }
    }
    if(dwRank <= SParamConfig::wSwordFightingLadderMaxPlayerNum )
    {
        for(auto it = dwRank - 1 - byStep; it != 0 && rvecEnemy.size() != 6 ;it-= byStep)
        {
            rvecEnemy.push_back(_vecLadderRank[it]);

        }
        return ;
    }
    else 
    {
        for(auto it = SParamConfig::wSwordFightingLadderMaxPlayerNum-1; it != 0 && rvecEnemy.size() != 6 ;it-= byStep)
        {
            rvecEnemy.push_back(_vecLadderRank[it]);

        }

        return ;


    }

}

NRoleInfoDefine::SRoleArenaInfo *CArenaManager::GetPlayerInfo(UINT64 qwRoleID)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        LOG_CRI <<"Player NOT ONLINE";
        return NULL;
    }
    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        LOG_CRI <<"RoleArenaInfo is empty";
        return NULL;
    }
    return &(rSelfInfo[0]);
}

void CArenaManager::SendLadderRankAward(UINT64 qwRoleID,UINT32 dwLastRank,UINT32 dwNowRank)
{
    if(dwNowRank == 0)
    {
        LOG_CRI << "ERR RANK";
        return ;
    }
    auto itend = _mapLadderAward.end();
    auto itbegin =  _mapLadderAward.lower_bound(dwNowRank);
    if(dwLastRank != 0)//大于等于dwNowRank的奖励皆可领取
    {
        itend = _mapLadderAward.lower_bound(dwLastRank);
        //大于等于dwNowRank，并且小于dwLastRank 的奖励皆可领取
    }
    map<UINT16,UINT32> map_award;
    if(itbegin != _mapLadderAward.end())
    {
        const vector<LadderRankAward>& rvec = itbegin->second;
        for(auto pos = rvec.begin();pos != rvec.end();pos++)
        {
            const LadderRankAward& sItem = *pos;
            map_award[sItem.wItemId] = sItem.dwItenNum;
        }
    }
    if(itend != _mapLadderAward.end())
    {
        const vector<LadderRankAward>& rvec = itend->second;
        for(auto pos = rvec.begin();pos != rvec.end();pos++)
        {
            const LadderRankAward& sItem = *pos;
            auto iter = map_award.find(sItem.wItemId);
            if(iter != map_award.end())
            {
                if(iter->second > sItem.dwItenNum)
                {
                    iter->second -= sItem.dwItenNum;
                }
                else
                {
                    map_award.erase(iter);
                }

            }
        }
    }
    if(map_award.empty())
    {
        return ;
    }
    //sendmail
    CSystemMail sysMail;
    sysMail.AddTarget(qwRoleID);
    NMailProt::SysMailSendTxt strMsgInfo;
    strMsgInfo.vecParam.push_back(NumberToString(dwNowRank));
    string strSender;
    string strTitle;

    CSystemMail::GetSysMailBody(527,strSender);
    CSystemMail::GetSysMailBody(528,strTitle); 
    strMsgInfo.dwstrMsgID = 529;
    strMsgInfo.vecParam.push_back(NumberToString(dwLastRank - dwNowRank));
    sysMail.SetBody(strMsgInfo);
    sysMail.SetSender(strSender);
    sysMail.SetSubject(strTitle);
    TVecMailItemInfo vecItem;
    for(map<UINT16,UINT32>::iterator pos = map_award.begin();pos != map_award.end();pos++)
    {
        SMailItemInfo rInfo;
        rInfo.wItemID = pos->first;
        rInfo.wCount = pos->second;
        vecItem.push_back(rInfo);
    }
    sysMail.AddItemInfo(vecItem);
    sysMail.Send();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(pUser)
    {
        pUser->SendPkg(g_ArenaGSS.BuildPkg_UpdateLadderMinRank( dwLastRank,dwNowRank));
    }


}

void CArenaManager::OnRecv_SendAllRobot(const TVecLadderRobot& vecRobot)
{
    _byLoadOver++;
    _vecRobot = vecRobot;
    if(_byLoadOver == 2 )
    {
        for(auto iter= _mapAllRank.begin();iter != _mapAllRank.end();iter++)
        {
            iter->second.SetPreNumAllForDB();
        }
        InsertErrPlayer();
        DoInitCase();
    }

}

bool CArenaManager::LockEnemy(UINT64 qwEnemyID)
{
    auto iter = _mapLadderEnemyLock.find(qwEnemyID);
    if(iter == _mapLadderEnemyLock.end() ||time(NULL) >= _mapLadderEnemyLock[qwEnemyID]  + EnemyLockTimer)
    {
        _mapLadderEnemyLock[qwEnemyID] = time(NULL);
        return true;
    }
    return false;
}
void CArenaManager::UnLockEnemy(UINT64 qwEnemyID)
{
    _mapLadderEnemyLock.erase(qwEnemyID);
}

