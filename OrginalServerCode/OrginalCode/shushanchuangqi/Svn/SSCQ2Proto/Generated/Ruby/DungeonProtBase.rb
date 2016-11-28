#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    DungeonProt.rb
#  Purpose:      副本相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ItemProtBase.rb'

#以下为类型定义

#副本结果
class EDungeonResult
	EDUNGEONSUCCESS = 0#成功
	EDUNGEONSWEEPINGERR = 1#正在扫荡中
	EDUNGEONPOWERERR = 2#体力不足
	EDUNGEONNOTSWEEPINGERR = 3#不在扫荡中
	EDUNGEONSWEEPINGSPEEDUPERR = 4#扫荡加速中
	EDUNGEONTYPENOTEXIST = 5#此副本类型不存在
	EDUNGEONINDGN = 6#你在副本中
	EDUNGEONLOWLEVEL = 7#你等级不够
	EDUNGEONCREATEERRTYPE = 8#副本类型不正确，不可以创建副本
	EDUNGEONPREDGNNOTFINISH = 9#前置副本未完成
	EDUNGEONPACKEMPTYMIN = 10#包裹空格子不足
	EDUNGEONOUTDGN = 11#你不在副本中
	EDUNGEONINSNOTEXIST = 12#副本不存在
	EDUNGEONNOTFINISH = 13#副本未完成
	EDUNGEONBUSY = 14#玩家忙
	EDUNGEONNOTSWEEPING = 15#不在扫荡状态
	ESPEEDUPITEMLIMIT = 16#加速道具不足
	EDUNGEONTIMESLIMIT = 17#进入次数不足
	EDUNGEONTIMESLIMITFORHERO = 18#英雄本进入次数不足
	EDUNGEONTIMESLIMITFORLIXIAN = 19#历险本进入次数不足
	EDUNGEONVIPBUYHERO = 20#购买英雄副本vip等级不足
	EDUNGEONVIPBUYLIXIAN = 21#购买历险副本vip等级不足
	EDUNGEONNOGOLD = 22#仙石不足
	EDUNGEONOTHERERR = 23#未知错误
end

#副本类型
class EDgnType
	ENONEDGN = 0#无定义
	EPLAYERDGN = 1#单人副本
	EGATHERDGN = 2#采集副本
	ETEAMDGN = 3#组队副本
	EDEMONTOWERDGN = 4#镇妖塔副本
end

#副本次类型
class EDgnSubType
	ESUBCOMMON = 0#普通
	ESUBHERO = 1#英雄副本
	ESUBHISTORY = 2#史诗副本
	ESUBLIXIAN = 3#历险副本
end

#条件状态
class EDgnCondStatus
	ECONDRUN = 0#未达成
	ECONDSUC = 1#已达成
	ECONDFAL = 2#已失败
end

#副本评价
class ELogicType
	ELOGICNONE = 0#无评价
	ELOGICORDERMONSTER = 1#按顺序杀怪
end

#结构体：DgnSucCond的继承体系类型
class EType_DgnSucCond
	ETYPE_DGNSUCCOND = 0#类型：DgnSucCond
	ETYPE_SUCMONSTER = 1#类型：SucMonster
	ETYPE_SUCGATHER = 2#类型：SucGather
	ETYPE_SUCTURNS = 3#类型：SucTurns
	ETYPE_SUCINTIMER = 4#类型：SucInTimer
	ETYPE_SUCMONSTERINTIMER = 5#类型：SucMonsterInTimer
	ETYPE_SUCGATHERINTIMER = 6#类型：SucGatherInTimer
	ETYPE_SUCFIGHTWITHMONSTERMINTIMES = 7#类型：SucFightWithMonsterMinTimes
	ETYPE_SUCARRIVEAREA = 8#类型：SucArriveArea
end

#副本条件
class DgnSucCond
	attr_accessor:wCondId #(UINT16)条件ID
	attr_accessor:eStatus #(枚举类型：EDgnCondStatus)0,未达成，1表示已达成，2表示已失败

	#构造函数
	def initialize
		@wCondId = 0
		@eStatus = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_DgnSucCond::ETYPE_DGNSUCCOND
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wCondId = @wCondId
		obj.eStatus = @eStatus
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = DgnSucCond.new
		s.wCondId = ByteUtil::readUINT16(data)
		s.eStatus = ByteUtil::readUINT8(data)
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_DgnSucCond::ETYPE_DGNSUCCOND
				s = DgnSucCond::fromStream(data)
			when EType_DgnSucCond::ETYPE_SUCMONSTER
				s = SucMonster::fromStream(data)
			when EType_DgnSucCond::ETYPE_SUCGATHER
				s = SucGather::fromStream(data)
			when EType_DgnSucCond::ETYPE_SUCTURNS
				s = SucTurns::fromStream(data)
			when EType_DgnSucCond::ETYPE_SUCINTIMER
				s = SucInTimer::fromStream(data)
			when EType_DgnSucCond::ETYPE_SUCMONSTERINTIMER
				s = SucMonsterInTimer::fromStream(data)
			when EType_DgnSucCond::ETYPE_SUCGATHERINTIMER
				s = SucGatherInTimer::fromStream(data)
			when EType_DgnSucCond::ETYPE_SUCFIGHTWITHMONSTERMINTIMES
				s = SucFightWithMonsterMinTimes::fromStream(data)
			when EType_DgnSucCond::ETYPE_SUCARRIVEAREA
				s = SucArriveArea::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = DgnSucCond::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = DgnSucCond::superFromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wCondId)
		ByteUtil::writeUINT8(data, @eStatus)
	end

	def superToStream(data)
		eType = getClassType()
		ByteUtil::writeUINT8(data, eType)
		toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end

	def self.superVectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.superToStream(data)
		end
	end
