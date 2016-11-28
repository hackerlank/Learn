#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    GuardEMeiProt.rb
#  Purpose:      守卫峨眉协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#操作结果
class EGEMOptResult
	EGEMOPTRESULTFAILED = 0#失败
	EGEMOPTRESULTSUCC = 1#成功
end

#战斗类型
class EGEMBattleType
	EGEMBATTLETYPEA = 0#播放战报战斗
	EGEMBATTLETYPEB = 1#不播放战报战斗
end

#战斗结果
class EGEMBattleRet
	EGEMBATTLEFAILED = 0#战斗失败
	EGEMBATTLESUCC = 1#战斗成功
end

#守卫峨眉参战散仙信息
class SGEMBattleFighterInfo
	attr_accessor:dwFighterID #(UINT32)将模版ID
	attr_accessor:byFighterLevel #(UINT8)将等级
	attr_accessor:byFighterColour #(UINT8)将颜色
	attr_accessor:dwFighterCurHP #(UINT32)将当前血量
	attr_accessor:dwFighterMaxHP #(UINT32)将最大血量
	attr_accessor:dwFighterCurAnima #(UINT32)将当前灵气
	attr_accessor:dwFighterMaxAnima #(UINT32)将最大灵气

	#构造函数
	def initialize
		@dwFighterID = 0
		@byFighterLevel = 0
		@byFighterColour = 0
		@dwFighterCurHP = 0
		@dwFighterMaxHP = 0
		@dwFighterCurAnima = 0
		@dwFighterMaxAnima = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwFighterID = @dwFighterID
		obj.byFighterLevel = @byFighterLevel
		obj.byFighterColour = @byFighterColour
		obj.dwFighterCurHP = @dwFighterCurHP
		obj.dwFighterMaxHP = @dwFighterMaxHP
		obj.dwFighterCurAnima = @dwFighterCurAnima
		obj.dwFighterMaxAnima = @dwFighterMaxAnima
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGEMBattleFighterInfo.new
		s.dwFighterID = ByteUtil::readUINT32(data)
		s.byFighterLevel = ByteUtil::readUINT8(data)
		s.byFighterColour = ByteUtil::readUINT8(data)
		s.dwFighterCurHP = ByteUtil::readUINT32(data)
		s.dwFighterMaxHP = ByteUtil::readUINT32(data)
		s.dwFighterCurAnima = ByteUtil::readUINT32(data)
		s.dwFighterMaxAnima = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGEMBattleFighterInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwFighterID)
		ByteUtil::writeUINT8(data, @byFighterLevel)
		ByteUtil::writeUINT8(data, @byFighterColour)
		ByteUtil::writeUINT32(data, @dwFighterCurHP)
		ByteUtil::writeUINT32(data, @dwFighterMaxHP)
		ByteUtil::writeUINT32(data, @dwFighterCurAnima)
		ByteUtil::writeUINT32(data, @dwFighterMaxAnima)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#守卫峨眉奖励信息
class SGEMAwardInfo
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
		s = SGEMAwardInfo.new
		s.wItemID = ByteUtil::readUINT16(data)
		s.dwCount = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGEMAwardInfo::fromStream(data)
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

#守卫峨眉Buff信息
class SGEMBuffInfo
	attr_accessor:dwBuffID #(UINT32)BuffID
	attr_accessor:dwBuffNum #(UINT32)Buff数量

	#构造函数
	def initialize
		@dwBuffID = 0
		@dwBuffNum = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwBuffID = @dwBuffID
		obj.dwBuffNum = @dwBuffNum
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGEMBuffInfo.new
		s.dwBuffID = ByteUtil::readUINT32(data)
		s.dwBuffNum = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGEMBuffInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwBuffID)
		ByteUtil::writeUINT32(data, @dwBuffNum)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#守卫峨眉准备战斗信息
