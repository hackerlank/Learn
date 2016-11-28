#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    DayTarget.rb
#  Purpose:      七日目标活动
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#错误码
class EDayTargetRet
	EDAYTARGETRET_SUCESS = 0#成功
	EDAYTARGETRET_NOTFINISH = 1#任务未完成
	EDAYTARGETRET_DAYLIMIT = 2#未到领奖天数
	EDAYTARGETRET_TAKEPRIZED = 3#已经领过奖励
	EDAYTARGETRET_CFGERROR = 4#基础配置错误
	EDAYTARGETRET_PACKFULL = 5#背包空间不足
end

#任务状态
class EDayTargeTasktStatus
	EDAYTARGETTASKSTATUS_INIT = 0#任务未完成
	EDAYTARGETTASKSTATUS_FINISH = 1#任务完成
	EDAYTARGETTASKSTATUS_TAKEPRIZED = 2#任务已领奖
end

#任务信息列表
class SDayTargetTask
	attr_accessor:wTaskID #(UINT16)任务ID
	attr_accessor:eTaskStatus #(枚举类型：EDayTargeTasktStatus)任务状态
	attr_accessor:dwParam #(UINT32)进度

	#构造函数
	def initialize
		@wTaskID = 0
		@eTaskStatus = 0
		@dwParam = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wTaskID = @wTaskID
		obj.eTaskStatus = @eTaskStatus
		obj.dwParam = @dwParam
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDayTargetTask.new
		s.wTaskID = ByteUtil::readUINT16(data)
		s.eTaskStatus = ByteUtil::readUINT8(data)
		s.dwParam = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDayTargetTask::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wTaskID)
		ByteUtil::writeUINT8(data, @eTaskStatus)
		ByteUtil::writeUINT32(data, @dwParam)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetTaskList:获取任务列表]的返回的参数组成的结构体
class SRetParam_GetTaskList
	attr_accessor:vecDayTargetTask#(SDayTargetTask的数组)任务列表

	#构造函数
	def initialize
		@vecDayTargetTask = Array.new
	end
end

#函数[TakePrize:领取奖励]的返回的参数组成的结构体
class SRetParam_TakePrize
	attr_accessor:eRet#(枚举类型：EDayTargetRet)领奖结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#协议类：七日目标活动
class DayTargetBase < ProtocolBase
	#以下为发送函数
	#发送：获取任务列表
	def send_GetTaskList(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：领取奖励
	def send_TakePrize(
		wTaskID #(UINT16)任务ID
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wTaskID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：任务信息更新
	def onRecv_UpdateTaskList(
		oDayTargetTask #(类类型：SDayTargetTask)任务信息
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取任务列表
	def onReturn_GetTaskList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetTaskList)返回的参数
	)
	end

	#返回：领取奖励
	def onReturn_TakePrize(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakePrize)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：任务信息更新
	def _doRecv_UpdateTaskList(data)
		oDayTargetTask = SDayTargetTask::fromStream(data)
		return onRecv_UpdateTaskList(oDayTargetTask)
	end

#以下为返回处理函数
	#返回处理：获取任务列表
	def _doReturn_GetTaskList(data)
		retParam = SRetParam_GetTaskList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecDayTargetTask = SDayTargetTask::vectorFromStream(data) #(SDayTargetTask的数组)任务列表
		retParam.vecDayTargetTask = vecDayTargetTask
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetTaskList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取任务列表
	def _onTimeOut_GetTaskList(sessionID)
		retParam = SRetParam_GetTaskList.new;
		onReturn_GetTaskList(2, retParam)
	end

	#返回处理：领取奖励
	def _doReturn_TakePrize(data)
		retParam = SRetParam_TakePrize.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EDayTargetRet)领奖结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakePrize(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：领取奖励
	def _onTimeOut_TakePrize(sessionID)
		retParam = SRetParam_TakePrize.new;
		onReturn_TakePrize(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 125;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_UpdateTaskList' #FuncID: 1

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetTaskList' #FuncID: 1
		@retFuncList[1] = '_doReturn_TakePrize' #FuncID: 2

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetTaskList' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_TakePrize' #FuncID: 2
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

