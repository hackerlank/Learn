#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    LevelPrize.rb
#  Purpose:      等级奖励
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ItemProtBase.rb'
require_relative './WonderActivityProtBase.rb'

#以下为类型定义

#奖励状态信息
class ELevelActStatus
	ELEVLEACTSTATUS_INIT = 0#未完成
	ELEVLEACTSTATUS_FINISH = 1#完成
	ELEVLEACTSTATUS_GETPRIZE = 2#已领取奖励
	ELEVLEACTSTATUS_FULLPACK = 3#背包满
	ELEVLEACTSTATUS_SUCCESS = 4#操作成功
	ELEVLEACTSTATUS_ERROR = 5#操作失败
end

#活动信息
class EActState
	EACTSTATE_INIT = 0#未完成
	EACTSTATE_ONADVANCE = 1#预告
	EACTSTATE_ONBEGIN = 2#开始
	EACTSTATE_ONEND = 3#结束
	EACTSTATE_ONRETAIN = 4#保留
end

#奖励
class SPrize
	attr_accessor:byIndex #(UINT8)第几个奖
	attr_accessor:eState #(枚举类型：ELevelActStatus)第几个奖状态
	attr_accessor:vecItem #(SItemGenInfo的数组)物品

	#构造函数
	def initialize
		@byIndex = 0
		@eState = 0
		@vecItem = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byIndex = @byIndex
		obj.eState = @eState
		obj.vecItem = @vecItem
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPrize.new
		s.byIndex = ByteUtil::readUINT8(data)
		s.eState = ByteUtil::readUINT8(data)
		s.vecItem = SItemGenInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPrize::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byIndex)
		ByteUtil::writeUINT8(data, @eState)
		SItemGenInfo::vectorToStream(data, @vecItem)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#数据操作
class SPrize2DB
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:wActID #(UINT16)活动ID
	attr_accessor:wLevel #(UINT16)奖励NO
	attr_accessor:wStatus #(UINT16)奖励状态

	#构造函数
	def initialize
		@qwRoleID = 0
		@wActID = 0
		@wLevel = 0
		@wStatus = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wActID = @wActID
		obj.wLevel = @wLevel
		obj.wStatus = @wStatus
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPrize2DB.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wActID = ByteUtil::readUINT16(data)
		s.wLevel = ByteUtil::readUINT16(data)
		s.wStatus = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPrize2DB::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wActID)
		ByteUtil::writeUINT16(data, @wLevel)
		ByteUtil::writeUINT16(data, @wStatus)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#活动配置时间
class STime
	attr_accessor:dwAdvTime #(UINT32)活动预告时间
	attr_accessor:dwBeginTime #(UINT32)活动开始时间
	attr_accessor:dwEndTime #(UINT32)活动结束时间
	attr_accessor:dwRetainTime #(UINT32)活动预留时间

	#构造函数
	def initialize
		@dwAdvTime = 0
		@dwBeginTime = 0
		@dwEndTime = 0
		@dwRetainTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwAdvTime = @dwAdvTime
		obj.dwBeginTime = @dwBeginTime
		obj.dwEndTime = @dwEndTime
		obj.dwRetainTime = @dwRetainTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STime.new
		s.dwAdvTime = ByteUtil::readUINT32(data)
		s.dwBeginTime = ByteUtil::readUINT32(data)
		s.dwEndTime = ByteUtil::readUINT32(data)
		s.dwRetainTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STime::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwAdvTime)
		ByteUtil::writeUINT32(data, @dwBeginTime)
		ByteUtil::writeUINT32(data, @dwEndTime)
		ByteUtil::writeUINT32(data, @dwRetainTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#奖励状态
class SPrizeState
	attr_accessor:byIndex #(UINT8)领奖
	attr_accessor:eStatus #(枚举类型：ELevelActStatus)奖励状态

	#构造函数
	def initialize
		@byIndex = 0
		@eStatus = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byIndex = @byIndex
		obj.eStatus = @eStatus
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPrizeState.new
		s.byIndex = ByteUtil::readUINT8(data)
		s.eStatus = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPrizeState::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byIndex)
		ByteUtil::writeUINT8(data, @eStatus)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetPrizeInfo:获取奖励]的返回的参数组成的结构体
class SRetParam_GetPrizeInfo
	attr_accessor:wActID#(UINT16)活动ID
	attr_accessor:vecPrize#(SPrize的数组)结果

	#构造函数
	def initialize
		@wActID = 0
		@vecPrize = Array.new
	end
end

#函数[TakePrize:获取奖励]的返回的参数组成的结构体
class SRetParam_TakePrize
	attr_accessor:wActID#(UINT16)活动Id
	attr_accessor:byIndex#(UINT8)活动Id
	attr_accessor:eRet#(枚举类型：ELevelActStatus)领取结果

	#构造函数
	def initialize
		@wActID = 0
		@byIndex = 0
		@eRet = 0
	end
end

#函数[GetRoleState:玩家在个人服活动中的状态]的返回的参数组成的结构体
class SRetParam_GetRoleState
	attr_accessor:vecRet#(SRoleAllStatus的数组)结果

	#构造函数
	def initialize
		@vecRet = Array.new
	end
end

#函数[TakePrizeForQQAlarm:QQAlarm获取奖励]的返回的参数组成的结构体
class SRetParam_TakePrizeForQQAlarm
	attr_accessor:eRet#(枚举类型：ELevelActStatus)领取结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#协议类：等级奖励
