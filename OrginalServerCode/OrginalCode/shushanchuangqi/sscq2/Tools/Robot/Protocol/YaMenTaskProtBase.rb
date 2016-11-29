#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    YaMenTaskProt.rb
#  Purpose:      衙门任务协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#任务的结果
class EYaMenTaskResult
	EYAMENTASKSUCCEED = 0#成功
	EYAMENTASKLOWMONEY = 1#钱不足
	EBUYTIMESUPLIMIT = 2#购买次数已达上限
	EYAMENSAVETIMESUPLIMIT = 3#总次数已达上限
	EYAMENAWARDPACKFULL = 4#包裹满
	EYAMENTASKERROTHER = 5#其它错误
end

#清修的状态
class EYaMenStudyState
	ECANSTUDY = 0#可清修
	ESTUDIED = 1#已清修
	ECANCHALLENGE = 2#可挑战
	ECHALLENGING = 3#正挑战
end

#推任务的状态
class EYaMenTaskState
	ENONE = 0#未接
	EACCEPT = 1#已接
	EFINISH = 2#已完成
	EFAL = 3#已失败
end

#挑战的任务状态
class SYaMenTask
	attr_accessor:dwTaskId #(UINT32)任务的ID
	attr_accessor:eYaMenTaskState #(枚举类型：EYaMenTaskState)当前刷的任务信息

	#构造函数
	def initialize
		@dwTaskId = 0
		@eYaMenTaskState = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwTaskId = @dwTaskId
		obj.eYaMenTaskState = @eYaMenTaskState
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SYaMenTask.new
		s.dwTaskId = ByteUtil::readUINT32(data)
		s.eYaMenTaskState = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SYaMenTask::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwTaskId)
		ByteUtil::writeUINT8(data, @eYaMenTaskState)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#衙门任务信息
class SYaMenTaskInfoForClient
	attr_accessor:eStudyState #(枚举类型：EYaMenStudyState)清修状态
	attr_accessor:dwYaMenRepute #(UINT32)声望
	attr_accessor:dwYaMenLevel #(UINT8)声望等级
	attr_accessor:byFinishTask #(UINT8)今日完成的衙门任务数
	attr_accessor:byAcceptTaskTimes #(UINT8)剩余可接任务数
	attr_accessor:byBuyTimesToday #(UINT8)今日购买的任务数
	attr_accessor:byVIPTaskTimes #(UINT8)购买的可接任务数
	attr_accessor:byFlushTask #(UINT8)今日刷新任务列表次数
	attr_accessor:byStudyAward #(UINT8)今日领取的清修次数
	attr_accessor:vecTask #(SYaMenTask的数组)推的任务列表

	#构造函数
	def initialize
		@eStudyState = 0
		@dwYaMenRepute = 0
		@dwYaMenLevel = 0
		@byFinishTask = 0
		@byAcceptTaskTimes = 0
		@byBuyTimesToday = 0
		@byVIPTaskTimes = 0
		@byFlushTask = 0
		@byStudyAward = 0
		@vecTask = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eStudyState = @eStudyState
		obj.dwYaMenRepute = @dwYaMenRepute
		obj.dwYaMenLevel = @dwYaMenLevel
		obj.byFinishTask = @byFinishTask
		obj.byAcceptTaskTimes = @byAcceptTaskTimes
		obj.byBuyTimesToday = @byBuyTimesToday
		obj.byVIPTaskTimes = @byVIPTaskTimes
		obj.byFlushTask = @byFlushTask
		obj.byStudyAward = @byStudyAward
		obj.vecTask = @vecTask
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SYaMenTaskInfoForClient.new
		s.eStudyState = ByteUtil::readUINT8(data)
		s.dwYaMenRepute = ByteUtil::readUINT32(data)
		s.dwYaMenLevel = ByteUtil::readUINT8(data)
		s.byFinishTask = ByteUtil::readUINT8(data)
		s.byAcceptTaskTimes = ByteUtil::readUINT8(data)
		s.byBuyTimesToday = ByteUtil::readUINT8(data)
		s.byVIPTaskTimes = ByteUtil::readUINT8(data)
		s.byFlushTask = ByteUtil::readUINT8(data)
		s.byStudyAward = ByteUtil::readUINT8(data)
		s.vecTask = SYaMenTask::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SYaMenTaskInfoForClient::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eStudyState)
		ByteUtil::writeUINT32(data, @dwYaMenRepute)
		ByteUtil::writeUINT8(data, @dwYaMenLevel)
		ByteUtil::writeUINT8(data, @byFinishTask)
		ByteUtil::writeUINT8(data, @byAcceptTaskTimes)
		ByteUtil::writeUINT8(data, @byBuyTimesToday)
		ByteUtil::writeUINT8(data, @byVIPTaskTimes)
		ByteUtil::writeUINT8(data, @byFlushTask)
		ByteUtil::writeUINT8(data, @byStudyAward)
		SYaMenTask::vectorToStream(data, @vecTask)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[YaMenTaskOp:请求操作]的返回的参数组成的结构体
