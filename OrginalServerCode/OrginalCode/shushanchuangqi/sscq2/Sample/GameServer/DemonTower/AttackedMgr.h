
#ifndef ATTACKEDMGR_H_
#define ATTACKEDMGR_H_
#include <deque>
#include "RoleInfoDefine.h"
#include "CommonDef.h"
#include "DemonTowerSvr.h"
#include "ProtoCommon.h"
using namespace NProtoCommon;
using namespace NRoleInfoDefine;
using namespace NProtoCommon;

class CPlayer;
typedef std::shared_ptr<SRoleAttaked> SRoleAttakedPtr;
typedef std::deque<SRoleAttakedPtr> QueRoleAttaked;

struct SAttackQueue
{
    UINT32 dwMaxSize;
    QueRoleAttaked queAttacked;
    SAttackQueue()
    {
        dwMaxSize = 0;
    }
};

typedef std::vector<SAttackQueue> TVecQueRoleAttaked;

class CAttackedMgr 
{

public:
    CAttackedMgr(CPlayer& rPlayer);
    ~CAttackedMgr() {}
    bool LoadFromDB(const RoleDataInfo& rRoleDataInfo);
    void Update2DB(SRoleAttaked& rInfo, EDataChange eDataChange = eOpUpdate);
    void OnAttackedInfo(const SRoleAttaked& rInfo);
    void GetAttakedList(TVecRoleAttaked& vecRoleAttaked,UINT32 dwFightType);
    UINT32 GenerateID();
private:
    TVecQueRoleAttaked _vecQueRoleAttaked;
    CPlayer&  _rPlayer;
    UINT32 _dwMaxID;
};

#endif // ATTACKEDMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