end

#杀怪条件
class SucMonster < DgnSucCond
	attr_accessor:wMonsterGroup #(UINT16)怪物组ID
	attr_accessor:byTotalNum #(UINT8)怪物总数
	attr_accessor:byCurNum #(UINT8)当前数量

	#构造函数
	def initialize
		super()
		@wMonsterGroup = 0
		@byTotalNum = 0
		@byCurNum = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_DgnSucCond::ETYPE_SUCMONSTER
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wMonsterGroup = @wMonsterGroup
		obj.byTotalNum = @byTotalNum
		obj.byCurNum = @byCurNum
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SucMonster.new
		base = DgnSucCond::fromStream(data)
		base.copyTo(s)
		s.wMonsterGroup = ByteUtil::readUINT16(data)
		s.byTotalNum = ByteUtil::readUINT8(data)
		s.byCurNum = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SucMonster::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wMonsterGroup)
		ByteUtil::writeUINT8(data, @byTotalNum)
		ByteUtil::writeUINT8(data, @byCurNum)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#采集条件
class SucGather < DgnSucCond
	attr_accessor:wGather #(UINT16)采集ID
	attr_accessor:byTotalNum #(UINT8)采集总数
	attr_accessor:byCurNum #(UINT8)当前数量

	#构造函数
	def initialize
		super()
		@wGather = 0
		@byTotalNum = 0
		@byCurNum = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_DgnSucCond::ETYPE_SUCGATHER
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wGather = @wGather
		obj.byTotalNum = @byTotalNum
		obj.byCurNum = @byCurNum
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SucGather.new
		base = DgnSucCond::fromStream(data)
		base.copyTo(s)
		s.wGather = ByteUtil::readUINT16(data)
		s.byTotalNum = ByteUtil::readUINT8(data)
		s.byCurNum = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SucGather::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wGather)
		ByteUtil::writeUINT8(data, @byTotalNum)
		ByteUtil::writeUINT8(data, @byCurNum)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#回合数判定
class SucTurns < DgnSucCond
	attr_accessor:byTotalTurns #(UINT8)总回合数
	attr_accessor:byCurTurns #(UINT8)当前回合数

	#构造函数
	def initialize
		super()
		@byTotalTurns = 0
		@byCurTurns = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_DgnSucCond::ETYPE_SUCTURNS
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.byTotalTurns = @byTotalTurns
		obj.byCurTurns = @byCurTurns
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SucTurns.new
		base = DgnSucCond::fromStream(data)
		base.copyTo(s)
		s.byTotalTurns = ByteUtil::readUINT8(data)
		s.byCurTurns = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SucTurns::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @byTotalTurns)
		ByteUtil::writeUINT8(data, @byCurTurns)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#时间判定
class SucInTimer < DgnSucCond
	attr_accessor:dwTotalTimer #(UINT32)总计时间
	attr_accessor:dwBeginTimer #(UINT32)起始时间

	#构造函数
	def initialize
		super()
		@dwTotalTimer = 0
		@dwBeginTimer = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_DgnSucCond::ETYPE_SUCINTIMER
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwTotalTimer = @dwTotalTimer
		obj.dwBeginTimer = @dwBeginTimer
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SucInTimer.new
		base = DgnSucCond::fromStream(data)
		base.copyTo(s)
		s.dwTotalTimer = ByteUtil::readUINT32(data)
		s.dwBeginTimer = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SucInTimer::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwTotalTimer)
		ByteUtil::writeUINT32(data, @dwBeginTimer)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#定时杀怪
class SucMonsterInTimer < DgnSucCond
	attr_accessor:dwTotalTimer #(UINT32)总计时间
	attr_accessor:dwBeginTimer #(UINT32)起始时间
	attr_accessor:wMonsterGroup #(UINT16)怪物组ID
	attr_accessor:byTotalNum #(UINT8)怪物总数
	attr_accessor:byCurNum #(UINT8)当前数量

	#构造函数
	def initialize
		super()
		@dwTotalTimer = 0
		@dwBeginTimer = 0
		@wMonsterGroup = 0
		@byTotalNum = 0
		@byCurNum = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_DgnSucCond::ETYPE_SUCMONSTERINTIMER
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwTotalTimer = @dwTotalTimer
		obj.dwBeginTimer = @dwBeginTimer
		obj.wMonsterGroup = @wMonsterGroup
		obj.byTotalNum = @byTotalNum
		obj.byCurNum = @byCurNum
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SucMonsterInTimer.new
		base = DgnSucCond::fromStream(data)
		base.copyTo(s)
		s.dwTotalTimer = ByteUtil::readUINT32(data)
		s.dwBeginTimer = ByteUtil::readUINT32(data)
		s.wMonsterGroup = ByteUtil::readUINT16(data)
		s.byTotalNum = ByteUtil::readUINT8(data)
		s.byCurNum = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SucMonsterInTimer::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwTotalTimer)
		ByteUtil::writeUINT32(data, @dwBeginTimer)
		ByteUtil::writeUINT16(data, @wMonsterGroup)
		ByteUtil::writeUINT8(data, @byTotalNum)
		ByteUtil::writeUINT8(data, @byCurNum)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#定时采集
