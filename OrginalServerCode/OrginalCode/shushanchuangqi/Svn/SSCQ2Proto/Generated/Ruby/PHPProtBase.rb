#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    PHPProt.rb
#  Purpose:      PHP相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#后台操作结果
class EOptResult
	EOPTRESULTSUCC = 0#成功
	EOPTRESULTFAILED = 1#失败
end

#后台操作类型
class EOptType
	EOPTNONE = 0#无
	EOPTLOCKUSER = 1#封号
	EOPTUNLOCKUSER = 2#解封
	EOPTLOCKSPEAK = 3#禁言
	EOPTUNLOCKSPEAK = 4#解禁
	EOPTSETPLAYERVIPLEVEL = 5#设置玩家VIP等级
	EOPTADDGROWTHVALUE = 6#增加玩家成长值
	EOPTEND = 7#结束
end

#日常任务类型
class EPHPTaskType
	EPHPTASKNONE = 0#无
	EPHPYAMENTASK = 1#衙门任务
	EPHPSHIMENTASK = 2#师门任务
	EPHPTASKEND = 3#结束
end

#发放对象
class ESendTarget
	ESENDTARGETNONE = 0#无
	EISONLINE = 1#在线玩家
	EALL = 2#所有玩家
	ECLANMEMBER = 3#帮派成员
	ECLANBAG = 4#帮派仓库
	ESENDTARGETEND = 5#结束
end

#任务集市中任务操作
class ETaskOpt
	ETASKOPTNONE = 0#无
	ETASKOPTCOMPLETE = 1#任务是否完成
	ETASKOPTCOMPANDREWARD = 2#任务是否完成，若完成发放奖励
	ETASKOPTREWARD = 3#发放奖励
	ETASKOPTEND = 4#结束
end

#任务集市状态返回
class ETaskState
	ETASKSTATENONE = 0#无
	ETASKSTATESUC = 1#奖励发放成功或任务步骤完成
	ETASKSTATENOROLE = 2#玩家没有创建角色
	ETASKSTATENOCOMP = 3#任务步骤没有完成
	ETASKSTATESENDED = 4#奖励已经发放过
	ETASKSTATESENDERR = 5#发放奖励错误
	ETASKSTATEPARAMERR = 6#请求参数错误
	ETASKSTATEOTHERERR = 7#其他错误
	ETASKSTATEEND = 8#结束
end

#平台类型
class EPlatformType
	EPLATFORMNONE = 0#无
	EPLATFORMTYPEQQYELLOW = 1#QQ黄钻平台/Qzone
	EPLATFORMTYPEQQPENGYOU = 2#QQ朋友/校友/黄钻
	EPLATFORMTYPEQQWEIBO = 3#QQ微博平台
	EPLATFORMTYPEQQPLUS = 4#QQ/Q+平台
	EPLATFORMTYPEQQGAME = 5#QQ蓝钻/游戏平台
	EPLATFORMTYPEQQ3366 = 6#QQ蓝钻/3366平台/包子
	EPLATFORMTYPEQQKINGXIN = 7#QQ官网平台/QQ会员
	EPLATFORMTYPEKINGXIN = 8#恺英官网平台
	EPLATFORMTYPEEND = 9#结束
end

#QQ平台类型
class EQQPlatformType
	EQQPLATFORMTYPENONE = 0#无
	EQQPLATFORMTYPEYELLOW = 1#黄钻平台
	EQQPLATFORMTYPEBLUE = 2#蓝钻平台
	EQQPLATFORMTYPERED = 3#红钻/VIP平台
	EQQPLATFORMTYPEEND = 4#结束
end

#平台类型定义
class EPHPPtType
	EPHPPTTYPENONE = 0#无
	EPHPPTTYPEQQYELLOW = 1#QQ黄钻平台/Qzone
	EPHPPTTYPEQQPENGYOU = 2#QQ朋友/校友/黄钻
	EPHPPTTYPEQQWEIBO = 3#QQ微博平台
	EPHPPTTYPEQQPLUS = 4#QQ/Q+平台
	EPHPPTTYPEQQGAME = 5#QQ蓝钻/游戏平台
	EPHPPTTYPEQQ3366 = 6#QQ蓝钻/3366平台/包子
	EPHPPTTYPEQQKINGXIN = 7#QQ官网平台/QQ会员
	EPHPPTTYPEKINGXIN = 8#恺英官网平台
	EPHPPTTYPEMAX = 9#最大值
end

#公告显示区域类型
class EShowType
	ESHOWNONE = 0#无
	ECHATWINDOWNOTICE = 1#聊天窗口显示公告
	EALLNOTICE = 2#全部显示
	ESHOWEND = 3#结束
end

#是否滚动
class ERollType
	EROLLNONE = 0#无
	EISROLL = 1#滚动
	ENOROLL = 2#不滚动
	EROLLEND = 3#结束
end

#是否立即发送
class ESendType
	ESENDNONE = 0#无
	EISIMMEDIATESEND = 1#立即发送
	ENOIMMEDIATESEND = 2#不立即发送
	ESENDEND = 3#结束
end

#弹窗类型
class EDialogType
	EDIALOGNONE = 0#无
	EUPDATENOTICEDIALOG = 1#更新公告弹窗
	ESYSDIALOG = 2#系统弹窗
	EDIALOGEND = 3#结束
end

#类型
class EActivityType
	EACTIVITY_NONE = 0#无
	EACTIVITY_WORLDBOSS = 1#世界boss活动
	EACTIVITY_LANGHUANBLESS = 2#琅环活动
	EACTIVITY_DRAGONBALL = 3#七星龙珠活动
	EACTIVITY_SEVENCONSUME = 4#七日消费活动
	EACTIVITY_QQCOIN = 5#Q币养成活动
	EACTIVITY_MAX = 6#结束
end

#UserID和Name
class SUserIDAndName
	attr_accessor:qwUserID #(UINT64)用户ID
	attr_accessor:strName #(string)角色名称

	#构造函数
	def initialize
		@qwUserID = 0
		@strName = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwUserID = @qwUserID
		obj.strName = @strName
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SUserIDAndName.new
		s.qwUserID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SUserIDAndName::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeSTRING(data, @strName)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#公告
