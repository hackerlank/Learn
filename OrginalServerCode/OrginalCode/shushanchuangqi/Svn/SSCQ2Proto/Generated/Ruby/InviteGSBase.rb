#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    InviteGS.rb
#  Purpose:      邀请好友相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#好友相关的结果
class EInviteResult
	EINVITE_SUCCESS = 0#成功
	EINVITE_FAILED = 1#失败
	EINVITE_ERRORUSERID = 2#玩家id错误
	EINVITE_ERRORCFGID = 3#配置id错误
	EINVITE_TASKINIT = 4#任务未完成
	EINVITE_TASKTAKEDPRIZE = 5#任务奖励已领取
	EINVITE_SERVERBUSY = 6#任务奖励已领取
end

#邀请任务状态
class EInvitedTask
	EINVITEDTASK_INIT = 0#未完成
	EINVITEDTASK_FINISH = 1#已完成
	EINVITEDTASK_TAKEPRIZED = 2#已领奖
end

#被邀请好友db信息
class SInvitedFriendDB
	attr_accessor:qwUserID #(UINT64)帐号ID
	attr_accessor:qwInviteID #(UINT64)邀请账号ID
	attr_accessor:strName #(string)名字
	attr_accessor:byColor #(UINT8)职业
	attr_accessor:byJob #(UINT8)职业
	attr_accessor:bySex #(UINT8)性别
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:byVIPLevel #(UINT8)VIP等级
	attr_accessor:dwTotalRecharge #(UINT32)总充值

	#构造函数
	def initialize
		@qwUserID = 0
		@qwInviteID = 0
		@strName = ''
		@byColor = 0
		@byJob = 0
		@bySex = 0
		@byLevel = 0
		@byVIPLevel = 0
		@dwTotalRecharge = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwUserID = @qwUserID
		obj.qwInviteID = @qwInviteID
		obj.strName = @strName
		obj.byColor = @byColor
		obj.byJob = @byJob
		obj.bySex = @bySex
		obj.byLevel = @byLevel
		obj.byVIPLevel = @byVIPLevel
		obj.dwTotalRecharge = @dwTotalRecharge
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SInvitedFriendDB.new
		s.qwUserID = ByteUtil::readUINT64(data)
		s.qwInviteID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.byColor = ByteUtil::readUINT8(data)
		s.byJob = ByteUtil::readUINT8(data)
		s.bySex = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.byVIPLevel = ByteUtil::readUINT8(data)
		s.dwTotalRecharge = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SInvitedFriendDB::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeUINT64(data, @qwInviteID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @byColor)
		ByteUtil::writeUINT8(data, @byJob)
		ByteUtil::writeUINT8(data, @bySex)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT8(data, @byVIPLevel)
		ByteUtil::writeUINT32(data, @dwTotalRecharge)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#被邀请好友信息
class SInvitedFriend
	attr_accessor:qwUserID #(UINT64)帐号ID
	attr_accessor:strName #(string)名字
	attr_accessor:byJob #(UINT8)职业
	attr_accessor:bySex #(UINT8)性别
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:byVIPLevel #(UINT8)VIP等级
	attr_accessor:dwTotalRecharge #(UINT32)总充值
	attr_accessor:vecPlatforms #(SPlatformParam的数组)平台信息

	#构造函数
	def initialize
		@qwUserID = 0
		@strName = ''
		@byJob = 0
		@bySex = 0
		@byLevel = 0
		@byVIPLevel = 0
		@dwTotalRecharge = 0
		@vecPlatforms = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwUserID = @qwUserID
		obj.strName = @strName
		obj.byJob = @byJob
		obj.bySex = @bySex
		obj.byLevel = @byLevel
		obj.byVIPLevel = @byVIPLevel
		obj.dwTotalRecharge = @dwTotalRecharge
		obj.vecPlatforms = @vecPlatforms
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SInvitedFriend.new
		s.qwUserID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.byJob = ByteUtil::readUINT8(data)
		s.bySex = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.byVIPLevel = ByteUtil::readUINT8(data)
		s.dwTotalRecharge = ByteUtil::readUINT32(data)
		s.vecPlatforms = SPlatformParam::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SInvitedFriend::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @byJob)
		ByteUtil::writeUINT8(data, @bySex)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT8(data, @byVIPLevel)
		ByteUtil::writeUINT32(data, @dwTotalRecharge)
		SPlatformParam::vectorToStream(data, @vecPlatforms)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#邀请任务状态
class SInvitedTask
	attr_accessor:dwInviteTaskID #(UINT32)任务id
	attr_accessor:wTaskType #(UINT16)任务类型
	attr_accessor:eInvitedTask #(枚举类型：EInvitedTask)任务状态

	#构造函数
	def initialize
		@dwInviteTaskID = 0
		@wTaskType = 0
		@eInvitedTask = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwInviteTaskID = @dwInviteTaskID
		obj.wTaskType = @wTaskType
		obj.eInvitedTask = @eInvitedTask
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SInvitedTask.new
		s.dwInviteTaskID = ByteUtil::readUINT32(data)
		s.wTaskType = ByteUtil::readUINT16(data)
		s.eInvitedTask = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SInvitedTask::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwInviteTaskID)
		ByteUtil::writeUINT16(data, @wTaskType)
		ByteUtil::writeUINT8(data, @eInvitedTask)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetInvitedFriendList:获取被邀请好友列表]的返回的参数组成的结构体
class SRetParam_GetInvitedFriendList
	attr_accessor:vecInvitedFriend#(SInvitedFriend的数组)被邀请好友列表

	#构造函数
	def initialize
		@vecInvitedFriend = Array.new
	end
end

