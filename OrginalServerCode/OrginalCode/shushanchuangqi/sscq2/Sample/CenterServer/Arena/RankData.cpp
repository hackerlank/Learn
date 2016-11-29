#include  "RankData.h"
#include  "ArenaManager.h"
#include "Tokenizer.h"
#include <algorithm>
#include "Random.h"
#include "User.h"
#include "UserMgr.h"
UINT32 CRankData::NewPlayerEnter(UINT64 qwRoleId)
{
    _mapScore[0].vecPlayer.push_back(qwRoleId);
    return _mapScore[0].vecPlayer.size() - 1;
}


void  CRankData::PlayerAddScore(INT32 dwAddScore,SArenaPlayerData *pPlayer,TSetUINT64& rSetUpdate)
{
    UINT32 dwPreScore = pPlayer->stBaseData.dwScore;
    UINT32 dwNowScore = INT32(dwPreScore) + dwAddScore > 0 ? INT32(dwPreScore) + dwAddScore : 0 ; 
    UINT64 qwRoleId = pPlayer->qwRoleID;
    UINT32 Pos = pPlayer->stBaseData.dwRanking;
    UINT32 NowPos =0;
    if(!(dwNowScore != dwPreScore))
    {
        LOG_CRI << "No Scorce ADD";
        return ;
    }
    auto iter =  _mapScore.find(dwPreScore);
    if(iter == _mapScore.end())
    {
        LOG_CRI <<"NO Find Score";
    }
    RankNode *selfNode = &(iter->second);
    if(selfNode->vecPlayer[Pos] != qwRoleId)
    {
        LOG_CRI <<"PreData ERR";
    }
    bool bNew =false;
    for(auto i = Pos+1 ;i != selfNode->vecPlayer.size();i++)
    {
        //之后的玩家序号减1
        SArenaPlayerData *pOtherPlayer = CArenaManager::GetPlayer(selfNode->vecPlayer[i]);
        if(NULL == pOtherPlayer)
        {
            LOG_CRI << "Can find Player";
        }
        else
        {
            pOtherPlayer->stBaseData.dwRanking--;
            rSetUpdate.insert(selfNode->vecPlayer[i]);
        }

    }
    selfNode->vecPlayer.erase(selfNode->vecPlayer.begin()+Pos);
    auto iterNow = _mapScore.find(dwNowScore);
    if(iterNow == _mapScore.end())
    {
        _mapScore[dwNowScore].vecPlayer.push_back(qwRoleId);
        bNew = true;
    }
    else
    {
        iterNow->second.vecPlayer.push_back(qwRoleId);
        NowPos = iterNow->second.vecPlayer.size() - 1;
    }
    SetPreNum(dwPreScore,dwNowScore,bNew);
    pPlayer->stBaseData.dwRanking = NowPos;
    pPlayer->stBaseData.dwScore = dwNowScore;
    rSetUpdate.insert(qwRoleId);
}

void CRankData::SetPreNum(UINT32 dwPreScore,UINT32 dwNowScore,bool bNewNote)
{
    auto PreIter =  _mapScore.find(dwPreScore);
    auto NowIter =  _mapScore.find(dwNowScore);
    if(PreIter == _mapScore.end() || NowIter == _mapScore.end())
    {
        return ;
    }
    if(bNewNote)
    {
        auto  NextIter = NowIter;
        NextIter++;
        NowIter->second.dwPreNum = NextIter->second.dwPreNum;
    }
    NowIter++;
    PreIter++;
    if(dwNowScore > dwPreScore)//增加
    {
        for(auto iter= NowIter;iter != PreIter;iter++)
        {
            iter->second.dwPreNum++;
        }

    }
    else
    {
        for(auto iter= PreIter;iter != NowIter;iter++)
        {
            if(iter->second.dwPreNum <= 1)
            {
                LOG_CRI<< "ERR Data";
                iter->second.dwPreNum = 0;

            }
            else
            {
                iter->second.dwPreNum--;

            }

        }
    }
}

