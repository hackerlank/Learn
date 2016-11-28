#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    LangHuanBlessProt.rb
#  Purpose:      中午挂机活动
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#操作结果
class ELHBResult
	ELHBRESULT_NONE = 0#无此技能
	ELHBRESULT_EMPTY = 1#次数用完
	ELHBRESULT_INCD = 2#技能CD中
	ELHBRESULT_HASBUFF = 3#身上有Buff
	ELHBRESULT_SUCCESS = 4#操作成功
	ELHBRESULT_CMAPERROR = 5#创建地图失败
	ELHBRESULT_ENTERMAPERROR = 6#进入地图失败
	ELHBRESULT_OTHERERROR = 7#其他错误
	ELHBRESULT_LOWLEVEL = 8#玩家等级不够
	ELHBRESULT_NOTBEGIN = 9#活动未开始
	ELHBRESULT_END = 10#玩家已经结束
	ELHBRESULT_WAIT5MIN = 11#玩家逃跑需要等待5分钟
end

#活动状态
class ELHBState
	ELHBSTATE_NONE = 0#无状态
	ELHBSTATE_ALARM = 1#警告
	ELHBSTATE_READY = 2#报名开始
	ELHBSTATE_BEGIN = 3#活动开始
	ELHBSTATE_END = 4#活动结束
end

#技能类型
class ELHBSkillType
	ELHBSKILLTYPE_ENONE = 0#无技能
	ELHBSKILLTYPE_EASKTAOISM = 1#问道技能
	ELHBSKILLTYPE_ETALKTAOISM = 2#论道技能
	ELHBSKILLTYPE_EWANDER = 3#开小差技能
	ELHBSKILLTYPE_ESIT = 4#打坐技能
	ELHBSKILLTYPE_MAX = 5#技能最大值
end

#技能信息
class SLHBSkillInfo
	attr_accessor:eLHBSkillType #(枚举类型：ELHBSkillType)技能类型
	attr_accessor:byCD #(UINT8)技能CD
	attr_accessor:wScore #(UINT32)修为值
	attr_accessor:byTimes #(UINT8)使用次数

	#构造函数
	def initialize
		@eLHBSkillType = 0
		@byCD = 0
		@wScore = 0
		@byTimes = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eLHBSkillType = @eLHBSkillType
		obj.byCD = @byCD
		obj.wScore = @wScore
		obj.byTimes = @byTimes
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SLHBSkillInfo.new
		s.eLHBSkillType = ByteUtil::readUINT8(data)
		s.byCD = ByteUtil::readUINT8(data)
		s.wScore = ByteUtil::readUINT32(data)
		s.byTimes = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SLHBSkillInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eLHBSkillType)
		ByteUtil::writeUINT8(data, @byCD)
		ByteUtil::writeUINT32(data, @wScore)
		ByteUtil::writeUINT8(data, @byTimes)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#总的信息
