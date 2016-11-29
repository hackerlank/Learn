#ifndef BATTLE_DEBUGGER_H
#define BATTLE_DEBUGGER_H

#include "ProtoCommon.h"

#include "BattleTypeDef.h"
#include "BattleSkill.h"

namespace NBattle
{

using namespace NProtoCommon;

extern CLog g_BattleLog;
extern UINT64 g_qwDebuggerID;
extern string g_strDeuggerFile;

class CBattleSkillEffect;
class CBattleBuff;

#ifdef _DEBUG
#define BATTLE_DEBUG    // 战斗调试输出总开关
#endif

#ifdef BATTLE_DEBUG

//#define BATTLE_STATE          // 状态机流程调试
//#define BATTLE_ACTION         // 动作机流程调试
//#define BATTLE_LIST_DEBUG       // 战斗队列流程调试
//#define BATTLE_FIGHTER_DEBUG    // 战斗散仙相关调试开关
#define BATTLE_SKILL_DEBUG      // 战斗技能相关调试开关
//#define BATTLE_CALC_DEBUG       // 战斗计算相关调试开关
#define BATTLE_HP_CHANGE        // 战斗血量变化调试开关
//#define BATTLE_AURA_CHANGE    // 战斗灵气变化调试开关 

#endif // #ifdef BATTLE_DEBUG

#ifdef BATTLE_FIGHTER_DEBUG
#define BATTLE_FIGHTER_DEBUG_ATTR     // 战斗散仙属性调试
#define BATTLE_FIGHTER_DEBUG_SKILL    // 战斗散仙技能调试
#endif // #ifdef BATTLE_FIGHTER_DEBUG


#ifdef BATTLE_SKILL_DEBUG           // 战斗技能相关调试开关

//#define BATTLE_SKILL_RATE         // 技能概率调试
//#define BATTLE_SKILL_ID           // 技能ID调试
//#define BATTLE_SKILL_TYPE         // 技能类型调试
//#define BATTLE_SKILL_AREA         // 战斗技能范围调试开关
//#define BATTLE_SKILL_COMBINE        // 连携技能调试 

//#define BATTLE_SKILL_INST_ID        // Buff流水号调试
#define BATTLE_SKILL_BUFF           // Buff相关调试
//#define BATTLE_SKILL_BUFF_LAST    // Buff持续时间相关调试
//#define BATTLE_SKILL_BUFF_CD      // BuffCD调试
#define BATTLE_SKILL_BUFF_COND    // Buff触发条件相关测试

#endif // #ifdef BATTLE_SKILL_DEBUG

#ifdef BATTLE_DEBUG
#define BATTLE_DBG CLogObj(g_BattleLog, eLogLevelInfo, NULL, 0, g_strDeuggerFile.c_str())
#else
#define BATTLE_DBG if(1) {} else CNulLog::_sNulLog
#endif //#ifdef BATTLE_DEBUG

#ifdef BATTLE_STATE
#define STATE_DEBUG   CLogObj(g_BattleLog, eLogLevelInfo, NULL, 0, g_strDeuggerFile.c_str())
#else
#define STATE_DEBUG if(1) {} else CNulLog::_sNulLog
#endif //#ifdef BATTLE_STATE

#ifdef BATTLE_ACTION
#define ACTION_DEBUG  CLogObj(g_BattleLog, eLogLevelInfo, NULL, 0, g_strDeuggerFile.c_str())
#else
#define ACTION_DEBUG  if(1) {} else CNulLog::_sNulLog
#endif //#ifdef BATTLE_ACTION

#ifdef BATTLE_SKILL_BUFF
#define BUFF_DEBUG    CLogObj(g_BattleLog, eLogLevelInfo, NULL, 0, g_strDeuggerFile.c_str())
#else
#define BUFF_DEBUG  if(1) {} else CNulLog::_sNulLog
#endif // #ifdef BATTLE_BUFF

#ifdef BATTLE_CALC_DEBUG
#define CALC_DBG CLogObj(g_BattleLog, eLogLevelInfo, NULL, 0, g_strDeuggerFile.c_str())
#else
#define CALC_DBG if(1) {} else CNulLog::_sNulLog
#endif // #ifdef BATTLE_CALC_DEBUG

string& operator << (string& s, const CBattleFighter& rBattleFighter);
string& operator << (string& s, CBattleFighterPtr pBattleFighter);

const char* AttrTypeToStr(EFighterAttr e);

const char* MSValToStr(EMachineState e);

string& operator << (string& s, const CBattleSkillEffect& rBattleSkillEffect);

string& operator << (string& s, const CBattleBuff& rBattleBuff);

const char* SETValToStr(ESkillEffectType e);
const char* BFTValToStr(EBStateBuffType e);

string GetAllAttrStr(const TVecFloat& rvecAttr);
string GetAddAttrStr(const TVecFloat& rvecAttr);


bool IsRate100();
bool IsPassiveDisable();
bool IsCrital100();
bool IsNoMain();
bool IsActiveDisable();
bool IsCounter100();
bool IsDodge50();


#define CHEAT_RATE       (0x01 << 0)    // 100%概率
#define NO_PASSIVE       (0x01 << 1)    // 不开启被动技能
#define CHEAT_CRITICAL   (0x01 << 2)    // 100%暴击
#define CHEAT_NO_MIAN    (0x01 << 3)    // 主将不出战
#define NO_ACTIVE        (0x01 << 4)    // 不开启主动技能
#define CHEAT_COUNTER    (0x01 << 5)    // 100%反击
#define CHEAT_DODGE_50   (0x01 << 6)    // 50%闪避

/*
#define CHEAT_RATE       (0x01 << 7)
*/

extern UINT32 g_dwCheatBit;

} // namespace NBattle
#endif // #ifndef BATTLE_DEBUGGER_H
