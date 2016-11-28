#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    MoneyTree.rb
#  Purpose:      摇钱树协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#操作结果
class EMoneyTreeResult
	SUCCEED = 0#成功
	ERROR = 1#失败
end

#函数[GetMoneyTreeInfo:请求摇钱树信息]的返回的参数组成的结构体
class SRetParam_GetMoneyTreeInfo
	attr_accessor:todayUseCount#(UINT16)今日使用次数

	#构造函数
	def initialize
		@todayUseCount = 0
	end
end

#函数[GetMoney:请求摇钱]的返回的参数组成的结构体
class SRetParam_GetMoney
	attr_accessor:todayUseCount#(UINT16)今日使用次数

	#构造函数
	def initialize
		@todayUseCount = 0
	end
end

#协议类：摇钱树协议
class MoneyTreeProtBase < ProtocolBase
	#以下为发送函数
	#发送：请求摇钱树信息
	def send_GetMoneyTreeInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求摇钱
	def send_GetMoney(
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
	#返回：请求摇钱树信息
	def onReturn_GetMoneyTreeInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetMoneyTreeInfo)返回的参数
	)
	end

	#返回：请求摇钱
	def onReturn_GetMoney(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetMoney)返回的参数
	)
	end

	#返回处理：请求摇钱树信息
	def _doReturn_GetMoneyTreeInfo(data)
		retParam = SRetParam_GetMoneyTreeInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		todayUseCount = ByteUtil::readUINT16(data) #(UINT16)今日使用次数
		retParam.todayUseCount = todayUseCount
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetMoneyTreeInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求摇钱树信息
	def _onTimeOut_GetMoneyTreeInfo(sessionID)
		retParam = SRetParam_GetMoneyTreeInfo.new;
		onReturn_GetMoneyTreeInfo(2, retParam)
	end

	#返回处理：请求摇钱
	def _doReturn_GetMoney(data)
		retParam = SRetParam_GetMoney.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		todayUseCount = ByteUtil::readUINT16(data) #(UINT16)今日使用次数
		retParam.todayUseCount = todayUseCount
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetMoney(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求摇钱
	def _onTimeOut_GetMoney(sessionID)
		retParam = SRetParam_GetMoney.new;
		onReturn_GetMoney(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 88;
		@recvFuncList = Array.new

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetMoneyTreeInfo' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetMoney' #FuncID: 2

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetMoneyTreeInfo' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetMoney' #FuncID: 2
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

