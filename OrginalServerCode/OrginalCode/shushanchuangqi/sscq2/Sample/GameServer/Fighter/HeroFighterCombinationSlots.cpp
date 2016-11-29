// =====================================================================================
//
//       Filename:  HeroFighterCombinationSlots.cpp
//
//    Description:  散仙组合槽
//
//        Version:  1.0
//        Created:  12/04/2014 05:17:42 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  SunTao (Steven), sunt@kingnet.com
//   Organization:
//
// =====================================================================================
#include "HeroFighterCombinationSlots.h"
#include "RoleInfoDefine.h"
#include "Protocols.h"
#include "User.h"

class CombinationEnumerate4List : public Enumerator<typename CVecSlots<int, CHeroFighterCombinationPtr>::value_type>
{
public:
    typedef CVecSlots<int, CHeroFighterCombinationPtr>::value_type value_type;

public:
    CombinationEnumerate4List(TVecFighterCombination& vecFighterCombinations) : vecFighterCombinations(vecFighterCombinations) {}

    bool operator()(value_type* obj)
    {
        if (obj && std::get<1>(*obj) && std::get<2>(*obj))
        {
            SFighterCombination oFighterCombination;
            std::get<2>(*obj)->ToProt(oFighterCombination);
            vecFighterCombinations.push_back(oFighterCombination);
        }
        return true;
    }

public:
    TVecFighterCombination& vecFighterCombinations;
};

CHeroFighterCombinationSlots::CHeroFighterCombinationSlots(CUser& rUser)
    : CVecSlots(100), _rUser(rUser)
{}

void CHeroFighterCombinationSlots::GetAllFighterCombination(TVecFighterCombination& vecCombinationInfo)
{
    CombinationEnumerate4List en(vecCombinationInfo);
    enumerate(en);
}

void CHeroFighterCombinationSlots::UpdateToClient()
{
    TVecFighterCombination vecCombinationInfo;
    CombinationEnumerate4List en(vecCombinationInfo);
    enumerate(en);
    _rUser.SendPkg(g_FighterProtS.BuildPkg_FighterCombinationNotify(vecCombinationInfo));
}

bool CHeroFighterCombinationSlots::LoadFromDB(const TVecFighterCombination& vecFighterCombination)
{
    size_t szCombinations = vecFighterCombination.size();
    for (size_t i = 0; i < szCombinations; ++i)
    {
        UINT8 byGroupID= vecFighterCombination[i].byGroupID;
        CHeroFighterCombinationPtr pFgtComb = GetFighterCombination(byGroupID);
        if (pFgtComb)
            continue;
        pFgtComb.reset(new CHeroFighterCombination(byGroupID));
        pFgtComb->SetLevel(vecFighterCombination[i].byGroupLvl);
        pFgtComb->SetExp(vecFighterCombination[i].dwGroupExp);
        pFgtComb->SetFightLineUp(vecFighterCombination[i].byInLineUp > 0);
        pFgtComb->SetFightEMei(vecFighterCombination[i].byInEMei > 0);

        Set(byGroupID-1, pFgtComb);
    }
    return true;
}

void CHeroFighterCombinationSlots::Update2DB(CHeroFighterCombinationPtr& pFgtComb, EDataChange eDataChange/* = eOpUpdate*/)
{
    string strData;
    COutArchive iar(strData);
    SFighterCombination oFighterCombination;
    pFgtComb->ToProt(oFighterCombination);
    iar << oFighterCombination;
    g_Game2DBCommC.Send_RoleDataUpdate(_rUser.GetUserID(), eTypeFighterComination, eDataChange, strData);
}

