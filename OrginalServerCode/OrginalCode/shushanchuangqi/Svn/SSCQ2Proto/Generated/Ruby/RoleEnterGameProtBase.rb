#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    RoleEnterGameProt.rb
#  Purpose:      角色信息相关操作协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#登录结果
class EEnterResult
	EENTERSUCCEED = 0#成功
	EROLENOEXIST = 1#角色未创建
	EENTERALREADY = 2#已经在游戏中
	EENTERDATAERR = 3#角色数据错误
	EENTERSTATEERR = 4#状态错误
	EENTERFREEZERR = 5#帐号被封
	EENTEROTHERERR = 6#其它错误
end

#角色操作的结果
class ECreateRoleResult
	EROLESUCCEED = 0#成功
	EROLEEXIST = 1#角色已存在
	EROLENAMEEXIST = 2#角色名已存在
	EROLENAMEINVALID = 3#角色名称有非法字符
	EROLENAMETOOLONG = 4#角色名过长
	EROLENAMETOOSHORT = 5#角色名过短
	EROLESTATEERR = 6#状态错误
	EROLEJOBERR = 7#职业错误
	EROLESEXERR = 8#性别错误
	EROLEOTHERERR = 9#其它错误
end

#查询基础消息
class PlayerBaseData
	attr_accessor:strName #(string)玩家名字
	attr_accessor:eCareer #(枚类型：ProtoCommon::ECareerType)职业
	attr_accessor:eSex #(枚类型：ProtoCommon::ESexType)性别
	attr_accessor:byLevel #(UINT8)玩家等级
	attr_accessor:qwExp #(UINT64)玩家经验值
	attr_accessor:wBagMax #(UINT16)背包容量
	attr_accessor:wDepotMax #(UINT16)仓库容量
	attr_accessor:byNation #(UINT8)国家
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
	attr_accessor:dwPoten #(UINT32)潜能
	attr_accessor:dwReiki #(UINT32)灵力
	attr_accessor:dwDemonSoul #(UINT32)锁妖塔魂值
	attr_accessor:dwSoulAttack #(UINT32)攻击之魂
	attr_accessor:dwSoulHp #(UINT32)生命之魂
	attr_accessor:dwSoulCritical #(UINT32)暴击之魂
	attr_accessor:dwSoulCounter #(UINT32)反击之魂
	attr_accessor:dwSoulSpeed #(UINT32)身法之魂
	attr_accessor:dwSoulDefence #(UINT32)防御之魂
	attr_accessor:dwSoulHit #(UINT32)命中之魂
	attr_accessor:dwSoulDodge #(UINT32)闪避之魂
	attr_accessor:dwStampHuang #(UINT32)黄阶除魔印
	attr_accessor:dwStampXuan #(UINT32)玄阶除魔印
	attr_accessor:dwStampDi #(UINT32)地阶除魔印
	attr_accessor:dwStampTian #(UINT32)天阶除魔印
	attr_accessor:dwStampXing #(UINT32)星阶除魔印
	attr_accessor:dwStampYue #(UINT32)月阶除魔印
	attr_accessor:dwStampDi2 #(UINT32)帝阶除魔印
	attr_accessor:dwStampXian #(UINT32)仙阶除魔印
	attr_accessor:dwStampSheng #(UINT32)圣阶除魔印
	attr_accessor:dwStampFo #(UINT32)佛阶除魔印
	attr_accessor:dwBTPoint #(UINT32)战斗力
	attr_accessor:dwBlueFairyFate #(UINT32)蓝色仙缘
	attr_accessor:dwPurpleFairyFate #(UINT32)紫色仙缘
	attr_accessor:dwOrangeFairyFate #(UINT32)橙色仙缘
	attr_accessor:dwTotalRecharge #(UINT32)总充值数
	attr_accessor:vecOwnTitle #(UINT16数组)拥有称号
	attr_accessor:vecEquipTitle #(UINT16数组)装备称号
	attr_accessor:strGuide #(string)新手引导信息
	attr_accessor:byWallow #(UINT8)防沉迷
	attr_accessor:vecIconAppear #(UINT16数组)Icon开启
	attr_accessor:vecIconDel #(UINT16数组)Icon关闭
	attr_accessor:dwDemonTowerFloorID #(UINT32)通关镇妖塔层数
	attr_accessor:dwDemonTowerPrizeFloorID #(UINT32)镇妖塔领奖层数
	attr_accessor:dwCreateTime #(UINT32)玩家创角时间

	#构造函数
	def initialize
		@strName = ''
		@eCareer = 0
		@eSex = 0
		@byLevel = 0
		@qwExp = 0
		@wBagMax = 0
		@wDepotMax = 0
		@byNation = 0
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
		@dwPoten = 0
		@dwReiki = 0
		@dwDemonSoul = 0
		@dwSoulAttack = 0
		@dwSoulHp = 0
		@dwSoulCritical = 0
		@dwSoulCounter = 0
		@dwSoulSpeed = 0
		@dwSoulDefence = 0
		@dwSoulHit = 0
		@dwSoulDodge = 0
		@dwStampHuang = 0
		@dwStampXuan = 0
		@dwStampDi = 0
		@dwStampTian = 0
		@dwStampXing = 0
		@dwStampYue = 0
		@dwStampDi2 = 0
		@dwStampXian = 0
		@dwStampSheng = 0
		@dwStampFo = 0
		@dwBTPoint = 0
		@dwBlueFairyFate = 0
		@dwPurpleFairyFate = 0
		@dwOrangeFairyFate = 0
		@dwTotalRecharge = 0
		@vecOwnTitle = Array.new
		@vecEquipTitle = Array.new
		@strGuide = ''
		@byWallow = 0
		@vecIconAppear = Array.new
		@vecIconDel = Array.new
		@dwDemonTowerFloorID = 0
		@dwDemonTowerPrizeFloorID = 0
		@dwCreateTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strName = @strName
		obj.eCareer = @eCareer
		obj.eSex = @eSex
		obj.byLevel = @byLevel
		obj.qwExp = @qwExp
		obj.wBagMax = @wBagMax
		obj.wDepotMax = @wDepotMax
		obj.byNation = @byNation
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
		obj.dwPoten = @dwPoten
		obj.dwReiki = @dwReiki
		obj.dwDemonSoul = @dwDemonSoul
		obj.dwSoulAttack = @dwSoulAttack
		obj.dwSoulHp = @dwSoulHp
		obj.dwSoulCritical = @dwSoulCritical
		obj.dwSoulCounter = @dwSoulCounter
		obj.dwSoulSpeed = @dwSoulSpeed
		obj.dwSoulDefence = @dwSoulDefence
		obj.dwSoulHit = @dwSoulHit
		obj.dwSoulDodge = @dwSoulDodge
		obj.dwStampHuang = @dwStampHuang
		obj.dwStampXuan = @dwStampXuan
		obj.dwStampDi = @dwStampDi
		obj.dwStampTian = @dwStampTian
		obj.dwStampXing = @dwStampXing
		obj.dwStampYue = @dwStampYue
		obj.dwStampDi2 = @dwStampDi2
		obj.dwStampXian = @dwStampXian
		obj.dwStampSheng = @dwStampSheng
		obj.dwStampFo = @dwStampFo
		obj.dwBTPoint = @dwBTPoint
		obj.dwBlueFairyFate = @dwBlueFairyFate
		obj.dwPurpleFairyFate = @dwPurpleFairyFate
		obj.dwOrangeFairyFate = @dwOrangeFairyFate
		obj.dwTotalRecharge = @dwTotalRecharge
		obj.vecOwnTitle = @vecOwnTitle
		obj.vecEquipTitle = @vecEquipTitle
		obj.strGuide = @strGuide
		obj.byWallow = @byWallow
		obj.vecIconAppear = @vecIconAppear
		obj.vecIconDel = @vecIconDel
		obj.dwDemonTowerFloorID = @dwDemonTowerFloorID
		obj.dwDemonTowerPrizeFloorID = @dwDemonTowerPrizeFloorID
		obj.dwCreateTime = @dwCreateTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = PlayerBaseData.new
		s.strName = ByteUtil::readSTRING(data)
		s.eCareer = ByteUtil::readUINT8(data)
		s.eSex = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.qwExp = ByteUtil::readUINT64(data)
		s.wBagMax = ByteUtil::readUINT16(data)
		s.wDepotMax = ByteUtil::readUINT16(data)
		s.byNation = ByteUtil::readUINT8(data)
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
		s.dwPoten = ByteUtil::readUINT32(data)
		s.dwReiki = ByteUtil::readUINT32(data)
		s.dwDemonSoul = ByteUtil::readUINT32(data)
		s.dwSoulAttack = ByteUtil::readUINT32(data)
		s.dwSoulHp = ByteUtil::readUINT32(data)
		s.dwSoulCritical = ByteUtil::readUINT32(data)
		s.dwSoulCounter = ByteUtil::readUINT32(data)
		s.dwSoulSpeed = ByteUtil::readUINT32(data)
		s.dwSoulDefence = ByteUtil::readUINT32(data)
		s.dwSoulHit = ByteUtil::readUINT32(data)
		s.dwSoulDodge = ByteUtil::readUINT32(data)
		s.dwStampHuang = ByteUtil::readUINT32(data)
		s.dwStampXuan = ByteUtil::readUINT32(data)
		s.dwStampDi = ByteUtil::readUINT32(data)
		s.dwStampTian = ByteUtil::readUINT32(data)
		s.dwStampXing = ByteUtil::readUINT32(data)
		s.dwStampYue = ByteUtil::readUINT32(data)
		s.dwStampDi2 = ByteUtil::readUINT32(data)
		s.dwStampXian = ByteUtil::readUINT32(data)
		s.dwStampSheng = ByteUtil::readUINT32(data)
		s.dwStampFo = ByteUtil::readUINT32(data)
		s.dwBTPoint = ByteUtil::readUINT32(data)
		s.dwBlueFairyFate = ByteUtil::readUINT32(data)
		s.dwPurpleFairyFate = ByteUtil::readUINT32(data)
		s.dwOrangeFairyFate = ByteUtil::readUINT32(data)
		s.dwTotalRecharge = ByteUtil::readUINT32(data)
		s.vecOwnTitle = ByteUtil::readVecUINT16(data)
		s.vecEquipTitle = ByteUtil::readVecUINT16(data)
		s.strGuide = ByteUtil::readSTRING(data)
		s.byWallow = ByteUtil::readUINT8(data)
		s.vecIconAppear = ByteUtil::readVecUINT16(data)
		s.vecIconDel = ByteUtil::readVecUINT16(data)
		s.dwDemonTowerFloorID = ByteUtil::readUINT32(data)
		s.dwDemonTowerPrizeFloorID = ByteUtil::readUINT32(data)
		s.dwCreateTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = PlayerBaseData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @eCareer)
		ByteUtil::writeUINT8(data, @eSex)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT64(data, @qwExp)
		ByteUtil::writeUINT16(data, @wBagMax)
		ByteUtil::writeUINT16(data, @wDepotMax)
		ByteUtil::writeUINT8(data, @byNation)
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
		ByteUtil::writeUINT32(data, @dwPoten)
		ByteUtil::writeUINT32(data, @dwReiki)
		ByteUtil::writeUINT32(data, @dwDemonSoul)
		ByteUtil::writeUINT32(data, @dwSoulAttack)
		ByteUtil::writeUINT32(data, @dwSoulHp)
		ByteUtil::writeUINT32(data, @dwSoulCritical)
		ByteUtil::writeUINT32(data, @dwSoulCounter)
		ByteUtil::writeUINT32(data, @dwSoulSpeed)
		ByteUtil::writeUINT32(data, @dwSoulDefence)
		ByteUtil::writeUINT32(data, @dwSoulHit)
		ByteUtil::writeUINT32(data, @dwSoulDodge)
		ByteUtil::writeUINT32(data, @dwStampHuang)
		ByteUtil::writeUINT32(data, @dwStampXuan)
		ByteUtil::writeUINT32(data, @dwStampDi)
		ByteUtil::writeUINT32(data, @dwStampTian)
		ByteUtil::writeUINT32(data, @dwStampXing)
		ByteUtil::writeUINT32(data, @dwStampYue)
		ByteUtil::writeUINT32(data, @dwStampDi2)
		ByteUtil::writeUINT32(data, @dwStampXian)
		ByteUtil::writeUINT32(data, @dwStampSheng)
		ByteUtil::writeUINT32(data, @dwStampFo)
		ByteUtil::writeUINT32(data, @dwBTPoint)
		ByteUtil::writeUINT32(data, @dwBlueFairyFate)
		ByteUtil::writeUINT32(data, @dwPurpleFairyFate)
		ByteUtil::writeUINT32(data, @dwOrangeFairyFate)
		ByteUtil::writeUINT32(data, @dwTotalRecharge)
		ByteUtil::writeVecUINT16(data, @vecOwnTitle)
		ByteUtil::writeVecUINT16(data, @vecEquipTitle)
		ByteUtil::writeSTRING(data, @strGuide)
		ByteUtil::writeUINT8(data, @byWallow)
		ByteUtil::writeVecUINT16(data, @vecIconAppear)
		ByteUtil::writeVecUINT16(data, @vecIconDel)
		ByteUtil::writeUINT32(data, @dwDemonTowerFloorID)
		ByteUtil::writeUINT32(data, @dwDemonTowerPrizeFloorID)
		ByteUtil::writeUINT32(data, @dwCreateTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#查询角色消息
class RoleEnterGameData
	attr_accessor:byIsUser #(UINT8)0表示不存在
	attr_accessor:sBaseInfo #(类类型：PlayerBaseData)基础信息

	#构造函数
	def initialize
		@byIsUser = 0
		@sBaseInfo = PlayerBaseData.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byIsUser = @byIsUser
		obj.sBaseInfo = @sBaseInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = RoleEnterGameData.new
		s.byIsUser = ByteUtil::readUINT8(data)
		s.sBaseInfo = PlayerBaseData::fromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = RoleEnterGameData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byIsUser)
		@sBaseInfo.toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#角色信息
