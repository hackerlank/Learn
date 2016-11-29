
#ifndef LOGINPKGMGR_H_
#define LOGINPKGMGR_H_

#include "Singleton.h"
#include "LoginPkgProt.h"
#include "User.h"
#include "VarDefine.h"
#include "EventMgr.h"

using namespace NVarDefine;
using namespace NLoginPkgProt;

class CLoginPkgMgr : public CRegiserterEvent
{
public:
    CLoginPkgMgr(CPlayer &rPlayer);
    virtual ~CLoginPkgMgr() {}
    UINT32             GetDays() { return _dwDays; }
    EResultInLoginProt GetLoginPkg(CUser &rUser,UINT8  byIndex, UINT16 &wResult);
    bool               GetPkgInfo(CUser &rUser,UINT16 &wDays,UINT16 &wResult);
    void               RegisterLoginEvent();
    void               OnEvent(SEventInfoPtr pEventInfoPtr);

    void               SendPkgInfoFor0();
    UINT32             GetLoginDays();
private:
    CPlayer &_rPlayer;
    UINT32 _dwEventID;
    UINT32 _dwDays;
};

#endif // CoinMGR_H_
extern CLoginPkgMgr g_LoginPkgMgr;
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