class SGEMPrepareBattleInfo
	attr_accessor:wCurProgress #(UINT16)当前进度
	attr_accessor:dwMonsterID #(UINT32)怪物ID
	attr_accessor:dwBattlePoint #(UINT32)参战散仙战斗力
	attr_accessor:vecGEMBuffInfo #(SGEMBuffInfo的数组)守卫峨眉Buff信息
	attr_accessor:vecGEMBattleFighterInfo #(SGEMBattleFighterInfo的数组)守卫峨眉参战散仙信息

	#构造函数
	def initialize
		@wCurProgress = 0
		@dwMonsterID = 0
		@dwBattlePoint = 0
		@vecGEMBuffInfo = Array.new
		@vecGEMBattleFighterInfo = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wCurProgress = @wCurProgress
		obj.dwMonsterID = @dwMonsterID
		obj.dwBattlePoint = @dwBattlePoint
		obj.vecGEMBuffInfo = @vecGEMBuffInfo
		obj.vecGEMBattleFighterInfo = @vecGEMBattleFighterInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGEMPrepareBattleInfo.new
		s.wCurProgress = ByteUtil::readUINT16(data)
		s.dwMonsterID = ByteUtil::readUINT32(data)
		s.dwBattlePoint = ByteUtil::readUINT32(data)
		s.vecGEMBuffInfo = SGEMBuffInfo::vectorFromStream(data)
		s.vecGEMBattleFighterInfo = SGEMBattleFighterInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGEMPrepareBattleInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wCurProgress)
		ByteUtil::writeUINT32(data, @dwMonsterID)
		ByteUtil::writeUINT32(data, @dwBattlePoint)
		SGEMBuffInfo::vectorToStream(data, @vecGEMBuffInfo)
		SGEMBattleFighterInfo::vectorToStream(data, @vecGEMBattleFighterInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#守卫峨眉关卡信息
class SGEMMissionInfo
	attr_accessor:wFreeEntryNumDay #(UINT16)当日免费进入次数
	attr_accessor:wBuyEntryNumDay #(UINT16)当日购买进入次数
	attr_accessor:wBuyEntryTotalNum #(UINT16)购买进入总次数
	attr_accessor:qwIsGuardSucc #(UINT64)每一位表示守卫是否成功（注：0未成功；1成功）
	attr_accessor:wCurMissionID #(UINT16)正在进行的关卡ID（注：0表示没有）
	attr_accessor:byGEMType #(UINT8)正在进行的类型（注：0表示没有；1：守卫；2：扫荡）
	attr_accessor:wCurProgress #(UINT16)正在进行的关卡进度（注：0表示没有）

	#构造函数
	def initialize
		@wFreeEntryNumDay = 0
		@wBuyEntryNumDay = 0
		@wBuyEntryTotalNum = 0
		@qwIsGuardSucc = 0
		@wCurMissionID = 0
		@byGEMType = 0
		@wCurProgress = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wFreeEntryNumDay = @wFreeEntryNumDay
		obj.wBuyEntryNumDay = @wBuyEntryNumDay
		obj.wBuyEntryTotalNum = @wBuyEntryTotalNum
		obj.qwIsGuardSucc = @qwIsGuardSucc
		obj.wCurMissionID = @wCurMissionID
		obj.byGEMType = @byGEMType
		obj.wCurProgress = @wCurProgress
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGEMMissionInfo.new
		s.wFreeEntryNumDay = ByteUtil::readUINT16(data)
		s.wBuyEntryNumDay = ByteUtil::readUINT16(data)
		s.wBuyEntryTotalNum = ByteUtil::readUINT16(data)
		s.qwIsGuardSucc = ByteUtil::readUINT64(data)
		s.wCurMissionID = ByteUtil::readUINT16(data)
		s.byGEMType = ByteUtil::readUINT8(data)
		s.wCurProgress = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGEMMissionInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wFreeEntryNumDay)
		ByteUtil::writeUINT16(data, @wBuyEntryNumDay)
		ByteUtil::writeUINT16(data, @wBuyEntryTotalNum)
		ByteUtil::writeUINT64(data, @qwIsGuardSucc)
		ByteUtil::writeUINT16(data, @wCurMissionID)
		ByteUtil::writeUINT8(data, @byGEMType)
		ByteUtil::writeUINT16(data, @wCurProgress)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#守卫峨眉DB信息
