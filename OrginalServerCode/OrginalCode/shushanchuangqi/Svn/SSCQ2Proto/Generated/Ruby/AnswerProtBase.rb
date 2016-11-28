#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    AnswerProt.rb
#  Purpose:      答题协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#答题操作结果
class EAnswerResult
	EANSWERRESULT_SUC = 0#操作成功
	EANSWERRESULT_LACK = 1#技能使用完
	EANSWERRESULT_NO = 2#技能无法使用
	EANSWERRESULT_ERR = 3#操作失败
end

#答题技能
class EAnswerSkill
	EANSWERSKILL_NONE = 0#无技能
	EANSWERSKILL_1 = 1#仙人之路
	EANSWERSKILL_2 = 2#天官赐福
	EANSWERSKILL_3 = 3#驱散迷雾
	EANSWERSKILL_END = 4#最大值
end

#答题时间控制
class SAnswerTime
	attr_accessor:dwReadTime #(UINT32)玩家阅读时间
	attr_accessor:dwAnswerTime #(UINT32)玩家答题时间
	attr_accessor:dwResultTime #(UINT32)玩家显示结果时间
	attr_accessor:dwEndTime #(UINT32)玩家答题结束时间

	#构造函数
	def initialize
		@dwReadTime = 0
		@dwAnswerTime = 0
		@dwResultTime = 0
		@dwEndTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwReadTime = @dwReadTime
		obj.dwAnswerTime = @dwAnswerTime
		obj.dwResultTime = @dwResultTime
		obj.dwEndTime = @dwEndTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SAnswerTime.new
		s.dwReadTime = ByteUtil::readUINT32(data)
		s.dwAnswerTime = ByteUtil::readUINT32(data)
		s.dwResultTime = ByteUtil::readUINT32(data)
		s.dwEndTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SAnswerTime::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwReadTime)
		ByteUtil::writeUINT32(data, @dwAnswerTime)
		ByteUtil::writeUINT32(data, @dwResultTime)
		ByteUtil::writeUINT32(data, @dwEndTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#答题技能信息
class SAnswerSkill
	attr_accessor:eSkillType #(枚举类型：EAnswerSkill)技能ID
	attr_accessor:byRemain #(UINT8)剩余次数

	#构造函数
	def initialize
		@eSkillType = 0
		@byRemain = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eSkillType = @eSkillType
		obj.byRemain = @byRemain
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SAnswerSkill.new
		s.eSkillType = ByteUtil::readUINT8(data)
		s.byRemain = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SAnswerSkill::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eSkillType)
		ByteUtil::writeUINT8(data, @byRemain)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#答题题目信息
class SAnswerTopic
	attr_accessor:byIndex #(UINT8)编号
	attr_accessor:dwTopicID #(UINT32)题目ID
	attr_accessor:byAnswer1 #(UINT8)答案1
	attr_accessor:byAnswer2 #(UINT8)答案2
	attr_accessor:byAnswer3 #(UINT8)答案3
	attr_accessor:byAnswer4 #(UINT8)答案4
	attr_accessor:sTimeInfo #(类类型：SAnswerTime)题目时间
	attr_accessor:dwRemain #(UINT32)剩余题目数

	#构造函数
	def initialize
		@byIndex = 0
		@dwTopicID = 0
		@byAnswer1 = 0
		@byAnswer2 = 0
		@byAnswer3 = 0
		@byAnswer4 = 0
		@sTimeInfo = SAnswerTime.new
		@dwRemain = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byIndex = @byIndex
		obj.dwTopicID = @dwTopicID
		obj.byAnswer1 = @byAnswer1
		obj.byAnswer2 = @byAnswer2
		obj.byAnswer3 = @byAnswer3
		obj.byAnswer4 = @byAnswer4
		obj.sTimeInfo = @sTimeInfo
		obj.dwRemain = @dwRemain
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SAnswerTopic.new
		s.byIndex = ByteUtil::readUINT8(data)
		s.dwTopicID = ByteUtil::readUINT32(data)
		s.byAnswer1 = ByteUtil::readUINT8(data)
		s.byAnswer2 = ByteUtil::readUINT8(data)
		s.byAnswer3 = ByteUtil::readUINT8(data)
		s.byAnswer4 = ByteUtil::readUINT8(data)
		s.sTimeInfo = SAnswerTime::fromStream(data)
		s.dwRemain = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SAnswerTopic::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byIndex)
		ByteUtil::writeUINT32(data, @dwTopicID)
		ByteUtil::writeUINT8(data, @byAnswer1)
		ByteUtil::writeUINT8(data, @byAnswer2)
		ByteUtil::writeUINT8(data, @byAnswer3)
		ByteUtil::writeUINT8(data, @byAnswer4)
		@sTimeInfo.toStream(data)
		ByteUtil::writeUINT32(data, @dwRemain)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家信息
