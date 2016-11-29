
#include "stdafx.h"
#include "Protocols.h"
#include "GodMonsterMgr.h"
#include "GuildUserMgr.h"
#include "GuildUser.h"
#include "GuildMgr.h"
#include "SystemMail.h" 
#include "Tokenizer.h"
#include "GodMonsterUser.h"
#include "PHPProtS.h"
//////////////////////////
const static UINT32 wMailID = 528;
const static UINT32 wMailIDForGuild = 532;
const static UINT32 wMailIDForPerson = 530;
const static UINT32 wContentID = 529;
const static UINT32 wContentIDForGuild = 533;
const static UINT32 wContentIDForPerson = 531;
CGodMonsterMgr g_GodMonsterMgr;

bool CGodMonsterMgr::Init()
{
    UINT64 qwMonsterID = 0;
    GodMonsterPtr pMonster(new CGodMonster(qwMonsterID));
    if(!pMonster)
    {
        LOG_INF <<" (0)pMonster new Err.";
        return false;
    }
    auto it = _mapID2Monster.find(qwMonsterID);
    if(it == _mapID2Monster.end())
        if(!_mapID2Monster.insert(make_pair(qwMonsterID,pMonster)).second)
            return false;
    if(!LoadConfig())
        return false;
    return true;
}

CGodMonsterMgr::CGodMonsterMgr()
{
    _dwBeginTime = 0;
    _dwEndTime = 0;
    _dwAlarmTime = 0;
    _bInit = true;
    _eState = eNone;
}

bool CGodMonsterMgr::LoadConfig()
{
    if(!LoadMonsterConfig())
    {
        LOG_CRI << " Load GodMonsterConfig Err.";
        return false;
    }
    if(!LoadMonsterDayPkg())
    {
        LOG_CRI << " Load GodMonsterDayPkg Err.";
        return false;
    }
    if(!LoadMonsterPersonPkg())
    {
        LOG_CRI << " Load GodMonsterPersonPkg Err.";
        return false;
    }
    if(!LoadMonsterGuildPkg())
    {
        LOG_CRI << " Load GodMonsterGuildPkg Err.";
        return false;
    }
    if(!LoadLimitPrizeConfig())
    {
        LOG_CRI << " Load GodMonsterLimitPrize Err.";
        return false;
    }
    return true;
}

bool CGodMonsterMgr::LoadMonsterConfig()
{
    string strPath = Config._strConfigDir + "Conf/Table/GodMonster.xml";
    CGodMonsterLoader  oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oGodMonster.LoadData fails! Path: " << strPath;
        return false;
    }
    TMapID2ConfigPtr pMap;
    //LOG_CRI <<"=====LoadMonsterConfig Begin======";
    for(size_t i = 0; i < oLoader._vecData.size(); ++i)
    {
        SGodMonsterCFG* p = oLoader._vecData[i];
        if(!p)
        {
            LOG_CRI << "Load GodMonsterCFG Err.";
            return false;
        }
        GodMonsterCFGPtr pEx(new SGodMonsterCFGEx());
        if(pEx)
        {
            pEx->byID = p->_ID;
            pEx->wFieldDown = p->_FieldDown;
            pEx->wFieldUp = p->_FieldUp;
            ParsePrize(p->_Content,pEx->vecItems);
            pMap.insert(make_pair(pEx->byID,pEx));
            //LOG_CRI<<"ID="<<pEx->byID<<",wField["<<pEx->wFieldDown<<","<<pEx->wFieldUp<<").";

        }
    }
   _mapType2MapConfig.insert(make_pair(eGodMonsterConfig,pMap));
    //LOG_CRI <<"=====LoadMonsterConfig End======";
    return true;
}

bool CGodMonsterMgr::LoadMonsterDayPkg()
{
    string strPath = Config._strConfigDir + "Conf/Table/GodMonsterDayPkg.xml";
    CGodMonsterDayPkgLoader  oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oGodMonsterDayPkg.LoadData fails! Path: " << strPath;
        return false;
    }
    TMapID2ConfigPtr pMap;
    //LOG_CRI <<"=====LoadMonsterDayPkg Begin======";
    for(size_t i = 0; i < oLoader._vecData.size(); ++i)
    {
        SGodMonsterDayPkgCFG* p = oLoader._vecData[i];
        if(!p)
        {
            LOG_CRI << "Load GodMonsterDayPkgCFG Err.";
            return false;
        }
        GodMonsterCFGPtr pEx(new SGodMonsterCFGEx());
        if(pEx)
        {
            pEx->byID = p->_ID;
            pEx->dwDayScore = p->_DayScore;
            ParsePrize(p->_Content,pEx->vecItems);
            pMap.insert(make_pair(pEx->byID,pEx));
            //LOG_CRI<<"ID="<<pEx->byID<<",dwDayScore="<<pEx->dwDayScore;
        }
    }
   _mapType2MapConfig.insert(make_pair(eGodMonsterDayPkg,pMap));
    //LOG_CRI <<"=====LoadMonsterDayPkg End======";
    return true;
}

