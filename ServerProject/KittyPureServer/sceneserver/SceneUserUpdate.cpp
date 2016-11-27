#include "SceneUser.h"
#include "zMetaData.h"
#include <stdarg.h>
#include "SceneServer.h"
#include "zMetaData.h"
#include "TimeTick.h"
#include "SceneUserManager.h"
#include <zlib.h>
#include <bitset>
#include "RecordClient.h"
#include "LoginUserCommand.h"
#include "xmlconfig.h"
#include <limits>
#include "RedisMgr.h"
#include "json/json.h"
#include "login.pb.h"
#include "extractProtoMsg.h"
#include "serialize.pb.h"
#include "dataManager.h"
#include "tbx.h"
#include "SceneTaskManager.h"
#include "SceneToOtherManager.h"
#include "key.h"

bool SceneUser::updateAttrVal(const ProtoMsgData::AttrType &attrID,const DWORD val)
{
    ProtoMsgData::AckUpdateAttrVal ack;
    ack.set_attrtype(attrID);
    ack.set_attrval(val);

    std::string ret;
    encodeMessage(&ack,ret);
    return sendCmdToMe(ret.c_str(),ret.size());
}
