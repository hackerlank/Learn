//此文件主要放user的一些检测函数

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

#if 0
bool SceneUser::updateAttrVal(const HelloKittyMsgData::AttrType &attrType,const DWORD value)
{
    HelloKittyMsgData::AckUpdateAttrVal updateAttr;
    updateAttr.set_attrtype(attrType);
    updateAttr.set_attrval(value);
    updateAttr.set_updatechar(charid);
    std::string ret;
    encodeMessage(&updateAttr,ret);
    sendCmdToMe(ret.c_str(),ret.size());
    return true;
}
#endif