class SCreateRoleInfo
	attr_accessor:strName #(string)角色名
	attr_accessor:eCareer #(枚类型：ProtoCommon::ECareerType)职业
	attr_accessor:eSex #(枚类型：ProtoCommon::ESexType)性别
	attr_accessor:strInviteRoleID #(string)好友邀请id
	attr_accessor:strIP #(string)创角时ip

	#构造函数
	def initialize
		@strName = ''
		@eCareer = 0
		@eSex = 0
		@strInviteRoleID = ''
		@strIP = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strName = @strName
		obj.eCareer = @eCareer
		obj.eSex = @eSex
		obj.strInviteRoleID = @strInviteRoleID
		obj.strIP = @strIP
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SCreateRoleInfo.new
		s.strName = ByteUtil::readSTRING(data)
		s.eCareer = ByteUtil::readUINT8(data)
		s.eSex = ByteUtil::readUINT8(data)
		s.strInviteRoleID = ByteUtil::readSTRING(data)
		s.strIP = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SCreateRoleInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @eCareer)
		ByteUtil::writeUINT8(data, @eSex)
		ByteUtil::writeSTRING(data, @strInviteRoleID)
		ByteUtil::writeSTRING(data, @strIP)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#角色信息
class SEnterParam
	attr_accessor:byPtType #(枚类型：ProtoCommon::EPtType)平台类型
	attr_accessor:byQQPtType #(枚类型：ProtoCommon::EQQPtType)QQ平台类型
	attr_accessor:byQQPtLv #(UINT8)QQ平台类型等级
	attr_accessor:byQQPtYearType #(UINT8)是否年费
	attr_accessor:byQQPtLuxuryType #(UINT8)是否豪华
	attr_accessor:customPar1 #(string)广告主来源
	attr_accessor:customPar2 #(string)广告次来源
	attr_accessor:strOpenId #(string)openID
	attr_accessor:strOpenKey #(string)openKey

	#构造函数
	def initialize
		@byPtType = 0
		@byQQPtType = 0
		@byQQPtLv = 0
		@byQQPtYearType = 0
		@byQQPtLuxuryType = 0
		@customPar1 = ''
		@customPar2 = ''
		@strOpenId = ''
		@strOpenKey = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byPtType = @byPtType
		obj.byQQPtType = @byQQPtType
		obj.byQQPtLv = @byQQPtLv
		obj.byQQPtYearType = @byQQPtYearType
		obj.byQQPtLuxuryType = @byQQPtLuxuryType
		obj.customPar1 = @customPar1
		obj.customPar2 = @customPar2
		obj.strOpenId = @strOpenId
		obj.strOpenKey = @strOpenKey
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEnterParam.new
		s.byPtType = ByteUtil::readUINT8(data)
		s.byQQPtType = ByteUtil::readUINT8(data)
		s.byQQPtLv = ByteUtil::readUINT8(data)
		s.byQQPtYearType = ByteUtil::readUINT8(data)
		s.byQQPtLuxuryType = ByteUtil::readUINT8(data)
		s.customPar1 = ByteUtil::readSTRING(data)
		s.customPar2 = ByteUtil::readSTRING(data)
		s.strOpenId = ByteUtil::readSTRING(data)
		s.strOpenKey = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEnterParam::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byPtType)
		ByteUtil::writeUINT8(data, @byQQPtType)
		ByteUtil::writeUINT8(data, @byQQPtLv)
		ByteUtil::writeUINT8(data, @byQQPtYearType)
		ByteUtil::writeUINT8(data, @byQQPtLuxuryType)
		ByteUtil::writeSTRING(data, @customPar1)
		ByteUtil::writeSTRING(data, @customPar2)
		ByteUtil::writeSTRING(data, @strOpenId)
		ByteUtil::writeSTRING(data, @strOpenKey)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#协议类：角色信息相关操作协议