bool CGodMonsterMgr::LoadMonsterPersonPkg()
{
    string strPath = Config._strConfigDir + "Conf/Table/GodMonsterPersonPkg.xml";
    CGodMonsterPersonPkgLoader  oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oGodMonsterPersonPkg.LoadData fails! Path: " << strPath;
        return false;
    }
    TMapID2ConfigPtr pMap;
    //LOG_CRI <<"=====LoadMonsterPersonPkg Begin======";
    for(size_t i = 0; i < oLoader._vecData.size(); ++i)
    {
        SGodMonsterPersonPkgCFG* p = oLoader._vecData[i];
        if(!p)
        {
            LOG_CRI << "Load GodMonsterPersonPkgCFG Err.";
            return false;
        }
        GodMonsterCFGPtr pEx(new SGodMonsterCFGEx());
        if(pEx)
        {
            pEx->byID = p->_ID;
            pEx->wFieldDown = p->_FieldDown;
            pEx->wFieldUp = p->_FieldUp;
            ParsePrize(p->_Content,pEx->vecItems);
            pMap.insert(make_pair(pEx->byID,pEx));
            //LOG_CRI<<"ID="<<pEx->byID<<",wField["<<pEx->wFieldDown<<","<<pEx->wFieldUp<<").";
        }
    }
   _mapType2MapConfig.insert(make_pair(eGodMonsterPersonRank,pMap));
    //LOG_CRI <<"=====LoadMonsterPersonPkg End======";
    return true;
}

bool CGodMonsterMgr::LoadMonsterGuildPkg()
{
    string strPath = Config._strConfigDir + "Conf/Table/GodMonsterGuildPkg.xml";
    CGodMonsterGuildPkgLoader  oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oGodMonsterGuildPkg.LoadData fails! Path: " << strPath;
        return false;
    }
    TMapID2ConfigPtr pMap;
    //LOG_CRI <<"=====LoadMonsterGuildPkg Begin======";
    for(size_t i = 0; i < oLoader._vecData.size(); ++i)
    {
        SGodMonsterGuildPkgCFG* p = oLoader._vecData[i];
        if(!p)
        {
            LOG_CRI << "Load GodMonsterGuildPkgCFG Err.";
            return false;
        }
        GodMonsterCFGPtr pEx(new SGodMonsterCFGEx());
        if(pEx)
        {
            pEx->byID = p->_ID;
            pEx->wFieldDown = p->_FieldDown;
            pEx->wFieldUp = p->_FieldUp;
            ParsePrize(p->_Content,pEx->vecItems);
            pMap.insert(make_pair(pEx->byID,pEx));
            //LOG_CRI<<"ID="<<pEx->byID<<",wField["<<pEx->wFieldDown<<","<<pEx->wFieldUp<<").";
        }
    }
   _mapType2MapConfig.insert(make_pair(eGodMonsterGuildRank,pMap));
    //LOG_CRI <<"=====LoadMonsterGuildPkg End======";
    return true;
}

bool CGodMonsterMgr::LoadLimitPrizeConfig()
{
    string strPath = Config._strConfigDir + "Conf/Table/GodMonsterLimitPrize.xml";
    CGodMonsterLimitPrizeLoader  oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oGodMonsterLimitPrize.LoadData fails! Path: " << strPath;
        return false;
    }
    //LOG_CRI<<"==============LimitPrizeBegin===========";
    for(size_t i = 0; i < oLoader._vecData.size(); ++i)
    {
        SGodMonsterLimitPrizeCFG* p = oLoader._vecData[i];
        if(!p)
        {
            LOG_CRI << "Load GodMonsterLimitPrizeCFG Err.";
            return false;
        }
        GodMonsterLimitPrizeCFGPtr pEx(new SGodMonsterLimitPrizeCFGEx());
        if(pEx)
        {
            //LOG_CRI<<"LimitID="<<pEx->wID;
            pEx->wID = p->_ID;
            pEx->wCurPrice = p->_CurPrice;
            pEx->fDiscount = p->_Discount;
            pEx->wOrigPrice = p->_OrigPrice;
            pEx->byCond = p->_Cond;
            pEx->byNum = p->_Num;
            pEx->dwDevote = p->_Devote;
            ParsePrize(p->_Content,pEx->vecItems);
            _mapID2LimitPrize.insert(make_pair(pEx->wID,pEx));
        }
    }
    //LOG_CRI<<"==============LimitPrizeEnd===========";
    return true;
}
bool CGodMonsterMgr::ParsePrize(string& strContent, TVecItemGenInfo& vecItem)
{
    Tokenizer tk(strContent,"|");
    for(UINT8 byIndex=0; byIndex<tk.size(); ++byIndex)
    {
        Tokenizer tkPrize(tk[byIndex],",");
        SItemGenInfo sItem;
        sItem.wItemID = atoi(tkPrize[0].c_str());
        sItem.dwCount = atoi(tkPrize[1].c_str());
        //LOG_CRI<<"ItemID="<<sItem.wItemID<<",Count="<<sItem.dwCount;
        vecItem.push_back(sItem);
    }
    return true;
}

