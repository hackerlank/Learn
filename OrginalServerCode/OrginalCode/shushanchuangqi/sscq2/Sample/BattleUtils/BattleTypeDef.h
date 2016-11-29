#ifndef _BATTLE_TYPE_DEF_H_
#define _BATTLE_TYPE_DEF_H_

#include "Battle.h"

namespace NBattle
{

////////////////////////////////////////////////////////////////////////////////////////////
//Smart Pointer

#ifndef DEF_SMART_POINTER
#define DEF_SMART_POINTER(type, name) \
type name; \
typedef shared_ptr<name> name##Ptr; \
typedef weak_ptr<name> name##Wtr;
#endif // #ifndef DEF_SMART_POINTER

class CBattleAction;
class CMachineState;

DEF_SMART_POINTER(class, CBattleFighter);
DEF_SMART_POINTER(class, CBattleArea);
DEF_SMART_POINTER(class, CBattleSimulator);

DEF_SMART_POINTER(struct, SBattleTeam);

//Smart Pointer
////////////////////////////////////////////////////////////////////////////////////////////

typedef vector  <CBattleFighter*>           TVecBattleFighterPtr;
typedef vector  <CBattleFighterPtr>         TVecBattleFighterSPtr;
typedef set     <CBattleFighterPtr>         TSetBattleFighterPtr;
typedef map     <UINT16, CBattleFighterPtr> TMapBattleFighterPtr;
typedef vector  <SBattleTeamPtr>            TVecBattleTeamPtr;

typedef vector<CBattleAction*> TVecBattleActionPtr;
typedef vector<CMachineState*> TVecMachineStatePtr;

//#define  BIG_POS  // 5*5 的战斗场地

#ifdef  BIG_POS
const UINT8 MAX_POS     = 25;
const UINT8 ROW_LEN     = 5;
const UINT8 LINE_LEN    = 5;
#else
const UINT8 MAX_POS     = 9;
const UINT8 ROW_LEN     = 3;
const UINT8 LINE_LEN    = 3;
#endif

#ifndef SKILL_RANGE_DEFINE
#define SKILL_RANGE_DEFINE

#define SKILL_LEVEL_MAX 100
#define SKILL_QUALITY_MAX 10
#define SKILL_LEVEL(x)  (((UINT32)(x))%(SKILL_LEVEL_MAX))
#define SKILL_ID(x) (((UINT32)(x))/(SKILL_LEVEL_MAX * SKILL_QUALITY_MAX))
#define SKILL_QUALITY(x) (((UINT32)(x))%(SKILL_LEVEL_MAX * SKILL_QUALITY_MAX)/SKILL_LEVEL_MAX)
#define SKILLANDLEVEL(s,l) (((UINT32)(s))*SKILL_LEVEL_MAX * SKILL_QUALITY_MAX + ((UINT32)(l)))
#define SKILLID_QUALITY_LEVEL(s,c,l) (((UINT32)(s))*SKILL_LEVEL_MAX * SKILL_QUALITY_MAX + (UINT32)(c)*SKILL_LEVEL_MAX + (UINT32)(l))

#endif // #ifndef SKILL_RANGE_DEFINE

const UINT8 DEFAULT_POS = 0xFF;     // 默认位置
const UINT8 SCENE_POS   = 255;      // 场景技能位置
const UINT8 PET_POS     = 250;      // 阵灵位置
const UINT8 BEAUTY_POS  = 252;      // 美女位置

const UINT8  MAX_SKILL_POS = 3;     // 主动技能最大个数

const UINT8  INFINIT_CD = 0xFF;     // CD无限长

const INT32 DEFAULT_AURA_ADD_VALUE = 25;       // 默认灵气增加值
const INT32 DEFAULT_AURA_SUB_VALUE = -200;     // 默认减少灵气

const UINT32 PEERLEES_AURA = 100;   // 无双释放需要的灵气值

const INT8 DEFAULT_NORMAL_ATTACK_REIATSU    = 10;    // 普通攻击增加的灵压值
const INT8 DEFAULT_SKILL_ATTACK_REIATSU     = 10;   // 技能攻击增加的灵压值
const INT8 DEFAULT_PEERLESS_ATTACK_REIATSU  = 20;   // 无双攻击增加的灵压值

const UINT8 MAX_REIATSU = 100;     // 最大灵压值

const UINT32 DEFAULT_MGC_JOB_ATTACK_RU  = 1301; // 儒普通攻击ID
const UINT32 DEFAULT_PHY_JOB_ATTACK_SHI = 2301; // 释普通攻击ID
const UINT32 DEFAULT_MGC_JOB_ATTACK_DAO = 3301; // 道普通攻击ID
const UINT32 DEFAULT_PHY_JOB_ATTACK_MO  = 4301; // 墨普通攻击ID

const UINT32 DEFAULT_MAX_ROUND = 50;    // 最大回合数限制

// 技能类型
enum ESkillType
{
    eSkillNone       = 0, // 无效技能
    eSkillActive     = 1, // 主动技能
    eSkillPeerless   = 2, // 无双技能
    eSkillPassive    = 3, // 被动技能
    eSkillSymbol     = 4, // 技能符文
    eSkillPet        = 5, // 阵灵技能
    eSkillScene      = 6, // 场景技能
    eSkillTalent     = 7, // 天赋技能
    eSkillCombine    = 8, // 连携技能
    eSkillBeauty     = 9, // 美女技能
    eSkillTrump      = 10,// 法宝技能
};

// 状态数值叠加方式
enum   EStateAddType
{
    eStateAddNone       = 0,
    eStateAddAdd        = 1,    // 累加形式增加状态
    eStateAddReplaceNew = 2,    // 覆盖形式增加状态（新的覆盖旧的）
    eStateAddReplaceBig = 3,    // 覆盖形式增加状态（大的覆盖小的）
};

// 状态数值减少方式
enum   EStateSubType
{
    eStateSubNone           = 0,
    eStateSubNoNagetive     = 1, // 不能为负数形式减少状态
    eStateSubCanNagetive    = 2, // 可以为负数形式减少状态
};

// 发动技能的类别
enum ESkillLaunchType
{
    eSkillLaunchNone,

