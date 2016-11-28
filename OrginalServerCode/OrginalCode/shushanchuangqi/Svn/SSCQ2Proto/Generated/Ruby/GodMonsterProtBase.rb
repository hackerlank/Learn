#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    GodMonsterProt.rb
#  Purpose:      天元神兽协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#操作结果
class EMonsterResult
	EMONSTERRESULT_SUC = 0#操作成功
	EMONSTERRESULT_FUL = 1#背包满
	EMONSTERRESULT_GET = 2#奖励已经领取
	EMONSTERRESULT_NOT = 3#无此奖励
	EMONSTERRESULT_LACK = 4#仙石不足
	EMONSTERRESULT_LEVEL = 5#等级不够
	EMONSTERRESULT_DEVOTE = 6#贡献度不够
	EMONSTERRESULT_GUILD = 7#不在帮派
	EMONSTERRESULT_NUM = 8#数量不足
	EMONSTERRESULT_ERR = 9#操作失败
end

#神兽阶段
class EMonsterPeroid
	EMONSTERPEROID_NONE = 0#无
	EMONSTERPEROID_1 = 1#神兽元胎
	EMONSTERPEROID_2 = 2#神兽幼年期
	EMONSTERPEROID_3 = 3#神兽成年期
	EMONSTERPEROID_4 = 4#神兽青年期
	EMONSTERPEROID_5 = 5#亚圣兽期
	EMONSTERPEROID_6 = 6#天元神兽
	EMONSTERPEROID_END = 7#最大值
end

#奖励类型
class EMonsterPrizeType
	EMONSTERPRIZE_BEGIN = 0#礼包Begin
	EMONSTERPRIZE_1 = 1#每日成长礼包
	EMONSTERPRIZE_2 = 2#每日初级礼包
	EMONSTERPRIZE_3 = 3#每日中级礼包
	EMONSTERPRIZE_4 = 4#每日高级礼包
	EMONSTERPRIZE_5 = 5#每日终极礼包
	EMONSTERPRIZE_END = 6#End
end

#排行榜
class EMonsterRank
	EMONSTERRANK_NONE = 0#无
	EMONSTERRANK_1 = 1#个人榜
	EMONSTERRANK_2 = 2#帮派榜
	EMONSTERRANK_END = 3#最大值
end

#排行榜数据
class SMonsterRankInfo
	attr_accessor:dwRank #(UINT32)排名
	attr_accessor:strName #(string)名字
	attr_accessor:dwScore #(UINT32)积分

	#构造函数
	def initialize
		@dwRank = 0
		@strName = ''
		@dwScore = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwRank = @dwRank
		obj.strName = @strName
		obj.dwScore = @dwScore
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMonsterRankInfo.new
		s.dwRank = ByteUtil::readUINT32(data)
		s.strName = ByteUtil::readSTRING(data)
		s.dwScore = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMonsterRankInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwRank)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT32(data, @dwScore)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#排行榜
class SMonsterRank
	attr_accessor:eRank #(枚举类型：EMonsterRank)排名
	attr_accessor:vecRankInfo #(SMonsterRankInfo的数组)数据

	#构造函数
	def initialize
		@eRank = 0
		@vecRankInfo = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eRank = @eRank
		obj.vecRankInfo = @vecRankInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMonsterRank.new
		s.eRank = ByteUtil::readUINT8(data)
		s.vecRankInfo = SMonsterRankInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMonsterRank::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eRank)
		SMonsterRankInfo::vectorToStream(data, @vecRankInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#排行榜
class SMonsterPrize
	attr_accessor:eType #(枚举类型：EMonsterPrizeType)奖励类型
	attr_accessor:byType #(UINT8)0表示条件未达到，1表示可以领取，2表示已经领取

	#构造函数
	def initialize
		@eType = 0
		@byType = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eType = @eType
		obj.byType = @byType
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMonsterPrize.new
		s.eType = ByteUtil::readUINT8(data)
		s.byType = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMonsterPrize::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eType)
		ByteUtil::writeUINT8(data, @byType)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮派成员贡献
