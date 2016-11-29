#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    LoginProt.rb
#  Purpose:      登陆LoginServer的协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#登陆结果
class ELoginResult
	ELOGINSUCCEED = 0#登陆成功
	EVERSIONLESS = 1#客户端版本号低于服务器
	ENOTACTIVATED = 2#帐号未激活此区服
	EACCOUNTINVALID = 3#帐号错误
	EPASSWORDINVALID = 4#密码错误
	EACCPWDERR = 5#账号不存在或密码错误
	EUSRSTATEERR = 6#帐号状态异常
	EACCOUNTFREEZE = 7#帐号冻结
	EACCOUNTLOGIN = 8#帐号正在登陆中
	EREQOVERTIME = 9#请求超时
	EREQTOOFREQENT = 10#请求太频繁
	ESERVERFULL = 11#服务器已满
	EROLEONLINE = 12#已有角色在线
	EKICKWAIT = 13#踢帐号等待
	ELEAVEWAIT = 14#下线等待
	EENTERTOOFREQENT = 15#请求太频繁
	ELOGINSERVERERR = 16#服务器内部错误
	ESERVERINITERR = 17#服务器未启动完毕
	ELOGINOTHERERR = 18#系统错误
end

#协议类：登陆LoginServer的协议
class LoginProtBase < ProtocolBase
	#以下为发送函数
	#发送：登陆请求
	def send_LoginReq(
		qwUsrID,  #(UINT64)帐号ID
		usGroupID,  #(UINT16)区号
		dwVersion,  #(UINT32)版本号
		strPassword #(string)验证key
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeUINT16(data, usGroupID)
		ByteUtil::writeUINT32(data, dwVersion)
		ByteUtil::writeSTRING(data, strPassword)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：登陆结果返回
	def onRecv_LoginAck(
		eLoginResult, #(枚举类型：ELoginResult)请求登录结果
		qwRoleId, #(UINT64)角色ID
		strGateIP, #(string)GateServer的IP
		wGatePort, #(UINT16)GateServer端口
		dwCryptoCode #(UINT32)登录验证码
	)
		raise NotImplementedError
	end
#以下为接收处理函数
	#接收处理：登陆结果返回
	def _doRecv_LoginAck(data)
		eLoginResult = ByteUtil::readUINT8(data)
		qwRoleId = ByteUtil::readUINT64(data)
		strGateIP = ByteUtil::readSTRING(data)
		wGatePort = ByteUtil::readUINT16(data)
		dwCryptoCode = ByteUtil::readUINT32(data)
		return onRecv_LoginAck(eLoginResult, qwRoleId, strGateIP, wGatePort, dwCryptoCode)
	end

	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 1;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_LoginAck' #FuncID: 1
	end

	def handleMessage(data)
		funcID = ByteUtil::readINT8(data);
		if funcID == 0 || funcID > @recvFuncList.length
			return false
		end
		if funcID > 0 
			func = @recvFuncList[funcID - 1]
		end
		if func
			 send(func, data)
		end
		#if func != nil
			#return call_user_func(Array.new(self, func), data)
		#end
		return true
	end
end