void CGodMonsterMgr::LoadFromDB()
{
    g_Center2DBCommC.Send_GetGodMonsterInfo([](UINT8 byRet_,const NGodMonsterProt::TVecGuildUser2DB& vecUser)
            {
                 if(byRet_ == 0)
                 {
                    g_GodMonsterMgr.Load(vecUser);
                 }
            });
}
void CGodMonsterMgr::Load(const TVecGuildUser2DB& vecUser)
{
    LOG_INF <<"GodMonster Load Begin!";
    for(auto it=vecUser.begin(); it!=vecUser.end(); ++it)
    {
         if(!InitMonsterUser(*it))
         {
             LOG_INF <<"qwRoleID(" << it->qwRoleID<<"),qwGuildID(" << it->qwGuildID<<") err.";
         }
    }
    //加载玩家的限购礼包信息
    CLimitPrizeMgr::Instance().LoadFromDB();
}

bool CGodMonsterMgr::InitMonsterUser(const SGuildUser2DB& rDBUser)
{
    UINT64 qwGuildID = rDBUser.qwGuildID;
    UINT64 qwRoleID = rDBUser.qwRoleID;
    if(qwGuildID == 0)
    {
        LOG_INF << "qwRoleID(" <<qwRoleID<<") not join Guild";
        _setUser.insert(qwRoleID);
    }
    GodMonsterPtr pMonster = NULL;
    if(!CreateGuild(qwGuildID,pMonster))
        return false;
    GodMonsterUserPtr pUser(new CGodMonsterUser(qwRoleID));
    if(!pUser)
    {
        LOG_INF <<"New User err.";
        return false;
    }
    pUser->LoadFromDB(rDBUser);
    pMonster->AddUser(pUser);
    OnRank(EMonsterRank_1,qwRoleID);
    return true;
}

bool CGodMonsterMgr::Enter(CUser& rUser,SyncInfoToClient& sClient)
{
    UINT64 qwRoleID = rUser.GetRoleID();
    //对玩家供养圣兽进行检测
    CheckGuildID(qwRoleID);
    //得到最新供奉的神兽ID
    UINT64 qwMonsterID = GetGuildIDByUserID(qwRoleID);
    GodMonsterPtr pMonster = GetMonster(qwMonsterID);
    if(!pMonster)
    {
        LOG_INF << "pMonster null.";
        return false;
    }
    LOG_INF<<"GodMonser Check qwRoleID(" <<qwRoleID<<") in Guild("<<pMonster->GetID()<<").";
    GodMonsterUserPtr pUser = pMonster->GetUserInfoByID(qwRoleID);
    if(!pUser)
    {
        LOG_CRI<<"pUser Null,so Create it.";
        pUser = GodMonsterUserPtr(new CGodMonsterUser(qwRoleID));
        pUser->SetGuildID(qwMonsterID);
        pUser->SetDevote(0);
        pUser->SetTotalDevote(0);
        pMonster->AddUser(pUser);
    }
    if(qwMonsterID == 0)
        sClient.ePeroid = EMonsterPeroid_1;
    else 
        sClient.ePeroid = static_cast<EMonsterPeroid>(pMonster->GetPeroid());
    sClient.dwGuildScore  = pMonster->GetScore();
    sClient.dwPersonScore = pUser->GetTotalScore();
    sClient.dwPersonDevote = pUser->GetDayScore();
    sClient.dwPersonRank = GetRank(EMonsterRank_1,qwRoleID);
    sClient.dwGuildRank = GetRank(EMonsterRank_2,qwMonsterID);
    sClient.dwFruit = pUser->GetFruit();
    GetAllDevote(pUser,sClient.vecUser); 
    GetLimitPrize(pUser,sClient.vecLimitPrize);
    pUser->GetPrizeInfo(sClient.vecPrize);
    GetRankInfo(sClient.vecRank);
    //LOG_CRI<<"神兽阶段："<<sClient.ePeroid<<",dwGuildScore="<<sClient.dwGuildScore <<",dwPersonScore="<<sClient.dwPersonScore<<",dwPersonDevote"<<sClient.dwPersonDevote<<",dwPersonRank="<<sClient.dwPersonRank <<",dwGuildRank="<<sClient.dwGuildRank<<",dwFruit="<<sClient.dwFruit;
    return true;
}

