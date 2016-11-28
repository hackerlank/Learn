#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    BattleGS.rb
#  Purpose:      战斗通信协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ItemProtBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#被动状态枚举
class EBStatusType
	EBSTATUSTYPE_EVADE = 0#闪避
	EBSTATUSTYPE_RESIST = 1#抵抗
	EBSTATUSTYPE_IMMU = 2#免疫
	EBSTATUSTYPE_BLOCK = 3#格挡
end

#State效果枚举
class EBStateBuffType
	EBFBUFFTYPENONE = 0#无状态
	EBFBUFFTYPEMIN = 0#出手时状态枚举最小值
	EBFBUFFTYPESTUN = 1#眩晕
	EBFBUFFTYPECONFUSE = 2#混乱
	EBFBUFFTYPECOVER = 3#掩护
	EBFBUFFTYPEESHOCK = 4#电击
	EBFBUFFTYPEBLOCK = 5#格挡
	EBFBUFFTYPEINVINCIBLE = 6#无敌
	EBFBUFFTYPESHIELD = 7#护盾
	EBFBUFFTYPEPIERCE = 8#破甲
	EBFBUFFTYPEBLEED = 9#流血
	EBFBUFFTYPEFORGET = 10#沉默
	EBFBUFFTYPEFREEZE = 11#冻结
	EBFBUFFTYPEBURNED = 12#点燃
	EBFBUFFTYPEATKADD = 13#攻击提升
	EBFBUFFTYPEATKSUB = 14#攻击下降
	EBFBUFFTYPEREDADD = 15#免伤提升
	EBFBUFFTYPEREDSUB = 16#免伤下降
	EBFBUFFTYPESTONED = 17#石化
	EBFBUFFTYPEPOISON = 18#中毒
	EBFBUFFTYPEHIDE = 19#影遁
	EBFBUFFTYPEBRONZE = 20#铜人
	EBFBUFFTYPEKINGKONG = 21#金刚
	EBFBUFFTYPEDMGREDUCE = 22#伤害减少
	EBFBUFFTYPEDMGADD = 23#伤害提升
	EBFBUFFTYPECONGEST = 24#蓄力
	EBFBUFFTYPEREFLECT = 25#反弹状态
	EBFBUFFTYPEHITDOWN = 26#命中降低
	EBFBUFFTYPECLONE = 27#分身
	EBFBUFFTYPESEALED = 28#封印
	EBFBUFFTYPEBEDMGREUDCE = 29#伤害减免
	EBFBUFFTYPEBLIND = 30#致盲
	EBFBUFFTYPESMOKE = 31#烟幕
	EBFBUFFTYPEGUARD = 32#护卫
	EBFBUFFTYPEKINDKING = 33#仁王
	EBFBUFFTYPEBLUNT = 34#麻痹
	EBFBUFFTYPEICEBLADE = 35#冰刃
	EBFBUFFTYPETHUNDERBLADE = 36#雷刃
	EBFBUFFTYPEFIREBLADE = 37#炎刃
	EBFBUFFTYPESNOWSOUL = 38#雪魂
	EBFBUFFTYPEHALORED = 39#光环红
	EBFBUFFTYPEHALOBLUE = 40#光环蓝
	EBFBUFFTYPEDROGENSTING = 41#龙刺
	EBFBUFFTYPEDMGSHARE = 42#伤害分担
	EBFBUFFTYPEATTRADD = 43#属性增益
	EBFBUFFTYPEATTRSUB = 44#属性减益
	EBFBUFFTYPEACTATKADD = 45#行动后攻击增加
	EBFBUFFTYPEACTDEFADD = 46#行动后防御增加
	EBFBUFFTYPEMAX = 47#状态最大值
end

#扣血伤害类型（物理/法术）
class EBSubHPType
	EBSUBHPPHY = 0#物理
	EBSUBHPMGC = 1#法术
end

#修改血的类型
class EBModifyHPType
	EBMODIFYHP_NORMAL = 0#普通
	EBMODIFYHP_CRITICAL = 1#暴击
end

#被动状态枚举
class EBSheildAbsorbType
	EBSHEILDABSORBPHYSIC = 1#吸收物理伤害
	EBSHEILDABSORBMAGIC = 2#吸收法术伤害
	EBSHEILDABSORBDAMAGE = 3#吸收伤害
end

#连携槽增长方式
class ECombineType
	ECTNONE = 0#无效方式
	ECTCRITICAL = 1#暴击
	ECTBLOCK = 2#格挡
	ECTEVADE = 3#闪避
	ECTCOUNTER = 4#反击
	ECTPEERLESS = 5#无双
	ECTMAX = 6#最大
end

#连携槽操作
class ECombineSlotOPType
	ECSOPTLOCK = 0#关闭连携槽
	ECSOPTUNLOCK = 1#开启连携槽
end

#战斗结果
class EBattleResult
	EBRESULTNONE = 0#无
	EBRESULTATTACKWIN = 1#攻击方胜利
	EBRESULTDEFENSEWIN = 2#防守方胜利
	EBRESULTTIE = 3#平局（最后血量都相同，可能为0）
end

#战斗模式：PVP/PVE
class EBattleType
	EBTINVALID = 1#PVE(攻击怪物)
	EBTMONSTER = 2#PVE(攻击怪物)
	EBTPLAYER = 3#PVP(攻击玩家)
	EBWORLDBOSS = 4#世界boss战
	EBARENA = 5#竞技场
	EBDEMONTOWER = 6#锁妖塔
	ETREASUREHUNT = 7#寻宝
	EGUARDEMEI = 8#守卫峨嵋
	EBSHIP = 9#运船
	EBSHUSHAN = 10#论剑
	EBLINGSHAN = 11#灵山寻宝
	EBATTLEEND = 12#结束标志
end

#战斗请求结果
class EBattleReqResult
	EBATTLEREQ_SUC = 1#成功
	EBATTLEREQ_COOLDOWN = 2#您还处在战斗冷却中
	EBATTLEREQ_PROTECT = 3#对方在战斗保护中
	EBATTLEREQ_GUARDFIRST = 4#请先去击杀护卫
	EBATTLEREQ_DIECD = 5#死亡冷却中
	EBATTLEREQ_FIELDCOOLDOWN = 6#野外战斗冷却中
	EBATTLEREQ_LEVEL = 7#等级不够
	EBATTLEREQ_OTHER = 8#未知错误
end

#战报请求结果
class EReportReqResult
	EREPORTREQ_SUC = 1#成功
	EREPORTREQ_NONEXISTENT = 2#请求的战报不存在
	EREPORTREQ_OTHER = 4#未知错误
end

#结构体：SFeatureBase的继承体系类型
class EType_SFeatureBase
	ETYPE_SFEATUREBASE = 0#类型：SFeatureBase
	ETYPE_SMONSTERFEATURE = 1#类型：SMonsterFeature
	ETYPE_SPLAYERFEATURE = 2#类型：SPlayerFeature
	ETYPE_SHEROFEATURE = 3#类型：SHeroFeature
	ETYPE_SFORMATIONFEATURE = 4#类型：SFormationFeature
	ETYPE_SFIELDFEATURE = 5#类型：SFieldFeature
	ETYPE_SBEAUTYFEATURE = 6#类型：SBeautyFeature
	ETYPE_SPLAYERFEATUREWITHBUFF = 7#类型：SPlayerFeatureWithBuff
	ETYPE_SMONSTERFEATUREWITHBUFF = 8#类型：SMonsterFeatureWithBuff
end