class SAnswerPlayer
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:bRight #(bool)本次答题是否正确
	attr_accessor:dwThisScore #(UINT32)本题玩家获得积分
	attr_accessor:dwScore #(UINT32)玩家积分
	attr_accessor:dwRank #(UINT32)玩家排名
	attr_accessor:dwRight #(UINT32)玩家答对题目数
	attr_accessor:dwUntilFail #(UINT32)连续答对题目数
	attr_accessor:vecSkillInfo #(SAnswerSkill的数组)技能信息

	#构造函数
	def initialize
		@qwRoleID = 0
		@bRight = false
		@dwThisScore = 0
		@dwScore = 0
		@dwRank = 0
		@dwRight = 0
		@dwUntilFail = 0
		@vecSkillInfo = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.bRight = @bRight
		obj.dwThisScore = @dwThisScore
		obj.dwScore = @dwScore
		obj.dwRank = @dwRank
		obj.dwRight = @dwRight
		obj.dwUntilFail = @dwUntilFail
		obj.vecSkillInfo = @vecSkillInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SAnswerPlayer.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.bRight = ByteUtil::readBOOL(data)
		s.dwThisScore = ByteUtil::readUINT32(data)
		s.dwScore = ByteUtil::readUINT32(data)
		s.dwRank = ByteUtil::readUINT32(data)
		s.dwRight = ByteUtil::readUINT32(data)
		s.dwUntilFail = ByteUtil::readUINT32(data)
		s.vecSkillInfo = SAnswerSkill::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SAnswerPlayer::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeBOOL(data, @bRight)
		ByteUtil::writeUINT32(data, @dwThisScore)
		ByteUtil::writeUINT32(data, @dwScore)
		ByteUtil::writeUINT32(data, @dwRank)
		ByteUtil::writeUINT32(data, @dwRight)
		ByteUtil::writeUINT32(data, @dwUntilFail)
		SAnswerSkill::vectorToStream(data, @vecSkillInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#排名信息
class SAnswerRank
	attr_accessor:dwRank #(UINT32)玩家排名
	attr_accessor:strName #(string)玩家名字
	attr_accessor:dwScore #(UINT32)玩家积分

	#构造函数
	def initialize
		@dwRank = 0
		@strName = ''
		@dwScore = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwRank = @dwRank
		obj.strName = @strName
		obj.dwScore = @dwScore
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SAnswerRank.new
		s.dwRank = ByteUtil::readUINT32(data)
		s.strName = ByteUtil::readSTRING(data)
		s.dwScore = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SAnswerRank::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwRank)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT32(data, @dwScore)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetCoutdown:获取活动开始倒计时]的返回的参数组成的结构体
class SRetParam_GetCoutdown
	attr_accessor:dwTime#(UINT32)倒计时时间
	attr_accessor:sPlayerInfo#(类类型：SAnswerPlayer)玩家信息
	attr_accessor:bRet#(bool)是否开启面板

	#构造函数
	def initialize
		@dwTime = 0
		@sPlayerInfo = SAnswerPlayer.new
		@bRet = false
	end
end

#函数[Answer:玩家答题]的返回的参数组成的结构体
class SRetParam_Answer
	attr_accessor:dwIndex#(UINT32)题目
	attr_accessor:eResult#(枚举类型：EAnswerResult)答题结果返回

	#构造函数
	def initialize
		@dwIndex = 0
		@eResult = 0
	end
end

#函数[UseSkill:玩家使用技能]的返回的参数组成的结构体
class SRetParam_UseSkill
	attr_accessor:eSkillTypeRet#(枚举类型：EAnswerSkill)技能ID
	attr_accessor:byAnswer1#(UINT8)答案1
	attr_accessor:byAnswer2#(UINT8)答案2
	attr_accessor:eResult#(枚举类型：EAnswerResult)结果

	#构造函数
	def initialize
		@eSkillTypeRet = 0
		@byAnswer1 = 0
		@byAnswer2 = 0
		@eResult = 0
	end
end

