#ifndef TRUMP_H_
#define TRUMP_H_

#include "Item.h"
#include "ItemProt.h"
#include "BoostObject.h"

// 法宝
class CTrump : public CItem, public CBoostObject
{
    public:
        CTrump(UINT16 wItemID);
        virtual ~CTrump();
        DEF_NEW_DELETE(CTrump);

        virtual SItemPtr ToProt() const;
        bool FromStream(const STrump& rStream);
        bool ToStream(STrump& rStream) const;

        UINT16 GetLevel() const { return _wLevel; }

        void SetRoleID(UINT64 qwRoleID);
        UINT64 GetRoleID() const;


        UINT8 GetUsed() const;
        void  SetUsed(UINT8 byIndex = 0);

        UINT32 GetExp()             const;
        UINT16 GetIntensifyLevel()  const;
        UINT16 GetRank()            const;

        void GetHaloAttr(TVecFloat& rvecAttr) const;
        void GetExtraAttr(TVecFloat& rvecAttr) const;
        void GetActiveAttr(TVecFloat& rvecAttr) const;

        void WriteTrumpLog(UINT32 dwID,string &sName,UINT16 wLevel,UINT32 dwSkillID);
        UINT32 GetSkill()     const; // 返回带等级的技能ID

        ETrumpResult Upgrade(bool bOneKey, CUserPtr pUser, UINT32& dwAddExp, UINT32& dwCount);
        ETrumpResult Evolve(CUserPtr pUser);

        UINT32 GetBattlePoint() const;

        virtual EBoostObjectType GetType() const { return eBOTTrump; };
        virtual void Super();

    private:
        UINT64  _qwRoleID;  //
        UINT8   _bUsed;     // 是否出战(大于0出战  主动法宝1 被动法宝1,2,3)
        UINT32  _dwExp;     // 祭炼值
        UINT16  _wLevel;    // 祭炼阶数
        UINT16  _wRank;     // 祭炼等级
};

#endif // TRUMP_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

