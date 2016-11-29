#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    DemonTowerGS.rb
#  Purpose:      锁妖塔
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#镇妖塔
class EDemonTower
	EDEMONTOWER_SUCESS = 0#成功
	EDEMONTOWER_ERROR = 1#锁妖塔错误码
	EDEMONTOWER_NOTPASS = 2#未通关层数，不能进入
	EDEMONTOWER_NOTINTOWER = 3#不在镇妖塔中
	EDEMONTOWER_INVALID_CFG = 4#配置不存在
	EDEMONTOWER_INVALID_FLOORID = 5#层数错误
	EDEMONTOWER_INVALID_POSITOIN = 6#镇守位置错误
	EDEMONTOWER_NOT_EMPTY_POSITOIN = 7#非空镇守位置
	EDEMONTOWER_EMPTY_POSITOIN = 8#空位置没有玩家镇守
	EDEMONTOWER_EMPTY_PRIZE = 9#无奖励或奖励已经领取
	EDEMONTOWER_INVALID_PRIZETYPE = 10#错误的领奖类型
	EDEMONTOWER_INVALID_USERID = 11#玩家不在线
	EDEMONTOWER_FIGHTCD = 12#镇守位处在战斗状态中
	EDEMONTOWER_LACKMONEY = 13#钻石不足
end

#数据更新类型
class EDemonTowerDB
	EDEMONTOWERDB_ADD = 1#添加
	EDEMONTOWERDB_UPDATE = 2#更新
	EDEMONTOWERDB_DELETE = 3#删除
end

#领取奖励
class EDemonTowerPrize
	EDEMONTOWER_PRIZE_FAIL = 1#镇守失败奖励
	EDEMONTOWER_PRIZE_DAY = 2#镇守1天收益奖励
	EDEMONTOWER_PRIZE_SEAL = 3#封印每天奖励(改成gmeserver领取)
end

#钱币列表
class MoneyInfo
	attr_accessor:dwMoneyType #(UINT32)钱币类型
	attr_accessor:dwMoneyValue #(UINT32)钱数

	#构造函数
	def initialize
		@dwMoneyType = 0
		@dwMoneyValue = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwMoneyType = @dwMoneyType
		obj.dwMoneyValue = @dwMoneyValue
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = MoneyInfo.new
		s.dwMoneyType = ByteUtil::readUINT32(data)
		s.dwMoneyValue = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = MoneyInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwMoneyType)
		ByteUtil::writeUINT32(data, @dwMoneyValue)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#镇守层的玩家信息
class SDemonFloorPlayer
	attr_accessor:dwFloorID #(UINT32)当前所在塔层
	attr_accessor:qwUserID #(UINT64)uid
	attr_accessor:strRoleName #(string)角色名
	attr_accessor:bySex #(UINT8)性别
	attr_accessor:byLevel #(UINT16)等级
	attr_accessor:dwPower #(UINT32)战斗力
	attr_accessor:dwGuardStartTime #(UINT32)镇守开始时间
	attr_accessor:dwGuardReduceRate #(UINT32)减弱比例(百分比1为%1)
	attr_accessor:vecSoulPrize #(MoneyInfo的数组)当前获得魄奖励

	#构造函数
	def initialize
		@dwFloorID = 0
		@qwUserID = 0
		@strRoleName = ''
		@bySex = 0
		@byLevel = 0
		@dwPower = 0
		@dwGuardStartTime = 0
		@dwGuardReduceRate = 0
		@vecSoulPrize = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwFloorID = @dwFloorID
		obj.qwUserID = @qwUserID
		obj.strRoleName = @strRoleName
		obj.bySex = @bySex
		obj.byLevel = @byLevel
		obj.dwPower = @dwPower
		obj.dwGuardStartTime = @dwGuardStartTime
		obj.dwGuardReduceRate = @dwGuardReduceRate
		obj.vecSoulPrize = @vecSoulPrize
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDemonFloorPlayer.new
		s.dwFloorID = ByteUtil::readUINT32(data)
		s.qwUserID = ByteUtil::readUINT64(data)
		s.strRoleName = ByteUtil::readSTRING(data)
		s.bySex = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT16(data)
		s.dwPower = ByteUtil::readUINT32(data)
		s.dwGuardStartTime = ByteUtil::readUINT32(data)
		s.dwGuardReduceRate = ByteUtil::readUINT32(data)
		s.vecSoulPrize = MoneyInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDemonFloorPlayer::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwFloorID)
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeSTRING(data, @strRoleName)
		ByteUtil::writeUINT8(data, @bySex)
		ByteUtil::writeUINT16(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwPower)
		ByteUtil::writeUINT32(data, @dwGuardStartTime)
		ByteUtil::writeUINT32(data, @dwGuardReduceRate)
		MoneyInfo::vectorToStream(data, @vecSoulPrize)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#镇守榜分页信息
