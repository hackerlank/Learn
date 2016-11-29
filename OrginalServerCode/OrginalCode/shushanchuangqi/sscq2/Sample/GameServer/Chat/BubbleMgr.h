#ifndef BUBBLE_MGR_H
#define BUBBLE_MGR_H

#include "stdafx.h"
#include "BubbleCFG.h"

#include "Singleton.h"

struct SBubbleCFGEx : public SBubbleCFG
{
    void SetConfig(const SBubbleCFG& rBubbleCFG)
    {
        *(SBubbleCFG*)this = rBubbleCFG;
    }
    //UINT16 GetMessageID() const { return _wMessageID;}
    UINT8 GetPriority () const { return _byPriority; }
    bool IsOfflineEnable() const { return _byOfflineEnable? true:false;}
    UINT16 GetGroupID() const { return _wGroupID;}
    UINT16 GetGroupType() const { return _wGroupType; }
};

class CBubbleMgr : public Singleton<CBubbleMgr>
{
    public:
        bool Init();
        bool LoadConfig();

        CBubblePtr CreateBubble(UINT16 wMsgID, const TVecINT64& vecParam, const TVecString& vecString) const;

        UINT8 GetPriority (UINT16 wMsgID) const;
        bool IsOfflineEnable(UINT16 wMsgID) const;
        UINT16 GetGroupID(UINT16 wMsgID) const;

        SBubbleCFGEx* GetConfig(UINT16 wMsgID) const;

        UINT16 GetMessageID(UINT16 wMsgID) const;

    //private:
       // bool InitID2MessageID();

    private:
        CBubbleLoader _cLoader;

        map<UINT16, SBubbleCFGEx*> _mapCFG;
        //TVecUINT16  _vecBubbleMessageID;
};

#endif // #ifndef BUBBLE_MGR_H