class SGEMDBInfo
	attr_accessor:qwRoleID #(UINT64)RoleID
	attr_accessor:wMissionID #(UINT16)关卡ID
	attr_accessor:byGEMType #(UINT8)正在进行的类型（注：0表示没有；1：守卫；2：扫荡）
	attr_accessor:wCurProgress #(UINT16)当前进度
	attr_accessor:wGuardProgress #(UINT16)守卫进度
	attr_accessor:dwGuardMonsterGroupID #(UINT32)怪物组ID
	attr_accessor:dwSweepEndTime #(UINT32)扫荡结束时间
	attr_accessor:strBuff #(string)守卫峨眉Buff

	#构造函数
	def initialize
		@qwRoleID = 0
		@wMissionID = 0
		@byGEMType = 0
		@wCurProgress = 0
		@wGuardProgress = 0
		@dwGuardMonsterGroupID = 0
		@dwSweepEndTime = 0
		@strBuff = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wMissionID = @wMissionID
		obj.byGEMType = @byGEMType
		obj.wCurProgress = @wCurProgress
		obj.wGuardProgress = @wGuardProgress
		obj.dwGuardMonsterGroupID = @dwGuardMonsterGroupID
		obj.dwSweepEndTime = @dwSweepEndTime
		obj.strBuff = @strBuff
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGEMDBInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wMissionID = ByteUtil::readUINT16(data)
		s.byGEMType = ByteUtil::readUINT8(data)
		s.wCurProgress = ByteUtil::readUINT16(data)
		s.wGuardProgress = ByteUtil::readUINT16(data)
		s.dwGuardMonsterGroupID = ByteUtil::readUINT32(data)
		s.dwSweepEndTime = ByteUtil::readUINT32(data)
		s.strBuff = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGEMDBInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wMissionID)
		ByteUtil::writeUINT8(data, @byGEMType)
		ByteUtil::writeUINT16(data, @wCurProgress)
		ByteUtil::writeUINT16(data, @wGuardProgress)
		ByteUtil::writeUINT32(data, @dwGuardMonsterGroupID)
		ByteUtil::writeUINT32(data, @dwSweepEndTime)
		ByteUtil::writeSTRING(data, @strBuff)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[ReqGEMInfo:请求守卫峨眉信息]的返回的参数组成的结构体
class SRetParam_ReqGEMInfo
	attr_accessor:vecGEMMissionInfo#(SGEMMissionInfo的数组)守卫峨眉关卡信息

	#构造函数
	def initialize
		@vecGEMMissionInfo = Array.new
	end
end

#函数[BuyGEMEntryNum:请求购买守卫峨眉进入次数]的返回的参数组成的结构体
class SRetParam_BuyGEMEntryNum
	attr_accessor:eGEMOptResult#(枚举类型：EGEMOptResult)操作结果

	#构造函数
	def initialize
		@eGEMOptResult = 0
	end
end

#函数[ReqUseBuff:请求使用Buff]的返回的参数组成的结构体
class SRetParam_ReqUseBuff
	attr_accessor:vecGEMBattleFighterInfo#(SGEMBattleFighterInfo的数组)守卫峨眉参战散仙信息
	attr_accessor:vecGEMBuffInfo#(SGEMBuffInfo的数组)守卫峨眉Buff信息

	#构造函数
	def initialize
		@vecGEMBattleFighterInfo = Array.new
		@vecGEMBuffInfo = Array.new
	end
end

#函数[ReqResetGEM:请求重置关卡]的返回的参数组成的结构体
class SRetParam_ReqResetGEM
	attr_accessor:eGEMOptResult#(枚举类型：EGEMOptResult)操作结果

	#构造函数
	def initialize
		@eGEMOptResult = 0
	end
