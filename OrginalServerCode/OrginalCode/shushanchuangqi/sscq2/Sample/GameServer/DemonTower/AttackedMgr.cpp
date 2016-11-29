#include "stdafx.h"
#include "Protocols.h"
#include "Player.h"
#include "User.h"
#include "DemonTowerMgr.h"
#include "AttackedMgr.h"
#include "SysMsgDefine.h"
CAttackedMgr::CAttackedMgr(CPlayer& rPlayer):
    _rPlayer(rPlayer)
{
    _vecQueRoleAttaked.resize(eAttacked_Max);

    _vecQueRoleAttaked[eAttacked_Demontower].dwMaxSize = 5;

    _dwMaxID = 1;
}

bool CAttackedMgr::LoadFromDB(const RoleDataInfo& rRoleDataInfo)
{
    const TVecRoleAttaked& vecRoleAttaked = rRoleDataInfo.vecRoleAttaked;
    for(auto itr = vecRoleAttaked.begin(); itr != vecRoleAttaked.end(); ++itr)
    {
        const SRoleAttaked& rInfo = *itr;
        if(rInfo.dwPos > _dwMaxID)
        {
            _dwMaxID = rInfo.dwPos;
        }

        if(rInfo.dwFighterType < _vecQueRoleAttaked.size())
        {
            SRoleAttakedPtr pSRoleAttaked(new SRoleAttaked);
            if(!pSRoleAttaked)
            {
                LOG_CRI<<"null pSRoleAttaked!";
                return false;
            }

            *pSRoleAttaked = rInfo;
            _vecQueRoleAttaked[rInfo.dwFighterType].queAttacked.push_back(pSRoleAttaked);

        }
    }

    return true;

}

void CAttackedMgr::Update2DB(SRoleAttaked& rInfo, EDataChange eDataChange/* = eOpUpdate*/)
{
    string strData;
    COutArchive iar(strData);
    iar << rInfo;
    
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(),eTypeAttacked, eDataChange, strData);
}

UINT32 CAttackedMgr::GenerateID()
{
    _dwMaxID++;
    return _dwMaxID;

}

void CAttackedMgr::GetAttakedList(TVecRoleAttaked& vecRoleAttaked,UINT32 dwFightType)
{
    if(dwFightType<_vecQueRoleAttaked.size())
    {
        SAttackQueue& oAttackQueue = _vecQueRoleAttaked[dwFightType];
        for(auto itr = oAttackQueue.queAttacked.rbegin(); itr != oAttackQueue.queAttacked.rend(); ++itr)
        {
            vecRoleAttaked.push_back(**itr);
        }

    }

}

void CAttackedMgr::OnAttackedInfo(const SRoleAttaked& rInfo)
{
    LOG_INF<<"OnAttackedInfo: attack roleId:"<<rInfo.qwRoleID;
    if(rInfo.dwFighterType >= _vecQueRoleAttaked.size())
    {
        LOG_CRI<<"Error dwFighterType: "<<rInfo.dwFighterType;
        return;
    }

    SAttackQueue& oAttackQueue = _vecQueRoleAttaked[rInfo.dwFighterType];

    if(oAttackQueue.queAttacked.size()>=oAttackQueue.dwMaxSize)
    {
        SRoleAttakedPtr pRoleAttaked = oAttackQueue.queAttacked.front();

        Update2DB(*pRoleAttaked,eOpDel);

        oAttackQueue.queAttacked.pop_front();
    }

    SRoleAttakedPtr pSRoleAttaked(new SRoleAttaked);
    if(!pSRoleAttaked)
    {
        LOG_CRI<<"null pSRoleAttaked!";
        return;
    }
    *pSRoleAttaked = rInfo;
    pSRoleAttaked->qwRoleID = _rPlayer.GetRoleID();
    pSRoleAttaked->dwPos = GenerateID();
    oAttackQueue.queAttacked.push_back(pSRoleAttaked);
    Update2DB(*pSRoleAttaked);

}

