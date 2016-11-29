#ifndef EQUIPTRUMP_MGR_H
#define EQUIPTRUMP_MGR_H

#include "stdafx.h"

#include "Singleton.h"
#include "StrengthProbabilityCFG.h"
#include "XiLianCFG.h"
#include "TrumpIntensifyCFG.h"
#include "EquipTrumpProt.h"
#include "ItemProt.h"

using namespace NEquipTrumpProt;
using namespace NItemProt;

struct SEquipTrumpSlotCFG;
struct SEquipTrumpRecycleCFG;

struct SStrengthProbabilityCFGEx:public SStrengthProbabilityCFG
{
    void CopyFrom(SStrengthProbabilityCFG& rStrengthProbabilityCFG)
    {
        *((SStrengthProbabilityCFG*)this)=rStrengthProbabilityCFG;
    }
};

typedef std::shared_ptr<SStrengthProbabilityCFGEx> SStrengthProbabilityCFGExPtr;
typedef std::map<UINT32,SStrengthProbabilityCFGExPtr> TMapStrengthProbabilityCFGExPtr;

struct SXiLianCFGEx:public SXiLianCFG
{
    TVecShuffleInfo _vecMaxShuffleInfo;
    TVecXiLianProb  _vecXiLianProb;
    TVecXiLianProb  _vecXiLianProb2;
    TVecXiLianProb  _vecXiLianProb3;
    void CopyFrom(SXiLianCFG& rXiLianCFG)
    {
        *((SXiLianCFG*)this)=rXiLianCFG;
    }
};

typedef std::shared_ptr<SXiLianCFGEx> SXiLianCFGExPtr;
typedef std::map<UINT32,SXiLianCFGExPtr> TMapXiLianCFGExPtr;

struct STrumpIntensifyCFGEx:public STrumpIntensifyCFG
{
    TVecFloat _vecAttr;
    void CopyFrom(STrumpIntensifyCFG& rTrumpIntensify)
    {
        *((STrumpIntensifyCFG*)this)=rTrumpIntensify;
    }
};

typedef std::shared_ptr<STrumpIntensifyCFGEx> STrumpIntensifyCFGExPtr;
typedef std::map<UINT32,STrumpIntensifyCFGExPtr> TMapTrumpIntensifyCFGExPtr;

struct SEquipTrumpSlotConfig
{
    UINT8               byIndex;
    EEquipTrumpSlotType eSlotType;
    UINT16              wMinDujieLevel;

    SEquipTrumpSlotConfig():
        byIndex(0), eSlotType(eETSTNone), wMinDujieLevel(0)
    {
    }
};

struct SEquipTrumpMergeConfig
{
    UINT16  wItemID;            // 法宝ID
    UINT32  dwSilver;           // 消耗硬币
    TVecItemCount vecMaterial;  // 消耗材料
    SEquipTrumpMergeConfig():
        wItemID(0), dwSilver(0)
    {
    }
};

class CEquipTrumpMgr : public Singleton<CEquipTrumpMgr>
{
    public:
        typedef map<UINT8, SEquipTrumpSlotConfig> MapSlotConfig;

    public:
        bool Init();

        bool LoadConfig(const string&);
        bool Reload();


        SStrengthProbabilityCFGExPtr GetStrengthProbabilityCFGEx(UINT32 dwStrongID);

        SXiLianCFGExPtr              GetXiLianCFGEx(UINT32 dwXiLianID);

        UINT32 GetStrengthID(UINT32 dwItemAttrID,UINT16 wLevel)
        {
            return dwItemAttrID*100 + wLevel;
        };

        //获取法宝强化配置
        STrumpIntensifyCFGExPtr GetTrumpIntensify(UINT32 dwItemAttrID,UINT16 wLevel);
        const MapSlotConfig&          GetSlotConfig() const;

        UINT32 GetBreakLootID(UINT16 wItemID, UINT8 byLevel) const;
        void GetMaterial(UINT16 wItemID, map<UINT16, UINT32>& rmapMaterial) const;
        UINT32 GetMergeCost(UINT16 wItemID) const;

    private:
        bool LoadStrenghProbability(const string& strFile);
        bool LoadXiLianConfig(const string& strFile);
        bool LoadEquipTrumpSlotConfig(const string& strFile);
        bool LoadTrumpIntensify(string& strFile);
        bool LoadMergeConfig(const string& strFile);
        bool LoadBreakConfig(const string& strFile);
    private:

        //强化概率
        TMapStrengthProbabilityCFGExPtr _mapStrengthProbabilityCFGExPtr;

        //洗练
        TMapXiLianCFGExPtr              _mapXiLianCFGExPtr;

        //强化属性
        TMapTrumpIntensifyCFGExPtr      _mapTrumpIntensifyCFGExPtr;

        //法宝装备位
        MapSlotConfig                   _mapSlotConfig;
        map<UINT32, SEquipTrumpMergeConfig*>    _mapMergeConfig;
        map<UINT32, SEquipTrumpRecycleCFG*>     _mapBreakConfig;
};

#endif // #define EQUIPTRUMP_MGR_H

