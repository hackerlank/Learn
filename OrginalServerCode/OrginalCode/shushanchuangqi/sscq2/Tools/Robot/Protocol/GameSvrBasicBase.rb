#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    GameSvrBasic.rb
#  Purpose:      GameServer的基本协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#断开原因
class EBreakReason
	EBREAKNONE = 0#无
	EBREAKUSRKICK = 1#被另一处登录的帐号踢下线
	EBREAKSVRKICK = 2#被服务器踢下线
	EBREAKEXCEPT = 3#发生异常
	EBREAKOTHER = 4#其它原因
	EBREAKINDULGEKICK = 5#防沉迷系统已启动，请休息5小时
	EBREAKINDULGETIMEKICK = 6#防沉迷系统已启动，请休息完5小时后登陆
end

#GM命令
class SGMCommand
	attr_accessor:strCmd #(string)命令
	attr_accessor:strName #(string)名称
	attr_accessor:strDesc #(string)描述

	#构造函数
	def initialize
		@strCmd = ''
		@strName = ''
		@strDesc = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strCmd = @strCmd
		obj.strName = @strName
		obj.strDesc = @strDesc
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGMCommand.new
		s.strCmd = ByteUtil::readSTRING(data)
		s.strName = ByteUtil::readSTRING(data)
		s.strDesc = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGMCommand::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeSTRING(data, @strCmd)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeSTRING(data, @strDesc)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[KeepAlive:心跳]的返回的参数组成的结构体
class SRetParam_KeepAlive
	attr_accessor:dwServerTime#(UINT32)服务器的当前时间(1970年1月1日0时开始的秒数)

	#构造函数
	def initialize
		@dwServerTime = 0
	end
end

#协议类：GameServer的基本协议
class GameSvrBasicBase < ProtocolBase
	#以下为发送函数
	#发送：心跳
	def send_KeepAlive(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：GM指令结果返回
	def onRecv_GMCommandAck(
		strResult #(string)指令结果
	)
		raise NotImplementedError
	end
	#接收：打开所有功能
	def onRecv_OpenAllSystem(
		bOpen #(bool)是否打开
	)
		raise NotImplementedError
	end
	#接收：服务器断开连接通知
	def onRecv_ServerDisconnectNtf(
		eBreakReason #(枚举类型：EBreakReason)断开连接原因
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：心跳
	def onReturn_KeepAlive(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_KeepAlive)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：GM指令结果返回
	def _doRecv_GMCommandAck(data)
		strResult = ByteUtil::readSTRING(data)
		return onRecv_GMCommandAck(strResult)
	end

	#接收处理：打开所有功能
	def _doRecv_OpenAllSystem(data)
		bOpen = ByteUtil::readBOOL(data)
		return onRecv_OpenAllSystem(bOpen)
	end

	#接收处理：服务器断开连接通知
	def _doRecv_ServerDisconnectNtf(data)
		eBreakReason = ByteUtil::readUINT8(data)
		return onRecv_ServerDisconnectNtf(eBreakReason)
	end

#以下为返回处理函数
	#返回处理：心跳
	def _doReturn_KeepAlive(data)
		retParam = SRetParam_KeepAlive.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwServerTime = ByteUtil::readUINT32(data) #(UINT32)服务器的当前时间(1970年1月1日0时开始的秒数)
		retParam.dwServerTime = dwServerTime
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_KeepAlive(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：心跳
	def _onTimeOut_KeepAlive(sessionID)
		retParam = SRetParam_KeepAlive.new;
		onReturn_KeepAlive(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 13;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_GMCommandAck' #FuncID: 1
		@recvFuncList[1] = '_doRecv_OpenAllSystem' #FuncID: 2
		@recvFuncList[2] = '_doRecv_ServerDisconnectNtf' #FuncID: 3

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_KeepAlive' #FuncID: 1

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_KeepAlive' #FuncID: 1
	end

	def handleMessage(data)
		funcID = ByteUtil::readINT8(data);
		if funcID == 0 || funcID > @recvFuncList.length || funcID < -@retFuncList.length
			return false
		end
		if funcID > 0 
			func = @recvFuncList[funcID - 1]
		else
			func = @retFuncList[-funcID - 1]
		end
		if func
			 send(func, data)
		end
		#if func != nil
			#return call_user_func(Array.new(self, func), data)
		#end
		return true
	end

	def onTimeOut(funcID, sessionID)
		if funcID == 0 || funcID > @timeFuncList.length
			return
		end
		send(@timeFuncList[funcID - 1], sessionID)
	end
end

