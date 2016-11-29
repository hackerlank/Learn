#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    TeamGS.rb
#  Purpose:      竞技场协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './BattleGSBase.rb'
require_relative './ItemProtBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#队伍状态
class EMemberStatus
	EMEMBER_NONE = 0#无状态
	EMEMBER_READY = 1#已准备好
	EMEMBER_ERR = 2#不满足条件提示
end

#队伍状态
class TeamListOP
	ETEAM_CREATE = 0#队伍创建
	ETEAM_UPDATE = 1#队伍更新
	ETEAM_DEL = 2#队伍删除
end

#竞技场操作结果
class ETEAMResult
	ETEAM_SUC = 0#成功
	ETEAM_OTHERTEAM = 1#在其他房间中
	ETEAM_NOTINTEAM = 2#不在房间中
	ETEAM_PREDGN = 3#前置副本没有通过
	ETEAM_PACKFULL = 4#包裹满
	ETEAM_FULL = 5#房间满
	ETEAM_NOLEADER = 6#您不是队长
	ETEAM_NODGNTYPE = 7#不存在这个副本
	ETEAM_ERRTEAM = 8#不存在这个队伍
	ETEAM_NEWHEROERR = 9#新将不存在
	ETEAM_MAINHERO = 10#主将不可替换
	ETEAM_NEWHEROIN = 11#新将已在
	ETEAM_NEWHEROPOSERR = 12#新将位置错误
	ETEAM_PLAYERINREADY = 13#玩家已准备
	ETEAM_PLAYERNOREADY = 14#玩家没有准备好
	ETEAM_MEMBERNOREADY = 15#有玩家没有准备好
	ETEAM_LOWLEVEL = 16#等级不足，无法进入副本
	ETEAM_FIGHTERS = 17#将不足，无法进入副本
	ETEAM_KICKSELF = 18#不可踢自己
	ETEAM_KICKERR = 19#被踢不在该队伍中
	ETEAM_POSERR = 20#位置不正确
	ETEAM_INBATTLE = 21#战斗中
	ETEAM_MINPERSON = 22#人数不足
	ETEAM_ERRPERSON = 23#有人不满足条件
	ETEAM_DIFFDGN = 24#副本人数不一致
	ETEAM_PETERR = 25#错误玩家阵灵
	ETEAM_PASSWORD = 26#密码错误
	ETEAM_ISLEADER = 27#已经是队长
	ETEAM_ERRMEM = 28#不是房间成员
	ETEAM_OTHERERR = 29#其他错误
end

#结构体：TeamFighter的继承体系类型
class EType_TeamFighter
	ETYPE_TEAMFIGHTER = 0#类型：TeamFighter
	ETYPE_COMMONFIGHTER = 1#类型：CommonFighter
	ETYPE_FORMATIONFIGHTER = 2#类型：FormationFighter
	ETYPE_BEAUTYFIGHTER = 3#类型：BeautyFighter
end

#房间里的战斗对象
class TeamFighter
	attr_accessor:pFeature #(类类型：BattleGS::SFeatureBase)外观信息
	attr_accessor:dwFighterPower #(UINT32)战斗力
	attr_accessor:byPos #(UINT8)在玩家将序列的位置

	#构造函数
	def initialize
		@pFeature = SFeatureBase.new
		@dwFighterPower = 0
		@byPos = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_TeamFighter::ETYPE_TEAMFIGHTER
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.pFeature = @pFeature
		obj.dwFighterPower = @dwFighterPower
		obj.byPos = @byPos
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = TeamFighter.new
		s.pFeature = SFeatureBase::superFromStream(data)
		s.dwFighterPower = ByteUtil::readUINT32(data)
		s.byPos = ByteUtil::readUINT8(data)
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_TeamFighter::ETYPE_TEAMFIGHTER
				s = TeamFighter::fromStream(data)
			when EType_TeamFighter::ETYPE_COMMONFIGHTER
				s = CommonFighter::fromStream(data)
			when EType_TeamFighter::ETYPE_FORMATIONFIGHTER
				s = FormationFighter::fromStream(data)
			when EType_TeamFighter::ETYPE_BEAUTYFIGHTER
				s = BeautyFighter::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = TeamFighter::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = TeamFighter::superFromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		@pFeature.superToStream(data)
		ByteUtil::writeUINT32(data, @dwFighterPower)
		ByteUtil::writeUINT8(data, @byPos)
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

