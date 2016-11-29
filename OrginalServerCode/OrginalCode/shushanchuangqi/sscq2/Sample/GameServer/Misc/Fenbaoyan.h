
#ifndef FENBAOYAN_H_
#define FENBAOYAN_H_

#include "Singleton.h"
#include "MiscProt.h"
#include "User.h"
#include "VarDefine.h"

using namespace NVarDefine;
using namespace NMiscProt;

class CFenbaoyanMgr
{
public:
    CFenbaoyanMgr(CPlayer &rPlayer);
    virtual ~CFenbaoyanMgr() {}
    void OnUserLogin();
    bool IsRun() const { return _bRun; }
    EMiscOptRes OnBuyFenbaoyan(UINT16 wNum);
    void CheckTime();
    void CloseIcon();
    void GetTime(UINT32 &dwBegin,UINT32 &dwEnd);
private:
    CPlayer &_rPlayer;
    bool  _bRun;
};

#endif // CoinMGR_H_
extern CFenbaoyanMgr g_FenbaoyanMgr;
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

