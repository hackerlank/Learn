#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    ShengLingProt.rb
#  Purpose:      圣陵协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ItemProtBase.rb'

#以下为类型定义

#操作结果
class EShengLingResult
	ESHENGLINGRESULTSUC = 0#操作成功
	ESHENGLINGRESULTPACKFUL = 1#背包空间不足
	ESHENGLINGRESULTPRIZETAKED = 2#奖励被领取
	ESHENGLINGRESULTFAILED = 3#战斗失败
	ESHENGLINGRESULTGOLDLACK = 4#仙石不足
	ESHENGLINGRESULTENTERLACK = 5#次数不足
	ESHENGLINGRESULTLIFELACK = 6#生命不足
	ESHENGLINGRESULTCONTROLDICELACK = 7#遥控骰子不足
	ESHENGLINGRESULTTURNDICELACK = 8#转向骰子不足
	ESHENGLINGRESULTSCORELACK = 9#积分不够
	ESHENGLINGRESULTSTEPLACK = 10#积分不够
	ESHENGLINGRESULTNOTFINISH = 11#格子未完成
	ESHENGLINGRESULTTYPEERROR = 12#格子类型不对
	ESHENGLINGRESULTERROR = 13#操作失败
end

#卡片类型
class ECardType
	ECARDTYPE_CONTROLDICE = 0#遥控骰子
	ECARDTYPE_TURNDICE = 1#转向卡片
end

#圣陵格子类型
class EGridType
	EGRIDTYPE_NONE = 0#无
	EGRIDTYPE_EMPTY = 1#空格子
	EGRIDTYPE_NORMAL = 2#普通怪物格子
	EGRIDTYPE_ELITE = 3#精英怪物格子
	EGRIDTYPE_BOSS = 4#Boss怪物格子
	EGRIDTYPE_BIG = 5#小宝箱格子
	EGRIDTYPE_MID = 6#中宝箱格子
	EGRIDTYPE_SMALL = 7#大宝箱格子
	EGRIDTYPE_BORN = 8#出生格子
	EGRIDTYPE_RANDOM = 9#随机格子
	EGRIDTYPE_MOTU = 10#三消陷阱格子
	EGRIDTYPE_PINTU = 11#拼图陷阱格子
	EGRIDTYPE_ZADAN = 12#砸蛋陷阱格子
	EGRIDTYPE_GO = 13#传送格子
	EGRIDTYPE_END = 14#最大值
end

#购买类型
class EBuyType
	EBUYTYPE_CONTROLDICE = 0#购买遥控骰子
	EBUYTYPE_TURNCARD = 1#购买转向卡片
	EBUYTYPE_LIFE = 2#购买生命
	EBUYTYPE_ENTER = 3#购买进入次数
	EBUYTYPE_STEP = 4#购买三消步数
end

#格子数据
class SGrid
	attr_accessor:byIndex #(UINT8)格子ID
	attr_accessor:byLevel #(UINT8)格子所在层
	attr_accessor:eGridType #(枚举类型：EGridType)格子类型
	attr_accessor:wNoteID #(UINT16)格子记录数据
	attr_accessor:bFinished #(bool)是否完成
	attr_accessor:bRandom #(bool)是否随机格子

	#构造函数
	def initialize
		@byIndex = 0
		@byLevel = 0
		@eGridType = 0
		@wNoteID = 0
		@bFinished = false
		@bRandom = false
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byIndex = @byIndex
		obj.byLevel = @byLevel
		obj.eGridType = @eGridType
		obj.wNoteID = @wNoteID
		obj.bFinished = @bFinished
		obj.bRandom = @bRandom
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGrid.new
		s.byIndex = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.eGridType = ByteUtil::readUINT8(data)
		s.wNoteID = ByteUtil::readUINT16(data)
		s.bFinished = ByteUtil::readBOOL(data)
		s.bRandom = ByteUtil::readBOOL(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGrid::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byIndex)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT8(data, @eGridType)
		ByteUtil::writeUINT16(data, @wNoteID)
		ByteUtil::writeBOOL(data, @bFinished)
		ByteUtil::writeBOOL(data, @bRandom)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#卡片信息
