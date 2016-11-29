/**
 * 灵山夺宝活动
 **/
#ifndef ZHANQIMGR_H_
#define ZHANQIMGR_H_

#include "RoleInfoDefine.h"
#include "ItemProt.h"
#include "LingShanProt.h"
#include <vector>
#include <deque>
#include "LingShanMapCFG.h"
#include "LingShanCFG.h"
#include "LingShanKillPrizeCFG.h"
#include "LingShanModelCFG.h"
#include "DayActivity.h"
#include "LingShanProtS.h"

using namespace NRoleInfoDefine;
using namespace NItemProt;
using namespace NLingShanProt;
using namespace NLingShanProt;

class CPlayer;

struct SLingShanMapCFGEx: public SLingShanMapCFG
{
    TSetUINT16 setPath;
    void CopyFrom(SLingShanMapCFG& rLingShanMapCFG)
    {
        *((SLingShanMapCFG*)this) = rLingShanMapCFG;
    }
};

typedef shared_ptr<SLingShanMapCFGEx> SLingShanMapCFGExPtr;
typedef std::vector<SLingShanMapCFGExPtr> TVecLingShanMapCFGExPtr;

//活动配置信息
struct SLingShanCFGEx: public SLingShanCFG
{
    TVecUINT16 vecInitPath;
    TVecItemGenInfo vecItemGenInfo;
    void CopyFrom(SLingShanCFG& rLingShanCFG)
    {
        *((SLingShanCFG*)this) = rLingShanCFG;
    }
};
typedef shared_ptr<SLingShanCFGEx> SLingShanCFGExPtr;
typedef std::map<UINT32,SLingShanCFGExPtr> TMapLingShanCFGExPtr;

//连杀奖励
struct SLingShanKillPrizeCFGEx: public SLingShanKillPrizeCFG
{
    void CopyFrom(SLingShanKillPrizeCFG& rLingShanKillPrizeCFG)
    {
        *((SLingShanKillPrizeCFG*)this) = rLingShanKillPrizeCFG;
    }
};
typedef shared_ptr<SLingShanKillPrizeCFGEx> SLingShanKillPrizeCFGExPtr;
typedef std::vector<SLingShanKillPrizeCFGExPtr> TVecLingShanKillPrizeCFGExPtr;

typedef std::map<UINT32,TVecLingShanMapCFGExPtr> TMapVecLingShanMapCFGExPtr;

//模型
struct SLingShanModelCFGEx: public SLingShanModelCFG
{
    void CopyFrom(SLingShanModelCFG& rLingShanModelCFG)
    {
        *((SLingShanModelCFG*)this) = rLingShanModelCFG;
    }
};
typedef shared_ptr<SLingShanModelCFGEx> SLingShanModelCFGExPtr;

typedef std::map<UINT32,SLingShanModelCFGExPtr> TMapLingShanModelCFGExPtr;


enum EZhanQiObjType
{
    eZhanQiObjType_Invalid,
    eZhanQiObjType_Box,
    eZhanQiObjType_Player,
    eZhanQiObjType_Monster,
};

struct SZhanQiObj
{
    //当前位置
    UINT16 wSrcID;

    //目标位置
    UINT16 wDstID;

    //是否有大宝箱
    UINT16 wGodBox;

    UINT8  byFail;

    //击杀次数
    UINT32 dwKillCnt;


    //模型id
    UINT32 dwModelID;

    EZhanQiObjType eZhanQiObjType;
    bool IsObj(const EZhanQiObjType eType)
    {
        return eType == eZhanQiObjType;
    }
    SZhanQiObj()
    {
        wSrcID = 0;
        wDstID = 0;
        wGodBox = 0;
        eZhanQiObjType = eZhanQiObjType_Invalid;
        byFail = 0;
        dwModelID = 0;
    }
    virtual ~SZhanQiObj(){}
};

typedef shared_ptr<SZhanQiObj> SZhanQiObjPtr;
typedef std::vector<SZhanQiObjPtr> TVecZhanQiObjPtr;

struct SCollideObj
{
    //单元
    SZhanQiObjPtr pObjPtr;
    TVecZhanQiObjPtr vecZhanQiObjPtr;
};

typedef std::map<UINT32,SCollideObj> TMapZhanQiObjPtr; //路径冲突

struct SZhanQiBox:public SZhanQiObj
{
    SZhanQiBox():SZhanQiObj()
    {
        eZhanQiObjType = eZhanQiObjType_Box; 
    }
};
typedef shared_ptr<SZhanQiBox> SZhanQiBoxPtr;

struct SZhanQiMonster:public SZhanQiObj
{
    CMonsterPtr pMonster;
    SZhanQiMonster():SZhanQiObj()
    {
       
        eZhanQiObjType = eZhanQiObjType_Monster;
        pMonster = NULL;
    }
};

typedef shared_ptr<SZhanQiMonster> SZhanQiMonsterPtr;

