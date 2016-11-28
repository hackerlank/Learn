#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    NewGuildBattleProt.rb
#  Purpose:      新帮派战相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#帮派战当前状态
class ENGBState
	ENGBSNONE = 0#没有开启帮派战
	ENGBSREADY = 1#帮派战即将开启，倒计时通知阶段
	ENGBSBATTLE = 2#帮派战进行中
	ENGBSBATTLEEND = 3#帮派战战役结束
end

#帮派战玩家状态
class ENGBPlayerState
	ENGBPSNONE = 0#无效状态
	ENGBPSWAIT = 1#待战状态
	ENGBPSDEAD = 2#死亡状态
	ENGBPSRUNAWAY = 3#逃跑状态
	ENGBPSMAX = 4#最大状态
end

#帮派战灵山
class ENGBMountain
	ENGBMNONE = 0#无效灵山
	ENGBMEMEI = 1#峨眉
	ENGBMKUNLUN = 2#昆仑
	ENGBMHUANGSHAN = 3#黄山
	ENGBMMAX = 4#最大灵山数
end

#帮派战洞府战阵眼类型
class ENGBCaveCore
	ENGBCCNONE = 0#无效阵眼
	ENGBCCDRAGON = 1#青龙
	ENGBCCTIGER = 2#白虎
	ENGBCCPHENIX = 3#朱雀
	ENGBCCTURTLE = 4#玄武
	ENGBCCMAX = 5#最大阵眼
end

#帮派灵山状态
class ENGBMountainState
	ENGBMSNONE = 0#无效状态
	ENGBMSGATE = 1#城门战
	ENGBMSCAVE = 2#洞府战
	ENGBMSEND = 3#战斗结束
	ENGBMSMAX = 4#最大状态
end

#帮派战战斗方向
class ENGBSide
	ENGBSIDEATTACKER = 0#进攻方
	ENGBSIDEDEFENCER = 1#防守方
	ENGBSIDEINVALID = 2#无效方
end

#帮派战返回结果
class ENGBResult
	ENGBRSUCCESS = 0#成功
	ENGBRFAILED = 1#失败
	ENGBRWRONGTIME = 2#时间段错误
	ENGBRNOTINBATTLE = 3#不在帮派战中
	ENGBRNOGUILD = 4#不存在帮派
	ENGBRINVALIDMOUNTAIN = 5#错误的灵山
	ENGBRNOAUTHORITY = 6#权限不足
end

#帮派战进入结果
class ENGBEnterResult
	ENGBERSUCCESS = 0#进入成功
	ENGBERFAILED = 1#进入失败
	ENGBERNOTINGUILD = 2#进入时不存在帮派
	ENGBERREPEAT = 3#进入重复
	ENGBERWRONGTIME = 4#不在进入时段
	ENGBERGUILDLEVEL = 5#帮派等级过低
	ENGBERESCAPE = 6#刚刚从战斗中逃离
	ENGBERGUILDWRONG = 7#您的帮派未入围洞府战
end

#帮派战城门战攻击返回结果
class ENGBGateAttackResult
	ENGBGARSUCCESS = 0#攻击成功
	ENGBGARFAILED = 1#攻击失败
	ENGBGARTARGETISDEAD = 2#目标已经死亡
	ENGBGARSELFISDEAD = 3#还在死亡冷却中
	ENGBGARWRONGTIME = 4#不在正确的时间段内
	ENGBGARDEFENCER = 5#防守方不能攻击城门
	ENGBGARDEFENCERALIVE = 6#存在防守方成员
end

#帮派战购买傀儡返回结果
class ENGBBuyPuppetResult
	ENGBBPRSUCCESS = 0#购买成功
	ENGBBPRFAILED = 1#购买失败
	ENGBBPRLACKOFMONEY = 2#货币不足
	ENGBBPRCOUNTLIMIT = 3#已经到达上限
	ENGBBPRWRONGTIME = 4#不在正确的时间段内
	ENGBBPRDEFENCER = 5#防守方不能购买傀儡
end

#帮派战买活返回结果
class ENGBClearDeadCDResult
	ENGBCDCDRSUCCESS = 0#买活成功
	ENGBCDCDRFAILED = 1#买活失败
	ENGBCDCDRISALIVE = 2#已经复活
	ENGBCDCDRWRONGTIME = 3#不在正确的时间段内
end

#帮派战洞府战战斗返回结果
class ENGBCaveAttackResult
	ENGBCARSUCCESS = 0#战斗成功
	ENGBCARFAILED = 1#战斗失败
	ENGBCARBECAPTURED = 2#已被他人占领
	ENGBCARCOUNTLIMIT = 3#已经到达上限
	ENGBCARWRONGTIME = 4#不在正确的时间段内
	ENGBCARTARGETDEAD = 5#目标已经死亡
	ENGBCARNOTINCORE = 6#不在阵眼上
	ENGBCARINCORE = 7#在阵眼上无法攻击
	ENGBCARSELFISDEAD = 8#还在死亡冷却中
	ENGBCARSELFSIDE = 9#不能攻击自己人
end

#帮派战退出结果
class ENGBQuitResult
	ENGBQUITSUCCESS = 0#退出成功
	ENGBQUITFAILED = 1#退出失败
end

#帮派战战斗相关结果
class ENGBBattleResult
	ENGBBATTLESUCCESS = 0#战斗成功
	ENGBBATTLEFAILED = 1#战斗失败
end

