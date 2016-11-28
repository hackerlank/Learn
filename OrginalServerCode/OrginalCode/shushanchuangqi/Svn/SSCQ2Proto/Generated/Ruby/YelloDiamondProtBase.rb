#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    YelloDiamondProt.rb
#  Purpose:      QQ黄钻协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#操作结果
class EOpResult
	EOTHERERROR = 0#其他错误
	ESHORTLEVEL = 1#等级不够
	ENOTACTIVE = 2#未开通QQ黄钻
	ENOTYEAR = 3#未开通年费黄钻贵族
	ENOTLUXURY = 4#未开通QQ豪华黄钻
	EAREADYGAIN = 5#已经领取
	EBAGFULL = 6#背包空间不足
	ESUCCESS = 7#操作成功
end

#礼包类型
class EBagType
	EBAGTYPE_ENONE = 0#无礼包可领取
	EBAGTYPE_EDAYBAG = 1#黄钻日常礼包
	EBAGTYPE_EYEARBAG = 2#年黄钻礼包
	EBAGTYPE_ELUXURYBAG = 3#豪华QQ黄钻礼包
	EBAGTYPE_ENEWBAG = 4#新手礼包
	EBAGTYPE_EGROWBAG = 5#成长礼包
	EBAGTYPE_EHORSEBAG = 6#座机礼包
	EBAGTYPE_EMAX = 7#最大值
end

#QQ黄钻类型
class EYDType
	EYDTYPE_ENONE = 0#未开通QQ黄钻
	EYDTYPE_EDAYTYPE = 1#普通QQ黄钻
	EYDTYPE_EYEARTYPE = 2#年QQ黄钻
	EYDTYPE_ELUXURYTYPE = 3#豪华QQ黄钻
end

#QQ黄钻信息
class SYDInfo
	attr_accessor:bGainDayBag #(bool)是否领取每日礼包
	attr_accessor:bGainYearBag #(bool)是否领取年费礼包
	attr_accessor:bGainLuxuryBag #(bool)是否领取豪华礼包
	attr_accessor:bGainHorseBag #(bool)是否领取座机礼包
	attr_accessor:dGrowBag #(UINT16)已领取成长礼包等级 从低位开始向高位 1表示领取，0表示未领取
	attr_accessor:bGainNewBag #(bool)是否领取新手礼包

	#构造函数
	def initialize
		@bGainDayBag = false
		@bGainYearBag = false
		@bGainLuxuryBag = false
		@bGainHorseBag = false
		@dGrowBag = 0
		@bGainNewBag = false
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.bGainDayBag = @bGainDayBag
		obj.bGainYearBag = @bGainYearBag
		obj.bGainLuxuryBag = @bGainLuxuryBag
		obj.bGainHorseBag = @bGainHorseBag
		obj.dGrowBag = @dGrowBag
		obj.bGainNewBag = @bGainNewBag
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SYDInfo.new
		s.bGainDayBag = ByteUtil::readBOOL(data)
		s.bGainYearBag = ByteUtil::readBOOL(data)
		s.bGainLuxuryBag = ByteUtil::readBOOL(data)
		s.bGainHorseBag = ByteUtil::readBOOL(data)
		s.dGrowBag = ByteUtil::readUINT16(data)
		s.bGainNewBag = ByteUtil::readBOOL(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SYDInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeBOOL(data, @bGainDayBag)
		ByteUtil::writeBOOL(data, @bGainYearBag)
		ByteUtil::writeBOOL(data, @bGainLuxuryBag)
		ByteUtil::writeBOOL(data, @bGainHorseBag)
		ByteUtil::writeUINT16(data, @dGrowBag)
		ByteUtil::writeBOOL(data, @bGainNewBag)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GainYDBag:获取黄钻礼包]的返回的参数组成的结构体
class SRetParam_GainYDBag
	attr_accessor:eOpResult#(枚举类型：EOpResult)操作结果

	#构造函数
	def initialize
		@eOpResult = 0
	end
end

#函数[GetYDBagInfo:获取黄钻礼包领取信息]的返回的参数组成的结构体
class SRetParam_GetYDBagInfo
	attr_accessor:ydInfo#(类类型：SYDInfo)黄钻信息

	#构造函数
	def initialize
		@ydInfo = SYDInfo.new
	end
end

#协议类：QQ黄钻协议
class YelloDiamondProtBase < ProtocolBase
	#以下为发送函数
	#发送：获取黄钻礼包
	def send_GainYDBag(
		eBagType,  #(枚举类型：EBagType)礼包类型
		dLevel #(UINT16)玩家等级成长礼包
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eBagType)
		ByteUtil::writeUINT16(data, dLevel)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取黄钻礼包领取信息
	def send_GetYDBagInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的返回函数需要重载
	#返回：获取黄钻礼包
	def onReturn_GainYDBag(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GainYDBag)返回的参数
	)
	end

	#返回：获取黄钻礼包领取信息
	def onReturn_GetYDBagInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetYDBagInfo)返回的参数
	)
	end

	#返回处理：获取黄钻礼包
	def _doReturn_GainYDBag(data)
		retParam = SRetParam_GainYDBag.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eOpResult = ByteUtil::readUINT8(data) #(枚举类型：EOpResult)操作结果
		retParam.eOpResult = eOpResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GainYDBag(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取黄钻礼包
	def _onTimeOut_GainYDBag(sessionID)
		retParam = SRetParam_GainYDBag.new;
		onReturn_GainYDBag(2, retParam)
	end

	#返回处理：获取黄钻礼包领取信息
	def _doReturn_GetYDBagInfo(data)
		retParam = SRetParam_GetYDBagInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		ydInfo = SYDInfo::fromStream(data) #(类类型：SYDInfo)黄钻信息
		retParam.ydInfo = ydInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetYDBagInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取黄钻礼包领取信息
	def _onTimeOut_GetYDBagInfo(sessionID)
		retParam = SRetParam_GetYDBagInfo.new;
		onReturn_GetYDBagInfo(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 200;
		@recvFuncList = Array.new

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GainYDBag' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetYDBagInfo' #FuncID: 2

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GainYDBag' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetYDBagInfo' #FuncID: 2
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

