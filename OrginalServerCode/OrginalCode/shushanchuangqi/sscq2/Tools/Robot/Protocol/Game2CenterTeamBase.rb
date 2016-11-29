#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    Game2CenterTeam.rb
#  Purpose:      GameServer到CenterServer关于Team的通信协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './BattleGSBase.rb'
require_relative './TeamGSBase.rb'

#以下为类型定义

#请求结果
class EPlayerTeam
	EPLAYERENTERTEAM = 0#玩家进入队伍
	EPLAYERLEAVETEAM = 1#玩家离开队伍
end

#一个战报
class BattleReport
	attr_accessor:qwBattleID #(UINT64)战报ID
	attr_accessor:strBattle #(string)战报
	attr_accessor:wMonsterGroup #(UINT16)怪物组
	attr_accessor:bySuc #(UINT8)是否胜利

	#构造函数
	def initialize
		@qwBattleID = 0
		@strBattle = ''
		@wMonsterGroup = 0
		@bySuc = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwBattleID = @qwBattleID
		obj.strBattle = @strBattle
		obj.wMonsterGroup = @wMonsterGroup
		obj.bySuc = @bySuc
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = BattleReport.new
		s.qwBattleID = ByteUtil::readUINT64(data)
		s.strBattle = ByteUtil::readSTRING(data)
		s.wMonsterGroup = ByteUtil::readUINT16(data)
		s.bySuc = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = BattleReport::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwBattleID)
		ByteUtil::writeSTRING(data, @strBattle)
		ByteUtil::writeUINT16(data, @wMonsterGroup)
		ByteUtil::writeUINT8(data, @bySuc)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#一场战斗结果
class TeamReport
	attr_accessor:vecReport #(BattleReport的数组)战报序列
	attr_accessor:bySuc #(UINT8)是否胜利
	attr_accessor:wTurns #(UINT16)总回合数
	attr_accessor:qwLeaderID #(UINT64)队长ID
	attr_accessor:qwLeaderFighter #(UINT64)队长主将

	#构造函数
	def initialize
		@vecReport = Array.new
		@bySuc = 0
		@wTurns = 0
		@qwLeaderID = 0
		@qwLeaderFighter = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.vecReport = @vecReport
		obj.bySuc = @bySuc
		obj.wTurns = @wTurns
		obj.qwLeaderID = @qwLeaderID
		obj.qwLeaderFighter = @qwLeaderFighter
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = TeamReport.new
		s.vecReport = BattleReport::vectorFromStream(data)
		s.bySuc = ByteUtil::readUINT8(data)
		s.wTurns = ByteUtil::readUINT16(data)
		s.qwLeaderID = ByteUtil::readUINT64(data)
		s.qwLeaderFighter = ByteUtil::readUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = TeamReport::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		BattleReport::vectorToStream(data, @vecReport)
		ByteUtil::writeUINT8(data, @bySuc)
		ByteUtil::writeUINT16(data, @wTurns)
		ByteUtil::writeUINT64(data, @qwLeaderID)
		ByteUtil::writeUINT64(data, @qwLeaderFighter)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#协议类：GameServer到CenterServer关于Team的通信协议