#结构体：SEffectBase的继承体系类型
class EType_SEffectBase
	ETYPE_SEFFECTBASE = 0#类型：SEffectBase
	ETYPE_SEFFECTDECHP = 1#类型：SEffectDecHP
	ETYPE_SEFFECTADDSTATUS = 2#类型：SEffectAddStatus
	ETYPE_SEFFECTADDHP = 3#类型：SEffectAddHP
	ETYPE_SEFFECTRELIVE = 4#类型：SEffectRelive
	ETYPE_SEFFECTCOUNTER = 5#类型：SEffectCounter
	ETYPE_SEFFECTSTATEBUFFADD = 6#类型：SEffectStateBuffAdd
	ETYPE_SEFFECTSTATEBUFFEFFECT = 7#类型：SEffectStateBuffEffect
	ETYPE_SEFFECTSTATEBUFFDEC = 8#类型：SEffectStateBuffDec
	ETYPE_SEFFECTSTATEBUFFLAST = 9#类型：SEffectStateBuffLast
	ETYPE_SEFFECTATTRBUFFADD = 10#类型：SEffectAttrBuffAdd
	ETYPE_SEFFECTATTRBUFFDEC = 11#类型：SEffectAttrBuffDec
	ETYPE_SEFFECTDIED = 12#类型：SEffectDied
	ETYPE_SEFFECTSHIELDABSORB = 13#类型：SEffectShieldAbsorb
	ETYPE_SEFFECTTRIGGEREXECUTE = 14#类型：SEffectTriggerExecute
	ETYPE_SEFFECTSYCHP = 15#类型：SEffectSycHP
	ETYPE_SEFFECTSYCAURA = 16#类型：SEffectSycAura
	ETYPE_SEFFECTSYCCOMBINE = 17#类型：SEffectSycCombine
	ETYPE_SEFFECTCOMBINESLOT = 18#类型：SEffectCombineSlot
	ETYPE_SEFFECTBROKENSHIELD = 19#类型：SEffectBrokenShield
	ETYPE_SEFFECTSUMMON = 20#类型：SEffectSummon
	ETYPE_SEFFECTDIALOG = 21#类型：SEffectDialog
	ETYPE_SEFFECTTRANSFORM = 22#类型：SEffectTransform
	ETYPE_SEFFECTPARTBROKEN = 23#类型：SEffectPartBroken
	ETYPE_SEFFECTBUFFACTION = 24#类型：SEffectBuffAction
end

#结构体：NewSBattleReport的继承体系类型
class EType_NewSBattleReport
	ETYPE_NEWSBATTLEREPORT = 0#类型：NewSBattleReport
	ETYPE_NEWSBATTLEREPORTV1 = 1#类型：NewSBattleReportV1
end

#发给前端用的显示外形的装备信息
class SEquipShowInfo
	attr_accessor:wEquipID #(UINT16)装备TypeID
	attr_accessor:byStrengthenLevel #(UINT8)强化等级
	attr_accessor:byPos #(UINT8)装备位置

	#构造函数
	def initialize
		@wEquipID = 0
		@byStrengthenLevel = 0
		@byPos = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wEquipID = @wEquipID
		obj.byStrengthenLevel = @byStrengthenLevel
		obj.byPos = @byPos
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEquipShowInfo.new
		s.wEquipID = ByteUtil::readUINT16(data)
		s.byStrengthenLevel = ByteUtil::readUINT8(data)
		s.byPos = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEquipShowInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wEquipID)
		ByteUtil::writeUINT8(data, @byStrengthenLevel)
		ByteUtil::writeUINT8(data, @byPos)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#装备的头衔外观
