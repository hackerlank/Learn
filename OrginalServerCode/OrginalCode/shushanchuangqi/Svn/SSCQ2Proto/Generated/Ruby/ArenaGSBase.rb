#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    ArenaGS.rb
#  Purpose:      竞技场协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './BattleGSBase.rb'

#以下为类型定义

#竞技等级
class EArenaLevel
	EARENALEVEL_NONE = 0#无等级
	EARENALEVEL_IRON = 1#黑铁
	EARENALEVEL_COPPER = 2#青铜
	EARENALEVEL_SILVER = 3#白银
	EARENALEVEL_GOLD = 4#黄金
	EARENALEVEL_DIAMOND = 5#钻石
	EARENALEVEL_END = 6#最大值
end

#竞技场操作结果
class EArenaResult
	EARENAR_SUC = 0#成功
	EARENAR_NOENTER = 1#没有参加斗剑
	EARENAR_CDTIME = 2#正在冷却
	EARENAR_NOCHANLLENGETIMES = 3#挑战次数用完
	EARENAR_BUYTIMESCHANLLENGETIMES = 4#购买挑战次数已达上限
	EARENAR_LACKMONEY = 5#钱钱不够
	EARENAR_ENEMYNOEXIST = 6#挑战目标不存在
	EARENAR_ENEMYTIMEOUT = 7#挑战目标已过期
	EARENAR_ENEMYISSUC = 8#挑战目标已胜利
	EARENAR_NOREWARD = 9#没有奖励可领取
	EARENAR_REWARDHASGET = 10#奖励已经领取
	EARENAR_PACKAGEFULL = 11#包裹满了
	EARENAR_AWARDTIMEOUT = 12#奖励已过期
	EARENAR_WIRSHIPOVERTIMES = 13#膜拜次数已达上限
	EARENAR_WIRSHIPPLAYEROVERTIMER = 14#膜拜对象已过期
	EARENAR_BUYTIMESMAX = 15#累计购买次数已达上限
	EARENAR_VIPLEVEL = 16#御剑等级不足
	EARENAR_LADDERNOOPEN = 17#天梯未开启
	EARENAR_LADDERTIMESLIMIT = 18#天梯挑战次数不足
	EARENAR_LADDERAWARDHASGET = 19#天梯挑战奖励已领
	EARENAR_LADDERRANKERR = 20#排名验证错误
	EARENAR_LADDERRANKLIMIT = 21#挑战资格验证错误
	EARENAR_ARENANOOPEN = 22#斗剑功能未开放
	EARENAR_ARENATIMESLIMIT = 23#历练挑战次数不足
	EARENAR_ARENAAWARDHASGET = 24#历练挑战奖励已领
	EARENAR_LADDERTIMESZERO = 25#天梯挑战次数用完
	EARENAR_LADDERBUYTIMESUP = 26#天梯挑战购买次数到达上限
	EARENAR_OTHERERR = 27#其他错误
end

#奖励包类型
class EArenaAwardType
	TYPE_NONE = 0#无定义
	TYPE_LEVEL = 1#段位包
	TYPE_RANK = 2#排名包
	TYPE_LADDERRANK = 3#天梯排名包
end

#机器人排名信息
class SLadderRobot
	attr_accessor:wMonsterID #(UINT16)机器人ID
	attr_accessor:wRank #(UINT16)机器人排名

	#构造函数
	def initialize
		@wMonsterID = 0
		@wRank = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wMonsterID = @wMonsterID
		obj.wRank = @wRank
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SLadderRobot.new
		s.wMonsterID = ByteUtil::readUINT16(data)
		s.wRank = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SLadderRobot::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wMonsterID)
		ByteUtil::writeUINT16(data, @wRank)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家奖励信息
