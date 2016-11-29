#include "BubbleMgr.h"
#include "Bubble.h"

#include "SysMsgDefine.h"

bool CBubbleMgr::Init()
{
    return LoadConfig();
}

bool CBubbleMgr::LoadConfig()
{
    for (auto it = _mapCFG.begin(); it != _mapCFG.end(); ++it)
    {
        if (it->second)
            delete it->second;
    }
    _mapCFG.clear();

    string strPath = Config._strConfigDir + "Conf/Table/Bubble.xml";

    LOG_INF << "Loading " << strPath << " ...";
    if(_cLoader.LoadData(strPath))
    {
        for (auto it = _cLoader._vecData.begin(); it != _cLoader._vecData.end(); ++it)
        {
            SBubbleCFGEx* pCFGEx = new SBubbleCFGEx;
            if (pCFGEx)
            {
                pCFGEx->SetConfig(**it);
                _mapCFG.insert(make_pair((*it)->_wID, pCFGEx));
            }
        }
    }
    else
    {
        LOG_INF << "Loading " << strPath << " failed.";
        return false;
    }
    //InitID2MessageID();
    return true;
}

// 初始化气泡信息
CBubblePtr CBubbleMgr::CreateBubble(UINT16 wMsgID, const TVecINT64& vecParam, const TVecString& vecString) const
{
    auto it = _mapCFG.find(wMsgID);
    if (it == _mapCFG.end())
        return NULL;
    if (!it->second)
        return NULL;
    CBubblePtr pBubble(new CBubble(wMsgID, GetMessageID(wMsgID)/*_vecBubbleMessageID[wMsgID]*/, vecParam, vecString));
    if (!pBubble)
        return pBubble;
    return pBubble;
}

UINT8 CBubbleMgr::GetPriority (UINT16 wMsgID) const
{
    SBubbleCFGEx* pCFG = GetConfig(wMsgID);
    if (pCFG)
        return pCFG->GetPriority();
    else
        return 0;
}

bool CBubbleMgr::IsOfflineEnable(UINT16 wMsgID) const
{
    SBubbleCFGEx* pCFG = GetConfig(wMsgID);
    if (pCFG)
        return pCFG->IsOfflineEnable();
    else
        return false;
}

UINT16 CBubbleMgr::GetGroupID(UINT16 wMsgID) const
{
    SBubbleCFGEx* pCFG = GetConfig(wMsgID);
    if (pCFG)
        return pCFG->GetGroupID();
    else
        return 0;
}

SBubbleCFGEx* CBubbleMgr::GetConfig(UINT16 wMsgID) const
{
    auto it = _mapCFG.find(wMsgID);
    if (it == _mapCFG.end())
        return NULL;
    else
        return it->second;
}

UINT16 CBubbleMgr::GetMessageID(UINT16 wMsgID) const
{
    const SBubbleCFGEx* pCfg =  CBubbleMgr::GetConfig(wMsgID);
    if(pCfg == NULL)
        return 0;
     return pCfg->_wMessageID;
}

/*/bool CBubbleMgr::InitID2MessageID()
{
    _vecBubbleMessageID.clear();
    _vecBubbleMessageID.resize(_mapCFG.size() + 1);
#define BUBBLE_REG(ID, MESSAGE_ID) _vecBubbleMessageID[ID] = MESSAGE_ID
#define BUBBLE_REG(ID, MESSAGE_ID) _vecBubbleMessageID[ID] = MESSAGE_ID
    BUBBLE_REG(1, eMsgMailBubble);
    BUBBLE_REG(2, eMsgFriendBubble);
    BUBBLE_REG(3, eMsgTalkBubble);
    BUBBLE_REG(4, eMsgGuildInvite);
    BUBBLE_REG(5, eMsgGuildImpeachFailed);
#undef BUBBLE_REG
}
*/
