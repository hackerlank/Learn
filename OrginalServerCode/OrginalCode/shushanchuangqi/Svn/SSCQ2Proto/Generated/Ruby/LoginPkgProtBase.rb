#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    LoginPkgProt.rb
#  Purpose:      累计登入礼包协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#操作结果
class EResultInLoginProt
	EPKGERROR = 0#错误
	EPKGGAIN = 1#已经领取
	EPKGFULL = 2#背包已满
	EPKGSUCCESS = 3#成功
end

#函数[GetLoginPkg:获取礼包]的返回的参数组成的结构体
class SRetParam_GetLoginPkg
	attr_accessor:wResult#(UINT16)操作结果:从地位向高位，1表示领取，0表示没有领
	attr_accessor:eResult#(枚举类型：EResultInLoginProt)操作结果

	#构造函数
	def initialize
		@wResult = 0
		@eResult = 0
	end
end

#函数[GetPkgInfo:登入礼包信息]的返回的参数组成的结构体
class SRetParam_GetPkgInfo
	attr_accessor:wDays#(UINT16)连续登入的天数
	attr_accessor:wResult#(UINT16)操作结果:从地位向高位，1表示领取，0表示没有领

	#构造函数
	def initialize
		@wDays = 0
		@wResult = 0
	end
end

#协议类：累计登入礼包协议
class LoginPkgProtBase < ProtocolBase
	#以下为发送函数
	#发送：获取礼包
	def send_GetLoginPkg(
		byIndex #(UINT8)累计天数
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byIndex)
		return @svrHandler.sendPacket(data)
	end

	#发送：登入礼包信息
	def send_GetPkgInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：登入礼包信息
	def onRecv_SendPkgInfo(
		wDays, #(UINT16)连续登入的天数
		wResult #(UINT16)操作结果:从地位向高位，1表示领取，0表示没有领
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取礼包
	def onReturn_GetLoginPkg(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetLoginPkg)返回的参数
	)
	end

	#返回：登入礼包信息
	def onReturn_GetPkgInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetPkgInfo)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：登入礼包信息
	def _doRecv_SendPkgInfo(data)
		wDays = ByteUtil::readUINT16(data)
		wResult = ByteUtil::readUINT16(data)
		return onRecv_SendPkgInfo(wDays, wResult)
	end

#以下为返回处理函数
	#返回处理：获取礼包
	def _doReturn_GetLoginPkg(data)
		retParam = SRetParam_GetLoginPkg.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		wResult = ByteUtil::readUINT16(data) #(UINT16)操作结果:从地位向高位，1表示领取，0表示没有领
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EResultInLoginProt)操作结果
		retParam.wResult = wResult
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetLoginPkg(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取礼包
	def _onTimeOut_GetLoginPkg(sessionID)
		retParam = SRetParam_GetLoginPkg.new;
		onReturn_GetLoginPkg(2, retParam)
	end

	#返回处理：登入礼包信息
	def _doReturn_GetPkgInfo(data)
		retParam = SRetParam_GetPkgInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		wDays = ByteUtil::readUINT16(data) #(UINT16)连续登入的天数
		wResult = ByteUtil::readUINT16(data) #(UINT16)操作结果:从地位向高位，1表示领取，0表示没有领
		retParam.wDays = wDays
		retParam.wResult = wResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetPkgInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：登入礼包信息
	def _onTimeOut_GetPkgInfo(sessionID)
		retParam = SRetParam_GetPkgInfo.new;
		onReturn_GetPkgInfo(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 92;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_SendPkgInfo' #FuncID: 1

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetLoginPkg' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetPkgInfo' #FuncID: 2

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetLoginPkg' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetPkgInfo' #FuncID: 2
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

