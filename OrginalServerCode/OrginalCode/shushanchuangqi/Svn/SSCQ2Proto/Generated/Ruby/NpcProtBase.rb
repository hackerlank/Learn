#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    NpcProt.rb
#  Purpose:      NPC相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './TaskProtBase.rb'

#以下为类型定义

#NPC对话结果
class ETalkResult
	ETALKSUCCEED = 0#打开对话成功
	ETALKNOTEXIST = 1#NPC不存在
	ETALKTOOFAR = 2#玩家距离NPC太远
	ETALKSCRIPTFAIL = 3#NPC对话脚本执行失败
	ETALKOTHER = 4#其它错误
end

#NPC的任务状态
class SNpcTaskState
	attr_accessor:wNpcID #(UINT16)NPC的ID
	attr_accessor:eNpcTaskState #(枚类型：TaskProt::ENpcTaskState)任务状态

	#构造函数
	def initialize
		@wNpcID = 0
		@eNpcTaskState = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wNpcID = @wNpcID
		obj.eNpcTaskState = @eNpcTaskState
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SNpcTaskState.new
		s.wNpcID = ByteUtil::readUINT16(data)
		s.eNpcTaskState = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SNpcTaskState::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wNpcID)
		ByteUtil::writeUINT8(data, @eNpcTaskState)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[FinishTaskTalk:完成一任务对话]的返回的参数组成的结构体
class SRetParam_FinishTaskTalk
	attr_accessor:strContent#(string)对话内容

	#构造函数
	def initialize
		@strContent = ''
	end
end

#协议类：NPC相关协议
class NpcProtBase < ProtocolBase
	#以下为发送函数
	#发送：打开NPC对话界面请求
	def send_NpcTalkReq(
		qwCreatureID #(UINT64)当前NPC的生物ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwCreatureID)
		return @svrHandler.sendPacket(data)
	end

	#发送：执行NPC对话脚本函数
	def send_ExecScriptFunc(
		qwCreatureID,  #(UINT64)当前NPC的生物ID
		strFuncName #(string)脚本函数名称
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwCreatureID)
		ByteUtil::writeSTRING(data, strFuncName)
		return @svrHandler.sendPacket(data)
	end

	#发送：地图的NPC任务状态请求
	def send_NpcTaskStateReq(
		wMapID #(UINT16)地图ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT16(data, wMapID)
		return @svrHandler.sendPacket(data)
	end

	#发送：完成一任务对话
	def send_FinishTaskTalk(
		qwCreatureID,  #(UINT64)当前NPC的生物ID
		wTaskID #(UINT16)对话的任务
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwCreatureID)
		ByteUtil::writeUINT16(data, wTaskID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：NPC对话通知
	def onRecv_NpcTalkNtf(
		qwCreatureID, #(UINT64)NPC的生物ID
		eResult, #(枚举类型：ETalkResult)对话结果
		strContent #(string)对话内容
	)
		raise NotImplementedError
	end
	#接收：NPC任务状态通知
	def onRecv_NpcTaskStateNtf(
		rVecNpcTask #(SNpcTaskState的数组)NPC任务状态列表
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：完成一任务对话
	def onReturn_FinishTaskTalk(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FinishTaskTalk)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：NPC对话通知
	def _doRecv_NpcTalkNtf(data)
		qwCreatureID = ByteUtil::readUINT64(data)
		eResult = ByteUtil::readUINT8(data)
		strContent = ByteUtil::readSTRING(data)
		return onRecv_NpcTalkNtf(qwCreatureID, eResult, strContent)
	end

	#接收处理：NPC任务状态通知
	def _doRecv_NpcTaskStateNtf(data)
		rVecNpcTask = SNpcTaskState::vectorFromStream(data)
		return onRecv_NpcTaskStateNtf(rVecNpcTask)
	end

#以下为返回处理函数
	#返回处理：完成一任务对话
	def _doReturn_FinishTaskTalk(data)
		retParam = SRetParam_FinishTaskTalk.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		strContent = ByteUtil::readSTRING(data) #(string)对话内容
		retParam.strContent = strContent
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FinishTaskTalk(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：完成一任务对话
	def _onTimeOut_FinishTaskTalk(sessionID)
		retParam = SRetParam_FinishTaskTalk.new;
		onReturn_FinishTaskTalk(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 14;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_NpcTalkNtf' #FuncID: 1
		@recvFuncList[1] = '_doRecv_NpcTaskStateNtf' #FuncID: 2

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_FinishTaskTalk' #FuncID: 1

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_FinishTaskTalk' #FuncID: 1
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

