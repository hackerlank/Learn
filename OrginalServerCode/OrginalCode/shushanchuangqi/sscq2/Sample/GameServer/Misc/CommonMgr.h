
#ifndef COMMONMGR_H_
#define COMMONMGR_H_

#include "Singleton.h"
#include "SevDiscountCFG.h"

using namespace NProtoCommon;

class CCommonMgr : public Singleton<CCommonMgr>
{
public:
    
    bool Init();
    bool LoadConfig(const string &);
    static SSevDiscountCFG* GetSevDiscountCFG(UINT16 wDay);

    static UINT64 GetVersion() { return _qwVersion; } // XXX: 如果配置被重新加载这可以通过这个version来确认是否要更新

private:
    
    static UINT64 _qwVersion;

private:
    
    static std::map<UINT16, SSevDiscountCFG> _mapSevDiscountCFG;
};

#endif // COMMONMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