bool  CRankData::InsertPlayerForDB(const SArenaPlayerData *pPlayer)
{
    UINT32 dwScore = pPlayer->stBaseData.dwScore;
    RankNode &rNode = _mapScore[dwScore];
    if(rNode.vecPlayer.size() < pPlayer->stBaseData.dwRanking+1)
    {
        rNode.vecPlayer.resize(pPlayer->stBaseData.dwRanking+1,0);
    }
    if(rNode.vecPlayer[pPlayer->stBaseData.dwRanking] != 0)
    {
        LOG_CRI << rNode.vecPlayer[pPlayer->stBaseData.dwRanking];
        return false;
    }
    rNode.vecPlayer[pPlayer->stBaseData.dwRanking] = pPlayer->qwRoleID;
    return true; 

}
UINT32  CRankData::InsertErrPlayerForDB(const SArenaPlayerData *pPlayer)
{
    UINT32 dwScore = pPlayer->stBaseData.dwScore;
    RankNode &rNode = _mapScore[dwScore];
    rNode.vecPlayer.push_back(pPlayer->qwRoleID);
    return rNode.vecPlayer.size() -1;
}

bool CRankData::CheckPlayer(SArenaPlayerData *pPlayer)
{
    UINT32 dwScore = pPlayer->stBaseData.dwScore;
    RankNode &rNode = _mapScore[dwScore];
    return rNode.vecPlayer[pPlayer->stBaseData.dwRanking] == pPlayer->qwRoleID;

}

void CRankData::SetPreNumAllForDB()
{
    if(_mapScore.empty())
    {
        return ;
    }
    auto iterPre = _mapScore.begin();
    auto iterAfter = iterPre;
    iterAfter++;

    while(iterAfter != _mapScore.end())
    {
        RankNode *preNode = &(iterPre->second);
        RankNode *afterNode= &(iterAfter->second);
        afterNode->dwPreNum = preNode->dwPreNum +preNode->vecPlayer.size();
        iterPre++;
        iterAfter++;
    }
    if(_mapScore.find(0) == _mapScore.end())
    {
        if(iterPre != _mapScore.end())
        {
            RankNode *preNode = &(iterPre->second);
            _mapScore[0].dwPreNum = preNode->dwPreNum + preNode->vecPlayer.size();

        }
    }
}
EArenaLevel CRankData::CalPlayerNewLevel(SArenaPlayerData *pPlayer,/*UINT32 &dwSameDays,*/UINT32 &dwCurRank)
{
    if(pPlayer == NULL)
    {
        return EArenaLevel_NONE;
    }
    //得到总人数
    UINT32 dwTotalSize = GetPlayerSize();
    if(dwTotalSize == 0)
    {
        return EArenaLevel_NONE;
    }
    //升级线
    UINT32 dwUpRank = dwTotalSize*_Config._byLevelUpRate/100;//小于这个值升级
    UINT32 dwDwonRank = dwTotalSize*(100 - _Config._byLevelDwonRate)/100;//大于等于这个值降级
    if(dwTotalSize <= 10)
    {
        dwUpRank = 10;
    }

    UINT32 dwScore = pPlayer->stBaseData.dwScore;
    auto iter = _mapScore.find(dwScore);
    if(iter == _mapScore.end())
    {
        return EArenaLevel_NONE;
    }
    dwCurRank =  iter->second.dwPreNum + pPlayer->stBaseData.dwRanking;
    //现在段位
    EArenaLevel eOldLevel = (EArenaLevel)_Config._id;
    //新段位
    EArenaLevel eNewLevel = eOldLevel;
    if(dwCurRank <= dwUpRank)//升级
    {
        if(_Config._id + 1 < EArenaLevel_END)
        {
            eNewLevel =(EArenaLevel)(_Config._id+1);
        }

    }
    else if(dwCurRank > dwDwonRank)//降级
    {
        if(_Config._id -1  >  EArenaLevel_NONE )
        {
            eNewLevel =(EArenaLevel)(_Config._id - 1);
        }
    }
    /*
       else
       {
       dwSameDays++;
       if( dwSameDays >  _Config._byKeepLevelDays)
       {
       dwSameDays  = 1;
       }
       }
       */
    return eNewLevel;

}
void CRankData::UpdateForCal(map<EArenaLevel,vector<UINT64> > &rmapUpdate,UINT32 dwNow,set<UINT64> &setSame)
{
    //得到总人数
    UINT32 dwTotalSize = GetPlayerSize();
    if(dwTotalSize == 0)
    {
        return ;
    }
    //升级线
    UINT32 dwUpRank = dwTotalSize*_Config._byLevelUpRate/100;//小于这个值升级
    UINT32 dwDwonRank = dwTotalSize*(100 - _Config._byLevelDwonRate)/100;//大于等于这个值降级
    if(dwTotalSize <= 10)
    {
        dwUpRank = 10;
    }
    UINT32 dwCurRank =0;
    for(auto pos =_mapScore.begin();pos != _mapScore.end();pos++)
    {
        RankNode& rNode = (pos->second); 
        vector<UINT64> &rvecPlayer = rNode.vecPlayer;
        for (size_t i = 0; i != rvecPlayer.size();i++)
        {
            //现在段位
            EArenaLevel eOldLevel = (EArenaLevel)_Config._id;
            //新段位
            EArenaLevel eNewLevel = eOldLevel;
            SArenaPlayerData * pPlayer = CArenaManager::GetPlayer(rvecPlayer[i]);
            if(!pPlayer)
            {
                continue;
            }

            if(dwCurRank < dwUpRank)//升级
            {
                if(_Config._id + 1 < EArenaLevel_END)
                {
                    eNewLevel =(EArenaLevel)(_Config._id+1);
                }

            }
            else if(dwCurRank >= dwDwonRank)//降级
            {
                if(_Config._id -1  >  EArenaLevel_NONE )
                {
                    eNewLevel =(EArenaLevel)(_Config._id - 1);
                }
            }

            const ArenaConfig& stArenaConfig =CArenaManager::GetArenaConfig();

            pPlayer->stBaseData.dwLastRank = dwCurRank;
            pPlayer->stBaseData.eLastLevel = eOldLevel;
            if(stArenaConfig.stDelCon.byDelLevel == _Config._id)
            {
                if(dwNow - pPlayer->stBaseData.dwLastFlushTime > stArenaConfig.stDelCon.byDays*24*3600 &&  pPlayer->stBaseData.dwLadderRank >= CArenaManager::LadderRankNoRank)
                {
                    eNewLevel = EArenaLevel_NONE;
                }
            }
            //pPlayer->stBaseData.dwLastLadderRank = pPlayer->stBaseData.dwLadderRank;
            rmapUpdate[eNewLevel].push_back(rvecPlayer[i]);
            dwCurRank++;
            if(eNewLevel ==  eOldLevel)
            {
                setSame.insert(rvecPlayer[i]);
            }
        }
    }
    _mapScore.clear(); 
}

