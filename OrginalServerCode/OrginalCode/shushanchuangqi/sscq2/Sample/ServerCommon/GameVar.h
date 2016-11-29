
#ifndef GAMEVAR_H_
#define GAMEVAR_H_

#include "Vars.h"
#include "ProtoCommon.h"

using namespace NProtoCommon;

class CUser;

class CGameVar : public Vars<UINT16, UINT64>
{
public:
    CGameVar(); 
    virtual ~CGameVar() {}
    UINT32 GetVar32(UINT16 wVar);
    UINT64 GetVar(UINT16 wVar);
    UINT64 AddVar(UINT16 wVar, UINT64 qwValue, UINT32 dwOffset = 0, time_t now = 0);
    void SetVar(UINT16 wVar, UINT64 qwValue, UINT32 dwOffset = 0, time_t now = 0);
    void DelVar(UINT16 wVar);
    void SetExpiredTime(UINT16 wVar, UINT32 dwExpired);
    UINT32 GetExpiredTime(UINT16 wVar);
    void SetVarFromDB(UINT16 wVar, UINT64 qwValue, UINT32 dwExpired);
    virtual void Update2DB(UINT16 wVar, UINT64 qwValue, UINT32 dwExpired, EDataChange eDataChange) {}

    static void Register();
};

#endif // GAMEVAR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

