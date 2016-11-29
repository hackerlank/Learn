#include "Citta.h"
#include "CittaMgr.h"

CCitta::CCitta(UINT16 wItemID):
    CItem(wItemID),
    _qwRoleID(0), _qwOwnerID(0),
    _bInited(false), _dwSkillID(0), _dwSignetID(0)
{
}


CCitta::~CCitta() 
{
}

bool CCitta::IsInited() const
{
    return _bInited;
}

void CCitta::SetInited(bool bInited)
{
    _bInited = bInited;
}

UINT64 CCitta::GetOwnerID() const
{
    return _qwOwnerID;
}

void CCitta::SetOwnerID(UINT64 qwOwnerID)
{
    _qwOwnerID = qwOwnerID;
    _qwRoleID = _qwOwnerID;
}

SItemPtr CCitta::ToProt() const
{
    SCitta* pCitta = new SCitta;
    if(pCitta == NULL)
        return NULL;
    if(!ToStream(*pCitta))
    {
        delete pCitta;
        return NULL;
    }
    return SItemPtr(pCitta);
}

bool CCitta::FromStream(const SCitta& rStream)
{
    CItem::FromStream(rStream);

    _qwOwnerID = rStream.qwOwnerID;
    _qwRoleID = _qwOwnerID;
    //_qwRoleID = rStream.qwRoleID;
    for (auto & rInfo : rStream.oAttrVec)
    {
        _mapAttr[rInfo._eAttr] = static_cast<UINT32>(rInfo._fValue);
    }
    _dwSkillID = rStream.dwSkillID;
    _dwSignetID = rStream.dwSignetID;

    return true;
}

bool CCitta::ToStream(SCitta& rStream) const
{
    CItem::ToStream(rStream);
    for (auto & rPair : _mapAttr)
    {
        SFtAttrMod sFtAttrMod(rPair.first, rPair.second);
        rStream.oAttrVec.push_back(sFtAttrMod);
        if (rPair.first == EFIGHTATTR_PHYATK)
        {
            SFtAttrMod sFtAttrMod(EFIGHTATTR_MGCATK, rPair.second);
            rStream.oAttrVec.push_back(sFtAttrMod);
        }
    }

    rStream.qwOwnerID = _qwOwnerID;
    rStream.dwSkillID = _dwSkillID;
    rStream.dwSignetID = _dwSignetID;
    rStream.eCittaNameType = CCittaMgr::Instance().GetNameType(GetID(), _mapAttr);
    return true;
}

bool CCitta::ToDBStream(SCitta& rStream) const
{
    CItem::ToStream(rStream);
    for (auto & rPair : _mapAttr)
    {
        SFtAttrMod sFtAttrMod(rPair.first, rPair.second);
        rStream.oAttrVec.push_back(sFtAttrMod);
    }

    rStream.qwOwnerID = _qwOwnerID;
    rStream.dwSkillID = _dwSkillID;
    rStream.dwSignetID = _dwSignetID;
    rStream.eCittaNameType = CCittaMgr::Instance().GetNameType(GetID(), _mapAttr);
    return true;
}

const TMapCittaAttr& CCitta::GetAttr() const
{
    return _mapAttr;
}

UINT32 CCitta::GetSignetID() const
{
    return _dwSignetID;
}

