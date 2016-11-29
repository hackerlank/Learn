#ifndef RETAINMGR_H__ 
#define RETAINMGR_H__
#include "stdafx.h"
#include "WonderActivity.h"
#include "UserMgr.h"

struct SWonderRetainKey
{
    SWonderRetainKey(UINT64 qwRoleID,UINT16 wActID,UINT16 wType)
        : qwRoleID(qwRoleID),wActID(wActID),wType(wType) {}

    UINT64  qwRoleID;
    UINT16  wActID;
    UINT16  wType;

    bool operator < (const SWonderRetainKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        if(wType != sk.wType)
            return wType < sk.wType;
        return wActID < sk.wActID;
    }
};
typedef std::map<SWonderRetainKey,SRetain> TMapID2Retain;

class CRetainMgr 
{
    public:
        CRetainMgr(){}
        virtual ~CRetainMgr(){};
        bool     Init();
        void     LoadFromDB();
        void     OnLoad(const TVecRetain& vecData);
        bool     GetRetainValue(UINT64& qwRoleID,UINT16 &wActID,UINT16 &wType, SRetain &rRetain);
        bool     GetRetainByType(UINT16 &wActID,UINT16 &wType, SRetain &rRetain);
        bool     GetRetainByRoleID(UINT64 qwRoleID,UINT16 &wActID, SRetain &rRetain);
        bool     SetRetainValue(UINT64& qwRoleID,UINT16 &wActID,UINT16 &wType,SRetain &sRetain);
        bool     SetRetain(SRetain &sRetain);
        bool     DelRetain(SRetain &sRetain);
        bool     DelRetainValue(UINT64& qwRoleID,UINT16 &wActID,UINT16 &wType,SRetain &sRetain);
        bool     DelRetainByActID(UINT16 &wActID);
    protected:
        TMapID2Retain _mapID2Retain;

};
#endif
extern CRetainMgr g_RetainMgr; 
