#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    ProtoCommon.rb
#  Purpose:      各个协议、服务器之间通用结构存放文件
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#枚举类型示例
class ECareerType
	ECAREER_ALL = 0#所有职业
	ECAREER_RU = 1#儒
	ECAREER_SHI = 2#释
	ECAREER_DAO = 3#道
	ECAREER_MO = 4#墨
	ECAREER_MAX = 5#最大值
end

#性别
class ESexType
	ESEX_ALL = 0#所有性别
	ESEX_MALE = 1
	ESEX_FEMALE = 2#女性
	ESEX_MAX = 3#最大值
end

#颜色
class EColor
	ECOLOR_BLACK = 0#黑
	ECOLOR_WHITE = 1
	ECOLOR_GREEN = 2#绿
	ECOLOR_BLUE = 3#兰
	ECOLOR_PURPLE = 4#紫
	ECOLOR_ORANGE = 5#橙
end

#货币类型
class ECoinType
	ECOINNONE = 0#无
	EGOLDCOIN = 1#仙石
	ESILVERCOIN = 2#银币
	ECOUPONCOIN = 3#礼券
	EHONOURCOIN = 4#荣誉
	ECOINEND = 5#结束
end

#数据变化类型
class EDataChange
	EOPNONE = 0#无变化
	EOPADD = 1#数据增加
	EOPDEL = 2#数据删除
	EOPUPDATE = 3#数据更新
	EOPREPLACE = 4#数据替换
	EOPADDIGNORE = 5#数据仅新增
	EOPMAX = 6#最大值
end

#货币类型
class EMoneyType
	EMONEY_NONE = 0#无类型表示不消耗
	EMONEY_GOLD = 1#仙石
	EMONEY_SILVER = 2#银币
	EMONEY_COUPON = 3#礼券
	EMONEY_GIFTCOIN = 4#金券
	EMONEY_EXP = 5#经验
	EMONEY_PRESTIGE = 6#声望
	EMONEY_SOUL = 7#魂魄
	EMONEY_HONOR = 8#荣誉
	EMONEY_PEXP = 9#修为
	EMONEY_SIGIL = 10#符印
	EMONEY_CENTSY = 11#仙元
	EMONEY_ACTION = 12#体力
	EMONEY_SOP = 13#阅历
	EMONEY_TAOISM = 14#道术
	EMONEY_POTEN = 15#渡劫点数
	EMONEY_REIKI = 16#副本星级
	EMONEY_HFP = 17#寻仙积分
	EMONEY_DEMONSOUL = 18#封印点
	EMONEY_SOULATTACK = 19#攻击之魂
	EMONEY_SOULHP = 20#生命之魂
	EMONEY_SOULCRITICAL = 21#暴击之魂
	EMONEY_SOULCOUNTER = 22#反击之魂
	EMONEY_SOULSPEED = 23#身法之魂
	EMONEY_SOULDEFENCE = 24#防御之魂
	EMONEY_SOULHIT = 25#命中之魂
	EMONEY_SOULDODGE = 26#闪避之魂
	EMONEY_ACHIEVEMENTAP = 27#成就点
	EMONEY_COLLECTAP = 28#收藏点
	EMONEY_GUILDCONTRIB = 29#帮派贡献
	EMONEY_STAMPHUANG = 30#橙阶除魔印
	EMONEY_STAMPXUAN = 31#蓝阶除魔印
	EMONEY_STAMPDI = 32#绿阶除魔印
	EMONEY_STAMPTIAN = 33#紫阶除魔印
	EMONEY_STAMPXING = 34#星阶除魔印
	EMONEY_STAMPYUE = 35#月阶除魔印
	EMONEY_STAMPDI2 = 36#帝阶除魔印
	EMONEY_STAMPXIAN = 37#仙阶除魔印
	EMONEY_STAMPSHENG = 38#圣阶除魔印
	EMONEY_STAMPFO = 39#佛阶除魔印
	EMONEY_LOVEHEART = 40#爱心
	EMONEY_BLUEFAIRYFATE = 51#蓝色仙缘
	EMONEY_PURPLEFAIRYFATE = 52#紫色仙缘
	EMONEY_ORANGEFAIRYFATE = 53#橙色仙缘
	EMONEY_DUJIEFU = 56#渡劫符
	EMONEY_LUCKYCOUPON = 57#抽奖券
	EMONEY_END = 100#货币类型上限标志