class STitleAppear
	attr_accessor:byPos #(UINT8)装备位置
	attr_accessor:wID #(UINT16)头衔ID

	#构造函数
	def initialize
		@byPos = 0
		@wID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byPos = @byPos
		obj.wID = @wID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STitleAppear.new
		s.byPos = ByteUtil::readUINT8(data)
		s.wID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STitleAppear::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byPos)
		ByteUtil::writeUINT16(data, @wID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战斗外的Buff信息
class SBattleBuffInfo
	attr_accessor:wBuffID #(UINT16)Buff种类
	attr_accessor:vecBuffData #(UINT32数组)Buff数值
	attr_accessor:dwBuffCount #(UINT32)Buff叠加层数
	attr_accessor:dwBuffTime #(UINT32)Buff失效时间

	#构造函数
	def initialize
		@wBuffID = 0
		@vecBuffData = Array.new
		@dwBuffCount = 0
		@dwBuffTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wBuffID = @wBuffID
		obj.vecBuffData = @vecBuffData
		obj.dwBuffCount = @dwBuffCount
		obj.dwBuffTime = @dwBuffTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleBuffInfo.new
		s.wBuffID = ByteUtil::readUINT16(data)
		s.vecBuffData = ByteUtil::readVecUINT32(data)
		s.dwBuffCount = ByteUtil::readUINT32(data)
		s.dwBuffTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleBuffInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wBuffID)
		ByteUtil::writeVecUINT32(data, @vecBuffData)
		ByteUtil::writeUINT32(data, @dwBuffCount)
		ByteUtil::writeUINT32(data, @dwBuffTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#外观信息
class SFeatureBase
	attr_accessor:vecBuffID #(UINT16数组)BUffID信息

	#构造函数
	def initialize
		@vecBuffID = Array.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SFeatureBase::ETYPE_SFEATUREBASE
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.vecBuffID = @vecBuffID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFeatureBase.new
		s.vecBuffID = ByteUtil::readVecUINT16(data)
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_SFeatureBase::ETYPE_SFEATUREBASE
				s = SFeatureBase::fromStream(data)
			when EType_SFeatureBase::ETYPE_SMONSTERFEATURE
				s = SMonsterFeature::fromStream(data)
			when EType_SFeatureBase::ETYPE_SPLAYERFEATURE
				s = SPlayerFeature::fromStream(data)
			when EType_SFeatureBase::ETYPE_SHEROFEATURE
				s = SHeroFeature::fromStream(data)
			when EType_SFeatureBase::ETYPE_SFORMATIONFEATURE
				s = SFormationFeature::fromStream(data)
			when EType_SFeatureBase::ETYPE_SFIELDFEATURE
				s = SFieldFeature::fromStream(data)
			when EType_SFeatureBase::ETYPE_SBEAUTYFEATURE
				s = SBeautyFeature::fromStream(data)
			when EType_SFeatureBase::ETYPE_SPLAYERFEATUREWITHBUFF
				s = SPlayerFeatureWithBuff::fromStream(data)
			when EType_SFeatureBase::ETYPE_SMONSTERFEATUREWITHBUFF
				s = SMonsterFeatureWithBuff::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFeatureBase::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFeatureBase::superFromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeVecUINT16(data, @vecBuffID)
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

#怪物
class SMonsterFeature < SFeatureBase
	attr_accessor:wMonsterID #(UINT16)配置表里面的英雄ID，根据ID可以取到怪物外观资源

	#构造函数
	def initialize
		super()
		@wMonsterID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SFeatureBase::ETYPE_SMONSTERFEATURE
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wMonsterID = @wMonsterID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMonsterFeature.new
		base = SFeatureBase::fromStream(data)
		base.copyTo(s)
		s.wMonsterID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMonsterFeature::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wMonsterID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家
class SPlayerFeature < SFeatureBase
	attr_accessor:strName #(string)玩家姓名
	attr_accessor:eJob #(枚类型：ProtoCommon::ECareerType)职业
	attr_accessor:eSex #(枚类型：ProtoCommon::ESexType)性别
	attr_accessor:vEquip #(SEquipShowInfo的数组)装备
	attr_accessor:vecTitle #(STitleAppear的数组)头衔
	attr_accessor:strGuildName #(string)帮派名称
	attr_accessor:byQuality #(UINT8)品质
	attr_accessor:byDujieLevel #(UINT8)散仙渡劫等级
	attr_accessor:byVIPLevel #(UINT8)VIP等级

	#构造函数
	def initialize
		super()
		@strName = ''
		@eJob = 0
		@eSex = 0
		@vEquip = Array.new
		@vecTitle = Array.new
		@strGuildName = ''
		@byQuality = 0
		@byDujieLevel = 0
		@byVIPLevel = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SFeatureBase::ETYPE_SPLAYERFEATURE
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.strName = @strName
		obj.eJob = @eJob
		obj.eSex = @eSex
		obj.vEquip = @vEquip
		obj.vecTitle = @vecTitle
		obj.strGuildName = @strGuildName
		obj.byQuality = @byQuality
		obj.byDujieLevel = @byDujieLevel
		obj.byVIPLevel = @byVIPLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPlayerFeature.new
		base = SFeatureBase::fromStream(data)
		base.copyTo(s)
		s.strName = ByteUtil::readSTRING(data)
		s.eJob = ByteUtil::readUINT8(data)
		s.eSex = ByteUtil::readUINT8(data)
		s.vEquip = SEquipShowInfo::vectorFromStream(data)
		s.vecTitle = STitleAppear::vectorFromStream(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.byDujieLevel = ByteUtil::readUINT8(data)
		s.byVIPLevel = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPlayerFeature::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @eJob)
		ByteUtil::writeUINT8(data, @eSex)
		SEquipShowInfo::vectorToStream(data, @vEquip)
		STitleAppear::vectorToStream(data, @vecTitle)
		ByteUtil::writeSTRING(data, @strGuildName)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT8(data, @byDujieLevel)
		ByteUtil::writeUINT8(data, @byVIPLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#散仙
class SHeroFeature < SFeatureBase
	attr_accessor:wHeroID #(UINT16)散仙类型
	attr_accessor:byQuality #(UINT8)品质
	attr_accessor:byDujieLevel #(UINT8)散仙渡劫等级

	#构造函数
	def initialize
		super()
		@wHeroID = 0
		@byQuality = 0
		@byDujieLevel = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SFeatureBase::ETYPE_SHEROFEATURE
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wHeroID = @wHeroID
		obj.byQuality = @byQuality
		obj.byDujieLevel = @byDujieLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SHeroFeature.new
		base = SFeatureBase::fromStream(data)
		base.copyTo(s)
		s.wHeroID = ByteUtil::readUINT16(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.byDujieLevel = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SHeroFeature::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wHeroID)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT8(data, @byDujieLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#阵灵
class SFormationFeature < SFeatureBase
	attr_accessor:wFormationID #(UINT16)阵灵配置表ID，同monster

	#构造函数
	def initialize
		super()
		@wFormationID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SFeatureBase::ETYPE_SFORMATIONFEATURE
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wFormationID = @wFormationID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFormationFeature.new
		base = SFeatureBase::fromStream(data)
		base.copyTo(s)
		s.wFormationID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFormationFeature::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wFormationID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#场景
class SFieldFeature < SFeatureBase
	attr_accessor:wSceneID #(UINT16)场景ID

	#构造函数
	def initialize
		super()
		@wSceneID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SFeatureBase::ETYPE_SFIELDFEATURE
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wSceneID = @wSceneID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFieldFeature.new
		base = SFeatureBase::fromStream(data)
		base.copyTo(s)
		s.wSceneID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFieldFeature::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wSceneID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#美女
class SBeautyFeature < SFeatureBase
	attr_accessor:wBeautyID #(UINT16)美女ID

	#构造函数
	def initialize
		super()
		@wBeautyID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SFeatureBase::ETYPE_SBEAUTYFEATURE
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wBeautyID = @wBeautyID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBeautyFeature.new
		base = SFeatureBase::fromStream(data)
		base.copyTo(s)
		s.wBeautyID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBeautyFeature::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wBeautyID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#带Buff的玩家信息
class SPlayerFeatureWithBuff < SFeatureBase
	attr_accessor:strName #(string)玩家姓名
	attr_accessor:eJob #(枚类型：ProtoCommon::ECareerType)职业
	attr_accessor:eSex #(枚类型：ProtoCommon::ESexType)性别
	attr_accessor:vEquip #(SEquipShowInfo的数组)装备
	attr_accessor:vecTitle #(STitleAppear的数组)头衔
	attr_accessor:strGuildName #(string)帮派名称
	attr_accessor:byQuality #(UINT8)品质
	attr_accessor:byDujieLevel #(UINT8)散仙渡劫等级
	attr_accessor:byVIPLevel #(UINT8)VIP等级
	attr_accessor:vecBuffInfo #(SBattleBuffInfo的数组)战斗外的Buff信息

	#构造函数
	def initialize
		super()
		@strName = ''
		@eJob = 0
		@eSex = 0
		@vEquip = Array.new
		@vecTitle = Array.new
		@strGuildName = ''
		@byQuality = 0
		@byDujieLevel = 0
		@byVIPLevel = 0
		@vecBuffInfo = Array.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SFeatureBase::ETYPE_SPLAYERFEATUREWITHBUFF
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.strName = @strName
		obj.eJob = @eJob
		obj.eSex = @eSex
		obj.vEquip = @vEquip
		obj.vecTitle = @vecTitle
		obj.strGuildName = @strGuildName
		obj.byQuality = @byQuality
		obj.byDujieLevel = @byDujieLevel
		obj.byVIPLevel = @byVIPLevel
		obj.vecBuffInfo = @vecBuffInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPlayerFeatureWithBuff.new
		base = SFeatureBase::fromStream(data)
		base.copyTo(s)
		s.strName = ByteUtil::readSTRING(data)
		s.eJob = ByteUtil::readUINT8(data)
		s.eSex = ByteUtil::readUINT8(data)
		s.vEquip = SEquipShowInfo::vectorFromStream(data)
		s.vecTitle = STitleAppear::vectorFromStream(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.byDujieLevel = ByteUtil::readUINT8(data)
		s.byVIPLevel = ByteUtil::readUINT8(data)
		s.vecBuffInfo = SBattleBuffInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPlayerFeatureWithBuff::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @eJob)
		ByteUtil::writeUINT8(data, @eSex)
		SEquipShowInfo::vectorToStream(data, @vEquip)
		STitleAppear::vectorToStream(data, @vecTitle)
		ByteUtil::writeSTRING(data, @strGuildName)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT8(data, @byDujieLevel)
		ByteUtil::writeUINT8(data, @byVIPLevel)
		SBattleBuffInfo::vectorToStream(data, @vecBuffInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#带Buff的怪物信息
class SMonsterFeatureWithBuff < SFeatureBase
	attr_accessor:wMonsterID #(UINT16)配置表里面的英雄ID，根据ID可以取到怪物外观资源
	attr_accessor:vecBuffInfo #(SBattleBuffInfo的数组)战斗外的Buff信息

	#构造函数
	def initialize
		super()
		@wMonsterID = 0
		@vecBuffInfo = Array.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SFeatureBase::ETYPE_SMONSTERFEATUREWITHBUFF
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wMonsterID = @wMonsterID
		obj.vecBuffInfo = @vecBuffInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMonsterFeatureWithBuff.new
		base = SFeatureBase::fromStream(data)
		base.copyTo(s)
		s.wMonsterID = ByteUtil::readUINT16(data)
		s.vecBuffInfo = SBattleBuffInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMonsterFeatureWithBuff::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wMonsterID)
		SBattleBuffInfo::vectorToStream(data, @vecBuffInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#参与战斗的技能信息
class SBattleFightSkillInfo
	attr_accessor:dwSkillID #(UINT32)技能ID
	attr_accessor:dwSymboleID #(UINT32)符文ID

	#构造函数
	def initialize
		@dwSkillID = 0
		@dwSymboleID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwSkillID = @dwSkillID
		obj.dwSymboleID = @dwSymboleID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleFightSkillInfo.new
		s.dwSkillID = ByteUtil::readUINT32(data)
		s.dwSymboleID = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleFightSkillInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwSkillID)
		ByteUtil::writeUINT32(data, @dwSymboleID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#队伍技能
class STeamSkillInfo
	attr_accessor:byIndex #(UINT8)队伍技能唯一编号
	attr_accessor:byTeamID #(UINT8)队伍ID
	attr_accessor:dwSkillID #(UINT32)技能ID

	#构造函数
	def initialize
		@byIndex = 0
		@byTeamID = 0
		@dwSkillID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byIndex = @byIndex
		obj.byTeamID = @byTeamID
		obj.dwSkillID = @dwSkillID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STeamSkillInfo.new
		s.byIndex = ByteUtil::readUINT8(data)
		s.byTeamID = ByteUtil::readUINT8(data)
		s.dwSkillID = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STeamSkillInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byIndex)
		ByteUtil::writeUINT8(data, @byTeamID)
		ByteUtil::writeUINT32(data, @dwSkillID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战斗者信息
class SBattleFighterInfo
	attr_accessor:qwInstID #(UINT64)将唯一ID
	attr_accessor:wFighterID #(UINT16)将类型ID
	attr_accessor:iPos #(INT32)将位置
	attr_accessor:byTeamID #(UINT8)所属队伍ID
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:strName #(string)将名字
	attr_accessor:eSex #(枚类型：ProtoCommon::ESexType)将性别
	attr_accessor:eCareer #(枚类型：ProtoCommon::ECareerType)将职业
	attr_accessor:dwHpMax #(UINT32)最大血量
	attr_accessor:dwHp #(UINT32)当前血量
	attr_accessor:dwAura #(UINT32)当前灵气
	attr_accessor:dwAuraMax #(UINT32)最大灵气
	attr_accessor:oAttrVec #(SFtAttrMod的数组)最终属性
	attr_accessor:vActiveSkill #(SBattleFightSkillInfo的数组)装备的主动技能
	attr_accessor:vPassiveSkill #(SBattleFightSkillInfo的数组)被动技能
	attr_accessor:oPeerLees #(类类型：SBattleFightSkillInfo)无双技能
	attr_accessor:oPeerLeesEx #(类类型：SBattleFightSkillInfo)变身后无双技能
	attr_accessor:pFeature #(类类型：SFeatureBase)外观信息

	#构造函数
	def initialize
		@qwInstID = 0
		@wFighterID = 0
		@iPos = 0
		@byTeamID = 0
		@byLevel = 0
		@strName = ''
		@eSex = 0
		@eCareer = 0
		@dwHpMax = 0
		@dwHp = 0
		@dwAura = 0
		@dwAuraMax = 0
		@oAttrVec = Array.new
		@vActiveSkill = Array.new
		@vPassiveSkill = Array.new
		@oPeerLees = SBattleFightSkillInfo.new
		@oPeerLeesEx = SBattleFightSkillInfo.new
		@pFeature = SFeatureBase.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInstID = @qwInstID
		obj.wFighterID = @wFighterID
		obj.iPos = @iPos
		obj.byTeamID = @byTeamID
		obj.byLevel = @byLevel
		obj.strName = @strName
		obj.eSex = @eSex
		obj.eCareer = @eCareer
		obj.dwHpMax = @dwHpMax
		obj.dwHp = @dwHp
		obj.dwAura = @dwAura
		obj.dwAuraMax = @dwAuraMax
		obj.oAttrVec = @oAttrVec
		obj.vActiveSkill = @vActiveSkill
		obj.vPassiveSkill = @vPassiveSkill
		obj.oPeerLees = @oPeerLees
		obj.oPeerLeesEx = @oPeerLeesEx
		obj.pFeature = @pFeature
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleFighterInfo.new
		s.qwInstID = ByteUtil::readUINT64(data)
		s.wFighterID = ByteUtil::readUINT16(data)
		s.iPos = ByteUtil::readINT32(data)
		s.byTeamID = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.strName = ByteUtil::readSTRING(data)
		s.eSex = ByteUtil::readUINT8(data)
		s.eCareer = ByteUtil::readUINT8(data)
		s.dwHpMax = ByteUtil::readUINT32(data)
		s.dwHp = ByteUtil::readUINT32(data)
		s.dwAura = ByteUtil::readUINT32(data)
		s.dwAuraMax = ByteUtil::readUINT32(data)
		s.oAttrVec = SFtAttrMod::vectorFromStream(data)
		s.vActiveSkill = SBattleFightSkillInfo::vectorFromStream(data)
		s.vPassiveSkill = SBattleFightSkillInfo::vectorFromStream(data)
		s.oPeerLees = SBattleFightSkillInfo::fromStream(data)
		s.oPeerLeesEx = SBattleFightSkillInfo::fromStream(data)
		s.pFeature = SFeatureBase::superFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleFighterInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeINT32(data, @iPos)
		ByteUtil::writeUINT8(data, @byTeamID)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @eSex)
		ByteUtil::writeUINT8(data, @eCareer)
		ByteUtil::writeUINT32(data, @dwHpMax)
		ByteUtil::writeUINT32(data, @dwHp)
		ByteUtil::writeUINT32(data, @dwAura)
		ByteUtil::writeUINT32(data, @dwAuraMax)
		SFtAttrMod::vectorToStream(data, @oAttrVec)
		SBattleFightSkillInfo::vectorToStream(data, @vActiveSkill)
		SBattleFightSkillInfo::vectorToStream(data, @vPassiveSkill)
		@oPeerLees.toStream(data)
		@oPeerLeesEx.toStream(data)
		@pFeature.superToStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#Fighter信息
class SBattleFighter
	attr_accessor:byFighterID #(UINT8)战场开始之后分配的唯一ID，groupID*5*5+pos
	attr_accessor:oFgtInfo #(类类型：SBattleFighterInfo)FighterInfo

	#构造函数
	def initialize
		@byFighterID = 0
		@oFgtInfo = SBattleFighterInfo.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byFighterID = @byFighterID
		obj.oFgtInfo = @oFgtInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleFighter.new
		s.byFighterID = ByteUtil::readUINT8(data)
		s.oFgtInfo = SBattleFighterInfo::fromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleFighter::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byFighterID)
		@oFgtInfo.toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战斗小队
class SBattleGroup
	attr_accessor:byGroupID #(UINT8)组ID
	attr_accessor:qwCreatrueID #(UINT64)玩家ID，地图上跑的时候用的那个ID，怪物为0
	attr_accessor:qwLeaderID #(UINT64)队伍主将ID
	attr_accessor:wLevel #(UINT16)队伍等级
	attr_accessor:vFighters #(SBattleFighter的数组)队伍里面的所有fighter
	attr_accessor:vecCombineSkillInfo #(STeamSkillInfo的数组)队伍中的连携技能
	attr_accessor:pMainFeature #(类类型：SFeatureBase)主将外观信息(用于显示头像用)
	attr_accessor:dwBattlePoint #(UINT32)战斗力

	#构造函数
	def initialize
		@byGroupID = 0
		@qwCreatrueID = 0
		@qwLeaderID = 0
		@wLevel = 0
		@vFighters = Array.new
		@vecCombineSkillInfo = Array.new
		@pMainFeature = SFeatureBase.new
		@dwBattlePoint = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byGroupID = @byGroupID
		obj.qwCreatrueID = @qwCreatrueID
		obj.qwLeaderID = @qwLeaderID
		obj.wLevel = @wLevel
		obj.vFighters = @vFighters
		obj.vecCombineSkillInfo = @vecCombineSkillInfo
		obj.pMainFeature = @pMainFeature
		obj.dwBattlePoint = @dwBattlePoint
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleGroup.new
		s.byGroupID = ByteUtil::readUINT8(data)
		s.qwCreatrueID = ByteUtil::readUINT64(data)
		s.qwLeaderID = ByteUtil::readUINT64(data)
		s.wLevel = ByteUtil::readUINT16(data)
		s.vFighters = SBattleFighter::vectorFromStream(data)
		s.vecCombineSkillInfo = STeamSkillInfo::vectorFromStream(data)
		s.pMainFeature = SFeatureBase::superFromStream(data)
		s.dwBattlePoint = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleGroup::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byGroupID)
		ByteUtil::writeUINT64(data, @qwCreatrueID)
		ByteUtil::writeUINT64(data, @qwLeaderID)
		ByteUtil::writeUINT16(data, @wLevel)
		SBattleFighter::vectorToStream(data, @vFighters)
		STeamSkillInfo::vectorToStream(data, @vecCombineSkillInfo)
		@pMainFeature.superToStream(data)
		ByteUtil::writeUINT32(data, @dwBattlePoint)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战斗基础效果类型
class SEffectBase
	attr_accessor:vecFighterID #(UINT8数组)表现这个效果的fighter(255表示为场景)

	#构造函数
	def initialize
		@vecFighterID = Array.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTBASE
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.vecFighterID = @vecFighterID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectBase.new
		s.vecFighterID = ByteUtil::readVecUINT8(data)
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_SEffectBase::ETYPE_SEFFECTBASE
				s = SEffectBase::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTDECHP
				s = SEffectDecHP::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTADDSTATUS
				s = SEffectAddStatus::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTADDHP
				s = SEffectAddHP::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTRELIVE
				s = SEffectRelive::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTCOUNTER
				s = SEffectCounter::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTSTATEBUFFADD
				s = SEffectStateBuffAdd::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTSTATEBUFFEFFECT
				s = SEffectStateBuffEffect::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTSTATEBUFFDEC
				s = SEffectStateBuffDec::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTSTATEBUFFLAST
				s = SEffectStateBuffLast::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTATTRBUFFADD
				s = SEffectAttrBuffAdd::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTATTRBUFFDEC
				s = SEffectAttrBuffDec::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTDIED
				s = SEffectDied::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTSHIELDABSORB
				s = SEffectShieldAbsorb::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTTRIGGEREXECUTE
				s = SEffectTriggerExecute::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTSYCHP
				s = SEffectSycHP::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTSYCAURA
				s = SEffectSycAura::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTSYCCOMBINE
				s = SEffectSycCombine::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTCOMBINESLOT
				s = SEffectCombineSlot::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTBROKENSHIELD
				s = SEffectBrokenShield::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTSUMMON
				s = SEffectSummon::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTDIALOG
				s = SEffectDialog::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTTRANSFORM
				s = SEffectTransform::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTPARTBROKEN
				s = SEffectPartBroken::fromStream(data)
			when EType_SEffectBase::ETYPE_SEFFECTBUFFACTION
				s = SEffectBuffAction::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectBase::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectBase::superFromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeVecUINT8(data, @vecFighterID)
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

#扣血
class SEffectDecHP < SEffectBase
	attr_accessor:dwSkillID #(UINT32)扣血对应ID
	attr_accessor:eSubHPType #(枚举类型：EBSubHPType)扣血伤害类型（物理/法术）
	attr_accessor:eHPType #(枚举类型：EBModifyHPType)扣血类型
	attr_accessor:dwDecHP #(UINT32)扣掉的血

	#构造函数
	def initialize
		super()
		@dwSkillID = 0
		@eSubHPType = 0
		@eHPType = 0
		@dwDecHP = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTDECHP
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwSkillID = @dwSkillID
		obj.eSubHPType = @eSubHPType
		obj.eHPType = @eHPType
		obj.dwDecHP = @dwDecHP
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectDecHP.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.dwSkillID = ByteUtil::readUINT32(data)
		s.eSubHPType = ByteUtil::readUINT8(data)
		s.eHPType = ByteUtil::readUINT8(data)
		s.dwDecHP = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectDecHP::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwSkillID)
		ByteUtil::writeUINT8(data, @eSubHPType)
		ByteUtil::writeUINT8(data, @eHPType)
		ByteUtil::writeUINT32(data, @dwDecHP)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#一个UINT32参数的效果
