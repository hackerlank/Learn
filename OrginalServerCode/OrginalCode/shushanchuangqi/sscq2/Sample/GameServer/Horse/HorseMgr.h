
#ifndef _HORSE_H_
#define _HORSE_H_
#include <memory>
#include <map>
#include "RoleInfoDefine.h"
#include "HorseBaseCFG.h"
#include "HorseUpgradeCFG.h"
#include "HorseSvr.h"
using namespace NRoleInfoDefine;
using namespace NProtoCommon;
using namespace NHorse;
class CHorseMgr;
namespace NGlobalChatProt { struct SShowInfo;};

class CHorse:public CPoolObj<CHorse>
{
public:
    CHorse(CUser& rUser,CHorseMgr& rHorseMgr) : _rUser(rUser),_rHorseMgr(rHorseMgr),_dwHorseSpeed(0) {}

    ~CHorse() {}

    //创建初始化
    bool HorseInit(UINT32 dwHorseID);

    void RebuildAttr();

    void LoadFromDB(const SHorseDB& sInfo);
    void Update2DB(SHorseDB& rInfo, EDataChange eDataChange = eOpUpdate);
    void Update2DB();

    //升阶
    UINT8 ActiveUpgrade(bool bAll);

    const TVecFloat& GetAttrVec() const { return _vecAttr; };

    UINT32 GetHorseID() { return _oHorseDB.dwHorseID; };
    UINT32 GetHorseLevel() { return _oHorseDB.dwHorseLevel;};
    UINT32 GetHorseAttrID(); 
    void ChangePos(UINT8 byPos);
    
    bool IsSkillAttrLock(UINT32 dwPOs);
    void UnLockSkillAttr(UINT32 dwPOs);

    void GetHorseInfo(SHorseInfo& rHorseInfo);

    SHorseDB& GetHorsInfo() { return _oHorseDB; }
    
    void UpdateSkillVec();

    UINT32 GetHorseSpeed() { return _dwHorseSpeed; }

    bool IsMounted() { return _oHorseDB.dwPos != 0; };

    void GetShowInfo(NGlobalChatProt::SShowInfo& sInfo);

private:
    CUser& _rUser;
    CHorseMgr& _rHorseMgr;
    SHorseDB _oHorseDB;
    TVecUINT32 _vecSkillAttr;    
    mutable TVecFloat _vecAttr;
    UINT32 _dwHorseSpeed;
};


typedef std::shared_ptr<CHorse> CHorsePtr;
typedef std::map<UINT32,CHorsePtr> TMapHorsePtr;

typedef shared_ptr<SHorseBaseCFG> SHorseBaseCFGPtr;
typedef std::map<UINT32,SHorseBaseCFGPtr> TMapHorseBaseCFGPtr;

typedef shared_ptr<SHorseUpgradeCFG> SHorseUpgradeCFGPtr;
typedef std::map<UINT32,SHorseUpgradeCFGPtr> TMapHorseUpgradeCFGPtr;


class CHorseMgr:public CPoolObj<CHorseMgr>
{

public:
   CHorseMgr(CUser& rUser): _rUser(rUser),_dwMountHorseID(0),_dwMountHorseLevel(0),_dwHorseSpeed(0), _dwExp(0), _dwPos(0) {}
   
   static bool HorseMgrInit();
   static bool ReLoadConfig(const string&);
   static SHorseBaseCFGPtr GetHorseBaseCFG(UINT32 dwHorseID);
   static SHorseUpgradeCFGPtr GetHorseUpgradeCFG(UINT32 dwHorseLevel);

   void WriteHorseLog(UINT32 dwID);
   void LoadFromDB(const TVecHorseDB& vecHorseDB);
   void Update2DB(EDataChange eDataChange = eOpUpdate );

   //修改坐骑位置
   bool ChangeHorseModel(UINT32 dwHorseID);

   //激活坐骑
   bool ActiveHorse(UINT32 dwHorseID, bool bForce = false);

   //坐骑进阶
   UINT8 UpgradeHorse(UINT32 dwHorseID,bool bAll= false);

   bool UnLockHorseSkillAttr(UINT32 dwHorseID, UINT32 dwPos);

   //通知坐骑属性
   bool NotifyAttrList(UINT32 dwHorseID=0);

   bool SetHorseStatus(UINT32 dwHorseID,UINT32 dwPos);

   //开启坐骑系统
   void Open();

   void HorseList(TVecHorseInfo& vecHorseInfo);

   void HorseNotifyList();

   void RebuildAttr();


   const TVecFloat& GetAttrVec() const { return _vecAttr; };

   UINT32 GetHorseSpeed(){ return _dwHorseSpeed; }


   void UpateGroupAttr(); 

   void BroadLookChange();
   const TMapHorsePtr& GetHorseList() { return _mapHorsePtr; } 

   void GetAppearHorse(UINT32& dwHorseId,UINT32& dwHorseLevel)
   {
       dwHorseId = _dwMountHorseID;
       dwHorseLevel = _dwMountHorseLevel;
   }

   CHorsePtr GetHorseByID(UINT32 dwHorseID);
   bool IsActiveModel(UINT32 dwHorseID);
private:
   CUser& _rUser;
   

   UINT32 _dwMountHorseID;

   UINT32 _dwMountHorseLevel;

   UINT32 _dwHorseSpeed;

   UINT32 _dwExp;

   //是否骑乘
   UINT32 _dwPos;

   TVecUINT32 _vecModelID;

   TMapHorsePtr _mapHorsePtr;

   mutable TVecFloat _vecAttr;

public:
   static TMapHorseBaseCFGPtr _mapHorseBaseCFGPtr;
   static TMapHorseUpgradeCFGPtr _mapHorseUpgradeCFGPtr;
};
#endif // _HORSE_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

