#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    RoleInfoDefine.rb
#  Purpose:      角色数据定义
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './AchievementProtBase.rb'
require_relative './ArenaGSBase.rb'
require_relative './BeautyBase.rb'
require_relative './CollectionProtBase.rb'
require_relative './DemonTowerBase.rb'
require_relative './DungeonProtBase.rb'
require_relative './ExchangeShopProtBase.rb'
require_relative './FighterProtBase.rb'
require_relative './FriendProtBase.rb'
require_relative './GroupTaskProtBase.rb'
require_relative './GuardEMeiProtBase.rb'
require_relative './HorseBase.rb'
require_relative './ItemProtBase.rb'
require_relative './LevelPrizeBase.rb'
require_relative './ProtoCommonBase.rb'
require_relative './ShengLingProtBase.rb'
require_relative './ShipProtBase.rb'
require_relative './TaskProtBase.rb'
require_relative './TreasureHuntProtBase.rb'
require_relative './TripodProtBase.rb'
require_relative './YaMenTaskProtBase.rb'

#以下为类型定义

#战报类型
class EBattleReportType
	ETYPELADDER = 0#天梯
end

#战报发起类型
class EBattleActionType
	ETYPEATTACK = 0#玩家进攻
	ETYPEDEFENSE = 1#玩家防守
	ETYPEALL = 2#防守和进攻
end

#兽魂种类
class EBeastSoulType
	EBEASTSOULNONE = 0#无加成
	EBEASTSOULATTTACK = 1#攻击之魂
	EBEASTSOULHP = 2#生命之魂
	EBEASTSOULCRITICAL = 3#暴击之魂
	EBEASTSOULCOUNTER = 4#反击之魂
	EBEASTSOULSPEED = 5#身法之魂
	EBEASTSOULDEFENCE = 6#防御之魂
	EBEASTSOULHIT = 7#命中之魂
	EBEASTSOULDODGE = 8#闪避之魂
	EBEASTSOULMAX = 9#最大
end

#数据类型
class EDataType
	ETYPEROLEBASEINFO = 0#玩家基本数据
	ETYPEITEMINFO = 1#玩家物品数据
	ETYPEPLAYERDGN = 2#玩家副本数据
	ETYPEFIGHTERINFO = 3#玩家将信息
	ETYPETASKINFO = 4#玩家任务信息
	ETYPESKILLINFO = 5#技能信息
	ETYPEPASSIVESKILLINFO = 6#被动技能信息
	ETYPEFRIENDINFO = 7#关系信息
	ETYPEVARINFO = 8#关系信息
	ETYPECITTAINFO = 9#玩家心法数据
	ETYPESLOTSINFO = 10#玩家/其他槽心法数据
	ETYPETRUMPINFO = 11#法宝信息
	ETYPEEQUIPTRUMPINFO = 12#装备法宝信息
	ETYPEEQUIPTRUMPSHUFFLEINFO = 13#装备法宝洗炼信息
	ETYPEFORMATIONINFO = 14#阵形信息
	ETYPEPETDATAINFO = 15#阵灵信息
	ETYPEROLEPETINFO = 16#阵灵全局信息
	ETYPEBEASTSOULINFO = 17#兽魂信息
	ETYPETRIPODFIREINFO = 18#九疑鼎的火种信息
	ETYPEARENA = 19#斗剑信息
	ETYPEBUFFINFO = 20#Buff信息
	ETYPEFASHIONINFO = 21#时装信息
	ETYPESOULSPACEINFO = 22#魄空间信息
	ETYPEBUBBLEINFO = 23#气泡信息
	ETYPEHORSEDBINFO = 24#坐骑信息
	ETYPEGROUPTASK = 25#师门任务
	ETYPEYAMENTASK = 26#衙门任务
	ETYPEACTIVITYTASK = 27#活跃度任务
	ETYPETITLE = 28#称号
	ETYPEACHIEVEMENTINFO = 29#成就
	ETYPECOLLECTIONINFO = 30#收藏
	ETYPEATTACKED = 31#玩家被攻击信息
	ETYPEEXCHANGEDITEM = 32#玩家兑换商品信息
	ETYPESWEEP = 33#玩家扫荡信息
	ETYPEPENDRES = 34#玩家暂存信息
	ETYPEXINFAINFO = 35#心法信息
	ETYPELEVELPRIZE = 36#心法信息
	ETYPEYELLODIAMOND = 37#黄钻信息
	ETYPEEVENTINFO = 38#事件信息
	ETYPEBUYITEMLIMIT = 39#商品数量限购信息
	ETYPEDAYTARGET = 40#七日目标活动
	ETYPEFIGHTERCOMINATION = 41#玩家的散仙组合信息
	ETYPEBATTLEARRAY = 42#破阵信息
	ETYPEAUTOSTORE = 43#动态存储信息
	ETYPETH = 44#寻宝信息
	ETYPEBEAUTY = 45#美女系统
	ETYPEFIGHTFORMATION = 46#新阵型系统
	ETYPEFIGHTHERO = 47#散仙数据
	ETYPESHIP = 48#金船
	ETYPEGUARDEMEI = 49#守卫峨眉
	ETYPEGEMSTONE = 50#宝石
	ETYPESHENGLING = 51#圣陵信息
	ETYPESHENGLINGPRIZE = 52#圣陵奖励信息
	ETYPEMAX = 53#最大值
end

