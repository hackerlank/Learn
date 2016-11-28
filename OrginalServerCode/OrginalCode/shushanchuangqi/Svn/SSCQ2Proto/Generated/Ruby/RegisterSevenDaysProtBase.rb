#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    RegisterSevenDays.rb
#  Purpose:      注册七天目标协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#操作结果
class ERegisterSevenDaysResult
	ESUCCEED = 0#成功
	EFAILED = 1#失败
end

#购买状态
class EBuyStatus
	ENOBUY = 0#不能购买
	ECANBUY = 1#能够购买
	EALREADYBUY = 2#已经购买
end

#函数[GetCurTargetInfo:请求当天目标信息]的返回的参数组成的结构体
class SRetParam_GetCurTargetInfo
	attr_accessor:dwDayID#(UINT32)第几天
	attr_accessor:qwTargetInfo#(UINT64)目标信息(注：每2位代表一个目标奖励的状态0：不能领取；1：能够领取；2：已领取)

	#构造函数
	def initialize
		@dwDayID = 0
		@qwTargetInfo = 0
	end
end

#函数[GetTargetInfoByDayID:通过dwDayID获取目标信息]的返回的参数组成的结构体
class SRetParam_GetTargetInfoByDayID
	attr_accessor:qwTargetInfo#(UINT64)目标信息(注：每2位代表一个目标奖励的状态0：不能领取；1：能够领取；2：已领取)

	#构造函数
	def initialize
		@qwTargetInfo = 0
	end
end

#函数[GetAward:获取奖励]的返回的参数组成的结构体
class SRetParam_GetAward
	attr_accessor:eResult#(枚举类型：ERegisterSevenDaysResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetCurBuyInfo:请求当天购买信息]的返回的参数组成的结构体
class SRetParam_GetCurBuyInfo
	attr_accessor:dwDayID#(UINT32)第几天
	attr_accessor:eBuyStatus#(枚举类型：EBuyStatus)购买状态

	#构造函数
	def initialize
		@dwDayID = 0
		@eBuyStatus = 0
	end
end

#函数[ReqBuy:请求购买]的返回的参数组成的结构体
class SRetParam_ReqBuy
	attr_accessor:eResult#(枚举类型：ERegisterSevenDaysResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：注册七天目标协议
class RegisterSevenDaysProtBase < ProtocolBase
	#以下为发送函数
	#发送：请求当天目标信息
	def send_GetCurTargetInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：通过dwDayID获取目标信息
	def send_GetTargetInfoByDayID(
		dwDayID #(UINT32)第几天
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwDayID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取奖励
	def send_GetAward(
		dwDayID,  #(UINT32)第几天
		byTargetID #(UINT8)目标ID
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwDayID)
		ByteUtil::writeUINT8(data, byTargetID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求当天购买信息
	def send_GetCurBuyInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求购买
	def send_ReqBuy(
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的返回函数需要重载
	#返回：请求当天目标信息
	def onReturn_GetCurTargetInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetCurTargetInfo)返回的参数
	)
	end

	#返回：通过dwDayID获取目标信息
	def onReturn_GetTargetInfoByDayID(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetTargetInfoByDayID)返回的参数
	)
	end

	#返回：获取奖励
	def onReturn_GetAward(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAward)返回的参数
	)
	end

	#返回：请求当天购买信息
	def onReturn_GetCurBuyInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetCurBuyInfo)返回的参数
	)
	end

	#返回：请求购买
	def onReturn_ReqBuy(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqBuy)返回的参数
	)
	end

	#返回处理：请求当天目标信息
	def _doReturn_GetCurTargetInfo(data)
		retParam = SRetParam_GetCurTargetInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwDayID = ByteUtil::readUINT32(data) #(UINT32)第几天
		qwTargetInfo = ByteUtil::readUINT64(data) #(UINT64)目标信息(注：每2位代表一个目标奖励的状态0：不能领取；1：能够领取；2：已领取)
		retParam.dwDayID = dwDayID
		retParam.qwTargetInfo = qwTargetInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetCurTargetInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求当天目标信息
	def _onTimeOut_GetCurTargetInfo(sessionID)
		retParam = SRetParam_GetCurTargetInfo.new;
		onReturn_GetCurTargetInfo(2, retParam)
	end

	#返回处理：通过dwDayID获取目标信息
	def _doReturn_GetTargetInfoByDayID(data)
		retParam = SRetParam_GetTargetInfoByDayID.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		qwTargetInfo = ByteUtil::readUINT64(data) #(UINT64)目标信息(注：每2位代表一个目标奖励的状态0：不能领取；1：能够领取；2：已领取)
		retParam.qwTargetInfo = qwTargetInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetTargetInfoByDayID(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：通过dwDayID获取目标信息
	def _onTimeOut_GetTargetInfoByDayID(sessionID)
		retParam = SRetParam_GetTargetInfoByDayID.new;
		onReturn_GetTargetInfoByDayID(2, retParam)
	end

	#返回处理：获取奖励
	def _doReturn_GetAward(data)
		retParam = SRetParam_GetAward.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ERegisterSevenDaysResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAward(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取奖励
	def _onTimeOut_GetAward(sessionID)
		retParam = SRetParam_GetAward.new;
		onReturn_GetAward(2, retParam)
	end

	#返回处理：请求当天购买信息
	def _doReturn_GetCurBuyInfo(data)
		retParam = SRetParam_GetCurBuyInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwDayID = ByteUtil::readUINT32(data) #(UINT32)第几天
		eBuyStatus = ByteUtil::readUINT8(data) #(枚举类型：EBuyStatus)购买状态
		retParam.dwDayID = dwDayID
		retParam.eBuyStatus = eBuyStatus
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetCurBuyInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求当天购买信息
	def _onTimeOut_GetCurBuyInfo(sessionID)
		retParam = SRetParam_GetCurBuyInfo.new;
		onReturn_GetCurBuyInfo(2, retParam)
	end

	#返回处理：请求购买
	def _doReturn_ReqBuy(data)
		retParam = SRetParam_ReqBuy.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ERegisterSevenDaysResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqBuy(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求购买
	def _onTimeOut_ReqBuy(sessionID)
		retParam = SRetParam_ReqBuy.new;
		onReturn_ReqBuy(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 89;
		@recvFuncList = Array.new

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetCurTargetInfo' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetTargetInfoByDayID' #FuncID: 2
		@retFuncList[2] = '_doReturn_GetAward' #FuncID: 3
		@retFuncList[3] = '_doReturn_GetCurBuyInfo' #FuncID: 4
		@retFuncList[4] = '_doReturn_ReqBuy' #FuncID: 5

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetCurTargetInfo' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetTargetInfoByDayID' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GetAward' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_GetCurBuyInfo' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_ReqBuy' #FuncID: 5
	end

	def handleMessage(data)
		funcID = ByteUtil::readINT8(data);
		if funcID == 0 || funcID < -@retFuncList.length
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