class SucGatherInTimer < DgnSucCond
	attr_accessor:dwTotalTimer #(UINT32)总计时间
	attr_accessor:dwBeginTimer #(UINT32)起始时间
	attr_accessor:wGather #(UINT16)采集ID
	attr_accessor:byTotalNum #(UINT8)采集总数
	attr_accessor:byCurNum #(UINT8)当前数量

	#构造函数
	def initialize
		super()
		@dwTotalTimer = 0
		@dwBeginTimer = 0
		@wGather = 0
		@byTotalNum = 0
		@byCurNum = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_DgnSucCond::ETYPE_SUCGATHERINTIMER
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwTotalTimer = @dwTotalTimer
		obj.dwBeginTimer = @dwBeginTimer
		obj.wGather = @wGather
		obj.byTotalNum = @byTotalNum
		obj.byCurNum = @byCurNum
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SucGatherInTimer.new
		base = DgnSucCond::fromStream(data)
		base.copyTo(s)
		s.dwTotalTimer = ByteUtil::readUINT32(data)
		s.dwBeginTimer = ByteUtil::readUINT32(data)
		s.wGather = ByteUtil::readUINT16(data)
		s.byTotalNum = ByteUtil::readUINT8(data)
		s.byCurNum = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SucGatherInTimer::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwTotalTimer)
		ByteUtil::writeUINT32(data, @dwBeginTimer)
		ByteUtil::writeUINT16(data, @wGather)
		ByteUtil::writeUINT8(data, @byTotalNum)
		ByteUtil::writeUINT8(data, @byCurNum)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#尽量不和怪物发生战斗
class SucFightWithMonsterMinTimes < DgnSucCond
	attr_accessor:wGroup #(UINT16)怪物
	attr_accessor:byTotalTimes #(UINT8)总战斗次数
	attr_accessor:byCurTimes #(UINT8)当前战斗次数

	#构造函数
	def initialize
		super()
		@wGroup = 0
		@byTotalTimes = 0
		@byCurTimes = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_DgnSucCond::ETYPE_SUCFIGHTWITHMONSTERMINTIMES
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wGroup = @wGroup
		obj.byTotalTimes = @byTotalTimes
		obj.byCurTimes = @byCurTimes
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SucFightWithMonsterMinTimes.new
		base = DgnSucCond::fromStream(data)
		base.copyTo(s)
		s.wGroup = ByteUtil::readUINT16(data)
		s.byTotalTimes = ByteUtil::readUINT8(data)
		s.byCurTimes = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SucFightWithMonsterMinTimes::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wGroup)
		ByteUtil::writeUINT8(data, @byTotalTimes)
		ByteUtil::writeUINT8(data, @byCurTimes)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#到达某个区域
class SucArriveArea < DgnSucCond
	attr_accessor:wAreaID #(UINT16)区域ID

	#构造函数
	def initialize
		super()
		@wAreaID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_DgnSucCond::ETYPE_SUCARRIVEAREA
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wAreaID = @wAreaID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SucArriveArea.new
		base = DgnSucCond::fromStream(data)
		base.copyTo(s)
		s.wAreaID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SucArriveArea::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wAreaID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#多重条件信息
class MulCond
	attr_accessor:vecCond #(DgnSucCond的数组)多重条件

	#构造函数
	def initialize
		@vecCond = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.vecCond = @vecCond
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = MulCond.new
		s.vecCond = DgnSucCond::superVectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = MulCond::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		DgnSucCond::superVectorToStream(data, @vecCond)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#副本星级信息
class DgnStar
	attr_accessor:wDgnId #(UINT16)副本ID
	attr_accessor:byStar #(UINT8)星级
	attr_accessor:dwFinishTimesToday #(UINT32)今日完成次数
	attr_accessor:dwBuyTimesToday #(UINT32)今日购买次数
	attr_accessor:dwBuyTimes #(UINT32)购买的总次数
	attr_accessor:dwCompleteTimes #(UINT32)总通关次数

	#构造函数
	def initialize
		@wDgnId = 0
		@byStar = 0
		@dwFinishTimesToday = 0
		@dwBuyTimesToday = 0
		@dwBuyTimes = 0
		@dwCompleteTimes = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wDgnId = @wDgnId
		obj.byStar = @byStar
		obj.dwFinishTimesToday = @dwFinishTimesToday
		obj.dwBuyTimesToday = @dwBuyTimesToday
		obj.dwBuyTimes = @dwBuyTimes
		obj.dwCompleteTimes = @dwCompleteTimes
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = DgnStar.new
		s.wDgnId = ByteUtil::readUINT16(data)
		s.byStar = ByteUtil::readUINT8(data)
		s.dwFinishTimesToday = ByteUtil::readUINT32(data)
		s.dwBuyTimesToday = ByteUtil::readUINT32(data)
		s.dwBuyTimes = ByteUtil::readUINT32(data)
		s.dwCompleteTimes = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = DgnStar::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wDgnId)
		ByteUtil::writeUINT8(data, @byStar)
		ByteUtil::writeUINT32(data, @dwFinishTimesToday)
		ByteUtil::writeUINT32(data, @dwBuyTimesToday)
		ByteUtil::writeUINT32(data, @dwBuyTimes)
		ByteUtil::writeUINT32(data, @dwCompleteTimes)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#历险副本信息
class DgnLiXian
	attr_accessor:dwFinishTimesToday #(UINT32)今日完成次数
	attr_accessor:dwBuyTimesToday #(UINT32)今日购买次数
	attr_accessor:dwBuyTimes #(UINT32)购买的总次数

	#构造函数
	def initialize
		@dwFinishTimesToday = 0
		@dwBuyTimesToday = 0
		@dwBuyTimes = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwFinishTimesToday = @dwFinishTimesToday
		obj.dwBuyTimesToday = @dwBuyTimesToday
		obj.dwBuyTimes = @dwBuyTimes
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = DgnLiXian.new
		s.dwFinishTimesToday = ByteUtil::readUINT32(data)
		s.dwBuyTimesToday = ByteUtil::readUINT32(data)
		s.dwBuyTimes = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = DgnLiXian::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwFinishTimesToday)
		ByteUtil::writeUINT32(data, @dwBuyTimesToday)
		ByteUtil::writeUINT32(data, @dwBuyTimes)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#扫荡信息
