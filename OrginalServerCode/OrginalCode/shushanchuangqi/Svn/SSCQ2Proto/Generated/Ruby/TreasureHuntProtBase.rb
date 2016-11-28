#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    TreasureHuntProt.rb
#  Purpose:      寻宝协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#操作结果
class ETHOptResult
	ETHOPTRESULTFAILED = 0#失败
	ETHOPTRESULTSUCC = 1#成功
	ETHMAXKILLNUMDAY = 2#今日已达到最大击杀次数
end

#寻宝状态
class ETHStatus
	ETHNONE = 0#无
	ETHPROGRESS = 1#寻宝进行中
	ETHWAITGETAWARD = 2#等待领取奖品
end

#寻宝开始/结束通知
class ETHNotify
	ETHBEGIN = 0#开始
	ETHEND = 1#结束
end

#寻宝日志类型
class ETHLogType
	ETHLOGTYPEA = 0#遇到怪物/BOSS (注：参数：NPCID)
	ETHLOGTYPEB = 1#击败怪物 (注：参数：NPCID)
	ETHLOGTYPEC = 2#获得银币 (注：参数：Silver)
	ETHLOGTYPED = 3#获得修为 (注：参数：Pexp)
	ETHLOGTYPEE = 4#获得宝物 (注：参数：ItemNum)
	ETHLOGTYPEF = 5#击败BOSS,造成XX伤害 (注：参数：BOSSID, HPValue)
	ETHLOGTYPEG = 6#被BOSS击败,查看战报 (注：参数：BOSSID, HPValue, ReportID)
	ETHLOGTYPEH = 7#使用BUFF (注：参数：BUFFID)
	ETHLOGTYPEI = 8#对BOSS,造成XX伤害 (注：参数：BOSSID, HPValue)
	ETHLOGTYPEJ = 9#获得心法残页数量 (注：参数：XFCYNum)
end

#寻宝buff信息
class STHBuffInfo
	attr_accessor:byBuffID #(UINT8)BuffID
	attr_accessor:byBuffNum #(UINT8)今日已使用Buff次数
	attr_accessor:dwBuffCDTime #(UINT32)Buff CD 时间

	#构造函数
	def initialize
		@byBuffID = 0
		@byBuffNum = 0
		@dwBuffCDTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byBuffID = @byBuffID
		obj.byBuffNum = @byBuffNum
		obj.dwBuffCDTime = @dwBuffCDTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STHBuffInfo.new
		s.byBuffID = ByteUtil::readUINT8(data)
		s.byBuffNum = ByteUtil::readUINT8(data)
		s.dwBuffCDTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STHBuffInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byBuffID)
		ByteUtil::writeUINT8(data, @byBuffNum)
		ByteUtil::writeUINT32(data, @dwBuffCDTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战斗结果
class STHBattleResult
	attr_accessor:byCopyID #(UINT8)副本ID
	attr_accessor:dwTotalTimes #(UINT32)寻宝时间
	attr_accessor:dwCurBossHP #(UINT32)当前BOSS血量
	attr_accessor:dwCurSilverNUm #(UINT32)当前掉落银币数量
	attr_accessor:dwCurItemNum #(UINT32)当前掉落物品数量
	attr_accessor:dwCurXFCYNum #(UINT32)当前掉落心法残页数量

	#构造函数
	def initialize
		@byCopyID = 0
		@dwTotalTimes = 0
		@dwCurBossHP = 0
		@dwCurSilverNUm = 0
		@dwCurItemNum = 0
		@dwCurXFCYNum = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byCopyID = @byCopyID
		obj.dwTotalTimes = @dwTotalTimes
		obj.dwCurBossHP = @dwCurBossHP
		obj.dwCurSilverNUm = @dwCurSilverNUm
		obj.dwCurItemNum = @dwCurItemNum
		obj.dwCurXFCYNum = @dwCurXFCYNum
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STHBattleResult.new
		s.byCopyID = ByteUtil::readUINT8(data)
		s.dwTotalTimes = ByteUtil::readUINT32(data)
		s.dwCurBossHP = ByteUtil::readUINT32(data)
		s.dwCurSilverNUm = ByteUtil::readUINT32(data)
		s.dwCurItemNum = ByteUtil::readUINT32(data)
		s.dwCurXFCYNum = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STHBattleResult::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byCopyID)
		ByteUtil::writeUINT32(data, @dwTotalTimes)
		ByteUtil::writeUINT32(data, @dwCurBossHP)
		ByteUtil::writeUINT32(data, @dwCurSilverNUm)
		ByteUtil::writeUINT32(data, @dwCurItemNum)
		ByteUtil::writeUINT32(data, @dwCurXFCYNum)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#寻宝奖励信息
