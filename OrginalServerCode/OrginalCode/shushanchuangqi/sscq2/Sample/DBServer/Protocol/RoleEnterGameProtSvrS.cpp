#include "stdafx.h"
#include "Protocols.h"
#include "RoleEnterGameProtSvrS.h"
#include "DBRoleMgr.h"
#include "DBRoleNameManager.h"
#include "Title.h"

void InitFromEnterParam(const SEnterParam& stEnterParam, TVecPlatformParam& vecPlatformParam, TVecString& vecString);

//接收：请求进入游戏
void CRoleEnterGameProtSvrS::OnRecv_EnterGameReq(
         const SEnterParam& stEnterParam //创角信息   
	) 

{
    if(!Config._bInited)
        return;
    if(!CDBConfig::Instance().IsPreLoad())
        return ;
    UINT64 qwUserID = GetCurUsrID();
    if(!CDBRoleMgr::Instance().AddLoadOrCreate(qwUserID))
    {
        return ;
    }
    assert(qwUserID != 0);
    UINT32 dwGateID = GetCurSvrID();
    NetMgr.GetGateHandler()->OnUserLogin(qwUserID, dwGateID);
    LOG_INF << "Client Platform Info:" << static_cast<UINT32>(stEnterParam.byPtType) << ", " << static_cast<UINT32>(stEnterParam.byQQPtType) << ", "
        << stEnterParam.byQQPtLv << "," << stEnterParam.byQQPtYearType << "," << stEnterParam.byQQPtLuxuryType << "," 
        << stEnterParam.customPar1 << "," << stEnterParam.customPar2 << "," << stEnterParam.strOpenId << "," << stEnterParam.strOpenKey;
    CDBRoleMgr::Instance().LoadRoleData(qwUserID,eLoadOnLine, 
            [qwUserID,dwGateID,stEnterParam,this](SDBRoleData* pRoleData, EEnterResult eResult)
            {
                CDBRoleMgr::Instance().RemoveLoadOrCreate(qwUserID);
                if(pRoleData == NULL)
                {
                    this->SendClt_EnterGameAck(&qwUserID,1, eResult, time(NULL));
                    return;
                }
                if(pRoleData->GetFreezeTimer() > time(NULL))//被封号
                {
                    SendClt_EnterGameAck(&qwUserID,1, eEnterFreezErr, time(NULL));
                    g_Gate2DBCommS.SendSvr_KickUserOffLine(&dwGateID, 1, qwUserID, eLeaveKick);
                    return;
                }
                switch(pRoleData->GetUserState())
                {
                    case eUserNone:
                    case eUserLeaveAway:
                    case eUserLeaveOff:
                        {
                            TVecPlatformParam vecPlatformParam;
                            TVecString vecString;
                            InitFromEnterParam(stEnterParam, vecPlatformParam, vecString);
                            if(!CDBRoleMgr::Instance().EnterGame(*pRoleData, vecPlatformParam, vecString))
                                SendClt_EnterGameAck(&qwUserID,1, eEnterOtherErr, time(NULL));
                        }
                        break;
                    case eUserInGame:
                        LOG_CRI << "State error: user still in game, UsrID: " << qwUserID;
                        SendClt_EnterGameAck(&qwUserID,1, eEnterAlready, time(NULL));
                        return;
                    case eUserReplace:
                        {
                            TVecPlatformParam vecPlatformParam;
                            TVecString vecString;
                            InitFromEnterParam(stEnterParam, vecPlatformParam, vecString);

                            if(!CDBRoleMgr::Instance().ReEnterGame(*pRoleData, dwGateID, vecPlatformParam, vecString))
                                SendClt_EnterGameAck(&qwUserID,1, eEnterOtherErr, time(NULL));
                            LOG_INF << "Enter Game qwUserID : " << qwUserID;
                        }
                        return;
                    default:
                        LOG_CRI << "State error: " << pRoleData->GetUserState() << ", UsrID: " << qwUserID;
                        SendClt_EnterGameAck(&qwUserID,1, eEnterStateErr, time(NULL));
                        return;
                }
            });
    /*
       }
// check server init finished
if(!CDBConfig::Instance()._bInited)
return;
if(!CDBConfig::Instance().IsPreLoad())
return ;

// check roleid valid
UINT64 qwUserID = GetCurUsrID();
assert(qwUserID != 0);
// check zoneid valid
// UINT16 wZoneID = GUID_G::GUID(qwRoleID).getZone();
// if (!CDBConfig::Instance().CheckZoneID(wZoneID))
//   return;

// if (vLoginExtendInfo.size() == 0)  // 至少会包含区号
// g_RoleInfoS.SendClt_EnterGameAck(qwRoleID, eEnterLackInfo);

// inform gateserver login user

CDBNetMgr::Instance().GetGateHandler()->OnUserLogin(qwUserID);
UINT32 dwGateID = CDBNetMgr::Instance().GetGateHandler()->GetGateID(qwUserID);
// combine extendinfo to string
// string strExtend;
// MISCUTILS_G::ComboExtendInfo(vLoginExtendInfo, strExtend);

// load role data
// UINT64 qwRoleID  = qwUserID;
CDBRoleMgr::Instance().LoadRoleData(qwUserID, [qwUserID,dwGateID,this](SDBRoleData* pRoleData, EEnterResult eResult) {
if(pRoleData == NULL)
{
this->SendClt_EnterGameAck(&qwUserID,1, eResult);
return;
}

// 封号检查
*/

}