end

#函数[ReqGEMPrepareBattleInfo:请求守卫峨眉准备战斗信息]的返回的参数组成的结构体
class SRetParam_ReqGEMPrepareBattleInfo
	attr_accessor:sGEMPrepareBattleInfo#(类类型：SGEMPrepareBattleInfo)守卫峨眉准备战斗信息

	#构造函数
	def initialize
		@sGEMPrepareBattleInfo = SGEMPrepareBattleInfo.new
	end
end

#函数[ReqGEMBattle:请求守卫峨眉战斗]的返回的参数组成的结构体
class SRetParam_ReqGEMBattle
	attr_accessor:eGEMBattleRet#(枚举类型：EGEMBattleRet)战斗结果
	attr_accessor:sGEMPrepareBattleInfo#(类类型：SGEMPrepareBattleInfo)守卫峨眉下一波准备战斗信息

	#构造函数
	def initialize
		@eGEMBattleRet = 0
		@sGEMPrepareBattleInfo = SGEMPrepareBattleInfo.new
	end
end

#函数[ReqSweepBegin:请求获取守卫峨眉扫荡开始]的返回的参数组成的结构体
class SRetParam_ReqSweepBegin
	attr_accessor:eGEMOptResult#(枚举类型：EGEMOptResult)操作结果

	#构造函数
	def initialize
		@eGEMOptResult = 0
	end
end

#函数[ReqSweepEnd:请求获取守卫峨眉扫荡结束(放弃扫荡)]的返回的参数组成的结构体
class SRetParam_ReqSweepEnd
	attr_accessor:wCurProgress#(UINT16)当前进度

	#构造函数
	def initialize
		@wCurProgress = 0
	end
end

#协议类：守卫峨眉协议
class GuardEMeiProtBase < ProtocolBase
	#以下为发送函数
	#发送：请求守卫峨眉信息
	def send_ReqGEMInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求购买守卫峨眉进入次数
	def send_BuyGEMEntryNum(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求使用Buff
	def send_ReqUseBuff(
		dwBuffID #(UINT32)BuffID
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwBuffID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求重置关卡
	def send_ReqResetGEM(
		wMissionID #(UINT16)关卡ID
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wMissionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求守卫峨眉准备战斗信息
	def send_ReqGEMPrepareBattleInfo(
		wMissionID #(UINT16)关卡ID
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wMissionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求守卫峨眉战斗
	def send_ReqGEMBattle(
		wMissionID,  #(UINT16)关卡ID
		dwBuffID,  #(UINT32)BuffID
		eGEMBattleType #(枚举类型：EGEMBattleType)战斗类型
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wMissionID)
		ByteUtil::writeUINT32(data, dwBuffID)
		ByteUtil::writeINT8(data, eGEMBattleType)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求获取守卫峨眉扫荡开始
	def send_ReqSweepBegin(
		wMissionID #(UINT16)关卡ID
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wMissionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求获取守卫峨眉扫荡结束(放弃扫荡)
	def send_ReqSweepEnd(
		wMissionID #(UINT16)关卡ID
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wMissionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：扫荡信息通知
	def onRecv_SweepInfoNotify(
		wCurProgress, #(UINT16)当前进度
		vecGEMSAwardInfo #(SGEMAwardInfo的数组)守卫峨眉扫荡奖励信息
	)
		raise NotImplementedError
	end
	#接收：关卡通关成功通知
	def onRecv_MissionPassSuccNotify(
	)
		raise NotImplementedError
	end
	#接收：关卡通关失败通知
	def onRecv_MissionPassFailedtify(
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：请求守卫峨眉信息
	def onReturn_ReqGEMInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqGEMInfo)返回的参数
	)
	end

	#返回：请求购买守卫峨眉进入次数
	def onReturn_BuyGEMEntryNum(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuyGEMEntryNum)返回的参数
	)
	end

	#返回：请求使用Buff
	def onReturn_ReqUseBuff(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqUseBuff)返回的参数
	)
	end

	#返回：请求重置关卡
	def onReturn_ReqResetGEM(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqResetGEM)返回的参数
	)
	end

	#返回：请求守卫峨眉准备战斗信息
	def onReturn_ReqGEMPrepareBattleInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqGEMPrepareBattleInfo)返回的参数
	)
	end

	#返回：请求守卫峨眉战斗
	def onReturn_ReqGEMBattle(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqGEMBattle)返回的参数
	)
	end

	#返回：请求获取守卫峨眉扫荡开始
	def onReturn_ReqSweepBegin(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqSweepBegin)返回的参数
	)
	end

	#返回：请求获取守卫峨眉扫荡结束(放弃扫荡)
	def onReturn_ReqSweepEnd(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqSweepEnd)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：扫荡信息通知
	def _doRecv_SweepInfoNotify(data)
		wCurProgress = ByteUtil::readUINT16(data)
		vecGEMSAwardInfo = SGEMAwardInfo::vectorFromStream(data)
		return onRecv_SweepInfoNotify(wCurProgress, vecGEMSAwardInfo)
	end

	#接收处理：关卡通关成功通知
	def _doRecv_MissionPassSuccNotify(data)
		return onRecv_MissionPassSuccNotify()
	end

	#接收处理：关卡通关失败通知
	def _doRecv_MissionPassFailedtify(data)
		return onRecv_MissionPassFailedtify()
	end

