#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    RoleEvent.rb
#  Purpose:      玩家在GameServer的消息处理
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './FighterProtBase.rb'
require_relative './ItemProtBase.rb'
require_relative './ProtoCommonBase.rb'
require_relative './RoleInfoDefineBase.rb'

#以下为类型定义

#暴击类型
class ECritType
	EPETCRIT = 0#阵灵暴击
	EHORSECRIT = 1#坐骑暴击
	EFASHIONCRIT = 2#时装暴击
	ETRUMPCRIT = 3#法宝暴击
	EDUJIECRIT = 4#渡劫暴击
	EMONEYTREECRIT = 5#摇钱树暴击
end

#暴击倍数
class ECritMultiple
	ETWOMULTIPLECRIT = 0#2倍暴击
	EFIVEMULTIPLECRIT = 1#5倍暴击
	ETENMULTIPLECRIT = 2#10倍暴击
end

#面板散仙信息
class SFighterSpecInfo
	attr_accessor:oEquips #(SItem的数组)散仙所有装备信息
	attr_accessor:oFighterInfo #(类类型：FighterProt::SFighterInfo)散仙基本信息

	#构造函数
	def initialize
		@oEquips = Array.new
		@oFighterInfo = SFighterInfo.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.oEquips = @oEquips
		obj.oFighterInfo = @oFighterInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFighterSpecInfo.new
		s.oEquips = SItem::superVectorFromStream(data)
		s.oFighterInfo = SFighterInfo::fromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFighterSpecInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		SItem::superVectorToStream(data, @oEquips)
		@oFighterInfo.toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#散仙信息
class SRoleFighterStream
	attr_accessor:oMainFighter #(类类型：SFighterSpecInfo)主散仙的信息
	attr_accessor:oFighters #(SFighterSpecInfo的数组)所有散仙的信息

	#构造函数
	def initialize
		@oMainFighter = SFighterSpecInfo.new
		@oFighters = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.oMainFighter = @oMainFighter
		obj.oFighters = @oFighters
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRoleFighterStream.new
		s.oMainFighter = SFighterSpecInfo::fromStream(data)
		s.oFighters = SFighterSpecInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRoleFighterStream::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		@oMainFighter.toStream(data)
		SFighterSpecInfo::vectorToStream(data, @oFighters)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#面板散仙信息
class SRoleStream
	attr_accessor:oMainFighter #(类类型：SFighterSpecInfo)主散仙的信息

	#构造函数
	def initialize
		@oMainFighter = SFighterSpecInfo.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.oMainFighter = @oMainFighter
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRoleStream.new
		s.oMainFighter = SFighterSpecInfo::fromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRoleStream::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		@oMainFighter.toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetRoleSpecInfo:获取角色面板信息]的返回的参数组成的结构体
class SRetParam_GetRoleSpecInfo
	attr_accessor:stRoleStream#(类类型：SRoleStream)角色信息

	#构造函数
	def initialize
		@stRoleStream = SRoleStream.new
	end
end

#函数[GetFighters:取得散仙列表]的返回的参数组成的结构体
class SRetParam_GetFighters
	attr_accessor:vecFighters#(SFighterSpecInfo的数组)散仙信息

	#构造函数
	def initialize
		@vecFighters = Array.new
	end
end

#函数[StoreGuide:存储新手引导信息]的返回的参数组成的结构体
class SRetParam_StoreGuide
	attr_accessor:bResult#(bool)结果

	#构造函数
	def initialize
		@bResult = false
	end
end

#函数[GetRoleBuffInfo:获取角色Buff信息]的返回的参数组成的结构体
class SRetParam_GetRoleBuffInfo
	attr_accessor:vecBuffInfo#(SBuffInfo的数组)玩家Buff信息

	#构造函数
	def initialize
		@vecBuffInfo = Array.new
	end
end

