#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    MallProt.rb
#  Purpose:      商城相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#商城类型
class EMallType
	EMALLGOLD = 1#奇珍商城
	EMALLFASHION = 2#时装商城
	EMALLVIP = 3#VIP商城
	EMALLPRESTIGE = 4#声望商城
	EMALLHONOR = 5#荣誉商城
	EMALLCOUPON = 6#礼券商城
	EMALLSILVER = 7#银币商城
	EMALLLIMIT = 8#限购商城
	EMALLGEM = 9#宝石商城
	EMALLEND = 10#商城
end

#商城操作结果
class EMallResult
	EMALLRESULTSUCC = 0#成功
	EMALLRESULTFAILED = 1#失败
	EMALLRESULTSTORE = 2#背包空间不足
	EMALLRESULTSTOREADD = 3#物品加入背包出错
	EMALLRESULTMONEY = 4#购买时相应货币不足
	EMALLRESULTNOITEM = 5#所购买的物品已下架
	EMALLRESULTFASHIONERR = 6#所购买的时装不能加入背包
	EMALLRESULTFASHIONALREADY = 7#所购买的时装已存在
	EMALLPRESENTSUCC = 8#赠送成功
	EMALLPRESENTNOTARGET = 9#赠送的玩家不存在
	EMALLRESULTDISCOUNTOVERTIME = 10#限购活动已过期
	EMALLRESULTDISCOUNTFULL = 11#超出限购数量限制
	EMALLRESULTDISCOUNTRECHARGEERR = 12#未达到限购充值仙石数量
	EMALLRESULTDISCOUNTCONSUMEERR = 13#未达到限购消耗仙石数量
	EMALLRESULTITEMCOUNT = 14#没有购买次数
end

#使用钱币标志
class EUseMoneyMark
	EUSEBINDMONEY = 0#使用绑定钱币
	EUSENOBINDMONEY = 1#使用非绑定钱币
end

#限购限制类型
class EDiscountLimitType
	EDISCOUNTLIMITTYPENO = 0#无条件
	EDISCOUNTLIMITTYPERECHARGE = 1#充值限购
	EDISCOUNTLIMITTYPECONSUME = 2#消费限购
	EDISCOUNTLIMITTYPEEND = 3#限购类型
end

#商城信息
class SMallInfo
	attr_accessor:dwInstID #(UINT32)商品编号
	attr_accessor:strName #(string)商品名称
	attr_accessor:wItemID #(UINT16)物品ID
	attr_accessor:dwItemCount #(UINT32)物品数量
	attr_accessor:eMoneyType #(枚类型：ProtoCommon::EMoneyType)所需货币类型
	attr_accessor:dwPrice #(UINT32)价格
	attr_accessor:byVIP #(UINT8)VIP等级限制
	attr_accessor:wIcon #(UINT16)图标
	attr_accessor:dwDayCntLimit #(UINT32)限购数量

	#构造函数
	def initialize
		@dwInstID = 0
		@strName = ''
		@wItemID = 0
		@dwItemCount = 0
		@eMoneyType = 0
		@dwPrice = 0
		@byVIP = 0
		@wIcon = 0
		@dwDayCntLimit = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwInstID = @dwInstID
		obj.strName = @strName
		obj.wItemID = @wItemID
		obj.dwItemCount = @dwItemCount
		obj.eMoneyType = @eMoneyType
		obj.dwPrice = @dwPrice
		obj.byVIP = @byVIP
		obj.wIcon = @wIcon
		obj.dwDayCntLimit = @dwDayCntLimit
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMallInfo.new
		s.dwInstID = ByteUtil::readUINT32(data)
		s.strName = ByteUtil::readSTRING(data)
		s.wItemID = ByteUtil::readUINT16(data)
		s.dwItemCount = ByteUtil::readUINT32(data)
		s.eMoneyType = ByteUtil::readUINT8(data)
		s.dwPrice = ByteUtil::readUINT32(data)
		s.byVIP = ByteUtil::readUINT8(data)
		s.wIcon = ByteUtil::readUINT16(data)
		s.dwDayCntLimit = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMallInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwInstID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeUINT32(data, @dwItemCount)
		ByteUtil::writeUINT8(data, @eMoneyType)
		ByteUtil::writeUINT32(data, @dwPrice)
		ByteUtil::writeUINT8(data, @byVIP)
		ByteUtil::writeUINT16(data, @wIcon)
		ByteUtil::writeUINT32(data, @dwDayCntLimit)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#商城折扣物品
