#ifndef ICONAPPEARMANAGERDMGR_H_
#define ICONAPPEARMANAGERDMGR_H_
#include "stdafx.h" 
#include "Singleton.h"
#include "IconAppearCFG.h"

class CUser;
enum EIconAppearCond
{
    eIconAppearNone,//不触发
    eIconAppearTask,//任务触发
    eIconAppearLevel,//等级触发
    eIconAppearRecharge,//充值触发
    //eIconAppearCanDel,//常驻功能，接口删除
   // eIconAppearBySelf,//自己控制Icon周期
    eIconAppearMax,//最大值
};

class IconAppearCondBase
{
    public:
        IconAppearCondBase(EIconAppearCond eType);
        EIconAppearCond GetCondType();
        virtual bool CanOpen(CUser &rUser) = 0;
        virtual ~IconAppearCondBase();
    private:
        EIconAppearCond _eCondType;
};
DEF_SMART_POINTER(class, IconAppearCondBase);

class IconAppearCondTask: public IconAppearCondBase
{
    public:
        IconAppearCondTask(UINT16 wTaskId);
        virtual bool CanOpen(CUser &rUser);
        virtual ~IconAppearCondTask();
    private:
        UINT16 _wTaskId;
};
DEF_SMART_POINTER(class, IconAppearCondTask);

class IconAppearCondLevel: public IconAppearCondBase
{
    public:
        IconAppearCondLevel(UINT16 wLevel);
        virtual bool CanOpen(CUser &rUser);
        virtual ~IconAppearCondLevel();
    private:
        UINT16 _wLevel;
};
DEF_SMART_POINTER(class, IconAppearCondLevel);


struct SIconAppearCFGEx : public SIconAppearCFG
{
    SIconAppearCFGEx()
    {
    }
    SIconAppearCFGEx(const SIconAppearCFG& rIconAppearCFG):
        SIconAppearCFG(rIconAppearCFG)
    {
        _pCond = NULL;
    }
    IconAppearCondBasePtr _pCond;
};
typedef vector<SIconAppearCFGEx> TVecAppearCFGEx;
class CIconAppearMgr : public Singleton<CIconAppearMgr>
{
    public:
        bool Init();
        void UserFinishTask(CUser &rUser);
        void UserLevelUp(CUser &rUser);
        //void IconControlBySelf(UINT32 dwActID);
        //void IconControlBySelf(CUser &rUser);
        bool LoadConfig(bool bReload = false);
        TVecAppearCFGEx*  GetVecAppearCFGEx(EIconAppearCond eCond);
        void SynToClientAddIconAppear(CUser &rUser,const TVecUINT16& vecIconAppear);
        void DelAction(CUser &rUser,UINT16 wIcon);
        void CloseAction(CUser &rUser,UINT16 wIcon);
        void CloseActionToClient(CUser&rUser, UINT16 wIcon);
        void OpenActionToClientForAll(UINT16 wIcon);
        void CloseActionToClientForAll(UINT16 wIcon);
        bool IsActive(UINT16 wIcon);
        void DoActiveIconForOnLine(CUser &rUser);
        UINT16 GetIconByActiveID(UINT32 dwActiveID);
        void FinishReCharge(CUser &rUser);
        bool IsActivityOpen(CUser& rUser,UINT32 dwActiveID);
        void OpenActionToClient(CUser& rUser,TVecUINT16 vecIcon);
        UINT32 GetActivityIDByIcon(UINT16 wIcon);
    private:
        void CheckIconAppear(CUser &rUser,EIconAppearCond eCond);
        void CheckIconAppear(UINT32 dwCond);
    private:
        map<EIconAppearCond, TVecAppearCFGEx > _mapIconAppearInfo;
        TVecUINT16 _vecActiveNoneCond;
        TSetUINT16 _rSetActive;
        TSetUINT16 _rSetReCharge;
        map<UINT32,UINT16> _mapActionID;

};

#endif // ICONAPPEARMANAGERDMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