#EDataType:eRoleBaseInfo
class RoleBaseInfo
	attr_accessor:strName #(string)玩家名字
	attr_accessor:eCareer #(枚类型：ProtoCommon::ECareerType)职业
	attr_accessor:eSex #(枚类型：ProtoCommon::ESexType)性别
	attr_accessor:wMapID #(UINT16)地图ID
	attr_accessor:fX #(float)X坐标
	attr_accessor:fY #(float)Y坐标
	attr_accessor:qwDgnId #(UINT64)副本实例ID
	attr_accessor:dwDgnTypeID #(UINT16)副本模版ID
	attr_accessor:wDgnMapId #(UINT16)副本地图ID
	attr_accessor:fDgnfX #(float)副本X坐标
	attr_accessor:fDgnfY #(float)副本Y坐标
	attr_accessor:wBagMax #(UINT16)背包容量
	attr_accessor:wDepotMax #(UINT16)仓库容量
	attr_accessor:dwPendSilver #(UINT32)延迟发放的银币
	attr_accessor:dwPendCoupon #(UINT32)延迟发放的礼券
	attr_accessor:dwPendExp #(UINT32)延迟发放的经验
	attr_accessor:dwPendGold #(UINT32)延迟发放的仙石
	attr_accessor:dwDemonTowerFloorID #(UINT32)通关镇妖塔层数
	attr_accessor:dwDemonTowerPrizeFloorID #(UINT32)镇妖塔层数
	attr_accessor:strGuide #(string)新手引导内容
	attr_accessor:szIcon #(string)功能开放标签
	attr_accessor:szIconDel #(string)功能关闭标签
	attr_accessor:szIconActive #(string)功能关闭标签
	attr_accessor:dwPackNextUnlockTime #(UINT32)背包下次解锁时间
	attr_accessor:dwActivity #(UINT32)活跃值
	attr_accessor:qwSittingPlayer #(UINT64)一起双修的人
	attr_accessor:szDgnStarAward #(string)副本星级领奖
	attr_accessor:strCreateIP #(string)玩家创角时IP
	attr_accessor:strLoginIP #(string)玩家登录时IP
	attr_accessor:dwLuckyCoupon #(UINT32)幸运券
	attr_accessor:byLevel #(UINT8)玩家等级
	attr_accessor:qwExp #(UINT64)玩家经验值
	attr_accessor:byNation #(UINT8)国家
	attr_accessor:byGMLvl #(UINT8)GM权限
	attr_accessor:dwTotalRecharge #(UINT32)充值金额
	attr_accessor:dwLoginTime #(UINT32)上次登陆时间
	attr_accessor:dwOfflineTime #(UINT32)上次下线时间
	attr_accessor:dwLockExpireTime #(UINT32)被封禁结束时间
	attr_accessor:dwForbExpireTime #(UINT32)被禁言结束时间
	attr_accessor:dwGold #(UINT32)充值仙石
	attr_accessor:dwFreeGold #(UINT32)免费仙石
	attr_accessor:dwSilver #(UINT32)银币
	attr_accessor:dwCoupon #(UINT32)礼券
	attr_accessor:dwSoul #(UINT32)魂魄
	attr_accessor:dwPrestige #(UINT32)声望
	attr_accessor:dwHonor #(UINT32)荣誉
	attr_accessor:dwPExp #(UINT32)修为
	attr_accessor:dwAction #(UINT32)体力
	attr_accessor:dwPoten #(UINT32)渡劫点数
	attr_accessor:dwReiki #(UINT32)副本星级
	attr_accessor:dwDemonSoul #(UINT32)锁妖塔魂值
	attr_accessor:dwSoulAttack #(UINT32)攻击之魂
	attr_accessor:dwSoulHp #(UINT32)生命之魂
	attr_accessor:dwSoulCritical #(UINT32)暴击之魂
	attr_accessor:dwSoulCounter #(UINT32)破击之魂
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
	attr_accessor:dwLoveHeart #(UINT32)爱心
	attr_accessor:dwBlueFairyFate #(UINT32)蓝色仙缘
	attr_accessor:dwPurpleFairyFate #(UINT32)紫色仙缘
	attr_accessor:dwOrangeFairyFate #(UINT32)橙色仙缘
	attr_accessor:dwDuJieFu #(UINT32)散仙渡劫符数量
	attr_accessor:dwBTPoint #(UINT32)战斗力
	attr_accessor:szOwnTitle #(string)拥有的称号
	attr_accessor:szEquipTitle #(string)装备的称号
	attr_accessor:byDomain #(UINT8)渠道
	attr_accessor:byDomainLvl #(UINT8)渠道等级
	attr_accessor:byDisplayLvl #(UINT8)显示等级
	attr_accessor:byDomainYear #(UINT8)年费
	attr_accessor:szOpenId #(string)szOpenId
	attr_accessor:szOpenKey #(string)szOpenKey
	attr_accessor:strSign #(string)签名
	attr_accessor:wMood #(UINT16)心情表情
	attr_accessor:wAchievementLevel #(UINT16)成就等级
	attr_accessor:dwAchievementAP #(UINT32)成就点
	attr_accessor:wCollectLevel #(UINT16)收藏等级
	attr_accessor:dwCollectAP #(UINT32)收藏点
	attr_accessor:qwInvitedID #(UINT64)邀请
	attr_accessor:byWallow #(UINT8)防沉迷
	attr_accessor:dwIndulgeKickTime #(UINT32)防沉迷t人时间
	attr_accessor:byYDLevel #(UINT8)玩家QQ黄钻等级
	attr_accessor:dwCreateTime #(UINT32)创角时间
	attr_accessor:wLastSaveMapID #(UINT16)保存地图ID
	attr_accessor:fLastSaveX #(float)保存X坐标
	attr_accessor:fLastSaveY #(float)保存Y坐标

	#构造函数
	def initialize
		@strName = ''
		@eCareer = 0
		@eSex = 0
		@wMapID = 0
		@fX = 0
		@fY = 0
		@qwDgnId = 0
		@dwDgnTypeID = 0
		@wDgnMapId = 0
		@fDgnfX = 0
		@fDgnfY = 0
		@wBagMax = 0
		@wDepotMax = 0
		@dwPendSilver = 0
		@dwPendCoupon = 0
		@dwPendExp = 0
		@dwPendGold = 0
		@dwDemonTowerFloorID = 0
		@dwDemonTowerPrizeFloorID = 0
		@strGuide = ''
		@szIcon = ''
		@szIconDel = ''
		@szIconActive = ''
		@dwPackNextUnlockTime = 0
		@dwActivity = 0
		@qwSittingPlayer = 0
		@szDgnStarAward = ''
		@strCreateIP = ''
		@strLoginIP = ''
		@dwLuckyCoupon = 0
		@byLevel = 0
		@qwExp = 0
		@byNation = 0
		@byGMLvl = 0
		@dwTotalRecharge = 0
		@dwLoginTime = 0
		@dwOfflineTime = 0
		@dwLockExpireTime = 0
		@dwForbExpireTime = 0
		@dwGold = 0
		@dwFreeGold = 0
		@dwSilver = 0
		@dwCoupon = 0
		@dwSoul = 0
		@dwPrestige = 0
		@dwHonor = 0
		@dwPExp = 0
		@dwAction = 0
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
		@dwLoveHeart = 0
		@dwBlueFairyFate = 0
		@dwPurpleFairyFate = 0
		@dwOrangeFairyFate = 0
		@dwDuJieFu = 0
		@dwBTPoint = 0
		@szOwnTitle = ''
		@szEquipTitle = ''
		@byDomain = 0
		@byDomainLvl = 0
		@byDisplayLvl = 0
		@byDomainYear = 0
		@szOpenId = ''
		@szOpenKey = ''
		@strSign = ''
		@wMood = 0
		@wAchievementLevel = 0
		@dwAchievementAP = 0
		@wCollectLevel = 0
		@dwCollectAP = 0
		@qwInvitedID = 0
		@byWallow = 0
		@dwIndulgeKickTime = 0
		@byYDLevel = 0
		@dwCreateTime = 0
		@wLastSaveMapID = 0
		@fLastSaveX = 0
		@fLastSaveY = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strName = @strName
		obj.eCareer = @eCareer
		obj.eSex = @eSex
		obj.wMapID = @wMapID
		obj.fX = @fX
		obj.fY = @fY
		obj.qwDgnId = @qwDgnId
		obj.dwDgnTypeID = @dwDgnTypeID
		obj.wDgnMapId = @wDgnMapId
		obj.fDgnfX = @fDgnfX
		obj.fDgnfY = @fDgnfY
		obj.wBagMax = @wBagMax
		obj.wDepotMax = @wDepotMax
		obj.dwPendSilver = @dwPendSilver
		obj.dwPendCoupon = @dwPendCoupon
		obj.dwPendExp = @dwPendExp
		obj.dwPendGold = @dwPendGold
		obj.dwDemonTowerFloorID = @dwDemonTowerFloorID
		obj.dwDemonTowerPrizeFloorID = @dwDemonTowerPrizeFloorID
		obj.strGuide = @strGuide
		obj.szIcon = @szIcon
		obj.szIconDel = @szIconDel
		obj.szIconActive = @szIconActive
		obj.dwPackNextUnlockTime = @dwPackNextUnlockTime
		obj.dwActivity = @dwActivity
		obj.qwSittingPlayer = @qwSittingPlayer
		obj.szDgnStarAward = @szDgnStarAward
		obj.strCreateIP = @strCreateIP
		obj.strLoginIP = @strLoginIP
		obj.dwLuckyCoupon = @dwLuckyCoupon
		obj.byLevel = @byLevel
		obj.qwExp = @qwExp
		obj.byNation = @byNation
		obj.byGMLvl = @byGMLvl
		obj.dwTotalRecharge = @dwTotalRecharge
		obj.dwLoginTime = @dwLoginTime
		obj.dwOfflineTime = @dwOfflineTime
		obj.dwLockExpireTime = @dwLockExpireTime
		obj.dwForbExpireTime = @dwForbExpireTime
		obj.dwGold = @dwGold
		obj.dwFreeGold = @dwFreeGold
		obj.dwSilver = @dwSilver
		obj.dwCoupon = @dwCoupon
		obj.dwSoul = @dwSoul
		obj.dwPrestige = @dwPrestige
		obj.dwHonor = @dwHonor
		obj.dwPExp = @dwPExp
		obj.dwAction = @dwAction
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
		obj.dwLoveHeart = @dwLoveHeart
		obj.dwBlueFairyFate = @dwBlueFairyFate
		obj.dwPurpleFairyFate = @dwPurpleFairyFate
		obj.dwOrangeFairyFate = @dwOrangeFairyFate
		obj.dwDuJieFu = @dwDuJieFu
		obj.dwBTPoint = @dwBTPoint
		obj.szOwnTitle = @szOwnTitle
		obj.szEquipTitle = @szEquipTitle
		obj.byDomain = @byDomain
		obj.byDomainLvl = @byDomainLvl
		obj.byDisplayLvl = @byDisplayLvl
		obj.byDomainYear = @byDomainYear
		obj.szOpenId = @szOpenId
		obj.szOpenKey = @szOpenKey
		obj.strSign = @strSign
		obj.wMood = @wMood
		obj.wAchievementLevel = @wAchievementLevel
		obj.dwAchievementAP = @dwAchievementAP
		obj.wCollectLevel = @wCollectLevel
		obj.dwCollectAP = @dwCollectAP
		obj.qwInvitedID = @qwInvitedID
		obj.byWallow = @byWallow
		obj.dwIndulgeKickTime = @dwIndulgeKickTime
		obj.byYDLevel = @byYDLevel
		obj.dwCreateTime = @dwCreateTime
		obj.wLastSaveMapID = @wLastSaveMapID
		obj.fLastSaveX = @fLastSaveX
		obj.fLastSaveY = @fLastSaveY
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = RoleBaseInfo.new
		s.strName = ByteUtil::readSTRING(data)
		s.eCareer = ByteUtil::readUINT8(data)
		s.eSex = ByteUtil::readUINT8(data)
		s.wMapID = ByteUtil::readUINT16(data)
		s.fX = ByteUtil::readFLOAT(data)
		s.fY = ByteUtil::readFLOAT(data)
		s.qwDgnId = ByteUtil::readUINT64(data)
		s.dwDgnTypeID = ByteUtil::readUINT16(data)
		s.wDgnMapId = ByteUtil::readUINT16(data)
		s.fDgnfX = ByteUtil::readFLOAT(data)
		s.fDgnfY = ByteUtil::readFLOAT(data)
		s.wBagMax = ByteUtil::readUINT16(data)
		s.wDepotMax = ByteUtil::readUINT16(data)
		s.dwPendSilver = ByteUtil::readUINT32(data)
		s.dwPendCoupon = ByteUtil::readUINT32(data)
		s.dwPendExp = ByteUtil::readUINT32(data)
		s.dwPendGold = ByteUtil::readUINT32(data)
		s.dwDemonTowerFloorID = ByteUtil::readUINT32(data)
		s.dwDemonTowerPrizeFloorID = ByteUtil::readUINT32(data)
		s.strGuide = ByteUtil::readSTRING(data)
		s.szIcon = ByteUtil::readSTRING(data)
		s.szIconDel = ByteUtil::readSTRING(data)
		s.szIconActive = ByteUtil::readSTRING(data)
		s.dwPackNextUnlockTime = ByteUtil::readUINT32(data)
		s.dwActivity = ByteUtil::readUINT32(data)
		s.qwSittingPlayer = ByteUtil::readUINT64(data)
		s.szDgnStarAward = ByteUtil::readSTRING(data)
		s.strCreateIP = ByteUtil::readSTRING(data)
		s.strLoginIP = ByteUtil::readSTRING(data)
		s.dwLuckyCoupon = ByteUtil::readUINT32(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.qwExp = ByteUtil::readUINT64(data)
		s.byNation = ByteUtil::readUINT8(data)
		s.byGMLvl = ByteUtil::readUINT8(data)
		s.dwTotalRecharge = ByteUtil::readUINT32(data)
		s.dwLoginTime = ByteUtil::readUINT32(data)
		s.dwOfflineTime = ByteUtil::readUINT32(data)
		s.dwLockExpireTime = ByteUtil::readUINT32(data)
		s.dwForbExpireTime = ByteUtil::readUINT32(data)
		s.dwGold = ByteUtil::readUINT32(data)
		s.dwFreeGold = ByteUtil::readUINT32(data)
		s.dwSilver = ByteUtil::readUINT32(data)
		s.dwCoupon = ByteUtil::readUINT32(data)
		s.dwSoul = ByteUtil::readUINT32(data)
		s.dwPrestige = ByteUtil::readUINT32(data)
		s.dwHonor = ByteUtil::readUINT32(data)
		s.dwPExp = ByteUtil::readUINT32(data)
		s.dwAction = ByteUtil::readUINT32(data)
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
		s.dwLoveHeart = ByteUtil::readUINT32(data)
		s.dwBlueFairyFate = ByteUtil::readUINT32(data)
		s.dwPurpleFairyFate = ByteUtil::readUINT32(data)
		s.dwOrangeFairyFate = ByteUtil::readUINT32(data)
		s.dwDuJieFu = ByteUtil::readUINT32(data)
		s.dwBTPoint = ByteUtil::readUINT32(data)
		s.szOwnTitle = ByteUtil::readSTRING(data)
		s.szEquipTitle = ByteUtil::readSTRING(data)
		s.byDomain = ByteUtil::readUINT8(data)
		s.byDomainLvl = ByteUtil::readUINT8(data)
		s.byDisplayLvl = ByteUtil::readUINT8(data)
		s.byDomainYear = ByteUtil::readUINT8(data)
		s.szOpenId = ByteUtil::readSTRING(data)
		s.szOpenKey = ByteUtil::readSTRING(data)
		s.strSign = ByteUtil::readSTRING(data)
		s.wMood = ByteUtil::readUINT16(data)
		s.wAchievementLevel = ByteUtil::readUINT16(data)
		s.dwAchievementAP = ByteUtil::readUINT32(data)
		s.wCollectLevel = ByteUtil::readUINT16(data)
		s.dwCollectAP = ByteUtil::readUINT32(data)
		s.qwInvitedID = ByteUtil::readUINT64(data)
		s.byWallow = ByteUtil::readUINT8(data)
		s.dwIndulgeKickTime = ByteUtil::readUINT32(data)
		s.byYDLevel = ByteUtil::readUINT8(data)
		s.dwCreateTime = ByteUtil::readUINT32(data)
		s.wLastSaveMapID = ByteUtil::readUINT16(data)
		s.fLastSaveX = ByteUtil::readFLOAT(data)
		s.fLastSaveY = ByteUtil::readFLOAT(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = RoleBaseInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @eCareer)
		ByteUtil::writeUINT8(data, @eSex)
		ByteUtil::writeUINT16(data, @wMapID)
		ByteUtil::writeFLOAT(data, @fX)
		ByteUtil::writeFLOAT(data, @fY)
		ByteUtil::writeUINT64(data, @qwDgnId)
		ByteUtil::writeUINT16(data, @dwDgnTypeID)
		ByteUtil::writeUINT16(data, @wDgnMapId)
		ByteUtil::writeFLOAT(data, @fDgnfX)
		ByteUtil::writeFLOAT(data, @fDgnfY)
		ByteUtil::writeUINT16(data, @wBagMax)
		ByteUtil::writeUINT16(data, @wDepotMax)
		ByteUtil::writeUINT32(data, @dwPendSilver)
		ByteUtil::writeUINT32(data, @dwPendCoupon)
		ByteUtil::writeUINT32(data, @dwPendExp)
		ByteUtil::writeUINT32(data, @dwPendGold)
		ByteUtil::writeUINT32(data, @dwDemonTowerFloorID)
		ByteUtil::writeUINT32(data, @dwDemonTowerPrizeFloorID)
		ByteUtil::writeSTRING(data, @strGuide)
		ByteUtil::writeSTRING(data, @szIcon)
		ByteUtil::writeSTRING(data, @szIconDel)
		ByteUtil::writeSTRING(data, @szIconActive)
		ByteUtil::writeUINT32(data, @dwPackNextUnlockTime)
		ByteUtil::writeUINT32(data, @dwActivity)
		ByteUtil::writeUINT64(data, @qwSittingPlayer)
		ByteUtil::writeSTRING(data, @szDgnStarAward)
		ByteUtil::writeSTRING(data, @strCreateIP)
		ByteUtil::writeSTRING(data, @strLoginIP)
		ByteUtil::writeUINT32(data, @dwLuckyCoupon)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT64(data, @qwExp)
		ByteUtil::writeUINT8(data, @byNation)
		ByteUtil::writeUINT8(data, @byGMLvl)
		ByteUtil::writeUINT32(data, @dwTotalRecharge)
		ByteUtil::writeUINT32(data, @dwLoginTime)
		ByteUtil::writeUINT32(data, @dwOfflineTime)
		ByteUtil::writeUINT32(data, @dwLockExpireTime)
		ByteUtil::writeUINT32(data, @dwForbExpireTime)
		ByteUtil::writeUINT32(data, @dwGold)
		ByteUtil::writeUINT32(data, @dwFreeGold)
		ByteUtil::writeUINT32(data, @dwSilver)
		ByteUtil::writeUINT32(data, @dwCoupon)
		ByteUtil::writeUINT32(data, @dwSoul)
		ByteUtil::writeUINT32(data, @dwPrestige)
		ByteUtil::writeUINT32(data, @dwHonor)
		ByteUtil::writeUINT32(data, @dwPExp)
		ByteUtil::writeUINT32(data, @dwAction)
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
		ByteUtil::writeUINT32(data, @dwLoveHeart)
		ByteUtil::writeUINT32(data, @dwBlueFairyFate)
		ByteUtil::writeUINT32(data, @dwPurpleFairyFate)
		ByteUtil::writeUINT32(data, @dwOrangeFairyFate)
		ByteUtil::writeUINT32(data, @dwDuJieFu)
		ByteUtil::writeUINT32(data, @dwBTPoint)
		ByteUtil::writeSTRING(data, @szOwnTitle)
		ByteUtil::writeSTRING(data, @szEquipTitle)
		ByteUtil::writeUINT8(data, @byDomain)
		ByteUtil::writeUINT8(data, @byDomainLvl)
		ByteUtil::writeUINT8(data, @byDisplayLvl)
		ByteUtil::writeUINT8(data, @byDomainYear)
		ByteUtil::writeSTRING(data, @szOpenId)
		ByteUtil::writeSTRING(data, @szOpenKey)
		ByteUtil::writeSTRING(data, @strSign)
		ByteUtil::writeUINT16(data, @wMood)
		ByteUtil::writeUINT16(data, @wAchievementLevel)
		ByteUtil::writeUINT32(data, @dwAchievementAP)
		ByteUtil::writeUINT16(data, @wCollectLevel)
		ByteUtil::writeUINT32(data, @dwCollectAP)
		ByteUtil::writeUINT64(data, @qwInvitedID)
		ByteUtil::writeUINT8(data, @byWallow)
		ByteUtil::writeUINT32(data, @dwIndulgeKickTime)
		ByteUtil::writeUINT8(data, @byYDLevel)
		ByteUtil::writeUINT32(data, @dwCreateTime)
		ByteUtil::writeUINT16(data, @wLastSaveMapID)
		ByteUtil::writeFLOAT(data, @fLastSaveX)
		ByteUtil::writeFLOAT(data, @fLastSaveY)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#EDataType:eTypePlayerDgn：剧情副本，特定日期副本可以考虑删除
class RoleDgnInfo
	attr_accessor:dwDgnType #(UINT32)副本类型
	attr_accessor:dwLastEnterTimer #(UINT32)最近副本支付代价时间
	attr_accessor:byCost #(UINT8)副本支付代价,是否没有消费,0表示已经消费
	attr_accessor:dwEnterTimesAppend #(UINT32)额外增加的副本进入次数
	attr_accessor:dwAppendEndTimer #(UINT32)额外增加的副本进入次数的到期时间
	attr_accessor:dwEnterTimes #(UINT32)当前副本进入次数
	attr_accessor:dwLastCompleteTimer #(UINT32)最近副本通过时间
	attr_accessor:dwCompleteTimes #(UINT32)副本通过次数，通过就记录下
	attr_accessor:wMinTurns #(UINT16)通过的最少回合数
	attr_accessor:dwBuyTimer #(UINT32)最近购买的时间
	attr_accessor:dwBuyTimesToday #(UINT32)当天购买的次数
	attr_accessor:dwFinishTimesToday #(UINT32)今日完成副本次数

	#构造函数
	def initialize
		@dwDgnType = 0
		@dwLastEnterTimer = 0
		@byCost = 0
		@dwEnterTimesAppend = 0
		@dwAppendEndTimer = 0
		@dwEnterTimes = 0
		@dwLastCompleteTimer = 0
		@dwCompleteTimes = 0
		@wMinTurns = 0
		@dwBuyTimer = 0
		@dwBuyTimesToday = 0
		@dwFinishTimesToday = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwDgnType = @dwDgnType
		obj.dwLastEnterTimer = @dwLastEnterTimer
		obj.byCost = @byCost
		obj.dwEnterTimesAppend = @dwEnterTimesAppend
		obj.dwAppendEndTimer = @dwAppendEndTimer
		obj.dwEnterTimes = @dwEnterTimes
		obj.dwLastCompleteTimer = @dwLastCompleteTimer
		obj.dwCompleteTimes = @dwCompleteTimes
		obj.wMinTurns = @wMinTurns
		obj.dwBuyTimer = @dwBuyTimer
		obj.dwBuyTimesToday = @dwBuyTimesToday
		obj.dwFinishTimesToday = @dwFinishTimesToday
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = RoleDgnInfo.new
		s.dwDgnType = ByteUtil::readUINT32(data)
		s.dwLastEnterTimer = ByteUtil::readUINT32(data)
		s.byCost = ByteUtil::readUINT8(data)
		s.dwEnterTimesAppend = ByteUtil::readUINT32(data)
		s.dwAppendEndTimer = ByteUtil::readUINT32(data)
		s.dwEnterTimes = ByteUtil::readUINT32(data)
		s.dwLastCompleteTimer = ByteUtil::readUINT32(data)
		s.dwCompleteTimes = ByteUtil::readUINT32(data)
		s.wMinTurns = ByteUtil::readUINT16(data)
		s.dwBuyTimer = ByteUtil::readUINT32(data)
		s.dwBuyTimesToday = ByteUtil::readUINT32(data)
		s.dwFinishTimesToday = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = RoleDgnInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwDgnType)
		ByteUtil::writeUINT32(data, @dwLastEnterTimer)
		ByteUtil::writeUINT8(data, @byCost)
		ByteUtil::writeUINT32(data, @dwEnterTimesAppend)
		ByteUtil::writeUINT32(data, @dwAppendEndTimer)
		ByteUtil::writeUINT32(data, @dwEnterTimes)
		ByteUtil::writeUINT32(data, @dwLastCompleteTimer)
		ByteUtil::writeUINT32(data, @dwCompleteTimes)
		ByteUtil::writeUINT16(data, @wMinTurns)
		ByteUtil::writeUINT32(data, @dwBuyTimer)
		ByteUtil::writeUINT32(data, @dwBuyTimesToday)
		ByteUtil::writeUINT32(data, @dwFinishTimesToday)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#任务存储结构