class SDemonFloorPage
	attr_accessor:wCurPage #(UINT16)当前页码
	attr_accessor:wMaxPage #(UINT16)最大页码
	attr_accessor:vecDemonFloorPlayer #(SDemonFloorPlayer的数组)分页信息

	#构造函数
	def initialize
		@wCurPage = 0
		@wMaxPage = 0
		@vecDemonFloorPlayer = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wCurPage = @wCurPage
		obj.wMaxPage = @wMaxPage
		obj.vecDemonFloorPlayer = @vecDemonFloorPlayer
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDemonFloorPage.new
		s.wCurPage = ByteUtil::readUINT16(data)
		s.wMaxPage = ByteUtil::readUINT16(data)
		s.vecDemonFloorPlayer = SDemonFloorPlayer::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDemonFloorPage::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wCurPage)
		ByteUtil::writeUINT16(data, @wMaxPage)
		SDemonFloorPlayer::vectorToStream(data, @vecDemonFloorPlayer)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#镇守的玩家信息列表
class SDemonTowerPlayer
	attr_accessor:qwUserID #(UINT64)uid
	attr_accessor:qwRoleID #(UINT64)角色id
	attr_accessor:strRoleName #(string)角色名
	attr_accessor:bySex #(UINT8)性别
	attr_accessor:byLevel #(UINT16)等级
	attr_accessor:dwFloorID #(UINT32)当前所在塔层
	attr_accessor:dwGuardFloorID #(UINT32)镇守塔层
	attr_accessor:dwGuardPos #(UINT32)镇守位置
	attr_accessor:dwGuardStartTime #(UINT32)镇守开始时间
	attr_accessor:dwGuardEndTime #(UINT32)镇守结束时间
	attr_accessor:dwGuardNextPrizeTime #(UINT32)下次奖励时间
	attr_accessor:dwGuardNextReduceRateTime #(UINT32)下次减弱时间
	attr_accessor:dwGuardGatherSpeed #(UINT32)聚魂速度
	attr_accessor:dwGuardGatherSpeedEndTimer #(UINT32)加速时间
	attr_accessor:dwGuardReduceRate #(UINT32)元神灵力(百分比1为1%)
	attr_accessor:dwGuardNextAttackTime #(UINT32)镇守可以攻击的时间
	attr_accessor:dwPower #(UINT32)战斗力
	attr_accessor:dwBuyTime #(UINT32)购买cd(服务器用)
	attr_accessor:vecGatherSoulPrize #(MoneyInfo的数组)当前聚集的魄奖励
	attr_accessor:vecFailSoulPrize #(MoneyInfo的数组)失败后的魄奖励
	attr_accessor:vecDaySoulPrize #(MoneyInfo的数组)7点结算的魄奖励
	attr_accessor:dwTotalTime #(UINT32)镇守时间(服务器用)
	attr_accessor:dwFailFloorID #(UINT32)失败镇守塔层
	attr_accessor:dwFailPos #(UINT32)失败镇守位置
	attr_accessor:byColor #(UINT8)角色颜色

	#构造函数
	def initialize
		@qwUserID = 0
		@qwRoleID = 0
		@strRoleName = ''
		@bySex = 0
		@byLevel = 0
		@dwFloorID = 0
		@dwGuardFloorID = 0
		@dwGuardPos = 0
		@dwGuardStartTime = 0
		@dwGuardEndTime = 0
		@dwGuardNextPrizeTime = 0
		@dwGuardNextReduceRateTime = 0
		@dwGuardGatherSpeed = 0
		@dwGuardGatherSpeedEndTimer = 0
		@dwGuardReduceRate = 0
		@dwGuardNextAttackTime = 0
		@dwPower = 0
		@dwBuyTime = 0
		@vecGatherSoulPrize = Array.new
		@vecFailSoulPrize = Array.new
		@vecDaySoulPrize = Array.new
		@dwTotalTime = 0
		@dwFailFloorID = 0
		@dwFailPos = 0
		@byColor = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwUserID = @qwUserID
		obj.qwRoleID = @qwRoleID
		obj.strRoleName = @strRoleName
		obj.bySex = @bySex
		obj.byLevel = @byLevel
		obj.dwFloorID = @dwFloorID
		obj.dwGuardFloorID = @dwGuardFloorID
		obj.dwGuardPos = @dwGuardPos
		obj.dwGuardStartTime = @dwGuardStartTime
		obj.dwGuardEndTime = @dwGuardEndTime
		obj.dwGuardNextPrizeTime = @dwGuardNextPrizeTime
		obj.dwGuardNextReduceRateTime = @dwGuardNextReduceRateTime
		obj.dwGuardGatherSpeed = @dwGuardGatherSpeed
		obj.dwGuardGatherSpeedEndTimer = @dwGuardGatherSpeedEndTimer
		obj.dwGuardReduceRate = @dwGuardReduceRate
		obj.dwGuardNextAttackTime = @dwGuardNextAttackTime
		obj.dwPower = @dwPower
		obj.dwBuyTime = @dwBuyTime
		obj.vecGatherSoulPrize = @vecGatherSoulPrize
		obj.vecFailSoulPrize = @vecFailSoulPrize
		obj.vecDaySoulPrize = @vecDaySoulPrize
		obj.dwTotalTime = @dwTotalTime
		obj.dwFailFloorID = @dwFailFloorID
		obj.dwFailPos = @dwFailPos
		obj.byColor = @byColor
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDemonTowerPlayer.new
		s.qwUserID = ByteUtil::readUINT64(data)
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.strRoleName = ByteUtil::readSTRING(data)
		s.bySex = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT16(data)
		s.dwFloorID = ByteUtil::readUINT32(data)
		s.dwGuardFloorID = ByteUtil::readUINT32(data)
		s.dwGuardPos = ByteUtil::readUINT32(data)
		s.dwGuardStartTime = ByteUtil::readUINT32(data)
		s.dwGuardEndTime = ByteUtil::readUINT32(data)
		s.dwGuardNextPrizeTime = ByteUtil::readUINT32(data)
		s.dwGuardNextReduceRateTime = ByteUtil::readUINT32(data)
		s.dwGuardGatherSpeed = ByteUtil::readUINT32(data)
		s.dwGuardGatherSpeedEndTimer = ByteUtil::readUINT32(data)
		s.dwGuardReduceRate = ByteUtil::readUINT32(data)
		s.dwGuardNextAttackTime = ByteUtil::readUINT32(data)
		s.dwPower = ByteUtil::readUINT32(data)
		s.dwBuyTime = ByteUtil::readUINT32(data)
		s.vecGatherSoulPrize = MoneyInfo::vectorFromStream(data)
		s.vecFailSoulPrize = MoneyInfo::vectorFromStream(data)
		s.vecDaySoulPrize = MoneyInfo::vectorFromStream(data)
		s.dwTotalTime = ByteUtil::readUINT32(data)
		s.dwFailFloorID = ByteUtil::readUINT32(data)
		s.dwFailPos = ByteUtil::readUINT32(data)
		s.byColor = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDemonTowerPlayer::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeSTRING(data, @strRoleName)
		ByteUtil::writeUINT8(data, @bySex)
		ByteUtil::writeUINT16(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwFloorID)
		ByteUtil::writeUINT32(data, @dwGuardFloorID)
		ByteUtil::writeUINT32(data, @dwGuardPos)
		ByteUtil::writeUINT32(data, @dwGuardStartTime)
		ByteUtil::writeUINT32(data, @dwGuardEndTime)
		ByteUtil::writeUINT32(data, @dwGuardNextPrizeTime)
		ByteUtil::writeUINT32(data, @dwGuardNextReduceRateTime)
		ByteUtil::writeUINT32(data, @dwGuardGatherSpeed)
		ByteUtil::writeUINT32(data, @dwGuardGatherSpeedEndTimer)
		ByteUtil::writeUINT32(data, @dwGuardReduceRate)
		ByteUtil::writeUINT32(data, @dwGuardNextAttackTime)
		ByteUtil::writeUINT32(data, @dwPower)
		ByteUtil::writeUINT32(data, @dwBuyTime)
		MoneyInfo::vectorToStream(data, @vecGatherSoulPrize)
		MoneyInfo::vectorToStream(data, @vecFailSoulPrize)
		MoneyInfo::vectorToStream(data, @vecDaySoulPrize)
		ByteUtil::writeUINT32(data, @dwTotalTime)
		ByteUtil::writeUINT32(data, @dwFailFloorID)
		ByteUtil::writeUINT32(data, @dwFailPos)
		ByteUtil::writeUINT8(data, @byColor)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#镇守的玩家信息列表
