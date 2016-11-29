#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    ShushanweiweiProt.rb
#  Purpose:      蜀山微微协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#操作结果
class EPkgResult
	EPACKERROR = 0#错误
	EPACKGAIN = 1#已经领取
	EPACKFULL = 2#背包已满
	EPACKSUCCESS = 3#成功
end

#领奖类型
class EPkgType
	EWEIBO = 0#微博
	EWEIXIN = 1#微信
	EMAX = 2#最大值
end

#奖励信息
class SPrizeInfo
	attr_accessor:eType #(枚举类型：EPkgType)奖励类型
	attr_accessor:dwCount #(UINT32)当前人数
	attr_accessor:bListen #(bool)微博是否收听
	attr_accessor:bResult #(bool)个人奖励是否领取
	attr_accessor:wResult #(UINT16)全服奖励领取结果

	#构造函数
	def initialize
		@eType = 0
		@dwCount = 0
		@bListen = false
		@bResult = false
		@wResult = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eType = @eType
		obj.dwCount = @dwCount
		obj.bListen = @bListen
		obj.bResult = @bResult
		obj.wResult = @wResult
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPrizeInfo.new
		s.eType = ByteUtil::readUINT8(data)
		s.dwCount = ByteUtil::readUINT32(data)
		s.bListen = ByteUtil::readBOOL(data)
		s.bResult = ByteUtil::readBOOL(data)
		s.wResult = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPrizeInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eType)
		ByteUtil::writeUINT32(data, @dwCount)
		ByteUtil::writeBOOL(data, @bListen)
		ByteUtil::writeBOOL(data, @bResult)
		ByteUtil::writeUINT16(data, @wResult)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[TakePrize:获取礼包]的返回的参数组成的结构体
class SRetParam_TakePrize
	attr_accessor:eRetType#(枚举类型：EPkgType)活动类型返回
	attr_accessor:wRetIndex#(UINT16)领奖类型返回：0表示个人奖励，1..16 表示领取全服第几个奖励
	attr_accessor:eRet#(枚举类型：EPkgResult)操作结果返回

	#构造函数
	def initialize
		@eRetType = 0
		@wRetIndex = 0
		@eRet = 0
	end
end

#函数[ListenWeibo:收听微博]的返回的参数组成的结构体
class SRetParam_ListenWeibo
	attr_accessor:eRet#(枚举类型：EPkgResult)操作结果返回

	#构造函数
	def initialize
		@eRet = 0
	end
end

#协议类：蜀山微微协议
class ShushanweiweiProtBase < ProtocolBase
	#以下为发送函数
	#发送：获取礼包
	def send_TakePrize(
		eType,  #(枚举类型：EPkgType)活动类型
		wIndex,  #(UINT16)领奖类型：0表示个人奖励，1..16位 表示领取全服第几个奖励
		strCDK #(string)CDK
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eType)
		ByteUtil::writeUINT16(data, wIndex)
		ByteUtil::writeSTRING(data, strCDK)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得玩家奖励信息
	def send_GetPrizeInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：收听微博
	def send_ListenWeibo(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：同步玩家奖励信息
	def onRecv_SyncPrizeInfo(
		vecResult #(SPrizeInfo的数组)奖励结果
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取礼包
	def onReturn_TakePrize(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakePrize)返回的参数
	)
	end

	#返回：收听微博
	def onReturn_ListenWeibo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ListenWeibo)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：同步玩家奖励信息
	def _doRecv_SyncPrizeInfo(data)
		vecResult = SPrizeInfo::vectorFromStream(data)
		return onRecv_SyncPrizeInfo(vecResult)
	end

#以下为返回处理函数
	#返回处理：获取礼包
	def _doReturn_TakePrize(data)
		retParam = SRetParam_TakePrize.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRetType = ByteUtil::readUINT8(data) #(枚举类型：EPkgType)活动类型返回
		wRetIndex = ByteUtil::readUINT16(data) #(UINT16)领奖类型返回：0表示个人奖励，1..16 表示领取全服第几个奖励
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EPkgResult)操作结果返回
		retParam.eRetType = eRetType
		retParam.wRetIndex = wRetIndex
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakePrize(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取礼包
	def _onTimeOut_TakePrize(sessionID)
		retParam = SRetParam_TakePrize.new;
		onReturn_TakePrize(2, retParam)
	end

	#返回处理：收听微博
	def _doReturn_ListenWeibo(data)
		retParam = SRetParam_ListenWeibo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EPkgResult)操作结果返回
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ListenWeibo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：收听微博
	def _onTimeOut_ListenWeibo(sessionID)
		retParam = SRetParam_ListenWeibo.new;
		onReturn_ListenWeibo(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 93;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_SyncPrizeInfo' #FuncID: 1

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_TakePrize' #FuncID: 1
		@retFuncList[1] = '_doReturn_ListenWeibo' #FuncID: 2

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_TakePrize' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_ListenWeibo' #FuncID: 2
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

