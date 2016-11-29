#ifndef HEROFIGHTERXinFa_H_
#define HEROFIGHTERXinFa_H_

//#define XINFA_MAX_LEVEL     30
#include "GameServerLog.h"

using namespace NProtoCommon;
using namespace NFighterProt;

class CHeroFighterXinFa : public CPoolObj<CHeroFighterXinFa> 
{
public:
    CHeroFighterXinFa();
    ~CHeroFighterXinFa();

    void SetUser(const CUserPtr& pUser);
    CUserPtr GetUser() const;
    void SetFighter(const CFighterPtr& pFighter);
    CFighterPtr GetFighter() const;

    void AddXinFaFromDB(UINT32 dwXinFaID, UINT8 byXinFaLvl, int iSlot);
    void HeroFighterXFInfo(TVecXinFaInfo& vecXinFa) const;
    void AllLearnedXFInfo(TVecXinFaInfo& vecXinFa);                 // 所有已学会的心法信息

    EXinFaResult LearnXinFa(UINT32 dwXinFaID);                      // 学习心法
    EXinFaResult XinFaUpgrade(UINT32 dwXinFaID);                    // 心法升级
    EXinFaResult XinFaDisperse(UINT32 dwXinFaID);                   // 心法散功
    void FighterXinFaDismiss(TVecItemGenInfo& vecItems);


    void WriteFighterLog(EFighterOptType eType,UINT32 dwDetail, UINT64 qwResult,UINT16 wID);
    bool IsXinFa(UINT32 dwXinFaID);
    bool CheckXinFaSlot(UINT32 dwXinFaID, UINT8 type);
    int CheckXinFaSlot2(UINT32 dwXinFaID);
    bool CheckSpiritPower(UINT32 dwXinFaID);
    int GetXinFaSlot(UINT32 dwXinFaID);
    void SetXinFaSlot(UINT32 dwXinFaID, int iSlot);
    UINT8 GetXinFaLevel(UINT32 dwXinFaID);
    void SetXinFaLevel(UINT32 dwXinFaID, UINT8 byXinFaLevel);

    void Update2DB(EDataChange eDataChange, UINT32 dwXinFaID);

    TVecFloat GetHeroFighterXinFaAttr() const;                     // 散仙心法属性加成

    void InitXinFaAttr(UINT32 dwXinFaID);
    void RebuildAttr(UINT32 dwXinFaID);
    void AppendAttr(UINT32 dwXinFaID, TVecFloat& vecAttr);
    void SetDirty(UINT32 dwXinFaID, bool mark);
    bool IsDirty(UINT32 dwXinFaID);

    bool GMLearnXinFa(UINT32 dwXinFaID);                            // GM学习心法
    bool GMXinFaUpgrade(UINT32 dwXinFaID);                          // GM心法升级
private:
    typedef std::map<UINT32, SXinFaInfo> LearnedXF;                 // <心法ID，心法信息> 已经学会的心法信息
    typedef std::map<UINT32, TVecFloat> LearnedXFAttr;              // <心法ID，心法属性加成> 已学会的心法属性加成信息
    typedef std::map<UINT32, UINT8> LearnedXFUpdateMark;            // <心法ID，心法属性更新标记> 已学会的心法属性更新标记信息

    LearnedXF _LearnedXF;
    LearnedXFAttr _LearnedXFAttr;
    LearnedXFUpdateMark _LearnedXFUpdateMark;

    CUserWtr _pUser;
    CFighterWtr _pFighter;
};

#endif // HEROFIGHTERXinFa_H_