class GuardInfo
	attr_accessor:qwUserID #(UINT64)uid
	attr_accessor:qwRoleID #(UINT64)角色id
	attr_accessor:dwGuardPos #(UINT32)封印位置
	attr_accessor:dwLastFightCD #(UINT32)战斗cd 1s
	attr_accessor:oDemonFloorPlayer #(类类型：SDemonFloorPlayer)玩家信息

	#构造函数
	def initialize
		@qwUserID = 0
		@qwRoleID = 0
		@dwGuardPos = 0
		@dwLastFightCD = 0
		@oDemonFloorPlayer = SDemonFloorPlayer.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwUserID = @qwUserID
		obj.qwRoleID = @qwRoleID
		obj.dwGuardPos = @dwGuardPos
		obj.dwLastFightCD = @dwLastFightCD
		obj.oDemonFloorPlayer = @oDemonFloorPlayer
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = GuardInfo.new
		s.qwUserID = ByteUtil::readUINT64(data)
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.dwGuardPos = ByteUtil::readUINT32(data)
		s.dwLastFightCD = ByteUtil::readUINT32(data)
		s.oDemonFloorPlayer = SDemonFloorPlayer::fromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = GuardInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT32(data, @dwGuardPos)
		ByteUtil::writeUINT32(data, @dwLastFightCD)
		@oDemonFloorPlayer.toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#通关信息