class STHAwardInfo
	attr_accessor:wItemID #(UINT16)物品ID
	attr_accessor:dwCount #(UINT32)堆叠数

	#构造函数
	def initialize
		@wItemID = 0
		@dwCount = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wItemID = @wItemID
		obj.dwCount = @dwCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STHAwardInfo.new
		s.wItemID = ByteUtil::readUINT16(data)
		s.dwCount = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STHAwardInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeUINT32(data, @dwCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#寻宝DB信息
class STHDBInfo
	attr_accessor:qwRoleID #(UINT64)RoleID
	attr_accessor:byCopyID #(UINT8)副本ID
	attr_accessor:byStatus #(UINT8)寻宝状态（1：正在进行；2：结束，等待领取奖品）
	attr_accessor:dwBossCurHP #(UINT32)Boss当前血量
	attr_accessor:dwLastTime #(UINT32)攻打上一波怪时间
	attr_accessor:dwTime #(UINT32)寻宝累计时间
	attr_accessor:dwNum #(UINT32)寻宝累计波数
	attr_accessor:strAward #(string)寻宝奖励

	#构造函数
	def initialize
		@qwRoleID = 0
		@byCopyID = 0
		@byStatus = 0
		@dwBossCurHP = 0
		@dwLastTime = 0
		@dwTime = 0
		@dwNum = 0
		@strAward = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.byCopyID = @byCopyID
		obj.byStatus = @byStatus
		obj.dwBossCurHP = @dwBossCurHP
		obj.dwLastTime = @dwLastTime
		obj.dwTime = @dwTime
		obj.dwNum = @dwNum
		obj.strAward = @strAward
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STHDBInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.byCopyID = ByteUtil::readUINT8(data)
		s.byStatus = ByteUtil::readUINT8(data)
		s.dwBossCurHP = ByteUtil::readUINT32(data)
		s.dwLastTime = ByteUtil::readUINT32(data)
		s.dwTime = ByteUtil::readUINT32(data)
		s.dwNum = ByteUtil::readUINT32(data)
		s.strAward = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STHDBInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT8(data, @byCopyID)
		ByteUtil::writeUINT8(data, @byStatus)
		ByteUtil::writeUINT32(data, @dwBossCurHP)
		ByteUtil::writeUINT32(data, @dwLastTime)
		ByteUtil::writeUINT32(data, @dwTime)
		ByteUtil::writeUINT32(data, @dwNum)
		ByteUtil::writeSTRING(data, @strAward)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[ReqTHInfo:请求寻宝信息]的返回的参数组成的结构体
class SRetParam_ReqTHInfo
	attr_accessor:byCopyID#(UINT8)0:没有副本进行中；非0:正在进行该副本
	attr_accessor:eTHStatus#(枚举类型：ETHStatus)寻宝状态
	attr_accessor:byKillNum#(UINT8)剩余击杀次数
	attr_accessor:byCurrentID#(UINT8)当前通关到副本ID

	#构造函数
	def initialize
		@byCopyID = 0
		@eTHStatus = 0
		@byKillNum = 0
		@byCurrentID = 0
	end
end

#函数[ReqTHBattlePrepareInfo:请求寻宝准备战斗信息(注：离线寻宝，重新登录游戏时请求此消息)]的返回的参数组成的结构体
class SRetParam_ReqTHBattlePrepareInfo
	attr_accessor:byKillNum#(UINT8)剩余击杀次数
	attr_accessor:dwCurBossHP#(UINT32)当前BOSS血量
	attr_accessor:dwTotalTimes#(UINT32)寻宝时间
	attr_accessor:vecTHAwardInfo#(STHAwardInfo的数组)寻宝奖励信息
	attr_accessor:vecTHBuffInfo#(STHBuffInfo的数组)Buff信息

	#构造函数
	def initialize
		@byKillNum = 0
		@dwCurBossHP = 0
		@dwTotalTimes = 0
		@vecTHAwardInfo = Array.new
		@vecTHBuffInfo = Array.new
	end
end

#函数[ReqTHStart:请求寻宝开始]的返回的参数组成的结构体
class SRetParam_ReqTHStart
	attr_accessor:eTHOptResult#(枚举类型：ETHOptResult)操作结果

	#构造函数
	def initialize
		@eTHOptResult = 0
	end
end

#函数[ReqTHQuickFinish:请求寻宝立即完成]的返回的参数组成的结构体
class SRetParam_ReqTHQuickFinish
	attr_accessor:eTHOptResult#(枚举类型：ETHOptResult)操作结果

	#构造函数
	def initialize
		@eTHOptResult = 0
	end
end

#函数[ReqTHGiveUp:请求放弃寻宝]的返回的参数组成的结构体
class SRetParam_ReqTHGiveUp
	attr_accessor:eTHOptResult#(枚举类型：ETHOptResult)操作结果

	#构造函数
	def initialize
		@eTHOptResult = 0
	end
end

#函数[ReqUseBuff:请求使用Buff]的返回的参数组成的结构体
class SRetParam_ReqUseBuff
	attr_accessor:eTHOptResult#(枚举类型：ETHOptResult)操作结果

	#构造函数
	def initialize
		@eTHOptResult = 0
	end
end

#函数[ReqTHAwardInfo:请求寻宝奖励信息]的返回的参数组成的结构体
class SRetParam_ReqTHAwardInfo
	attr_accessor:byCopyID#(UINT8)副本ID
	attr_accessor:vecTHAwardInfo#(STHAwardInfo的数组)寻宝奖励信息

	#构造函数
	def initialize
		@byCopyID = 0
		@vecTHAwardInfo = Array.new
	end
end

#函数[GetTHAward:获取寻宝奖励]的返回的参数组成的结构体
class SRetParam_GetTHAward
	attr_accessor:eTHOptResult#(枚举类型：ETHOptResult)操作结果

	#构造函数
	def initialize
		@eTHOptResult = 0
	end
end

#协议类：寻宝协议
class TreasureHuntProtBase < ProtocolBase
	#以下为发送函数
	#发送：请求寻宝信息
	def send_ReqTHInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求寻宝准备战斗信息(注：离线寻宝，重新登录游戏时请求此消息)
	def send_ReqTHBattlePrepareInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求寻宝开始
	def send_ReqTHStart(
		byCopyID #(UINT8)副本ID
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byCopyID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求寻宝立即完成
	def send_ReqTHQuickFinish(
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求放弃寻宝
	def send_ReqTHGiveUp(
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求使用Buff
	def send_ReqUseBuff(
		byBuffID #(UINT8)BuffID
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byBuffID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求寻宝奖励信息
	def send_ReqTHAwardInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取寻宝奖励
	def send_GetTHAward(
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：寻宝开始/结束通知
	def onRecv_THNotify(
		eTHNotify, #(枚举类型：ETHNotify)开始/结束
		byKillNum, #(UINT8)今日已击杀BOSS次数
		vecTHBuffInfo #(STHBuffInfo的数组)Buff信息
	)
		raise NotImplementedError
	end
	#接收：战斗结果通知
	def onRecv_THBattleResultNotify(
		sBattleResult #(类类型：STHBattleResult)战斗结果
	)
		raise NotImplementedError
	end
	#接收：寻宝掉落通知
	def onRecv_THLootNotify(
		vecTHAwardInfo #(STHAwardInfo的数组)掉落
	)
		raise NotImplementedError
	end
	#接收：日志通知
	def onRecv_THLogNotify(
		eTHLogType, #(枚举类型：ETHLogType)寻宝日志类型
		dwParamA, #(UINT32)参数A
		dwParamB, #(UINT32)参数B(注：只对eTHLogTypeF\eTHLogTypeG类型有用,其他类型默认为0)
		dwParamC #(UINT64)参数C(注：只对eTHLogTypeG类型有用,其他类型默认为0)
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：请求寻宝信息
	def onReturn_ReqTHInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqTHInfo)返回的参数
	)
	end

	#返回：请求寻宝准备战斗信息(注：离线寻宝，重新登录游戏时请求此消息)
	def onReturn_ReqTHBattlePrepareInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqTHBattlePrepareInfo)返回的参数
	)
	end

	#返回：请求寻宝开始
	def onReturn_ReqTHStart(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqTHStart)返回的参数
	)
	end

	#返回：请求寻宝立即完成
	def onReturn_ReqTHQuickFinish(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqTHQuickFinish)返回的参数
	)
	end

	#返回：请求放弃寻宝
	def onReturn_ReqTHGiveUp(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqTHGiveUp)返回的参数
	)
	end

	#返回：请求使用Buff
	def onReturn_ReqUseBuff(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqUseBuff)返回的参数
	)
	end

	#返回：请求寻宝奖励信息
	def onReturn_ReqTHAwardInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqTHAwardInfo)返回的参数
	)
	end

	#返回：获取寻宝奖励
	def onReturn_GetTHAward(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetTHAward)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：寻宝开始/结束通知
	def _doRecv_THNotify(data)
		eTHNotify = ByteUtil::readINT8(data)
		byKillNum = ByteUtil::readUINT8(data)
		vecTHBuffInfo = STHBuffInfo::vectorFromStream(data)
		return onRecv_THNotify(eTHNotify, byKillNum, vecTHBuffInfo)
	end

	#接收处理：战斗结果通知
	def _doRecv_THBattleResultNotify(data)
		sBattleResult = STHBattleResult::fromStream(data)
		return onRecv_THBattleResultNotify(sBattleResult)
	end

	#接收处理：寻宝掉落通知
	def _doRecv_THLootNotify(data)
		vecTHAwardInfo = STHAwardInfo::vectorFromStream(data)
		return onRecv_THLootNotify(vecTHAwardInfo)
	end

	#接收处理：日志通知
	def _doRecv_THLogNotify(data)
		eTHLogType = ByteUtil::readINT8(data)
		dwParamA = ByteUtil::readUINT32(data)
		dwParamB = ByteUtil::readUINT32(data)
		dwParamC = ByteUtil::readUINT64(data)
		return onRecv_THLogNotify(eTHLogType, dwParamA, dwParamB, dwParamC)
	end