void  CRankData::InsertPlayerForCal(vector<UINT64>& rVec)
{
    for(size_t iter = 0; iter != rVec.size();iter++)
    {
        SArenaPlayerData * pPlayer = CArenaManager::GetPlayer(rVec[iter]);
        if(pPlayer == NULL)
        {
            continue;
        }
        TVecINT32 vecParam;
        vecParam.push_back(pPlayer->stBaseData.eLevel);
        vecParam.push_back((EArenaLevel)_Config._id);

        CUserPtr pUser = CUserMgr::GetUserByUserID(rVec[iter]);
        if(!pUser || (pUser->GetState() != eUserInGame && pUser->GetState() != eUserReplace))
        {
            CUser::AddOffLineEvent(rVec[iter],eEventType_ExperienceLevelChange,vecParam);
        }
        else
        {
            pUser->OnEvent(eEventType_ExperienceLevelChange,vecParam);
        }
        pPlayer->stBaseData.dwRanking  = iter;
        pPlayer->stBaseData.dwScore = 0;
        pPlayer->stBaseData.eLevel = (EArenaLevel)_Config._id;

    }
    _mapScore[0].vecPlayer = rVec;
}

UINT32 CRankData::GetPreNumByScore(UINT32 dwScore)
{
    auto iter = _mapScore.find(dwScore);
    if(iter != _mapScore.end())
    {
        return iter->second.dwPreNum;
    }
    return 0;
}

