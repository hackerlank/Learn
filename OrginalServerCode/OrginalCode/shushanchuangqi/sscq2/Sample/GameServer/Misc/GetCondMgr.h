
#ifndef GETCONDMGR_H_
#define GETCONDMGR_H_

#include "Singleton.h"
#include "GetCondCFG.h"
#include "ItemProt.h"
#include "ProtoCommon.h" // XXX: for TVecMoneyCount

using namespace NItemProt;
using namespace NProtoCommon;

class CUser;

struct SGetCondCFGEx : public SGetCondCFG
{
    TVecMoneyCount vecMoney;
    TVecItemCount vecItem;
    TVecUINT32 vecDgnID;
    TVecUINT32 vecTaskID;
    TVecUINT16 vecPreHero;
    SGetCondCFGEx()
    {
    }
    SGetCondCFGEx(const SGetCondCFG& rGetCondCFG):
        SGetCondCFG(rGetCondCFG)
    {
    }
};

class CGetCondMgr : public Singleton<CGetCondMgr>
{
public:
    bool Init();
    bool LoadConfig(bool bReload = false);

    bool TestCond(CUser& rUser, UINT16 wCondID,UINT16 fromwhere=0, bool bNodify = false);
    bool ProcessCond(CUser& rUser, UINT16 wCondID, UINT16 towhere);
    SGetCondCFGEx* GetGetCondMgrCFG(UINT16 wCondID);

private:
    map<UINT16, SGetCondCFGEx> _mapID2GetCondInfo;
};

#endif // GETCONDMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

