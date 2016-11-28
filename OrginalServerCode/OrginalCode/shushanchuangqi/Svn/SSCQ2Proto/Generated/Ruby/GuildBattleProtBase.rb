#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    GuildBattleProt.rb
#  Purpose:      帮派相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './MapProtBase.rb'

#以下为类型定义

#帮派战当前状态
class EGBState
	EGBSTATENONE = 0#没有开启或即将开启的帮派战
	EGBSTATEPREREADY = 1#帮派战报名即将开启
	EGBSTATEREADY = 2#帮派战即将开启，报名阶段
	EGBSTATEPREPARE = 3#帮派战准备中
	EGBSTATEBATTLE = 4#帮派战进行中
	EGBSTATEBATTLEEND = 5#帮派战战役结束
end

#帮派战玩家状态
class EGBUserState
	EGBUSERSTATENONE = 0#无效状态
	EGBUSERSTATEPREPARE = 1#准备状态(在准备场中)
	EGBUSERSTATEWAIT = 2#待战状态
	EGBUSERSTATEBATTLE = 3#战斗状态
	EGBUSERSTATEDEAD = 4#死亡状态
	EGBUSERSTATEWIN = 5#胜利状态
	EGBUSERSTATEWINTOOMUCH = 6#连胜八场，封刀
	EGBUSERSTATERUNAWAY = 7#逃跑状态
	EGBUSERSTATEMAX = 8#最大状态
end

#帮派战据点
class EGBSpot
	EGBSPOTNONE = 0#无效据点
	EGBSPOTYUZHUFENG = 1#玉柱峰
	EGBSPOTGUANGMINGDING = 2#光明顶
	EGBSPOTSHIWANGFENG = 3#十王峰
	EGBSPOTWANFODING = 4#万佛顶
	EGBSPOTMAX = 5#最大据点
	EGBSPOTZHURONGFENG = 5#祝融峰
	EGBSPOTYUXUDING = 6#玉虚顶
end

#帮派据点状态
class EGBSpotState
	EGBSPOTSTATENONE = 0#无效状态
	EGBSPOTSTATEWIN = 1#胜利
	EGBSPOTSTATELOSE = 2#失败
	EGBSPOTSTATETIE = 3#平局
	EGBSPOTSTATEBATTLE = 4#战斗中
	EGBSPOTSTATENOBODY = 5#无人参战
	EGBSPOTSTATEMAX = 6#最大状态
end

#帮派战战斗方向
class EGBSide
	EGBSIDEA = 0#A方
	EGBSIDEB = 1#B方
	EGBSIDEINVALID = 2#无效方
end

#帮派战技能
class EGBSkill
	EGBSKILLNONE = 0#无效技能
	EGBSKILLATTACK = 1#攻击强化
	EGBSKILLDEFENCE = 2#防御强化
	EGBSKILLSPEED = 3#身法强化
	EGBSKILLHP = 4#生命强化
	EGBSKILLMAX = 5#技能最大值
end

#帮派战返回结果
class EGBResult
	EGBRESULTSUCCESS = 0#成功
	EGBRESULTFAILED = 1#失败
	EGBRESULTWRONGTIME = 2#时间段错误
	EGBRESULTNOTINBATTLE = 3#不在帮派战中
	EGBRESULTNOGUILD = 4#不存在帮派
	EGBRESULTNOAUTHORITY = 5#权限不足
end

#帮派战报名结果
class EGBSignUpResult
	EGBSIGNUPSUCCESS = 0#报名成功
	EGBSIGNUPFAILED = 1#报名失败
	EGBSIGNUPNOTINGUILD = 2#报名时不存在帮派
	EGBSIGNUPREPEAT = 3#报名重复
	EGBSIGNUPWRONGTIME = 4#不在报名时段
	EGBSIGNUPSPOTFULL = 5#报名据点已满
	EGBSIGNUPESCAPE = 6#由于您刚刚逃离了帮派战，暂时无法报名
end

#帮派战进入结果
class EGBEnterResult
	EGBENTERSUCCESS = 0#进入成功
	EGBENTERFAILED = 1#进入失败
	EGBENTERNOTINGUILD = 2#进入时不存在帮派
	EGBENTERREPEAT = 3#进入重复
	EGBENTERWRONGTIME = 4#不在进入时段
end

#帮派战退出结果
class EGBQuitResult
	EGBQUITSUCCESS = 0#退出成功
	EGBQUITFAILED = 1#退出失败
	EGBQUITNOTINGUILD = 2#退出时不存在帮派
	EGBQUITNOTINBATTLE = 3#当前不在帮派战
	EGBQUITREPEAT = 4#退出重复
	EGBQUITWRONGTIME = 5#当前不存在帮派战
end

