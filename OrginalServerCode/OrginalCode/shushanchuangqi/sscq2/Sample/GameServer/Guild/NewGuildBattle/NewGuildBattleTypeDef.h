// =====================================================================================
//
//       Filename:  NewGuildBattleTypeDef.h
//
//    Description:  新帮派战相关类型声名
//
//        Version:  1.0
//        Created:  03/21/2015 05:43:50 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef NEW_GUILD_BATTLE_TYPE_DEF_H
#define NEW_GUILD_BATTLE_TYPE_DEF_H

#ifndef DEF_SMART_POINTER

#define DEF_SMART_POINTER(type, name) \
type name; \
typedef shared_ptr<name> name##Ptr; \
typedef weak_ptr<name> name##Wtr;

#endif // #ifndef DEF_SMART_POINTER

namespace NNewGuildBattle
{

DEF_SMART_POINTER(class, CMountain);
DEF_SMART_POINTER(class, CMountainHistory);
DEF_SMART_POINTER(class, CGate);
DEF_SMART_POINTER(class, CCave);
DEF_SMART_POINTER(class, CCaveCore);
DEF_SMART_POINTER(class, CPlayer);
DEF_SMART_POINTER(class, CPuppet);

DEF_SMART_POINTER(class, CGuildRankMgr);
DEF_SMART_POINTER(class, CGuildMemberRankMgr);
DEF_SMART_POINTER(class, CPlayerRankMgr);

typedef list<CMountainHistoryPtr>       TListMountainHistoryPtr;
typedef vector<CMountainHistoryPtr>     TVecMountainHistoryPtr;
typedef vector<CPuppetPtr>              TVecPuppetPtr;

// MsgLingMountainEnd{color:2:{0}}帮派在{color:2:{1}}灵山战中胜利，获得该灵山所有权！
// MsgLingMountainDoorBreak{color:2:{0}}灵山的禁制已被{color:{1}:[{2}]}攻破！
// MsgLingMountainAttackDoor{color:{0}:[{1}]}对山门禁制造成{color:6:{2}}点伤害

} // namespace NNewGuildBattle

#endif // #ifndef NEW_GUILD_BATTLE_TYPE_DEF_H
