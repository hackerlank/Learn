#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    FightFormation.rb
#  Purpose:      新阵型相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './RoleInfoDefineBase.rb'

#以下为类型定义

#新阵型相关协议
class EFightFormationResult
	EFIGHTFORMATIONRESULT_SUCCES = 0#操作成功
	EFIGHTFORMATIONRESULT_FAIL = 1#设置错误
end

#阵型信息
class SBattlePosInfo
	attr_accessor:qwInstID #(UINT64)散仙唯一ID
	attr_accessor:byPos #(INT8)位置

	#构造函数
	def initialize
		@qwInstID = 0
		@byPos = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInstID = @qwInstID
		obj.byPos = @byPos
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattlePosInfo.new
		s.qwInstID = ByteUtil::readUINT64(data)
		s.byPos = ByteUtil::readINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattlePosInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeINT8(data, @byPos)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战斗阵型信息
class FightFormationInfo
	attr_accessor:wFormationID #(UINT16)当前阵形ID
	attr_accessor:vecBattlePosInfo #(SBattlePosInfo的数组)位置

	#构造函数
	def initialize
		@wFormationID = 0
		@vecBattlePosInfo = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wFormationID = @wFormationID
		obj.vecBattlePosInfo = @vecBattlePosInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = FightFormationInfo.new
		s.wFormationID = ByteUtil::readUINT16(data)
		s.vecBattlePosInfo = SBattlePosInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = FightFormationInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wFormationID)
		SBattlePosInfo::vectorToStream(data, @vecBattlePosInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战斗散仙信息
class FightHeroInfo
	attr_accessor:qwInstID #(UINT64)散仙InstID
	attr_accessor:dwHP #(UINT32)当前生命值
	attr_accessor:dwMaxHP #(UINT32)最大生命值（可能用到）
	attr_accessor:dwAura #(UINT32)灵气值
	attr_accessor:dwMaxAura #(UINT32)最大灵气值

	#构造函数
	def initialize
		@qwInstID = 0
		@dwHP = 0
		@dwMaxHP = 0
		@dwAura = 0
		@dwMaxAura = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInstID = @qwInstID
		obj.dwHP = @dwHP
		obj.dwMaxHP = @dwMaxHP
		obj.dwAura = @dwAura
		obj.dwMaxAura = @dwMaxAura
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = FightHeroInfo.new
		s.qwInstID = ByteUtil::readUINT64(data)
		s.dwHP = ByteUtil::readUINT32(data)
		s.dwMaxHP = ByteUtil::readUINT32(data)
		s.dwAura = ByteUtil::readUINT32(data)
		s.dwMaxAura = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = FightHeroInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT32(data, @dwHP)
		ByteUtil::writeUINT32(data, @dwMaxHP)
		ByteUtil::writeUINT32(data, @dwAura)
		ByteUtil::writeUINT32(data, @dwMaxAura)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetFightFormation:取得阵形信息]的返回的参数组成的结构体
class SRetParam_GetFightFormation
	attr_accessor:oFightFormation#(类类型：FightFormationInfo)战斗阵形信息

	#构造函数
	def initialize
		@oFightFormation = FightFormationInfo.new
	end
end

#函数[SetFightFormation:设置阵形信息]的返回的参数组成的结构体
class SRetParam_SetFightFormation
	attr_accessor:eRet#(枚举类型：EFightFormationResult)操作结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#函数[GetFightHeroInfo:战斗散仙信息]的返回的参数组成的结构体
class SRetParam_GetFightHeroInfo
	attr_accessor:vecFightHeroInfo#(FightHeroInfo的数组)战斗阵形信息

	#构造函数
	def initialize
		@vecFightHeroInfo = Array.new
	end
end

#协议类：新阵型相关协议
class FightFormationBase < ProtocolBase
	#以下为发送函数
	#发送：取得阵形信息
	def send_GetFightFormation(
		wBattleType #(UINT16)战斗类型 EBattleType
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wBattleType)
		return @svrHandler.sendPacket(data)
	end

	#发送：设置阵形信息
	def send_SetFightFormation(
		wBattleType,  #(UINT16)战斗类型
		oFightFormation #(类类型：FightFormationInfo)阵形ID
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wBattleType)
		oFightFormation.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：战斗散仙信息
	def send_GetFightHeroInfo(
		wBattleType #(UINT16)战斗类型 EBattleType
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wBattleType)
		return @svrHandler.sendPacket(data)
	end

#以下的返回函数需要重载
	#返回：取得阵形信息
	def onReturn_GetFightFormation(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetFightFormation)返回的参数
	)
	end

	#返回：设置阵形信息
	def onReturn_SetFightFormation(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SetFightFormation)返回的参数
	)
	end

	#返回：战斗散仙信息
	def onReturn_GetFightHeroInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetFightHeroInfo)返回的参数
	)
	end

	#返回处理：取得阵形信息
	def _doReturn_GetFightFormation(data)
		retParam = SRetParam_GetFightFormation.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		oFightFormation = FightFormationInfo::fromStream(data) #(类类型：FightFormationInfo)战斗阵形信息
		retParam.oFightFormation = oFightFormation
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetFightFormation(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：取得阵形信息
	def _onTimeOut_GetFightFormation(sessionID)
		retParam = SRetParam_GetFightFormation.new;
		onReturn_GetFightFormation(2, retParam)
	end

	#返回处理：设置阵形信息
	def _doReturn_SetFightFormation(data)
		retParam = SRetParam_SetFightFormation.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EFightFormationResult)操作结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SetFightFormation(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：设置阵形信息
	def _onTimeOut_SetFightFormation(sessionID)
		retParam = SRetParam_SetFightFormation.new;
		onReturn_SetFightFormation(2, retParam)
	end

	#返回处理：战斗散仙信息
	def _doReturn_GetFightHeroInfo(data)
		retParam = SRetParam_GetFightHeroInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecFightHeroInfo = FightHeroInfo::vectorFromStream(data) #(FightHeroInfo的数组)战斗阵形信息
		retParam.vecFightHeroInfo = vecFightHeroInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetFightHeroInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：战斗散仙信息
	def _onTimeOut_GetFightHeroInfo(sessionID)
		retParam = SRetParam_GetFightHeroInfo.new;
		onReturn_GetFightHeroInfo(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 132;
		@recvFuncList = Array.new

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetFightFormation' #FuncID: 1
		@retFuncList[1] = '_doReturn_SetFightFormation' #FuncID: 2
		@retFuncList[2] = '_doReturn_GetFightHeroInfo' #FuncID: 3

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetFightFormation' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_SetFightFormation' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GetFightHeroInfo' #FuncID: 3
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