class SGuildUserDevote
	attr_accessor:qwRoleID #(UINT64)ID
	attr_accessor:strName #(string)名字
	attr_accessor:strLevel #(string)职务
	attr_accessor:dwScore #(UINT32)积分

	#构造函数
	def initialize
		@qwRoleID = 0
		@strName = ''
		@strLevel = ''
		@dwScore = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.strName = @strName
		obj.strLevel = @strLevel
		obj.dwScore = @dwScore
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildUserDevote.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.strLevel = ByteUtil::readSTRING(data)
		s.dwScore = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildUserDevote::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeSTRING(data, @strLevel)
		ByteUtil::writeUINT32(data, @dwScore)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#限购礼包
class SLimitPrize
	attr_accessor:wPrizeID #(UINT16)礼品ID
	attr_accessor:wCurNum #(UINT16)已经购买数量
	attr_accessor:wMaxNum #(UINT16)最大值

	#构造函数
	def initialize
		@wPrizeID = 0
		@wCurNum = 0
		@wMaxNum = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wPrizeID = @wPrizeID
		obj.wCurNum = @wCurNum
		obj.wMaxNum = @wMaxNum
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SLimitPrize.new
		s.wPrizeID = ByteUtil::readUINT16(data)
		s.wCurNum = ByteUtil::readUINT16(data)
		s.wMaxNum = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SLimitPrize::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wPrizeID)
		ByteUtil::writeUINT16(data, @wCurNum)
		ByteUtil::writeUINT16(data, @wMaxNum)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#发送给客户端的数据
class SyncInfoToClient
	attr_accessor:ePeroid #(枚举类型：EMonsterPeroid)神兽阶段
	attr_accessor:dwPersonScore #(UINT32)个人总积分
	attr_accessor:dwGuildScore #(UINT32)帮派总积分
	attr_accessor:dwPersonDevote #(UINT32)个人贡献值
	attr_accessor:dwPersonRank #(UINT32)个人总排名
	attr_accessor:dwGuildRank #(UINT32)帮派总排名
	attr_accessor:dwFruit #(UINT32)朱果数量
	attr_accessor:vecPrize #(SMonsterPrize的数组)奖励数据
	attr_accessor:vecRank #(SMonsterRank的数组)排行榜数据
	attr_accessor:vecUser #(SGuildUserDevote的数组)成员贡献数据
	attr_accessor:vecLimitPrize #(SLimitPrize的数组)玩家限购礼包数据

	#构造函数
	def initialize
		@ePeroid = 0
		@dwPersonScore = 0
		@dwGuildScore = 0
		@dwPersonDevote = 0
		@dwPersonRank = 0
		@dwGuildRank = 0
		@dwFruit = 0
		@vecPrize = Array.new
		@vecRank = Array.new
		@vecUser = Array.new
		@vecLimitPrize = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.ePeroid = @ePeroid
		obj.dwPersonScore = @dwPersonScore
		obj.dwGuildScore = @dwGuildScore
		obj.dwPersonDevote = @dwPersonDevote
		obj.dwPersonRank = @dwPersonRank
		obj.dwGuildRank = @dwGuildRank
		obj.dwFruit = @dwFruit
		obj.vecPrize = @vecPrize
		obj.vecRank = @vecRank
		obj.vecUser = @vecUser
		obj.vecLimitPrize = @vecLimitPrize
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SyncInfoToClient.new
		s.ePeroid = ByteUtil::readUINT8(data)
		s.dwPersonScore = ByteUtil::readUINT32(data)
		s.dwGuildScore = ByteUtil::readUINT32(data)
		s.dwPersonDevote = ByteUtil::readUINT32(data)
		s.dwPersonRank = ByteUtil::readUINT32(data)
		s.dwGuildRank = ByteUtil::readUINT32(data)
		s.dwFruit = ByteUtil::readUINT32(data)
		s.vecPrize = SMonsterPrize::vectorFromStream(data)
		s.vecRank = SMonsterRank::vectorFromStream(data)
		s.vecUser = SGuildUserDevote::vectorFromStream(data)
		s.vecLimitPrize = SLimitPrize::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SyncInfoToClient::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @ePeroid)
		ByteUtil::writeUINT32(data, @dwPersonScore)
		ByteUtil::writeUINT32(data, @dwGuildScore)
		ByteUtil::writeUINT32(data, @dwPersonDevote)
		ByteUtil::writeUINT32(data, @dwPersonRank)
		ByteUtil::writeUINT32(data, @dwGuildRank)
		ByteUtil::writeUINT32(data, @dwFruit)
		SMonsterPrize::vectorToStream(data, @vecPrize)
		SMonsterRank::vectorToStream(data, @vecRank)
		SGuildUserDevote::vectorToStream(data, @vecUser)
		SLimitPrize::vectorToStream(data, @vecLimitPrize)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#DB Operator
