
#ifndef TASKMARKET_H_
#define TASKMARKET_H_

#include "User.h"
#include "VarDefine.h"
#include "Singleton.h"
#include "V3TaskCFG.h"
#include "PHPProt.h"

//using namespace NPHPProt;
using namespace NVarDefine;

struct STaskMarketKey
{
    UINT64 qwRoleID;
    UINT32 dwTaskID;
    UINT8  byStep;
    STaskMarketKey(UINT64 _qwRoleID,UINT32 _dwTaskID, UINT8 _byStep) : 
        qwRoleID(_qwRoleID),
        dwTaskID(_dwTaskID),
        byStep(_byStep)
    { }
    bool operator < (const STaskMarketKey & sKey) const 
    {
        if(dwTaskID != sKey.dwTaskID)
            return dwTaskID > sKey.dwTaskID;
        if(byStep != sKey.byStep)
            return byStep > sKey.byStep; 
        return qwRoleID > sKey.qwRoleID;
    }
};
enum ETaskCond
{
    eTaskCondNone, //无
    eTaskCond15Tower     = 2, //通过锁妖塔15层
    eTaskCondDuoBao      = 3, //参加一次秘境夺宝
    eTaskCondDujie       = 6, //渡劫主角金丹期
    eTaskCond5Fighter    = 7, //上阵5个散仙
    eTaskCondLevel42     = 10, //主角升级42级
    eTaskCondGuild       = 11, //创建或者加入一个帮派
    eTaskCondEquip       = 14, //强化任意装备到 7级
    eTaskCondTeamDungon  = 15, //通关路月林副本
    eTaskCondFighter107  = 17, //招募散仙秦子玲
    eTaskCondEnd //最大值
    
};
struct STaskCFGEx : public SV3TaskCFG
{
    UINT32 dwTaskID;
    UINT8  byStep;
    UINT32 dwLootID;
    UINT32 dwCondID;
    void CopyConfig(const SV3TaskCFG& rConfig)
    {
        (*(SV3TaskCFG*)this) = rConfig;
    }
};
typedef shared_ptr<STaskCFGEx> STaskCFGExPtr;
typedef std::vector<STaskCFGExPtr> TVecTaskCFGEx;

class CTaskMarketMgr : public Singleton<CTaskMarketMgr>
{
    public:
        CTaskMarketMgr()
            { }
        virtual ~CTaskMarketMgr() { }
        //初始化
        bool Init();
        //加载配置
        bool LoadConfig();
        //检测任务是否完成
        NPHPProt::ETaskState CheckTask(CPlayer &rPlayer, UINT32 dwTaskID, UINT8 byStep,UINT8 byOpt);
    private:
        //发放奖励
        bool SendMail(CPlayer& rPlayer,UINT32 dwLootID,STaskMarketKey& oKey);
        bool CheckCond(CPlayer& rPlayer, UINT32 dwCondID);
        UINT32 GetTaksID(const string& strTask);
        //获得配置
        STaskCFGExPtr GetConfig(UINT32 dwTaskID, UINT8 byStep);
    private:
        TVecTaskCFGEx _vecConfig;
        std::set<STaskMarketKey> _setTmp; //临时记录玩家领奖数据
};

#define TaskMarketMgr CTaskMarketMgr::Instance()
#endif 
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

