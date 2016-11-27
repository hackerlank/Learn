/**
 * \file	SceneUser.h
 * \version  	$Id: SceneUser.h 67 2013-04-23 09:44:20Z  $
 * \author  	,
 * \date 	2013年04月07日 15时48分31秒 CST
 * \brief 	场景用户定义
 *
 * 
 */

#ifndef _SCENEUSER_H_
#define _SCENEUSER_H_

#include <map>
#include "Fir.h"
#include "SceneTask.h"
#include "CharBase.h"
#include "zTime.h"
#include "RecordCommand.h"
#include "zSerialize.h"
#include "zCmdBuffer.h"
#include "common.h"
#include "dataManager.h"
#include "zMemDB.h"
#include "zMemDBPool.h"
#include "serialize.pb.h"
#include "package.h"

class RecordClient;

class SceneUser 
{
    public:
        friend class SceneUserManager;
        //角色id，全服唯一
        QWORD charid;
        //昵称
        CharBase charbase;
        //后面角色需要存档的零散数据，放这里
        ProtoMsgData::CharBin charbin;
        //包裹
        Package m_package;
        //存档md5	
        char lastSaveMD5[16];
    public:
        SceneUser(SceneTask *gate,QWORD setCharid);
        virtual ~SceneUser();
        //发送数据到客户端
        bool sendCmdToMe(const void *pstrCmd, const DWORD nCmdLen) const;
        //发送数据到网关
        bool sendCmdToGateway(const void *pstrCmd, const DWORD nCmdLen) const;
        //是否在线标志
        inline bool is_online()
        {
            return _online;
        }
        //轮询
        bool loop();
        //上线函数
        bool online(SceneTask* _gate);
        //从session注册到场景函数
        bool reg(CMD::SCENE::t_regUser_Gatescene *Cmd);
        //注销
        bool unreg();
        // 从charbase和二进制数据克隆一个玩家
        bool clone(CharBase charbase,std::string allbinary);
        //压缩角色数据
        DWORD saveBinaryArchive(unsigned char *out , const int maxsize);
        //保存角色数据
        bool save();
        //刷新角色基本信息
        bool flushUserInfo();
        RecordClient  *getSelfRecord();
        //上线辅助函数
        void onlineInit();
        //获得gate
        inline SceneTask* getGate()
        {
            return gate;
        }
    public:
        //更新属性
        bool updateAttrVal(const ProtoMsgData::AttrType &attrID,const DWORD val);
    private:
        //下线辅助函数
        void offline();
        //新建角色初始化信息
        bool initNewRole();
        // 获取该角色二进制数据
        std::string getBinaryArchive();
        //反序列化二进制数据
        void setupBinaryArchive(ProtoMsgData::Serialize& binary);
        //第一次访问家园
    private:
        SceneTask *gate;
        //玩家在线状态
        bool _online; 
        bool needSave;
        char lastSaveCharBaseMD5[16];
};
#endif
