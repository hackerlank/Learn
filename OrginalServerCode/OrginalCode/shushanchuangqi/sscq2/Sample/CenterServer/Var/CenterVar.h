
#ifndef VAR_CENTER_H_
#define VAR_CENTER_H_

#include "GameVar.h"

class CUser;
class CCenterVar : public CGameVar
{
public:
    CCenterVar(CUser& rUser) : _rUser(rUser) {}
    ~CCenterVar() {}
    CUser& GetUser(){return _rUser;}
    virtual void Update2DB(UINT16 wVar, UINT64 qwValue, UINT32 dwExpired, EDataChange eDataChange);
private:
    CUser& _rUser;
};

#endif // VAR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