class RoleTaskInfo
	attr_accessor:dwTaskId #(UINT32)任务Id
	attr_accessor:eTaskState #(枚类型：TaskProt::ETaskState)任务状态
	attr_accessor:dwAcceptTimes #(UINT32)接受任务次数
	attr_accessor:dwLastAcceptTimer #(UINT32)最近任务接受时间
	attr_accessor:dwFinishTimes #(UINT32)完成任务次数
	attr_accessor:dwLastFinishTimer #(UINT32)最近完成任务时间
	attr_accessor:byProcessType1 #(UINT8)进度1的类型
	attr_accessor:dwProcessParam11 #(UINT32)进度1的第1个参数
	attr_accessor:dwProcessParam12 #(UINT32)进度1的第2个参数
	attr_accessor:byProcessType2 #(UINT8)进度2的类型
	attr_accessor:dwProcessParam21 #(UINT32)进度2的第1个参数
	attr_accessor:dwProcessParam22 #(UINT32)进度2的第2个参数
	attr_accessor:byProcessType3 #(UINT8)进度3的类型
	attr_accessor:dwProcessParam31 #(UINT32)进度3的第1个参数
	attr_accessor:dwProcessParam32 #(UINT32)进度3的第2个参数
	attr_accessor:dwRepeatAcceptTimes #(UINT32)当前有效接任务次数

	#构造函数
	def initialize
		@dwTaskId = 0
		@eTaskState = 0
		@dwAcceptTimes = 0
		@dwLastAcceptTimer = 0
		@dwFinishTimes = 0
		@dwLastFinishTimer = 0
		@byProcessType1 = 0
		@dwProcessParam11 = 0
		@dwProcessParam12 = 0
		@byProcessType2 = 0
		@dwProcessParam21 = 0
		@dwProcessParam22 = 0
		@byProcessType3 = 0
		@dwProcessParam31 = 0
		@dwProcessParam32 = 0
		@dwRepeatAcceptTimes = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwTaskId = @dwTaskId
		obj.eTaskState = @eTaskState
		obj.dwAcceptTimes = @dwAcceptTimes
		obj.dwLastAcceptTimer = @dwLastAcceptTimer
		obj.dwFinishTimes = @dwFinishTimes
		obj.dwLastFinishTimer = @dwLastFinishTimer
		obj.byProcessType1 = @byProcessType1
		obj.dwProcessParam11 = @dwProcessParam11
		obj.dwProcessParam12 = @dwProcessParam12
		obj.byProcessType2 = @byProcessType2
		obj.dwProcessParam21 = @dwProcessParam21
		obj.dwProcessParam22 = @dwProcessParam22
		obj.byProcessType3 = @byProcessType3
		obj.dwProcessParam31 = @dwProcessParam31
		obj.dwProcessParam32 = @dwProcessParam32
		obj.dwRepeatAcceptTimes = @dwRepeatAcceptTimes
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = RoleTaskInfo.new
		s.dwTaskId = ByteUtil::readUINT32(data)
		s.eTaskState = ByteUtil::readUINT8(data)
		s.dwAcceptTimes = ByteUtil::readUINT32(data)
		s.dwLastAcceptTimer = ByteUtil::readUINT32(data)
		s.dwFinishTimes = ByteUtil::readUINT32(data)
		s.dwLastFinishTimer = ByteUtil::readUINT32(data)
		s.byProcessType1 = ByteUtil::readUINT8(data)
		s.dwProcessParam11 = ByteUtil::readUINT32(data)
		s.dwProcessParam12 = ByteUtil::readUINT32(data)
		s.byProcessType2 = ByteUtil::readUINT8(data)
		s.dwProcessParam21 = ByteUtil::readUINT32(data)
		s.dwProcessParam22 = ByteUtil::readUINT32(data)
		s.byProcessType3 = ByteUtil::readUINT8(data)
		s.dwProcessParam31 = ByteUtil::readUINT32(data)
		s.dwProcessParam32 = ByteUtil::readUINT32(data)
		s.dwRepeatAcceptTimes = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = RoleTaskInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwTaskId)
		ByteUtil::writeUINT8(data, @eTaskState)
		ByteUtil::writeUINT32(data, @dwAcceptTimes)
		ByteUtil::writeUINT32(data, @dwLastAcceptTimer)
		ByteUtil::writeUINT32(data, @dwFinishTimes)
		ByteUtil::writeUINT32(data, @dwLastFinishTimer)
		ByteUtil::writeUINT8(data, @byProcessType1)
		ByteUtil::writeUINT32(data, @dwProcessParam11)
		ByteUtil::writeUINT32(data, @dwProcessParam12)
		ByteUtil::writeUINT8(data, @byProcessType2)
		ByteUtil::writeUINT32(data, @dwProcessParam21)
		ByteUtil::writeUINT32(data, @dwProcessParam22)
		ByteUtil::writeUINT8(data, @byProcessType3)
		ByteUtil::writeUINT32(data, @dwProcessParam31)
		ByteUtil::writeUINT32(data, @dwProcessParam32)
		ByteUtil::writeUINT32(data, @dwRepeatAcceptTimes)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家变量数据
