#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    RankProt.rb
#  Purpose:      排行榜相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './BattleGSBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#排行榜类型
class ERankType
	ERTNONE = 0#无效排行榜类型
	ERTHEAD = 1#魁首榜
	ERTROLERANKBEGIN = 2#玩家排行榜开始索引
	ERTBATTLEPOINT = 2#总战力榜
	ERTLEVEL = 3#等级榜
	ERTFORMATION = 4#阵灵榜
	ERTHEROFIGHTER = 5#散仙榜
	ERTTRUMP = 6#法宝榜
	ERTARENA = 7#斗剑榜
	ERTROLERANKEND = 7#玩家排行榜结束索引
	ERTGUILDRANKBEGIN = 8#帮派排行榜开始索引
	ERTGUILDBATTLE = 8#帮派战排行榜
	ERTGUILDRANKEND = 9#帮派排行榜结束索引
	ERTMAX = 10#排名类型最大值
end

#排行榜返回结果集
class ERankResult
	ERRSUCCESS = 0#操作成功
	ERRFAILED = 1#操作失败
	ERRNOTEXIST = 2#不存在
end

#排行榜返回结果集
class EAdoreResult
	EARSUCCESS = 0#操作成功
	EARFAILED = 1#操作失败
	EARNOTEXIST = 2#不存在
end

#结构体：SRankInfo的继承体系类型
class EType_SRankInfo
	ETYPE_SRANKINFO = 0#类型：SRankInfo
	ETYPE_SROLEHEADINFO = 1#类型：SRoleHeadInfo
	ETYPE_SROLERANKINFO = 2#类型：SRoleRankInfo
	ETYPE_SGUILDRANKINFO = 3#类型：SGuildRankInfo
	ETYPE_SRRBATTLEPOINTINFO = 4#类型：SRRBattlePointInfo
	ETYPE_SRRLEVELINFO = 5#类型：SRRLevelInfo
	ETYPE_SRRFORMATIONINFO = 6#类型：SRRFormationInfo
	ETYPE_SRRHEROFIGHTERINFO = 7#类型：SRRHeroFighterInfo
	ETYPE_SRRTRUMPINFO = 8#类型：SRRTrumpInfo
	ETYPE_SRRARENAINFO = 9#类型：SRRArenaInfo
	ETYPE_SGRBATTLEINFO = 10#类型：SGRBattleInfo
	ETYPE_SGRLEVELINFO = 11#类型：SGRLevelInfo
end

#排名信息
class SRankInfo
	attr_accessor:dwValue #(UINT32)排名依据的信息(战斗力/等级……)
	attr_accessor:dwUpdateTime #(UINT32)更新时间

	#构造函数
	def initialize
		@dwValue = 0
		@dwUpdateTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SRankInfo::ETYPE_SRANKINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwValue = @dwValue
		obj.dwUpdateTime = @dwUpdateTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRankInfo.new
		s.dwValue = ByteUtil::readUINT32(data)
		s.dwUpdateTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_SRankInfo::ETYPE_SRANKINFO
				s = SRankInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SROLEHEADINFO
				s = SRoleHeadInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SROLERANKINFO
				s = SRoleRankInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SGUILDRANKINFO
				s = SGuildRankInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SRRBATTLEPOINTINFO
				s = SRRBattlePointInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SRRLEVELINFO
				s = SRRLevelInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SRRFORMATIONINFO
				s = SRRFormationInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SRRHEROFIGHTERINFO
				s = SRRHeroFighterInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SRRTRUMPINFO
				s = SRRTrumpInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SRRARENAINFO
				s = SRRArenaInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SGRBATTLEINFO
				s = SGRBattleInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SGRLEVELINFO
				s = SGRLevelInfo::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRankInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRankInfo::superFromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwValue)
		ByteUtil::writeUINT32(data, @dwUpdateTime)
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