void CGodMonsterMgr::OnSync(GodMonsterUserPtr pUser,GodMonsterPtr pMonster, UINT64 qwRoleID)
{
    SyncInfoToClient sClient;
    UINT64 qwMonsterID = pMonster->GetID();
    if(qwMonsterID == 0)
        sClient.ePeroid = EMonsterPeroid_1;
    else 
        sClient.ePeroid = static_cast<EMonsterPeroid>(pMonster->GetPeroid());
    sClient.dwGuildScore  = pMonster->GetScore();
    sClient.dwPersonScore = pUser->GetTotalScore();
    sClient.dwPersonDevote = pUser->GetDayScore();
    sClient.dwPersonRank = GetRank(EMonsterRank_1,qwRoleID);
    sClient.dwGuildRank = GetRank(EMonsterRank_2,qwMonsterID);
    sClient.dwFruit = pUser->GetFruit();
    GetAllDevote(pUser,sClient.vecUser); 
    GetLimitPrize(pUser,sClient.vecLimitPrize);
    pUser->GetPrizeInfo(sClient.vecPrize);
    GetRankInfo(sClient.vecRank);
    CUserPtr oUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!oUser)
        return;
   oUser->SendPkg(g_GodMonsterProtS.BuildPkg_SyncClientInfo(sClient)); 
    //LOG_CRI<<"神兽阶段："<<sClient.ePeroid<<",dwGuildScore="<<sClient.dwGuildScore <<",dwPersonScore="<<sClient.dwPersonScore<<",dwPersonDevote"<<sClient.dwPersonDevote<<",dwPersonRank="<<sClient.dwPersonRank <<",dwGuildRank="<<sClient.dwGuildRank<<",dwFruit="<<sClient.dwFruit;
}

UINT32 CGodMonsterMgr::GetRank(EMonsterRank eType,UINT64 qwID)
{
    UINT32 dwTmp = 0;
    bool bFind = false;
    UINT32 dwIndex = 1;
    if(eType == EMonsterRank_1)
    {
        for(auto & it : _setUserRank)
        {
            if(qwID == it.qwID)
            {
                bFind = true;
                break;
            }
            dwIndex ++;
        }
    }else if(eType == EMonsterRank_2)
    {
        for(auto & it : _setMonsterRank)
        {
            if(qwID == it.qwID)
            {
                bFind = true;
                break;
            }
            dwIndex ++;
        }
    }

    if(bFind)
        dwTmp = dwIndex;
    return dwTmp;
}

void CGodMonsterMgr::GetRankInfo(TVecMonsterRank& vecRank)
{
    SMonsterRank oRank;
    oRank.eRank = EMonsterRank_1;
    UINT32 dwIndex = 1;
    for(auto & it : _setUserRank)
    {
        SMonsterRankInfo o;
        o.dwRank = dwIndex ++;
        o.strName = it.strName;
        o.dwScore = it.dwScore;
        //LOG_CRI<<"个人排行：dwRank=" << dwIndex<<",strName=" << o.strName;
        oRank.vecRankInfo.push_back(o);
    }
    vecRank.push_back(oRank);

    SMonsterRank oRank1; 
    oRank1.eRank = EMonsterRank_2;
    dwIndex = 1;
    for(auto & it : _setMonsterRank)
    {
        SMonsterRankInfo o;
        o.dwRank = dwIndex ++;
        o.strName = it.strName;
        o.dwScore = it.dwScore;
        //LOG_CRI<<"帮派排行：dwRank=" << dwIndex<<",strName=" << o.strName;
        oRank1.vecRankInfo.push_back(o);
    }
    vecRank.push_back(oRank1);
}

UINT64 CGodMonsterMgr::GetGuildIDByUserID(UINT64 qwRoleID)
{
    UINT64 qwGuildID = 0;
    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
    if(pUser)
         qwGuildID = pUser->GetGuildID();
    return qwGuildID; 
}