class SDemonTowerKillMonster
	attr_accessor:qwUserID #(UINT64)账号id
	attr_accessor:strName #(string)名字
	attr_accessor:byColor #(UINT8)角色颜色
	attr_accessor:bySex #(UINT8)性别
	attr_accessor:byCareer #(UINT8)职业
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:dwRounds #(UINT32)通关回合数
	attr_accessor:dwBattlePoint #(UINT32)战斗力
	attr_accessor:qwReportID #(UINT64)战报

	#构造函数
	def initialize
		@qwUserID = 0
		@strName = ''
		@byColor = 0
		@bySex = 0
		@byCareer = 0
		@byLevel = 0
		@dwRounds = 0
		@dwBattlePoint = 0
		@qwReportID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwUserID = @qwUserID
		obj.strName = @strName
		obj.byColor = @byColor
		obj.bySex = @bySex
		obj.byCareer = @byCareer
		obj.byLevel = @byLevel
		obj.dwRounds = @dwRounds
		obj.dwBattlePoint = @dwBattlePoint
		obj.qwReportID = @qwReportID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDemonTowerKillMonster.new
		s.qwUserID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.byColor = ByteUtil::readUINT8(data)
		s.bySex = ByteUtil::readUINT8(data)
		s.byCareer = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.dwRounds = ByteUtil::readUINT32(data)
		s.dwBattlePoint = ByteUtil::readUINT32(data)
		s.qwReportID = ByteUtil::readUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDemonTowerKillMonster::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @byColor)
		ByteUtil::writeUINT8(data, @bySex)
		ByteUtil::writeUINT8(data, @byCareer)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwRounds)
		ByteUtil::writeUINT32(data, @dwBattlePoint)
		ByteUtil::writeUINT64(data, @qwReportID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[EnterDemonTower:进入锁妖塔]的返回的参数组成的结构体
class SRetParam_EnterDemonTower
	attr_accessor:dwRet#(UINT32)结果 0成功其他错误码

	#构造函数
	def initialize
		@dwRet = 0
	end
end

#函数[LeaveDemonTower:离开锁妖塔]的返回的参数组成的结构体
class SRetParam_LeaveDemonTower
	attr_accessor:dwRet#(UINT32)结果 0成功其他错误码

	#构造函数
	def initialize
		@dwRet = 0
	end
end

#函数[SealMonster:封印怪物(挑战?)]的返回的参数组成的结构体
class SRetParam_SealMonster
	attr_accessor:dwRet#(UINT32)结果 0成功其他错误码

	#构造函数
	def initialize
		@dwRet = 0
	end
end

#函数[GuardAtk:镇守锁妖塔]的返回的参数组成的结构体
class SRetParam_GuardAtk
	attr_accessor:dwRet#(UINT32)结果 0成功其他错误码

	#构造函数
	def initialize
		@dwRet = 0
	end
end

#函数[AtkPlayer:抢夺镇守位置]的返回的参数组成的结构体
class SRetParam_AtkPlayer
	attr_accessor:dwRet#(UINT32)结果 0成功其他错误码

	#构造函数
	def initialize
		@dwRet = 0
	end
end

#函数[TakePrize:领取奖励]的返回的参数组成的结构体
class SRetParam_TakePrize
	attr_accessor:dwRet#(UINT32)结果 0成功其他错误码

	#构造函数
	def initialize
		@dwRet = 0
	end
end

#函数[GetTopList:获取镇守榜]的返回的参数组成的结构体
class SRetParam_GetTopList
	attr_accessor:oDemonFloorPage#(类类型：SDemonFloorPage)分页信息

	#构造函数
	def initialize
		@oDemonFloorPage = SDemonFloorPage.new
	end
end

#函数[GetDemonTowerInfo:获取本人镇妖塔相关信息]的返回的参数组成的结构体
class SRetParam_GetDemonTowerInfo
	attr_accessor:dwRet#(UINT32)结果 0成功 1-失败（非错误，没有进过镇妖塔）
	attr_accessor:oDemonTowerPlayer#(类类型：SDemonTowerPlayer)玩家镇守信息

	#构造函数
	def initialize
		@dwRet = 0
		@oDemonTowerPlayer = SDemonTowerPlayer.new
	end
end

#函数[GetGuardInfo:获取镇守信息信息]的返回的参数组成的结构体
class SRetParam_GetGuardInfo
	attr_accessor:vecGuardInfo#(GuardInfo的数组)镇守信息信息

	#构造函数
	def initialize
		@vecGuardInfo = Array.new
	end
end

#函数[GetPlayerInfo:获取玩家镇守信息]的返回的参数组成的结构体
class SRetParam_GetPlayerInfo
	attr_accessor:bRet#(UINT8)0 成功 1玩家不存在
	attr_accessor:oDemonFloorPlayer#(类类型：SDemonFloorPlayer)玩家镇守信息

	#构造函数
	def initialize
		@bRet = 0
		@oDemonFloorPlayer = SDemonFloorPlayer.new
	end
end

#函数[ClearFightCd:清除pvp战斗cd]的返回的参数组成的结构体
class SRetParam_ClearFightCd
	attr_accessor:bRet#(UINT8)0成功 其他失败

	#构造函数
	def initialize
		@bRet = 0
	end
end

#函数[GetPassInfo:获取过关信息]的返回的参数组成的结构体
class SRetParam_GetPassInfo
	attr_accessor:vecMinRound#(SDemonTowerKillMonster的数组)最快通关
	attr_accessor:vecMinBattlePoint#(SDemonTowerKillMonster的数组)最小战斗力通关

	#构造函数
	def initialize
		@vecMinRound = Array.new
		@vecMinBattlePoint = Array.new
	end
end

#协议类：锁妖塔
class DemonTowerGSBase < ProtocolBase
	#以下为发送函数
	#发送：进入锁妖塔
	def send_EnterDemonTower(
		dwFloorID #(UINT32)层数
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwFloorID)
		return @svrHandler.sendPacket(data)
	end

	#发送：离开锁妖塔
	def send_LeaveDemonTower(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：封印怪物(挑战?)
	def send_SealMonster(
		dwFloorID #(UINT32)层数
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwFloorID)
		return @svrHandler.sendPacket(data)
	end

	#发送：镇守锁妖塔
	def send_GuardAtk(
		dwFloorID,  #(UINT32)层数 0表示放弃镇守位置
		dwGuardPos #(UINT32)镇守位置
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwFloorID)
		ByteUtil::writeUINT32(data, dwGuardPos)
		return @svrHandler.sendPacket(data)
	end

	#发送：抢夺镇守位置
	def send_AtkPlayer(
		dwFloorID,  #(UINT32)层数
		dwGuardPos #(UINT32)镇守位置
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwFloorID)
		ByteUtil::writeUINT32(data, dwGuardPos)
		return @svrHandler.sendPacket(data)
	end

	#发送：领取奖励
	def send_TakePrize(
		ePrizeType #(枚举类型：EDemonTowerPrize)奖励类型
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, ePrizeType)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取镇守榜
	def send_GetTopList(
		wPage,  #(UINT16)页码 1开始
		wPageItemCount #(UINT16)每页显示数目 默认5
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wPage)
		ByteUtil::writeUINT16(data, wPageItemCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取本人镇妖塔相关信息
	def send_GetDemonTowerInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取镇守信息信息
	def send_GetGuardInfo(
		dwFloorID #(UINT32)镇守层
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwFloorID)
		return @svrHandler.sendPacket(data)
	end

	#发送：恢复元神
	def send_Restore(
		dwCount #(UINT32)物品数量
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, dwCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：增加聚魂速度
	def send_AddSpeed(
		dwCount #(UINT32)物品数量
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, dwCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取玩家镇守信息
	def send_GetPlayerInfo(
		qwUserID #(UINT64)账号ID
	)
		sessionID = @sessionMgr.getNewSession(self, 10);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwUserID)
		return @svrHandler.sendPacket(data)
	end

	#发送：清除pvp战斗cd
	def send_ClearFightCd(
	)
		sessionID = @sessionMgr.getNewSession(self, 11);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 13
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取过关信息
	def send_GetPassInfo(
		wFloorID #(UINT16)通关层
	)
		sessionID = @sessionMgr.getNewSession(self, 12);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 14
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wFloorID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：锁妖塔镇守信息
	def onRecv_GuardInfoNotify(
		dwFloorID, #(UINT32)层数
		vecGuardInfo #(GuardInfo的数组)镇守玩家信息
	)
		raise NotImplementedError
	end
	#接收：锁妖塔镇守信息更新
	def onRecv_GuardInfoChangeNotify(
		dwFloorID, #(UINT32)层数
		dwPos, #(UINT32)镇守玩家信息
		qwUserID, #(UINT64)玩家ID 0 表示该位置放弃镇守
		oGuardInfo #(类类型：GuardInfo)镇守信息
	)
		raise NotImplementedError
	end
	#接收：锁妖塔过关通知
	def onRecv_PassDemonTowerNotify(
		dwFloorID #(UINT32)锁妖塔过关层数
	)
		raise NotImplementedError
	end
	#接收：锁妖塔镇守攻击cd
	def onRecv_DemonTowerAtkCDNotify(
		dwGuardNextAttackTime #(UINT32)锁妖塔可攻击最早时间
	)
		raise NotImplementedError
	end
	#接收：镇妖塔玩家信息
	def onRecv_DemonTowerPlayerNotify(
		oDemonTowerPlayerInfo #(类类型：SDemonTowerPlayer)镇妖塔玩家信息
	)
		raise NotImplementedError
	end
	#接收：镇妖塔错误信息
	def onRecv_DemonTowerErrorNotify(
		dwError #(UINT32)错误码
	)
		raise NotImplementedError
	end
	#接收：镇守锁妖塔通知
	def onRecv_GuardSucessNotify(
		dwFloorID, #(UINT32)层数
		dwGuardPos #(UINT32)镇守位置
	)
		raise NotImplementedError
	end
	#接收：19点重置奖励通知
	def onRecv_DemonTowerResetNotify(
		dwFloorID, #(UINT32)层数
		dwGuardPos, #(UINT32)镇守位置
		vecSoulPrize #(MoneyInfo的数组)获得的魄奖励
	)
		raise NotImplementedError
	end
	#接收：镇妖塔被抢通知
	def onRecv_DemonTowerBeAttackNotify(
		dwFloorID, #(UINT32)层数
		dwPos, #(UINT32)位置
		qwAtkUserID, #(UINT64)抢夺人的Id
		strRole, #(string)抢夺人的名字
		vecFailSoulPrize #(MoneyInfo的数组)失败后的魄奖励
	)
		raise NotImplementedError
	end
	#接收：玩家切层通知
	def onRecv_EnterDemonTowerNotify(
		dwCurFloorID #(UINT32)当前进入的层数
	)
		raise NotImplementedError
	end
	#接收：镇妖塔分身崩溃通知
	def onRecv_PrizeNotify(
		eDemonTowerPrize, #(枚举类型：EDemonTowerPrize)魄奖励类型
		dwFloorID, #(UINT32)层数
		dwGuardPos, #(UINT32)镇守位置
		vecPrize #(MoneyInfo的数组)魄奖励
	)
		raise NotImplementedError
	end
	#接收：过关信息
	def onRecv_PassInfoNotify(
		wFloorID, #(UINT16)通关层
		vecMinRound, #(SDemonTowerKillMonster的数组)最快通关
		vecMinBattlePoint #(SDemonTowerKillMonster的数组)最小战斗力通关
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：进入锁妖塔
	def onReturn_EnterDemonTower(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_EnterDemonTower)返回的参数
	)
	end

	#返回：离开锁妖塔
	def onReturn_LeaveDemonTower(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LeaveDemonTower)返回的参数
	)
	end

	#返回：封印怪物(挑战?)
	def onReturn_SealMonster(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SealMonster)返回的参数
	)
	end

	#返回：镇守锁妖塔
	def onReturn_GuardAtk(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GuardAtk)返回的参数
	)
	end

	#返回：抢夺镇守位置
	def onReturn_AtkPlayer(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_AtkPlayer)返回的参数
	)
	end

	#返回：领取奖励
	def onReturn_TakePrize(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakePrize)返回的参数
	)
	end

	#返回：获取镇守榜
	def onReturn_GetTopList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetTopList)返回的参数
	)
	end

	#返回：获取本人镇妖塔相关信息
	def onReturn_GetDemonTowerInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetDemonTowerInfo)返回的参数
	)
	end

	#返回：获取镇守信息信息
	def onReturn_GetGuardInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetGuardInfo)返回的参数
	)
	end

	#返回：获取玩家镇守信息
	def onReturn_GetPlayerInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetPlayerInfo)返回的参数
	)
	end

	#返回：清除pvp战斗cd
	def onReturn_ClearFightCd(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ClearFightCd)返回的参数
	)
	end

	#返回：获取过关信息
	def onReturn_GetPassInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetPassInfo)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：锁妖塔镇守信息
	def _doRecv_GuardInfoNotify(data)
		dwFloorID = ByteUtil::readUINT32(data)
		vecGuardInfo = GuardInfo::vectorFromStream(data)
		return onRecv_GuardInfoNotify(dwFloorID, vecGuardInfo)
	end

	#接收处理：锁妖塔镇守信息更新
	def _doRecv_GuardInfoChangeNotify(data)
		dwFloorID = ByteUtil::readUINT32(data)
		dwPos = ByteUtil::readUINT32(data)
		qwUserID = ByteUtil::readUINT64(data)
		oGuardInfo = GuardInfo::fromStream(data)
		return onRecv_GuardInfoChangeNotify(dwFloorID, dwPos, qwUserID, oGuardInfo)
	end

	#接收处理：锁妖塔过关通知
	def _doRecv_PassDemonTowerNotify(data)
		dwFloorID = ByteUtil::readUINT32(data)
		return onRecv_PassDemonTowerNotify(dwFloorID)
	end

	#接收处理：锁妖塔镇守攻击cd
	def _doRecv_DemonTowerAtkCDNotify(data)
		dwGuardNextAttackTime = ByteUtil::readUINT32(data)
		return onRecv_DemonTowerAtkCDNotify(dwGuardNextAttackTime)
	end

	#接收处理：镇妖塔玩家信息
	def _doRecv_DemonTowerPlayerNotify(data)
		oDemonTowerPlayerInfo = SDemonTowerPlayer::fromStream(data)
		return onRecv_DemonTowerPlayerNotify(oDemonTowerPlayerInfo)
	end

	#接收处理：镇妖塔错误信息
	def _doRecv_DemonTowerErrorNotify(data)
		dwError = ByteUtil::readUINT32(data)
		return onRecv_DemonTowerErrorNotify(dwError)
	end

	#接收处理：镇守锁妖塔通知
	def _doRecv_GuardSucessNotify(data)
		dwFloorID = ByteUtil::readUINT32(data)
		dwGuardPos = ByteUtil::readUINT32(data)
		return onRecv_GuardSucessNotify(dwFloorID, dwGuardPos)
	end

	#接收处理：19点重置奖励通知
	def _doRecv_DemonTowerResetNotify(data)
		dwFloorID = ByteUtil::readUINT32(data)
		dwGuardPos = ByteUtil::readUINT32(data)
		vecSoulPrize = MoneyInfo::vectorFromStream(data)
		return onRecv_DemonTowerResetNotify(dwFloorID, dwGuardPos, vecSoulPrize)
	end

	#接收处理：镇妖塔被抢通知
	def _doRecv_DemonTowerBeAttackNotify(data)
		dwFloorID = ByteUtil::readUINT32(data)
		dwPos = ByteUtil::readUINT32(data)
		qwAtkUserID = ByteUtil::readUINT64(data)
		strRole = ByteUtil::readSTRING(data)
		vecFailSoulPrize = MoneyInfo::vectorFromStream(data)
		return onRecv_DemonTowerBeAttackNotify(dwFloorID, dwPos, qwAtkUserID, strRole, vecFailSoulPrize)
	end

	#接收处理：玩家切层通知
	def _doRecv_EnterDemonTowerNotify(data)
		dwCurFloorID = ByteUtil::readUINT32(data)
		return onRecv_EnterDemonTowerNotify(dwCurFloorID)
	end

	#接收处理：镇妖塔分身崩溃通知
	def _doRecv_PrizeNotify(data)
		eDemonTowerPrize = ByteUtil::readUINT8(data)
		dwFloorID = ByteUtil::readUINT32(data)
		dwGuardPos = ByteUtil::readUINT32(data)
		vecPrize = MoneyInfo::vectorFromStream(data)
		return onRecv_PrizeNotify(eDemonTowerPrize, dwFloorID, dwGuardPos, vecPrize)
	end

	#接收处理：过关信息
	def _doRecv_PassInfoNotify(data)
		wFloorID = ByteUtil::readUINT16(data)
		vecMinRound = SDemonTowerKillMonster::vectorFromStream(data)
		vecMinBattlePoint = SDemonTowerKillMonster::vectorFromStream(data)
		return onRecv_PassInfoNotify(wFloorID, vecMinRound, vecMinBattlePoint)
	end

