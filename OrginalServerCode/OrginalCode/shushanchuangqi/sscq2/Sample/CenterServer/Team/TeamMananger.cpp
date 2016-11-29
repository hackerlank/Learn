#include "TeamMananger.h"
#include "CenterConfig.h"
#include "TeamGSS.h"
#include "Game2CenterTeamS.h"
#include "User.h"
#include "UserMgr.h"
#include "SysMsgDefine.h"

#include "Protocols.h" // XXX: for g_GlobalChatProtS;
#include "Parameter.h"
CTeamManager g_TeamManager;

bool CTeamInfo::CanJoin()
{
    return  GetFreePos() != ERRPOS;
}

UINT64  CTeamInfo::GetBeautyOwer()
{
    return _qwBeautyOwner;
}

void CTeamInfo::SetBeautyOwer( UINT64 qwBeautyOwer)
{
    _qwBeautyOwner = qwBeautyOwer;
}

void CTeamInfo::FindBeautyOwer()
{
    _qwBeautyOwner = 0;
    if (_vecMems.empty())
        return;

    CMemInfo * pMember = g_TeamManager.GetRoleInfoByID(GetLeaderID());
    if(NULL == pMember)
    {
        LOG_CRI <<"Can not Find Player:"<< GetLeaderID();
        return ;
    }

    if(pMember->IsHaveBeauty())
        _qwBeautyOwner = GetLeaderID();
}

UINT8 CTeamInfo::GetFreePos()
{
    if(_setFreePos.empty())
        return ERRPOS;
    return *(_setFreePos.begin());
}

CTeamInfo::CTeamInfo()
{
    _dwTeamID = 0;
    _wDgnType = 0;
    _bBattle = false;
    _qwBeautyOwner = 0;

}

CTeamInfo::CTeamInfo(UINT32 dwTeamID,UINT16 wDgnType)
{
    _dwTeamID = dwTeamID;
    _wDgnType = wDgnType;
    _bBattle = false;
    _qwBeautyOwner = 0;
    const SDungeonCFG *pCfg = g_TeamManager.GetDgnConfigByType(_wDgnType);
    if(pCfg == NULL)
    {
        LOG_CRI << "Can not find Dgn  config : "<<_wDgnType;
        return  ;
    }
    for(UINT8 pos = 0 ; pos < pCfg->_Max ;pos++)
    {
        _setFreePos.insert(pos);
    }


}

UINT64 CTeamInfo::GetLeaderID()
{
    if(_vecMems.empty())
        return 0;
    return _vecMems[0];
}

void  CTeamInfo::ChangLeader(UINT64 qwNewLeader)
{
    UINT32 dwIndex = 0;
    for(dwIndex = 0; dwIndex != _vecMems.size(); dwIndex++)
    {
        if(_vecMems[dwIndex] == qwNewLeader)
            break;
    }
    if(dwIndex != 0 && dwIndex != _vecMems.size())
        swap(_vecMems[0],_vecMems[dwIndex]);

    CMemInfo * pBeautyMemInfo = g_TeamManager.GetRoleInfoByID(qwNewLeader);
    if(!pBeautyMemInfo)
        return;

    if(pBeautyMemInfo->IsHaveBeauty())
        SetBeautyOwer(qwNewLeader);
    else
        SetBeautyOwer(0);
}

void CTeamInfo::SetSetting(const TeamSetting& stSetting)
{
    _stSetting = stSetting;
}

const TeamSetting& CTeamInfo::GetSetting()
{
    return _stSetting;
}

UINT8 CTeamInfo::PlayerJoin(UINT64 qwRoleID)
{
    _vecMems.push_back(qwRoleID);
    UINT8 byPos = GetFreePos();
    _setFreePos.erase(byPos);
    return byPos;
}
bool CTeamInfo::GetTeamInfoForList(TeamInfoForList &Info)
{
    Info.TeamID = _dwTeamID;
    Info.DgnType =  _wDgnType;
    UINT64 qwLeaderID = GetLeaderID();
    CMemInfo * pMember = g_TeamManager.GetRoleInfoByID(qwLeaderID);
    if(NULL == pMember)
    {
        LOG_CRI <<"Can not Find Leader:"<< qwLeaderID;
        return false;

    }
    Info.bySize = GetSize();
    Info.stLeader = pMember->GetMainFighter();
    Info.strLeaderName = pMember->GetName();
    Info.stSetting = _stSetting;
    if(Info.stSetting.dwPassWord != 0)
        Info.stSetting.dwPassWord = 1;
    if(Info.stLeader == NULL)
    {
        LOG_CRI <<"Can not Find Leader desc:"<< qwLeaderID;
        return false;
    }
    return true;

}

