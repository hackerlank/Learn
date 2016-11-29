#ifndef MailBox_h__
#define MailBox_h__
#include "MailProt.h"
#include "Center2DBComm.h"
const UINT64 MAIL_SEVEN_DAYS = 7 * 3600 * 24;
const UINT64 MAIL_THIRTY_DAYS = 30 * 3600 * 24;
const UINT64 MAIL_SIXTY_DAYS = 60 * 3600 * 24;
const UINT64 MAIL_REFRESH_TIME = 30 * 60 * 1000;
using namespace NMailProt;
using namespace NCenter2DBComm;
class CUser;
class CMailBox 
{
public:
    CMailBox(CUser& rUser);
    virtual ~CMailBox();
   static void AddItemInfo( vector<SMailItemInfo> &vecResults,const SMailItemInfo &rItem );
   static void  AddVecItemInfo(vector<SMailItemInfo> &vecResults,const vector<SMailItemInfo> &SourceItems);

    void LoadMailList();
    void GetMailPageID(UINT32 dwStartIndex, UINT32 dwReqNum, EMailQueryType eQueryType, TVecUINT64& vecMailIDs);
    void GetMailSummaryList(const TVecUINT64& vecMailIDs, TVecMailList& vecMailSummary);
    bool GetMailDetail(UINT64 qwMailID, SMailDetail& rMailDetail);
    UINT32 GetMailCount(EMailQueryType eQueryType) const;
    bool IsMailOverTime(UINT32 dwNow, const SMailDetail& rDetail);
    bool SetMailDetail(UINT64 qwMailID, EMailState  eState);
    bool AddMailToList(const SMailDetail& rMailDetail);
    void RemoveMailFromList(const TVecUINT64& vecMailIDs);
    void GetMailAttachment(UINT64 qwMailID);
    void SendNormalMail(UINT64 qwRoleID, const std::string& strReceiveName, const std::string& strTitle, const std::string& strMsg);

    void TimerCheck();
    bool IsLoadData(){return _bLoadData;}
    void SetLoadData(bool bLoad){_bLoadData = bLoad;}
    bool IsDrawLock(){return  _bDrawLock;}
    void SetDrawLock(bool bLock);//{_bDrawLock = bLock;}
    void PushWaitDraw(UINT64 qwMailId);

    UINT32 GetNewMailCount() const;
    void SortMail();
private:
    CUser& _rOwnerUser;// 拥有者
    TVecMailDetail _vecMail;//邮件列表
    TVecMailDelData _vecInvalidMailIDs;//无效ID
    UINT64 _qwCheckCount;//最近检测时间
    bool _bLoadData;
    bool _bDrawLock;
    set<UINT64> _setWaitDraw;
};

#endif // MailBox_h__
