#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    Game2CenterDemonTower.rb
#  Purpose:      GameServer到CenterServer关于镇妖塔的通信协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './DemonTowerBase.rb'

#以下为类型定义

#进入镇妖塔玩家信息
class SDemonTowerEnterPlayer
	attr_accessor:qwUserID #(UINT64)账号Id
	attr_accessor:qwRoleID #(UINT64)角色Id
	attr_accessor:strName #(string)角色名
	attr_accessor:dwFloorID #(UINT32)楼层
	attr_accessor:bySex #(UINT8)性别
	attr_accessor:byLevel #(UINT16)等级
	attr_accessor:dwCareer #(UINT32)职业
	attr_accessor:dwPower #(UINT32)战斗力

	#构造函数
	def initialize
		@qwUserID = 0
		@qwRoleID = 0
		@strName = ''
		@dwFloorID = 0
		@bySex = 0
		@byLevel = 0
		@dwCareer = 0
		@dwPower = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwUserID = @qwUserID
		obj.qwRoleID = @qwRoleID
		obj.strName = @strName
		obj.dwFloorID = @dwFloorID
		obj.bySex = @bySex
		obj.byLevel = @byLevel
		obj.dwCareer = @dwCareer
		obj.dwPower = @dwPower
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDemonTowerEnterPlayer.new
		s.qwUserID = ByteUtil::readUINT64(data)
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.dwFloorID = ByteUtil::readUINT32(data)
		s.bySex = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT16(data)
		s.dwCareer = ByteUtil::readUINT32(data)
		s.dwPower = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDemonTowerEnterPlayer::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT32(data, @dwFloorID)
		ByteUtil::writeUINT8(data, @bySex)
		ByteUtil::writeUINT16(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwCareer)
		ByteUtil::writeUINT32(data, @dwPower)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#镇妖塔玩家击败怪物信息
class SDemonTowerPassPlayer
	attr_accessor:dwCurFloorID #(UINT32)当前楼层
	attr_accessor:qwUserID #(UINT64)账号Id
	attr_accessor:dwPower #(UINT32)战斗力
	attr_accessor:wTurns #(UINT16)回合数
	attr_accessor:qwReportID #(UINT64)战报id

	#构造函数
	def initialize
		@dwCurFloorID = 0
		@qwUserID = 0
		@dwPower = 0
		@wTurns = 0
		@qwReportID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwCurFloorID = @dwCurFloorID
		obj.qwUserID = @qwUserID
		obj.dwPower = @dwPower
		obj.wTurns = @wTurns
		obj.qwReportID = @qwReportID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDemonTowerPassPlayer.new
		s.dwCurFloorID = ByteUtil::readUINT32(data)
		s.qwUserID = ByteUtil::readUINT64(data)
		s.dwPower = ByteUtil::readUINT32(data)
		s.wTurns = ByteUtil::readUINT16(data)
		s.qwReportID = ByteUtil::readUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDemonTowerPassPlayer::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwCurFloorID)
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeUINT32(data, @dwPower)
		ByteUtil::writeUINT16(data, @wTurns)
		ByteUtil::writeUINT64(data, @qwReportID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetAttackedLayerInfo:获取玩家被攻击信息列表]的返回的参数组成的结构体
class SRetParam_GetAttackedLayerInfo
	attr_accessor:qwUserID#(UINT64)玩家账号
	attr_accessor:oAttackedList#(SDemonToweAttackedInfo的数组)被攻击列表

	#构造函数
	def initialize
		@qwUserID = 0
		@oAttackedList = Array.new
	end
end

