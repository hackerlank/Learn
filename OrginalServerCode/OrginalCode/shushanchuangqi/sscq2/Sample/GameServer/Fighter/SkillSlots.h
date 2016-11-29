
#ifndef SKILLSLOTS_H_
#define SKILLSLOTS_H_

#include "ArrSlots.h"
#include "Skill.h" // XXX: for SKILL_*

#define SKILLS_SLOTS 9 // 主将所能学习的技能数
#define MAIN_UPSKILL_SLOTS 3 // 主将最多可装备的主动技能数
#define HERO_UPSKILL_SLOTS 6 // 散仙最多可装备的技能数
#define PET_UPSKILL_SLOTS 1 // 阵灵最多可装备的主动技能数

using namespace NProtoCommon;

template <size_t SIZE>
class CSkillSlots : public CArrSlots<int/*位置*/, UINT32/*技能或者心法ID*/, SIZE/*技能数*/>
{
public:
    explicit CSkillSlots() {}
    ~CSkillSlots() {}

    int GetSkillSlot(UINT32 dwSkillID) const;   //dwSkillID带有技能id、品质、等级
    UINT8 GetAllSkills(TVecUINT32& rVecSkills) const;
    bool HasSkillID(UINT32 dwSkillID) const;    //dwSkillID只是技能id
};

template <size_t SIZE>
class SlotsEnumerateBySkillIDQualityLevel : public Enumerator<typename CArrSlots<int, UINT32, SIZE>::value_type>
{
public:
    typedef typename CArrSlots<int, UINT32, SIZE>::value_type value_type;

public:
    SlotsEnumerateBySkillIDQualityLevel(UINT32 dwSkillID)
        : _dwSkillID(dwSkillID), _iSlot(INVALID_SLOT) { }

    bool operator()(const value_type* obj) const
    {
        if (obj && std::get<1>(*obj) && std::get<2>(*obj) == _dwSkillID)
            _iSlot = std::get<0>(*obj);
        return true;
    }

public:
    UINT32 _dwSkillID;
    mutable int _iSlot;
};

template <size_t SIZE>
int CSkillSlots<SIZE>::GetSkillSlot(UINT32 dwSkillID) const
{
    SlotsEnumerateBySkillIDQualityLevel<SIZE> en(dwSkillID);
    CArrSlots<int, UINT32, SIZE>::enumerate(en);
    return en._iSlot;
}

template <size_t SIZE>
class SlotsEnumerateBySkillID : public Enumerator<typename CArrSlots<int, UINT32, SIZE>::value_type>
{
public:
    typedef typename CArrSlots<int, UINT32, SIZE>::value_type value_type;

public:
    SlotsEnumerateBySkillID(UINT32 dwSkillID)
        : _dwSkillID(dwSkillID), _bHased(false) { }

    bool operator()(const value_type* obj) const
    {
        if (obj && std::get<1>(*obj) && SKILL_ID(std::get<2>(*obj)) == _dwSkillID)
            _bHased = true;
        return true;
    }

public:
    UINT32 _dwSkillID;
    mutable bool _bHased;
};

template <size_t SIZE>
bool CSkillSlots<SIZE>::HasSkillID(UINT32 dwSkillID) const
{
    SlotsEnumerateBySkillID<SIZE> en(dwSkillID);
    CArrSlots<int, UINT32, SIZE>::enumerate(en);
    return en._bHased;
}

template <size_t SIZE>
class EnumerateGetAll : public Enumerator<typename CArrSlots<int, UINT32, SIZE>::value_type>
{
public:
    typedef typename CArrSlots<int, UINT32, SIZE>::value_type value_type;

public:
    EnumerateGetAll(TVecUINT32& rVecSkills) : _rVecSkills(rVecSkills) {}

    bool operator()(const value_type* obj) const
    {
        if (obj && std::get<1>(*obj) && std::get<2>(*obj))
            _rVecSkills.push_back(std::get<2>(*obj));
        return true;
    }

public:
    TVecUINT32& _rVecSkills;
};

template <size_t SIZE>
UINT8 CSkillSlots<SIZE>::GetAllSkills(TVecUINT32& rVecSkills) const
{
    EnumerateGetAll<SIZE> en(rVecSkills);
    CArrSlots<int, UINT32, SIZE>::enumerate(en);
    return rVecSkills.size();
}

#endif // SKILLSLOTS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