void CGodMonsterMgr::CheckGuildID(UINT64 qwRoleID)
{
    UINT64 qwGuildID = 0;
    GodMonsterPtr pMonster = NULL;
    UINT64 qwNewID = GetGuildIDByUserID(qwRoleID);
    
    bool bFind = false;
    for(auto& it : _mapID2Monster)
    {
        pMonster = it.second;
        bFind = pMonster->CheckUserByID(qwRoleID);
        if(bFind)
        {
            qwGuildID = pMonster->GetID();
            break;
        }
    }
   /* 
    GodMonsterUserPtr pUser = NULL;
    GetMonsterUser(qwRoleID,pUser);
    if(pUser)
        qwGuildID = pUser->GetGuildID();
    */
    if(qwNewID != qwGuildID)
    {
        if(!ChangeGuild(qwRoleID,pMonster,qwNewID))
        {
            LOG_INF <<"Check UserID("<<qwRoleID <<") ChangeGuild err.";
            return;
        }
    }
}

bool CGodMonsterMgr::ChangeGuild(UINT64 qwRoleID,GodMonsterPtr pMonster,UINT64 qwGuildID)
{
    if(!pMonster)
    {
        LOG_INF << "pMonster NULL.";
        return false;
    }
    GodMonsterPtr pNewMonster = GetMonster(qwGuildID);
    if(!pNewMonster)
    {
        LOG_INF << "qwGuildID(" << qwGuildID <<") not exsit.";
        return false;
    }
    //创建帮派的时候需要通知我TODO
    GodMonsterUserPtr pUser = pMonster->GetUserInfoByID(qwRoleID);
    if(!pUser)
    {
        LOG_INF <<"pUser Not Find.";
        return false;
    }
    pMonster->DeleteUser(qwRoleID);
    pUser->SetGuildID(qwGuildID); //更换帮派
    pUser->SetDevote(0); //在帮派中的贡献设置为0
    if(!pNewMonster->AddUser(pUser))
    {
        LOG_INF <<"qwGuildID(" <<qwGuildID<<" addUser(" <<qwRoleID<<") err.";
        return false;
    }
    //LOG_CRI << " qwRoleID Change GuildID(" << pMonster->GetID() <<") to GuildID(" << qwGuildID<<") Suc.";
    return true;
}

EMonsterResult CGodMonsterMgr::OneFeed(CUser& rUser,UINT32 dwFruit /* = 1*/)
{
    UINT64 qwRoleID = rUser.GetRoleID();
    GodMonsterUserPtr pUser = NULL;
    GetMonsterUser(qwRoleID, pUser); 
    if(!pUser)
    {
        LOG_INF << "pUser null.";
        return EMonsterResult_Err;
    }
    if(!pUser->IsGuildUser())
    {
        LOG_INF << "qwRoleID(" << qwRoleID<<" not in Guild.";
        return EMonsterResult_guild;
    }
    if(!pUser->CheckFruit(dwFruit))
    {
        LOG_INF<<"dwFruit Lack.";
        return EMonsterResult_Err;
    }
    UINT64 qwMonsterID = pUser->GetGuildID();
    GodMonsterPtr pMonster = GetMonster(qwMonsterID);
    if(!pMonster)
    {
        LOG_INF<<"pMonster NULL.";
        return EMonsterResult_Err;
    }
    EMonsterResult eResult = EMonsterResult_Err;
    eResult = pUser->OneFeed(dwFruit);
    OnRank(EMonsterRank_1,qwRoleID);

    pMonster->AddScore(dwFruit * BASESCORE);
    OnRank(EMonsterRank_2,qwMonsterID);
    
    OnSync(pUser,pMonster,qwRoleID);
    return eResult;
}

//玩家购买限购礼包
EMonsterResult CGodMonsterMgr::Buy(CUser& rUser,UINT16 wIndex,UINT8 byCount)
{
    EMonsterResult eResult;
    UINT64 qwRoleID = rUser.GetRoleID();
    GodMonsterUserPtr pUser = NULL;
    GetMonsterUser(qwRoleID,pUser);
    if(!pUser)
    {
        return EMonsterResult_Err;
    }
    if(!pUser->IsGuildUser())
    {
        LOG_INF << "qwRoleID=" << qwRoleID<<" not in guild";
        return  EMonsterResult_guild;
    }
    eResult = pUser->Buy(wIndex,byCount);
    return eResult;
}

EMonsterResult CGodMonsterMgr::AllFeed(CUser& rUser)
{
    UINT64 qwRoleID = rUser.GetRoleID();
    GodMonsterUserPtr p = NULL;
    GetMonsterUser(qwRoleID,p);
    if(!p)
    {
        return EMonsterResult_Err;
    }
    return OneFeed(rUser,p->GetFruit());
}

