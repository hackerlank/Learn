#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    AchievementProt.rb
#  Purpose:      成就相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#成就完成进度
class EAchievementRet
	EACHIEVEMENTRET_SUCESS = 0#成功
	EACHIEVEMENTRET_NOTFINISH = 1#未完成
	EACHIEVEMENTRET_TAKEPRIZED = 2#已领奖
	EACHIEVEMENTRET_ERRORCFG = 3#配置错误
	EACHIEVEMENTRET_PACKFULL = 4#包满
end

#成就完成进度
class EAchievementProcess
	EACHIEVEMENTPROCESS_INIT = 0#未完成
	EACHIEVEMENTPROCESS_FINISH = 1#已完成
	EACHIEVEMENTPROCESS_TAKEPRIZE = 2#已领奖
end

#成就分享类型
class EAchievementShareType
	EACHIEVEMENTSHARETYPE_INVALID = 0#无效类型
	EACHIEVEMENTSHARETYPE_FRIEND = 1#qq好友分享
	EACHIEVEMENTSHARETYPE_GAME = 2#游戏内炫耀
end

#EDataType:eTypeAchievementInfo
class SAchievementInfo
	attr_accessor:qwRoleID #(UINT64)角色ID
	attr_accessor:wAchievementID #(UINT16)成就ID
	attr_accessor:dwCount #(UINT32)EAchievementProcess类型成就完成进度
	attr_accessor:dwProcess #(UINT32)当前进度(持续型事件记录数据)
	attr_accessor:dwFinishTime #(UINT32)完成时间

	#构造函数
	def initialize
		@qwRoleID = 0
		@wAchievementID = 0
		@dwCount = 0
		@dwProcess = 0
		@dwFinishTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wAchievementID = @wAchievementID
		obj.dwCount = @dwCount
		obj.dwProcess = @dwProcess
		obj.dwFinishTime = @dwFinishTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SAchievementInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wAchievementID = ByteUtil::readUINT16(data)
		s.dwCount = ByteUtil::readUINT32(data)
		s.dwProcess = ByteUtil::readUINT32(data)
		s.dwFinishTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SAchievementInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wAchievementID)
		ByteUtil::writeUINT32(data, @dwCount)
		ByteUtil::writeUINT32(data, @dwProcess)
		ByteUtil::writeUINT32(data, @dwFinishTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#成就分享列表
class SAchievementShare
	attr_accessor:wAchievementID #(UINT16)成就ID
	attr_accessor:eProcess #(枚举类型：EAchievementProcess)分享状态

	#构造函数
	def initialize
		@wAchievementID = 0
		@eProcess = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wAchievementID = @wAchievementID
		obj.eProcess = @eProcess
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SAchievementShare.new
		s.wAchievementID = ByteUtil::readUINT16(data)
		s.eProcess = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SAchievementShare::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wAchievementID)
		ByteUtil::writeUINT8(data, @eProcess)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GeAchievementInfo:获取成就信息]的返回的参数组成的结构体
class SRetParam_GeAchievementInfo
	attr_accessor:vecAchievementInfo#(SAchievementInfo的数组)成就榜信息
	attr_accessor:wLevel#(UINT16)成就等级
	attr_accessor:dwAP#(UINT32)成就点

	#构造函数
	def initialize
		@vecAchievementInfo = Array.new
		@wLevel = 0
		@dwAP = 0
	end
end

#函数[TakePrize:获取成就奖励]的返回的参数组成的结构体
class SRetParam_TakePrize
	attr_accessor:eRet#(枚举类型：EAchievementRet)结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#函数[GeAchievementShareList:获取成就分享信息]的返回的参数组成的结构体
class SRetParam_GeAchievementShareList
	attr_accessor:vecAchievementShare#(SAchievementShare的数组)成就分享信息

	#构造函数
	def initialize
		@vecAchievementShare = Array.new
	end
end

#函数[TakeSharePrize:获取成就分享奖励]的返回的参数组成的结构体
class SRetParam_TakeSharePrize
	attr_accessor:eRet#(枚举类型：EAchievementRet)结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#协议类：成就相关协议