class SSweepInfo
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:wCurDgnID #(UINT16)当前扫荡副本
	attr_accessor:wCurCount #(UINT16)当前剩余扫荡次数
	attr_accessor:dwReserverTime #(UINT32)下次扫荡剩余时间
	attr_accessor:dwSaveTime #(UINT32)保存时间
	attr_accessor:wOptions #(UINT16)扫荡类型
	attr_accessor:wCount #(UINT16)扫荡需求次数
	attr_accessor:strVecDgn #(string)未开始扫荡副本

	#构造函数
	def initialize
		@qwRoleID = 0
		@wCurDgnID = 0
		@wCurCount = 0
		@dwReserverTime = 0
		@dwSaveTime = 0
		@wOptions = 0
		@wCount = 0
		@strVecDgn = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wCurDgnID = @wCurDgnID
		obj.wCurCount = @wCurCount
		obj.dwReserverTime = @dwReserverTime
		obj.dwSaveTime = @dwSaveTime
		obj.wOptions = @wOptions
		obj.wCount = @wCount
		obj.strVecDgn = @strVecDgn
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSweepInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wCurDgnID = ByteUtil::readUINT16(data)
		s.wCurCount = ByteUtil::readUINT16(data)
		s.dwReserverTime = ByteUtil::readUINT32(data)
		s.dwSaveTime = ByteUtil::readUINT32(data)
		s.wOptions = ByteUtil::readUINT16(data)
		s.wCount = ByteUtil::readUINT16(data)
		s.strVecDgn = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSweepInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wCurDgnID)
		ByteUtil::writeUINT16(data, @wCurCount)
		ByteUtil::writeUINT32(data, @dwReserverTime)
		ByteUtil::writeUINT32(data, @dwSaveTime)
		ByteUtil::writeUINT16(data, @wOptions)
		ByteUtil::writeUINT16(data, @wCount)
		ByteUtil::writeSTRING(data, @strVecDgn)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#扫荡日志信息
class SSweepItem
	attr_accessor:wTurn #(UINT16)当前扫荡轮数
	attr_accessor:vecItemGenInfo #(SItemGenInfo的数组)获得物品
	attr_accessor:vecResource #(SResource的数组)获得资源

	#构造函数
	def initialize
		@wTurn = 0
		@vecItemGenInfo = Array.new
		@vecResource = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wTurn = @wTurn
		obj.vecItemGenInfo = @vecItemGenInfo
		obj.vecResource = @vecResource
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSweepItem.new
		s.wTurn = ByteUtil::readUINT16(data)
		s.vecItemGenInfo = SItemGenInfo::vectorFromStream(data)
		s.vecResource = SResource::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSweepItem::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wTurn)
		SItemGenInfo::vectorToStream(data, @vecItemGenInfo)
		SResource::vectorToStream(data, @vecResource)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#客户段获取的扫荡信息
class SGetSweepInfo
	attr_accessor:wDgnId #(UINT16)扫荡副本实例
	attr_accessor:dwReserverTimer #(UINT32)剩余时间
	attr_accessor:wCount #(UINT16)剩余次数
	attr_accessor:wMaxCount #(UINT16)总的扫荡次数
	attr_accessor:vecSweepItem #(SSweepItem的数组)扫荡日志

	#构造函数
	def initialize
		@wDgnId = 0
		@dwReserverTimer = 0
		@wCount = 0
		@wMaxCount = 0
		@vecSweepItem = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wDgnId = @wDgnId
		obj.dwReserverTimer = @dwReserverTimer
		obj.wCount = @wCount
		obj.wMaxCount = @wMaxCount
		obj.vecSweepItem = @vecSweepItem
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGetSweepInfo.new
		s.wDgnId = ByteUtil::readUINT16(data)
		s.dwReserverTimer = ByteUtil::readUINT32(data)
		s.wCount = ByteUtil::readUINT16(data)
		s.wMaxCount = ByteUtil::readUINT16(data)
		s.vecSweepItem = SSweepItem::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGetSweepInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wDgnId)
		ByteUtil::writeUINT32(data, @dwReserverTimer)
		ByteUtil::writeUINT16(data, @wCount)
		ByteUtil::writeUINT16(data, @wMaxCount)
		SSweepItem::vectorToStream(data, @vecSweepItem)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#组队副本领奖记录
class TeamAwardRecord
	attr_accessor:wDgnType #(UINT16)副本模板
	attr_accessor:byAwardTimes #(UINT8)今日领奖次数

	#构造函数
	def initialize
		@wDgnType = 0
		@byAwardTimes = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wDgnType = @wDgnType
		obj.byAwardTimes = @byAwardTimes
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = TeamAwardRecord.new
		s.wDgnType = ByteUtil::readUINT16(data)
		s.byAwardTimes = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = TeamAwardRecord::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wDgnType)
		ByteUtil::writeUINT8(data, @byAwardTimes)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#组队副本总领奖记录
class TeamAwardAllRecord
	attr_accessor:byAwardTimesToday #(UINT8)今日领奖次数
	attr_accessor:vecDgn #(TeamAwardRecord的数组)每个副本领奖次数

	#构造函数
	def initialize
		@byAwardTimesToday = 0
		@vecDgn = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byAwardTimesToday = @byAwardTimesToday
		obj.vecDgn = @vecDgn
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = TeamAwardAllRecord.new
		s.byAwardTimesToday = ByteUtil::readUINT8(data)
		s.vecDgn = TeamAwardRecord::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = TeamAwardAllRecord::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byAwardTimesToday)
		TeamAwardRecord::vectorToStream(data, @vecDgn)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[Sweeping:扫荡]的原来的参数组成的结构体
