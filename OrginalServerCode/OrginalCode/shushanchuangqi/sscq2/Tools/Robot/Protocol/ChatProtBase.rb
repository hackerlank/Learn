#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    ChatProt.rb
#  Purpose:      聊天协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './GlobalChatProtBase.rb'
require_relative './ProtoCommonBase.rb'
require_relative './RoleInfoDefineBase.rb'

#以下为类型定义

#聊天结果提示
class EChatResult
	ECHATSUCCEED = 0#成功
	ECHATNOTEXIST = 1#展示道具不存在
	ECHATERRSTORE = 2#容器错误
	ECHATERROTHER = 3#其他错误
end

#气泡操作失败
class EBubbleResult
	EBRSUCCESS = 0#气泡操作成功
	EBRFAILED = 1#气泡操作失败
end

#函数[BubbleGet:气泡信息获取]的返回的参数组成的结构体
class SRetParam_BubbleGet
	attr_accessor:vecBubbleInfo#(SBubbleInfo的数组)气泡列表信息

	#构造函数
	def initialize
		@vecBubbleInfo = Array.new
	end
end

#函数[BubbleRespond:气泡回应]的返回的参数组成的结构体
class SRetParam_BubbleRespond
	attr_accessor:eResult#(枚举类型：EBubbleResult)气泡操作返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：聊天协议
