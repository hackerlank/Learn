
#ifndef GODMONSTER_H_
#define GODMONSTER_H_

#include "GodMonsterUser.h"
#include "VarDefine.h"
using namespace NVarDefine;

class CGodMonster
{
public:
    CGodMonster(UINT64 qwGuildID);
    virtual ~CGodMonster(); 
    UINT64 GetMonsterID() { return _qwGuildID; }
    UINT64 GetID() { return GetMonsterID(); }
    UINT32 GetScore() { return _dwScore; }
    void   SetScore(UINT32 dwTmp) { _dwScore = dwTmp; }
    UINT8  GetPeroid() { return _byPeroid; }
    void   SetPeroid(UINT8 byTmp) { _byPeroid = byTmp; }
    void AddScore(UINT32 dwTmp);
    TMapID2MonsterUserPtr& GetAllMonsterUser() { return _mapID2UserPtr; }
    GodMonsterUserPtr GetUserInfoByID(UINT64 qwRoleID);
    bool  CheckUserByID(UINT64 qwRoleID);
    void  DeleteUser(UINT64 qwRoleID);
    bool  AddUser(GodMonsterUserPtr pUser);
    void  CheckPeroid(UINT32 dwScore);
private:
    UINT64 _qwGuildID;
    UINT32 _dwScore;
    UINT8  _byPeroid;
    TMapID2MonsterUserPtr _mapID2UserPtr; 
};
#endif
typedef shared_ptr<CGodMonster> GodMonsterPtr;
typedef std::map<UINT64,GodMonsterPtr> TMapID2Monster;
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