class SEffectAddStatus < SEffectBase
	attr_accessor:eStatus #(枚举类型：EBStatusType)状态类型

	#构造函数
	def initialize
		super()
		@eStatus = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTADDSTATUS
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.eStatus = @eStatus
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectAddStatus.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.eStatus = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectAddStatus::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @eStatus)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#加血
class SEffectAddHP < SEffectBase
	attr_accessor:dwSkillID #(UINT32)加血对应ID
	attr_accessor:eHPType #(枚举类型：EBModifyHPType)加血类型
	attr_accessor:dwAddHP #(UINT32)增加的血量

	#构造函数
	def initialize
		super()
		@dwSkillID = 0
		@eHPType = 0
		@dwAddHP = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTADDHP
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwSkillID = @dwSkillID
		obj.eHPType = @eHPType
		obj.dwAddHP = @dwAddHP
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectAddHP.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.dwSkillID = ByteUtil::readUINT32(data)
		s.eHPType = ByteUtil::readUINT8(data)
		s.dwAddHP = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectAddHP::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwSkillID)
		ByteUtil::writeUINT8(data, @eHPType)
		ByteUtil::writeUINT32(data, @dwAddHP)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#重生
class SEffectRelive < SEffectBase
	attr_accessor:byGroupID #(UINT8)组编号
	attr_accessor:bySide #(UINT8)方向编号
	attr_accessor:byPos #(UINT8)位置编号
	attr_accessor:wFighterID #(UINT16)散仙ID
	attr_accessor:dwHpMax #(UINT32)最大血量
	attr_accessor:dwHp #(UINT32)当前血量
	attr_accessor:dwAura #(UINT32)当前灵气
	attr_accessor:dwAuraMax #(UINT32)最大灵气

	#构造函数
	def initialize
		super()
		@byGroupID = 0
		@bySide = 0
		@byPos = 0
		@wFighterID = 0
		@dwHpMax = 0
		@dwHp = 0
		@dwAura = 0
		@dwAuraMax = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTRELIVE
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.byGroupID = @byGroupID
		obj.bySide = @bySide
		obj.byPos = @byPos
		obj.wFighterID = @wFighterID
		obj.dwHpMax = @dwHpMax
		obj.dwHp = @dwHp
		obj.dwAura = @dwAura
		obj.dwAuraMax = @dwAuraMax
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectRelive.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.byGroupID = ByteUtil::readUINT8(data)
		s.bySide = ByteUtil::readUINT8(data)
		s.byPos = ByteUtil::readUINT8(data)
		s.wFighterID = ByteUtil::readUINT16(data)
		s.dwHpMax = ByteUtil::readUINT32(data)
		s.dwHp = ByteUtil::readUINT32(data)
		s.dwAura = ByteUtil::readUINT32(data)
		s.dwAuraMax = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectRelive::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @byGroupID)
		ByteUtil::writeUINT8(data, @bySide)
		ByteUtil::writeUINT8(data, @byPos)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT32(data, @dwHpMax)
		ByteUtil::writeUINT32(data, @dwHp)
		ByteUtil::writeUINT32(data, @dwAura)
		ByteUtil::writeUINT32(data, @dwAuraMax)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#反击
