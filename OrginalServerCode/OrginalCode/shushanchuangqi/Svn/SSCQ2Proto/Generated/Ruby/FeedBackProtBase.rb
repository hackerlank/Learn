#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    FeedBackProt.rb
#  Purpose:      消费回馈
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#消费回馈错误码
class EFeedBackRet
	EFEEDBACKRET_SUCESS = 0#成功
	EFEEDBACKRET_MONEYLIMIT = 1#仙元不足
	EFEEDBACKRET_TAKECNTLIMIT = 2#领取次数限制
	EFEEDBACKRET_IDERROR = 3#领奖id错误
	EFEEDBACKRET_TIMEERROR = 4#不在限购时间
	EFEEDBACKRET_CFGERROR = 5#配置错误
	EFEEDBACKRET_PARAMERROR = 6#参数错误
	EFEEDBACKRET_PACKERROR = 7#背包空间不足
	EFEEDBACKRET_ACTIVETIMEERROR = 8#不在活动时间内
	EFEEDBACKRET_PRIZECNTERROR = 9#领奖次数限制
end

#消费回馈类型
class EFeedBackActType
	EFEEDBACKACTTYPE_INVALID = 0#无效
	EFEEDBACKACTTYPE_EQUIPTRUMP = 1#法宝强化
	EFEEDBACKACTTYPE_STONE = 2#宝石合成
end

#回馈信息
class SFeedBackInfo
	attr_accessor:dwActID #(UINT32)活动id
	attr_accessor:dwBeginTime #(UINT32)开始时间
	attr_accessor:dwEndTime #(UINT32)结束时间
	attr_accessor:dwTakePrizeMax #(UINT32)可领奖次数
	attr_accessor:dwTakePrizedCnt #(UINT32)已领奖次数

	#构造函数
	def initialize
		@dwActID = 0
		@dwBeginTime = 0
		@dwEndTime = 0
		@dwTakePrizeMax = 0
		@dwTakePrizedCnt = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwActID = @dwActID
		obj.dwBeginTime = @dwBeginTime
		obj.dwEndTime = @dwEndTime
		obj.dwTakePrizeMax = @dwTakePrizeMax
		obj.dwTakePrizedCnt = @dwTakePrizedCnt
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFeedBackInfo.new
		s.dwActID = ByteUtil::readUINT32(data)
		s.dwBeginTime = ByteUtil::readUINT32(data)
		s.dwEndTime = ByteUtil::readUINT32(data)
		s.dwTakePrizeMax = ByteUtil::readUINT32(data)
		s.dwTakePrizedCnt = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFeedBackInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwActID)
		ByteUtil::writeUINT32(data, @dwBeginTime)
		ByteUtil::writeUINT32(data, @dwEndTime)
		ByteUtil::writeUINT32(data, @dwTakePrizeMax)
		ByteUtil::writeUINT32(data, @dwTakePrizedCnt)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#折扣限购信息
class SBuyDiscountInfo
	attr_accessor:eType #(枚举类型：EFeedBackActType)消费回馈类型
	attr_accessor:dwBuyCount #(UINT32)已领购买次数

	#构造函数
	def initialize
		@eType = 0
		@dwBuyCount = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eType = @eType
		obj.dwBuyCount = @dwBuyCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBuyDiscountInfo.new
		s.eType = ByteUtil::readUINT8(data)
		s.dwBuyCount = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBuyDiscountInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eType)
		ByteUtil::writeUINT32(data, @dwBuyCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetFeedBackList:获取回馈列表]的返回的参数组成的结构体
class SRetParam_GetFeedBackList
	attr_accessor:vecFeedBackInfo#(SFeedBackInfo的数组)回馈信息列表
	attr_accessor:vecSBuyDiscountInfo#(SBuyDiscountInfo的数组)折扣限购信息

	#构造函数
	def initialize
		@vecFeedBackInfo = Array.new
		@vecSBuyDiscountInfo = Array.new
	end
end

#函数[BuyDisCountItem:购买折扣物品]的返回的参数组成的结构体
class SRetParam_BuyDisCountItem
	attr_accessor:eRet#(枚举类型：EFeedBackRet)结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#函数[TakeFeedBackPrize:领取奖励]的返回的参数组成的结构体
