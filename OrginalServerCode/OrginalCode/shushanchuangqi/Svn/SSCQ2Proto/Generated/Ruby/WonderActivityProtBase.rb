#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    WonderActivityProt.rb
#  Purpose:      精彩活动
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#操作结果
class EWActResult
	EWACTRESULT_NONE = 0#无此活动
	EWACTRESULT_SUCCESS = 1#操作成功
	EWACTRESULT_ERROR = 2#操作失败
end

#领奖操作结果
class EGainResult
	EGAINRESULT_NONE = 0#无此奖励
	EGAINRESULT_SUCCESS = 1#领奖成功
	EGAINRESULT_ALREADYGAIN = 2#奖励已领
	EGAINRESULT_FULLBAG = 3#背包满
	EGAINRESULT_NOTGET = 4#条件未达到
	EGAINRESULT_ERROR = 5#操作失败
end

#活动类型
class EWActType
	EWACTTYPE_NONE = 0#无活动
	EWACTTYPE_RANKPOINT = 702#战力排行榜
	EWACTTYPE_LEVELACT = 703#全服等级奖励
	EWACTTYPE_HORSEACT = 704#坐骑收集奖励
	EWACTTYPE_DUNGON = 705#全服副本奖励
	EWACTTYPE_FIGHTER = 706#全服散仙奖励
	EWACTTYPE_FORMATION = 707#全服阵灵奖励
	EWACTTYPE_TRUMP = 708#全服法宝奖励
	EWACTTYPE_RANKLEVEL = 709#等级排行榜
	EWACTTYPE_RANKPET = 710#阵灵排行榜
	EWACTTYPE_RANKFIGHTER = 711#散仙排行榜
	EWACTTYPE_RANKARENA = 712#斗剑排行榜
	EWACTTYPE_RANKGUILD = 713#帮派排行榜
	EWACTTYPE_RANKTRUMP = 717#法宝排行榜
	EWACTTYPE_QQCOIN = 715#Q养成活动
	EWACTTYPE_BEAUTYACT = 716#美女奖励
	EWACTTYPE_POINT = 718#战力奖励
	EWACTTYPE_OPENBUY = 719#开服购买礼包
	EWACTTYPE_MAX = 720#活动最大值
end

#活动状态
class EWActState
	EWACTSTATE_INIT = 0#初始状态
	EWACTSTATE_ADVANCE = 1#活动预告
	EWACTSTATE_BEGIN = 2#活动开始
	EWACTSTATE_END = 3#活动结束
	EWACTSTATE_RETAIN = 4#活动保留时间
end

#活动奖励类型
class EWActPrizeType
	EWACTPRIZETYPE_DEFAULT = 0#全部奖励
	EWACTPRIZETYPE_FIRST = 1#第一名玩家奖励
	EWACTPRIZETYPE_ONE = 2#一等奖
	EWACTPRIZETYPE_TWO = 3#二等奖
	EWACTPRIZETYPE_THREE = 4#三等奖
	EWACTPRIZETYPE_MAX = 5#奖励最大值
end

#奖励道具信息
class SItemConfig
	attr_accessor:dwItemID #(UINT32)道具ID
	attr_accessor:dwCount #(UINT32)道具数量

	#构造函数
	def initialize
		@dwItemID = 0
		@dwCount = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwItemID = @dwItemID
		obj.dwCount = @dwCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SItemConfig.new
		s.dwItemID = ByteUtil::readUINT32(data)
		s.dwCount = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SItemConfig::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwItemID)
		ByteUtil::writeUINT32(data, @dwCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#奖励道具信息
class SPrizeConfig
	attr_accessor:ePrizeType #(枚举类型：EWActPrizeType)奖励类型
	attr_accessor:vecItems #(SItemConfig的数组)道具

	#构造函数
	def initialize
		@ePrizeType = 0
		@vecItems = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.ePrizeType = @ePrizeType
		obj.vecItems = @vecItems
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPrizeConfig.new
		s.ePrizeType = ByteUtil::readUINT8(data)
		s.vecItems = SItemConfig::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPrizeConfig::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @ePrizeType)
		SItemConfig::vectorToStream(data, @vecItems)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#活动具体配置信息