UINT8 CTeamInfo::PlayerLeave(UINT64 qwRoleID,UINT8 byPos)//返回0：正常，返回1：队长变更：返回2：队伍空
{

    size_t pos = 0;
    bool bFind = false;

    for(pos = 0; pos != _vecMems.size(); pos++)
    {
        if(_vecMems[pos] == qwRoleID)
        {
            _vecMems.erase(_vecMems.begin() + pos);
            bFind = true;
            break;
        }
    }
    if(!bFind)
        LOG_CRI << "ERR Member";
    else
        _setFreePos.insert(byPos);

    //重新设置阵灵
    if(GetBeautyOwer() == qwRoleID)
        FindBeautyOwer();

    if(_vecMems.empty())
        return 2;

    if(pos == 0)
        return 1;

    return  0;
}

bool  CTeamInfo::IsMember(UINT64 qwRoleID)
{
    size_t pos = 0;
    bool bFind = false;
    for(;pos != _vecMems.size();pos++)
    {
        if(_vecMems[pos] == qwRoleID)
        {
            bFind = true;
            break;
        }
    }
    return bFind;
}

CMemInfo::CMemInfo()
{
    _qwRoleID = 0;
    _dwTeamID = 0;
    _eStatus = EMEMBER_NONE;

}

void CMemInfo::Reset()
{
    _eStatus = EMEMBER_NONE;
}

string CMemInfo::GetName()
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(_qwRoleID);
    if(pUser == NULL)
    {
        return "";
    }
    return pUser->GetUserName();

}

CommonFighterPtr CMemInfo::GetMainFighter()
{
    for (auto iter = _vecFigthers.begin();iter != _vecFigthers.end();iter++)
    {
        TeamFighterPtr &pFighter = *iter;
        if(pFighter->GetClassType() == eType_CommonFighter) 
        {
            CommonFighterPtr pMainFighter =  dynamic_pointer_cast<CommonFighter>(pFighter); 
            if(pMainFighter == NULL)
            {
                LOG_CRI << "Trans CommonFighterPtr ERR";
                return NULL;
            }
            if(pMainFighter->byMain > 0)
            {
                return pMainFighter;
            }
        }
    }
    return NULL;
}

const vector<UINT32>* CTeamManager::GetTeamByType(UINT16 wDgnType)
{
    auto iter = _mapType.find(wDgnType);
    if(iter == _mapType.end())
    {
        return NULL;
    }
    return &(iter->second);
}

CTeamInfo* CTeamManager::GetTeamInfoByID(UINT32 dwTeamID)
{
    auto iter = _mapTeam.find(dwTeamID);
    if(iter == _mapTeam.end())
    {
        return NULL;
    }
    return &(iter->second);
}

CMemInfo * CTeamManager::GetRoleInfoByID(UINT64 qwRoleID)
{
    auto iter = _mapRole.find(qwRoleID);
    if( iter == _mapRole.end())
    {
        return NULL;
    }
    return &(iter->second);
}

bool CMemInfo::IsHaveBeauty() const
{

    for(auto iter = _vecFigthers.begin();iter != _vecFigthers.end();iter++)
    {
        if((*iter)->pFeature->GetClassType() == NBattleGS::eType_SBeautyFeature)
            return true;
    }
    return false;
}


void CTeamManager::OpenQueryRoom(UINT64 qwRoleID,UINT16 wDgnType)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(pUser == NULL || GetDgnConfigByType(wDgnType) == NULL)
    {
        return ;
    }
    UINT16 wOldDgnType = pUser->GetQueryRoom();
    if(wOldDgnType != 0)
    {
        _mapQuery[wOldDgnType].erase(qwRoleID);
    }
    pUser->SetQueryRoom(wDgnType);
    _mapQuery[wDgnType].insert(qwRoleID);
}

void CTeamManager::CloseQueryRoom(UINT64 qwRoleID)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(pUser == NULL)
    {
        return ;
    }
    UINT16 wDgnType = pUser->GetQueryRoom();
    if(wDgnType == 0)
    {
        return ;
    }
    pUser->SetQueryRoom(0);
    _mapQuery[wDgnType].erase(qwRoleID);
}