class ChatProtBase < ProtocolBase
	#以下为发送函数
	#发送：聊天
	def send_Chat(
		eChannelType,  #(枚类型：GlobalChatProt::EChannelType)通道类型
		strInfo,  #(string)聊天信息
		vecShowInfo #(SShowInfo的数组)炫耀物品信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eChannelType)
		ByteUtil::writeSTRING(data, strInfo)
		SShowInfo::vectorToStream(data, vecShowInfo)
		return @svrHandler.sendPacket(data)
	end

	#发送：气泡信息获取
	def send_BubbleGet(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：气泡回应
	def send_BubbleRespond(
		wIndex,  #(UINT16)气泡对应位置
		vecParam,  #(INT64数组)整型变量
		vecString #(string数组)字符串型变量
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wIndex)
		ByteUtil::writeVecINT64(data, vecParam)
		ByteUtil::writeVecSTRING(data, vecString)
		return @svrHandler.sendPacket(data)
	end

	#发送：邀请平台好友成功
	def send_InviteSuc(
		qwRoleID #(UINT64)被邀请人
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：聊天信息通知
	def onRecv_ChatInfoNotify(
		eChannelType, #(枚类型：GlobalChatProt::EChannelType)通道类型
		rSenderInfo, #(类类型：GlobalChatProt::SSenderInfo)发送者信息
		strInfo, #(string)聊天信息
		vecShowInfo #(SShowInfo的数组)炫耀物品信息
	)
		raise NotImplementedError
	end
	#接收：系统信息通知
	def onRecv_SystemMsgNotify(
		eChannelType, #(枚类型：GlobalChatProt::EChannelType)通道类型
		strInfo, #(string)聊天信息
		eSubType #(枚类型：GlobalChatProt::EChannelSubType)额外信息
	)
		raise NotImplementedError
	end
	#接收：系统MsgID通知
	def onRecv_SystemMsgIDNotify(
		wMsgID #(UINT16)消息ID
	)
		raise NotImplementedError
	end
	#接收：弹窗通知
	def onRecv_ElasticFrameNotify(
		wMsgID #(UINT16)消息ID
	)
		raise NotImplementedError
	end
	#接收：系统MsgID通知
	def onRecv_SystemFormatMsgIDNotify(
		wMsgID, #(UINT16)消息ID
		vecStr #(string数组)聊天信息参数
	)
		raise NotImplementedError
	end
	#接收：气泡提示信息
	def onRecv_BubbleNotify(
		vecBubbleInfo #(SBubbleInfo的数组)气泡列表信息
	)
		raise NotImplementedError
	end
	#接收：气泡提示信息更新
	def onRecv_BubbleUpdate(
		eType, #(枚类型：ProtoCommon::EDataChange)更新类型，增加，删除，修改
		sBubbleInfo #(类类型：RoleInfoDefine::SBubbleInfo)受影响的气泡信息
	)
		raise NotImplementedError
	end
	#接收：系统MsgID通知
	def onRecv_SystemFormatMsgIDNotifyWithShow(
		wMsgID, #(UINT16)消息ID
		vecStr, #(string数组)聊天信息参数
		vecShow #(SShowInfo的数组)炫耀信息
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：气泡信息获取
	def onReturn_BubbleGet(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BubbleGet)返回的参数
	)
	end

	#返回：气泡回应
	def onReturn_BubbleRespond(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BubbleRespond)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：聊天信息通知
	def _doRecv_ChatInfoNotify(data)
		eChannelType = ByteUtil::readUINT8(data)
		rSenderInfo = SSenderInfo::fromStream(data)
		strInfo = ByteUtil::readSTRING(data)
		vecShowInfo = SShowInfo::vectorFromStream(data)
		return onRecv_ChatInfoNotify(eChannelType, rSenderInfo, strInfo, vecShowInfo)
	end

	#接收处理：系统信息通知
	def _doRecv_SystemMsgNotify(data)
		eChannelType = ByteUtil::readUINT8(data)
		strInfo = ByteUtil::readSTRING(data)
		eSubType = ByteUtil::readUINT8(data)
		return onRecv_SystemMsgNotify(eChannelType, strInfo, eSubType)
	end

	#接收处理：系统MsgID通知
	def _doRecv_SystemMsgIDNotify(data)
		wMsgID = ByteUtil::readUINT16(data)
		return onRecv_SystemMsgIDNotify(wMsgID)
	end

	#接收处理：弹窗通知
	def _doRecv_ElasticFrameNotify(data)
		wMsgID = ByteUtil::readUINT16(data)
		return onRecv_ElasticFrameNotify(wMsgID)
	end

	#接收处理：系统MsgID通知
	def _doRecv_SystemFormatMsgIDNotify(data)
		wMsgID = ByteUtil::readUINT16(data)
		vecStr = ByteUtil::readVecSTRING(data)
		return onRecv_SystemFormatMsgIDNotify(wMsgID, vecStr)
	end

	#接收处理：气泡提示信息
	def _doRecv_BubbleNotify(data)
		vecBubbleInfo = SBubbleInfo::vectorFromStream(data)
		return onRecv_BubbleNotify(vecBubbleInfo)
	end

	#接收处理：气泡提示信息更新
	def _doRecv_BubbleUpdate(data)
		eType = ByteUtil::readUINT8(data)
		sBubbleInfo = SBubbleInfo::fromStream(data)
		return onRecv_BubbleUpdate(eType, sBubbleInfo)
	end

	#接收处理：系统MsgID通知
	def _doRecv_SystemFormatMsgIDNotifyWithShow(data)
		wMsgID = ByteUtil::readUINT16(data)
		vecStr = ByteUtil::readVecSTRING(data)
		vecShow = SShowInfo::vectorFromStream(data)
		return onRecv_SystemFormatMsgIDNotifyWithShow(wMsgID, vecStr, vecShow)
	end

#以下为返回处理函数
	#返回处理：气泡信息获取
	def _doReturn_BubbleGet(data)
		retParam = SRetParam_BubbleGet.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecBubbleInfo = SBubbleInfo::vectorFromStream(data) #(SBubbleInfo的数组)气泡列表信息
		retParam.vecBubbleInfo = vecBubbleInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BubbleGet(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：气泡信息获取
	def _onTimeOut_BubbleGet(sessionID)
		retParam = SRetParam_BubbleGet.new;
		onReturn_BubbleGet(2, retParam)
	end

	#返回处理：气泡回应
	def _doReturn_BubbleRespond(data)
		retParam = SRetParam_BubbleRespond.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EBubbleResult)气泡操作返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BubbleRespond(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：气泡回应
	def _onTimeOut_BubbleRespond(sessionID)
		retParam = SRetParam_BubbleRespond.new;
		onReturn_BubbleRespond(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 23;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_ChatInfoNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_SystemMsgNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_SystemMsgIDNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_ElasticFrameNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_SystemFormatMsgIDNotify' #FuncID: 5
		@recvFuncList[5] = '_doRecv_BubbleNotify' #FuncID: 6
		@recvFuncList[6] = '_doRecv_BubbleUpdate' #FuncID: 7
		@recvFuncList[7] = '_doRecv_SystemFormatMsgIDNotifyWithShow' #FuncID: 8

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_BubbleGet' #FuncID: 1
		@retFuncList[1] = '_doReturn_BubbleRespond' #FuncID: 2

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_BubbleGet' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_BubbleRespond' #FuncID: 2
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