class SArenaAward
	attr_accessor:eType #(枚举类型：EArenaAwardType)奖励包类型
	attr_accessor:byDraw #(UINT8)0,表示未领取；1，表示已领取
	attr_accessor:dwDrawID #(UINT32)掉落包ID

	#构造函数
	def initialize
		@eType = 0
		@byDraw = 0
		@dwDrawID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eType = @eType
		obj.byDraw = @byDraw
		obj.dwDrawID = @dwDrawID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SArenaAward.new
		s.eType = ByteUtil::readUINT8(data)
		s.byDraw = ByteUtil::readUINT8(data)
		s.dwDrawID = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SArenaAward::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eType)
		ByteUtil::writeUINT8(data, @byDraw)
		ByteUtil::writeUINT32(data, @dwDrawID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#竞技场玩家信息
class SArenaFighter
	attr_accessor:strName #(string)名字
	attr_accessor:wLevel #(UINT16)等级
	attr_accessor:stAppear #(类类型：BattleGS::SPlayerFeature)外观

	#构造函数
	def initialize
		@strName = ''
		@wLevel = 0
		@stAppear = SPlayerFeature.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strName = @strName
		obj.wLevel = @wLevel
		obj.stAppear = @stAppear
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SArenaFighter.new
		s.strName = ByteUtil::readSTRING(data)
		s.wLevel = ByteUtil::readUINT16(data)
		s.stAppear = SPlayerFeature::fromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SArenaFighter::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT16(data, @wLevel)
		@stAppear.toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家刷对手信息
class SFlushFighter
	attr_accessor:bySuc #(UINT8)0,表示未战胜；1，表示已击败
	attr_accessor:qwFighterID #(UINT64)对手ID,小于65535为怪物

	#构造函数
	def initialize
		@bySuc = 0
		@qwFighterID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.bySuc = @bySuc
		obj.qwFighterID = @qwFighterID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFlushFighter.new
		s.bySuc = ByteUtil::readUINT8(data)
		s.qwFighterID = ByteUtil::readUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFlushFighter::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @bySuc)
		ByteUtil::writeUINT64(data, @qwFighterID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#竞技场玩家基本信息
class SArenaPlayerBaseData
	attr_accessor:dwRanking #(UINT32)同积分序号
	attr_accessor:dwScore #(UINT32)积分
	attr_accessor:dwLadderRank #(UINT32)天梯排名0表示天梯功未开启，10000表示天梯功能已开启未挑机器人，9999表示已挑战机器人
	attr_accessor:eLevel #(枚举类型：EArenaLevel)竞技等级
	attr_accessor:dwLastFlushTime #(UINT32)最近客户端刷新时间
	attr_accessor:dwLastRank #(UINT32)最近结算排名
	attr_accessor:eLastLevel #(枚举类型：EArenaLevel)最近结算之前段位
	attr_accessor:dwFighterPower #(UINT32)战斗力
	attr_accessor:byQuality #(UINT8)品质
	attr_accessor:byVIPLevel #(UINT8)VIP等级
	attr_accessor:dwLastLadderRank #(UINT32)最近结算排名

	#构造函数
	def initialize
		@dwRanking = 0
		@dwScore = 0
		@dwLadderRank = 0
		@eLevel = 0
		@dwLastFlushTime = 0
		@dwLastRank = 0
		@eLastLevel = 0
		@dwFighterPower = 0
		@byQuality = 0
		@byVIPLevel = 0
		@dwLastLadderRank = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwRanking = @dwRanking
		obj.dwScore = @dwScore
		obj.dwLadderRank = @dwLadderRank
		obj.eLevel = @eLevel
		obj.dwLastFlushTime = @dwLastFlushTime
		obj.dwLastRank = @dwLastRank
		obj.eLastLevel = @eLastLevel
		obj.dwFighterPower = @dwFighterPower
		obj.byQuality = @byQuality
		obj.byVIPLevel = @byVIPLevel
		obj.dwLastLadderRank = @dwLastLadderRank
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SArenaPlayerBaseData.new
		s.dwRanking = ByteUtil::readUINT32(data)
		s.dwScore = ByteUtil::readUINT32(data)
		s.dwLadderRank = ByteUtil::readUINT32(data)
		s.eLevel = ByteUtil::readUINT8(data)
		s.dwLastFlushTime = ByteUtil::readUINT32(data)
		s.dwLastRank = ByteUtil::readUINT32(data)
		s.eLastLevel = ByteUtil::readUINT8(data)
		s.dwFighterPower = ByteUtil::readUINT32(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.byVIPLevel = ByteUtil::readUINT8(data)
		s.dwLastLadderRank = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SArenaPlayerBaseData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwRanking)
		ByteUtil::writeUINT32(data, @dwScore)
		ByteUtil::writeUINT32(data, @dwLadderRank)
		ByteUtil::writeUINT8(data, @eLevel)
		ByteUtil::writeUINT32(data, @dwLastFlushTime)
		ByteUtil::writeUINT32(data, @dwLastRank)
		ByteUtil::writeUINT8(data, @eLastLevel)
		ByteUtil::writeUINT32(data, @dwFighterPower)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT8(data, @byVIPLevel)
		ByteUtil::writeUINT32(data, @dwLastLadderRank)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#竞技场玩家信息，要进数据库的总信息
class SArenaPlayerData
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:stFighter #(类类型：SArenaFighter)角色基本信息
	attr_accessor:stBaseData #(类类型：SArenaPlayerBaseData)基本竞技场信息

	#构造函数
	def initialize
		@qwRoleID = 0
		@stFighter = SArenaFighter.new
		@stBaseData = SArenaPlayerBaseData.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.stFighter = @stFighter
		obj.stBaseData = @stBaseData
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SArenaPlayerData.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.stFighter = SArenaFighter::fromStream(data)
		s.stBaseData = SArenaPlayerBaseData::fromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SArenaPlayerData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		@stFighter.toStream(data)
		@stBaseData.toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#竞技场更新信息
class SArenaPlayerBaseDataUpdate
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:stBaseData #(类类型：SArenaPlayerBaseData)基本竞技场信息

	#构造函数
	def initialize
		@qwRoleID = 0
		@stBaseData = SArenaPlayerBaseData.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.stBaseData = @stBaseData
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SArenaPlayerBaseDataUpdate.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.stBaseData = SArenaPlayerBaseData::fromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SArenaPlayerBaseDataUpdate::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		@stBaseData.toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#客户端竞技场的对手
class SFlushFitherForClient
	attr_accessor:stFlushFighter #(类类型：SFlushFighter)id，小于65535为机器人，读怪物列表
	attr_accessor:wGroup #(UINT32)
	attr_accessor:eLevel #(枚举类型：EArenaLevel)段位,无段位表示没有加入竞技场
	attr_accessor:stFighter #(类类型：SArenaFighter)其他属性
	attr_accessor:dwFighterPower #(UINT32)战斗力
	attr_accessor:dwLadderRank #(UINT32)天梯排名
	attr_accessor:dwArenaRank #(UINT32)历练排名

	#构造函数
	def initialize
		@stFlushFighter = SFlushFighter.new
		@wGroup = 0
		@eLevel = 0
		@stFighter = SArenaFighter.new
		@dwFighterPower = 0
		@dwLadderRank = 0
		@dwArenaRank = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.stFlushFighter = @stFlushFighter
		obj.wGroup = @wGroup
		obj.eLevel = @eLevel
		obj.stFighter = @stFighter
		obj.dwFighterPower = @dwFighterPower
		obj.dwLadderRank = @dwLadderRank
		obj.dwArenaRank = @dwArenaRank
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFlushFitherForClient.new
		s.stFlushFighter = SFlushFighter::fromStream(data)
		s.wGroup = ByteUtil::readUINT32(data)
		s.eLevel = ByteUtil::readUINT8(data)
		s.stFighter = SArenaFighter::fromStream(data)
		s.dwFighterPower = ByteUtil::readUINT32(data)
		s.dwLadderRank = ByteUtil::readUINT32(data)
		s.dwArenaRank = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFlushFitherForClient::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		@stFlushFighter.toStream(data)
		ByteUtil::writeUINT32(data, @wGroup)
		ByteUtil::writeUINT8(data, @eLevel)
		@stFighter.toStream(data)
		ByteUtil::writeUINT32(data, @dwFighterPower)
		ByteUtil::writeUINT32(data, @dwLadderRank)
		ByteUtil::writeUINT32(data, @dwArenaRank)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战报
class SLadderReport
	attr_accessor:qwBattleID #(UINT64)战报ID
	attr_accessor:qwEmemyID #(UINT64)对手ID
	attr_accessor:strName #(string)对手名字
	attr_accessor:dwMonsterId #(UINT32)对手是机器人,机器人ID
	attr_accessor:byAttack #(UINT8)0,表示挑战别人，1表示别人挑战自己
	attr_accessor:bySuc #(UINT8)0,自己失败，1，自己胜利
	attr_accessor:dwPreRank #(UINT32)挑战之前的排名
	attr_accessor:dwNowRank #(UINT32)挑战之后的排名
	attr_accessor:dwTimer #(UINT32)战报时间

	#构造函数
	def initialize
		@qwBattleID = 0
		@qwEmemyID = 0
		@strName = ''
		@dwMonsterId = 0
		@byAttack = 0
		@bySuc = 0
		@dwPreRank = 0
		@dwNowRank = 0
		@dwTimer = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwBattleID = @qwBattleID
		obj.qwEmemyID = @qwEmemyID
		obj.strName = @strName
		obj.dwMonsterId = @dwMonsterId
		obj.byAttack = @byAttack
		obj.bySuc = @bySuc
		obj.dwPreRank = @dwPreRank
		obj.dwNowRank = @dwNowRank
		obj.dwTimer = @dwTimer
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SLadderReport.new
		s.qwBattleID = ByteUtil::readUINT64(data)
		s.qwEmemyID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.dwMonsterId = ByteUtil::readUINT32(data)
		s.byAttack = ByteUtil::readUINT8(data)
		s.bySuc = ByteUtil::readUINT8(data)
		s.dwPreRank = ByteUtil::readUINT32(data)
		s.dwNowRank = ByteUtil::readUINT32(data)
		s.dwTimer = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SLadderReport::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwBattleID)
		ByteUtil::writeUINT64(data, @qwEmemyID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT32(data, @dwMonsterId)
		ByteUtil::writeUINT8(data, @byAttack)
		ByteUtil::writeUINT8(data, @bySuc)
		ByteUtil::writeUINT32(data, @dwPreRank)
		ByteUtil::writeUINT32(data, @dwNowRank)
		ByteUtil::writeUINT32(data, @dwTimer)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#排行信息
class SArenaRank2Client
	attr_accessor:qwRoleID #(UINT64)ID
	attr_accessor:dwRank #(UINT32)名次
	attr_accessor:dwScore #(UINT32)积分
	attr_accessor:stFighter #(类类型：SArenaFighter)其它信息
	attr_accessor:dwFighterPower #(UINT32)战斗力
	attr_accessor:byQuality #(UINT8)品质
	attr_accessor:byVIPLevel #(UINT8)品质
	attr_accessor:dwLadderRank #(UINT32)天梯排名

	#构造函数
	def initialize
		@qwRoleID = 0
		@dwRank = 0
		@dwScore = 0
		@stFighter = SArenaFighter.new
		@dwFighterPower = 0
		@byQuality = 0
		@byVIPLevel = 0
		@dwLadderRank = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.dwRank = @dwRank
		obj.dwScore = @dwScore
		obj.stFighter = @stFighter
		obj.dwFighterPower = @dwFighterPower
		obj.byQuality = @byQuality
		obj.byVIPLevel = @byVIPLevel
		obj.dwLadderRank = @dwLadderRank
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SArenaRank2Client.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.dwRank = ByteUtil::readUINT32(data)
		s.dwScore = ByteUtil::readUINT32(data)
		s.stFighter = SArenaFighter::fromStream(data)
		s.dwFighterPower = ByteUtil::readUINT32(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.byVIPLevel = ByteUtil::readUINT8(data)
		s.dwLadderRank = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SArenaRank2Client::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT32(data, @dwRank)
		ByteUtil::writeUINT32(data, @dwScore)
		@stFighter.toStream(data)
		ByteUtil::writeUINT32(data, @dwFighterPower)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT8(data, @byVIPLevel)
		ByteUtil::writeUINT32(data, @dwLadderRank)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#竞技场玩家基本信息，也是发给前端用的信息
class SArenaPlayerBaseData2Client
	attr_accessor:dwRanking #(UINT32)本段位排名
	attr_accessor:dwScore #(UINT32)积分
	attr_accessor:eLevel #(枚举类型：EArenaLevel)段位
	attr_accessor:dwTotalSize #(UINT32)本段位总人数
	attr_accessor:ePreLevel #(枚举类型：EArenaLevel)前次结算段位
	attr_accessor:dwPreRank #(UINT32)前次结算排名
	attr_accessor:vecAwards #(SArenaAward的数组)奖励包状态
	attr_accessor:dwArenaCDTime #(UINT32)历练冷却到期时间戳
	attr_accessor:dwLadderCDTime #(UINT32)天梯冷却到期时间戳
	attr_accessor:wChallenge #(UINT16)当前挑战次数，每天0点清0
	attr_accessor:wChallengeBuyTimes #(UINT16)购买的挑战次数
	attr_accessor:wSelfReflush #(UINT16)当前购买刷新次数
	attr_accessor:wSelfFreeReflush #(UINT16)当前VIP免费刷新次数
	attr_accessor:byArenaWirship #(UINT8)膜拜次数
	attr_accessor:dwLastLadderRank #(UINT32)上次结算天梯排名，0表示排名
	attr_accessor:dwMinLadderRank #(UINT32)天梯最好排名,0表示无排名
	attr_accessor:vecFlushFigter #(SFlushFitherForClient的数组)最近刷的对手
	attr_accessor:vecWirshipFigter #(SArenaRank2Client的数组)膜拜对象列表
	attr_accessor:dwFighterPower #(UINT32)战斗力
	attr_accessor:dwLadderRank #(UINT32)天梯排名，0表示未参与天梯，9999表示已经与机器战斗，但是不计入排名，否者为真实排名
	attr_accessor:wLadderChallenge #(UINT16)天梯挑战次数
	attr_accessor:dwArenaAward #(UINT32)历练挑战奖励，天梯挑战奖励领取状况，右到左1位历练，2位天梯
	attr_accessor:dwLadderBuyTimes #(UINT32)购买的天梯挑战次数
	attr_accessor:dwLadderBuyTimesToday #(UINT32)今日购买的天梯挑战次数

	#构造函数
	def initialize
		@dwRanking = 0
		@dwScore = 0
		@eLevel = 0
		@dwTotalSize = 0
		@ePreLevel = 0
		@dwPreRank = 0
		@vecAwards = Array.new
		@dwArenaCDTime = 0
		@dwLadderCDTime = 0
		@wChallenge = 0
		@wChallengeBuyTimes = 0
		@wSelfReflush = 0
		@wSelfFreeReflush = 0
		@byArenaWirship = 0
		@dwLastLadderRank = 0
		@dwMinLadderRank = 0
		@vecFlushFigter = Array.new
		@vecWirshipFigter = Array.new
		@dwFighterPower = 0
		@dwLadderRank = 0
		@wLadderChallenge = 0
		@dwArenaAward = 0
		@dwLadderBuyTimes = 0
		@dwLadderBuyTimesToday = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwRanking = @dwRanking
		obj.dwScore = @dwScore
		obj.eLevel = @eLevel
		obj.dwTotalSize = @dwTotalSize
		obj.ePreLevel = @ePreLevel
		obj.dwPreRank = @dwPreRank
		obj.vecAwards = @vecAwards
		obj.dwArenaCDTime = @dwArenaCDTime
		obj.dwLadderCDTime = @dwLadderCDTime
		obj.wChallenge = @wChallenge
		obj.wChallengeBuyTimes = @wChallengeBuyTimes
		obj.wSelfReflush = @wSelfReflush
		obj.wSelfFreeReflush = @wSelfFreeReflush
		obj.byArenaWirship = @byArenaWirship
		obj.dwLastLadderRank = @dwLastLadderRank
		obj.dwMinLadderRank = @dwMinLadderRank
		obj.vecFlushFigter = @vecFlushFigter
		obj.vecWirshipFigter = @vecWirshipFigter
		obj.dwFighterPower = @dwFighterPower
		obj.dwLadderRank = @dwLadderRank
		obj.wLadderChallenge = @wLadderChallenge
		obj.dwArenaAward = @dwArenaAward
		obj.dwLadderBuyTimes = @dwLadderBuyTimes
		obj.dwLadderBuyTimesToday = @dwLadderBuyTimesToday
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SArenaPlayerBaseData2Client.new
		s.dwRanking = ByteUtil::readUINT32(data)
		s.dwScore = ByteUtil::readUINT32(data)
		s.eLevel = ByteUtil::readUINT8(data)
		s.dwTotalSize = ByteUtil::readUINT32(data)
		s.ePreLevel = ByteUtil::readUINT8(data)
		s.dwPreRank = ByteUtil::readUINT32(data)
		s.vecAwards = SArenaAward::vectorFromStream(data)
		s.dwArenaCDTime = ByteUtil::readUINT32(data)
		s.dwLadderCDTime = ByteUtil::readUINT32(data)
		s.wChallenge = ByteUtil::readUINT16(data)
		s.wChallengeBuyTimes = ByteUtil::readUINT16(data)
		s.wSelfReflush = ByteUtil::readUINT16(data)
		s.wSelfFreeReflush = ByteUtil::readUINT16(data)
		s.byArenaWirship = ByteUtil::readUINT8(data)
		s.dwLastLadderRank = ByteUtil::readUINT32(data)
		s.dwMinLadderRank = ByteUtil::readUINT32(data)
		s.vecFlushFigter = SFlushFitherForClient::vectorFromStream(data)
		s.vecWirshipFigter = SArenaRank2Client::vectorFromStream(data)
		s.dwFighterPower = ByteUtil::readUINT32(data)
		s.dwLadderRank = ByteUtil::readUINT32(data)
		s.wLadderChallenge = ByteUtil::readUINT16(data)
		s.dwArenaAward = ByteUtil::readUINT32(data)
		s.dwLadderBuyTimes = ByteUtil::readUINT32(data)
		s.dwLadderBuyTimesToday = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SArenaPlayerBaseData2Client::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwRanking)
		ByteUtil::writeUINT32(data, @dwScore)
		ByteUtil::writeUINT8(data, @eLevel)
		ByteUtil::writeUINT32(data, @dwTotalSize)
		ByteUtil::writeUINT8(data, @ePreLevel)
		ByteUtil::writeUINT32(data, @dwPreRank)
		SArenaAward::vectorToStream(data, @vecAwards)
		ByteUtil::writeUINT32(data, @dwArenaCDTime)
		ByteUtil::writeUINT32(data, @dwLadderCDTime)
		ByteUtil::writeUINT16(data, @wChallenge)
		ByteUtil::writeUINT16(data, @wChallengeBuyTimes)
		ByteUtil::writeUINT16(data, @wSelfReflush)
		ByteUtil::writeUINT16(data, @wSelfFreeReflush)
		ByteUtil::writeUINT8(data, @byArenaWirship)
		ByteUtil::writeUINT32(data, @dwLastLadderRank)
		ByteUtil::writeUINT32(data, @dwMinLadderRank)
		SFlushFitherForClient::vectorToStream(data, @vecFlushFigter)
		SArenaRank2Client::vectorToStream(data, @vecWirshipFigter)
		ByteUtil::writeUINT32(data, @dwFighterPower)
		ByteUtil::writeUINT32(data, @dwLadderRank)
		ByteUtil::writeUINT16(data, @wLadderChallenge)
		ByteUtil::writeUINT32(data, @dwArenaAward)
		ByteUtil::writeUINT32(data, @dwLadderBuyTimes)
		ByteUtil::writeUINT32(data, @dwLadderBuyTimesToday)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[ArenaInfoReq:请求自己竞技场信息,同时开启竞技场]的返回的参数组成的结构体
class SRetParam_ArenaInfoReq
	attr_accessor:eResult#(枚举类型：EArenaResult)结果提示
	attr_accessor:stReturn#(类类型：SArenaPlayerBaseData2Client)返回的自己信息

	#构造函数
	def initialize
		@eResult = 0
		@stReturn = SArenaPlayerBaseData2Client.new
	end
end

#函数[ArenaChallengeReq:请求挑战]的返回的参数组成的结构体
class SRetParam_ArenaChallengeReq
	attr_accessor:eResult#(枚举类型：EArenaResult)请求挑战返回
	attr_accessor:qwBattleID#(UINT64)战报ID
	attr_accessor:bySuc#(UINT8)0,表示挑战失败，1表示挑战成功
	attr_accessor:dwScore#(UINT32)当前积分
	attr_accessor:dwRanking#(UINT32)当前排名
	attr_accessor:wChallenge#(UINT16)今日挑战次数
	attr_accessor:wChallengeBuyTimes#(UINT16)购买的挑战次数
	attr_accessor:dwCDTimer#(UINT32)冷却时间戳

	#构造函数
	def initialize
		@eResult = 0
		@qwBattleID = 0
		@bySuc = 0
		@dwScore = 0
		@dwRanking = 0
		@wChallenge = 0
		@wChallengeBuyTimes = 0
		@dwCDTimer = 0
	end
end

#函数[ArenaByChallengeTimes:请求购买挑战次数]的返回的参数组成的结构体
class SRetParam_ArenaByChallengeTimes
	attr_accessor:eResult#(枚举类型：EArenaResult)请求挑战返回
	attr_accessor:wChallenge#(UINT16)今日挑战次数
	attr_accessor:wChallengeBuyTimes#(UINT16)购买的挑战次数

	#构造函数
	def initialize
		@eResult = 0
		@wChallenge = 0
		@wChallengeBuyTimes = 0
	end
end

#函数[ArenaPageUpReq:请求翻页]的返回的参数组成的结构体
class SRetParam_ArenaPageUpReq
	attr_accessor:eResult#(枚举类型：EArenaResult)查询结果
	attr_accessor:dwSize#(UINT32)本段位的人数总计
	attr_accessor:vecRankData#(SArenaRank2Client的数组)排行榜数据

	#构造函数
	def initialize
		@eResult = 0
		@dwSize = 0
		@vecRankData = Array.new
	end
end

#函数[ArenaClearCDReq:请求清除冷却]的返回的参数组成的结构体
class SRetParam_ArenaClearCDReq
	attr_accessor:eResult#(枚举类型：EArenaResult)请求清除冷却返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[ArenaGetRankingRewardReq:请求获取奖池奖励]的返回的参数组成的结构体
class SRetParam_ArenaGetRankingRewardReq
	attr_accessor:eResult#(枚举类型：EArenaResult)请求获取奖池奖励返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[ArenaWorship:膜拜请求]的返回的参数组成的结构体
class SRetParam_ArenaWorship
	attr_accessor:eResult#(枚举类型：EArenaResult)膜拜请求返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[FlushNewEnemy:请求刷将]的返回的参数组成的结构体
class SRetParam_FlushNewEnemy
	attr_accessor:eResult#(枚举类型：EArenaResult)请求刷将返回
	attr_accessor:wSelfReflush#(UINT16)当前购买刷新次数
	attr_accessor:wSelfFreeReflush#(UINT16)当前VIP免费刷新次数

	#构造函数
	def initialize
		@eResult = 0
		@wSelfReflush = 0
		@wSelfFreeReflush = 0
	end
end

#函数[GetAllEnemy:请求对手信息]的返回的参数组成的结构体
class SRetParam_GetAllEnemy
	attr_accessor:eResult#(枚举类型：EArenaResult)请求刷将返回
	attr_accessor:vecFlushFigter#(SFlushFitherForClient的数组)最近刷的对手

	#构造函数
	def initialize
		@eResult = 0
		@vecFlushFigter = Array.new
	end
end

#函数[GetAllAward:请求奖励信息]的返回的参数组成的结构体
class SRetParam_GetAllAward
	attr_accessor:eResult#(枚举类型：EArenaResult)请求刷将返回
	attr_accessor:vecAwards#(SArenaAward的数组)奖励包状态

	#构造函数
	def initialize
		@eResult = 0
		@vecAwards = Array.new
	end
end

#函数[GetAllWirship:请求膜拜信息]的返回的参数组成的结构体
class SRetParam_GetAllWirship
	attr_accessor:eResult#(枚举类型：EArenaResult)请求刷将返回
	attr_accessor:vecWirshipFigter#(SArenaRank2Client的数组)膜拜对象列表

	#构造函数
	def initialize
		@eResult = 0
		@vecWirshipFigter = Array.new
	end
end

#函数[GetAllAwardInfo:请求计算:奖励信息]的返回的参数组成的结构体
class SRetParam_GetAllAwardInfo
	attr_accessor:eResult#(枚举类型：EArenaResult)返回
	attr_accessor:vecAwards#(SArenaAward的数组)奖励包状态

	#构造函数
	def initialize
		@eResult = 0
		@vecAwards = Array.new
	end
end

#函数[ReFluseLadderEnemy:请求对手信息]的返回的参数组成的结构体
class SRetParam_ReFluseLadderEnemy
	attr_accessor:eResult#(枚举类型：EArenaResult)请求刷将返回
	attr_accessor:vecFlushFigter#(SFlushFitherForClient的数组)最近刷的对手

	#构造函数
	def initialize
		@eResult = 0
		@vecFlushFigter = Array.new
	end
end

#函数[GetLadderAward:清求领取今日天梯奖励]的返回的参数组成的结构体
class SRetParam_GetLadderAward
	attr_accessor:eResult#(枚举类型：EArenaResult)请求刷将返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetArenaAward:清求领取今日历练奖励]的返回的参数组成的结构体
class SRetParam_GetArenaAward
	attr_accessor:eResult#(枚举类型：EArenaResult)请求刷将返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetLadderReport:清求战报]的返回的参数组成的结构体
class SRetParam_GetLadderReport
	attr_accessor:eResult#(枚举类型：EArenaResult)请求刷将返回
	attr_accessor:vecReport#(SLadderReport的数组)请求刷将返回

	#构造函数
	def initialize
		@eResult = 0
		@vecReport = Array.new
	end
end

#函数[LadderBattle:请求天梯挑战]的返回的参数组成的结构体
class SRetParam_LadderBattle
	attr_accessor:eResult#(枚举类型：EArenaResult)请求刷将返回
	attr_accessor:bySuc#(UINT8)0,失败，1成功
	attr_accessor:vecFlushFigter#(SFlushFitherForClient的数组)最近刷的对手
	attr_accessor:dwSelfRank#(UINT32)自己排名
	attr_accessor:dwLadderTimes#(UINT16)今日挑战天梯次数
	attr_accessor:dwLadderCDTimer#(UINT32)冷却时间戳
	attr_accessor:dwMinLadderRank#(UINT32)天梯最好排名,0表示无排名
	attr_accessor:dwLadderBuyTimes#(UINT32)购买的天梯挑战次数

	#构造函数
	def initialize
		@eResult = 0
		@bySuc = 0
		@vecFlushFigter = Array.new
		@dwSelfRank = 0
		@dwLadderTimes = 0
		@dwLadderCDTimer = 0
		@dwMinLadderRank = 0
		@dwLadderBuyTimes = 0
	end
end

#函数[LadderPageUpReq:请求天梯排名]的返回的参数组成的结构体
class SRetParam_LadderPageUpReq
	attr_accessor:eResult#(枚举类型：EArenaResult)查询结果
	attr_accessor:vecRankData#(SArenaRank2Client的数组)排行榜数据

	#构造函数
	def initialize
		@eResult = 0
		@vecRankData = Array.new
	end
end

#函数[ArenaBuyLadderTimes:请求购买天梯挑战次数]的返回的参数组成的结构体
class SRetParam_ArenaBuyLadderTimes
	attr_accessor:eResult#(枚举类型：EArenaResult)请求购买返回
	attr_accessor:dwLadderBuyTimesToday#(UINT32)今日购买天梯挑战次数
	attr_accessor:dwLadderBuyTimes#(UINT32)购买的天梯挑战次数

	#构造函数
	def initialize
		@eResult = 0
		@dwLadderBuyTimesToday = 0
		@dwLadderBuyTimes = 0
	end
end

#协议类：竞技场协议
class ArenaGSBase < ProtocolBase
	#以下为发送函数
	#发送：请求自己竞技场信息,同时开启竞技场
	def send_ArenaInfoReq(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求挑战
	def send_ArenaChallengeReq(
		qwDefense #(UINT64)被挑战者ID
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwDefense)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求购买挑战次数
	def send_ArenaByChallengeTimes(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求翻页
	def send_ArenaPageUpReq(
		eLevel,  #(枚举类型：EArenaLevel)段位
		dwRank,  #(UINT32)请求排名开始名次
		byNum #(UINT8)请求数量
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eLevel)
		ByteUtil::writeUINT32(data, dwRank)
		ByteUtil::writeUINT8(data, byNum)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求清除冷却
	def send_ArenaClearCDReq(
		byType #(UINT8)0,历练，1天梯
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byType)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求获取奖池奖励
	def send_ArenaGetRankingRewardReq(
		dwLootId,  #(UINT32)奖励包
		eType #(枚举类型：EArenaAwardType)奖励包类型
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwLootId)
		ByteUtil::writeUINT8(data, eType)
		return @svrHandler.sendPacket(data)
	end

	#发送：膜拜请求
	def send_ArenaWorship(
		qwRoleID #(UINT64)膜拜对象
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求刷将
	def send_FlushNewEnemy(
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求对手信息
	def send_GetAllEnemy(
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求奖励信息
	def send_GetAllAward(
	)
		sessionID = @sessionMgr.getNewSession(self, 10);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求膜拜信息
	def send_GetAllWirship(
	)
		sessionID = @sessionMgr.getNewSession(self, 11);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求计算:奖励信息
	def send_GetAllAwardInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 12);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求对手信息
	def send_ReFluseLadderEnemy(
		byType #(UINT8)0,默认刷对手，1顺次刷对手
	)
		sessionID = @sessionMgr.getNewSession(self, 13);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 13
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byType)
		return @svrHandler.sendPacket(data)
	end

	#发送：清求领取今日天梯奖励
	def send_GetLadderAward(
	)
		sessionID = @sessionMgr.getNewSession(self, 14);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 14
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：清求领取今日历练奖励
	def send_GetArenaAward(
	)
		sessionID = @sessionMgr.getNewSession(self, 15);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 15
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：清求战报
	def send_GetLadderReport(
	)
		sessionID = @sessionMgr.getNewSession(self, 16);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 16
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求天梯挑战
	def send_LadderBattle(
		qwEnemyID,  #(UINT64)对手ID
		dwEnemyRank #(UINT32)对手天梯排名
	)
		sessionID = @sessionMgr.getNewSession(self, 17);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 17
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwEnemyID)
		ByteUtil::writeUINT32(data, dwEnemyRank)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求天梯排名
	def send_LadderPageUpReq(
		dwRank,  #(UINT32)请求排名开始名次
		byNum #(UINT8)请求数量
	)
		sessionID = @sessionMgr.getNewSession(self, 18);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 18
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwRank)
		ByteUtil::writeUINT8(data, byNum)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求购买天梯挑战次数
	def send_ArenaBuyLadderTimes(
	)
		sessionID = @sessionMgr.getNewSession(self, 19);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 19
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：通告获得最好天梯排名
	def onRecv_UpdateLadderMinRank(
		dwLastRank, #(UINT32)前排名,0表示无排名
		dwNowRank #(UINT32)现排名
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：请求自己竞技场信息,同时开启竞技场
	def onReturn_ArenaInfoReq(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ArenaInfoReq)返回的参数
	)
	end

	#返回：请求挑战
	def onReturn_ArenaChallengeReq(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ArenaChallengeReq)返回的参数
	)
	end

	#返回：请求购买挑战次数
	def onReturn_ArenaByChallengeTimes(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ArenaByChallengeTimes)返回的参数
	)
	end

	#返回：请求翻页
	def onReturn_ArenaPageUpReq(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ArenaPageUpReq)返回的参数
	)
	end

	#返回：请求清除冷却
	def onReturn_ArenaClearCDReq(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ArenaClearCDReq)返回的参数
	)
	end

	#返回：请求获取奖池奖励
	def onReturn_ArenaGetRankingRewardReq(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ArenaGetRankingRewardReq)返回的参数
	)
	end

	#返回：膜拜请求
	def onReturn_ArenaWorship(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ArenaWorship)返回的参数
	)
	end

	#返回：请求刷将
	def onReturn_FlushNewEnemy(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FlushNewEnemy)返回的参数
	)
	end

	#返回：请求对手信息
	def onReturn_GetAllEnemy(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAllEnemy)返回的参数
	)
	end

	#返回：请求奖励信息
	def onReturn_GetAllAward(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAllAward)返回的参数
	)
	end

	#返回：请求膜拜信息
	def onReturn_GetAllWirship(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAllWirship)返回的参数
	)
	end

	#返回：请求计算:奖励信息
	def onReturn_GetAllAwardInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAllAwardInfo)返回的参数
	)
	end

	#返回：请求对手信息
	def onReturn_ReFluseLadderEnemy(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReFluseLadderEnemy)返回的参数
	)
	end

	#返回：清求领取今日天梯奖励
	def onReturn_GetLadderAward(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetLadderAward)返回的参数
	)
	end

	#返回：清求领取今日历练奖励
	def onReturn_GetArenaAward(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetArenaAward)返回的参数
	)
	end

	#返回：清求战报
	def onReturn_GetLadderReport(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetLadderReport)返回的参数
	)
	end

	#返回：请求天梯挑战
	def onReturn_LadderBattle(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LadderBattle)返回的参数
	)
	end

	#返回：请求天梯排名
	def onReturn_LadderPageUpReq(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LadderPageUpReq)返回的参数
	)
	end

	#返回：请求购买天梯挑战次数
	def onReturn_ArenaBuyLadderTimes(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ArenaBuyLadderTimes)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：通告获得最好天梯排名
	def _doRecv_UpdateLadderMinRank(data)
		dwLastRank = ByteUtil::readUINT32(data)
		dwNowRank = ByteUtil::readUINT32(data)
		return onRecv_UpdateLadderMinRank(dwLastRank, dwNowRank)
	end