class RoleEnterGameProtBase < ProtocolBase
	#以下为发送函数
	#发送：请求进入游戏
	def send_EnterGameReq(
		stEnterParam #(类类型：SEnterParam)信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		stEnterParam.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：创建角色请求
	def send_CreateRoleReq(
		stCreateInfo #(类类型：SCreateRoleInfo)创角信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		stCreateInfo.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家请求推荐名字
	def send_PlayerRamdomNameReq(
		byIsMale #(UINT8)非0表示男性
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, byIsMale)
		return @svrHandler.sendPacket(data)
	end

	#发送：角色信息查询
	def send_GetUserInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：请求进入游戏应答
	def onRecv_EnterGameAck(
		eEnterResult, #(枚举类型：EEnterResult)登陆结果
		dwNowTimer #(UINT32)目前服务器的时间
	)
		raise NotImplementedError
	end
	#接收：创建角色应答
	def onRecv_CreateRoleAck(
		eCreateRoleResult #(枚举类型：ECreateRoleResult)创建结果
	)
		raise NotImplementedError
	end
	#接收：玩家请求推荐名字返回
	def onRecv_PlayerRamdomNameAck(
		strName #(string)空表示没有得到
	)
		raise NotImplementedError
	end
	#接收：角色查询返回
	def onRecv_GetUserInfoAck(
		stRoleEnterInfo #(类类型：RoleEnterGameData)进入信息
	)
		raise NotImplementedError
	end
#以下为接收处理函数
	#接收处理：请求进入游戏应答
	def _doRecv_EnterGameAck(data)
		eEnterResult = ByteUtil::readUINT8(data)
		dwNowTimer = ByteUtil::readUINT32(data)
		return onRecv_EnterGameAck(eEnterResult, dwNowTimer)
	end

	#接收处理：创建角色应答
	def _doRecv_CreateRoleAck(data)
		eCreateRoleResult = ByteUtil::readUINT8(data)
		return onRecv_CreateRoleAck(eCreateRoleResult)
	end

	#接收处理：玩家请求推荐名字返回
	def _doRecv_PlayerRamdomNameAck(data)
		strName = ByteUtil::readSTRING(data)
		return onRecv_PlayerRamdomNameAck(strName)
	end

	#接收处理：角色查询返回
	def _doRecv_GetUserInfoAck(data)
		stRoleEnterInfo = RoleEnterGameData::fromStream(data)
		return onRecv_GetUserInfoAck(stRoleEnterInfo)
	end

	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 3;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_EnterGameAck' #FuncID: 1
		@recvFuncList[1] = '_doRecv_CreateRoleAck' #FuncID: 2
		@recvFuncList[2] = '_doRecv_PlayerRamdomNameAck' #FuncID: 3
		@recvFuncList[3] = '_doRecv_GetUserInfoAck' #FuncID: 4
	end

	def handleMessage(data)
		funcID = ByteUtil::readINT8(data);
		if funcID == 0 || funcID > @recvFuncList.length
			return false
		end
		if funcID > 0 
			func = @recvFuncList[funcID - 1]
		end
		if func
			 send(func, data)
		end
		#if func != nil
			#return call_user_func(Array.new(self, func), data)
		#end
		return true
	end
end