EMonsterResult CGodMonsterMgr::TakePrize(CUser& rUser,EMonsterPrizeType eType)
{
    UINT64 qwRoleID = rUser.GetRoleID();
    GodMonsterUserPtr pUser = NULL;
    GetMonsterUser(qwRoleID,pUser);
    if(!pUser)
    {
        LOG_INF << "pUser NULL.";
        return EMonsterResult_Err;
    }
    if(!pUser->IsGuildUser())
    {
        LOG_INF << "qwRoleID=" << qwRoleID<<" not joinGuild";
        return EMonsterResult_guild; 
    }
    if(!pUser->IsTake(eType))
    {
        LOG_INF << "qwRoleID=" << qwRoleID<<" Taked";
        return EMonsterResult_get; 
    }
    return pUser->TakePrize(eType);
}

bool CGodMonsterMgr::OnRank(EMonsterRank eRank,UINT64 qwID)
{
    SRankKey oKey;
    oKey.qwID = qwID;
    switch(eRank)
    {
        case EMonsterRank_1:
            {
                for(auto & it : _setUserRank)
                {
                    if(it.qwID == qwID)
                    {
                        _setUserRank.erase(it);
                        break;
                    }
                }
                GodMonsterUserPtr pUser = NULL;
                GetMonsterUser(qwID,pUser);
                oKey.strName = g_PHPProtS.GetUserNameByID(qwID);
                oKey.dwScore = pUser->GetTotalScore(); 
                _setUserRank.insert(oKey);
                
            }
            break;
        case EMonsterRank_2:
            {
                for(auto &it : _setMonsterRank)
                {
                    if(qwID == it.qwID)
                    {
                        _setMonsterRank.erase(it);
                        break;
                    }
                }
                GodMonsterPtr pMonster = GetMonster(qwID);
                CGuildPtr pGuild = CGuildMgr::Instance().GetGuild(qwID);
                if(!pMonster || !pGuild)
                    return false;
                oKey.strName = pGuild->GetName();
                oKey.dwScore = pMonster->GetScore();
                _setMonsterRank.insert(oKey);
            }
            break;
        default:
            break;
    }
    return true;
}

GodMonsterPtr CGodMonsterMgr::GetMonster(UINT64 qwMonsterID)
{
    auto it = _mapID2Monster.find(qwMonsterID);
    if(it != _mapID2Monster.end())
    {
        return it->second;
    }
    return NULL;
}

void  CGodMonsterMgr::GetMonsterUser(UINT64 qwRoleID,GodMonsterUserPtr& pUser)
{
    GodMonsterPtr pMonster = NULL;
    for(auto& it : _mapID2Monster)
    {
        pMonster = it.second;
        pUser = pMonster->GetUserInfoByID(qwRoleID);
        if(pUser)
            break;
    }
}

bool CGodMonsterMgr::CreateGuild(UINT64 qwMonsterID,GodMonsterPtr& pMonster /* = NULL */)
{
    pMonster = GetMonster(qwMonsterID);
    if(!pMonster)
    {
        pMonster = GodMonsterPtr(new CGodMonster(qwMonsterID));
        if(!pMonster)
        {
#ifdef _DEBUG            
            LOG_INF <<" New GodMonster err.";
#endif
            return false;
        }
        if(!_mapID2Monster.insert(make_pair(qwMonsterID,pMonster)).second)
        {
            LOG_INF <<" _mapID2Monster insert err.";
            return false;
        }
        //LOG_CRI << " qwMonsterID=" <<qwMonsterID<<" create Suc.";
    }
    //LOG_CRI<<"qwMonsterID=" << qwMonsterID<<" Insert Suc.";
    return true;
}

GodMonsterCFGPtr CGodMonsterMgr::GetConfig(EGodMonsterPkg eType,UINT8 byID)
{
    auto it = _mapType2MapConfig.find(eType);
    if(it == _mapType2MapConfig.end())
        return NULL;
    TMapID2ConfigPtr pEx = it->second;
    switch(eType)
    {
        case eGodMonsterConfig:
        case eGodMonsterDayPkg:
            {
                auto oIt = pEx.find(byID);
                if(oIt != pEx.end())
                    return oIt->second;
            }
            break;
        case eGodMonsterGuildRank:
        case eGodMonsterPersonRank:
            {
                for(auto &o : pEx)
                {
                    GodMonsterCFGPtr p = o.second;
                    if(p
                       && (byID <= p->wFieldDown
                       && byID < p->wFieldUp))
                            return p; 
                }
            }
            break;
        default:
            break;
    }
    return NULL;
}

