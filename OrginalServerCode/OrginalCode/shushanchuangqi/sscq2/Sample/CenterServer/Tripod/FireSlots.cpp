#include "Protocols.h"
#include "FireSlots.h"
#include "RoleInfoDefine.h"
#include "TripodMgr.h"
#include "User.h"

using namespace NRoleInfoDefine;

class FireEnumerate4List : public Enumerator<typename CVecSlots<int, CFirePtr>::value_type>
{
public:
    typedef CVecSlots<int, CFirePtr>::value_type value_type;

public:
    FireEnumerate4List(TVecFireInfo& vecFires) : vecFires(vecFires) {}

    bool operator()(value_type* obj)
    {
        if (obj && std::get<1>(*obj) && std::get<2>(*obj))
        {
            SFireInfo oFireInfo;
            std::get<2>(*obj)->ToProt(oFireInfo);
            vecFires.push_back(oFireInfo);
        }
        return true;
    }

public:
    TVecFireInfo& vecFires;
};

bool CFireSlots::LoadFireFromDB(const TVecFireInfo& vecFireInfo)
{
    size_t szFires = vecFireInfo.size();
    for (size_t i = 0; i < szFires; ++i)
    {
        UINT16 wFireID = vecFireInfo[i].wFireID;
        CFirePtr pFire = GetFire(wFireID);
        if (pFire)
            continue;
        pFire.reset(new CFire(wFireID));
        pFire->SetSucceedCnt(vecFireInfo[i].dwSucceed);
        pFire->SetRemainCnt(vecFireInfo[i].dwRemain);

        Set(wFireID-1, pFire);
    }
    return true;
}

bool CFireSlots::HasRemainCnt(UINT16 wFireID)
{
    CFirePtr pFire = GetFire(wFireID);
    if (!pFire)
        return false;
    SStoveFireCFGEx* pFireCfg = CTripodMgr::GetStoveFireCfg(wFireID);
    if (!pFireCfg)
        return false;
    if (pFireCfg->_LimitTimes == 0)     //不限制起火次数
        return true;
    return pFire->GetRemainCnt() > 0;
}

void CFireSlots::GetAllFires(TVecFireInfo& vecFires)
{
    FireEnumerate4List en(vecFires);
    enumerate(en);
    for (auto& rInfo : vecFires)
    {
        LOG_WRN << "ID: " << rInfo.wFireID << ", Remain = " << rInfo.dwRemain << ".";
    }
}

bool CFireSlots::ActiveFire(UINT16 wFireID)
{
    SStoveFireCFGEx* pFireCfg = CTripodMgr::GetStoveFireCfg(wFireID);
    if (!pFireCfg)
        return false;
    CFirePtr pFire = GetFire(wFireID);
    if (!pFire)
    {
        pFire.reset(new CFire(wFireID));
        if (!Set(wFireID-1, pFire))
            return false;
        pFire->SetRemainCnt(pFireCfg->_LimitTimes);
        Update2DB(pFire, eOpAdd);
    }
    else
    {
        pFire->AddRemainCnt(pFireCfg->_LimitTimes);
        Update2DB(pFire, eOpUpdate);
    }

    TVecINT32 vecParam;
    vecParam.push_back(wFireID);
    vecParam.push_back(pFire->GetRemainCnt());
    _rUser.OnEvent(eEventType_StoveFireLearning, vecParam);
    return true;
}

void CFireSlots::Update2DB(CFirePtr& pFire, EDataChange eDataChange/* = eOpUpdate*/)
{
    string strData;
    COutArchive iar(strData);
    SFireInfo oFireInfo;
    pFire->ToProt(oFireInfo);
    iar << oFireInfo;
    g_Center2DBCommC.Send_RoleDataUpdate(_rUser.GetUserID(), eTypeTripodFireInfo, eDataChange, strData);
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

