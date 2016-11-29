#include "TitlePkg.h"
#include "Protocols.h"
#include "Player.h"
#include "TitleManager.h"
#include "User.h"
#include "SysMsgDefine.h"
#include "FighterManager.h"
#include "Map.h"
#include "ItemMgr.h"
#include "VIPMgr.h"

using namespace NVarDefine;

CTitlePkg::CTitlePkg(CPlayer &rPlayer):_rPlayer(rPlayer)
{
    _equip.resize(3,0);

}
void CTitlePkg::Init(const TVecTitle &rvec)
{
    UINT32 dwNow = time(NULL);
    for(auto it = rvec.begin();it != rvec.end();it++)
    {
        const STitle& rTitle = *(it);
        const STitleCFG * pCfg = g_CTitleManager.GetCFGbyId(rTitle.wId);
        if(pCfg == NULL)
        {
            LOG_CRI <<"ERR ID";
            Update2DB(rTitle,eOpDel);
            continue;
        }
        if(rTitle.dwValidTime != 0 && rTitle.dwValidTime < dwNow)
        {
            //称号超时删除
            Update2DB(rTitle,eOpDel);
            continue;
        }

        if(!_mapAllTitle.insert(make_pair(rTitle.wId,rTitle)).second)
        {
            LOG_CRI<<"Repeat Title";
            continue;
        }

        if(rTitle.byEquipPos > 0)
        {
            if(!CheckTypeWithPos(pCfg->_Type,rTitle.byEquipPos))
            {
                STitle *pTitle = GetTitle(rTitle.wId);
                pTitle->byEquipPos = 0;
                if(pTitle != NULL)
                {
                    Update2DB(*pTitle,eOpUpdate);
                }
                LOG_CRI <<"ERR POS";
            }
            else
            {
                if(_equip[rTitle.byEquipPos-1] > 0)
                {
                    LOG_CRI << "POS Has Used"; 
                }
                else
                {
                    _equip[rTitle.byEquipPos-1] = rTitle.wId;
                }
            }
        }
    }
    NoticeFighter();
}
bool CTitlePkg::CheckTypeWithPos(UINT8 byType,UINT8 byPos)
{
    if(byType == ETitle_Common)
    {
        return 1;
    }
    else if(byType == ETitle_Rare)
    {
        return 2;
    }
    else if(byType == ETitle_Legend )
    {
        return  3;
    }
    return false;
}

void CTitlePkg::Update2DB(const STitle& rInfo,EDataChange eUpdateType)
{
    string strData;
    COutArchive iar(strData);
    iar << rInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(), eTypeTitle, eUpdateType, strData);
}

void CTitlePkg::GetAllTitle(TVecTitle &rvec)
{
    for(auto it = _mapAllTitle.begin();it != _mapAllTitle.end();it++)
    {
        rvec.push_back(it->second);
    }
}

ETitleResult CTitlePkg::EquipTitle(UINT16 wId,UINT8 byPos,UINT8& byCurPos)
{
    if(wId == 0)//卸下称号
    {
        if(byPos == 0 || byPos > 3)
        {
            return eTitleErrOther;
        }
        if(_equip[byPos-1] == 0)
        {
            return eTitleErrOther;
        }
        STitle *pTitle = GetTitle(_equip[byPos-1]);
        if(NULL == pTitle)
        {
            return eTitleErrOther;
        }
        pTitle->byEquipPos =0;
        byCurPos = byPos;
        Update2DB(*pTitle,eOpUpdate);
        _equip[byPos-1] = 0;
    }
    else//装备称号
    {
        if(wId == 0)
        {
            return eTitleErrOther;
        }
        const STitleCFG * pCfg = g_CTitleManager.GetCFGbyId(wId);
        if(pCfg == NULL)
        {
            return eTitleErrOther;
        }
        STitle *pTitle = GetTitle(wId);
        if(NULL == pTitle)
        {
            return eTitleNoHas;
        }
        UINT16 wOldId = 0;
        if(byPos == 0)//任意位置
        {
            if(pTitle->byEquipPos != 0)//已经装备，且任意位置，直接返回
            {
                byCurPos = pTitle->byEquipPos;
                return eTitleSucceed;
            }

            if( pCfg->_Type == ETitle_Common)
            {

                wOldId = _equip[0];
                byCurPos = 1;
            }
            else if( pCfg->_Type == ETitle_Rare)
            {
                wOldId = _equip[1];
                byCurPos = 2;

            }
            else if(pCfg->_Type == ETitle_Legend)
            {
                wOldId = _equip[2];
                byCurPos = 3;
            }

        }
        else //指定位置
        {
            if(pTitle->byEquipPos != 0 && pTitle->byEquipPos == byPos)//已经装备，且任意位置，直接返回
            {
                byCurPos = pTitle->byEquipPos;
                return eTitleSucceed;
            }

            if(!CheckTypeWithPos(pCfg->_Type,byPos))
            {
                return eTitleErrOther;
            }
            byCurPos = byPos;
            wOldId = _equip[byCurPos-1];

        }
        _equip[byCurPos-1] = wId;
        pTitle->byEquipPos = byCurPos;
        Update2DB(*pTitle,eOpUpdate);
        if(wOldId != 0)
        {
            STitle *pOldTitle = GetTitle(wOldId);
            if(NULL != pOldTitle)
            {
                pOldTitle->byEquipPos = 0;
                Update2DB(*pOldTitle,eOpUpdate);
                _rPlayer.SendPkg(g_TitleProtS.BuildPkg_AddTitle(*pOldTitle));
            }
        }
    }
    CGameMapPtr pMap= _rPlayer.GetMap();
    if(NULL != pMap)
    {
        pMap->AppearToSurround(_rPlayer);
    }

    return eTitleSucceed;
}

