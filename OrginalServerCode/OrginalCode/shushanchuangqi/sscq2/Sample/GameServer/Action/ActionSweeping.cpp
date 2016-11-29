#include "ActionSweeping.h"
#include "DungeonMgr.h" 
#include "Protocols.h"
#include "Player.h"
#include "User.h"
#include "Protocols.h"
using namespace NDungeonProt;
void CActionSweeping::End()
{
    CActionBase::End();

    if(_pManager&&_pManager->IsInitSweep())
         _pManager->SetInitSweep(false);
}

void CActionSweeping::Break()
{
    //发送消息，扫荡中止
    CActionBase::Break();
    if(_pManager)
    {
        ClearDB(_pManager->GetPlayer());
        if(_pManager->IsInitSweep())
            _pManager->SetInitSweep(false);
    }

}

void CActionSweeping::TimeOut()
{
    CActionBase::TimeOut();
    if(_pManager != NULL)
    {
        //LOG_INF<<"CActionSweeping TimeOut";
        std::vector<SItemGenInfo> VecItems;
        TVecResource vecRes;
        EDungeonResult result = CDungeonMgr::CleanDGN(_wDgnId,_pManager->GetPlayer(),&VecItems,&vecRes);
        if(result != eDungeonSuccess)
        {
            Break();
            _pManager->GetPlayer().SendPkg(g_DungeonProtS.BuildPkg_SweepingEndNotify(result));
            g_DungeonProtS.SystemMsgNotify(result,_pManager->GetPlayer().GetUser().GetUserID());
            return ;
        }
        else
        {
            NDungeonProt::SSweepItem oSweepItem;
            oSweepItem.wTurn = _wMaxCount - _dwTimes;
            oSweepItem.vecItemGenInfo = VecItems;
            oSweepItem.vecResource = vecRes;
            _vecSweepItem.push_back(oSweepItem);
            TVecINT32 vecData;
            vecData.push_back(_wDgnId);
            _pManager->GetPlayer().GetEventMgr()->OnEvent(eEventType_DungeonAutoFight,vecData);
            _pManager->GetPlayer().GetDgnPkg().PlayerCompleteDgn(_wDgnId,0,true);
            vecData.clear();
            vecData.push_back(1);
            _pManager->GetPlayer().GetEventMgr()->OnEvent(eEventType_DungeonFinishAndAuto,vecData);

            //LOG_INF<<"CActionSweeping::TimeOut:"<<oSweepItem.wTurn<<"|"<<_wMaxCount;
            _pManager->GetPlayer().SendPkg(g_DungeonProtS.BuildPkg_SweepingUpdateNotify(VecItems,vecRes,oSweepItem.wTurn,ReserverTime()));
        }

        if(_dwTimes)
        {
            SaveDB(_pManager->GetPlayer());
        }
        else
        {
            //发送消息，扫荡结束
            _pManager->GetPlayer().SendPkg(g_DungeonProtS.BuildPkg_SweepingEndNotify(eDungeonSuccess));

            ClearDB(_pManager->GetPlayer());
            if(_pManager->IsInitSweep())
                _pManager->SetInitSweep(false);


        }
    }

}

bool CActionSweeping::CheckSpeedUp(UINT8 byOptions)
{
    const SDgnInfo* pDgnInfo = CDungeonMgr::GetDgnInfo(_wDgnId);
    if(pDgnInfo == NULL)
    {
        return false;
    }
    if(byOptions == 0)
    {
        UINT32 dwCoin = pDgnInfo->oDgnCfg._dwSweepingCoin;
        if(_pManager != NULL)
        {

            if(!_pManager->GetPlayer().GetUser().CanSubMoney(EMONEY_GOLD,dwCoin))
            {
                return false;
            }
            _pManager->GetPlayer().GetUser().SubMoney(EMONEY_GOLD,dwCoin,NLogDataDefine::ItemTo_SweepingSpeedUp);
            return true;
        }

    }
    return false ;
}

bool CActionSweeping::IsTimeOut(time_t tNow)
{
    if(_pManager->GetPlayer().GetUser().GetVIPLevel()>= SParamConfig::byAutoFightNoCDRequiredVipLevel)
    {
        return true;
    }

    if(_LastEndTimer < tNow)
    {
        _pManager->SetInitSweep(true);
        return true;
    }

    if(_pManager->IsInitSweep())
        _pManager->SetInitSweep(false);

    if(_dwSpeedTime)
    {
        UINT32 lastTime = _LastEndTimer - tNow;

        if(lastTime < _dwSpeedTime)
        {
            _dwSpeedTime  -= lastTime;
            _LastEndTimer -= lastTime;
            //LOG_INF<<"add speed time:"<<lastTime;
            return true;
        }
        else //加速时间耗尽
        {
            //LOG_INF<<"add speed time LACK:"<<_dwSpeedTime;
            _LastEndTimer -= _dwSpeedTime;
            _dwSpeedTime = 0;
        }
    }

    return false;

}

void  CActionSweeping::ClearDB(CPlayer& rPlayer)
{
    SSweepInfo oSweepInfo;
    oSweepInfo.qwRoleID = rPlayer.GetRoleID();

    string strData;
    COutArchive iar(strData);
    iar << oSweepInfo;

    g_Game2DBCommC.Send_RoleDataUpdate(rPlayer.GetUserID(),eTypeSweep, eOpDel, strData);

}


void  CActionSweeping::SaveDB(CPlayer& rPlayer)
{
    SSweepInfo oSweepInfo;
    oSweepInfo.qwRoleID = rPlayer.GetRoleID();
    oSweepInfo.wCurDgnID = _wDgnId;
    oSweepInfo.wCurCount = _dwTimes;
    oSweepInfo.dwReserverTime = _LastEndTimer>time(NULL)?_LastEndTimer-time(NULL):0;
    oSweepInfo.dwSaveTime = time(NULL);
    oSweepInfo.wCount = _wMaxCount;  //最大次数
    //以下字段保留
    //oSweepInfo.wOptions
    //oSweepInfo.strVecDgn

    string strData;
    COutArchive iar(strData);
    iar << oSweepInfo;

    g_Game2DBCommC.Send_RoleDataUpdate(rPlayer.GetUserID(),eTypeSweep,eOpAdd, strData);
}


