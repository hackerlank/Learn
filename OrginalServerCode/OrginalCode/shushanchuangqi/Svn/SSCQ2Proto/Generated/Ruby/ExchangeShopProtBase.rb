#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    ExchangeShopProt.rb
#  Purpose:      兑换商店
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#兑换商店错误码
class EExchangeShop
	EEXCHANGESHOP_SUCESS = 0#成功
	EEXCHANGESHOP_CFGLIMIT = 1#没有该兑换商品
	EEXCHANGESHOP_MONEYLIMIT = 2#钱不够
	EEXCHANGESHOP_CONDLIMIT = 3#购买条件不满足
	EEXCHANGESHOP_COUNTLIMIT = 4#购买数量限制
	EEXCHANGESHOP_ERRORITEMID = 5#物品配置找不到
	EEXCHANGESHOP_ERRORPACK = 6#背包满无法添加物品
end

#已兑换信息列表
class ExchangeInfo
	attr_accessor:qwRoleID #(UINT64)角色ID
	attr_accessor:dwExchangeID #(UINT32)兑换ID
	attr_accessor:dwCount #(UINT32)已兑换次数
	attr_accessor:dwFinishTime #(UINT32)兑换时间

	#构造函数
	def initialize
		@qwRoleID = 0
		@dwExchangeID = 0
		@dwCount = 0
		@dwFinishTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.dwExchangeID = @dwExchangeID
		obj.dwCount = @dwCount
		obj.dwFinishTime = @dwFinishTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = ExchangeInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.dwExchangeID = ByteUtil::readUINT32(data)
		s.dwCount = ByteUtil::readUINT32(data)
		s.dwFinishTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = ExchangeInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT32(data, @dwExchangeID)
		ByteUtil::writeUINT32(data, @dwCount)
		ByteUtil::writeUINT32(data, @dwFinishTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[ExchangeItem:兑换物品]的返回的参数组成的结构体
class SRetParam_ExchangeItem
	attr_accessor:dwRet#(UINT32)结果

	#构造函数
	def initialize
		@dwRet = 0
	end
end

#函数[ExchangeItemList:已兑换列表]的返回的参数组成的结构体
class SRetParam_ExchangeItemList
	attr_accessor:vecExchangeInfo#(ExchangeInfo的数组)已兑换列表

	#构造函数
	def initialize
		@vecExchangeInfo = Array.new
	end
end

#协议类：兑换商店
class ExchangeShopProtBase < ProtocolBase
	#以下为发送函数
	#发送：兑换物品
	def send_ExchangeItem(
		dwExchangeID,  #(UINT32)兑换id
		dwCount #(UINT32)兑换数量
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwExchangeID)
		ByteUtil::writeUINT32(data, dwCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：已兑换列表
	def send_ExchangeItemList(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：已兑换信息更新
	def onRecv_ExchangeItemUpdate(
		oExchangeInfo #(类类型：ExchangeInfo)更新已兑换信息
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：兑换物品
	def onReturn_ExchangeItem(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ExchangeItem)返回的参数
	)
	end

	#返回：已兑换列表
	def onReturn_ExchangeItemList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ExchangeItemList)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：已兑换信息更新
	def _doRecv_ExchangeItemUpdate(data)
		oExchangeInfo = ExchangeInfo::fromStream(data)
		return onRecv_ExchangeItemUpdate(oExchangeInfo)
	end

#以下为返回处理函数
	#返回处理：兑换物品
	def _doReturn_ExchangeItem(data)
		retParam = SRetParam_ExchangeItem.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果
		retParam.dwRet = dwRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ExchangeItem(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：兑换物品
	def _onTimeOut_ExchangeItem(sessionID)
		retParam = SRetParam_ExchangeItem.new;
		onReturn_ExchangeItem(2, retParam)
	end

	#返回处理：已兑换列表
	def _doReturn_ExchangeItemList(data)
		retParam = SRetParam_ExchangeItemList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecExchangeInfo = ExchangeInfo::vectorFromStream(data) #(ExchangeInfo的数组)已兑换列表
		retParam.vecExchangeInfo = vecExchangeInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ExchangeItemList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：已兑换列表
	def _onTimeOut_ExchangeItemList(sessionID)
		retParam = SRetParam_ExchangeItemList.new;
		onReturn_ExchangeItemList(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 101;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_ExchangeItemUpdate' #FuncID: 1

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_ExchangeItem' #FuncID: 1
		@retFuncList[1] = '_doReturn_ExchangeItemList' #FuncID: 2

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_ExchangeItem' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_ExchangeItemList' #FuncID: 2
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