class SVarsDBInfo
	attr_accessor:qwRoleID #(UINT64)玩家RoleId
	attr_accessor:byServerType #(UINT8)服务器类型
	attr_accessor:wVar #(UINT16)变量ID
	attr_accessor:qwValue #(UINT64)变量值
	attr_accessor:dwExpired #(UINT32)过期时间

	#构造函数
	def initialize
		@qwRoleID = 0
		@byServerType = 0
		@wVar = 0
		@qwValue = 0
		@dwExpired = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.byServerType = @byServerType
		obj.wVar = @wVar
		obj.qwValue = @qwValue
		obj.dwExpired = @dwExpired
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SVarsDBInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.byServerType = ByteUtil::readUINT8(data)
		s.wVar = ByteUtil::readUINT16(data)
		s.qwValue = ByteUtil::readUINT64(data)
		s.dwExpired = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SVarsDBInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT8(data, @byServerType)
		ByteUtil::writeUINT16(data, @wVar)
		ByteUtil::writeUINT64(data, @qwValue)
		ByteUtil::writeUINT32(data, @dwExpired)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#系统变量数据
class SGameVarsDBInfo
	attr_accessor:byServerType #(UINT8)服务器类型
	attr_accessor:wVar #(UINT16)变量ID
	attr_accessor:qwValue #(UINT64)变量值
	attr_accessor:dwExpired #(UINT32)过期时间

	#构造函数
	def initialize
		@byServerType = 0
		@wVar = 0
		@qwValue = 0
		@dwExpired = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byServerType = @byServerType
		obj.wVar = @wVar
		obj.qwValue = @qwValue
		obj.dwExpired = @dwExpired
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGameVarsDBInfo.new
		s.byServerType = ByteUtil::readUINT8(data)
		s.wVar = ByteUtil::readUINT16(data)
		s.qwValue = ByteUtil::readUINT64(data)
		s.dwExpired = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGameVarsDBInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byServerType)
		ByteUtil::writeUINT16(data, @wVar)
		ByteUtil::writeUINT64(data, @qwValue)
		ByteUtil::writeUINT32(data, @dwExpired)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#EDataType:eTypeSlotsInfo:玩家各种槽数据
class SRoleSlotsInfo
	attr_accessor:qwRoleID #(UINT64)玩家RoleID
	attr_accessor:qwOwnerID #(UINT64)槽拥有者ID
	attr_accessor:eStoreType #(枚类型：ItemProt::EStoreType)槽类型
	attr_accessor:wMaxSlot #(UINT16)槽允许的最大数量
	attr_accessor:wMaxAvaliableSlot #(UINT16)槽当前的最大数量

	#构造函数
	def initialize
		@qwRoleID = 0
		@qwOwnerID = 0
		@eStoreType = 0
		@wMaxSlot = 0
		@wMaxAvaliableSlot = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.qwOwnerID = @qwOwnerID
		obj.eStoreType = @eStoreType
		obj.wMaxSlot = @wMaxSlot
		obj.wMaxAvaliableSlot = @wMaxAvaliableSlot
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRoleSlotsInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.qwOwnerID = ByteUtil::readUINT64(data)
		s.eStoreType = ByteUtil::readUINT8(data)
		s.wMaxSlot = ByteUtil::readUINT16(data)
		s.wMaxAvaliableSlot = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRoleSlotsInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT64(data, @qwOwnerID)
		ByteUtil::writeUINT8(data, @eStoreType)
		ByteUtil::writeUINT16(data, @wMaxSlot)
		ByteUtil::writeUINT16(data, @wMaxAvaliableSlot)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#阵型信息
class SFormationInfo
	attr_accessor:wFormationID #(UINT16)阵型ID
	attr_accessor:bySelected #(UINT8)是否启用

	#构造函数
	def initialize
		@wFormationID = 0
		@bySelected = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wFormationID = @wFormationID
		obj.bySelected = @bySelected
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFormationInfo.new
		s.wFormationID = ByteUtil::readUINT16(data)
		s.bySelected = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFormationInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wFormationID)
		ByteUtil::writeUINT8(data, @bySelected)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#阵灵信息
class SPetDataInfo
	attr_accessor:wPetID #(UINT16)阵灵ID
	attr_accessor:bySelected #(UINT8)是否启用: 0-未启用 1-出战跟随 2-出战不跟随
	attr_accessor:byLevel #(UINT8)阵灵等级
	attr_accessor:dwExp #(UINT32)阵灵经验

	#构造函数
	def initialize
		@wPetID = 0
		@bySelected = 0
		@byLevel = 0
		@dwExp = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wPetID = @wPetID
		obj.bySelected = @bySelected
		obj.byLevel = @byLevel
		obj.dwExp = @dwExp
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPetDataInfo.new
		s.wPetID = ByteUtil::readUINT16(data)
		s.bySelected = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.dwExp = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPetDataInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wPetID)
		ByteUtil::writeUINT8(data, @bySelected)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwExp)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#阵灵全局信息
class SRolePetInfo
	attr_accessor:dwExp #(UINT32)阵灵经验
	attr_accessor:byLevel #(UINT8)阵灵等级
	attr_accessor:dwSpirit #(UINT32)阵灵灵力值

	#构造函数
	def initialize
		@dwExp = 0
		@byLevel = 0
		@dwSpirit = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwExp = @dwExp
		obj.byLevel = @byLevel
		obj.dwSpirit = @dwSpirit
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRolePetInfo.new
		s.dwExp = ByteUtil::readUINT32(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.dwSpirit = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRolePetInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwExp)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwSpirit)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#兽魂信息
