#include "stdafx.h"
#include "DataSlots.h"
#include "Protocols.h"
#include "Game2DBComm.h"

using namespace NRoleInfoDefine;
using namespace NProtoCommon;

CDataSlots::CDataSlots()
    : _wMaxSlot(0), _wMaxAvaliableSlot(0)
{
}

CDataSlots::~CDataSlots()
{
}

UINT16 CDataSlots::GetMaxSlot() const
{
    return _wMaxSlot;
}

UINT16 CDataSlots::GetMaxAvaliableSlot() const
{
    return _wMaxAvaliableSlot;
}

bool  CDataSlots::InitSlot(UINT16 wMaxSlot, UINT16 wMaxAvaliableSlot)
{
    _wMaxSlot = wMaxSlot;
    _wMaxAvaliableSlot = wMaxAvaliableSlot;
    if (_wMaxAvaliableSlot > _wMaxSlot)
        _wMaxAvaliableSlot = _wMaxSlot;
    return true;
}

bool    CDataSlots::SetMaxSlot(UINT16 wSlot, bool bInit /* = false */)
{
    if (wSlot <= _wMaxSlot)
        return false;
    _wMaxSlot = wSlot;
    if (!bInit)
        Update2DB(*this);
    return true;
}

bool    CDataSlots::SetMaxAvaliable(UINT16 wSlot, bool bInit /* = false */)
{
    if (wSlot <= _wMaxAvaliableSlot || wSlot > _wMaxSlot)
        return false;
    _wMaxAvaliableSlot = wSlot;
    if (!bInit)
        Update2DB(*this);
    return true;
}

void    CDataSlots::Update2DB(const CDataSlots& rDataSlots)
{
    // FIXME: 和外部调用重复
    /*
    string strData;
    COutArchive iar(strData);
    SRoleSlotsInfo sRoleSlotsInfo;
    sRoleSlotsInfo.qwRoleID = rDataSlots.GetRoleID();
    sRoleSlotsInfo.qwOwnerID = rDataSlots.GetOwnerID();
    sRoleSlotsInfo.eStoreType = rDataSlots.GetStoreType();
    sRoleSlotsInfo.wMaxSlot = rDataSlots._wMaxSlot;
    sRoleSlotsInfo.wMaxAvaliableSlot = rDataSlots._wMaxAvaliableSlot;
    iar << sRoleSlotsInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(rDataSlots.GetRoleID(), eTypeSlotsInfo, eOpUpdate, strData);
    */
}
