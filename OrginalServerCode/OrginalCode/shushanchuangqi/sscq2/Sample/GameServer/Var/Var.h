
#ifndef VAR_H_
#define VAR_H_

#include "GameVar.h"
#include "VarDefine.h" // XXX: for NVarDefine::*

class CUser;
class CVar : public CGameVar
{
public:
    CVar(CUser& rUser) : _rUser(rUser) {}
    CUser& GetUser(){return _rUser;}
    ~CVar() {}
    virtual void Update2DB(UINT16 wVar, UINT64 qwValue, UINT32 dwExpired, EDataChange eDataChange);
private:
    CUser& _rUser;
};

#endif // VAR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