class SGuildUser2DB
	attr_accessor:qwRoleID #(UINT64)名字
	attr_accessor:qwGuildID #(UINT64)职务
	attr_accessor:dwFruit #(UINT32)朱果数量
	attr_accessor:dwScore #(UINT32)积分
	attr_accessor:dwTotalScore #(UINT32)总积分

	#构造函数
	def initialize
		@qwRoleID = 0
		@qwGuildID = 0
		@dwFruit = 0
		@dwScore = 0
		@dwTotalScore = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.qwGuildID = @qwGuildID
		obj.dwFruit = @dwFruit
		obj.dwScore = @dwScore
		obj.dwTotalScore = @dwTotalScore
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildUser2DB.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.qwGuildID = ByteUtil::readUINT64(data)
		s.dwFruit = ByteUtil::readUINT32(data)
		s.dwScore = ByteUtil::readUINT32(data)
		s.dwTotalScore = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildUser2DB::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT64(data, @qwGuildID)
		ByteUtil::writeUINT32(data, @dwFruit)
		ByteUtil::writeUINT32(data, @dwScore)
		ByteUtil::writeUINT32(data, @dwTotalScore)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#DB Operator
class SLimitPrize2DB
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:wPrizeID #(UINT16)礼品ID
	attr_accessor:wNum #(UINT16)购买数量

	#构造函数
	def initialize
		@qwRoleID = 0
		@wPrizeID = 0
		@wNum = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wPrizeID = @wPrizeID
		obj.wNum = @wNum
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SLimitPrize2DB.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wPrizeID = ByteUtil::readUINT16(data)
		s.wNum = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SLimitPrize2DB::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wPrizeID)
		ByteUtil::writeUINT16(data, @wNum)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[OnEnter:打开活动面板]的返回的参数组成的结构体
class SRetParam_OnEnter
	attr_accessor:sInfo#(类类型：SyncInfoToClient)客户端数据

	#构造函数
	def initialize
		@sInfo = SyncInfoToClient.new
	end
end

#函数[OnFeed:喂养]的返回的参数组成的结构体
class SRetParam_OnFeed
	attr_accessor:eResult#(枚举类型：EMonsterResult)操作结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[TakePrize:领奖]的返回的参数组成的结构体
class SRetParam_TakePrize
	attr_accessor:eResult#(枚举类型：EMonsterResult)操作结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[BuyPkg:购买限购礼包]的返回的参数组成的结构体
class SRetParam_BuyPkg
	attr_accessor:eResult#(枚举类型：EMonsterResult)操作结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：天元神兽协议