class SDiscountItem
	attr_accessor:wItemID #(UINT16)物品ID
	attr_accessor:wOriginalPrice #(UINT16)原价
	attr_accessor:wDiscountPrice #(UINT16)折扣价

	#构造函数
	def initialize
		@wItemID = 0
		@wOriginalPrice = 0
		@wDiscountPrice = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wItemID = @wItemID
		obj.wOriginalPrice = @wOriginalPrice
		obj.wDiscountPrice = @wDiscountPrice
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDiscountItem.new
		s.wItemID = ByteUtil::readUINT16(data)
		s.wOriginalPrice = ByteUtil::readUINT16(data)
		s.wDiscountPrice = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDiscountItem::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeUINT16(data, @wOriginalPrice)
		ByteUtil::writeUINT16(data, @wDiscountPrice)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#商城折扣物品信息
class SDiscount
	attr_accessor:byPos #(UINT8)限购位置(0,1,2表示)
	attr_accessor:qwMarkID #(UINT64)栏位版本ID
	attr_accessor:vecDisItems #(SDiscountItem的数组)限购道具
	attr_accessor:byLimitType #(UINT8)类型限制(0无条件、1充值限购、2消费限购)
	attr_accessor:dwLimitValue #(UINT32)达到的仙石数量限制(0无条件、1充值限购、2消费限购)
	attr_accessor:wLimitCount #(UINT16)购买道具个数限制
	attr_accessor:dwBeginTime #(UINT32)限购开始时间
	attr_accessor:dwEndTime #(UINT32)限购结束时间

	#构造函数
	def initialize
		@byPos = 0
		@qwMarkID = 0
		@vecDisItems = Array.new
		@byLimitType = 0
		@dwLimitValue = 0
		@wLimitCount = 0
		@dwBeginTime = 0
		@dwEndTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byPos = @byPos
		obj.qwMarkID = @qwMarkID
		obj.vecDisItems = @vecDisItems
		obj.byLimitType = @byLimitType
		obj.dwLimitValue = @dwLimitValue
		obj.wLimitCount = @wLimitCount
		obj.dwBeginTime = @dwBeginTime
		obj.dwEndTime = @dwEndTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDiscount.new
		s.byPos = ByteUtil::readUINT8(data)
		s.qwMarkID = ByteUtil::readUINT64(data)
		s.vecDisItems = SDiscountItem::vectorFromStream(data)
		s.byLimitType = ByteUtil::readUINT8(data)
		s.dwLimitValue = ByteUtil::readUINT32(data)
		s.wLimitCount = ByteUtil::readUINT16(data)
		s.dwBeginTime = ByteUtil::readUINT32(data)
		s.dwEndTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDiscount::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byPos)
		ByteUtil::writeUINT64(data, @qwMarkID)
		SDiscountItem::vectorToStream(data, @vecDisItems)
		ByteUtil::writeUINT8(data, @byLimitType)
		ByteUtil::writeUINT32(data, @dwLimitValue)
		ByteUtil::writeUINT16(data, @wLimitCount)
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

#物品购买信息
class SBuyItemInfo
	attr_accessor:dwInstID #(UINT32)实例ID
	attr_accessor:dwCount #(UINT32)物品数量

	#构造函数
	def initialize
		@dwInstID = 0
		@dwCount = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwInstID = @dwInstID
		obj.dwCount = @dwCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBuyItemInfo.new
		s.dwInstID = ByteUtil::readUINT32(data)
		s.dwCount = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBuyItemInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
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

#函数[MalGet:预览商城信息]的返回的参数组成的结构体
class SRetParam_MalGet
	attr_accessor:vecMallInfo#(SMallInfo的数组)商场信息列表

	#构造函数
	def initialize
		@vecMallInfo = Array.new
	end
end

#函数[MalBuy:商场购买]的返回的参数组成的结构体
class SRetParam_MalBuy
	attr_accessor:eResult#(枚举类型：EMallResult)购买结果返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[MallPresent:商场赠送]的返回的参数组成的结构体
class SRetParam_MallPresent
	attr_accessor:eResult#(枚举类型：EMallResult)赠送结果返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[BuyDiscountItem:购买商场限购道具]的返回的参数组成的结构体
class SRetParam_BuyDiscountItem
	attr_accessor:eResult#(枚举类型：EMallResult)购买结果返回
	attr_accessor:byPos#(UINT8)限购位置(0,1,2)
	attr_accessor:wCount#(UINT16)购买个数

	#构造函数
	def initialize
		@eResult = 0
		@byPos = 0
		@wCount = 0
	end
end

#函数[GetBuyItemList:获取物品购买数量列表]的返回的参数组成的结构体
class SRetParam_GetBuyItemList
	attr_accessor:vecBuyItemInfo#(SBuyItemInfo的数组)购买数量列表

	#构造函数
	def initialize
		@vecBuyItemInfo = Array.new
	end
end

