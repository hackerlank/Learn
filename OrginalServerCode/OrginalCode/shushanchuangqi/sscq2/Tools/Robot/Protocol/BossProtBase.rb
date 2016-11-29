#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    BossProt.rb
#  Purpose:      BOSS相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#购买加持类型
class EBossBuyType
	EGOLD = 0#金币购买
	ESLIVER = 1#银币购买
end

#boss奖励类型
class EWorldBossPrize
	EWORLDBOSSPRIZETOP = 1#排名奖励
	EWORLDBOSSPRIZEDAMAGE = 2#伤害奖励
	EWORLDBOSSPRIZERANDOM = 3#幸运奖励
	EWORLDBOSSPRIZENPC = 4#参与奖励
	EWORLDBOSSPRIZEKILLBOSS = 5#击杀世界boss奖励
	EWORLDBOSSPRIZEBOSSHP = 6#伤害boss百分比血量奖励
end

#排行帮信息
class SPlayerInfo
	attr_accessor:dwNo #(UINT32)名次
	attr_accessor:qwUserID #(UINT64)uid
	attr_accessor:strUserName #(string)玩家名字
	attr_accessor:dwDamageHP #(UINT32)伤害的总血量
	attr_accessor:dwBossMaxHP #(UINT32)Boss的总血量

	#构造函数
	def initialize
		@dwNo = 0
		@qwUserID = 0
		@strUserName = ''
		@dwDamageHP = 0
		@dwBossMaxHP = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwNo = @dwNo
		obj.qwUserID = @qwUserID
		obj.strUserName = @strUserName
		obj.dwDamageHP = @dwDamageHP
		obj.dwBossMaxHP = @dwBossMaxHP
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPlayerInfo.new
		s.dwNo = ByteUtil::readUINT32(data)
		s.qwUserID = ByteUtil::readUINT64(data)
		s.strUserName = ByteUtil::readSTRING(data)
		s.dwDamageHP = ByteUtil::readUINT32(data)
		s.dwBossMaxHP = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPlayerInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwNo)
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeSTRING(data, @strUserName)
		ByteUtil::writeUINT32(data, @dwDamageHP)
		ByteUtil::writeUINT32(data, @dwBossMaxHP)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#货币列表
class SPrizeMoneyInfo
	attr_accessor:dwMoneyType #(UINT32)货币类型
	attr_accessor:dwMoneyValue #(UINT32)货币值

	#构造函数
	def initialize
		@dwMoneyType = 0
		@dwMoneyValue = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwMoneyType = @dwMoneyType
		obj.dwMoneyValue = @dwMoneyValue
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPrizeMoneyInfo.new
		s.dwMoneyType = ByteUtil::readUINT32(data)
		s.dwMoneyValue = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPrizeMoneyInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwMoneyType)
		ByteUtil::writeUINT32(data, @dwMoneyValue)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#货币列表
