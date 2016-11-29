#ifndef _COLLECTMGR_H
#define _COLLECTMGR_H
#include "CollectionCFG.h"
#include "CollectionLevelCFG.h"
#include "EventMgr.h"
#include "CollectionProt.h"
#include "EventMgr.h"
using namespace NProtoCommon;
using namespace NCollectionProt;
//成就基本信息
struct SCollectionCFGEx:SCollectionCFG
{
    void CopyFrom(SCollectionCFG& rCollectionCFG)
    {
        *((SCollectionCFG*)this) = rCollectionCFG;
    }
};

typedef shared_ptr<SCollectionCFGEx> SCollectionCFGExPtr;
typedef std::map<UINT32,SCollectionCFGExPtr> TMapCollectionCFGExPtr;
typedef std::vector<SCollectionCFGExPtr>   TVecCollectionCFGExPtr;

//成就等级信息
struct SCollectionLevelCFGEx:public SCollectionLevelCFG
{
    void CopyFrom(SCollectionLevelCFG& rCFG)
    {
        *((SCollectionLevelCFG*)this) = rCFG;
    }
};

typedef shared_ptr<SCollectionLevelCFGEx> SCollectionLevelCFGExPtr;
typedef std::vector<SCollectionLevelCFGExPtr> TVecCollectionLevelCFGExPtr;

typedef std::map<UINT32,SCollectionInfo> TMapCollectionInfo;

class CPlayer;
class CCollectionMgr:public CRegiserterEvent
{
 public:
     CCollectionMgr(CPlayer& rPlayer);
     ~CCollectionMgr(){};
     
     static bool CollectionInit();
     
     static bool ReLoadConfig(const string&);

     static TMapCollectionCFGExPtr& GetAllCollection();

     static SCollectionLevelCFGExPtr GetCollectionLevelCFGByLevel(UINT32 dwLevel);

     void LoadFromDB(const TVecCollectionInfo& vecCollectionInfo);
     void UpdateToDB(SCollectionInfo& rInfo,EDataChange eDataChange = eOpUpdate);

     void OnFinishCollection(const SCollectionCFGExPtr& pCollectionCFGEx);

     //第一次完成
     void OnNewFinishCollection(const SCollectionCFGExPtr& pCollectionCFGEx);

     bool IsFinished(UINT16 wCollectionID);

     UINT32 GetProcess(UINT16 wCollectionID);

     void SetProcess(UINT16 wCollectionID,UINT32 dwTotal);

     void NotifyInfo(SCollectionInfo& rInfo);
    
     //检查升级
     void OnCheckLevel();

     void RebuildAttr();

     const TVecFloat& GetAttrVec() const { return _vecAttr; };

     void GetCollectionInfo(TVecCollectionInfo& vecCollectionInfo);

     SCollectionCFGExPtr GetCollectCFG(UINT32 dwCollectID);
     
     //事件中心发过来的消息
     virtual void OnEvent(SEventInfoPtr pEventInfo);


 private:
     CPlayer& _rPlayer;

     //属性
     TVecFloat  _vecAttr;


     
     TMapCollectionInfo _mapCollectionInfo;

     static TMapCollectionCFGExPtr _mapCollectionCFGExPtr;
     static TVecCollectionLevelCFGExPtr _VecCollectionLevelCFGExPtr;
     bool _bLog;
     bool _bGetData;
};


#endif