end

#属性枚举
class EFighterAttr
	EFIGHTATTR_MIN = 0#属性枚举最小值
	EFIGHTATTR_PHYATK = 1#物理攻击
	EFIGHTATTR_MGCATK = 2#法术攻击
	EFIGHTATTR_PHYDEF = 3#物理防御
	EFIGHTATTR_MGCDEF = 4#法术防御
	EFIGHTATTR_PHYRDC = 5#物理免伤
	EFIGHTATTR_MGCRDC = 6#魔法免伤
	EFIGHTATTR_MAXHP = 7#最大生命
	EFIGHTATTR_SPEED = 8#身法
	EFIGHTATTR_HIT = 9#命中值
	EFIGHTATTR_HITRATE = 10#命中率
	EFIGHTATTR_DODGE = 11#闪避值
	EFIGHTATTR_DODGERATE = 12#闪避率
	EFIGHTATTR_CRITICAL = 13#暴击值
	EFIGHTATTR_CRTRATE = 14#暴击率
	EFIGHTATTR_ANTICRITCAL = 15#稳固值
	EFIGHTATTR_ANTICRTRATE = 16#稳固率
	EFIGHTATTR_BLOCK = 17#格挡值
	EFIGHTATTR_BLOCKRATE = 18#格挡率
	EFIGHTATTR_PIERCE = 19#穿透值
	EFIGHTATTR_PIERCERATE = 20#穿透率
	EFIGHTATTR_COUNTER = 21#反击值
	EFIGHTATTR_COUNTERRATE = 22#反击率
	EFIGHTATTR_RESIST = 23#压制值
	EFIGHTATTR_RESISTRATE = 24#压制率
	EFIGHTATTR_INITAURA = 25#入场灵气
	EFIGHTATTR_MAXAURA = 26#最大灵气
	EFIGHTATTR_CRIEXTRAADD = 27#暴击伤害增加
	EFIGHTATTR_CRIEXTRARDC = 28#暴击伤害减免
	EFIGHTATTR_METALATK = 29#金攻
	EFIGHTATTR_WOODATK = 30#木攻
	EFIGHTATTR_WATERATK = 31#水攻
	EFIGHTATTR_FIREATK = 32#火攻
	EFIGHTATTR_EARTHATK = 33#土攻
	EFIGHTATTR_METALDEF = 34#金防
	EFIGHTATTR_WOODDEF = 35#木防
	EFIGHTATTR_WATERDEF = 36#水防
	EFIGHTATTR_FIREDEF = 37#火防
	EFIGHTATTR_EARTHDEF = 38#土防
	EFIGHTATTR_PHYATK_PER = 39#物理攻击%
	EFIGHTATTR_MGCATK_PER = 40#法术攻击%
	EFIGHTATTR_PHYDEF_PER = 41#物理防御%
	EFIGHTATTR_MGCDEF_PER = 42#法术防御%
	EFIGHTATTR_MAXHP_PER = 43#最大生命%
	EFIGHTATTR_SPEED_PER = 44#身法%
	EFIGHTATTR_HIT_PER = 45#命中值%
	EFIGHTATTR_DODGE_PER = 46#闪避值%
	EFIGHTATTR_CRITICAL_PER = 47#暴击值%
	EFIGHTATTR_ANTICRITCAL_PER = 48#稳固值%
	EFIGHTATTR_BLOCK_PER = 49#格挡值%
	EFIGHTATTR_PIERCE_PER = 50#穿透值%
	EFIGHTATTR_COUNTER_PER = 51#反击值%
	EFIGHTATTR_RESIST_PER = 52#压制值%
	EFIGHTATTR_ANTIEFFECT = 53#法术抵抗
	EFIGHTATTR_COUTEREXTRAADD = 54#反击伤害增加
	EFIGHTATTR_COUTEREXTRARDC = 55#反击伤害减免
	EFIGHTATTR_MAX = 56#属性枚举最大值
end

