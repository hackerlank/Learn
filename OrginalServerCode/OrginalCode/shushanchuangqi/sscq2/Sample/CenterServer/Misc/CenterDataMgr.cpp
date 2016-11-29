#include "stdafx.h"
#include "CenterDataMgr.h"
#include "BeautyLogSvrS.h"
#include "Center2DBCommC.h"
#include "UserMgr.h"
#include "InvitedFriendMgr.h"
#include "DemonTowerMgr.h"
CCenterDataMgr g_CenterDataMgr;
extern CCenter2DBCommC g_Center2DBCommC; 

CCenterDataMgr::CCenterDataMgr()
{
    _qwMaxBeautyInstID = 1;
    _bLoading = true;

}

void CCenterDataMgr::InitDB()
{
    g_Center2DBCommC.Send_GetCenterData( [this](UINT8 byRet_, //0为成功，1为失败，2为超时
			const TVecCenterData& vecCenterData //(返回值)中心服数据
		)
        {
            if(byRet_)
            {
                LOG_CRI<<"GetCenterData fail!!!";
                return;
            }
            //加载完数据标志
            _bLoading = false;
            g_CenterDataMgr.OnLoad(vecCenterData);
            LOG_INF<<"CCenterDataMgr::InitDB Sucess!!";
        }
	);

}

void CCenterDataMgr::OnLoad(const TVecCenterData& vecCenterData)
{
    for(size_t i=0; i < vecCenterData.size(); i++)
    {
        const SCenterData& oCenterData = vecCenterData[i];
        ECenterData eType = (ECenterData)oCenterData.wType;
        switch(eType)
        {
            case eCenterDate_BeautyLog:
                {
                    OnBeautyLogLoad(oCenterData);
                }
                break;
            case eCenterDate_InviteFriend:
                {
                    g_InvitedFriendMgr.OnLoad_InviteFriend(oCenterData);

                }
                break;
            case eCenterDate_InviteTask:
                {
                    g_InvitedFriendMgr.OnLoad_InviteTask(oCenterData);
                }
                break;
            case eCenterDate_DemonTower_MinRonds:
                {
                    g_DemonTowerMgr.OnLoad_MinTurns(oCenterData);
                }
                break;
            case eCenterDate_DemonTower_MinBattlePoint:
                {
                    g_DemonTowerMgr.OnLoad_MinBattlePoint(oCenterData);
                }
                break;
            default:
                {
                    LOG_CRI<<"ERROR ECenterData:"<<oCenterData.wType;
                }
                break;
        }
    }
}

//美女log数据
void CCenterDataMgr::OnBeautyLogLoad(const SCenterData& oCenterData)
{
    _dequeBeautyLog.push_back(oCenterData);

    if(oCenterData.qwInstID > _qwMaxBeautyInstID)
    {
        _qwMaxBeautyInstID = oCenterData.qwInstID;
    }

}

void CCenterDataMgr::OnGetBeautyLog(UINT64 dwUserID,TVecBeautyLog& vecBeautyLog)
{
    for(auto itr = _dequeBeautyLog.begin(); itr != _dequeBeautyLog.end(); ++itr)
    {
        SCenterData& oCenterData = *itr;
        SBeautyLog oBeautyLog;
        oBeautyLog.qwUserID = oCenterData.qwParam;
        oBeautyLog.strRoleName = oCenterData.strParam;
        oBeautyLog.byColor = oCenterData.dwParam1;
        oBeautyLog.wItemID = oCenterData.dwParam2;
        oBeautyLog.dwCount = oCenterData.dwParam3;

        vecBeautyLog.push_back(oBeautyLog);
    }
    LOG_INF<<"OnGetBeautyLog qwUserID:"<<dwUserID;
}

void CCenterDataMgr::OnAddBeautyLog(const SBeautyLog& oBeautyLog)
{
    if(_bLoading)
    {
        LOG_CRI<<"_bLoading error!!";
        return;
    }
    SCenterData oCenterData;
    oCenterData.wType = eCenterDate_BeautyLog;
    oCenterData.qwInstID = GenBeautyInstID();
    oCenterData.qwInstID2 = 0;
    oCenterData.qwParam = oBeautyLog.qwUserID;
    oCenterData.strParam = oBeautyLog.strRoleName;
    oCenterData.dwParam1 = oBeautyLog.byColor; 
    oCenterData.dwParam2 = oBeautyLog.wItemID;
    oCenterData.dwParam3 = oBeautyLog.dwCount;

    _dequeBeautyLog.push_back(oCenterData);
    Update2DB(oCenterData,false);
    while(_dequeBeautyLog.size() > MAX_BEAUTY_LOG_COUNT)
    {
        SCenterData& oFrontCenterData = _dequeBeautyLog.front();
        Update2DB(oFrontCenterData,true);
        _dequeBeautyLog.pop_front();
    }

    /*
    CUserPtr pUser =  CUserMgr::GetUserByUserID(oBeautyLog.qwUserID);
    if(pUser&&pUser->IsOnline())
    {
        pUser->SendPkg(g_BeautyLogSvrS.SendClt_AddBeautyLogNotify(NULL,0,oBeautyLog));
    }
*/
    g_BeautyLogSvrS.SendClt_AddBeautyLogNotify(NULL,0,oBeautyLog);
}

void CCenterDataMgr::Update2DB(const SCenterData& oCenterData,bool bDelete)
{
    g_Center2DBCommC.Send_UpateCenterData(oCenterData,bDelete);
}
UINT64 CCenterDataMgr::GenBeautyInstID()
{
    _qwMaxBeautyInstID++;
    return _qwMaxBeautyInstID;
}
