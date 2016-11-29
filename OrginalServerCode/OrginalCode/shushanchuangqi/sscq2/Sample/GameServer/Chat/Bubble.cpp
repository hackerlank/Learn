#include "Bubble.h"

#include "RoleInfoDefine.h"
#include "BubbleMgr.h"
#include "Protocols.h"
#include "User.h"

using namespace NRoleInfoDefine;

CBubble::CBubble(UINT16 wID, UINT16 wMessageID, const TVecINT64& vecParam, const TVecString& vecString):
    _wID(wID), _wMessageID(wMessageID), _qwTransID(0)
{
    _dwTime = time(NULL);
    _vecParam = vecParam;
    _vecString = vecString;
}

CBubble::CBubble(const SDBBubbleInfo& rInfo):
    _wID(rInfo.wMsgID), _dwTime(rInfo.dwTime), _qwTransID(rInfo.qwTransID)
{
    _wMessageID = CBubbleMgr::Instance().GetMessageID(_wID);
    _vecParam = rInfo.vecParam;
    _vecString = rInfo.vecString;
}

CBubble::~CBubble()
{
}

UINT16 CBubble::GetID() const
{
    return _wID;
}

UINT16 CBubble::GetMessageID() const
{
    return _wMessageID;
}

UINT32 CBubble::GetTime() const
{
    return _dwTime;
}

const TVecINT64&  CBubble::GetParam() const
{
    return _vecParam;
}

TVecINT64&  CBubble::GetParam()
{
    return _vecParam;
}

const TVecString& CBubble::GetString() const
{
    return _vecString;
}

void CBubble::SetTransID(UINT64 qwTransID)
{
    _qwTransID = qwTransID;
}

UINT64 CBubble::GetTransID() const
{
    return _qwTransID;
}

bool CBubble::GetAllInfo(SBubbleInfo& rInfo, UINT8 byIndex) const
{
    rInfo.wMsgID        = GetID();
    rInfo.wMessageID    = GetMessageID();
    rInfo.dwTime        = GetTime();
    rInfo.vecParam      = GetParam();
    rInfo.vecString     = GetString();
    rInfo.byIndex       = byIndex;
    return true;
}

bool CBubble::GetAllDBInfo(SDBBubbleInfo& rInfo, UINT64 qwRoleID) const
{
    rInfo.qwRoleID      = qwRoleID;
    rInfo.wMsgID        = GetID();
    rInfo.qwTransID     = GetTransID();
    rInfo.dwTime        = GetTime();
    rInfo.vecParam      = GetParam();
    rInfo.vecString     = GetString();
    return true;
}


CBubbleOwner::CBubbleOwner(CUserPtr pUser):
    _qwMaxTransID(0)
{
    _pUser = pUser;
}

CBubbleOwner::~CBubbleOwner()
{
}

bool CBubbleOwner::InitFromDB(const TVecDBBubbleInfo& vecInfo)
{
    for (auto it = vecInfo.begin(); it != vecInfo.end(); ++it)
    {
        CBubblePtr pBubble(new CBubble(*it));
        AddBubble(pBubble, true);
        if ((*it).qwTransID > _qwMaxTransID)
            _qwMaxTransID = (*it).qwTransID;
    }
    return true;
}

bool CBubbleOwner::CreateBubble(UINT16 wMsgID)
{
    TVecINT64 vecParam;
    TVecString vecString;
    return CreateBubble(wMsgID, vecParam, vecString);
}

bool CBubbleOwner::CreateBubble(UINT16 wMsgID, const TVecINT64& vecParam)
{
    TVecString vecString;
    return CreateBubble(wMsgID, vecParam, vecString);
}

bool CBubbleOwner::CreateBubble(UINT16 wMsgID, const TVecString& vecString)
{
    TVecINT64 vecParam;
    return CreateBubble(wMsgID, vecParam, vecString);
}

bool CBubbleOwner::CreateBubble(UINT16 wMsgID, const TVecINT64& vecParam, const TVecString& vecString)
{
    CBubblePtr pBubble = CBubbleMgr::Instance().CreateBubble(wMsgID, vecParam, vecString);
    if (pBubble)
    {
        pBubble->SetTransID(++ _qwMaxTransID);
        return AddBubble(pBubble);
    }
    return false;
}

bool CBubbleOwner::Respond(UINT8 byIndex, const TVecINT64& vecParam, const TVecString& vecString)
{
    if (byIndex)
        --byIndex;
    if (_vecBubble.size() <= byIndex)
        return false;
    Update2DB(_vecBubble[byIndex], eOpDel);
    NotifyBubbleUpdate(byIndex + 1, _vecBubble[byIndex], eOpDel);
    _vecBubble.erase(_vecBubble.begin() + byIndex);
    return true;
}

void CBubbleOwner::ClearOfflineBubble()
{
    for (size_t byOffset = 0; byOffset < _vecBubble.size();)
    {
        SBubbleCFGEx* pCFG = CBubbleMgr::Instance().GetConfig(_vecBubble[byOffset]->GetID());
        if (pCFG && pCFG->IsOfflineEnable())
        {
            LOG_WRN << "IsOfflineEnable: " << pCFG->_wID << ".";
            ++byOffset;
        }
        else
        {
            LOG_WRN << "Not IsOfflineEnable: " << (pCFG ? pCFG->_wID:0) << ".";
            _vecBubble.erase(_vecBubble.begin() + byOffset);
        }
    }
}