GodMonsterLimitPrizeCFGPtr CGodMonsterMgr::GetLimitPrizeConfig(UINT16 wID)
{
    auto it = _mapID2LimitPrize.find(wID);
    if(it != _mapID2LimitPrize.end())
        return it->second;
    return NULL;
}

void CGodMonsterMgr::InitMonsterFromGuild(UINT64 qwMonsterID,UINT32 dwScore)
{
    auto it = _mapID2ScoreCache.find(qwMonsterID);
    if(it == _mapID2ScoreCache.end())
    {
        _mapID2ScoreCache.insert(make_pair(qwMonsterID,dwScore));
        //LOG_CRI <<"qwMonsterID=" <<qwMonsterID<<",dwScore=" <<dwScore<<" insert Suc.";
    }
}

void CGodMonsterMgr::CalcMonsterPeroid()
{
    //LOG_CRI<<"_mapID2ScoreCache.size() = " << _mapID2ScoreCache.size();
    if(_mapID2ScoreCache.size() == 0)
        return;
    TMapID2ConfigPtr* pMap = NULL;
    auto oIt = _mapType2MapConfig.find(eGodMonsterConfig);
    if(oIt != _mapType2MapConfig.end())
        pMap  = &oIt->second;
    for(auto &it : _mapID2ScoreCache)
    {
        UINT64 qwMonsterID = it.first;
        UINT32 dwScore = it.second;
        GodMonsterPtr pMonster = NULL;
        if(!CreateGuild(qwMonsterID,pMonster))
        {
            LOG_INF << " CreateMonster(" << qwMonsterID<<") Err.";
        }
        pMonster->SetScore(dwScore);
        OnRank(EMonsterRank_2,qwMonsterID);
        for(auto &it : *pMap)
        {
            GodMonsterCFGPtr pEx = it.second;
            //LOG_CRI << "wFieldDown = " << pEx->wFieldDown;
                if(pEx->wFieldDown <= dwScore 
                    && dwScore < pEx->wFieldUp)
                        pMonster->SetPeroid(pEx->byID);

        }
    }
}

#if 0
void CGodMonsterMgr::BuyFruit(CUser& rUser,UINT32 dwCount)
{
    UINT64 qwRoleID = rUser.GetRoleID();
    GodMonsterUserPtr pUser = NULL;
    GetMonsterUser(qwRoleID, pUser); 
    if(!pUser)
    {
        LOG_INF << "pUser null.";
        return;
    }
    pUser->BuyFruit(dwCount);
}
#endif

void CGodMonsterMgr::GetLimitPrize(GodMonsterUserPtr pUser,TVecLimitPrize & vecLimitPrize)
{
    LOG_CRI<<"开始获取限购礼包信息";
    for(auto & it : _mapID2LimitPrize)
    {
        SLimitPrize oLimit;
        oLimit.wPrizeID = it.second->wID;
        oLimit.wMaxNum = it.second->byNum;
        vecLimitPrize.push_back(oLimit);
    }
    pUser->GetLimitInfo(vecLimitPrize);
}
void CGodMonsterMgr::GetAllDevote(GodMonsterUserPtr pUser,TVecGuildUserDevote& vecUser)
{
    if(!pUser->IsGuildUser())
    {
        LOG_INF << "qwRoleID(" << pUser->GetRoleID()<<" not in Guild.";
        return;
    }
    UINT64 qwMonsterID = pUser->GetGuildID();
    GodMonsterPtr pMonster = GetMonster(qwMonsterID);
    if(!pMonster)
        return;
    TMapID2MonsterUserPtr mapID2User = pMonster->GetAllMonsterUser();
    if(mapID2User.size() != 0)
    {
        for(auto & it : mapID2User)
        {
            SGuildUserDevote oUser;
            CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(it.first);
            if(!pGuildUser)
               continue;
            oUser.qwRoleID = it.first;
            oUser.strName = pGuildUser->GetName();
            oUser.strLevel = pGuildUser->GetRankName();
            oUser.dwScore = it.second->GetDevote();
            vecUser.push_back(oUser);
        }
    }
}

void CGodMonsterMgr::OnPraise(CUser& rUser,UINT64 qwRoleID)
{
    string strName = g_PHPProtS.GetUserNameByID(qwRoleID);
    //rUser.SendPkg(); 
}

void CGodMonsterMgr::OnUrge(CUser& rUser,UINT64 qwRoleID)
{
    string strName = "";
    strName = g_PHPProtS.GetUserNameByID(qwRoleID);
}