class SEffectCounter < SEffectBase
	attr_accessor:eSubHPType #(枚举类型：EBSubHPType)扣血伤害类型（物理/法术）
	attr_accessor:eHPType #(枚举类型：EBModifyHPType)扣血类型
	attr_accessor:dwDecHP #(UINT32)反击的伤害量

	#构造函数
	def initialize
		super()
		@eSubHPType = 0
		@eHPType = 0
		@dwDecHP = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTCOUNTER
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.eSubHPType = @eSubHPType
		obj.eHPType = @eHPType
		obj.dwDecHP = @dwDecHP
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectCounter.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.eSubHPType = ByteUtil::readUINT8(data)
		s.eHPType = ByteUtil::readUINT8(data)
		s.dwDecHP = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectCounter::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @eSubHPType)
		ByteUtil::writeUINT8(data, @eHPType)
		ByteUtil::writeUINT32(data, @dwDecHP)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#加状态Buff
class SEffectStateBuffAdd < SEffectBase
	attr_accessor:dwBuffKey #(UINT32)查找这个buff的唯一ID
	attr_accessor:eStateBuffType #(枚举类型：EBStateBuffType)状态枚举
	attr_accessor:dwSkillID #(UINT32)该Buff的技能来源
	attr_accessor:dwBaseSkillID #(UINT32)初始技能ID（SkillBase表的ID）
	attr_accessor:byLast #(UINT8)持续时间
	attr_accessor:dwValue #(INT32)该Buff的效果值

	#构造函数
	def initialize
		super()
		@dwBuffKey = 0
		@eStateBuffType = 0
		@dwSkillID = 0
		@dwBaseSkillID = 0
		@byLast = 0
		@dwValue = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTSTATEBUFFADD
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwBuffKey = @dwBuffKey
		obj.eStateBuffType = @eStateBuffType
		obj.dwSkillID = @dwSkillID
		obj.dwBaseSkillID = @dwBaseSkillID
		obj.byLast = @byLast
		obj.dwValue = @dwValue
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectStateBuffAdd.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.dwBuffKey = ByteUtil::readUINT32(data)
		s.eStateBuffType = ByteUtil::readUINT16(data)
		s.dwSkillID = ByteUtil::readUINT32(data)
		s.dwBaseSkillID = ByteUtil::readUINT32(data)
		s.byLast = ByteUtil::readUINT8(data)
		s.dwValue = ByteUtil::readINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectStateBuffAdd::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwBuffKey)
		ByteUtil::writeUINT16(data, @eStateBuffType)
		ByteUtil::writeUINT32(data, @dwSkillID)
		ByteUtil::writeUINT32(data, @dwBaseSkillID)
		ByteUtil::writeUINT8(data, @byLast)
		ByteUtil::writeINT32(data, @dwValue)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#状态Buff生效
