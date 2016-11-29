#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    ShushanBattleProt.rb
#  Purpose:      蜀山论剑相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './MapProtBase.rb'

#以下为类型定义

#蜀山论剑参加状态
class ESSBattleStatus
	ESSBATTLE_ENTER = 0#已进入
	ESSBATTLE_QUIT = 1#已退出
	ESSBATTLE_JOINBYE = 2#轮空
	ESSBATTLE_FIGHTING = 3#正在战斗
end

#蜀山论剑操作结果
class ESSBattleResult
	ESSBATTLE_SUC = 0#成功
	ESSBATTLE_NOTRUNING = 1#论剑活动未开始
	ESSBATTLE_CDTIME = 2#正在冷却
	ESSBATTLE_LEVELLIMIT = 3#等级小于30级
	ESSBATTLE_LACKMONEY = 4#金钱不够
	ESSBATTLE_NOTENTER = 5#未参加
	ESSBATTLE_FULL = 6#霸气or怒气已满
	ESSBATTLE_NOTENOUGH = 7#霸气or怒气不足
	ESSBATTLE_USED = 8#已使用
	ESSBATTLE_OTHERERR = 9#其他错误
end

#任务数据结构
class SBattleTaskData
	attr_accessor:byTaskID #(UINT8)任务ID
	attr_accessor:byAward #(UINT8)荣誉奖励值
	attr_accessor:byComplete #(UINT8)是否完成(0否,1是)

	#构造函数
	def initialize
		@byTaskID = 0
		@byAward = 0
		@byComplete = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byTaskID = @byTaskID
		obj.byAward = @byAward
		obj.byComplete = @byComplete
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleTaskData.new
		s.byTaskID = ByteUtil::readUINT8(data)
		s.byAward = ByteUtil::readUINT8(data)
		s.byComplete = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleTaskData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byTaskID)
		ByteUtil::writeUINT8(data, @byAward)
		ByteUtil::writeUINT8(data, @byComplete)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战斗战报数据结构
class SSSBattleReport
	attr_accessor:byRound #(UINT8)当前轮次
	attr_accessor:strNameA #(string)攻方玩家名字
	attr_accessor:qwRoleA #(UINT64)攻方玩家ID
	attr_accessor:strNameB #(string)守方玩家名字
	attr_accessor:qwRoleB #(UINT64)守方玩家ID
	attr_accessor:byResult #(UINT8)结果(0是攻方胜利,1是守方胜利,2是攻方逃跑,3守方逃跑,4攻方轮空)
	attr_accessor:qwBattleID #(UINT64)战报ID
	attr_accessor:byCurrKill #(UINT8)当前连杀数(若个人战报即表明个人连杀数,若全部战报即表明攻方连杀数)
	attr_accessor:wHonor #(UINT16)当场获得荣誉值(若个人战报即表明个人获得荣誉值,若全部战报即表明攻方获得荣誉值)

	#构造函数
	def initialize
		@byRound = 0
		@strNameA = ''
		@qwRoleA = 0
		@strNameB = ''
		@qwRoleB = 0
		@byResult = 0
		@qwBattleID = 0
		@byCurrKill = 0
		@wHonor = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byRound = @byRound
		obj.strNameA = @strNameA
		obj.qwRoleA = @qwRoleA
		obj.strNameB = @strNameB
		obj.qwRoleB = @qwRoleB
		obj.byResult = @byResult
		obj.qwBattleID = @qwBattleID
		obj.byCurrKill = @byCurrKill
		obj.wHonor = @wHonor
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSSBattleReport.new
		s.byRound = ByteUtil::readUINT8(data)
		s.strNameA = ByteUtil::readSTRING(data)
		s.qwRoleA = ByteUtil::readUINT64(data)
		s.strNameB = ByteUtil::readSTRING(data)
		s.qwRoleB = ByteUtil::readUINT64(data)
		s.byResult = ByteUtil::readUINT8(data)
		s.qwBattleID = ByteUtil::readUINT64(data)
		s.byCurrKill = ByteUtil::readUINT8(data)
		s.wHonor = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSSBattleReport::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byRound)
		ByteUtil::writeSTRING(data, @strNameA)
		ByteUtil::writeUINT64(data, @qwRoleA)
		ByteUtil::writeSTRING(data, @strNameB)
		ByteUtil::writeUINT64(data, @qwRoleB)
		ByteUtil::writeUINT8(data, @byResult)
		ByteUtil::writeUINT64(data, @qwBattleID)
		ByteUtil::writeUINT8(data, @byCurrKill)
		ByteUtil::writeUINT16(data, @wHonor)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#对方玩家数据结构