class GodMonsterProtBase < ProtocolBase
	#以下为发送函数
	#发送：打开活动面板
	def send_OnEnter(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：喂养
	def send_OnFeed(
		byType #(UINT8)0: 表示喂养一次，1: 表示一键喂养
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byType)
		return @svrHandler.sendPacket(data)
	end

	#发送：领奖
	def send_TakePrize(
		ePrizeType #(枚举类型：EMonsterPrizeType)奖励类型
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, ePrizeType)
		return @svrHandler.sendPacket(data)
	end

	#发送：购买限购礼包
	def send_BuyPkg(
		wIndex,  #(UINT16)礼包ID
		byCount #(UINT8)礼包数量
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wIndex)
		ByteUtil::writeUINT8(data, byCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：表扬
	def send_OnPraise(
		qwRoleID #(UINT64)玩家
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：督促
	def send_OnUrge(
		qwRoleID #(UINT64)玩家
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：同步数据
	def onRecv_SyncClientInfo(
		sInfo #(类类型：SyncInfoToClient)客户端数据
	)
		raise NotImplementedError
	end
	#接收：活动开始
	def onRecv_OnBegin(
		dwTime #(UINT32)时间
	)
		raise NotImplementedError
	end
	#接收：活动结束
	def onRecv_OnEnd(
		dwTime #(UINT32)时间
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：打开活动面板
	def onReturn_OnEnter(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_OnEnter)返回的参数
	)
	end

	#返回：喂养
	def onReturn_OnFeed(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_OnFeed)返回的参数
	)
	end

	#返回：领奖
	def onReturn_TakePrize(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakePrize)返回的参数
	)
	end

	#返回：购买限购礼包
	def onReturn_BuyPkg(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuyPkg)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：同步数据
	def _doRecv_SyncClientInfo(data)
		sInfo = SyncInfoToClient::fromStream(data)
		return onRecv_SyncClientInfo(sInfo)
	end

	#接收处理：活动开始
	def _doRecv_OnBegin(data)
		dwTime = ByteUtil::readUINT32(data)
		return onRecv_OnBegin(dwTime)
	end

	#接收处理：活动结束
	def _doRecv_OnEnd(data)
		dwTime = ByteUtil::readUINT32(data)
		return onRecv_OnEnd(dwTime)
	end

#以下为返回处理函数
	#返回处理：打开活动面板
	def _doReturn_OnEnter(data)
		retParam = SRetParam_OnEnter.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		sInfo = SyncInfoToClient::fromStream(data) #(类类型：SyncInfoToClient)客户端数据
		retParam.sInfo = sInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_OnEnter(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：打开活动面板
	def _onTimeOut_OnEnter(sessionID)
		retParam = SRetParam_OnEnter.new;
		onReturn_OnEnter(2, retParam)
	end

	#返回处理：喂养
	def _doReturn_OnFeed(data)
		retParam = SRetParam_OnFeed.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EMonsterResult)操作结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_OnFeed(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：喂养
	def _onTimeOut_OnFeed(sessionID)
		retParam = SRetParam_OnFeed.new;
		onReturn_OnFeed(2, retParam)
	end

	#返回处理：领奖
	def _doReturn_TakePrize(data)
		retParam = SRetParam_TakePrize.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EMonsterResult)操作结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakePrize(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：领奖
	def _onTimeOut_TakePrize(sessionID)
		retParam = SRetParam_TakePrize.new;
		onReturn_TakePrize(2, retParam)
	end

	#返回处理：购买限购礼包
	def _doReturn_BuyPkg(data)
		retParam = SRetParam_BuyPkg.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EMonsterResult)操作结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuyPkg(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：购买限购礼包
	def _onTimeOut_BuyPkg(sessionID)
		retParam = SRetParam_BuyPkg.new;
		onReturn_BuyPkg(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 96;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_SyncClientInfo' #FuncID: 1
		@recvFuncList[1] = '_doRecv_OnBegin' #FuncID: 2
		@recvFuncList[2] = '_doRecv_OnEnd' #FuncID: 3

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_OnEnter' #FuncID: 1
		@retFuncList[1] = '_doReturn_OnFeed' #FuncID: 2
		@retFuncList[2] = '_doReturn_TakePrize' #FuncID: 3
		@retFuncList[3] = '_doReturn_BuyPkg' #FuncID: 4

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_OnEnter' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_OnFeed' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_TakePrize' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_BuyPkg' #FuncID: 4
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