class SBeastSoulInfo
	attr_accessor:eType #(枚举类型：EBeastSoulType)兽魂类型
	attr_accessor:byRank #(UINT8)兽魂星图等级
	attr_accessor:byLevel #(UINT8)兽魂星魂等级

	#构造函数
	def initialize
		@eType = 0
		@byRank = 0
		@byLevel = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eType = @eType
		obj.byRank = @byRank
		obj.byLevel = @byLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBeastSoulInfo.new
		s.eType = ByteUtil::readUINT8(data)
		s.byRank = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBeastSoulInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eType)
		ByteUtil::writeUINT8(data, @byRank)
		ByteUtil::writeUINT8(data, @byLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家魄空间信息
class SSoulSpaceInfo
	attr_accessor:qwRoleID #(UINT64)角色ID
	attr_accessor:dwSoulSpaceID #(UINT64)魄空间ID
	attr_accessor:dwSoulSpaceLevel #(UINT64)魄空间等级

	#构造函数
	def initialize
		@qwRoleID = 0
		@dwSoulSpaceID = 0
		@dwSoulSpaceLevel = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.dwSoulSpaceID = @dwSoulSpaceID
		obj.dwSoulSpaceLevel = @dwSoulSpaceLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSoulSpaceInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.dwSoulSpaceID = ByteUtil::readUINT64(data)
		s.dwSoulSpaceLevel = ByteUtil::readUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSoulSpaceInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT64(data, @dwSoulSpaceID)
		ByteUtil::writeUINT64(data, @dwSoulSpaceLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#EDataType:eTypeArena:玩家斗剑信息
class SRoleArenaInfo
	attr_accessor:dwLastAwardTimer #(UINT32)上次刷的那次奖励，记录系统计算时间
	attr_accessor:vecAwards #(SArenaAward的数组)奖励包状态
	attr_accessor:dwCDTime #(UINT32)战斗冷却到期时间戳
	attr_accessor:dwLadderCDTime #(UINT32)天梯战斗冷却到期时间戳
	attr_accessor:vecFlushFigter #(SFlushFighter的数组)最近刷的对手

	#构造函数
	def initialize
		@dwLastAwardTimer = 0
		@vecAwards = Array.new
		@dwCDTime = 0
		@dwLadderCDTime = 0
		@vecFlushFigter = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwLastAwardTimer = @dwLastAwardTimer
		obj.vecAwards = @vecAwards
		obj.dwCDTime = @dwCDTime
		obj.dwLadderCDTime = @dwLadderCDTime
		obj.vecFlushFigter = @vecFlushFigter
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRoleArenaInfo.new
		s.dwLastAwardTimer = ByteUtil::readUINT32(data)
		s.vecAwards = SArenaAward::vectorFromStream(data)
		s.dwCDTime = ByteUtil::readUINT32(data)
		s.dwLadderCDTime = ByteUtil::readUINT32(data)
		s.vecFlushFigter = SFlushFighter::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRoleArenaInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwLastAwardTimer)
		SArenaAward::vectorToStream(data, @vecAwards)
		ByteUtil::writeUINT32(data, @dwCDTime)
		ByteUtil::writeUINT32(data, @dwLadderCDTime)
		SFlushFighter::vectorToStream(data, @vecFlushFigter)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战报保存
class SBattleRePort
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:qwBattleID #(UINT64)战报Id
	attr_accessor:qwAttackID #(UINT64)对方ID
	attr_accessor:strAttackID #(string)对方名字
	attr_accessor:eActionType #(枚举类型：EBattleActionType)玩家战斗方式
	attr_accessor:eType #(枚举类型：EBattleReportType)战报类型
	attr_accessor:eSuc #(枚举类型：EBattleActionType)胜利方
	attr_accessor:dwTime #(UINT32)战报时间
	attr_accessor:dwParam1 #(UINT32)参数1
	attr_accessor:dwParam2 #(UINT32)参数2
	attr_accessor:dwParam3 #(UINT32)参数3
	attr_accessor:dwIndex #(UINT32)类型流水

	#构造函数
	def initialize
		@qwRoleID = 0
		@qwBattleID = 0
		@qwAttackID = 0
		@strAttackID = ''
		@eActionType = 0
		@eType = 0
		@eSuc = 0
		@dwTime = 0
		@dwParam1 = 0
		@dwParam2 = 0
		@dwParam3 = 0
		@dwIndex = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.qwBattleID = @qwBattleID
		obj.qwAttackID = @qwAttackID
		obj.strAttackID = @strAttackID
		obj.eActionType = @eActionType
		obj.eType = @eType
		obj.eSuc = @eSuc
		obj.dwTime = @dwTime
		obj.dwParam1 = @dwParam1
		obj.dwParam2 = @dwParam2
		obj.dwParam3 = @dwParam3
		obj.dwIndex = @dwIndex
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleRePort.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.qwBattleID = ByteUtil::readUINT64(data)
		s.qwAttackID = ByteUtil::readUINT64(data)
		s.strAttackID = ByteUtil::readSTRING(data)
		s.eActionType = ByteUtil::readUINT8(data)
		s.eType = ByteUtil::readUINT8(data)
		s.eSuc = ByteUtil::readUINT8(data)
		s.dwTime = ByteUtil::readUINT32(data)
		s.dwParam1 = ByteUtil::readUINT32(data)
		s.dwParam2 = ByteUtil::readUINT32(data)
		s.dwParam3 = ByteUtil::readUINT32(data)
		s.dwIndex = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleRePort::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT64(data, @qwBattleID)
		ByteUtil::writeUINT64(data, @qwAttackID)
		ByteUtil::writeSTRING(data, @strAttackID)
		ByteUtil::writeUINT8(data, @eActionType)
		ByteUtil::writeUINT8(data, @eType)
		ByteUtil::writeUINT8(data, @eSuc)
		ByteUtil::writeUINT32(data, @dwTime)
		ByteUtil::writeUINT32(data, @dwParam1)
		ByteUtil::writeUINT32(data, @dwParam2)
		ByteUtil::writeUINT32(data, @dwParam3)
		ByteUtil::writeUINT32(data, @dwIndex)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#气泡信息
class SDBBubbleInfo
	attr_accessor:qwRoleID #(UINT64)角色ID
	attr_accessor:qwTransID #(UINT64)唯一流水ID
	attr_accessor:wMsgID #(UINT16)气泡ID
	attr_accessor:dwTime #(UINT32)气泡时间
	attr_accessor:vecParam #(INT64数组)整型变量
	attr_accessor:vecString #(string数组)字符串型变量

	#构造函数
	def initialize
		@qwRoleID = 0
		@qwTransID = 0
		@wMsgID = 0
		@dwTime = 0
		@vecParam = Array.new
		@vecString = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.qwTransID = @qwTransID
		obj.wMsgID = @wMsgID
		obj.dwTime = @dwTime
		obj.vecParam = @vecParam
		obj.vecString = @vecString
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDBBubbleInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.qwTransID = ByteUtil::readUINT64(data)
		s.wMsgID = ByteUtil::readUINT16(data)
		s.dwTime = ByteUtil::readUINT32(data)
		s.vecParam = ByteUtil::readVecINT64(data)
		s.vecString = ByteUtil::readVecSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDBBubbleInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT64(data, @qwTransID)
		ByteUtil::writeUINT16(data, @wMsgID)
		ByteUtil::writeUINT32(data, @dwTime)
		ByteUtil::writeVecINT64(data, @vecParam)
		ByteUtil::writeVecSTRING(data, @vecString)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#气泡信息
class SBubbleInfo
	attr_accessor:wMsgID #(UINT16)气泡ID
	attr_accessor:wMessageID #(UINT16)消息ID
	attr_accessor:byIndex #(UINT8)气泡位置
	attr_accessor:dwTime #(UINT32)气泡时间
	attr_accessor:vecParam #(INT64数组)整型变量
	attr_accessor:vecString #(string数组)字符串型变量

	#构造函数
	def initialize
		@wMsgID = 0
		@wMessageID = 0
		@byIndex = 0
		@dwTime = 0
		@vecParam = Array.new
		@vecString = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wMsgID = @wMsgID
		obj.wMessageID = @wMessageID
		obj.byIndex = @byIndex
		obj.dwTime = @dwTime
		obj.vecParam = @vecParam
		obj.vecString = @vecString
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBubbleInfo.new
		s.wMsgID = ByteUtil::readUINT16(data)
		s.wMessageID = ByteUtil::readUINT16(data)
		s.byIndex = ByteUtil::readUINT8(data)
		s.dwTime = ByteUtil::readUINT32(data)
		s.vecParam = ByteUtil::readVecINT64(data)
		s.vecString = ByteUtil::readVecSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBubbleInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wMsgID)
		ByteUtil::writeUINT16(data, @wMessageID)
		ByteUtil::writeUINT8(data, @byIndex)
		ByteUtil::writeUINT32(data, @dwTime)
		ByteUtil::writeVecINT64(data, @vecParam)
		ByteUtil::writeVecSTRING(data, @vecString)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#师门任务
class SGroupTaskInfo
	attr_accessor:dwRepute #(UINT32)声望
	attr_accessor:byReputeLevel #(UINT8)声望等级
	attr_accessor:byBuyTimes #(UINT8)购买的师门任务数
	attr_accessor:dwFlushTask1 #(UINT32)刷的任务
	attr_accessor:eState1 #(枚类型：GroupTaskProt::EGroupTaskState)任务状态
	attr_accessor:dwFlushTask2 #(UINT32)刷的任务
	attr_accessor:eState2 #(枚类型：GroupTaskProt::EGroupTaskState)任务状态
	attr_accessor:dwFlushTask3 #(UINT32)刷的任务
	attr_accessor:eState3 #(枚类型：GroupTaskProt::EGroupTaskState)任务状态
	attr_accessor:dwFlushTask4 #(UINT32)刷的任务
	attr_accessor:eState4 #(枚类型：GroupTaskProt::EGroupTaskState)任务状态
	attr_accessor:dwFlushTask5 #(UINT32)刷的任务
	attr_accessor:eState5 #(枚类型：GroupTaskProt::EGroupTaskState)任务状态

	#构造函数
	def initialize
		@dwRepute = 0
		@byReputeLevel = 0
		@byBuyTimes = 0
		@dwFlushTask1 = 0
		@eState1 = 0
		@dwFlushTask2 = 0
		@eState2 = 0
		@dwFlushTask3 = 0
		@eState3 = 0
		@dwFlushTask4 = 0
		@eState4 = 0
		@dwFlushTask5 = 0
		@eState5 = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwRepute = @dwRepute
		obj.byReputeLevel = @byReputeLevel
		obj.byBuyTimes = @byBuyTimes
		obj.dwFlushTask1 = @dwFlushTask1
		obj.eState1 = @eState1
		obj.dwFlushTask2 = @dwFlushTask2
		obj.eState2 = @eState2
		obj.dwFlushTask3 = @dwFlushTask3
		obj.eState3 = @eState3
		obj.dwFlushTask4 = @dwFlushTask4
		obj.eState4 = @eState4
		obj.dwFlushTask5 = @dwFlushTask5
		obj.eState5 = @eState5
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGroupTaskInfo.new
		s.dwRepute = ByteUtil::readUINT32(data)
		s.byReputeLevel = ByteUtil::readUINT8(data)
		s.byBuyTimes = ByteUtil::readUINT8(data)
		s.dwFlushTask1 = ByteUtil::readUINT32(data)
		s.eState1 = ByteUtil::readUINT8(data)
		s.dwFlushTask2 = ByteUtil::readUINT32(data)
		s.eState2 = ByteUtil::readUINT8(data)
		s.dwFlushTask3 = ByteUtil::readUINT32(data)
		s.eState3 = ByteUtil::readUINT8(data)
		s.dwFlushTask4 = ByteUtil::readUINT32(data)
		s.eState4 = ByteUtil::readUINT8(data)
		s.dwFlushTask5 = ByteUtil::readUINT32(data)
		s.eState5 = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGroupTaskInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwRepute)
		ByteUtil::writeUINT8(data, @byReputeLevel)
		ByteUtil::writeUINT8(data, @byBuyTimes)
		ByteUtil::writeUINT32(data, @dwFlushTask1)
		ByteUtil::writeUINT8(data, @eState1)
		ByteUtil::writeUINT32(data, @dwFlushTask2)
		ByteUtil::writeUINT8(data, @eState2)
		ByteUtil::writeUINT32(data, @dwFlushTask3)
		ByteUtil::writeUINT8(data, @eState3)
		ByteUtil::writeUINT32(data, @dwFlushTask4)
		ByteUtil::writeUINT8(data, @eState4)
		ByteUtil::writeUINT32(data, @dwFlushTask5)
		ByteUtil::writeUINT8(data, @eState5)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#衙门任务
class SYaMenTaskInfo
	attr_accessor:dwHoly #(UINT32)圣义值
	attr_accessor:byHolyLevel #(UINT8)圣义等级
	attr_accessor:byBuyTimes #(UINT8)购买的衙门任务数
	attr_accessor:dwFlushTask1 #(UINT32)刷的任务
	attr_accessor:eState1 #(枚类型：YaMenTaskProt::EYaMenTaskState)任务状态
	attr_accessor:dwFlushTask2 #(UINT32)刷的任务
	attr_accessor:eState2 #(枚类型：YaMenTaskProt::EYaMenTaskState)任务状态
	attr_accessor:dwFlushTask3 #(UINT32)刷的任务
	attr_accessor:eState3 #(枚类型：YaMenTaskProt::EYaMenTaskState)任务状态
	attr_accessor:dwFlushTask4 #(UINT32)刷的任务
	attr_accessor:eState4 #(枚类型：YaMenTaskProt::EYaMenTaskState)任务状态
	attr_accessor:dwFlushTask5 #(UINT32)刷的任务
	attr_accessor:eState5 #(枚类型：YaMenTaskProt::EYaMenTaskState)任务状态

	#构造函数
	def initialize
		@dwHoly = 0
		@byHolyLevel = 0
		@byBuyTimes = 0
		@dwFlushTask1 = 0
		@eState1 = 0
		@dwFlushTask2 = 0
		@eState2 = 0
		@dwFlushTask3 = 0
		@eState3 = 0
		@dwFlushTask4 = 0
		@eState4 = 0
		@dwFlushTask5 = 0
		@eState5 = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwHoly = @dwHoly
		obj.byHolyLevel = @byHolyLevel
		obj.byBuyTimes = @byBuyTimes
		obj.dwFlushTask1 = @dwFlushTask1
		obj.eState1 = @eState1
		obj.dwFlushTask2 = @dwFlushTask2
		obj.eState2 = @eState2
		obj.dwFlushTask3 = @dwFlushTask3
		obj.eState3 = @eState3
		obj.dwFlushTask4 = @dwFlushTask4
		obj.eState4 = @eState4
		obj.dwFlushTask5 = @dwFlushTask5
		obj.eState5 = @eState5
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SYaMenTaskInfo.new
		s.dwHoly = ByteUtil::readUINT32(data)
		s.byHolyLevel = ByteUtil::readUINT8(data)
		s.byBuyTimes = ByteUtil::readUINT8(data)
		s.dwFlushTask1 = ByteUtil::readUINT32(data)
		s.eState1 = ByteUtil::readUINT8(data)
		s.dwFlushTask2 = ByteUtil::readUINT32(data)
		s.eState2 = ByteUtil::readUINT8(data)
		s.dwFlushTask3 = ByteUtil::readUINT32(data)
		s.eState3 = ByteUtil::readUINT8(data)
		s.dwFlushTask4 = ByteUtil::readUINT32(data)
		s.eState4 = ByteUtil::readUINT8(data)
		s.dwFlushTask5 = ByteUtil::readUINT32(data)
		s.eState5 = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SYaMenTaskInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwHoly)
		ByteUtil::writeUINT8(data, @byHolyLevel)
		ByteUtil::writeUINT8(data, @byBuyTimes)
		ByteUtil::writeUINT32(data, @dwFlushTask1)
		ByteUtil::writeUINT8(data, @eState1)
		ByteUtil::writeUINT32(data, @dwFlushTask2)
		ByteUtil::writeUINT8(data, @eState2)
		ByteUtil::writeUINT32(data, @dwFlushTask3)
		ByteUtil::writeUINT8(data, @eState3)
		ByteUtil::writeUINT32(data, @dwFlushTask4)
		ByteUtil::writeUINT8(data, @eState4)
		ByteUtil::writeUINT32(data, @dwFlushTask5)
		ByteUtil::writeUINT8(data, @eState5)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#活跃任务