class SCard
	attr_accessor:eCardType #(枚举类型：ECardType)卡片类型
	attr_accessor:byBuy #(UINT8)玩家购买次数
	attr_accessor:byUse #(UINT8)当日使用次数
	attr_accessor:byBuyForToday #(UINT8)当日购买次数

	#构造函数
	def initialize
		@eCardType = 0
		@byBuy = 0
		@byUse = 0
		@byBuyForToday = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eCardType = @eCardType
		obj.byBuy = @byBuy
		obj.byUse = @byUse
		obj.byBuyForToday = @byBuyForToday
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SCard.new
		s.eCardType = ByteUtil::readUINT8(data)
		s.byBuy = ByteUtil::readUINT8(data)
		s.byUse = ByteUtil::readUINT8(data)
		s.byBuyForToday = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SCard::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eCardType)
		ByteUtil::writeUINT8(data, @byBuy)
		ByteUtil::writeUINT8(data, @byUse)
		ByteUtil::writeUINT8(data, @byBuyForToday)
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
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:byCurLevel #(UINT8)玩家当前所在层
	attr_accessor:byCurIndex #(UINT8)玩家当前所在层格子ID
	attr_accessor:byPreLevel #(UINT8)玩家上一次所在层
	attr_accessor:byPreIndex #(UINT8)玩家上一次所在层格子ID
	attr_accessor:byBuy #(UINT8)玩家购买生命数
	attr_accessor:byUse #(UINT8)玩家当前使用生命数
	attr_accessor:byNext #(UINT8)是否进入下一层
	attr_accessor:vecGrid #(SGrid的数组)格子数据

	#构造函数
	def initialize
		@qwRoleID = 0
		@byCurLevel = 0
		@byCurIndex = 0
		@byPreLevel = 0
		@byPreIndex = 0
		@byBuy = 0
		@byUse = 0
		@byNext = 0
		@vecGrid = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.byCurLevel = @byCurLevel
		obj.byCurIndex = @byCurIndex
		obj.byPreLevel = @byPreLevel
		obj.byPreIndex = @byPreIndex
		obj.byBuy = @byBuy
		obj.byUse = @byUse
		obj.byNext = @byNext
		obj.vecGrid = @vecGrid
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPlayerInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.byCurLevel = ByteUtil::readUINT8(data)
		s.byCurIndex = ByteUtil::readUINT8(data)
		s.byPreLevel = ByteUtil::readUINT8(data)
		s.byPreIndex = ByteUtil::readUINT8(data)
		s.byBuy = ByteUtil::readUINT8(data)
		s.byUse = ByteUtil::readUINT8(data)
		s.byNext = ByteUtil::readUINT8(data)
		s.vecGrid = SGrid::vectorFromStream(data)
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
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT8(data, @byCurLevel)
		ByteUtil::writeUINT8(data, @byCurIndex)
		ByteUtil::writeUINT8(data, @byPreLevel)
		ByteUtil::writeUINT8(data, @byPreIndex)
		ByteUtil::writeUINT8(data, @byBuy)
		ByteUtil::writeUINT8(data, @byUse)
		ByteUtil::writeUINT8(data, @byNext)
		SGrid::vectorToStream(data, @vecGrid)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家进入信息