#傀儡信息
class SPuppetInfo
	attr_accessor:byIndex #(UINT8)所属站位(0,1,2; 0为系统战争傀儡)
	attr_accessor:qwOwnerID #(UINT64)拥有者ID
	attr_accessor:dwNextAttackTime #(UINT32)下一次攻击时间

	#构造函数
	def initialize
		@byIndex = 0
		@qwOwnerID = 0
		@dwNextAttackTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byIndex = @byIndex
		obj.qwOwnerID = @qwOwnerID
		obj.dwNextAttackTime = @dwNextAttackTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPuppetInfo.new
		s.byIndex = ByteUtil::readUINT8(data)
		s.qwOwnerID = ByteUtil::readUINT64(data)
		s.dwNextAttackTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPuppetInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byIndex)
		ByteUtil::writeUINT64(data, @qwOwnerID)
		ByteUtil::writeUINT32(data, @dwNextAttackTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家信息
class SPlayerInfo
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:strName #(string)玩家姓名
	attr_accessor:eJob #(枚类型：ProtoCommon::ECareerType)职业
	attr_accessor:eSex #(枚类型：ProtoCommon::ESexType)性别
	attr_accessor:byQuality #(UINT8)品质
	attr_accessor:qwGuildID #(UINT64)帮派ID
	attr_accessor:eSide #(枚举类型：ENGBSide)自己所在方向
	attr_accessor:dwMaxHP #(UINT32)最大血量
	attr_accessor:dwHP #(UINT32)当前血量
	attr_accessor:dwDeadTime #(UINT32)死亡时间（复活所需时间）

	#构造函数
	def initialize
		@qwRoleID = 0
		@strName = ''
		@eJob = 0
		@eSex = 0
		@byQuality = 0
		@qwGuildID = 0
		@eSide = 0
		@dwMaxHP = 0
		@dwHP = 0
		@dwDeadTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.strName = @strName
		obj.eJob = @eJob
		obj.eSex = @eSex
		obj.byQuality = @byQuality
		obj.qwGuildID = @qwGuildID
		obj.eSide = @eSide
		obj.dwMaxHP = @dwMaxHP
		obj.dwHP = @dwHP
		obj.dwDeadTime = @dwDeadTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPlayerInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.eJob = ByteUtil::readUINT8(data)
		s.eSex = ByteUtil::readUINT8(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.qwGuildID = ByteUtil::readUINT64(data)
		s.eSide = ByteUtil::readUINT8(data)
		s.dwMaxHP = ByteUtil::readUINT32(data)
		s.dwHP = ByteUtil::readUINT32(data)
		s.dwDeadTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPlayerInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @eJob)
		ByteUtil::writeUINT8(data, @eSex)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT64(data, @qwGuildID)
		ByteUtil::writeUINT8(data, @eSide)
		ByteUtil::writeUINT32(data, @dwMaxHP)
		ByteUtil::writeUINT32(data, @dwHP)
		ByteUtil::writeUINT32(data, @dwDeadTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#灵山面板信息
class SMountainPanelInfo
	attr_accessor:eMountainType #(枚举类型：ENGBMountain)灵山类型
	attr_accessor:eState #(枚举类型：ENGBMountainState)灵山状态
	attr_accessor:qwGuildID #(UINT64)当前占领帮派ID
	attr_accessor:strGuildName #(string)当前占领帮派名称
	attr_accessor:wGuildLevel #(UINT16)当前占领帮派等级
	attr_accessor:strGuildOwnerName #(string)当前占领帮派帮主名称
	attr_accessor:dwGuildOwnCount #(UINT32)当前占领帮派占领次数
	attr_accessor:vecAttackGuildID #(UINT64数组)（洞府战）攻击帮派ID

	#构造函数
	def initialize
		@eMountainType = 0
		@eState = 0
		@qwGuildID = 0
		@strGuildName = ''
		@wGuildLevel = 0
		@strGuildOwnerName = ''
		@dwGuildOwnCount = 0
		@vecAttackGuildID = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eMountainType = @eMountainType
		obj.eState = @eState
		obj.qwGuildID = @qwGuildID
		obj.strGuildName = @strGuildName
		obj.wGuildLevel = @wGuildLevel
		obj.strGuildOwnerName = @strGuildOwnerName
		obj.dwGuildOwnCount = @dwGuildOwnCount
		obj.vecAttackGuildID = @vecAttackGuildID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMountainPanelInfo.new
		s.eMountainType = ByteUtil::readUINT8(data)
		s.eState = ByteUtil::readUINT8(data)
		s.qwGuildID = ByteUtil::readUINT64(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		s.wGuildLevel = ByteUtil::readUINT16(data)
		s.strGuildOwnerName = ByteUtil::readSTRING(data)
		s.dwGuildOwnCount = ByteUtil::readUINT32(data)
		s.vecAttackGuildID = ByteUtil::readVecUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMountainPanelInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eMountainType)
		ByteUtil::writeUINT8(data, @eState)
		ByteUtil::writeUINT64(data, @qwGuildID)
		ByteUtil::writeSTRING(data, @strGuildName)
		ByteUtil::writeUINT16(data, @wGuildLevel)
		ByteUtil::writeSTRING(data, @strGuildOwnerName)
		ByteUtil::writeUINT32(data, @dwGuildOwnCount)
		ByteUtil::writeVecUINT64(data, @vecAttackGuildID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#面板玩家信息
class SPlayerPanelInfo
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:strName #(string)玩家姓名
	attr_accessor:byLevel #(UINT8)玩家等级
	attr_accessor:byQuality #(UINT8)品质
	attr_accessor:qwGuildID #(UINT64)帮派ID
	attr_accessor:eSide #(枚举类型：ENGBSide)自己所在方向
	attr_accessor:strGuildName #(string)帮派名称
	attr_accessor:byHPP #(UINT8)剩余生命值百分比
	attr_accessor:dwMaxHP #(UINT32)最大血量
	attr_accessor:dwHP #(UINT32)当前血量

	#构造函数
	def initialize
		@qwRoleID = 0
		@strName = ''
		@byLevel = 0
		@byQuality = 0
		@qwGuildID = 0
		@eSide = 0
		@strGuildName = ''
		@byHPP = 0
		@dwMaxHP = 0
		@dwHP = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.strName = @strName
		obj.byLevel = @byLevel
		obj.byQuality = @byQuality
		obj.qwGuildID = @qwGuildID
		obj.eSide = @eSide
		obj.strGuildName = @strGuildName
		obj.byHPP = @byHPP
		obj.dwMaxHP = @dwMaxHP
		obj.dwHP = @dwHP
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPlayerPanelInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.qwGuildID = ByteUtil::readUINT64(data)
		s.eSide = ByteUtil::readUINT8(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		s.byHPP = ByteUtil::readUINT8(data)
		s.dwMaxHP = ByteUtil::readUINT32(data)
		s.dwHP = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPlayerPanelInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT64(data, @qwGuildID)
		ByteUtil::writeUINT8(data, @eSide)
		ByteUtil::writeSTRING(data, @strGuildName)
		ByteUtil::writeUINT8(data, @byHPP)
		ByteUtil::writeUINT32(data, @dwMaxHP)
		ByteUtil::writeUINT32(data, @dwHP)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#占领历史信息
class SOwnerHistoryInfo
	attr_accessor:eMountainType #(枚举类型：ENGBMountain)灵山类型
	attr_accessor:qwGuildID #(UINT64)当前占领帮派ID
	attr_accessor:strGuildName #(string)当前占领帮派名称
	attr_accessor:strGuildOwnerName #(string)当前占领帮派帮主名称
	attr_accessor:dwTime #(UINT32)占领时间

	#构造函数
	def initialize
		@eMountainType = 0
		@qwGuildID = 0
		@strGuildName = ''
		@strGuildOwnerName = ''
		@dwTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eMountainType = @eMountainType
		obj.qwGuildID = @qwGuildID
		obj.strGuildName = @strGuildName
		obj.strGuildOwnerName = @strGuildOwnerName
		obj.dwTime = @dwTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SOwnerHistoryInfo.new
		s.eMountainType = ByteUtil::readUINT8(data)
		s.qwGuildID = ByteUtil::readUINT64(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		s.strGuildOwnerName = ByteUtil::readSTRING(data)
		s.dwTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SOwnerHistoryInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eMountainType)
		ByteUtil::writeUINT64(data, @qwGuildID)
		ByteUtil::writeSTRING(data, @strGuildName)
		ByteUtil::writeSTRING(data, @strGuildOwnerName)
		ByteUtil::writeUINT32(data, @dwTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#灵山城门信息
class SMountainGateInfo
	attr_accessor:dwRemainTime #(UINT32)开始倒计时
	attr_accessor:dwGateMaxHP #(UINT32)城门总血量
	attr_accessor:dwGateHP #(UINT32)城门剩余血量
	attr_accessor:vecPuppetInfo #(SPuppetInfo的数组)傀儡信息
	attr_accessor:eSelfSide #(枚举类型：ENGBSide)自己所在方向
	attr_accessor:sSelfInfo #(类类型：SPlayerInfo)自己的信息
	attr_accessor:vecPlayerInfo #(SPlayerPanelInfo的数组)对面玩家信息

	#构造函数
	def initialize
		@dwRemainTime = 0
		@dwGateMaxHP = 0
		@dwGateHP = 0
		@vecPuppetInfo = Array.new
		@eSelfSide = 0
		@sSelfInfo = SPlayerInfo.new
		@vecPlayerInfo = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwRemainTime = @dwRemainTime
		obj.dwGateMaxHP = @dwGateMaxHP
		obj.dwGateHP = @dwGateHP
		obj.vecPuppetInfo = @vecPuppetInfo
		obj.eSelfSide = @eSelfSide
		obj.sSelfInfo = @sSelfInfo
		obj.vecPlayerInfo = @vecPlayerInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMountainGateInfo.new
		s.dwRemainTime = ByteUtil::readUINT32(data)
		s.dwGateMaxHP = ByteUtil::readUINT32(data)
		s.dwGateHP = ByteUtil::readUINT32(data)
		s.vecPuppetInfo = SPuppetInfo::vectorFromStream(data)
		s.eSelfSide = ByteUtil::readUINT8(data)
		s.sSelfInfo = SPlayerInfo::fromStream(data)
		s.vecPlayerInfo = SPlayerPanelInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMountainGateInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwRemainTime)
		ByteUtil::writeUINT32(data, @dwGateMaxHP)
		ByteUtil::writeUINT32(data, @dwGateHP)
		SPuppetInfo::vectorToStream(data, @vecPuppetInfo)
		ByteUtil::writeUINT8(data, @eSelfSide)
		@sSelfInfo.toStream(data)
		SPlayerPanelInfo::vectorToStream(data, @vecPlayerInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#洞府阵眼信息
class SCaveCoreInfo
	attr_accessor:eType #(枚举类型：ENGBCaveCore)阵眼类型
	attr_accessor:vecPlayerInfo #(SPlayerPanelInfo的数组)占领者信息（数量只能为0/1）

	#构造函数
	def initialize
		@eType = 0
		@vecPlayerInfo = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eType = @eType
		obj.vecPlayerInfo = @vecPlayerInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SCaveCoreInfo.new
		s.eType = ByteUtil::readUINT8(data)
		s.vecPlayerInfo = SPlayerPanelInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SCaveCoreInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eType)
		SPlayerPanelInfo::vectorToStream(data, @vecPlayerInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#洞府战攻击帮派信息
class SCaveAttackGuildInfo
	attr_accessor:qwGuildID #(UINT64)帮派ID
	attr_accessor:strName #(string)帮派姓名
	attr_accessor:dwMaxEnergy #(UINT32)能量上限
	attr_accessor:dwEnergy #(UINT32)当前能量

	#构造函数
	def initialize
		@qwGuildID = 0
		@strName = ''
		@dwMaxEnergy = 0
		@dwEnergy = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwGuildID = @qwGuildID
		obj.strName = @strName
		obj.dwMaxEnergy = @dwMaxEnergy
		obj.dwEnergy = @dwEnergy
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SCaveAttackGuildInfo.new
		s.qwGuildID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.dwMaxEnergy = ByteUtil::readUINT32(data)
		s.dwEnergy = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SCaveAttackGuildInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwGuildID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT32(data, @dwMaxEnergy)
		ByteUtil::writeUINT32(data, @dwEnergy)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#洞府战具体信息
class SCaveInfo
	attr_accessor:dwRemainTime #(UINT32)开始倒计时
	attr_accessor:eSelfSide #(枚举类型：ENGBSide)自己所在方向
	attr_accessor:vecCaveCoreInfo #(SCaveCoreInfo的数组)阵眼信息
	attr_accessor:vecCaveAttackGuildInfo #(SCaveAttackGuildInfo的数组)洞府攻击帮派信息
	attr_accessor:sSelfInfo #(类类型：SPlayerInfo)自己的信息
	attr_accessor:vecPlayerInfo #(SPlayerPanelInfo的数组)对面玩家信息

	#构造函数
	def initialize
		@dwRemainTime = 0
		@eSelfSide = 0
		@vecCaveCoreInfo = Array.new
		@vecCaveAttackGuildInfo = Array.new
		@sSelfInfo = SPlayerInfo.new
		@vecPlayerInfo = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwRemainTime = @dwRemainTime
		obj.eSelfSide = @eSelfSide
		obj.vecCaveCoreInfo = @vecCaveCoreInfo
		obj.vecCaveAttackGuildInfo = @vecCaveAttackGuildInfo
		obj.sSelfInfo = @sSelfInfo
		obj.vecPlayerInfo = @vecPlayerInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SCaveInfo.new
		s.dwRemainTime = ByteUtil::readUINT32(data)
		s.eSelfSide = ByteUtil::readUINT8(data)
		s.vecCaveCoreInfo = SCaveCoreInfo::vectorFromStream(data)
		s.vecCaveAttackGuildInfo = SCaveAttackGuildInfo::vectorFromStream(data)
		s.sSelfInfo = SPlayerInfo::fromStream(data)
		s.vecPlayerInfo = SPlayerPanelInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SCaveInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwRemainTime)
		ByteUtil::writeUINT8(data, @eSelfSide)
		SCaveCoreInfo::vectorToStream(data, @vecCaveCoreInfo)
		SCaveAttackGuildInfo::vectorToStream(data, @vecCaveAttackGuildInfo)
		@sSelfInfo.toStream(data)
		SPlayerPanelInfo::vectorToStream(data, @vecPlayerInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#排行榜帮派信息
class SGuildRankInfo
	attr_accessor:wRank #(UINT16)排名
	attr_accessor:qwGuildID #(UINT64)帮派ID
	attr_accessor:strName #(string)帮派姓名
	attr_accessor:dwScore #(UINT32)战功

	#构造函数
	def initialize
		@wRank = 0
		@qwGuildID = 0
		@strName = ''
		@dwScore = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wRank = @wRank
		obj.qwGuildID = @qwGuildID
		obj.strName = @strName
		obj.dwScore = @dwScore
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildRankInfo.new
		s.wRank = ByteUtil::readUINT16(data)
		s.qwGuildID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.dwScore = ByteUtil::readUINT32(data)
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

	def toStream(data)
		ByteUtil::writeUINT16(data, @wRank)
		ByteUtil::writeUINT64(data, @qwGuildID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT32(data, @dwScore)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#排行榜帮派信息
class SGuildMemberRankInfo
	attr_accessor:wRank #(UINT16)排名
	attr_accessor:qwGuildID #(UINT64)帮派ID
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:strName #(string)玩家姓名
	attr_accessor:dwScore #(UINT32)战功

	#构造函数
	def initialize
		@wRank = 0
		@qwGuildID = 0
		@qwRoleID = 0
		@strName = ''
		@dwScore = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wRank = @wRank
		obj.qwGuildID = @qwGuildID
		obj.qwRoleID = @qwRoleID
		obj.strName = @strName
		obj.dwScore = @dwScore
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildMemberRankInfo.new
		s.wRank = ByteUtil::readUINT16(data)
		s.qwGuildID = ByteUtil::readUINT64(data)
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.dwScore = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildMemberRankInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wRank)
		ByteUtil::writeUINT64(data, @qwGuildID)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT32(data, @dwScore)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#排行榜个人信息
class SPlayerRankInfo
	attr_accessor:wRank #(UINT16)排名
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:strName #(string)玩家姓名
	attr_accessor:dwScore #(UINT32)战功

	#构造函数
	def initialize
		@wRank = 0
		@qwRoleID = 0
		@strName = ''
		@dwScore = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wRank = @wRank
		obj.qwRoleID = @qwRoleID
		obj.strName = @strName
		obj.dwScore = @dwScore
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPlayerRankInfo.new
		s.wRank = ByteUtil::readUINT16(data)
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.dwScore = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPlayerRankInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wRank)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT32(data, @dwScore)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetState:获取帮派战状态]的返回的参数组成的结构体
class SRetParam_GetState
	attr_accessor:eState#(枚举类型：ENGBState)当前帮派战状态
	attr_accessor:dwRemainTime#(UINT32)新帮派战剩余时间
	attr_accessor:vecInfo#(SMountainPanelInfo的数组)各个灵山信息
	attr_accessor:eMountainType#(枚举类型：ENGBMountain)自己所在战斗信息

	#构造函数
	def initialize
		@eState = 0
		@dwRemainTime = 0
		@vecInfo = Array.new
		@eMountainType = 0
	end
end

#函数[GetOwnerHistory:获取历届占领帮会]的返回的参数组成的结构体
class SRetParam_GetOwnerHistory
	attr_accessor:vecInfo#(SOwnerHistoryInfo的数组)理解帮派信息

	#构造函数
	def initialize
		@vecInfo = Array.new
	end
end

#函数[Enter:进入帮派战(进入准备场地)]的返回的参数组成的结构体
class SRetParam_Enter
	attr_accessor:eResult#(枚举类型：ENGBEnterResult)进入结果
	attr_accessor:eState#(枚举类型：ENGBMountainState)灵山状态

	#构造函数
	def initialize
		@eResult = 0
		@eState = 0
	end
end

#函数[GateAttackPlayer:城门战攻击玩家/城门]的返回的参数组成的结构体
class SRetParam_GateAttackPlayer
	attr_accessor:eResult#(枚举类型：ENGBGateAttackResult)攻击返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[BuyPuppet:购买傀儡]的返回的参数组成的结构体
class SRetParam_BuyPuppet
	attr_accessor:eResult#(枚举类型：ENGBBuyPuppetResult)购买结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetGateInfo:获取城门战信息]的返回的参数组成的结构体
class SRetParam_GetGateInfo
	attr_accessor:eResult#(枚举类型：ENGBResult)返回结果
	attr_accessor:sInfo#(类类型：SMountainGateInfo)城门信息

	#构造函数
	def initialize
		@eResult = 0
		@sInfo = SMountainGateInfo.new
	end
end

#函数[CaveCapture:洞府战占领阵眼]的返回的参数组成的结构体
class SRetParam_CaveCapture
	attr_accessor:eResult#(枚举类型：ENGBCaveAttackResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[CaveAttack:洞府战攻击他人]的返回的参数组成的结构体
class SRetParam_CaveAttack
	attr_accessor:eResult#(枚举类型：ENGBCaveAttackResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[CaveRest:洞府战从阵眼下阵]的返回的参数组成的结构体
class SRetParam_CaveRest
	attr_accessor:eResult#(枚举类型：ENGBCaveAttackResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetCaveInfo:获取洞府战信息]的返回的参数组成的结构体
class SRetParam_GetCaveInfo
	attr_accessor:eResult#(枚举类型：ENGBResult)返回结果
	attr_accessor:sInfo#(类类型：SCaveInfo)洞府信息

	#构造函数
	def initialize
		@eResult = 0
		@sInfo = SCaveInfo.new
	end
end

#函数[ClearDeadCD:立即买活]的返回的参数组成的结构体
class SRetParam_ClearDeadCD
	attr_accessor:eResult#(枚举类型：ENGBClearDeadCDResult)返回类型

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[Quit:帮派战退出]的返回的参数组成的结构体
class SRetParam_Quit
	attr_accessor:eResult#(枚举类型：ENGBQuitResult)退出返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetGuildRankInfo:获取战功榜帮派排名信息]的返回的参数组成的结构体
class SRetParam_GetGuildRankInfo
	attr_accessor:eResult#(枚举类型：ENGBResult)返回结果
	attr_accessor:dwMaxCount#(UINT32)最大排名数量
	attr_accessor:dwCurIndex#(UINT32)当前排名索引
	attr_accessor:vecInfo#(SGuildRankInfo的数组)排名信息

	#构造函数
	def initialize
		@eResult = 0
		@dwMaxCount = 0
		@dwCurIndex = 0
		@vecInfo = Array.new
	end
end

#函数[GetGuildMemberRankInfo:获取战功榜帮派成员排名信息]的返回的参数组成的结构体
class SRetParam_GetGuildMemberRankInfo
	attr_accessor:eResult#(枚举类型：ENGBResult)返回结果
	attr_accessor:dwMaxCount#(UINT32)最大排名数量
	attr_accessor:dwCurIndex#(UINT32)当前排名索引
	attr_accessor:vecInfo#(SGuildMemberRankInfo的数组)排名信息

	#构造函数
	def initialize
		@eResult = 0
		@dwMaxCount = 0
		@dwCurIndex = 0
		@vecInfo = Array.new
	end
end

#函数[GetPlayerRankInfo:获取战功榜个人排名信息]的返回的参数组成的结构体
class SRetParam_GetPlayerRankInfo
	attr_accessor:eResult#(枚举类型：ENGBResult)返回结果
	attr_accessor:dwMaxCount#(UINT32)最大排名数量
	attr_accessor:dwCurIndex#(UINT32)当前排名索引
	attr_accessor:vecInfo#(SPlayerRankInfo的数组)排名信息

	#构造函数
	def initialize
		@eResult = 0
		@dwMaxCount = 0
		@dwCurIndex = 0
		@vecInfo = Array.new
	end
end

#函数[CallMember:召集帮众广播]的返回的参数组成的结构体
class SRetParam_CallMember
	attr_accessor:eResult#(枚举类型：ENGBResult)召集结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：新帮派战相关协议
class NewGuildBattleProtBase < ProtocolBase
	#以下为发送函数
	#发送：获取帮派战状态
	def send_GetState(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取历届占领帮会
	def send_GetOwnerHistory(
		eMountainType #(枚举类型：ENGBMountain)灵山类型
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eMountainType)
		return @svrHandler.sendPacket(data)
	end

	#发送：进入帮派战(进入准备场地)
	def send_Enter(
		eMountainType #(枚举类型：ENGBMountain)灵山类型
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eMountainType)
		return @svrHandler.sendPacket(data)
	end

	#发送：城门战攻击玩家/城门
	def send_GateAttackPlayer(
		qwTargetRoleID #(UINT64)目标唯一ID(0为城墙)
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwTargetRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：购买傀儡
	def send_BuyPuppet(
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取城门战信息
	def send_GetGateInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：洞府战占领阵眼
	def send_CaveCapture(
		eCaveType #(枚举类型：ENGBCaveCore)阵眼类型
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eCaveType)
		return @svrHandler.sendPacket(data)
	end

	#发送：洞府战攻击他人
	def send_CaveAttack(
		qwTargetRoleID #(UINT64)目标唯一ID
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwTargetRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：洞府战从阵眼下阵
	def send_CaveRest(
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取洞府战信息
	def send_GetCaveInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 10);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：立即买活
	def send_ClearDeadCD(
	)
		sessionID = @sessionMgr.getNewSession(self, 11);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派战退出
	def send_Quit(
	)
		sessionID = @sessionMgr.getNewSession(self, 12);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取战功榜帮派排名信息
	def send_GetGuildRankInfo(
		dwIndex,  #(UINT32)排名索引
		dwCount #(UINT32)排名个数
	)
		sessionID = @sessionMgr.getNewSession(self, 13);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 13
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwIndex)
		ByteUtil::writeUINT32(data, dwCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取战功榜帮派成员排名信息
	def send_GetGuildMemberRankInfo(
		dwIndex,  #(UINT32)排名索引
		dwCount #(UINT32)排名个数
	)
		sessionID = @sessionMgr.getNewSession(self, 14);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 14
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwIndex)
		ByteUtil::writeUINT32(data, dwCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取战功榜个人排名信息
	def send_GetPlayerRankInfo(
		dwIndex,  #(UINT32)排名索引
		dwCount #(UINT32)排名个数
	)
		sessionID = @sessionMgr.getNewSession(self, 15);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 15
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwIndex)
		ByteUtil::writeUINT32(data, dwCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：召集帮众广播
	def send_CallMember(
	)
		sessionID = @sessionMgr.getNewSession(self, 16);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 16
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：状态变更广播
	def onRecv_StateNotify(
		eState, #(枚举类型：ENGBState)当前帮派战状态
		dwRemainTime, #(UINT32)新帮派战剩余时间
		vecInfo #(SMountainPanelInfo的数组)各个灵山信息
	)
		raise NotImplementedError
	end
	#接收：城门战广播
	def onRecv_GateInfoNotify(
		sInfo #(类类型：SMountainGateInfo)城门信息
	)
		raise NotImplementedError
	end
	#接收：城门战列表通知
	def onRecv_GateListNotify(
		vecInfo #(SPlayerPanelInfo的数组)城门玩家列表信息通知
	)
		raise NotImplementedError
	end
	#接收：城门被攻破广播
	def onRecv_GateBrokenNotify(
		eMountainType, #(枚举类型：ENGBMountain)灵山类型
		vecAttackGuildID #(UINT64数组)（洞府战）攻击帮派ID
	)
		raise NotImplementedError
	end
	#接收：洞府战广播
	def onRecv_CaveInfoNotify(
		sInfo #(类类型：SCaveInfo)洞府具体信息
	)
		raise NotImplementedError
	end
	#接收：洞府战列表通知
	def onRecv_CaveListNotify(
		vecInfo #(SPlayerPanelInfo的数组)洞府玩家列表信息通知
	)
		raise NotImplementedError
	end
	#接收：洞府战阵眼信息通知
	def onRecv_CaveCoreNotify(
		vecCaveCoreInfo #(SCaveCoreInfo的数组)阵眼信息
	)
		raise NotImplementedError
	end
	#接收：洞府战被占领通知
	def onRecv_CaveCapture(
		eMountainType, #(枚举类型：ENGBMountain)灵山类型
		strGuildName #(string)当前占领帮派名称
	)
		raise NotImplementedError
	end
	#接收：战斗日志通知
	def onRecv_BattleLogNotify(
		wMsgID, #(UINT16)消息ID
		vecStr #(string数组)聊天信息参数
	)
		raise NotImplementedError
	end
	#接收：战斗日志通知
	def onRecv_PuppetAttackNotify(
		byIndex #(UINT8)所属站位(0,1,2; 0为系统战争傀儡)
	)
		raise NotImplementedError
	end
	#接收：战功榜帮派排名信息广播
	def onRecv_GuildRankInfoNotify(
		dwMaxCount, #(UINT32)最大排名数量
		dwCurIndex, #(UINT32)当前排名索引
		vecInfo #(SGuildRankInfo的数组)排名信息
	)
		raise NotImplementedError
	end
	#接收：战功榜帮派成员排名信息广播
	def onRecv_GuildMemberRankInfoNotify(
		dwMaxCount, #(UINT32)最大排名数量
		dwCurIndex, #(UINT32)当前排名索引
		vecInfo #(SGuildMemberRankInfo的数组)排名信息
	)
		raise NotImplementedError
	end
	#接收：战功榜个人排名信息广播
	def onRecv_PlayerRankInfoNotify(
		dwMaxCount, #(UINT32)最大排名数量
		dwCurIndex, #(UINT32)当前排名索引
		vecInfo #(SPlayerRankInfo的数组)排名信息
	)
		raise NotImplementedError
	end
	#接收：召集帮众广播
	def onRecv_CallMemberNotify(
		byQuality, #(UINT8)品质
		strName #(string)名字
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取帮派战状态
	def onReturn_GetState(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetState)返回的参数
	)
	end

	#返回：获取历届占领帮会
	def onReturn_GetOwnerHistory(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetOwnerHistory)返回的参数
	)
	end

	#返回：进入帮派战(进入准备场地)
	def onReturn_Enter(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Enter)返回的参数
	)
	end

	#返回：城门战攻击玩家/城门
	def onReturn_GateAttackPlayer(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GateAttackPlayer)返回的参数
	)
	end

	#返回：购买傀儡
	def onReturn_BuyPuppet(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuyPuppet)返回的参数
	)
	end

	#返回：获取城门战信息
	def onReturn_GetGateInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetGateInfo)返回的参数
	)
	end

	#返回：洞府战占领阵眼
	def onReturn_CaveCapture(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_CaveCapture)返回的参数
	)
	end

	#返回：洞府战攻击他人
	def onReturn_CaveAttack(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_CaveAttack)返回的参数
	)
	end

	#返回：洞府战从阵眼下阵
	def onReturn_CaveRest(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_CaveRest)返回的参数
	)
	end

	#返回：获取洞府战信息
	def onReturn_GetCaveInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetCaveInfo)返回的参数
	)
	end

	#返回：立即买活
	def onReturn_ClearDeadCD(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ClearDeadCD)返回的参数
	)
	end

	#返回：帮派战退出
	def onReturn_Quit(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Quit)返回的参数
	)
	end

	#返回：获取战功榜帮派排名信息
	def onReturn_GetGuildRankInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetGuildRankInfo)返回的参数
	)
	end

	#返回：获取战功榜帮派成员排名信息
	def onReturn_GetGuildMemberRankInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetGuildMemberRankInfo)返回的参数
	)
	end

	#返回：获取战功榜个人排名信息
	def onReturn_GetPlayerRankInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetPlayerRankInfo)返回的参数
	)
	end

	#返回：召集帮众广播
	def onReturn_CallMember(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_CallMember)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：状态变更广播
	def _doRecv_StateNotify(data)
		eState = ByteUtil::readUINT8(data)
		dwRemainTime = ByteUtil::readUINT32(data)
		vecInfo = SMountainPanelInfo::vectorFromStream(data)
		return onRecv_StateNotify(eState, dwRemainTime, vecInfo)
	end

	#接收处理：城门战广播
	def _doRecv_GateInfoNotify(data)
		sInfo = SMountainGateInfo::fromStream(data)
		return onRecv_GateInfoNotify(sInfo)
	end

	#接收处理：城门战列表通知
	def _doRecv_GateListNotify(data)
		vecInfo = SPlayerPanelInfo::vectorFromStream(data)
		return onRecv_GateListNotify(vecInfo)
	end

	#接收处理：城门被攻破广播
	def _doRecv_GateBrokenNotify(data)
		eMountainType = ByteUtil::readUINT8(data)
		vecAttackGuildID = ByteUtil::readVecUINT64(data)
		return onRecv_GateBrokenNotify(eMountainType, vecAttackGuildID)
	end

	#接收处理：洞府战广播
	def _doRecv_CaveInfoNotify(data)
		sInfo = SCaveInfo::fromStream(data)
		return onRecv_CaveInfoNotify(sInfo)
	end

	#接收处理：洞府战列表通知
	def _doRecv_CaveListNotify(data)
		vecInfo = SPlayerPanelInfo::vectorFromStream(data)
		return onRecv_CaveListNotify(vecInfo)
	end

	#接收处理：洞府战阵眼信息通知
	def _doRecv_CaveCoreNotify(data)
		vecCaveCoreInfo = SCaveCoreInfo::vectorFromStream(data)
		return onRecv_CaveCoreNotify(vecCaveCoreInfo)
	end

	#接收处理：洞府战被占领通知
	def _doRecv_CaveCapture(data)
		eMountainType = ByteUtil::readUINT8(data)
		strGuildName = ByteUtil::readSTRING(data)
		return onRecv_CaveCapture(eMountainType, strGuildName)
	end

	#接收处理：战斗日志通知
	def _doRecv_BattleLogNotify(data)
		wMsgID = ByteUtil::readUINT16(data)
		vecStr = ByteUtil::readVecSTRING(data)
		return onRecv_BattleLogNotify(wMsgID, vecStr)
	end

	#接收处理：战斗日志通知
	def _doRecv_PuppetAttackNotify(data)
		byIndex = ByteUtil::readUINT8(data)
		return onRecv_PuppetAttackNotify(byIndex)
	end

	#接收处理：战功榜帮派排名信息广播
	def _doRecv_GuildRankInfoNotify(data)
		dwMaxCount = ByteUtil::readUINT32(data)
		dwCurIndex = ByteUtil::readUINT32(data)
		vecInfo = SGuildRankInfo::vectorFromStream(data)
		return onRecv_GuildRankInfoNotify(dwMaxCount, dwCurIndex, vecInfo)
	end

	#接收处理：战功榜帮派成员排名信息广播
	def _doRecv_GuildMemberRankInfoNotify(data)
		dwMaxCount = ByteUtil::readUINT32(data)
		dwCurIndex = ByteUtil::readUINT32(data)
		vecInfo = SGuildMemberRankInfo::vectorFromStream(data)
		return onRecv_GuildMemberRankInfoNotify(dwMaxCount, dwCurIndex, vecInfo)
	end

	#接收处理：战功榜个人排名信息广播
	def _doRecv_PlayerRankInfoNotify(data)
		dwMaxCount = ByteUtil::readUINT32(data)
		dwCurIndex = ByteUtil::readUINT32(data)
		vecInfo = SPlayerRankInfo::vectorFromStream(data)
		return onRecv_PlayerRankInfoNotify(dwMaxCount, dwCurIndex, vecInfo)
	end

	#接收处理：召集帮众广播
	def _doRecv_CallMemberNotify(data)
		byQuality = ByteUtil::readUINT8(data)
		strName = ByteUtil::readSTRING(data)
		return onRecv_CallMemberNotify(byQuality, strName)
	end

