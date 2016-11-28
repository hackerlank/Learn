#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    DemonTower.rb
#  Purpose:      锁妖塔
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#被攻击类型
class EAttackedType
	EATTACKEDTYPE_DEMONTOWER = 1#锁妖塔
end

#魄空间列表
class SSpaceInfo
	attr_accessor:dwSoulSpaceID #(UINT32)魄空间id
	attr_accessor:dwSoulSpaceLevel #(UINT32)魄空间等级

	#构造函数
	def initialize
		@dwSoulSpaceID = 0
		@dwSoulSpaceLevel = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwSoulSpaceID = @dwSoulSpaceID
		obj.dwSoulSpaceLevel = @dwSoulSpaceLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSpaceInfo.new
		s.dwSoulSpaceID = ByteUtil::readUINT32(data)
		s.dwSoulSpaceLevel = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSpaceInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwSoulSpaceID)
		ByteUtil::writeUINT32(data, @dwSoulSpaceLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#被攻击列表
class SRoleAttaked
	attr_accessor:qwRoleID #(UINT64)角色ID
	attr_accessor:dwPos #(UINT32)存储位置
	attr_accessor:qwAtkRoleID #(UINT64)攻击角色ID
	attr_accessor:strRoleName #(string)角色名
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:dwAttackedTime #(UINT32)攻击时间
	attr_accessor:dwFighterType #(UINT32)战斗类型

	#构造函数
	def initialize
		@qwRoleID = 0
		@dwPos = 0
		@qwAtkRoleID = 0
		@strRoleName = ''
		@byLevel = 0
		@dwAttackedTime = 0
		@dwFighterType = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.dwPos = @dwPos
		obj.qwAtkRoleID = @qwAtkRoleID
		obj.strRoleName = @strRoleName
		obj.byLevel = @byLevel
		obj.dwAttackedTime = @dwAttackedTime
		obj.dwFighterType = @dwFighterType
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRoleAttaked.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.dwPos = ByteUtil::readUINT32(data)
		s.qwAtkRoleID = ByteUtil::readUINT64(data)
		s.strRoleName = ByteUtil::readSTRING(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.dwAttackedTime = ByteUtil::readUINT32(data)
		s.dwFighterType = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRoleAttaked::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT32(data, @dwPos)
		ByteUtil::writeUINT64(data, @qwAtkRoleID)
		ByteUtil::writeSTRING(data, @strRoleName)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwAttackedTime)
		ByteUtil::writeUINT32(data, @dwFighterType)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#锁妖塔被攻击列表
class SDemonToweAttackedInfo
	attr_accessor:qwAtkRoleID #(UINT64)攻击角色ID
	attr_accessor:strRoleName #(string)角色名
	attr_accessor:dwLayerID #(UINT32)层数
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:dwAttackedTime #(UINT32)攻击时间

	#构造函数
	def initialize
		@qwAtkRoleID = 0
		@strRoleName = ''
		@dwLayerID = 0
		@byLevel = 0
		@dwAttackedTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwAtkRoleID = @qwAtkRoleID
		obj.strRoleName = @strRoleName
		obj.dwLayerID = @dwLayerID
		obj.byLevel = @byLevel
		obj.dwAttackedTime = @dwAttackedTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDemonToweAttackedInfo.new
		s.qwAtkRoleID = ByteUtil::readUINT64(data)
		s.strRoleName = ByteUtil::readSTRING(data)
		s.dwLayerID = ByteUtil::readUINT32(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.dwAttackedTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDemonToweAttackedInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwAtkRoleID)
		ByteUtil::writeSTRING(data, @strRoleName)
		ByteUtil::writeUINT32(data, @dwLayerID)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwAttackedTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[EnterDemonTower:进入锁妖塔 (暂时不用)]的返回的参数组成的结构体
class SRetParam_EnterDemonTower
	attr_accessor:dwRet#(UINT32)结果 0成功其他错误码

	#构造函数
	def initialize
		@dwRet = 0
	end
end

#函数[LeaveDemonTower:离开锁妖塔 (暂时不用)]的返回的参数组成的结构体
class SRetParam_LeaveDemonTower
	attr_accessor:dwRet#(UINT32)结果 0成功其他错误码

	#构造函数
	def initialize
		@dwRet = 0
	end
end

#函数[SealMonster:封印怪物(暂时不用)]的返回的参数组成的结构体
class SRetParam_SealMonster
	attr_accessor:dwRet#(UINT32)结果 0成功其他错误码

	#构造函数
	def initialize
		@dwRet = 0
	end
end

#函数[UpgradeSoulSpace:升级魄空间]的返回的参数组成的结构体
class SRetParam_UpgradeSoulSpace
	attr_accessor:dwRet#(UINT32)结果 0成功其他错误码

	#构造函数
	def initialize
		@dwRet = 0
	end
end

#函数[TakeDayPrize:获取每日奖励]的返回的参数组成的结构体
class SRetParam_TakeDayPrize
	attr_accessor:dwRet#(UINT32)结果 0成功其他错误码

	#构造函数
	def initialize
		@dwRet = 0
	end
end

#函数[TakeLayerPrize:领取每层奖励]的返回的参数组成的结构体
class SRetParam_TakeLayerPrize
	attr_accessor:dwRet#(UINT32)结果 0成功其他错误码
	attr_accessor:dwFloorID#(UINT32)最高已领奖层

	#构造函数
	def initialize
		@dwRet = 0
		@dwFloorID = 0
	end
end

#函数[GetTopPrizeLayer:获取最高已领奖层]的返回的参数组成的结构体
class SRetParam_GetTopPrizeLayer
	attr_accessor:dwFloorID#(UINT32)层数

	#构造函数
	def initialize
		@dwFloorID = 0
	end
end

#函数[ClearFightMonsterCd:清除pve战斗cd]的返回的参数组成的结构体
class SRetParam_ClearFightMonsterCd
	attr_accessor:bRet#(UINT8)0成功 其他失败

	#构造函数
	def initialize
		@bRet = 0
	end
end

#函数[GetLayerPrized:获取已领奖励层数]的返回的参数组成的结构体
class SRetParam_GetLayerPrized
	attr_accessor:vecFloorID#(UINT32数组)已领奖励层数

	#构造函数
	def initialize
		@vecFloorID = Array.new
	end
end

#协议类：锁妖塔
class DemonTowerBase < ProtocolBase
	#以下为发送函数
	#发送：进入锁妖塔 (暂时不用)
	def send_EnterDemonTower(
		dwFloorID #(UINT32)层数
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwFloorID)
		return @svrHandler.sendPacket(data)
	end

	#发送：离开锁妖塔 (暂时不用)
	def send_LeaveDemonTower(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：封印怪物(暂时不用)
	def send_SealMonster(
		dwFloorID #(UINT32)层数
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwFloorID)
		return @svrHandler.sendPacket(data)
	end

	#发送：升级魄空间
	def send_UpgradeSoulSpace(
		dwSoulSpaceID #(UINT32)魄空间类型ID
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwSoulSpaceID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取魄空间列表
	def send_GetSoulSpace(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取被攻击列表
	def send_GetAttackedList(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取每日奖励
	def send_TakeDayPrize(
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：领取每层奖励
	def send_TakeLayerPrize(
		dwFloorID #(UINT32)层数
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwFloorID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取最高已领奖层
	def send_GetTopPrizeLayer(
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：清除pve战斗cd
	def send_ClearFightMonsterCd(
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取已领奖励层数
	def send_GetLayerPrized(
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：升级魄空间通知
	def onRecv_UpgradeSoulSpaceNotify(
		dwSoulSpaceID, #(UINT32)魄空间类型ID(升级结果)
		dwSoulSpaceLevel #(UINT32)魄空间等级(升级结果)
	)
		raise NotImplementedError
	end
	#接收：魄空间列表
	def onRecv_SoulSpaceListNotify(
		vecSpaceInfo #(SSpaceInfo的数组)魄空间列表
	)
		raise NotImplementedError
	end
	#接收：每日重置奖励通知
	def onRecv_DayPrizeResetNotify(
		dwFloorID #(UINT32)层数
	)
		raise NotImplementedError
	end
	#接收：被攻击列表通知
	def onRecv_AttackListNotify(
		oDemonToweAttackedInfo #(SDemonToweAttackedInfo的数组)被攻击列表
	)
		raise NotImplementedError
	end
	#接收：被攻击通知(收到通知后拉取被攻击列表)
	def onRecv_AttackChangedNotify(
	)
		raise NotImplementedError
	end
	#接收：通关协议
	def onRecv_FloorPassNotify(
		dwFloorID #(UINT32)通关层数
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：进入锁妖塔 (暂时不用)
	def onReturn_EnterDemonTower(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_EnterDemonTower)返回的参数
	)
	end

	#返回：离开锁妖塔 (暂时不用)
	def onReturn_LeaveDemonTower(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LeaveDemonTower)返回的参数
	)
	end

	#返回：封印怪物(暂时不用)
	def onReturn_SealMonster(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SealMonster)返回的参数
	)
	end

	#返回：升级魄空间
	def onReturn_UpgradeSoulSpace(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UpgradeSoulSpace)返回的参数
	)
	end

	#返回：获取每日奖励
	def onReturn_TakeDayPrize(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakeDayPrize)返回的参数
	)
	end

	#返回：领取每层奖励
	def onReturn_TakeLayerPrize(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakeLayerPrize)返回的参数
	)
	end

	#返回：获取最高已领奖层
	def onReturn_GetTopPrizeLayer(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetTopPrizeLayer)返回的参数
	)
	end

	#返回：清除pve战斗cd
	def onReturn_ClearFightMonsterCd(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ClearFightMonsterCd)返回的参数
	)
	end

	#返回：获取已领奖励层数
	def onReturn_GetLayerPrized(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetLayerPrized)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：升级魄空间通知
	def _doRecv_UpgradeSoulSpaceNotify(data)
		dwSoulSpaceID = ByteUtil::readUINT32(data)
		dwSoulSpaceLevel = ByteUtil::readUINT32(data)
		return onRecv_UpgradeSoulSpaceNotify(dwSoulSpaceID, dwSoulSpaceLevel)
	end

	#接收处理：魄空间列表
	def _doRecv_SoulSpaceListNotify(data)
		vecSpaceInfo = SSpaceInfo::vectorFromStream(data)
		return onRecv_SoulSpaceListNotify(vecSpaceInfo)
	end

	#接收处理：每日重置奖励通知
	def _doRecv_DayPrizeResetNotify(data)
		dwFloorID = ByteUtil::readUINT32(data)
		return onRecv_DayPrizeResetNotify(dwFloorID)
	end

	#接收处理：被攻击列表通知
	def _doRecv_AttackListNotify(data)
		oDemonToweAttackedInfo = SDemonToweAttackedInfo::vectorFromStream(data)
		return onRecv_AttackListNotify(oDemonToweAttackedInfo)
	end

	#接收处理：被攻击通知(收到通知后拉取被攻击列表)
	def _doRecv_AttackChangedNotify(data)
		return onRecv_AttackChangedNotify()
	end

	#接收处理：通关协议
	def _doRecv_FloorPassNotify(data)
		dwFloorID = ByteUtil::readUINT32(data)
		return onRecv_FloorPassNotify(dwFloorID)
	end

#以下为返回处理函数
	#返回处理：进入锁妖塔 (暂时不用)
	def _doReturn_EnterDemonTower(data)
		retParam = SRetParam_EnterDemonTower.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果 0成功其他错误码
		retParam.dwRet = dwRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_EnterDemonTower(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：进入锁妖塔 (暂时不用)
	def _onTimeOut_EnterDemonTower(sessionID)
		retParam = SRetParam_EnterDemonTower.new;
		onReturn_EnterDemonTower(2, retParam)
	end

	#返回处理：离开锁妖塔 (暂时不用)
	def _doReturn_LeaveDemonTower(data)
		retParam = SRetParam_LeaveDemonTower.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果 0成功其他错误码
		retParam.dwRet = dwRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LeaveDemonTower(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：离开锁妖塔 (暂时不用)
	def _onTimeOut_LeaveDemonTower(sessionID)
		retParam = SRetParam_LeaveDemonTower.new;
		onReturn_LeaveDemonTower(2, retParam)
	end

	#返回处理：封印怪物(暂时不用)
	def _doReturn_SealMonster(data)
		retParam = SRetParam_SealMonster.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果 0成功其他错误码
		retParam.dwRet = dwRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SealMonster(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：封印怪物(暂时不用)
	def _onTimeOut_SealMonster(sessionID)
		retParam = SRetParam_SealMonster.new;
		onReturn_SealMonster(2, retParam)
	end

	#返回处理：升级魄空间
	def _doReturn_UpgradeSoulSpace(data)
		retParam = SRetParam_UpgradeSoulSpace.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果 0成功其他错误码
		retParam.dwRet = dwRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UpgradeSoulSpace(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：升级魄空间
	def _onTimeOut_UpgradeSoulSpace(sessionID)
		retParam = SRetParam_UpgradeSoulSpace.new;
		onReturn_UpgradeSoulSpace(2, retParam)
	end

	#返回处理：获取每日奖励
	def _doReturn_TakeDayPrize(data)
		retParam = SRetParam_TakeDayPrize.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果 0成功其他错误码
		retParam.dwRet = dwRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakeDayPrize(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取每日奖励
	def _onTimeOut_TakeDayPrize(sessionID)
		retParam = SRetParam_TakeDayPrize.new;
		onReturn_TakeDayPrize(2, retParam)
	end

	#返回处理：领取每层奖励
	def _doReturn_TakeLayerPrize(data)
		retParam = SRetParam_TakeLayerPrize.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果 0成功其他错误码
		dwFloorID = ByteUtil::readUINT32(data) #(UINT32)最高已领奖层
		retParam.dwRet = dwRet
		retParam.dwFloorID = dwFloorID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakeLayerPrize(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：领取每层奖励
	def _onTimeOut_TakeLayerPrize(sessionID)
		retParam = SRetParam_TakeLayerPrize.new;
		onReturn_TakeLayerPrize(2, retParam)
	end

	#返回处理：获取最高已领奖层
	def _doReturn_GetTopPrizeLayer(data)
		retParam = SRetParam_GetTopPrizeLayer.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwFloorID = ByteUtil::readUINT32(data) #(UINT32)层数
		retParam.dwFloorID = dwFloorID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetTopPrizeLayer(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取最高已领奖层
	def _onTimeOut_GetTopPrizeLayer(sessionID)
		retParam = SRetParam_GetTopPrizeLayer.new;
		onReturn_GetTopPrizeLayer(2, retParam)
	end

	#返回处理：清除pve战斗cd
	def _doReturn_ClearFightMonsterCd(data)
		retParam = SRetParam_ClearFightMonsterCd.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		bRet = ByteUtil::readUINT8(data) #(UINT8)0成功 其他失败
		retParam.bRet = bRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ClearFightMonsterCd(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：清除pve战斗cd
	def _onTimeOut_ClearFightMonsterCd(sessionID)
		retParam = SRetParam_ClearFightMonsterCd.new;
		onReturn_ClearFightMonsterCd(2, retParam)
	end

	#返回处理：获取已领奖励层数
	def _doReturn_GetLayerPrized(data)
		retParam = SRetParam_GetLayerPrized.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecFloorID = ByteUtil::readVecUINT32(data) #(UINT32数组)已领奖励层数
		retParam.vecFloorID = vecFloorID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetLayerPrized(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取已领奖励层数
	def _onTimeOut_GetLayerPrized(sessionID)
		retParam = SRetParam_GetLayerPrized.new;
		onReturn_GetLayerPrized(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 70;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_UpgradeSoulSpaceNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_SoulSpaceListNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_DayPrizeResetNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_AttackListNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_AttackChangedNotify' #FuncID: 5
		@recvFuncList[5] = '_doRecv_FloorPassNotify' #FuncID: 6

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_EnterDemonTower' #FuncID: 1
		@retFuncList[1] = '_doReturn_LeaveDemonTower' #FuncID: 2
		@retFuncList[2] = '_doReturn_SealMonster' #FuncID: 3
		@retFuncList[3] = '_doReturn_UpgradeSoulSpace' #FuncID: 4
		@retFuncList[4] = '_doReturn_TakeDayPrize' #FuncID: 5
		@retFuncList[5] = '_doReturn_TakeLayerPrize' #FuncID: 6
		@retFuncList[6] = '_doReturn_GetTopPrizeLayer' #FuncID: 7
		@retFuncList[7] = '_doReturn_ClearFightMonsterCd' #FuncID: 8
		@retFuncList[8] = '_doReturn_GetLayerPrized' #FuncID: 9

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_EnterDemonTower' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_LeaveDemonTower' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_SealMonster' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_UpgradeSoulSpace' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_TakeDayPrize' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_TakeLayerPrize' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_GetTopPrizeLayer' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_ClearFightMonsterCd' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_GetLayerPrized' #FuncID: 9
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