class SNotice
	attr_accessor:dwNoticeID #(UINT32)公告ID
	attr_accessor:byNoticeType #(UINT8)公告类型
	attr_accessor:strContent #(string)公告内容
	attr_accessor:dwBeginTime #(UINT32)公告开始时间
	attr_accessor:dwEndTime #(UINT32)公告结束

	#构造函数
	def initialize
		@dwNoticeID = 0
		@byNoticeType = 0
		@strContent = ''
		@dwBeginTime = 0
		@dwEndTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwNoticeID = @dwNoticeID
		obj.byNoticeType = @byNoticeType
		obj.strContent = @strContent
		obj.dwBeginTime = @dwBeginTime
		obj.dwEndTime = @dwEndTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SNotice.new
		s.dwNoticeID = ByteUtil::readUINT32(data)
		s.byNoticeType = ByteUtil::readUINT8(data)
		s.strContent = ByteUtil::readSTRING(data)
		s.dwBeginTime = ByteUtil::readUINT32(data)
		s.dwEndTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SNotice::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwNoticeID)
		ByteUtil::writeUINT8(data, @byNoticeType)
		ByteUtil::writeSTRING(data, @strContent)
		ByteUtil::writeUINT32(data, @dwBeginTime)
		ByteUtil::writeUINT32(data, @dwEndTime)
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
	attr_accessor:qwUserID #(UINT64)用户ID
	attr_accessor:strName #(string)角色名称
	attr_accessor:wLevel #(UINT16)等级
	attr_accessor:strGuildName #(string)帮派名
	attr_accessor:qwGuildID #(UINT64)帮派ID
	attr_accessor:byJob #(UINT8)职业(1、儒；2、释；3、道；4、墨)
	attr_accessor:bySex #(UINT8)性别(1、男；2、女)
	attr_accessor:dwSilver #(UINT32)银币
	attr_accessor:dwGold #(UINT32)仙石
	attr_accessor:dwCoupon #(UINT32)礼券
	attr_accessor:byForbExpire #(UINT8)是否禁言(0、否；1、是)
	attr_accessor:byLockExpire #(UINT8)是否封号(0、否；1、是)
	attr_accessor:byVIPLevel #(UINT8)VIP等级
	attr_accessor:dwPrestige #(UINT32)声望
	attr_accessor:dwHonor #(UINT32)荣誉
	attr_accessor:dwDJ #(UINT32)斗剑排名
	attr_accessor:dwHistoryDJ #(UINT32)历史最高斗剑
	attr_accessor:dwCreateTime #(UINT32)创角时间
	attr_accessor:wShiMenTask #(UINT16)师门任务
	attr_accessor:wYaMenTaTask #(UINT16)衙门任务

	#构造函数
	def initialize
		@qwUserID = 0
		@strName = ''
		@wLevel = 0
		@strGuildName = ''
		@qwGuildID = 0
		@byJob = 0
		@bySex = 0
		@dwSilver = 0
		@dwGold = 0
		@dwCoupon = 0
		@byForbExpire = 0
		@byLockExpire = 0
		@byVIPLevel = 0
		@dwPrestige = 0
		@dwHonor = 0
		@dwDJ = 0
		@dwHistoryDJ = 0
		@dwCreateTime = 0
		@wShiMenTask = 0
		@wYaMenTaTask = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwUserID = @qwUserID
		obj.strName = @strName
		obj.wLevel = @wLevel
		obj.strGuildName = @strGuildName
		obj.qwGuildID = @qwGuildID
		obj.byJob = @byJob
		obj.bySex = @bySex
		obj.dwSilver = @dwSilver
		obj.dwGold = @dwGold
		obj.dwCoupon = @dwCoupon
		obj.byForbExpire = @byForbExpire
		obj.byLockExpire = @byLockExpire
		obj.byVIPLevel = @byVIPLevel
		obj.dwPrestige = @dwPrestige
		obj.dwHonor = @dwHonor
		obj.dwDJ = @dwDJ
		obj.dwHistoryDJ = @dwHistoryDJ
		obj.dwCreateTime = @dwCreateTime
		obj.wShiMenTask = @wShiMenTask
		obj.wYaMenTaTask = @wYaMenTaTask
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPlayerInfo.new
		s.qwUserID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.wLevel = ByteUtil::readUINT16(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		s.qwGuildID = ByteUtil::readUINT64(data)
		s.byJob = ByteUtil::readUINT8(data)
		s.bySex = ByteUtil::readUINT8(data)
		s.dwSilver = ByteUtil::readUINT32(data)
		s.dwGold = ByteUtil::readUINT32(data)
		s.dwCoupon = ByteUtil::readUINT32(data)
		s.byForbExpire = ByteUtil::readUINT8(data)
		s.byLockExpire = ByteUtil::readUINT8(data)
		s.byVIPLevel = ByteUtil::readUINT8(data)
		s.dwPrestige = ByteUtil::readUINT32(data)
		s.dwHonor = ByteUtil::readUINT32(data)
		s.dwDJ = ByteUtil::readUINT32(data)
		s.dwHistoryDJ = ByteUtil::readUINT32(data)
		s.dwCreateTime = ByteUtil::readUINT32(data)
		s.wShiMenTask = ByteUtil::readUINT16(data)
		s.wYaMenTaTask = ByteUtil::readUINT16(data)
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
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT16(data, @wLevel)
		ByteUtil::writeSTRING(data, @strGuildName)
		ByteUtil::writeUINT64(data, @qwGuildID)
		ByteUtil::writeUINT8(data, @byJob)
		ByteUtil::writeUINT8(data, @bySex)
		ByteUtil::writeUINT32(data, @dwSilver)
		ByteUtil::writeUINT32(data, @dwGold)
		ByteUtil::writeUINT32(data, @dwCoupon)
		ByteUtil::writeUINT8(data, @byForbExpire)
		ByteUtil::writeUINT8(data, @byLockExpire)
		ByteUtil::writeUINT8(data, @byVIPLevel)
		ByteUtil::writeUINT32(data, @dwPrestige)
		ByteUtil::writeUINT32(data, @dwHonor)
		ByteUtil::writeUINT32(data, @dwDJ)
		ByteUtil::writeUINT32(data, @dwHistoryDJ)
		ByteUtil::writeUINT32(data, @dwCreateTime)
		ByteUtil::writeUINT16(data, @wShiMenTask)
		ByteUtil::writeUINT16(data, @wYaMenTaTask)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家背包信息
class SPlayerBagInfo
	attr_accessor:qwInstID #(UINT64)物品唯一ID
	attr_accessor:wItemID #(UINT16)物品模板
	attr_accessor:byType #(UINT8)1；背包，2：仓库
	attr_accessor:wCount #(UINT16)堆叠数
	attr_accessor:byBind #(UINT8)0：非绑定，1：绑定

	#构造函数
	def initialize
		@qwInstID = 0
		@wItemID = 0
		@byType = 0
		@wCount = 0
		@byBind = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInstID = @qwInstID
		obj.wItemID = @wItemID
		obj.byType = @byType
		obj.wCount = @wCount
		obj.byBind = @byBind
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPlayerBagInfo.new
		s.qwInstID = ByteUtil::readUINT64(data)
		s.wItemID = ByteUtil::readUINT16(data)
		s.byType = ByteUtil::readUINT8(data)
		s.wCount = ByteUtil::readUINT16(data)
		s.byBind = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPlayerBagInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeUINT8(data, @byType)
		ByteUtil::writeUINT16(data, @wCount)
		ByteUtil::writeUINT8(data, @byBind)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#天赐宝箱活动参数修改
class SChestInfo
	attr_accessor:dwTime #(UINT32)开启时间
	attr_accessor:byBig #(UINT8)大宝箱个数
	attr_accessor:byMid #(UINT8)中宝箱个数
	attr_accessor:bySmall #(UINT8)小宝箱个数
	attr_accessor:byPeroid #(UINT8)活动持续时间
	attr_accessor:wMapID #(UINT16)宝箱刷新地图

	#构造函数
	def initialize
		@dwTime = 0
		@byBig = 0
		@byMid = 0
		@bySmall = 0
		@byPeroid = 0
		@wMapID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwTime = @dwTime
		obj.byBig = @byBig
		obj.byMid = @byMid
		obj.bySmall = @bySmall
		obj.byPeroid = @byPeroid
		obj.wMapID = @wMapID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SChestInfo.new
		s.dwTime = ByteUtil::readUINT32(data)
		s.byBig = ByteUtil::readUINT8(data)
		s.byMid = ByteUtil::readUINT8(data)
		s.bySmall = ByteUtil::readUINT8(data)
		s.byPeroid = ByteUtil::readUINT8(data)
		s.wMapID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SChestInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwTime)
		ByteUtil::writeUINT8(data, @byBig)
		ByteUtil::writeUINT8(data, @byMid)
		ByteUtil::writeUINT8(data, @bySmall)
		ByteUtil::writeUINT8(data, @byPeroid)
		ByteUtil::writeUINT16(data, @wMapID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[OnUserRecharge:玩家充值仙石]的返回的参数组成的结构体
class SRetParam_OnUserRecharge
	attr_accessor:byRet#(UINT8)充值返回值(值为0:成功 非0其他错误)
	attr_accessor:strError#(string)错误码字符串(若成功为空)

	#构造函数
	def initialize
		@byRet = 0
		@strError = ''
	end
end

#函数[ModifyActivityIntegral:修改玩家各种活动积分信息]的返回的参数组成的结构体
class SRetParam_ModifyActivityIntegral
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[GetPlayerInfo:获取玩家信息]的返回的参数组成的结构体
class SRetParam_GetPlayerInfo
	attr_accessor:vecPlayerInfo#(SPlayerInfo的数组)玩家信息

	#构造函数
	def initialize
		@vecPlayerInfo = Array.new
	end
end

#函数[GetPlayerBagInfo:获取玩家背包信息]的返回的参数组成的结构体
class SRetParam_GetPlayerBagInfo
	attr_accessor:vecPlayerBagInfo#(SPlayerBagInfo的数组)玩家背包信息

	#构造函数
	def initialize
		@vecPlayerBagInfo = Array.new
	end
end

#函数[DelItem:删除物品]的返回的参数组成的结构体
class SRetParam_DelItem
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[GetActList:获取活动列表信息]的返回的参数组成的结构体
class SRetParam_GetActList
	attr_accessor:vecIDs#(UINT16数组)活动列表

	#构造函数
	def initialize
		@vecIDs = Array.new
	end
end

#函数[OpenAct:开启指定活动]的返回的参数组成的结构体
class SRetParam_OpenAct
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[LockOrUnlockUser:封号/解封]的返回的参数组成的结构体
class SRetParam_LockOrUnlockUser
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[LockOrUnlockSpeak:禁言/解禁]的返回的参数组成的结构体
class SRetParam_LockOrUnlockSpeak
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[GetOnlineNum:获取在线人数]的返回的参数组成的结构体
class SRetParam_GetOnlineNum
	attr_accessor:dwOnlineNum#(UINT32)在线人数

	#构造函数
	def initialize
		@dwOnlineNum = 0
	end
end

#函数[SendItem:发放物品/货币]的返回的参数组成的结构体
class SRetParam_SendItem
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[SubMoney:减少货币数量]的返回的参数组成的结构体
class SRetParam_SubMoney
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[SendVIPItem:发放VIP物品]的返回的参数组成的结构体
class SRetParam_SendVIPItem
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[SendClanItem:发放帮派物品]的返回的参数组成的结构体
class SRetParam_SendClanItem
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[GlobalSendItem:全区发放物品]的返回的参数组成的结构体
class SRetParam_GlobalSendItem
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[SendMail:发送邮件]的返回的参数组成的结构体
class SRetParam_SendMail
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[GlobalSendMail:全区发送邮件]的返回的参数组成的结构体
class SRetParam_GlobalSendMail
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[GlobalSendNotice:发送公告]的返回的参数组成的结构体
class SRetParam_GlobalSendNotice
	attr_accessor:dwNoticeID#(UINT32)返回公告ID
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@dwNoticeID = 0
		@eOptResult = 0
	end
end

#函数[GlobalDelNotice:删除公告]的返回的参数组成的结构体
class SRetParam_GlobalDelNotice
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[GlobalSendSysDialog:发送系统弹窗]的返回的参数组成的结构体
class SRetParam_GlobalSendSysDialog
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[OpenDiscountActivity:开启商城限购活动]的返回的参数组成的结构体
class SRetParam_OpenDiscountActivity
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[SetPlayerLevel:设置玩家等级]的返回的参数组成的结构体
class SRetParam_SetPlayerLevel
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[SetPlayerVIPLevel:设置玩家VIP等级]的返回的参数组成的结构体
class SRetParam_SetPlayerVIPLevel
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[TaskManager:日常任务管理]的返回的参数组成的结构体
class SRetParam_TaskManager
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[GetTaskState:任务集市中任务状态查询]的返回的参数组成的结构体
class SRetParam_GetTaskState
	attr_accessor:wServerNo#(UINT16)区服ID
	attr_accessor:eTaskState#(枚举类型：ETaskState)状态返回

	#构造函数
	def initialize
		@wServerNo = 0
		@eTaskState = 0
	end
end

#函数[SynWeiweiPersonNum:同步微信微博人数]的返回的参数组成的结构体
class SRetParam_SynWeiweiPersonNum
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[CheckCDK:检测CDK]的返回的参数组成的结构体
class SRetParam_CheckCDK
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[SynQQAlarm:QQAlarm安装]的返回的参数组成的结构体
class SRetParam_SynQQAlarm
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[ModifyChest:天赐宝箱活动参数修改]的返回的参数组成的结构体
class SRetParam_ModifyChest
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[SetPool:设置汇灵盏奖励池]的返回的参数组成的结构体
class SRetParam_SetPool
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[GetLoginDays:请求玩家累计登入天数]的返回的参数组成的结构体
class SRetParam_GetLoginDays
	attr_accessor:dwDays#(UINT32)累计登入天数
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@dwDays = 0
		@eOptResult = 0
	end
end

#函数[SendQQGroupMsg:发送工会聊天信息]的返回的参数组成的结构体
class SRetParam_SendQQGroupMsg
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#函数[SendTitle:添加称号]的返回的参数组成的结构体
class SRetParam_SendTitle
	attr_accessor:eOptResult#(枚举类型：EOptResult)后台操作结果

	#构造函数
	def initialize
		@eOptResult = 0
	end
end

#协议类：PHP相关协议
class PHPProtBase < ProtocolBase
	#以下为发送函数
	#发送：玩家充值仙石
	def send_OnUserRecharge(
		wServerNo,  #(UINT16)区服ID
		strToken,  #(string)memcach校验
		strNo,  #(string)充值流水号
		qwUserID,  #(UINT64)用户ID
		wID,  #(UINT16)仙石包ID(41[10仙石],42[100仙石],43[300仙石],44[500仙石],45[1000仙石],46[3000仙石])或者Q点直购道具ID
		dwValue,  #(UINT32)充值的仙石包数量或者Q点直购道具数量
		strUINT,  #(string)单位,默认发QQCOIN(Q点)
		strMoney,  #(string)仙石对应的QQCOIN值
		strParam #(string)用来url请求
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeSTRING(data, strToken)
		ByteUtil::writeSTRING(data, strNo)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeUINT16(data, wID)
		ByteUtil::writeUINT32(data, dwValue)
		ByteUtil::writeSTRING(data, strUINT)
		ByteUtil::writeSTRING(data, strMoney)
		ByteUtil::writeSTRING(data, strParam)
		return @svrHandler.sendPacket(data)
	end

	#发送：修改玩家各种活动积分信息
	def send_ModifyActivityIntegral(
		wServerNo,  #(UINT16)区服ID
		qwUserID,  #(UINT64)用户ID
		eType,  #(枚举类型：EActivityType)活动ID
		dwActCount #(INT32)活动积分(负数表明减少)
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeUINT8(data, eType)
		ByteUtil::writeINT32(data, dwActCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取玩家信息
	def send_GetPlayerInfo(
		wServerNo,  #(UINT16)区服ID
		strName,  #(string)角色名称
		qwUserID #(UINT64)用户ID
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeSTRING(data, strName)
		ByteUtil::writeUINT64(data, qwUserID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取玩家背包信息
	def send_GetPlayerBagInfo(
		wServerNo,  #(UINT16)区服ID
		strName,  #(string)角色名称
		qwUserID #(UINT64)用户ID
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeSTRING(data, strName)
		ByteUtil::writeUINT64(data, qwUserID)
		return @svrHandler.sendPacket(data)
	end

	#发送：删除物品
	def send_DelItem(
		wServerNo,  #(UINT16)区服ID
		strName,  #(string)角色名称
		qwUserID,  #(UINT64)用户ID
		byType,  #(UINT8)1；背包，2：仓库
		qwInstID,  #(UINT64)物品唯一ID
		wCount #(UINT16)堆叠数
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeSTRING(data, strName)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeUINT8(data, byType)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT16(data, wCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取活动列表信息
	def send_GetActList(
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：开启指定活动
	def send_OpenAct(
		eType,  #(枚举类型：EActivityType)活动ID
		dwBegin,  #(UINT32)活动开启时间
		dwEnd #(UINT32)活动结束时间
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eType)
		ByteUtil::writeUINT32(data, dwBegin)
		ByteUtil::writeUINT32(data, dwEnd)
		return @svrHandler.sendPacket(data)
	end

	#发送：封号/解封
	def send_LockOrUnlockUser(
		wServerNo,  #(UINT16)区服ID
		strName,  #(string)角色名称
		qwUserID,  #(UINT64)用户ID
		eOptType,  #(枚举类型：EOptType)后台操作类型(eOptLockUser/eOptUnlockUser)
		dwEndTime,  #(UINT32)时间
		strArgument #(string)理由
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeSTRING(data, strName)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeINT8(data, eOptType)
		ByteUtil::writeUINT32(data, dwEndTime)
		ByteUtil::writeSTRING(data, strArgument)
		return @svrHandler.sendPacket(data)
	end

	#发送：禁言/解禁
	def send_LockOrUnlockSpeak(
		wServerNo,  #(UINT16)区服ID
		strName,  #(string)角色名称
		qwUserID,  #(UINT64)用户ID
		eOptType,  #(枚举类型：EOptType)后台操作类型(eOptLockSpeak/eOptUnlockSpeak)
		dwEndTime,  #(UINT32)时间
		strArgument #(string)理由
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeSTRING(data, strName)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeINT8(data, eOptType)
		ByteUtil::writeUINT32(data, dwEndTime)
		ByteUtil::writeSTRING(data, strArgument)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取在线人数
	def send_GetOnlineNum(
		wServerNo #(UINT16)区服ID
	)
		sessionID = @sessionMgr.getNewSession(self, 10);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		return @svrHandler.sendPacket(data)
	end

	#发送：发放物品/货币
	def send_SendItem(
		wServerNo,  #(UINT16)区服ID
		strUserID,  #(string)格式：用户AID|户BID|..
		strName,  #(string)角色名称(注：考虑到解析字符异常，名字不支持多个)
		strItem,  #(string)格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		strTitle,  #(string)邮件标题
		strContent,  #(string)邮件内容
		strArgument #(string)理由
	)
		sessionID = @sessionMgr.getNewSession(self, 11);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeSTRING(data, strUserID)
		ByteUtil::writeSTRING(data, strName)
		ByteUtil::writeSTRING(data, strItem)
		ByteUtil::writeSTRING(data, strTitle)
		ByteUtil::writeSTRING(data, strContent)
		ByteUtil::writeSTRING(data, strArgument)
		return @svrHandler.sendPacket(data)
	end

	#发送：减少货币数量
	def send_SubMoney(
		wServerNo,  #(UINT16)区服ID
		strUserID,  #(string)格式：用户AID|户BID|..
		strName,  #(string)角色名称(注：考虑到解析字符异常，名字不支持多个)
		strItem #(string)格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
	)
		sessionID = @sessionMgr.getNewSession(self, 12);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeSTRING(data, strUserID)
		ByteUtil::writeSTRING(data, strName)
		ByteUtil::writeSTRING(data, strItem)
		return @svrHandler.sendPacket(data)
	end

	#发送：发放VIP物品
	def send_SendVIPItem(
		wServerNo,  #(UINT16)区服ID
		byVIPMinLevel,  #(UINT8)VIP最小等级
		byVIPMaxLevel,  #(UINT8)VIP最大等级
		strItem,  #(string)格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		strTitle,  #(string)邮件标题
		strContent,  #(string)邮件内容
		strArgument #(string)理由
	)
		sessionID = @sessionMgr.getNewSession(self, 13);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 13
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeUINT8(data, byVIPMinLevel)
		ByteUtil::writeUINT8(data, byVIPMaxLevel)
		ByteUtil::writeSTRING(data, strItem)
		ByteUtil::writeSTRING(data, strTitle)
		ByteUtil::writeSTRING(data, strContent)
		ByteUtil::writeSTRING(data, strArgument)
		return @svrHandler.sendPacket(data)
	end

	#发送：发放帮派物品
	def send_SendClanItem(
		wServerNo,  #(UINT16)区服ID
		qwClanID,  #(UINT64)帮派ID
		eTarget,  #(枚举类型：ESendTarget)对象
		strItem,  #(string)格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		strTitle,  #(string)邮件标题
		strContent,  #(string)邮件内容
		strArgument #(string)理由
	)
		sessionID = @sessionMgr.getNewSession(self, 14);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 14
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeUINT64(data, qwClanID)
		ByteUtil::writeUINT8(data, eTarget)
		ByteUtil::writeSTRING(data, strItem)
		ByteUtil::writeSTRING(data, strTitle)
		ByteUtil::writeSTRING(data, strContent)
		ByteUtil::writeSTRING(data, strArgument)
		return @svrHandler.sendPacket(data)
	end

	#发送：全区发放物品
	def send_GlobalSendItem(
		wServerNo,  #(UINT16)区服ID
		eTarget,  #(枚举类型：ESendTarget)对象
		strItem,  #(string)格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		strTitle,  #(string)邮件标题
		strContent,  #(string)邮件内容
		strArgument #(string)理由
	)
		sessionID = @sessionMgr.getNewSession(self, 15);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 15
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeUINT8(data, eTarget)
		ByteUtil::writeSTRING(data, strItem)
		ByteUtil::writeSTRING(data, strTitle)
		ByteUtil::writeSTRING(data, strContent)
		ByteUtil::writeSTRING(data, strArgument)
		return @svrHandler.sendPacket(data)
	end

	#发送：发送邮件
	def send_SendMail(
		wServerNo,  #(UINT16)区服ID
		strUserID,  #(string)格式：用户AID|户BID|..
		strName,  #(string)角色名称(注：考虑到解析字符异常，名字不支持多个)
		strTitle,  #(string)邮件标题
		strContent #(string)邮件内容
	)
		sessionID = @sessionMgr.getNewSession(self, 16);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 16
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeSTRING(data, strUserID)
		ByteUtil::writeSTRING(data, strName)
		ByteUtil::writeSTRING(data, strTitle)
		ByteUtil::writeSTRING(data, strContent)
		return @svrHandler.sendPacket(data)
	end

	#发送：全区发送邮件
	def send_GlobalSendMail(
		wServerNo,  #(UINT16)区服ID
		eTarget,  #(枚举类型：ESendTarget)对象
		strTitle,  #(string)邮件标题
		strContent #(string)邮件内容
	)
		sessionID = @sessionMgr.getNewSession(self, 17);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 17
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeUINT8(data, eTarget)
		ByteUtil::writeSTRING(data, strTitle)
		ByteUtil::writeSTRING(data, strContent)
		return @svrHandler.sendPacket(data)
	end

	#发送：发送公告
	def send_GlobalSendNotice(
		wServerNo,  #(UINT16)区服ID
		strContent,  #(string)系统弹窗内容
		ePlatformType,  #(枚举类型：EPlatformType)平台类型
		eShowType,  #(枚举类型：EShowType)显示区域
		eRollType,  #(枚举类型：ERollType)是否滚动
		eSendType,  #(枚举类型：ESendType)是否立即发送
		dwBeginTime,  #(UINT32)公告开始时间(注：如果选择立即发送，dwBeginTime为0)
		dwEndTime #(UINT32)公告结束时间(注：如果选择立即发送，dwEndTime为0)
	)
		sessionID = @sessionMgr.getNewSession(self, 18);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 18
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeSTRING(data, strContent)
		ByteUtil::writeUINT8(data, ePlatformType)
		ByteUtil::writeUINT8(data, eShowType)
		ByteUtil::writeUINT8(data, eRollType)
		ByteUtil::writeUINT8(data, eSendType)
		ByteUtil::writeUINT32(data, dwBeginTime)
		ByteUtil::writeUINT32(data, dwEndTime)
		return @svrHandler.sendPacket(data)
	end

	#发送：删除公告
	def send_GlobalDelNotice(
		wServerNo,  #(UINT16)区服ID
		dwNoticeID #(UINT32)公告ID
	)
		sessionID = @sessionMgr.getNewSession(self, 19);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 19
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeUINT32(data, dwNoticeID)
		return @svrHandler.sendPacket(data)
	end

	#发送：发送系统弹窗
	def send_GlobalSendSysDialog(
		wServerNo,  #(UINT16)区服ID
		ePlatformType,  #(枚举类型：EPlatformType)平台类型
		eDialogType #(枚举类型：EDialogType)弹窗类型
	)
		sessionID = @sessionMgr.getNewSession(self, 20);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 20
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeUINT8(data, ePlatformType)
		ByteUtil::writeUINT8(data, eDialogType)
		return @svrHandler.sendPacket(data)
	end

	#发送：开启商城限购活动
	def send_OpenDiscountActivity(
		wServerNo,  #(UINT16)区服ID
		byPos,  #(UINT8)限购位置(0,1,2表示)
		byOptType,  #(UINT8)操作类型(0：增加；1：删除)
		strDisItems,  #(string)限购道具信息(itemID,原价,折扣价|...)
		byLimitType,  #(UINT8)类型限制(0无条件、1充值限购、2消费限购)
		dwLimitValue,  #(UINT32)达到的仙石数量限制(0无条件、1充值限购、2消费限购)
		wLimitCount,  #(UINT16)购买道具个数限制
		dwBeginTime,  #(UINT32)限购开始时间
		dwEndTime #(UINT32)限购结束时间
	)
		sessionID = @sessionMgr.getNewSession(self, 21);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 21
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeUINT8(data, byPos)
		ByteUtil::writeUINT8(data, byOptType)
		ByteUtil::writeSTRING(data, strDisItems)
		ByteUtil::writeUINT8(data, byLimitType)
		ByteUtil::writeUINT32(data, dwLimitValue)
		ByteUtil::writeUINT16(data, wLimitCount)
		ByteUtil::writeUINT32(data, dwBeginTime)
		ByteUtil::writeUINT32(data, dwEndTime)
		return @svrHandler.sendPacket(data)
	end

	#发送：设置玩家等级
	def send_SetPlayerLevel(
		wServerNo,  #(UINT16)区服ID
		strName,  #(string)角色名称
		qwUserID,  #(UINT64)用户ID
		wLevel #(UINT16)等级
	)
		sessionID = @sessionMgr.getNewSession(self, 22);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 22
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeSTRING(data, strName)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeUINT16(data, wLevel)
		return @svrHandler.sendPacket(data)
	end

	#发送：设置玩家VIP等级
	def send_SetPlayerVIPLevel(
		wServerNo,  #(UINT16)区服ID
		strName,  #(string)角色名称
		qwUserID,  #(UINT64)用户ID
		eOptType,  #(枚举类型：EOptType)后台台操作类型(eOptSetPlayerVIPLevel/eOptAddGrowthValue)
		wLevelOrGrowthValue #(UINT32)等级or成长值
	)
		sessionID = @sessionMgr.getNewSession(self, 23);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 23
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeSTRING(data, strName)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeINT8(data, eOptType)
		ByteUtil::writeUINT32(data, wLevelOrGrowthValue)
		return @svrHandler.sendPacket(data)
	end

	#发送：日常任务管理
	def send_TaskManager(
		wServerNo,  #(UINT16)区服ID
		strUserID,  #(string)格式：用户AID|户BID|..
		strName,  #(string)角色名称(注：考虑到解析字符异常，名字不支持多个)
		ePHPTaskType #(枚举类型：EPHPTaskType)任务类型
	)
		sessionID = @sessionMgr.getNewSession(self, 24);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 24
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeSTRING(data, strUserID)
		ByteUtil::writeSTRING(data, strName)
		ByteUtil::writeUINT8(data, ePHPTaskType)
		return @svrHandler.sendPacket(data)
	end

	#发送：平台信息
	def send_PlatformInfo(
		byPtType,  #(枚举类型：EPlatformType)平台类型
		byQQPtType,  #(枚举类型：EQQPlatformType)QQ平台类型
		byQQPtLv,  #(UINT8)QQ平台类型等级
		byQQPtYearType,  #(UINT8)是否年费
		byQQPtLuxuryType,  #(UINT8)是否豪华
		customPar1,  #(string)广告主来源
		customPar2,  #(string)广告次来源
		strOpenId,  #(string)openID
		strOpenKey #(string)openKey
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 25
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, byPtType)
		ByteUtil::writeUINT8(data, byQQPtType)
		ByteUtil::writeUINT8(data, byQQPtLv)
		ByteUtil::writeUINT8(data, byQQPtYearType)
		ByteUtil::writeUINT8(data, byQQPtLuxuryType)
		ByteUtil::writeSTRING(data, customPar1)
		ByteUtil::writeSTRING(data, customPar2)
		ByteUtil::writeSTRING(data, strOpenId)
		ByteUtil::writeSTRING(data, strOpenKey)
		return @svrHandler.sendPacket(data)
	end

	#发送：任务集市中任务状态查询
	def send_GetTaskState(
		wServerNo,  #(UINT16)区服ID
		qwUserID,  #(UINT64)玩家ID
		dwTaskID,  #(UINT32)任务ID
		byStep,  #(UINT8)步骤ID
		eTaskOpt #(枚举类型：ETaskOpt)任务操作
	)
		sessionID = @sessionMgr.getNewSession(self, 25);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 26
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeUINT32(data, dwTaskID)
		ByteUtil::writeUINT8(data, byStep)
		ByteUtil::writeUINT8(data, eTaskOpt)
		return @svrHandler.sendPacket(data)
	end

	#发送：同步微信微博人数
	def send_SynWeiweiPersonNum(
		wServerNo,  #(UINT16)区服ID
		qwUserID,  #(UINT64)玩家ID
		byType,  #(UINT8)任务ID
		dwCount #(UINT32)步骤ID
	)
		sessionID = @sessionMgr.getNewSession(self, 26);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 27
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeUINT8(data, byType)
		ByteUtil::writeUINT32(data, dwCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：检测CDK
	def send_CheckCDK(
		wServerNo,  #(UINT16)区服ID
		qwUserID,  #(UINT64)玩家ID
		strCDK #(string)CDK码
	)
		sessionID = @sessionMgr.getNewSession(self, 27);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 28
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeSTRING(data, strCDK)
		return @svrHandler.sendPacket(data)
	end

	#发送：QQAlarm安装
	def send_SynQQAlarm(
		wServerNo,  #(UINT16)区服ID
		qwUserID #(UINT64)玩家ID
	)
		sessionID = @sessionMgr.getNewSession(self, 28);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 29
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeUINT64(data, qwUserID)
		return @svrHandler.sendPacket(data)
	end

	#发送：天赐宝箱活动参数修改
	def send_ModifyChest(
		sInfo #(类类型：SChestInfo)数据
	)
		sessionID = @sessionMgr.getNewSession(self, 29);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 30
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		sInfo.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：设置汇灵盏奖励池
	def send_SetPool(
		byType,  #(UINT8)类型，0表示设置奖励池最大值，1表示设置奖励池现有值
		dwValue #(UINT32)数据
	)
		sessionID = @sessionMgr.getNewSession(self, 30);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 31
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byType)
		ByteUtil::writeUINT32(data, dwValue)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求玩家累计登入天数
	def send_GetLoginDays(
		wServerNo,  #(UINT16)区服ID
		qwUserID #(UINT64)玩家ID
	)
		sessionID = @sessionMgr.getNewSession(self, 31);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 32
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeUINT64(data, qwUserID)
		return @svrHandler.sendPacket(data)
	end

	#发送：发送工会聊天信息
	def send_SendQQGroupMsg(
		qwGroupUserID,  #(UINT64)绑定qq的玩家ID
		wServerNo,  #(UINT16)聊天玩家区号ID
		qwUserID,  #(UINT64)聊天玩家账号ID
		strChatMsg #(string)聊天
	)
		sessionID = @sessionMgr.getNewSession(self, 32);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 33
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwGroupUserID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeSTRING(data, strChatMsg)
		return @svrHandler.sendPacket(data)
	end

	#发送：添加称号
	def send_SendTitle(
		wServerNo,  #(UINT16)区服ID
		qwUserID,  #(UINT64)玩家ID
		wTitleID #(UINT16)TitleID
	)
		sessionID = @sessionMgr.getNewSession(self, 33);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 34
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wServerNo)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeUINT16(data, wTitleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：Test
	def send_TestPHP(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 35
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

#以下的返回函数需要重载
	#返回：玩家充值仙石
	def onReturn_OnUserRecharge(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_OnUserRecharge)返回的参数
	)
	end

	#返回：修改玩家各种活动积分信息
	def onReturn_ModifyActivityIntegral(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ModifyActivityIntegral)返回的参数
	)
	end

	#返回：获取玩家信息
	def onReturn_GetPlayerInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetPlayerInfo)返回的参数
	)
	end

	#返回：获取玩家背包信息
	def onReturn_GetPlayerBagInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetPlayerBagInfo)返回的参数
	)
	end

	#返回：删除物品
	def onReturn_DelItem(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_DelItem)返回的参数
	)
	end

	#返回：获取活动列表信息
	def onReturn_GetActList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetActList)返回的参数
	)
	end

	#返回：开启指定活动
	def onReturn_OpenAct(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_OpenAct)返回的参数
	)
	end

	#返回：封号/解封
	def onReturn_LockOrUnlockUser(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LockOrUnlockUser)返回的参数
	)
	end

	#返回：禁言/解禁
	def onReturn_LockOrUnlockSpeak(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LockOrUnlockSpeak)返回的参数
	)
	end

	#返回：获取在线人数
	def onReturn_GetOnlineNum(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetOnlineNum)返回的参数
	)
	end

	#返回：发放物品/货币
	def onReturn_SendItem(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SendItem)返回的参数
	)
	end

	#返回：减少货币数量
	def onReturn_SubMoney(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SubMoney)返回的参数
	)
	end

	#返回：发放VIP物品
	def onReturn_SendVIPItem(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SendVIPItem)返回的参数
	)
	end

	#返回：发放帮派物品
	def onReturn_SendClanItem(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SendClanItem)返回的参数
	)
	end

	#返回：全区发放物品
	def onReturn_GlobalSendItem(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GlobalSendItem)返回的参数
	)
	end

	#返回：发送邮件
	def onReturn_SendMail(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SendMail)返回的参数
	)
	end

	#返回：全区发送邮件
	def onReturn_GlobalSendMail(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GlobalSendMail)返回的参数
	)
	end

	#返回：发送公告
	def onReturn_GlobalSendNotice(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GlobalSendNotice)返回的参数
	)
	end

	#返回：删除公告
	def onReturn_GlobalDelNotice(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GlobalDelNotice)返回的参数
	)
	end

	#返回：发送系统弹窗
	def onReturn_GlobalSendSysDialog(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GlobalSendSysDialog)返回的参数
	)
	end

	#返回：开启商城限购活动
	def onReturn_OpenDiscountActivity(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_OpenDiscountActivity)返回的参数
	)
	end

	#返回：设置玩家等级
	def onReturn_SetPlayerLevel(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SetPlayerLevel)返回的参数
	)
	end

	#返回：设置玩家VIP等级
	def onReturn_SetPlayerVIPLevel(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SetPlayerVIPLevel)返回的参数
	)
	end

	#返回：日常任务管理
	def onReturn_TaskManager(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TaskManager)返回的参数
	)
	end

	#返回：任务集市中任务状态查询
	def onReturn_GetTaskState(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetTaskState)返回的参数
	)
	end

	#返回：同步微信微博人数
	def onReturn_SynWeiweiPersonNum(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SynWeiweiPersonNum)返回的参数
	)
	end

	#返回：检测CDK
	def onReturn_CheckCDK(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_CheckCDK)返回的参数
	)
	end

	#返回：QQAlarm安装
	def onReturn_SynQQAlarm(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SynQQAlarm)返回的参数
	)
	end

	#返回：天赐宝箱活动参数修改
	def onReturn_ModifyChest(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ModifyChest)返回的参数
	)
	end

	#返回：设置汇灵盏奖励池
	def onReturn_SetPool(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SetPool)返回的参数
	)
	end

	#返回：请求玩家累计登入天数
	def onReturn_GetLoginDays(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetLoginDays)返回的参数
	)
	end

	#返回：发送工会聊天信息
	def onReturn_SendQQGroupMsg(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SendQQGroupMsg)返回的参数
	)
	end

	#返回：添加称号
	def onReturn_SendTitle(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SendTitle)返回的参数
	)
	end

	#返回处理：玩家充值仙石
	def _doReturn_OnUserRecharge(data)
		retParam = SRetParam_OnUserRecharge.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readUINT8(data) #(UINT8)充值返回值(值为0:成功 非0其他错误)
		strError = ByteUtil::readSTRING(data) #(string)错误码字符串(若成功为空)
		retParam.byRet = byRet
		retParam.strError = strError
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_OnUserRecharge(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：玩家充值仙石
	def _onTimeOut_OnUserRecharge(sessionID)
		retParam = SRetParam_OnUserRecharge.new;
		onReturn_OnUserRecharge(2, retParam)
	end

	#返回处理：修改玩家各种活动积分信息
	def _doReturn_ModifyActivityIntegral(data)
		retParam = SRetParam_ModifyActivityIntegral.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ModifyActivityIntegral(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：修改玩家各种活动积分信息
	def _onTimeOut_ModifyActivityIntegral(sessionID)
		retParam = SRetParam_ModifyActivityIntegral.new;
		onReturn_ModifyActivityIntegral(2, retParam)
	end

	#返回处理：获取玩家信息
	def _doReturn_GetPlayerInfo(data)
		retParam = SRetParam_GetPlayerInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecPlayerInfo = SPlayerInfo::vectorFromStream(data) #(SPlayerInfo的数组)玩家信息
		retParam.vecPlayerInfo = vecPlayerInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetPlayerInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取玩家信息
	def _onTimeOut_GetPlayerInfo(sessionID)
		retParam = SRetParam_GetPlayerInfo.new;
		onReturn_GetPlayerInfo(2, retParam)
	end

	#返回处理：获取玩家背包信息
	def _doReturn_GetPlayerBagInfo(data)
		retParam = SRetParam_GetPlayerBagInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecPlayerBagInfo = SPlayerBagInfo::vectorFromStream(data) #(SPlayerBagInfo的数组)玩家背包信息
		retParam.vecPlayerBagInfo = vecPlayerBagInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetPlayerBagInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取玩家背包信息
	def _onTimeOut_GetPlayerBagInfo(sessionID)
		retParam = SRetParam_GetPlayerBagInfo.new;
		onReturn_GetPlayerBagInfo(2, retParam)
	end

	#返回处理：删除物品
	def _doReturn_DelItem(data)
		retParam = SRetParam_DelItem.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_DelItem(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：删除物品
	def _onTimeOut_DelItem(sessionID)
		retParam = SRetParam_DelItem.new;
		onReturn_DelItem(2, retParam)
	end

	#返回处理：获取活动列表信息
	def _doReturn_GetActList(data)
		retParam = SRetParam_GetActList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecIDs = ByteUtil::readVecUINT16(data) #(UINT16数组)活动列表
		retParam.vecIDs = vecIDs
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetActList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取活动列表信息
	def _onTimeOut_GetActList(sessionID)
		retParam = SRetParam_GetActList.new;
		onReturn_GetActList(2, retParam)
	end

	#返回处理：开启指定活动
	def _doReturn_OpenAct(data)
		retParam = SRetParam_OpenAct.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_OpenAct(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：开启指定活动
	def _onTimeOut_OpenAct(sessionID)
		retParam = SRetParam_OpenAct.new;
		onReturn_OpenAct(2, retParam)
	end

	#返回处理：封号/解封
	def _doReturn_LockOrUnlockUser(data)
		retParam = SRetParam_LockOrUnlockUser.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LockOrUnlockUser(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：封号/解封
	def _onTimeOut_LockOrUnlockUser(sessionID)
		retParam = SRetParam_LockOrUnlockUser.new;
		onReturn_LockOrUnlockUser(2, retParam)
	end

	#返回处理：禁言/解禁
	def _doReturn_LockOrUnlockSpeak(data)
		retParam = SRetParam_LockOrUnlockSpeak.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LockOrUnlockSpeak(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：禁言/解禁
	def _onTimeOut_LockOrUnlockSpeak(sessionID)
		retParam = SRetParam_LockOrUnlockSpeak.new;
		onReturn_LockOrUnlockSpeak(2, retParam)
	end

	#返回处理：获取在线人数
	def _doReturn_GetOnlineNum(data)
		retParam = SRetParam_GetOnlineNum.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwOnlineNum = ByteUtil::readUINT32(data) #(UINT32)在线人数
		retParam.dwOnlineNum = dwOnlineNum
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetOnlineNum(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取在线人数
	def _onTimeOut_GetOnlineNum(sessionID)
		retParam = SRetParam_GetOnlineNum.new;
		onReturn_GetOnlineNum(2, retParam)
	end

	#返回处理：发放物品/货币
	def _doReturn_SendItem(data)
		retParam = SRetParam_SendItem.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SendItem(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：发放物品/货币
	def _onTimeOut_SendItem(sessionID)
		retParam = SRetParam_SendItem.new;
		onReturn_SendItem(2, retParam)
	end

	#返回处理：减少货币数量
	def _doReturn_SubMoney(data)
		retParam = SRetParam_SubMoney.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SubMoney(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：减少货币数量
	def _onTimeOut_SubMoney(sessionID)
		retParam = SRetParam_SubMoney.new;
		onReturn_SubMoney(2, retParam)
	end

	#返回处理：发放VIP物品
	def _doReturn_SendVIPItem(data)
		retParam = SRetParam_SendVIPItem.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SendVIPItem(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：发放VIP物品
	def _onTimeOut_SendVIPItem(sessionID)
		retParam = SRetParam_SendVIPItem.new;
		onReturn_SendVIPItem(2, retParam)
	end

	#返回处理：发放帮派物品
	def _doReturn_SendClanItem(data)
		retParam = SRetParam_SendClanItem.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SendClanItem(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：发放帮派物品
	def _onTimeOut_SendClanItem(sessionID)
		retParam = SRetParam_SendClanItem.new;
		onReturn_SendClanItem(2, retParam)
	end

	#返回处理：全区发放物品
	def _doReturn_GlobalSendItem(data)
		retParam = SRetParam_GlobalSendItem.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GlobalSendItem(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：全区发放物品
	def _onTimeOut_GlobalSendItem(sessionID)
		retParam = SRetParam_GlobalSendItem.new;
		onReturn_GlobalSendItem(2, retParam)
	end

	#返回处理：发送邮件
	def _doReturn_SendMail(data)
		retParam = SRetParam_SendMail.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SendMail(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：发送邮件
	def _onTimeOut_SendMail(sessionID)
		retParam = SRetParam_SendMail.new;
		onReturn_SendMail(2, retParam)
	end

	#返回处理：全区发送邮件
	def _doReturn_GlobalSendMail(data)
		retParam = SRetParam_GlobalSendMail.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GlobalSendMail(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：全区发送邮件
	def _onTimeOut_GlobalSendMail(sessionID)
		retParam = SRetParam_GlobalSendMail.new;
		onReturn_GlobalSendMail(2, retParam)
	end

	#返回处理：发送公告
	def _doReturn_GlobalSendNotice(data)
		retParam = SRetParam_GlobalSendNotice.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwNoticeID = ByteUtil::readUINT32(data) #(UINT32)返回公告ID
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.dwNoticeID = dwNoticeID
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GlobalSendNotice(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：发送公告
	def _onTimeOut_GlobalSendNotice(sessionID)
		retParam = SRetParam_GlobalSendNotice.new;
		onReturn_GlobalSendNotice(2, retParam)
	end

	#返回处理：删除公告
	def _doReturn_GlobalDelNotice(data)
		retParam = SRetParam_GlobalDelNotice.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GlobalDelNotice(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：删除公告
	def _onTimeOut_GlobalDelNotice(sessionID)
		retParam = SRetParam_GlobalDelNotice.new;
		onReturn_GlobalDelNotice(2, retParam)
	end

	#返回处理：发送系统弹窗
	def _doReturn_GlobalSendSysDialog(data)
		retParam = SRetParam_GlobalSendSysDialog.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GlobalSendSysDialog(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：发送系统弹窗
	def _onTimeOut_GlobalSendSysDialog(sessionID)
		retParam = SRetParam_GlobalSendSysDialog.new;
		onReturn_GlobalSendSysDialog(2, retParam)
	end

	#返回处理：开启商城限购活动
	def _doReturn_OpenDiscountActivity(data)
		retParam = SRetParam_OpenDiscountActivity.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_OpenDiscountActivity(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：开启商城限购活动
	def _onTimeOut_OpenDiscountActivity(sessionID)
		retParam = SRetParam_OpenDiscountActivity.new;
		onReturn_OpenDiscountActivity(2, retParam)
	end

	#返回处理：设置玩家等级
	def _doReturn_SetPlayerLevel(data)
		retParam = SRetParam_SetPlayerLevel.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SetPlayerLevel(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：设置玩家等级
	def _onTimeOut_SetPlayerLevel(sessionID)
		retParam = SRetParam_SetPlayerLevel.new;
		onReturn_SetPlayerLevel(2, retParam)
	end

	#返回处理：设置玩家VIP等级
	def _doReturn_SetPlayerVIPLevel(data)
		retParam = SRetParam_SetPlayerVIPLevel.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SetPlayerVIPLevel(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：设置玩家VIP等级
	def _onTimeOut_SetPlayerVIPLevel(sessionID)
		retParam = SRetParam_SetPlayerVIPLevel.new;
		onReturn_SetPlayerVIPLevel(2, retParam)
	end

	#返回处理：日常任务管理
	def _doReturn_TaskManager(data)
		retParam = SRetParam_TaskManager.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TaskManager(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：日常任务管理
	def _onTimeOut_TaskManager(sessionID)
		retParam = SRetParam_TaskManager.new;
		onReturn_TaskManager(2, retParam)
	end

	#返回处理：任务集市中任务状态查询
	def _doReturn_GetTaskState(data)
		retParam = SRetParam_GetTaskState.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		wServerNo = ByteUtil::readUINT16(data) #(UINT16)区服ID
		eTaskState = ByteUtil::readUINT8(data) #(枚举类型：ETaskState)状态返回
		retParam.wServerNo = wServerNo
		retParam.eTaskState = eTaskState
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetTaskState(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：任务集市中任务状态查询
	def _onTimeOut_GetTaskState(sessionID)
		retParam = SRetParam_GetTaskState.new;
		onReturn_GetTaskState(2, retParam)
	end

	#返回处理：同步微信微博人数
	def _doReturn_SynWeiweiPersonNum(data)
		retParam = SRetParam_SynWeiweiPersonNum.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SynWeiweiPersonNum(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：同步微信微博人数
	def _onTimeOut_SynWeiweiPersonNum(sessionID)
		retParam = SRetParam_SynWeiweiPersonNum.new;
		onReturn_SynWeiweiPersonNum(2, retParam)
	end

	#返回处理：检测CDK
	def _doReturn_CheckCDK(data)
		retParam = SRetParam_CheckCDK.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_CheckCDK(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：检测CDK
	def _onTimeOut_CheckCDK(sessionID)
		retParam = SRetParam_CheckCDK.new;
		onReturn_CheckCDK(2, retParam)
	end

	#返回处理：QQAlarm安装
	def _doReturn_SynQQAlarm(data)
		retParam = SRetParam_SynQQAlarm.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SynQQAlarm(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：QQAlarm安装
	def _onTimeOut_SynQQAlarm(sessionID)
		retParam = SRetParam_SynQQAlarm.new;
		onReturn_SynQQAlarm(2, retParam)
	end

	#返回处理：天赐宝箱活动参数修改
	def _doReturn_ModifyChest(data)
		retParam = SRetParam_ModifyChest.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ModifyChest(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：天赐宝箱活动参数修改
	def _onTimeOut_ModifyChest(sessionID)
		retParam = SRetParam_ModifyChest.new;
		onReturn_ModifyChest(2, retParam)
	end

	#返回处理：设置汇灵盏奖励池
	def _doReturn_SetPool(data)
		retParam = SRetParam_SetPool.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SetPool(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：设置汇灵盏奖励池
	def _onTimeOut_SetPool(sessionID)
		retParam = SRetParam_SetPool.new;
		onReturn_SetPool(2, retParam)
	end

	#返回处理：请求玩家累计登入天数
	def _doReturn_GetLoginDays(data)
		retParam = SRetParam_GetLoginDays.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwDays = ByteUtil::readUINT32(data) #(UINT32)累计登入天数
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.dwDays = dwDays
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetLoginDays(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求玩家累计登入天数
	def _onTimeOut_GetLoginDays(sessionID)
		retParam = SRetParam_GetLoginDays.new;
		onReturn_GetLoginDays(2, retParam)
	end

	#返回处理：发送工会聊天信息
	def _doReturn_SendQQGroupMsg(data)
		retParam = SRetParam_SendQQGroupMsg.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SendQQGroupMsg(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：发送工会聊天信息
	def _onTimeOut_SendQQGroupMsg(sessionID)
		retParam = SRetParam_SendQQGroupMsg.new;
		onReturn_SendQQGroupMsg(2, retParam)
	end

	#返回处理：添加称号
	def _doReturn_SendTitle(data)
		retParam = SRetParam_SendTitle.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOptResult = ByteUtil::readINT8(data) #(枚举类型：EOptResult)后台操作结果
		retParam.eOptResult = eOptResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SendTitle(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：添加称号
	def _onTimeOut_SendTitle(sessionID)
		retParam = SRetParam_SendTitle.new;
		onReturn_SendTitle(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 90;
		@recvFuncList = Array.new

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_OnUserRecharge' #FuncID: 1
		@retFuncList[1] = '_doReturn_ModifyActivityIntegral' #FuncID: 2
		@retFuncList[2] = '_doReturn_GetPlayerInfo' #FuncID: 3
		@retFuncList[3] = '_doReturn_GetPlayerBagInfo' #FuncID: 4
		@retFuncList[4] = '_doReturn_DelItem' #FuncID: 5
		@retFuncList[5] = '_doReturn_GetActList' #FuncID: 6
		@retFuncList[6] = '_doReturn_OpenAct' #FuncID: 7
		@retFuncList[7] = '_doReturn_LockOrUnlockUser' #FuncID: 8
		@retFuncList[8] = '_doReturn_LockOrUnlockSpeak' #FuncID: 9
		@retFuncList[9] = '_doReturn_GetOnlineNum' #FuncID: 10
		@retFuncList[10] = '_doReturn_SendItem' #FuncID: 11
		@retFuncList[11] = '_doReturn_SubMoney' #FuncID: 12
		@retFuncList[12] = '_doReturn_SendVIPItem' #FuncID: 13
		@retFuncList[13] = '_doReturn_SendClanItem' #FuncID: 14
		@retFuncList[14] = '_doReturn_GlobalSendItem' #FuncID: 15
		@retFuncList[15] = '_doReturn_SendMail' #FuncID: 16
		@retFuncList[16] = '_doReturn_GlobalSendMail' #FuncID: 17
		@retFuncList[17] = '_doReturn_GlobalSendNotice' #FuncID: 18
		@retFuncList[18] = '_doReturn_GlobalDelNotice' #FuncID: 19
		@retFuncList[19] = '_doReturn_GlobalSendSysDialog' #FuncID: 20
		@retFuncList[20] = '_doReturn_OpenDiscountActivity' #FuncID: 21
		@retFuncList[21] = '_doReturn_SetPlayerLevel' #FuncID: 22
		@retFuncList[22] = '_doReturn_SetPlayerVIPLevel' #FuncID: 23
		@retFuncList[23] = '_doReturn_TaskManager' #FuncID: 24
		@retFuncList[24] = '_doReturn_GetTaskState' #FuncID: 25
		@retFuncList[25] = '_doReturn_SynWeiweiPersonNum' #FuncID: 26
		@retFuncList[26] = '_doReturn_CheckCDK' #FuncID: 27
		@retFuncList[27] = '_doReturn_SynQQAlarm' #FuncID: 28
		@retFuncList[28] = '_doReturn_ModifyChest' #FuncID: 29
		@retFuncList[29] = '_doReturn_SetPool' #FuncID: 30
		@retFuncList[30] = '_doReturn_GetLoginDays' #FuncID: 31
		@retFuncList[31] = '_doReturn_SendQQGroupMsg' #FuncID: 32
		@retFuncList[32] = '_doReturn_SendTitle' #FuncID: 33

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_OnUserRecharge' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_ModifyActivityIntegral' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GetPlayerInfo' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_GetPlayerBagInfo' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_DelItem' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_GetActList' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_OpenAct' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_LockOrUnlockUser' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_LockOrUnlockSpeak' #FuncID: 9
		@timeFuncList[9] = '_onTimeOut_GetOnlineNum' #FuncID: 10
		@timeFuncList[10] = '_onTimeOut_SendItem' #FuncID: 11
		@timeFuncList[11] = '_onTimeOut_SubMoney' #FuncID: 12
		@timeFuncList[12] = '_onTimeOut_SendVIPItem' #FuncID: 13
		@timeFuncList[13] = '_onTimeOut_SendClanItem' #FuncID: 14
		@timeFuncList[14] = '_onTimeOut_GlobalSendItem' #FuncID: 15
		@timeFuncList[15] = '_onTimeOut_SendMail' #FuncID: 16
		@timeFuncList[16] = '_onTimeOut_GlobalSendMail' #FuncID: 17
		@timeFuncList[17] = '_onTimeOut_GlobalSendNotice' #FuncID: 18
		@timeFuncList[18] = '_onTimeOut_GlobalDelNotice' #FuncID: 19
		@timeFuncList[19] = '_onTimeOut_GlobalSendSysDialog' #FuncID: 20
		@timeFuncList[20] = '_onTimeOut_OpenDiscountActivity' #FuncID: 21
		@timeFuncList[21] = '_onTimeOut_SetPlayerLevel' #FuncID: 22
		@timeFuncList[22] = '_onTimeOut_SetPlayerVIPLevel' #FuncID: 23
		@timeFuncList[23] = '_onTimeOut_TaskManager' #FuncID: 24
		@timeFuncList[24] = '_onTimeOut_GetTaskState' #FuncID: 25
		@timeFuncList[25] = '_onTimeOut_SynWeiweiPersonNum' #FuncID: 26
		@timeFuncList[26] = '_onTimeOut_CheckCDK' #FuncID: 27
		@timeFuncList[27] = '_onTimeOut_SynQQAlarm' #FuncID: 28
		@timeFuncList[28] = '_onTimeOut_ModifyChest' #FuncID: 29
		@timeFuncList[29] = '_onTimeOut_SetPool' #FuncID: 30
		@timeFuncList[30] = '_onTimeOut_GetLoginDays' #FuncID: 31
		@timeFuncList[31] = '_onTimeOut_SendQQGroupMsg' #FuncID: 32
		@timeFuncList[32] = '_onTimeOut_SendTitle' #FuncID: 33
	end

	def handleMessage(data)
		funcID = ByteUtil::readINT8(data);
		if funcID == 0 || funcID < -@retFuncList.length
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

