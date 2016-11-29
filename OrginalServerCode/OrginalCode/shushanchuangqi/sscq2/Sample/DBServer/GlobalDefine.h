#pragma once

#define DB_SERVER

#define TIMER_SAVE_INTERVAL 5
#define LEAVE_WAIT_INTERVAL 3 * 60

#define MAX_SAVE_QUEUE_LENGTH 200

////////////////////////////////////////////////////////////////////////////////////////////
//Smart Pointer

#define DEF_SMART_POINTER(type, name) \
type name; \
typedef shared_ptr<name> name##Ptr; \
typedef weak_ptr<name> name##Wtr;

DEF_SMART_POINTER(struct, SRoleData);
DEF_SMART_POINTER(struct, SUsrIDNameInfo);
DEF_SMART_POINTER(class, IDBEvt);
DEF_SMART_POINTER(class, CQueryDBEvt);
DEF_SMART_POINTER(class, CDBGuildData);
DEF_SMART_POINTER(class, CDBPubGuildData);
DEF_SMART_POINTER(class, CDBRankData);
DEF_SMART_POINTER(class, CDBRoleRankData);
DEF_SMART_POINTER(class, CDBRoleAdoreData);
DEF_SMART_POINTER(class, CDBGuildRankData);
DEF_SMART_POINTER(class, CDBRankMgr);