#帮派战调整结果
class EGBAdjustResult
	EGBADJUSTSUCCESS = 0#调整成功
	EGBADJUSTFAILED = 1#调整失败
	EGBADJUSTNOTINGUILD = 2#调整时不存在帮派
	EGBADJUSTNOAUTHORITY = 3#调整权限不足
	EGBADJUSTWRONGTIME = 4#不在调整时间段
	EGBADJUSTSPOTFULL = 5#调整目标据点已满
end

#帮派战战斗相关结果
class EGBBattleResult
	EGBBATTLESUCCESS = 0#战斗成功
	EGBBATTLEFAILED = 1#战斗失败
	EGBBATTLENOTINGUILD = 2#战斗时不存在帮派
end

#帮派战技能相关结果
class EGBSkillResult
	EGBSKILLSUCCESS = 0#成功
	EGBSKILLFAILED = 1#失败
	EGBSKILLWRONGTIME = 2#只有在准备阶段才可以购买增益祝福
	EGBSKILLNOGOLD = 3#仙石不足
	EGBSKILLALREADYHAVE = 4#已经拥有该效果
end

#结构体：SBattleUserInfo的继承体系类型
class EType_SBattleUserInfo
	ETYPE_SBATTLEUSERINFO = 0#类型：SBattleUserInfo
	ETYPE_SBATTLEUSERALLINFO = 1#类型：SBattleUserAllInfo
end

#结构体：SSpotInfo的继承体系类型
class EType_SSpotInfo
	ETYPE_SSPOTINFO = 0#类型：SSpotInfo
	ETYPE_SSPOTALLINFO = 1#类型：SSpotAllInfo
	ETYPE_SSPOTBRIEFINFO = 2#类型：SSpotBriefInfo
	ETYPE_SSPOTREADYINFO = 3#类型：SSpotReadyInfo
end

#技能信息
class SSkillInfo
	attr_accessor:eType #(枚举类型：EGBSkill)技能类型

	#构造函数
	def initialize
		@eType = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eType = @eType
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSkillInfo.new
		s.eType = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSkillInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eType)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮派战玩家信息
class SBattleUserInfo
	attr_accessor:qwRoleID #(UINT64)成员角色ID
	attr_accessor:strName #(string)名字
	attr_accessor:wLevel #(UINT16)等级
	attr_accessor:eState #(枚举类型：EGBUserState)玩家状态
	attr_accessor:wFighterID #(UINT16)玩家主将ID
	attr_accessor:vecSkillInfo #(SSkillInfo的数组)玩家技能信息

	#构造函数
	def initialize
		@qwRoleID = 0
		@strName = ''
		@wLevel = 0
		@eState = 0
		@wFighterID = 0
		@vecSkillInfo = Array.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SBattleUserInfo::ETYPE_SBATTLEUSERINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.strName = @strName
		obj.wLevel = @wLevel
		obj.eState = @eState
		obj.wFighterID = @wFighterID
		obj.vecSkillInfo = @vecSkillInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleUserInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.wLevel = ByteUtil::readUINT16(data)
		s.eState = ByteUtil::readUINT8(data)
		s.wFighterID = ByteUtil::readUINT16(data)
		s.vecSkillInfo = SSkillInfo::vectorFromStream(data)
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_SBattleUserInfo::ETYPE_SBATTLEUSERINFO
				s = SBattleUserInfo::fromStream(data)
			when EType_SBattleUserInfo::ETYPE_SBATTLEUSERALLINFO
				s = SBattleUserAllInfo::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleUserInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleUserInfo::superFromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT16(data, @wLevel)
		ByteUtil::writeUINT8(data, @eState)
		ByteUtil::writeUINT16(data, @wFighterID)
		SSkillInfo::vectorToStream(data, @vecSkillInfo)
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

#帮派战玩家详细信息（包括战斗相关属性）
class SBattleUserAllInfo < SBattleUserInfo
	attr_accessor:sAppear #(类类型：MapProt::SPlayerAppear)外观
	attr_accessor:byHPP #(UINT8)剩余HP百分比
	attr_accessor:byPosIndex #(UINT8)据点站位编号
	attr_accessor:dwBattlePoint #(UINT32)战斗力

	#构造函数
	def initialize
		super()
		@sAppear = SPlayerAppear.new
		@byHPP = 0
		@byPosIndex = 0
		@dwBattlePoint = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SBattleUserInfo::ETYPE_SBATTLEUSERALLINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.sAppear = @sAppear
		obj.byHPP = @byHPP
		obj.byPosIndex = @byPosIndex
		obj.dwBattlePoint = @dwBattlePoint
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleUserAllInfo.new
		base = SBattleUserInfo::fromStream(data)
		base.copyTo(s)
		s.sAppear = SPlayerAppear::fromStream(data)
		s.byHPP = ByteUtil::readUINT8(data)
		s.byPosIndex = ByteUtil::readUINT8(data)
		s.dwBattlePoint = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleUserAllInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		@sAppear.toStream(data)
		ByteUtil::writeUINT8(data, @byHPP)
		ByteUtil::writeUINT8(data, @byPosIndex)
		ByteUtil::writeUINT32(data, @dwBattlePoint)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战斗信息