class SWActConfig
	attr_accessor:wWActID #(UINT16)活动ID
	attr_accessor:wCfgID #(UINT16)活动配置ID
	attr_accessor:eWactPrizeType #(枚举类型：EWActPrizeType)奖励类型
	attr_accessor:vecItemConfig #(SItemConfig的数组)奖励道具列表

	#构造函数
	def initialize
		@wWActID = 0
		@wCfgID = 0
		@eWactPrizeType = 0
		@vecItemConfig = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wWActID = @wWActID
		obj.wCfgID = @wCfgID
		obj.eWactPrizeType = @eWactPrizeType
		obj.vecItemConfig = @vecItemConfig
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SWActConfig.new
		s.wWActID = ByteUtil::readUINT16(data)
		s.wCfgID = ByteUtil::readUINT16(data)
		s.eWactPrizeType = ByteUtil::readUINT8(data)
		s.vecItemConfig = SItemConfig::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SWActConfig::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wWActID)
		ByteUtil::writeUINT16(data, @wCfgID)
		ByteUtil::writeUINT8(data, @eWactPrizeType)
		SItemConfig::vectorToStream(data, @vecItemConfig)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#人物信息
class SWActPlayerInfo
	attr_accessor:wWActID #(UINT16)活动ID
	attr_accessor:wID #(UINT16)散仙|阵灵ID
	attr_accessor:qwPlayerID #(UINT64)玩家ID
	attr_accessor:strName #(string)玩家名字|帮主名
	attr_accessor:eCareer #(枚类型：ProtoCommon::ECareerType)玩家职业
	attr_accessor:eSex #(枚类型：ProtoCommon::ESexType)玩家性别
	attr_accessor:strName1 #(string)帮派名
	attr_accessor:dwValue1 #(UINT32)参数1(战力，等级，散仙，阵灵，帮派）排名
	attr_accessor:dwValue2 #(UINT32)参数2(战力，等级，散仙战力，阵灵战力，帮派等级)

	#构造函数
	def initialize
		@wWActID = 0
		@wID = 0
		@qwPlayerID = 0
		@strName = ''
		@eCareer = 0
		@eSex = 0
		@strName1 = ''
		@dwValue1 = 0
		@dwValue2 = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wWActID = @wWActID
		obj.wID = @wID
		obj.qwPlayerID = @qwPlayerID
		obj.strName = @strName
		obj.eCareer = @eCareer
		obj.eSex = @eSex
		obj.strName1 = @strName1
		obj.dwValue1 = @dwValue1
		obj.dwValue2 = @dwValue2
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SWActPlayerInfo.new
		s.wWActID = ByteUtil::readUINT16(data)
		s.wID = ByteUtil::readUINT16(data)
		s.qwPlayerID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.eCareer = ByteUtil::readUINT8(data)
		s.eSex = ByteUtil::readUINT8(data)
		s.strName1 = ByteUtil::readSTRING(data)
		s.dwValue1 = ByteUtil::readUINT32(data)
		s.dwValue2 = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SWActPlayerInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wWActID)
		ByteUtil::writeUINT16(data, @wID)
		ByteUtil::writeUINT64(data, @qwPlayerID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @eCareer)
		ByteUtil::writeUINT8(data, @eSex)
		ByteUtil::writeSTRING(data, @strName1)
		ByteUtil::writeUINT32(data, @dwValue1)
		ByteUtil::writeUINT32(data, @dwValue2)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#活动时间信息
