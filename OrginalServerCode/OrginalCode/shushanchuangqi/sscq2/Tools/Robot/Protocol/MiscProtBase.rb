#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    MiscProt.rb
#  Purpose:      不好归类的小协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#购买体力错误码
class EBuyActionRet
	EBUYACTIONRET_SUCESS = 0#成功
	EBUYACTIONRET_MAXACTION = 1#体力已满
	EBUYACTIONRET_MONEYLIMIT = 2#仙元不足
	EBUYACTIONRET_COUNTLIMIT = 3#购买次数限制
	EBUYACTIONRET_VIPCFGERROR = 4#vip配置出错
end

#操作结果
class EMiscOptRes
	EMISCOPTRES_SUCESS = 0#成功
	EMISCOPTRES_ERROR = 1#失败
end

#抽奖操作结果
class ELotteryRes
	ELOTTERYRES_SUCESS = 0#成功
	ELOTTERYRES_PACKFUL = 1#背包满
	ELOTTERYRES_LACKMONEY = 2#缺钱
	ELOTTERYRES_ERROR = 3#失败
end

#每日冲值领奖奖励
class EEveryDayReChargeAward
	EEVERYDAYRECHARGEAWARD_SUCESS = 0#成功
	EEVERYDAYRECHARGEAWARD_LOWMONEY = 1#今日冲值不足
	EEVERYDAYRECHARGEAWARD_HASDONE = 2#今日已经领奖
	EEVERYDAYRECHARGEAWARD_NOAWARD = 3#今日无奖
end

#刷宝箱信息
class SGodChestInfo
	attr_accessor:byState #(UINT8)状态
	attr_accessor:byRount #(UINT8)回合数
	attr_accessor:dwTime #(UINT32)倒计时数
	attr_accessor:dwEnd #(UINT32)活动结束时间

	#构造函数
	def initialize
		@byState = 0
		@byRount = 0
		@dwTime = 0
		@dwEnd = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byState = @byState
		obj.byRount = @byRount
		obj.dwTime = @dwTime
		obj.dwEnd = @dwEnd
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGodChestInfo.new
		s.byState = ByteUtil::readUINT8(data)
		s.byRount = ByteUtil::readUINT8(data)
		s.dwTime = ByteUtil::readUINT32(data)
		s.dwEnd = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGodChestInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byState)
		ByteUtil::writeUINT8(data, @byRount)
		ByteUtil::writeUINT32(data, @dwTime)
		ByteUtil::writeUINT32(data, @dwEnd)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#抽奖信息
class SLotteryInfo
	attr_accessor:strName #(string)玩家
	attr_accessor:dwLotteryID #(UINT32)奖励ID(对应配置表)

	#构造函数
	def initialize
		@strName = ''
		@dwLotteryID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strName = @strName
		obj.dwLotteryID = @dwLotteryID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SLotteryInfo.new
		s.strName = ByteUtil::readSTRING(data)
		s.dwLotteryID = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SLotteryInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT32(data, @dwLotteryID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[BuyAction:购买体力]的返回的参数组成的结构体
class SRetParam_BuyAction
	attr_accessor:dwRet#(UINT32)结果
	attr_accessor:dwCount#(UINT32)购买体力次数
	attr_accessor:dwPrice#(UINT32)购买体力价格

	#构造函数
	def initialize
		@dwRet = 0
		@dwCount = 0
		@dwPrice = 0
	end
end

#函数[GetBuyActionCount:获取购买体力次数]的返回的参数组成的结构体
class SRetParam_GetBuyActionCount
	attr_accessor:dwCount#(UINT32)购买体力次数
	attr_accessor:dwPrice#(UINT32)购买体力价格
	attr_accessor:dwAction#(UINT32)体力

	#构造函数
	def initialize
		@dwCount = 0
		@dwPrice = 0
		@dwAction = 0
	end
end

#函数[GetMoneyList:获取货币基础数值]的返回的参数组成的结构体
class SRetParam_GetMoneyList
	attr_accessor:vecMoneyCount#(SMoneyCount的数组)货币列表（货币数量为0的不发送）

	#构造函数
	def initialize
		@vecMoneyCount = Array.new
	end
end

#函数[Draw:玩家抽奖]的返回的参数组成的结构体
class SRetParam_Draw
	attr_accessor:wLotteryID#(UINT16)抽奖号码
	attr_accessor:eResult#(枚举类型：ELotteryRes)操作结果

	#构造函数
	def initialize
		@wLotteryID = 0
		@eResult = 0
	end
end

#函数[GetEveryDayRechargeAward:获取每日冲值奖励]的返回的参数组成的结构体
class SRetParam_GetEveryDayRechargeAward
	attr_accessor:eResult#(枚举类型：EEveryDayReChargeAward)消息返回

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetEveryDayRecharge:获取每日冲值金额]的返回的参数组成的结构体
class SRetParam_GetEveryDayRecharge
	attr_accessor:dwTotalRechargeToday#(UINT32)仙石

	#构造函数
	def initialize
		@dwTotalRechargeToday = 0
	end
