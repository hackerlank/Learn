#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    LogDataDefine.rb
#  Purpose:      日志数据定义
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './MailProtBase.rb'

#以下为类型定义

#副本操作
class EDgnOpType
	EDGNOPTYPE_CREATE = 0#副本创建
	EDGNOPTYPE_PLAYERENTER = 1#玩家进入
	EDGNOPTYPE_PLAYERLEAVE = 2#玩家退出
	EDGNOPTYPE_FINISH = 3#副本完成
	EDGNOPTYPE_DESTROY = 4#副本销毁
end

#获得物品/或者货币
class ItemFrom
	ITEMFROM_GM = 1#GM指令里得到的物品
	ITEMFROM_INLUABOX = 2#lua脚本使用宝箱获得
	ITEMFROM_SYSTEM = 3#系统奖励
	ITEMFROM_EDGN = 4#副本奖励
	ITEMFROM_DUJIEAWARD = 5#渡劫奖励
	ITEMFROM_MONSTERDROP = 6#怪物掉落
	ITEMFROM_YAMENAWARD = 7#衙门每日奖励
	ITEMFROM_BEASTSOUL = 8#兽魂奖励
	ITEMFROM_GATHER = 9#采集
	ITEMFROM_TASK = 10#任务奖励
	ITEMFROM_MAIL = 11#邮件
	ITEMFROM_MALL = 12#商城购买
	ITEMFROM_DEMONTOWER = 13#锁妖塔
	ITEMFROM_TRIPODAWARD = 14#九疑鼎奖励
	ITEMFROM_ARENAAWARD = 15#斗剑奖励
	ITEMFROM_RANKADOREAWARD = 16#排行榜崇拜奖励
	ITEMFROM_VIPAWARD = 17#VIP礼包
	ITEMFROM_YELLODIAMONDAWARD = 18#黄钻礼包
	ITEMFROM_FIGHTERFIND = 19#刷将奖励
	ITEMFROM_EXCHANGEITEM = 20#兑换物品
	ITEMFROM_LEVELPRIZEACT = 21#运营活动
	ITEMFROM_ACTIVITY = 22#活跃度
	ITEMFROM_CITTASTORE = 23#天书背包
	ITEMFROM_USERDEPTORPACK = 24#玩家仓库与背包道具交换、拆分、合并
	ITEMFROM_ACTIVETRUMP = 25#法宝激活
	ITEMFROM_MERGECITTA = 26#心法合成
	ITEMFROM_BREAKCITTA = 27#心法分解
	ITEMFROM_HEROXINFADISPERSE = 28#散仙心法分解
	ITEMFROM_PLAYERXINFADISPERSE = 29#主将心法分解
	ITEMFROM_NEWCOLLECTION = 30#收藏
	ITEMFROM_NEWACHIEVE = 31#成就
	ITEMFROM_ENERGYBUY = 32#购买精力
	ITEMFROM_ENERGYBUFF = 33#buffer增加精力
	ITEMFROM_DEMONTOWERSEAL = 34#锁妖塔每日领取
	ITEMFROM_DEMONTOWERPASS = 35#锁妖塔过关领取
	ITEMFROM_PEND = 36#延迟发放
	ITEMFROM_SITING = 37#双修
	ITEMFROM_RECHARGE = 38#充值
	ITEMFROM_LANGHUANBLESS = 39#琅環福地
	ITEMFROM_GROUPTASK = 40#师门任务
	ITEMFROM_SELLITEM = 41#卖出物品
	ITEMFROM_SIGNINAWARD = 42#领取签到奖励礼包
	ITEMFROM_ARENABATTLE = 43#斗剑历练奖励声望
	ITEMFROM_CHARINIT = 44#角色初始化获得
	ITEMFROM_LOGINPKG = 45#累计登入获得
	ITEMFROM_SEVENDAYTARGET = 46#7日目标活动
	ITEMFROM_WONDERACTIVITY = 47#精彩活动
	ITEMFROM_PHP = 48#客服后台操作
	ITEMFROM_BATTLEARRAYITEM = 49#破阵
	ITEMFROM_TREASUREHUNT = 50#寻宝
	ITEMFROM_BEAUTY = 51#美女系统
	ITEMFROM_QQCOINEXCHANGE = 52#QQ养成计划
	ITEMFROM_SHUSHANWEIWEI = 53#蜀山微微
	ITEMFROM_SHUSHANFOUND = 54#蜀山基金
	ITEMFROM_CIRCLETASK = 55#环任务奖励
	ITEMFROM_CIRCLETASKFINISH = 56#环任务全部完成奖励
	ITEMFROM_MALLCHONGZHI = 57#商城充值活动奖励
	ITEMFROM_ANSWER = 58#答题活动
	ITEMFROM_GUARDEMEI = 59#守卫峨眉
	ITEMFROM_INVITEFRIEND = 60#邀请好友
	ITEMFROM_QQALARM = 61#QQAlarm奖励
	ITEMFROM_GUILDXIHE = 62#羲和神车奖励
	ITEMFROM_ACHIEVEMENT = 63#羲和神车奖励
	ITEMFROM_LADDERBATTLE = 64#斗剑奖励资源
	ITEMFROM_EXCHANGEMONEY = 65#货币兑换
	ITEMFROM_DRAW = 66#求签
	ITEMFROM_STARAWARD = 67#副本星级领奖
	ITEMFROM_GODMONSTER = 68#天元神兽奖励
	ITEMFROM_LINGSHAN = 69#秘境寻宝
	ITEMFROM_GUILDEXCHANGEDITEM = 70#帮派战物品兑换
	ITEMFROM_MONEYTREE = 71#摇钱树
	ITEMFROM_OFFSTONE = 72#取下宝石
	ITEMFROM_MERGESTONE = 73#宝石合成
	ITEMFROM_LOTTERY = 74#抽奖
	ITEMFROM_REGISTERSEVENDAYSDIS = 75#注册七天折扣豪礼大回馈
	ITEMFROM_SECONDRECHARGEAWARD = 76#二次充值礼包
	ITEMFROM_MALL_NOGOLD = 77#商城购买非仙石
	ITEMFROM_ETRUMPSTRENGTH = 78#装备法宝强化
	ITEMFROM_ETRUMPXILIAN = 79#装备法宝洗练
	ITEMFROM_BREAKEQUIPTRUMP = 80#分解装备法宝
	ITEMFROM_MERGEEQUIPTRUMP = 81#合成装备法宝
	ITEMFROM_WEAREQUIPTRUMP = 82#穿戴装备法宝
	ITEMFROM_TAKEOFFEQUIPTRUMP = 83#卸下装备法宝
	ITEMFROM_SHENGLING = 84#圣陵
	ITEMFROM_FENBAOYAN = 85#分宝岩
	ITEMFROM_FEEDBACK = 86#消费回馈
end

