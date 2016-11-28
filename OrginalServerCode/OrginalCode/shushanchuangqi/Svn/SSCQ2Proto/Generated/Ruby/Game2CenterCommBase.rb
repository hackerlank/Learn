#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    Game2CenterComm.rb
#  Purpose:      GameServer到CenterServer的通信协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './BattleGSBase.rb'
require_relative './BeautyLogGSBase.rb'
require_relative './EventCenterBase.rb'
require_relative './FriendProtBase.rb'
require_relative './GuildProtBase.rb'
require_relative './ItemProtBase.rb'
require_relative './LogDataDefineBase.rb'
require_relative './MailProtBase.rb'
require_relative './MallProtBase.rb'
require_relative './PHPProtBase.rb'
require_relative './ProtoCommonBase.rb'
require_relative './RoleInfoDefineBase.rb'
require_relative './ShipProtBase.rb'
require_relative './TripodProtBase.rb'

#以下为类型定义

#数据同步键
class ESyncKey
	ESYNCNONE = 0#无
	ESYNCGAMESVRC2S = 1#GameServer之间的C2S通信协议
	ESYNCGAMESVRS2C = 2#GameServer之间的S2C通信协议
end

#角色同步属性字段
class EUserSyncPropField
	ESYNCPROPLEVEL = 0#等级
	ESYNCPROPNATION = 1#阵营
	ESYNCPROPYELLOWDIAMOND = 2#QQ黄钻
	ESYNCPROPGOLD = 3#仙石
	ESYNCPROPSILVER = 4#银币
	ESYNCPROPCOUPON = 5#礼券
	ESYNCPROPBYTITLE = 6#称号
	ESYNCPROPBYWALLOW = 7#防沉迷
	ESYNCPROPVIPLEVEL = 8#vip等级
	ESYNCPROPQUALITY = 9#主将品质
	ESYNCPROPPLAYERFIGHTERID = 10#主将ID
	ESYNCPROPTOTALRECHARGE = 11#玩家每次仙石充值数
end

#操作原因
class EOpSource
	EOPAREAAWARD = 0#斗剑奖励
	EOPAREAFLUSH = 1#斗剑刷将
	EOPCLEARAREACD = 2#清除斗剑CD
	EOPARENAWIRSHIP = 3#斗剑膜拜
	EOPGUILDDONATE = 4#帮派捐献
	EOPGUILDWORSHIP = 5#帮派供奉
	EOPBUYAREATIMES = 6#购买挑战次数
	EOPLADDERAWARD = 7#天梯奖励
	EOPAREAAWARDDAYS = 8#斗剑挑战奖励
	EOPCLEARLADDERCD = 9#天梯cd清除
	EOPADOREAWARD = 10#崇拜奖励
	EOPTRIPODAWARD = 11#九疑鼎扇火、协助奖励
end

#更新/查询用户数据
class EUpdateError
	EUPDATEERRORNOUSER = 0#无用户
	EUPDATEERRORITEMCOUNT = 1#物品不足
	EUPDATEERRORMONEYCOUNT = 2#钱币不足
	EUPDATEERRORUNKOWN = 3#未知错误
end

#玩家整形属性字段
class EPlayerUINTProp
	EPROPTOPDEMONFLOORID = 0#镇妖塔最高层
	EPROPPRIZEDEMONFLOORID = 1#镇妖塔奖励层数
end

#全服活动类型信息
class EWonderActType
	EACTTRUMP = 1#法宝
	EACTLEVEL = 2#等级
	EACTFIGHTER = 3#散仙
	EACTFORMATION = 4#阵灵
	EACTDUNGON = 5#副本
	EACTBEAUTY = 6#美女
	EACTHORSE = 7#坐骑
	EACTEND = 8#结束
end

#活动消息同步
class ActiveParam
	ESHIP = 0#运船金船
end