void CTeamManager::UpdateQueryRoom(TeamListOP eOp,const TeamInfoForList &Info)
{
    set<UINT64> &rSet = _mapQuery[Info.DgnType];
    if(eOp != ETeam_Del)
    {
        TVecTeamInfoForList vecInfo;
        vecInfo.push_back(Info);
        for(auto it = rSet.begin();it != rSet.end();)
        {
            UINT64 qwRoleID = *it;
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            if(pUser == NULL)
            {
                it = rSet.erase(it);
                continue;

            }
            g_CTeamGSS.SendClt_UpdateTeamInfoList(&qwRoleID,1,eOp,vecInfo);
            ++it;

        }

    }
    else
    {
        for(auto it = rSet.begin();it != rSet.end();)
        {
            UINT64 qwRoleID = *it;
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            if(pUser == NULL)
            {
                it = rSet.erase(it);
                continue;

            }
            g_CTeamGSS.SendClt_TeamDelForList(&qwRoleID,1,Info.TeamID);
            ++it;

        }

    }
}

const SDungeonCFG * CTeamManager::GetDgnConfigByType(UINT16 wDgnType)
{
    auto iter = _mapConfig.find(wDgnType);
    if( iter == _mapConfig.end())
    {
        return NULL;
    }
    return &(iter->second); 
}

bool CTeamManager::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/Dungeon.xml";
    CDungeonLoader oDungeonLoader;
    if(!oDungeonLoader.LoadData(strPath))
    {
        LOG_CRI << "oDungeonLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oDungeonLoader._vecData.size(); ++i)
    {
        SDungeonCFG* pDungeonCFG = oDungeonLoader._vecData[i];
        if(pDungeonCFG->_TYPE == TeamDGN) 
        {
            _mapConfig[pDungeonCFG->_ID] = *pDungeonCFG;
        }

    }
    return true;
}

UINT32  CTeamManager::CreateTeam(UINT64 qwRoleID, UINT16 wDgnType, const TeamSetting& stSetting, TVecTeamFighter& vecFighter)
{
    UINT32 dwTeamID = ++_dwTeamBase;

    CTeamInfo stTeamInfo(dwTeamID,wDgnType);
    stTeamInfo.SetSetting(stSetting);

    CMemInfo &stInfo = _mapRole[qwRoleID];
    stInfo.SetTeamID(dwTeamID);
    stInfo.SetRoleID(qwRoleID);
    stInfo.SetFighters(vecFighter);
    stInfo.SetPos(stTeamInfo.PlayerJoin(qwRoleID));

    //设置默认美女
    if(stInfo.IsHaveBeauty())
        stTeamInfo.SetBeautyOwer(qwRoleID);

    _mapTeam[dwTeamID] = stTeamInfo;
    _mapType[wDgnType].push_back(dwTeamID);

    //推送队伍信息
    NoticeTeamInfo(dwTeamID);
    SynPlayerTeam(qwRoleID,true);

    TeamInfoForList Info;
    if(stTeamInfo.GetTeamInfoForList(Info))
        UpdateQueryRoom(ETeam_Create,Info);

    LOG_INF << qwRoleID << " CreateTeam " << dwTeamID;

    return dwTeamID;
}

bool CTeamManager::JoinTeam(UINT64 qwRoleID,CTeamInfo* pTeam,TVecTeamFighter& vecFighter)
{
    if(!pTeam)
        return false;

    CMemInfo &stInfo =  _mapRole[qwRoleID];
    stInfo.SetRoleID(qwRoleID);
    stInfo.SetTeamID(pTeam->GetTeamID());
    stInfo.SetFighters(vecFighter);
    stInfo.SetPos(pTeam->PlayerJoin(qwRoleID));

    NoticeTeamInfo(pTeam->GetTeamID()); 
    SynPlayerTeam(qwRoleID,true);
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(pUser)
    {
        const TVecUINT64& rvecUserID = pTeam->GetMemBers();
        g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(rvecUserID.data(), rvecUserID.size(), eMsgTeamComeIn, BuildStrVec(static_cast<UINT32>(pUser->GetQuality()), pUser->GetUserName()));
    }
    LOG_INF << qwRoleID << " JoinTeam " << pTeam->GetTeamID();
    return true;
}

