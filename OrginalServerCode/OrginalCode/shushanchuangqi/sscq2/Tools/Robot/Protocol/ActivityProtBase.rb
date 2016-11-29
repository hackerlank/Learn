#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    Activity.rb
#  Purpose:      活力任务协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './RoleInfoDefineBase.rb'

#以下为类型定义

#任务的结果
class EActivityResult
	EACTIVITYSUCCEED = 0#成功
	EACTIVITYMIN = 1#活力度不足
	EACTIVITYTOTALMIN = 2#累计活力值不足
	EACTIVITYPACKNOSPACE = 3#背包不足
	EACTIVITYHASGET = 4#奖励已领取
	EACTIVITYVIP = 5#御剑等级不足
	EACTIVITYERROTHER = 6#其它错误
	EACTIVITYNOTFINISH = 7#任务未完成
end

#成就完成进度
class EShareStatus
	ESHARESTATUS_INIT = 0#未完成
	ESHARESTATUS_FINISH = 1#已完成
	ESHARESTATUS_TAKEPRIZE = 2#已领奖
end

#每日已领活力奖励
class SActivityAward
	attr_accessor:byId #(UINT8)奖励ID
	attr_accessor:byVIP #(UINT8)是否VIP

	#构造函数
	def initialize
		@byId = 0
		@byVIP = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byId = @byId
		obj.byVIP = @byVIP
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SActivityAward.new
		s.byId = ByteUtil::readUINT8(data)
		s.byVIP = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SActivityAward::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byId)
		ByteUtil::writeUINT8(data, @byVIP)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#活力任务信息
class SActivityInfoForClient
	attr_accessor:dwTotolActivity #(UINT32)累计活力值
	attr_accessor:wActivity #(UINT16)当前活力
	attr_accessor:vecActivityTask #(SActivityTaskInfo的数组)活力监测点
	attr_accessor:vecActivityAward #(SActivityAward的数组)已领活力

	#构造函数
	def initialize
		@dwTotolActivity = 0
		@wActivity = 0
		@vecActivityTask = Array.new
		@vecActivityAward = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwTotolActivity = @dwTotolActivity
		obj.wActivity = @wActivity
		obj.vecActivityTask = @vecActivityTask
		obj.vecActivityAward = @vecActivityAward
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SActivityInfoForClient.new
		s.dwTotolActivity = ByteUtil::readUINT32(data)
		s.wActivity = ByteUtil::readUINT16(data)
		s.vecActivityTask = SActivityTaskInfo::vectorFromStream(data)
		s.vecActivityAward = SActivityAward::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SActivityInfoForClient::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwTotolActivity)
		ByteUtil::writeUINT16(data, @wActivity)
		SActivityTaskInfo::vectorToStream(data, @vecActivityTask)
		SActivityAward::vectorToStream(data, @vecActivityAward)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#活力分享列表
class SActivityShare
	attr_accessor:dwActivityID #(UINT32)活跃度ID
	attr_accessor:eStatus #(枚举类型：EShareStatus)分享状态

	#构造函数
	def initialize
		@dwActivityID = 0
		@eStatus = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwActivityID = @dwActivityID
		obj.eStatus = @eStatus
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SActivityShare.new
		s.dwActivityID = ByteUtil::readUINT32(data)
		s.eStatus = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SActivityShare::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwActivityID)
		ByteUtil::writeUINT8(data, @eStatus)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetActivityPool:请求获得奖池]的返回的参数组成的结构体
class SRetParam_GetActivityPool
	attr_accessor:eResult#(枚举类型：EActivityResult)操作结果
	attr_accessor:dwTotolActivity#(UINT32)活力总值

	#构造函数
	def initialize
		@eResult = 0
		@dwTotolActivity = 0
	end
end

#函数[GetActivityAward:请求活力奖励]的返回的参数组成的结构体
class SRetParam_GetActivityAward
	attr_accessor:eResult#(枚举类型：EActivityResult)操作结果
	attr_accessor:stActivityPost#(类类型：SActivityAward)奖励Id

	#构造函数
	def initialize
		@eResult = 0
		@stActivityPost = SActivityAward.new
	end
end

#函数[GeShareList:获取成就分享信息]的返回的参数组成的结构体
class SRetParam_GeShareList
	attr_accessor:vecActivityShare#(SActivityShare的数组)成就分享信息

	#构造函数
	def initialize
		@vecActivityShare = Array.new
	end
end

#函数[TakeSharePrize:获取成就分享奖励]的返回的参数组成的结构体
class SRetParam_TakeSharePrize
	attr_accessor:eRet#(枚举类型：EActivityResult)结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#协议类：活力任务协议
