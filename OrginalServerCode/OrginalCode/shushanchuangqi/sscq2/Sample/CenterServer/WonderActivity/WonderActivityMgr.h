
#ifndef WONDERACTIVITYMGR_H_
#define WONDERACTIVITYMGR_H_

#include "Singleton.h"
#include "WonderActivity.h"
#include "Game2CenterComm.h"

typedef std::map<UINT16,SWActCFGExPtr> TMapID2WActInfoPtr;
typedef std::map<UINT16,CWonderActivity*> TMapID2WAct;
typedef std::map<UINT32,CWonderActivityEventPtr> TMapID2WActEventPtr;
typedef std::map<UINT16,SWActConfigCFGPtr> TMapID2WActConfig;
typedef std::map<UINT16,SActivityOperatingCFG> TMapID2ActivityOperatingCFG;

class CWonderActivityMgr
{
public:
    CWonderActivityMgr() :
        _bInitCheck(true),
        _dwOpenTime(0),
        _bConfigReady(false),
        _qwVersion(0)
    { }
    virtual ~CWonderActivityMgr() { }
    bool                      Init();
    bool                      LoadConfig(bool bReload = false);
    bool                      ReLoadConfig(const string& strFile);
    void                      RegisterAct();
    void                      TimerCheck(time_t tNow);
    void                      OneMinCheck(time_t tNow);
    void                      OpenActivity(UINT16 &wActID,string sAdv,string sBegin,string sEnd,string sRetain);
    SWActCFGExPtr             GetConfigEx(UINT16 wWActID);
    CWonderActivity*          GetWAct(UINT16 wWActID);
    CWonderActivityEventPtr   GetWActEvent(UINT16 wWActID);
    SWActConfigCFGPtr         GetPrizeConfig(UINT16 wPrizeConfigID);  
    UINT16                    GetServerType(UINT16 wActID);
    UINT64                    GetVersion() { return _qwVersion; } // XXX: 如果配置被重新加载这可以通过这个version来确认是否要更新
    bool                      IsAllowReload(UINT16 wID,UINT8 byFlag /* 1表示判断配置表，2表示判断奖励配置表 */ );
    EWActResult               GetPrize(UINT16& wActID, UINT8& byIndex, TVecItemConfig &vecItems);
    EWActResult               GetPrizeInfo(UINT16& wActID, EWActPrizeType, TVecItemConfig &vecItem); 
    EWActResult               GetAllPrize(UINT16& wActID, TVecPrizeConfig&); 
    EWActResult               GetAllTime(UINT16& wActID, STime&); 
    EWActResult               GetActList(TVecTime&); 
    EWActResult               GetPlayerInfo(UINT64 &qwRoleID, bool bType,UINT16 &wActID,SWActPlayerInfo& sPlayer); 
    void                      TakePrize(UINT64 &qwRoleID, UINT16& wActID,UINT32 &wCond); 
    void                      GetRoleActInfo(UINT64 &qwRoleID, UINT16& wActID,TVecRoleStatus &vecRet); 
    UINT16                    GetTypeByActID(UINT16& wActID); 
    void                      LoadRoleLevelData();
    void                      LoadFromDB();
    void                      OnLoad(const TVecWonderPrize2DB& vecData);
    void                      OnSuccess(UINT64 qwRoleID,UINT16 wActID,UINT32 wCond);
    void                      InitReachActID(); //初始化需要通知的活动和条件
    void                      CheckReachActID();
    SActivityOperatingCFG*    GetActivityOperatingCFG(UINT16 wActID);

    UINT8                  GetPrizeStateByRoleID(UINT64 qwRoleID,UINT16 wActID,UINT32 wCond);
    TMapID2PrizeState&     GetMapID2PrizeState();
     void                  GetOpenServerTime(UINT32& dwTime,bool& bOpen);
     void                  GetRoleAllState(UINT64& qwRoleID,TVecRoleAllStatus& vecRet);
    UINT32                 GetOpenTime(){ return _dwOpenTime; }
    bool                   IsRun(UINT16 wActID);
private:
    bool                  ParseConfigInfo(UINT16 wConfigID,TVecPrizeCFGPtr &rVecPrizePtr,string &rPrizeString,string &rItemString);
    bool                  IsFined(SActID2Cond &sTmp);

//Q养成活动
public:
    EWActResult           ExChange(CUser& rUser,UINT8 byType);
    void                  SetPoolValue(UINT8 byType,UINT32 dwValue);
    void                  SyncCoinInfo(CUser& rUser);
private:
    bool CheckActivityVar();
    bool InitTimeForAct();
    bool CheckActID(UINT16 wActID);
    
    //不需要在精彩活动面板中显示的活动需要注册进来
    void AddActIDToNotSend(UINT16 wActID,UINT16 wType);
private:
    TMapID2ActivityOperatingCFG _mapID2ActivityOperatingCFG;
    TMapID2WActInfoPtr    _mapID2WActInfo; //活动总的配置信息
    TMapID2WActConfig     _mapID2WActCfg;  //活动奖励配置信息
    TMapID2WAct           _mapID2WAct;
    TMapID2WActEventPtr   _mapID2WActEvent;
    bool                  _bInitCheck;
    UINT32                _dwOpenTime;
    bool                  _bConfigReady;
    UINT32                _qwVersion;
    //奖励状态信息 
    TMapID2PrizeState _mapID2PrizeState;
    TMapID2PrizeState _mapID2PrizeStateCached;
    //活动通知检测
    std::vector<SActID2Cond> _vecActID2Cond;

    std::set<UINT16> _setActID; //暂存不需要发给客户端显示的 ID列表
};

extern CWonderActivityMgr g_WonderActivityMgr;

#endif // WonderActivityMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