class STime
	attr_accessor:wWActID #(UINT16)活动ID
	attr_accessor:dwAdvTime #(UINT32)活动预告时间
	attr_accessor:dwBeginTime #(UINT32)活动开始时间
	attr_accessor:dwEndTime #(UINT32)活动结束时间
	attr_accessor:dwRetainTime #(UINT32)活动预留时间

	#构造函数
	def initialize
		@wWActID = 0
		@dwAdvTime = 0
		@dwBeginTime = 0
		@dwEndTime = 0
		@dwRetainTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wWActID = @wWActID
		obj.dwAdvTime = @dwAdvTime
		obj.dwBeginTime = @dwBeginTime
		obj.dwEndTime = @dwEndTime
		obj.dwRetainTime = @dwRetainTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STime.new
		s.wWActID = ByteUtil::readUINT16(data)
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
		ByteUtil::writeUINT16(data, @wWActID)
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

#数据库信息
class SWonderPrize2DB
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:wActID #(UINT16)活动ID
	attr_accessor:wActType #(UINT16)活动类型
	attr_accessor:wCond #(UINT32)活动条件
	attr_accessor:byStatus #(UINT8)活动状态

	#构造函数
	def initialize
		@qwRoleID = 0
		@wActID = 0
		@wActType = 0
		@wCond = 0
		@byStatus = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wActID = @wActID
		obj.wActType = @wActType
		obj.wCond = @wCond
		obj.byStatus = @byStatus
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SWonderPrize2DB.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wActID = ByteUtil::readUINT16(data)
		s.wActType = ByteUtil::readUINT16(data)
		s.wCond = ByteUtil::readUINT32(data)
		s.byStatus = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SWonderPrize2DB::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wActID)
		ByteUtil::writeUINT16(data, @wActType)
		ByteUtil::writeUINT32(data, @wCond)
		ByteUtil::writeUINT8(data, @byStatus)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#状态信息
class SPrizeStatus
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:wActID #(UINT16)活动ID
	attr_accessor:vecStatus #(UINT8数组)活动状态

	#构造函数
	def initialize
		@qwRoleID = 0
		@wActID = 0
		@vecStatus = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wActID = @wActID
		obj.vecStatus = @vecStatus
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPrizeStatus.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wActID = ByteUtil::readUINT16(data)
		s.vecStatus = ByteUtil::readVecUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPrizeStatus::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wActID)
		ByteUtil::writeVecUINT8(data, @vecStatus)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家在活动中的状态信息
class SRoleStatus
	attr_accessor:wCond #(UINT32)活动ID
	attr_accessor:dwMaxRole #(UINT32)活动达到条件人数
	attr_accessor:dwCurRole #(UINT32)活动目前人数
	attr_accessor:byStatus #(UINT8)活动状态

	#构造函数
	def initialize
		@wCond = 0
		@dwMaxRole = 0
		@dwCurRole = 0
		@byStatus = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wCond = @wCond
		obj.dwMaxRole = @dwMaxRole
		obj.dwCurRole = @dwCurRole
		obj.byStatus = @byStatus
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRoleStatus.new
		s.wCond = ByteUtil::readUINT32(data)
		s.dwMaxRole = ByteUtil::readUINT32(data)
		s.dwCurRole = ByteUtil::readUINT32(data)
		s.byStatus = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRoleStatus::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @wCond)
		ByteUtil::writeUINT32(data, @dwMaxRole)
		ByteUtil::writeUINT32(data, @dwCurRole)
		ByteUtil::writeUINT8(data, @byStatus)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家在活动中的保留值
