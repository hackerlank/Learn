#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    CompareBattlePoint.rb
#  Purpose:      变强(战力对比)相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#对比的数据结构
class SCompareData
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:strName #(string)玩家名字
	attr_accessor:byLevel #(UINT8)玩家等级
	attr_accessor:eCareer #(枚类型：ProtoCommon::ECareerType)玩家主将职业
	attr_accessor:eSex #(枚类型：ProtoCommon::ESexType)玩家主将性别
	attr_accessor:dwBattlePoint #(UINT32)玩家总战斗力
	attr_accessor:dwHeroBP #(UINT32)散仙的战斗力(渡劫和心法除外)
	attr_accessor:dwBeautyBP #(UINT32)美女系统战斗力
	attr_accessor:dwTrumpBP #(UINT32)法宝战斗力
	attr_accessor:dwHorseBP #(UINT32)坐骑战斗力
	attr_accessor:dwDujieBP #(UINT32)渡劫战斗力
	attr_accessor:dwXinfaBP #(UINT32)心法战斗力
	attr_accessor:dwClanBP #(UINT32)帮派战斗力

	#构造函数
	def initialize
		@qwRoleID = 0
		@strName = ''
		@byLevel = 0
		@eCareer = 0
		@eSex = 0
		@dwBattlePoint = 0
		@dwHeroBP = 0
		@dwBeautyBP = 0
		@dwTrumpBP = 0
		@dwHorseBP = 0
		@dwDujieBP = 0
		@dwXinfaBP = 0
		@dwClanBP = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.strName = @strName
		obj.byLevel = @byLevel
		obj.eCareer = @eCareer
		obj.eSex = @eSex
		obj.dwBattlePoint = @dwBattlePoint
		obj.dwHeroBP = @dwHeroBP
		obj.dwBeautyBP = @dwBeautyBP
		obj.dwTrumpBP = @dwTrumpBP
		obj.dwHorseBP = @dwHorseBP
		obj.dwDujieBP = @dwDujieBP
		obj.dwXinfaBP = @dwXinfaBP
		obj.dwClanBP = @dwClanBP
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SCompareData.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.eCareer = ByteUtil::readUINT8(data)
		s.eSex = ByteUtil::readUINT8(data)
		s.dwBattlePoint = ByteUtil::readUINT32(data)
		s.dwHeroBP = ByteUtil::readUINT32(data)
		s.dwBeautyBP = ByteUtil::readUINT32(data)
		s.dwTrumpBP = ByteUtil::readUINT32(data)
		s.dwHorseBP = ByteUtil::readUINT32(data)
		s.dwDujieBP = ByteUtil::readUINT32(data)
		s.dwXinfaBP = ByteUtil::readUINT32(data)
		s.dwClanBP = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SCompareData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT8(data, @eCareer)
		ByteUtil::writeUINT8(data, @eSex)
		ByteUtil::writeUINT32(data, @dwBattlePoint)
		ByteUtil::writeUINT32(data, @dwHeroBP)
		ByteUtil::writeUINT32(data, @dwBeautyBP)
		ByteUtil::writeUINT32(data, @dwTrumpBP)
		ByteUtil::writeUINT32(data, @dwHorseBP)
		ByteUtil::writeUINT32(data, @dwDujieBP)
		ByteUtil::writeUINT32(data, @dwXinfaBP)
		ByteUtil::writeUINT32(data, @dwClanBP)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[CompareOtherBPByID:战斗力对比]的返回的参数组成的结构体
class SRetParam_CompareOtherBPByID
	attr_accessor:vecCompareData#(SCompareData的数组)玩家的对比数据信息

	#构造函数
	def initialize
		@vecCompareData = Array.new
	end
end

#函数[CompareOtherBPByName:战斗力对比]的返回的参数组成的结构体
class SRetParam_CompareOtherBPByName
	attr_accessor:vecCompareData#(SCompareData的数组)玩家的对比数据信息

	#构造函数
	def initialize
		@vecCompareData = Array.new
	end
end

#协议类：变强(战力对比)相关协议
class CompareBattlePointBase < ProtocolBase
	#以下为发送函数
	#发送：战斗力对比
	def send_CompareOtherBPByID(
		qwRoleID #(UINT64)对方的玩家ID
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：战斗力对比
	def send_CompareOtherBPByName(
		strName #(string)对方的玩家名字
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeSTRING(data, strName)
		return @svrHandler.sendPacket(data)
	end

#以下的返回函数需要重载
	#返回：战斗力对比
	def onReturn_CompareOtherBPByID(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_CompareOtherBPByID)返回的参数
	)
	end

	#返回：战斗力对比
	def onReturn_CompareOtherBPByName(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_CompareOtherBPByName)返回的参数
	)
	end

	#返回处理：战斗力对比
	def _doReturn_CompareOtherBPByID(data)
		retParam = SRetParam_CompareOtherBPByID.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecCompareData = SCompareData::vectorFromStream(data) #(SCompareData的数组)玩家的对比数据信息
		retParam.vecCompareData = vecCompareData
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_CompareOtherBPByID(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：战斗力对比
	def _onTimeOut_CompareOtherBPByID(sessionID)
		retParam = SRetParam_CompareOtherBPByID.new;
		onReturn_CompareOtherBPByID(2, retParam)
	end

	#返回处理：战斗力对比
	def _doReturn_CompareOtherBPByName(data)
		retParam = SRetParam_CompareOtherBPByName.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecCompareData = SCompareData::vectorFromStream(data) #(SCompareData的数组)玩家的对比数据信息
		retParam.vecCompareData = vecCompareData
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_CompareOtherBPByName(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：战斗力对比
	def _onTimeOut_CompareOtherBPByName(sessionID)
		retParam = SRetParam_CompareOtherBPByName.new;
		onReturn_CompareOtherBPByName(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 58;
		@recvFuncList = Array.new

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_CompareOtherBPByID' #FuncID: 1
		@retFuncList[1] = '_doReturn_CompareOtherBPByName' #FuncID: 2

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_CompareOtherBPByID' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_CompareOtherBPByName' #FuncID: 2
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

