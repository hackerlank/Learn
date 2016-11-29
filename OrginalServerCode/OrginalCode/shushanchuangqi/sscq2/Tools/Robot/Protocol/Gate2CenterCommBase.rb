#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    Gate2CenterComm.rb
#  Purpose:      GateServer到CenterServer的通信协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ServerCommonBase.rb'

#协议类：GateServer到CenterServer的通信协议
class Gate2CenterCommBase < ProtocolBase
	#以下为发送函数
	#发送：心跳
	def send_KeepAlive(
		dwUsrCnt #(UINT32)玩家数量
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, dwUsrCnt)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家上线通知
	def send_UserLoginNtf(
		qwUsrID,  #(UINT64)帐号ID
		strIPAddr #(string)IP地址
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeSTRING(data, strIPAddr)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家下线通知
	def send_UserLogoutNtf(
		qwUsrID,  #(UINT64)帐号ID
		eLeaveType #(枚类型：ServerCommon::ELeaveType)下线类型
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeUINT8(data, eLeaveType)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：玩家登录通知
	def onRecv_UserWantLoginNtf(
		qwUsrID, #(UINT64)帐号ID
		dwCryptoCode #(UINT32)登录验证码
	)
		raise NotImplementedError
	end
	#接收：踢玩家下线
	def onRecv_KickUserOffLine(
		qwUsrID, #(UINT64)帐号ID
		eLeaveType #(枚类型：ServerCommon::ELeaveType)下线类型
	)
		raise NotImplementedError
	end
	#接收：替换帐号
	def onRecv_ReplaceUser(
		qwUsrID #(UINT64)帐号ID
	)
		raise NotImplementedError
	end
#以下为接收处理函数
	#接收处理：玩家登录通知
	def _doRecv_UserWantLoginNtf(data)
		qwUsrID = ByteUtil::readUINT64(data)
		dwCryptoCode = ByteUtil::readUINT32(data)
		return onRecv_UserWantLoginNtf(qwUsrID, dwCryptoCode)
	end

	#接收处理：踢玩家下线
	def _doRecv_KickUserOffLine(data)
		qwUsrID = ByteUtil::readUINT64(data)
		eLeaveType = ByteUtil::readUINT8(data)
		return onRecv_KickUserOffLine(qwUsrID, eLeaveType)
	end

	#接收处理：替换帐号
	def _doRecv_ReplaceUser(data)
		qwUsrID = ByteUtil::readUINT64(data)
		return onRecv_ReplaceUser(qwUsrID)
	end

	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 6;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_UserWantLoginNtf' #FuncID: 1
		@recvFuncList[1] = '_doRecv_KickUserOffLine' #FuncID: 2
		@recvFuncList[2] = '_doRecv_ReplaceUser' #FuncID: 3
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