class SRetain
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:strName #(string)玩家名字
	attr_accessor:byCareer #(UINT8)玩家职业
	attr_accessor:bySex #(UINT8)性别
	attr_accessor:wActID #(UINT16)活动ID
	attr_accessor:wID #(UINT16)保留值（散仙ID,帮派ID,阵灵ID.....)
	attr_accessor:strGuildName #(string)帮派名字
	attr_accessor:wType #(UINT16)保留类型
	attr_accessor:dwValue #(UINT32)保留值
	attr_accessor:dwTime #(UINT32)时间

	#构造函数
	def initialize
		@qwRoleID = 0
		@strName = ''
		@byCareer = 0
		@bySex = 0
		@wActID = 0
		@wID = 0
		@strGuildName = ''
		@wType = 0
		@dwValue = 0
		@dwTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.strName = @strName
		obj.byCareer = @byCareer
		obj.bySex = @bySex
		obj.wActID = @wActID
		obj.wID = @wID
		obj.strGuildName = @strGuildName
		obj.wType = @wType
		obj.dwValue = @dwValue
		obj.dwTime = @dwTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRetain.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.byCareer = ByteUtil::readUINT8(data)
		s.bySex = ByteUtil::readUINT8(data)
		s.wActID = ByteUtil::readUINT16(data)
		s.wID = ByteUtil::readUINT16(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		s.wType = ByteUtil::readUINT16(data)
		s.dwValue = ByteUtil::readUINT32(data)
		s.dwTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRetain::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @byCareer)
		ByteUtil::writeUINT8(data, @bySex)
		ByteUtil::writeUINT16(data, @wActID)
		ByteUtil::writeUINT16(data, @wID)
		ByteUtil::writeSTRING(data, @strGuildName)
		ByteUtil::writeUINT16(data, @wType)
		ByteUtil::writeUINT32(data, @dwValue)
		ByteUtil::writeUINT32(data, @dwTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家在所有活动中的信息
class SRoleAllStatus
	attr_accessor:wActID #(UINT16)活动ID
	attr_accessor:vecAllState #(SRoleStatus的数组)状态

	#构造函数
	def initialize
		@wActID = 0
		@vecAllState = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wActID = @wActID
		obj.vecAllState = @vecAllState
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRoleAllStatus.new
		s.wActID = ByteUtil::readUINT16(data)
		s.vecAllState = SRoleStatus::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRoleAllStatus::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wActID)
		SRoleStatus::vectorToStream(data, @vecAllState)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#七星龙珠活动信息
class SDragonBallAct
	attr_accessor:dwBeginTime #(UINT32)活动开始时间
	attr_accessor:dwEndTime #(UINT32)活动结束时间
	attr_accessor:dwRecharge #(UINT32)今日充值仙石数
	attr_accessor:byIdx #(UINT8)第几期活动
	attr_accessor:byDay #(UINT8)今日完成的龙珠数
	attr_accessor:byAll #(UINT8)完成的龙珠总数
	attr_accessor:byRemain #(UINT8)今日之前剩余可点亮的龙珠数

	#构造函数
	def initialize
		@dwBeginTime = 0
		@dwEndTime = 0
		@dwRecharge = 0
		@byIdx = 0
		@byDay = 0
		@byAll = 0
		@byRemain = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwBeginTime = @dwBeginTime
		obj.dwEndTime = @dwEndTime
		obj.dwRecharge = @dwRecharge
		obj.byIdx = @byIdx
		obj.byDay = @byDay
		obj.byAll = @byAll
		obj.byRemain = @byRemain
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDragonBallAct.new
		s.dwBeginTime = ByteUtil::readUINT32(data)
		s.dwEndTime = ByteUtil::readUINT32(data)
		s.dwRecharge = ByteUtil::readUINT32(data)
		s.byIdx = ByteUtil::readUINT8(data)
		s.byDay = ByteUtil::readUINT8(data)
		s.byAll = ByteUtil::readUINT8(data)
		s.byRemain = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDragonBallAct::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwBeginTime)
		ByteUtil::writeUINT32(data, @dwEndTime)
		ByteUtil::writeUINT32(data, @dwRecharge)
		ByteUtil::writeUINT8(data, @byIdx)
		ByteUtil::writeUINT8(data, @byDay)
		ByteUtil::writeUINT8(data, @byAll)
		ByteUtil::writeUINT8(data, @byRemain)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#七日消费活动信息