#属性加成类型
class EAttrGroupType
	EATTRGPMIN = 0#属性加成
	EATTRGPPLAYERBEGIN = 1#主将属性加成开始---
	EATTRGPFASHION = 2#时装属性加成
	EATTRGPTITLE = 3#称号属性加成
	EATTRGPCITTA = 4#心法属性加成
	EATTRGPPLAYEREND = 5#主将加成属性结束-----
	EATTRGPHEROBEGIN = 6#散仙加成属性开始
	EATTRGPEQUIPTRUMP = 7#装备法宝属性加成
	EATTRGPGEMSTONE = 8#宝石属性加成
	EATTRGPHEROEND = 9#散仙加成属性结束
	EATTRGPHEROANDPLAYERBEGIN = 10#全员加成属性开始--
	EATTRGPTRUMPACTIVE = 11#法宝激活属性加成
	EATTRGPTRUMPEXTRA = 12#法宝附加属性加成
	EATTRGPTRUMPHALO = 13#法宝光环属性加成
	EATTRGPHORSE = 14#坐骑属性加成
	EATTRGPSHUSHANBATTLE = 15#蜀山论剑属性加成
	EATTRGPBAG = 16#背包解锁的属性加成
	EATTRGPACHIEVEMENT = 17#成就属性加成
	EATTRGPCOLLECTION = 18#收集属性加成
	EATTRGPFORMATION = 19#阵形属性加成
	EATTRGPPET = 20#阵灵属性加成
	EATTRGPBEASTSOUL = 21#兽魂
	EATTRGPGUILDTECH = 22#帮派技能加成
	EATTRGPBUFFER = 23#外部buffer属性加成
	EATTRGPTRIPOD = 24#九疑鼎属性加成
	EATTRGPFIGHTERCOMBINATION = 25#散仙组合属性加成
	EATTRBEAUTY = 26#美女系统
	EATTRGPHEROANDPLAYEREND = 27#全员加成属性结束--
	EATTRGPMAX = 28#属性加成
end

#奖励类型
class AWARDTYPE
	AWARDTYPE_TITLE = 1#称号
end

#Buff大类
class EBuffType
	EBTNONE = 0#无效Buff大类
	EBTUSER = 1#帐号相关Buff类型
	EBTPLAYER = 2#玩家自带Buff类型
	EBTMAINFIGHTER = 3#主将相关Buff类型
	EBTFIGHTER = 4#散仙相关Buff类型
	EBTMONSTER = 5#怪物相关Buff类型
	EBTNPC = 6#NPC相关Buff类型
	EBTMAX = 7#Buff大类最大值
end

#Buff效果类型
class EBuffEffectType
	EBETNONE = 0#无效Buff效果类型
	EBETATTR = 1#Buff属性加成
	EBETTIMECOUNT = 2#Buff持续时间同时持续次数
	EBETCOUNT = 3#Buff仅持续时间
	EBETMAX = 4#Buff效果最大值
end

#Buff状态
class EBuffState
	EBSNONE = 0#无效Buff状态
	EBSACTIVED = 1#Buff生效
	EBSPAUSED = 2#Buff暂停
	EBSOVERDUE = 3#Buff过期
	EBSMAX = 4#Buff状态最大值
end

#Buff相关操作结果
class EBuffOpResult
	EBORSUCCESS = 0#操作成功
	EBORFAILED = 1#操作失败
	EBOREXISTED = 2#存在相同Buff
	EBORNOTEXISTED = 3#不存在该Buff
	EBOROVERDUE = 4#已经过期的Buff
	EBORPAUSED = 5#已经暂停的Buff
end

#被攻击类型
class EAttacked
	EATTACKED_NONE = 0#无
	EATTACKED_DEMONTOWER = 1#锁妖塔
	EATTACKED_MAX = 2#类型上限
end

#QQ平台类型
class EQQPtType
	EQQPTTYPENONE = 0#无
	EQQPTTYPEYELLOW = 1#黄钻平台
	EQQPTTYPEBLUE = 2#蓝钻平台
	EQQPTTYPERED = 3#红钻/VIP平台
	EQQPTTYPEMAX = 4#最大值
end