class SActivityTaskInfo
	attr_accessor:wId #(UINT16)活跃触发点ID
	attr_accessor:byTimes #(UINT8)完成次数
	attr_accessor:byIsSpecial #(UINT8)是否特别任务

	#构造函数
	def initialize
		@wId = 0
		@byTimes = 0
		@byIsSpecial = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wId = @wId
		obj.byTimes = @byTimes
		obj.byIsSpecial = @byIsSpecial
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SActivityTaskInfo.new
		s.wId = ByteUtil::readUINT16(data)
		s.byTimes = ByteUtil::readUINT8(data)
		s.byIsSpecial = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SActivityTaskInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wId)
		ByteUtil::writeUINT8(data, @byTimes)
		ByteUtil::writeUINT8(data, @byIsSpecial)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#头衔
class STitle
	attr_accessor:wId #(UINT16)头衔ID
	attr_accessor:byEquipPos #(UINT8)装备位,从1开始，0表示未装备
	attr_accessor:dwValidTime #(UINT32)有效截止时间,0表示永久

	#构造函数
	def initialize
		@wId = 0
		@byEquipPos = 0
		@dwValidTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wId = @wId
		obj.byEquipPos = @byEquipPos
		obj.dwValidTime = @dwValidTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STitle.new
		s.wId = ByteUtil::readUINT16(data)
		s.byEquipPos = ByteUtil::readUINT8(data)
		s.dwValidTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STitle::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wId)
		ByteUtil::writeUINT8(data, @byEquipPos)
		ByteUtil::writeUINT32(data, @dwValidTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#暂存信息
class SPendRes
	attr_accessor:byResType #(UINT8)类型
	attr_accessor:dwValue #(UINT32)数据
	attr_accessor:bySource #(UINT8)暂存原因0,战斗，1副本
	attr_accessor:dwParam #(UINT32)参数

	#构造函数
	def initialize
		@byResType = 0
		@dwValue = 0
		@bySource = 0
		@dwParam = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byResType = @byResType
		obj.dwValue = @dwValue
		obj.bySource = @bySource
		obj.dwParam = @dwParam
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPendRes.new
		s.byResType = ByteUtil::readUINT8(data)
		s.dwValue = ByteUtil::readUINT32(data)
		s.bySource = ByteUtil::readUINT8(data)
		s.dwParam = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPendRes::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byResType)
		ByteUtil::writeUINT32(data, @dwValue)
		ByteUtil::writeUINT8(data, @bySource)
		ByteUtil::writeUINT32(data, @dwParam)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#事件信息
class SEventInfo
	attr_accessor:qwRoleID #(UINT64)角色ID
	attr_accessor:byActClassID #(UINT8)活动类型ID
	attr_accessor:dwEventInstID #(UINT32)事件实例ID
	attr_accessor:dwApplyID #(UINT32)具体活动ID
	attr_accessor:wEventStatus #(UINT16)事件状态
	attr_accessor:bySave #(UINT8)是否存数据库
	attr_accessor:dwParam1 #(UINT32)统计参数1
	attr_accessor:dwParam2 #(INT32)统计参数2
	attr_accessor:dwStartTime #(UINT32)开始时间
	attr_accessor:dwEndTime #(UINT32)结束时间

	#构造函数
	def initialize
		@qwRoleID = 0
		@byActClassID = 0
		@dwEventInstID = 0
		@dwApplyID = 0
		@wEventStatus = 0
		@bySave = 0
		@dwParam1 = 0
		@dwParam2 = 0
		@dwStartTime = 0
		@dwEndTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.byActClassID = @byActClassID
		obj.dwEventInstID = @dwEventInstID
		obj.dwApplyID = @dwApplyID
		obj.wEventStatus = @wEventStatus
		obj.bySave = @bySave
		obj.dwParam1 = @dwParam1
		obj.dwParam2 = @dwParam2
		obj.dwStartTime = @dwStartTime
		obj.dwEndTime = @dwEndTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEventInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.byActClassID = ByteUtil::readUINT8(data)
		s.dwEventInstID = ByteUtil::readUINT32(data)
		s.dwApplyID = ByteUtil::readUINT32(data)
		s.wEventStatus = ByteUtil::readUINT16(data)
		s.bySave = ByteUtil::readUINT8(data)
		s.dwParam1 = ByteUtil::readUINT32(data)
		s.dwParam2 = ByteUtil::readINT32(data)
		s.dwStartTime = ByteUtil::readUINT32(data)
		s.dwEndTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEventInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT8(data, @byActClassID)
		ByteUtil::writeUINT32(data, @dwEventInstID)
		ByteUtil::writeUINT32(data, @dwApplyID)
		ByteUtil::writeUINT16(data, @wEventStatus)
		ByteUtil::writeUINT8(data, @bySave)
		ByteUtil::writeUINT32(data, @dwParam1)
		ByteUtil::writeINT32(data, @dwParam2)
		ByteUtil::writeUINT32(data, @dwStartTime)
		ByteUtil::writeUINT32(data, @dwEndTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#离线事件
class SEventOffLine
	attr_accessor:byServerType #(UINT8)服务器类型
	attr_accessor:dwEventType #(UINT32)事件类型
	attr_accessor:dwTime #(UINT32)发生时间
	attr_accessor:strParam1 #(string)TVecUINT32
	attr_accessor:strParam2 #(string)字符参数

	#构造函数
	def initialize
		@byServerType = 0
		@dwEventType = 0
		@dwTime = 0
		@strParam1 = ''
		@strParam2 = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byServerType = @byServerType
		obj.dwEventType = @dwEventType
		obj.dwTime = @dwTime
		obj.strParam1 = @strParam1
		obj.strParam2 = @strParam2
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEventOffLine.new
		s.byServerType = ByteUtil::readUINT8(data)
		s.dwEventType = ByteUtil::readUINT32(data)
		s.dwTime = ByteUtil::readUINT32(data)
		s.strParam1 = ByteUtil::readSTRING(data)
		s.strParam2 = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEventOffLine::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byServerType)
		ByteUtil::writeUINT32(data, @dwEventType)
		ByteUtil::writeUINT32(data, @dwTime)
		ByteUtil::writeSTRING(data, @strParam1)
		ByteUtil::writeSTRING(data, @strParam2)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#物品购买数量db信息
class SBuyItemDBInfo
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:dwInstID #(UINT32)实例ID
	attr_accessor:dwCount #(UINT32)物品数量

	#构造函数
	def initialize
		@qwRoleID = 0
		@dwInstID = 0
		@dwCount = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.dwInstID = @dwInstID
		obj.dwCount = @dwCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBuyItemDBInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.dwInstID = ByteUtil::readUINT32(data)
		s.dwCount = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBuyItemDBInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT32(data, @dwInstID)
		ByteUtil::writeUINT32(data, @dwCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#7日目标活动信息
class SDayTargetDBInfo
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:wTaskID #(UINT16)任务ID
	attr_accessor:byStatus #(UINT8)任务状态
	attr_accessor:dwProcess #(UINT32)任务进度

	#构造函数
	def initialize
		@qwRoleID = 0
		@wTaskID = 0
		@byStatus = 0
		@dwProcess = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wTaskID = @wTaskID
		obj.byStatus = @byStatus
		obj.dwProcess = @dwProcess
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDayTargetDBInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wTaskID = ByteUtil::readUINT16(data)
		s.byStatus = ByteUtil::readUINT8(data)
		s.dwProcess = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDayTargetDBInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wTaskID)
		ByteUtil::writeUINT8(data, @byStatus)
		ByteUtil::writeUINT32(data, @dwProcess)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#破阵信息
class SBattleArrayDBInfo
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:wBattleArrayID #(UINT16)阵id
	attr_accessor:dwBattleArrayLevelID #(UINT32)进度(阵图id)
	attr_accessor:byBattleArrayStatus #(UINT8)状态

	#构造函数
	def initialize
		@qwRoleID = 0
		@wBattleArrayID = 0
		@dwBattleArrayLevelID = 0
		@byBattleArrayStatus = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wBattleArrayID = @wBattleArrayID
		obj.dwBattleArrayLevelID = @dwBattleArrayLevelID
		obj.byBattleArrayStatus = @byBattleArrayStatus
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleArrayDBInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wBattleArrayID = ByteUtil::readUINT16(data)
		s.dwBattleArrayLevelID = ByteUtil::readUINT32(data)
		s.byBattleArrayStatus = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleArrayDBInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wBattleArrayID)
		ByteUtil::writeUINT32(data, @dwBattleArrayLevelID)
		ByteUtil::writeUINT8(data, @byBattleArrayStatus)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#动态存储信息
class SAutoStoreDBInfo
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:wType #(UINT16)大类
	attr_accessor:dwClassID #(UINT32)小类
	attr_accessor:dwValue #(UINT32)数值

	#构造函数
	def initialize
		@qwRoleID = 0
		@wType = 0
		@dwClassID = 0
		@dwValue = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wType = @wType
		obj.dwClassID = @dwClassID
		obj.dwValue = @dwValue
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SAutoStoreDBInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wType = ByteUtil::readUINT16(data)
		s.dwClassID = ByteUtil::readUINT32(data)
		s.dwValue = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SAutoStoreDBInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wType)
		ByteUtil::writeUINT32(data, @dwClassID)
		ByteUtil::writeUINT32(data, @dwValue)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#新阵型信息