struct SZhanQiPlayer:public SZhanQiObj
{
    CPlayerWtr pPlayer;

    //死亡次数
    UINT32 dwDeadCnt;

    //血量值
    float  fHPRate;

    //随缘值
    UINT32 dwSuiYuan;

    //获得普通宝箱次数
    UINT32 dwNormalBoxCnt;

    //玩家状态
    ELingShanStatus eStatus;

    UINT64 qwRoleID;

    //移动cd
    UINT32 dwMoveCd;

    //排队编号
    UINT32 dwWaitNo;

    //所在分组
    UINT32 dwRoomID;

    UINT32 dwNextChatTime;

    //参观房间
    UINT16 wVisitRoomID;

    //
    UINT32 dwSelfTurns;

    //奖励log
    TVecTakePrizeLog vecTakePrizeLog;
    SZhanQiPlayer():SZhanQiObj()
    {
        dwModelID = 0;
        dwKillCnt = 0;
        dwDeadCnt = 0;
        fHPRate = 1.0;
        dwSuiYuan = 0;
        dwNormalBoxCnt = 0;
        dwMoveCd = 0;
        dwWaitNo = 0;
        eStatus = eLingShanStatus_Init;
        eZhanQiObjType = eZhanQiObjType_Player;
        qwRoleID = 0;
        dwModelID = 1;
        dwNextChatTime = 0;
        wVisitRoomID = 0;
        dwSelfTurns = 0;
    }

    void SetVisitRoomID(UINT16 wRoomID)
    {
        wVisitRoomID = wRoomID;
    }

    UINT16 GetVisitRoomID()
    {
        return wVisitRoomID;
    }

    UINT32 GetTotleItemCnt()
    {
        return dwNormalBoxCnt + dwSuiYuan/SParamConfig::wSecretAreaSuiYan2Item;
    }

    void GetRoomInfo(SRoomPlayInfo& rRoomPlayInfo)
    {
        rRoomPlayInfo.qwRoleID = this->qwRoleID;
        rRoomPlayInfo.dwModelID = this->dwModelID;
        rRoomPlayInfo.dwKillCnt = this->dwKillCnt;
        rRoomPlayInfo.bGodBox   = this->wGodBox;
        rRoomPlayInfo.wPos      = this->wSrcID;
    }


    //回归等待队列
    void ResetWait()
    {
        eStatus = eLingShanStatus_Wait;
        dwRoomID = 0;
        wSrcID  = 0;
        wDstID = 0;
        wGodBox = 0;
        byFail  = 0;
        dwSelfTurns = 0;
    }
};

typedef std::shared_ptr<SZhanQiPlayer> SZhanQiPlayerPtr;

//队列
typedef std::deque<SZhanQiPlayerPtr> TDequeZhanQiPlayerPtr;

//vector
typedef std::vector<SZhanQiPlayerPtr> TVecZhanQiPlayerPtr;

//报名的列表
typedef std::map<UINT64,SZhanQiPlayerPtr> TMapZhanQiPlayerPtr;


struct SMapGrid
{
    SZhanQiObjPtr pZhanQiObjPtr;
    bool IsEmpty()
    {
        return NULL == pZhanQiObjPtr;
    }

    SMapGrid()
    {
    }
};

typedef std::vector<SMapGrid> TVecMapGrid; //地图格子结构

class CZhanQiRoom;
typedef shared_ptr<CZhanQiRoom> CZhanQiRoomPtr;
typedef std::vector<CZhanQiRoomPtr> TVecZhanQiRoomPtr;


class CZhanQiMgr:public CDayActivity  
{
    enum
    {
       Event_Update    = 1,  //Loop
       Event_SendPrize = 2,  //奖励发放 
       Event_AddExp    = 3,  //经验增加
    };

    enum
    {
        Status_Move = 1,    //移动阶段
        Status_PlayMovie,   //播放动画阶段
    };

    enum EZhanQiAuto
    {
        eZhanQiAuto_ItemID,
        eZhanQiAuto_ItemCnt,
    };

public:
    CZhanQiMgr();
    ~CZhanQiMgr() {}
    bool ZhanQiInit();


    //获取玩家状态
    void OnGetPlayerStatus(CPlayerPtr pPlayer);

    //玩家报名
    UINT32 OnPlayerReg(CPlayerPtr pPlayer);

    //玩家移动
    UINT32 OnPlayerMove(CPlayer& rPlayer,UINT16 wDestPos,UINT32& dwMoveCd);

    //玩家
    UINT32 OnPlayerLeave(CPlayer& rPlayer);

    //接收：当前棋盘信息状态
    UINT32 OnGetMatchInfo(CPlayer& rPlayer,shared_func<CLingShanProtS::SGetMatchInfoAck>& fnAck);