class SShengLingInfo
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:wPassword #(UINT16)初始密码
	attr_accessor:byDir #(UINT8)玩家在棋盘中的方向（0表示反向，1表示正向）
	attr_accessor:byLevel #(UINT8)玩家当前所在层
	attr_accessor:byIndex #(UINT8)玩家当前所在层格子ID
	attr_accessor:byBuyLife #(UINT8)玩家购买生命数
	attr_accessor:byUseLife #(UINT8)玩家今日使用生命数
	attr_accessor:byStep #(UINT8)玩家在“三消”中剩余步数
	attr_accessor:byScore #(UINT16)玩家在“三消”中累计积分
	attr_accessor:byBit #(UINT8)玩家在“三消”中奖励领取状态，bit位表示从低到高
	attr_accessor:byBuyLifeToday #(UINT8)玩家今天购买生命数
	attr_accessor:byFirst #(UINT8)玩家是否第一次进入圣陵
	attr_accessor:vecGrid #(SGrid的数组)格子数据
	attr_accessor:vecCard #(SCard的数组)卡片数据
	attr_accessor:vecItem #(SItemGenInfo的数组)获得的奖励数据

	#构造函数
	def initialize
		@qwRoleID = 0
		@wPassword = 0
		@byDir = 0
		@byLevel = 0
		@byIndex = 0
		@byBuyLife = 0
		@byUseLife = 0
		@byStep = 0
		@byScore = 0
		@byBit = 0
		@byBuyLifeToday = 0
		@byFirst = 0
		@vecGrid = Array.new
		@vecCard = Array.new
		@vecItem = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wPassword = @wPassword
		obj.byDir = @byDir
		obj.byLevel = @byLevel
		obj.byIndex = @byIndex
		obj.byBuyLife = @byBuyLife
		obj.byUseLife = @byUseLife
		obj.byStep = @byStep
		obj.byScore = @byScore
		obj.byBit = @byBit
		obj.byBuyLifeToday = @byBuyLifeToday
		obj.byFirst = @byFirst
		obj.vecGrid = @vecGrid
		obj.vecCard = @vecCard
		obj.vecItem = @vecItem
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SShengLingInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wPassword = ByteUtil::readUINT16(data)
		s.byDir = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.byIndex = ByteUtil::readUINT8(data)
		s.byBuyLife = ByteUtil::readUINT8(data)
		s.byUseLife = ByteUtil::readUINT8(data)
		s.byStep = ByteUtil::readUINT8(data)
		s.byScore = ByteUtil::readUINT16(data)
		s.byBit = ByteUtil::readUINT8(data)
		s.byBuyLifeToday = ByteUtil::readUINT8(data)
		s.byFirst = ByteUtil::readUINT8(data)
		s.vecGrid = SGrid::vectorFromStream(data)
		s.vecCard = SCard::vectorFromStream(data)
		s.vecItem = SItemGenInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SShengLingInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wPassword)
		ByteUtil::writeUINT8(data, @byDir)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT8(data, @byIndex)
		ByteUtil::writeUINT8(data, @byBuyLife)
		ByteUtil::writeUINT8(data, @byUseLife)
		ByteUtil::writeUINT8(data, @byStep)
		ByteUtil::writeUINT16(data, @byScore)
		ByteUtil::writeUINT8(data, @byBit)
		ByteUtil::writeUINT8(data, @byBuyLifeToday)
		ByteUtil::writeUINT8(data, @byFirst)
		SGrid::vectorToStream(data, @vecGrid)
		SCard::vectorToStream(data, @vecCard)
		SItemGenInfo::vectorToStream(data, @vecItem)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#数据库信息
class SShengLingInfo2DB
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:byLevel #(UINT8)玩家所在层
	attr_accessor:byIndex #(UINT8)格子ID
	attr_accessor:byType #(UINT8)格子类型
	attr_accessor:wNoteID #(UINT16)格子中记录ID
	attr_accessor:byRandom #(UINT8)是否随机格子
	attr_accessor:byFinish #(UINT8)是否完成

	#构造函数
	def initialize
		@qwRoleID = 0
		@byLevel = 0
		@byIndex = 0
		@byType = 0
		@wNoteID = 0
		@byRandom = 0
		@byFinish = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.byLevel = @byLevel
		obj.byIndex = @byIndex
		obj.byType = @byType
		obj.wNoteID = @wNoteID
		obj.byRandom = @byRandom
		obj.byFinish = @byFinish
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SShengLingInfo2DB.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.byIndex = ByteUtil::readUINT8(data)
		s.byType = ByteUtil::readUINT8(data)
		s.wNoteID = ByteUtil::readUINT16(data)
		s.byRandom = ByteUtil::readUINT8(data)
		s.byFinish = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SShengLingInfo2DB::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT8(data, @byIndex)
		ByteUtil::writeUINT8(data, @byType)
		ByteUtil::writeUINT16(data, @wNoteID)
		ByteUtil::writeUINT8(data, @byRandom)
		ByteUtil::writeUINT8(data, @byFinish)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#数据库奖励信息