class SFightFormationDBInfo
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:wBattleType #(UINT16)战斗类型
	attr_accessor:wFormationID #(UINT16)当前阵形ID
	attr_accessor:strBattlePosInfo #(string)阵型信息

	#构造函数
	def initialize
		@qwRoleID = 0
		@wBattleType = 0
		@wFormationID = 0
		@strBattlePosInfo = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wBattleType = @wBattleType
		obj.wFormationID = @wFormationID
		obj.strBattlePosInfo = @strBattlePosInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFightFormationDBInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wBattleType = ByteUtil::readUINT16(data)
		s.wFormationID = ByteUtil::readUINT16(data)
		s.strBattlePosInfo = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFightFormationDBInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wBattleType)
		ByteUtil::writeUINT16(data, @wFormationID)
		ByteUtil::writeSTRING(data, @strBattlePosInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战斗散仙数据
class SFightHeroDBInfo
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:wBattleType #(UINT16)战斗类型
	attr_accessor:qwInstID #(UINT64)散仙instID
	attr_accessor:dwHP #(UINT32)当前生命值
	attr_accessor:dwMaxHP #(UINT32)最大生命值（可能用到）
	attr_accessor:dwAura #(UINT32)灵气值
	attr_accessor:dwMaxAura #(UINT32)灵气值

	#构造函数
	def initialize
		@qwRoleID = 0
		@wBattleType = 0
		@qwInstID = 0
		@dwHP = 0
		@dwMaxHP = 0
		@dwAura = 0
		@dwMaxAura = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wBattleType = @wBattleType
		obj.qwInstID = @qwInstID
		obj.dwHP = @dwHP
		obj.dwMaxHP = @dwMaxHP
		obj.dwAura = @dwAura
		obj.dwMaxAura = @dwMaxAura
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFightHeroDBInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wBattleType = ByteUtil::readUINT16(data)
		s.qwInstID = ByteUtil::readUINT64(data)
		s.dwHP = ByteUtil::readUINT32(data)
		s.dwMaxHP = ByteUtil::readUINT32(data)
		s.dwAura = ByteUtil::readUINT32(data)
		s.dwMaxAura = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFightHeroDBInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wBattleType)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT32(data, @dwHP)
		ByteUtil::writeUINT32(data, @dwMaxHP)
		ByteUtil::writeUINT32(data, @dwAura)
		ByteUtil::writeUINT32(data, @dwMaxAura)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家整体数据
class RoleDataInfo
	attr_accessor:qwRoleId #(UINT64)玩家RoleId
	attr_accessor:stBaseInfo #(类类型：RoleBaseInfo)玩家基本数据成员
	attr_accessor:vecFighterInfo #(SFighterDBInfo的数组)将信息
	attr_accessor:vecSkillInfo #(SSkillDBInfo的数组)将技能信息
	attr_accessor:vecPassiveSkillInfo #(SPassiveSkillDBInfo的数组)将技能信息
	attr_accessor:vecFighterCombination #(SFighterCombination的数组)玩家的散仙组合信息
	attr_accessor:vecRoleItemInfo #(SItem的数组)玩家物品成员
	attr_accessor:vecFriendsInfo #(SFriendDBInfo的数组)好友信息
	attr_accessor:vecRoleDgnInfo #(RoleDgnInfo的数组)玩家副本信息
	attr_accessor:vecRoleTaskInfo #(RoleTaskInfo的数组)玩家任务信息
	attr_accessor:vecGameVars #(SVarsDBInfo的数组)玩家身上Game上的变量任务信息
	attr_accessor:vecRoleSlotsInfo #(SRoleSlotsInfo的数组)玩家身上的槽的信息
	attr_accessor:vecFormationInfo #(SFormationInfo的数组)玩家的阵形信息
	attr_accessor:vecPetDataInfo #(SPetDataInfo的数组)玩家的阵灵信息
	attr_accessor:oRolePetInfo #(类类型：SRolePetInfo)玩家的阵形全局信息
	attr_accessor:vecBeastSoulInfo #(SBeastSoulInfo的数组)玩家的兽魂信息
	attr_accessor:vecFireInfo #(SFireInfo的数组)玩家九疑鼎的火种信息
	attr_accessor:vecArenaInfo #(SRoleArenaInfo的数组)玩家斗剑信息
	attr_accessor:vecDBBuffInfo #(SDBBuffInfo的数组)玩家Buff信息
	attr_accessor:vecSoulSpaceInfo #(SSoulSpaceInfo的数组)玩家魄空间信息
	attr_accessor:vecBubbleInfo #(SDBBubbleInfo的数组)玩家气泡信息
	attr_accessor:vecHorseDB #(SHorseDB的数组)玩家魄坐骑信息
	attr_accessor:sGroupInfo #(类类型：SGroupTaskInfo)师门任务信息
	attr_accessor:sYaMenInfo #(类类型：SYaMenTaskInfo)衙门任务信息
	attr_accessor:vecActivityTask #(SActivityTaskInfo的数组)活跃度任务信息
	attr_accessor:vecTitle #(STitle的数组)称号信息
	attr_accessor:vecAchievementInfo #(SAchievementInfo的数组)成就信息
	attr_accessor:vecCollectionInfo #(SCollectionInfo的数组)收藏信息
	attr_accessor:vecRoleAttaked #(SRoleAttaked的数组)玩家被攻击信息列表
	attr_accessor:vecExchangeInfo #(ExchangeInfo的数组)玩家兑换信息列表
	attr_accessor:vecSweepInfo #(SSweepInfo的数组)玩家兑换信息列表
	attr_accessor:vecPendRes #(SPendRes的数组)玩家暂存资源列表
	attr_accessor:vecXinFaDBInfo #(SXinFaDBInfo的数组)玩家心法信息
	attr_accessor:vecLevelPrize #(SPrize2DB的数组)玩家条件奖励信息
	attr_accessor:vecPlatformParam #(SPlatformParam的数组)玩家平台信息
	attr_accessor:vecEventInfo #(SEventInfo的数组)事件信息
	attr_accessor:vecEventOffLine #(SEventOffLine的数组)离线事件
	attr_accessor:vecBuyItemDBInfo #(SBuyItemDBInfo的数组)商品购买数量
	attr_accessor:vecDayTargetDBInfo #(SDayTargetDBInfo的数组)7日目标活动信息
	attr_accessor:vecBattleArrayDBInfo #(SBattleArrayDBInfo的数组)破阵信息
	attr_accessor:vecAutoStoreDBInfo #(SAutoStoreDBInfo的数组)动态存储信息
	attr_accessor:vecTHDBInfo #(STHDBInfo的数组)玩家寻宝信息
	attr_accessor:vecBeauty #(SBeauty的数组)美女信息
	attr_accessor:vecFightFormationDBInfo #(SFightFormationDBInfo的数组)新阵型信息
	attr_accessor:vecFightHeroDBInfo #(SFightHeroDBInfo的数组)战斗散仙数据
	attr_accessor:sShipData #(类类型：ShipProt::PlayerSelfShipData)自己运船信息
	attr_accessor:vecShipReport #(ShipReport的数组)战报信息
	attr_accessor:vecGEMDBInfo #(SGEMDBInfo的数组)玩家守卫峨眉信息
	attr_accessor:vecShengLing #(SShengLingInfo2DB的数组)玩家圣陵信息
	attr_accessor:vecShengLingPrize #(SShengLingPrize2DB的数组)玩家圣陵奖励

	#构造函数
	def initialize
		@qwRoleId = 0
		@stBaseInfo = RoleBaseInfo.new
		@vecFighterInfo = Array.new
		@vecSkillInfo = Array.new
		@vecPassiveSkillInfo = Array.new
		@vecFighterCombination = Array.new
		@vecRoleItemInfo = Array.new
		@vecFriendsInfo = Array.new
		@vecRoleDgnInfo = Array.new
		@vecRoleTaskInfo = Array.new
		@vecGameVars = Array.new
		@vecRoleSlotsInfo = Array.new
		@vecFormationInfo = Array.new
		@vecPetDataInfo = Array.new
		@oRolePetInfo = SRolePetInfo.new
		@vecBeastSoulInfo = Array.new
		@vecFireInfo = Array.new
		@vecArenaInfo = Array.new
		@vecDBBuffInfo = Array.new
		@vecSoulSpaceInfo = Array.new
		@vecBubbleInfo = Array.new
		@vecHorseDB = Array.new
		@sGroupInfo = SGroupTaskInfo.new
		@sYaMenInfo = SYaMenTaskInfo.new
		@vecActivityTask = Array.new
		@vecTitle = Array.new
		@vecAchievementInfo = Array.new
		@vecCollectionInfo = Array.new
		@vecRoleAttaked = Array.new
		@vecExchangeInfo = Array.new
		@vecSweepInfo = Array.new
		@vecPendRes = Array.new
		@vecXinFaDBInfo = Array.new
		@vecLevelPrize = Array.new
		@vecPlatformParam = Array.new
		@vecEventInfo = Array.new
		@vecEventOffLine = Array.new
		@vecBuyItemDBInfo = Array.new
		@vecDayTargetDBInfo = Array.new
		@vecBattleArrayDBInfo = Array.new
		@vecAutoStoreDBInfo = Array.new
		@vecTHDBInfo = Array.new
		@vecBeauty = Array.new
		@vecFightFormationDBInfo = Array.new
		@vecFightHeroDBInfo = Array.new
		@sShipData = PlayerSelfShipData.new
		@vecShipReport = Array.new
		@vecGEMDBInfo = Array.new
		@vecShengLing = Array.new
		@vecShengLingPrize = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleId = @qwRoleId
		obj.stBaseInfo = @stBaseInfo
		obj.vecFighterInfo = @vecFighterInfo
		obj.vecSkillInfo = @vecSkillInfo
		obj.vecPassiveSkillInfo = @vecPassiveSkillInfo
		obj.vecFighterCombination = @vecFighterCombination
		obj.vecRoleItemInfo = @vecRoleItemInfo
		obj.vecFriendsInfo = @vecFriendsInfo
		obj.vecRoleDgnInfo = @vecRoleDgnInfo
		obj.vecRoleTaskInfo = @vecRoleTaskInfo
		obj.vecGameVars = @vecGameVars
		obj.vecRoleSlotsInfo = @vecRoleSlotsInfo
		obj.vecFormationInfo = @vecFormationInfo
		obj.vecPetDataInfo = @vecPetDataInfo
		obj.oRolePetInfo = @oRolePetInfo
		obj.vecBeastSoulInfo = @vecBeastSoulInfo
		obj.vecFireInfo = @vecFireInfo
		obj.vecArenaInfo = @vecArenaInfo
		obj.vecDBBuffInfo = @vecDBBuffInfo
		obj.vecSoulSpaceInfo = @vecSoulSpaceInfo
		obj.vecBubbleInfo = @vecBubbleInfo
		obj.vecHorseDB = @vecHorseDB
		obj.sGroupInfo = @sGroupInfo
		obj.sYaMenInfo = @sYaMenInfo
		obj.vecActivityTask = @vecActivityTask
		obj.vecTitle = @vecTitle
		obj.vecAchievementInfo = @vecAchievementInfo
		obj.vecCollectionInfo = @vecCollectionInfo
		obj.vecRoleAttaked = @vecRoleAttaked
		obj.vecExchangeInfo = @vecExchangeInfo
		obj.vecSweepInfo = @vecSweepInfo
		obj.vecPendRes = @vecPendRes
		obj.vecXinFaDBInfo = @vecXinFaDBInfo
		obj.vecLevelPrize = @vecLevelPrize
		obj.vecPlatformParam = @vecPlatformParam
		obj.vecEventInfo = @vecEventInfo
		obj.vecEventOffLine = @vecEventOffLine
		obj.vecBuyItemDBInfo = @vecBuyItemDBInfo
		obj.vecDayTargetDBInfo = @vecDayTargetDBInfo
		obj.vecBattleArrayDBInfo = @vecBattleArrayDBInfo
		obj.vecAutoStoreDBInfo = @vecAutoStoreDBInfo
		obj.vecTHDBInfo = @vecTHDBInfo
		obj.vecBeauty = @vecBeauty
		obj.vecFightFormationDBInfo = @vecFightFormationDBInfo
		obj.vecFightHeroDBInfo = @vecFightHeroDBInfo
		obj.sShipData = @sShipData
		obj.vecShipReport = @vecShipReport
		obj.vecGEMDBInfo = @vecGEMDBInfo
		obj.vecShengLing = @vecShengLing
		obj.vecShengLingPrize = @vecShengLingPrize
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = RoleDataInfo.new
		s.qwRoleId = ByteUtil::readUINT64(data)
		s.stBaseInfo = RoleBaseInfo::fromStream(data)
		s.vecFighterInfo = SFighterDBInfo::vectorFromStream(data)
		s.vecSkillInfo = SSkillDBInfo::vectorFromStream(data)
		s.vecPassiveSkillInfo = SPassiveSkillDBInfo::vectorFromStream(data)
		s.vecFighterCombination = SFighterCombination::vectorFromStream(data)
		s.vecRoleItemInfo = SItem::superVectorFromStream(data)
		s.vecFriendsInfo = SFriendDBInfo::vectorFromStream(data)
		s.vecRoleDgnInfo = RoleDgnInfo::vectorFromStream(data)
		s.vecRoleTaskInfo = RoleTaskInfo::vectorFromStream(data)
		s.vecGameVars = SVarsDBInfo::vectorFromStream(data)
		s.vecRoleSlotsInfo = SRoleSlotsInfo::vectorFromStream(data)
		s.vecFormationInfo = SFormationInfo::vectorFromStream(data)
		s.vecPetDataInfo = SPetDataInfo::vectorFromStream(data)
		s.oRolePetInfo = SRolePetInfo::fromStream(data)
		s.vecBeastSoulInfo = SBeastSoulInfo::vectorFromStream(data)
		s.vecFireInfo = SFireInfo::vectorFromStream(data)
		s.vecArenaInfo = SRoleArenaInfo::vectorFromStream(data)
		s.vecDBBuffInfo = SDBBuffInfo::vectorFromStream(data)
		s.vecSoulSpaceInfo = SSoulSpaceInfo::vectorFromStream(data)
		s.vecBubbleInfo = SDBBubbleInfo::vectorFromStream(data)
		s.vecHorseDB = SHorseDB::vectorFromStream(data)
		s.sGroupInfo = SGroupTaskInfo::fromStream(data)
		s.sYaMenInfo = SYaMenTaskInfo::fromStream(data)
		s.vecActivityTask = SActivityTaskInfo::vectorFromStream(data)
		s.vecTitle = STitle::vectorFromStream(data)
		s.vecAchievementInfo = SAchievementInfo::vectorFromStream(data)
		s.vecCollectionInfo = SCollectionInfo::vectorFromStream(data)
		s.vecRoleAttaked = SRoleAttaked::vectorFromStream(data)
		s.vecExchangeInfo = ExchangeInfo::vectorFromStream(data)
		s.vecSweepInfo = SSweepInfo::vectorFromStream(data)
		s.vecPendRes = SPendRes::vectorFromStream(data)
		s.vecXinFaDBInfo = SXinFaDBInfo::vectorFromStream(data)
		s.vecLevelPrize = SPrize2DB::vectorFromStream(data)
		s.vecPlatformParam = SPlatformParam::vectorFromStream(data)
		s.vecEventInfo = SEventInfo::vectorFromStream(data)
		s.vecEventOffLine = SEventOffLine::vectorFromStream(data)
		s.vecBuyItemDBInfo = SBuyItemDBInfo::vectorFromStream(data)
		s.vecDayTargetDBInfo = SDayTargetDBInfo::vectorFromStream(data)
		s.vecBattleArrayDBInfo = SBattleArrayDBInfo::vectorFromStream(data)
		s.vecAutoStoreDBInfo = SAutoStoreDBInfo::vectorFromStream(data)
		s.vecTHDBInfo = STHDBInfo::vectorFromStream(data)
		s.vecBeauty = SBeauty::vectorFromStream(data)
		s.vecFightFormationDBInfo = SFightFormationDBInfo::vectorFromStream(data)
		s.vecFightHeroDBInfo = SFightHeroDBInfo::vectorFromStream(data)
		s.sShipData = PlayerSelfShipData::fromStream(data)
		s.vecShipReport = ShipReport::vectorFromStream(data)
		s.vecGEMDBInfo = SGEMDBInfo::vectorFromStream(data)
		s.vecShengLing = SShengLingInfo2DB::vectorFromStream(data)
		s.vecShengLingPrize = SShengLingPrize2DB::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = RoleDataInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleId)
		@stBaseInfo.toStream(data)
		SFighterDBInfo::vectorToStream(data, @vecFighterInfo)
		SSkillDBInfo::vectorToStream(data, @vecSkillInfo)
		SPassiveSkillDBInfo::vectorToStream(data, @vecPassiveSkillInfo)
		SFighterCombination::vectorToStream(data, @vecFighterCombination)
		SItem::superVectorToStream(data, @vecRoleItemInfo)
		SFriendDBInfo::vectorToStream(data, @vecFriendsInfo)
		RoleDgnInfo::vectorToStream(data, @vecRoleDgnInfo)
		RoleTaskInfo::vectorToStream(data, @vecRoleTaskInfo)
		SVarsDBInfo::vectorToStream(data, @vecGameVars)
		SRoleSlotsInfo::vectorToStream(data, @vecRoleSlotsInfo)
		SFormationInfo::vectorToStream(data, @vecFormationInfo)
		SPetDataInfo::vectorToStream(data, @vecPetDataInfo)
		@oRolePetInfo.toStream(data)
		SBeastSoulInfo::vectorToStream(data, @vecBeastSoulInfo)
		SFireInfo::vectorToStream(data, @vecFireInfo)
		SRoleArenaInfo::vectorToStream(data, @vecArenaInfo)
		SDBBuffInfo::vectorToStream(data, @vecDBBuffInfo)
		SSoulSpaceInfo::vectorToStream(data, @vecSoulSpaceInfo)
		SDBBubbleInfo::vectorToStream(data, @vecBubbleInfo)
		SHorseDB::vectorToStream(data, @vecHorseDB)
		@sGroupInfo.toStream(data)
		@sYaMenInfo.toStream(data)
		SActivityTaskInfo::vectorToStream(data, @vecActivityTask)
		STitle::vectorToStream(data, @vecTitle)
		SAchievementInfo::vectorToStream(data, @vecAchievementInfo)
		SCollectionInfo::vectorToStream(data, @vecCollectionInfo)
		SRoleAttaked::vectorToStream(data, @vecRoleAttaked)
		ExchangeInfo::vectorToStream(data, @vecExchangeInfo)
		SSweepInfo::vectorToStream(data, @vecSweepInfo)
		SPendRes::vectorToStream(data, @vecPendRes)
		SXinFaDBInfo::vectorToStream(data, @vecXinFaDBInfo)
		SPrize2DB::vectorToStream(data, @vecLevelPrize)
		SPlatformParam::vectorToStream(data, @vecPlatformParam)
		SEventInfo::vectorToStream(data, @vecEventInfo)
		SEventOffLine::vectorToStream(data, @vecEventOffLine)
		SBuyItemDBInfo::vectorToStream(data, @vecBuyItemDBInfo)
		SDayTargetDBInfo::vectorToStream(data, @vecDayTargetDBInfo)
		SBattleArrayDBInfo::vectorToStream(data, @vecBattleArrayDBInfo)
		SAutoStoreDBInfo::vectorToStream(data, @vecAutoStoreDBInfo)
		STHDBInfo::vectorToStream(data, @vecTHDBInfo)
		SBeauty::vectorToStream(data, @vecBeauty)
		SFightFormationDBInfo::vectorToStream(data, @vecFightFormationDBInfo)
		SFightHeroDBInfo::vectorToStream(data, @vecFightHeroDBInfo)
		@sShipData.toStream(data)
		ShipReport::vectorToStream(data, @vecShipReport)
		SGEMDBInfo::vectorToStream(data, @vecGEMDBInfo)
		SShengLingInfo2DB::vectorToStream(data, @vecShengLing)
		SShengLingPrize2DB::vectorToStream(data, @vecShengLingPrize)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#DB存储玩家充值仙石的结构体