    //接收：获取自己的比赛信息 
    UINT32 OnGetMathSelInfo(CPlayer& rPlayer,shared_func<CLingShanProtSvr::SGetMathSelInfoAck>& fnAck);

    //接收：更换模型信息
    UINT32 OnChangeModel(CPlayer& rPlayer,UINT32 dwModelID,UINT32& dwRetModelID);


    //gain math info
    UINT32 OnGetActInfo(CPlayer& rPlayer,shared_func<CLingShanProtSvr::SGetActInfoAck>& fnAck);

    //接收：聊天
    UINT32 OnChat(CPlayer& rPlayer,const std::string& strChatMsg);

    //获取房间信息
    UINT32 OnGetRoomList(CPlayer& rPlayer,TVecRoomInfo& vecRoomInfo); 

    //进入参观房间
    UINT32 OnEnterVisitRoom(CPlayer& rPlayer,UINT16 wRoomID); 
    //离开参观房间
    UINT32 OnLeaveVisitRoom(CPlayer& rPlayer); 


    //接收：获取动画播放信息
    UINT32 OnGetPlayMovieInfo(CPlayer& rPlayer,shared_func<CLingShanProtSvr::SGetPlayMovieInfoAck> fnAck);

    //登陆事件
    void   OnLogin(CPlayer& rPlayer);

    //保存当前获得的物品
    void   SaveItem(SZhanQiPlayerPtr pZhanQiPlayer);

    //数据库数据
    void   ClearItemDB(SZhanQiPlayerPtr pZhanQiPlayer);

    //是否开放
    bool IsOpen();


    //每秒更新
    void OnSecUpdate();

    virtual bool GMOpen();        // GM指令直接开启活动

    virtual bool OnAlarm();       // 程序开始准备
    virtual void OnReady();       // 开始通知
    virtual void OnBegin();       // 正式开始
    virtual void OnEnd();         // 活动结束
    
    virtual void OnReBegin();   // 服务器重启,处于活动期间的处理
    virtual void ResetState();                  // 重置原始状态
    virtual void OnEvent(SActEventData& oSActEventData);    // 注册事件触发

    bool   IsEnd();

    //加入等待队列
    void PushWait(SZhanQiPlayerPtr pZhanQiPlayerPtr);
    //获取报名玩家
    SZhanQiPlayerPtr GetMatchPlayer(UINT64 qwRoleID);

    TVecLingShanMapCFGExPtr& GetMapCFG(UINT32 dwMapType) { return _mapVecLingShanMapCFGExPtr[dwMapType]; };

    //取当前活动配置活动配置
    SLingShanCFGExPtr GetCurLingShanCFG();

    //取当前活动配置地图
    TVecLingShanMapCFGExPtr& GetCurMapCFG();


    //设置当前活动
    void SetCurLingShanCFGEx();

    //获取活动配置
    SLingShanCFGExPtr GetLingShanCFG(UINT32 dwActID);

    //获取连杀奖励,wKillCnts>=1
    UINT32 GetLastKillPrize(UINT16 wKillCnts);

    //检查是否创建房间
    bool IsNeedCreateRoom();

    //创建新的房间
    void CreateRoom();

    //出队一定数量的等待玩家
    void GetWaitPlayer(TVecZhanQiPlayerPtr& vecZhanQiPlayerPtr,UINT16 wPlayerCnt);

    //通知队列状态改变
    void NotifyWaitNoUpdate();

    CZhanQiRoomPtr GetRoom(UINT32 dwRoomID);

    //获取模型锁定条件
    SLingShanModelCFGExPtr  GetModelCFG(UINT32 dwModelID);

    //活动结束
    void OnAllEnd();

    //所有参加活动的玩家加经验
    void OnAddExp();

public:
    //是否在活动内
    bool IsInAct(UINT64 qwRoleID);

private:
    //报名队列
    TMapZhanQiPlayerPtr _mapZhanQiPlayerPtr;

    //等待队列
    TDequeZhanQiPlayerPtr _dequeZhanQiPlayerPtr;

    //地图类型配置
    TMapVecLingShanMapCFGExPtr _mapVecLingShanMapCFGExPtr;

    //连杀奖励配置
    TVecLingShanKillPrizeCFGExPtr _vecLingShanKillPrizeCFGExPtr;

    //活动类型配置
    TMapLingShanCFGExPtr _mapLingShanCFGExPtr;

    //当前活动配置
    SLingShanCFGExPtr _pCurLingShanCFGEx;

    //人物模型id
    TMapLingShanModelCFGExPtr _mapLingShanModelCFGExPtr;

    UINT16 _wCurMapID;

    UINT16 _wMapSize;

    bool bNeedUpdateRoom;

    //房间列表
    TVecZhanQiRoomPtr  _vecZhanQiRoom;

    //参与奖励
    TVecItemGenInfo _vecItemGenInfo;

};

extern CZhanQiMgr g_ZhanQiMgr;

#endif // 

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

