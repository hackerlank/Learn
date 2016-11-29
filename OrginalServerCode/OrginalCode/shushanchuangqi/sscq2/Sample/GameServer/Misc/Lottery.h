
#ifndef LOTTERY_H_
#define LOTTERY_H_

#include "MiscProtS.h"
#include "ProtoCommon.h"
#include "Item.h"
#include "LotteryCFG.h"

using namespace NMiscProt;
using namespace NItemProt;
struct SLotteryCFGEx
{
    UINT16 wLotteryID;
    UINT8 byCount;
    TVecItemGenInfo vecItems;
    SLotteryCFGEx()
    {
        wLotteryID = byCount = 0;
        vecItems.clear();
    }
};

typedef shared_ptr<SLotteryCFGEx> SLotteryCFGExPtr;
typedef map<UINT16, SLotteryCFGExPtr> TMapID2LotteryCFGPtr;

class CLottery
{
public:
    CLottery();
    virtual ~CLottery();
    bool Init();
    bool LoadConfig();
    void InitLotteryNum();
    SLotteryCFGExPtr GetConfig(UINT16 wLotteryID);
    ELotteryRes Draw(CUser& rUser,UINT16 &wLotteryID); 
    void DrawRet(CUser& rUser,SLotteryCFGExPtr pConfig);
    void SendLottery(CUser& rUser,UINT32 dwTotal,UINT32 dwSelf);

private:
    void OnSync(CUser& rUser,UINT32 dwTotal  = 5 , UINT32 dwSelf = 5);
    void GetLotterInfo(CUser& rUser,TVecLotteryInfo& vecInfo,UINT32 dwSelf);
private:
    std::vector<UINT16> vecNum;
    TMapID2LotteryCFGPtr _mapID2Config;
    UINT32 dwCount;
    UINT32 dwTotalNum;
    UINT32 dwSelfNum;
    TVecLotteryInfo _vecTotalInfo;
    std::map<UINT64,TVecUINT32> _mapID2VecID;
};

extern CLottery g_Lottery;
#endif // VIPMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

