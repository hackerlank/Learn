#ifndef ZHANQIROOM_H_
#define ZHANQIROOM_H_
#include "ZhanQiMgr.h"
#include "LingShanProt.h"

//#include "ItemProt.h"
//using namespace NItemProt;

using namespace NLingShanProt;

class CPlayer;
enum EZhanQiRoomStatus
{
    eZhanQiRoomStatus_Init,
    eZhanQiRoomStatus_GameStart, //游戏初始状态
    eZhanQiRoomStatus_Move,      //移动状态
    eZhanQiRoomStatus_Play,
    eZhanQiRoomStatus_End,
};
/*
enum ECollideType
{
    eCollideType_Path=1,  //路径碰撞
    eCollideType_Grid,  //格子碰撞
};
*/
class CZhanQiRoom  
{

public:
    CZhanQiRoom();
    ~CZhanQiRoom() {}

    void SetRoomID(UINT32 dwRoomID) { _dwRoomID = dwRoomID; };

    void SetFreshTurn(UINT8 byTurns) { _wMaxFreshTurn = byTurns; }

    UINT32 GetRoomID() { return _dwRoomID; }

   //玩家 初始玩家队列
    bool  StartGame(TVecZhanQiPlayerPtr& vecZhanQiPlayerPtr,TVecUINT16& vecInitPath,UINT16 dwMapSize);

    //把玩家放入格子
    bool  PutObjIntoGrid(SZhanQiObjPtr pZhanQiObjPtr, UINT16 wPos,bool bCollide);

    //进入新的玩家
    void Push_Player(TVecZhanQiPlayerPtr& vecZhanQiPlayerPtr,TVecUINT16& vecEmptyPos);

    //获取当前格子配置
    SLingShanMapCFGExPtr GetPlayerCurGridCFG(SZhanQiObjPtr pZhanQiObjPtr);

    //玩家移动
    ELingShanOP  OnMove(SZhanQiPlayerPtr pPlayer,UINT16 wPos);

    //玩家模型改变
    void  OnChangeModel(SZhanQiPlayerPtr pPlayer,UINT32 dwModelID);

    //当前棋盘信息
    void OnGetMatchInfo(SZhanQiPlayerPtr pZhanQiPlayer,shared_func<CLingShanProtS::SGetMatchInfoAck>& fnAck);

    //聊天
    void OnChat(CPlayer& rPlayer,const std::string& strChatMsg); 

    //进入参观房间
    void OnEnterVisitRoom(SZhanQiPlayerPtr pPlayer);

    //离开参观房间
    void OnLeaveVisitRoom(SZhanQiPlayerPtr pPlayer);

    //接收：获取动画播放信息
    ELingShanOP OnGetRoomPlayMovieInfo(CPlayer& rPlayer,shared_func<CLingShanProtSvr::SGetPlayMovieInfoAck> fnAck);


    //刷新宝箱
    void  OnSpawBox();

    //刷新普通宝箱
    bool  OnSpawGodBox();

    //刷新怪物
    void OnSpawMonster();

    //玩家离开
    void  OnPlayerLeave(SZhanQiPlayerPtr pPlayer);

    void  SetRandomMove(SZhanQiPlayerPtr pPlayer,TVecLingShanMapCFGExPtr& vecMapCfg);

    //未移动的玩家或怪物移动
    void CheckRandomMove();

    //移动开始
    void OnTurnMove();


    //移动结束开始处理逻辑
    void OnMoveEnd();

    //玩家移动的信息
    void SendMoveNotify();

    //玩家信息更新
    void SendPlayerUpdateNotify();

    //一轮开始
    void OnTurnStart();

    //一轮结束
    void OnTurnEnd();

    //播放动画结束
    void OnPlayMovieEnd();

    //刷新事件
    void OnFreshTurn();


    //玩家离开格子
    void OnPlayerLeaveGrid(SZhanQiObjPtr pObj);

    //玩家进入新格子
    void OnPlayerEnterGrid(SZhanQiObjPtr pObj);



    //路径相遇检测
    void  OnMovePathCheck();

    //在同一个格子检查
    void  OnSameGridCheck();

    //时钟
    void  OnSecUpdate();

    //活动结束
    void  OnGameOver();

    void GetAllUser(TVecUINT64& vecUserID);

    //获取参观的玩家
    void GetAllVisitUser(TVecUINT64& vecUserID);

    //设置房间所有玩家状态
    void SetAllUserStatus(ELingShanStatus eStatus,UINT32 dwParam);

    //设置房间状态
    void SetStatus(EZhanQiRoomStatus eStatus) { _eStatus=eStatus; }

    void OnFight(TMapZhanQiObjPtr& mapFight,ECollideType eType); 
    SZhanQiObjPtr CollideBattle(TVecZhanQiObjPtr& vecObj,ECollideType eType);
    SZhanQiObjPtr ObjFightResult(SZhanQiObjPtr pAtkObj, SZhanQiObjPtr pDefObj,ECollideType eType);  

    //获取下一次刷新宝箱的剩余轮数
    UINT32 GetNexFreshTurns();
    UINT32 GetPlayerCnt() { return _mapZhanQiPlayerPtr.size(); }

    UINT32 GetCurTurn() { return _wTurns; }

    //获取房间状态
    void GetRoomPlayerStatus(ELingShanStatus& eStatus,UINT32& dwTime);
    
    //已进入房间事件
    void OnEnterRoom(SZhanQiPlayerPtr pPlayer);


    //检查离线玩家
    void CheckPlayer();

public:

private:

    //普通宝箱id
    UINT32 _dwNormalBoxModelID;

    //大宝箱id
    UINT32 _dwGodBoxModelID;

    //刷新玩家数量
    UINT16 _wFreshPlayCnt;

    //下一次移动时间
    UINT32 _dwMoveEndTime;

    //下一轮时间
    UINT32 _dwPlayerEndTime;

    //下一状态时间
    UINT32 _dwNextStatusTime;

    //当前回合数
    UINT16 _wTurns;

    //玩家房间号
    UINT32 _dwRoomID;

    //大宝箱位置
    UINT16 _wGodBoxPos;

    UINT16  _wMaxFreshTurn;
    //
    UINT16 _wFreshTurn;

    //地图格子
    TVecMapGrid _vecMapGrid;

    //移动路径列表
    TMapZhanQiObjPtr _mapSamePathObjPtr;

    //路径碰撞信息
    TVecPathCollideInfo _vecPathCollideInfo;

    //c
    TMapZhanQiObjPtr _mapSameGridObjPtr;

    TVecGridCollideInfo _vecGridCollideInfo;
    
    //房间内的玩家
    TMapZhanQiPlayerPtr _mapZhanQiPlayerPtr;

    //房间内参观的玩家
    TMapZhanQiPlayerPtr _mapVisitPlayerPtr;

    //动画播放信息
    SPlayMovieInfo _oSPlayMovieInfo;


    bool _bAllOver;

    EZhanQiRoomStatus _eStatus;
};

#endif // 

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