class SLHBTotalInfo
	attr_accessor:byState #(枚举类型：ELHBState)活动状态
	attr_accessor:dwTime #(UINT32)玩家持续时间
	attr_accessor:dwXiuwei #(UINT32)获得的修为值
	attr_accessor:dwExp #(UINT32)获得的经验值
	attr_accessor:vecLHBSkillInfo #(SLHBSkillInfo的数组)技能使用信息

	#构造函数
	def initialize
		@byState = 0
		@dwTime = 0
		@dwXiuwei = 0
		@dwExp = 0
		@vecLHBSkillInfo = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byState = @byState
		obj.dwTime = @dwTime
		obj.dwXiuwei = @dwXiuwei
		obj.dwExp = @dwExp
		obj.vecLHBSkillInfo = @vecLHBSkillInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SLHBTotalInfo.new
		s.byState = ByteUtil::readUINT8(data)
		s.dwTime = ByteUtil::readUINT32(data)
		s.dwXiuwei = ByteUtil::readUINT32(data)
		s.dwExp = ByteUtil::readUINT32(data)
		s.vecLHBSkillInfo = SLHBSkillInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SLHBTotalInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byState)
		ByteUtil::writeUINT32(data, @dwTime)
		ByteUtil::writeUINT32(data, @dwXiuwei)
		ByteUtil::writeUINT32(data, @dwExp)
		SLHBSkillInfo::vectorToStream(data, @vecLHBSkillInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[EnterMap:进入LangHuanBless地图]的返回的参数组成的结构体
class SRetParam_EnterMap
	attr_accessor:eLHBResult#(枚举类型：ELHBResult)结果

	#构造函数
	def initialize
		@eLHBResult = 0
	end
end

#函数[SelectSkill:选择问道]的返回的参数组成的结构体
class SRetParam_SelectSkill
	attr_accessor:eRetLHBSkillType#(枚举类型：ELHBSkillType)返回使用技能
	attr_accessor:eLHBResult#(枚举类型：ELHBResult)结果

	#构造函数
	def initialize
		@eRetLHBSkillType = 0
		@eLHBResult = 0
	end
end

#函数[GetScore:获得的修为值]的返回的参数组成的结构体
class SRetParam_GetScore
	attr_accessor:wScore#(UINT32)修为值

	#构造函数
	def initialize
		@wScore = 0
	end
end

#函数[GetSustainTime:获得游戏中持续时间]的返回的参数组成的结构体
class SRetParam_GetSustainTime
	attr_accessor:dwTime#(UINT32)时间值

	#构造函数
	def initialize
		@dwTime = 0
	end
end

#函数[GetTotalInfo:获得玩家所有信息]的返回的参数组成的结构体
class SRetParam_GetTotalInfo
	attr_accessor:sTotalInfo#(类类型：SLHBTotalInfo)时间值
	attr_accessor:bRet#(bool)结果

	#构造函数
	def initialize
		@sTotalInfo = SLHBTotalInfo.new
		@bRet = false
	end
end

#函数[GetSkillInfo:获得技能使用信息]的返回的参数组成的结构体
class SRetParam_GetSkillInfo
	attr_accessor:vecLHBSkillInfo#(SLHBSkillInfo的数组)技能使用信息
	attr_accessor:eLHBResult#(枚举类型：ELHBResult)结果

	#构造函数
	def initialize
		@vecLHBSkillInfo = Array.new
		@eLHBResult = 0
	end
end

#函数[LeaveMap:离开LangHuanBless地图]的返回的参数组成的结构体
class SRetParam_LeaveMap
	attr_accessor:eLHBResult#(枚举类型：ELHBResult)结果

	#构造函数
	def initialize
		@eLHBResult = 0
	end
end

#协议类：中午挂机活动
class LangHuanBlessProtBase < ProtocolBase
	#以下为发送函数
	#发送：进入LangHuanBless地图
	def send_EnterMap(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：选择问道
	def send_SelectSkill(
		qwPlayerID,  #(UINT64)被选择的玩家
		eLHBSkillType #(枚举类型：ELHBSkillType)技能类型
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwPlayerID)
		ByteUtil::writeUINT8(data, eLHBSkillType)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得的修为值
	def send_GetScore(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得游戏中持续时间
	def send_GetSustainTime(
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得玩家所有信息
	def send_GetTotalInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得技能使用信息
	def send_GetSkillInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：离开LangHuanBless地图
	def send_LeaveMap(
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：挂机活动报名开始
	def onRecv_EnrollNotify(
		dwEnrollTime #(UINT32)开始时间
	)
		raise NotImplementedError
	end
	#接收：挂机活动开始
	def onRecv_BeginNotify(
		dwBeginTime #(UINT32)开始时间
	)
		raise NotImplementedError
	end
	#接收：发送经验值和修为值
	def onRecv_PrizeNotify(
		dwXiuwei, #(UINT32)修为值
		dwExp #(UINT32)经验值
	)
		raise NotImplementedError
	end
	#接收：发送玩家在副本中的信息
	def onRecv_TotalInfo(
		qwPlayerID, #(UINT64)玩家ID
		sTotalInfo #(类类型：SLHBTotalInfo)玩家信息
	)
		raise NotImplementedError
	end
	#接收：发送技能信息
	def onRecv_SkillInfo(
		qwAtkPlayerID, #(UINT64)攻击者
		qwDfePlayerID, #(UINT64)被攻击者
		eLHBSkillType #(枚举类型：ELHBSkillType)使用的技能ID
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：进入LangHuanBless地图
	def onReturn_EnterMap(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_EnterMap)返回的参数
	)
	end

	#返回：选择问道
	def onReturn_SelectSkill(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SelectSkill)返回的参数
	)
	end

	#返回：获得的修为值
	def onReturn_GetScore(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetScore)返回的参数
	)
	end

	#返回：获得游戏中持续时间
	def onReturn_GetSustainTime(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetSustainTime)返回的参数
	)
	end

	#返回：获得玩家所有信息
	def onReturn_GetTotalInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetTotalInfo)返回的参数
	)
	end

	#返回：获得技能使用信息
	def onReturn_GetSkillInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetSkillInfo)返回的参数
	)
	end

	#返回：离开LangHuanBless地图
	def onReturn_LeaveMap(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LeaveMap)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：挂机活动报名开始
	def _doRecv_EnrollNotify(data)
		dwEnrollTime = ByteUtil::readUINT32(data)
		return onRecv_EnrollNotify(dwEnrollTime)
	end

	#接收处理：挂机活动开始
	def _doRecv_BeginNotify(data)
		dwBeginTime = ByteUtil::readUINT32(data)
		return onRecv_BeginNotify(dwBeginTime)
	end

	#接收处理：发送经验值和修为值
	def _doRecv_PrizeNotify(data)
		dwXiuwei = ByteUtil::readUINT32(data)
		dwExp = ByteUtil::readUINT32(data)
		return onRecv_PrizeNotify(dwXiuwei, dwExp)
	end

	#接收处理：发送玩家在副本中的信息
	def _doRecv_TotalInfo(data)
		qwPlayerID = ByteUtil::readUINT64(data)
		sTotalInfo = SLHBTotalInfo::fromStream(data)
		return onRecv_TotalInfo(qwPlayerID, sTotalInfo)
	end

	#接收处理：发送技能信息
	def _doRecv_SkillInfo(data)
		qwAtkPlayerID = ByteUtil::readUINT64(data)
		qwDfePlayerID = ByteUtil::readUINT64(data)
		eLHBSkillType = ByteUtil::readUINT8(data)
		return onRecv_SkillInfo(qwAtkPlayerID, qwDfePlayerID, eLHBSkillType)
	end

