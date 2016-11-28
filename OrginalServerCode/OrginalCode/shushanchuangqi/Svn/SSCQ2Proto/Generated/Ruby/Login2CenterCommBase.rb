#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    Login2CenterComm.rb
#  Purpose:      LoginServer到CenterServer的基本通信协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#登陆请求的结果
class EReqResult
	EREQSUCCEED = 0#登陆请求成功
	EREQFULL = 1#玩家数量达到上限
	EREQONLINE = 2#已有角色在线
	EREQKICKWAIT = 3#踢帐号等待
	EREQLEAVEWAIT = 4#下线等待
	EREQTOOFREQENT = 5#请求太频繁
	EREQNOTINITED = 6#服务器未完全启动
	EREQOTHERERR = 7#其它错误
end

#协议类：LoginServer到CenterServer的基本通信协议
class Login2CenterCommBase < ProtocolBase
	#以下为发送函数
	#发送：心跳
	def send_KeepAlive(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家请求进入服务器
	def send_UserLoginReq(
		qwUsrID,  #(UINT64)帐号ID
		dwSessionID,  #(UINT32)会话ID
		byAddrType #(UINT8)地址类型
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeUINT32(data, dwSessionID)
		ByteUtil::writeUINT8(data, byAddrType)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：玩家请求进入服务器应答
	def onRecv_UserLoginAck(
		eResult, #(枚举类型：EReqResult)登陆请求的结果
		qwUsrID, #(UINT64)帐号ID
		dwSessionID, #(UINT32)会话ID
		strGateAddr, #(string)GateServer的地址
		wGatePort, #(UINT16)GateServer的端口
		dwCryptoCode #(UINT32)登录验证码
	)
		raise NotImplementedError
	end
#以下为接收处理函数
	#接收处理：玩家请求进入服务器应答
	def _doRecv_UserLoginAck(data)
		eResult = ByteUtil::readUINT8(data)
		qwUsrID = ByteUtil::readUINT64(data)
		dwSessionID = ByteUtil::readUINT32(data)
		strGateAddr = ByteUtil::readSTRING(data)
		wGatePort = ByteUtil::readUINT16(data)
		dwCryptoCode = ByteUtil::readUINT32(data)
		return onRecv_UserLoginAck(eResult, qwUsrID, dwSessionID, strGateAddr, wGatePort, dwCryptoCode)
	end

	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 2;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_UserLoginAck' #FuncID: 1
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