#以下为返回处理函数
	#返回处理：进入锁妖塔
	def _doReturn_EnterDemonTower(data)
		retParam = SRetParam_EnterDemonTower.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果 0成功其他错误码
		retParam.dwRet = dwRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_EnterDemonTower(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：进入锁妖塔
	def _onTimeOut_EnterDemonTower(sessionID)
		retParam = SRetParam_EnterDemonTower.new;
		onReturn_EnterDemonTower(2, retParam)
	end

	#返回处理：离开锁妖塔
	def _doReturn_LeaveDemonTower(data)
		retParam = SRetParam_LeaveDemonTower.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果 0成功其他错误码
		retParam.dwRet = dwRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LeaveDemonTower(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：离开锁妖塔
	def _onTimeOut_LeaveDemonTower(sessionID)
		retParam = SRetParam_LeaveDemonTower.new;
		onReturn_LeaveDemonTower(2, retParam)
	end

	#返回处理：封印怪物(挑战?)
	def _doReturn_SealMonster(data)
		retParam = SRetParam_SealMonster.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果 0成功其他错误码
		retParam.dwRet = dwRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SealMonster(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：封印怪物(挑战?)
	def _onTimeOut_SealMonster(sessionID)
		retParam = SRetParam_SealMonster.new;
		onReturn_SealMonster(2, retParam)
	end

	#返回处理：镇守锁妖塔
	def _doReturn_GuardAtk(data)
		retParam = SRetParam_GuardAtk.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果 0成功其他错误码
		retParam.dwRet = dwRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GuardAtk(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：镇守锁妖塔
	def _onTimeOut_GuardAtk(sessionID)
		retParam = SRetParam_GuardAtk.new;
		onReturn_GuardAtk(2, retParam)
	end

	#返回处理：抢夺镇守位置
	def _doReturn_AtkPlayer(data)
		retParam = SRetParam_AtkPlayer.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果 0成功其他错误码
		retParam.dwRet = dwRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_AtkPlayer(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：抢夺镇守位置
	def _onTimeOut_AtkPlayer(sessionID)
		retParam = SRetParam_AtkPlayer.new;
		onReturn_AtkPlayer(2, retParam)
	end

	#返回处理：领取奖励
	def _doReturn_TakePrize(data)
		retParam = SRetParam_TakePrize.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果 0成功其他错误码
		retParam.dwRet = dwRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakePrize(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：领取奖励
	def _onTimeOut_TakePrize(sessionID)
		retParam = SRetParam_TakePrize.new;
		onReturn_TakePrize(2, retParam)
	end

	#返回处理：获取镇守榜
	def _doReturn_GetTopList(data)
		retParam = SRetParam_GetTopList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		oDemonFloorPage = SDemonFloorPage::fromStream(data) #(类类型：SDemonFloorPage)分页信息
		retParam.oDemonFloorPage = oDemonFloorPage
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetTopList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取镇守榜
	def _onTimeOut_GetTopList(sessionID)
		retParam = SRetParam_GetTopList.new;
		onReturn_GetTopList(2, retParam)
	end

	#返回处理：获取本人镇妖塔相关信息
	def _doReturn_GetDemonTowerInfo(data)
		retParam = SRetParam_GetDemonTowerInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果 0成功 1-失败（非错误，没有进过镇妖塔）
		oDemonTowerPlayer = SDemonTowerPlayer::fromStream(data) #(类类型：SDemonTowerPlayer)玩家镇守信息
		retParam.dwRet = dwRet
		retParam.oDemonTowerPlayer = oDemonTowerPlayer
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetDemonTowerInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取本人镇妖塔相关信息
	def _onTimeOut_GetDemonTowerInfo(sessionID)
		retParam = SRetParam_GetDemonTowerInfo.new;
		onReturn_GetDemonTowerInfo(2, retParam)
	end

	#返回处理：获取镇守信息信息
	def _doReturn_GetGuardInfo(data)
		retParam = SRetParam_GetGuardInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecGuardInfo = GuardInfo::vectorFromStream(data) #(GuardInfo的数组)镇守信息信息
		retParam.vecGuardInfo = vecGuardInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetGuardInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取镇守信息信息
	def _onTimeOut_GetGuardInfo(sessionID)
		retParam = SRetParam_GetGuardInfo.new;
		onReturn_GetGuardInfo(2, retParam)
	end

	#返回处理：获取玩家镇守信息
	def _doReturn_GetPlayerInfo(data)
		retParam = SRetParam_GetPlayerInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		bRet = ByteUtil::readUINT8(data) #(UINT8)0 成功 1玩家不存在
		oDemonFloorPlayer = SDemonFloorPlayer::fromStream(data) #(类类型：SDemonFloorPlayer)玩家镇守信息
		retParam.bRet = bRet
		retParam.oDemonFloorPlayer = oDemonFloorPlayer
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetPlayerInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取玩家镇守信息
	def _onTimeOut_GetPlayerInfo(sessionID)
		retParam = SRetParam_GetPlayerInfo.new;
		onReturn_GetPlayerInfo(2, retParam)
	end

	#返回处理：清除pvp战斗cd
	def _doReturn_ClearFightCd(data)
		retParam = SRetParam_ClearFightCd.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		bRet = ByteUtil::readUINT8(data) #(UINT8)0成功 其他失败
		retParam.bRet = bRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ClearFightCd(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：清除pvp战斗cd
	def _onTimeOut_ClearFightCd(sessionID)
		retParam = SRetParam_ClearFightCd.new;
		onReturn_ClearFightCd(2, retParam)
	end

	#返回处理：获取过关信息
	def _doReturn_GetPassInfo(data)
		retParam = SRetParam_GetPassInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecMinRound = SDemonTowerKillMonster::vectorFromStream(data) #(SDemonTowerKillMonster的数组)最快通关
		vecMinBattlePoint = SDemonTowerKillMonster::vectorFromStream(data) #(SDemonTowerKillMonster的数组)最小战斗力通关
		retParam.vecMinRound = vecMinRound
		retParam.vecMinBattlePoint = vecMinBattlePoint
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetPassInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取过关信息
	def _onTimeOut_GetPassInfo(sessionID)
		retParam = SRetParam_GetPassInfo.new;
		onReturn_GetPassInfo(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 71;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_GuardInfoNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_GuardInfoChangeNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_PassDemonTowerNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_DemonTowerAtkCDNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_DemonTowerPlayerNotify' #FuncID: 5
		@recvFuncList[5] = '_doRecv_DemonTowerErrorNotify' #FuncID: 6
		@recvFuncList[6] = '_doRecv_GuardSucessNotify' #FuncID: 7
		@recvFuncList[7] = '_doRecv_DemonTowerResetNotify' #FuncID: 8
		@recvFuncList[8] = '_doRecv_DemonTowerBeAttackNotify' #FuncID: 9
		@recvFuncList[9] = '_doRecv_EnterDemonTowerNotify' #FuncID: 10
		@recvFuncList[10] = '_doRecv_PrizeNotify' #FuncID: 11
		@recvFuncList[11] = '_doRecv_PassInfoNotify' #FuncID: 12

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_EnterDemonTower' #FuncID: 1
		@retFuncList[1] = '_doReturn_LeaveDemonTower' #FuncID: 2
		@retFuncList[2] = '_doReturn_SealMonster' #FuncID: 3
		@retFuncList[3] = '_doReturn_GuardAtk' #FuncID: 4
		@retFuncList[4] = '_doReturn_AtkPlayer' #FuncID: 5
		@retFuncList[5] = '_doReturn_TakePrize' #FuncID: 6
		@retFuncList[6] = '_doReturn_GetTopList' #FuncID: 7
		@retFuncList[7] = '_doReturn_GetDemonTowerInfo' #FuncID: 8
		@retFuncList[8] = '_doReturn_GetGuardInfo' #FuncID: 9
		@retFuncList[9] = '_doReturn_GetPlayerInfo' #FuncID: 10
		@retFuncList[10] = '_doReturn_ClearFightCd' #FuncID: 11
		@retFuncList[11] = '_doReturn_GetPassInfo' #FuncID: 12

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_EnterDemonTower' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_LeaveDemonTower' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_SealMonster' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_GuardAtk' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_AtkPlayer' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_TakePrize' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_GetTopList' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_GetDemonTowerInfo' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_GetGuardInfo' #FuncID: 9
		@timeFuncList[9] = '_onTimeOut_GetPlayerInfo' #FuncID: 10
		@timeFuncList[10] = '_onTimeOut_ClearFightCd' #FuncID: 11
		@timeFuncList[11] = '_onTimeOut_GetPassInfo' #FuncID: 12
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