class SShengLingPrize2DB
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:wItemID #(UINT16)物品
	attr_accessor:wNum #(UINT16)数量

	#构造函数
	def initialize
		@qwRoleID = 0
		@wItemID = 0
		@wNum = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wItemID = @wItemID
		obj.wNum = @wNum
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SShengLingPrize2DB.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wItemID = ByteUtil::readUINT16(data)
		s.wNum = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SShengLingPrize2DB::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeUINT16(data, @wNum)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[OnOpen:玩家打开活动面板]的返回的参数组成的结构体
class SRetParam_OnOpen
	attr_accessor:byUseEnter#(UINT8)玩家当日使用进入次数
	attr_accessor:byBuyEnter#(UINT8)玩家购买进入次数
	attr_accessor:byBuyEnterToday#(UINT8)玩家今天购买进入次数
	attr_accessor:bContinue#(bool)是否继续

	#构造函数
	def initialize
		@byUseEnter = 0
		@byBuyEnter = 0
		@byBuyEnterToday = 0
		@bContinue = false
	end
end

#函数[OnEnter:玩家进入圣陵]的返回的参数组成的结构体
class SRetParam_OnEnter
	attr_accessor:byBuyEnterToday#(UINT8)玩家今天购买进入次数
	attr_accessor:sInfo#(类类型：SShengLingInfo)玩家数据
	attr_accessor:eResult#(枚举类型：EShengLingResult)操作结果

	#构造函数
	def initialize
		@byBuyEnterToday = 0
		@sInfo = SShengLingInfo.new
		@eResult = 0
	end
end

#函数[DrawDice:玩家摇骰子]的返回的参数组成的结构体
class SRetParam_DrawDice
	attr_accessor:byIndex#(UINT8)骰子数
	attr_accessor:qwBattleID#(UINT64)战报ID
	attr_accessor:sInfo#(类类型：SPlayerInfo)玩家数据
	attr_accessor:eResult#(枚举类型：EShengLingResult)操作结果

	#构造函数
	def initialize
		@byIndex = 0
		@qwBattleID = 0
		@sInfo = SPlayerInfo.new
		@eResult = 0
	end
end

#函数[UseCard:使用卡片]的返回的参数组成的结构体
class SRetParam_UseCard
	attr_accessor:sCard#(类类型：SCard)卡片信息
	attr_accessor:sInfo#(类类型：SPlayerInfo)玩家数据
	attr_accessor:qwBattleID#(UINT64)战报ID
	attr_accessor:eResult#(枚举类型：EShengLingResult)操作结果

	#构造函数
	def initialize
		@sCard = SCard.new
		@sInfo = SPlayerInfo.new
		@qwBattleID = 0
		@eResult = 0
	end
end

#函数[Buy:购买]的返回的参数组成的结构体
class SRetParam_Buy
	attr_accessor:eBuyTypeRet#(枚举类型：EBuyType)返回购买类型
	attr_accessor:byBuy#(UINT8)返回购买次数
	attr_accessor:byBuyToday#(UINT8)返回今日购买次数
	attr_accessor:byUse#(UINT8)返回当日使用次数
	attr_accessor:eResult#(枚举类型：EShengLingResult)操作结果

	#构造函数
	def initialize
		@eBuyTypeRet = 0
		@byBuy = 0
		@byBuyToday = 0
		@byUse = 0
		@eResult = 0
	end
