#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    GatherProt.rb
#  Purpose:      采集协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ItemProtBase.rb'

#以下为类型定义

#副本结果
class EGatherResult
	EGATHERSUCCESS = 0#成功
	EGATHERIN = 1#正在采集中
	EGATHEROUT = 2#没有采集中
	EGATHERITEMLIMIT = 3#采集所需物品不足
	EGATHERBUSY = 4#玩家忙
	EGATHERPACKEMPTYMIN = 5#采集空格子不足
	EGATHERVIP = 6#御剑等级不足
	EGATHERLEVEL = 7#等级不足
	EGATHERNOTEXIST = 8#采集物不存在
	EGATHERTOOFAR = 9#采集物太远
	EGATHERNUMLIMIT = 10#采集物数量不足
	EGATHERTASK = 11#需要接相关任务才可以采集
	EGATHERCANCEL = 12#采集中断
	EGATHERFINISH = 13#采集完成
	EGATHERLUAERR = 14#Lua脚本拒绝
	EGATHEROTHERERR = 15#未知错误
end

#采集条件
class EGatherConType
	EGCT_NONE = 0#无定义
	EGCT_LEVEL = 1#等级
	EGCT_ITEM = 2#道具，包括仙石等
	EGCT_VIP = 3#VIP宝箱
	EGCT_END = 4#定义完毕
end

#函数[GatherReq:采集请求]的原来的参数组成的结构体
class SOrigParam_GatherReq
	attr_accessor:dwGatherId #(UINT32)采集ID

	#构造函数
	def initialize
		@dwGatherId = 0
	end
end

#函数[GatherReq:采集请求]的返回的参数组成的结构体
class SRetParam_GatherReq
	attr_accessor:eResult#(枚举类型：EGatherResult)采集结果
	attr_accessor:dwGatherTimer#(UINT32)采集剩余时间

	#构造函数
	def initialize
		@eResult = 0
		@dwGatherTimer = 0
	end
end

#函数[CancelGather:取消采集]的返回的参数组成的结构体
class SRetParam_CancelGather
	attr_accessor:eResult#(枚举类型：EGatherResult)取消采集结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetGatherInfo:客户端查询采集信息]的返回的参数组成的结构体
class SRetParam_GetGatherInfo
	attr_accessor:dwGtatherId#(UINT32)采集实例
	attr_accessor:dwReserverTimer#(UINT32)剩余时间

	#构造函数
	def initialize
		@dwGtatherId = 0
		@dwReserverTimer = 0
	end
end

#协议类：采集协议
class GatherProtBase < ProtocolBase
	#以下为发送函数
	#发送：采集请求
	def send_GatherReq(
		dwGatherId #(UINT32)采集ID
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		origParam = SOrigParam_GatherReq.new
		origParam.dwGatherId = dwGatherId
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwGatherId)
		return @svrHandler.sendPacket(data)
	end

	#发送：取消采集
	def send_CancelGather(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：客户端查询采集信息
	def send_GetGatherInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：采集结束通知
	def onRecv_GatherEndNotify(
		eResult #(枚举类型：EGatherResult)服务器返回结果
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：采集请求
	def onReturn_GatherReq(
		ret, #0为成功，1为失败，2为超时
		origParam, #(类类型：SOrigParam_GatherReq)原来的参数
		retParam #(类类型：SRetParam_GatherReq)返回的参数
	)
	end

	#返回：取消采集
	def onReturn_CancelGather(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_CancelGather)返回的参数
	)
	end

	#返回：客户端查询采集信息
	def onReturn_GetGatherInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetGatherInfo)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：采集结束通知
	def _doRecv_GatherEndNotify(data)
		eResult = ByteUtil::readUINT8(data)
		return onRecv_GatherEndNotify(eResult)
	end

#以下为返回处理函数
	#返回处理：采集请求
	def _doReturn_GatherReq(data)
		retParam = SRetParam_GatherReq.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGatherResult)采集结果
		dwGatherTimer = ByteUtil::readUINT32(data) #(UINT32)采集剩余时间
		retParam.eResult = eResult
		retParam.dwGatherTimer = dwGatherTimer
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_GatherReq(ret, origParam, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：采集请求
	def _onTimeOut_GatherReq(sessionID)
		retParam = SRetParam_GatherReq.new;
		origParam = @sessionMgr.getData(sessionID)
		onReturn_GatherReq(2, origParam, retParam)
	end

	#返回处理：取消采集
	def _doReturn_CancelGather(data)
		retParam = SRetParam_CancelGather.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGatherResult)取消采集结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_CancelGather(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：取消采集
	def _onTimeOut_CancelGather(sessionID)
		retParam = SRetParam_CancelGather.new;
		onReturn_CancelGather(2, retParam)
	end

	#返回处理：客户端查询采集信息
	def _doReturn_GetGatherInfo(data)
		retParam = SRetParam_GetGatherInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwGtatherId = ByteUtil::readUINT32(data) #(UINT32)采集实例
		dwReserverTimer = ByteUtil::readUINT32(data) #(UINT32)剩余时间
		retParam.dwGtatherId = dwGtatherId
		retParam.dwReserverTimer = dwReserverTimer
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetGatherInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：客户端查询采集信息
	def _onTimeOut_GetGatherInfo(sessionID)
		retParam = SRetParam_GetGatherInfo.new;
		onReturn_GetGatherInfo(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 60;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_GatherEndNotify' #FuncID: 1

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GatherReq' #FuncID: 1
		@retFuncList[1] = '_doReturn_CancelGather' #FuncID: 2
		@retFuncList[2] = '_doReturn_GetGatherInfo' #FuncID: 3

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GatherReq' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_CancelGather' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GetGatherInfo' #FuncID: 3
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