#魁首榜
class SRoleHeadInfo < SRankInfo
	attr_accessor:eType #(枚举类型：ERankType)排行榜类型
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:strName #(string)玩家姓名
	attr_accessor:wID #(UINT16)对应ID
	attr_accessor:wPlayerFighterID #(UINT16)主将ID
	attr_accessor:byQuality #(UINT8)主将品质(颜色)
	attr_accessor:byInfoQuality #(UINT8)魁首品质(颜色)
	attr_accessor:strGuildName #(string)帮派名字

	#构造函数
	def initialize
		super()
		@eType = 0
		@qwRoleID = 0
		@strName = ''
		@wID = 0
		@wPlayerFighterID = 0
		@byQuality = 0
		@byInfoQuality = 0
		@strGuildName = ''
	end

	#获取继承类的类型
	def getClassType
		return EType_SRankInfo::ETYPE_SROLEHEADINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.eType = @eType
		obj.qwRoleID = @qwRoleID
		obj.strName = @strName
		obj.wID = @wID
		obj.wPlayerFighterID = @wPlayerFighterID
		obj.byQuality = @byQuality
		obj.byInfoQuality = @byInfoQuality
		obj.strGuildName = @strGuildName
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRoleHeadInfo.new
		base = SRankInfo::fromStream(data)
		base.copyTo(s)
		s.eType = ByteUtil::readUINT8(data)
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.wID = ByteUtil::readUINT16(data)
		s.wPlayerFighterID = ByteUtil::readUINT16(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.byInfoQuality = ByteUtil::readUINT8(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRoleHeadInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @eType)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT16(data, @wID)
		ByteUtil::writeUINT16(data, @wPlayerFighterID)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT8(data, @byInfoQuality)
		ByteUtil::writeSTRING(data, @strGuildName)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家相关排名信息
class SRoleRankInfo < SRankInfo
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:strName #(string)玩家姓名
	attr_accessor:wPlayerFighterID #(UINT16)主将ID
	attr_accessor:byQuality #(UINT8)散仙品质(颜色)
	attr_accessor:byVIPLevel #(UINT8)玩家VIP等级
	attr_accessor:vecPlatforms #(SPlatformParam的数组)平台信息

	#构造函数
	def initialize
		super()
		@qwRoleID = 0
		@strName = ''
		@wPlayerFighterID = 0
		@byQuality = 0
		@byVIPLevel = 0
		@vecPlatforms = Array.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SRankInfo::ETYPE_SROLERANKINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.qwRoleID = @qwRoleID
		obj.strName = @strName
		obj.wPlayerFighterID = @wPlayerFighterID
		obj.byQuality = @byQuality
		obj.byVIPLevel = @byVIPLevel
		obj.vecPlatforms = @vecPlatforms
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRoleRankInfo.new
		base = SRankInfo::fromStream(data)
		base.copyTo(s)
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.wPlayerFighterID = ByteUtil::readUINT16(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.byVIPLevel = ByteUtil::readUINT8(data)
		s.vecPlatforms = SPlatformParam::vectorFromStream(data)
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_SRankInfo::ETYPE_SROLERANKINFO
				s = SRoleRankInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SRRBATTLEPOINTINFO
				s = SRRBattlePointInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SRRLEVELINFO
				s = SRRLevelInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SRRFORMATIONINFO
				s = SRRFormationInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SRRHEROFIGHTERINFO
				s = SRRHeroFighterInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SRRTRUMPINFO
				s = SRRTrumpInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SRRARENAINFO
				s = SRRArenaInfo::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRoleRankInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRoleRankInfo::superFromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT16(data, @wPlayerFighterID)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT8(data, @byVIPLevel)
		SPlatformParam::vectorToStream(data, @vecPlatforms)
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

#战力信息
class SRRBattlePointInfo < SRoleRankInfo
	attr_accessor:dwBattlePoint #(UINT32)战斗力
	attr_accessor:strGuildName #(string)帮派名称

	#构造函数
	def initialize
		super()
		@dwBattlePoint = 0
		@strGuildName = ''
	end

	#获取继承类的类型
	def getClassType
		return EType_SRankInfo::ETYPE_SRRBATTLEPOINTINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwBattlePoint = @dwBattlePoint
		obj.strGuildName = @strGuildName
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRRBattlePointInfo.new
		base = SRoleRankInfo::fromStream(data)
		base.copyTo(s)
		s.dwBattlePoint = ByteUtil::readUINT32(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRRBattlePointInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwBattlePoint)
		ByteUtil::writeSTRING(data, @strGuildName)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#等级信息
class SRRLevelInfo < SRoleRankInfo
	attr_accessor:wLevel #(UINT16)等级
	attr_accessor:qwExp #(UINT64)经验值

	#构造函数
	def initialize
		super()
		@wLevel = 0
		@qwExp = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SRankInfo::ETYPE_SRRLEVELINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wLevel = @wLevel
		obj.qwExp = @qwExp
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRRLevelInfo.new
		base = SRoleRankInfo::fromStream(data)
		base.copyTo(s)
		s.wLevel = ByteUtil::readUINT16(data)
		s.qwExp = ByteUtil::readUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRRLevelInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wLevel)
		ByteUtil::writeUINT64(data, @qwExp)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#阵灵信息
class SRRFormationInfo < SRoleRankInfo
	attr_accessor:dwBattlePoint #(UINT32)战斗力
	attr_accessor:strGuildName #(string)帮派名称
	attr_accessor:wID #(UINT16)阵灵配置表ID，同monster

	#构造函数
	def initialize
		super()
		@dwBattlePoint = 0
		@strGuildName = ''
		@wID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SRankInfo::ETYPE_SRRFORMATIONINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwBattlePoint = @dwBattlePoint
		obj.strGuildName = @strGuildName
		obj.wID = @wID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRRFormationInfo.new
		base = SRoleRankInfo::fromStream(data)
		base.copyTo(s)
		s.dwBattlePoint = ByteUtil::readUINT32(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		s.wID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRRFormationInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwBattlePoint)
		ByteUtil::writeSTRING(data, @strGuildName)
		ByteUtil::writeUINT16(data, @wID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#散仙信息
class SRRHeroFighterInfo < SRoleRankInfo
	attr_accessor:dwBattlePoint #(UINT32)战斗力
	attr_accessor:strGuildName #(string)帮派名称
	attr_accessor:wID #(UINT16)散仙类型
	attr_accessor:byInfoQuality #(UINT8)散仙品质(颜色)

	#构造函数
	def initialize
		super()
		@dwBattlePoint = 0
		@strGuildName = ''
		@wID = 0
		@byInfoQuality = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SRankInfo::ETYPE_SRRHEROFIGHTERINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwBattlePoint = @dwBattlePoint
		obj.strGuildName = @strGuildName
		obj.wID = @wID
		obj.byInfoQuality = @byInfoQuality
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRRHeroFighterInfo.new
		base = SRoleRankInfo::fromStream(data)
		base.copyTo(s)
		s.dwBattlePoint = ByteUtil::readUINT32(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		s.wID = ByteUtil::readUINT16(data)
		s.byInfoQuality = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRRHeroFighterInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwBattlePoint)
		ByteUtil::writeSTRING(data, @strGuildName)
		ByteUtil::writeUINT16(data, @wID)
		ByteUtil::writeUINT8(data, @byInfoQuality)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#法宝信息
class SRRTrumpInfo < SRoleRankInfo
	attr_accessor:dwBattlePoint #(UINT32)战斗力
	attr_accessor:strGuildName #(string)帮派名称
	attr_accessor:wID #(UINT16)法宝ID

	#构造函数
	def initialize
		super()
		@dwBattlePoint = 0
		@strGuildName = ''
		@wID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SRankInfo::ETYPE_SRRTRUMPINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwBattlePoint = @dwBattlePoint
		obj.strGuildName = @strGuildName
		obj.wID = @wID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRRTrumpInfo.new
		base = SRoleRankInfo::fromStream(data)
		base.copyTo(s)
		s.dwBattlePoint = ByteUtil::readUINT32(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		s.wID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRRTrumpInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwBattlePoint)
		ByteUtil::writeSTRING(data, @strGuildName)
		ByteUtil::writeUINT16(data, @wID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#斗剑信息
class SRRArenaInfo < SRoleRankInfo
	attr_accessor:dwBattlePoint #(UINT32)战斗力
	attr_accessor:strGuildName #(string)帮派名称

	#构造函数
	def initialize
		super()
		@dwBattlePoint = 0
		@strGuildName = ''
	end

	#获取继承类的类型
	def getClassType
		return EType_SRankInfo::ETYPE_SRRARENAINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwBattlePoint = @dwBattlePoint
		obj.strGuildName = @strGuildName
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRRArenaInfo.new
		base = SRoleRankInfo::fromStream(data)
		base.copyTo(s)
		s.dwBattlePoint = ByteUtil::readUINT32(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRRArenaInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwBattlePoint)
		ByteUtil::writeSTRING(data, @strGuildName)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮派相关排名信息
class SGuildRankInfo < SRankInfo
	attr_accessor:qwGuildID #(UINT64)帮派ID
	attr_accessor:strName #(string)帮主姓名
	attr_accessor:wLevel #(UINT16)帮派等级
	attr_accessor:strGuildName #(string)帮派姓名
	attr_accessor:qwRoleID #(UINT64)帮主ID
	attr_accessor:byQuality #(UINT8)主将品质(颜色)
	attr_accessor:wPlayerFighterID #(UINT16)主将ID

	#构造函数
	def initialize
		super()
		@qwGuildID = 0
		@strName = ''
		@wLevel = 0
		@strGuildName = ''
		@qwRoleID = 0
		@byQuality = 0
		@wPlayerFighterID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SRankInfo::ETYPE_SGUILDRANKINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.qwGuildID = @qwGuildID
		obj.strName = @strName
		obj.wLevel = @wLevel
		obj.strGuildName = @strGuildName
		obj.qwRoleID = @qwRoleID
		obj.byQuality = @byQuality
		obj.wPlayerFighterID = @wPlayerFighterID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildRankInfo.new
		base = SRankInfo::fromStream(data)
		base.copyTo(s)
		s.qwGuildID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.wLevel = ByteUtil::readUINT16(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.wPlayerFighterID = ByteUtil::readUINT16(data)
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_SRankInfo::ETYPE_SGUILDRANKINFO
				s = SGuildRankInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SGRBATTLEINFO
				s = SGRBattleInfo::fromStream(data)
			when EType_SRankInfo::ETYPE_SGRLEVELINFO
				s = SGRLevelInfo::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildRankInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildRankInfo::superFromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT64(data, @qwGuildID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT16(data, @wLevel)
		ByteUtil::writeSTRING(data, @strGuildName)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT16(data, @wPlayerFighterID)
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

#帮派战排名
class SGRBattleInfo < SGuildRankInfo
	attr_accessor:dwBattleScore #(UINT32)帮派战积分

	#构造函数
	def initialize
		super()
		@dwBattleScore = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SRankInfo::ETYPE_SGRBATTLEINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwBattleScore = @dwBattleScore
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGRBattleInfo.new
		base = SGuildRankInfo::fromStream(data)
		base.copyTo(s)
		s.dwBattleScore = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGRBattleInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwBattleScore)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮派等级排名
class SGRLevelInfo < SGuildRankInfo
	attr_accessor:wLevel2 #(UINT16)帮派等级

	#构造函数
	def initialize
		super()
		@wLevel2 = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SRankInfo::ETYPE_SGRLEVELINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wLevel2 = @wLevel2
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGRLevelInfo.new
		base = SGuildRankInfo::fromStream(data)
		base.copyTo(s)
		s.wLevel2 = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGRLevelInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wLevel2)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#崇拜数据库信息
class SDBAdoreInfo
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:dwCount #(UINT32)被崇拜数量
	attr_accessor:dwUpdateTime #(UINT32)更新时间

	#构造函数
	def initialize
		@qwRoleID = 0
		@dwCount = 0
		@dwUpdateTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.dwCount = @dwCount
		obj.dwUpdateTime = @dwUpdateTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDBAdoreInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.dwCount = ByteUtil::readUINT32(data)
		s.dwUpdateTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDBAdoreInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT32(data, @dwCount)
		ByteUtil::writeUINT32(data, @dwUpdateTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetRankInfo:获取排行榜数据]的返回的参数组成的结构体
class SRetParam_GetRankInfo
	attr_accessor:eType#(枚举类型：ERankType)排行榜类型
	attr_accessor:dwMaxCount#(UINT32)最大排名数量
	attr_accessor:dwCurIndex#(UINT32)当前排名索引
	attr_accessor:dwSelfRank#(UINT32)自己所在排名
	attr_accessor:vecRankInfo#(SRankInfo的数组)排行榜数据
	attr_accessor:vecSelfRankInfo#(SRankInfo的数组)自己所在排名

	#构造函数
	def initialize
		@eType = 0
		@dwMaxCount = 0
		@dwCurIndex = 0
		@dwSelfRank = 0
		@vecRankInfo = Array.new
		@vecSelfRankInfo = Array.new
	end
end

#函数[GetPlayerFeature:获得玩家外观信息]的返回的参数组成的结构体
class SRetParam_GetPlayerFeature
	attr_accessor:eResult#(枚举类型：ERankResult)崇拜结果
	attr_accessor:pFeature#(类类型：BattleGS::SFeatureBase)外观信息

	#构造函数
	def initialize
		@eResult = 0
		@pFeature = SFeatureBase.new
	end
end

#函数[GetAdoreCount:获得崇拜数量]的返回的参数组成的结构体
class SRetParam_GetAdoreCount
	attr_accessor:dwCount#(UINT32)崇拜数量
	attr_accessor:dwSelfCount#(UINT32)自己剩余崇拜数量

	#构造函数
	def initialize
		@dwCount = 0
		@dwSelfCount = 0
	end
end

#函数[AdorePlayer:崇拜玩家]的返回的参数组成的结构体
class SRetParam_AdorePlayer
	attr_accessor:eResult#(枚举类型：ERankResult)崇拜结果
	attr_accessor:dwCount#(UINT32)崇拜数量
	attr_accessor:dwSelfCount#(UINT32)自己剩余崇拜数量

	#构造函数
	def initialize
		@eResult = 0
		@dwCount = 0
		@dwSelfCount = 0
	end
end

#协议类：排行榜相关协议
class RankProtBase < ProtocolBase
	#以下为发送函数
	#发送：获取排行榜数据
	def send_GetRankInfo(
		eType,  #(枚举类型：ERankType)排行榜类型
		dwIndex,  #(UINT32)排名索引
		dwCount #(UINT32)排名个数
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eType)
		ByteUtil::writeUINT32(data, dwIndex)
		ByteUtil::writeUINT32(data, dwCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得玩家外观信息
	def send_GetPlayerFeature(
		qwRoleID #(UINT64)玩家ID
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得崇拜数量
	def send_GetAdoreCount(
		qwRoleID #(UINT64)玩家ID
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：崇拜玩家
	def send_AdorePlayer(
		qwRoleID #(UINT64)玩家ID
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

#以下的返回函数需要重载
	#返回：获取排行榜数据
	def onReturn_GetRankInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetRankInfo)返回的参数
	)
	end

	#返回：获得玩家外观信息
	def onReturn_GetPlayerFeature(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetPlayerFeature)返回的参数
	)
	end

	#返回：获得崇拜数量
	def onReturn_GetAdoreCount(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAdoreCount)返回的参数
	)
	end

	#返回：崇拜玩家
	def onReturn_AdorePlayer(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_AdorePlayer)返回的参数
	)
	end

	#返回处理：获取排行榜数据
	def _doReturn_GetRankInfo(data)
		retParam = SRetParam_GetRankInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eType = ByteUtil::readUINT8(data) #(枚举类型：ERankType)排行榜类型
		dwMaxCount = ByteUtil::readUINT32(data) #(UINT32)最大排名数量
		dwCurIndex = ByteUtil::readUINT32(data) #(UINT32)当前排名索引
		dwSelfRank = ByteUtil::readUINT32(data) #(UINT32)自己所在排名
		vecRankInfo = SRankInfo::superVectorFromStream(data) #(SRankInfo的数组)排行榜数据
		vecSelfRankInfo = SRankInfo::superVectorFromStream(data) #(SRankInfo的数组)自己所在排名
		retParam.eType = eType
		retParam.dwMaxCount = dwMaxCount
		retParam.dwCurIndex = dwCurIndex
		retParam.dwSelfRank = dwSelfRank
		retParam.vecRankInfo = vecRankInfo
		retParam.vecSelfRankInfo = vecSelfRankInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetRankInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取排行榜数据
	def _onTimeOut_GetRankInfo(sessionID)
		retParam = SRetParam_GetRankInfo.new;
		onReturn_GetRankInfo(2, retParam)
	end

	#返回处理：获得玩家外观信息
	def _doReturn_GetPlayerFeature(data)
		retParam = SRetParam_GetPlayerFeature.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ERankResult)崇拜结果
		pFeature = SFeatureBase::superFromStream(data) #(类类型：BattleGS::SFeatureBase)外观信息
		retParam.eResult = eResult
		retParam.pFeature = pFeature
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetPlayerFeature(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获得玩家外观信息
	def _onTimeOut_GetPlayerFeature(sessionID)
		retParam = SRetParam_GetPlayerFeature.new;
		onReturn_GetPlayerFeature(2, retParam)
	end

	#返回处理：获得崇拜数量
	def _doReturn_GetAdoreCount(data)
		retParam = SRetParam_GetAdoreCount.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwCount = ByteUtil::readUINT32(data) #(UINT32)崇拜数量
		dwSelfCount = ByteUtil::readUINT32(data) #(UINT32)自己剩余崇拜数量
		retParam.dwCount = dwCount
		retParam.dwSelfCount = dwSelfCount
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAdoreCount(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获得崇拜数量
	def _onTimeOut_GetAdoreCount(sessionID)
		retParam = SRetParam_GetAdoreCount.new;
		onReturn_GetAdoreCount(2, retParam)
	end

	#返回处理：崇拜玩家
	def _doReturn_AdorePlayer(data)
		retParam = SRetParam_AdorePlayer.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ERankResult)崇拜结果
		dwCount = ByteUtil::readUINT32(data) #(UINT32)崇拜数量
		dwSelfCount = ByteUtil::readUINT32(data) #(UINT32)自己剩余崇拜数量
		retParam.eResult = eResult
		retParam.dwCount = dwCount
		retParam.dwSelfCount = dwSelfCount
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_AdorePlayer(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：崇拜玩家
	def _onTimeOut_AdorePlayer(sessionID)
		retParam = SRetParam_AdorePlayer.new;
		onReturn_AdorePlayer(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 80;
		@recvFuncList = Array.new

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetRankInfo' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetPlayerFeature' #FuncID: 2
		@retFuncList[2] = '_doReturn_GetAdoreCount' #FuncID: 3
		@retFuncList[3] = '_doReturn_AdorePlayer' #FuncID: 4

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetRankInfo' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetPlayerFeature' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GetAdoreCount' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_AdorePlayer' #FuncID: 4
	end

	def handleMessage(data)
		funcID = ByteUtil::readINT8(data);
		if funcID == 0 || funcID < -@retFuncList.length
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

