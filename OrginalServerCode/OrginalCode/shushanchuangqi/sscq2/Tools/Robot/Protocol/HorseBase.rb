#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    Horse.rb
#  Purpose:      坐骑
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#骑乘状态
class EHorseStatus
	EHORSESTATUSUNMOUNT = 0#下马
	EHORSESTATUSMOUNTED = 1#上马
end

#坐骑信息更新类型
class EHorseOpType
	EHORSEOPTYPE_ADD = 0#添加坐骑
	EHORSEOPTYPE_UPDATE = 1#更新坐骑信息
end

#坐骑数据库数据
class SHorseDB
	attr_accessor:qwRoleID #(UINT64)角色id
	attr_accessor:qwUserID #(UINT64)账号
	attr_accessor:dwHorseID #(UINT32)坐骑id
	attr_accessor:dwHorseLevel #(UINT32)坐骑等级
	attr_accessor:dwPos #(UINT32)坐骑位置1表示骑乘
	attr_accessor:dwModelID #(UINT32)坐骑模型id
	attr_accessor:dwExp #(UINT32)坐骑当前经验
	attr_accessor:dwLock #(UINT32)坐骑技能锁定
	attr_accessor:strModel #(string)坐骑外观列表

	#构造函数
	def initialize
		@qwRoleID = 0
		@qwUserID = 0
		@dwHorseID = 0
		@dwHorseLevel = 0
		@dwPos = 0
		@dwModelID = 0
		@dwExp = 0
		@dwLock = 0
		@strModel = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.qwUserID = @qwUserID
		obj.dwHorseID = @dwHorseID
		obj.dwHorseLevel = @dwHorseLevel
		obj.dwPos = @dwPos
		obj.dwModelID = @dwModelID
		obj.dwExp = @dwExp
		obj.dwLock = @dwLock
		obj.strModel = @strModel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SHorseDB.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.qwUserID = ByteUtil::readUINT64(data)
		s.dwHorseID = ByteUtil::readUINT32(data)
		s.dwHorseLevel = ByteUtil::readUINT32(data)
		s.dwPos = ByteUtil::readUINT32(data)
		s.dwModelID = ByteUtil::readUINT32(data)
		s.dwExp = ByteUtil::readUINT32(data)
		s.dwLock = ByteUtil::readUINT32(data)
		s.strModel = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SHorseDB::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeUINT32(data, @dwHorseID)
		ByteUtil::writeUINT32(data, @dwHorseLevel)
		ByteUtil::writeUINT32(data, @dwPos)
		ByteUtil::writeUINT32(data, @dwModelID)
		ByteUtil::writeUINT32(data, @dwExp)
		ByteUtil::writeUINT32(data, @dwLock)
		ByteUtil::writeSTRING(data, @strModel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#坐骑信息
class SHorseInfo
	attr_accessor:dwHorseID #(UINT32)坐骑id
	attr_accessor:dwHorseLevel #(UINT32)坐骑等阶
	attr_accessor:dwExp #(UINT32)坐骑当前经验
	attr_accessor:dwPos #(UINT32)骑乘状态
	attr_accessor:vecHorseID #(UINT32数组)坐骑外观列表

	#构造函数
	def initialize
		@dwHorseID = 0
		@dwHorseLevel = 0
		@dwExp = 0
		@dwPos = 0
		@vecHorseID = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwHorseID = @dwHorseID
		obj.dwHorseLevel = @dwHorseLevel
		obj.dwExp = @dwExp
		obj.dwPos = @dwPos
		obj.vecHorseID = @vecHorseID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SHorseInfo.new
		s.dwHorseID = ByteUtil::readUINT32(data)
		s.dwHorseLevel = ByteUtil::readUINT32(data)
		s.dwExp = ByteUtil::readUINT32(data)
		s.dwPos = ByteUtil::readUINT32(data)
		s.vecHorseID = ByteUtil::readVecUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SHorseInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwHorseID)
		ByteUtil::writeUINT32(data, @dwHorseLevel)
		ByteUtil::writeUINT32(data, @dwExp)
		ByteUtil::writeUINT32(data, @dwPos)
		ByteUtil::writeVecUINT32(data, @vecHorseID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#属性信息表
class SAttrInfo
	attr_accessor:dwAttrType #(UINT32)属性类型id
	attr_accessor:fAttrValue #(float)属性值

	#构造函数
	def initialize
		@dwAttrType = 0
		@fAttrValue = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwAttrType = @dwAttrType
		obj.fAttrValue = @fAttrValue
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SAttrInfo.new
		s.dwAttrType = ByteUtil::readUINT32(data)
		s.fAttrValue = ByteUtil::readFLOAT(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SAttrInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwAttrType)
		ByteUtil::writeFLOAT(data, @fAttrValue)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[ActiveHorse:激活坐骑]的返回的参数组成的结构体
class SRetParam_ActiveHorse
	attr_accessor:dwRet#(UINT32)结果 0成功其他错误码

	#构造函数
	def initialize
		@dwRet = 0
	end
end

#函数[UpgradeHorse:坐骑进阶]的返回的参数组成的结构体
class SRetParam_UpgradeHorse
	attr_accessor:dwRet#(UINT32)结果 0成功其他错误码

	#构造函数
	def initialize
		@dwRet = 0
	end
end

#函数[SetHorseStatus:骑乘状态修改]的返回的参数组成的结构体
class SRetParam_SetHorseStatus
	attr_accessor:bRet#(bool)结果

	#构造函数
	def initialize
		@bRet = false
	end
end

#函数[GetHorseAttr:获取坐骑属性]的返回的参数组成的结构体
class SRetParam_GetHorseAttr
	attr_accessor:dwRet#(UINT32)结果 0成功其他错误码

	#构造函数
	def initialize
		@dwRet = 0
	end
end

#函数[UnLockHorseSkillAttr:解锁技能属性（暂时不用）]的返回的参数组成的结构体
class SRetParam_UnLockHorseSkillAttr
	attr_accessor:bRet#(bool)结果

	#构造函数
	def initialize
		@bRet = false
	end
end

#协议类：坐骑
class HorseBase < ProtocolBase
	#以下为发送函数
	#发送：获取坐骑信息
	def send_GetHorseList(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：激活坐骑
	def send_ActiveHorse(
		dwHorseID #(UINT32)坐骑ID
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwHorseID)
		return @svrHandler.sendPacket(data)
	end

	#发送：坐骑进阶
	def send_UpgradeHorse(
		dwHorseID,  #(UINT32)坐骑ID
		bAll #(bool)是否一键进阶
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwHorseID)
		ByteUtil::writeBOOL(data, bAll)
		return @svrHandler.sendPacket(data)
	end

	#发送：骑乘状态修改
	def send_SetHorseStatus(
		dwHorseID,  #(UINT32)坐骑ID
		eHorseStatus #(UINT32)骑乘状态
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwHorseID)
		ByteUtil::writeUINT32(data, eHorseStatus)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取坐骑属性
	def send_GetHorseAttr(
		dwHorseID #(UINT32)坐骑ID id=0为所有坐骑属性
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwHorseID)
		return @svrHandler.sendPacket(data)
	end

	#发送：解锁技能属性（暂时不用）
	def send_UnLockHorseSkillAttr(
		dwHorseID,  #(UINT32)坐骑ID
		dwPos #(UINT32)第几个技能属性 1开始
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwHorseID)
		ByteUtil::writeUINT32(data, dwPos)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：坐骑信息
	def onRecv_HorseNotifyList(
		vecHorseInfo #(SHorseInfo的数组)坐骑信息
	)
		raise NotImplementedError
	end
	#接收：坐骑信息更新
	def onRecv_HorseInfoChangeNotifyList(
		dwHorseOpType, #(UINT32)更新类型
		oHorseInfo #(类类型：SHorseInfo)坐骑信息更新
	)
		raise NotImplementedError
	end
	#接收：坐骑属性信息
	def onRecv_HorseAttrNotify(
		dwHorseID, #(UINT32)坐骑ID
		vecAttrInfo #(SFtAttrMod的数组)坐骑属性信息表
	)
		raise NotImplementedError
	end
	#接收：玩家速度通知
	def onRecv_SpeedChangeNotify(
		dwSpeed #(UINT32)玩家速度
	)
		raise NotImplementedError
	end
	#接收：坐骑外观改变
	def onRecv_HorseLookChangeNotify(
		qwRoleID, #(UINT64)角色Id
		dwHorseID, #(UINT32)坐骑模型
		dwHorseLevel #(UINT32)坐骑等级
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：激活坐骑
	def onReturn_ActiveHorse(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ActiveHorse)返回的参数
	)
	end

	#返回：坐骑进阶
	def onReturn_UpgradeHorse(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UpgradeHorse)返回的参数
	)
	end

	#返回：骑乘状态修改
	def onReturn_SetHorseStatus(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SetHorseStatus)返回的参数
	)
	end

	#返回：获取坐骑属性
	def onReturn_GetHorseAttr(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetHorseAttr)返回的参数
	)
	end

	#返回：解锁技能属性（暂时不用）
	def onReturn_UnLockHorseSkillAttr(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UnLockHorseSkillAttr)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：坐骑信息
	def _doRecv_HorseNotifyList(data)
		vecHorseInfo = SHorseInfo::vectorFromStream(data)
		return onRecv_HorseNotifyList(vecHorseInfo)
	end

	#接收处理：坐骑信息更新
	def _doRecv_HorseInfoChangeNotifyList(data)
		dwHorseOpType = ByteUtil::readUINT32(data)
		oHorseInfo = SHorseInfo::fromStream(data)
		return onRecv_HorseInfoChangeNotifyList(dwHorseOpType, oHorseInfo)
	end

	#接收处理：坐骑属性信息
	def _doRecv_HorseAttrNotify(data)
		dwHorseID = ByteUtil::readUINT32(data)
		vecAttrInfo = SFtAttrMod::vectorFromStream(data)
		return onRecv_HorseAttrNotify(dwHorseID, vecAttrInfo)
	end

	#接收处理：玩家速度通知
	def _doRecv_SpeedChangeNotify(data)
		dwSpeed = ByteUtil::readUINT32(data)
		return onRecv_SpeedChangeNotify(dwSpeed)
	end

	#接收处理：坐骑外观改变
	def _doRecv_HorseLookChangeNotify(data)
		qwRoleID = ByteUtil::readUINT64(data)
		dwHorseID = ByteUtil::readUINT32(data)
		dwHorseLevel = ByteUtil::readUINT32(data)
		return onRecv_HorseLookChangeNotify(qwRoleID, dwHorseID, dwHorseLevel)
	end