class ActivityProtBase < ProtocolBase
	#以下为发送函数
	#发送：请求获得奖池
	def send_GetActivityPool(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求活力奖励
	def send_GetActivityAward(
		stActivityGet #(类类型：SActivityAward)奖励Id
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		stActivityGet.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取活力任务详情
	def send_GetAllInfoActivity(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取成就分享信息
	def send_GeShareList(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取成就分享奖励
	def send_TakeSharePrize(
		dwActivityID #(UINT32)活跃度ID
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwActivityID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：获取活力任务详情
	def onRecv_ReturnAllInfoActivity(
		stActivityInfo #(类类型：SActivityInfoForClient)活力任务详情
	)
		raise NotImplementedError
	end
	#接收：活力监测点更新
	def onRecv_UpdateActivityTask(
		stActivityTask, #(类类型：RoleInfoDefine::SActivityTaskInfo)活力监测点更新
		dwTotolActivity, #(UINT32)活力总值
		wActivity #(UINT16)今日活力值
	)
		raise NotImplementedError
	end
	#接收：活力总值更新
	def onRecv_UpdateActivityTotal(
		dwTotolActivity #(UINT32)活力总值
	)
		raise NotImplementedError
	end
	#接收：成就分享通知
	def onRecv_ShareNotify(
		oActivityShare #(类类型：SActivityShare)成就分享信息
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：请求获得奖池
	def onReturn_GetActivityPool(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetActivityPool)返回的参数
	)
	end

	#返回：请求活力奖励
	def onReturn_GetActivityAward(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetActivityAward)返回的参数
	)
	end

	#返回：获取成就分享信息
	def onReturn_GeShareList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GeShareList)返回的参数
	)
	end

	#返回：获取成就分享奖励
	def onReturn_TakeSharePrize(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakeSharePrize)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：获取活力任务详情
	def _doRecv_ReturnAllInfoActivity(data)
		stActivityInfo = SActivityInfoForClient::fromStream(data)
		return onRecv_ReturnAllInfoActivity(stActivityInfo)
	end

	#接收处理：活力监测点更新
	def _doRecv_UpdateActivityTask(data)
		stActivityTask = SActivityTaskInfo::fromStream(data)
		dwTotolActivity = ByteUtil::readUINT32(data)
		wActivity = ByteUtil::readUINT16(data)
		return onRecv_UpdateActivityTask(stActivityTask, dwTotolActivity, wActivity)
	end

	#接收处理：活力总值更新
	def _doRecv_UpdateActivityTotal(data)
		dwTotolActivity = ByteUtil::readUINT32(data)
		return onRecv_UpdateActivityTotal(dwTotolActivity)
	end

	#接收处理：成就分享通知
	def _doRecv_ShareNotify(data)
		oActivityShare = SActivityShare::fromStream(data)
		return onRecv_ShareNotify(oActivityShare)
	end

#以下为返回处理函数
	#返回处理：请求获得奖池
	def _doReturn_GetActivityPool(data)
		retParam = SRetParam_GetActivityPool.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EActivityResult)操作结果
		dwTotolActivity = ByteUtil::readUINT32(data) #(UINT32)活力总值
		retParam.eResult = eResult
		retParam.dwTotolActivity = dwTotolActivity
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetActivityPool(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求获得奖池
	def _onTimeOut_GetActivityPool(sessionID)
		retParam = SRetParam_GetActivityPool.new;
		onReturn_GetActivityPool(2, retParam)
	end

	#返回处理：请求活力奖励
	def _doReturn_GetActivityAward(data)
		retParam = SRetParam_GetActivityAward.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EActivityResult)操作结果
		stActivityPost = SActivityAward::fromStream(data) #(类类型：SActivityAward)奖励Id
		retParam.eResult = eResult
		retParam.stActivityPost = stActivityPost
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetActivityAward(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求活力奖励
	def _onTimeOut_GetActivityAward(sessionID)
		retParam = SRetParam_GetActivityAward.new;
		onReturn_GetActivityAward(2, retParam)
	end

	#返回处理：获取成就分享信息
	def _doReturn_GeShareList(data)
		retParam = SRetParam_GeShareList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecActivityShare = SActivityShare::vectorFromStream(data) #(SActivityShare的数组)成就分享信息
		retParam.vecActivityShare = vecActivityShare
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GeShareList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取成就分享信息
	def _onTimeOut_GeShareList(sessionID)
		retParam = SRetParam_GeShareList.new;
		onReturn_GeShareList(2, retParam)
	end

	#返回处理：获取成就分享奖励
	def _doReturn_TakeSharePrize(data)
		retParam = SRetParam_TakeSharePrize.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EActivityResult)结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakeSharePrize(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取成就分享奖励
	def _onTimeOut_TakeSharePrize(sessionID)
		retParam = SRetParam_TakeSharePrize.new;
		onReturn_TakeSharePrize(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 53;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_ReturnAllInfoActivity' #FuncID: 1
		@recvFuncList[1] = '_doRecv_UpdateActivityTask' #FuncID: 2
		@recvFuncList[2] = '_doRecv_UpdateActivityTotal' #FuncID: 3
		@recvFuncList[3] = '_doRecv_ShareNotify' #FuncID: 4

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetActivityPool' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetActivityAward' #FuncID: 2
		@retFuncList[2] = '_doReturn_GeShareList' #FuncID: 3
		@retFuncList[3] = '_doReturn_TakeSharePrize' #FuncID: 4

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetActivityPool' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetActivityAward' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GeShareList' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_TakeSharePrize' #FuncID: 4
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

