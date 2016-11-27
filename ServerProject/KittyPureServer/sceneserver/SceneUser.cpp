//角色类一般函数实现

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
const DWORD DelCount = 30;

SceneUser::SceneUser(SceneTask *t,QWORD setCharid) :charid(setCharid),m_package(this),gate(t)
{
    needSave = false;
    _online = false;
    bzero(lastSaveCharBaseMD5,16);
    bzero(lastSaveMD5,16);
}

SceneUser::~SceneUser()
{
}

bool SceneUser::sendCmdToMe(const void *pstrCmd, const DWORD nCmdLen) const
{
    if ((DWORD)nCmdLen > zSocket::MAX_DATASIZE)
    {
        Fir::logger->error("发送消息过大:%d",nCmdLen);
        return false;
    }
    if(gate)
    {
        return gate->sendCmdToUser(charid, pstrCmd, nCmdLen);
    }

    return false;
}

bool SceneUser::sendCmdToGateway(const void *pstrCmd, const DWORD nCmdLen) const
{
    if ((DWORD)nCmdLen > zSocket::MAX_DATASIZE)
    {    
        Fir::logger->error("发送消息过大:%d",nCmdLen);
        return false;
    } 

    if(gate)
    {
        return gate->sendCmd(pstrCmd,nCmdLen);
    }

    return false;
}

bool SceneUser::loop()
{
    return false;
}