class LevelPrizeBase < ProtocolBase
	#以下为发送函数
	#发送：获取奖励
	def send_GetPrizeInfo(
		wActID #(UINT16)活动Id
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wActID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取奖励
	def send_TakePrize(
		wActID,  #(UINT16)活动Id
		byIndex #(UINT8)第几个奖励
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wActID)
		ByteUtil::writeUINT8(data, byIndex)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家在个人服活动中的状态
	def send_GetRoleState(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：QQAlarm获取奖励
	def send_TakePrizeForQQAlarm(
		wActID #(UINT16)活动Id
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wActID)
		return @svrHandler.sendPacket(data)
	end

	#发送：QQAlarm获取奖励状态
	def send_GetStateForQQAlarm(
		wActID #(UINT16)活动Id
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT16(data, wActID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：等级奖励活动状态通知
	def onRecv_LevelPrizeNotify(
		wActID, #(UINT16)活动Id
		eStatus #(枚举类型：EActState)活动状态
	)
		raise NotImplementedError
	end
	#接收：可领状态通知
	def onRecv_SendReachCondNfy(
		wActID, #(UINT16)活动Id
		byIndex #(UINT8)第几个奖励
	)
		raise NotImplementedError
	end
	#接收：QQAlarm奖励状态通知
	def onRecv_SendStateForQQAlarm(
		wActID, #(UINT16)活动ID
		eRet #(枚举类型：ELevelActStatus)结果
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取奖励
	def onReturn_GetPrizeInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetPrizeInfo)返回的参数
	)
	end

	#返回：获取奖励
	def onReturn_TakePrize(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakePrize)返回的参数
	)
	end

	#返回：玩家在个人服活动中的状态
	def onReturn_GetRoleState(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetRoleState)返回的参数
	)
	end

	#返回：QQAlarm获取奖励
	def onReturn_TakePrizeForQQAlarm(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakePrizeForQQAlarm)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：等级奖励活动状态通知
	def _doRecv_LevelPrizeNotify(data)
		wActID = ByteUtil::readUINT16(data)
		eStatus = ByteUtil::readUINT8(data)
		return onRecv_LevelPrizeNotify(wActID, eStatus)
	end

	#接收处理：可领状态通知
	def _doRecv_SendReachCondNfy(data)
		wActID = ByteUtil::readUINT16(data)
		byIndex = ByteUtil::readUINT8(data)
		return onRecv_SendReachCondNfy(wActID, byIndex)
	end

	#接收处理：QQAlarm奖励状态通知
	def _doRecv_SendStateForQQAlarm(data)
		wActID = ByteUtil::readUINT16(data)
		eRet = ByteUtil::readUINT8(data)
		return onRecv_SendStateForQQAlarm(wActID, eRet)
	end

#以下为返回处理函数
	#返回处理：获取奖励
	def _doReturn_GetPrizeInfo(data)
		retParam = SRetParam_GetPrizeInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		wActID = ByteUtil::readUINT16(data) #(UINT16)活动ID
		vecPrize = SPrize::vectorFromStream(data) #(SPrize的数组)结果
		retParam.wActID = wActID
		retParam.vecPrize = vecPrize
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetPrizeInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取奖励
	def _onTimeOut_GetPrizeInfo(sessionID)
		retParam = SRetParam_GetPrizeInfo.new;
		onReturn_GetPrizeInfo(2, retParam)
	end

	#返回处理：获取奖励
	def _doReturn_TakePrize(data)
		retParam = SRetParam_TakePrize.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		wActID = ByteUtil::readUINT16(data) #(UINT16)活动Id
		byIndex = ByteUtil::readUINT8(data) #(UINT8)活动Id
		eRet = ByteUtil::readUINT8(data) #(枚举类型：ELevelActStatus)领取结果
		retParam.wActID = wActID
		retParam.byIndex = byIndex
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakePrize(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取奖励
	def _onTimeOut_TakePrize(sessionID)
		retParam = SRetParam_TakePrize.new;
		onReturn_TakePrize(2, retParam)
	end

	#返回处理：玩家在个人服活动中的状态
	def _doReturn_GetRoleState(data)
		retParam = SRetParam_GetRoleState.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecRet = SRoleAllStatus::vectorFromStream(data) #(SRoleAllStatus的数组)结果
		retParam.vecRet = vecRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetRoleState(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：玩家在个人服活动中的状态
	def _onTimeOut_GetRoleState(sessionID)
		retParam = SRetParam_GetRoleState.new;
		onReturn_GetRoleState(2, retParam)
	end

	#返回处理：QQAlarm获取奖励
	def _doReturn_TakePrizeForQQAlarm(data)
		retParam = SRetParam_TakePrizeForQQAlarm.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：ELevelActStatus)领取结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakePrizeForQQAlarm(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：QQAlarm获取奖励
	def _onTimeOut_TakePrizeForQQAlarm(sessionID)
		retParam = SRetParam_TakePrizeForQQAlarm.new;
		onReturn_TakePrizeForQQAlarm(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 121;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_LevelPrizeNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_SendReachCondNfy' #FuncID: 2
		@recvFuncList[2] = '_doRecv_SendStateForQQAlarm' #FuncID: 3

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetPrizeInfo' #FuncID: 1
		@retFuncList[1] = '_doReturn_TakePrize' #FuncID: 2
		@retFuncList[2] = '_doReturn_GetRoleState' #FuncID: 3
		@retFuncList[3] = '_doReturn_TakePrizeForQQAlarm' #FuncID: 4

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetPrizeInfo' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_TakePrize' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GetRoleState' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_TakePrizeForQQAlarm' #FuncID: 4
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