#协议类：答题协议
class AnswerProtBase < ProtocolBase
	#以下为发送函数
	#发送：玩家报名
	def send_Join(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家离开
	def send_Leave(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取活动开始倒计时
	def send_GetCoutdown(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家答题
	def send_Answer(
		byAnswerID #(UINT8)玩家选择答案
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byAnswerID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家使用技能
	def send_UseSkill(
		eSkillType #(枚举类型：EAnswerSkill)技能ID
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eSkillType)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：答题预告
	def onRecv_AnswerAlarm(
		dwTime #(UINT32)时间
	)
		raise NotImplementedError
	end
	#接收：答题开始倒计时30秒通知
	def onRecv_AnswerCountdown(
		dwTime #(UINT32)时间
	)
		raise NotImplementedError
	end
	#接收：答题开始
	def onRecv_AnswerBegin(
		dwTime #(UINT32)时间
	)
		raise NotImplementedError
	end
	#接收：答题结束
	def onRecv_AnswerEnd(
		dwTime #(UINT32)时间
	)
		raise NotImplementedError
	end
	#接收：发送题目
	def onRecv_SendTopic(
		sTopic #(类类型：SAnswerTopic)题目信息
	)
		raise NotImplementedError
	end
	#接收：答完一题信息发送
	def onRecv_SendAnswerInfo(
		sPlayerInfo, #(类类型：SAnswerPlayer)玩家信息
		vecRankInfo #(SAnswerRank的数组)排名列表
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取活动开始倒计时
	def onReturn_GetCoutdown(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetCoutdown)返回的参数
	)
	end

	#返回：玩家答题
	def onReturn_Answer(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Answer)返回的参数
	)
	end

	#返回：玩家使用技能
	def onReturn_UseSkill(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UseSkill)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：答题预告
	def _doRecv_AnswerAlarm(data)
		dwTime = ByteUtil::readUINT32(data)
		return onRecv_AnswerAlarm(dwTime)
	end

	#接收处理：答题开始倒计时30秒通知
	def _doRecv_AnswerCountdown(data)
		dwTime = ByteUtil::readUINT32(data)
		return onRecv_AnswerCountdown(dwTime)
	end

	#接收处理：答题开始
	def _doRecv_AnswerBegin(data)
		dwTime = ByteUtil::readUINT32(data)
		return onRecv_AnswerBegin(dwTime)
	end

	#接收处理：答题结束
	def _doRecv_AnswerEnd(data)
		dwTime = ByteUtil::readUINT32(data)
		return onRecv_AnswerEnd(dwTime)
	end

	#接收处理：发送题目
	def _doRecv_SendTopic(data)
		sTopic = SAnswerTopic::fromStream(data)
		return onRecv_SendTopic(sTopic)
	end

	#接收处理：答完一题信息发送
	def _doRecv_SendAnswerInfo(data)
		sPlayerInfo = SAnswerPlayer::fromStream(data)
		vecRankInfo = SAnswerRank::vectorFromStream(data)
		return onRecv_SendAnswerInfo(sPlayerInfo, vecRankInfo)
	end

#以下为返回处理函数
	#返回处理：获取活动开始倒计时
	def _doReturn_GetCoutdown(data)
		retParam = SRetParam_GetCoutdown.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwTime = ByteUtil::readUINT32(data) #(UINT32)倒计时时间
		sPlayerInfo = SAnswerPlayer::fromStream(data) #(类类型：SAnswerPlayer)玩家信息
		bRet = ByteUtil::readBOOL(data) #(bool)是否开启面板
		retParam.dwTime = dwTime
		retParam.sPlayerInfo = sPlayerInfo
		retParam.bRet = bRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetCoutdown(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取活动开始倒计时
	def _onTimeOut_GetCoutdown(sessionID)
		retParam = SRetParam_GetCoutdown.new;
		onReturn_GetCoutdown(2, retParam)
	end

	#返回处理：玩家答题
	def _doReturn_Answer(data)
		retParam = SRetParam_Answer.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwIndex = ByteUtil::readUINT32(data) #(UINT32)题目
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EAnswerResult)答题结果返回
		retParam.dwIndex = dwIndex
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_Answer(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：玩家答题
	def _onTimeOut_Answer(sessionID)
		retParam = SRetParam_Answer.new;
		onReturn_Answer(2, retParam)
	end

	#返回处理：玩家使用技能
	def _doReturn_UseSkill(data)
		retParam = SRetParam_UseSkill.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eSkillTypeRet = ByteUtil::readUINT8(data) #(枚举类型：EAnswerSkill)技能ID
		byAnswer1 = ByteUtil::readUINT8(data) #(UINT8)答案1
		byAnswer2 = ByteUtil::readUINT8(data) #(UINT8)答案2
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EAnswerResult)结果
		retParam.eSkillTypeRet = eSkillTypeRet
		retParam.byAnswer1 = byAnswer1
		retParam.byAnswer2 = byAnswer2
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UseSkill(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：玩家使用技能
	def _onTimeOut_UseSkill(sessionID)
		retParam = SRetParam_UseSkill.new;
		onReturn_UseSkill(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 95;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_AnswerAlarm' #FuncID: 1
		@recvFuncList[1] = '_doRecv_AnswerCountdown' #FuncID: 2
		@recvFuncList[2] = '_doRecv_AnswerBegin' #FuncID: 3
		@recvFuncList[3] = '_doRecv_AnswerEnd' #FuncID: 4
		@recvFuncList[4] = '_doRecv_SendTopic' #FuncID: 5
		@recvFuncList[5] = '_doRecv_SendAnswerInfo' #FuncID: 6

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetCoutdown' #FuncID: 1
		@retFuncList[1] = '_doReturn_Answer' #FuncID: 2
		@retFuncList[2] = '_doReturn_UseSkill' #FuncID: 3

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetCoutdown' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_Answer' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_UseSkill' #FuncID: 3
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

