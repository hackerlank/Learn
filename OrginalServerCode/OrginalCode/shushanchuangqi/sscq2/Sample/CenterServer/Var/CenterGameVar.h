
#ifndef VAR_GAMECENTER_H_
#define VAR_GAMECENTER_H_

#include "GameVar.h"

class CCenterGameVar : public CGameVar
{
public:
    CCenterGameVar():_bIsLoad(false){}; 
    ~CCenterGameVar() {}
    virtual void Update2DB(UINT16 wVar, UINT64 qwValue, UINT32 dwExpired, EDataChange eDataChange);
    bool IsLoad(){return _bIsLoad;}
    void LoadFromDB();
private:
    bool _bIsLoad;
};
extern CCenterGameVar g_CenterGameVar;
#endif // VAR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