#删除物品/扣除货币
class ItemTo
	ITEMTO_SELL = 5000#出售给系统
	ITEMTO_GM = 5001#GM指令里删除物品
	ITEMTO_USEITEM = 5002#物品使用
	ITEMTO_BEASTSLOTS = 5003#激活兽魂
	ITEMTO_COMMITDUJIETASK = 5004#提交渡劫任务消耗
	ITEMTO_TRIPODMAKEFIRE = 5005#九疑鼎祈火
	ITEMTO_TRIPODSPEED = 5006#九疑鼎道具入鼎
	ITEMTO_TRIPODACTIVE = 5007#九疑鼎激活消耗
	ITEMTO_TRIPODUPGRADE = 5008#九疑鼎升级消耗
	ITEMTO_DEMONTOWER = 5009#锁妖塔消耗
	ITEMTO_ARENAFLUSH = 5010#斗剑刷将
	ITEMTO_ARENACLEARCD = 5011#清除斗剑CD
	ITEMTO_ARENAWIRSHIP = 5012#斗剑膜拜
	ITEMTO_ARENABUYTIMES = 5013#斗剑购买挑战次数
	ITEMTO_ARENACLEARLADDERCD = 5014#斗剑天梯cd清除
	ITEMTO_GUILDDONATE = 5015#帮派捐献
	ITEMTO_GUILDWORSHIP = 5016#帮派供奉
	ITEMTO_MERGECITTA = 5017#天书使用、分解、穿戴
	ITEMTO_USERDEPTORPACK = 5018#玩家仓库与背包道具交换、拆分、合并
	ITEMTO_GATHERCOND = 5019#玩家收集消耗
	ITEMTO_TASK = 5020#任务消耗
	ITEMTO_TRUMPACTIVE = 5021#主将法宝激活消耗
	ITEMTO_TRUMPUPGRADE = 5022#主将法宝祭炼升级消耗
	ITEMTO_TRUMPEVOLVE = 5023#主将法宝升阶消耗
	ITEMTO_LEARNXINFA = 5024#学习心法消耗
	ITEMTO_ZODTRUMPUPGRADE = 5025#散仙本命法宝祭炼升级消耗
	ITEMTO_EQUIPUPGRADE = 5026#装备升级消耗
	ITEMTO_FASHIONUPGRADE = 5027#时装升级消耗
	ITEMTO_FASHIONACTIVE = 5028#时装激活消耗
	ITEMTO_HORSEACTIVE = 5029#坐骑激活消耗
	ITEMTO_HORSEUPGRADE = 5030#坐骑升级消耗
	ITEMTO_HEROINSTINCT = 5031#散仙血脉激活消耗
	ITEMTO_TALENTACTIVE = 5032#天赋激活消耗
	ITEMTO_FORMATIONACTIVE = 5033#阵型激活消耗
	ITEMTO_PETACTIVE = 5034#宠物激活消耗
	ITEMTO_PETLVLUP = 5035#宠物升级消耗
	ITEMTO_RECRUIT = 5036#将领招募消耗
	ITEMTO_EXCHANGEITEM = 5037#兑换物品消耗
	ITEMTO_FLUSHTASK = 5038#刷新师门任务
	ITEMTO_BUYTASK = 5039#购买师门任务
	ITEMTO_YAMENFLUSHTASK = 5040#刷新衙门任务
	ITEMTO_YAMENBUYTASK = 5041#购买衙门任务
	ITEMTO_HEROSHIFT = 5042#散仙转移
	ITEMTO_HEROCUITIUPGRADE = 5043#散仙粹体升级
	ITEMTO_FIGHTERLUCKYEXCHANGE = 5044#散仙兑换
	ITEMTO_FIGHTERSEARCH = 5045#散仙搜索
	ITEMTO_FIGHTERTAOISMUPGRADE = 5046#道术升级
	ITEMTO_TASKFORGROUPAWARD = 5047#师门任务领奖
	ITEMTO_TASKFORYAMENAWARD = 5048#衙门任务领奖
	ITEMTO_FIGTHERTOOTHER = 5049#发起战斗
	ITEMTO_EXPANDSTORE = 5050#扩展背包
	ITEMTO_BUYGUILDSKILL = 5051#购买工会战技能
	ITEMTO_SWEEPINGSPEEDUP = 5052#扫荡加速
	ITEMTO_EQUIPINTENSIFY = 5053#装备强化
	ITEMTO_ATTACHSPIRIT = 5054#装备注灵
	ITEMTO_MALLBUY = 5055#商城购买
	ITEMTO_HEROLEVELUPGRADE = 5056#散仙升级
	ITEMTO_HEROSKILLLEVELUPGRADE = 5057#散仙天赋技能升级
	ITEMTO_HEROXINFAUPGRADE = 5058#散仙心法升级
	ITEMTO_HEROSKILLUPGRADE = 5059#散仙技能升级
	ITEMTO_PLAYERXINFAUPGRADE = 5060#玩家心法升级
	ITEMTO_OPENVIP = 5061#开启vip
	ITEMTO_OPENFRIENDVIP = 5062#给好友开启vip
	ITEMTO_BUYACTION = 5063#购买行动力
	ITEMTO_CONSUMEACTION = 5064#副本或扫荡消耗
	ITEMTO_ZODTRUMP = 5065#法宝升级
	ITEMTO_BATTLEBUYSKILL = 5066#论剑购买技能
	ITEMTO_SOULSPACEUPGRADE = 5067#魄空间升级
	ITEMTO_WORLDBOSSRELIVE = 5068#世界boss复活
	ITEMTO_WORLDBOSSBUYSTRENGTH = 5069#世界boss购买buffer
	ITEMTO_WORLDATTACK = 5070#世界boss购买立即攻击
	ITEMTO_PLAYERADVANCEUPGRADE = 5071#主将技能进阶
	ITEMTO_PLAYERSKILLUPGRADE = 5072#主将技能升级
	ITEMTO_RUNEUPGRADE = 5073#主将技能熔炼
	ITEMTO_UPGRADEBEASTSOUL = 5074#兽魂
	ITEMTO_PHP = 5075#客服后台操作
	ITEMTO_FIGHTERCOMBINATION = 5076#散仙组合升级消耗
	ITEMTO_BATTLEARRAYITEM = 5077#破阵
	ITEMTO_TREASUREHUNT = 5078#一键寻宝
	ITEMTO_BEAUTY = 5079#美女系统
	ITEMTO_BYOPENSHIPTIMES = 5080#购买运船次数
	ITEMTO_BYROBSHIPTIMES = 5081#购买抢船次数
	ITEMTO_BYREFLUSHSHIPTIMES = 5082#购买刷船次数
	ITEMTO_SHUSHANFOUND = 5083#购买蜀山基金
	ITEMTO_CIRCLEONEKEY = 5084#环任务立即完成当前
	ITEMTO_CIRCLEONEKEYALL = 5085#环任务立即完成所有
	ITEMTO_GETSHIPONEKEY = 5086#vip召唤船只
	ITEMTO_FINISHSHIPONEKEY = 5087#一键完成运船
	ITEMTO_CIRCLEUPSTAR = 5088#环任务升星
	ITEMTO_BUYHERODGN = 5089#购买英雄副本次数
	ITEMTO_BUYLIXIANDGN = 5090#购买历险副本次数
	ITEMTO_BUYENTRYNUM = 5091#购买守卫峨眉进入次数
	ITEMTO_GUILDXIHE = 5092#羲和神车消耗
	ITEMTO_BUYLADDERTIMES = 5093#购买天梯挑战次数
	ITEMTO_EXCHANGEMONEY = 5094#货币兑换
	ITEMTO_DRAW = 5095#求签
	ITEMTO_FIGHTERDISMISS = 5096#散功消耗
	ITEMTO_LINGSHAN = 5097#秘境寻宝
	ITEMTO_GODMONSTER = 5098#天元神兽消耗
	ITEMTO_DUJIECONSUME = 5099#散仙渡劫消耗
	ITEMTO_MONEYTREE = 5100#摇钱树消耗
	ITEMTO_WARESTONE = 5101#装备宝石
	ITEMTO_MERGESTONE = 5102#合成消耗
	ITEMTO_REGISTERSEVENDAYSDIS = 5103#注册七天折扣豪礼大回馈消耗
	ITEMTO_MALLBUY_NOGOLD = 5104#商城购买_礼卷
	ITEMTO_NEWGUILDBATTLEDEAD = 5105#灵山买活
	ITEMTO_NEWGUILDBATTLEBUYPUPPET = 5106#购买傀儡
	ITEMTO_LOTTERY = 5106#抽奖
	ITEMTO_BREAKCITTA = 5107#心法分解
	ITEMTO_FIGHTERBUYLYQ = 5108#邀仙居——李英琼
	ITEMTO_FIGHTERBUYQLY = 5109#邀仙居——齐灵云
	ITEMTO_ETRUMPSTRENGTH = 5110#装备法宝强化
	ITEMTO_ETRUMPXILIAN = 5111#装备法宝洗练
	ITEMTO_BREAKEQUIPTRUMP = 5112#分解装备法宝
	ITEMTO_MERGEEQUIPTRUMP = 5113#合成装备法宝
	ITEMTO_WEAREQUIPTRUMP = 5114#穿戴装备法宝
	ITEMTO_TAKEOFFEQUIPTRUMP = 5115#卸下装备法宝
	ITEMTO_SHENGLING = 5116#圣陵
	ITEMTO_FENBAOYAN = 5117#分宝岩
	ITEMTO_FEEDBACK = 5118#消费回馈
end

#散仙操作类型
class EFighterOptType
	EOPTTYPE_RECURIT = 0#招募
	EOPTTYPE_UPGRADE = 1#升级
	EOPTTYPE_CUITI = 2#猝体
	EOPTTYPE_FABAO = 3#法宝
	EOPTTYPE_SKILL = 4#技能
	EOPTTYPE_SHIFT = 5#CuiTi转移
	EOPTTYPE_XINFA = 6#心法
	EOPTTYPE_PASSIVESKILL = 7#被动技能