#普通将
class CommonFighter < TeamFighter
	attr_accessor:qwInstID #(UINT64)将唯一ID
	attr_accessor:wFighterID #(UINT16)将类型ID
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:byMain #(UINT8)是否主将

	#构造函数
	def initialize
		super()
		@qwInstID = 0
		@wFighterID = 0
		@byLevel = 0
		@byMain = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_TeamFighter::ETYPE_COMMONFIGHTER
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.qwInstID = @qwInstID
		obj.wFighterID = @wFighterID
		obj.byLevel = @byLevel
		obj.byMain = @byMain
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = CommonFighter.new
		base = TeamFighter::fromStream(data)
		base.copyTo(s)
		s.qwInstID = ByteUtil::readUINT64(data)
		s.wFighterID = ByteUtil::readUINT16(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.byMain = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = CommonFighter::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT8(data, @byMain)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#阵灵
class FormationFighter < TeamFighter
	attr_accessor:wFighterID #(UINT16)阵灵ID
	attr_accessor:byPetLevel #(UINT8)阵灵的阶

	#构造函数
	def initialize
		super()
		@wFighterID = 0
		@byPetLevel = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_TeamFighter::ETYPE_FORMATIONFIGHTER
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wFighterID = @wFighterID
		obj.byPetLevel = @byPetLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = FormationFighter.new
		base = TeamFighter::fromStream(data)
		base.copyTo(s)
		s.wFighterID = ByteUtil::readUINT16(data)
		s.byPetLevel = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = FormationFighter::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT8(data, @byPetLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#阵灵
class BeautyFighter < TeamFighter
	attr_accessor:wFighterID #(UINT16)阵灵ID

	#构造函数
	def initialize
		super()
		@wFighterID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_TeamFighter::ETYPE_BEAUTYFIGHTER
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wFighterID = @wFighterID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = BeautyFighter.new
		base = TeamFighter::fromStream(data)
		base.copyTo(s)
		s.wFighterID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = BeautyFighter::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wFighterID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#队伍玩家
class TeamMember
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:byPos #(UINT8)位置
	attr_accessor:strName #(string)名字
	attr_accessor:eStatus #(枚举类型：EMemberStatus)玩家状态
	attr_accessor:byVIPLevel #(UINT8)vip等级
	attr_accessor:oPlatformParam #(类类型：ProtoCommon::SPlatformParam)qq平台信息
	attr_accessor:vecFighter #(TeamFighter的数组)战斗对象

	#构造函数
	def initialize
		@qwRoleID = 0
		@byPos = 0
		@strName = ''
		@eStatus = 0
		@byVIPLevel = 0
		@oPlatformParam = SPlatformParam.new
		@vecFighter = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.byPos = @byPos
		obj.strName = @strName
		obj.eStatus = @eStatus
		obj.byVIPLevel = @byVIPLevel
		obj.oPlatformParam = @oPlatformParam
		obj.vecFighter = @vecFighter
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = TeamMember.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.byPos = ByteUtil::readUINT8(data)
		s.strName = ByteUtil::readSTRING(data)
		s.eStatus = ByteUtil::readUINT8(data)
		s.byVIPLevel = ByteUtil::readUINT8(data)
		s.oPlatformParam = SPlatformParam::fromStream(data)
		s.vecFighter = TeamFighter::superVectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = TeamMember::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT8(data, @byPos)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @eStatus)
		ByteUtil::writeUINT8(data, @byVIPLevel)
		@oPlatformParam.toStream(data)
		TeamFighter::superVectorToStream(data, @vecFighter)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#队伍设定
class TeamSetting
	attr_accessor:dwPassWord #(UINT32)队伍密码

	#构造函数
	def initialize
		@dwPassWord = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwPassWord = @dwPassWord
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = TeamSetting.new
		s.dwPassWord = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = TeamSetting::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwPassWord)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#队伍信息