#以下为返回处理函数
	#返回处理：获取帮派战状态
	def _doReturn_GetState(data)
		retParam = SRetParam_GetState.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eState = ByteUtil::readUINT8(data) #(枚举类型：ENGBState)当前帮派战状态
		dwRemainTime = ByteUtil::readUINT32(data) #(UINT32)新帮派战剩余时间
		vecInfo = SMountainPanelInfo::vectorFromStream(data) #(SMountainPanelInfo的数组)各个灵山信息
		eMountainType = ByteUtil::readUINT8(data) #(枚举类型：ENGBMountain)自己所在战斗信息
		retParam.eState = eState
		retParam.dwRemainTime = dwRemainTime
		retParam.vecInfo = vecInfo
		retParam.eMountainType = eMountainType
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetState(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取帮派战状态
	def _onTimeOut_GetState(sessionID)
		retParam = SRetParam_GetState.new;
		onReturn_GetState(2, retParam)
	end

	#返回处理：获取历届占领帮会
	def _doReturn_GetOwnerHistory(data)
		retParam = SRetParam_GetOwnerHistory.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecInfo = SOwnerHistoryInfo::vectorFromStream(data) #(SOwnerHistoryInfo的数组)理解帮派信息
		retParam.vecInfo = vecInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetOwnerHistory(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取历届占领帮会
	def _onTimeOut_GetOwnerHistory(sessionID)
		retParam = SRetParam_GetOwnerHistory.new;
		onReturn_GetOwnerHistory(2, retParam)
	end

	#返回处理：进入帮派战(进入准备场地)
	def _doReturn_Enter(data)
		retParam = SRetParam_Enter.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ENGBEnterResult)进入结果
		eState = ByteUtil::readUINT8(data) #(枚举类型：ENGBMountainState)灵山状态
		retParam.eResult = eResult
		retParam.eState = eState
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_Enter(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：进入帮派战(进入准备场地)
	def _onTimeOut_Enter(sessionID)
		retParam = SRetParam_Enter.new;
		onReturn_Enter(2, retParam)
	end

	#返回处理：城门战攻击玩家/城门
	def _doReturn_GateAttackPlayer(data)
		retParam = SRetParam_GateAttackPlayer.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ENGBGateAttackResult)攻击返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GateAttackPlayer(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：城门战攻击玩家/城门
	def _onTimeOut_GateAttackPlayer(sessionID)
		retParam = SRetParam_GateAttackPlayer.new;
		onReturn_GateAttackPlayer(2, retParam)
	end

	#返回处理：购买傀儡
	def _doReturn_BuyPuppet(data)
		retParam = SRetParam_BuyPuppet.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ENGBBuyPuppetResult)购买结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuyPuppet(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：购买傀儡
	def _onTimeOut_BuyPuppet(sessionID)
		retParam = SRetParam_BuyPuppet.new;
		onReturn_BuyPuppet(2, retParam)
	end

	#返回处理：获取城门战信息
	def _doReturn_GetGateInfo(data)
		retParam = SRetParam_GetGateInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ENGBResult)返回结果
		sInfo = SMountainGateInfo::fromStream(data) #(类类型：SMountainGateInfo)城门信息
		retParam.eResult = eResult
		retParam.sInfo = sInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetGateInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取城门战信息
	def _onTimeOut_GetGateInfo(sessionID)
		retParam = SRetParam_GetGateInfo.new;
		onReturn_GetGateInfo(2, retParam)
	end

	#返回处理：洞府战占领阵眼
	def _doReturn_CaveCapture(data)
		retParam = SRetParam_CaveCapture.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ENGBCaveAttackResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_CaveCapture(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：洞府战占领阵眼
	def _onTimeOut_CaveCapture(sessionID)
		retParam = SRetParam_CaveCapture.new;
		onReturn_CaveCapture(2, retParam)
	end

	#返回处理：洞府战攻击他人
	def _doReturn_CaveAttack(data)
		retParam = SRetParam_CaveAttack.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ENGBCaveAttackResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_CaveAttack(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：洞府战攻击他人
	def _onTimeOut_CaveAttack(sessionID)
		retParam = SRetParam_CaveAttack.new;
		onReturn_CaveAttack(2, retParam)
	end

	#返回处理：洞府战从阵眼下阵
	def _doReturn_CaveRest(data)
		retParam = SRetParam_CaveRest.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ENGBCaveAttackResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_CaveRest(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：洞府战从阵眼下阵
	def _onTimeOut_CaveRest(sessionID)
		retParam = SRetParam_CaveRest.new;
		onReturn_CaveRest(2, retParam)
	end

	#返回处理：获取洞府战信息
	def _doReturn_GetCaveInfo(data)
		retParam = SRetParam_GetCaveInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ENGBResult)返回结果
		sInfo = SCaveInfo::fromStream(data) #(类类型：SCaveInfo)洞府信息
		retParam.eResult = eResult
		retParam.sInfo = sInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetCaveInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取洞府战信息
	def _onTimeOut_GetCaveInfo(sessionID)
		retParam = SRetParam_GetCaveInfo.new;
		onReturn_GetCaveInfo(2, retParam)
	end

	#返回处理：立即买活
	def _doReturn_ClearDeadCD(data)
		retParam = SRetParam_ClearDeadCD.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ENGBClearDeadCDResult)返回类型
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ClearDeadCD(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：立即买活
	def _onTimeOut_ClearDeadCD(sessionID)
		retParam = SRetParam_ClearDeadCD.new;
		onReturn_ClearDeadCD(2, retParam)
	end

	#返回处理：帮派战退出
	def _doReturn_Quit(data)
		retParam = SRetParam_Quit.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ENGBQuitResult)退出返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_Quit(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：帮派战退出
	def _onTimeOut_Quit(sessionID)
		retParam = SRetParam_Quit.new;
		onReturn_Quit(2, retParam)
	end

	#返回处理：获取战功榜帮派排名信息
	def _doReturn_GetGuildRankInfo(data)
		retParam = SRetParam_GetGuildRankInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ENGBResult)返回结果
		dwMaxCount = ByteUtil::readUINT32(data) #(UINT32)最大排名数量
		dwCurIndex = ByteUtil::readUINT32(data) #(UINT32)当前排名索引
		vecInfo = SGuildRankInfo::vectorFromStream(data) #(SGuildRankInfo的数组)排名信息
		retParam.eResult = eResult
		retParam.dwMaxCount = dwMaxCount
		retParam.dwCurIndex = dwCurIndex
		retParam.vecInfo = vecInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetGuildRankInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取战功榜帮派排名信息
	def _onTimeOut_GetGuildRankInfo(sessionID)
		retParam = SRetParam_GetGuildRankInfo.new;
		onReturn_GetGuildRankInfo(2, retParam)
	end

	#返回处理：获取战功榜帮派成员排名信息
	def _doReturn_GetGuildMemberRankInfo(data)
		retParam = SRetParam_GetGuildMemberRankInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ENGBResult)返回结果
		dwMaxCount = ByteUtil::readUINT32(data) #(UINT32)最大排名数量
		dwCurIndex = ByteUtil::readUINT32(data) #(UINT32)当前排名索引
		vecInfo = SGuildMemberRankInfo::vectorFromStream(data) #(SGuildMemberRankInfo的数组)排名信息
		retParam.eResult = eResult
		retParam.dwMaxCount = dwMaxCount
		retParam.dwCurIndex = dwCurIndex
		retParam.vecInfo = vecInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetGuildMemberRankInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取战功榜帮派成员排名信息
	def _onTimeOut_GetGuildMemberRankInfo(sessionID)
		retParam = SRetParam_GetGuildMemberRankInfo.new;
		onReturn_GetGuildMemberRankInfo(2, retParam)
	end

	#返回处理：获取战功榜个人排名信息
	def _doReturn_GetPlayerRankInfo(data)
		retParam = SRetParam_GetPlayerRankInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ENGBResult)返回结果
		dwMaxCount = ByteUtil::readUINT32(data) #(UINT32)最大排名数量
		dwCurIndex = ByteUtil::readUINT32(data) #(UINT32)当前排名索引
		vecInfo = SPlayerRankInfo::vectorFromStream(data) #(SPlayerRankInfo的数组)排名信息
		retParam.eResult = eResult
		retParam.dwMaxCount = dwMaxCount
		retParam.dwCurIndex = dwCurIndex
		retParam.vecInfo = vecInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetPlayerRankInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取战功榜个人排名信息
	def _onTimeOut_GetPlayerRankInfo(sessionID)
		retParam = SRetParam_GetPlayerRankInfo.new;
		onReturn_GetPlayerRankInfo(2, retParam)
	end

	#返回处理：召集帮众广播
	def _doReturn_CallMember(data)
		retParam = SRetParam_CallMember.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ENGBResult)召集结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_CallMember(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：召集帮众广播
	def _onTimeOut_CallMember(sessionID)
		retParam = SRetParam_CallMember.new;
		onReturn_CallMember(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 68;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_StateNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_GateInfoNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_GateListNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_GateBrokenNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_CaveInfoNotify' #FuncID: 5
		@recvFuncList[5] = '_doRecv_CaveListNotify' #FuncID: 6
		@recvFuncList[6] = '_doRecv_CaveCoreNotify' #FuncID: 7
		@recvFuncList[7] = '_doRecv_CaveCapture' #FuncID: 8
		@recvFuncList[8] = '_doRecv_BattleLogNotify' #FuncID: 9
		@recvFuncList[9] = '_doRecv_PuppetAttackNotify' #FuncID: 10
		@recvFuncList[10] = '_doRecv_GuildRankInfoNotify' #FuncID: 11
		@recvFuncList[11] = '_doRecv_GuildMemberRankInfoNotify' #FuncID: 12
		@recvFuncList[12] = '_doRecv_PlayerRankInfoNotify' #FuncID: 13
		@recvFuncList[13] = '_doRecv_CallMemberNotify' #FuncID: 14

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetState' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetOwnerHistory' #FuncID: 2
		@retFuncList[2] = '_doReturn_Enter' #FuncID: 3
		@retFuncList[3] = '_doReturn_GateAttackPlayer' #FuncID: 4
		@retFuncList[4] = '_doReturn_BuyPuppet' #FuncID: 5
		@retFuncList[5] = '_doReturn_GetGateInfo' #FuncID: 6
		@retFuncList[6] = '_doReturn_CaveCapture' #FuncID: 7
		@retFuncList[7] = '_doReturn_CaveAttack' #FuncID: 8
		@retFuncList[8] = '_doReturn_CaveRest' #FuncID: 9
		@retFuncList[9] = '_doReturn_GetCaveInfo' #FuncID: 10
		@retFuncList[10] = '_doReturn_ClearDeadCD' #FuncID: 11
		@retFuncList[11] = '_doReturn_Quit' #FuncID: 12
		@retFuncList[12] = '_doReturn_GetGuildRankInfo' #FuncID: 13
		@retFuncList[13] = '_doReturn_GetGuildMemberRankInfo' #FuncID: 14
		@retFuncList[14] = '_doReturn_GetPlayerRankInfo' #FuncID: 15
		@retFuncList[15] = '_doReturn_CallMember' #FuncID: 16

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetState' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetOwnerHistory' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_Enter' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_GateAttackPlayer' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_BuyPuppet' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_GetGateInfo' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_CaveCapture' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_CaveAttack' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_CaveRest' #FuncID: 9
		@timeFuncList[9] = '_onTimeOut_GetCaveInfo' #FuncID: 10
		@timeFuncList[10] = '_onTimeOut_ClearDeadCD' #FuncID: 11
		@timeFuncList[11] = '_onTimeOut_Quit' #FuncID: 12
		@timeFuncList[12] = '_onTimeOut_GetGuildRankInfo' #FuncID: 13
		@timeFuncList[13] = '_onTimeOut_GetGuildMemberRankInfo' #FuncID: 14
		@timeFuncList[14] = '_onTimeOut_GetPlayerRankInfo' #FuncID: 15
		@timeFuncList[15] = '_onTimeOut_CallMember' #FuncID: 16
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

