#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    Game2CenterGuildBattle.rb
#  Purpose:      帮派战相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './GuildBattleProtBase.rb'
require_relative './NewGuildBattleProtBase.rb'

#以下为类型定义

#帮派战玩家分数信息
class SMemberScore
	attr_accessor:qwRoleID #(UINT64)成员角色ID
	attr_accessor:dwScore #(UINT32)积分

	#构造函数
	def initialize
		@qwRoleID = 0
		@dwScore = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.dwScore = @dwScore
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMemberScore.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.dwScore = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMemberScore::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT32(data, @dwScore)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[UserSignUp:帮派战用户报名]的返回的参数组成的结构体
class SRetParam_UserSignUp
	attr_accessor:qwGuildID#(UINT64)帮派ID
	attr_accessor:wLevel#(UINT16)帮派等级
	attr_accessor:strGuildName#(string)帮派名称
	attr_accessor:dwScore#(UINT32)帮派战积分
	attr_accessor:eResult#(枚类型：GuildBattleProt::EGBSignUpResult)玩家报名结果

	#构造函数
	def initialize
		@qwGuildID = 0
		@wLevel = 0
		@strGuildName = ''
		@dwScore = 0
		@eResult = 0
	end
end

#函数[GetAuthority:是否有帮派战操作权限]的返回的参数组成的结构体
class SRetParam_GetAuthority
	attr_accessor:bHasAuthority#(bool)是否有帮派战操作权限

	#构造函数
	def initialize
		@bHasAuthority = false
	end
end

#函数[GetPanelInfo:获取帮派战相关面板信息]的返回的参数组成的结构体
class SRetParam_GetPanelInfo
	attr_accessor:dwSelfScore#(UINT32)我的积分
	attr_accessor:dwGuildScore#(UINT32)帮派积分
	attr_accessor:dwGuildRank#(UINT32)帮派排名

	#构造函数
	def initialize
		@dwSelfScore = 0
		@dwGuildScore = 0
		@dwGuildRank = 0
	end
end

#函数[NewGetGuildID:获取帮派ID]的返回的参数组成的结构体
class SRetParam_NewGetGuildID
	attr_accessor:qwGuildID#(UINT64)帮派ID
	attr_accessor:strGuildName#(string)帮派名称
	attr_accessor:byGuildLvl#(UINT8)帮派等级

	#构造函数
	def initialize
		@qwGuildID = 0
		@strGuildName = ''
		@byGuildLvl = 0
	end
end