class SSevenConsumeAct
	attr_accessor:dwBeginTime #(UINT32)活动开始时间
	attr_accessor:dwEndTime #(UINT32)活动结束时间
	attr_accessor:dwConsume #(UINT32)七日总消费仙石数
	attr_accessor:byInfo #(UINT8)奖励领取状态信息(从低到高按位取,1已领取 0未领取)

	#构造函数
	def initialize
		@dwBeginTime = 0
		@dwEndTime = 0
		@dwConsume = 0
		@byInfo = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwBeginTime = @dwBeginTime
		obj.dwEndTime = @dwEndTime
		obj.dwConsume = @dwConsume
		obj.byInfo = @byInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSevenConsumeAct.new
		s.dwBeginTime = ByteUtil::readUINT32(data)
		s.dwEndTime = ByteUtil::readUINT32(data)
		s.dwConsume = ByteUtil::readUINT32(data)
		s.byInfo = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSevenConsumeAct::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwBeginTime)
		ByteUtil::writeUINT32(data, @dwEndTime)
		ByteUtil::writeUINT32(data, @dwConsume)
		ByteUtil::writeUINT8(data, @byInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#Q币养成活动信息
class SQQCoinActInfo
	attr_accessor:dwTime #(UINT32)活动剩余时间
	attr_accessor:byLevel #(UINT8)当前兑换的等级
	attr_accessor:dwMaxValue #(UINT32)奖励最大值
	attr_accessor:dwCurValue #(UINT32)当前值

	#构造函数
	def initialize
		@dwTime = 0
		@byLevel = 0
		@dwMaxValue = 0
		@dwCurValue = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwTime = @dwTime
		obj.byLevel = @byLevel
		obj.dwMaxValue = @dwMaxValue
		obj.dwCurValue = @dwCurValue
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SQQCoinActInfo.new
		s.dwTime = ByteUtil::readUINT32(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.dwMaxValue = ByteUtil::readUINT32(data)
		s.dwCurValue = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SQQCoinActInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwTime)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwMaxValue)
		ByteUtil::writeUINT32(data, @dwCurValue)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetConfigTime:获得活动时间配置]的返回的参数组成的结构体
class SRetParam_GetConfigTime
	attr_accessor:sTimes#(类类型：STime)时间
	attr_accessor:eRet#(枚举类型：EWActResult)操作结果

	#构造函数
	def initialize
		@sTimes = STime.new
		@eRet = 0
	end
end

#函数[GetAllPrize:获得活动所有奖励配置]的返回的参数组成的结构体
class SRetParam_GetAllPrize
	attr_accessor:wActID#(UINT16)活动ID
	attr_accessor:sFirstPlayer#(类类型：SWActPlayerInfo)第一名玩家信息
	attr_accessor:sSelfPlayer#(类类型：SWActPlayerInfo)玩家自己信息
	attr_accessor:vecPrizeConfig#(SPrizeConfig的数组)奖励信息
	attr_accessor:eRet#(枚举类型：EWActResult)操作结果

	#构造函数
	def initialize
		@wActID = 0
		@sFirstPlayer = SWActPlayerInfo.new
		@sSelfPlayer = SWActPlayerInfo.new
		@vecPrizeConfig = Array.new
		@eRet = 0
	end
end

#函数[GetActList:获得活动列表]的返回的参数组成的结构体
class SRetParam_GetActList
	attr_accessor:vecTimes#(STime的数组)奖励信息
	attr_accessor:eRet#(枚举类型：EWActResult)操作结果

	#构造函数
	def initialize
		@vecTimes = Array.new
		@eRet = 0
	end
end

#函数[TakePrize:玩家领奖]的返回的参数组成的结构体
class SRetParam_TakePrize
	attr_accessor:wActIDRet#(UINT16)返回活动ID
	attr_accessor:wCondRet#(UINT32)返回条件

	#构造函数
	def initialize
		@wActIDRet = 0
		@wCondRet = 0
	end
end

#函数[GetRoleActInfo:玩家活动信息]的返回的参数组成的结构体
class SRetParam_GetRoleActInfo
	attr_accessor:wActIDRet#(UINT16)活动ID
	attr_accessor:vecRet#(SRoleStatus的数组)操作结果

	#构造函数
	def initialize
		@wActIDRet = 0
		@vecRet = Array.new
	end
end

#函数[GetRoleAllState:玩家在所有活动中的状态]的返回的参数组成的结构体
class SRetParam_GetRoleAllState
	attr_accessor:vecRet#(SRoleAllStatus的数组)结果

	#构造函数
	def initialize
		@vecRet = Array.new
	end