class SEffectStateBuffEffect < SEffectBase
	attr_accessor:dwBuffKey #(UINT32)查找这个Buff的唯一ID

	#构造函数
	def initialize
		super()
		@dwBuffKey = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTSTATEBUFFEFFECT
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwBuffKey = @dwBuffKey
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectStateBuffEffect.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.dwBuffKey = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectStateBuffEffect::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwBuffKey)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#减状态Buff
class SEffectStateBuffDec < SEffectBase
	attr_accessor:dwBuffKey #(UINT32)查找这个Buff的唯一ID

	#构造函数
	def initialize
		super()
		@dwBuffKey = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTSTATEBUFFDEC
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwBuffKey = @dwBuffKey
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectStateBuffDec.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.dwBuffKey = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectStateBuffDec::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwBuffKey)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#Buff持续时间
class SEffectStateBuffLast < SEffectBase
	attr_accessor:dwBuffKey #(UINT32)查找这个Buff的唯一ID
	attr_accessor:byLast #(UINT8)持续时间

	#构造函数
	def initialize
		super()
		@dwBuffKey = 0
		@byLast = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTSTATEBUFFLAST
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwBuffKey = @dwBuffKey
		obj.byLast = @byLast
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectStateBuffLast.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.dwBuffKey = ByteUtil::readUINT32(data)
		s.byLast = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectStateBuffLast::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwBuffKey)
		ByteUtil::writeUINT8(data, @byLast)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#加修改人物属性buff
class SEffectAttrBuffAdd < SEffectBase
	attr_accessor:eBuffType #(枚类型：ProtoCommon::EFighterAttr)修改的属性枚举
	attr_accessor:dwBuffKey #(UINT32)查找这个buff的唯一ID
	attr_accessor:dwSkillID #(UINT32)该Buff的技能来源
	attr_accessor:byLast #(UINT8)持续时间
	attr_accessor:dwValue #(INT32)该Buff的效果值

	#构造函数
	def initialize
		super()
		@eBuffType = 0
		@dwBuffKey = 0
		@dwSkillID = 0
		@byLast = 0
		@dwValue = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTATTRBUFFADD
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.eBuffType = @eBuffType
		obj.dwBuffKey = @dwBuffKey
		obj.dwSkillID = @dwSkillID
		obj.byLast = @byLast
		obj.dwValue = @dwValue
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectAttrBuffAdd.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.eBuffType = ByteUtil::readUINT8(data)
		s.dwBuffKey = ByteUtil::readUINT32(data)
		s.dwSkillID = ByteUtil::readUINT32(data)
		s.byLast = ByteUtil::readUINT8(data)
		s.dwValue = ByteUtil::readINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectAttrBuffAdd::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @eBuffType)
		ByteUtil::writeUINT32(data, @dwBuffKey)
		ByteUtil::writeUINT32(data, @dwSkillID)
		ByteUtil::writeUINT8(data, @byLast)
		ByteUtil::writeINT32(data, @dwValue)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#减修改人物属性buff
class SEffectAttrBuffDec < SEffectBase
	attr_accessor:dwBuffKey #(UINT32)查找这个buff的唯一ID

	#构造函数
	def initialize
		super()
		@dwBuffKey = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTATTRBUFFDEC
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwBuffKey = @dwBuffKey
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectAttrBuffDec.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.dwBuffKey = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectAttrBuffDec::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwBuffKey)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#我死了
class SEffectDied < SEffectBase
	attr_accessor:dwSkillID #(UINT32)死亡时动画技能ID

	#构造函数
	def initialize
		super()
		@dwSkillID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTDIED
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwSkillID = @dwSkillID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectDied.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.dwSkillID = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectDied::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwSkillID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#盾牌吸收伤害
class SEffectShieldAbsorb < SEffectBase
	attr_accessor:eType #(枚举类型：EBSheildAbsorbType)吸收类型
	attr_accessor:dwHP #(UINT32)吸收的数值

	#构造函数
	def initialize
		super()
		@eType = 0
		@dwHP = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTSHIELDABSORB
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.eType = @eType
		obj.dwHP = @dwHP
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectShieldAbsorb.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.eType = ByteUtil::readUINT8(data)
		s.dwHP = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectShieldAbsorb::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @eType)
		ByteUtil::writeUINT32(data, @dwHP)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#被动触发执行
class SEffectTriggerExecute < SEffectBase
	attr_accessor:dwSkillID #(UINT32)技能ID

	#构造函数
	def initialize
		super()
		@dwSkillID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTTRIGGEREXECUTE
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwSkillID = @dwSkillID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectTriggerExecute.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.dwSkillID = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectTriggerExecute::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwSkillID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#同步血量和血上限
class SEffectSycHP < SEffectBase
	attr_accessor:dwHP #(UINT32)当前血量
	attr_accessor:dwHPMax #(UINT32)当前血上限

	#构造函数
	def initialize
		super()
		@dwHP = 0
		@dwHPMax = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTSYCHP
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwHP = @dwHP
		obj.dwHPMax = @dwHPMax
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectSycHP.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.dwHP = ByteUtil::readUINT32(data)
		s.dwHPMax = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectSycHP::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwHP)
		ByteUtil::writeUINT32(data, @dwHPMax)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#同步灵气
class SEffectSycAura < SEffectBase
	attr_accessor:iAura #(INT32)当前怒气值

	#构造函数
	def initialize
		super()
		@iAura = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTSYCAURA
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.iAura = @iAura
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectSycAura.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.iAura = ByteUtil::readINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectSycAura::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeINT32(data, @iAura)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#同步连携值
class SEffectSycCombine < SEffectBase
	attr_accessor:iCombine #(INT32)当前连携值
	attr_accessor:vecSycType #(UINT8数组)更改方式（见ECombineType）)

	#构造函数
	def initialize
		super()
		@iCombine = 0
		@vecSycType = Array.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTSYCCOMBINE
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.iCombine = @iCombine
		obj.vecSycType = @vecSycType
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectSycCombine.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.iCombine = ByteUtil::readINT32(data)
		s.vecSycType = ByteUtil::readVecUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectSycCombine::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeINT32(data, @iCombine)
		ByteUtil::writeVecUINT8(data, @vecSycType)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#连携槽相关操作效果
class SEffectCombineSlot < SEffectBase
	attr_accessor:eType #(枚举类型：ECombineSlotOPType)操作方式

	#构造函数
	def initialize
		super()
		@eType = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTCOMBINESLOT
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.eType = @eType
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectCombineSlot.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.eType = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectCombineSlot::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @eType)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#破盾效果
class SEffectBrokenShield < SEffectBase
	attr_accessor:iPoint #(INT32)盾牌耐久扣减值

	#构造函数
	def initialize
		super()
		@iPoint = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTBROKENSHIELD
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.iPoint = @iPoint
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectBrokenShield.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.iPoint = ByteUtil::readINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectBrokenShield::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeINT32(data, @iPoint)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#召唤效果
class SEffectSummon < SEffectBase
	attr_accessor:byGroupID #(UINT8)组编号
	attr_accessor:bySide #(UINT8)方向编号
	attr_accessor:byPos #(UINT8)位置编号
	attr_accessor:wFighterID #(UINT16)散仙ID
	attr_accessor:dwHpMax #(UINT32)最大血量
	attr_accessor:dwHp #(UINT32)当前血量
	attr_accessor:dwAura #(UINT32)当前灵气
	attr_accessor:dwAuraMax #(UINT32)最大灵气

	#构造函数
	def initialize
		super()
		@byGroupID = 0
		@bySide = 0
		@byPos = 0
		@wFighterID = 0
		@dwHpMax = 0
		@dwHp = 0
		@dwAura = 0
		@dwAuraMax = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTSUMMON
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.byGroupID = @byGroupID
		obj.bySide = @bySide
		obj.byPos = @byPos
		obj.wFighterID = @wFighterID
		obj.dwHpMax = @dwHpMax
		obj.dwHp = @dwHp
		obj.dwAura = @dwAura
		obj.dwAuraMax = @dwAuraMax
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectSummon.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.byGroupID = ByteUtil::readUINT8(data)
		s.bySide = ByteUtil::readUINT8(data)
		s.byPos = ByteUtil::readUINT8(data)
		s.wFighterID = ByteUtil::readUINT16(data)
		s.dwHpMax = ByteUtil::readUINT32(data)
		s.dwHp = ByteUtil::readUINT32(data)
		s.dwAura = ByteUtil::readUINT32(data)
		s.dwAuraMax = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectSummon::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @byGroupID)
		ByteUtil::writeUINT8(data, @bySide)
		ByteUtil::writeUINT8(data, @byPos)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT32(data, @dwHpMax)
		ByteUtil::writeUINT32(data, @dwHp)
		ByteUtil::writeUINT32(data, @dwAura)
		ByteUtil::writeUINT32(data, @dwAuraMax)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#对话效果