#协议类：商城相关协议
class MallProtBase < ProtocolBase
	#以下为发送函数
	#发送：预览商城信息
	def send_MalGet(
		eType #(枚举类型：EMallType)商城类型
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeINT8(data, eType)
		return @svrHandler.sendPacket(data)
	end

	#发送：商场购买
	def send_MalBuy(
		eMark,  #(枚举类型：EUseMoneyMark)使用钱币标志
		eType,  #(枚举类型：EMallType)商城类型
		wInstID,  #(UINT32)实例ID
		wCount #(UINT16)物品个数
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeINT8(data, eMark)
		ByteUtil::writeINT8(data, eType)
		ByteUtil::writeUINT32(data, wInstID)
		ByteUtil::writeUINT16(data, wCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：商场赠送
	def send_MallPresent(
		eMark,  #(枚举类型：EUseMoneyMark)使用钱币标志
		eType,  #(枚举类型：EMallType)商城类型
		wInstID,  #(UINT32)物品ID
		wCount,  #(UINT16)物品个数
		strReceiveName,  #(string)接受者姓名
		strTitle,  #(string)邮件标题
		strMsg #(string)邮件内容
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeINT8(data, eMark)
		ByteUtil::writeINT8(data, eType)
		ByteUtil::writeUINT32(data, wInstID)
		ByteUtil::writeUINT16(data, wCount)
		ByteUtil::writeSTRING(data, strReceiveName)
		ByteUtil::writeSTRING(data, strTitle)
		ByteUtil::writeSTRING(data, strMsg)
		return @svrHandler.sendPacket(data)
	end

	#发送：预览商城限购信息
	def send_GetMallDiscountInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：购买商场限购道具
	def send_BuyDiscountItem(
		byPos,  #(UINT8)限购位置(0,1,2)
		wCount #(UINT16)购买个数
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byPos)
		ByteUtil::writeUINT16(data, wCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取物品购买数量列表
	def send_GetBuyItemList(
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取玩家首次充值活动完成信息(在商城界面的奖励)
	def send_GetChongZhiActInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：通知玩家商城限购信息
	def onRecv_UpdateMallDiscountInfo(
		vecDiscount, #(SDiscount的数组)限购信息列表
		wCountPos1, #(UINT32)限购位置1购买道具数
		wCountPos2, #(UINT32)限购位置2购买道具数
		wCountPos3, #(UINT32)限购位置3购买道具数
		wRechargePos1, #(UINT32)位置1充值限购期间充值仙石数
		wRechargePos2, #(UINT32)位置2充值限购期间充值仙石数
		wRechargePos3, #(UINT32)位置3充值限购期间充值仙石数
		wConsumePos1, #(UINT32)位置1消费限购期间消费仙石数
		wConsumePos2, #(UINT32)位置2消费限购期间消费仙石数
		wConsumePos3 #(UINT32)位置3消费限购期间消费仙石数
	)
		raise NotImplementedError
	end
	#接收：通过栏位通知玩家商城限购信息
	def onRecv_UpdateMallDiscountInfoByPos(
		oDiscount #(类类型：SDiscount)限购信息列表
	)
		raise NotImplementedError
	end
	#接收：物品购买数量更新
	def onRecv_BuyItemNotify(
		oBuyItemInfo #(类类型：SBuyItemInfo)更新信息 dwInstID=0 表示整个更新列表清空数量（0点刷新）
	)
		raise NotImplementedError
	end
	#接收：更新玩家'首次充值'活动完成信息(在商城界面的奖励)
	def onRecv_UpdateChongZhiActInfo(
		byIdx, #(UINT8)当前充值完成的第几个
		dwCount, #(UINT32)当前充值了几个仙石包
		byInfo #(UINT8)按位取(低6位,每位为1表明已完成)
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：预览商城信息
	def onReturn_MalGet(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_MalGet)返回的参数
	)
	end

	#返回：商场购买
	def onReturn_MalBuy(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_MalBuy)返回的参数
	)
	end

	#返回：商场赠送
	def onReturn_MallPresent(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_MallPresent)返回的参数
	)
	end

	#返回：购买商场限购道具
	def onReturn_BuyDiscountItem(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuyDiscountItem)返回的参数
	)
	end

	#返回：获取物品购买数量列表
	def onReturn_GetBuyItemList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetBuyItemList)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：通知玩家商城限购信息
	def _doRecv_UpdateMallDiscountInfo(data)
		vecDiscount = SDiscount::vectorFromStream(data)
		wCountPos1 = ByteUtil::readUINT32(data)
		wCountPos2 = ByteUtil::readUINT32(data)
		wCountPos3 = ByteUtil::readUINT32(data)
		wRechargePos1 = ByteUtil::readUINT32(data)
		wRechargePos2 = ByteUtil::readUINT32(data)
		wRechargePos3 = ByteUtil::readUINT32(data)
		wConsumePos1 = ByteUtil::readUINT32(data)
		wConsumePos2 = ByteUtil::readUINT32(data)
		wConsumePos3 = ByteUtil::readUINT32(data)
		return onRecv_UpdateMallDiscountInfo(vecDiscount, wCountPos1, wCountPos2, wCountPos3, wRechargePos1, wRechargePos2, wRechargePos3, wConsumePos1, wConsumePos2, wConsumePos3)
	end

	#接收处理：通过栏位通知玩家商城限购信息
	def _doRecv_UpdateMallDiscountInfoByPos(data)
		oDiscount = SDiscount::fromStream(data)
		return onRecv_UpdateMallDiscountInfoByPos(oDiscount)
	end

	#接收处理：物品购买数量更新
	def _doRecv_BuyItemNotify(data)
		oBuyItemInfo = SBuyItemInfo::fromStream(data)
		return onRecv_BuyItemNotify(oBuyItemInfo)
	end

	#接收处理：更新玩家'首次充值'活动完成信息(在商城界面的奖励)
	def _doRecv_UpdateChongZhiActInfo(data)
		byIdx = ByteUtil::readUINT8(data)
		dwCount = ByteUtil::readUINT32(data)
		byInfo = ByteUtil::readUINT8(data)
		return onRecv_UpdateChongZhiActInfo(byIdx, dwCount, byInfo)
	end

#以下为返回处理函数
	#返回处理：预览商城信息
	def _doReturn_MalGet(data)
		retParam = SRetParam_MalGet.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecMallInfo = SMallInfo::vectorFromStream(data) #(SMallInfo的数组)商场信息列表
		retParam.vecMallInfo = vecMallInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_MalGet(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：预览商城信息
	def _onTimeOut_MalGet(sessionID)
		retParam = SRetParam_MalGet.new;
		onReturn_MalGet(2, retParam)
	end

	#返回处理：商场购买
	def _doReturn_MalBuy(data)
		retParam = SRetParam_MalBuy.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readINT8(data) #(枚举类型：EMallResult)购买结果返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_MalBuy(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：商场购买
	def _onTimeOut_MalBuy(sessionID)
		retParam = SRetParam_MalBuy.new;
		onReturn_MalBuy(2, retParam)
	end

	#返回处理：商场赠送
	def _doReturn_MallPresent(data)
		retParam = SRetParam_MallPresent.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readINT8(data) #(枚举类型：EMallResult)赠送结果返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_MallPresent(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：商场赠送
	def _onTimeOut_MallPresent(sessionID)
		retParam = SRetParam_MallPresent.new;
		onReturn_MallPresent(2, retParam)
	end

	#返回处理：购买商场限购道具
	def _doReturn_BuyDiscountItem(data)
		retParam = SRetParam_BuyDiscountItem.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readINT8(data) #(枚举类型：EMallResult)购买结果返回
		byPos = ByteUtil::readUINT8(data) #(UINT8)限购位置(0,1,2)
		wCount = ByteUtil::readUINT16(data) #(UINT16)购买个数
		retParam.eResult = eResult
		retParam.byPos = byPos
		retParam.wCount = wCount
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuyDiscountItem(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：购买商场限购道具
	def _onTimeOut_BuyDiscountItem(sessionID)
		retParam = SRetParam_BuyDiscountItem.new;
		onReturn_BuyDiscountItem(2, retParam)
	end

	#返回处理：获取物品购买数量列表
	def _doReturn_GetBuyItemList(data)
		retParam = SRetParam_GetBuyItemList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecBuyItemInfo = SBuyItemInfo::vectorFromStream(data) #(SBuyItemInfo的数组)购买数量列表
		retParam.vecBuyItemInfo = vecBuyItemInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetBuyItemList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取物品购买数量列表
	def _onTimeOut_GetBuyItemList(sessionID)
		retParam = SRetParam_GetBuyItemList.new;
		onReturn_GetBuyItemList(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 27;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_UpdateMallDiscountInfo' #FuncID: 1
		@recvFuncList[1] = '_doRecv_UpdateMallDiscountInfoByPos' #FuncID: 2
		@recvFuncList[2] = '_doRecv_BuyItemNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_UpdateChongZhiActInfo' #FuncID: 4

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_MalGet' #FuncID: 1
		@retFuncList[1] = '_doReturn_MalBuy' #FuncID: 2
		@retFuncList[2] = '_doReturn_MallPresent' #FuncID: 3
		@retFuncList[3] = '_doReturn_BuyDiscountItem' #FuncID: 4
		@retFuncList[4] = '_doReturn_GetBuyItemList' #FuncID: 5

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_MalGet' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_MalBuy' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_MallPresent' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_BuyDiscountItem' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_GetBuyItemList' #FuncID: 5
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

