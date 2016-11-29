
#ifndef FORMATIONPET_H_
#define FORMATIONPET_H_

//#include "FormationSlots.h"
#include "PetSlots.h"
#include "RoleInfoDefine.h"
#include "BeastSoul.h"

using namespace NRoleInfoDefine;

class CUser;

class CFormationPet
{
public:
    CFormationPet(CUser& rUser);
    ~CFormationPet() {}

    //CFormationPtr GetCurrFormation() { return _oFormations.GetCurrFormation(); }
    CPetPtr GetCurrPet() { return _oPets.GetCurrPet(); }

    //const CFormationSlots& GetFormationSlots() const { return _oFormations; }
    //CFormationSlots& GetFormationSlots()  { return _oFormations; }

    const CPetSlots& GetPetSlots() const { return _oPets; }
    CPetSlots& GetPetSlots() { return _oPets; }
    CBeastSoul& GetBeastSoul() { return _oBeastSoul; }
    const CBeastSoul& GetBeastSoul() const{ return _oBeastSoul; }

    //bool LoadFormationFromDB(const SFormationInfo& sFormationInfo);
    bool LoadPetDataFromDB(const SPetDataInfo& sPetDataInfo);
    bool LoadRolePetFromDB(const SRolePetInfo& sRolePetInfo);
    bool LoadBeastSoulFromDB(const TVecBeastSoulInfo& vecBeastSoulInfo);

private:
    CUser& _rUser;
    //CFormationSlots _oFormations;
    CPetSlots _oPets;
    CBeastSoul  _oBeastSoul;  // 兽魂
};

#endif // FORMATIONPET_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

