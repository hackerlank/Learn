
#ifndef LEVELPRIZEMGR_H_
#define LEVELPRIZEMGR_H_
#include "RoleInfoDefine.h"
#include "CommonDef.h"
#include "ItemProt.h"
#include "LevelPrizeSvr.h"
#include "ProtoCommon.h"
#include "User.h"
#include "UserMgr.h"
#include "LevelPrize.h"
#include "EventMgr.h"
#include "WondActMgr.h"

using namespace NProtoCommon;
using namespace NRoleInfoDefine;
using namespace NItemProt;
using namespace NLevelPrize;

class CPlayer;
struct SActConfigEx;
struct SActInfoEx;

class CLevelPrizeAct : /*public Singleton<CLevelPrizeAct>, */public CRegiserterEvent, public CPoolObj<CLevelPrizeAct> 
{

public:
    CLevelPrizeAct(CPlayer &rPlayer);
    ~CLevelPrizeAct() {}
    bool LoadFromDB(const RoleDataInfo& rRoleDataInfo);
    void Update2DB(SPrize2DB& rInfo, EDataChange eDataChange = eOpUpdate);
    void OnEvent(SEventInfoPtr pEventInfo);
    ELevelActStatus TakePrize(UINT16 wID,UINT8 byIndex);
    void RegisterEvent(UINT16 wID);
    void RegisterActEvent(UINT16 wID,UINT8 byIndex,TVecUINT32& vecConds);
    TVecPrize2DB& GetPrize2DB();
    void RemoveActEvent(UINT16 wID,TVecUINT32 &vecConds);
    void SetPrizeState(UINT8 wID,UINT8 byState);
    void RemoveAllEvent(UINT16 wID);
    UINT8 GetPrizeStateByID(UINT8 byIndex);
    void ClearPrize2DB(SPrize2DB sPrize);
    bool CheckFinish(UINT64 qwRoleID,UINT16 wActID,UINT16 wLevel);
private:
    UINT32 ThisDayZero();
    CPlayer&   _rPlayer;
    TSetUINT32 _setEventIDs;
    TVecPrize2DB _vecPrize2DB;
};

#endif // 
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