class TeamInfo
	attr_accessor:TeamID #(UINT32)队伍ID
	attr_accessor:DgnType #(UINT16)副本模板
	attr_accessor:TeamLeader #(UINT64)队长ID
	attr_accessor:qwPetOwner #(UINT64)出战阵灵的拥有者
	attr_accessor:stSetting #(类类型：TeamSetting)队伍设置
	attr_accessor:vecMember #(TeamMember的数组)队伍成员

	#构造函数
	def initialize
		@TeamID = 0
		@DgnType = 0
		@TeamLeader = 0
		@qwPetOwner = 0
		@stSetting = TeamSetting.new
		@vecMember = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.TeamID = @TeamID
		obj.DgnType = @DgnType
		obj.TeamLeader = @TeamLeader
		obj.qwPetOwner = @qwPetOwner
		obj.stSetting = @stSetting
		obj.vecMember = @vecMember
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = TeamInfo.new
		s.TeamID = ByteUtil::readUINT32(data)
		s.DgnType = ByteUtil::readUINT16(data)
		s.TeamLeader = ByteUtil::readUINT64(data)
		s.qwPetOwner = ByteUtil::readUINT64(data)
		s.stSetting = TeamSetting::fromStream(data)
		s.vecMember = TeamMember::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = TeamInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @TeamID)
		ByteUtil::writeUINT16(data, @DgnType)
		ByteUtil::writeUINT64(data, @TeamLeader)
		ByteUtil::writeUINT64(data, @qwPetOwner)
		@stSetting.toStream(data)
		TeamMember::vectorToStream(data, @vecMember)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#房间列表信息
class TeamInfoForList
	attr_accessor:TeamID #(UINT32)队伍ID
	attr_accessor:DgnType #(UINT16)房间ID
	attr_accessor:stSetting #(类类型：TeamSetting)队伍设置密码0 或 1，1表示有密码
	attr_accessor:stLeader #(类类型：TeamFighter)队长信息
	attr_accessor:strLeaderName #(string)队长名字
	attr_accessor:bySize #(UINT8)当前人数

	#构造函数
	def initialize
		@TeamID = 0
		@DgnType = 0
		@stSetting = TeamSetting.new
		@stLeader = TeamFighter.new
		@strLeaderName = ''
		@bySize = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.TeamID = @TeamID
		obj.DgnType = @DgnType
		obj.stSetting = @stSetting
		obj.stLeader = @stLeader
		obj.strLeaderName = @strLeaderName
		obj.bySize = @bySize
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = TeamInfoForList.new
		s.TeamID = ByteUtil::readUINT32(data)
		s.DgnType = ByteUtil::readUINT16(data)
		s.stSetting = TeamSetting::fromStream(data)
		s.stLeader = TeamFighter::superFromStream(data)
		s.strLeaderName = ByteUtil::readSTRING(data)
		s.bySize = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = TeamInfoForList::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @TeamID)
		ByteUtil::writeUINT16(data, @DgnType)
		@stSetting.toStream(data)
		@stLeader.superToStream(data)
		ByteUtil::writeSTRING(data, @strLeaderName)
		ByteUtil::writeUINT8(data, @bySize)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetTeamList:根据模板查询可加入房间]的返回的参数组成的结构体
class SRetParam_GetTeamList
	attr_accessor:vecReturn#(TeamInfoForList的数组)返回的房间列表

	#构造函数
	def initialize
		@vecReturn = Array.new
	end
end

#函数[CreateTeam:请求创建房间]的返回的参数组成的结构体
class SRetParam_CreateTeam
	attr_accessor:dwTeamID#(UINT32)房间ID
	attr_accessor:eResult#(枚举类型：ETEAMResult)创建房间结果

	#构造函数
	def initialize
		@dwTeamID = 0
		@eResult = 0
	end
end

#函数[EnterTeam:请求加入房间]的返回的参数组成的结构体
class SRetParam_EnterTeam
	attr_accessor:dwTeamID#(UINT32)房间ID
	attr_accessor:eResult#(枚举类型：ETEAMResult)请求加入房间

	#构造函数
	def initialize
		@dwTeamID = 0
		@eResult = 0
	end
end

#函数[ResetFigter:请求更换将]的返回的参数组成的结构体
class SRetParam_ResetFigter
	attr_accessor:eResult#(枚举类型：ETEAMResult)请求更换将

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[ChangeSelfPos:交换自己的将位置]的返回的参数组成的结构体
class SRetParam_ChangeSelfPos
	attr_accessor:eResult#(枚举类型：ETEAMResult)返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[ChangeArrayPos:交换列的位置]的返回的参数组成的结构体