CUserPtr CBubbleOwner::GetUser() const
{
    return _pUser.lock();
}
void CBubbleOwner::NotifyBubbleUpdate(UINT8 byIndex, CBubblePtr pBubble, EDataChange eType) const
{
    if (!pBubble)
        return;
    SBubbleInfo sInfo;
    if (pBubble->GetAllInfo(sInfo, byIndex))
    {
        std::string strData =  g_ChatProtS.BuildPkg_BubbleUpdate(eType, sInfo);
        GetUser()->SendPkg(strData);
    }
}

void CBubbleOwner::NotifyAllInfo() const
{
    TVecBubbleInfo vecBubbleInfo;
    for (auto it = _vecBubble.begin(); it != _vecBubble.end(); ++it)
    {
        SBubbleInfo sInfo;
        (*it)->GetAllInfo(sInfo, it-_vecBubble.begin());
        vecBubbleInfo.push_back(sInfo);
    }
    std::string strData =  g_ChatProtS.BuildPkg_BubbleNotify(vecBubbleInfo);
    GetUser()->SendPkg(strData);
}

bool CBubbleOwner::AddBubble(CBubblePtr pBubble, bool bInit /* = false */)
{
    if (pBubble)
    {
        SBubbleCFGEx* pCFG = CBubbleMgr::Instance().GetConfig(pBubble->GetID());
        if (!pCFG)
            return false;
        if (GetUser()->GetUserState() != eUserInGame && !pCFG->IsOfflineEnable())
            return false;

        //  相同组别的气泡，直接顶掉
        for (auto it = _vecBubble.begin(); it != _vecBubble.end(); ++it)
        {
            CBubblePtr pBubbleOther = *it;
            SBubbleCFGEx* pCFG2 = CBubbleMgr::Instance().GetConfig(pBubbleOther->GetID());

            if (pCFG->GetGroupID() 
                    && pCFG2->GetGroupID() == pCFG->GetGroupID())
            {
                if (!bInit)
                {
                    switch(pCFG->GetGroupType())
                    {
                        case 1: // 被覆盖不累加
                            break;
                        case 2: // 覆盖同时累加
                            {
                                TVecINT64& rvecParam = pBubble->GetParam();
                                const TVecINT64& rvecParam2 = pBubbleOther->GetParam();
                                auto it = rvecParam.begin();
                                auto it2 = rvecParam2.begin();
                                for (; it != rvecParam.end() && it2 != rvecParam2.end(); ++it, ++it2)
                                {
                                    *it += *it2;
                                }
                            }
                            break;
                    }
                    Update2DB(pBubbleOther, eOpDel);
                    if (pCFG->IsOfflineEnable())
                        Update2DB(pBubble, eOpAdd);
                    NotifyBubbleUpdate(static_cast<UINT8>(it - _vecBubble.begin() + 1), pBubble, eOpReplace);
                }
                *it = pBubble;
                return true;
            }
        }
        // 插入到优先级没有自己高的前面
        for (auto it = _vecBubble.begin(); it != _vecBubble.end(); ++it)
        {
            CBubblePtr pBubbleOther = *it;
            SBubbleCFGEx* pCFG2 = CBubbleMgr::Instance().GetConfig(pBubbleOther->GetID());
            if (pCFG2->GetPriority() <= pCFG->GetPriority()) // 只有低优先级的了
            {
                if (!bInit)
                {
                    NotifyBubbleUpdate(static_cast<UINT8>(it - _vecBubble.begin() + 1), pBubble, eOpAdd);
                    if (pCFG->IsOfflineEnable())
                        Update2DB(pBubble, eOpAdd);
                }
                _vecBubble.insert(it, pBubble);
                return true;
            }
        }

        // 直接最末位插入
        if (!bInit)
        {
            NotifyBubbleUpdate(static_cast<UINT8>(_vecBubble.size() + 1), pBubble, eOpAdd);
            if (pCFG->IsOfflineEnable())
                Update2DB(pBubble, eOpAdd);
        }
        _vecBubble.push_back(pBubble);
        return true;
    }
    return false;
}

bool CBubbleOwner::GetAllInfo(TVecBubbleInfo& vecInfo) const
{
    for (auto it = _vecBubble.begin(); it != _vecBubble.end(); ++it)
    {
        SBubbleInfo sInfo;
        if ((*it)->GetAllInfo(sInfo, static_cast<UINT8>(it - _vecBubble.begin() + 1)))
            vecInfo.push_back(sInfo);
    }
    return true;
}

void CBubbleOwner::Update2DB(CBubblePtr pBubble, EDataChange eType) const
{
    if (!pBubble)
        return;
    SDBBubbleInfo sInfo;
    if (!pBubble->GetAllDBInfo(sInfo, GetUser()->GetUserID()))
        return;
    string strData;
    COutArchive iar(strData);
    iar << sInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(GetUser()->GetUserID(), eTypeBubbleInfo, eType, strData);
}