end

#函数[GetDragonBallAct:请求七星龙珠活动信息]的返回的参数组成的结构体
class SRetParam_GetDragonBallAct
	attr_accessor:byRet#(UINT8)0活动未开启 >0活动已开启

	#构造函数
	def initialize
		@byRet = 0
	end
end

#函数[GetSevenConsumeAct:请求七日消费活动信息]的返回的参数组成的结构体
class SRetParam_GetSevenConsumeAct
	attr_accessor:byRet#(UINT8)0活动未开启 >0活动已开启

	#构造函数
	def initialize
		@byRet = 0
	end
end

#函数[ExChange:兑换仙石或者领取Q币]的返回的参数组成的结构体
class SRetParam_ExChange
	attr_accessor:eResult#(枚举类型：EWActResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：精彩活动
class WonderActivityProtBase < ProtocolBase
	#以下为发送函数
	#发送：获得活动时间配置
	def send_GetConfigTime(
		wWActID #(UINT16)精彩活动ID
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wWActID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得活动所有奖励配置
	def send_GetAllPrize(
		wWActID #(UINT16)精彩活动ID
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wWActID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得活动列表
	def send_GetActList(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家领奖
	def send_TakePrize(
		wActID,  #(UINT16)精彩活动ID
		wCond #(UINT32)条件
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wActID)
		ByteUtil::writeUINT32(data, wCond)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家活动信息
	def send_GetRoleActInfo(
		wActID #(UINT16)活动ID
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wActID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家在所有活动中的状态
	def send_GetRoleAllState(
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求七星龙珠活动信息
	def send_GetDragonBallAct(
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求七日消费活动信息
	def send_GetSevenConsumeAct(
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求Q养成活动信息
	def send_GetQQCoinAct(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：兑换仙石或者领取Q币
	def send_ExChange(
		byType #(UINT8)0表示Q币，1表示仙石
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byType)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：领奖状态通知
	def onRecv_SendTakePrizeNtf(
		wActID, #(UINT16)活动ID
		wCond, #(UINT32)条件ID
		eRet #(枚举类型：EGainResult)状态
	)
		raise NotImplementedError
	end
	#接收：达到条件通知
	def onRecv_SendReachCondNtf(
		wActID, #(UINT16)活动ID
		wCond #(UINT32)条件ID
	)
		raise NotImplementedError
	end
	#接收：更新七星龙珠活动信息
	def onRecv_UpdateDragonBallAct(
		oDragonBallAct #(类类型：SDragonBallAct)七星龙珠活动信息
	)
		raise NotImplementedError
	end
	#接收：更新七日消费活动信息
	def onRecv_UpdateSevenConsumeAct(
		oSevenConsumeAct #(类类型：SSevenConsumeAct)七日消费活动信息
	)
		raise NotImplementedError
	end
	#接收：同步QQ养成信息
	def onRecv_SyncQQCoinInfo(
		oQQCoinInfo #(类类型：SQQCoinActInfo)Q养成活动信息
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获得活动时间配置
	def onReturn_GetConfigTime(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetConfigTime)返回的参数
	)
	end

	#返回：获得活动所有奖励配置
	def onReturn_GetAllPrize(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAllPrize)返回的参数
	)
	end

	#返回：获得活动列表
	def onReturn_GetActList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetActList)返回的参数
	)
	end

	#返回：玩家领奖
	def onReturn_TakePrize(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakePrize)返回的参数
	)
	end

	#返回：玩家活动信息
	def onReturn_GetRoleActInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetRoleActInfo)返回的参数
	)
	end

	#返回：玩家在所有活动中的状态
	def onReturn_GetRoleAllState(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetRoleAllState)返回的参数
	)
	end

	#返回：请求七星龙珠活动信息
	def onReturn_GetDragonBallAct(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetDragonBallAct)返回的参数
	)
	end

	#返回：请求七日消费活动信息
	def onReturn_GetSevenConsumeAct(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetSevenConsumeAct)返回的参数
	)
	end

	#返回：兑换仙石或者领取Q币
	def onReturn_ExChange(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ExChange)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：领奖状态通知
	def _doRecv_SendTakePrizeNtf(data)
		wActID = ByteUtil::readUINT16(data)
		wCond = ByteUtil::readUINT32(data)
		eRet = ByteUtil::readUINT8(data)
		return onRecv_SendTakePrizeNtf(wActID, wCond, eRet)
	end

	#接收处理：达到条件通知
	def _doRecv_SendReachCondNtf(data)
		wActID = ByteUtil::readUINT16(data)
		wCond = ByteUtil::readUINT32(data)
		return onRecv_SendReachCondNtf(wActID, wCond)
	end

	#接收处理：更新七星龙珠活动信息
	def _doRecv_UpdateDragonBallAct(data)
		oDragonBallAct = SDragonBallAct::fromStream(data)
		return onRecv_UpdateDragonBallAct(oDragonBallAct)
	end

	#接收处理：更新七日消费活动信息
	def _doRecv_UpdateSevenConsumeAct(data)
		oSevenConsumeAct = SSevenConsumeAct::fromStream(data)
		return onRecv_UpdateSevenConsumeAct(oSevenConsumeAct)
	end

	#接收处理：同步QQ养成信息
	def _doRecv_SyncQQCoinInfo(data)
		oQQCoinInfo = SQQCoinActInfo::fromStream(data)
		return onRecv_SyncQQCoinInfo(oQQCoinInfo)
	end