class SRetParam_YaMenTaskOp
	attr_accessor:eResult#(枚举类型：EYaMenTaskResult)操作结果
	attr_accessor:eState#(枚举类型：EYaMenStudyState)当前清修状态

	#构造函数
	def initialize
		@eResult = 0
		@eState = 0
	end
end

#函数[FlushTask:刷新衙门任务列表]的返回的参数组成的结构体
class SRetParam_FlushTask
	attr_accessor:eResult#(枚举类型：EYaMenTaskResult)操作结果
	attr_accessor:vecTask#(SYaMenTask的数组)推的任务列表
	attr_accessor:byFlushTask#(UINT8)今日刷新任务列表次数

	#构造函数
	def initialize
		@eResult = 0
		@vecTask = Array.new
		@byFlushTask = 0
	end
end

#函数[BuyTaskTimes:购买衙门任务]的返回的参数组成的结构体
class SRetParam_BuyTaskTimes
	attr_accessor:eResult#(枚举类型：EYaMenTaskResult)操作结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：衙门任务协议
class YaMenTaskProtBase < ProtocolBase
	#以下为发送函数
	#发送：请求操作
	def send_YaMenTaskOp(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：刷新衙门任务列表
	def send_FlushTask(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取衙门任务详情
	def send_GetAllInfoTask(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：购买衙门任务
	def send_BuyTaskTimes(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：获取衙门任务详情
	def onRecv_ReturnAllInfoTask(
		stYaMenTaskInfo #(类类型：SYaMenTaskInfoForClient)衙门任务详情
	)
		raise NotImplementedError
	end
	#接收：任务列表更新
	def onRecv_UpdateYaMenTask(
		stTask #(类类型：SYaMenTask)衙门任务详情
	)
		raise NotImplementedError
	end
	#接收：完成任务数更新
	def onRecv_UpdateFinishTask(
		byFinishTask, #(UINT8)今日完成的衙门任务数
		byAcceptTaskTimes, #(UINT8)剩余可接任务数
		byVIPTaskTimes, #(UINT8)购买的可接任务数
		byBuyTimesToday #(UINT8)今日购买的任务数
	)
		raise NotImplementedError
	end
	#接收：更新清修状态
	def onRecv_UpdateStudyState(
		eStudyState #(枚举类型：EYaMenStudyState)清修状态
	)
		raise NotImplementedError
	end
	#接收：更新声望等级
	def onRecv_UpdateYaMenReputeLevel(
		dwYaMenLevel #(UINT8)声望等级
	)
		raise NotImplementedError
	end
	#接收：更新声望
	def onRecv_UpdateYaMenRepute(
		dwYaMenRepute #(UINT32)声望
	)
		raise NotImplementedError
	end
	#接收：更新今日清修领奖次数
	def onRecv_UpdateStudyAward(
		byStudyAward #(UINT8)今日领取的清修次数
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：请求操作
	def onReturn_YaMenTaskOp(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_YaMenTaskOp)返回的参数
	)
	end

	#返回：刷新衙门任务列表
	def onReturn_FlushTask(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FlushTask)返回的参数
	)
	end

	#返回：购买衙门任务
	def onReturn_BuyTaskTimes(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuyTaskTimes)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：获取衙门任务详情
	def _doRecv_ReturnAllInfoTask(data)
		stYaMenTaskInfo = SYaMenTaskInfoForClient::fromStream(data)
		return onRecv_ReturnAllInfoTask(stYaMenTaskInfo)
	end

	#接收处理：任务列表更新
	def _doRecv_UpdateYaMenTask(data)
		stTask = SYaMenTask::fromStream(data)
		return onRecv_UpdateYaMenTask(stTask)
	end

	#接收处理：完成任务数更新
	def _doRecv_UpdateFinishTask(data)
		byFinishTask = ByteUtil::readUINT8(data)
		byAcceptTaskTimes = ByteUtil::readUINT8(data)
		byVIPTaskTimes = ByteUtil::readUINT8(data)
		byBuyTimesToday = ByteUtil::readUINT8(data)
		return onRecv_UpdateFinishTask(byFinishTask, byAcceptTaskTimes, byVIPTaskTimes, byBuyTimesToday)
	end

	#接收处理：更新清修状态
	def _doRecv_UpdateStudyState(data)
		eStudyState = ByteUtil::readUINT8(data)
		return onRecv_UpdateStudyState(eStudyState)
	end

	#接收处理：更新声望等级
	def _doRecv_UpdateYaMenReputeLevel(data)
		dwYaMenLevel = ByteUtil::readUINT8(data)
		return onRecv_UpdateYaMenReputeLevel(dwYaMenLevel)
	end

	#接收处理：更新声望
	def _doRecv_UpdateYaMenRepute(data)
		dwYaMenRepute = ByteUtil::readUINT32(data)
		return onRecv_UpdateYaMenRepute(dwYaMenRepute)
	end

	#接收处理：更新今日清修领奖次数
	def _doRecv_UpdateStudyAward(data)
		byStudyAward = ByteUtil::readUINT8(data)
		return onRecv_UpdateStudyAward(byStudyAward)
	end

#以下为返回处理函数
	#返回处理：请求操作
	def _doReturn_YaMenTaskOp(data)
		retParam = SRetParam_YaMenTaskOp.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EYaMenTaskResult)操作结果
		eState = ByteUtil::readUINT8(data) #(枚举类型：EYaMenStudyState)当前清修状态
		retParam.eResult = eResult
		retParam.eState = eState
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_YaMenTaskOp(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求操作
	def _onTimeOut_YaMenTaskOp(sessionID)
		retParam = SRetParam_YaMenTaskOp.new;
		onReturn_YaMenTaskOp(2, retParam)
	end

	#返回处理：刷新衙门任务列表
	def _doReturn_FlushTask(data)
		retParam = SRetParam_FlushTask.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EYaMenTaskResult)操作结果
		vecTask = SYaMenTask::vectorFromStream(data) #(SYaMenTask的数组)推的任务列表
		byFlushTask = ByteUtil::readUINT8(data) #(UINT8)今日刷新任务列表次数
		retParam.eResult = eResult
		retParam.vecTask = vecTask
		retParam.byFlushTask = byFlushTask
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FlushTask(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：刷新衙门任务列表
	def _onTimeOut_FlushTask(sessionID)
		retParam = SRetParam_FlushTask.new;
		onReturn_FlushTask(2, retParam)
	end

	#返回处理：购买衙门任务
	def _doReturn_BuyTaskTimes(data)
		retParam = SRetParam_BuyTaskTimes.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EYaMenTaskResult)操作结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuyTaskTimes(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：购买衙门任务
	def _onTimeOut_BuyTaskTimes(sessionID)
		retParam = SRetParam_BuyTaskTimes.new;
		onReturn_BuyTaskTimes(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 52;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_ReturnAllInfoTask' #FuncID: 1
		@recvFuncList[1] = '_doRecv_UpdateYaMenTask' #FuncID: 2
		@recvFuncList[2] = '_doRecv_UpdateFinishTask' #FuncID: 3
		@recvFuncList[3] = '_doRecv_UpdateStudyState' #FuncID: 4
		@recvFuncList[4] = '_doRecv_UpdateYaMenReputeLevel' #FuncID: 5
		@recvFuncList[5] = '_doRecv_UpdateYaMenRepute' #FuncID: 6
		@recvFuncList[6] = '_doRecv_UpdateStudyAward' #FuncID: 7

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_YaMenTaskOp' #FuncID: 1
		@retFuncList[1] = '_doReturn_FlushTask' #FuncID: 2
		@retFuncList[2] = '_doReturn_BuyTaskTimes' #FuncID: 3

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_YaMenTaskOp' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_FlushTask' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_BuyTaskTimes' #FuncID: 3
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