#物品信息
class SUserItem
	attr_accessor:dwTypeID #(UINT32)物品ID/钱币类型
	attr_accessor:dwCount #(UINT32)数量

	#构造函数
	def initialize
		@dwTypeID = 0
		@dwCount = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwTypeID = @dwTypeID
		obj.dwCount = @dwCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SUserItem.new
		s.dwTypeID = ByteUtil::readUINT32(data)
		s.dwCount = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SUserItem::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwTypeID)
		ByteUtil::writeUINT32(data, @dwCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#角色进入游戏信息
class SUserEnterInfo
	attr_accessor:wHeroID #(UINT16)主将ID
	attr_accessor:eSex #(枚类型：ProtoCommon::ESexType)性别
	attr_accessor:eCareer #(枚类型：ProtoCommon::ECareerType)职业
	attr_accessor:strName #(string)玩家名字
	attr_accessor:byLevel #(UINT8)玩家等级
	attr_accessor:byNation #(UINT8)国家
	attr_accessor:byGMLvl #(UINT8)GM权限
	attr_accessor:dwTotalRecharge #(UINT32)充值金额
	attr_accessor:dwCreateTime #(UINT32)创角时间
	attr_accessor:dwLoginTime #(UINT32)上次登陆时间
	attr_accessor:dwOfflineTime #(UINT32)上次下线时间
	attr_accessor:dwLockExpireTime #(UINT32)被封禁结束时间
	attr_accessor:dwForbExpireTime #(UINT32)被禁言结束时间
	attr_accessor:dwGold #(UINT32)仙石
	attr_accessor:dwSilver #(UINT32)银币
	attr_accessor:dwCoupon #(UINT32)礼券
	attr_accessor:dwSoul #(UINT32)魂魄
	attr_accessor:dwPrestige #(UINT32)声望
	attr_accessor:dwHonor #(UINT32)荣誉
	attr_accessor:dwPExp #(UINT32)修为
	attr_accessor:dwSigil #(UINT32)符印
	attr_accessor:dwCentsY #(UINT32)仙元
	attr_accessor:dwAction #(UINT32)体力
	attr_accessor:dwSop #(UINT32)阅历
	attr_accessor:dwBTPoint #(UINT32)战斗力
	attr_accessor:vecOwnTitle #(UINT16数组)拥有称号
	attr_accessor:vecEquipTitle #(UINT16数组)装备称号
	attr_accessor:byDomain #(UINT8)渠道
	attr_accessor:byDomainLvl #(UINT8)渠道等级
	attr_accessor:byDisplayLvl #(UINT8)显示等级
	attr_accessor:byDomainYear #(UINT8)年费
	attr_accessor:szOpenId #(string)szOpenId
	attr_accessor:szOpenKey #(string)szOpenKey
	attr_accessor:qwInvitedID #(UINT64)邀请
	attr_accessor:byWallow #(UINT8)防沉迷
	attr_accessor:byVIPLvl #(UINT8)VIP等级
	attr_accessor:byYDLvl #(UINT8)黄钻等级
	attr_accessor:strSign #(string)签名
	attr_accessor:wMood #(UINT16)心情表情
	attr_accessor:dwFighterPower #(UINT32)战斗力
	attr_accessor:byQuality #(UINT8)主将品质
	attr_accessor:wPlayerFighterID #(UINT16)主将ID
	attr_accessor:vecFriendsInfo #(SFriendDBInfo的数组)关系信息
	attr_accessor:vecGameVars #(SVarsDBInfo的数组)传到center的Var数据
	attr_accessor:vecArenaInfo #(SRoleArenaInfo的数组)玩家斗剑信息
	attr_accessor:vecFireInfo #(SFireInfo的数组)玩家九疑鼎的火种信息
	attr_accessor:szIconAppear #(string)开启的功能
	attr_accessor:vecPlatform #(SPlatformParam的数组)平台参数列表
	attr_accessor:vecShipReport #(ShipReport的数组)金船战报
	attr_accessor:sShipData #(类类型：ShipProt::PlayerSelfShipData)自己金船相关信息

	#构造函数
	def initialize
		@wHeroID = 0
		@eSex = 0
		@eCareer = 0
		@strName = ''
		@byLevel = 0
		@byNation = 0
		@byGMLvl = 0
		@dwTotalRecharge = 0
		@dwCreateTime = 0
		@dwLoginTime = 0
		@dwOfflineTime = 0
		@dwLockExpireTime = 0
		@dwForbExpireTime = 0
		@dwGold = 0
		@dwSilver = 0
		@dwCoupon = 0
		@dwSoul = 0
		@dwPrestige = 0
		@dwHonor = 0
		@dwPExp = 0
		@dwSigil = 0
		@dwCentsY = 0
		@dwAction = 0
		@dwSop = 0
		@dwBTPoint = 0
		@vecOwnTitle = Array.new
		@vecEquipTitle = Array.new
		@byDomain = 0
		@byDomainLvl = 0
		@byDisplayLvl = 0
		@byDomainYear = 0
		@szOpenId = ''
		@szOpenKey = ''
		@qwInvitedID = 0
		@byWallow = 0
		@byVIPLvl = 0
		@byYDLvl = 0
		@strSign = ''
		@wMood = 0
		@dwFighterPower = 0
		@byQuality = 0
		@wPlayerFighterID = 0
		@vecFriendsInfo = Array.new
		@vecGameVars = Array.new
		@vecArenaInfo = Array.new
		@vecFireInfo = Array.new
		@szIconAppear = ''
		@vecPlatform = Array.new
		@vecShipReport = Array.new
		@sShipData = PlayerSelfShipData.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wHeroID = @wHeroID
		obj.eSex = @eSex
		obj.eCareer = @eCareer
		obj.strName = @strName
		obj.byLevel = @byLevel
		obj.byNation = @byNation
		obj.byGMLvl = @byGMLvl
		obj.dwTotalRecharge = @dwTotalRecharge
		obj.dwCreateTime = @dwCreateTime
		obj.dwLoginTime = @dwLoginTime
		obj.dwOfflineTime = @dwOfflineTime
		obj.dwLockExpireTime = @dwLockExpireTime
		obj.dwForbExpireTime = @dwForbExpireTime
		obj.dwGold = @dwGold
		obj.dwSilver = @dwSilver
		obj.dwCoupon = @dwCoupon
		obj.dwSoul = @dwSoul
		obj.dwPrestige = @dwPrestige
		obj.dwHonor = @dwHonor
		obj.dwPExp = @dwPExp
		obj.dwSigil = @dwSigil
		obj.dwCentsY = @dwCentsY
		obj.dwAction = @dwAction
		obj.dwSop = @dwSop
		obj.dwBTPoint = @dwBTPoint
		obj.vecOwnTitle = @vecOwnTitle
		obj.vecEquipTitle = @vecEquipTitle
		obj.byDomain = @byDomain
		obj.byDomainLvl = @byDomainLvl
		obj.byDisplayLvl = @byDisplayLvl
		obj.byDomainYear = @byDomainYear
		obj.szOpenId = @szOpenId
		obj.szOpenKey = @szOpenKey
		obj.qwInvitedID = @qwInvitedID
		obj.byWallow = @byWallow
		obj.byVIPLvl = @byVIPLvl
		obj.byYDLvl = @byYDLvl
		obj.strSign = @strSign
		obj.wMood = @wMood
		obj.dwFighterPower = @dwFighterPower
		obj.byQuality = @byQuality
		obj.wPlayerFighterID = @wPlayerFighterID
		obj.vecFriendsInfo = @vecFriendsInfo
		obj.vecGameVars = @vecGameVars
		obj.vecArenaInfo = @vecArenaInfo
		obj.vecFireInfo = @vecFireInfo
		obj.szIconAppear = @szIconAppear
		obj.vecPlatform = @vecPlatform
		obj.vecShipReport = @vecShipReport
		obj.sShipData = @sShipData
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SUserEnterInfo.new
		s.wHeroID = ByteUtil::readUINT16(data)
		s.eSex = ByteUtil::readUINT8(data)
		s.eCareer = ByteUtil::readUINT8(data)
		s.strName = ByteUtil::readSTRING(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.byNation = ByteUtil::readUINT8(data)
		s.byGMLvl = ByteUtil::readUINT8(data)
		s.dwTotalRecharge = ByteUtil::readUINT32(data)
		s.dwCreateTime = ByteUtil::readUINT32(data)
		s.dwLoginTime = ByteUtil::readUINT32(data)
		s.dwOfflineTime = ByteUtil::readUINT32(data)
		s.dwLockExpireTime = ByteUtil::readUINT32(data)
		s.dwForbExpireTime = ByteUtil::readUINT32(data)
		s.dwGold = ByteUtil::readUINT32(data)
		s.dwSilver = ByteUtil::readUINT32(data)
		s.dwCoupon = ByteUtil::readUINT32(data)
		s.dwSoul = ByteUtil::readUINT32(data)
		s.dwPrestige = ByteUtil::readUINT32(data)
		s.dwHonor = ByteUtil::readUINT32(data)
		s.dwPExp = ByteUtil::readUINT32(data)
		s.dwSigil = ByteUtil::readUINT32(data)
		s.dwCentsY = ByteUtil::readUINT32(data)
		s.dwAction = ByteUtil::readUINT32(data)
		s.dwSop = ByteUtil::readUINT32(data)
		s.dwBTPoint = ByteUtil::readUINT32(data)
		s.vecOwnTitle = ByteUtil::readVecUINT16(data)
		s.vecEquipTitle = ByteUtil::readVecUINT16(data)
		s.byDomain = ByteUtil::readUINT8(data)
		s.byDomainLvl = ByteUtil::readUINT8(data)
		s.byDisplayLvl = ByteUtil::readUINT8(data)
		s.byDomainYear = ByteUtil::readUINT8(data)
		s.szOpenId = ByteUtil::readSTRING(data)
		s.szOpenKey = ByteUtil::readSTRING(data)
		s.qwInvitedID = ByteUtil::readUINT64(data)
		s.byWallow = ByteUtil::readUINT8(data)
		s.byVIPLvl = ByteUtil::readUINT8(data)
		s.byYDLvl = ByteUtil::readUINT8(data)
		s.strSign = ByteUtil::readSTRING(data)
		s.wMood = ByteUtil::readUINT16(data)
		s.dwFighterPower = ByteUtil::readUINT32(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.wPlayerFighterID = ByteUtil::readUINT16(data)
		s.vecFriendsInfo = SFriendDBInfo::vectorFromStream(data)
		s.vecGameVars = SVarsDBInfo::vectorFromStream(data)
		s.vecArenaInfo = SRoleArenaInfo::vectorFromStream(data)
		s.vecFireInfo = SFireInfo::vectorFromStream(data)
		s.szIconAppear = ByteUtil::readSTRING(data)
		s.vecPlatform = SPlatformParam::vectorFromStream(data)
		s.vecShipReport = ShipReport::vectorFromStream(data)
		s.sShipData = PlayerSelfShipData::fromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SUserEnterInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wHeroID)
		ByteUtil::writeUINT8(data, @eSex)
		ByteUtil::writeUINT8(data, @eCareer)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT8(data, @byNation)
		ByteUtil::writeUINT8(data, @byGMLvl)
		ByteUtil::writeUINT32(data, @dwTotalRecharge)
		ByteUtil::writeUINT32(data, @dwCreateTime)
		ByteUtil::writeUINT32(data, @dwLoginTime)
		ByteUtil::writeUINT32(data, @dwOfflineTime)
		ByteUtil::writeUINT32(data, @dwLockExpireTime)
		ByteUtil::writeUINT32(data, @dwForbExpireTime)
		ByteUtil::writeUINT32(data, @dwGold)
		ByteUtil::writeUINT32(data, @dwSilver)
		ByteUtil::writeUINT32(data, @dwCoupon)
		ByteUtil::writeUINT32(data, @dwSoul)
		ByteUtil::writeUINT32(data, @dwPrestige)
		ByteUtil::writeUINT32(data, @dwHonor)
		ByteUtil::writeUINT32(data, @dwPExp)
		ByteUtil::writeUINT32(data, @dwSigil)
		ByteUtil::writeUINT32(data, @dwCentsY)
		ByteUtil::writeUINT32(data, @dwAction)
		ByteUtil::writeUINT32(data, @dwSop)
		ByteUtil::writeUINT32(data, @dwBTPoint)
		ByteUtil::writeVecUINT16(data, @vecOwnTitle)
		ByteUtil::writeVecUINT16(data, @vecEquipTitle)
		ByteUtil::writeUINT8(data, @byDomain)
		ByteUtil::writeUINT8(data, @byDomainLvl)
		ByteUtil::writeUINT8(data, @byDisplayLvl)
		ByteUtil::writeUINT8(data, @byDomainYear)
		ByteUtil::writeSTRING(data, @szOpenId)
		ByteUtil::writeSTRING(data, @szOpenKey)
		ByteUtil::writeUINT64(data, @qwInvitedID)
		ByteUtil::writeUINT8(data, @byWallow)
		ByteUtil::writeUINT8(data, @byVIPLvl)
		ByteUtil::writeUINT8(data, @byYDLvl)
		ByteUtil::writeSTRING(data, @strSign)
		ByteUtil::writeUINT16(data, @wMood)
		ByteUtil::writeUINT32(data, @dwFighterPower)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT16(data, @wPlayerFighterID)
		SFriendDBInfo::vectorToStream(data, @vecFriendsInfo)
		SVarsDBInfo::vectorToStream(data, @vecGameVars)
		SRoleArenaInfo::vectorToStream(data, @vecArenaInfo)
		SFireInfo::vectorToStream(data, @vecFireInfo)
		ByteUtil::writeSTRING(data, @szIconAppear)
		SPlatformParam::vectorToStream(data, @vecPlatform)
		ShipReport::vectorToStream(data, @vecShipReport)
		@sShipData.toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#灵山商店数据
class SLingShanShopData
	attr_accessor:qwGuildID #(UINT64)帮派ID
	attr_accessor:vecLingShanType #(UINT8数组)灵山类型

	#构造函数
	def initialize
		@qwGuildID = 0
		@vecLingShanType = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwGuildID = @qwGuildID
		obj.vecLingShanType = @vecLingShanType
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SLingShanShopData.new
		s.qwGuildID = ByteUtil::readUINT64(data)
		s.vecLingShanType = ByteUtil::readVecUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SLingShanShopData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwGuildID)
		ByteUtil::writeVecUINT8(data, @vecLingShanType)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#活动状态数据
class SActivityState
	attr_accessor:dwActID #(UINT32)活动ID
	attr_accessor:bOpen #(bool)状态

	#构造函数
	def initialize
		@dwActID = 0
		@bOpen = false
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwActID = @dwActID
		obj.bOpen = @bOpen
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SActivityState.new
		s.dwActID = ByteUtil::readUINT32(data)
		s.bOpen = ByteUtil::readBOOL(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SActivityState::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwActID)
		ByteUtil::writeBOOL(data, @bOpen)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[IsFriend:是否为好友]的返回的参数组成的结构体
class SRetParam_IsFriend
	attr_accessor:byRet#(UINT8)0是好友 1非好友

	#构造函数
	def initialize
		@byRet = 0
	end
end

#函数[IsSameGuild:是否在同一个帮派]的返回的参数组成的结构体
class SRetParam_IsSameGuild
	attr_accessor:byRet#(UINT8)0在同一个帮派 1不在同一个帮派

	#构造函数
	def initialize
		@byRet = 0
	end
end

#函数[GetGuildID:获取帮派ID]的返回的参数组成的结构体
class SRetParam_GetGuildID
	attr_accessor:qwGuildID#(UINT64)帮派ID
	attr_accessor:strGuildName#(string)帮派名称
	attr_accessor:byGuildLvl#(UINT8)帮派等级
	attr_accessor:strGuildOwnerName#(string)帮主名称

	#构造函数
	def initialize
		@qwGuildID = 0
		@strGuildName = ''
		@byGuildLvl = 0
		@strGuildOwnerName = ''
	end
end

#函数[GetGuildName:获取帮派ID]的返回的参数组成的结构体
class SRetParam_GetGuildName
	attr_accessor:bValid#(bool)是否已经找到
	attr_accessor:qwGuildID#(UINT64)帮派ID
	attr_accessor:strGuildName#(string)帮派名称
	attr_accessor:byGuildLvl#(UINT8)帮派等级
	attr_accessor:strGuildOwnerName#(string)帮主名称

	#构造函数
	def initialize
		@bValid = false
		@qwGuildID = 0
		@strGuildName = ''
		@byGuildLvl = 0
		@strGuildOwnerName = ''
	end
end

#函数[SubGuildContribution:扣除帮贡]的返回的参数组成的结构体
class SRetParam_SubGuildContribution
	attr_accessor:eResult#(枚类型：GuildProt::EGuildResult)检测结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetSystemVar:获取全局Var值]的返回的参数组成的结构体
class SRetParam_GetSystemVar
	attr_accessor:vecVars#(UINT16数组)varID列表
	attr_accessor:vecValues#(UINT64数组)var数值列表(必须与vecVars对应)

	#构造函数
	def initialize
		@vecVars = Array.new
		@vecValues = Array.new
	end
end

#函数[SetSystemVar:设置全局Var值]的返回的参数组成的结构体
class SRetParam_SetSystemVar
	attr_accessor:vecVarID#(UINT16数组)设置成功的varID列表(只是校验用)

	#构造函数
	def initialize
		@vecVarID = Array.new
	end
end

#协议类：GameServer到CenterServer的通信协议
class Game2CenterCommBase < ProtocolBase
	#以下为发送函数
	#发送：心跳
	def send_KeepAlive(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：GameServer初始化完成通知
	def send_GameSvrInitNft(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：CenterServer状态请求
	def send_GetCenterState(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：GameServer数据同步请求
	def send_GameSvrDataSyncReq(
		eSyncKey,  #(枚举类型：ESyncKey)同步Key
		wDestGroup,  #(UINT16)目的服务器组号
		byDestIndex,  #(UINT8)目的GameServer(0为全部)
		vecParam,  #(INT32数组)同步参数
		strSyncData #(string)同步数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eSyncKey)
		ByteUtil::writeUINT16(data, wDestGroup)
		ByteUtil::writeUINT8(data, byDestIndex)
		ByteUtil::writeVecINT32(data, vecParam)
		ByteUtil::writeSTRING(data, strSyncData)
		return @svrHandler.sendPacket(data)
	end

	#发送：账号进入游戏通知
	def send_UserLoginNtf(
		qwUsrID,  #(UINT64)账号ID
		rUserInfo #(类类型：SUserEnterInfo)帐号进入信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		rUserInfo.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：账号退出游戏通知
	def send_UserLogoutNtf(
		qwUsrID #(UINT64)账号ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		return @svrHandler.sendPacket(data)
	end

	#发送：账号替换通知
	def send_UserReplaceNtf(
		qwUsrID #(UINT64)账号ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		return @svrHandler.sendPacket(data)
	end

	#发送：帐号跳GameServer通知
	def send_UserJumpSvrNtf(
		qwUsrID #(UINT64)账号ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家同步属性通知
	def send_UserSyncPropNtf(
		qwUsrID,  #(UINT64)账号ID
		eField,  #(枚举类型：EUserSyncPropField)同步属性类型
		strVal #(string)值序列化字符串
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeUINT8(data, eField)
		ByteUtil::writeSTRING(data, strVal)
		return @svrHandler.sendPacket(data)
	end

	#发送：是否为好友
	def send_IsFriend(
		qwUsrID,  #(UINT64)账号ID
		qwFriID #(UINT64)好友账号ID
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeUINT64(data, qwFriID)
		return @svrHandler.sendPacket(data)
	end

	#发送：是否在同一个帮派
	def send_IsSameGuild(
		qwUsrID,  #(UINT64)账号ID
		qwOtherID #(UINT64)帮派成员ID
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeUINT64(data, qwOtherID)
		return @svrHandler.sendPacket(data)
	end

	#发送：发送系统邮件,自定义字符串
	def send_SendMail(
		strSender,  #(string)发送者
		strTitle,  #(string)标题
		strMsgInfo,  #(类类型：MailProt::SysMailSendTxt)内容
		vecItemInfo,  #(SMailBaseAttachment的数组)物品信息
		vecTargetIDs #(UINT64数组)接受者IDs
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeSTRING(data, strSender)
		ByteUtil::writeSTRING(data, strTitle)
		strMsgInfo.toStream(data)
		SMailBaseAttachment::superVectorToStream(data, vecItemInfo)
		ByteUtil::writeVecUINT64(data, vecTargetIDs)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取帮派ID
	def send_GetGuildID(
		qwRoleID #(UINT64)玩家ID
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 13
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取帮派ID
	def send_GetGuildName(
		qwGuildID #(UINT64)帮派ID
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 14
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwGuildID)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派广播
	def send_NotifyGuildInfo(
		qwGuildID,  #(UINT64)帮派ID
		vecExcpRoleID,  #(UINT64数组)不需要通知的人ID
		strData #(string)具体信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 15
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwGuildID)
		ByteUtil::writeVecUINT64(data, vecExcpRoleID)
		ByteUtil::writeSTRING(data, strData)
		return @svrHandler.sendPacket(data)
	end

	#发送：同步增加icon
	def send_SynIconAppear(
		qwRoleID,  #(UINT64)角色ID
		szIcon #(string)功能
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 16
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeSTRING(data, szIcon)
		return @svrHandler.sendPacket(data)
	end

	#发送：增加帮派贡献
	def send_AddGuildContribution(
		qwRoleID,  #(UINT64)玩家ID
		dwContribution #(UINT32)帮派贡献
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 17
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT32(data, dwContribution)
		return @svrHandler.sendPacket(data)
	end

	#发送：增加玩家九疑鼎火种
	def send_ActiveTripodFire(
		qwRoleID,  #(UINT64)玩家ID
		wFireID #(UINT16)火种ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 18
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT16(data, wFireID)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新登录参数
	def send_UpdatePlatformParam(
		qwRoleID,  #(UINT64)玩家ID
		vecPlatform,  #(SPlatformParam的数组)平台参数列表
		dwIndex #(UINT32)当前平台索引
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 19
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		SPlatformParam::vectorToStream(data, vecPlatform)
		ByteUtil::writeUINT32(data, dwIndex)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新登录其他参数
	def send_UpdateEnterString(
		qwRoleID,  #(UINT64)玩家ID
		vecEnterString #(string数组)平台参数列表
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 20
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeVecSTRING(data, vecEnterString)
		return @svrHandler.sendPacket(data)
	end

	#发送：发送全服活动信息
	def send_SendWonderType(
		eActType,  #(枚举类型：EWonderActType)活动类型
		qwRoleID,  #(UINT64)玩家ID
		dwCond #(UINT32)条件ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 21
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eActType)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT32(data, dwCond)
		return @svrHandler.sendPacket(data)
	end

	#发送：扣除帮贡
	def send_SubGuildContribution(
		qwRoleID,  #(UINT64)玩家ID
		dwContribution #(UINT32)帮贡数量
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 22
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT32(data, dwContribution)
		return @svrHandler.sendPacket(data)
	end

	#发送：美女抽奖log
	def send_BeautyLotteryLog(
		oBeautyLog #(类类型：BeautyLogGS::SBeautyLog)抽奖log
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 23
		ByteUtil::writeINT8(data, funcID)
		oBeautyLog.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：邀请好友成功
	def send_InviteFriend(
		qwUserID,  #(UINT64)邀请人
		qwInvitedUserID #(UINT64)被邀请人
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 24
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeUINT64(data, qwInvitedUserID)
		return @svrHandler.sendPacket(data)
	end

	#发送：通知帮派兑换物品开始
	def send_NotifyGuildExchangedItemBegin(
		vecLingShanShopData #(SLingShanShopData的数组)灵山商店数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 25
		ByteUtil::writeINT8(data, funcID)
		SLingShanShopData::vectorToStream(data, vecLingShanShopData)
		return @svrHandler.sendPacket(data)
	end

	#发送：同步在Center使用的buff结束时间(待修改完善)
	def send_SyncGameBuffUseInCenter(
		qwRoleID,  #(UINT64)玩家ID
		wBuffID,  #(UINT16)buffID
		dwEndTime #(UINT32)结束时间
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 26
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT16(data, wBuffID)
		ByteUtil::writeUINT32(data, dwEndTime)
		return @svrHandler.sendPacket(data)
	end

	#发送：同步活动参数
	def send_SyncGameActiveParam(
		eParam,  #(枚举类型：ActiveParam)参数类型
		vecParam #(UINT32数组)参数
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 27
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eParam)
		ByteUtil::writeVecUINT32(data, vecParam)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取全局Var值
	def send_GetSystemVar(
		vecVarID #(UINT16数组)varID列表
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 28
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeVecUINT16(data, vecVarID)
		return @svrHandler.sendPacket(data)
	end

	#发送：设置全局Var值
	def send_SetSystemVar(
		vecVars,  #(UINT16数组)varID列表
		vecValues #(UINT64数组)var数值列表(必须与vecVars对应)
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 29
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeVecUINT16(data, vecVars)
		ByteUtil::writeVecUINT64(data, vecValues)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：替换帐号
	def onRecv_ReplaceUser(
		qwUsrID #(UINT64)帐号ID
	)
		raise NotImplementedError
	end
	#接收：GM指令
	def onRecv_GMCmd(
		qwUsrID, #(UINT64)帐号ID
		strInfo #(string)GM指令信息
	)
		raise NotImplementedError
	end
	#接收：充值接口
	def onRecv_AddTotalRecharge(
		oRecharge, #(类类型：RoleInfoDefine::SRecharge)充值仙石的数据
		strUdp1, #(string)udpLog参数1(平台传来的)
		strUdp2 #(string)udpLog参数2(平台传来的)
	)
		raise NotImplementedError
	end
	#接收：充值接口(改版:加仙石礼包到邮件)
	def onRecv_AddRechargeMailItem(
		oRecharge, #(类类型：RoleInfoDefine::SRecharge)充值仙石的数据
		strUdp1, #(string)udpLog参数1(平台传来的)
		strUdp2 #(string)udpLog参数2(平台传来的)
	)
		raise NotImplementedError
	end
	#接收：补偿玩家未创建预先充值的仙石
	def onRecv_AddTotalPrepaid(
		qwUsrID, #(UINT64)帐号ID
		dwGold #(UINT32)仙石数量
	)
		raise NotImplementedError
	end
	#接收：Q点直购道具
	def onRecv_AddQQCoinBuyItem(
		qwUsrID, #(UINT64)帐号ID
		vecUserItem #(SUserItem的数组)物品列表
	)
		raise NotImplementedError
	end
	#接收：询问可否提取附件
	def onRecv_CheckMailAttch(
		qwUsrID, #(UINT64)帐号ID
		qwMailID, #(UINT64)邮件ID
		vecItemInfo #(SMailBaseAttachment的数组)附件
	)
		raise NotImplementedError
	end
	#接收：发送附件
	def onRecv_SendMailAttch(
		qwUsrID, #(UINT64)帐号ID
		qwMailID, #(UINT64)邮件ID
		vecItemInfo #(SMailBaseAttachment的数组)附件
	)
		raise NotImplementedError
	end
	#接收：修改签名
	def onRecv_SetSign(
		qwUsrID, #(UINT64)帐号ID
		strSign #(string)签名
	)
		raise NotImplementedError
	end
	#接收：修改表情
	def onRecv_SetMood(
		qwUsrID, #(UINT64)帐号ID
		wMood #(UINT16)表情
	)
		raise NotImplementedError
	end
	#接收：请求和他人发起战斗
	def onRecv_FigtherToOther(
		qwUsrID, #(UINT64)帐号ID
		qwOtherID, #(UINT64)他人的ID
		dwCost, #(UINT32)花费的游戏币
		eBattleType, #(枚类型：BattleGS::EBattleType)战斗类型
		dwBufferID, #(UINT32)临时增加的buffer
		dwSkillAttrID, #(UINT32)增加的属性
		dwCount #(UINT32)buffer叠加层数
	)
		raise NotImplementedError
	end
	#接收：询问可否放下掉落
	def onRecv_CanPushLoot(
		qwUsrID, #(UINT64)帐号ID
		dwLootId #(UINT32)掉落的ID
	)
		raise NotImplementedError
	end
	#接收：掉落到玩家包裹
	def onRecv_PushLoot(
		qwUsrID, #(UINT64)帐号ID
		eSource, #(枚举类型：EOpSource)原因
		eItemFrom, #(枚类型：LogDataDefine::ItemFrom)道具or资源来源类型
		dwLootId #(UINT32)掉落的ID
	)
		raise NotImplementedError
	end
	#接收：扣钱或物品
	def onRecv_ReduceItem(
		qwUsrID, #(UINT64)帐号ID
		eItemTo, #(枚类型：LogDataDefine::ItemTo)道具or资源消耗类型
		dwID, #(UINT32)钱或物品ID
		dwCount #(UINT32)数量
	)
		raise NotImplementedError
	end
	#接收：物品/资源数量是否够
	def onRecv_CanReduceItem(
		qwUsrID, #(UINT64)帐号ID
		dwItemID, #(UINT32)物品ID
		dwCount #(UINT32)数量
	)
		raise NotImplementedError
	end
	#接收：查询玩家属性
	def onRecv_GetUserUINTProp(
		qwUsrID, #(UINT64)帐号ID
		eUINTPropType #(枚举类型：EPlayerUINTProp)属性类型
	)
		raise NotImplementedError
	end
	#接收：设置玩家属性
	def onRecv_SetUserUINTProp(
		qwUsrID, #(UINT64)帐号ID
		eUINTPropType, #(枚举类型：EPlayerUINTProp)属性类型
		dwValue #(UINT32)属性值
	)
		raise NotImplementedError
	end
	#接收：扣除物品/钱币
	def onRecv_UserSubItem(
		qwUsrID, #(UINT64)帐号ID
		eItemTo, #(枚类型：LogDataDefine::ItemTo)道具or资源消耗类型
		vecUserItem #(SUserItem的数组)物品列表
	)
		raise NotImplementedError
	end
	#接收：添加物品/钱币
	def onRecv_UserAddItem(
		qwUsrID, #(UINT64)帐号ID
		eItemFrom, #(枚类型：LogDataDefine::ItemFrom)道具or资源来源类型
		vecUserItem #(SUserItem的数组)物品列表
	)
		raise NotImplementedError
	end
	#接收：转发系统消息
	def onRecv_SendSysMsg(
		qwUsrID, #(UINT64)帐号ID
		wMsgID #(UINT16)消息ID
	)
		raise NotImplementedError
	end
	#接收：任务事件通知
	def onRecv_ActionNotify(
		qwUsrID, #(UINT64)帐号ID
		wAction #(UINT16)通知类型
	)
		raise NotImplementedError
	end
	#接收：气泡事件通知
	def onRecv_BubbleNotify(
		qwUsrID, #(UINT64)帐号ID
		eType, #(枚类型：ProtoCommon::EDataChange)修改类型
		wMsgID, #(UINT16)通知类型
		vecParam, #(INT64数组)整型变量
		vecString #(string数组)字符串型变量
	)
		raise NotImplementedError
	end
	#接收：玩家帮派等级更新
	def onRecv_GuildLevelUpdated(
		qwRoleID, #(UINT64)玩家ID
		wLevel #(UINT16)帮派等级
	)
		raise NotImplementedError
	end
	#接收：玩家帮派名有更新
	def onRecv_GuildNameUpdated(
		qwRoleID, #(UINT64)玩家ID
		strGuildName #(string)帮派名称
	)
		raise NotImplementedError
	end
	#接收：帮派技能属性更新
	def onRecv_GuildTechUpdate(
		qwRoleID, #(UINT64)玩家唯一ID
		vecFtAttr, #(SFtAttrMod的数组)玩家的帮派技能属性
		vecGuildTech #(SGuildTechInfo的数组)玩家的帮派技能信息
	)
		raise NotImplementedError
	end
	#接收：重新加载表格
	def onRecv_ReloadTable(
		vecTableName #(string数组)表格名字
	)
		raise NotImplementedError
	end
	#接收：玩家九疑鼎属性更新
	def onRecv_TripodAttrUpdate(
		qwRoleID, #(UINT64)玩家唯一ID
		vecValue #(UINT32数组)九疑鼎ID、等级
	)
		raise NotImplementedError
	end
	#接收：完成GetCond条件
	def onRecv_ProcessCond(
		qwUsrID, #(UINT64)玩家ID
		wCondID, #(UINT16)条件ID
		eItemTo #(枚类型：LogDataDefine::ItemTo)道具or资源消耗类型
	)
		raise NotImplementedError
	end
	#接收：玩家升级九疑鼎
	def onRecv_UpgradeTripod(
		qwUsrID, #(UINT64)玩家ID
		byTripodID, #(UINT8)九疑鼎ID
		byLevel, #(UINT8)九疑鼎当前等级
		dwExp, #(UINT32)九疑鼎当前经验值
		byOneKey #(UINT8)是否一键
	)
		raise NotImplementedError
	end
	#接收：加速九疑鼎炼丹(道具入鼎)
	def onRecv_SpeedTripod(
		qwUsrID, #(UINT64)玩家ID
		dwCurSoul, #(UINT32)当前九疑鼎的火种元气值
		dwMaxSoul, #(UINT32)当前九疑鼎的火种最大元气值(配置)
		vecItems #(SItemCount的数组)入鼎道具列表
	)
		raise NotImplementedError
	end
	#接收：判断玩家是否拥有散仙
	def onRecv_CheckHasFighter(
		qwUsrID, #(UINT64)玩家ID
		wFighterID #(UINT16)散仙ID
	)
		raise NotImplementedError
	end
	#接收：获取战斗力
	def onRecv_GetBattlePoint(
		qwUsrID #(UINT64)玩家ID
	)
		raise NotImplementedError
	end
	#接收：玩家发事件中心消息
	def onRecv_OnPlayerEvent(
		qwUsrID, #(UINT64)玩家ID
		eEventType, #(枚类型：EventCenter::EventType)事件类型
		vecParam, #(INT32数组)事件参数
		strParam, #(string)事件参数
		bLog #(bool)事件参数
	)
		raise NotImplementedError
	end
	#接收：增加或者设置玩家GameVar数值
	def onRecv_AddORSetGameVar(
		qwUsrID, #(UINT64)玩家ID
		byType, #(UINT8)0增加 >0设置
		vecVars, #(UINT16数组)varID列表
		vecValues #(UINT64数组)var数值列表(必须与vecVars对应)
	)
		raise NotImplementedError
	end
	#接收：清除玩家GameVar
	def onRecv_DeleteGameVar(
		qwUsrID, #(UINT64)玩家ID
		vecVars #(UINT16数组)varID列表
	)
		raise NotImplementedError
	end
	#接收：增加商城限购活动
	def onRecv_AddMallDiscount(
		oDiscount #(类类型：MallProt::SDiscount)限购道具列表
	)
		raise NotImplementedError
	end
	#接收：清除商城限购活动
	def onRecv_ClearMallDiscount(
		byPos #(UINT8)限购道具栏位
	)
		raise NotImplementedError
	end
	#接收：扣除多个玩家钱币/物品
	def onRecv_SubPlayerMoney(
		vecUserID, #(UINT64数组)玩家ID
		vecUserItem #(SUserItem的数组)物品列表
	)
		raise NotImplementedError
	end
	#接收：设置玩家等级
	def onRecv_SetPlayerLevel(
		qwUsrID, #(UINT64)玩家ID
		wLevel #(UINT16)玩家等级
	)
		raise NotImplementedError
	end
	#接收：设置玩家VIP等级
	def onRecv_SetPlayerVIPLevel(
		qwUsrID, #(UINT64)玩家ID
		eOptType, #(枚类型：PHPProt::EOptType)台台操作类型(eOptSetPlayerVIPLevel/eOptAddGrowthValue)
		dwLevelOrGrowthValue #(UINT32)等级or成长值
	)
		raise NotImplementedError
	end
	#接收：设置日常任务
	def onRecv_SetDayTask(
		vecUserID, #(UINT64数组)玩家ID
		eTaskType #(枚类型：PHPProt::EPHPTaskType)日常任务类型
	)
		raise NotImplementedError
	end
	#接收：获取玩家信息
	def onRecv_GetPlayerInfo(
		qwUserID #(UINT64)玩家ID
	)
		raise NotImplementedError
	end
	#接收：获取玩家背包信息
	def onRecv_GetPlayerBagInfo(
		qwUserID #(UINT64)玩家ID
	)
		raise NotImplementedError
	end
	#接收：删除玩家物品
	def onRecv_DelPlayerItem(
		qwUserID, #(UINT64)用户ID
		byType, #(UINT8)1；背包，2：仓库
		qwInstID, #(UINT64)物品唯一ID
		wCount #(UINT16)堆叠数
	)
		raise NotImplementedError
	end
	#接收：给玩家用掉落包发系统邮件
	def onRecv_SendSysMailByLootId(
		qwUserID, #(UINT64)用户ID
		wTitle, #(UINT16)邮件标题
		wText, #(UINT16)邮件正文
		vecParam, #(string数组)邮件参数
		dwLootId, #(UINT32)掉落包
		dwRate #(UINT32)倍率
	)
		raise NotImplementedError
	end
	#接收：任务集市
	def onRecv_GetTaskStateForPlatfrom(
		qwUserID, #(UINT64)用户ID
		dwTaskID, #(UINT32)邮件标题
		byStep, #(UINT8)邮件正文
		byOpt #(UINT8)邮件正文
	)
		raise NotImplementedError
	end
	#接收：同步微信微博人数
	def onRecv_SynWeiweiPersonNum(
		qwUserID, #(UINT64)玩家ID
		byType, #(UINT8)类型
		dwCount #(UINT32)人数
	)
		raise NotImplementedError
	end
	#接收：检测CDK
	def onRecv_CheckCDK(
		qwUserID, #(UINT64)玩家ID
		strCDK #(string)CDK码
	)
		raise NotImplementedError
	end
	#接收：QQAlarm安装
	def onRecv_SynQQAlarm(
		qwUserID #(UINT64)玩家ID
	)
		raise NotImplementedError
	end
	#接收：运营修改宝箱信息
	def onRecv_ModifyChest(
		sChestInfo #(类类型：PHPProt::SChestInfo)信息
	)
		raise NotImplementedError
	end
	#接收：Center2Game活动时间同步
	def onRecv_SyncActivityTime(
		sActTime #(类类型：ProtoCommon::SActivityTime)信息
	)
		raise NotImplementedError
	end
	#接收：请求累计登入天数
	def onRecv_GetLoginDays(
		qwUserID #(UINT64)玩家ID
	)
		raise NotImplementedError
	end
	#接收：同步活动状态
	def onRecv_SyncActState(
		oInfo, #(类类型：SActivityState)数据
		bNotify #(bool)是否通知全服
	)
		raise NotImplementedError
	end
	#接收：添加Title
	def onRecv_SyncTitle(
		qwUserID, #(UINT64)玩家ID
		wTitleID #(UINT16)添加Title
	)
		raise NotImplementedError
	end
	#接收：扣除礼卷钻石
	def onRecv_SubGoldOrCoupon(
		qwUsrID, #(UINT64)帐号ID
		eItemTo, #(枚类型：LogDataDefine::ItemTo)道具or资源消耗类型
		dwCount #(UINT32)扣款数量
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：CenterServer状态请求
	def onReturn_GetCenterState(
		ret #0为成功，1为失败，2为超时
	)
	end

	#返回：是否为好友
	def onReturn_IsFriend(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_IsFriend)返回的参数
	)
	end

	#返回：是否在同一个帮派
	def onReturn_IsSameGuild(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_IsSameGuild)返回的参数
	)
	end

	#返回：获取帮派ID
	def onReturn_GetGuildID(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetGuildID)返回的参数
	)
	end

	#返回：获取帮派ID
	def onReturn_GetGuildName(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetGuildName)返回的参数
	)
	end

	#返回：扣除帮贡
	def onReturn_SubGuildContribution(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SubGuildContribution)返回的参数
	)
	end

	#返回：获取全局Var值
	def onReturn_GetSystemVar(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetSystemVar)返回的参数
	)
	end

	#返回：设置全局Var值
	def onReturn_SetSystemVar(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SetSystemVar)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：替换帐号
	def _doRecv_ReplaceUser(data)
		qwUsrID = ByteUtil::readUINT64(data)
		return onRecv_ReplaceUser(qwUsrID)
	end

	#接收处理：GM指令
	def _doRecv_GMCmd(data)
		qwUsrID = ByteUtil::readUINT64(data)
		strInfo = ByteUtil::readSTRING(data)
		return onRecv_GMCmd(qwUsrID, strInfo)
	end

	#接收处理：充值接口
	def _doRecv_AddTotalRecharge(data)
		oRecharge = SRecharge::fromStream(data)
		strUdp1 = ByteUtil::readSTRING(data)
		strUdp2 = ByteUtil::readSTRING(data)
		return onRecv_AddTotalRecharge(oRecharge, strUdp1, strUdp2)
	end

	#接收处理：充值接口(改版:加仙石礼包到邮件)
	def _doRecv_AddRechargeMailItem(data)
		oRecharge = SRecharge::fromStream(data)
		strUdp1 = ByteUtil::readSTRING(data)
		strUdp2 = ByteUtil::readSTRING(data)
		return onRecv_AddRechargeMailItem(oRecharge, strUdp1, strUdp2)
	end

	#接收处理：补偿玩家未创建预先充值的仙石
	def _doRecv_AddTotalPrepaid(data)
		qwUsrID = ByteUtil::readUINT64(data)
		dwGold = ByteUtil::readUINT32(data)
		return onRecv_AddTotalPrepaid(qwUsrID, dwGold)
	end

	#接收处理：Q点直购道具
	def _doRecv_AddQQCoinBuyItem(data)
		qwUsrID = ByteUtil::readUINT64(data)
		vecUserItem = SUserItem::vectorFromStream(data)
		return onRecv_AddQQCoinBuyItem(qwUsrID, vecUserItem)
	end

	#接收处理：询问可否提取附件
	def _doRecv_CheckMailAttch(data)
		qwUsrID = ByteUtil::readUINT64(data)
		qwMailID = ByteUtil::readUINT64(data)
		vecItemInfo = SMailBaseAttachment::superVectorFromStream(data)
		return onRecv_CheckMailAttch(qwUsrID, qwMailID, vecItemInfo)
	end

	#接收处理：发送附件
	def _doRecv_SendMailAttch(data)
		qwUsrID = ByteUtil::readUINT64(data)
		qwMailID = ByteUtil::readUINT64(data)
		vecItemInfo = SMailBaseAttachment::superVectorFromStream(data)
		return onRecv_SendMailAttch(qwUsrID, qwMailID, vecItemInfo)
	end

	#接收处理：修改签名
	def _doRecv_SetSign(data)
		qwUsrID = ByteUtil::readUINT64(data)
		strSign = ByteUtil::readSTRING(data)
		return onRecv_SetSign(qwUsrID, strSign)
	end

	#接收处理：修改表情
	def _doRecv_SetMood(data)
		qwUsrID = ByteUtil::readUINT64(data)
		wMood = ByteUtil::readUINT16(data)
		return onRecv_SetMood(qwUsrID, wMood)
	end

	#接收处理：请求和他人发起战斗
	def _doRecv_FigtherToOther(data)
		qwUsrID = ByteUtil::readUINT64(data)
		qwOtherID = ByteUtil::readUINT64(data)
		dwCost = ByteUtil::readUINT32(data)
		eBattleType = ByteUtil::readUINT8(data)
		dwBufferID = ByteUtil::readUINT32(data)
		dwSkillAttrID = ByteUtil::readUINT32(data)
		dwCount = ByteUtil::readUINT32(data)
		return onRecv_FigtherToOther(qwUsrID, qwOtherID, dwCost, eBattleType, dwBufferID, dwSkillAttrID, dwCount)
	end

	#接收处理：询问可否放下掉落
	def _doRecv_CanPushLoot(data)
		qwUsrID = ByteUtil::readUINT64(data)
		dwLootId = ByteUtil::readUINT32(data)
		return onRecv_CanPushLoot(qwUsrID, dwLootId)
	end

	#接收处理：掉落到玩家包裹
	def _doRecv_PushLoot(data)
		qwUsrID = ByteUtil::readUINT64(data)
		eSource = ByteUtil::readUINT8(data)
		eItemFrom = ByteUtil::readUINT16(data)
		dwLootId = ByteUtil::readUINT32(data)
		return onRecv_PushLoot(qwUsrID, eSource, eItemFrom, dwLootId)
	end

	#接收处理：扣钱或物品
	def _doRecv_ReduceItem(data)
		qwUsrID = ByteUtil::readUINT64(data)
		eItemTo = ByteUtil::readUINT16(data)
		dwID = ByteUtil::readUINT32(data)
		dwCount = ByteUtil::readUINT32(data)
		return onRecv_ReduceItem(qwUsrID, eItemTo, dwID, dwCount)
	end

	#接收处理：物品/资源数量是否够
	def _doRecv_CanReduceItem(data)
		qwUsrID = ByteUtil::readUINT64(data)
		dwItemID = ByteUtil::readUINT32(data)
		dwCount = ByteUtil::readUINT32(data)
		return onRecv_CanReduceItem(qwUsrID, dwItemID, dwCount)
	end

	#接收处理：查询玩家属性
	def _doRecv_GetUserUINTProp(data)
		qwUsrID = ByteUtil::readUINT64(data)
		eUINTPropType = ByteUtil::readUINT8(data)
		return onRecv_GetUserUINTProp(qwUsrID, eUINTPropType)
	end

	#接收处理：设置玩家属性
	def _doRecv_SetUserUINTProp(data)
		qwUsrID = ByteUtil::readUINT64(data)
		eUINTPropType = ByteUtil::readUINT8(data)
		dwValue = ByteUtil::readUINT32(data)
		return onRecv_SetUserUINTProp(qwUsrID, eUINTPropType, dwValue)
	end

	#接收处理：扣除物品/钱币
	def _doRecv_UserSubItem(data)
		qwUsrID = ByteUtil::readUINT64(data)
		eItemTo = ByteUtil::readUINT16(data)
		vecUserItem = SUserItem::vectorFromStream(data)
		return onRecv_UserSubItem(qwUsrID, eItemTo, vecUserItem)
	end

	#接收处理：添加物品/钱币
	def _doRecv_UserAddItem(data)
		qwUsrID = ByteUtil::readUINT64(data)
		eItemFrom = ByteUtil::readUINT16(data)
		vecUserItem = SUserItem::vectorFromStream(data)
		return onRecv_UserAddItem(qwUsrID, eItemFrom, vecUserItem)
	end

	#接收处理：转发系统消息
	def _doRecv_SendSysMsg(data)
		qwUsrID = ByteUtil::readUINT64(data)
		wMsgID = ByteUtil::readUINT16(data)
		return onRecv_SendSysMsg(qwUsrID, wMsgID)
	end

	#接收处理：任务事件通知
	def _doRecv_ActionNotify(data)
		qwUsrID = ByteUtil::readUINT64(data)
		wAction = ByteUtil::readUINT16(data)
		return onRecv_ActionNotify(qwUsrID, wAction)
	end

	#接收处理：气泡事件通知
	def _doRecv_BubbleNotify(data)
		qwUsrID = ByteUtil::readUINT64(data)
		eType = ByteUtil::readUINT8(data)
		wMsgID = ByteUtil::readUINT16(data)
		vecParam = ByteUtil::readVecINT64(data)
		vecString = ByteUtil::readVecSTRING(data)
		return onRecv_BubbleNotify(qwUsrID, eType, wMsgID, vecParam, vecString)
	end

	#接收处理：玩家帮派等级更新
	def _doRecv_GuildLevelUpdated(data)
		qwRoleID = ByteUtil::readUINT64(data)
		wLevel = ByteUtil::readUINT16(data)
		return onRecv_GuildLevelUpdated(qwRoleID, wLevel)
	end

	#接收处理：玩家帮派名有更新
	def _doRecv_GuildNameUpdated(data)
		qwRoleID = ByteUtil::readUINT64(data)
		strGuildName = ByteUtil::readSTRING(data)
		return onRecv_GuildNameUpdated(qwRoleID, strGuildName)
	end

	#接收处理：帮派技能属性更新
	def _doRecv_GuildTechUpdate(data)
		qwRoleID = ByteUtil::readUINT64(data)
		vecFtAttr = SFtAttrMod::vectorFromStream(data)
		vecGuildTech = SGuildTechInfo::vectorFromStream(data)
		return onRecv_GuildTechUpdate(qwRoleID, vecFtAttr, vecGuildTech)
	end

	#接收处理：重新加载表格
	def _doRecv_ReloadTable(data)
		vecTableName = ByteUtil::readVecSTRING(data)
		return onRecv_ReloadTable(vecTableName)
	end

	#接收处理：玩家九疑鼎属性更新
	def _doRecv_TripodAttrUpdate(data)
		qwRoleID = ByteUtil::readUINT64(data)
		vecValue = ByteUtil::readVecUINT32(data)
		return onRecv_TripodAttrUpdate(qwRoleID, vecValue)
	end

	#接收处理：完成GetCond条件
	def _doRecv_ProcessCond(data)
		qwUsrID = ByteUtil::readUINT64(data)
		wCondID = ByteUtil::readUINT16(data)
		eItemTo = ByteUtil::readUINT16(data)
		return onRecv_ProcessCond(qwUsrID, wCondID, eItemTo)
	end

	#接收处理：玩家升级九疑鼎
	def _doRecv_UpgradeTripod(data)
		qwUsrID = ByteUtil::readUINT64(data)
		byTripodID = ByteUtil::readUINT8(data)
		byLevel = ByteUtil::readUINT8(data)
		dwExp = ByteUtil::readUINT32(data)
		byOneKey = ByteUtil::readUINT8(data)
		return onRecv_UpgradeTripod(qwUsrID, byTripodID, byLevel, dwExp, byOneKey)
	end

	#接收处理：加速九疑鼎炼丹(道具入鼎)
	def _doRecv_SpeedTripod(data)
		qwUsrID = ByteUtil::readUINT64(data)
		dwCurSoul = ByteUtil::readUINT32(data)
		dwMaxSoul = ByteUtil::readUINT32(data)
		vecItems = SItemCount::vectorFromStream(data)
		return onRecv_SpeedTripod(qwUsrID, dwCurSoul, dwMaxSoul, vecItems)
	end

	#接收处理：判断玩家是否拥有散仙
	def _doRecv_CheckHasFighter(data)
		qwUsrID = ByteUtil::readUINT64(data)
		wFighterID = ByteUtil::readUINT16(data)
		return onRecv_CheckHasFighter(qwUsrID, wFighterID)
	end

	#接收处理：获取战斗力
	def _doRecv_GetBattlePoint(data)
		qwUsrID = ByteUtil::readUINT64(data)
		return onRecv_GetBattlePoint(qwUsrID)
	end

	#接收处理：玩家发事件中心消息
	def _doRecv_OnPlayerEvent(data)
		qwUsrID = ByteUtil::readUINT64(data)
		eEventType = ByteUtil::readUINT16(data)
		vecParam = ByteUtil::readVecINT32(data)
		strParam = ByteUtil::readSTRING(data)
		bLog = ByteUtil::readBOOL(data)
		return onRecv_OnPlayerEvent(qwUsrID, eEventType, vecParam, strParam, bLog)
	end

	#接收处理：增加或者设置玩家GameVar数值
	def _doRecv_AddORSetGameVar(data)
		qwUsrID = ByteUtil::readUINT64(data)
		byType = ByteUtil::readUINT8(data)
		vecVars = ByteUtil::readVecUINT16(data)
		vecValues = ByteUtil::readVecUINT64(data)
		return onRecv_AddORSetGameVar(qwUsrID, byType, vecVars, vecValues)
	end

	#接收处理：清除玩家GameVar
	def _doRecv_DeleteGameVar(data)
		qwUsrID = ByteUtil::readUINT64(data)
		vecVars = ByteUtil::readVecUINT16(data)
		return onRecv_DeleteGameVar(qwUsrID, vecVars)
	end

	#接收处理：增加商城限购活动
	def _doRecv_AddMallDiscount(data)
		oDiscount = SDiscount::fromStream(data)
		return onRecv_AddMallDiscount(oDiscount)
	end

	#接收处理：清除商城限购活动
	def _doRecv_ClearMallDiscount(data)
		byPos = ByteUtil::readUINT8(data)
		return onRecv_ClearMallDiscount(byPos)
	end

	#接收处理：扣除多个玩家钱币/物品
	def _doRecv_SubPlayerMoney(data)
		vecUserID = ByteUtil::readVecUINT64(data)
		vecUserItem = SUserItem::vectorFromStream(data)
		return onRecv_SubPlayerMoney(vecUserID, vecUserItem)
	end

	#接收处理：设置玩家等级
	def _doRecv_SetPlayerLevel(data)
		qwUsrID = ByteUtil::readUINT64(data)
		wLevel = ByteUtil::readUINT16(data)
		return onRecv_SetPlayerLevel(qwUsrID, wLevel)
	end

	#接收处理：设置玩家VIP等级
	def _doRecv_SetPlayerVIPLevel(data)
		qwUsrID = ByteUtil::readUINT64(data)
		eOptType = ByteUtil::readINT8(data)
		dwLevelOrGrowthValue = ByteUtil::readUINT32(data)
		return onRecv_SetPlayerVIPLevel(qwUsrID, eOptType, dwLevelOrGrowthValue)
	end

	#接收处理：设置日常任务
	def _doRecv_SetDayTask(data)
		vecUserID = ByteUtil::readVecUINT64(data)
		eTaskType = ByteUtil::readUINT8(data)
		return onRecv_SetDayTask(vecUserID, eTaskType)
	end

	#接收处理：获取玩家信息
	def _doRecv_GetPlayerInfo(data)
		qwUserID = ByteUtil::readUINT64(data)
		return onRecv_GetPlayerInfo(qwUserID)
	end

	#接收处理：获取玩家背包信息
	def _doRecv_GetPlayerBagInfo(data)
		qwUserID = ByteUtil::readUINT64(data)
		return onRecv_GetPlayerBagInfo(qwUserID)
	end

	#接收处理：删除玩家物品
	def _doRecv_DelPlayerItem(data)
		qwUserID = ByteUtil::readUINT64(data)
		byType = ByteUtil::readUINT8(data)
		qwInstID = ByteUtil::readUINT64(data)
		wCount = ByteUtil::readUINT16(data)
		return onRecv_DelPlayerItem(qwUserID, byType, qwInstID, wCount)
	end

	#接收处理：给玩家用掉落包发系统邮件
	def _doRecv_SendSysMailByLootId(data)
		qwUserID = ByteUtil::readUINT64(data)
		wTitle = ByteUtil::readUINT16(data)
		wText = ByteUtil::readUINT16(data)
		vecParam = ByteUtil::readVecSTRING(data)
		dwLootId = ByteUtil::readUINT32(data)
		dwRate = ByteUtil::readUINT32(data)
		return onRecv_SendSysMailByLootId(qwUserID, wTitle, wText, vecParam, dwLootId, dwRate)
	end

	#接收处理：任务集市
	def _doRecv_GetTaskStateForPlatfrom(data)
		qwUserID = ByteUtil::readUINT64(data)
		dwTaskID = ByteUtil::readUINT32(data)
		byStep = ByteUtil::readUINT8(data)
		byOpt = ByteUtil::readUINT8(data)
		return onRecv_GetTaskStateForPlatfrom(qwUserID, dwTaskID, byStep, byOpt)
	end

	#接收处理：同步微信微博人数
	def _doRecv_SynWeiweiPersonNum(data)
		qwUserID = ByteUtil::readUINT64(data)
		byType = ByteUtil::readUINT8(data)
		dwCount = ByteUtil::readUINT32(data)
		return onRecv_SynWeiweiPersonNum(qwUserID, byType, dwCount)
	end

	#接收处理：检测CDK
	def _doRecv_CheckCDK(data)
		qwUserID = ByteUtil::readUINT64(data)
		strCDK = ByteUtil::readSTRING(data)
		return onRecv_CheckCDK(qwUserID, strCDK)
	end

	#接收处理：QQAlarm安装
	def _doRecv_SynQQAlarm(data)
		qwUserID = ByteUtil::readUINT64(data)
		return onRecv_SynQQAlarm(qwUserID)
	end

	#接收处理：运营修改宝箱信息
	def _doRecv_ModifyChest(data)
		sChestInfo = SChestInfo::fromStream(data)
		return onRecv_ModifyChest(sChestInfo)
	end

	#接收处理：Center2Game活动时间同步
	def _doRecv_SyncActivityTime(data)
		sActTime = SActivityTime::fromStream(data)
		return onRecv_SyncActivityTime(sActTime)
	end

	#接收处理：请求累计登入天数
	def _doRecv_GetLoginDays(data)
		qwUserID = ByteUtil::readUINT64(data)
		return onRecv_GetLoginDays(qwUserID)
	end

	#接收处理：同步活动状态
	def _doRecv_SyncActState(data)
		oInfo = SActivityState::fromStream(data)
		bNotify = ByteUtil::readBOOL(data)
		return onRecv_SyncActState(oInfo, bNotify)
	end

	#接收处理：添加Title
	def _doRecv_SyncTitle(data)
		qwUserID = ByteUtil::readUINT64(data)
		wTitleID = ByteUtil::readUINT16(data)
		return onRecv_SyncTitle(qwUserID, wTitleID)
	end

	#接收处理：扣除礼卷钻石
	def _doRecv_SubGoldOrCoupon(data)
		qwUsrID = ByteUtil::readUINT64(data)
		eItemTo = ByteUtil::readUINT16(data)
		dwCount = ByteUtil::readUINT32(data)
		return onRecv_SubGoldOrCoupon(qwUsrID, eItemTo, dwCount)
	end

#以下为返回处理函数
	#返回处理：CenterServer状态请求
	def _doReturn_GetCenterState(data)
		retParam = SRetParam_GetCenterState.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetCenterState(ret)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：CenterServer状态请求
	def _onTimeOut_GetCenterState(sessionID)
		onReturn_GetCenterState(2)
	end

	#返回处理：是否为好友
	def _doReturn_IsFriend(data)
		retParam = SRetParam_IsFriend.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readUINT8(data) #(UINT8)0是好友 1非好友
		retParam.byRet = byRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_IsFriend(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：是否为好友
	def _onTimeOut_IsFriend(sessionID)
		retParam = SRetParam_IsFriend.new;
		onReturn_IsFriend(2, retParam)
	end

	#返回处理：是否在同一个帮派
	def _doReturn_IsSameGuild(data)
		retParam = SRetParam_IsSameGuild.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readUINT8(data) #(UINT8)0在同一个帮派 1不在同一个帮派
		retParam.byRet = byRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_IsSameGuild(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：是否在同一个帮派
	def _onTimeOut_IsSameGuild(sessionID)
		retParam = SRetParam_IsSameGuild.new;
		onReturn_IsSameGuild(2, retParam)
	end

	#返回处理：获取帮派ID
	def _doReturn_GetGuildID(data)
		retParam = SRetParam_GetGuildID.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		qwGuildID = ByteUtil::readUINT64(data) #(UINT64)帮派ID
		strGuildName = ByteUtil::readSTRING(data) #(string)帮派名称
		byGuildLvl = ByteUtil::readUINT8(data) #(UINT8)帮派等级
		strGuildOwnerName = ByteUtil::readSTRING(data) #(string)帮主名称
		retParam.qwGuildID = qwGuildID
		retParam.strGuildName = strGuildName
		retParam.byGuildLvl = byGuildLvl
		retParam.strGuildOwnerName = strGuildOwnerName
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetGuildID(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取帮派ID
	def _onTimeOut_GetGuildID(sessionID)
		retParam = SRetParam_GetGuildID.new;
		onReturn_GetGuildID(2, retParam)
	end

	#返回处理：获取帮派ID
	def _doReturn_GetGuildName(data)
		retParam = SRetParam_GetGuildName.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		bValid = ByteUtil::readBOOL(data) #(bool)是否已经找到
		qwGuildID = ByteUtil::readUINT64(data) #(UINT64)帮派ID
		strGuildName = ByteUtil::readSTRING(data) #(string)帮派名称
		byGuildLvl = ByteUtil::readUINT8(data) #(UINT8)帮派等级
		strGuildOwnerName = ByteUtil::readSTRING(data) #(string)帮主名称
		retParam.bValid = bValid
		retParam.qwGuildID = qwGuildID
		retParam.strGuildName = strGuildName
		retParam.byGuildLvl = byGuildLvl
		retParam.strGuildOwnerName = strGuildOwnerName
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetGuildName(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取帮派ID
	def _onTimeOut_GetGuildName(sessionID)
		retParam = SRetParam_GetGuildName.new;
		onReturn_GetGuildName(2, retParam)
	end

	#返回处理：扣除帮贡
	def _doReturn_SubGuildContribution(data)
		retParam = SRetParam_SubGuildContribution.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚类型：GuildProt::EGuildResult)检测结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SubGuildContribution(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：扣除帮贡
	def _onTimeOut_SubGuildContribution(sessionID)
		retParam = SRetParam_SubGuildContribution.new;
		onReturn_SubGuildContribution(2, retParam)
	end

	#返回处理：获取全局Var值
	def _doReturn_GetSystemVar(data)
		retParam = SRetParam_GetSystemVar.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecVars = ByteUtil::readVecUINT16(data) #(UINT16数组)varID列表
		vecValues = ByteUtil::readVecUINT64(data) #(UINT64数组)var数值列表(必须与vecVars对应)
		retParam.vecVars = vecVars
		retParam.vecValues = vecValues
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetSystemVar(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取全局Var值
	def _onTimeOut_GetSystemVar(sessionID)
		retParam = SRetParam_GetSystemVar.new;
		onReturn_GetSystemVar(2, retParam)
	end

	#返回处理：设置全局Var值
	def _doReturn_SetSystemVar(data)
		retParam = SRetParam_SetSystemVar.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecVarID = ByteUtil::readVecUINT16(data) #(UINT16数组)设置成功的varID列表(只是校验用)
		retParam.vecVarID = vecVarID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SetSystemVar(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：设置全局Var值
	def _onTimeOut_SetSystemVar(sessionID)
		retParam = SRetParam_SetSystemVar.new;
		onReturn_SetSystemVar(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 12;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_ReplaceUser' #FuncID: 1
		@recvFuncList[1] = '_doRecv_GMCmd' #FuncID: 2
		@recvFuncList[2] = '_doRecv_AddTotalRecharge' #FuncID: 3
		@recvFuncList[3] = '_doRecv_AddRechargeMailItem' #FuncID: 4
		@recvFuncList[4] = '_doRecv_AddTotalPrepaid' #FuncID: 5
		@recvFuncList[5] = '_doRecv_AddQQCoinBuyItem' #FuncID: 6
		@recvFuncList[6] = '_doRecv_CheckMailAttch' #FuncID: 7
		@recvFuncList[7] = '_doRecv_SendMailAttch' #FuncID: 8
		@recvFuncList[8] = '_doRecv_SetSign' #FuncID: 9
		@recvFuncList[9] = '_doRecv_SetMood' #FuncID: 10
		@recvFuncList[10] = '_doRecv_FigtherToOther' #FuncID: 11
		@recvFuncList[11] = '_doRecv_CanPushLoot' #FuncID: 12
		@recvFuncList[12] = '_doRecv_PushLoot' #FuncID: 13
		@recvFuncList[13] = '_doRecv_ReduceItem' #FuncID: 14
		@recvFuncList[14] = '_doRecv_CanReduceItem' #FuncID: 15
		@recvFuncList[15] = '_doRecv_GetUserUINTProp' #FuncID: 16
		@recvFuncList[16] = '_doRecv_SetUserUINTProp' #FuncID: 17
		@recvFuncList[17] = '_doRecv_UserSubItem' #FuncID: 18
		@recvFuncList[18] = '_doRecv_UserAddItem' #FuncID: 19
		@recvFuncList[19] = '_doRecv_SendSysMsg' #FuncID: 20
		@recvFuncList[20] = '_doRecv_ActionNotify' #FuncID: 21
		@recvFuncList[21] = '_doRecv_BubbleNotify' #FuncID: 22
		@recvFuncList[22] = '_doRecv_GuildLevelUpdated' #FuncID: 23
		@recvFuncList[23] = '_doRecv_GuildNameUpdated' #FuncID: 24
		@recvFuncList[24] = '_doRecv_GuildTechUpdate' #FuncID: 25
		@recvFuncList[25] = '_doRecv_ReloadTable' #FuncID: 26
		@recvFuncList[26] = '_doRecv_TripodAttrUpdate' #FuncID: 27
		@recvFuncList[27] = '_doRecv_ProcessCond' #FuncID: 28
		@recvFuncList[28] = '_doRecv_UpgradeTripod' #FuncID: 29
		@recvFuncList[29] = '_doRecv_SpeedTripod' #FuncID: 30
		@recvFuncList[30] = '_doRecv_CheckHasFighter' #FuncID: 31
		@recvFuncList[31] = '_doRecv_GetBattlePoint' #FuncID: 32
		@recvFuncList[32] = '_doRecv_OnPlayerEvent' #FuncID: 33
		@recvFuncList[33] = '_doRecv_AddORSetGameVar' #FuncID: 34
		@recvFuncList[34] = '_doRecv_DeleteGameVar' #FuncID: 35
		@recvFuncList[35] = '_doRecv_AddMallDiscount' #FuncID: 36
		@recvFuncList[36] = '_doRecv_ClearMallDiscount' #FuncID: 37
		@recvFuncList[37] = '_doRecv_SubPlayerMoney' #FuncID: 38
		@recvFuncList[38] = '_doRecv_SetPlayerLevel' #FuncID: 39
		@recvFuncList[39] = '_doRecv_SetPlayerVIPLevel' #FuncID: 40
		@recvFuncList[40] = '_doRecv_SetDayTask' #FuncID: 41
		@recvFuncList[41] = '_doRecv_GetPlayerInfo' #FuncID: 42
		@recvFuncList[42] = '_doRecv_GetPlayerBagInfo' #FuncID: 43
		@recvFuncList[43] = '_doRecv_DelPlayerItem' #FuncID: 44
		@recvFuncList[44] = '_doRecv_SendSysMailByLootId' #FuncID: 45
		@recvFuncList[45] = '_doRecv_GetTaskStateForPlatfrom' #FuncID: 46
		@recvFuncList[46] = '_doRecv_SynWeiweiPersonNum' #FuncID: 47
		@recvFuncList[47] = '_doRecv_CheckCDK' #FuncID: 48
		@recvFuncList[48] = '_doRecv_SynQQAlarm' #FuncID: 49
		@recvFuncList[49] = '_doRecv_ModifyChest' #FuncID: 50
		@recvFuncList[50] = '_doRecv_SyncActivityTime' #FuncID: 51
		@recvFuncList[51] = '_doRecv_GetLoginDays' #FuncID: 52
		@recvFuncList[52] = '_doRecv_SyncActState' #FuncID: 53
		@recvFuncList[53] = '_doRecv_SyncTitle' #FuncID: 54
		@recvFuncList[54] = '_doRecv_SubGoldOrCoupon' #FuncID: 55

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetCenterState' #FuncID: 1
		@retFuncList[1] = '_doReturn_IsFriend' #FuncID: 2
		@retFuncList[2] = '_doReturn_IsSameGuild' #FuncID: 3
		@retFuncList[3] = '_doReturn_GetGuildID' #FuncID: 4
		@retFuncList[4] = '_doReturn_GetGuildName' #FuncID: 5
		@retFuncList[5] = '_doReturn_SubGuildContribution' #FuncID: 6
		@retFuncList[6] = '_doReturn_GetSystemVar' #FuncID: 7
		@retFuncList[7] = '_doReturn_SetSystemVar' #FuncID: 8

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetCenterState' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_IsFriend' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_IsSameGuild' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_GetGuildID' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_GetGuildName' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_SubGuildContribution' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_GetSystemVar' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_SetSystemVar' #FuncID: 8
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