#以下为返回处理函数
	#返回处理：请求守卫峨眉信息
	def _doReturn_ReqGEMInfo(data)
		retParam = SRetParam_ReqGEMInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecGEMMissionInfo = SGEMMissionInfo::vectorFromStream(data) #(SGEMMissionInfo的数组)守卫峨眉关卡信息
		retParam.vecGEMMissionInfo = vecGEMMissionInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqGEMInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求守卫峨眉信息
	def _onTimeOut_ReqGEMInfo(sessionID)
		retParam = SRetParam_ReqGEMInfo.new;
		onReturn_ReqGEMInfo(2, retParam)
	end

	#返回处理：请求购买守卫峨眉进入次数
	def _doReturn_BuyGEMEntryNum(data)
		retParam = SRetParam_BuyGEMEntryNum.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eGEMOptResult = ByteUtil::readINT8(data) #(枚举类型：EGEMOptResult)操作结果
		retParam.eGEMOptResult = eGEMOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuyGEMEntryNum(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求购买守卫峨眉进入次数
	def _onTimeOut_BuyGEMEntryNum(sessionID)
		retParam = SRetParam_BuyGEMEntryNum.new;
		onReturn_BuyGEMEntryNum(2, retParam)
	end

	#返回处理：请求使用Buff
	def _doReturn_ReqUseBuff(data)
		retParam = SRetParam_ReqUseBuff.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecGEMBattleFighterInfo = SGEMBattleFighterInfo::vectorFromStream(data) #(SGEMBattleFighterInfo的数组)守卫峨眉参战散仙信息
		vecGEMBuffInfo = SGEMBuffInfo::vectorFromStream(data) #(SGEMBuffInfo的数组)守卫峨眉Buff信息
		retParam.vecGEMBattleFighterInfo = vecGEMBattleFighterInfo
		retParam.vecGEMBuffInfo = vecGEMBuffInfo
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

	#返回处理：请求重置关卡
	def _doReturn_ReqResetGEM(data)
		retParam = SRetParam_ReqResetGEM.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eGEMOptResult = ByteUtil::readINT8(data) #(枚举类型：EGEMOptResult)操作结果
		retParam.eGEMOptResult = eGEMOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqResetGEM(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求重置关卡
	def _onTimeOut_ReqResetGEM(sessionID)
		retParam = SRetParam_ReqResetGEM.new;
		onReturn_ReqResetGEM(2, retParam)
	end

	#返回处理：请求守卫峨眉准备战斗信息
	def _doReturn_ReqGEMPrepareBattleInfo(data)
		retParam = SRetParam_ReqGEMPrepareBattleInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		sGEMPrepareBattleInfo = SGEMPrepareBattleInfo::fromStream(data) #(类类型：SGEMPrepareBattleInfo)守卫峨眉准备战斗信息
		retParam.sGEMPrepareBattleInfo = sGEMPrepareBattleInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqGEMPrepareBattleInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求守卫峨眉准备战斗信息
	def _onTimeOut_ReqGEMPrepareBattleInfo(sessionID)
		retParam = SRetParam_ReqGEMPrepareBattleInfo.new;
		onReturn_ReqGEMPrepareBattleInfo(2, retParam)
	end

	#返回处理：请求守卫峨眉战斗
	def _doReturn_ReqGEMBattle(data)
		retParam = SRetParam_ReqGEMBattle.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eGEMBattleRet = ByteUtil::readINT8(data) #(枚举类型：EGEMBattleRet)战斗结果
		sGEMPrepareBattleInfo = SGEMPrepareBattleInfo::fromStream(data) #(类类型：SGEMPrepareBattleInfo)守卫峨眉下一波准备战斗信息
		retParam.eGEMBattleRet = eGEMBattleRet
		retParam.sGEMPrepareBattleInfo = sGEMPrepareBattleInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqGEMBattle(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求守卫峨眉战斗
	def _onTimeOut_ReqGEMBattle(sessionID)
		retParam = SRetParam_ReqGEMBattle.new;
		onReturn_ReqGEMBattle(2, retParam)
	end

	#返回处理：请求获取守卫峨眉扫荡开始
	def _doReturn_ReqSweepBegin(data)
		retParam = SRetParam_ReqSweepBegin.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eGEMOptResult = ByteUtil::readINT8(data) #(枚举类型：EGEMOptResult)操作结果
		retParam.eGEMOptResult = eGEMOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqSweepBegin(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求获取守卫峨眉扫荡开始
	def _onTimeOut_ReqSweepBegin(sessionID)
		retParam = SRetParam_ReqSweepBegin.new;
		onReturn_ReqSweepBegin(2, retParam)
	end

	#返回处理：请求获取守卫峨眉扫荡结束(放弃扫荡)
	def _doReturn_ReqSweepEnd(data)
		retParam = SRetParam_ReqSweepEnd.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		wCurProgress = ByteUtil::readUINT16(data) #(UINT16)当前进度
		retParam.wCurProgress = wCurProgress
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqSweepEnd(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求获取守卫峨眉扫荡结束(放弃扫荡)
	def _onTimeOut_ReqSweepEnd(sessionID)
		retParam = SRetParam_ReqSweepEnd.new;
		onReturn_ReqSweepEnd(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 86;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_SweepInfoNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_MissionPassSuccNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_MissionPassFailedtify' #FuncID: 3

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_ReqGEMInfo' #FuncID: 1
		@retFuncList[1] = '_doReturn_BuyGEMEntryNum' #FuncID: 2
		@retFuncList[2] = '_doReturn_ReqUseBuff' #FuncID: 3
		@retFuncList[3] = '_doReturn_ReqResetGEM' #FuncID: 4
		@retFuncList[4] = '_doReturn_ReqGEMPrepareBattleInfo' #FuncID: 5
		@retFuncList[5] = '_doReturn_ReqGEMBattle' #FuncID: 6
		@retFuncList[6] = '_doReturn_ReqSweepBegin' #FuncID: 7
		@retFuncList[7] = '_doReturn_ReqSweepEnd' #FuncID: 8

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_ReqGEMInfo' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_BuyGEMEntryNum' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_ReqUseBuff' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_ReqResetGEM' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_ReqGEMPrepareBattleInfo' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_ReqGEMBattle' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_ReqSweepBegin' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_ReqSweepEnd' #FuncID: 8
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

