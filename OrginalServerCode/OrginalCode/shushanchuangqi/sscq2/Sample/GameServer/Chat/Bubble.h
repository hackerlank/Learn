#ifndef BUBBLE_H
#define BUBBLE_H

#include "stdafx.h"

#include "RoleInfoDefine.h"

using namespace NRoleInfoDefine;
using namespace NProtoCommon;
enum BubbleType
{
    BubbleType_NewMail  =1,//新邮件
    BubbleType_FrindInvite = 2,//好友邀请
    BubbleType_ChatMsg = 3,//聊天消息
    BubbleType_GuidInvite = 4,//帮派邀请
    BubbleType_AccuseGuidLeader =5,//弹劾帮主
    BubbleType_Sit =6,//打坐消息
    BubbleType_DemonTowerFail=9,//锁妖塔被抢
};

class CBubble
{
    public:
        CBubble(UINT16 wID, UINT16 wMessageID, const TVecINT64& vecParam, const TVecString& vecString);
        CBubble(const SDBBubbleInfo& rInfo);

        virtual ~CBubble();

        UINT16 GetID() const;
        UINT16 GetMessageID() const;
        UINT32 GetTime() const;
        const TVecINT64&  GetParam() const;
        TVecINT64&  GetParam();
        const TVecString& GetString() const;

        void SetTransID(UINT64 qwTransID);
        UINT64 GetTransID() const;

        bool GetAllInfo(SBubbleInfo& rInfo, UINT8 byIndex) const;
        bool GetAllDBInfo(SDBBubbleInfo& rInfo, UINT64 qwRoleID) const;

    private:
        UINT16     _wID;
        UINT16     _wMessageID;
        UINT32     _dwTime;
        TVecINT64  _vecParam; //整型变量
        TVecString _vecString; //字符串型变量
        UINT64     _qwTransID;
};

class CBubbleOwner
{
    public:
        CBubbleOwner(CUserPtr pUser);
        virtual ~CBubbleOwner();

        bool GetAllInfo(TVecBubbleInfo& vecInfo) const;
        bool InitFromDB(const TVecDBBubbleInfo& vecInfo);

        bool CreateBubble(UINT16 wMsgID);
        bool CreateBubble(UINT16 wMsgID, const TVecINT64& vecParam);
        bool CreateBubble(UINT16 wMsgID, const TVecString& vecString);
        bool CreateBubble(UINT16 wMsgID, const TVecINT64& vecParam, const TVecString& vecString);

        bool Respond(UINT8 byIndex, const TVecINT64& vecParam, const TVecString& vecString);

        void ClearOfflineBubble();

        void NotifyBubbleUpdate(UINT8 byIndex, CBubblePtr pBubble, EDataChange eType) const ;
        void NotifyAllInfo() const;

    private:
        void Update2DB(CBubblePtr pBubble, EDataChange eType) const;
        bool AddBubble(CBubblePtr pBubble, bool bInit = false);
        CUserPtr GetUser() const;

    private:
        UINT64          _qwMaxTransID;
        TVecBubblePtr   _vecBubble;
        CUserWtr        _pUser;
};

#endif // #ifndef BUBBLE_H