class SOrigParam_Sweeping
	attr_accessor:wDgnID #(UINT16)副本ID
	attr_accessor:wCount #(UINT16)次数

	#构造函数
	def initialize
		@wDgnID = 0
		@wCount = 0
	end
end

#函数[Sweeping:扫荡]的返回的参数组成的结构体
class SRetParam_Sweeping
	attr_accessor:eResult#(枚举类型：EDungeonResult)扫荡结果
	attr_accessor:dwSweepEndTime#(UINT32)扫荡结束时间

	#构造函数
	def initialize
		@eResult = 0
		@dwSweepEndTime = 0
	end
end

#函数[SweepingSpeedUp:加速扫荡]的返回的参数组成的结构体
class SRetParam_SweepingSpeedUp
	attr_accessor:eResult#(枚举类型：EDungeonResult)加速扫荡结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[CancelSweeping:取消扫荡]的返回的参数组成的结构体
class SRetParam_CancelSweeping
	attr_accessor:eResult#(枚举类型：EDungeonResult)取消扫荡结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[EnterPlayerDungeon:]的返回的参数组成的结构体
class SRetParam_EnterPlayerDungeon
	attr_accessor:eResult#(枚举类型：EDungeonResult)服务器返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[LeavePlayerDungeon:离开单人副本]的返回的参数组成的结构体
class SRetParam_LeavePlayerDungeon
	attr_accessor:eResult#(枚举类型：EDungeonResult)服务器返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[NotifyAcceptDgnAward:客户端确认领奖]的返回的参数组成的结构体
class SRetParam_NotifyAcceptDgnAward
	attr_accessor:eResult#(枚举类型：EDungeonResult)服务器返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetAllDgnInfo:查询副本星级]的返回的参数组成的结构体
class SRetParam_GetAllDgnInfo
	attr_accessor:sLiXian#(类类型：DgnLiXian)历险副本信息
	attr_accessor:vecStar#(DgnStar的数组)副本星级

	#构造函数
	def initialize
		@sLiXian = DgnLiXian.new
		@vecStar = Array.new
	end
end

#函数[GetDgnSweepingInfo:客户端查询扫荡信息]的返回的参数组成的结构体
class SRetParam_GetDgnSweepingInfo
	attr_accessor:oGetSweepInfo#(类类型：SGetSweepInfo)扫荡信息

	#构造函数
	def initialize
		@oGetSweepInfo = SGetSweepInfo.new
	end
end

#函数[BuyHeroDgnTimes:购买英雄副本次数]的返回的参数组成的结构体
class SRetParam_BuyHeroDgnTimes
	attr_accessor:eResult#(枚举类型：EDungeonResult)服务器返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[BuyLiXianDgnTimes:购买历险副本次数]的返回的参数组成的结构体
class SRetParam_BuyLiXianDgnTimes
	attr_accessor:eResult#(枚举类型：EDungeonResult)服务器返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetDgnStarAwardInfo:查询副本星级领奖状态]的返回的参数组成的结构体
class SRetParam_GetDgnStarAwardInfo
	attr_accessor:vecAward#(UINT16数组)副本星级已领奖ID

	#构造函数
	def initialize
		@vecAward = Array.new
	end
end

#函数[GetDgnStarAward:领取副本星级奖励]的返回的参数组成的结构体
class SRetParam_GetDgnStarAward
	attr_accessor:eResult#(枚举类型：EDungeonResult)服务器返回结果
	attr_accessor:vecAward#(UINT16数组)副本星级已领奖ID

	#构造函数
	def initialize
		@eResult = 0
		@vecAward = Array.new
	end
end