//接收：创建角色请求
void CRoleEnterGameProtSvrS::OnRecv_CreateRoleReq(
        const SCreateRoleInfo& stCreateInfo //创角信息
        )
{ 
    if(!Config._bInited)
        return;
    if(!CDBConfig::Instance().IsPreLoad())
    {
        return ;
    }
    UINT64 qwUserID = GetCurUsrID();
    if (!CDBRoleMgr::Instance().AddLoadOrCreate(qwUserID))
    {
        return ;
    }
    UINT32 dwGateID = GetCurSvrID();
    NetMgr.GetGateHandler()->OnUserLogin(qwUserID, dwGateID);
    CDBRoleMgr::Instance().CreateRole(qwUserID, stCreateInfo, [this, qwUserID](SDBRoleData* pRoleData, ECreateRoleResult eResult) mutable {
            SendClt_CreateRoleAck(&qwUserID,1,eResult);        
            CDBRoleMgr::Instance().RemoveLoadOrCreate(qwUserID);
#if 0
            //不向数据库添加数据
            if (pRoleData != NULL)
            {
            if (!CDBRoleMgr::Instance().EnterGame(*pRoleData))
            {
            /*  g_RoleInfoS.SendClt_EnterGameAck(pRoleData->stBaseInfo.qwRoleID, eEnterOtherErr);*/
            this->SendClt_EnterGameAck(&qwUserID,1,eEnterOtherErr);   
            LOG_INF << "Create Role qwUserID : " << qwUserID;
            return;
            }
            }
#endif            
            });
}

void CRoleEnterGameProtSvrS::OnRecv_PlayerRamdomNameReq(UINT8 byIsMale) 
{
    if(!Config._bInited)
        return ;
    if(!CDBConfig::Instance().IsPreLoad())
        return ;

    UINT64 qwUserID = GetCurUsrID();
    string strName;
    RoleNameManager::Instance().CreateRandomName(qwUserID, byIsMale > 0,strName);
     LOG_INF << "PlayerRamdomNameReq qwUserID : " << qwUserID;
    SendClt_PlayerRamdomNameAck(&qwUserID,1,strName);
}

//接收：玩家请求角色信息
void CRoleEnterGameProtSvrS::OnRecv_GetUserInfo(
	)
{
    if(!Config._bInited)
        return;
    if(!CDBConfig::Instance().IsPreLoad())
        return ;
    UINT64 qwUserID = GetCurUsrID();
    if(!CDBRoleMgr::Instance().AddLoadOrCreate(qwUserID))
    {
        return ;
    }
    assert(qwUserID != 0);
    UINT32 dwGateID = GetCurSvrID();
    NetMgr.GetGateHandler()->OnUserLogin(qwUserID, dwGateID);
    CDBRoleMgr::Instance().LoadRoleData(qwUserID,eLoadOterSvr, [qwUserID,dwGateID,this](SDBRoleData* pRoleData, EEnterResult eResult) {
            CDBRoleMgr::Instance().RemoveLoadOrCreate(qwUserID);
            RoleEnterGameData stRoleEnterInfo;
            stRoleEnterInfo.byIsUser = 0;
            if(pRoleData != NULL)
            {
                InitUserInfoFromDB(*pRoleData,stRoleEnterInfo);
                stRoleEnterInfo.byIsUser = 1;
            }
            SendClt_GetUserInfoAck(&qwUserID,1, stRoleEnterInfo);
            LOG_INF << "Send_UserInfo : " << qwUserID;
    });
  
}