end

#函数[BuyFenbaoyan:分宝岩购买活动]的返回的参数组成的结构体
class SRetParam_BuyFenbaoyan
	attr_accessor:eRet#(枚举类型：EMiscOptRes)购买结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#函数[FenbaoyanTime:分宝岩购买活动时间]的返回的参数组成的结构体
class SRetParam_FenbaoyanTime
	attr_accessor:dwBegin#(UINT32)开始时间
	attr_accessor:dwEnd#(UINT32)结束时间

	#构造函数
	def initialize
		@dwBegin = 0
		@dwEnd = 0
	end
end

#协议类：不好归类的小协议
class MiscProtBase < ProtocolBase
	#以下为发送函数
	#发送：设置防沉迷状态
	def send_SetIndulge(
		bIndulge #(bool)设置防沉迷状态
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeBOOL(data, bIndulge)
		return @svrHandler.sendPacket(data)
	end

	#发送：设置防沉迷收益率
	def send_SetIndulgeRate(
		dwIndulgeRate #(UINT32)设置防沉迷收益率
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, dwIndulgeRate)
		return @svrHandler.sendPacket(data)
	end

	#发送：购买体力
	def send_BuyAction(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取购买体力次数
	def send_GetBuyActionCount(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取体力buff数值
	def send_GetActionBuff(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：发送udplog
	def send_SendUdpLog(
		strParam1,  #(string)参数1
		strParam2 #(string)参数2
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeSTRING(data, strParam1)
		ByteUtil::writeSTRING(data, strParam2)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取货币基础数值
	def send_GetMoneyList(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：领取体力buff
	def send_TakeActionBuff(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：客户端黑屏Log
	def send_ClientBlankScreenLog(
		strParam1 #(string)参数1
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeSTRING(data, strParam1)
		return @svrHandler.sendPacket(data)
	end

	#发送：天赐宝箱
	def send_OnEnter(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得回合数和活动状态
	def send_GetRount(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家抽奖
	def send_Draw(
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：客户端通知动画播放完毕
	def send_DrawRet(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 13
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：同步客户端玩家抽奖
	def send_SendLottery(
		dwTotalNum,  #(UINT32)总的抽奖信息条数
		dwSelfNum #(UINT32)自己的抽奖信息条数
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 14
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, dwTotalNum)
		ByteUtil::writeUINT32(data, dwSelfNum)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取每日冲值奖励
	def send_GetEveryDayRechargeAward(
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 15
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取每日冲值金额
	def send_GetEveryDayRecharge(
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 16
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：分宝岩购买活动
	def send_BuyFenbaoyan(
		wNum #(UINT16)购买数量
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 17
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wNum)
		return @svrHandler.sendPacket(data)
	end

	#发送：分宝岩购买活动时间
	def send_FenbaoyanTime(
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 18
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：聊天信息通知
	def onRecv_IndulgeTimeNotify(
		dwIndulgeTime #(UINT32)防沉迷时间(秒)
	)
		raise NotImplementedError
	end
	#接收：聊天信息通知
	def onRecv_IndulgeNextLoginTime(
		dwTime #(UINT32)可以登陆时间(秒)
	)
		raise NotImplementedError
	end
	#接收：Buffer中的体力
	def onRecv_GetActionBuffNotify(
		dwValue, #(UINT32)Buffer中的体力
		TakeTime #(UINT32)最近领取时间
	)
		raise NotImplementedError
	end
	#接收：通知活动开始
	def onRecv_OnBegin(
	)
		raise NotImplementedError
	end
	#接收：宝箱下一波公告
	def onRecv_SendNotice(
		byRount, #(UINT8)剩余波数
		byMaxRount #(UINT8)最大波数
	)
		raise NotImplementedError
	end
	#接收：通知倒计时
	def onRecv_OnCountDown(
		dwTime #(UINT32)活动倒计时时间
	)
		raise NotImplementedError
	end
	#接收：通知活动结束
	def onRecv_OnEnd(
	)
		raise NotImplementedError
	end
	#接收：通知宝箱活动剩余轮次
	def onRecv_SyncChestInfo(
		sInfo #(类类型：SGodChestInfo)宝箱信息
	)
		raise NotImplementedError
	end
	#接收：通知宝箱活动剩余轮次
	def onRecv_SyncLotteryInfo(
		dwLottery, #(UINT32)抽奖券
		vecTotalInfo, #(SLotteryInfo的数组)总的抽奖信息
		vecSelfInfo #(SLotteryInfo的数组)自己抽奖信息
	)
		raise NotImplementedError
	end
	#接收：同步今日冲值仙石总数
	def onRecv_SyncRechargeToday(
		dwTotalRechargeToday #(UINT32)仙石
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：购买体力
	def onReturn_BuyAction(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuyAction)返回的参数
	)
	end

	#返回：获取购买体力次数
	def onReturn_GetBuyActionCount(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetBuyActionCount)返回的参数
	)
	end

	#返回：获取货币基础数值
	def onReturn_GetMoneyList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetMoneyList)返回的参数
	)
	end

	#返回：玩家抽奖
	def onReturn_Draw(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Draw)返回的参数
	)
	end

	#返回：获取每日冲值奖励
	def onReturn_GetEveryDayRechargeAward(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetEveryDayRechargeAward)返回的参数
	)
	end

	#返回：获取每日冲值金额
	def onReturn_GetEveryDayRecharge(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetEveryDayRecharge)返回的参数
	)
	end

	#返回：分宝岩购买活动
	def onReturn_BuyFenbaoyan(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuyFenbaoyan)返回的参数
	)
	end

	#返回：分宝岩购买活动时间
	def onReturn_FenbaoyanTime(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FenbaoyanTime)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：聊天信息通知
	def _doRecv_IndulgeTimeNotify(data)
		dwIndulgeTime = ByteUtil::readUINT32(data)
		return onRecv_IndulgeTimeNotify(dwIndulgeTime)
	end

	#接收处理：聊天信息通知
	def _doRecv_IndulgeNextLoginTime(data)
		dwTime = ByteUtil::readUINT32(data)
		return onRecv_IndulgeNextLoginTime(dwTime)
	end

	#接收处理：Buffer中的体力
	def _doRecv_GetActionBuffNotify(data)
		dwValue = ByteUtil::readUINT32(data)
		TakeTime = ByteUtil::readUINT32(data)
		return onRecv_GetActionBuffNotify(dwValue, TakeTime)
	end

	#接收处理：通知活动开始
	def _doRecv_OnBegin(data)
		return onRecv_OnBegin()
	end

	#接收处理：宝箱下一波公告
	def _doRecv_SendNotice(data)
		byRount = ByteUtil::readUINT8(data)
		byMaxRount = ByteUtil::readUINT8(data)
		return onRecv_SendNotice(byRount, byMaxRount)
	end

	#接收处理：通知倒计时
	def _doRecv_OnCountDown(data)
		dwTime = ByteUtil::readUINT32(data)
		return onRecv_OnCountDown(dwTime)
	end

	#接收处理：通知活动结束
	def _doRecv_OnEnd(data)
		return onRecv_OnEnd()
	end

	#接收处理：通知宝箱活动剩余轮次
	def _doRecv_SyncChestInfo(data)
		sInfo = SGodChestInfo::fromStream(data)
		return onRecv_SyncChestInfo(sInfo)
	end

	#接收处理：通知宝箱活动剩余轮次
	def _doRecv_SyncLotteryInfo(data)
		dwLottery = ByteUtil::readUINT32(data)
		vecTotalInfo = SLotteryInfo::vectorFromStream(data)
		vecSelfInfo = SLotteryInfo::vectorFromStream(data)
		return onRecv_SyncLotteryInfo(dwLottery, vecTotalInfo, vecSelfInfo)
	end

	#接收处理：同步今日冲值仙石总数
	def _doRecv_SyncRechargeToday(data)
		dwTotalRechargeToday = ByteUtil::readUINT32(data)
		return onRecv_SyncRechargeToday(dwTotalRechargeToday)
	end

#以下为返回处理函数
	#返回处理：购买体力
	def _doReturn_BuyAction(data)
		retParam = SRetParam_BuyAction.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRet = ByteUtil::readUINT32(data) #(UINT32)结果
		dwCount = ByteUtil::readUINT32(data) #(UINT32)购买体力次数
		dwPrice = ByteUtil::readUINT32(data) #(UINT32)购买体力价格
		retParam.dwRet = dwRet
		retParam.dwCount = dwCount
		retParam.dwPrice = dwPrice
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuyAction(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：购买体力
	def _onTimeOut_BuyAction(sessionID)
		retParam = SRetParam_BuyAction.new;
		onReturn_BuyAction(2, retParam)
	end

	#返回处理：获取购买体力次数
	def _doReturn_GetBuyActionCount(data)
		retParam = SRetParam_GetBuyActionCount.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwCount = ByteUtil::readUINT32(data) #(UINT32)购买体力次数
		dwPrice = ByteUtil::readUINT32(data) #(UINT32)购买体力价格
		dwAction = ByteUtil::readUINT32(data) #(UINT32)体力
		retParam.dwCount = dwCount
		retParam.dwPrice = dwPrice
		retParam.dwAction = dwAction
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetBuyActionCount(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取购买体力次数
	def _onTimeOut_GetBuyActionCount(sessionID)
		retParam = SRetParam_GetBuyActionCount.new;
		onReturn_GetBuyActionCount(2, retParam)
	end

	#返回处理：获取货币基础数值
	def _doReturn_GetMoneyList(data)
		retParam = SRetParam_GetMoneyList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecMoneyCount = SMoneyCount::vectorFromStream(data) #(SMoneyCount的数组)货币列表（货币数量为0的不发送）
		retParam.vecMoneyCount = vecMoneyCount
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetMoneyList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取货币基础数值
	def _onTimeOut_GetMoneyList(sessionID)
		retParam = SRetParam_GetMoneyList.new;
		onReturn_GetMoneyList(2, retParam)
	end

	#返回处理：玩家抽奖
	def _doReturn_Draw(data)
		retParam = SRetParam_Draw.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		wLotteryID = ByteUtil::readUINT16(data) #(UINT16)抽奖号码
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ELotteryRes)操作结果
		retParam.wLotteryID = wLotteryID
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_Draw(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：玩家抽奖
	def _onTimeOut_Draw(sessionID)
		retParam = SRetParam_Draw.new;
		onReturn_Draw(2, retParam)
	end

	#返回处理：获取每日冲值奖励
	def _doReturn_GetEveryDayRechargeAward(data)
		retParam = SRetParam_GetEveryDayRechargeAward.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EEveryDayReChargeAward)消息返回
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetEveryDayRechargeAward(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取每日冲值奖励
	def _onTimeOut_GetEveryDayRechargeAward(sessionID)
		retParam = SRetParam_GetEveryDayRechargeAward.new;
		onReturn_GetEveryDayRechargeAward(2, retParam)
	end

	#返回处理：获取每日冲值金额
	def _doReturn_GetEveryDayRecharge(data)
		retParam = SRetParam_GetEveryDayRecharge.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwTotalRechargeToday = ByteUtil::readUINT32(data) #(UINT32)仙石
		retParam.dwTotalRechargeToday = dwTotalRechargeToday
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetEveryDayRecharge(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取每日冲值金额
	def _onTimeOut_GetEveryDayRecharge(sessionID)
		retParam = SRetParam_GetEveryDayRecharge.new;
		onReturn_GetEveryDayRecharge(2, retParam)
	end

	#返回处理：分宝岩购买活动
	def _doReturn_BuyFenbaoyan(data)
		retParam = SRetParam_BuyFenbaoyan.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EMiscOptRes)购买结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuyFenbaoyan(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：分宝岩购买活动
	def _onTimeOut_BuyFenbaoyan(sessionID)
		retParam = SRetParam_BuyFenbaoyan.new;
		onReturn_BuyFenbaoyan(2, retParam)
	end

	#返回处理：分宝岩购买活动时间
	def _doReturn_FenbaoyanTime(data)
		retParam = SRetParam_FenbaoyanTime.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwBegin = ByteUtil::readUINT32(data) #(UINT32)开始时间
		dwEnd = ByteUtil::readUINT32(data) #(UINT32)结束时间
		retParam.dwBegin = dwBegin
		retParam.dwEnd = dwEnd
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FenbaoyanTime(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：分宝岩购买活动时间
	def _onTimeOut_FenbaoyanTime(sessionID)
		retParam = SRetParam_FenbaoyanTime.new;
		onReturn_FenbaoyanTime(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 72;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_IndulgeTimeNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_IndulgeNextLoginTime' #FuncID: 2
		@recvFuncList[2] = '_doRecv_GetActionBuffNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_OnBegin' #FuncID: 4
		@recvFuncList[4] = '_doRecv_SendNotice' #FuncID: 5
		@recvFuncList[5] = '_doRecv_OnCountDown' #FuncID: 6
		@recvFuncList[6] = '_doRecv_OnEnd' #FuncID: 7
		@recvFuncList[7] = '_doRecv_SyncChestInfo' #FuncID: 8
		@recvFuncList[8] = '_doRecv_SyncLotteryInfo' #FuncID: 9
		@recvFuncList[9] = '_doRecv_SyncRechargeToday' #FuncID: 10

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_BuyAction' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetBuyActionCount' #FuncID: 2
		@retFuncList[2] = '_doReturn_GetMoneyList' #FuncID: 3
		@retFuncList[3] = '_doReturn_Draw' #FuncID: 4
		@retFuncList[4] = '_doReturn_GetEveryDayRechargeAward' #FuncID: 5
		@retFuncList[5] = '_doReturn_GetEveryDayRecharge' #FuncID: 6
		@retFuncList[6] = '_doReturn_BuyFenbaoyan' #FuncID: 7
		@retFuncList[7] = '_doReturn_FenbaoyanTime' #FuncID: 8

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_BuyAction' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetBuyActionCount' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GetMoneyList' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_Draw' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_GetEveryDayRechargeAward' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_GetEveryDayRecharge' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_BuyFenbaoyan' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_FenbaoyanTime' #FuncID: 8
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

