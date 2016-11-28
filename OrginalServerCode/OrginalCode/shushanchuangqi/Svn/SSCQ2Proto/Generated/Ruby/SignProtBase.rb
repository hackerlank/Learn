#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    SignProt.rb
#  Purpose:      签到协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#请求的结果
class ESignResult
	ESIGNSUCCEED = 0#成功
	ESIGNHASDONE = 1#今日已签到
	ESIGNRESIGNDONE = 2#补签日已签到
	ESIGNRESIGNERRDATE = 3#补签日期错误
	ESIGNRESIGNOVERTIMES = 4#补签次数用完
	ESIGNAWARDHASGET = 5#该签到奖励已领
	ESIGNAWARDIDERR = 6#该签到奖励id不正确
	ESIGNAWARDLOWDAYS = 7#该签到奖励的签到天数不足
	ESIGNAWARDPACKETFULL = 8#签到奖励包裹放不下
	ESIGNVIP = 9#提醒开通御剑
	ESIGNOTHER = 10#其它错误
end

#函数[GetSignInfo:请求签到信息]的返回的参数组成的结构体
class SRetParam_GetSignInfo
	attr_accessor:dwSignData#(UINT32)按位计数，从右到左，一位表示1天，1表示该日已签到
	attr_accessor:byReSignTimes#(UINT8)该月补签天数
	attr_accessor:dwAward#(UINT32)签到奖励包获取状态

	#构造函数
	def initialize
		@dwSignData = 0
		@byReSignTimes = 0
		@dwAward = 0
	end
end

#函数[DoSign:请求签到]的返回的参数组成的结构体
class SRetParam_DoSign
	attr_accessor:eResult#(枚举类型：ESignResult)处理结果
	attr_accessor:dwSignData#(UINT32)按位计数，从右到左，一位表示1天，1表示该日已签到

	#构造函数
	def initialize
		@eResult = 0
		@dwSignData = 0
	end
end

#函数[DoReSign:请求补签]的返回的参数组成的结构体
class SRetParam_DoReSign
	attr_accessor:eResult#(枚举类型：ESignResult)处理结果
	attr_accessor:dwSignData#(UINT32)按位计数，从右到左，一位表示1天，1表示该日已签到
	attr_accessor:byReSignTimes#(UINT8)该月补签天数

	#构造函数
	def initialize
		@eResult = 0
		@dwSignData = 0
		@byReSignTimes = 0
	end
end

#函数[DoGetAward:请求领取奖励]的返回的参数组成的结构体
class SRetParam_DoGetAward
	attr_accessor:eResult#(枚举类型：ESignResult)处理结果
	attr_accessor:dwAward#(UINT32)签到奖励包获取状态

	#构造函数
	def initialize
		@eResult = 0
		@dwAward = 0
	end
end

#协议类：签到协议
class SignProtBase < ProtocolBase
	#以下为发送函数
	#发送：请求签到信息
	def send_GetSignInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求签到
	def send_DoSign(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求补签
	def send_DoReSign(
		byDay #(UINT8)补签日期
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byDay)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求领取奖励
	def send_DoGetAward(
		byId #(UINT8)奖励ID
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byId)
		return @svrHandler.sendPacket(data)
	end

#以下的返回函数需要重载
	#返回：请求签到信息
	def onReturn_GetSignInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetSignInfo)返回的参数
	)
	end

	#返回：请求签到
	def onReturn_DoSign(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_DoSign)返回的参数
	)
	end

	#返回：请求补签
	def onReturn_DoReSign(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_DoReSign)返回的参数
	)
	end

	#返回：请求领取奖励
	def onReturn_DoGetAward(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_DoGetAward)返回的参数
	)
	end

	#返回处理：请求签到信息
	def _doReturn_GetSignInfo(data)
		retParam = SRetParam_GetSignInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwSignData = ByteUtil::readUINT32(data) #(UINT32)按位计数，从右到左，一位表示1天，1表示该日已签到
		byReSignTimes = ByteUtil::readUINT8(data) #(UINT8)该月补签天数
		dwAward = ByteUtil::readUINT32(data) #(UINT32)签到奖励包获取状态
		retParam.dwSignData = dwSignData
		retParam.byReSignTimes = byReSignTimes
		retParam.dwAward = dwAward
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetSignInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求签到信息
	def _onTimeOut_GetSignInfo(sessionID)
		retParam = SRetParam_GetSignInfo.new;
		onReturn_GetSignInfo(2, retParam)
	end

	#返回处理：请求签到
	def _doReturn_DoSign(data)
		retParam = SRetParam_DoSign.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ESignResult)处理结果
		dwSignData = ByteUtil::readUINT32(data) #(UINT32)按位计数，从右到左，一位表示1天，1表示该日已签到
		retParam.eResult = eResult
		retParam.dwSignData = dwSignData
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_DoSign(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求签到
	def _onTimeOut_DoSign(sessionID)
		retParam = SRetParam_DoSign.new;
		onReturn_DoSign(2, retParam)
	end

	#返回处理：请求补签
	def _doReturn_DoReSign(data)
		retParam = SRetParam_DoReSign.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ESignResult)处理结果
		dwSignData = ByteUtil::readUINT32(data) #(UINT32)按位计数，从右到左，一位表示1天，1表示该日已签到
		byReSignTimes = ByteUtil::readUINT8(data) #(UINT8)该月补签天数
		retParam.eResult = eResult
		retParam.dwSignData = dwSignData
		retParam.byReSignTimes = byReSignTimes
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_DoReSign(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求补签
	def _onTimeOut_DoReSign(sessionID)
		retParam = SRetParam_DoReSign.new;
		onReturn_DoReSign(2, retParam)
	end

	#返回处理：请求领取奖励
	def _doReturn_DoGetAward(data)
		retParam = SRetParam_DoGetAward.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ESignResult)处理结果
		dwAward = ByteUtil::readUINT32(data) #(UINT32)签到奖励包获取状态
		retParam.eResult = eResult
		retParam.dwAward = dwAward
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_DoGetAward(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求领取奖励
	def _onTimeOut_DoGetAward(sessionID)
		retParam = SRetParam_DoGetAward.new;
		onReturn_DoGetAward(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 83;
		@recvFuncList = Array.new

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetSignInfo' #FuncID: 1
		@retFuncList[1] = '_doReturn_DoSign' #FuncID: 2
		@retFuncList[2] = '_doReturn_DoReSign' #FuncID: 3
		@retFuncList[3] = '_doReturn_DoGetAward' #FuncID: 4

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetSignInfo' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_DoSign' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_DoReSign' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_DoGetAward' #FuncID: 4
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