class SBattleInfo
	attr_accessor:qwBattleID #(UINT64)战报ID
	attr_accessor:strNameA #(string)A方名字
	attr_accessor:qwRoleIDA #(UINT64)A方ID
	attr_accessor:strNameB #(string)B方名字
	attr_accessor:qwRoleIDB #(UINT64)B方ID
	attr_accessor:eWinnerSide #(枚举类型：EGBSide)获胜方

	#构造函数
	def initialize
		@qwBattleID = 0
		@strNameA = ''
		@qwRoleIDA = 0
		@strNameB = ''
		@qwRoleIDB = 0
		@eWinnerSide = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwBattleID = @qwBattleID
		obj.strNameA = @strNameA
		obj.qwRoleIDA = @qwRoleIDA
		obj.strNameB = @strNameB
		obj.qwRoleIDB = @qwRoleIDB
		obj.eWinnerSide = @eWinnerSide
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleInfo.new
		s.qwBattleID = ByteUtil::readUINT64(data)
		s.strNameA = ByteUtil::readSTRING(data)
		s.qwRoleIDA = ByteUtil::readUINT64(data)
		s.strNameB = ByteUtil::readSTRING(data)
		s.qwRoleIDB = ByteUtil::readUINT64(data)
		s.eWinnerSide = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwBattleID)
		ByteUtil::writeSTRING(data, @strNameA)
		ByteUtil::writeUINT64(data, @qwRoleIDA)
		ByteUtil::writeSTRING(data, @strNameB)
		ByteUtil::writeUINT64(data, @qwRoleIDB)
		ByteUtil::writeUINT8(data, @eWinnerSide)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战斗详细数据
class SBattleData
	attr_accessor:byIndex #(UINT8)战斗场编号(1~3)
	attr_accessor:qwRoleIDA #(UINT64)A方玩家ID
	attr_accessor:qwRoleIDB #(UINT64)B方玩家ID
	attr_accessor:eWinnerSide #(枚举类型：EGBSide)获胜方
	attr_accessor:strBattleReport #(string)战报

	#构造函数
	def initialize
		@byIndex = 0
		@qwRoleIDA = 0
		@qwRoleIDB = 0
		@eWinnerSide = 0
		@strBattleReport = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byIndex = @byIndex
		obj.qwRoleIDA = @qwRoleIDA
		obj.qwRoleIDB = @qwRoleIDB
		obj.eWinnerSide = @eWinnerSide
		obj.strBattleReport = @strBattleReport
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleData.new
		s.byIndex = ByteUtil::readUINT8(data)
		s.qwRoleIDA = ByteUtil::readUINT64(data)
		s.qwRoleIDB = ByteUtil::readUINT64(data)
		s.eWinnerSide = ByteUtil::readUINT8(data)
		s.strBattleReport = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byIndex)
		ByteUtil::writeUINT64(data, @qwRoleIDA)
		ByteUtil::writeUINT64(data, @qwRoleIDB)
		ByteUtil::writeUINT8(data, @eWinnerSide)
		ByteUtil::writeSTRING(data, @strBattleReport)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战斗场信息
class SBattleSlotInfo
	attr_accessor:byIndex #(UINT8)战斗场编号(1~3)
	attr_accessor:qwBattleID #(UINT64)战报ID
	attr_accessor:sUserAllInfoA #(类类型：SBattleUserAllInfo)A方成员信息
	attr_accessor:sUserAllInfoB #(类类型：SBattleUserAllInfo)B方成员信息

	#构造函数
	def initialize
		@byIndex = 0
		@qwBattleID = 0
		@sUserAllInfoA = SBattleUserAllInfo.new
		@sUserAllInfoB = SBattleUserAllInfo.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byIndex = @byIndex
		obj.qwBattleID = @qwBattleID
		obj.sUserAllInfoA = @sUserAllInfoA
		obj.sUserAllInfoB = @sUserAllInfoB
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleSlotInfo.new
		s.byIndex = ByteUtil::readUINT8(data)
		s.qwBattleID = ByteUtil::readUINT64(data)
		s.sUserAllInfoA = SBattleUserAllInfo::fromStream(data)
		s.sUserAllInfoB = SBattleUserAllInfo::fromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleSlotInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byIndex)
		ByteUtil::writeUINT64(data, @qwBattleID)
		@sUserAllInfoA.toStream(data)
		@sUserAllInfoB.toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#据点信息