class SOtherPlayer
	attr_accessor:qwRoleIDOther #(UINT64)对方玩家ID
	attr_accessor:byCurrKillOther #(UINT8)对方当前连杀数
	attr_accessor:wHonorOther #(UINT16)对方总荣誉值
	attr_accessor:wSkillFlagsOther #(UINT16)对方技能使用位域,对应位表示技能是否已使用(低8位)
	attr_accessor:dwMaxHpOther #(UINT32)对方总血量
	attr_accessor:dwCurHpOther #(UINT32)对方当前血量
	attr_accessor:dwBattlePowerOther #(UINT32)对方总战斗力
	attr_accessor:rPlayerAppear #(类类型：MapProt::SPlayerAppear)对方玩家的外观

	#构造函数
	def initialize
		@qwRoleIDOther = 0
		@byCurrKillOther = 0
		@wHonorOther = 0
		@wSkillFlagsOther = 0
		@dwMaxHpOther = 0
		@dwCurHpOther = 0
		@dwBattlePowerOther = 0
		@rPlayerAppear = SPlayerAppear.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleIDOther = @qwRoleIDOther
		obj.byCurrKillOther = @byCurrKillOther
		obj.wHonorOther = @wHonorOther
		obj.wSkillFlagsOther = @wSkillFlagsOther
		obj.dwMaxHpOther = @dwMaxHpOther
		obj.dwCurHpOther = @dwCurHpOther
		obj.dwBattlePowerOther = @dwBattlePowerOther
		obj.rPlayerAppear = @rPlayerAppear
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SOtherPlayer.new
		s.qwRoleIDOther = ByteUtil::readUINT64(data)
		s.byCurrKillOther = ByteUtil::readUINT8(data)
		s.wHonorOther = ByteUtil::readUINT16(data)
		s.wSkillFlagsOther = ByteUtil::readUINT16(data)
		s.dwMaxHpOther = ByteUtil::readUINT32(data)
		s.dwCurHpOther = ByteUtil::readUINT32(data)
		s.dwBattlePowerOther = ByteUtil::readUINT32(data)
		s.rPlayerAppear = SPlayerAppear::fromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SOtherPlayer::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleIDOther)
		ByteUtil::writeUINT8(data, @byCurrKillOther)
		ByteUtil::writeUINT16(data, @wHonorOther)
		ByteUtil::writeUINT16(data, @wSkillFlagsOther)
		ByteUtil::writeUINT32(data, @dwMaxHpOther)
		ByteUtil::writeUINT32(data, @dwCurHpOther)
		ByteUtil::writeUINT32(data, @dwBattlePowerOther)
		@rPlayerAppear.toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#论剑场玩家的配对信息，也是发给前端用的信息