void CRoleEnterGameProtSvrS::InitUserInfoFromDB(SDBRoleData& rRoleData,RoleEnterGameData& stRoleEnterInfo)
{
    NRoleInfoDefine::RoleDataInfo  Info; 
    for (auto iter = rRoleData._mapDataManager.begin(); iter != rRoleData._mapDataManager.end();iter++)
    {
        iter->second->GetALLInfo(Info);
    }
    NRoleInfoDefine::RoleBaseInfo &sBaseInfo = Info.stBaseInfo;
    stRoleEnterInfo.sBaseInfo.strName = sBaseInfo.strName;
    stRoleEnterInfo.sBaseInfo.eCareer = sBaseInfo.eCareer;
    stRoleEnterInfo.sBaseInfo.eSex    = sBaseInfo.eSex;
    stRoleEnterInfo.sBaseInfo.byLevel = sBaseInfo.byLevel;
	stRoleEnterInfo.sBaseInfo.wBagMax = sBaseInfo.wBagMax; //背包容量
	stRoleEnterInfo.sBaseInfo.wDepotMax = sBaseInfo.wDepotMax; //仓库容量
	stRoleEnterInfo.sBaseInfo.byNation = sBaseInfo.byNation; //国家
	stRoleEnterInfo.sBaseInfo.dwGold = sBaseInfo.dwGold + sBaseInfo.dwFreeGold; //仙石(充值+免费)
	stRoleEnterInfo.sBaseInfo.dwSilver =  sBaseInfo.dwSilver; //银币
	stRoleEnterInfo.sBaseInfo.dwCoupon = sBaseInfo.dwCoupon; //礼券
	stRoleEnterInfo.sBaseInfo.dwSoul = sBaseInfo.dwSoul; //魂魄
	stRoleEnterInfo.sBaseInfo.dwPrestige = sBaseInfo.dwPrestige; //声望
	stRoleEnterInfo.sBaseInfo.dwHonor = sBaseInfo.dwHonor; //荣誉
	stRoleEnterInfo.sBaseInfo.dwPExp = sBaseInfo.dwPExp; //修为
	stRoleEnterInfo.sBaseInfo.dwAction = sBaseInfo.dwAction; //体力
	stRoleEnterInfo.sBaseInfo.dwPoten = sBaseInfo.dwPoten; //渡劫点数
	stRoleEnterInfo.sBaseInfo.dwReiki = sBaseInfo.dwReiki; //副本星级
    stRoleEnterInfo.sBaseInfo.dwDemonSoul = sBaseInfo.dwDemonSoul;   //锁妖塔魂值
    stRoleEnterInfo.sBaseInfo.dwSoulAttack = sBaseInfo.dwSoulAttack;        //攻击之魄
    stRoleEnterInfo.sBaseInfo.dwSoulHp = sBaseInfo.dwSoulHp;         //生命之魄
    stRoleEnterInfo.sBaseInfo.dwSoulCritical = sBaseInfo.dwSoulCritical;    //暴击之魄
    stRoleEnterInfo.sBaseInfo.dwSoulCounter = sBaseInfo.dwSoulCounter;  //反击之魄
    stRoleEnterInfo.sBaseInfo.dwSoulSpeed = sBaseInfo.dwSoulSpeed;  //身法之魄
    stRoleEnterInfo.sBaseInfo.dwSoulDefence = sBaseInfo.dwSoulDefence;        //防御之魄
    stRoleEnterInfo.sBaseInfo.dwSoulHit = sBaseInfo.dwSoulHit; //命中之魄
    stRoleEnterInfo.sBaseInfo.dwSoulDodge = sBaseInfo.dwSoulDodge;//闪避之魄
    stRoleEnterInfo.sBaseInfo.dwBTPoint = sBaseInfo.dwBTPoint; //战斗力
	stRoleEnterInfo.sBaseInfo.dwTotalRecharge = sBaseInfo.dwTotalRecharge; //总充值数
    TITLE_DATA::CharToVecNum(stRoleEnterInfo.sBaseInfo.vecOwnTitle,sBaseInfo.szOwnTitle);
    TITLE_DATA::CharToVecNum(stRoleEnterInfo.sBaseInfo.vecEquipTitle,sBaseInfo.szEquipTitle);
	stRoleEnterInfo.sBaseInfo.strGuide = sBaseInfo.strGuide; //新手引导信息
	stRoleEnterInfo.sBaseInfo.byWallow = sBaseInfo.byWallow; //防沉迷
    stRoleEnterInfo.sBaseInfo.dwDemonTowerFloorID = (sBaseInfo.dwDemonTowerFloorID &= 0xFFFF); //镇妖塔最高层
    stRoleEnterInfo.sBaseInfo.dwDemonTowerPrizeFloorID = (sBaseInfo.dwDemonTowerPrizeFloorID &= 0xFFFF); //镇妖塔领奖层数
    TITLE_DATA::CharToVecNum(stRoleEnterInfo.sBaseInfo.vecIconAppear,sBaseInfo.szIcon);
   	stRoleEnterInfo.sBaseInfo.dwCreateTime = sBaseInfo.dwCreateTime; //创角时间
    TITLE_DATA::CharToVecNum(stRoleEnterInfo.sBaseInfo.vecIconDel,sBaseInfo.szIconDel);

}

void InitFromEnterParam(const SEnterParam& stEnterParam, TVecPlatformParam& vecPlatformParam, TVecString& vecString)
{
    SPlatformParam sPlatformParam;
    sPlatformParam.byPtType     = stEnterParam.byPtType;
    sPlatformParam.byQQPtType   = stEnterParam.byQQPtType;
    sPlatformParam.byQQPtLv     = stEnterParam.byQQPtLv;
    if (stEnterParam.byQQPtYearType)
        sPlatformParam.bySPType    |= 1 << ePBBitYearly;
    else
        sPlatformParam.bySPType    &= ~(1 << ePBBitYearly);
    if (stEnterParam.byQQPtLuxuryType)
        sPlatformParam.bySPType    |= 1 << ePBBitSuper;
    else
        sPlatformParam.bySPType    &= ~(1 << ePBBitSuper);
    vecPlatformParam.push_back(sPlatformParam);
    vecString.resize(4);
    vecString[0] = stEnterParam.customPar1;
    vecString[1] = stEnterParam.customPar1;
    vecString[2] = stEnterParam.strOpenId;
    vecString[3] = stEnterParam.strOpenKey;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

