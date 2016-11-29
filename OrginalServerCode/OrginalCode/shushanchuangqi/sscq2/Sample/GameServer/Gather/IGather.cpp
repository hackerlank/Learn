#include "stdafx.h"
#include "Map.h"
#include "GatherMgr.h"
#include "Player.h"
#include "User.h"
#include "DungeonMgr.h"
#include "Loot.h"
#include "GameServerSysMail.h"
#include "SysMsgDefine.h"
#include "Protocols.h"
SGatherCFGEx::SGatherCFGEx():
    _dwOtherType(0)
    ,_bLuaHasCanGather(false)
    ,_bLuaHasFinishGather(false)
    ,_bCheckLua(false)
{
}

SGatherCFGEx::SGatherCFGEx(const SGatherCFG& rCfg):
    SGatherCFG(rCfg)
    ,_dwOtherType(0)
    ,_bLuaHasCanGather(false)
    ,_bLuaHasFinishGather(false)
    ,_bCheckLua(false)
{
}

bool SGatherCFGEx::CheckHasOtherType(EOtherType eType)
{
    return (_dwOtherType & eType) > 0;
}

UINT8 SGatherCFGEx::CanGagtherFromLua(CPlayer &rPlayer)
{
    DoCheckLua();
    if (!_bLuaHasCanGather)
    {
        return 0;
    }
    return Config.GetScript().CanGather(_wGatherId,rPlayer.GetUser());
}

void  SGatherCFGEx::FinishGather(CPlayer &rPlayer)
{
    DoCheckLua();
    if (!_bLuaHasFinishGather)
    {
        return ;
    }
    Config.GetScript().OnFinishGather(_wGatherId,rPlayer.GetUser());

}

void SGatherCFGEx::DoCheckLua()
{
    if (_bCheckLua)
    {
        return ;
    }
    _bLuaHasCanGather =  Config.GetScript().HasCanGatherFunction(_wGatherId);
    _bLuaHasFinishGather =  Config.GetScript().HasOnFinishGatherFunction(_wGatherId);
    _bCheckLua = true;

}

IGather::IGather(UINT16 wGatherID, UINT32 dwInstID, SGatherCFGEx& rGatherCFG,UINT64 qwVersion):
    _wGatherID(wGatherID), _dwInstID(dwInstID), _pGatherCFGEx(&rGatherCFG),_qwVersion(qwVersion)
{ }

void IGather::CancelAll(EGatherResult eResult)
{
}
IGather::~IGather() { }

SGatherCFGEx& IGather::GetGatherConfig()
{
    if(_qwVersion != CGatherMgr::GetVersion())
        _pGatherCFGEx = CGatherMgr::GetGatherConfig(_pGatherCFGEx->_wGatherId);
    return *_pGatherCFGEx;
}
UINT8 IGather::byIndex()
{
    return _byIndex;
}


void IGather::Disappear()
{
    CGameMapPtr pMap = GetMap();
    if(pMap != NULL)
        pMap->GatherDisappear(*this);
}


void IGather::GetGatherAppear(SGatherAppear& rGatherAppear, UINT64 qwUsrID /*= 0*/)
{
    rGatherAppear.wGatherID = GetGatherConfig()._wGatherId;
}

EGatherResult IGather::CanConsume(CPlayer& rPlayer)
{
    for(auto it = GetGatherConfig()._vecCond.begin();it != GetGatherConfig()._vecCond.end();it++)
    {
        CGatherCondBasePtr pCond = *it;
        EGatherResult eResult =pCond->CheckCond(rPlayer);
        if(eResult != eGatherSuccess)
        {
            return eResult ;
        }
    }
    return eGatherSuccess;
}


void  IGather::Consume(CPlayer& rPlayer)
{
    for(auto it = GetGatherConfig()._vecCond.begin();it != GetGatherConfig()._vecCond.end();it++)
    {
        CGatherCondBasePtr pCond = *it;
        pCond->DoCond(rPlayer);
    }
}

EGatherResult  IGather::CanGater(CPlayer& rPlayer,bool bIsFinish)
{
    //先查看包裹
    if (GetGatherConfig()._byEmptyPack >rPlayer.GetUser().GetPack().GetEmptyCount())
    {
        return eGatherPackEmptyMin;
    }
    EGatherResult eResult = CanConsume(rPlayer);
    if(eResult != eGatherSuccess)
    {
        return eResult;
    }
    return eResult;
}

EGatherResult  IGather::GatherFinish(CPlayer& rPlayer,std::vector<SItemGenInfo>*pvecItems,TVecResource* pvecRes)
{
    EGatherResult eResult = CanGater(rPlayer,true);
    if(eResult != eGatherSuccess)
    {
        return eResult;
    }
    Consume(rPlayer);
    //发送奖励
    UINT32 dwDropId = GetGatherConfig()._dwDropId;
    TVecItemGenInfo vecItems;
    TVecResource vecRes;
    LOOT.Roll(dwDropId, vecItems,vecRes);
    if(!vecItems.empty())
    {
        CPack& oPack = rPlayer.GetUser().GetPack();
        if(!oPack.CanAddItem(vecItems))
        {
            rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgMonsterDropPackFull));
            //发送邮件
            NMailProt::SysMailSendTxt stBody;
            stBody.dwstrMsgID = BODY_GATHERDROP;
            stBody.vecParam.push_back(GetGatherConfig()._strName);
            TVecUINT64 vecTargets;
            vecTargets.push_back(rPlayer.GetUser().GetUserID());
            GameServerSysMail::SendSysMail(SEND_GATHERDROP,TITLE_GATHERDROP,stBody,vecTargets,&vecItems);
        }
        else
        {
            oPack.AddItem(vecItems,NLogDataDefine::ItemFrom_Gather);
        }
    }
    if(!vecRes.empty())
    {
        CStore::AddResource(rPlayer.GetUser(),vecRes,NLogDataDefine::ItemFrom_Gather);
    }
    if( NULL != pvecItems)
    {
        for(auto iter =vecItems.begin();iter != vecItems.end();iter++)
        {
            pvecItems->push_back(*iter);
        }
    }
    if(NULL != pvecRes)
    {
        for(auto iter =vecRes.begin();iter != vecRes.end();iter++)
        {
            pvecRes->push_back(*iter);
        }
    }
    rPlayer.GetUser().GetTaskPkg().OnGather(_wGatherID);
   GetGatherConfig().FinishGather(rPlayer);
   //如果在采集副本中
    UINT64 qwDgnID = rPlayer.GetDgnInstID();
    if(qwDgnID != 0)
    {
         CDungeonPtr pDgn = CDungeonMgr::GetDungeon(qwDgnID);
         if(pDgn)
         {
             pDgn->OnGather(_wGatherID,rPlayer);
         }
    }

    if(IsGatherType(eGatherType_Chest))
    {
        {
            TVecINT32 vecParam;
            vecParam.push_back(GetGatherID());
            rPlayer.OnEvent(eEventType_SkyTreasureGet,vecParam);
        }

        {
            TVecINT32 vecParam;
            vecParam.push_back(1);
            rPlayer.OnEvent(eEventType_SkyTreasureJoin,vecParam);
        }
    }

    return eGatherSuccess;
}
bool  IGather::CanGatherTwoPerson()
{
    return GetGatherConfig()._IsPublic > 0;

}


bool IGather::IsGatherType(EGatherType eGatherType)
{
    return GetGatherConfig()._AssetType == eGatherType;
}