class SRetParam_ChangeArrayPos
	attr_accessor:eResult#(枚举类型：ETEAMResult)返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[LeaveTeam:请求离开房间]的返回的参数组成的结构体
class SRetParam_LeaveTeam
	attr_accessor:eResult#(枚举类型：ETEAMResult)返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[DoReady:玩家已经准备好]的返回的参数组成的结构体
class SRetParam_DoReady
	attr_accessor:eResult#(枚举类型：ETEAMResult)返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[CancelDoReady:玩家取消准备好]的返回的参数组成的结构体
class SRetParam_CancelDoReady
	attr_accessor:eResult#(枚举类型：ETEAMResult)返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[EnterDgn:请求进入副本]的返回的参数组成的结构体
class SRetParam_EnterDgn
	attr_accessor:eResult#(枚举类型：ETEAMResult)返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[KickOffPlayer:请求踢玩家出队伍]的返回的参数组成的结构体
class SRetParam_KickOffPlayer
	attr_accessor:eResult#(枚举类型：ETEAMResult)返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetTeamInfo:获取队伍信息]的返回的参数组成的结构体
class SRetParam_GetTeamInfo
	attr_accessor:eResult#(枚举类型：ETEAMResult)返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[ChangDgnType:换副本请求]的返回的参数组成的结构体
class SRetParam_ChangDgnType
	attr_accessor:eResult#(枚举类型：ETEAMResult)返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[ChangPet:换阵灵请求]的返回的参数组成的结构体
class SRetParam_ChangPet
	attr_accessor:eResult#(枚举类型：ETEAMResult)返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[ChangSetting:更改设置请求]的返回的参数组成的结构体
class SRetParam_ChangSetting
	attr_accessor:eResult#(枚举类型：ETEAMResult)返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[ChangLeader:换队长]的返回的参数组成的结构体
class SRetParam_ChangLeader
	attr_accessor:eResult#(枚举类型：ETEAMResult)返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：竞技场协议