class SSSBattlePairInfo
	attr_accessor:byRound #(UINT8)当前轮次
	attr_accessor:wTimeLeft #(UINT16)距离下一场【或者开始】时间(秒)
	attr_accessor:byCurrKill #(UINT8)当前连杀数
	attr_accessor:byMaxKill #(UINT8)最高连杀数
	attr_accessor:byTotalWin #(UINT8)胜利场数
	attr_accessor:byTotalLose #(UINT8)失败场数
	attr_accessor:wHonor #(UINT16)总荣誉值
	attr_accessor:byDomineer #(UINT8)霸气值
	attr_accessor:byAnger #(UINT8)怒气值
	attr_accessor:wSkillFlags #(UINT16)技能使用位域,对应位表示技能是否已使用(低8位)
	attr_accessor:vecTaskData #(SBattleTaskData的数组)任务数据vec
	attr_accessor:dwMaxHp #(UINT32)自己总血量
	attr_accessor:dwCurHp #(UINT32)自己当前血量
	attr_accessor:dwBattlePower #(UINT32)自己总战斗力
	attr_accessor:vecOtherPlayer #(SOtherPlayer的数组)对方玩家数据

	#构造函数
	def initialize
		@byRound = 0
		@wTimeLeft = 0
		@byCurrKill = 0
		@byMaxKill = 0
		@byTotalWin = 0
		@byTotalLose = 0
		@wHonor = 0
		@byDomineer = 0
		@byAnger = 0
		@wSkillFlags = 0
		@vecTaskData = Array.new
		@dwMaxHp = 0
		@dwCurHp = 0
		@dwBattlePower = 0
		@vecOtherPlayer = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byRound = @byRound
		obj.wTimeLeft = @wTimeLeft
		obj.byCurrKill = @byCurrKill
		obj.byMaxKill = @byMaxKill
		obj.byTotalWin = @byTotalWin
		obj.byTotalLose = @byTotalLose
		obj.wHonor = @wHonor
		obj.byDomineer = @byDomineer
		obj.byAnger = @byAnger
		obj.wSkillFlags = @wSkillFlags
		obj.vecTaskData = @vecTaskData
		obj.dwMaxHp = @dwMaxHp
		obj.dwCurHp = @dwCurHp
		obj.dwBattlePower = @dwBattlePower
		obj.vecOtherPlayer = @vecOtherPlayer
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSSBattlePairInfo.new
		s.byRound = ByteUtil::readUINT8(data)
		s.wTimeLeft = ByteUtil::readUINT16(data)
		s.byCurrKill = ByteUtil::readUINT8(data)
		s.byMaxKill = ByteUtil::readUINT8(data)
		s.byTotalWin = ByteUtil::readUINT8(data)
		s.byTotalLose = ByteUtil::readUINT8(data)
		s.wHonor = ByteUtil::readUINT16(data)
		s.byDomineer = ByteUtil::readUINT8(data)
		s.byAnger = ByteUtil::readUINT8(data)
		s.wSkillFlags = ByteUtil::readUINT16(data)
		s.vecTaskData = SBattleTaskData::vectorFromStream(data)
		s.dwMaxHp = ByteUtil::readUINT32(data)
		s.dwCurHp = ByteUtil::readUINT32(data)
		s.dwBattlePower = ByteUtil::readUINT32(data)
		s.vecOtherPlayer = SOtherPlayer::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSSBattlePairInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byRound)
		ByteUtil::writeUINT16(data, @wTimeLeft)
		ByteUtil::writeUINT8(data, @byCurrKill)
		ByteUtil::writeUINT8(data, @byMaxKill)
		ByteUtil::writeUINT8(data, @byTotalWin)
		ByteUtil::writeUINT8(data, @byTotalLose)
		ByteUtil::writeUINT16(data, @wHonor)
		ByteUtil::writeUINT8(data, @byDomineer)
		ByteUtil::writeUINT8(data, @byAnger)
		ByteUtil::writeUINT16(data, @wSkillFlags)
		SBattleTaskData::vectorToStream(data, @vecTaskData)
		ByteUtil::writeUINT32(data, @dwMaxHp)
		ByteUtil::writeUINT32(data, @dwCurHp)
		ByteUtil::writeUINT32(data, @dwBattlePower)
		SOtherPlayer::vectorToStream(data, @vecOtherPlayer)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#蜀山论剑场玩家使用技能返回的数据结构
class SSSBattleUseSkill
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:wHonor #(UINT16)总荣誉值
	attr_accessor:wSkillFlags #(UINT16)技能使用位域,对应位表示技能是否已使用(低8位)
	attr_accessor:dwCurHp #(UINT32)当前血量

	#构造函数
	def initialize
		@qwRoleID = 0
		@wHonor = 0
		@wSkillFlags = 0
		@dwCurHp = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wHonor = @wHonor
		obj.wSkillFlags = @wSkillFlags
		obj.dwCurHp = @dwCurHp
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSSBattleUseSkill.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wHonor = ByteUtil::readUINT16(data)
		s.wSkillFlags = ByteUtil::readUINT16(data)
		s.dwCurHp = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSSBattleUseSkill::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wHonor)
		ByteUtil::writeUINT16(data, @wSkillFlags)
		ByteUtil::writeUINT32(data, @dwCurHp)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[PlayerEnter:参加蜀山论剑活动]的返回的参数组成的结构体
