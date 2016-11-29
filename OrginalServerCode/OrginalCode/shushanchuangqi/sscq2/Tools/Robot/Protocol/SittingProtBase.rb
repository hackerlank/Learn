#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    SittingProt.rb
#  Purpose:      打坐协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ItemProtBase.rb'
require_relative './MapProtBase.rb'

#以下为类型定义

#请求的结果
class ESittingResult
	ESITTINGSUCCEED = 0#成功
	ESITTINGTOGETHER = 1#没有找到双修的人
	EHASSITTING = 2#您已经在打坐
	ENOTINCITY = 3#主城才能打坐
	ELEVELLOW = 4#等级不足
	ESITTINGERROTHER = 5#其它错误
end

#函数[DoSittingTogether:请求双修]的返回的参数组成的结构体
class SRetParam_DoSittingTogether
	attr_accessor:eResult#(枚举类型：ESittingResult)请求结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：打坐协议
class SittingProtBase < ProtocolBase
	#以下为发送函数
	#发送：请求双修
	def send_DoSittingTogether(
		qwOtherID #(UINT64)对方ID,0表示单修，非0表示双修
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwOtherID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求取消修炼
	def send_CancelSitting(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：玩家打坐结算
	def onRecv_CancelSittingOffLine(
		byType, #(UINT8)0,表示单修，1表示双修
		vecRes, #(SResource的数组)获得的资源
		dwSittingTimer #(UINT32)开始时间
	)
		raise NotImplementedError
	end
	#接收：打坐状态变化
	def onRecv_UpdateSitting(
		byState, #(UINT8)0,表示结束打坐，1 ，开始打坐
		vecOtherApear, #(SPlayerAppear的数组)空表示单修，非空表示双修
		dwSittingTimer #(UINT32)开始时间
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：请求双修
	def onReturn_DoSittingTogether(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_DoSittingTogether)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：玩家打坐结算
	def _doRecv_CancelSittingOffLine(data)
		byType = ByteUtil::readUINT8(data)
		vecRes = SResource::vectorFromStream(data)
		dwSittingTimer = ByteUtil::readUINT32(data)
		return onRecv_CancelSittingOffLine(byType, vecRes, dwSittingTimer)
	end

	#接收处理：打坐状态变化
	def _doRecv_UpdateSitting(data)
		byState = ByteUtil::readUINT8(data)
		vecOtherApear = SPlayerAppear::vectorFromStream(data)
		dwSittingTimer = ByteUtil::readUINT32(data)
		return onRecv_UpdateSitting(byState, vecOtherApear, dwSittingTimer)
	end

#以下为返回处理函数
	#返回处理：请求双修
	def _doReturn_DoSittingTogether(data)
		retParam = SRetParam_DoSittingTogether.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ESittingResult)请求结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_DoSittingTogether(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求双修
	def _onTimeOut_DoSittingTogether(sessionID)
		retParam = SRetParam_DoSittingTogether.new;
		onReturn_DoSittingTogether(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 55;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_CancelSittingOffLine' #FuncID: 1
		@recvFuncList[1] = '_doRecv_UpdateSitting' #FuncID: 2

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_DoSittingTogether' #FuncID: 1

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_DoSittingTogether' #FuncID: 1
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