class SRetParam_TakeFeedBackPrize
	attr_accessor:eRet#(枚举类型：EFeedBackRet)结果
	attr_accessor:dwBuyCount#(UINT32)已购买次数（购买成功后返回次数）

	#构造函数
	def initialize
		@eRet = 0
		@dwBuyCount = 0
	end
end

#协议类：消费回馈
class FeedBackProtBase < ProtocolBase
	#以下为发送函数
	#发送：获取回馈列表
	def send_GetFeedBackList(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：购买折扣物品
	def send_BuyDisCountItem(
		dwBuyID,  #(UINT32)购买id
		dwCount #(UINT32)购买id数量
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwBuyID)
		ByteUtil::writeUINT32(data, dwCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：领取奖励
	def send_TakeFeedBackPrize(
		dwActID #(UINT32)活动id
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwActID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：回馈信息更新
	def onRecv_FeedBackInfoNotify(
		oFeedBackInfo #(类类型：SFeedBackInfo)回馈信息
	)
		raise NotImplementedError
	end
	#接收：回馈活动过期
	def onRecv_FeedBackExpireNotify(
		dwActID #(UINT32)活动id
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取回馈列表
	def onReturn_GetFeedBackList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetFeedBackList)返回的参数
	)
	end

	#返回：购买折扣物品
	def onReturn_BuyDisCountItem(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuyDisCountItem)返回的参数
	)
	end

	#返回：领取奖励
	def onReturn_TakeFeedBackPrize(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakeFeedBackPrize)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：回馈信息更新
	def _doRecv_FeedBackInfoNotify(data)
		oFeedBackInfo = SFeedBackInfo::fromStream(data)
		return onRecv_FeedBackInfoNotify(oFeedBackInfo)
	end

	#接收处理：回馈活动过期
	def _doRecv_FeedBackExpireNotify(data)
		dwActID = ByteUtil::readUINT32(data)
		return onRecv_FeedBackExpireNotify(dwActID)
	end

#以下为返回处理函数
	#返回处理：获取回馈列表
	def _doReturn_GetFeedBackList(data)
		retParam = SRetParam_GetFeedBackList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecFeedBackInfo = SFeedBackInfo::vectorFromStream(data) #(SFeedBackInfo的数组)回馈信息列表
		vecSBuyDiscountInfo = SBuyDiscountInfo::vectorFromStream(data) #(SBuyDiscountInfo的数组)折扣限购信息
		retParam.vecFeedBackInfo = vecFeedBackInfo
		retParam.vecSBuyDiscountInfo = vecSBuyDiscountInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetFeedBackList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取回馈列表
	def _onTimeOut_GetFeedBackList(sessionID)
		retParam = SRetParam_GetFeedBackList.new;
		onReturn_GetFeedBackList(2, retParam)
	end

	#返回处理：购买折扣物品
	def _doReturn_BuyDisCountItem(data)
		retParam = SRetParam_BuyDisCountItem.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EFeedBackRet)结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuyDisCountItem(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：购买折扣物品
	def _onTimeOut_BuyDisCountItem(sessionID)
		retParam = SRetParam_BuyDisCountItem.new;
		onReturn_BuyDisCountItem(2, retParam)
	end

	#返回处理：领取奖励
	def _doReturn_TakeFeedBackPrize(data)
		retParam = SRetParam_TakeFeedBackPrize.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EFeedBackRet)结果
		dwBuyCount = ByteUtil::readUINT32(data) #(UINT32)已购买次数（购买成功后返回次数）
		retParam.eRet = eRet
		retParam.dwBuyCount = dwBuyCount
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakeFeedBackPrize(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：领取奖励
	def _onTimeOut_TakeFeedBackPrize(sessionID)
		retParam = SRetParam_TakeFeedBackPrize.new;
		onReturn_TakeFeedBackPrize(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 144;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_FeedBackInfoNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_FeedBackExpireNotify' #FuncID: 2

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetFeedBackList' #FuncID: 1
		@retFuncList[1] = '_doReturn_BuyDisCountItem' #FuncID: 2
		@retFuncList[2] = '_doReturn_TakeFeedBackPrize' #FuncID: 3

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetFeedBackList' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_BuyDisCountItem' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_TakeFeedBackPrize' #FuncID: 3
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