class SSpotInfo
	attr_accessor:eSpotType #(枚举类型：EGBSpot)据点类型

	#构造函数
	def initialize
		@eSpotType = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SSpotInfo::ETYPE_SSPOTINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eSpotType = @eSpotType
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSpotInfo.new
		s.eSpotType = ByteUtil::readUINT8(data)
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_SSpotInfo::ETYPE_SSPOTINFO
				s = SSpotInfo::fromStream(data)
			when EType_SSpotInfo::ETYPE_SSPOTALLINFO
				s = SSpotAllInfo::fromStream(data)
			when EType_SSpotInfo::ETYPE_SSPOTBRIEFINFO
				s = SSpotBriefInfo::fromStream(data)
			when EType_SSpotInfo::ETYPE_SSPOTREADYINFO
				s = SSpotReadyInfo::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSpotInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSpotInfo::superFromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eSpotType)
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

#据点详细信息
class SSpotAllInfo < SSpotInfo
	attr_accessor:eState #(枚举类型：EGBSpotState)据点状态
	attr_accessor:vecMemberInfoA #(SBattleUserInfo的数组)A方成员信息
	attr_accessor:vecMemberInfoB #(SBattleUserInfo的数组)B方成员信息
	attr_accessor:vecBattleSlotInfo #(SBattleSlotInfo的数组)战斗场信息
	attr_accessor:vecBattleInfo #(SBattleInfo的数组)战报信息

	#构造函数
	def initialize
		super()
		@eState = 0
		@vecMemberInfoA = Array.new
		@vecMemberInfoB = Array.new
		@vecBattleSlotInfo = Array.new
		@vecBattleInfo = Array.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SSpotInfo::ETYPE_SSPOTALLINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.eState = @eState
		obj.vecMemberInfoA = @vecMemberInfoA
		obj.vecMemberInfoB = @vecMemberInfoB
		obj.vecBattleSlotInfo = @vecBattleSlotInfo
		obj.vecBattleInfo = @vecBattleInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSpotAllInfo.new
		base = SSpotInfo::fromStream(data)
		base.copyTo(s)
		s.eState = ByteUtil::readUINT8(data)
		s.vecMemberInfoA = SBattleUserInfo::superVectorFromStream(data)
		s.vecMemberInfoB = SBattleUserInfo::superVectorFromStream(data)
		s.vecBattleSlotInfo = SBattleSlotInfo::vectorFromStream(data)
		s.vecBattleInfo = SBattleInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSpotAllInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @eState)
		SBattleUserInfo::superVectorToStream(data, @vecMemberInfoA)
		SBattleUserInfo::superVectorToStream(data, @vecMemberInfoB)
		SBattleSlotInfo::vectorToStream(data, @vecBattleSlotInfo)
		SBattleInfo::vectorToStream(data, @vecBattleInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#据点简略信息
class SSpotBriefInfo < SSpotInfo
	attr_accessor:eState #(枚举类型：EGBSpotState)据点状态

	#构造函数
	def initialize
		super()
		@eState = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SSpotInfo::ETYPE_SSPOTBRIEFINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.eState = @eState
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSpotBriefInfo.new
		base = SSpotInfo::fromStream(data)
		base.copyTo(s)
		s.eState = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSpotBriefInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @eState)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#报名阶段据点信息
class SSpotReadyInfo < SSpotInfo
	attr_accessor:byCount #(UINT8)该据点人数

	#构造函数
	def initialize
		super()
		@byCount = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SSpotInfo::ETYPE_SSPOTREADYINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.byCount = @byCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSpotReadyInfo.new
		base = SSpotInfo::fromStream(data)
		base.copyTo(s)
		s.byCount = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSpotReadyInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @byCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战场信息
