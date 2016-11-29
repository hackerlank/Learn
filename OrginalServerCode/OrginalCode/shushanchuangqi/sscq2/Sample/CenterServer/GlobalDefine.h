#pragma once

////////////////////////////////////////////////////////////////////////////////////////////
//Server Macro

#define CENTER_SERVER

////////////////////////////////////////////////////////////////////////////////////////////
//Game Macro

#define ROLE_REQ_WAIT 2
#define ROLE_LOGIN_WAIT 5 * 60 
#define ROLE_KICK_WAIT 10
#define ROLE_LEAVE_WAIT 5 * 60

#define PER_MINUTE_TO_S 60
#define PER_HOUR_TO_S 3600
#define PER_DAY_TO_S 86400
#define GAME_RANDOM_PERCENT 10000
#define GAME_COEF_PERCENT 10000

////////////////////////////////////////////////////////////////////////////////////////////
//Smart Pointer

#define DEF_SMART_PTR_NAME(name) \
typedef shared_ptr<name> name##Ptr; \
typedef weak_ptr<name> name##Wtr;

#define DEF_SMART_POINTER(type, name) \
type name; \
typedef shared_ptr<name> name##Ptr; \
typedef weak_ptr<name> name##Wtr;

DEF_SMART_POINTER(class, CUser);

DEF_SMART_POINTER(class, CUDPLog);
DEF_SMART_POINTER(class, CUdpLogger);
DEF_SMART_POINTER(class, CForbidDB);

DEF_SMART_POINTER(class, CGuild);
DEF_SMART_POINTER(class, CGuildUser);
DEF_SMART_POINTER(class, CGuildApplyInfo);
DEF_SMART_POINTER(class, CGuildListInfo);

DEF_SMART_POINTER(class, CGuildStatue);
DEF_SMART_POINTER(class, CGuildStatueLog);
DEF_SMART_POINTER(class, CGuildStatueOwner);

DEF_SMART_POINTER(class, CGuildBuilding);
DEF_SMART_POINTER(class, CGuildBuildingOwner);

DEF_SMART_POINTER(class, CGuildTech);
DEF_SMART_POINTER(class, CGuildTechOwner);

DEF_SMART_POINTER(class, CGuildLog);
DEF_SMART_POINTER(class, CGuildMemberLog);
DEF_SMART_POINTER(class, CGuildBuildingLog);
DEF_SMART_POINTER(class, CGuildDonateLog);
DEF_SMART_POINTER(class, CGuildStatueLog);

DEF_SMART_POINTER(class, CTripod);
DEF_SMART_POINTER(class, CFire);
DEF_SMART_POINTER(class, CTripodLog);
DEF_SMART_POINTER(class, CTripodHelpLog);

DEF_SMART_POINTER(class, CGuildXihe);

/////////////////////////////////////////////////////////////////////////////////
//typedef
typedef vector<CGuildUser>          TVecGuildUser;
typedef vector<CGuildUserPtr>       TVecGuildUserPtr;
typedef vector<CGuildApplyInfoPtr>  TVecGuildApplyInfoPtr;
typedef vector<CGuildStatueLogPtr>  TvecGuildStatueLogPtr;
typedef vector<CGuildTechPtr>       TVecGuildTechPtr;
typedef vector<CGuildLogPtr>        TVecGuildLogPtr;
typedef vector<CGuildStatueLogPtr>  TVecGuildStatueLogPtr;
typedef vector<CTripodLogPtr>       TVecTripodLogPtr;
typedef list<CTripodLogPtr>         TListTripodLogPtr;
typedef deque<CTripodLogPtr>        TDequeTripodLogPtr;