class SEffectDialog < SEffectBase
	attr_accessor:dwID #(UINT32)对话ID

	#构造函数
	def initialize
		super()
		@dwID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTDIALOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwID = @dwID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectDialog.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.dwID = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectDialog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#变身效果
class SEffectTransform < SEffectBase
	attr_accessor:wFeatureID #(UINT16)模型ID

	#构造函数
	def initialize
		super()
		@wFeatureID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTTRANSFORM
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wFeatureID = @wFeatureID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectTransform.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.wFeatureID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectTransform::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wFeatureID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#部位破坏
class SEffectPartBroken < SEffectBase
	attr_accessor:wPartID #(UINT16)部位ID

	#构造函数
	def initialize
		super()
		@wPartID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTPARTBROKEN
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wPartID = @wPartID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectPartBroken.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.wPartID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectPartBroken::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wPartID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#被动技能出手动作
class SEffectBuffAction < SEffectBase
	attr_accessor:dwSkillID #(UINT32)技能ID

	#构造函数
	def initialize
		super()
		@dwSkillID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SEffectBase::ETYPE_SEFFECTBUFFACTION
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dwSkillID = @dwSkillID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEffectBuffAction.new
		base = SEffectBase::fromStream(data)
		base.copyTo(s)
		s.dwSkillID = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEffectBuffAction::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwSkillID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#目标位置，由组ID和位置唯一能找到坐标
class SBattleTargetPos
	attr_accessor:byGroupID #(UINT8)组ID
	attr_accessor:byPos #(UINT8)位置ID

	#构造函数
	def initialize
		@byGroupID = 0
		@byPos = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byGroupID = @byGroupID
		obj.byPos = @byPos
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleTargetPos.new
		s.byGroupID = ByteUtil::readUINT8(data)
		s.byPos = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleTargetPos::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byGroupID)
		ByteUtil::writeUINT8(data, @byPos)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#某个fighter一次出手
class SBattleProgress
	attr_accessor:vecCasterIndex #(UINT8数组)主犯(255代表入场技能或者场景技能
	attr_accessor:vEffectsBefore #(SEffectBase的数组)主犯施法前的效果列表
	attr_accessor:dwSkillID #(UINT32)技能ID
	attr_accessor:vTargetID #(UINT8数组)所有目标ID
	attr_accessor:vTargetIDEx #(UINT8数组)波及目标ID
	attr_accessor:vTargetPos #(SBattleTargetPos的数组)技能主执行覆盖区域位置
	attr_accessor:vSkillEffects #(SEffectBase的数组)技能效果列表
	attr_accessor:vEffectsAfter #(SEffectBase的数组)主犯施法后效果列表

	#构造函数
	def initialize
		@vecCasterIndex = Array.new
		@vEffectsBefore = Array.new
		@dwSkillID = 0
		@vTargetID = Array.new
		@vTargetIDEx = Array.new
		@vTargetPos = Array.new
		@vSkillEffects = Array.new
		@vEffectsAfter = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.vecCasterIndex = @vecCasterIndex
		obj.vEffectsBefore = @vEffectsBefore
		obj.dwSkillID = @dwSkillID
		obj.vTargetID = @vTargetID
		obj.vTargetIDEx = @vTargetIDEx
		obj.vTargetPos = @vTargetPos
		obj.vSkillEffects = @vSkillEffects
		obj.vEffectsAfter = @vEffectsAfter
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleProgress.new
		s.vecCasterIndex = ByteUtil::readVecUINT8(data)
		s.vEffectsBefore = SEffectBase::superVectorFromStream(data)
		s.dwSkillID = ByteUtil::readUINT32(data)
		s.vTargetID = ByteUtil::readVecUINT8(data)
		s.vTargetIDEx = ByteUtil::readVecUINT8(data)
		s.vTargetPos = SBattleTargetPos::vectorFromStream(data)
		s.vSkillEffects = SEffectBase::superVectorFromStream(data)
		s.vEffectsAfter = SEffectBase::superVectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleProgress::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeVecUINT8(data, @vecCasterIndex)
		SEffectBase::superVectorToStream(data, @vEffectsBefore)
		ByteUtil::writeUINT32(data, @dwSkillID)
		ByteUtil::writeVecUINT8(data, @vTargetID)
		ByteUtil::writeVecUINT8(data, @vTargetIDEx)
		SBattleTargetPos::vectorToStream(data, @vTargetPos)
		SEffectBase::superVectorToStream(data, @vSkillEffects)
		SEffectBase::superVectorToStream(data, @vEffectsAfter)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#一个回合（所有队伍都出手一次）
class SBattleRound
	attr_accessor:dwRounds #(UINT32)当前回合数
	attr_accessor:vTargets #(SBattleProgress的数组)其它人出手

	#构造函数
	def initialize
		@dwRounds = 0
		@vTargets = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwRounds = @dwRounds
		obj.vTargets = @vTargets
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleRound.new
		s.dwRounds = ByteUtil::readUINT32(data)
		s.vTargets = SBattleProgress::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleRound::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwRounds)
		SBattleProgress::vectorToStream(data, @vTargets)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战报
class SBattleReport
	attr_accessor:qwBattleID #(UINT64)战报ID
	attr_accessor:qwNextBattleID #(UINT64)next战报ID
	attr_accessor:wSceneID #(UINT16)战斗场景ID
	attr_accessor:by1Vs1 #(UINT8)0:普通一打多，1：普通一打一，2：boss一打多， 3：boss一打一
	attr_accessor:eType #(枚举类型：EBattleType)战斗模式：PVP/PVE
	attr_accessor:vAGroups #(SBattleGroup的数组)A队伍里的所有小组
	attr_accessor:vBGroups #(SBattleGroup的数组)B队伍里的所有小组
	attr_accessor:vSummons #(SBattleFighter的数组)战斗中可能召唤的散仙
	attr_accessor:vRound #(SBattleRound的数组)所有的出手回合
	attr_accessor:byAWaves #(UINT8)A队剩余波数
	attr_accessor:byBWaves #(UINT8)B队剩余波数
	attr_accessor:eResult #(枚举类型：EBattleResult)战斗结果
	attr_accessor:vecItem #(SItemGenInfo的数组)获得物品
	attr_accessor:vecResSource #(SResource的数组)获得资源

	#构造函数
	def initialize
		@qwBattleID = 0
		@qwNextBattleID = 0
		@wSceneID = 0
		@by1Vs1 = 0
		@eType = 0
		@vAGroups = Array.new
		@vBGroups = Array.new
		@vSummons = Array.new
		@vRound = Array.new
		@byAWaves = 0
		@byBWaves = 0
		@eResult = 0
		@vecItem = Array.new
		@vecResSource = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwBattleID = @qwBattleID
		obj.qwNextBattleID = @qwNextBattleID
		obj.wSceneID = @wSceneID
		obj.by1Vs1 = @by1Vs1
		obj.eType = @eType
		obj.vAGroups = @vAGroups
		obj.vBGroups = @vBGroups
		obj.vSummons = @vSummons
		obj.vRound = @vRound
		obj.byAWaves = @byAWaves
		obj.byBWaves = @byBWaves
		obj.eResult = @eResult
		obj.vecItem = @vecItem
		obj.vecResSource = @vecResSource
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleReport.new
		s.qwBattleID = ByteUtil::readUINT64(data)
		s.qwNextBattleID = ByteUtil::readUINT64(data)
		s.wSceneID = ByteUtil::readUINT16(data)
		s.by1Vs1 = ByteUtil::readUINT8(data)
		s.eType = ByteUtil::readUINT8(data)
		s.vAGroups = SBattleGroup::vectorFromStream(data)
		s.vBGroups = SBattleGroup::vectorFromStream(data)
		s.vSummons = SBattleFighter::vectorFromStream(data)
		s.vRound = SBattleRound::vectorFromStream(data)
		s.byAWaves = ByteUtil::readUINT8(data)
		s.byBWaves = ByteUtil::readUINT8(data)
		s.eResult = ByteUtil::readUINT8(data)
		s.vecItem = SItemGenInfo::vectorFromStream(data)
		s.vecResSource = SResource::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleReport::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwBattleID)
		ByteUtil::writeUINT64(data, @qwNextBattleID)
		ByteUtil::writeUINT16(data, @wSceneID)
		ByteUtil::writeUINT8(data, @by1Vs1)
		ByteUtil::writeUINT8(data, @eType)
		SBattleGroup::vectorToStream(data, @vAGroups)
		SBattleGroup::vectorToStream(data, @vBGroups)
		SBattleFighter::vectorToStream(data, @vSummons)
		SBattleRound::vectorToStream(data, @vRound)
		ByteUtil::writeUINT8(data, @byAWaves)
		ByteUtil::writeUINT8(data, @byBWaves)
		ByteUtil::writeUINT8(data, @eResult)
		SItemGenInfo::vectorToStream(data, @vecItem)
		SResource::vectorToStream(data, @vecResSource)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战报