end

#函数[TakePrize:玩家领奖]的返回的参数组成的结构体
class SRetParam_TakePrize
	attr_accessor:byBit#(UINT8)奖励状态(其他忽略此参数）
	attr_accessor:eResult#(枚举类型：EShengLingResult)操作结果

	#构造函数
	def initialize
		@byBit = 0
		@eResult = 0
	end
end

#函数[AddScore:三消中积分累计]的返回的参数组成的结构体
class SRetParam_AddScore
	attr_accessor:wNextPwd#(UINT16)下一次密码
	attr_accessor:byTotalStep#(UINT8)剩余步数
	attr_accessor:wTotalScore#(UINT16)总积分
	attr_accessor:eResult#(枚举类型：EShengLingResult)操作结果

	#构造函数
	def initialize
		@wNextPwd = 0
		@byTotalStep = 0
		@wTotalScore = 0
		@eResult = 0
	end
end

#函数[FinishTrapGrid:玩家完成或者放弃小游戏]的返回的参数组成的结构体
class SRetParam_FinishTrapGrid
	attr_accessor:eResult#(枚举类型：EShengLingResult)操作结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：圣陵协议
class ShengLingProtBase < ProtocolBase
	#以下为发送函数
	#发送：玩家打开活动面板
	def send_OnOpen(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家进入圣陵
	def send_OnEnter(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家摇骰子
	def send_DrawDice(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：使用卡片
	def send_UseCard(
		eCardType,  #(枚举类型：ECardType)卡片类型
		byIndex #(UINT8)骰子数(转向时byIndex=0)
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eCardType)
		ByteUtil::writeUINT8(data, byIndex)
		return @svrHandler.sendPacket(data)
	end

	#发送：购买
	def send_Buy(
		eBuyType,  #(枚举类型：EBuyType)购买类型
		byNum #(UINT8)购买次数
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eBuyType)
		ByteUtil::writeUINT8(data, byNum)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家领奖
	def send_TakePrize(
		eGridType,  #(枚举类型：EGridType)格子类型(小游戏）
		byIndex #(UINT8)三消中第几个奖励或者拼图是否一键完成(其他忽略此参数）
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eGridType)
		ByteUtil::writeUINT8(data, byIndex)
		return @svrHandler.sendPacket(data)
	end

	#发送：三消中积分累计
	def send_AddScore(
		wScore,  #(UINT16)积分
		byStep,  #(UINT8)减少步数
		wPassword #(UINT16)密码
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wScore)
		ByteUtil::writeUINT8(data, byStep)
		ByteUtil::writeUINT16(data, wPassword)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家完成或者放弃小游戏
	def send_FinishTrapGrid(
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家离开圣陵
	def send_Leave(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：玩家通关
	def onRecv_Clearance(
	)
		raise NotImplementedError
	end
	#接收：玩家数据推送（0点)
	def onRecv_SyncData(
		sInfo #(类类型：SShengLingInfo)玩家数据
	)
		raise NotImplementedError
	end
	#接收：播放特效
	def onRecv_PlayEffect(
	)
		raise NotImplementedError
	end
	#接收：获得奖励道具
	def onRecv_GetPrizeInfo(
		vecItem #(SItemGenInfo的数组)玩家物品
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：玩家打开活动面板
	def onReturn_OnOpen(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_OnOpen)返回的参数
	)
	end

	#返回：玩家进入圣陵
	def onReturn_OnEnter(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_OnEnter)返回的参数
	)
	end

	#返回：玩家摇骰子
	def onReturn_DrawDice(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_DrawDice)返回的参数
	)
	end

	#返回：使用卡片
	def onReturn_UseCard(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UseCard)返回的参数
	)
	end

	#返回：购买
	def onReturn_Buy(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Buy)返回的参数
	)
	end

	#返回：玩家领奖
	def onReturn_TakePrize(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakePrize)返回的参数
	)
	end

	#返回：三消中积分累计
	def onReturn_AddScore(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_AddScore)返回的参数
	)
	end

	#返回：玩家完成或者放弃小游戏
	def onReturn_FinishTrapGrid(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FinishTrapGrid)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：玩家通关
	def _doRecv_Clearance(data)
		return onRecv_Clearance()
	end

	#接收处理：玩家数据推送（0点)
	def _doRecv_SyncData(data)
		sInfo = SShengLingInfo::fromStream(data)
		return onRecv_SyncData(sInfo)
	end

	#接收处理：播放特效
	def _doRecv_PlayEffect(data)
		return onRecv_PlayEffect()
	end

	#接收处理：获得奖励道具
	def _doRecv_GetPrizeInfo(data)
		vecItem = SItemGenInfo::vectorFromStream(data)
		return onRecv_GetPrizeInfo(vecItem)
	end