#协议类：副本相关协议
class DungeonProtBase < ProtocolBase
	#以下为发送函数
	#发送：扫荡
	def send_Sweeping(
		wDgnID,  #(UINT16)副本ID
		wCount,  #(UINT16)次数
		byOptions #(UINT8)选项, 1位为gold，2位为key,采集相关
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		origParam = SOrigParam_Sweeping.new
		origParam.wDgnID = wDgnID
		origParam.wCount = wCount
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wDgnID)
		ByteUtil::writeUINT16(data, wCount)
		ByteUtil::writeUINT8(data, byOptions)
		return @svrHandler.sendPacket(data)
	end

	#发送：加速扫荡
	def send_SweepingSpeedUp(
		byOptions #(UINT8)0为使用仙石
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byOptions)
		return @svrHandler.sendPacket(data)
	end

	#发送：取消扫荡
	def send_CancelSweeping(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：
	def send_EnterPlayerDungeon(
		wDgnID #(UINT16)副本ID
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wDgnID)
		return @svrHandler.sendPacket(data)
	end

	#发送：离开单人副本
	def send_LeavePlayerDungeon(
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：客户端确认领奖
	def send_NotifyAcceptDgnAward(
		qwDgnID #(UINT64)副本唯一实例ID
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwDgnID)
		return @svrHandler.sendPacket(data)
	end

	#发送：查询副本星级
	def send_GetAllDgnInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：客户端查询扫荡信息
	def send_GetDgnSweepingInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：查询副本进度和星级
	def send_GetDgnProcessAndStar(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：副本中玩家复活
	def send_ReliveInDgn(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取组队副本信息
	def send_GetTeamInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：购买英雄副本次数
	def send_BuyHeroDgnTimes(
		wDgnID #(UINT16)副本ID
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wDgnID)
		return @svrHandler.sendPacket(data)
	end

	#发送：购买历险副本次数
	def send_BuyLiXianDgnTimes(
	)
		sessionID = @sessionMgr.getNewSession(self, 10);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 13
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：查询副本星级领奖状态
	def send_GetDgnStarAwardInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 11);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 14
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：领取副本星级奖励
	def send_GetDgnStarAward(
		wStarID #(UINT16)领奖ID
	)
		sessionID = @sessionMgr.getNewSession(self, 12);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 15
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wStarID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：扫荡更新通知
	def onRecv_SweepingUpdateNotify(
		vecItem, #(SItemGenInfo的数组)获得物品
		vecResSource, #(SResource的数组)获得资源
		wCurrCount, #(UINT16)当前次数
		dwSweepEndTime #(UINT32)扫荡结束时间
	)
		raise NotImplementedError
	end
	#接收：扫荡结束通知
	def onRecv_SweepingEndNotify(
		eResult #(枚举类型：EDungeonResult)服务器返回结果
	)
		raise NotImplementedError
	end
	#接收：副本地图怪物采集物索引通知
	def onRecv_DungeonMapIdxNotify(
		vecIdx #(UINT8数组)索引ID
	)
		raise NotImplementedError
	end
	#接收：通知通关副本领奖
	def onRecv_NotifyDgnAward(
		qwDgnId, #(UINT64)副本唯一实例
		wDgnType, #(UINT16)副本类型
		qwLastBattleID, #(UINT64)最后战报
		byStar, #(UINT8)战斗评级
		vecItem, #(SItemGenInfo的数组)获得物品
		vecResSource #(SResource的数组)获得资源
	)
		raise NotImplementedError
	end
	#接收：通告副本进程
	def onRecv_NotifyDgnProcess(
		wDgnType, #(UINT16)副本类型
		vecProcess #(MulCond的数组)副本进度
	)
		raise NotImplementedError
	end
	#接收：通告副本星级
	def onRecv_NotifyDgnStar(
		wDgnType, #(UINT16)副本类型
		vecStar #(MulCond的数组)副本星级
	)
		raise NotImplementedError
	end
	#接收：同步领奖记录
	def onRecv_SynTeamAwardRecord(
		stAward #(类类型：TeamAwardAllRecord)同步数据
	)
		raise NotImplementedError
	end
	#接收：队伍战斗结果
	def onRecv_TeamBattleResult(
		DgnType, #(UINT16)副本类型
		bySuc #(UINT8)0,失败，1成功
	)
		raise NotImplementedError
	end
	#接收：更新历险副本信息
	def onRecv_UpdateLiXian(
		sLiXian #(类类型：DgnLiXian)历险副本信息
	)
		raise NotImplementedError
	end
	#接收：更新单个副本信息
	def onRecv_UpdateDgnInfo(
		sDgnStar #(类类型：DgnStar)副本信息
	)
		raise NotImplementedError
	end
	#接收：更新所有副本信息
	def onRecv_UpdateDgnInfoForAll(
		sLiXian, #(类类型：DgnLiXian)历险副本信息
		vecStar #(DgnStar的数组)副本星级
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：扫荡
	def onReturn_Sweeping(
		ret, #0为成功，1为失败，2为超时
		origParam, #(类类型：SOrigParam_Sweeping)原来的参数
		retParam #(类类型：SRetParam_Sweeping)返回的参数
	)
	end

	#返回：加速扫荡
	def onReturn_SweepingSpeedUp(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SweepingSpeedUp)返回的参数
	)
	end

	#返回：取消扫荡
	def onReturn_CancelSweeping(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_CancelSweeping)返回的参数
	)
	end

	#返回：
	def onReturn_EnterPlayerDungeon(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_EnterPlayerDungeon)返回的参数
	)
	end

	#返回：离开单人副本
	def onReturn_LeavePlayerDungeon(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LeavePlayerDungeon)返回的参数
	)
	end

	#返回：客户端确认领奖
	def onReturn_NotifyAcceptDgnAward(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_NotifyAcceptDgnAward)返回的参数
	)
	end

	#返回：查询副本星级
	def onReturn_GetAllDgnInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAllDgnInfo)返回的参数
	)
	end

	#返回：客户端查询扫荡信息
	def onReturn_GetDgnSweepingInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetDgnSweepingInfo)返回的参数
	)
	end

	#返回：购买英雄副本次数
	def onReturn_BuyHeroDgnTimes(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuyHeroDgnTimes)返回的参数
	)
	end

	#返回：购买历险副本次数
	def onReturn_BuyLiXianDgnTimes(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuyLiXianDgnTimes)返回的参数
	)
	end

	#返回：查询副本星级领奖状态
	def onReturn_GetDgnStarAwardInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetDgnStarAwardInfo)返回的参数
	)
	end

	#返回：领取副本星级奖励
	def onReturn_GetDgnStarAward(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetDgnStarAward)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：扫荡更新通知
	def _doRecv_SweepingUpdateNotify(data)
		vecItem = SItemGenInfo::vectorFromStream(data)
		vecResSource = SResource::vectorFromStream(data)
		wCurrCount = ByteUtil::readUINT16(data)
		dwSweepEndTime = ByteUtil::readUINT32(data)
		return onRecv_SweepingUpdateNotify(vecItem, vecResSource, wCurrCount, dwSweepEndTime)
	end

	#接收处理：扫荡结束通知
	def _doRecv_SweepingEndNotify(data)
		eResult = ByteUtil::readUINT8(data)
		return onRecv_SweepingEndNotify(eResult)
	end

	#接收处理：副本地图怪物采集物索引通知
	def _doRecv_DungeonMapIdxNotify(data)
		vecIdx = ByteUtil::readVecUINT8(data)
		return onRecv_DungeonMapIdxNotify(vecIdx)
	end

	#接收处理：通知通关副本领奖
	def _doRecv_NotifyDgnAward(data)
		qwDgnId = ByteUtil::readUINT64(data)
		wDgnType = ByteUtil::readUINT16(data)
		qwLastBattleID = ByteUtil::readUINT64(data)
		byStar = ByteUtil::readUINT8(data)
		vecItem = SItemGenInfo::vectorFromStream(data)
		vecResSource = SResource::vectorFromStream(data)
		return onRecv_NotifyDgnAward(qwDgnId, wDgnType, qwLastBattleID, byStar, vecItem, vecResSource)
	end

	#接收处理：通告副本进程
	def _doRecv_NotifyDgnProcess(data)
		wDgnType = ByteUtil::readUINT16(data)
		vecProcess = MulCond::vectorFromStream(data)
		return onRecv_NotifyDgnProcess(wDgnType, vecProcess)
	end

	#接收处理：通告副本星级
	def _doRecv_NotifyDgnStar(data)
		wDgnType = ByteUtil::readUINT16(data)
		vecStar = MulCond::vectorFromStream(data)
		return onRecv_NotifyDgnStar(wDgnType, vecStar)
	end

	#接收处理：同步领奖记录
	def _doRecv_SynTeamAwardRecord(data)
		stAward = TeamAwardAllRecord::fromStream(data)
		return onRecv_SynTeamAwardRecord(stAward)
	end

	#接收处理：队伍战斗结果
	def _doRecv_TeamBattleResult(data)
		DgnType = ByteUtil::readUINT16(data)
		bySuc = ByteUtil::readUINT8(data)
		return onRecv_TeamBattleResult(DgnType, bySuc)
	end

	#接收处理：更新历险副本信息
	def _doRecv_UpdateLiXian(data)
		sLiXian = DgnLiXian::fromStream(data)
		return onRecv_UpdateLiXian(sLiXian)
	end

	#接收处理：更新单个副本信息
	def _doRecv_UpdateDgnInfo(data)
		sDgnStar = DgnStar::fromStream(data)
		return onRecv_UpdateDgnInfo(sDgnStar)
	end

	#接收处理：更新所有副本信息
	def _doRecv_UpdateDgnInfoForAll(data)
		sLiXian = DgnLiXian::fromStream(data)
		vecStar = DgnStar::vectorFromStream(data)
		return onRecv_UpdateDgnInfoForAll(sLiXian, vecStar)
	end