    eSkillActiveBegin,                         // 主动释放技能开始
    eSkillActiveNormal = eSkillActiveBegin,    // 普通攻击
    eSkillActiveSkill,                         // 技能攻击
    eSkillActivePeerless,                      // 无双攻击
    eSkillActiveEnd,                           // 主动释放技能结束
                                               
    eSkillPassiveBegin,                        // 被动释放技能开始
    eSkillPassiveCombine = eSkillPassiveBegin, // 连携技能
    eSkillPassiveActive,                       // 被动技能主动出手
    eSkillPassiveBeauty,                       // 美女技能
    eSkillPassiveEnd,                          // 被动释放技能结束
    eSkillMax
};

// 状态机的所有状态
enum EMachineState
{
    eMSNone                 =   0,  //      无条件触发
    eMSBeforeAct            =   1,  //      行动前触发
    eMSAfterAct             =   2,  //      行动后触发
    eMSOnAct                =   3,  //      行动时触发
    eMSAftCounter           =   4,  //      反击后触发
    eMSAftEvade             =   5,  //      闪避后触发
    eMSAftHit               =   6,  //      命中后触发
    eMSAftCri               =   7,  //      暴击后触发
    eMSAftBlocked           =   8,  //      格挡后触发
    eMSOnHPAdd              =   9,  //      回血时触发
    eMSOnHPSub              =   10, //      减血时触发
    eMSAftNormaleAtk        =   11, //      普通攻击后触发
    eMSAftActSkill          =   12, //      主动技能攻击后触发
    eMSAftPeerless          =   13, //      无双技能攻击后触发
    eMSAftPassiveSkill      =   14, //      被动技能后触发
    eMSAftSomeSkillAtk      =   15, //      指定技能攻击后触发
    eMSAftSomeSkillAct      =   16, //      指定技能触发后触发
    eMSBeforeDead           =   17, //      死亡时触发
    eMSOnHPLow              =   18, //      生命下降至指定百分比时触发
    eMSOnEnter              =   19, //      入场时触发
    eMSOnAuraAdd            =   20, //      增加灵气时触发
    eMSOnAuraSub            =   21, //      减少灵气时触发
    eMSOnRoundStart         =   22, //      指定回合开始时触发
    eMSAftRound             =   23, //      X回合后触发
    eMSOnBuffGet            =   24, //      获得指定buff时触发
    eMSOnBuffSet            =   25, //      造成指定buff时触发
    eMSOnBuffAct            =   26, //      指定buff触发时触发
    eMSAftBeAtked           =   27, //      被攻击后触发
    eMSBeforeCri            =   28, //      暴击前
    eMSBeAtk                =   29, //      被攻击
    eMSOnAtkDmg             =   30, //      产生攻击伤害
    eMSOnCounter            =   31, //      反击
    eMSForget               =   32, //      封印时
    eMSAfterAtk             =   33, //      攻击后
    eMSBeforeAtk            =   34, //      攻击前
    eMSBleed                =   35, //      流血时
    eMSHit                  =   36, //      命中
    eMSNormalAtk            =   37, //      普通攻击
    eMSStart                =   38, //      起手
    eMSEnter                =   39, //      入场
    eMSEvade                =   40, //      闪避
    eMSOnLostBuff           =   41, //      失去指定buff时触发
    eMSRelease              =   42, //      释放CD
    eMSBeDmged              =   43, //      受伤害
    eMSAftDmg               =   44, //      受伤害后
    eMSBeforeDmg            =   45, //      受伤害前
    eMSOnDead               =   46, //      死亡
    eMSState                =   47, //      异常时
    eMSStun                 =   48, //      晕眩时
    eMSSkillAtk             =   49, //      主动技能攻击
    eMSOnHPChanged          =   50, //      HP变化后
    eMSOnHPHigh             =   51, //      生命值上升至指定百分比触发
    eMSOnAllBuffGet         =   52, //      全场获得指定BUFF
    eMSOnAllLostBuff        =   53, //      全场失去指定BUFF
    eMSOnReiatsuAdd         =   54, //      灵气达到指定数值触发
    eMSBeforeRound          =   55, //      每次回合开始前
    eMSOnTherapyLaunch      =   56, //      释放治疗技能时触发
    eMSOnClearBuff          =   57, //      清除指定Buff时触发
    eMSAftDead              =   58, //      死亡后
    eMSOnOtherSideBuffAct   =   59, //      敌方指定Buff触发
    eMSOnKilled             =   60, //      杀死目标时触发
    eMSSummonTimeOut        =   61, //      召唤物持续时间减少
    eMSSelfSideDead         =   62, //      我方有单位死亡
    eMSSelfSideDamaged      =   63, //      我方有单位受伤
    eMSSelfSideTherapy      =   64, //      我方受到治疗效果
    eMSOnCombineAdd         =   65, //      连携点数到达指定值触发
    eMSAfterCombineAdd      =   66, //      连携技能触发后
    eMSBeforeCombineSkill   =   67, //      连携技能发动前
    eMSOnCombineSkill       =   68, //      连携技能发动
    eMSAfterCombineSkill    =   69, //      连携技能发动
    eMSSelfSideDeadAll      =   70, //      我方全死完了
    eMSOnSelfSideBuffGet    =   71, //      我方获得指定BUFF
    eMSOnOtherBounceDmg     =   72, //      敌方受到反伤伤害
    eMSOnSelfPeerless       =   73, //      我方释放无双时
    eMSOnOtherBeDmged       =   74, //      敌方受到伤害
    eMSOnSelfCrit           =   75, //      我方造成暴击
    eMSOnSelfCounter        =   76, //      我方造成反击
    eMSMax                      //      最大值，现用于释放CD状态
};

// 效果对应出手状态
enum EEffectType
{
    eETNone    = 0,     
    eETBefore,          // 出手前
    eETSkill,           // 出手中
    eETAfter,           // 出手后
    eETMax
};

//技能效果类型
enum ESkillEffectType
{
    ENone         = 0,  // 无效类型
    EPhyDmg       = 1,  // 物理伤害
    EMgcDmg       = 2,  // 法术伤害
    ETrueDmg      = 3,  // 真实伤害
    EHPDmg        = 4,  // 生命百分比伤害
    EAbsorbHP     = 5,  // 吸血
    EAuraAdd      = 6,  // 增加灵气
    EAuraSub      = 7,  // 减少灵气
    ETherapy      = 8,  // 回复
    EAbsorb       = 9,  // 吸血
    EBuffLast     = 10, // 持续状态
    EStun         = 11, // 眩晕
    EConfuse      = 12, // 混乱
    EForget       = 13, // 沉默
    EBleed        = 14, // 流血
    EAttrAdd      = 15, // 属性增益
    EAttrSub      = 16, // 属性减益
    EShield       = 17, // 护盾
    EAtkMulti     = 18, // 伤害提升指定倍数
    EAssist       = 19, // 援护
    EProtect      = 20, // 承受其他单位x%的伤害
    EPierce       = 24, // 破甲(伤害减免减少一半)
    EBounceDmg    = 25, // 反伤
    EHide         = 26, // 影遁
    EInvincible   = 27, // 无敌
    EFreeze       = 29, // 冻结
    EExtendLast   = 30, // 延长回合
    ETherapyAdd   = 31, // 治疗效果提升
    ESummon       = 32, // 召唤
    ECongest      = 33, // 蓄力
    EBronze       = 34, // 铜人
    EKingkong     = 35, // 金刚
    EBlock        = 36, // 格挡
    EShoke        = 37, // 电击
    ENeverDead    = 38, // 免疫死亡
    EReflect      = 39, // 反弹状态
    EResist       = 40, // 免疫
    EClone        = 41, // 分身
    ESealed       = 42, // 封印
    EDamgeAbsorb  = 43, // 吸收伤害百分比
    EDamageReduce = 44, // 伤害减免
    EAttackAddP   = 45, // 攻击提升
    EAttackSubP   = 46, // 攻击减少
    EDefendAddP   = 47, // 防御提升
    EDefendSubP   = 48, // 防御减少
    EDialog       = 49, // 对话
    EBlunt        = 50, // 麻痹
    EClearDebuff  = 51, // 清除负面效果
    EResistDeBuff = 52, // 免疫负面效果
    ETransForm    = 53, // 变身
    EToggleSkills = 54, // 技能切换
    EPartBroken   = 55, // 部位破坏
    ENoGainAura   = 56, // 无法获得灵气
    EEffectAdd    = 57, // 效果值增益
    EEffectSub    = 58, // 效果值减益
    EDmgTherapy   = 59, // 受伤回血
    EBuffAction   = 60, // 被动技能出手动作
    ESkillTrigger = 61, // 技能跳字
    EAttr2AttrAdd = 62, // 属性增益其他属性
    EStoned       = 63, // 石化
    EDeadAction   = 64, // 死亡动画
    EBlind        = 65, // 致盲
    EResistAdd    = 66, // 抗性增益
    EResistSub    = 67, // 抗性减益
    EDamageShare  = 68, // 伤害分担
    ERevival      = 69, // 复活
    EBuffAction2  = 70, // 被动技能施法动作
    ESkillEffectTypeMax // 技能效果的最大值
};

// 技能目标的选择方式
enum EAreaSelectType
{
    eAreaSelectDefault      = 0,    // 默认选择方式
    eAreaSelectAbsolute     = 1,    // 绝对坐标
    eAreaSelectRandom       = 2,    // 随机选择
    eAreaSelectMirro        = 3,    // 镜像或者自己
    eAreaSelectResponse     = 4,    // 反馈对象
    eAreaSelectHPPMin       = 5,    // 生命比率最低
    eAreaSelectRandomPos    = 6,    // 随机坐标
    eAreaSelectRandomCnt    = 7,    // 随机选择（目标不重复）
    eAreaSelectRandomEpt    = 8,    // 随机选择空位
    eAreaSelectRandomCtrl   = 9,    // 随机选择控制目标
    eAreaSelectRandomHPLost = 10,   // 随机选择HP不满的
    eAreaSelectID           = 11,   // 指定ID的散仙
    eAreaSelectDefaultPos   = 12,   // 默认选择方式（允许空位）
};

// 技能范围的概率选择方式
enum EAreaRateType
{
    eAreaRateDefault = 0,   // 每个范围独立计算概率
    eAreaRateSame,          // 所有范围统一计算概率
    eAreaRateMax,
};

// 技能范围的方向
enum EAreaSide
{
    eAreaSideBoth   = 0,    // 双方
    eAreaSideSelf   = 1,    // 自己方
    eAreaSideOther  = 2,    // 对方
};

// 状态机的状态
enum EMSCheckType
{
    eMSCTNone = 0,
    eMSCTSelf,          // 自己引发的状态
    eMSCTOther,         // 所有人引发的状态
    eMSCTSelfSide,      // 自己一方所有人引发的状态
    eMSCTOtherSide,     // 对面一方所有人引发的状态
    eMSCTMax,
};

// 技能的免疫类型
enum EResistType
{
    eResistTypeNone = 0,    // 不可免疫
    eResistTypeNormal,      // 可以被免疫
    eResistTypeControl,     // 可以被免疫（控制类异常状态）
    eResistTypeMax,
};

// 伤害行为的触发类型
enum EDamageType
{
    eDTNone = 0,
    eDTActive,          // 非Buff触发的伤害（主动技能/普通攻击/法宝）
    eDTNoPosActive,     // 非主动攻击，Buff触发的伤害（美女/阵灵/组合）
    eDTCounter,         // 反击伤害
    eDTBuff,            // 持续性Buff或者被动技能造成的伤害
    eDTBounce,          // 伤害反弹
    eDTShare,           // 分担伤害
    eDTMax
};

// 战场中的指定地方
enum EBattleFieldDest
{
    eBFDNone = 0,   // 非法位置
    eBFDNormal,     // 战场中的位置（0-8的散仙站位or250的阵灵站位）
    eBFDSummon,     // 战场中的召唤位置
    eBFDScene,      // 战场中的场景位置（就是场景技能）
    eBFDMax         // 最大位置
};

//战斗所在的方向
enum EBattleSide
{
	eBSideAttack = 0, //进攻方向
	eBSideDefend = 1, //防守方向
	eBSideMax //最大值
};

} // namespace NBattle

#endif  // _BATTLE_TYPE_DEF_H_