class SRecharge
	attr_accessor:strNo #(string)充值流水号
	attr_accessor:qwRoleID #(UINT64)用户ID
	attr_accessor:wGoldID #(UINT16)仙石包ID(41[10仙石],42[100仙石],43[300仙石],44[500仙石],45[1000仙石],46[3000仙石])
	attr_accessor:dwCount #(UINT32)充值的仙石包数量
	attr_accessor:dwGold #(UINT32)充值的仙石总数
	attr_accessor:byStatus #(UINT8)仙石是否到账(0-准备/不成功 1-成功,2-补单成功)
	attr_accessor:dwHappenedTime #(UINT32)充值时间

	#构造函数
	def initialize
		@strNo = ''
		@qwRoleID = 0
		@wGoldID = 0
		@dwCount = 0
		@dwGold = 0
		@byStatus = 0
		@dwHappenedTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strNo = @strNo
		obj.qwRoleID = @qwRoleID
		obj.wGoldID = @wGoldID
		obj.dwCount = @dwCount
		obj.dwGold = @dwGold
		obj.byStatus = @byStatus
		obj.dwHappenedTime = @dwHappenedTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRecharge.new
		s.strNo = ByteUtil::readSTRING(data)
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wGoldID = ByteUtil::readUINT16(data)
		s.dwCount = ByteUtil::readUINT32(data)
		s.dwGold = ByteUtil::readUINT32(data)
		s.byStatus = ByteUtil::readUINT8(data)
		s.dwHappenedTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRecharge::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeSTRING(data, @strNo)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wGoldID)
		ByteUtil::writeUINT32(data, @dwCount)
		ByteUtil::writeUINT32(data, @dwGold)
		ByteUtil::writeUINT8(data, @byStatus)
		ByteUtil::writeUINT32(data, @dwHappenedTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#DB存储玩家未创角预先充值仙石的结构体
class SPrepaid
	attr_accessor:qwRoleID #(UINT64)用户ID
	attr_accessor:dwGold #(UINT32)预先充值的仙石总数量

	#构造函数
	def initialize
		@qwRoleID = 0
		@dwGold = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.dwGold = @dwGold
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPrepaid.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.dwGold = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPrepaid::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT32(data, @dwGold)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#协议类：角色数据定义
class RoleInfoDefineBase < ProtocolBase
	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 10;
		@recvFuncList = Array.new
	end

	def handleMessage(data)
		return true;
	end
end

