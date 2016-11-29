#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    VIPProt.rb
#  Purpose:      VIP特权相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#VIP特权操作结果
class EVIPResult
	EVIP_SUCCEED = 0#成功
	EVIP_LACKMONEY = 1#金钱不够
	EVIP_HASGETAWARD = 2#已领取过礼包
	EVIP_EXPIRED = 3#VIP特权已过期
	EVIP_UNFRIEND = 4#对方不是你的好友并且不是你的帮派成员
	EVIP_LEVELERR = 5#VIP特权等级不足
	EVIP_OTHERERR = 6#其他错误
end

#开启VIP特权数据结构
class SVIPData
	attr_accessor:dwMonthCardEndTime #(UINT32)月卡结束时间
	attr_accessor:dwDayPack #(UINT32)VIP特权每日礼包领取状态
	attr_accessor:dwLvlAward #(UINT32)VIP特权等级奖励领取状态

	#构造函数
	def initialize
		@dwMonthCardEndTime = 0
		@dwDayPack = 0
		@dwLvlAward = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwMonthCardEndTime = @dwMonthCardEndTime
		obj.dwDayPack = @dwDayPack
		obj.dwLvlAward = @dwLvlAward
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SVIPData.new
		s.dwMonthCardEndTime = ByteUtil::readUINT32(data)
		s.dwDayPack = ByteUtil::readUINT32(data)
		s.dwLvlAward = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SVIPData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwMonthCardEndTime)
		ByteUtil::writeUINT32(data, @dwDayPack)
		ByteUtil::writeUINT32(data, @dwLvlAward)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[OpenSelfVIP:请求个人VIP特权]的返回的参数组成的结构体
class SRetParam_OpenSelfVIP
	attr_accessor:eResult#(枚举类型：EVIPResult)操作结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[OpenOtherVIP:请求开启好友VIP特权]的返回的参数组成的结构体
class SRetParam_OpenOtherVIP
	attr_accessor:eResult#(枚举类型：EVIPResult)操作结果
	attr_accessor:qwRoleID#(UINT64)好友玩家ID

	#构造函数
	def initialize
		@eResult = 0
		@qwRoleID = 0
	end
end

#函数[OpenSelfMonthCard:请求开启个人月卡]的返回的参数组成的结构体
class SRetParam_OpenSelfMonthCard
	attr_accessor:eResult#(枚举类型：EVIPResult)操作结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[OpenOtherMonthCard:请求开启好友月卡]的返回的参数组成的结构体
class SRetParam_OpenOtherMonthCard
	attr_accessor:eResult#(枚举类型：EVIPResult)操作结果
	attr_accessor:qwRoleID#(UINT64)好友玩家ID

	#构造函数
	def initialize
		@eResult = 0
		@qwRoleID = 0
	end
end

#函数[GetDayPackAward:领取VIP特权每日礼包]的返回的参数组成的结构体
class SRetParam_GetDayPackAward
	attr_accessor:eResult#(枚举类型：EVIPResult)操作结果
	attr_accessor:dwDayPack#(UINT32)VIP特权每日礼包领取状态(低15位,按位取)

	#构造函数
	def initialize
		@eResult = 0
		@dwDayPack = 0
	end
end

#函数[GetVIPLevelAward:领取VIP特权等级奖励]的返回的参数组成的结构体
class SRetParam_GetVIPLevelAward
	attr_accessor:eResult#(枚举类型：EVIPResult)操作结果
	attr_accessor:dwLvlAward#(UINT32)VIP等级奖励领取状态(低15位,按位取)

	#构造函数
	def initialize
		@eResult = 0
		@dwLvlAward = 0
	end
end

#协议类：VIP特权相关协议
class VIPProtBase < ProtocolBase
	#以下为发送函数
	#发送：请求个人VIP特权信息
	def send_GetVIPInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求个人VIP特权
	def send_OpenSelfVIP(
		byType #(UINT8)VIP特权类型
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byType)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求开启好友VIP特权
	def send_OpenOtherVIP(
		byType,  #(UINT8)VIP特权类型
		qwRoleID,  #(UINT64)好友玩家ID
		qwRoleID2 #(UINT64)好友玩家ID(匹配验证)
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byType)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT64(data, qwRoleID2)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求开启个人月卡
	def send_OpenSelfMonthCard(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求开启好友月卡
	def send_OpenOtherMonthCard(
		qwRoleID #(UINT64)好友玩家ID
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：领取VIP特权每日礼包
	def send_GetDayPackAward(
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：领取VIP特权等级奖励
	def send_GetVIPLevelAward(
		byLevel #(UINT8)VIP等级
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byLevel)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：个人VIP特权信息
	def onRecv_SelfVIPInfo(
		stVIPData #(类类型：SVIPData)VIP特权信息
	)
		raise NotImplementedError
	end
	#接收：月卡过期通知消息
	def onRecv_UpdateMonthCardOverdue(
		byVal #(UINT8)0未过期 >0已过期
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：请求个人VIP特权
	def onReturn_OpenSelfVIP(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_OpenSelfVIP)返回的参数
	)
	end

	#返回：请求开启好友VIP特权
	def onReturn_OpenOtherVIP(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_OpenOtherVIP)返回的参数
	)
	end

	#返回：请求开启个人月卡
	def onReturn_OpenSelfMonthCard(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_OpenSelfMonthCard)返回的参数
	)
	end

	#返回：请求开启好友月卡
	def onReturn_OpenOtherMonthCard(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_OpenOtherMonthCard)返回的参数
	)
	end

	#返回：领取VIP特权每日礼包
	def onReturn_GetDayPackAward(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetDayPackAward)返回的参数
	)
	end

	#返回：领取VIP特权等级奖励
	def onReturn_GetVIPLevelAward(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetVIPLevelAward)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：个人VIP特权信息
	def _doRecv_SelfVIPInfo(data)
		stVIPData = SVIPData::fromStream(data)
		return onRecv_SelfVIPInfo(stVIPData)
	end

	#接收处理：月卡过期通知消息
	def _doRecv_UpdateMonthCardOverdue(data)
		byVal = ByteUtil::readUINT8(data)
		return onRecv_UpdateMonthCardOverdue(byVal)
	end

