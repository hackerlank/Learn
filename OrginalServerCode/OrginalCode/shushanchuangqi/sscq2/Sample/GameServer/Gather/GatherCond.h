#ifndef GATTHERCOND_H__
#define GATTHERCOND_H__
#include "ObjPool.h"
#include "GatherProt.h"
class CPlayer;
using namespace NGatherProt; 
class CGatherCondBase
{
    public:
        DEF_NEW_DELETE(CGatherCondBase);
        CGatherCondBase(EGatherConType eType)
            :_ConType(eType)
        {
        }
        CGatherCondBase()
            :_ConType(eGCT_None)
        {
        }
        static CGatherCondBase* CreateCond(EGatherConType eType,UINT32 dwParam1,UINT32 dwParam2);
        virtual EGatherResult CheckCond(CPlayer & rPlayer) = 0;
        virtual void DoCond(CPlayer & rPlayer){};
        EGatherConType GetType(){return _ConType;}
    private:
        EGatherConType _ConType;
};
typedef shared_ptr<CGatherCondBase> CGatherCondBasePtr;
class CGatherCondLevel: public CGatherCondBase
{
    public:
        DEF_NEW_DELETE(CGatherCondLevel);
        CGatherCondLevel(UINT16 wLevel)
            :CGatherCondBase(eGCT_Level),_wLevel(wLevel)
        {
        }
        virtual EGatherResult CheckCond(CPlayer & rPlayer);
    private:
        UINT16 _wLevel;
};

class CGatherCondItem: public CGatherCondBase
{
    public:
        DEF_NEW_DELETE(CGatherCondItem);
        CGatherCondItem(UINT16 wItemId,UINT16 wItemNum)
            :CGatherCondBase(eGCT_Item),_wItemId(wItemId),_wItemNum(wItemNum)
        {
        }
        virtual EGatherResult CheckCond(CPlayer & rPlayer);
        virtual void DoCond(CPlayer & rPlayer);
    private:
        UINT16 _wItemId;
        UINT16 _wItemNum;
};

class CGatherCondVIP: public CGatherCondBase
{
    public:
         DEF_NEW_DELETE(CGatherCondVIP);
        CGatherCondVIP(UINT8 byVIPLevel)
            :CGatherCondBase(eGCT_VIP),_byVIPLevel(byVIPLevel)
        {
        }
        virtual EGatherResult CheckCond(CPlayer & rPlayer);
    private:
        UINT8 _byVIPLevel;
};
#endif// GATTHERCOND_H__