#以下为返回处理函数
	#返回处理：请求自己竞技场信息,同时开启竞技场
	def _doReturn_ArenaInfoReq(data)
		retParam = SRetParam_ArenaInfoReq.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)结果提示
		stReturn = SArenaPlayerBaseData2Client::fromStream(data) #(类类型：SArenaPlayerBaseData2Client)返回的自己信息
		retParam.eResult = eResult
		retParam.stReturn = stReturn
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ArenaInfoReq(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求自己竞技场信息,同时开启竞技场
	def _onTimeOut_ArenaInfoReq(sessionID)
		retParam = SRetParam_ArenaInfoReq.new;
		onReturn_ArenaInfoReq(2, retParam)
	end

	#返回处理：请求挑战
	def _doReturn_ArenaChallengeReq(data)
		retParam = SRetParam_ArenaChallengeReq.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)请求挑战返回
		qwBattleID = ByteUtil::readUINT64(data) #(UINT64)战报ID
		bySuc = ByteUtil::readUINT8(data) #(UINT8)0,表示挑战失败，1表示挑战成功
		dwScore = ByteUtil::readUINT32(data) #(UINT32)当前积分
		dwRanking = ByteUtil::readUINT32(data) #(UINT32)当前排名
		wChallenge = ByteUtil::readUINT16(data) #(UINT16)今日挑战次数
		wChallengeBuyTimes = ByteUtil::readUINT16(data) #(UINT16)购买的挑战次数
		dwCDTimer = ByteUtil::readUINT32(data) #(UINT32)冷却时间戳
		retParam.eResult = eResult
		retParam.qwBattleID = qwBattleID
		retParam.bySuc = bySuc
		retParam.dwScore = dwScore
		retParam.dwRanking = dwRanking
		retParam.wChallenge = wChallenge
		retParam.wChallengeBuyTimes = wChallengeBuyTimes
		retParam.dwCDTimer = dwCDTimer
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ArenaChallengeReq(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求挑战
	def _onTimeOut_ArenaChallengeReq(sessionID)
		retParam = SRetParam_ArenaChallengeReq.new;
		onReturn_ArenaChallengeReq(2, retParam)
	end

	#返回处理：请求购买挑战次数
	def _doReturn_ArenaByChallengeTimes(data)
		retParam = SRetParam_ArenaByChallengeTimes.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)请求挑战返回
		wChallenge = ByteUtil::readUINT16(data) #(UINT16)今日挑战次数
		wChallengeBuyTimes = ByteUtil::readUINT16(data) #(UINT16)购买的挑战次数
		retParam.eResult = eResult
		retParam.wChallenge = wChallenge
		retParam.wChallengeBuyTimes = wChallengeBuyTimes
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ArenaByChallengeTimes(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求购买挑战次数
	def _onTimeOut_ArenaByChallengeTimes(sessionID)
		retParam = SRetParam_ArenaByChallengeTimes.new;
		onReturn_ArenaByChallengeTimes(2, retParam)
	end

	#返回处理：请求翻页
	def _doReturn_ArenaPageUpReq(data)
		retParam = SRetParam_ArenaPageUpReq.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)查询结果
		dwSize = ByteUtil::readUINT32(data) #(UINT32)本段位的人数总计
		vecRankData = SArenaRank2Client::vectorFromStream(data) #(SArenaRank2Client的数组)排行榜数据
		retParam.eResult = eResult
		retParam.dwSize = dwSize
		retParam.vecRankData = vecRankData
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ArenaPageUpReq(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求翻页
	def _onTimeOut_ArenaPageUpReq(sessionID)
		retParam = SRetParam_ArenaPageUpReq.new;
		onReturn_ArenaPageUpReq(2, retParam)
	end

	#返回处理：请求清除冷却
	def _doReturn_ArenaClearCDReq(data)
		retParam = SRetParam_ArenaClearCDReq.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)请求清除冷却返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ArenaClearCDReq(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求清除冷却
	def _onTimeOut_ArenaClearCDReq(sessionID)
		retParam = SRetParam_ArenaClearCDReq.new;
		onReturn_ArenaClearCDReq(2, retParam)
	end

	#返回处理：请求获取奖池奖励
	def _doReturn_ArenaGetRankingRewardReq(data)
		retParam = SRetParam_ArenaGetRankingRewardReq.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)请求获取奖池奖励返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ArenaGetRankingRewardReq(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求获取奖池奖励
	def _onTimeOut_ArenaGetRankingRewardReq(sessionID)
		retParam = SRetParam_ArenaGetRankingRewardReq.new;
		onReturn_ArenaGetRankingRewardReq(2, retParam)
	end

	#返回处理：膜拜请求
	def _doReturn_ArenaWorship(data)
		retParam = SRetParam_ArenaWorship.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)膜拜请求返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ArenaWorship(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：膜拜请求
	def _onTimeOut_ArenaWorship(sessionID)
		retParam = SRetParam_ArenaWorship.new;
		onReturn_ArenaWorship(2, retParam)
	end

	#返回处理：请求刷将
	def _doReturn_FlushNewEnemy(data)
		retParam = SRetParam_FlushNewEnemy.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)请求刷将返回
		wSelfReflush = ByteUtil::readUINT16(data) #(UINT16)当前购买刷新次数
		wSelfFreeReflush = ByteUtil::readUINT16(data) #(UINT16)当前VIP免费刷新次数
		retParam.eResult = eResult
		retParam.wSelfReflush = wSelfReflush
		retParam.wSelfFreeReflush = wSelfFreeReflush
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FlushNewEnemy(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求刷将
	def _onTimeOut_FlushNewEnemy(sessionID)
		retParam = SRetParam_FlushNewEnemy.new;
		onReturn_FlushNewEnemy(2, retParam)
	end

	#返回处理：请求对手信息
	def _doReturn_GetAllEnemy(data)
		retParam = SRetParam_GetAllEnemy.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)请求刷将返回
		vecFlushFigter = SFlushFitherForClient::vectorFromStream(data) #(SFlushFitherForClient的数组)最近刷的对手
		retParam.eResult = eResult
		retParam.vecFlushFigter = vecFlushFigter
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAllEnemy(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求对手信息
	def _onTimeOut_GetAllEnemy(sessionID)
		retParam = SRetParam_GetAllEnemy.new;
		onReturn_GetAllEnemy(2, retParam)
	end

	#返回处理：请求奖励信息
	def _doReturn_GetAllAward(data)
		retParam = SRetParam_GetAllAward.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)请求刷将返回
		vecAwards = SArenaAward::vectorFromStream(data) #(SArenaAward的数组)奖励包状态
		retParam.eResult = eResult
		retParam.vecAwards = vecAwards
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAllAward(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求奖励信息
	def _onTimeOut_GetAllAward(sessionID)
		retParam = SRetParam_GetAllAward.new;
		onReturn_GetAllAward(2, retParam)
	end

	#返回处理：请求膜拜信息
	def _doReturn_GetAllWirship(data)
		retParam = SRetParam_GetAllWirship.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)请求刷将返回
		vecWirshipFigter = SArenaRank2Client::vectorFromStream(data) #(SArenaRank2Client的数组)膜拜对象列表
		retParam.eResult = eResult
		retParam.vecWirshipFigter = vecWirshipFigter
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAllWirship(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求膜拜信息
	def _onTimeOut_GetAllWirship(sessionID)
		retParam = SRetParam_GetAllWirship.new;
		onReturn_GetAllWirship(2, retParam)
	end

	#返回处理：请求计算:奖励信息
	def _doReturn_GetAllAwardInfo(data)
		retParam = SRetParam_GetAllAwardInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)返回
		vecAwards = SArenaAward::vectorFromStream(data) #(SArenaAward的数组)奖励包状态
		retParam.eResult = eResult
		retParam.vecAwards = vecAwards
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAllAwardInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求计算:奖励信息
	def _onTimeOut_GetAllAwardInfo(sessionID)
		retParam = SRetParam_GetAllAwardInfo.new;
		onReturn_GetAllAwardInfo(2, retParam)
	end

	#返回处理：请求对手信息
	def _doReturn_ReFluseLadderEnemy(data)
		retParam = SRetParam_ReFluseLadderEnemy.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)请求刷将返回
		vecFlushFigter = SFlushFitherForClient::vectorFromStream(data) #(SFlushFitherForClient的数组)最近刷的对手
		retParam.eResult = eResult
		retParam.vecFlushFigter = vecFlushFigter
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReFluseLadderEnemy(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求对手信息
	def _onTimeOut_ReFluseLadderEnemy(sessionID)
		retParam = SRetParam_ReFluseLadderEnemy.new;
		onReturn_ReFluseLadderEnemy(2, retParam)
	end

	#返回处理：清求领取今日天梯奖励
	def _doReturn_GetLadderAward(data)
		retParam = SRetParam_GetLadderAward.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)请求刷将返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetLadderAward(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：清求领取今日天梯奖励
	def _onTimeOut_GetLadderAward(sessionID)
		retParam = SRetParam_GetLadderAward.new;
		onReturn_GetLadderAward(2, retParam)
	end

	#返回处理：清求领取今日历练奖励
	def _doReturn_GetArenaAward(data)
		retParam = SRetParam_GetArenaAward.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)请求刷将返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetArenaAward(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：清求领取今日历练奖励
	def _onTimeOut_GetArenaAward(sessionID)
		retParam = SRetParam_GetArenaAward.new;
		onReturn_GetArenaAward(2, retParam)
	end

	#返回处理：清求战报
	def _doReturn_GetLadderReport(data)
		retParam = SRetParam_GetLadderReport.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)请求刷将返回
		vecReport = SLadderReport::vectorFromStream(data) #(SLadderReport的数组)请求刷将返回
		retParam.eResult = eResult
		retParam.vecReport = vecReport
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetLadderReport(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：清求战报
	def _onTimeOut_GetLadderReport(sessionID)
		retParam = SRetParam_GetLadderReport.new;
		onReturn_GetLadderReport(2, retParam)
	end

	#返回处理：请求天梯挑战
	def _doReturn_LadderBattle(data)
		retParam = SRetParam_LadderBattle.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)请求刷将返回
		bySuc = ByteUtil::readUINT8(data) #(UINT8)0,失败，1成功
		vecFlushFigter = SFlushFitherForClient::vectorFromStream(data) #(SFlushFitherForClient的数组)最近刷的对手
		dwSelfRank = ByteUtil::readUINT32(data) #(UINT32)自己排名
		dwLadderTimes = ByteUtil::readUINT16(data) #(UINT16)今日挑战天梯次数
		dwLadderCDTimer = ByteUtil::readUINT32(data) #(UINT32)冷却时间戳
		dwMinLadderRank = ByteUtil::readUINT32(data) #(UINT32)天梯最好排名,0表示无排名
		dwLadderBuyTimes = ByteUtil::readUINT32(data) #(UINT32)购买的天梯挑战次数
		retParam.eResult = eResult
		retParam.bySuc = bySuc
		retParam.vecFlushFigter = vecFlushFigter
		retParam.dwSelfRank = dwSelfRank
		retParam.dwLadderTimes = dwLadderTimes
		retParam.dwLadderCDTimer = dwLadderCDTimer
		retParam.dwMinLadderRank = dwMinLadderRank
		retParam.dwLadderBuyTimes = dwLadderBuyTimes
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LadderBattle(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求天梯挑战
	def _onTimeOut_LadderBattle(sessionID)
		retParam = SRetParam_LadderBattle.new;
		onReturn_LadderBattle(2, retParam)
	end

	#返回处理：请求天梯排名
	def _doReturn_LadderPageUpReq(data)
		retParam = SRetParam_LadderPageUpReq.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)查询结果
		vecRankData = SArenaRank2Client::vectorFromStream(data) #(SArenaRank2Client的数组)排行榜数据
		retParam.eResult = eResult
		retParam.vecRankData = vecRankData
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LadderPageUpReq(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求天梯排名
	def _onTimeOut_LadderPageUpReq(sessionID)
		retParam = SRetParam_LadderPageUpReq.new;
		onReturn_LadderPageUpReq(2, retParam)
	end

	#返回处理：请求购买天梯挑战次数
	def _doReturn_ArenaBuyLadderTimes(data)
		retParam = SRetParam_ArenaBuyLadderTimes.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EArenaResult)请求购买返回
		dwLadderBuyTimesToday = ByteUtil::readUINT32(data) #(UINT32)今日购买天梯挑战次数
		dwLadderBuyTimes = ByteUtil::readUINT32(data) #(UINT32)购买的天梯挑战次数
		retParam.eResult = eResult
		retParam.dwLadderBuyTimesToday = dwLadderBuyTimesToday
		retParam.dwLadderBuyTimes = dwLadderBuyTimes
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ArenaBuyLadderTimes(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求购买天梯挑战次数
	def _onTimeOut_ArenaBuyLadderTimes(sessionID)
		retParam = SRetParam_ArenaBuyLadderTimes.new;
		onReturn_ArenaBuyLadderTimes(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 26;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_UpdateLadderMinRank' #FuncID: 1

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_ArenaInfoReq' #FuncID: 1
		@retFuncList[1] = '_doReturn_ArenaChallengeReq' #FuncID: 2
		@retFuncList[2] = '_doReturn_ArenaByChallengeTimes' #FuncID: 3
		@retFuncList[3] = '_doReturn_ArenaPageUpReq' #FuncID: 4
		@retFuncList[4] = '_doReturn_ArenaClearCDReq' #FuncID: 5
		@retFuncList[5] = '_doReturn_ArenaGetRankingRewardReq' #FuncID: 6
		@retFuncList[6] = '_doReturn_ArenaWorship' #FuncID: 7
		@retFuncList[7] = '_doReturn_FlushNewEnemy' #FuncID: 8
		@retFuncList[8] = '_doReturn_GetAllEnemy' #FuncID: 9
		@retFuncList[9] = '_doReturn_GetAllAward' #FuncID: 10
		@retFuncList[10] = '_doReturn_GetAllWirship' #FuncID: 11
		@retFuncList[11] = '_doReturn_GetAllAwardInfo' #FuncID: 12
		@retFuncList[12] = '_doReturn_ReFluseLadderEnemy' #FuncID: 13
		@retFuncList[13] = '_doReturn_GetLadderAward' #FuncID: 14
		@retFuncList[14] = '_doReturn_GetArenaAward' #FuncID: 15
		@retFuncList[15] = '_doReturn_GetLadderReport' #FuncID: 16
		@retFuncList[16] = '_doReturn_LadderBattle' #FuncID: 17
		@retFuncList[17] = '_doReturn_LadderPageUpReq' #FuncID: 18
		@retFuncList[18] = '_doReturn_ArenaBuyLadderTimes' #FuncID: 19

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_ArenaInfoReq' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_ArenaChallengeReq' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_ArenaByChallengeTimes' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_ArenaPageUpReq' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_ArenaClearCDReq' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_ArenaGetRankingRewardReq' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_ArenaWorship' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_FlushNewEnemy' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_GetAllEnemy' #FuncID: 9
		@timeFuncList[9] = '_onTimeOut_GetAllAward' #FuncID: 10
		@timeFuncList[10] = '_onTimeOut_GetAllWirship' #FuncID: 11
		@timeFuncList[11] = '_onTimeOut_GetAllAwardInfo' #FuncID: 12
		@timeFuncList[12] = '_onTimeOut_ReFluseLadderEnemy' #FuncID: 13
		@timeFuncList[13] = '_onTimeOut_GetLadderAward' #FuncID: 14
		@timeFuncList[14] = '_onTimeOut_GetArenaAward' #FuncID: 15
		@timeFuncList[15] = '_onTimeOut_GetLadderReport' #FuncID: 16
		@timeFuncList[16] = '_onTimeOut_LadderBattle' #FuncID: 17
		@timeFuncList[17] = '_onTimeOut_LadderPageUpReq' #FuncID: 18
		@timeFuncList[18] = '_onTimeOut_ArenaBuyLadderTimes' #FuncID: 19
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