#以下为返回处理函数
	#返回处理：请求寻宝信息
	def _doReturn_ReqTHInfo(data)
		retParam = SRetParam_ReqTHInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byCopyID = ByteUtil::readUINT8(data) #(UINT8)0:没有副本进行中；非0:正在进行该副本
		eTHStatus = ByteUtil::readINT8(data) #(枚举类型：ETHStatus)寻宝状态
		byKillNum = ByteUtil::readUINT8(data) #(UINT8)剩余击杀次数
		byCurrentID = ByteUtil::readUINT8(data) #(UINT8)当前通关到副本ID
		retParam.byCopyID = byCopyID
		retParam.eTHStatus = eTHStatus
		retParam.byKillNum = byKillNum
		retParam.byCurrentID = byCurrentID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqTHInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求寻宝信息
	def _onTimeOut_ReqTHInfo(sessionID)
		retParam = SRetParam_ReqTHInfo.new;
		onReturn_ReqTHInfo(2, retParam)
	end

	#返回处理：请求寻宝准备战斗信息(注：离线寻宝，重新登录游戏时请求此消息)
	def _doReturn_ReqTHBattlePrepareInfo(data)
		retParam = SRetParam_ReqTHBattlePrepareInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byKillNum = ByteUtil::readUINT8(data) #(UINT8)剩余击杀次数
		dwCurBossHP = ByteUtil::readUINT32(data) #(UINT32)当前BOSS血量
		dwTotalTimes = ByteUtil::readUINT32(data) #(UINT32)寻宝时间
		vecTHAwardInfo = STHAwardInfo::vectorFromStream(data) #(STHAwardInfo的数组)寻宝奖励信息
		vecTHBuffInfo = STHBuffInfo::vectorFromStream(data) #(STHBuffInfo的数组)Buff信息
		retParam.byKillNum = byKillNum
		retParam.dwCurBossHP = dwCurBossHP
		retParam.dwTotalTimes = dwTotalTimes
		retParam.vecTHAwardInfo = vecTHAwardInfo
		retParam.vecTHBuffInfo = vecTHBuffInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqTHBattlePrepareInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求寻宝准备战斗信息(注：离线寻宝，重新登录游戏时请求此消息)
	def _onTimeOut_ReqTHBattlePrepareInfo(sessionID)
		retParam = SRetParam_ReqTHBattlePrepareInfo.new;
		onReturn_ReqTHBattlePrepareInfo(2, retParam)
	end

	#返回处理：请求寻宝开始
	def _doReturn_ReqTHStart(data)
		retParam = SRetParam_ReqTHStart.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eTHOptResult = ByteUtil::readINT8(data) #(枚举类型：ETHOptResult)操作结果
		retParam.eTHOptResult = eTHOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqTHStart(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求寻宝开始
	def _onTimeOut_ReqTHStart(sessionID)
		retParam = SRetParam_ReqTHStart.new;
		onReturn_ReqTHStart(2, retParam)
	end

	#返回处理：请求寻宝立即完成
	def _doReturn_ReqTHQuickFinish(data)
		retParam = SRetParam_ReqTHQuickFinish.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eTHOptResult = ByteUtil::readINT8(data) #(枚举类型：ETHOptResult)操作结果
		retParam.eTHOptResult = eTHOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqTHQuickFinish(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求寻宝立即完成
	def _onTimeOut_ReqTHQuickFinish(sessionID)
		retParam = SRetParam_ReqTHQuickFinish.new;
		onReturn_ReqTHQuickFinish(2, retParam)
	end

	#返回处理：请求放弃寻宝
	def _doReturn_ReqTHGiveUp(data)
		retParam = SRetParam_ReqTHGiveUp.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eTHOptResult = ByteUtil::readINT8(data) #(枚举类型：ETHOptResult)操作结果
		retParam.eTHOptResult = eTHOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqTHGiveUp(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求放弃寻宝
	def _onTimeOut_ReqTHGiveUp(sessionID)
		retParam = SRetParam_ReqTHGiveUp.new;
		onReturn_ReqTHGiveUp(2, retParam)
	end

	#返回处理：请求使用Buff
	def _doReturn_ReqUseBuff(data)
		retParam = SRetParam_ReqUseBuff.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eTHOptResult = ByteUtil::readINT8(data) #(枚举类型：ETHOptResult)操作结果
		retParam.eTHOptResult = eTHOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqUseBuff(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求使用Buff
	def _onTimeOut_ReqUseBuff(sessionID)
		retParam = SRetParam_ReqUseBuff.new;
		onReturn_ReqUseBuff(2, retParam)
	end

	#返回处理：请求寻宝奖励信息
	def _doReturn_ReqTHAwardInfo(data)
		retParam = SRetParam_ReqTHAwardInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byCopyID = ByteUtil::readUINT8(data) #(UINT8)副本ID
		vecTHAwardInfo = STHAwardInfo::vectorFromStream(data) #(STHAwardInfo的数组)寻宝奖励信息
		retParam.byCopyID = byCopyID
		retParam.vecTHAwardInfo = vecTHAwardInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqTHAwardInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求寻宝奖励信息
	def _onTimeOut_ReqTHAwardInfo(sessionID)
		retParam = SRetParam_ReqTHAwardInfo.new;
		onReturn_ReqTHAwardInfo(2, retParam)
	end

	#返回处理：获取寻宝奖励
	def _doReturn_GetTHAward(data)
		retParam = SRetParam_GetTHAward.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eTHOptResult = ByteUtil::readINT8(data) #(枚举类型：ETHOptResult)操作结果
		retParam.eTHOptResult = eTHOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetTHAward(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取寻宝奖励
	def _onTimeOut_GetTHAward(sessionID)
		retParam = SRetParam_GetTHAward.new;
		onReturn_GetTHAward(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 85;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_THNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_THBattleResultNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_THLootNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_THLogNotify' #FuncID: 4

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_ReqTHInfo' #FuncID: 1
		@retFuncList[1] = '_doReturn_ReqTHBattlePrepareInfo' #FuncID: 2
		@retFuncList[2] = '_doReturn_ReqTHStart' #FuncID: 3
		@retFuncList[3] = '_doReturn_ReqTHQuickFinish' #FuncID: 4
		@retFuncList[4] = '_doReturn_ReqTHGiveUp' #FuncID: 5
		@retFuncList[5] = '_doReturn_ReqUseBuff' #FuncID: 6
		@retFuncList[6] = '_doReturn_ReqTHAwardInfo' #FuncID: 7
		@retFuncList[7] = '_doReturn_GetTHAward' #FuncID: 8

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_ReqTHInfo' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_ReqTHBattlePrepareInfo' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_ReqTHStart' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_ReqTHQuickFinish' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_ReqTHGiveUp' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_ReqUseBuff' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_ReqTHAwardInfo' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_GetTHAward' #FuncID: 8
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