void CTitlePkg::AddTitle(UINT16 wId,UINT32 dwIntralTime, bool bAdd/* = true*/)
{
    const STitleCFG * pCfg = g_CTitleManager.GetCFGbyId(wId);
    if(pCfg == NULL)
        return;
    if(dwIntralTime == 0  && pCfg->_Time > 0)
    {
        dwIntralTime = pCfg->_Time;
    }

    STitle *pTitle = GetTitle(wId);
    if(pTitle )
    {
        UINT32 dwNowTime = 0 ;
        if(dwIntralTime > 0)//设置时效
        {
            //如果原来有时效，时效延长
            if(pTitle->dwValidTime > 0)
            {
                if (bAdd)
                    dwNowTime = pTitle->dwValidTime + dwIntralTime;
                else
                    dwNowTime = time(NULL) + dwIntralTime;
            }
            else //如果原来无时效，设置时效
            {
                dwNowTime = time(NULL) + dwIntralTime;
            }
        }
        //否则，永久时效
        pTitle->dwValidTime = dwNowTime;
        Update2DB(*pTitle,eOpUpdate);
        NoticeFighter();
        _rPlayer.SendPkg(g_TitleProtS.BuildPkg_AddTitle(*pTitle));
    }
    else if(pTitle == NULL)//初次获得时效
    {
        STitle tepTitle;
        tepTitle.wId = wId;
        if(dwIntralTime > 0)
        {
            tepTitle.dwValidTime = time(NULL)+dwIntralTime;
        }
        Update2DB(tepTitle,eOpAdd);
        _mapAllTitle[wId] = tepTitle;
        NoticeFighter();
        _rPlayer.SendPkg(g_TitleProtS.BuildPkg_AddTitle(tepTitle));
        if(pCfg && (pCfg->_Type == 2 || pCfg->_Type == 3))
        {
            TVecString vecstring;
            vecstring.push_back(NumberToString(_rPlayer.GetColor()));
            vecstring.push_back(_rPlayer.GetName());
            UINT8 byColor = NProtoCommon::ECOLOR_PURPLE;
            if(pCfg->_Type == 3)
            {
                byColor = NProtoCommon:: ECOLOR_ORANGE;
            }
            vecstring.push_back(NumberToString(byColor));
            vecstring.push_back(pCfg->_Name);
            g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgPurpleTitleGet,vecstring);
        }
    }
}

void CTitlePkg::DelTitle(UINT16 wId,bool bNoticeFighter)
{
    STitle *pTitle = GetTitle(wId);
    if(pTitle ==NULL)
    {
        return ;
    }
    Update2DB(*pTitle,eOpDel);
    if(pTitle->byEquipPos <= 3)
    {
        _equip[pTitle->byEquipPos-1] = 0;
        CGameMapPtr pMap= _rPlayer.GetMap();
        if(NULL != pMap)
        {
            pMap->AppearToSurround(_rPlayer);
        }
    }
    _mapAllTitle.erase(wId);
    if(bNoticeFighter)
    {
        NoticeFighter();
    }
    _rPlayer.SendPkg(g_TitleProtS.BuildPkg_DelTitle(wId));
}

void CTitlePkg::TimerCheck(UINT32 dwNow)
{
    vector<UINT16> vecDel;
    for(auto it =  _mapAllTitle.begin();it !=  _mapAllTitle.end();it++)
    {
        STitle &rTitle = it->second;
        if(rTitle.dwValidTime >0 && rTitle.dwValidTime < dwNow)
        {
            vecDel.push_back(it->first);
        }
    }
    for(auto it = vecDel.begin();it != vecDel.end();it++)
    {
        DelTitle(*it,true);
    }
    if(!vecDel.empty())
    {
        NoticeFighter();
    }

}

STitle * CTitlePkg::GetTitle(UINT16 wId)
{
    auto it = _mapAllTitle.find(wId);
    if(it != _mapAllTitle.end())
    {
        return &(it->second);
    }
    return NULL;
}

void CTitlePkg::GetAllTitleAttr(TVecFloat &rVecAttr)
{
    for(auto it = _mapAllTitle.begin();it != _mapAllTitle.end();it++)
    {
        const STitleCFG * pCfg = g_CTitleManager.GetCFGbyId(it->first);
        if(pCfg != NULL)
        {
            SItemAttrCFGEx* pCFG = CItemMgr::GetItemAttrConfig(pCfg->_PropID);
            if (pCFG)
                pCFG->SetIntoVec(rVecAttr);
        }
    }
}


void CTitlePkg::NoticeFighter()
{
    //通知战斗模块，有数据 更新
    CFighterManagerPtr pFighterManager = _rPlayer.GetFighterManager();
    if (pFighterManager)
        pFighterManager->SetDirty(eAttrGpTitle);
}
void CTitlePkg::GetTitleApear(map<UINT8,UINT16> &rmapAppear)
{
    for(size_t it = 0;it < _equip.size();it++)
    {
        if(_equip[it] != 0)
        {
            rmapAppear[it+1] = _equip[it];
        }
    }
}