class SFieldInfo
	attr_accessor:strGuildNameA #(string)A方帮派名称
	attr_accessor:strGuildNameB #(string)B方帮派名称
	attr_accessor:vecSpotInfo #(SSpotInfo的数组)据点详细信息

	#构造函数
	def initialize
		@strGuildNameA = ''
		@strGuildNameB = ''
		@vecSpotInfo = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strGuildNameA = @strGuildNameA
		obj.strGuildNameB = @strGuildNameB
		obj.vecSpotInfo = @vecSpotInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFieldInfo.new
		s.strGuildNameA = ByteUtil::readSTRING(data)
		s.strGuildNameB = ByteUtil::readSTRING(data)
		s.vecSpotInfo = SSpotInfo::superVectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFieldInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeSTRING(data, @strGuildNameA)
		ByteUtil::writeSTRING(data, @strGuildNameB)
		SSpotInfo::superVectorToStream(data, @vecSpotInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[SignUp:帮派战报名]的返回的参数组成的结构体
class SRetParam_SignUp
	attr_accessor:eResult#(枚举类型：EGBSignUpResult)报名返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[Enter:进入帮派战(进入准备场地)]的返回的参数组成的结构体
class SRetParam_Enter
	attr_accessor:eResult#(枚举类型：EGBEnterResult)报名返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[Quit:帮派战退出]的返回的参数组成的结构体
class SRetParam_Quit
	attr_accessor:eResult#(枚举类型：EGBQuitResult)退出返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[AdjustMember:帮派成员调整]的返回的参数组成的结构体
class SRetParam_AdjustMember
	attr_accessor:eResult#(枚举类型：EGBAdjustResult)调整返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetState:获取帮派战状态]的返回的参数组成的结构体
class SRetParam_GetState
	attr_accessor:eState#(枚举类型：EGBState)当前帮派战状态
	attr_accessor:byBattleCount#(UINT8)当前已经战斗的数量
	attr_accessor:dwRemainTime#(UINT32)当前状态剩余时间
	attr_accessor:eSpotType#(枚举类型：EGBSpot)自己所在据点(不为None也可能在准备地图中)
	attr_accessor:bGuildJoined#(bool)自己所在帮派是否已经参加
	attr_accessor:eSelfSide#(枚举类型：EGBSide)自己所在帮派方向

	#构造函数
	def initialize
		@eState = 0
		@byBattleCount = 0
		@dwRemainTime = 0
		@eSpotType = 0
		@bGuildJoined = false
		@eSelfSide = 0
	end
end

#函数[GetFieldInfo:帮派战场信息]的返回的参数组成的结构体
class SRetParam_GetFieldInfo
	attr_accessor:eResult#(枚举类型：EGBResult)返回结果
	attr_accessor:vecFieldInfo#(SFieldInfo的数组)帮派战场信息

	#构造函数
	def initialize
		@eResult = 0
		@vecFieldInfo = Array.new
	end
end

#函数[GetSpotInfo:帮派据点信息]的返回的参数组成的结构体
class SRetParam_GetSpotInfo
	attr_accessor:eResult#(枚举类型：EGBResult)返回结果
	attr_accessor:vecSpotInfo#(SSpotInfo的数组)据点详细信息（数量为0/1）

	#构造函数
	def initialize
		@eResult = 0
		@vecSpotInfo = Array.new
	end
end

#函数[GetSpotBattle:据点战报获取]的返回的参数组成的结构体
class SRetParam_GetSpotBattle
	attr_accessor:eResult#(枚举类型：EGBBattleResult)战报获取结果
	attr_accessor:vecBattleData#(SBattleData的数组)战报信息

	#构造函数
	def initialize
		@eResult = 0
		@vecBattleData = Array.new
	end
end

#函数[GetSkillInfo:帮派战技能信息获取]的返回的参数组成的结构体
class SRetParam_GetSkillInfo
	attr_accessor:eResult#(枚举类型：EGBSkillResult)购买结果
	attr_accessor:vecSkillInfo#(SSkillInfo的数组)具体已购买技能

	#构造函数
	def initialize
		@eResult = 0
		@vecSkillInfo = Array.new
	end
end

#函数[BuySkill:帮派购买技能结果]的返回的参数组成的结构体
class SRetParam_BuySkill
	attr_accessor:eResult#(枚举类型：EGBSkillResult)购买结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetPanelInfo:获取帮派战小面板信息]的返回的参数组成的结构体
class SRetParam_GetPanelInfo
	attr_accessor:dwSelfScore#(UINT32)我的积分
	attr_accessor:dwGuildScore#(UINT32)帮派积分
	attr_accessor:dwGuildRank#(UINT32)帮派排名

	#构造函数
	def initialize
		@dwSelfScore = 0
		@dwGuildScore = 0
		@dwGuildRank = 0
	end
end

#函数[CallMember:召集帮众广播]的返回的参数组成的结构体
class SRetParam_CallMember
	attr_accessor:eResult#(枚举类型：EGBResult)召集结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：帮派相关协议
class GuildBattleProtBase < ProtocolBase
	#以下为发送函数
	#发送：帮派战报名
	def send_SignUp(
		eSpotType #(枚举类型：EGBSpot)据点类型
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eSpotType)
		return @svrHandler.sendPacket(data)
	end

	#发送：进入帮派战(进入准备场地)
	def send_Enter(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派战退出
	def send_Quit(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派成员调整
	def send_AdjustMember(
		qwRoleID,  #(UINT64)成员角色ID
		eSpotType,  #(枚举类型：EGBSpot)目标据点类型
		byIndex #(UINT8)新目标对应位置(从1开始)
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT8(data, eSpotType)
		ByteUtil::writeUINT8(data, byIndex)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取帮派战状态
	def send_GetState(
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派战场信息
	def send_GetFieldInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派据点信息
	def send_GetSpotInfo(
		eType #(枚举类型：EGBSpot)据点类型
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eType)
		return @svrHandler.sendPacket(data)
	end

	#发送：据点战报获取
	def send_GetSpotBattle(
		eType #(枚举类型：EGBSpot)据点类型
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eType)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派战技能信息获取
	def send_GetSkillInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派购买技能结果
	def send_BuySkill(
		eType #(枚举类型：EGBSkill)购买的技能类型
	)
		sessionID = @sessionMgr.getNewSession(self, 10);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eType)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取帮派战小面板信息
	def send_GetPanelInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 11);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：召集帮众广播
	def send_CallMember(
	)
		sessionID = @sessionMgr.getNewSession(self, 12);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：帮派战状态通知
	def onRecv_StateNotify(
		eState, #(枚举类型：EGBState)当前帮派战状态
		byBattleCount, #(UINT8)当前已经战斗的数量
		dwRemainTime, #(UINT32)当前状态剩余时间
		eSpotType, #(枚举类型：EGBSpot)自己所在据点(报名的据点或者目前被调整到的据点)
		eSelfSide #(枚举类型：EGBSide)自己所在帮派方向
	)
		raise NotImplementedError
	end
	#接收：帮派战信息通知
	def onRecv_FieldInfoNotify(
		sFieldInfo #(类类型：SFieldInfo)战场信息
	)
		raise NotImplementedError
	end
	#接收：帮派战据点信息通知
	def onRecv_SpotInfoNotify(
		vecSpotInfo #(SSpotInfo的数组)据点详细信息
	)
		raise NotImplementedError
	end
	#接收：据点战斗通知
	def onRecv_SpotBattleNotify(
		eType, #(枚举类型：EGBSpot)据点类型
		vecBattleData #(SBattleData的数组)战报信息
	)
		raise NotImplementedError
	end
	#接收：帮派战技能信息通知
	def onRecv_SkillInfoNotify(
		vecSkillInfo #(SSkillInfo的数组)具体已购买技能
	)
		raise NotImplementedError
	end
	#接收：更新帮派战小面板信息
	def onRecv_PanelInfoNotify(
		dwSelfScore, #(UINT32)我的积分
		dwGuildScore, #(UINT32)帮派积分
		dwGuildRank #(UINT32)帮派排名
	)
		raise NotImplementedError
	end
	#接收：报名还没进入的通知进入
	def onRecv_SignupEnterNotify(
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
	#返回：帮派战报名
	def onReturn_SignUp(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SignUp)返回的参数
	)
	end

	#返回：进入帮派战(进入准备场地)
	def onReturn_Enter(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Enter)返回的参数
	)
	end

	#返回：帮派战退出
	def onReturn_Quit(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Quit)返回的参数
	)
	end

	#返回：帮派成员调整
	def onReturn_AdjustMember(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_AdjustMember)返回的参数
	)
	end

	#返回：获取帮派战状态
	def onReturn_GetState(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetState)返回的参数
	)
	end

	#返回：帮派战场信息
	def onReturn_GetFieldInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetFieldInfo)返回的参数
	)
	end

	#返回：帮派据点信息
	def onReturn_GetSpotInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetSpotInfo)返回的参数
	)
	end

	#返回：据点战报获取
	def onReturn_GetSpotBattle(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetSpotBattle)返回的参数
	)
	end

	#返回：帮派战技能信息获取
	def onReturn_GetSkillInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetSkillInfo)返回的参数
	)
	end

	#返回：帮派购买技能结果
	def onReturn_BuySkill(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuySkill)返回的参数
	)
	end

	#返回：获取帮派战小面板信息
	def onReturn_GetPanelInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetPanelInfo)返回的参数
	)
	end

	#返回：召集帮众广播
	def onReturn_CallMember(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_CallMember)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：帮派战状态通知
	def _doRecv_StateNotify(data)
		eState = ByteUtil::readUINT8(data)
		byBattleCount = ByteUtil::readUINT8(data)
		dwRemainTime = ByteUtil::readUINT32(data)
		eSpotType = ByteUtil::readUINT8(data)
		eSelfSide = ByteUtil::readUINT8(data)
		return onRecv_StateNotify(eState, byBattleCount, dwRemainTime, eSpotType, eSelfSide)
	end

	#接收处理：帮派战信息通知
	def _doRecv_FieldInfoNotify(data)
		sFieldInfo = SFieldInfo::fromStream(data)
		return onRecv_FieldInfoNotify(sFieldInfo)
	end

	#接收处理：帮派战据点信息通知
	def _doRecv_SpotInfoNotify(data)
		vecSpotInfo = SSpotInfo::superVectorFromStream(data)
		return onRecv_SpotInfoNotify(vecSpotInfo)
	end

	#接收处理：据点战斗通知
	def _doRecv_SpotBattleNotify(data)
		eType = ByteUtil::readUINT8(data)
		vecBattleData = SBattleData::vectorFromStream(data)
		return onRecv_SpotBattleNotify(eType, vecBattleData)
	end

	#接收处理：帮派战技能信息通知
	def _doRecv_SkillInfoNotify(data)
		vecSkillInfo = SSkillInfo::vectorFromStream(data)
		return onRecv_SkillInfoNotify(vecSkillInfo)
	end

	#接收处理：更新帮派战小面板信息
	def _doRecv_PanelInfoNotify(data)
		dwSelfScore = ByteUtil::readUINT32(data)
		dwGuildScore = ByteUtil::readUINT32(data)
		dwGuildRank = ByteUtil::readUINT32(data)
		return onRecv_PanelInfoNotify(dwSelfScore, dwGuildScore, dwGuildRank)
	end

	#接收处理：报名还没进入的通知进入
	def _doRecv_SignupEnterNotify(data)
		return onRecv_SignupEnterNotify()
	end

	#接收处理：召集帮众广播
	def _doRecv_CallMemberNotify(data)
		byQuality = ByteUtil::readUINT8(data)
		strName = ByteUtil::readSTRING(data)
		return onRecv_CallMemberNotify(byQuality, strName)
	end