end

#结构体：LogDataBase的继承体系类型
class EType_LogDataBase
	ETYPE_LOGDATABASE = 0#类型：LogDataBase
	ETYPE_SDGNLOG = 1#类型：SDgnLog
	ETYPE_SREGISTERLOG = 2#类型：SRegisterLog
	ETYPE_SLOGINLOG = 3#类型：SLoginLog
	ETYPE_SITEMCOURSESLOG = 4#类型：SItemCoursesLog
	ETYPE_SMONEYCOURSESLOG = 5#类型：SMoneyCoursesLog
	ETYPE_SMAILLOG = 6#类型：SMailLog
	ETYPE_SPETLOG = 7#类型：SPetLog
	ETYPE_SDUJIELOG = 8#类型：SDujieLog
	ETYPE_SFASHIONLOG = 9#类型：SFashionLog
	ETYPE_SFIGHTERLOG = 10#类型：SFighterLog
	ETYPE_SHORSELOG = 11#类型：SHorseLog
	ETYPE_STRUMPLOG = 12#类型：STrumpLog
	ETYPE_SBEAUTYLOG = 13#类型：SBeautyLog
	ETYPE_SEQUIPLOG = 14#类型：SEquipLog
	ETYPE_SGUILDLOG = 15#类型：SGuildLog
	ETYPE_SSENDMONEYLOG = 16#类型：SSendMoneyLog
	ETYPE_SSENDITEMLOG = 17#类型：SSendItemLog
	ETYPE_SMAILOPLOG = 18#类型：SMailOpLog
	ETYPE_SFORBIDDENLOG = 19#类型：SForbiddenLog
	ETYPE_SFORBIDDENCHATLOG = 20#类型：SForbiddenChatLog
	ETYPE_SGLOBALSENDITEMLOG = 21#类型：SGlobalSendItemLog
	ETYPE_SQUESOPTLOG = 22#类型：SQuesOptLog
	ETYPE_SSENDMAILLOG = 23#类型：SSendMailLog
	ETYPE_SVIPSENDLOG = 24#类型：SVIPSendLog
	ETYPE_SACTIVITYOPENLOG = 25#类型：SActivityOpenLog
	ETYPE_SDISCOUNTITEMLOG = 26#类型：SDiscountItemLog
	ETYPE_SLEVELCHANGELOG = 27#类型：SLevelChangeLog
end

#日志数据基类
class LogDataBase
	#构造函数
	def initialize
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_LOGDATABASE
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = LogDataBase.new
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_LogDataBase::ETYPE_LOGDATABASE
				s = LogDataBase::fromStream(data)
			when EType_LogDataBase::ETYPE_SDGNLOG
				s = SDgnLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SREGISTERLOG
				s = SRegisterLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SLOGINLOG
				s = SLoginLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SITEMCOURSESLOG
				s = SItemCoursesLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SMONEYCOURSESLOG
				s = SMoneyCoursesLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SMAILLOG
				s = SMailLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SPETLOG
				s = SPetLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SDUJIELOG
				s = SDujieLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SFASHIONLOG
				s = SFashionLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SFIGHTERLOG
				s = SFighterLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SHORSELOG
				s = SHorseLog::fromStream(data)
			when EType_LogDataBase::ETYPE_STRUMPLOG
				s = STrumpLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SBEAUTYLOG
				s = SBeautyLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SEQUIPLOG
				s = SEquipLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SGUILDLOG
				s = SGuildLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SSENDMONEYLOG
				s = SSendMoneyLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SSENDITEMLOG
				s = SSendItemLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SMAILOPLOG
				s = SMailOpLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SFORBIDDENLOG
				s = SForbiddenLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SFORBIDDENCHATLOG
				s = SForbiddenChatLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SGLOBALSENDITEMLOG
				s = SGlobalSendItemLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SQUESOPTLOG
				s = SQuesOptLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SSENDMAILLOG
				s = SSendMailLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SVIPSENDLOG
				s = SVIPSendLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SACTIVITYOPENLOG
				s = SActivityOpenLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SDISCOUNTITEMLOG
				s = SDiscountItemLog::fromStream(data)
			when EType_LogDataBase::ETYPE_SLEVELCHANGELOG
				s = SLevelChangeLog::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = LogDataBase::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = LogDataBase::superFromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
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

#副本日志
class SDgnLog < LogDataBase
	attr_accessor:eOpType #(枚举类型：EDgnOpType)操作类型
	attr_accessor:wDgnType #(UINT16)副本类型
	attr_accessor:qwDgnInsID #(UINT64)副本实例ID
	attr_accessor:qwUserID #(UINT64)操作者，0表示系统

	#构造函数
	def initialize
		super()
		@eOpType = 0
		@wDgnType = 0
		@qwDgnInsID = 0
		@qwUserID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SDGNLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eOpType = @eOpType
		obj.wDgnType = @wDgnType
		obj.qwDgnInsID = @qwDgnInsID
		obj.qwUserID = @qwUserID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDgnLog.new
		base = LogDataBase::fromStream(data)
		s.eOpType = ByteUtil::readUINT8(data)
		s.wDgnType = ByteUtil::readUINT16(data)
		s.qwDgnInsID = ByteUtil::readUINT64(data)
		s.qwUserID = ByteUtil::readUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDgnLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @eOpType)
		ByteUtil::writeUINT16(data, @wDgnType)
		ByteUtil::writeUINT64(data, @qwDgnInsID)
		ByteUtil::writeUINT64(data, @qwUserID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#注册日志
class SRegisterLog < LogDataBase
	attr_accessor:serverId #(UINT32)服务器ID
	attr_accessor:playerId #(UINT64)玩家ID
	attr_accessor:playerName #(string)玩家名字

	#构造函数
	def initialize
		super()
		@serverId = 0
		@playerId = 0
		@playerName = ''
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SREGISTERLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.serverId = @serverId
		obj.playerId = @playerId
		obj.playerName = @playerName
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRegisterLog.new
		base = LogDataBase::fromStream(data)
		s.serverId = ByteUtil::readUINT32(data)
		s.playerId = ByteUtil::readUINT64(data)
		s.playerName = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRegisterLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @serverId)
		ByteUtil::writeUINT64(data, @playerId)
		ByteUtil::writeSTRING(data, @playerName)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#登录日志
