#ifndef TRUMP_SLOTS_H
#define TRUMP_SLOTS_H

#include "Store.h"
#include "ItemProt.h"
#include "ProtoCommon.h" // XXX: for EAttrGroupType

#include "BoostOwner.h"

using namespace NProtoCommon;

const UINT16 TRUMP_SLOTS_COUNT = 999;
const UINT8 MAX_PASSIVE_COUNT = 1;

class CTrumpSlots : public CStore, public CBoostOwner
{
    public:

        CTrumpSlots(CUserPtr pUser);
        virtual ~CTrumpSlots();

        virtual EStoreType GetStoreType() const;

        virtual CUser& GetUser();
        virtual CUser& GetUser() const;

        CUserPtr GetUserPtr();

        void SetDirty(EAttrGroupType eType) const;

	    bool AddItem(CItem& rItem, INT16 wIndex = -1, bool bNotify = true, bool bNew = false, bool bUpdate = true, UINT16 fromWhere = 0);

        void WriteTrumpLog(UINT32 dwID,string &sName,UINT16 wLevel,UINT32 dwSkillID,UINT32 dwExp);
        //激活法宝
        ETrumpResult ActiveTrump    (UINT16 wItemID, bool bForce = false);
        ETrumpResult ActiveTrump    (UINT16 wItemID, TVecTrump& vecTrump, bool bForce = false);
        //出战法宝
        ETrumpResult EquipTrump     (UINT64 qwInstID, TVecTrump& vecTrump);
        //卸下法宝
        ETrumpResult UnEquipTrump   (UINT64 qwInstID, TVecTrump& vecTrump);
        //祭炼法宝
        ETrumpResult UpgradeTrump   (UINT64 qwInstID, UINT8 byOneKey, TVecTrump& vecTrump);

        //提升法宝品级
        ETrumpResult EvolveTrump    (UINT64 qwInstID, TVecTrump& vecTrump);

        bool GetHaloAttr(TVecFloat& rvecAttr) const;
        bool GetExtraAttr(TVecFloat& rvecAttr) const;
        bool GetActiveAttr(TVecFloat& rvecAttr) const;

        CTrumpPtr GetActiveTrump();
        CTrumpPtr GetActiveTrump() const;
        vector<CTrumpPtr> GetPassiveTrump();
        vector<CTrumpPtr> GetPassiveTrump() const;

        bool IsTrumpActived(UINT16 wItemID) const;

        UINT32  GetPeerlessSkill() const;
        void    GetPassiveSkills(TVecUINT32& rvecPassiveSkill) const;
        bool    GetAllActiveTrump(vector<CItemPtr>& rvecItem) const;

        void    Boost(ECareerType eType);

        virtual void    SuperBoostObjects();

        void    RobotBoost(ECareerType eType);
        void    Super(ECareerType eType);

        void    UpdateRankInfo() const;

    private:

        CUserWtr            _pUser;

        INT16               _wActiveIndex;                      // 当前出战的主动法宝位置索引（-1表示未出战）
        INT16               _wPassiveIndex[MAX_PASSIVE_COUNT];  // 当前出战的被动法宝位置索引（-1表示未出战）
};

#endif // #ifndef TRUMP_SLOTS_H