#以下为返回处理函数
	#返回处理：请求个人VIP特权
	def _doReturn_OpenSelfVIP(data)
		retParam = SRetParam_OpenSelfVIP.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EVIPResult)操作结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_OpenSelfVIP(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求个人VIP特权
	def _onTimeOut_OpenSelfVIP(sessionID)
		retParam = SRetParam_OpenSelfVIP.new;
		onReturn_OpenSelfVIP(2, retParam)
	end

	#返回处理：请求开启好友VIP特权
	def _doReturn_OpenOtherVIP(data)
		retParam = SRetParam_OpenOtherVIP.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EVIPResult)操作结果
		qwRoleID = ByteUtil::readUINT64(data) #(UINT64)好友玩家ID
		retParam.eResult = eResult
		retParam.qwRoleID = qwRoleID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_OpenOtherVIP(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求开启好友VIP特权
	def _onTimeOut_OpenOtherVIP(sessionID)
		retParam = SRetParam_OpenOtherVIP.new;
		onReturn_OpenOtherVIP(2, retParam)
	end

	#返回处理：请求开启个人月卡
	def _doReturn_OpenSelfMonthCard(data)
		retParam = SRetParam_OpenSelfMonthCard.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EVIPResult)操作结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_OpenSelfMonthCard(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求开启个人月卡
	def _onTimeOut_OpenSelfMonthCard(sessionID)
		retParam = SRetParam_OpenSelfMonthCard.new;
		onReturn_OpenSelfMonthCard(2, retParam)
	end

	#返回处理：请求开启好友月卡
	def _doReturn_OpenOtherMonthCard(data)
		retParam = SRetParam_OpenOtherMonthCard.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EVIPResult)操作结果
		qwRoleID = ByteUtil::readUINT64(data) #(UINT64)好友玩家ID
		retParam.eResult = eResult
		retParam.qwRoleID = qwRoleID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_OpenOtherMonthCard(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求开启好友月卡
	def _onTimeOut_OpenOtherMonthCard(sessionID)
		retParam = SRetParam_OpenOtherMonthCard.new;
		onReturn_OpenOtherMonthCard(2, retParam)
	end

	#返回处理：领取VIP特权每日礼包
	def _doReturn_GetDayPackAward(data)
		retParam = SRetParam_GetDayPackAward.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EVIPResult)操作结果
		dwDayPack = ByteUtil::readUINT32(data) #(UINT32)VIP特权每日礼包领取状态(低15位,按位取)
		retParam.eResult = eResult
		retParam.dwDayPack = dwDayPack
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetDayPackAward(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：领取VIP特权每日礼包
	def _onTimeOut_GetDayPackAward(sessionID)
		retParam = SRetParam_GetDayPackAward.new;
		onReturn_GetDayPackAward(2, retParam)
	end

	#返回处理：领取VIP特权等级奖励
	def _doReturn_GetVIPLevelAward(data)
		retParam = SRetParam_GetVIPLevelAward.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EVIPResult)操作结果
		dwLvlAward = ByteUtil::readUINT32(data) #(UINT32)VIP等级奖励领取状态(低15位,按位取)
		retParam.eResult = eResult
		retParam.dwLvlAward = dwLvlAward
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetVIPLevelAward(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：领取VIP特权等级奖励
	def _onTimeOut_GetVIPLevelAward(sessionID)
		retParam = SRetParam_GetVIPLevelAward.new;
		onReturn_GetVIPLevelAward(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 65;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_SelfVIPInfo' #FuncID: 1
		@recvFuncList[1] = '_doRecv_UpdateMonthCardOverdue' #FuncID: 2

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_OpenSelfVIP' #FuncID: 1
		@retFuncList[1] = '_doReturn_OpenOtherVIP' #FuncID: 2
		@retFuncList[2] = '_doReturn_OpenSelfMonthCard' #FuncID: 3
		@retFuncList[3] = '_doReturn_OpenOtherMonthCard' #FuncID: 4
		@retFuncList[4] = '_doReturn_GetDayPackAward' #FuncID: 5
		@retFuncList[5] = '_doReturn_GetVIPLevelAward' #FuncID: 6

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_OpenSelfVIP' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_OpenOtherVIP' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_OpenSelfMonthCard' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_OpenOtherMonthCard' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_GetDayPackAward' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_GetVIPLevelAward' #FuncID: 6
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