#以下为返回处理函数
	#返回处理：进入LangHuanBless地图
	def _doReturn_EnterMap(data)
		retParam = SRetParam_EnterMap.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eLHBResult = ByteUtil::readUINT8(data) #(枚举类型：ELHBResult)结果
		retParam.eLHBResult = eLHBResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_EnterMap(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：进入LangHuanBless地图
	def _onTimeOut_EnterMap(sessionID)
		retParam = SRetParam_EnterMap.new;
		onReturn_EnterMap(2, retParam)
	end

	#返回处理：选择问道
	def _doReturn_SelectSkill(data)
		retParam = SRetParam_SelectSkill.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRetLHBSkillType = ByteUtil::readUINT8(data) #(枚举类型：ELHBSkillType)返回使用技能
		eLHBResult = ByteUtil::readUINT8(data) #(枚举类型：ELHBResult)结果
		retParam.eRetLHBSkillType = eRetLHBSkillType
		retParam.eLHBResult = eLHBResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SelectSkill(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：选择问道
	def _onTimeOut_SelectSkill(sessionID)
		retParam = SRetParam_SelectSkill.new;
		onReturn_SelectSkill(2, retParam)
	end

	#返回处理：获得的修为值
	def _doReturn_GetScore(data)
		retParam = SRetParam_GetScore.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		wScore = ByteUtil::readUINT32(data) #(UINT32)修为值
		retParam.wScore = wScore
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetScore(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获得的修为值
	def _onTimeOut_GetScore(sessionID)
		retParam = SRetParam_GetScore.new;
		onReturn_GetScore(2, retParam)
	end

	#返回处理：获得游戏中持续时间
	def _doReturn_GetSustainTime(data)
		retParam = SRetParam_GetSustainTime.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwTime = ByteUtil::readUINT32(data) #(UINT32)时间值
		retParam.dwTime = dwTime
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetSustainTime(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获得游戏中持续时间
	def _onTimeOut_GetSustainTime(sessionID)
		retParam = SRetParam_GetSustainTime.new;
		onReturn_GetSustainTime(2, retParam)
	end

	#返回处理：获得玩家所有信息
	def _doReturn_GetTotalInfo(data)
		retParam = SRetParam_GetTotalInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		sTotalInfo = SLHBTotalInfo::fromStream(data) #(类类型：SLHBTotalInfo)时间值
		bRet = ByteUtil::readBOOL(data) #(bool)结果
		retParam.sTotalInfo = sTotalInfo
		retParam.bRet = bRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetTotalInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获得玩家所有信息
	def _onTimeOut_GetTotalInfo(sessionID)
		retParam = SRetParam_GetTotalInfo.new;
		onReturn_GetTotalInfo(2, retParam)
	end

	#返回处理：获得技能使用信息
	def _doReturn_GetSkillInfo(data)
		retParam = SRetParam_GetSkillInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecLHBSkillInfo = SLHBSkillInfo::vectorFromStream(data) #(SLHBSkillInfo的数组)技能使用信息
		eLHBResult = ByteUtil::readUINT8(data) #(枚举类型：ELHBResult)结果
		retParam.vecLHBSkillInfo = vecLHBSkillInfo
		retParam.eLHBResult = eLHBResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetSkillInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获得技能使用信息
	def _onTimeOut_GetSkillInfo(sessionID)
		retParam = SRetParam_GetSkillInfo.new;
		onReturn_GetSkillInfo(2, retParam)
	end

	#返回处理：离开LangHuanBless地图
	def _doReturn_LeaveMap(data)
		retParam = SRetParam_LeaveMap.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eLHBResult = ByteUtil::readUINT8(data) #(枚举类型：ELHBResult)结果
		retParam.eLHBResult = eLHBResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LeaveMap(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：离开LangHuanBless地图
	def _onTimeOut_LeaveMap(sessionID)
		retParam = SRetParam_LeaveMap.new;
		onReturn_LeaveMap(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 79;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_EnrollNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_BeginNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_PrizeNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_TotalInfo' #FuncID: 4
		@recvFuncList[4] = '_doRecv_SkillInfo' #FuncID: 5

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_EnterMap' #FuncID: 1
		@retFuncList[1] = '_doReturn_SelectSkill' #FuncID: 2
		@retFuncList[2] = '_doReturn_GetScore' #FuncID: 3
		@retFuncList[3] = '_doReturn_GetSustainTime' #FuncID: 4
		@retFuncList[4] = '_doReturn_GetTotalInfo' #FuncID: 5
		@retFuncList[5] = '_doReturn_GetSkillInfo' #FuncID: 6
		@retFuncList[6] = '_doReturn_LeaveMap' #FuncID: 7

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_EnterMap' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_SelectSkill' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GetScore' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_GetSustainTime' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_GetTotalInfo' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_GetSkillInfo' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_LeaveMap' #FuncID: 7
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

