#ifndef TRIPOD_LOG_H
#define TRIPOD_LOG_H

#include  "TripodProt.h"

using namespace NTripodProt;
using namespace NProtoCommon;


class CTripodLog
{
    public:
        CTripodLog(UINT64 qwRoleID);
        virtual ~CTripodLog();

        virtual ETripodLogType GetType() const = 0;

        UINT64 GetRoleID() const;
        UINT16 GetID() const;

        bool GetAllInfo(STripodLog& rInfo) const;

        bool InitFromDB(const STripodLog& rInfo);

        static void Update2DB(CTripodLogPtr pTripodLog);

        virtual bool FormatParam(UINT16 wMsgID, const TVecINT64& rvecParam, const TVecString& rvecString, UINT32 dwTime);

    private:
        UINT64      _qwRoleID;
        UINT16      _wMsgID;
        TVecINT64   _vecParam;
        TVecString  _vecString;
        UINT32      _dwTime;
};

class CTripodHelpLog : public CTripodLog
{
    public:
        CTripodHelpLog(UINT64 qwRoleID);
        virtual ~CTripodHelpLog();

        virtual ETripodLogType GetType() const;
};

#endif // #ifndef TRIPOD_LOG_H