#以下为返回处理函数
	#返回处理：帮派战报名
	def _doReturn_SignUp(data)
		retParam = SRetParam_SignUp.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGBSignUpResult)报名返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SignUp(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：帮派战报名
	def _onTimeOut_SignUp(sessionID)
		retParam = SRetParam_SignUp.new;
		onReturn_SignUp(2, retParam)
	end

	#返回处理：进入帮派战(进入准备场地)
	def _doReturn_Enter(data)
		retParam = SRetParam_Enter.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGBEnterResult)报名返回结果
		retParam.eResult = eResult
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

	#返回处理：帮派战退出
	def _doReturn_Quit(data)
		retParam = SRetParam_Quit.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGBQuitResult)退出返回结果
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

	#返回处理：帮派成员调整
	def _doReturn_AdjustMember(data)
		retParam = SRetParam_AdjustMember.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGBAdjustResult)调整返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_AdjustMember(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：帮派成员调整
	def _onTimeOut_AdjustMember(sessionID)
		retParam = SRetParam_AdjustMember.new;
		onReturn_AdjustMember(2, retParam)
	end

	#返回处理：获取帮派战状态
	def _doReturn_GetState(data)
		retParam = SRetParam_GetState.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eState = ByteUtil::readUINT8(data) #(枚举类型：EGBState)当前帮派战状态
		byBattleCount = ByteUtil::readUINT8(data) #(UINT8)当前已经战斗的数量
		dwRemainTime = ByteUtil::readUINT32(data) #(UINT32)当前状态剩余时间
		eSpotType = ByteUtil::readUINT8(data) #(枚举类型：EGBSpot)自己所在据点(不为None也可能在准备地图中)
		bGuildJoined = ByteUtil::readBOOL(data) #(bool)自己所在帮派是否已经参加
		eSelfSide = ByteUtil::readUINT8(data) #(枚举类型：EGBSide)自己所在帮派方向
		retParam.eState = eState
		retParam.byBattleCount = byBattleCount
		retParam.dwRemainTime = dwRemainTime
		retParam.eSpotType = eSpotType
		retParam.bGuildJoined = bGuildJoined
		retParam.eSelfSide = eSelfSide
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

	#返回处理：帮派战场信息
	def _doReturn_GetFieldInfo(data)
		retParam = SRetParam_GetFieldInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGBResult)返回结果
		vecFieldInfo = SFieldInfo::vectorFromStream(data) #(SFieldInfo的数组)帮派战场信息
		retParam.eResult = eResult
		retParam.vecFieldInfo = vecFieldInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetFieldInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：帮派战场信息
	def _onTimeOut_GetFieldInfo(sessionID)
		retParam = SRetParam_GetFieldInfo.new;
		onReturn_GetFieldInfo(2, retParam)
	end

	#返回处理：帮派据点信息
	def _doReturn_GetSpotInfo(data)
		retParam = SRetParam_GetSpotInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGBResult)返回结果
		vecSpotInfo = SSpotInfo::superVectorFromStream(data) #(SSpotInfo的数组)据点详细信息（数量为0/1）
		retParam.eResult = eResult
		retParam.vecSpotInfo = vecSpotInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetSpotInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：帮派据点信息
	def _onTimeOut_GetSpotInfo(sessionID)
		retParam = SRetParam_GetSpotInfo.new;
		onReturn_GetSpotInfo(2, retParam)
	end

	#返回处理：据点战报获取
	def _doReturn_GetSpotBattle(data)
		retParam = SRetParam_GetSpotBattle.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGBBattleResult)战报获取结果
		vecBattleData = SBattleData::vectorFromStream(data) #(SBattleData的数组)战报信息
		retParam.eResult = eResult
		retParam.vecBattleData = vecBattleData
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetSpotBattle(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：据点战报获取
	def _onTimeOut_GetSpotBattle(sessionID)
		retParam = SRetParam_GetSpotBattle.new;
		onReturn_GetSpotBattle(2, retParam)
	end

	#返回处理：帮派战技能信息获取
	def _doReturn_GetSkillInfo(data)
		retParam = SRetParam_GetSkillInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGBSkillResult)购买结果
		vecSkillInfo = SSkillInfo::vectorFromStream(data) #(SSkillInfo的数组)具体已购买技能
		retParam.eResult = eResult
		retParam.vecSkillInfo = vecSkillInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetSkillInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：帮派战技能信息获取
	def _onTimeOut_GetSkillInfo(sessionID)
		retParam = SRetParam_GetSkillInfo.new;
		onReturn_GetSkillInfo(2, retParam)
	end

	#返回处理：帮派购买技能结果
	def _doReturn_BuySkill(data)
		retParam = SRetParam_BuySkill.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGBSkillResult)购买结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuySkill(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：帮派购买技能结果
	def _onTimeOut_BuySkill(sessionID)
		retParam = SRetParam_BuySkill.new;
		onReturn_BuySkill(2, retParam)
	end

	#返回处理：获取帮派战小面板信息
	def _doReturn_GetPanelInfo(data)
		retParam = SRetParam_GetPanelInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwSelfScore = ByteUtil::readUINT32(data) #(UINT32)我的积分
		dwGuildScore = ByteUtil::readUINT32(data) #(UINT32)帮派积分
		dwGuildRank = ByteUtil::readUINT32(data) #(UINT32)帮派排名
		retParam.dwSelfScore = dwSelfScore
		retParam.dwGuildScore = dwGuildScore
		retParam.dwGuildRank = dwGuildRank
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetPanelInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取帮派战小面板信息
	def _onTimeOut_GetPanelInfo(sessionID)
		retParam = SRetParam_GetPanelInfo.new;
		onReturn_GetPanelInfo(2, retParam)
	end

	#返回处理：召集帮众广播
	def _doReturn_CallMember(data)
		retParam = SRetParam_CallMember.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGBResult)召集结果
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
		@protID = 76;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_StateNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_FieldInfoNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_SpotInfoNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_SpotBattleNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_SkillInfoNotify' #FuncID: 5
		@recvFuncList[5] = '_doRecv_PanelInfoNotify' #FuncID: 6
		@recvFuncList[6] = '_doRecv_SignupEnterNotify' #FuncID: 7
		@recvFuncList[7] = '_doRecv_CallMemberNotify' #FuncID: 8

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_SignUp' #FuncID: 1
		@retFuncList[1] = '_doReturn_Enter' #FuncID: 2
		@retFuncList[2] = '_doReturn_Quit' #FuncID: 3
		@retFuncList[3] = '_doReturn_AdjustMember' #FuncID: 4
		@retFuncList[4] = '_doReturn_GetState' #FuncID: 5
		@retFuncList[5] = '_doReturn_GetFieldInfo' #FuncID: 6
		@retFuncList[6] = '_doReturn_GetSpotInfo' #FuncID: 7
		@retFuncList[7] = '_doReturn_GetSpotBattle' #FuncID: 8
		@retFuncList[8] = '_doReturn_GetSkillInfo' #FuncID: 9
		@retFuncList[9] = '_doReturn_BuySkill' #FuncID: 10
		@retFuncList[10] = '_doReturn_GetPanelInfo' #FuncID: 11
		@retFuncList[11] = '_doReturn_CallMember' #FuncID: 12

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_SignUp' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_Enter' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_Quit' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_AdjustMember' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_GetState' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_GetFieldInfo' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_GetSpotInfo' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_GetSpotBattle' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_GetSkillInfo' #FuncID: 9
		@timeFuncList[9] = '_onTimeOut_BuySkill' #FuncID: 10
		@timeFuncList[10] = '_onTimeOut_GetPanelInfo' #FuncID: 11
		@timeFuncList[11] = '_onTimeOut_CallMember' #FuncID: 12
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