void CTeamManager::NoticeTeamInfo(UINT32 dwTeamID,UINT64 qwRoleID /* = 0 */)
{
    CTeamInfo* pTeam = GetTeamInfoByID(dwTeamID);
    if(pTeam == NULL)
    {
        LOG_CRI << "Can NOT Find Team";
        return ;
    }

    if(qwRoleID != 0 && !pTeam->IsMember(qwRoleID))
    {
        LOG_CRI << "NO mem For Team";
        return ;
    }

    const TVecUINT64& rvecMem = pTeam->GetMemBers();
    if(rvecMem.empty())
    {
        LOG_CRI <<"Team  is Empty";
        return ;
    }

    TeamInfo stInfo;

    stInfo.TeamID       = pTeam->GetTeamID();
    stInfo.DgnType      = pTeam->GetDgnType();
    stInfo.TeamLeader   = pTeam->GetLeaderID(); 
    stInfo.qwPetOwner   = pTeam->GetBeautyOwer();
    stInfo.stSetting    = pTeam->GetSetting();

    for(auto & rRoleID : rvecMem)
    {
        CMemInfo * pMem = GetRoleInfoByID(rRoleID); 
        if(NULL == pMem)
        {
            LOG_CRI << "CAN NOT find Member";
            continue;
        }

        TeamMember stMem;
        stMem.qwRoleID      = rRoleID;
        stMem.byPos         = pMem->GetPos(); 
        stMem.eStatus       = pMem->GetStatus();
        stMem.vecFighter    = pMem->GetFighters();
        stMem.strName       = pMem->GetName();

        CUserPtr pUser      = CUserMgr::GetUserByUserID(rRoleID);
        if(pUser)
        {
            stMem.byVIPLevel         = pUser->GetVIPLevel();
            stMem.oPlatformParam     = pUser->GetCurPlatform();
        }

        stInfo.vecMember.push_back(stMem);
        LOG_WRN << stMem.strName << ": " << stMem.vecFighter.size() << ".";
    }
    if(qwRoleID != 0)
        g_CTeamGSS.SendClt_TeamInfoUpdate(&qwRoleID,1,stInfo);
    else
        g_CTeamGSS.SendClt_TeamInfoUpdate(&rvecMem[0],rvecMem.size(),stInfo);
}

void CTeamInfo::SendMsgForAll(const string& strMsg)
{
    const TVecUINT64& rvecMem = GetMemBers();
    for(auto it =  rvecMem.begin(); it != rvecMem.end();it++)
    {
        CUserPtr pUser = CUserMgr::GetUserByUserID(*it);
        if(pUser)
        {
            pUser->SendPkg(strMsg);
        }

    }
}

void CTeamInfo::ChangeFreePos(UINT8 byPos1,UINT8 byPos2)
{
    bool bFree1 = (_setFreePos.find(byPos1) == _setFreePos.end());
    bool bFree2 = (_setFreePos.find(byPos2)  == _setFreePos.end());
    if( (bFree1 && bFree2) || (!bFree1 && !bFree2))
    {
        return ;
    }
    if(bFree1)
    {
        _setFreePos.erase(byPos2);
        _setFreePos.insert(byPos1);
    }
    else
    {
        _setFreePos.erase(byPos1);
        _setFreePos.insert(byPos2);

    }
}

void CTeamManager::SynPlayerTeamForJump(UINT64 qwRoleID)
{
    CMemInfo *pMember = GetRoleInfoByID(qwRoleID);
    if(NULL == pMember)
        return ;
    SynPlayerTeam(qwRoleID,true);
}

void CTeamManager::SynPlayerTeam(UINT64 qwRoleID,bool bEnter)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(pUser == NULL)
        return ;

    UINT32 dwServerID = pUser->GetGameSvrID();  
    g_Game2CenterTeamS.SendSvr_SynTeam(&dwServerID, 1, qwRoleID, bEnter ? EPlayerEnterTeam : EPlayerLeaveTeam);
}