class SLoginLog < LogDataBase
	attr_accessor:serverId #(UINT32)服务器ID
	attr_accessor:playerId #(UINT64)玩家ID
	attr_accessor:loginTime #(UINT32)登录时间
	attr_accessor:loginIp #(string)登录IP
	attr_accessor:logoutTime #(UINT32)离开时间

	#构造函数
	def initialize
		super()
		@serverId = 0
		@playerId = 0
		@loginTime = 0
		@loginIp = ''
		@logoutTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SLOGINLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.serverId = @serverId
		obj.playerId = @playerId
		obj.loginTime = @loginTime
		obj.loginIp = @loginIp
		obj.logoutTime = @logoutTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SLoginLog.new
		base = LogDataBase::fromStream(data)
		s.serverId = ByteUtil::readUINT32(data)
		s.playerId = ByteUtil::readUINT64(data)
		s.loginTime = ByteUtil::readUINT32(data)
		s.loginIp = ByteUtil::readSTRING(data)
		s.logoutTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SLoginLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @serverId)
		ByteUtil::writeUINT64(data, @playerId)
		ByteUtil::writeUINT32(data, @loginTime)
		ByteUtil::writeSTRING(data, @loginIp)
		ByteUtil::writeUINT32(data, @logoutTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#道具流水日志
class SItemCoursesLog < LogDataBase
	attr_accessor:serverId #(UINT32)服务器ID
	attr_accessor:playerId #(UINT64)玩家ID
	attr_accessor:strOpenId #(string)玩家的openId
	attr_accessor:qwInstId #(UINT64)物品流水ID
	attr_accessor:itemId #(UINT32)物品ID
	attr_accessor:itemNum #(UINT32)物品使用or增加数量
	attr_accessor:fromto #(UINT16)物品出处id
	attr_accessor:fromtoStr #(string)物品出处字符描述
	attr_accessor:happenedTime #(UINT32)时间

	#构造函数
	def initialize
		super()
		@serverId = 0
		@playerId = 0
		@strOpenId = ''
		@qwInstId = 0
		@itemId = 0
		@itemNum = 0
		@fromto = 0
		@fromtoStr = ''
		@happenedTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SITEMCOURSESLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.serverId = @serverId
		obj.playerId = @playerId
		obj.strOpenId = @strOpenId
		obj.qwInstId = @qwInstId
		obj.itemId = @itemId
		obj.itemNum = @itemNum
		obj.fromto = @fromto
		obj.fromtoStr = @fromtoStr
		obj.happenedTime = @happenedTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SItemCoursesLog.new
		base = LogDataBase::fromStream(data)
		s.serverId = ByteUtil::readUINT32(data)
		s.playerId = ByteUtil::readUINT64(data)
		s.strOpenId = ByteUtil::readSTRING(data)
		s.qwInstId = ByteUtil::readUINT64(data)
		s.itemId = ByteUtil::readUINT32(data)
		s.itemNum = ByteUtil::readUINT32(data)
		s.fromto = ByteUtil::readUINT16(data)
		s.fromtoStr = ByteUtil::readSTRING(data)
		s.happenedTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SItemCoursesLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @serverId)
		ByteUtil::writeUINT64(data, @playerId)
		ByteUtil::writeSTRING(data, @strOpenId)
		ByteUtil::writeUINT64(data, @qwInstId)
		ByteUtil::writeUINT32(data, @itemId)
		ByteUtil::writeUINT32(data, @itemNum)
		ByteUtil::writeUINT16(data, @fromto)
		ByteUtil::writeSTRING(data, @fromtoStr)
		ByteUtil::writeUINT32(data, @happenedTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#货币流水日志
class SMoneyCoursesLog < LogDataBase
	attr_accessor:serverId #(UINT32)服务器ID
	attr_accessor:playerId #(UINT64)玩家ID
	attr_accessor:strOpenId #(string)玩家的openId
	attr_accessor:moneyType #(UINT8)货币类型ID
	attr_accessor:moneyNum #(UINT32)货币使用or增加数量
	attr_accessor:totalNum #(UINT32)当前货币总数量
	attr_accessor:fromto #(UINT16)物品出处id
	attr_accessor:fromtoStr #(string)物品出处字符描述
	attr_accessor:happenedTime #(UINT32)时间
	attr_accessor:bIsFreeGold #(UINT8)是否使用免费仙石

	#构造函数
	def initialize
		super()
		@serverId = 0
		@playerId = 0
		@strOpenId = ''
		@moneyType = 0
		@moneyNum = 0
		@totalNum = 0
		@fromto = 0
		@fromtoStr = ''
		@happenedTime = 0
		@bIsFreeGold = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SMONEYCOURSESLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.serverId = @serverId
		obj.playerId = @playerId
		obj.strOpenId = @strOpenId
		obj.moneyType = @moneyType
		obj.moneyNum = @moneyNum
		obj.totalNum = @totalNum
		obj.fromto = @fromto
		obj.fromtoStr = @fromtoStr
		obj.happenedTime = @happenedTime
		obj.bIsFreeGold = @bIsFreeGold
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMoneyCoursesLog.new
		base = LogDataBase::fromStream(data)
		s.serverId = ByteUtil::readUINT32(data)
		s.playerId = ByteUtil::readUINT64(data)
		s.strOpenId = ByteUtil::readSTRING(data)
		s.moneyType = ByteUtil::readUINT8(data)
		s.moneyNum = ByteUtil::readUINT32(data)
		s.totalNum = ByteUtil::readUINT32(data)
		s.fromto = ByteUtil::readUINT16(data)
		s.fromtoStr = ByteUtil::readSTRING(data)
		s.happenedTime = ByteUtil::readUINT32(data)
		s.bIsFreeGold = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMoneyCoursesLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @serverId)
		ByteUtil::writeUINT64(data, @playerId)
		ByteUtil::writeSTRING(data, @strOpenId)
		ByteUtil::writeUINT8(data, @moneyType)
		ByteUtil::writeUINT32(data, @moneyNum)
		ByteUtil::writeUINT32(data, @totalNum)
		ByteUtil::writeUINT16(data, @fromto)
		ByteUtil::writeSTRING(data, @fromtoStr)
		ByteUtil::writeUINT32(data, @happenedTime)
		ByteUtil::writeUINT8(data, @bIsFreeGold)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#邮件流水日志