#以下为返回处理函数
	#返回处理：激活坐骑
	def _doReturn_ActiveHorse(data)
		retParam = SRetParam_ActiveHorse.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果 0成功其他错误码
		retParam.dwRet = dwRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ActiveHorse(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：激活坐骑
	def _onTimeOut_ActiveHorse(sessionID)
		retParam = SRetParam_ActiveHorse.new;
		onReturn_ActiveHorse(2, retParam)
	end

	#返回处理：坐骑进阶
	def _doReturn_UpgradeHorse(data)
		retParam = SRetParam_UpgradeHorse.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果 0成功其他错误码
		retParam.dwRet = dwRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UpgradeHorse(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：坐骑进阶
	def _onTimeOut_UpgradeHorse(sessionID)
		retParam = SRetParam_UpgradeHorse.new;
		onReturn_UpgradeHorse(2, retParam)
	end

	#返回处理：骑乘状态修改
	def _doReturn_SetHorseStatus(data)
		retParam = SRetParam_SetHorseStatus.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		bRet = ByteUtil::readBOOL(data) #(bool)结果
		retParam.bRet = bRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SetHorseStatus(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：骑乘状态修改
	def _onTimeOut_SetHorseStatus(sessionID)
		retParam = SRetParam_SetHorseStatus.new;
		onReturn_SetHorseStatus(2, retParam)
	end

	#返回处理：获取坐骑属性
	def _doReturn_GetHorseAttr(data)
		retParam = SRetParam_GetHorseAttr.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果 0成功其他错误码
		retParam.dwRet = dwRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetHorseAttr(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取坐骑属性
	def _onTimeOut_GetHorseAttr(sessionID)
		retParam = SRetParam_GetHorseAttr.new;
		onReturn_GetHorseAttr(2, retParam)
	end

	#返回处理：解锁技能属性（暂时不用）
	def _doReturn_UnLockHorseSkillAttr(data)
		retParam = SRetParam_UnLockHorseSkillAttr.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		bRet = ByteUtil::readBOOL(data) #(bool)结果
		retParam.bRet = bRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UnLockHorseSkillAttr(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：解锁技能属性（暂时不用）
	def _onTimeOut_UnLockHorseSkillAttr(sessionID)
		retParam = SRetParam_UnLockHorseSkillAttr.new;
		onReturn_UnLockHorseSkillAttr(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 74;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_HorseNotifyList' #FuncID: 1
		@recvFuncList[1] = '_doRecv_HorseInfoChangeNotifyList' #FuncID: 2
		@recvFuncList[2] = '_doRecv_HorseAttrNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_SpeedChangeNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_HorseLookChangeNotify' #FuncID: 5

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_ActiveHorse' #FuncID: 1
		@retFuncList[1] = '_doReturn_UpgradeHorse' #FuncID: 2
		@retFuncList[2] = '_doReturn_SetHorseStatus' #FuncID: 3
		@retFuncList[3] = '_doReturn_GetHorseAttr' #FuncID: 4
		@retFuncList[4] = '_doReturn_UnLockHorseSkillAttr' #FuncID: 5

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_ActiveHorse' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_UpgradeHorse' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_SetHorseStatus' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_GetHorseAttr' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_UnLockHorseSkillAttr' #FuncID: 5
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