bool CTeamManager::ResetFighter(CMemInfo *pMember,UINT8 byPos,const NTeamGS::CommonFighterPtr& pNewFighter)
{
    if( NULL == pMember)
    {
        LOG_CRI << "Can not Find member!";
        return false;
    }
    CTeamInfo* pTeam = GetTeamInfoByID(pMember->GetTeamID());
    if(pTeam == NULL)
    {
        LOG_CRI << "Can NOT Find Team";
        return false;
    }
    TVecTeamFighter& rvecFighter = pMember->GetFighters();
    for (auto pos = rvecFighter.begin();pos != rvecFighter.end();pos++)
    {
        TeamFighterPtr& pFighter = *pos;
        if(pFighter->byPos == byPos)
        {
            rvecFighter.erase(pos);
            break;
        }
    }
    pNewFighter->byPos = byPos;
    rvecFighter.push_back(pNewFighter);
    NoticeTeamInfo(pMember->GetTeamID());
    return true;
}

bool CTeamManager::PlayerLeave(CMemInfo *pMember)
{
    if(NULL == pMember)
    {
        LOG_CRI << "Can not Find member!";
        return false;
    }
    UINT32 dwTeamID = pMember->GetTeamID();
    LOG_INF << pMember->GetRoleID() << " Leave Team " << dwTeamID;
    CTeamInfo* pTeam = GetTeamInfoByID(dwTeamID);
    if(NULL == pTeam)
    {

        LOG_CRI << "Can not Find Team!";
        return false;
    }   
    UINT64 qwRoleID = pMember->GetRoleID();
    _mapRole.erase(qwRoleID);
    SynPlayerTeam(qwRoleID,false);
    UINT8 byResult = pTeam->PlayerLeave(qwRoleID,pMember->GetPos());
    if(byResult == 2)
    {
        //队伍解散
        DisMiss(dwTeamID);
        return true;
    }
    else
    {
        NoticeTeamInfo(dwTeamID);
        TeamInfoForList Info;
        if(pTeam->GetTeamInfoForList(Info))
            UpdateQueryRoom(ETeam_UpDate,Info); 
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if(pUser)
        {
            const TVecUINT64& rvecUserID = pTeam->GetMemBers();
            g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(rvecUserID.data(), rvecUserID.size(), eMsgTeamGetOut, BuildStrVec(static_cast<UINT32>(pUser->GetQuality()), pUser->GetUserName()));
        }
        return true;
    }


}

void CTeamManager::PlayerOffLine(UINT64 qwRoleID)
{
    PlayerLeave(qwRoleID);
    CloseQueryRoom(qwRoleID);
}

bool CTeamManager::PlayerLeave(UINT64 qwRoleID)
{
    CMemInfo *pMember = GetRoleInfoByID(qwRoleID);
    if(NULL == pMember)
    {
        return false;
    }
    return PlayerLeave(pMember);
}

void  CTeamManager::DisMiss(UINT32 dwTeamID)
{
    //处理房间玩家
    CTeamInfo* pTeam = GetTeamInfoByID(dwTeamID);
    if(NULL == pTeam)
    {

        LOG_CRI << "Can not Find Team!";
        return ;
    }
    const TVecUINT64& rMembers = pTeam->GetMemBers();
    for(auto pos = rMembers.begin();pos != rMembers.end();pos++)
    {
        UINT64 qwRoleID = *pos;
        _mapRole.erase(qwRoleID);
        SynPlayerTeam(qwRoleID,false);
        g_CTeamGSS.SendClt_NoticeKicked(&qwRoleID,1,dwTeamID);
    }
    //解散队伍
    UINT16 wType = pTeam->GetDgnType();
    _mapTeam.erase(dwTeamID);
    auto pos = _mapType.find(wType);
    if(pos == _mapType.end())
    {
        LOG_CRI << "Can find team from Type";
        return ;
    }
    bool bFind = false;
    vector<UINT32> &rvecType = pos->second;
    for(auto iter = rvecType.begin();iter != rvecType.end();iter++)
    {
        if(dwTeamID == *iter)
        {
            rvecType.erase(iter);
            bFind = true;
            break;
        }
    }
    if(!bFind)
        LOG_CRI << "Can find team from ListType";

    LOG_INF <<"Team NUmber IS " << _mapTeam.size(); 
    LOG_INF << " Team " << dwTeamID << "DisMiss";

    TeamInfoForList Info;
    Info.TeamID     = dwTeamID;
    Info.DgnType    = wType;
    Info.stLeader   = NULL;
    UpdateQueryRoom(ETeam_Del,Info);
}