class TeamGSBase < ProtocolBase
	#以下为发送函数
	#发送：根据模板查询可加入房间
	def send_GetTeamList(
		DgnType #(UINT16)房间ID
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, DgnType)
		return @svrHandler.sendPacket(data)
	end

	#发送：停止查询
	def send_StopTeamList(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求创建房间
	def send_CreateTeam(
		DgnType,  #(UINT16)副本类型
		stSetting #(类类型：TeamSetting)队伍设置
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, DgnType)
		stSetting.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求加入房间
	def send_EnterTeam(
		dwTeamID,  #(UINT32)房间ID
		dwPassWord #(UINT32)队伍密码
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwTeamID)
		ByteUtil::writeUINT32(data, dwPassWord)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求更换将
	def send_ResetFigter(
		qwNewFighter,  #(UINT64)新将
		byPos #(UINT8)将位置
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwNewFighter)
		ByteUtil::writeUINT8(data, byPos)
		return @svrHandler.sendPacket(data)
	end

	#发送：交换自己的将位置
	def send_ChangeSelfPos(
		byPos1,  #(UINT8)第1个位置
		byPos2 #(UINT8)第2个位置
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byPos1)
		ByteUtil::writeUINT8(data, byPos2)
		return @svrHandler.sendPacket(data)
	end

	#发送：交换列的位置
	def send_ChangeArrayPos(
		byPos1,  #(UINT8)第1个位置
		byPos2 #(UINT8)第2个位置
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byPos1)
		ByteUtil::writeUINT8(data, byPos2)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求离开房间
	def send_LeaveTeam(
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家已经准备好
	def send_DoReady(
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家取消准备好
	def send_CancelDoReady(
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求进入副本
	def send_EnterDgn(
	)
		sessionID = @sessionMgr.getNewSession(self, 10);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求踢玩家出队伍
	def send_KickOffPlayer(
		qwRoleID #(UINT64)踢的人
	)
		sessionID = @sessionMgr.getNewSession(self, 11);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取队伍信息
	def send_GetTeamInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 12);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 13
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：换副本请求
	def send_ChangDgnType(
		NewDgnType #(UINT16)新副本类型
	)
		sessionID = @sessionMgr.getNewSession(self, 13);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 14
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, NewDgnType)
		return @svrHandler.sendPacket(data)
	end

	#发送：换阵灵请求
	def send_ChangPet(
		qwRoleID #(UINT64)阵灵的主人
	)
		sessionID = @sessionMgr.getNewSession(self, 14);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 15
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：更改设置请求
	def send_ChangSetting(
		stSetting #(类类型：TeamSetting)队伍设置
	)
		sessionID = @sessionMgr.getNewSession(self, 15);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 16
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		stSetting.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：换队长
	def send_ChangLeader(
		qwNewLeader #(UINT64)新队长ID
	)
		sessionID = @sessionMgr.getNewSession(self, 16);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 17
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwNewLeader)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：房间信息更新
	def onRecv_TeamInfoUpdate(
		stInfo #(类类型：TeamInfo)房间信息
	)
		raise NotImplementedError
	end
	#接收：通告自己被踢
	def onRecv_NoticeKicked(
		DgnType #(UINT16)副本类型
	)
		raise NotImplementedError
	end
	#接收：房间列表更新
	def onRecv_UpdateTeamInfoList(
		eOpType, #(枚举类型：TeamListOP)操作类型
		vecInfo #(TeamInfoForList的数组)修改的数据
	)
		raise NotImplementedError
	end
	#接收：队伍解散
	def onRecv_TeamDelForList(
		dwTeamID #(UINT32)队伍ID
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：根据模板查询可加入房间
	def onReturn_GetTeamList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetTeamList)返回的参数
	)
	end

	#返回：请求创建房间
	def onReturn_CreateTeam(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_CreateTeam)返回的参数
	)
	end

	#返回：请求加入房间
	def onReturn_EnterTeam(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_EnterTeam)返回的参数
	)
	end

	#返回：请求更换将
	def onReturn_ResetFigter(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ResetFigter)返回的参数
	)
	end

	#返回：交换自己的将位置
	def onReturn_ChangeSelfPos(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ChangeSelfPos)返回的参数
	)
	end

	#返回：交换列的位置
	def onReturn_ChangeArrayPos(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ChangeArrayPos)返回的参数
	)
	end

	#返回：请求离开房间
	def onReturn_LeaveTeam(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LeaveTeam)返回的参数
	)
	end

	#返回：玩家已经准备好
	def onReturn_DoReady(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_DoReady)返回的参数
	)
	end

	#返回：玩家取消准备好
	def onReturn_CancelDoReady(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_CancelDoReady)返回的参数
	)
	end

	#返回：请求进入副本
	def onReturn_EnterDgn(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_EnterDgn)返回的参数
	)
	end

	#返回：请求踢玩家出队伍
	def onReturn_KickOffPlayer(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_KickOffPlayer)返回的参数
	)
	end

	#返回：获取队伍信息
	def onReturn_GetTeamInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetTeamInfo)返回的参数
	)
	end

	#返回：换副本请求
	def onReturn_ChangDgnType(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ChangDgnType)返回的参数
	)
	end

	#返回：换阵灵请求
	def onReturn_ChangPet(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ChangPet)返回的参数
	)
	end

	#返回：更改设置请求
	def onReturn_ChangSetting(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ChangSetting)返回的参数
	)
	end

	#返回：换队长
	def onReturn_ChangLeader(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ChangLeader)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：房间信息更新
	def _doRecv_TeamInfoUpdate(data)
		stInfo = TeamInfo::fromStream(data)
		return onRecv_TeamInfoUpdate(stInfo)
	end

	#接收处理：通告自己被踢
	def _doRecv_NoticeKicked(data)
		DgnType = ByteUtil::readUINT16(data)
		return onRecv_NoticeKicked(DgnType)
	end

	#接收处理：房间列表更新
	def _doRecv_UpdateTeamInfoList(data)
		eOpType = ByteUtil::readUINT8(data)
		vecInfo = TeamInfoForList::vectorFromStream(data)
		return onRecv_UpdateTeamInfoList(eOpType, vecInfo)
	end

	#接收处理：队伍解散
	def _doRecv_TeamDelForList(data)
		dwTeamID = ByteUtil::readUINT32(data)
		return onRecv_TeamDelForList(dwTeamID)
	end