#以下为返回处理函数
	#返回处理：玩家打开活动面板
	def _doReturn_OnOpen(data)
		retParam = SRetParam_OnOpen.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byUseEnter = ByteUtil::readUINT8(data) #(UINT8)玩家当日使用进入次数
		byBuyEnter = ByteUtil::readUINT8(data) #(UINT8)玩家购买进入次数
		byBuyEnterToday = ByteUtil::readUINT8(data) #(UINT8)玩家今天购买进入次数
		bContinue = ByteUtil::readBOOL(data) #(bool)是否继续
		retParam.byUseEnter = byUseEnter
		retParam.byBuyEnter = byBuyEnter
		retParam.byBuyEnterToday = byBuyEnterToday
		retParam.bContinue = bContinue
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_OnOpen(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：玩家打开活动面板
	def _onTimeOut_OnOpen(sessionID)
		retParam = SRetParam_OnOpen.new;
		onReturn_OnOpen(2, retParam)
	end

	#返回处理：玩家进入圣陵
	def _doReturn_OnEnter(data)
		retParam = SRetParam_OnEnter.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byBuyEnterToday = ByteUtil::readUINT8(data) #(UINT8)玩家今天购买进入次数
		sInfo = SShengLingInfo::fromStream(data) #(类类型：SShengLingInfo)玩家数据
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShengLingResult)操作结果
		retParam.byBuyEnterToday = byBuyEnterToday
		retParam.sInfo = sInfo
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_OnEnter(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：玩家进入圣陵
	def _onTimeOut_OnEnter(sessionID)
		retParam = SRetParam_OnEnter.new;
		onReturn_OnEnter(2, retParam)
	end

	#返回处理：玩家摇骰子
	def _doReturn_DrawDice(data)
		retParam = SRetParam_DrawDice.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byIndex = ByteUtil::readUINT8(data) #(UINT8)骰子数
		qwBattleID = ByteUtil::readUINT64(data) #(UINT64)战报ID
		sInfo = SPlayerInfo::fromStream(data) #(类类型：SPlayerInfo)玩家数据
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShengLingResult)操作结果
		retParam.byIndex = byIndex
		retParam.qwBattleID = qwBattleID
		retParam.sInfo = sInfo
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_DrawDice(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：玩家摇骰子
	def _onTimeOut_DrawDice(sessionID)
		retParam = SRetParam_DrawDice.new;
		onReturn_DrawDice(2, retParam)
	end

	#返回处理：使用卡片
	def _doReturn_UseCard(data)
		retParam = SRetParam_UseCard.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		sCard = SCard::fromStream(data) #(类类型：SCard)卡片信息
		sInfo = SPlayerInfo::fromStream(data) #(类类型：SPlayerInfo)玩家数据
		qwBattleID = ByteUtil::readUINT64(data) #(UINT64)战报ID
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShengLingResult)操作结果
		retParam.sCard = sCard
		retParam.sInfo = sInfo
		retParam.qwBattleID = qwBattleID
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UseCard(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：使用卡片
	def _onTimeOut_UseCard(sessionID)
		retParam = SRetParam_UseCard.new;
		onReturn_UseCard(2, retParam)
	end

	#返回处理：购买
	def _doReturn_Buy(data)
		retParam = SRetParam_Buy.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eBuyTypeRet = ByteUtil::readUINT8(data) #(枚举类型：EBuyType)返回购买类型
		byBuy = ByteUtil::readUINT8(data) #(UINT8)返回购买次数
		byBuyToday = ByteUtil::readUINT8(data) #(UINT8)返回今日购买次数
		byUse = ByteUtil::readUINT8(data) #(UINT8)返回当日使用次数
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShengLingResult)操作结果
		retParam.eBuyTypeRet = eBuyTypeRet
		retParam.byBuy = byBuy
		retParam.byBuyToday = byBuyToday
		retParam.byUse = byUse
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_Buy(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：购买
	def _onTimeOut_Buy(sessionID)
		retParam = SRetParam_Buy.new;
		onReturn_Buy(2, retParam)
	end

	#返回处理：玩家领奖
	def _doReturn_TakePrize(data)
		retParam = SRetParam_TakePrize.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byBit = ByteUtil::readUINT8(data) #(UINT8)奖励状态(其他忽略此参数）
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShengLingResult)操作结果
		retParam.byBit = byBit
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakePrize(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：玩家领奖
	def _onTimeOut_TakePrize(sessionID)
		retParam = SRetParam_TakePrize.new;
		onReturn_TakePrize(2, retParam)
	end

	#返回处理：三消中积分累计
	def _doReturn_AddScore(data)
		retParam = SRetParam_AddScore.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		wNextPwd = ByteUtil::readUINT16(data) #(UINT16)下一次密码
		byTotalStep = ByteUtil::readUINT8(data) #(UINT8)剩余步数
		wTotalScore = ByteUtil::readUINT16(data) #(UINT16)总积分
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShengLingResult)操作结果
		retParam.wNextPwd = wNextPwd
		retParam.byTotalStep = byTotalStep
		retParam.wTotalScore = wTotalScore
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_AddScore(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：三消中积分累计
	def _onTimeOut_AddScore(sessionID)
		retParam = SRetParam_AddScore.new;
		onReturn_AddScore(2, retParam)
	end

	#返回处理：玩家完成或者放弃小游戏
	def _doReturn_FinishTrapGrid(data)
		retParam = SRetParam_FinishTrapGrid.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShengLingResult)操作结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FinishTrapGrid(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：玩家完成或者放弃小游戏
	def _onTimeOut_FinishTrapGrid(sessionID)
		retParam = SRetParam_FinishTrapGrid.new;
		onReturn_FinishTrapGrid(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 98;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_Clearance' #FuncID: 1
		@recvFuncList[1] = '_doRecv_SyncData' #FuncID: 2
		@recvFuncList[2] = '_doRecv_PlayEffect' #FuncID: 3
		@recvFuncList[3] = '_doRecv_GetPrizeInfo' #FuncID: 4

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_OnOpen' #FuncID: 1
		@retFuncList[1] = '_doReturn_OnEnter' #FuncID: 2
		@retFuncList[2] = '_doReturn_DrawDice' #FuncID: 3
		@retFuncList[3] = '_doReturn_UseCard' #FuncID: 4
		@retFuncList[4] = '_doReturn_Buy' #FuncID: 5
		@retFuncList[5] = '_doReturn_TakePrize' #FuncID: 6
		@retFuncList[6] = '_doReturn_AddScore' #FuncID: 7
		@retFuncList[7] = '_doReturn_FinishTrapGrid' #FuncID: 8

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_OnOpen' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_OnEnter' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_DrawDice' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_UseCard' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_Buy' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_TakePrize' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_AddScore' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_FinishTrapGrid' #FuncID: 8
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