UINT32 CRankData::GetPlayerSize()
{
    if(_mapScore.empty())
    {
        return 0;
    }
    auto iter = _mapScore.rbegin();
    RankNode *pNode = &(iter->second);  
    return pNode->dwPreNum + pNode->vecPlayer.size();

}
void CRankData::GetPlayerListByRank(TVecUINT64& vecPlayer,UINT32 dwFrom,UINT16 wNum)     
{
    //找到起始节点
    auto iter =  _mapScore.begin();
    while (iter != _mapScore.end())
    {
        if (iter->second.dwPreNum + iter->second.vecPlayer.size() > dwFrom)
        {
            break;
        }
        iter++;

    }
    if(iter == _mapScore.end())
    {
        return ;
    }
    UINT32 dwPos =dwFrom - iter->second.dwPreNum; 
    while(iter != _mapScore.end() && vecPlayer.size() < wNum)
    {
        for(;dwPos != iter->second.vecPlayer.size();dwPos++)
        {
            if(vecPlayer.size() < wNum)
            {
                vecPlayer.push_back(iter->second.vecPlayer[dwPos]);
            }
            else
            {
                break;
            }
        }
        dwPos = 0;
        iter++;
    }
}

UINT32 CRankData::GetRankAward(UINT32 dwRank)
{
    if(dwRank >= _vecRankAward.size())
    {
        return 0;
    }
    return _vecRankAward[dwRank];
}

UINT32   CRankData::GetLevelAward()
{
    return _Config._dwLevelLoot;

}
/*
   UINT32 CRankData::GetSameDaysAward(UINT32 dwDays)
   {
   if(dwDays >= _Config._byKeepLevelDays)
   {
   return _Config._dwKeepLevelLoot; 
   }
   return 0;
   }
   */
void CRankData::ResetConfig(const SArenaCFG *pConfig)
{
    _Config = *pConfig;
    _vecRankAward.clear();
    _vecExtraScore.clear();
    buf::Tokenizer Ranktk(pConfig->_strAwardLoot,',');
    for(size_t i = 0;i < Ranktk.size();i++)
    { 
        _vecRankAward.push_back(atoi(Ranktk[i].c_str())); 
    }
    buf::Tokenizer Extratk(pConfig->_strExtraScore,',');
    for(size_t i = 0;i < Extratk.size();i++)
    { 
        _vecExtraScore.push_back(atoi(Extratk[i].c_str())); 
    }
}

CRankData::CRankData(const SArenaCFG *pConfig):
    _Config(*pConfig)
{
    buf::Tokenizer Ranktk(pConfig->_strAwardLoot,',');
    for(size_t i = 0;i < Ranktk.size();i++)
    { 
        _vecRankAward.push_back(atoi(Ranktk[i].c_str())); 
    }
    buf::Tokenizer Extratk(pConfig->_strExtraScore,',');
    for(size_t i = 0;i < Extratk.size();i++)
    { 
        _vecExtraScore.push_back(atoi(Extratk[i].c_str())); 
    }

}

void CRankData::FindRandom(TVecUINT64 &vecSel,UINT64 qwExtraID,UINT8 byNum)
{
    //得到总数
    UINT32 dwTotalSize = GetPlayerSize();
    TVecUINT64 vecRankSource;
    if(dwTotalSize == 0)
    {
        return ; 
    }
    UINT32 dwStartPos = 0;
    //抽取连续的1000个样本
    if (dwTotalSize > 1000)
    {
        dwStartPos = CRandom::RandInt(0,dwTotalSize-1000);
    }
    GetPlayerListByRank(vecRankSource,dwStartPos,1000);
    if(vecRankSource.empty())
    {
        return ;
    }
    UINT32 dwEndPos = vecRankSource.size();
    while(dwEndPos >0 && byNum > 0)
    {
        UINT32 dwPos = CRandom::RandInt(0,dwEndPos-1);
        UINT64 qwRoleID = vecRankSource[dwPos];
        if(qwExtraID != qwRoleID)
        {
            byNum--;
            vecSel.push_back(qwRoleID);
        }
        dwEndPos--;
        swap(vecRankSource[dwPos],vecRankSource[dwEndPos]);
    }
}

UINT32 CRankData::GetExtraScore(UINT8 byLevel)
{
    if(byLevel == 0)
    {
        byLevel = 1;//无段位，按黑铁处理
    }
    if(_Config._id >= byLevel)
    {
        return 0;
    }
    UINT8 byDiff = byLevel - _Config._id -1;

    if(_vecExtraScore.size() <= byDiff)
    {
        return 0;
    }
    return _vecExtraScore[byDiff];
}
