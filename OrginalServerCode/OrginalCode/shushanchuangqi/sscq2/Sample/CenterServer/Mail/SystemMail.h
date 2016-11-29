#ifndef SystemMail_h__
#define SystemMail_h__
#include "MailProtS.h"
#include "ItemProt.h"
#include "Center2DBComm.h"

using namespace NCenter2DBComm;

enum SysMailSource
{
    SEND_DRAGONBALL_ACT         = 73,   //七龙珠奖励邮件
    TITLE_DRAGONBALL_ACT        = 74,   //七星龙珠奖励标题
    BODY_DRAGONBALL_ACT         = 75,   //七星龙珠奖励正文
    SEND_DRAGONBALL_ENDACT      = SEND_DRAGONBALL_ACT,   //七星连珠奖励邮件
    TITLE_DRAGONBALL_ENDACT     = 76,   //七星连珠奖励标题
    BODY_DRAGONBALL_ENDACT      = 77,   //七星连珠奖励正文

    SEND_XIHESHENCHEALL_ACT     = 80,   //羲和神车装满奖励邮件
    TITLE_XIHESHENCHEALL_ACT    = SEND_XIHESHENCHEALL_ACT,   //羲和神车装满奖励标题
    BODY_XIHESHENCHEALL_ACT     = 81,   //羲和神车装满奖励正文
    SEND_XIHESHENCHENOT_ACT     = 82,   //羲和神车未装满邮件
    TITLE_XIHESHENCHENOT_ACT    = SEND_XIHESHENCHENOT_ACT,   //羲和神车未装满标题
    BODY_XIHESHENCHENOT_ACT     = 83,   //羲和神车未装满正文

    SEND_SEVENCONSUME_ACT       = 90,   //七日消费活动奖励邮件
    TITLE_SEVENCONSUME_ACT      = SEND_SEVENCONSUME_ACT,   //七日消费活动标题
    BODY_SEVENCONSUME_ACT       = 91,   //七日消费活动正文

    SEND_FIRST_GOLD_LOTTERY     = 524,   //游历奖励
    TITLE_FIRST_GOLD_LOTTERY    = 525,   //游历奖励
    BODY_FIRST_GOLD_LOTTERY     = 526,   //\x20\x20\x20\x20行千里路，得万贯财，你在游历中获得了散仙谢琳的认可！点击附件领取奖励！

};

class CSystemMail
{
    public:
        CSystemMail();
        void AddTarget(UINT64 qwRoleID);
        void SetSubject(const string& strSubject);
        void SetSubject(const NMailProt::SysMailSendTxt& strMsgInfo);
        void SetSender(const string& strSender);
        void SetBody(const NMailProt::SysMailSendTxt& strMsgInfo);
        void SetBody(const std::string& strBody);
        //模板物品
        void AddItemInfo(const TVecMailItemInfo& vecInfo);
        void AddItem(const SMailItemInfo& rInfo);
        /*
           void AddMoney(EMoneyType eMoneyType, int nCount, UINT64 OPID)
           {
           AilddItem(eMoneyType, nCount, OPID);
           }
           */
        //实例物品
        void AddBaseItems(const NItemProt::TVecItem& vecItems);
        bool Send(function<void(UINT8 byRet_)> onSent = nullptr);
        UINT8 TestByGet();
        static void SysMailSendTxtToDBString(const NMailProt::SysMailSendTxt& strMsgInfo,string &strBody);
        static void  DBStringToShowString(const string& DBstrMsg, string &strShowBody);
        static bool Init();
        static bool GetSysMailBody(UINT32 dwBodyId,string& strBody);
    private:
        void InitItemAttach();
    private:
        TVecSystemMailTargetInfo vecTarget;
        SSystemMailInfo stMail;
        TVecMailAttachment vecAttach;
        TVecMailItemInfo* pVecItems;
        static map<UINT32,string> _mapBody;
};
#endif // SystemMail_h__
