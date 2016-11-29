
#ifndef GUILDXIHE_H_
#define GUILDXIHE_H_

#include "stdafx.h"

#include "GuildProt.h"

using namespace NGuildProt;

#define XIHE_TASKCOUNT 8

class CUser;

class CGuildXihe : public CPoolObj<CGuildXihe>
{
public:
    CGuildXihe(UINT64 qwRoleID);
    ~CGuildXihe();

    void SetOwnerID(UINT64 qwRoleID)                    { _qwOwnerID = qwRoleID; }
    UINT64 GetOwnerID() const                           { return _qwOwnerID; }
    void SetStage(EXiheStage eStage)                    { _byStage = eStage; }
    EXiheStage GetStage() const                         { return _byStage; }
    void SetEndTime(UINT32 dwTime)                      { _dwEndTime = dwTime; }
    UINT32 GetEndTime() const                           { return _dwEndTime; }
    void SetTruckInfo(TVecTruckInfo vecTruck)           { _vecTruckInfo = vecTruck; }
    TVecTruckInfo& GetTruckInfo()                       { return _vecTruckInfo; }
    void AddRequest(UINT8 byCount)                      { _byRequest += byCount; }
    void SetRequest(UINT8 byCount)                      { _byRequest = byCount; }
    UINT8 GetRequest() const                            { return _byRequest; }
    void SetTruckHelpName(UINT8 byPos, const string& strName,UINT8 byColor);
    void SetTruckStatus(UINT8 byPos, UINT8 byStatus);
    UINT8 GetTruckStatus(UINT8 byPos) const;
    STruckInfo& GetTruckInfoByPos(UINT8 byPos);
    STruckInfo& GetTruckInfoByID(UINT8 byTruckID);

    void UpdateGuildXiheInfo(CUserPtr pUser);
    UINT8 GetFinishTaskCount();
    bool IsFinishAllTask();
    void AssignTask();
    void ToProt(SGuildXihe& oGuildXihe);
    void Update2DB(NProtoCommon::EDataChange eDataChange/* = eOpUpdate*/);

private:
    UINT64 _qwOwnerID;
    EXiheStage _byStage;
    UINT32 _dwEndTime;
    UINT8 _byRequest;
    TVecTruckInfo _vecTruckInfo;
};


#endif // GUILDXIHE_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