class SMailLog < LogDataBase
	attr_accessor:dwServerId #(UINT32)服务器ID
	attr_accessor:qwPlayerId #(UINT64)玩家ID
	attr_accessor:qwMailId #(UINT64)邮件ID
	attr_accessor:byType #(UINT8)邮件类型
	attr_accessor:strTitle #(string)邮件标题
	attr_accessor:strText #(string)邮件正文
	attr_accessor:strAttach #(string)邮件附件
	attr_accessor:byState #(UINT8)邮件状态
	attr_accessor:dwRevTime #(UINT32)操作时间
	attr_accessor:dwDelTime #(UINT32)删除时间

	#构造函数
	def initialize
		super()
		@dwServerId = 0
		@qwPlayerId = 0
		@qwMailId = 0
		@byType = 0
		@strTitle = ''
		@strText = ''
		@strAttach = ''
		@byState = 0
		@dwRevTime = 0
		@dwDelTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SMAILLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwServerId = @dwServerId
		obj.qwPlayerId = @qwPlayerId
		obj.qwMailId = @qwMailId
		obj.byType = @byType
		obj.strTitle = @strTitle
		obj.strText = @strText
		obj.strAttach = @strAttach
		obj.byState = @byState
		obj.dwRevTime = @dwRevTime
		obj.dwDelTime = @dwDelTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMailLog.new
		base = LogDataBase::fromStream(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwPlayerId = ByteUtil::readUINT64(data)
		s.qwMailId = ByteUtil::readUINT64(data)
		s.byType = ByteUtil::readUINT8(data)
		s.strTitle = ByteUtil::readSTRING(data)
		s.strText = ByteUtil::readSTRING(data)
		s.strAttach = ByteUtil::readSTRING(data)
		s.byState = ByteUtil::readUINT8(data)
		s.dwRevTime = ByteUtil::readUINT32(data)
		s.dwDelTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMailLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwPlayerId)
		ByteUtil::writeUINT64(data, @qwMailId)
		ByteUtil::writeUINT8(data, @byType)
		ByteUtil::writeSTRING(data, @strTitle)
		ByteUtil::writeSTRING(data, @strText)
		ByteUtil::writeSTRING(data, @strAttach)
		ByteUtil::writeUINT8(data, @byState)
		ByteUtil::writeUINT32(data, @dwRevTime)
		ByteUtil::writeUINT32(data, @dwDelTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#阵灵日志
class SPetLog < LogDataBase
	attr_accessor:dwServerId #(UINT32)服务器ID
	attr_accessor:qwPlayerId #(UINT64)玩家ID
	attr_accessor:sName #(string)阵灵名字
	attr_accessor:byOpType #(UINT8)操作类型
	attr_accessor:wLevel #(UINT16)阵灵等级
	attr_accessor:happenedTime #(UINT32)时间

	#构造函数
	def initialize
		super()
		@dwServerId = 0
		@qwPlayerId = 0
		@sName = ''
		@byOpType = 0
		@wLevel = 0
		@happenedTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SPETLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwServerId = @dwServerId
		obj.qwPlayerId = @qwPlayerId
		obj.sName = @sName
		obj.byOpType = @byOpType
		obj.wLevel = @wLevel
		obj.happenedTime = @happenedTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPetLog.new
		base = LogDataBase::fromStream(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwPlayerId = ByteUtil::readUINT64(data)
		s.sName = ByteUtil::readSTRING(data)
		s.byOpType = ByteUtil::readUINT8(data)
		s.wLevel = ByteUtil::readUINT16(data)
		s.happenedTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPetLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwPlayerId)
		ByteUtil::writeSTRING(data, @sName)
		ByteUtil::writeUINT8(data, @byOpType)
		ByteUtil::writeUINT16(data, @wLevel)
		ByteUtil::writeUINT32(data, @happenedTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#渡劫日志
class SDujieLog < LogDataBase
	attr_accessor:dwServerId #(UINT32)服务器ID
	attr_accessor:qwPlayerId #(UINT64)玩家ID
	attr_accessor:wFighterId #(UINT16)散仙ID
	attr_accessor:sFighterName #(string)散仙名字
	attr_accessor:sPeriodName #(string)渡劫阶段
	attr_accessor:dwExp #(UINT32)当前渡劫经验值
	attr_accessor:happenedTime #(UINT32)时间

	#构造函数
	def initialize
		super()
		@dwServerId = 0
		@qwPlayerId = 0
		@wFighterId = 0
		@sFighterName = ''
		@sPeriodName = ''
		@dwExp = 0
		@happenedTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SDUJIELOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwServerId = @dwServerId
		obj.qwPlayerId = @qwPlayerId
		obj.wFighterId = @wFighterId
		obj.sFighterName = @sFighterName
		obj.sPeriodName = @sPeriodName
		obj.dwExp = @dwExp
		obj.happenedTime = @happenedTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDujieLog.new
		base = LogDataBase::fromStream(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwPlayerId = ByteUtil::readUINT64(data)
		s.wFighterId = ByteUtil::readUINT16(data)
		s.sFighterName = ByteUtil::readSTRING(data)
		s.sPeriodName = ByteUtil::readSTRING(data)
		s.dwExp = ByteUtil::readUINT32(data)
		s.happenedTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDujieLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwPlayerId)
		ByteUtil::writeUINT16(data, @wFighterId)
		ByteUtil::writeSTRING(data, @sFighterName)
		ByteUtil::writeSTRING(data, @sPeriodName)
		ByteUtil::writeUINT32(data, @dwExp)
		ByteUtil::writeUINT32(data, @happenedTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#时装日志
class SFashionLog < LogDataBase
	attr_accessor:dwServerId #(UINT32)服务器ID
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:wId #(UINT16)时装ID
	attr_accessor:sName #(string)时装名字
	attr_accessor:dwLevel #(UINT32)时装等级
	attr_accessor:happenedTime #(UINT32)时间

	#构造函数
	def initialize
		super()
		@dwServerId = 0
		@qwUserId = 0
		@wId = 0
		@sName = ''
		@dwLevel = 0
		@happenedTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SFASHIONLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.wId = @wId
		obj.sName = @sName
		obj.dwLevel = @dwLevel
		obj.happenedTime = @happenedTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFashionLog.new
		base = LogDataBase::fromStream(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.wId = ByteUtil::readUINT16(data)
		s.sName = ByteUtil::readSTRING(data)
		s.dwLevel = ByteUtil::readUINT32(data)
		s.happenedTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFashionLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeUINT16(data, @wId)
		ByteUtil::writeSTRING(data, @sName)
		ByteUtil::writeUINT32(data, @dwLevel)
		ByteUtil::writeUINT32(data, @happenedTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#散仙日志
class SFighterLog < LogDataBase
	attr_accessor:dwServerId #(UINT32)服务器ID
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:wFighterId #(UINT16)散仙ID
	attr_accessor:sName #(string)散仙名字
	attr_accessor:wLevel #(UINT16)散仙等级
	attr_accessor:byQuality #(UINT8)散仙品质
	attr_accessor:eOptType #(枚举类型：EFighterOptType)操作类型1
	attr_accessor:dwType #(UINT32)操作类型2(本命法宝时，0表示法宝，1表示法宝技能)
	attr_accessor:qwResult #(UINT64)操作结果(本命法宝时：前32位表示ID，后32为表示等级
	attr_accessor:happenedTime #(UINT32)时间

	#构造函数
	def initialize
		super()
		@dwServerId = 0
		@qwUserId = 0
		@wFighterId = 0
		@sName = ''
		@wLevel = 0
		@byQuality = 0
		@eOptType = 0
		@dwType = 0
		@qwResult = 0
		@happenedTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SFIGHTERLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.wFighterId = @wFighterId
		obj.sName = @sName
		obj.wLevel = @wLevel
		obj.byQuality = @byQuality
		obj.eOptType = @eOptType
		obj.dwType = @dwType
		obj.qwResult = @qwResult
		obj.happenedTime = @happenedTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFighterLog.new
		base = LogDataBase::fromStream(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.wFighterId = ByteUtil::readUINT16(data)
		s.sName = ByteUtil::readSTRING(data)
		s.wLevel = ByteUtil::readUINT16(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.eOptType = ByteUtil::readUINT8(data)
		s.dwType = ByteUtil::readUINT32(data)
		s.qwResult = ByteUtil::readUINT64(data)
		s.happenedTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFighterLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeUINT16(data, @wFighterId)
		ByteUtil::writeSTRING(data, @sName)
		ByteUtil::writeUINT16(data, @wLevel)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT8(data, @eOptType)
		ByteUtil::writeUINT32(data, @dwType)
		ByteUtil::writeUINT64(data, @qwResult)
		ByteUtil::writeUINT32(data, @happenedTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#坐骑日志
class SHorseLog < LogDataBase
	attr_accessor:dwServerId #(UINT32)服务器ID
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:dwID #(UINT32)坐骑ID
	attr_accessor:sName #(string)坐骑名字
	attr_accessor:dwLevel #(UINT32)坐骑等级
	attr_accessor:happenedTime #(UINT32)时间

	#构造函数
	def initialize
		super()
		@dwServerId = 0
		@qwUserId = 0
		@dwID = 0
		@sName = ''
		@dwLevel = 0
		@happenedTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SHORSELOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.dwID = @dwID
		obj.sName = @sName
		obj.dwLevel = @dwLevel
		obj.happenedTime = @happenedTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SHorseLog.new
		base = LogDataBase::fromStream(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.dwID = ByteUtil::readUINT32(data)
		s.sName = ByteUtil::readSTRING(data)
		s.dwLevel = ByteUtil::readUINT32(data)
		s.happenedTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SHorseLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeUINT32(data, @dwID)
		ByteUtil::writeSTRING(data, @sName)
		ByteUtil::writeUINT32(data, @dwLevel)
		ByteUtil::writeUINT32(data, @happenedTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#法宝日志
class STrumpLog < LogDataBase
	attr_accessor:dwServerId #(UINT32)服务器ID
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:wID #(UINT16)法宝ID
	attr_accessor:sName #(string)法宝名字
	attr_accessor:dwSkillId #(UINT32)法宝技能等级
	attr_accessor:dwLevel #(UINT32)法宝品节
	attr_accessor:dwExp #(UINT32)法宝当前祭炼值
	attr_accessor:happenedTime #(UINT32)时间

	#构造函数
	def initialize
		super()
		@dwServerId = 0
		@qwUserId = 0
		@wID = 0
		@sName = ''
		@dwSkillId = 0
		@dwLevel = 0
		@dwExp = 0
		@happenedTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_STRUMPLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.wID = @wID
		obj.sName = @sName
		obj.dwSkillId = @dwSkillId
		obj.dwLevel = @dwLevel
		obj.dwExp = @dwExp
		obj.happenedTime = @happenedTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STrumpLog.new
		base = LogDataBase::fromStream(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.wID = ByteUtil::readUINT16(data)
		s.sName = ByteUtil::readSTRING(data)
		s.dwSkillId = ByteUtil::readUINT32(data)
		s.dwLevel = ByteUtil::readUINT32(data)
		s.dwExp = ByteUtil::readUINT32(data)
		s.happenedTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STrumpLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeUINT16(data, @wID)
		ByteUtil::writeSTRING(data, @sName)
		ByteUtil::writeUINT32(data, @dwSkillId)
		ByteUtil::writeUINT32(data, @dwLevel)
		ByteUtil::writeUINT32(data, @dwExp)
		ByteUtil::writeUINT32(data, @happenedTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#美女日志
class SBeautyLog < LogDataBase
	attr_accessor:dwServerId #(UINT32)服务器ID
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:wID #(UINT16)美女ID
	attr_accessor:sName #(string)美女名字
	attr_accessor:wLevel #(UINT16)亲密等级
	attr_accessor:dwExp #(UINT32)亲密度
	attr_accessor:happenedTime #(UINT32)时间

	#构造函数
	def initialize
		super()
		@dwServerId = 0
		@qwUserId = 0
		@wID = 0
		@sName = ''
		@wLevel = 0
		@dwExp = 0
		@happenedTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SBEAUTYLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.wID = @wID
		obj.sName = @sName
		obj.wLevel = @wLevel
		obj.dwExp = @dwExp
		obj.happenedTime = @happenedTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBeautyLog.new
		base = LogDataBase::fromStream(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.wID = ByteUtil::readUINT16(data)
		s.sName = ByteUtil::readSTRING(data)
		s.wLevel = ByteUtil::readUINT16(data)
		s.dwExp = ByteUtil::readUINT32(data)
		s.happenedTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBeautyLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeUINT16(data, @wID)
		ByteUtil::writeSTRING(data, @sName)
		ByteUtil::writeUINT16(data, @wLevel)
		ByteUtil::writeUINT32(data, @dwExp)
		ByteUtil::writeUINT32(data, @happenedTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#装备日志
class SEquipLog < LogDataBase
	attr_accessor:dwServerId #(UINT32)服务器ID
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:dwID #(UINT32)装备ID
	attr_accessor:sName #(string)装备名字
	attr_accessor:dwLevel #(UINT32)装备等级
	attr_accessor:happenedTime #(UINT32)时间

	#构造函数
	def initialize
		super()
		@dwServerId = 0
		@qwUserId = 0
		@dwID = 0
		@sName = ''
		@dwLevel = 0
		@happenedTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SEQUIPLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.dwID = @dwID
		obj.sName = @sName
		obj.dwLevel = @dwLevel
		obj.happenedTime = @happenedTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEquipLog.new
		base = LogDataBase::fromStream(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.dwID = ByteUtil::readUINT32(data)
		s.sName = ByteUtil::readSTRING(data)
		s.dwLevel = ByteUtil::readUINT32(data)
		s.happenedTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEquipLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeUINT32(data, @dwID)
		ByteUtil::writeSTRING(data, @sName)
		ByteUtil::writeUINT32(data, @dwLevel)
		ByteUtil::writeUINT32(data, @happenedTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮会日志
class SGuildLog < LogDataBase
	attr_accessor:dwServerId #(UINT32)服务器ID
	attr_accessor:qwGuildId #(UINT64)帮派ID
	attr_accessor:sName #(string)帮派名字
	attr_accessor:byLevel #(UINT8)帮派等级
	attr_accessor:dwCount #(UINT32)帮派人员
	attr_accessor:byTowerLvl #(UINT8)神谕塔等级
	attr_accessor:byStoreLvl #(UINT8)仓库等级
	attr_accessor:byHourseLvl #(UINT8)剑阁等级
	attr_accessor:dwScore #(UINT32)帮派积分
	attr_accessor:dwMoney #(UINT32)帮派金钱
	attr_accessor:happenedTime #(UINT32)创建时间
	attr_accessor:byOptType #(UINT8)数据库操作 (1创建，其他Update)
	attr_accessor:byOptParam #(UINT8)附加参数(1加入2加钱3加积分4神谕塔升级5仓库升级6剑阁升级)

	#构造函数
	def initialize
		super()
		@dwServerId = 0
		@qwGuildId = 0
		@sName = ''
		@byLevel = 0
		@dwCount = 0
		@byTowerLvl = 0
		@byStoreLvl = 0
		@byHourseLvl = 0
		@dwScore = 0
		@dwMoney = 0
		@happenedTime = 0
		@byOptType = 0
		@byOptParam = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SGUILDLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwServerId = @dwServerId
		obj.qwGuildId = @qwGuildId
		obj.sName = @sName
		obj.byLevel = @byLevel
		obj.dwCount = @dwCount
		obj.byTowerLvl = @byTowerLvl
		obj.byStoreLvl = @byStoreLvl
		obj.byHourseLvl = @byHourseLvl
		obj.dwScore = @dwScore
		obj.dwMoney = @dwMoney
		obj.happenedTime = @happenedTime
		obj.byOptType = @byOptType
		obj.byOptParam = @byOptParam
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildLog.new
		base = LogDataBase::fromStream(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwGuildId = ByteUtil::readUINT64(data)
		s.sName = ByteUtil::readSTRING(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.dwCount = ByteUtil::readUINT32(data)
		s.byTowerLvl = ByteUtil::readUINT8(data)
		s.byStoreLvl = ByteUtil::readUINT8(data)
		s.byHourseLvl = ByteUtil::readUINT8(data)
		s.dwScore = ByteUtil::readUINT32(data)
		s.dwMoney = ByteUtil::readUINT32(data)
		s.happenedTime = ByteUtil::readUINT32(data)
		s.byOptType = ByteUtil::readUINT8(data)
		s.byOptParam = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwGuildId)
		ByteUtil::writeSTRING(data, @sName)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwCount)
		ByteUtil::writeUINT8(data, @byTowerLvl)
		ByteUtil::writeUINT8(data, @byStoreLvl)
		ByteUtil::writeUINT8(data, @byHourseLvl)
		ByteUtil::writeUINT32(data, @dwScore)
		ByteUtil::writeUINT32(data, @dwMoney)
		ByteUtil::writeUINT32(data, @happenedTime)
		ByteUtil::writeUINT8(data, @byOptType)
		ByteUtil::writeUINT8(data, @byOptParam)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#发送货币日志
class SSendMoneyLog < LogDataBase
	attr_accessor:strSendName #(string)发送人
	attr_accessor:byStatus #(UINT8)状态
	attr_accessor:dwServerId #(UINT32)大区
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:byMoneyType #(UINT8)货币类型
	attr_accessor:dwMoneyValue #(UINT32)发送数量
	attr_accessor:strReason #(string)发送理由
	attr_accessor:dwOpTime #(UINT32)操作时间

	#构造函数
	def initialize
		super()
		@strSendName = ''
		@byStatus = 0
		@dwServerId = 0
		@qwUserId = 0
		@byMoneyType = 0
		@dwMoneyValue = 0
		@strReason = ''
		@dwOpTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SSENDMONEYLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strSendName = @strSendName
		obj.byStatus = @byStatus
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.byMoneyType = @byMoneyType
		obj.dwMoneyValue = @dwMoneyValue
		obj.strReason = @strReason
		obj.dwOpTime = @dwOpTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSendMoneyLog.new
		base = LogDataBase::fromStream(data)
		s.strSendName = ByteUtil::readSTRING(data)
		s.byStatus = ByteUtil::readUINT8(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.byMoneyType = ByteUtil::readUINT8(data)
		s.dwMoneyValue = ByteUtil::readUINT32(data)
		s.strReason = ByteUtil::readSTRING(data)
		s.dwOpTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSendMoneyLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeSTRING(data, @strSendName)
		ByteUtil::writeUINT8(data, @byStatus)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeUINT8(data, @byMoneyType)
		ByteUtil::writeUINT32(data, @dwMoneyValue)
		ByteUtil::writeSTRING(data, @strReason)
		ByteUtil::writeUINT32(data, @dwOpTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#发送物品日志
class SSendItemLog < LogDataBase
	attr_accessor:strSendName #(string)发送人
	attr_accessor:byStatus #(UINT8)状态
	attr_accessor:dwServerId #(UINT32)大区
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:strTitle #(string)标题
	attr_accessor:strBody #(string)内容
	attr_accessor:strItemList #(string)物品列表
	attr_accessor:strReason #(string)发送理由
	attr_accessor:dwOpTime #(UINT32)操作时间

	#构造函数
	def initialize
		super()
		@strSendName = ''
		@byStatus = 0
		@dwServerId = 0
		@qwUserId = 0
		@strTitle = ''
		@strBody = ''
		@strItemList = ''
		@strReason = ''
		@dwOpTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SSENDITEMLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strSendName = @strSendName
		obj.byStatus = @byStatus
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.strTitle = @strTitle
		obj.strBody = @strBody
		obj.strItemList = @strItemList
		obj.strReason = @strReason
		obj.dwOpTime = @dwOpTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSendItemLog.new
		base = LogDataBase::fromStream(data)
		s.strSendName = ByteUtil::readSTRING(data)
		s.byStatus = ByteUtil::readUINT8(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.strTitle = ByteUtil::readSTRING(data)
		s.strBody = ByteUtil::readSTRING(data)
		s.strItemList = ByteUtil::readSTRING(data)
		s.strReason = ByteUtil::readSTRING(data)
		s.dwOpTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSendItemLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeSTRING(data, @strSendName)
		ByteUtil::writeUINT8(data, @byStatus)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeSTRING(data, @strTitle)
		ByteUtil::writeSTRING(data, @strBody)
		ByteUtil::writeSTRING(data, @strItemList)
		ByteUtil::writeSTRING(data, @strReason)
		ByteUtil::writeUINT32(data, @dwOpTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#邮件操作日志
class SMailOpLog < LogDataBase
	attr_accessor:strSendName #(string)操作人
	attr_accessor:byStatus #(UINT8)状态
	attr_accessor:dwServerId #(UINT32)大区
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:byMailOpType #(UINT8)邮件操作类型
	attr_accessor:dwOpTime #(UINT32)操作时间

	#构造函数
	def initialize
		super()
		@strSendName = ''
		@byStatus = 0
		@dwServerId = 0
		@qwUserId = 0
		@byMailOpType = 0
		@dwOpTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SMAILOPLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strSendName = @strSendName
		obj.byStatus = @byStatus
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.byMailOpType = @byMailOpType
		obj.dwOpTime = @dwOpTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMailOpLog.new
		base = LogDataBase::fromStream(data)
		s.strSendName = ByteUtil::readSTRING(data)
		s.byStatus = ByteUtil::readUINT8(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.byMailOpType = ByteUtil::readUINT8(data)
		s.dwOpTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMailOpLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeSTRING(data, @strSendName)
		ByteUtil::writeUINT8(data, @byStatus)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeUINT8(data, @byMailOpType)
		ByteUtil::writeUINT32(data, @dwOpTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#封号*解封记录
class SForbiddenLog < LogDataBase
	attr_accessor:strSendName #(string)操作人
	attr_accessor:byStatus #(UINT8)状态
	attr_accessor:dwServerId #(UINT32)大区
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:byOpType #(UINT8)操作类型
	attr_accessor:dwForbidTime #(UINT32)封禁时间
	attr_accessor:strReason #(string)理由
	attr_accessor:dwOpTime #(UINT32)操作时间

	#构造函数
	def initialize
		super()
		@strSendName = ''
		@byStatus = 0
		@dwServerId = 0
		@qwUserId = 0
		@byOpType = 0
		@dwForbidTime = 0
		@strReason = ''
		@dwOpTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SFORBIDDENLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strSendName = @strSendName
		obj.byStatus = @byStatus
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.byOpType = @byOpType
		obj.dwForbidTime = @dwForbidTime
		obj.strReason = @strReason
		obj.dwOpTime = @dwOpTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SForbiddenLog.new
		base = LogDataBase::fromStream(data)
		s.strSendName = ByteUtil::readSTRING(data)
		s.byStatus = ByteUtil::readUINT8(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.byOpType = ByteUtil::readUINT8(data)
		s.dwForbidTime = ByteUtil::readUINT32(data)
		s.strReason = ByteUtil::readSTRING(data)
		s.dwOpTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SForbiddenLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeSTRING(data, @strSendName)
		ByteUtil::writeUINT8(data, @byStatus)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeUINT8(data, @byOpType)
		ByteUtil::writeUINT32(data, @dwForbidTime)
		ByteUtil::writeSTRING(data, @strReason)
		ByteUtil::writeUINT32(data, @dwOpTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#禁言*解禁记录
class SForbiddenChatLog < LogDataBase
	attr_accessor:strSendName #(string)操作人
	attr_accessor:byStatus #(UINT8)状态
	attr_accessor:dwServerId #(UINT32)大区
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:byOpType #(UINT8)操作类型
	attr_accessor:dwForbidTime #(UINT32)封禁时间
	attr_accessor:strReason #(string)理由
	attr_accessor:dwOpTime #(UINT32)操作时间

	#构造函数
	def initialize
		super()
		@strSendName = ''
		@byStatus = 0
		@dwServerId = 0
		@qwUserId = 0
		@byOpType = 0
		@dwForbidTime = 0
		@strReason = ''
		@dwOpTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SFORBIDDENCHATLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strSendName = @strSendName
		obj.byStatus = @byStatus
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.byOpType = @byOpType
		obj.dwForbidTime = @dwForbidTime
		obj.strReason = @strReason
		obj.dwOpTime = @dwOpTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SForbiddenChatLog.new
		base = LogDataBase::fromStream(data)
		s.strSendName = ByteUtil::readSTRING(data)
		s.byStatus = ByteUtil::readUINT8(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.byOpType = ByteUtil::readUINT8(data)
		s.dwForbidTime = ByteUtil::readUINT32(data)
		s.strReason = ByteUtil::readSTRING(data)
		s.dwOpTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SForbiddenChatLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeSTRING(data, @strSendName)
		ByteUtil::writeUINT8(data, @byStatus)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeUINT8(data, @byOpType)
		ByteUtil::writeUINT32(data, @dwForbidTime)
		ByteUtil::writeSTRING(data, @strReason)
		ByteUtil::writeUINT32(data, @dwOpTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#发送物品日志
class SGlobalSendItemLog < LogDataBase
	attr_accessor:strSendName #(string)发送人
	attr_accessor:byStatus #(UINT8)状态
	attr_accessor:dwServerId #(UINT32)大区
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:dwGold #(UINT32)仙石
	attr_accessor:dwCoupon #(UINT32)礼卷
	attr_accessor:dwSliver #(UINT32)银币
	attr_accessor:dwHonor #(UINT32)荣誉
	attr_accessor:strItemList #(string)物品列表
	attr_accessor:strReason #(string)理由
	attr_accessor:dwOpTime #(UINT32)操作时间

	#构造函数
	def initialize
		super()
		@strSendName = ''
		@byStatus = 0
		@dwServerId = 0
		@qwUserId = 0
		@dwGold = 0
		@dwCoupon = 0
		@dwSliver = 0
		@dwHonor = 0
		@strItemList = ''
		@strReason = ''
		@dwOpTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SGLOBALSENDITEMLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strSendName = @strSendName
		obj.byStatus = @byStatus
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.dwGold = @dwGold
		obj.dwCoupon = @dwCoupon
		obj.dwSliver = @dwSliver
		obj.dwHonor = @dwHonor
		obj.strItemList = @strItemList
		obj.strReason = @strReason
		obj.dwOpTime = @dwOpTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGlobalSendItemLog.new
		base = LogDataBase::fromStream(data)
		s.strSendName = ByteUtil::readSTRING(data)
		s.byStatus = ByteUtil::readUINT8(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.dwGold = ByteUtil::readUINT32(data)
		s.dwCoupon = ByteUtil::readUINT32(data)
		s.dwSliver = ByteUtil::readUINT32(data)
		s.dwHonor = ByteUtil::readUINT32(data)
		s.strItemList = ByteUtil::readSTRING(data)
		s.strReason = ByteUtil::readSTRING(data)
		s.dwOpTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGlobalSendItemLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeSTRING(data, @strSendName)
		ByteUtil::writeUINT8(data, @byStatus)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeUINT32(data, @dwGold)
		ByteUtil::writeUINT32(data, @dwCoupon)
		ByteUtil::writeUINT32(data, @dwSliver)
		ByteUtil::writeUINT32(data, @dwHonor)
		ByteUtil::writeSTRING(data, @strItemList)
		ByteUtil::writeSTRING(data, @strReason)
		ByteUtil::writeUINT32(data, @dwOpTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#任务管理记录
class SQuesOptLog < LogDataBase
	attr_accessor:strSendName #(string)操作人
	attr_accessor:byStatus #(UINT8)状态
	attr_accessor:dwServerId #(UINT32)大区
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:byOpType #(UINT8)操作类型
	attr_accessor:wQuestType #(UINT16)任务类型
	attr_accessor:strQuestName #(string)任务名字
	attr_accessor:dwOpTime #(UINT32)操作时间

	#构造函数
	def initialize
		super()
		@strSendName = ''
		@byStatus = 0
		@dwServerId = 0
		@qwUserId = 0
		@byOpType = 0
		@wQuestType = 0
		@strQuestName = ''
		@dwOpTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SQUESOPTLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strSendName = @strSendName
		obj.byStatus = @byStatus
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.byOpType = @byOpType
		obj.wQuestType = @wQuestType
		obj.strQuestName = @strQuestName
		obj.dwOpTime = @dwOpTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SQuesOptLog.new
		base = LogDataBase::fromStream(data)
		s.strSendName = ByteUtil::readSTRING(data)
		s.byStatus = ByteUtil::readUINT8(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.byOpType = ByteUtil::readUINT8(data)
		s.wQuestType = ByteUtil::readUINT16(data)
		s.strQuestName = ByteUtil::readSTRING(data)
		s.dwOpTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SQuesOptLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeSTRING(data, @strSendName)
		ByteUtil::writeUINT8(data, @byStatus)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeUINT8(data, @byOpType)
		ByteUtil::writeUINT16(data, @wQuestType)
		ByteUtil::writeSTRING(data, @strQuestName)
		ByteUtil::writeUINT32(data, @dwOpTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#邮件发送日志
class SSendMailLog < LogDataBase
	attr_accessor:strSendName #(string)发送人
	attr_accessor:byStatus #(UINT8)状态
	attr_accessor:dwServerId #(UINT32)大区
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:strTitel #(string)标题
	attr_accessor:strBody #(string)内容
	attr_accessor:dwOpTime #(UINT32)操作时间

	#构造函数
	def initialize
		super()
		@strSendName = ''
		@byStatus = 0
		@dwServerId = 0
		@qwUserId = 0
		@strTitel = ''
		@strBody = ''
		@dwOpTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SSENDMAILLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strSendName = @strSendName
		obj.byStatus = @byStatus
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.strTitel = @strTitel
		obj.strBody = @strBody
		obj.dwOpTime = @dwOpTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSendMailLog.new
		base = LogDataBase::fromStream(data)
		s.strSendName = ByteUtil::readSTRING(data)
		s.byStatus = ByteUtil::readUINT8(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.strTitel = ByteUtil::readSTRING(data)
		s.strBody = ByteUtil::readSTRING(data)
		s.dwOpTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSendMailLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeSTRING(data, @strSendName)
		ByteUtil::writeUINT8(data, @byStatus)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeSTRING(data, @strTitel)
		ByteUtil::writeSTRING(data, @strBody)
		ByteUtil::writeUINT32(data, @dwOpTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#VIP物品发放记录
class SVIPSendLog < LogDataBase
	attr_accessor:strSendName #(string)发送人
	attr_accessor:byStatus #(UINT8)状态
	attr_accessor:dwServerId #(UINT32)大区
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:dwVIPLevel #(UINT32)vip等级
	attr_accessor:strBody #(string)内容
	attr_accessor:dwOpTime #(UINT32)操作时间

	#构造函数
	def initialize
		super()
		@strSendName = ''
		@byStatus = 0
		@dwServerId = 0
		@qwUserId = 0
		@dwVIPLevel = 0
		@strBody = ''
		@dwOpTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SVIPSENDLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strSendName = @strSendName
		obj.byStatus = @byStatus
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.dwVIPLevel = @dwVIPLevel
		obj.strBody = @strBody
		obj.dwOpTime = @dwOpTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SVIPSendLog.new
		base = LogDataBase::fromStream(data)
		s.strSendName = ByteUtil::readSTRING(data)
		s.byStatus = ByteUtil::readUINT8(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.dwVIPLevel = ByteUtil::readUINT32(data)
		s.strBody = ByteUtil::readSTRING(data)
		s.dwOpTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SVIPSendLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeSTRING(data, @strSendName)
		ByteUtil::writeUINT8(data, @byStatus)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeUINT32(data, @dwVIPLevel)
		ByteUtil::writeSTRING(data, @strBody)
		ByteUtil::writeUINT32(data, @dwOpTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#活动开启记录
class SActivityOpenLog < LogDataBase
	attr_accessor:strSendName #(string)发送人
	attr_accessor:byStatus #(UINT8)状态
	attr_accessor:dwServerId #(UINT32)大区
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:strActivityName #(string)活动名称
	attr_accessor:dwBeginTime #(UINT32)开始时间
	attr_accessor:dwEndTime #(UINT32)结束时间
	attr_accessor:dwOpTime #(UINT32)操作时间

	#构造函数
	def initialize
		super()
		@strSendName = ''
		@byStatus = 0
		@dwServerId = 0
		@qwUserId = 0
		@strActivityName = ''
		@dwBeginTime = 0
		@dwEndTime = 0
		@dwOpTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SACTIVITYOPENLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strSendName = @strSendName
		obj.byStatus = @byStatus
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.strActivityName = @strActivityName
		obj.dwBeginTime = @dwBeginTime
		obj.dwEndTime = @dwEndTime
		obj.dwOpTime = @dwOpTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SActivityOpenLog.new
		base = LogDataBase::fromStream(data)
		s.strSendName = ByteUtil::readSTRING(data)
		s.byStatus = ByteUtil::readUINT8(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.strActivityName = ByteUtil::readSTRING(data)
		s.dwBeginTime = ByteUtil::readUINT32(data)
		s.dwEndTime = ByteUtil::readUINT32(data)
		s.dwOpTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SActivityOpenLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeSTRING(data, @strSendName)
		ByteUtil::writeUINT8(data, @byStatus)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeSTRING(data, @strActivityName)
		ByteUtil::writeUINT32(data, @dwBeginTime)
		ByteUtil::writeUINT32(data, @dwEndTime)
		ByteUtil::writeUINT32(data, @dwOpTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#限时限购配置记录
class SDiscountItemLog < LogDataBase
	attr_accessor:strSendName #(string)发送人
	attr_accessor:byStatus #(UINT8)状态
	attr_accessor:dwServerId #(UINT32)大区
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:byType #(UINT8)类型
	attr_accessor:dwBeginTime #(UINT32)开始时间
	attr_accessor:dwEndTime #(UINT32)结束时间
	attr_accessor:strItemList #(string)物品列表
	attr_accessor:dwOpTime #(UINT32)操作时间

	#构造函数
	def initialize
		super()
		@strSendName = ''
		@byStatus = 0
		@dwServerId = 0
		@qwUserId = 0
		@byType = 0
		@dwBeginTime = 0
		@dwEndTime = 0
		@strItemList = ''
		@dwOpTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SDISCOUNTITEMLOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strSendName = @strSendName
		obj.byStatus = @byStatus
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.byType = @byType
		obj.dwBeginTime = @dwBeginTime
		obj.dwEndTime = @dwEndTime
		obj.strItemList = @strItemList
		obj.dwOpTime = @dwOpTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDiscountItemLog.new
		base = LogDataBase::fromStream(data)
		s.strSendName = ByteUtil::readSTRING(data)
		s.byStatus = ByteUtil::readUINT8(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.byType = ByteUtil::readUINT8(data)
		s.dwBeginTime = ByteUtil::readUINT32(data)
		s.dwEndTime = ByteUtil::readUINT32(data)
		s.strItemList = ByteUtil::readSTRING(data)
		s.dwOpTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDiscountItemLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeSTRING(data, @strSendName)
		ByteUtil::writeUINT8(data, @byStatus)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeUINT8(data, @byType)
		ByteUtil::writeUINT32(data, @dwBeginTime)
		ByteUtil::writeUINT32(data, @dwEndTime)
		ByteUtil::writeSTRING(data, @strItemList)
		ByteUtil::writeUINT32(data, @dwOpTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#等级修改记录
class SLevelChangeLog < LogDataBase
	attr_accessor:strSendName #(string)发送人
	attr_accessor:byStatus #(UINT8)状态
	attr_accessor:dwServerId #(UINT32)大区
	attr_accessor:qwUserId #(UINT64)玩家ID
	attr_accessor:byLevel #(UINT8)玩家等级
	attr_accessor:dwOpTime #(UINT32)操作时间

	#构造函数
	def initialize
		super()
		@strSendName = ''
		@byStatus = 0
		@dwServerId = 0
		@qwUserId = 0
		@byLevel = 0
		@dwOpTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_LogDataBase::ETYPE_SLEVELCHANGELOG
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strSendName = @strSendName
		obj.byStatus = @byStatus
		obj.dwServerId = @dwServerId
		obj.qwUserId = @qwUserId
		obj.byLevel = @byLevel
		obj.dwOpTime = @dwOpTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SLevelChangeLog.new
		base = LogDataBase::fromStream(data)
		s.strSendName = ByteUtil::readSTRING(data)
		s.byStatus = ByteUtil::readUINT8(data)
		s.dwServerId = ByteUtil::readUINT32(data)
		s.qwUserId = ByteUtil::readUINT64(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.dwOpTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SLevelChangeLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeSTRING(data, @strSendName)
		ByteUtil::writeUINT8(data, @byStatus)
		ByteUtil::writeUINT32(data, @dwServerId)
		ByteUtil::writeUINT64(data, @qwUserId)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwOpTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#协议类：日志数据定义
class LogDataDefineBase < ProtocolBase
	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 61;
		@recvFuncList = Array.new
	end

	def handleMessage(data)
		return true;
	end
end

