
#ifndef SHUSHANWEIWEI_H_
#define SHUSHANWEIWEI_H_

#include "ShushanweiweiProt.h"
#include "User.h"
#include "VarDefine.h"
#include "Singleton.h"

using namespace NVarDefine;
using namespace NShushanweiweiProt;

class CShushanweiwei
{
public:
    CShushanweiwei(CPlayer &rPlayer) : _rPlayer(rPlayer) { };
    virtual ~CShushanweiwei() {}

    EPkgResult TakePrize(CUser& rUser,EPkgType eType,UINT16 wIndex,const string& strCDK);
    void       GMOpen(CUser& rUser,EPkgType eType,UINT32 dwCount);
    void       SyncPrizeInfo(CUser& rUser,TVecPrizeInfo& vecPrizeInfo);
    bool       CheckCDK(std::string strRecvCDK);
    void       SetListenWeibo(CUser& rUser);
private:
    void       GetPrizeInfo(CUser& rUser,TVecPrizeInfo& vecPrizeInfo);
    bool       Check(CUser& rUser,EPkgType eType,UINT16 wIndex,UINT32& dwRootIndex,const string& strCDK);
    void       SetShushanVar(CUser &rUser,EPkgType eType,UINT16 wIndex);
    void       SetPrizeInfo(CUser& rUser,EPkgType eType,SPrizeInfo& sInfo);
private:
    CPlayer &_rPlayer;
};

//不在需要
class CShushanweiweiMgr : public Singleton<CShushanweiweiMgr>
{
    public:
        CShushanweiweiMgr():
            _dwWeibo(0),
            _dwWeixin(0)
            { }
        virtual ~CShushanweiweiMgr() { }
        bool Init();
        void SetWeiboNum(UINT32 dwTmp) { _dwWeibo = dwTmp; }
        void SetWeixinNum(UINT32 dwTmp) { _dwWeixin = dwTmp; }
        UINT32 GetWeiboNum() { return _dwWeibo; }
        UINT32 GetWeixinNum() { return _dwWeixin; }
        void Attention(UINT64 qwRoleID,UINT8 byType,UINT32 dwCount);
    private:
        UINT32 _dwWeibo;
        UINT32 _dwWeixin;
};

#define ShushanweiweiMgr CShushanweiweiMgr::Instance()
#endif // CoinMGR_H_
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