#平台类型定义
class EPtType
	EPTTYPENONE = 0#无
	EPTTYPEQQYELLOW = 1#QQ黄钻平台/Qzone
	EPTTYPEQQPENGYOU = 2#QQ朋友/校友/黄钻
	EPTTYPEQQWEIBO = 3#QQ微博平台
	EPTTYPEQQPLUS = 4#QQ/Q+平台
	EPTTYPEQQGAME = 5#QQ蓝钻/游戏平台
	EPTTYPEQQ3366 = 6#QQ蓝钻/3366平台/包子
	EPTTYPEQQKINGXIN = 7#QQ官网平台/QQ会员
	EPTTYPEKINGXIN = 8#恺英官网平台
	EPTTYPEMAX = 9#最大值
end

#平台额外bit参数定义
class EPlatformBitType
	EPBBITSUPER = 0#豪华/超级
	EPBBITYEARLY = 1#年费
end

#货币信息
class SCoinValue
	attr_accessor:eCoinType #(枚举类型：ECoinType)货币类型
	attr_accessor:dwValue #(UINT32)值

	#构造函数
	def initialize
		@eCoinType = 0
		@dwValue = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eCoinType = @eCoinType
		obj.dwValue = @dwValue
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SCoinValue.new
		s.eCoinType = ByteUtil::readUINT8(data)
		s.dwValue = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SCoinValue::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eCoinType)
		ByteUtil::writeUINT32(data, @dwValue)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#属性变化结构
class SFtAttrMod
	attr_accessor:_eAttr #(枚举类型：EFighterAttr)属性类型
	attr_accessor:_fValue #(float)改变的值

	#构造函数
	def initialize
		@_eAttr = 0
		@_fValue = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj._eAttr = @_eAttr
		obj._fValue = @_fValue
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFtAttrMod.new
		s._eAttr = ByteUtil::readUINT8(data)
		s._fValue = ByteUtil::readFLOAT(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFtAttrMod::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @_eAttr)
		ByteUtil::writeFLOAT(data, @_fValue)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#属性加成
class SAttrGroup
	attr_accessor:eType #(枚举类型：EAttrGroupType)属性加成类型
	attr_accessor:vecFtAttrMod #(SFtAttrMod的数组)属性变化结构

	#构造函数
	def initialize
		@eType = 0
		@vecFtAttrMod = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eType = @eType
		obj.vecFtAttrMod = @vecFtAttrMod
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SAttrGroup.new
		s.eType = ByteUtil::readUINT8(data)
		s.vecFtAttrMod = SFtAttrMod::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SAttrGroup::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eType)
		SFtAttrMod::vectorToStream(data, @vecFtAttrMod)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#Buff数据信息
class SDBBuffInfo
	attr_accessor:qwRoleID #(UINT64)对应玩家ID
	attr_accessor:qwOwnerID #(UINT64)所属实例ID(Role/Fighter/...
	attr_accessor:eBuffType #(枚举类型：EBuffType)Buff大类
	attr_accessor:wBuffID #(UINT16)Buff种类
	attr_accessor:eBuffEffectType #(枚举类型：EBuffEffectType)Buff效果类型
	attr_accessor:eBuffState #(枚举类型：EBuffState)Buff当前状态
	attr_accessor:vecBuffParam #(UINT32数组)Buff效果参数
	attr_accessor:dwBuffCount #(UINT32)Buff失效次数
	attr_accessor:dwBuffTime #(UINT32)Buff失效时间
	attr_accessor:vecEffectMapID #(UINT32数组)地图ID限制，空表示任意地图
	attr_accessor:byBattleType #(UINT8)有效的战斗类型(不存数据库)

	#构造函数
	def initialize
		@qwRoleID = 0
		@qwOwnerID = 0
		@eBuffType = 0
		@wBuffID = 0
		@eBuffEffectType = 0
		@eBuffState = 0
		@vecBuffParam = Array.new
		@dwBuffCount = 0
		@dwBuffTime = 0
		@vecEffectMapID = Array.new
		@byBattleType = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.qwOwnerID = @qwOwnerID
		obj.eBuffType = @eBuffType
		obj.wBuffID = @wBuffID
		obj.eBuffEffectType = @eBuffEffectType
		obj.eBuffState = @eBuffState
		obj.vecBuffParam = @vecBuffParam
		obj.dwBuffCount = @dwBuffCount
		obj.dwBuffTime = @dwBuffTime
		obj.vecEffectMapID = @vecEffectMapID
		obj.byBattleType = @byBattleType
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDBBuffInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.qwOwnerID = ByteUtil::readUINT64(data)
		s.eBuffType = ByteUtil::readUINT8(data)
		s.wBuffID = ByteUtil::readUINT16(data)
		s.eBuffEffectType = ByteUtil::readUINT8(data)
		s.eBuffState = ByteUtil::readUINT8(data)
		s.vecBuffParam = ByteUtil::readVecUINT32(data)
		s.dwBuffCount = ByteUtil::readUINT32(data)
		s.dwBuffTime = ByteUtil::readUINT32(data)
		s.vecEffectMapID = ByteUtil::readVecUINT32(data)
		s.byBattleType = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDBBuffInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT64(data, @qwOwnerID)
		ByteUtil::writeUINT8(data, @eBuffType)
		ByteUtil::writeUINT16(data, @wBuffID)
		ByteUtil::writeUINT8(data, @eBuffEffectType)
		ByteUtil::writeUINT8(data, @eBuffState)
		ByteUtil::writeVecUINT32(data, @vecBuffParam)
		ByteUtil::writeUINT32(data, @dwBuffCount)
		ByteUtil::writeUINT32(data, @dwBuffTime)
		ByteUtil::writeVecUINT32(data, @vecEffectMapID)
		ByteUtil::writeUINT8(data, @byBattleType)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#Buff详细信息