#以下为返回处理函数
	#返回处理：获得活动时间配置
	def _doReturn_GetConfigTime(data)
		retParam = SRetParam_GetConfigTime.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		sTimes = STime::fromStream(data) #(类类型：STime)时间
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EWActResult)操作结果
		retParam.sTimes = sTimes
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetConfigTime(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获得活动时间配置
	def _onTimeOut_GetConfigTime(sessionID)
		retParam = SRetParam_GetConfigTime.new;
		onReturn_GetConfigTime(2, retParam)
	end

	#返回处理：获得活动所有奖励配置
	def _doReturn_GetAllPrize(data)
		retParam = SRetParam_GetAllPrize.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		wActID = ByteUtil::readUINT16(data) #(UINT16)活动ID
		sFirstPlayer = SWActPlayerInfo::fromStream(data) #(类类型：SWActPlayerInfo)第一名玩家信息
		sSelfPlayer = SWActPlayerInfo::fromStream(data) #(类类型：SWActPlayerInfo)玩家自己信息
		vecPrizeConfig = SPrizeConfig::vectorFromStream(data) #(SPrizeConfig的数组)奖励信息
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EWActResult)操作结果
		retParam.wActID = wActID
		retParam.sFirstPlayer = sFirstPlayer
		retParam.sSelfPlayer = sSelfPlayer
		retParam.vecPrizeConfig = vecPrizeConfig
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAllPrize(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获得活动所有奖励配置
	def _onTimeOut_GetAllPrize(sessionID)
		retParam = SRetParam_GetAllPrize.new;
		onReturn_GetAllPrize(2, retParam)
	end

	#返回处理：获得活动列表
	def _doReturn_GetActList(data)
		retParam = SRetParam_GetActList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecTimes = STime::vectorFromStream(data) #(STime的数组)奖励信息
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EWActResult)操作结果
		retParam.vecTimes = vecTimes
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetActList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获得活动列表
	def _onTimeOut_GetActList(sessionID)
		retParam = SRetParam_GetActList.new;
		onReturn_GetActList(2, retParam)
	end

	#返回处理：玩家领奖
	def _doReturn_TakePrize(data)
		retParam = SRetParam_TakePrize.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		wActIDRet = ByteUtil::readUINT16(data) #(UINT16)返回活动ID
		wCondRet = ByteUtil::readUINT32(data) #(UINT32)返回条件
		retParam.wActIDRet = wActIDRet
		retParam.wCondRet = wCondRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakePrize(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：玩家领奖
	def _onTimeOut_TakePrize(sessionID)
		retParam = SRetParam_TakePrize.new;
		onReturn_TakePrize(2, retParam)
	end

	#返回处理：玩家活动信息
	def _doReturn_GetRoleActInfo(data)
		retParam = SRetParam_GetRoleActInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		wActIDRet = ByteUtil::readUINT16(data) #(UINT16)活动ID
		vecRet = SRoleStatus::vectorFromStream(data) #(SRoleStatus的数组)操作结果
		retParam.wActIDRet = wActIDRet
		retParam.vecRet = vecRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetRoleActInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：玩家活动信息
	def _onTimeOut_GetRoleActInfo(sessionID)
		retParam = SRetParam_GetRoleActInfo.new;
		onReturn_GetRoleActInfo(2, retParam)
	end

	#返回处理：玩家在所有活动中的状态
	def _doReturn_GetRoleAllState(data)
		retParam = SRetParam_GetRoleAllState.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecRet = SRoleAllStatus::vectorFromStream(data) #(SRoleAllStatus的数组)结果
		retParam.vecRet = vecRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetRoleAllState(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：玩家在所有活动中的状态
	def _onTimeOut_GetRoleAllState(sessionID)
		retParam = SRetParam_GetRoleAllState.new;
		onReturn_GetRoleAllState(2, retParam)
	end

	#返回处理：请求七星龙珠活动信息
	def _doReturn_GetDragonBallAct(data)
		retParam = SRetParam_GetDragonBallAct.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readUINT8(data) #(UINT8)0活动未开启 >0活动已开启
		retParam.byRet = byRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetDragonBallAct(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求七星龙珠活动信息
	def _onTimeOut_GetDragonBallAct(sessionID)
		retParam = SRetParam_GetDragonBallAct.new;
		onReturn_GetDragonBallAct(2, retParam)
	end

	#返回处理：请求七日消费活动信息
	def _doReturn_GetSevenConsumeAct(data)
		retParam = SRetParam_GetSevenConsumeAct.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readUINT8(data) #(UINT8)0活动未开启 >0活动已开启
		retParam.byRet = byRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetSevenConsumeAct(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求七日消费活动信息
	def _onTimeOut_GetSevenConsumeAct(sessionID)
		retParam = SRetParam_GetSevenConsumeAct.new;
		onReturn_GetSevenConsumeAct(2, retParam)
	end

	#返回处理：兑换仙石或者领取Q币
	def _doReturn_ExChange(data)
		retParam = SRetParam_ExChange.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EWActResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ExChange(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：兑换仙石或者领取Q币
	def _onTimeOut_ExChange(sessionID)
		retParam = SRetParam_ExChange.new;
		onReturn_ExChange(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 199;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_SendTakePrizeNtf' #FuncID: 1
		@recvFuncList[1] = '_doRecv_SendReachCondNtf' #FuncID: 2
		@recvFuncList[2] = '_doRecv_UpdateDragonBallAct' #FuncID: 3
		@recvFuncList[3] = '_doRecv_UpdateSevenConsumeAct' #FuncID: 4
		@recvFuncList[4] = '_doRecv_SyncQQCoinInfo' #FuncID: 5

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetConfigTime' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetAllPrize' #FuncID: 2
		@retFuncList[2] = '_doReturn_GetActList' #FuncID: 3
		@retFuncList[3] = '_doReturn_TakePrize' #FuncID: 4
		@retFuncList[4] = '_doReturn_GetRoleActInfo' #FuncID: 5
		@retFuncList[5] = '_doReturn_GetRoleAllState' #FuncID: 6
		@retFuncList[6] = '_doReturn_GetDragonBallAct' #FuncID: 7
		@retFuncList[7] = '_doReturn_GetSevenConsumeAct' #FuncID: 8
		@retFuncList[8] = '_doReturn_ExChange' #FuncID: 9

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetConfigTime' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetAllPrize' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GetActList' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_TakePrize' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_GetRoleActInfo' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_GetRoleAllState' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_GetDragonBallAct' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_GetSevenConsumeAct' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_ExChange' #FuncID: 9
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

