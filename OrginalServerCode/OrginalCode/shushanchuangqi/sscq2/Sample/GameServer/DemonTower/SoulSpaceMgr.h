
#ifndef SOULSPACEMGR_H_
#define SOULSPACEMGR_H_
#include "RoleInfoDefine.h"
#include "CommonDef.h"
using namespace NProtoCommon;
using namespace NRoleInfoDefine;
class CSoulSpaceEx
{
public:
    CSoulSpaceEx(){};
    ~CSoulSpaceEx(){};

    const TVecFloat& GetAttrVec() const { return _vecAttr; }
    bool IsChange(){return _bChange;}

public:
    UINT32 dwSoulSpaceID;      //类型id
    UINT32 dwSoulSpaceLevel;   //等级
    bool   _bChange;
    TVecFloat _vecAttr;
};

typedef std::shared_ptr<CSoulSpaceEx> CSoulSpaceExPtr;
typedef std::map<UINT32,CSoulSpaceExPtr> TMapSoulSpaceExPtr;

class CPlayer;

class CSoulSpaceMgr 
{

public:
    CSoulSpaceMgr(CPlayer* pPlayer);
    ~CSoulSpaceMgr() {}
    void LoadFromDB(const TVecSoulSpaceInfo& vecSoulSpaceInfo);
    void Update2DB(CSoulSpaceExPtr pSoulSpaceEx, EDataChange eDataChanige = eOpUpdate);
    void Update2DB(SSoulSpaceInfo& rInfo, EDataChange eDataChanige = eOpUpdate);
  
    void Upgrade(UINT32 dwSoulSpaceID);
    
    void NotifyList();

    const TVecFloat& GetAttrVec();
    bool IsChange(){return _bChange;}
    
    void RebuildAttr();

    TMapSoulSpaceExPtr& GetAllSoulSpace() { return _mapSoulSpaceExPtr; }

private:
    CPlayer*  _pPlayer;
    TMapSoulSpaceExPtr _mapSoulSpaceExPtr;
    bool   _bChange;
    TVecFloat _vecAttr;
};

#endif // SOULSPACEMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