#协议类：帮派战相关协议
class Game2CenterGuildBattleBase < ProtocolBase
	#以下为发送函数
	#发送：帮派战状态设定
	def send_SetState(
		eState #(枚类型：GuildBattleProt::EGBState)当前帮派战状态
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eState)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派战用户报名
	def send_UserSignUp(
		qwRoleID #(UINT64)玩家ID
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派战相关广播
	def send_InfoNotify(
		qwGuildID,  #(UINT64)帮派对应ID
		wMsgID,  #(UINT16)消息ID
		vecStr #(string数组)聊天信息参数
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwGuildID)
		ByteUtil::writeUINT16(data, wMsgID)
		ByteUtil::writeVecSTRING(data, vecStr)
		return @svrHandler.sendPacket(data)
	end

	#发送：是否有帮派战操作权限
	def send_GetAuthority(
		qwRoleID #(UINT64)玩家ID
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：增加帮派战积分
	def send_AddScore(
		qwGuildID,  #(UINT64)帮派ID
		dwScore,  #(UINT32)帮派战积分
		vecMemberScore #(SMemberScore的数组)玩家获得积分
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwGuildID)
		ByteUtil::writeUINT32(data, dwScore)
		SMemberScore::vectorToStream(data, vecMemberScore)
		return @svrHandler.sendPacket(data)
	end

	#发送：增加帮派战帮派积分
	def send_AddGuildScore(
		qwGuildID,  #(UINT64)帮派ID
		dwScore #(UINT32)帮派战积分
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwGuildID)
		ByteUtil::writeUINT32(data, dwScore)
		return @svrHandler.sendPacket(data)
	end

	#发送：增加帮派战成员积分
	def send_AddMemberScore(
		qwGuildID,  #(UINT64)帮派ID
		vecMemberScore #(SMemberScore的数组)玩家获得积分
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwGuildID)
		SMemberScore::vectorToStream(data, vecMemberScore)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取帮派战相关面板信息
	def send_GetPanelInfo(
		qwRoleID #(UINT64)玩家ID
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新帮派战积分排名
	def send_SyncGuildRank(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派战状态设定
	def send_NewSetState(
		eState #(枚类型：NewGuildBattleProt::ENGBState)当前帮派战状态
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eState)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取帮派ID
	def send_NewGetGuildID(
		qwRoleID #(UINT64)玩家ID
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：帮派等级更新
	def onRecv_GuildLevelChanged(
		qwGuildID, #(UINT64)帮派对应ID
		wLevel #(UINT16)帮派等级
	)
		raise NotImplementedError
	end
	#接收：帮主更新
	def onRecv_GuildOwnerChanged(
		qwGuildID, #(UINT64)帮派对应ID
		strGuildOwnerName #(string)帮主名称
	)
		raise NotImplementedError
	end
	#接收：帮派解散
	def onRecv_GuildDisband(
		qwGuildID #(UINT64)帮派对应ID
	)
		raise NotImplementedError
	end
	#接收：可以发送新帮派战数据
	def onRecv_ReadyToSendNewGuildBattle(
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：帮派战用户报名
	def onReturn_UserSignUp(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UserSignUp)返回的参数
	)
	end

	#返回：是否有帮派战操作权限
	def onReturn_GetAuthority(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAuthority)返回的参数
	)
	end

	#返回：获取帮派战相关面板信息
	def onReturn_GetPanelInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetPanelInfo)返回的参数
	)
	end

	#返回：获取帮派ID
	def onReturn_NewGetGuildID(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_NewGetGuildID)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：帮派等级更新
	def _doRecv_GuildLevelChanged(data)
		qwGuildID = ByteUtil::readUINT64(data)
		wLevel = ByteUtil::readUINT16(data)
		return onRecv_GuildLevelChanged(qwGuildID, wLevel)
	end

	#接收处理：帮主更新
	def _doRecv_GuildOwnerChanged(data)
		qwGuildID = ByteUtil::readUINT64(data)
		strGuildOwnerName = ByteUtil::readSTRING(data)
		return onRecv_GuildOwnerChanged(qwGuildID, strGuildOwnerName)
	end

	#接收处理：帮派解散
	def _doRecv_GuildDisband(data)
		qwGuildID = ByteUtil::readUINT64(data)
		return onRecv_GuildDisband(qwGuildID)
	end

	#接收处理：可以发送新帮派战数据
	def _doRecv_ReadyToSendNewGuildBattle(data)
		return onRecv_ReadyToSendNewGuildBattle()
	end

#以下为返回处理函数
	#返回处理：帮派战用户报名
	def _doReturn_UserSignUp(data)
		retParam = SRetParam_UserSignUp.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		qwGuildID = ByteUtil::readUINT64(data) #(UINT64)帮派ID
		wLevel = ByteUtil::readUINT16(data) #(UINT16)帮派等级
		strGuildName = ByteUtil::readSTRING(data) #(string)帮派名称
		dwScore = ByteUtil::readUINT32(data) #(UINT32)帮派战积分
		eResult = ByteUtil::readUINT8(data) #(枚类型：GuildBattleProt::EGBSignUpResult)玩家报名结果
		retParam.qwGuildID = qwGuildID
		retParam.wLevel = wLevel
		retParam.strGuildName = strGuildName
		retParam.dwScore = dwScore
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UserSignUp(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：帮派战用户报名
	def _onTimeOut_UserSignUp(sessionID)
		retParam = SRetParam_UserSignUp.new;
		onReturn_UserSignUp(2, retParam)
	end

	#返回处理：是否有帮派战操作权限
	def _doReturn_GetAuthority(data)
		retParam = SRetParam_GetAuthority.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		bHasAuthority = ByteUtil::readBOOL(data) #(bool)是否有帮派战操作权限
		retParam.bHasAuthority = bHasAuthority
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAuthority(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：是否有帮派战操作权限
	def _onTimeOut_GetAuthority(sessionID)
		retParam = SRetParam_GetAuthority.new;
		onReturn_GetAuthority(2, retParam)
	end

	#返回处理：获取帮派战相关面板信息
	def _doReturn_GetPanelInfo(data)
		retParam = SRetParam_GetPanelInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwSelfScore = ByteUtil::readUINT32(data) #(UINT32)我的积分
		dwGuildScore = ByteUtil::readUINT32(data) #(UINT32)帮派积分
		dwGuildRank = ByteUtil::readUINT32(data) #(UINT32)帮派排名
		retParam.dwSelfScore = dwSelfScore
		retParam.dwGuildScore = dwGuildScore
		retParam.dwGuildRank = dwGuildRank
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetPanelInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取帮派战相关面板信息
	def _onTimeOut_GetPanelInfo(sessionID)
		retParam = SRetParam_GetPanelInfo.new;
		onReturn_GetPanelInfo(2, retParam)
	end

	#返回处理：获取帮派ID
	def _doReturn_NewGetGuildID(data)
		retParam = SRetParam_NewGetGuildID.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		qwGuildID = ByteUtil::readUINT64(data) #(UINT64)帮派ID
		strGuildName = ByteUtil::readSTRING(data) #(string)帮派名称
		byGuildLvl = ByteUtil::readUINT8(data) #(UINT8)帮派等级
		retParam.qwGuildID = qwGuildID
		retParam.strGuildName = strGuildName
		retParam.byGuildLvl = byGuildLvl
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_NewGetGuildID(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取帮派ID
	def _onTimeOut_NewGetGuildID(sessionID)
		retParam = SRetParam_NewGetGuildID.new;
		onReturn_NewGetGuildID(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 77;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_GuildLevelChanged' #FuncID: 1
		@recvFuncList[1] = '_doRecv_GuildOwnerChanged' #FuncID: 2
		@recvFuncList[2] = '_doRecv_GuildDisband' #FuncID: 3
		@recvFuncList[3] = '_doRecv_ReadyToSendNewGuildBattle' #FuncID: 4

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_UserSignUp' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetAuthority' #FuncID: 2
		@retFuncList[2] = '_doReturn_GetPanelInfo' #FuncID: 3
		@retFuncList[3] = '_doReturn_NewGetGuildID' #FuncID: 4

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_UserSignUp' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetAuthority' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GetPanelInfo' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_NewGetGuildID' #FuncID: 4
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

