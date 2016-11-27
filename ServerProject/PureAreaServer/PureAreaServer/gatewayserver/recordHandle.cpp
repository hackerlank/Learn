#include "recordHandle.h"

RecordHandle::RecordHandle() : MessageHandle("档案服客户端消息处理")
{
}

RecordHandle::~RecordHandle()
{
}

bool RecordHandle::init()
{
#define MESSAGE_INIT(msg,call) \
    {\
        boost::shared_ptr<MsgCallBack<boost::shared_ptr<RecordClient>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<RecordClient>,ProtoMsgData::msg>(&RecordHandle::call));\
    }
#undef MESSAGE_INIT
    return true;
}