#以下为返回处理函数
	#返回处理：根据模板查询可加入房间
	def _doReturn_GetTeamList(data)
		retParam = SRetParam_GetTeamList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecReturn = TeamInfoForList::vectorFromStream(data) #(TeamInfoForList的数组)返回的房间列表
		retParam.vecReturn = vecReturn
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetTeamList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：根据模板查询可加入房间
	def _onTimeOut_GetTeamList(sessionID)
		retParam = SRetParam_GetTeamList.new;
		onReturn_GetTeamList(2, retParam)
	end

	#返回处理：请求创建房间
	def _doReturn_CreateTeam(data)
		retParam = SRetParam_CreateTeam.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwTeamID = ByteUtil::readUINT32(data) #(UINT32)房间ID
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETEAMResult)创建房间结果
		retParam.dwTeamID = dwTeamID
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_CreateTeam(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求创建房间
	def _onTimeOut_CreateTeam(sessionID)
		retParam = SRetParam_CreateTeam.new;
		onReturn_CreateTeam(2, retParam)
	end

	#返回处理：请求加入房间
	def _doReturn_EnterTeam(data)
		retParam = SRetParam_EnterTeam.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwTeamID = ByteUtil::readUINT32(data) #(UINT32)房间ID
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETEAMResult)请求加入房间
		retParam.dwTeamID = dwTeamID
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_EnterTeam(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求加入房间
	def _onTimeOut_EnterTeam(sessionID)
		retParam = SRetParam_EnterTeam.new;
		onReturn_EnterTeam(2, retParam)
	end

	#返回处理：请求更换将
	def _doReturn_ResetFigter(data)
		retParam = SRetParam_ResetFigter.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETEAMResult)请求更换将
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ResetFigter(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求更换将
	def _onTimeOut_ResetFigter(sessionID)
		retParam = SRetParam_ResetFigter.new;
		onReturn_ResetFigter(2, retParam)
	end

	#返回处理：交换自己的将位置
	def _doReturn_ChangeSelfPos(data)
		retParam = SRetParam_ChangeSelfPos.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETEAMResult)返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ChangeSelfPos(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：交换自己的将位置
	def _onTimeOut_ChangeSelfPos(sessionID)
		retParam = SRetParam_ChangeSelfPos.new;
		onReturn_ChangeSelfPos(2, retParam)
	end

	#返回处理：交换列的位置
	def _doReturn_ChangeArrayPos(data)
		retParam = SRetParam_ChangeArrayPos.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETEAMResult)返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ChangeArrayPos(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：交换列的位置
	def _onTimeOut_ChangeArrayPos(sessionID)
		retParam = SRetParam_ChangeArrayPos.new;
		onReturn_ChangeArrayPos(2, retParam)
	end

	#返回处理：请求离开房间
	def _doReturn_LeaveTeam(data)
		retParam = SRetParam_LeaveTeam.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETEAMResult)返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LeaveTeam(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求离开房间
	def _onTimeOut_LeaveTeam(sessionID)
		retParam = SRetParam_LeaveTeam.new;
		onReturn_LeaveTeam(2, retParam)
	end

	#返回处理：玩家已经准备好
	def _doReturn_DoReady(data)
		retParam = SRetParam_DoReady.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETEAMResult)返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_DoReady(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：玩家已经准备好
	def _onTimeOut_DoReady(sessionID)
		retParam = SRetParam_DoReady.new;
		onReturn_DoReady(2, retParam)
	end

	#返回处理：玩家取消准备好
	def _doReturn_CancelDoReady(data)
		retParam = SRetParam_CancelDoReady.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETEAMResult)返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_CancelDoReady(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：玩家取消准备好
	def _onTimeOut_CancelDoReady(sessionID)
		retParam = SRetParam_CancelDoReady.new;
		onReturn_CancelDoReady(2, retParam)
	end

	#返回处理：请求进入副本
	def _doReturn_EnterDgn(data)
		retParam = SRetParam_EnterDgn.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETEAMResult)返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_EnterDgn(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求进入副本
	def _onTimeOut_EnterDgn(sessionID)
		retParam = SRetParam_EnterDgn.new;
		onReturn_EnterDgn(2, retParam)
	end

	#返回处理：请求踢玩家出队伍
	def _doReturn_KickOffPlayer(data)
		retParam = SRetParam_KickOffPlayer.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETEAMResult)返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_KickOffPlayer(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求踢玩家出队伍
	def _onTimeOut_KickOffPlayer(sessionID)
		retParam = SRetParam_KickOffPlayer.new;
		onReturn_KickOffPlayer(2, retParam)
	end

	#返回处理：获取队伍信息
	def _doReturn_GetTeamInfo(data)
		retParam = SRetParam_GetTeamInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETEAMResult)返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetTeamInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取队伍信息
	def _onTimeOut_GetTeamInfo(sessionID)
		retParam = SRetParam_GetTeamInfo.new;
		onReturn_GetTeamInfo(2, retParam)
	end

	#返回处理：换副本请求
	def _doReturn_ChangDgnType(data)
		retParam = SRetParam_ChangDgnType.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETEAMResult)返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ChangDgnType(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：换副本请求
	def _onTimeOut_ChangDgnType(sessionID)
		retParam = SRetParam_ChangDgnType.new;
		onReturn_ChangDgnType(2, retParam)
	end

	#返回处理：换阵灵请求
	def _doReturn_ChangPet(data)
		retParam = SRetParam_ChangPet.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETEAMResult)返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ChangPet(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：换阵灵请求
	def _onTimeOut_ChangPet(sessionID)
		retParam = SRetParam_ChangPet.new;
		onReturn_ChangPet(2, retParam)
	end

	#返回处理：更改设置请求
	def _doReturn_ChangSetting(data)
		retParam = SRetParam_ChangSetting.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETEAMResult)返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ChangSetting(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：更改设置请求
	def _onTimeOut_ChangSetting(sessionID)
		retParam = SRetParam_ChangSetting.new;
		onReturn_ChangSetting(2, retParam)
	end

	#返回处理：换队长
	def _doReturn_ChangLeader(data)
		retParam = SRetParam_ChangLeader.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETEAMResult)返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ChangLeader(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：换队长
	def _onTimeOut_ChangLeader(sessionID)
		retParam = SRetParam_ChangLeader.new;
		onReturn_ChangLeader(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 56;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_TeamInfoUpdate' #FuncID: 1
		@recvFuncList[1] = '_doRecv_NoticeKicked' #FuncID: 2
		@recvFuncList[2] = '_doRecv_UpdateTeamInfoList' #FuncID: 3
		@recvFuncList[3] = '_doRecv_TeamDelForList' #FuncID: 4

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetTeamList' #FuncID: 1
		@retFuncList[1] = '_doReturn_CreateTeam' #FuncID: 2
		@retFuncList[2] = '_doReturn_EnterTeam' #FuncID: 3
		@retFuncList[3] = '_doReturn_ResetFigter' #FuncID: 4
		@retFuncList[4] = '_doReturn_ChangeSelfPos' #FuncID: 5
		@retFuncList[5] = '_doReturn_ChangeArrayPos' #FuncID: 6
		@retFuncList[6] = '_doReturn_LeaveTeam' #FuncID: 7
		@retFuncList[7] = '_doReturn_DoReady' #FuncID: 8
		@retFuncList[8] = '_doReturn_CancelDoReady' #FuncID: 9
		@retFuncList[9] = '_doReturn_EnterDgn' #FuncID: 10
		@retFuncList[10] = '_doReturn_KickOffPlayer' #FuncID: 11
		@retFuncList[11] = '_doReturn_GetTeamInfo' #FuncID: 12
		@retFuncList[12] = '_doReturn_ChangDgnType' #FuncID: 13
		@retFuncList[13] = '_doReturn_ChangPet' #FuncID: 14
		@retFuncList[14] = '_doReturn_ChangSetting' #FuncID: 15
		@retFuncList[15] = '_doReturn_ChangLeader' #FuncID: 16

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetTeamList' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_CreateTeam' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_EnterTeam' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_ResetFigter' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_ChangeSelfPos' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_ChangeArrayPos' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_LeaveTeam' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_DoReady' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_CancelDoReady' #FuncID: 9
		@timeFuncList[9] = '_onTimeOut_EnterDgn' #FuncID: 10
		@timeFuncList[10] = '_onTimeOut_KickOffPlayer' #FuncID: 11
		@timeFuncList[11] = '_onTimeOut_GetTeamInfo' #FuncID: 12
		@timeFuncList[12] = '_onTimeOut_ChangDgnType' #FuncID: 13
		@timeFuncList[13] = '_onTimeOut_ChangPet' #FuncID: 14
		@timeFuncList[14] = '_onTimeOut_ChangSetting' #FuncID: 15
		@timeFuncList[15] = '_onTimeOut_ChangLeader' #FuncID: 16
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