#函数[GetInvitedTaskList:邀请任务列表]的返回的参数组成的结构体
class SRetParam_GetInvitedTaskList
	attr_accessor:vecInvitedTask#(SInvitedTask的数组)邀请任务状态信息

	#构造函数
	def initialize
		@vecInvitedTask = Array.new
	end
end

#函数[GetDayInvitedFriends:每日邀请好友数量]的返回的参数组成的结构体
class SRetParam_GetDayInvitedFriends
	attr_accessor:dwInviteCnt#(UINT32)邀请数量

	#构造函数
	def initialize
		@dwInviteCnt = 0
	end
end

#函数[TakeTaskPrize:领取奖励]的返回的参数组成的结构体
class SRetParam_TakeTaskPrize
	attr_accessor:eRet#(枚举类型：EInviteResult)结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#协议类：邀请好友相关协议
class InviteGSBase < ProtocolBase
	#以下为发送函数
	#发送：获取被邀请好友列表
	def send_GetInvitedFriendList(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：邀请任务列表
	def send_GetInvitedTaskList(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：每日邀请好友数量
	def send_GetDayInvitedFriends(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：领取奖励
	def send_TakeTaskPrize(
		dwPrizeID #(UINT32)领奖任务ID
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwPrizeID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：被邀请好友信息更新
	def onRecv_UpdateInvitedFriend(
		oInvitedFriend #(类类型：SInvitedFriend)查询返回
	)
		raise NotImplementedError
	end
	#接收：被邀请任务信息更新
	def onRecv_UpdateInvitedTask(
		oInvitedTask #(类类型：SInvitedTask)被邀请任务信息
	)
		raise NotImplementedError
	end
	#接收：每日邀请好友数量
	def onRecv_UpdateDayInvitedFriends(
		dwInviteCnt #(UINT32)邀请数量
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取被邀请好友列表
	def onReturn_GetInvitedFriendList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetInvitedFriendList)返回的参数
	)
	end

	#返回：邀请任务列表
	def onReturn_GetInvitedTaskList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetInvitedTaskList)返回的参数
	)
	end

	#返回：每日邀请好友数量
	def onReturn_GetDayInvitedFriends(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetDayInvitedFriends)返回的参数
	)
	end

	#返回：领取奖励
	def onReturn_TakeTaskPrize(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakeTaskPrize)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：被邀请好友信息更新
	def _doRecv_UpdateInvitedFriend(data)
		oInvitedFriend = SInvitedFriend::fromStream(data)
		return onRecv_UpdateInvitedFriend(oInvitedFriend)
	end

	#接收处理：被邀请任务信息更新
	def _doRecv_UpdateInvitedTask(data)
		oInvitedTask = SInvitedTask::fromStream(data)
		return onRecv_UpdateInvitedTask(oInvitedTask)
	end

	#接收处理：每日邀请好友数量
	def _doRecv_UpdateDayInvitedFriends(data)
		dwInviteCnt = ByteUtil::readUINT32(data)
		return onRecv_UpdateDayInvitedFriends(dwInviteCnt)
	end

#以下为返回处理函数
	#返回处理：获取被邀请好友列表
	def _doReturn_GetInvitedFriendList(data)
		retParam = SRetParam_GetInvitedFriendList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecInvitedFriend = SInvitedFriend::vectorFromStream(data) #(SInvitedFriend的数组)被邀请好友列表
		retParam.vecInvitedFriend = vecInvitedFriend
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetInvitedFriendList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取被邀请好友列表
	def _onTimeOut_GetInvitedFriendList(sessionID)
		retParam = SRetParam_GetInvitedFriendList.new;
		onReturn_GetInvitedFriendList(2, retParam)
	end

	#返回处理：邀请任务列表
	def _doReturn_GetInvitedTaskList(data)
		retParam = SRetParam_GetInvitedTaskList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecInvitedTask = SInvitedTask::vectorFromStream(data) #(SInvitedTask的数组)邀请任务状态信息
		retParam.vecInvitedTask = vecInvitedTask
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetInvitedTaskList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：邀请任务列表
	def _onTimeOut_GetInvitedTaskList(sessionID)
		retParam = SRetParam_GetInvitedTaskList.new;
		onReturn_GetInvitedTaskList(2, retParam)
	end

	#返回处理：每日邀请好友数量
	def _doReturn_GetDayInvitedFriends(data)
		retParam = SRetParam_GetDayInvitedFriends.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwInviteCnt = ByteUtil::readUINT32(data) #(UINT32)邀请数量
		retParam.dwInviteCnt = dwInviteCnt
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetDayInvitedFriends(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：每日邀请好友数量
	def _onTimeOut_GetDayInvitedFriends(sessionID)
		retParam = SRetParam_GetDayInvitedFriends.new;
		onReturn_GetDayInvitedFriends(2, retParam)
	end

	#返回处理：领取奖励
	def _doReturn_TakeTaskPrize(data)
		retParam = SRetParam_TakeTaskPrize.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EInviteResult)结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakeTaskPrize(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：领取奖励
	def _onTimeOut_TakeTaskPrize(sessionID)
		retParam = SRetParam_TakeTaskPrize.new;
		onReturn_TakeTaskPrize(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 134;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_UpdateInvitedFriend' #FuncID: 1
		@recvFuncList[1] = '_doRecv_UpdateInvitedTask' #FuncID: 2
		@recvFuncList[2] = '_doRecv_UpdateDayInvitedFriends' #FuncID: 3

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetInvitedFriendList' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetInvitedTaskList' #FuncID: 2
		@retFuncList[2] = '_doReturn_GetDayInvitedFriends' #FuncID: 3
		@retFuncList[3] = '_doReturn_TakeTaskPrize' #FuncID: 4

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetInvitedFriendList' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetInvitedTaskList' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GetDayInvitedFriends' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_TakeTaskPrize' #FuncID: 4
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

