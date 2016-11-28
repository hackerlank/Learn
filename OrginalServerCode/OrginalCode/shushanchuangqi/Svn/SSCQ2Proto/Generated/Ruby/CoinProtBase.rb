#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    CoinProt.rb
#  Purpose:      888礼券协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#操作结果
class EResultInCoinProt
	ECOINERROR = 0#错误
	ECOINGAIN = 1#已经领取
	ECOINSUCCESS = 2#成功
end

#函数[GetCoinPacket:获取礼包]的返回的参数组成的结构体
class SRetParam_GetCoinPacket
	attr_accessor:eResult#(枚举类型：EResultInCoinProt)操作结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：888礼券协议
class CoinProtBase < ProtocolBase
	#以下为发送函数
	#发送：获取礼包
	def send_GetCoinPacket(
		eType,  #(枚类型：ProtoCommon::EMoneyType)礼包类型
		dwMoney #(UINT32)数量
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eType)
		ByteUtil::writeUINT32(data, dwMoney)
		return @svrHandler.sendPacket(data)
	end

#以下的返回函数需要重载
	#返回：获取礼包
	def onReturn_GetCoinPacket(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetCoinPacket)返回的参数
	)
	end

	#返回处理：获取礼包
	def _doReturn_GetCoinPacket(data)
		retParam = SRetParam_GetCoinPacket.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EResultInCoinProt)操作结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetCoinPacket(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取礼包
	def _onTimeOut_GetCoinPacket(sessionID)
		retParam = SRetParam_GetCoinPacket.new;
		onReturn_GetCoinPacket(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 91;
		@recvFuncList = Array.new

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetCoinPacket' #FuncID: 1

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetCoinPacket' #FuncID: 1
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