class SBuffInfo
	attr_accessor:qwRoleID #(UINT64)对应玩家ID
	attr_accessor:qwOwnerID #(UINT64)所属实例ID(Role/Fighter/...
	attr_accessor:wBuffID #(UINT16)Buff种类
	attr_accessor:eBuffState #(枚举类型：EBuffState)Buff当前状态
	attr_accessor:vecBuffData #(UINT32数组)Buff数值
	attr_accessor:dwBuffCount #(UINT32)Buff叠加层数
	attr_accessor:dwBuffTime #(UINT32)Buff失效时间

	#构造函数
	def initialize
		@qwRoleID = 0
		@qwOwnerID = 0
		@wBuffID = 0
		@eBuffState = 0
		@vecBuffData = Array.new
		@dwBuffCount = 0
		@dwBuffTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.qwOwnerID = @qwOwnerID
		obj.wBuffID = @wBuffID
		obj.eBuffState = @eBuffState
		obj.vecBuffData = @vecBuffData
		obj.dwBuffCount = @dwBuffCount
		obj.dwBuffTime = @dwBuffTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBuffInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.qwOwnerID = ByteUtil::readUINT64(data)
		s.wBuffID = ByteUtil::readUINT16(data)
		s.eBuffState = ByteUtil::readUINT8(data)
		s.vecBuffData = ByteUtil::readVecUINT32(data)
		s.dwBuffCount = ByteUtil::readUINT32(data)
		s.dwBuffTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBuffInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT64(data, @qwOwnerID)
		ByteUtil::writeUINT16(data, @wBuffID)
		ByteUtil::writeUINT8(data, @eBuffState)
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

#货币列表
class SMoneyCount
	attr_accessor:eMoneyType #(枚举类型：EMoneyType)货币类型
	attr_accessor:dwCount #(UINT32)货币量

	#构造函数
	def initialize
		@eMoneyType = 0
		@dwCount = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eMoneyType = @eMoneyType
		obj.dwCount = @dwCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMoneyCount.new
		s.eMoneyType = ByteUtil::readUINT8(data)
		s.dwCount = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMoneyCount::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eMoneyType)
		ByteUtil::writeUINT32(data, @dwCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#平台相关参数
class SPlatformParam
	attr_accessor:byPtType #(枚举类型：EPtType)平台类型
	attr_accessor:byQQPtType #(枚举类型：EQQPtType)QQ平台类型
	attr_accessor:byQQPtLv #(UINT8)QQ平台类型等级
	attr_accessor:bySPType #(UINT8)Bit位定义见EPlatformBitType

	#构造函数
	def initialize
		@byPtType = 0
		@byQQPtType = 0
		@byQQPtLv = 0
		@bySPType = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byPtType = @byPtType
		obj.byQQPtType = @byQQPtType
		obj.byQQPtLv = @byQQPtLv
		obj.bySPType = @bySPType
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPlatformParam.new
		s.byPtType = ByteUtil::readUINT8(data)
		s.byQQPtType = ByteUtil::readUINT8(data)
		s.byQQPtLv = ByteUtil::readUINT8(data)
		s.bySPType = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPlatformParam::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byPtType)
		ByteUtil::writeUINT8(data, @byQQPtType)
		ByteUtil::writeUINT8(data, @byQQPtLv)
		ByteUtil::writeUINT8(data, @bySPType)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#Center2Game 活动时间同步