void  CTeamManager::ResetTeam(CTeamInfo* pTeam) 
{
    if(NULL == pTeam)
    {

        LOG_CRI << "Can not Find Team!";
        return ;
    } 
    //重置
    const TVecUINT64& rMembers = pTeam->GetMemBers();
    for(auto pos = rMembers.begin();pos != rMembers.end();pos++)
    {
        CMemInfo * pMem =  GetRoleInfoByID(*pos);
        if(pMem == NULL)
        {
            LOG_CRI << "Can not Find Memeber";
            continue;
        }
        pMem->Reset();
    }
    NoticeTeamInfo(pTeam->GetTeamID()); 

}

void  CTeamManager::ResetTeam(UINT32 dwTeamID) 
{
    CTeamInfo* pTeam = GetTeamInfoByID(dwTeamID);
    if(NULL == pTeam)
    {
        LOG_CRI << "Can not Find Team!";
        return ;
    } 
    ResetTeam(pTeam);
}

bool CTeamManager::PlayerReady(CMemInfo *pMember)
{
    if( NULL == pMember)
        LOG_CRI << "CMemInfo * Is NULL";
    pMember->SetStatus(EMEMBER_READY);
    NoticeTeamInfo(pMember->GetTeamID()); 
    return true;
}

bool CTeamManager::PlayerCancelReady(CMemInfo *pMember)
{
    if( NULL == pMember)
        LOG_CRI << "CMemInfo * Is NULL";
    pMember->SetStatus(EMEMBER_NONE);
    NoticeTeamInfo(pMember->GetTeamID()); 
    return true;
}

// 计算站位
UINT8 CTeamManager::CalFighterPos(UINT64 qwFighterID, CMemInfo *pMember)
{
    if(pMember == NULL)
    {
        LOG_CRI <<"Team is NULL";
        return ERRPOS;
    }

    //第几行
    UINT8 byPlayerPos = pMember->GetPos();
    for(auto& pFighter : pMember->GetFighters())
    {
        if(pFighter->GetClassType() == eType_CommonFighter)
        {
            CommonFighterPtr pCommon = dynamic_pointer_cast<CommonFighter>(pFighter);
            if(qwFighterID ==  pCommon->qwInstID)
            {
                LOG_INF << "byPlayerPos is " << byPlayerPos << ", "
                    "Fighter Pos is: 1 " << byPlayerPos * (MAXHERO + 1) + pCommon->byPos << ".";
                UINT8 byPos = (MAXHERO - byPlayerPos) + pCommon->byPos*(MAXHERO+1);
                LOG_INF << "byPos = " << static_cast<UINT32>(byPos) << ", "
                    "byPlayerPos is "<< static_cast<UINT32>(byPlayerPos) << ", "
                    "Fighter Pos is " << static_cast<UINT32>(byPlayerPos * (MAXHERO + 1) + pCommon->byPos);
                return byPos;
            }
        }
    }
    return ERRPOS;
}

void CTeamManager::ResetNewDgn(CTeamInfo*pTeam,UINT16 wNewDgnType)
{
    if(NULL == pTeam)
    {
        LOG_CRI << "NULL TEAM";
    }
    UINT32 dwTeamID = pTeam->GetTeamID();
    auto iter = _mapType.find(pTeam->GetDgnType());
    if(iter == _mapType.end())
        LOG_CRI <<" ERR! CAN NOT FIND DgnType";
    else
    {
        bool bFind = false;
        for(auto it = iter->second.begin();it != iter->second.end();)
        {
            if( *it == dwTeamID)
            {
                it =iter->second.erase(it);
                bFind = true;
                break;
            }
        }
        if(!bFind)
            LOG_CRI <<" ERR! CAN NOT FIND Old Team";
    }
    _mapType[wNewDgnType].push_back(dwTeamID);
    pTeam->SetDgnType(wNewDgnType);
    ResetTeam(pTeam);
}

void CTeamManager::SetRewardRate(UINT32 dwRewardRate)
{
    _dwRewardRate = dwRewardRate;
}

UINT32 CTeamManager::GetRewardRate() const
{
    return _dwRewardRate;
}

UINT32 CTeamManager::GetRewardRateByPerson(UINT8 byNum) const
{
    switch (byNum)
    {
        case 2:
            {
              return SParamConfig::wTeamBattleAward2 > 10000 ? SParamConfig::wTeamBattleAward2 : 10000;
            };
            break;
        case 3:
            {
               return SParamConfig::wTeamBattleAward3 > 10000 ? SParamConfig::wTeamBattleAward3 :10000;
            }
            break;
        default:
            break;
    }
    return 10000;

}