class SRetParam_PlayerEnter
	attr_accessor:eResult#(枚举类型：ESSBattleResult)请求参加蜀山论剑返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[PlayerLeave:退出蜀山论剑活动]的返回的参数组成的结构体
class SRetParam_PlayerLeave
	attr_accessor:eResult#(枚举类型：ESSBattleResult)请求退出蜀山论剑返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[UseSkill:使用蜀山论剑技能]的返回的参数组成的结构体
class SRetParam_UseSkill
	attr_accessor:bySkillID#(UINT8)技能ID
	attr_accessor:eResult#(枚举类型：ESSBattleResult)请求使用蜀山论剑技能返回

	#构造函数
	def initialize
		@bySkillID = 0
		@eResult = 0
	end
end

#函数[BuySkill:购买蜀山论剑霸气or怒气]的返回的参数组成的结构体
class SRetParam_BuySkill
	attr_accessor:byFlag#(UINT8)购买类型:0霸气 1怒气
	attr_accessor:eResult#(枚举类型：ESSBattleResult)购买蜀山论剑霸气or怒气返回

	#构造函数
	def initialize
		@byFlag = 0
		@eResult = 0
	end
end

#协议类：蜀山论剑相关协议
class ShushanBattleProtBase < ProtocolBase
	#以下为发送函数
	#发送：蜀山论剑准备/开始/结束信息
	def send_GetBattleStartInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求蜀山论剑玩家的配对信息
	def send_GetPlayerPairInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求连杀王、荣誉王信息
	def send_GetFirstPlayer(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：参加蜀山论剑活动
	def send_PlayerEnter(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：退出蜀山论剑活动
	def send_PlayerLeave(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：使用蜀山论剑技能
	def send_UseSkill(
		bySkillID #(UINT8)技能ID
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, bySkillID)
		return @svrHandler.sendPacket(data)
	end

	#发送：购买蜀山论剑霸气or怒气
	def send_BuySkill(
		byFlag #(UINT8)购买类型:0霸气 1怒气
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byFlag)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：蜀山论剑准备/开始/结束信息
	def onRecv_BattleStartInfo(
		byStatus, #(UINT8)状态=>0:准备 1:开始 2:结束
		dwTimeLeft #(UINT32)byStatus为0:距离开始的剩余时间;byStatus为1:距离结束的剩余时间;byStatus为2:距离下一次开始的剩余时间
	)
		raise NotImplementedError
	end
	#接收：蜀山论剑玩家的配对信息
	def onRecv_PlayerPairInfo(
		stPairInfo #(类类型：SSSBattlePairInfo)玩家的配对信息
	)
		raise NotImplementedError
	end
	#接收：广播连杀王玩家信息
	def onRecv_TopKiller(
		strName, #(string)玩家名字
		byTopStreak #(UINT8)最高连杀数
	)
		raise NotImplementedError
	end
	#接收：广播荣誉王玩家信息
	def onRecv_HonorKinger(
		strName, #(string)玩家名字
		wMaxHonor #(UINT16)最高荣誉值
	)
		raise NotImplementedError
	end
	#接收：蜀山论剑玩家的战报信息
	def onRecv_BattleReportInfo(
		byType, #(UINT8)0表示个人战报 1表示全部
		vecReport #(SSSBattleReport的数组)玩家的战斗信息
	)
		raise NotImplementedError
	end
	#接收：蜀山论剑玩家使用技能信息
	def onRecv_UseSkillInfo(
		stUseSkill #(类类型：SSSBattleUseSkill)使用技能信息
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：参加蜀山论剑活动
	def onReturn_PlayerEnter(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_PlayerEnter)返回的参数
	)
	end

	#返回：退出蜀山论剑活动
	def onReturn_PlayerLeave(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_PlayerLeave)返回的参数
	)
	end

	#返回：使用蜀山论剑技能
	def onReturn_UseSkill(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UseSkill)返回的参数
	)
	end

	#返回：购买蜀山论剑霸气or怒气
	def onReturn_BuySkill(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuySkill)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：蜀山论剑准备/开始/结束信息
	def _doRecv_BattleStartInfo(data)
		byStatus = ByteUtil::readUINT8(data)
		dwTimeLeft = ByteUtil::readUINT32(data)
		return onRecv_BattleStartInfo(byStatus, dwTimeLeft)
	end

	#接收处理：蜀山论剑玩家的配对信息
	def _doRecv_PlayerPairInfo(data)
		stPairInfo = SSSBattlePairInfo::fromStream(data)
		return onRecv_PlayerPairInfo(stPairInfo)
	end

	#接收处理：广播连杀王玩家信息
	def _doRecv_TopKiller(data)
		strName = ByteUtil::readSTRING(data)
		byTopStreak = ByteUtil::readUINT8(data)
		return onRecv_TopKiller(strName, byTopStreak)
	end

	#接收处理：广播荣誉王玩家信息
	def _doRecv_HonorKinger(data)
		strName = ByteUtil::readSTRING(data)
		wMaxHonor = ByteUtil::readUINT16(data)
		return onRecv_HonorKinger(strName, wMaxHonor)
	end

	#接收处理：蜀山论剑玩家的战报信息
	def _doRecv_BattleReportInfo(data)
		byType = ByteUtil::readUINT8(data)
		vecReport = SSSBattleReport::vectorFromStream(data)
		return onRecv_BattleReportInfo(byType, vecReport)
	end

	#接收处理：蜀山论剑玩家使用技能信息
	def _doRecv_UseSkillInfo(data)
		stUseSkill = SSSBattleUseSkill::fromStream(data)
		return onRecv_UseSkillInfo(stUseSkill)
	end

#以下为返回处理函数
	#返回处理：参加蜀山论剑活动
	def _doReturn_PlayerEnter(data)
		retParam = SRetParam_PlayerEnter.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ESSBattleResult)请求参加蜀山论剑返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_PlayerEnter(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：参加蜀山论剑活动
	def _onTimeOut_PlayerEnter(sessionID)
		retParam = SRetParam_PlayerEnter.new;
		onReturn_PlayerEnter(2, retParam)
	end

	#返回处理：退出蜀山论剑活动
	def _doReturn_PlayerLeave(data)
		retParam = SRetParam_PlayerLeave.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ESSBattleResult)请求退出蜀山论剑返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_PlayerLeave(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：退出蜀山论剑活动
	def _onTimeOut_PlayerLeave(sessionID)
		retParam = SRetParam_PlayerLeave.new;
		onReturn_PlayerLeave(2, retParam)
	end

	#返回处理：使用蜀山论剑技能
	def _doReturn_UseSkill(data)
		retParam = SRetParam_UseSkill.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		bySkillID = ByteUtil::readUINT8(data) #(UINT8)技能ID
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ESSBattleResult)请求使用蜀山论剑技能返回
		retParam.bySkillID = bySkillID
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UseSkill(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：使用蜀山论剑技能
	def _onTimeOut_UseSkill(sessionID)
		retParam = SRetParam_UseSkill.new;
		onReturn_UseSkill(2, retParam)
	end

	#返回处理：购买蜀山论剑霸气or怒气
	def _doReturn_BuySkill(data)
		retParam = SRetParam_BuySkill.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byFlag = ByteUtil::readUINT8(data) #(UINT8)购买类型:0霸气 1怒气
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ESSBattleResult)购买蜀山论剑霸气or怒气返回
		retParam.byFlag = byFlag
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuySkill(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：购买蜀山论剑霸气or怒气
	def _onTimeOut_BuySkill(sessionID)
		retParam = SRetParam_BuySkill.new;
		onReturn_BuySkill(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 66;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_BattleStartInfo' #FuncID: 1
		@recvFuncList[1] = '_doRecv_PlayerPairInfo' #FuncID: 2
		@recvFuncList[2] = '_doRecv_TopKiller' #FuncID: 3
		@recvFuncList[3] = '_doRecv_HonorKinger' #FuncID: 4
		@recvFuncList[4] = '_doRecv_BattleReportInfo' #FuncID: 5
		@recvFuncList[5] = '_doRecv_UseSkillInfo' #FuncID: 6

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_PlayerEnter' #FuncID: 1
		@retFuncList[1] = '_doReturn_PlayerLeave' #FuncID: 2
		@retFuncList[2] = '_doReturn_UseSkill' #FuncID: 3
		@retFuncList[3] = '_doReturn_BuySkill' #FuncID: 4

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_PlayerEnter' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_PlayerLeave' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_UseSkill' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_BuySkill' #FuncID: 4
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