void CGodMonsterMgr::OnMail()
{
    //个人积分奖励
    UINT64 qwTmp = 0;
    UINT8 byIndex = 1;
    for(auto& it : _setUserRank)
    {
        if(byIndex > 7)
            break;
        qwTmp = it.qwID;
        SendMailForUser(qwTmp,byIndex);
        byIndex ++;
    }
    //帮派积分排名奖励
    byIndex = 1;
    for(auto& oIt : _setMonsterRank)
    {
        if(byIndex > 3)
            break;
        qwTmp = oIt.qwID;
        if(qwTmp == 0) //0帮派 特别处理
            continue;
        SendMailForGuild(qwTmp,byIndex);
        byIndex ++;
    }
    //帮派积分奖励
    for(auto& oIt : _mapID2Monster)
    {
        if(oIt.first == 0)
            continue;
        SendMailForDevote(oIt.second);
    }
}

void CGodMonsterMgr::SendMailForDevote(GodMonsterPtr pMonster)
{
    if(!pMonster)
        return;
    UINT8 byIndex = pMonster->GetPeroid();
    GodMonsterCFGPtr pEx = GetConfig(eGodMonsterConfig,byIndex);
    if(!pEx)
        return;
    SItemAttachmentPtr pItem(new SItemAttachment());
    if(!pItem)
    {
        LOG_INF <<"pItem null.";
        return ;
    }
    InitMailItem(pEx->vecItems,pItem->vecItemInfo); 
    TMapID2MonsterUserPtr pMap = pMonster->GetAllMonsterUser();
    for(auto & it : pMap)
    {
        CSystemMail sysMail;
        sysMail.AddTarget(it.second->GetRoleID());
        sysMail.SetSender("系统");
        sysMail.SetBody(SysMailSendTxt(wContentID, BuildStrVec(byIndex)));
        string strTile;
        CSystemMail::GetSysMailBody(wMailID,strTile);
        sysMail.SetSubject(strTile);
        sysMail.AddItemInfo(pItem->vecItemInfo);
        sysMail.Send();
    }
}

void CGodMonsterMgr::SendMailForUser(UINT64 qwRoleID,UINT8 byIndex)
{
    GodMonsterUserPtr pUser = NULL;
    GetMonsterUser(qwRoleID,pUser);
    GodMonsterCFGPtr pEx = GetConfig(eGodMonsterPersonRank,byIndex);
    
    if(!pUser || !pEx)
        return;
    SItemAttachmentPtr pItem(new SItemAttachment());
    if(!pItem)
    {
        LOG_INF <<"pItem null.";
        return ;
    }
    InitMailItem(pEx->vecItems,pItem->vecItemInfo); 
    
    CSystemMail sysMail;
    sysMail.AddTarget(qwRoleID);
    sysMail.SetSender("系统");
    sysMail.SetBody(SysMailSendTxt(wContentIDForPerson, BuildStrVec(byIndex)));
    string strTile;
    CSystemMail::GetSysMailBody(wMailIDForPerson,strTile);
    sysMail.SetSubject(strTile);
    sysMail.AddItemInfo(pItem->vecItemInfo);
    sysMail.Send();
}

void CGodMonsterMgr::SendMailForGuild(UINT64 qwMonsterID,UINT8 byIndex)
{
    GodMonsterPtr pMonster = GetMonster(qwMonsterID);
    GodMonsterCFGPtr pEx = GetConfig(eGodMonsterGuildRank,byIndex);
    
    if(!pMonster || !pEx)
        return;
    SItemAttachmentPtr pItem(new SItemAttachment());
    if(!pItem)
    {
        LOG_INF <<"pItem null.";
        return ;
    }
    InitMailItem(pEx->vecItems,pItem->vecItemInfo); 
    TMapID2MonsterUserPtr pMap = pMonster->GetAllMonsterUser();
    for(auto & it : pMap)
    {
        CSystemMail sysMail;
        sysMail.AddTarget(it.second->GetRoleID());
        sysMail.SetSender("系统");
        sysMail.SetBody(SysMailSendTxt(wContentIDForGuild, BuildStrVec(byIndex)));
        string strTile;
        CSystemMail::GetSysMailBody(wMailIDForGuild,strTile);
        sysMail.SetSubject(strTile);
        sysMail.AddItemInfo(pItem->vecItemInfo);
        sysMail.Send();
    }
}

void CGodMonsterMgr::InitMailItem(TVecItemGenInfo& vecSource,TVecMailItemInfo& vecDesc)
{
    for(auto & it : vecSource)
    {
        SMailItemInfo oInfo;
        oInfo.wItemID = it.wItemID;
        oInfo.wCount = it.dwCount;
        oInfo.eBindType = NItemProt::eBindGet;
        vecDesc.push_back(oInfo);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