#协议类：GameServer到CenterServer关于镇妖塔的通信协议
class Game2CenterDemonTowerBase < ProtocolBase
	#以下为发送函数
	#发送：玩家进入镇妖塔
	def send_OnEnterDemonTower(
		oDemonTowerEnterPlayer #(类类型：SDemonTowerEnterPlayer)进入镇妖塔玩家信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		oDemonTowerEnterPlayer.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家离开镇妖塔
	def send_OnLeaveDemonTower(
		qwUserID #(UINT64)玩家账号
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUserID)
		return @svrHandler.sendPacket(data)
	end

	#发送：镇妖塔过关
	def send_OnPassDemonTower(
		qwUserID,  #(UINT64)玩家账号
		wFloorID,  #(UINT16)过关层数
		wMonsterColor,  #(UINT16)怪物颜色
		strMonsterName #(string)封印怪物
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeUINT16(data, wFloorID)
		ByteUtil::writeUINT16(data, wMonsterColor)
		ByteUtil::writeSTRING(data, strMonsterName)
		return @svrHandler.sendPacket(data)
	end

	#发送：击败锁妖塔怪物
	def send_OnKillMonster(
		oDemonTowerPassPlayer #(类类型：SDemonTowerPassPlayer)镇妖塔玩家击败怪物信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		oDemonTowerPassPlayer.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：19点重置事件
	def send_OnPlayerReset(
		qwUserID #(UINT64)玩家账号
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUserID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家进入下一层
	def send_OnPlayerEnterNextFloor(
		qwUserID #(UINT64)玩家账号
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUserID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家进入请求
	def send_PlayerEnterFloorRequest(
		qwUserID,  #(UINT64)玩家账号
		dwFloorID #(UINT32)层数
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeUINT32(data, dwFloorID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取玩家被攻击信息列表
	def send_GetAttackedLayerInfo(
		qwUserID,  #(UINT64)玩家账号
		oAttackedList #(SDemonToweAttackedInfo的数组)被攻击列表
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwUserID)
		SDemonToweAttackedInfo::vectorToStream(data, oAttackedList)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：玩家请求进入镇妖塔
	def onRecv_EnterDemonTower(
		qwUserID, #(UINT64)帐号ID
		dwFloorID #(UINT32)层数
	)
		raise NotImplementedError
	end
	#接收：玩家请求离开镇妖塔
	def onRecv_LeaveDemonTower(
		qwUsrID #(UINT64)帐号ID
	)
		raise NotImplementedError
	end
	#接收：获取每日魂值奖励
	def onRecv_TakeDailyPrize(
		qwUsrID #(UINT64)帐号ID
	)
		raise NotImplementedError
	end
	#接收：被攻击信息
	def onRecv_Attacked(
		qwUsrID, #(UINT64)帐号ID
		oAttacker #(类类型：DemonTower::SDemonToweAttackedInfo)被攻击信息
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取玩家被攻击信息列表
	def onReturn_GetAttackedLayerInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAttackedLayerInfo)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：玩家请求进入镇妖塔
	def _doRecv_EnterDemonTower(data)
		qwUserID = ByteUtil::readUINT64(data)
		dwFloorID = ByteUtil::readUINT32(data)
		return onRecv_EnterDemonTower(qwUserID, dwFloorID)
	end

	#接收处理：玩家请求离开镇妖塔
	def _doRecv_LeaveDemonTower(data)
		qwUsrID = ByteUtil::readUINT64(data)
		return onRecv_LeaveDemonTower(qwUsrID)
	end

	#接收处理：获取每日魂值奖励
	def _doRecv_TakeDailyPrize(data)
		qwUsrID = ByteUtil::readUINT64(data)
		return onRecv_TakeDailyPrize(qwUsrID)
	end

	#接收处理：被攻击信息
	def _doRecv_Attacked(data)
		qwUsrID = ByteUtil::readUINT64(data)
		oAttacker = SDemonToweAttackedInfo::fromStream(data)
		return onRecv_Attacked(qwUsrID, oAttacker)
	end

#以下为返回处理函数
	#返回处理：获取玩家被攻击信息列表
	def _doReturn_GetAttackedLayerInfo(data)
		retParam = SRetParam_GetAttackedLayerInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		qwUserID = ByteUtil::readUINT64(data) #(UINT64)玩家账号
		oAttackedList = SDemonToweAttackedInfo::vectorFromStream(data) #(SDemonToweAttackedInfo的数组)被攻击列表
		retParam.qwUserID = qwUserID
		retParam.oAttackedList = oAttackedList
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAttackedLayerInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取玩家被攻击信息列表
	def _onTimeOut_GetAttackedLayerInfo(sessionID)
		retParam = SRetParam_GetAttackedLayerInfo.new;
		onReturn_GetAttackedLayerInfo(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 73;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_EnterDemonTower' #FuncID: 1
		@recvFuncList[1] = '_doRecv_LeaveDemonTower' #FuncID: 2
		@recvFuncList[2] = '_doRecv_TakeDailyPrize' #FuncID: 3
		@recvFuncList[3] = '_doRecv_Attacked' #FuncID: 4

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetAttackedLayerInfo' #FuncID: 1

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetAttackedLayerInfo' #FuncID: 1
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

