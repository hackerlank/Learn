// =====================================================================================
//
//       Filename:  Battle.h
//
//    Description:  战斗模块
//
//        Version:  1.0
//        Created:  08/15/2014 05:52:17 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#ifndef BATTLE_H
#define BATTLE_H

#include "BattleGS.h"
#include "ProtoCommon.h"

#ifndef DEF_SMART_POINTER
#define DEF_SMART_POINTER(type, name) \
type name; \
typedef shared_ptr<name> name##Ptr; \
typedef weak_ptr<name> name##Wtr;
#endif // #ifndef DEF_SMART_POINTER

DEF_SMART_POINTER(class, IBattleSimulator);
DEF_SMART_POINTER(class, IBattleFighter);

typedef vector<IBattleFighterPtr>       TVecBattleFighterPtr;
typedef vector<TVecBattleFighterPtr>    TVecVecBattleFighterPtr;

using namespace NBattleGS;
using namespace NProtoCommon;

class IBattleSimulator
{
    public:
        virtual ~IBattleSimulator();

        // 放置某个方向的战斗对象
        virtual void PutFighters(UINT8 bySide, UINT64 qwLeaderID, UINT16 wLevel, 
                TVecBattleFighterPtr& rvecBattleFighter, UINT64 qwInstID = 0, bool bFullHP = true,
                SFeatureBasePtr pMainFeature = NULL) = 0;

        // 放置场景技能
        virtual void PutScene(IBattleFighterPtr pFighter) = 0;

        // 获取当前战斗模拟器中的战斗对象
        virtual bool GetFighterList(UINT8 bySide, TVecBattleFighterPtr& rvecBattleFighter) = 0;

        // 战斗开始
        virtual void          Start(EBattleType eType) = 0;

        // 获取战斗胜利者
        virtual EBattleResult GetFinalWinner() const = 0;
        // 是否攻击者全部死亡
        virtual bool          IsAttackDead() const = 0;
        // 是否防守者全部死亡
        virtual bool          IsDefenseDead() const = 0;

        // 获取战斗总出手数目
        virtual UINT32        GetTurns() const = 0;
        // 获取战斗总回合数
        virtual UINT32        GetRounds() const = 0;
        // 获取战报
        virtual void          GetReport(std::string& strReport) const = 0;

        // 获取战报ID
        virtual UINT64        GetBattleID() const = 0;
};

// 用于外部类赋值，供IBattleFighter类初始化基本参数的结构体
struct SBFInfo
{
    UINT64          qwInstID;      // 将唯一ID
    UINT16          wFighterID;    // 将类型ID
    INT32           dwPos;         // 阵型中的位置
    UINT8           byTeamID;      // 所属的队伍ID
    UINT8           byLevel;       // 等级
    ECareerType     eJob;          // 职业
    string          strName;       // 玩家姓名
    ESexType        eSex;          // 性别
    SFeatureBasePtr pFeature;      // 外观形象
    SBFInfo() : 
        qwInstID(0), wFighterID(0), dwPos(-1), byTeamID(0),
        byLevel(0), eJob(ECAREER_ALL), eSex(ESEX_ALL)
    {}
};

typedef function < IBattleFighterPtr (UINT16 wFighterID) > FunBFCreateFromID;
typedef function < UINT32 (const TVecFloat& rvecAttr) > FunBFAttrBP;
typedef function < UINT32 (const TVecUINT32& rvecSkillsID) > FunBFSkillBP;

class IBattleFighter
{
    public:
        virtual ~IBattleFighter();

        // 设置战斗对象基本参数
        virtual bool InitFighter(const SBFInfo& rBFInfo) = 0;

        // 设置战斗对象外观
        virtual bool InitFighterAttr(const TVecFloat& rvecFighterAttr) = 0;
        virtual bool InitFighterBattleInfo(UINT32 dwHpMax, UINT32 dwHp, UINT32 dwAura, UINT32 dwAuraMax) = 0;
        virtual bool SetFighterAttr(UINT8 byIndex, FLOAT fValue) = 0; //InitFighterAttr 前用

        // 设置战斗对象技能
        virtual bool InitFighterSkills(const TVecUINT32& rvecAllSkills, UINT32 dwNormalAttack = 0) = 0;


        // 额外增加技能
        virtual bool PushMoreSkills(const TVecUINT32& rvecSkills) = 0;

        // 设置战斗对象备用切换技能
        virtual bool InitFighterSkillsEx(const std::vector<TVecUINT32>& rvecvecAllSkills, const TVecUINT32& vecNormalAttack) = 0;

        // 从协议中的
        virtual bool InitFromInfo(const SBattleFighter& rBF, TVecBattleFighterPtr& rvecBattleFighterSummon) = 0;

        virtual void GetBattleFighterInfo(SBattleFighter& sBf) const = 0;

        virtual void   SetPos(INT32 dwPos) = 0;
        virtual INT32  GetPos() const = 0;

        virtual void   SetLevel(UINT32 dwLevel) = 0;

        virtual UINT16 GetID() const = 0;
        virtual UINT8  GetColour() const = 0;
        virtual UINT8  GetQuality() const = 0;
        virtual UINT16 GetLevel() const = 0;

        virtual UINT32 RegenAllHP() = 0;
        virtual UINT32 GetHP() const = 0;
        virtual void   SetHP(UINT32 dwHp) = 0;
        virtual void   SetMaxHP(UINT32 dwMaxHP) = 0;
        virtual void   SetAura(UINT32 dwAura) = 0;
        virtual UINT32 GetAura() const = 0;
        virtual UINT32 GetMaxAura() const = 0;
        virtual UINT32 GetMaxHP() const = 0;
        virtual UINT64 GetInstID() const = 0;

    public:
        // 静态函数用于全集变量的初始化或者获取
        
        static FunBFCreateFromID    _funCreateFromID;   //  这个函数需要调用类注册，从ID生成IBattleFighter对象的方法
        static FunBFAttrBP          _funAttrBP;         //  这个函数需要调用类注册，计算属性对应的战斗力
        static FunBFSkillBP         _funSkillBP;        //  这个函数需要调用类注册，计算技能对应的战斗力

        static INT32 GetScenePos();
        static INT32 GetFormationPos();
        static INT32 GetPetPos();
        static INT32 GetBeautyPos();
        static INT32 GetMaxPos();
        static INT32 GetMinPos();

};

// 创建战斗模拟器对象
IBattleSimulatorPtr CreateBattleSimulator(UINT64 qwGUID);
// 创建战斗对象
IBattleFighterPtr   CreateBattleFighter();

// 战斗总体初始化(配置，战报)
bool BattleInit(const string& strReportDir, const string& strPath);

// =====================================================================================
// 战报线程相关处理

// 获取战报
void GetBattleReport( UINT64 qwBattleID , function<void(string*)> funcGetted);
// 战报处理
void ProcessBattleReportResult();

// 战报线程相关处理
// =====================================================================================

// =====================================================================================
// 战斗相关配置重载

// 战斗所有配置重载
void BattleConfigReload(const string& strPath);
// 技能基本配置重载
bool BattleSkillBaseReload(const string& strPath, const string& strName);
// 技能效果重载
bool BattleSkillEffectReload(const string& strPath, const string& strName);
// 技能范围重载
bool BattleAreaReload(const string& strPath, const string& strName);

// 战斗相关配置重载
// =====================================================================================

// 战斗作弊模式
UINT32 BattleCheatMode(UINT32 dwCheatBit);

#endif // #ifndef BATTLE_H