#协议类：玩家在GameServer的消息处理
class RoleEventBase < ProtocolBase
	#以下为发送函数
	#发送：获取角色面板信息
	def send_GetRoleSpecInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：取得散仙列表
	def send_GetFighters(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：存储新手引导信息
	def send_StoreGuide(
		strGuide #(string)引导步骤信息
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeSTRING(data, strGuide)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取角色Buff信息
	def send_GetRoleBuffInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：散仙信息通知列表
	def onRecv_FighterInfoNotify(
		vecFighters #(SFighterSpecInfo的数组)散仙信息
	)
		raise NotImplementedError
	end
	#接收：增加的AppearIcon通知
	def onRecv_AddAppearIconNotify(
		vecAppearIcon #(UINT16数组)增加的Icon列表
	)
		raise NotImplementedError
	end
	#接收：玩家Buff变化通知
	def onRecv_BuffNotify(
		eType, #(枚类型：ProtoCommon::EDataChange)更新类型，增加，删除，修改
		vecBuffInfo #(SBuffInfo的数组)玩家Buff信息
	)
		raise NotImplementedError
	end
	#接收：准备切地图
	def onRecv_ChangeMapNotify(
		wMapId, #(UINT16)地图id，客户端准备资源
		qwDgnId, #(UINT64)副本实例，非单人副本为0
		wDgnType #(UINT16)副本模板，单人副本为0
	)
		raise NotImplementedError
	end
	#接收：暴击通知
	def onRecv_CritNotify(
		eCritType, #(枚举类型：ECritType)暴击类型
		eCritMultiple #(枚举类型：ECritMultiple)暴击倍数
	)
		raise NotImplementedError
	end
	#接收：删除AppearIcon通知
	def onRecv_DelAppearIconNotify(
		wIconID #(UINT16)删除的IconApear
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取角色面板信息
	def onReturn_GetRoleSpecInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetRoleSpecInfo)返回的参数
	)
	end

	#返回：取得散仙列表
	def onReturn_GetFighters(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetFighters)返回的参数
	)
	end

	#返回：存储新手引导信息
	def onReturn_StoreGuide(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_StoreGuide)返回的参数
	)
	end

	#返回：获取角色Buff信息
	def onReturn_GetRoleBuffInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetRoleBuffInfo)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：散仙信息通知列表
	def _doRecv_FighterInfoNotify(data)
		vecFighters = SFighterSpecInfo::vectorFromStream(data)
		return onRecv_FighterInfoNotify(vecFighters)
	end

	#接收处理：增加的AppearIcon通知
	def _doRecv_AddAppearIconNotify(data)
		vecAppearIcon = ByteUtil::readVecUINT16(data)
		return onRecv_AddAppearIconNotify(vecAppearIcon)
	end

	#接收处理：玩家Buff变化通知
	def _doRecv_BuffNotify(data)
		eType = ByteUtil::readUINT8(data)
		vecBuffInfo = SBuffInfo::vectorFromStream(data)
		return onRecv_BuffNotify(eType, vecBuffInfo)
	end

	#接收处理：准备切地图
	def _doRecv_ChangeMapNotify(data)
		wMapId = ByteUtil::readUINT16(data)
		qwDgnId = ByteUtil::readUINT64(data)
		wDgnType = ByteUtil::readUINT16(data)
		return onRecv_ChangeMapNotify(wMapId, qwDgnId, wDgnType)
	end

	#接收处理：暴击通知
	def _doRecv_CritNotify(data)
		eCritType = ByteUtil::readINT8(data)
		eCritMultiple = ByteUtil::readINT8(data)
		return onRecv_CritNotify(eCritType, eCritMultiple)
	end

	#接收处理：删除AppearIcon通知
	def _doRecv_DelAppearIconNotify(data)
		wIconID = ByteUtil::readUINT16(data)
		return onRecv_DelAppearIconNotify(wIconID)
	end

#以下为返回处理函数
	#返回处理：获取角色面板信息
	def _doReturn_GetRoleSpecInfo(data)
		retParam = SRetParam_GetRoleSpecInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		stRoleStream = SRoleStream::fromStream(data) #(类类型：SRoleStream)角色信息
		retParam.stRoleStream = stRoleStream
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetRoleSpecInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取角色面板信息
	def _onTimeOut_GetRoleSpecInfo(sessionID)
		retParam = SRetParam_GetRoleSpecInfo.new;
		onReturn_GetRoleSpecInfo(2, retParam)
	end

	#返回处理：取得散仙列表
	def _doReturn_GetFighters(data)
		retParam = SRetParam_GetFighters.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecFighters = SFighterSpecInfo::vectorFromStream(data) #(SFighterSpecInfo的数组)散仙信息
		retParam.vecFighters = vecFighters
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetFighters(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：取得散仙列表
	def _onTimeOut_GetFighters(sessionID)
		retParam = SRetParam_GetFighters.new;
		onReturn_GetFighters(2, retParam)
	end

	#返回处理：存储新手引导信息
	def _doReturn_StoreGuide(data)
		retParam = SRetParam_StoreGuide.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		bResult = ByteUtil::readBOOL(data) #(bool)结果
		retParam.bResult = bResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_StoreGuide(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：存储新手引导信息
	def _onTimeOut_StoreGuide(sessionID)
		retParam = SRetParam_StoreGuide.new;
		onReturn_StoreGuide(2, retParam)
	end

	#返回处理：获取角色Buff信息
	def _doReturn_GetRoleBuffInfo(data)
		retParam = SRetParam_GetRoleBuffInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecBuffInfo = SBuffInfo::vectorFromStream(data) #(SBuffInfo的数组)玩家Buff信息
		retParam.vecBuffInfo = vecBuffInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetRoleBuffInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取角色Buff信息
	def _onTimeOut_GetRoleBuffInfo(sessionID)
		retParam = SRetParam_GetRoleBuffInfo.new;
		onReturn_GetRoleBuffInfo(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 11;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_FighterInfoNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_AddAppearIconNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_BuffNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_ChangeMapNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_CritNotify' #FuncID: 5
		@recvFuncList[5] = '_doRecv_DelAppearIconNotify' #FuncID: 6

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetRoleSpecInfo' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetFighters' #FuncID: 2
		@retFuncList[2] = '_doReturn_StoreGuide' #FuncID: 3
		@retFuncList[3] = '_doReturn_GetRoleBuffInfo' #FuncID: 4

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetRoleSpecInfo' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetFighters' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_StoreGuide' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_GetRoleBuffInfo' #FuncID: 4
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