class Game2CenterTeamBase < ProtocolBase
	#以下为发送函数
	#发送：同步队伍成员
	def send_SynTeamFighter(
		qwUsrID,  #(UINT64)帐号ID
		vecFighter #(TeamFighter的数组)战斗对象
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		TeamFighter::superVectorToStream(data, vecFighter)
		return @svrHandler.sendPacket(data)
	end

	#发送：同步增加美女,如果原来有美女，替换
	def send_SynTeamAddBeauty(
		qwUsrID,  #(UINT64)帐号ID
		vecFighter #(TeamFighter的数组)战斗对象
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		TeamFighter::superVectorToStream(data, vecFighter)
		return @svrHandler.sendPacket(data)
	end

	#发送：同步删除美女
	def send_SynTeamDelBeauty(
		qwUsrID #(UINT64)帐号ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		return @svrHandler.sendPacket(data)
	end

	#发送：同步奖励系数
	def send_SynRewardRate(
		dwRewardRate #(UINT32)奖励系数万分比
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, dwRewardRate)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：玩家请求加入，创建队伍
	def onRecv_CanEnterCreateTeam(
		qwUsrID, #(UINT64)帐号ID
		byHeroNum, #(UINT8)0,不需要将，>0，需要主将，散仙数量：byHeroNum，美女
		wDgnType #(UINT16)副本模板
	)
		raise NotImplementedError
	end
	#接收：玩家加入/离开队伍信息同步
	def onRecv_SynTeam(
		qwUsrID, #(UINT64)帐号ID
		eStatus #(枚举类型：EPlayerTeam)玩家操作
	)
		raise NotImplementedError
	end
	#接收：根据实例拉取将外观
	def onRecv_GetFighterFeatureByInsID(
		qwUsrID, #(UINT64)帐号ID
		qwFighterID #(UINT64)将ID
	)
		raise NotImplementedError
	end
	#接收：获取玩家战斗信息
	def onRecv_GetPlayerBattleInfo(
		qwUsrID, #(UINT64)帐号ID
		byPlayerPos, #(UINT8)玩家所在的队伍位置
		vecFigther, #(UINT64数组)散仙唯一ID
		vecPos, #(UINT8数组)玩家序列位置
		byNeedBeauty, #(UINT8)0,不需要美女，1需要美女
		wDgnType #(UINT16)副本类型
	)
		raise NotImplementedError
	end
	#接收：请求发起战斗
	def onRecv_StartBattle(
		qwUsrID, #(UINT64)队长ID
		wDgnType, #(UINT16)副本类型
		vecFighter #(SBattleFighter的数组)其他服战斗对象
	)
		raise NotImplementedError
	end
	#接收：通告战斗结果
	def onRecv_NoticeTeamReport(
		qwUsrID, #(UINT64)帐号ID
		wDgnType, #(UINT16)副本类型
		stTeamReport, #(类类型：TeamReport)副本类型
		dwRewardRate #(UINT32)奖励系数
	)
		raise NotImplementedError
	end
#以下为接收处理函数
	#接收处理：玩家请求加入，创建队伍
	def _doRecv_CanEnterCreateTeam(data)
		qwUsrID = ByteUtil::readUINT64(data)
		byHeroNum = ByteUtil::readUINT8(data)
		wDgnType = ByteUtil::readUINT16(data)
		return onRecv_CanEnterCreateTeam(qwUsrID, byHeroNum, wDgnType)
	end

	#接收处理：玩家加入/离开队伍信息同步
	def _doRecv_SynTeam(data)
		qwUsrID = ByteUtil::readUINT64(data)
		eStatus = ByteUtil::readUINT8(data)
		return onRecv_SynTeam(qwUsrID, eStatus)
	end

	#接收处理：根据实例拉取将外观
	def _doRecv_GetFighterFeatureByInsID(data)
		qwUsrID = ByteUtil::readUINT64(data)
		qwFighterID = ByteUtil::readUINT64(data)
		return onRecv_GetFighterFeatureByInsID(qwUsrID, qwFighterID)
	end

	#接收处理：获取玩家战斗信息
	def _doRecv_GetPlayerBattleInfo(data)
		qwUsrID = ByteUtil::readUINT64(data)
		byPlayerPos = ByteUtil::readUINT8(data)
		vecFigther = ByteUtil::readVecUINT64(data)
		vecPos = ByteUtil::readVecUINT8(data)
		byNeedBeauty = ByteUtil::readUINT8(data)
		wDgnType = ByteUtil::readUINT16(data)
		return onRecv_GetPlayerBattleInfo(qwUsrID, byPlayerPos, vecFigther, vecPos, byNeedBeauty, wDgnType)
	end

	#接收处理：请求发起战斗
	def _doRecv_StartBattle(data)
		qwUsrID = ByteUtil::readUINT64(data)
		wDgnType = ByteUtil::readUINT16(data)
		vecFighter = SBattleFighter::vectorFromStream(data)
		return onRecv_StartBattle(qwUsrID, wDgnType, vecFighter)
	end

	#接收处理：通告战斗结果
	def _doRecv_NoticeTeamReport(data)
		qwUsrID = ByteUtil::readUINT64(data)
		wDgnType = ByteUtil::readUINT16(data)
		stTeamReport = TeamReport::fromStream(data)
		dwRewardRate = ByteUtil::readUINT32(data)
		return onRecv_NoticeTeamReport(qwUsrID, wDgnType, stTeamReport, dwRewardRate)
	end

	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 57;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_CanEnterCreateTeam' #FuncID: 1
		@recvFuncList[1] = '_doRecv_SynTeam' #FuncID: 2
		@recvFuncList[2] = '_doRecv_GetFighterFeatureByInsID' #FuncID: 3
		@recvFuncList[3] = '_doRecv_GetPlayerBattleInfo' #FuncID: 4
		@recvFuncList[4] = '_doRecv_StartBattle' #FuncID: 5
		@recvFuncList[5] = '_doRecv_NoticeTeamReport' #FuncID: 6
	end

	def handleMessage(data)
		funcID = ByteUtil::readINT8(data);
		if funcID == 0 || funcID > @recvFuncList.length
			return false
		end
		if funcID > 0 
			func = @recvFuncList[funcID - 1]
		end
		if func
			 send(func, data)
		end
		#if func != nil
			#return call_user_func(Array.new(self, func), data)
		#end
		return true
	end
end

