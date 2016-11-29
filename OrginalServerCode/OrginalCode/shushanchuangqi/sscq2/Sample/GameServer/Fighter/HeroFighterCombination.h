
#ifndef HEROFIGHTERCOMBINATION_H_
#define HEROFIGHTERCOMBINATION_H_

#include "FighterProt.h"
#include "ProtoCommon.h"

using namespace NProtoCommon;
using namespace NFighterProt;


class CHeroFighterCombination
{
public:
    CHeroFighterCombination(UINT8 byGroupID);
    ~CHeroFighterCombination() {}

    UINT8 GetID() const { return _byGroupID; }
    UINT8 GetLevel() const { return _byGroupLvl; }
    UINT32 GetExp() const { return _dwGroupExp; }
    void SetLevel(UINT8 byLvl) { _byGroupLvl = byLvl; }
    void SetExp(UINT32 dwExp) { _dwGroupExp = dwExp; }
    bool IsFightInEMei() const { return _bInEMei; }
    bool IsFightInLineUp() const { return _bInLineUp; }
    void SetFightLineUp(bool b) { _bInLineUp = b; }
    void SetFightEMei(bool b) { _bInEMei = b; }

    bool IsDirty() const { return _bDirty; }
    void SetDirty(bool bDirty) { _bDirty = bDirty; }

    void ToProt(SFighterCombination& rInfo);
    void AppendAttr(TVecFloat& vecAttr);
private:
    void RebuildAttr();
private:
    UINT8 _byGroupID;
    UINT8 _byGroupLvl;
    UINT32 _dwGroupExp; //当前等级下多余的经验
    bool _bInLineUp;    //当前是否出战在阵型
    bool _bInEMei;      //当前是否出战在守卫峨眉
    bool _bDirty;
    TVecFloat _vecFinalAttr; // 属性加成
};

#endif // HEROFIGHTERCOMBINATION_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

