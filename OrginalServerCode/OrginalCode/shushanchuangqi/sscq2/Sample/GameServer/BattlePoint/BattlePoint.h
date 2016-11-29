#ifndef BATTLE_POINT_H
#define BATTLE_POINT_H

#include "stdafx.h"
#include "Singleton.h"
#include "AttrShowCFG.h"


class CBattlePointOwner
{
    public:
        CBattlePointOwner();
        virtual ~CBattlePointOwner();

        void SetDirty() const;
        bool IsDirty() const;

        virtual void GetAllSkillsID(TVecUINT32& vecSkillsID) const = 0;
        virtual void AppendBPAttr(TVecFloat& vecAttr) const = 0;

        UINT32 GetBattlePoint() const;

    private:
        void RebuildBattlePoint() const;

    private:
        mutable UINT32 _dwBattlePoint;
        mutable bool   _bDirty;
};

class CBattlePointCalucator: public Singleton<CBattlePointCalucator>
{
    public:
        static UINT64 GetVersion() { return _qwVersion; } // XXX: 如果配置被重新加载这可以通过这个version来确认是否要更新
        bool Init();

        static UINT32 CalcAttrBattlePoint2(const TVecFloat& rvecAttr);
        static UINT32 CalcSkillBattlePoint2(const TVecUINT32& vecSkillsID);

        UINT32 CalcAttrBattlePoint(const TVecFloat& rvecAttr) const;
        UINT32 CalcSkillBattlePoint(const TVecUINT32& vecSkillsID) const;

    private:
        static UINT64 _qwVersion;
        TVecFloat _vecAttrFactor;
};

#define BattlePointCalucator CBattlePointCalucator::Instance()

#endif // #ifndef BATTLE_POINT_H