class AchievementProtBase < ProtocolBase
	#以下为发送函数
	#发送：获取成就信息
	def send_GeAchievementInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取成就奖励
	def send_TakePrize(
		wAchievementID #(UINT16)成就ID
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wAchievementID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取成就分享信息
	def send_GeAchievementShareList(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取成就分享奖励
	def send_TakeSharePrize(
		wAchievementID #(UINT16)成就ID
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wAchievementID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：成就点通知
	def onRecv_APNotify(
		dwAP #(UINT32)成就点
	)
		raise NotImplementedError
	end
	#接收：成就等级通知
	def onRecv_AchievementLevelNotify(
		wLevel #(UINT16)成就等级
	)
		raise NotImplementedError
	end
	#接收：成就等级通知
	def onRecv_AchievementInfoNotify(
		oAchievementInfo #(类类型：SAchievementInfo)成就信息
	)
		raise NotImplementedError
	end
	#接收：成就分享通知
	def onRecv_AchievementShareNotify(
		oAchievementShare #(类类型：SAchievementShare)成就分享信息
	)
		raise NotImplementedError
	end
	#接收：零点通知
	def onRecv_MidnightNotify(
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取成就信息
	def onReturn_GeAchievementInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GeAchievementInfo)返回的参数
	)
	end

	#返回：获取成就奖励
	def onReturn_TakePrize(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakePrize)返回的参数
	)
	end

	#返回：获取成就分享信息
	def onReturn_GeAchievementShareList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GeAchievementShareList)返回的参数
	)
	end

	#返回：获取成就分享奖励
	def onReturn_TakeSharePrize(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakeSharePrize)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：成就点通知
	def _doRecv_APNotify(data)
		dwAP = ByteUtil::readUINT32(data)
		return onRecv_APNotify(dwAP)
	end

	#接收处理：成就等级通知
	def _doRecv_AchievementLevelNotify(data)
		wLevel = ByteUtil::readUINT16(data)
		return onRecv_AchievementLevelNotify(wLevel)
	end

	#接收处理：成就等级通知
	def _doRecv_AchievementInfoNotify(data)
		oAchievementInfo = SAchievementInfo::fromStream(data)
		return onRecv_AchievementInfoNotify(oAchievementInfo)
	end

	#接收处理：成就分享通知
	def _doRecv_AchievementShareNotify(data)
		oAchievementShare = SAchievementShare::fromStream(data)
		return onRecv_AchievementShareNotify(oAchievementShare)
	end

	#接收处理：零点通知
	def _doRecv_MidnightNotify(data)
		return onRecv_MidnightNotify()
	end

#以下为返回处理函数
	#返回处理：获取成就信息
	def _doReturn_GeAchievementInfo(data)
		retParam = SRetParam_GeAchievementInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecAchievementInfo = SAchievementInfo::vectorFromStream(data) #(SAchievementInfo的数组)成就榜信息
		wLevel = ByteUtil::readUINT16(data) #(UINT16)成就等级
		dwAP = ByteUtil::readUINT32(data) #(UINT32)成就点
		retParam.vecAchievementInfo = vecAchievementInfo
		retParam.wLevel = wLevel
		retParam.dwAP = dwAP
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GeAchievementInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取成就信息
	def _onTimeOut_GeAchievementInfo(sessionID)
		retParam = SRetParam_GeAchievementInfo.new;
		onReturn_GeAchievementInfo(2, retParam)
	end

	#返回处理：获取成就奖励
	def _doReturn_TakePrize(data)
		retParam = SRetParam_TakePrize.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EAchievementRet)结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakePrize(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取成就奖励
	def _onTimeOut_TakePrize(sessionID)
		retParam = SRetParam_TakePrize.new;
		onReturn_TakePrize(2, retParam)
	end

	#返回处理：获取成就分享信息
	def _doReturn_GeAchievementShareList(data)
		retParam = SRetParam_GeAchievementShareList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecAchievementShare = SAchievementShare::vectorFromStream(data) #(SAchievementShare的数组)成就分享信息
		retParam.vecAchievementShare = vecAchievementShare
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GeAchievementShareList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取成就分享信息
	def _onTimeOut_GeAchievementShareList(sessionID)
		retParam = SRetParam_GeAchievementShareList.new;
		onReturn_GeAchievementShareList(2, retParam)
	end

	#返回处理：获取成就分享奖励
	def _doReturn_TakeSharePrize(data)
		retParam = SRetParam_TakeSharePrize.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EAchievementRet)结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakeSharePrize(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取成就分享奖励
	def _onTimeOut_TakeSharePrize(sessionID)
		retParam = SRetParam_TakeSharePrize.new;
		onReturn_TakeSharePrize(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 75;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_APNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_AchievementLevelNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_AchievementInfoNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_AchievementShareNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_MidnightNotify' #FuncID: 5

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GeAchievementInfo' #FuncID: 1
		@retFuncList[1] = '_doReturn_TakePrize' #FuncID: 2
		@retFuncList[2] = '_doReturn_GeAchievementShareList' #FuncID: 3
		@retFuncList[3] = '_doReturn_TakeSharePrize' #FuncID: 4

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GeAchievementInfo' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_TakePrize' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GeAchievementShareList' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_TakeSharePrize' #FuncID: 4
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

