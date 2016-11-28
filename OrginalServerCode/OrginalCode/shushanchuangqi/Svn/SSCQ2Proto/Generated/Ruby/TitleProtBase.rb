#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    TitleProt.rb
#  Purpose:      称号协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './RoleInfoDefineBase.rb'

#以下为类型定义

#请求的结果
class ETitleResult
	ETITLESUCCEED = 0#成功
	ETITLEVIPLEVEL = 1#御剑等级不足
	ETITLENOHAS = 2#该称号没有获得
	ETITLEERROTHER = 3#其它错误
end

#函数[GetAllTitle:得到当前所有称号]的返回的参数组成的结构体
class SRetParam_GetAllTitle
	attr_accessor:vecTitle#(STitle的数组)当前所有称号

	#构造函数
	def initialize
		@vecTitle = Array.new
	end
end

#函数[EquipTitle:刷新称号列表]的返回的参数组成的结构体
class SRetParam_EquipTitle
	attr_accessor:eResult#(枚举类型：ETitleResult)操作结果
	attr_accessor:wId#(UINT16)称号ID
	attr_accessor:byPos#(UINT8)装备位置

	#构造函数
	def initialize
		@eResult = 0
		@wId = 0
		@byPos = 0
	end
end

#协议类：称号协议
class TitleProtBase < ProtocolBase
	#以下为发送函数
	#发送：得到当前所有称号
	def send_GetAllTitle(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：刷新称号列表
	def send_EquipTitle(
		wId,  #(UINT16)称号ID
		byPos #(UINT8)装备位置,0表示任意位置
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wId)
		ByteUtil::writeUINT8(data, byPos)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：获得称号
	def onRecv_AddTitle(
		stTitleInfo #(类类型：RoleInfoDefine::STitle)称号详情
	)
		raise NotImplementedError
	end
	#接收：删除称号
	def onRecv_DelTitle(
		wId #(UINT16)称号ID
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：得到当前所有称号
	def onReturn_GetAllTitle(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAllTitle)返回的参数
	)
	end

	#返回：刷新称号列表
	def onReturn_EquipTitle(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_EquipTitle)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：获得称号
	def _doRecv_AddTitle(data)
		stTitleInfo = STitle::fromStream(data)
		return onRecv_AddTitle(stTitleInfo)
	end

	#接收处理：删除称号
	def _doRecv_DelTitle(data)
		wId = ByteUtil::readUINT16(data)
		return onRecv_DelTitle(wId)
	end

#以下为返回处理函数
	#返回处理：得到当前所有称号
	def _doReturn_GetAllTitle(data)
		retParam = SRetParam_GetAllTitle.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecTitle = STitle::vectorFromStream(data) #(STitle的数组)当前所有称号
		retParam.vecTitle = vecTitle
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAllTitle(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：得到当前所有称号
	def _onTimeOut_GetAllTitle(sessionID)
		retParam = SRetParam_GetAllTitle.new;
		onReturn_GetAllTitle(2, retParam)
	end

	#返回处理：刷新称号列表
	def _doReturn_EquipTitle(data)
		retParam = SRetParam_EquipTitle.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETitleResult)操作结果
		wId = ByteUtil::readUINT16(data) #(UINT16)称号ID
		byPos = ByteUtil::readUINT8(data) #(UINT8)装备位置
		retParam.eResult = eResult
		retParam.wId = wId
		retParam.byPos = byPos
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_EquipTitle(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：刷新称号列表
	def _onTimeOut_EquipTitle(sessionID)
		retParam = SRetParam_EquipTitle.new;
		onReturn_EquipTitle(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 54;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_AddTitle' #FuncID: 1
		@recvFuncList[1] = '_doRecv_DelTitle' #FuncID: 2

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetAllTitle' #FuncID: 1
		@retFuncList[1] = '_doReturn_EquipTitle' #FuncID: 2

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetAllTitle' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_EquipTitle' #FuncID: 2
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

