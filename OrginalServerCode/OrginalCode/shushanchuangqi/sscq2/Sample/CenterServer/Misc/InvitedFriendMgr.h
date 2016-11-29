#ifndef INVITEDMGR_H__
#define INVITEDMGR_H__
#include<deque>
#include "Center2DBCommC.h"
#include "InviteGS.h"
#include "FriendInvitePrizeCFG.h"
#include "Game2CenterComm.h"
using namespace NGame2CenterComm;
using namespace NCenter2DBComm;
using namespace NInviteGS;
typedef shared_ptr<SInvitedFriendDB> SInvitedFriendDBPtr;
typedef std::map<UINT64,SInvitedFriendDBPtr> TMapInvitedFriendDBPtr;
typedef shared_ptr<SInvitedTask> SInvitedTaskPtr;
typedef std::map<UINT32,SInvitedTaskPtr> TMapInvitedTaskPtr;
typedef std::map<UINT64,TMapInvitedTaskPtr> TMapRoleID2MapInvitedTaskPtr;

struct SFriendInvitePrizeCFGEx: public SFriendInvitePrizeCFG
{
    TVecUserItem _vecPrize;
    SFriendInvitePrizeCFGEx(const SFriendInvitePrizeCFG* pFriendInvitePrizerCFG)
    {
        *(SFriendInvitePrizeCFG*)this = *pFriendInvitePrizerCFG;
    }
};

typedef shared_ptr<SFriendInvitePrizeCFGEx> SFriendInvitePrizeCFGExPtr;
typedef std::map<UINT32,SFriendInvitePrizeCFGExPtr> TMapFriendInvitePrizeCFGExPtr;

class CInvitedFriendMgr
{
public:
    enum EInvitedTaskType
    {
        eInvitedTask_day   = 1,  //每日邀请
        eInvitedTask_Level = 2,  //好友升级
        eInvitedTask_vip   = 3,   //vip数量
        eInvitedTask_Gold  = 4,  //冲值数量
    };

    CInvitedFriendMgr();
    bool InvitedFriendMgr_Init();

    void OnLoad_InviteFriend(const SCenterData& oCenterData);
    void OnLoad_InviteTask(const SCenterData& oCenterData);

    void Update2DB(UINT64 qwUserID,const SInvitedTask& rSInvitedTask,bool bDelete);

    void Update2DB(const SInvitedFriendDB& oInvitedFriendDB,bool bDelete);
    
    //有被邀请的朋友加入
    void OnAddFriend(SInvitedFriendDBPtr pInvitedFriendDBPtr,UINT64 qwInviteID);

    //被邀请朋友信息更新
    void UpdateFriend(SInvitedFriendDB& rInvitedFriendDB);

    //获得被邀请任信息
    SInvitedFriendDBPtr GetInvitedFriend(UINT64 qwUserID);

    //获取奖励配置
    SFriendInvitePrizeCFGExPtr GetPrizeCFG(UINT32 dwPrizeID);

    //获得邀请人列表
    TMapInvitedFriendDBPtr& GetInviteMap(UINT64 qwUserID);

    //获取日常任务
    TMapInvitedTaskPtr&  GetDayTaskMap(UINT64 qwUserID);

    //获取日常任务
    SInvitedTaskPtr      GetDayTask(UINT64 qwUserID,UINT32 dwPrizeID);

    //获取普通任务
    TMapInvitedTaskPtr&  GetNormalTaskMap(UINT64 qwUserID);

    //获取普通任务
    SInvitedTaskPtr      GetNormalTask(UINT64 qwUserID,UINT32 dwPrizeID);

    void OnMiddNight();


    //玩家属性变化
    void OnUserPropChanged(CUser& rUser, NGame2CenterComm::EUserSyncPropField eField,UINT32 dwValue);

    //邀请玩家登陆
    void OnUserLogin(CUser& rUser);


    //from Client

    //接收：获取被邀请好友列表
    void OnGetInvitedFriendList(UINT64 qwUserID,TVecInvitedFriend& vecInvitedFriend);
    //接收：邀请任务列表
    void OnGetInvitedTaskList(UINT64 qwUserID,TVecInvitedTask& vecInvitedTask); 
    //接收：每日邀请好友数量
    void OnGetDayInvitedFriends(UINT64 qwUserID,UINT32 &dwInviteCnt);

    //接收：领取奖励
    EInviteResult OnTakeTaskPrize(UINT64 qwUserID,UINT32 dwPrizeID);

    //from gameserver
    //接收：邀请好友成功
    void OnInviteFriend(UINT64 qwUserID, //邀请人
    UINT64 qwInvitedUserID //被邀请人
    );
   
private:
    void InsertFriend(SInvitedFriendDBPtr pInvitedFriendDBPtr,UINT64 qwInviteID);

    //检查任务是否完成
    bool CheckTaskEnd(TMapInvitedFriendDBPtr& rMap, SFriendInvitePrizeCFGExPtr);

    //@in rInvitedFriendDB
    //@out rInvitedFriend
    void GetInfo(SInvitedFriend& rInvitedFriend, const SInvitedFriendDB& rInvitedFriendDB);

    //清理每日任务
    void Clear(UINT64 qwUserID,TMapInvitedTaskPtr& pMapInvitedTask);

private:

    //被邀请的好友列表
    TMapInvitedFriendDBPtr _mapInvitedFriendDBPtr;

    //邀请的好友列表
    std::map<UINT64,TMapInvitedFriendDBPtr> _mapmapInvitPtr;

    //每日任务
    TMapRoleID2MapInvitedTaskPtr _mapDayInvitedTaskPtr;

    //普通任务
    TMapRoleID2MapInvitedTaskPtr _mapNormalInvitedTaskPtr;

    //奖励配置
    TMapFriendInvitePrizeCFGExPtr _mapFriendInvitePrizeCFGExPtr;

    //每日邀请配置
    TMapFriendInvitePrizeCFGExPtr _mapDayInviteFriendPrizeCFGExPtr;

    bool _bLoading;
};

extern CInvitedFriendMgr g_InvitedFriendMgr;

#endif //INVITEDMGR_H__