class SPrizeIteminfo
	attr_accessor:dwItemID #(UINT32)物品id
	attr_accessor:dwItemCount #(UINT32)物品数量

	#构造函数
	def initialize
		@dwItemID = 0
		@dwItemCount = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwItemID = @dwItemID
		obj.dwItemCount = @dwItemCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPrizeIteminfo.new
		s.dwItemID = ByteUtil::readUINT32(data)
		s.dwItemCount = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPrizeIteminfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwItemID)
		ByteUtil::writeUINT32(data, @dwItemCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#排行帮信息
class SPlayerPrize
	attr_accessor:dwPrizeType #(UINT8)奖励类型
	attr_accessor:vecPrizeMoneyInfo #(SPrizeMoneyInfo的数组)货币奖励
	attr_accessor:vecPrizeItemInfo #(SPrizeIteminfo的数组)物品奖励

	#构造函数
	def initialize
		@dwPrizeType = 0
		@vecPrizeMoneyInfo = Array.new
		@vecPrizeItemInfo = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwPrizeType = @dwPrizeType
		obj.vecPrizeMoneyInfo = @vecPrizeMoneyInfo
		obj.vecPrizeItemInfo = @vecPrizeItemInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPlayerPrize.new
		s.dwPrizeType = ByteUtil::readUINT8(data)
		s.vecPrizeMoneyInfo = SPrizeMoneyInfo::vectorFromStream(data)
		s.vecPrizeItemInfo = SPrizeIteminfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPlayerPrize::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @dwPrizeType)
		SPrizeMoneyInfo::vectorToStream(data, @vecPrizeMoneyInfo)
		SPrizeIteminfo::vectorToStream(data, @vecPrizeItemInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[WBAlive:世界BOSS中复活]的返回的参数组成的结构体
class SRetParam_WBAlive
	attr_accessor:bRet#(bool)结果

	#构造函数
	def initialize
		@bRet = false
	end
end

#函数[WBStrength:加持]的返回的参数组成的结构体
class SRetParam_WBStrength
	attr_accessor:dwSilverBufferCnt#(UINT32)银币加持次数
	attr_accessor:dwGoldBufferCnt#(UINT32)金币加持次数
	attr_accessor:dwSilverBufferCdTime#(UINT32)银币加持cd
	attr_accessor:bRet#(bool)结果

	#构造函数
	def initialize
		@dwSilverBufferCnt = 0
		@dwGoldBufferCnt = 0
		@dwSilverBufferCdTime = 0
		@bRet = false
	end
end

#函数[WBAttack:直接攻击boss]的返回的参数组成的结构体
class SRetParam_WBAttack
	attr_accessor:bRet#(bool)结果

	#构造函数
	def initialize
		@bRet = false
	end
end

#函数[EnterMap:进入boss地图]的返回的参数组成的结构体
class SRetParam_EnterMap
	attr_accessor:bRet#(bool)结果

	#构造函数
	def initialize
		@bRet = false
	end
end

#函数[LeaveMap:离开boss地图]的返回的参数组成的结构体
class SRetParam_LeaveMap
	attr_accessor:bRet#(bool)结果

	#构造函数
	def initialize
		@bRet = false
	end
end

#协议类：BOSS相关协议
class BossProtBase < ProtocolBase
	#以下为发送函数
	#发送：世界BOSS中复活
	def send_WBAlive(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：加持
	def send_WBStrength(
		eBuyType #(枚举类型：EBossBuyType)购买类型
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eBuyType)
		return @svrHandler.sendPacket(data)
	end

	#发送：直接攻击boss
	def send_WBAttack(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取排行榜信息
	def send_GetTopList(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取玩家自己的排行榜信息
	def send_GetSelfInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取boss信息
	def send_GetBossInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：进入boss地图
	def send_EnterMap(
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：离开boss地图
	def send_LeaveMap(
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：世界BOSS信息通知
	def onRecv_BossInfoNotify(
		dwBoosID, #(UINT32)bossID
		dwCurHP, #(UINT32)当前血量
		dwMaxHP, #(UINT32)最大血量
		dwPlayerCnt #(UINT32)当前地图人数
	)
		raise NotImplementedError
	end
	#接收：排行榜通知
	def onRecv_TopListNotify(
		vecTopList #(SPlayerInfo的数组)排行榜列表
	)
		raise NotImplementedError
	end
	#接收：个人信息通知
	def onRecv_SelfInfoNotify(
		oSelfInfo, #(类类型：SPlayerInfo)玩家信息
		dwBeginTime, #(UINT32)开始时间
		dwEndTime, #(UINT32)结束时间
		dwReliveTime, #(UINT32)复活时间
		dwSilverBufferCdTime, #(UINT32)银币加持cd
		dwSilverBufferCnt, #(UINT32)银币加持次数
		dwGoldBufferCnt, #(UINT32)金币加持次数
		dwGoldAttackCnt #(UINT32)直接攻击次数
	)
		raise NotImplementedError
	end
	#接收：伤害boss信息
	def onRecv_AtkInfoNotify(
		dwDamage, #(UINT32)本次伤害
		dwExp, #(UINT32)本次活动经验值
		dwTotalDamage, #(UINT32)总伤害
		dwBossMaxHp #(UINT32)boss最大血量
	)
		raise NotImplementedError
	end
	#接收：玩家名次变化通知
	def onRecv_NoChangeNotify(
		dwNo #(UINT32)玩家名次
	)
		raise NotImplementedError
	end
	#接收：玩家奖励获取通知
	def onRecv_PrizeNotify(
		vecPlayerPrize #(SPlayerPrize的数组)玩家奖励列表
	)
		raise NotImplementedError
	end
	#接收：玩家复活时间通知
	def onRecv_ReliveTimeNotify(
		dwReliveTime #(UINT32)复活时间
	)
		raise NotImplementedError
	end
	#接收：活动结束通知
	def onRecv_EndNotify(
		dwLeaveTime #(UINT32)离开时间
	)
		raise NotImplementedError
	end
	#接收：玩家直接攻击次数
	def onRecv_AttackCountNotify(
		dwAttackCount #(UINT16)玩家直接攻击次数
	)
		raise NotImplementedError
	end
	#接收：结算通知
	def onRecv_GainPrizeNotify(
		dwNo, #(UINT32)玩家名次
		dwExp, #(UINT32)总共获得经验
		bKillBoss #(bool)是否击杀boss
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：世界BOSS中复活
	def onReturn_WBAlive(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_WBAlive)返回的参数
	)
	end

	#返回：加持
	def onReturn_WBStrength(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_WBStrength)返回的参数
	)
	end

	#返回：直接攻击boss
	def onReturn_WBAttack(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_WBAttack)返回的参数
	)
	end

	#返回：进入boss地图
	def onReturn_EnterMap(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_EnterMap)返回的参数
	)
	end

	#返回：离开boss地图
	def onReturn_LeaveMap(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LeaveMap)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：世界BOSS信息通知
	def _doRecv_BossInfoNotify(data)
		dwBoosID = ByteUtil::readUINT32(data)
		dwCurHP = ByteUtil::readUINT32(data)
		dwMaxHP = ByteUtil::readUINT32(data)
		dwPlayerCnt = ByteUtil::readUINT32(data)
		return onRecv_BossInfoNotify(dwBoosID, dwCurHP, dwMaxHP, dwPlayerCnt)
	end

	#接收处理：排行榜通知
	def _doRecv_TopListNotify(data)
		vecTopList = SPlayerInfo::vectorFromStream(data)
		return onRecv_TopListNotify(vecTopList)
	end

	#接收处理：个人信息通知
	def _doRecv_SelfInfoNotify(data)
		oSelfInfo = SPlayerInfo::fromStream(data)
		dwBeginTime = ByteUtil::readUINT32(data)
		dwEndTime = ByteUtil::readUINT32(data)
		dwReliveTime = ByteUtil::readUINT32(data)
		dwSilverBufferCdTime = ByteUtil::readUINT32(data)
		dwSilverBufferCnt = ByteUtil::readUINT32(data)
		dwGoldBufferCnt = ByteUtil::readUINT32(data)
		dwGoldAttackCnt = ByteUtil::readUINT32(data)
		return onRecv_SelfInfoNotify(oSelfInfo, dwBeginTime, dwEndTime, dwReliveTime, dwSilverBufferCdTime, dwSilverBufferCnt, dwGoldBufferCnt, dwGoldAttackCnt)
	end

	#接收处理：伤害boss信息
	def _doRecv_AtkInfoNotify(data)
		dwDamage = ByteUtil::readUINT32(data)
		dwExp = ByteUtil::readUINT32(data)
		dwTotalDamage = ByteUtil::readUINT32(data)
		dwBossMaxHp = ByteUtil::readUINT32(data)
		return onRecv_AtkInfoNotify(dwDamage, dwExp, dwTotalDamage, dwBossMaxHp)
	end

	#接收处理：玩家名次变化通知
	def _doRecv_NoChangeNotify(data)
		dwNo = ByteUtil::readUINT32(data)
		return onRecv_NoChangeNotify(dwNo)
	end

	#接收处理：玩家奖励获取通知
	def _doRecv_PrizeNotify(data)
		vecPlayerPrize = SPlayerPrize::vectorFromStream(data)
		return onRecv_PrizeNotify(vecPlayerPrize)
	end

	#接收处理：玩家复活时间通知
	def _doRecv_ReliveTimeNotify(data)
		dwReliveTime = ByteUtil::readUINT32(data)
		return onRecv_ReliveTimeNotify(dwReliveTime)
	end

	#接收处理：活动结束通知
	def _doRecv_EndNotify(data)
		dwLeaveTime = ByteUtil::readUINT32(data)
		return onRecv_EndNotify(dwLeaveTime)
	end

	#接收处理：玩家直接攻击次数
	def _doRecv_AttackCountNotify(data)
		dwAttackCount = ByteUtil::readUINT16(data)
		return onRecv_AttackCountNotify(dwAttackCount)
	end

	#接收处理：结算通知
	def _doRecv_GainPrizeNotify(data)
		dwNo = ByteUtil::readUINT32(data)
		dwExp = ByteUtil::readUINT32(data)
		bKillBoss = ByteUtil::readBOOL(data)
		return onRecv_GainPrizeNotify(dwNo, dwExp, bKillBoss)
	end

#以下为返回处理函数
	#返回处理：世界BOSS中复活
	def _doReturn_WBAlive(data)
		retParam = SRetParam_WBAlive.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		bRet = ByteUtil::readBOOL(data) #(bool)结果
		retParam.bRet = bRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_WBAlive(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：世界BOSS中复活
	def _onTimeOut_WBAlive(sessionID)
		retParam = SRetParam_WBAlive.new;
		onReturn_WBAlive(2, retParam)
	end

	#返回处理：加持
	def _doReturn_WBStrength(data)
		retParam = SRetParam_WBStrength.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwSilverBufferCnt = ByteUtil::readUINT32(data) #(UINT32)银币加持次数
		dwGoldBufferCnt = ByteUtil::readUINT32(data) #(UINT32)金币加持次数
		dwSilverBufferCdTime = ByteUtil::readUINT32(data) #(UINT32)银币加持cd
		bRet = ByteUtil::readBOOL(data) #(bool)结果
		retParam.dwSilverBufferCnt = dwSilverBufferCnt
		retParam.dwGoldBufferCnt = dwGoldBufferCnt
		retParam.dwSilverBufferCdTime = dwSilverBufferCdTime
		retParam.bRet = bRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_WBStrength(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：加持
	def _onTimeOut_WBStrength(sessionID)
		retParam = SRetParam_WBStrength.new;
		onReturn_WBStrength(2, retParam)
	end

	#返回处理：直接攻击boss
	def _doReturn_WBAttack(data)
		retParam = SRetParam_WBAttack.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		bRet = ByteUtil::readBOOL(data) #(bool)结果
		retParam.bRet = bRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_WBAttack(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：直接攻击boss
	def _onTimeOut_WBAttack(sessionID)
		retParam = SRetParam_WBAttack.new;
		onReturn_WBAttack(2, retParam)
	end

	#返回处理：进入boss地图
	def _doReturn_EnterMap(data)
		retParam = SRetParam_EnterMap.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		bRet = ByteUtil::readBOOL(data) #(bool)结果
		retParam.bRet = bRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_EnterMap(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：进入boss地图
	def _onTimeOut_EnterMap(sessionID)
		retParam = SRetParam_EnterMap.new;
		onReturn_EnterMap(2, retParam)
	end

	#返回处理：离开boss地图
	def _doReturn_LeaveMap(data)
		retParam = SRetParam_LeaveMap.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		bRet = ByteUtil::readBOOL(data) #(bool)结果
		retParam.bRet = bRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LeaveMap(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：离开boss地图
	def _onTimeOut_LeaveMap(sessionID)
		retParam = SRetParam_LeaveMap.new;
		onReturn_LeaveMap(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 25;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_BossInfoNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_TopListNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_SelfInfoNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_AtkInfoNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_NoChangeNotify' #FuncID: 5
		@recvFuncList[5] = '_doRecv_PrizeNotify' #FuncID: 6
		@recvFuncList[6] = '_doRecv_ReliveTimeNotify' #FuncID: 7
		@recvFuncList[7] = '_doRecv_EndNotify' #FuncID: 8
		@recvFuncList[8] = '_doRecv_AttackCountNotify' #FuncID: 9
		@recvFuncList[9] = '_doRecv_GainPrizeNotify' #FuncID: 10

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_WBAlive' #FuncID: 1
		@retFuncList[1] = '_doReturn_WBStrength' #FuncID: 2
		@retFuncList[2] = '_doReturn_WBAttack' #FuncID: 3
		@retFuncList[3] = '_doReturn_EnterMap' #FuncID: 4
		@retFuncList[4] = '_doReturn_LeaveMap' #FuncID: 5

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_WBAlive' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_WBStrength' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_WBAttack' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_EnterMap' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_LeaveMap' #FuncID: 5
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

