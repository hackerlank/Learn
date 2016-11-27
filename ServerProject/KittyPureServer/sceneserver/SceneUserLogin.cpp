//此文件为user登录下线的一些逻辑操作

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


bool SceneUser::reg(CMD::SCENE::t_regUser_Gatescene* cmd)
{
	this->charid = cmd->charid;
	if(!RedisMgr::getMe().get_charbase(this->charid,this->charbase))
	{
        Fir::logger->debug("[登录网关]:角色注册场景失败(charbase数据异常,%lu)",this->charid);
		return false;
	}
	ProtoMsgData::Serialize binary;
	if(!RedisMgr::getMe().get_binary(this->charid,binary))
	{
        Fir::logger->debug("[登录网关]:角色注册场景失败(binary数据异常,%lu)",this->charid);
		return false;
	}

	if(!RedisMgr::getMe().is_login_first(this->charid))
	{
		setupBinaryArchive(binary);
	}
	bool ret = SceneUserManager::getMe().addUser(this);
    Fir::logger->debug("[登录网关]:角色注册场景%s(注册场景,%lu)",ret ? "成功" : "失败",this->charid);
    return ret;
}


void SceneUser::offline()
{
	Fir::logger->error("[下线]:%lu 角色下线成功", this->charid);
	zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
	if(handle)
    {
		handle->delSet("playerset",0 ,"online" , this->charid);
    }
	charbase.offlinetime = SceneTimeTick::currentTime.sec();
	save();
	gate = NULL;
}

bool SceneUser::online(SceneTask* _gate)
{
	if (_online) 
	{
        Fir::logger->debug("[客户端登录_3]:角色注册场景失败(角色已在线,%lu)",this->charid);
		return false;
	}
	gate = _gate;
	_online = true;
	zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
	if(handle)
    {
		handle->setSet("playerset",0 ,"online" , this->charid);
    }
    Fir::logger->debug("[客户端登录_3]:角色注册场景成功(角色在线成功,%lu)",this->charid);


	//----所有上线初始化，放在该行以上------
	//通知会话，场景上线成功

	CMD::SCENE::t_Refresh_LoginScene ret_gate;
	ret_gate.charid = this->charid;
	std::string ret;
	encodeMessage(&ret_gate,sizeof(ret_gate),ret);
	if (gate)
	{
		gate->sendCmd(ret.c_str(),ret.size());
	}

	//----上线初始化完成后的处理 都放在onlineInit这个函数里------
	this->onlineInit();
	return true;
}

bool SceneUser::unreg()
{
	//玩家处于离线状态，除了登录消息，不接收任何其它用户指令
	this->offline();
	return true;
}

bool SceneUser::initNewRole()
{
	const pb::Conf_t_InitRole *conf = tbx::InitRole().get_base(1);
	if(!conf)
	{
		Fir::logger->debug("错误:SceneUser::initNewRole找不到对应的初始数据表");
		return false;
	}
    m_package.init(conf->getItemMap());
	return true;
}

bool SceneUser::flushUserInfo()
{   
    ProtoMsgData::AckUserInfo ack;
    ProtoMsgData::UserInfo *userInfo = ack.mutable_userinfo();
    if(userInfo)
    {
        userInfo->set_charid(charid);
        userInfo->set_account(charbase.account);
        userInfo->set_level(ProtoMsgData::Attr_Level);
        userInfo->set_vouchers(ProtoMsgData::Attr_Vouchers);
    }
    std::string ret;
    encodeMessage(&ack,ret);
    return sendCmdToMe(ret.c_str(),ret.size());
}

void SceneUser::onlineInit()
{
	if(!charbase.onlinetime)
	{
		initNewRole();
	}
	//登录时间
	charbase.onlinetime = SceneTimeTick::currentTime.sec();     

	//保存数据
	save();

	//刷新角色面板消息
	flushUserInfo();
}
