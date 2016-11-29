
#ifndef WONDACTMGR_H_
#define WONDACTMGR_H_
#include "stdafx.h"
#include "ItemProt.h"
#include "ProtoCommon.h"
#include "ActivityOperatingCFG.h"
#include "ActivityOperatingConfigCFG.h"
#include "LevelPrizeAct.h"
#include "LevelPrize.h"
#include "Player.h"
#include "WonderActivityProt.h"
using namespace NLevelPrize;
using namespace NProtoCommon;
using namespace NItemProt;

enum EWondActType
{
    eWondActType_NONE,
    eWondActType_CONDPRIZE = 701,
    eWondActType_MAX
};
struct SID2Prize
{
    TVecUINT32 vecConds;
    TVecItemGenInfo vecItems; 
};
typedef shared_ptr<SID2Prize> SID2PrizePtr;
typedef std::vector<SID2PrizePtr> TVecID2PrizePtr;
//typedef shared_ptr<CLevelPrizeAct> CLevelPrizeActPtr;
struct SActInfoEx : SActivityOperatingCFG
{
   UINT16 wActID;
   UINT16 wConfigID;
   UINT16 wType;
   UINT16 wOpenAct;
   UINT32 dwAdvance;
   UINT32 dwBegin;
   UINT32 dwEnd;
   UINT32 dwRetain;
   EActState eState;
   bool bReg;
   void CopyFrom(SActivityOperatingCFG &rCFG)
   {
      *((SActivityOperatingCFG*)this) = rCFG;
   }
   SActInfoEx()
   {
       eState = eActState_Init;
       bReg = false;
   }

};
typedef shared_ptr<SActInfoEx> SActInfoExPtr;
typedef std::map<UINT16,SActInfoExPtr> TMapID2ActInfoExPtr;

struct SActConfigEx : SActivityOperatingConfigCFG
{
    UINT16          wConfigID;
    UINT16          wType;
    TVecID2PrizePtr vecPrizes;
    void CopyFrom(SActivityOperatingConfigCFG &rCFG)
    {
        *((SActivityOperatingConfigCFG*)this) = rCFG;
    }
};
typedef shared_ptr<SActConfigEx> SActConfigExPtr;
typedef std::map<UINT16,SActConfigExPtr> TMapID2ActConfigExPtr;
typedef std::map<UINT64,TSetUINT16> TMapID2ActID;

class CWondActMgr 
{

public:
    CWondActMgr();
    ~CWondActMgr() {}
    bool                    Init();
    bool                    ReLoadConfig(const string &str);
    bool                    IsAllowReload(UINT16 wID,UINT8 byFlag /* 1表示判断配置表，2表示判断奖励配置表 */ );
    void                    OnAdvance(UINT16);
    //服务器重启，判断函数
    bool                    IsAdvTime(UINT32,UINT32);
    bool                    IsBeginTime(UINT32,UINT32);
    bool                    IsRetainTime(UINT32 dwEndTime,UINT32 dwRetainTime);
    string                  GetActName(const UINT16&);
    void                    OnBegin(const UINT16);
    void                    OnReBegin(const UINT16);
    void                    OnEnd(const UINT16);
    void                    OnRetain(UINT16);
    void                    OneMinCheck(time_t tNow);
    void                    TimerCheck(time_t tNow);
    bool                    AdvTime(UINT32);
    EActState               GetState(UINT16 wID);
    void                    SetState(UINT16 wID,EActState eType);
    void                    UpdateState(UINT16& wID);
    UINT8                   GetPrizeState(CPlayer&,UINT16 wID,UINT8 byIndex);
    SActInfoExPtr           GetActInfo(const UINT16 &wActID);
    bool                    GetPrize(CPlayer&,UINT16 &,TVecPrize &);
    SActConfigExPtr         GetActConfig(UINT16 &wConfigID);
    bool                    ParseConfigInfo(TVecID2PrizePtr &vecPrizes,string &rPrizeString,string &rItemString);
    ELevelActStatus         TakePrize(CPlayer &rPlayer,const UINT16& wID,UINT8);
    TSetUINT16&             GetActList();
    void                    GetConds(UINT16 wID,UINT8 byIndex,TSetUINT32&);
    bool                    GetConds(UINT16 wID,UINT8 byIndex,TVecUINT32&);
    bool                    GetPrizeByID(UINT16 wID,UINT8 byIndex,TVecItemGenInfo &vecItems);
    void                    ClearDB(CPlayer&,UINT16 wID);
    UINT8                   GetIndex(UINT16 wID);
    TVecID2PrizePtr        GetConds(UINT16 wID);
    bool                    OpenActivity(UINT16 wID,string&,string&sBegin,string& sEnd,string& dwRetain);
    bool                    EndActivity(UINT16 wID);
    UINT16                  GetActType(UINT16 wID);
    bool                    ModifyTime(UINT16 wID,UINT8 byType,UINT32 dwTime);
    void                    GetRoleState(CPlayer& rPlayer,NWonderActivityProt::TVecRoleAllStatus& vecRet);
    UINT32                  GetOpenTime() { return _dwOpenTime; } 
private:
    bool InitActTime();
private:
    TMapID2ActConfigExPtr _mapID2Config;
    TMapID2ActInfoExPtr   _mapID2Info;
    TMapID2ActID          _mapID2ActID;
    TSetUINT16            _setIDs;
    bool                  _bInitCheck;
    bool                  _bInitOpenTime;
    bool                  _bConfigReady;
    UINT32                _dwOpenTime;
    
};

extern CWondActMgr g_WondActMgr;
#endif // 
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