#以下为返回处理函数
	#返回处理：扫荡
	def _doReturn_Sweeping(data)
		retParam = SRetParam_Sweeping.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EDungeonResult)扫荡结果
		dwSweepEndTime = ByteUtil::readUINT32(data) #(UINT32)扫荡结束时间
		retParam.eResult = eResult
		retParam.dwSweepEndTime = dwSweepEndTime
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_Sweeping(ret, origParam, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：扫荡
	def _onTimeOut_Sweeping(sessionID)
		retParam = SRetParam_Sweeping.new;
		origParam = @sessionMgr.getData(sessionID)
		onReturn_Sweeping(2, origParam, retParam)
	end

	#返回处理：加速扫荡
	def _doReturn_SweepingSpeedUp(data)
		retParam = SRetParam_SweepingSpeedUp.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EDungeonResult)加速扫荡结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SweepingSpeedUp(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：加速扫荡
	def _onTimeOut_SweepingSpeedUp(sessionID)
		retParam = SRetParam_SweepingSpeedUp.new;
		onReturn_SweepingSpeedUp(2, retParam)
	end

	#返回处理：取消扫荡
	def _doReturn_CancelSweeping(data)
		retParam = SRetParam_CancelSweeping.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EDungeonResult)取消扫荡结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_CancelSweeping(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：取消扫荡
	def _onTimeOut_CancelSweeping(sessionID)
		retParam = SRetParam_CancelSweeping.new;
		onReturn_CancelSweeping(2, retParam)
	end

	#返回处理：
	def _doReturn_EnterPlayerDungeon(data)
		retParam = SRetParam_EnterPlayerDungeon.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EDungeonResult)服务器返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_EnterPlayerDungeon(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：
	def _onTimeOut_EnterPlayerDungeon(sessionID)
		retParam = SRetParam_EnterPlayerDungeon.new;
		onReturn_EnterPlayerDungeon(2, retParam)
	end

	#返回处理：离开单人副本
	def _doReturn_LeavePlayerDungeon(data)
		retParam = SRetParam_LeavePlayerDungeon.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EDungeonResult)服务器返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LeavePlayerDungeon(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：离开单人副本
	def _onTimeOut_LeavePlayerDungeon(sessionID)
		retParam = SRetParam_LeavePlayerDungeon.new;
		onReturn_LeavePlayerDungeon(2, retParam)
	end

	#返回处理：客户端确认领奖
	def _doReturn_NotifyAcceptDgnAward(data)
		retParam = SRetParam_NotifyAcceptDgnAward.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EDungeonResult)服务器返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_NotifyAcceptDgnAward(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：客户端确认领奖
	def _onTimeOut_NotifyAcceptDgnAward(sessionID)
		retParam = SRetParam_NotifyAcceptDgnAward.new;
		onReturn_NotifyAcceptDgnAward(2, retParam)
	end

	#返回处理：查询副本星级
	def _doReturn_GetAllDgnInfo(data)
		retParam = SRetParam_GetAllDgnInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		sLiXian = DgnLiXian::fromStream(data) #(类类型：DgnLiXian)历险副本信息
		vecStar = DgnStar::vectorFromStream(data) #(DgnStar的数组)副本星级
		retParam.sLiXian = sLiXian
		retParam.vecStar = vecStar
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAllDgnInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：查询副本星级
	def _onTimeOut_GetAllDgnInfo(sessionID)
		retParam = SRetParam_GetAllDgnInfo.new;
		onReturn_GetAllDgnInfo(2, retParam)
	end

	#返回处理：客户端查询扫荡信息
	def _doReturn_GetDgnSweepingInfo(data)
		retParam = SRetParam_GetDgnSweepingInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		oGetSweepInfo = SGetSweepInfo::fromStream(data) #(类类型：SGetSweepInfo)扫荡信息
		retParam.oGetSweepInfo = oGetSweepInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetDgnSweepingInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：客户端查询扫荡信息
	def _onTimeOut_GetDgnSweepingInfo(sessionID)
		retParam = SRetParam_GetDgnSweepingInfo.new;
		onReturn_GetDgnSweepingInfo(2, retParam)
	end

	#返回处理：购买英雄副本次数
	def _doReturn_BuyHeroDgnTimes(data)
		retParam = SRetParam_BuyHeroDgnTimes.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EDungeonResult)服务器返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuyHeroDgnTimes(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：购买英雄副本次数
	def _onTimeOut_BuyHeroDgnTimes(sessionID)
		retParam = SRetParam_BuyHeroDgnTimes.new;
		onReturn_BuyHeroDgnTimes(2, retParam)
	end

	#返回处理：购买历险副本次数
	def _doReturn_BuyLiXianDgnTimes(data)
		retParam = SRetParam_BuyLiXianDgnTimes.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EDungeonResult)服务器返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuyLiXianDgnTimes(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：购买历险副本次数
	def _onTimeOut_BuyLiXianDgnTimes(sessionID)
		retParam = SRetParam_BuyLiXianDgnTimes.new;
		onReturn_BuyLiXianDgnTimes(2, retParam)
	end

	#返回处理：查询副本星级领奖状态
	def _doReturn_GetDgnStarAwardInfo(data)
		retParam = SRetParam_GetDgnStarAwardInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecAward = ByteUtil::readVecUINT16(data) #(UINT16数组)副本星级已领奖ID
		retParam.vecAward = vecAward
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetDgnStarAwardInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：查询副本星级领奖状态
	def _onTimeOut_GetDgnStarAwardInfo(sessionID)
		retParam = SRetParam_GetDgnStarAwardInfo.new;
		onReturn_GetDgnStarAwardInfo(2, retParam)
	end

	#返回处理：领取副本星级奖励
	def _doReturn_GetDgnStarAward(data)
		retParam = SRetParam_GetDgnStarAward.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EDungeonResult)服务器返回结果
		vecAward = ByteUtil::readVecUINT16(data) #(UINT16数组)副本星级已领奖ID
		retParam.eResult = eResult
		retParam.vecAward = vecAward
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetDgnStarAward(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：领取副本星级奖励
	def _onTimeOut_GetDgnStarAward(sessionID)
		retParam = SRetParam_GetDgnStarAward.new;
		onReturn_GetDgnStarAward(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 59;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_SweepingUpdateNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_SweepingEndNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_DungeonMapIdxNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_NotifyDgnAward' #FuncID: 4
		@recvFuncList[4] = '_doRecv_NotifyDgnProcess' #FuncID: 5
		@recvFuncList[5] = '_doRecv_NotifyDgnStar' #FuncID: 6
		@recvFuncList[6] = '_doRecv_SynTeamAwardRecord' #FuncID: 7
		@recvFuncList[7] = '_doRecv_TeamBattleResult' #FuncID: 8
		@recvFuncList[8] = '_doRecv_UpdateLiXian' #FuncID: 9
		@recvFuncList[9] = '_doRecv_UpdateDgnInfo' #FuncID: 10
		@recvFuncList[10] = '_doRecv_UpdateDgnInfoForAll' #FuncID: 11

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_Sweeping' #FuncID: 1
		@retFuncList[1] = '_doReturn_SweepingSpeedUp' #FuncID: 2
		@retFuncList[2] = '_doReturn_CancelSweeping' #FuncID: 3
		@retFuncList[3] = '_doReturn_EnterPlayerDungeon' #FuncID: 4
		@retFuncList[4] = '_doReturn_LeavePlayerDungeon' #FuncID: 5
		@retFuncList[5] = '_doReturn_NotifyAcceptDgnAward' #FuncID: 6
		@retFuncList[6] = '_doReturn_GetAllDgnInfo' #FuncID: 7
		@retFuncList[7] = '_doReturn_GetDgnSweepingInfo' #FuncID: 8
		@retFuncList[8] = '_doReturn_BuyHeroDgnTimes' #FuncID: 9
		@retFuncList[9] = '_doReturn_BuyLiXianDgnTimes' #FuncID: 10
		@retFuncList[10] = '_doReturn_GetDgnStarAwardInfo' #FuncID: 11
		@retFuncList[11] = '_doReturn_GetDgnStarAward' #FuncID: 12

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_Sweeping' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_SweepingSpeedUp' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_CancelSweeping' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_EnterPlayerDungeon' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_LeavePlayerDungeon' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_NotifyAcceptDgnAward' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_GetAllDgnInfo' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_GetDgnSweepingInfo' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_BuyHeroDgnTimes' #FuncID: 9
		@timeFuncList[9] = '_onTimeOut_BuyLiXianDgnTimes' #FuncID: 10
		@timeFuncList[10] = '_onTimeOut_GetDgnStarAwardInfo' #FuncID: 11
		@timeFuncList[11] = '_onTimeOut_GetDgnStarAward' #FuncID: 12
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