class NewSBattleReport
	attr_accessor:qwHash #(UINT64)新版本战报校验字段(应该始终为0xFFFFFFFF)

	#构造函数
	def initialize
		@qwHash = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_NewSBattleReport::ETYPE_NEWSBATTLEREPORT
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwHash = @qwHash
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = NewSBattleReport.new
		s.qwHash = ByteUtil::readUINT64(data)
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_NewSBattleReport::ETYPE_NEWSBATTLEREPORT
				s = NewSBattleReport::fromStream(data)
			when EType_NewSBattleReport::ETYPE_NEWSBATTLEREPORTV1
				s = NewSBattleReportV1::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = NewSBattleReport::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = NewSBattleReport::superFromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwHash)
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

#版本1战报
class NewSBattleReportV1 < NewSBattleReport
	attr_accessor:qwBattleID #(UINT64)战报ID
	attr_accessor:qwNextBattleID #(UINT64)next战报ID
	attr_accessor:wSceneID #(UINT16)战斗场景ID
	attr_accessor:by1Vs1 #(UINT8)0:普通一打多，1：普通一打一，2：boss一打多， 3：boss一打一
	attr_accessor:eType #(枚举类型：EBattleType)战斗模式：PVP/PVE
	attr_accessor:vAGroups #(SBattleGroup的数组)A队伍里的所有小组
	attr_accessor:vBGroups #(SBattleGroup的数组)B队伍里的所有小组
	attr_accessor:vSummons #(SBattleFighter的数组)战斗中可能召唤的散仙
	attr_accessor:vRound #(SBattleRound的数组)所有的出手回合
	attr_accessor:byAWaves #(UINT8)A队剩余波数
	attr_accessor:byBWaves #(UINT8)B队剩余波数
	attr_accessor:eResult #(枚举类型：EBattleResult)战斗结果
	attr_accessor:vecItem #(SItemGenInfo的数组)获得物品
	attr_accessor:vecResSource #(SResource的数组)获得资源

	#构造函数
	def initialize
		super()
		@qwBattleID = 0
		@qwNextBattleID = 0
		@wSceneID = 0
		@by1Vs1 = 0
		@eType = 0
		@vAGroups = Array.new
		@vBGroups = Array.new
		@vSummons = Array.new
		@vRound = Array.new
		@byAWaves = 0
		@byBWaves = 0
		@eResult = 0
		@vecItem = Array.new
		@vecResSource = Array.new
	end

	#获取继承类的类型
	def getClassType
		return EType_NewSBattleReport::ETYPE_NEWSBATTLEREPORTV1
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.qwBattleID = @qwBattleID
		obj.qwNextBattleID = @qwNextBattleID
		obj.wSceneID = @wSceneID
		obj.by1Vs1 = @by1Vs1
		obj.eType = @eType
		obj.vAGroups = @vAGroups
		obj.vBGroups = @vBGroups
		obj.vSummons = @vSummons
		obj.vRound = @vRound
		obj.byAWaves = @byAWaves
		obj.byBWaves = @byBWaves
		obj.eResult = @eResult
		obj.vecItem = @vecItem
		obj.vecResSource = @vecResSource
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = NewSBattleReportV1.new
		base = NewSBattleReport::fromStream(data)
		base.copyTo(s)
		s.qwBattleID = ByteUtil::readUINT64(data)
		s.qwNextBattleID = ByteUtil::readUINT64(data)
		s.wSceneID = ByteUtil::readUINT16(data)
		s.by1Vs1 = ByteUtil::readUINT8(data)
		s.eType = ByteUtil::readUINT8(data)
		s.vAGroups = SBattleGroup::vectorFromStream(data)
		s.vBGroups = SBattleGroup::vectorFromStream(data)
		s.vSummons = SBattleFighter::vectorFromStream(data)
		s.vRound = SBattleRound::vectorFromStream(data)
		s.byAWaves = ByteUtil::readUINT8(data)
		s.byBWaves = ByteUtil::readUINT8(data)
		s.eResult = ByteUtil::readUINT8(data)
		s.vecItem = SItemGenInfo::vectorFromStream(data)
		s.vecResSource = SResource::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = NewSBattleReportV1::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT64(data, @qwBattleID)
		ByteUtil::writeUINT64(data, @qwNextBattleID)
		ByteUtil::writeUINT16(data, @wSceneID)
		ByteUtil::writeUINT8(data, @by1Vs1)
		ByteUtil::writeUINT8(data, @eType)
		SBattleGroup::vectorToStream(data, @vAGroups)
		SBattleGroup::vectorToStream(data, @vBGroups)
		SBattleFighter::vectorToStream(data, @vSummons)
		SBattleRound::vectorToStream(data, @vRound)
		ByteUtil::writeUINT8(data, @byAWaves)
		ByteUtil::writeUINT8(data, @byBWaves)
		ByteUtil::writeUINT8(data, @eResult)
		SItemGenInfo::vectorToStream(data, @vecItem)
		SResource::vectorToStream(data, @vecResSource)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#协议类：战斗通信协议
class BattleGSBase < ProtocolBase
	#以下为发送函数
	#发送：请求战斗
	def send_BattleReq(
		qwDefenseID #(UINT64)防守ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwDefenseID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求战报
	def send_BattleReportReq(
		qwReportID,  #(UINT64)请求战报ID
		qwMasterID #(UINT64)视角角色ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwReportID)
		ByteUtil::writeUINT64(data, qwMasterID)
		return @svrHandler.sendPacket(data)
	end

	#发送：战报阅读完成
	def send_FinishBattleReport(
		qwReportID #(UINT64)请求战报ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwReportID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：战斗请求结果
	def onRecv_BattleAck(
		eResult #(枚举类型：EBattleReqResult)返回结果
	)
		raise NotImplementedError
	end
	#接收：请求战报结果
	def onRecv_BattleReportAck(
		eResult #(枚举类型：EReportReqResult)战报请求结果
	)
		raise NotImplementedError
	end
	#接收：战报
	def onRecv_BattleReportData(
		strBattleReport, #(string)战报
		qwMasterID, #(UINT64)视角角色ID
		wFighterID #(UINT16)主将ID
	)
		raise NotImplementedError
	end
#以下为接收处理函数
	#接收处理：战斗请求结果
	def _doRecv_BattleAck(data)
		eResult = ByteUtil::readUINT8(data)
		return onRecv_BattleAck(eResult)
	end

	#接收处理：请求战报结果
	def _doRecv_BattleReportAck(data)
		eResult = ByteUtil::readUINT8(data)
		return onRecv_BattleReportAck(eResult)
	end

	#接收处理：战报
	def _doRecv_BattleReportData(data)
		strBattleReport = ByteUtil::readSTRING(data)
		qwMasterID = ByteUtil::readUINT64(data)
		wFighterID = ByteUtil::readUINT16(data)
		return onRecv_BattleReportData(strBattleReport, qwMasterID, wFighterID)
	end

	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 21;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_BattleAck' #FuncID: 1
		@recvFuncList[1] = '_doRecv_BattleReportAck' #FuncID: 2
		@recvFuncList[2] = '_doRecv_BattleReportData' #FuncID: 3
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