class SActivityTime
	attr_accessor:dwActID #(UINT32)活动ID
	attr_accessor:dwAlarm #(UINT32)公告
	attr_accessor:dwReady #(UINT32)准备
	attr_accessor:dwBegin #(UINT32)开始
	attr_accessor:dwEnd #(UINT32)结束

	#构造函数
	def initialize
		@dwActID = 0
		@dwAlarm = 0
		@dwReady = 0
		@dwBegin = 0
		@dwEnd = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwActID = @dwActID
		obj.dwAlarm = @dwAlarm
		obj.dwReady = @dwReady
		obj.dwBegin = @dwBegin
		obj.dwEnd = @dwEnd
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SActivityTime.new
		s.dwActID = ByteUtil::readUINT32(data)
		s.dwAlarm = ByteUtil::readUINT32(data)
		s.dwReady = ByteUtil::readUINT32(data)
		s.dwBegin = ByteUtil::readUINT32(data)
		s.dwEnd = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SActivityTime::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwActID)
		ByteUtil::writeUINT32(data, @dwAlarm)
		ByteUtil::writeUINT32(data, @dwReady)
		ByteUtil::writeUINT32(data, @dwBegin)
		ByteUtil::writeUINT32(data, @dwEnd)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#活动中心数据库记录
class SActivityOpt
	attr_accessor:dwActID #(UINT32)活动ID
	attr_accessor:byIndex #(UINT8)场次
	attr_accessor:strName #(string)活动名字
	attr_accessor:dwSync #(UINT32)活动时间 同步
	attr_accessor:dwAlarm #(UINT32)活动公告时间
	attr_accessor:dwReady #(UINT32)活动准备时间
	attr_accessor:dwBegin #(UINT32)活动开始时间
	attr_accessor:dwEnd #(UINT32)活动结束时间
	attr_accessor:bSync #(bool)是否同步Game
	attr_accessor:dwOptTime #(UINT32)操作时间

	#构造函数
	def initialize
		@dwActID = 0
		@byIndex = 0
		@strName = ''
		@dwSync = 0
		@dwAlarm = 0
		@dwReady = 0
		@dwBegin = 0
		@dwEnd = 0
		@bSync = false
		@dwOptTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwActID = @dwActID
		obj.byIndex = @byIndex
		obj.strName = @strName
		obj.dwSync = @dwSync
		obj.dwAlarm = @dwAlarm
		obj.dwReady = @dwReady
		obj.dwBegin = @dwBegin
		obj.dwEnd = @dwEnd
		obj.bSync = @bSync
		obj.dwOptTime = @dwOptTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SActivityOpt.new
		s.dwActID = ByteUtil::readUINT32(data)
		s.byIndex = ByteUtil::readUINT8(data)
		s.strName = ByteUtil::readSTRING(data)
		s.dwSync = ByteUtil::readUINT32(data)
		s.dwAlarm = ByteUtil::readUINT32(data)
		s.dwReady = ByteUtil::readUINT32(data)
		s.dwBegin = ByteUtil::readUINT32(data)
		s.dwEnd = ByteUtil::readUINT32(data)
		s.bSync = ByteUtil::readBOOL(data)
		s.dwOptTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SActivityOpt::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwActID)
		ByteUtil::writeUINT8(data, @byIndex)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT32(data, @dwSync)
		ByteUtil::writeUINT32(data, @dwAlarm)
		ByteUtil::writeUINT32(data, @dwReady)
		ByteUtil::writeUINT32(data, @dwBegin)
		ByteUtil::writeUINT32(data, @dwEnd)
		ByteUtil::writeBOOL(data, @bSync)
		ByteUtil::writeUINT32(data, @dwOptTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#协议类：各个协议、服务器之间通用结构存放文件
class ProtoCommonBase < ProtocolBase
	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 258;
		@recvFuncList = Array.new
	end

	def handleMessage(data)
		return true;
	end
end

