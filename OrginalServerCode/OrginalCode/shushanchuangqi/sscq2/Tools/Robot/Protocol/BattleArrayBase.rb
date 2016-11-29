#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    BattleArray.rb
#  Purpose:      破阵
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ItemProtBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#阵状态
class EBattleArrayStatus
	EBATTLEARRAYSTATUS_INIT = 0#初始状态
	EBATTLEARRAYSTATUS_END = 1#已破阵
	EBATTLEARRAYSTATUS_TAKEPRIZED = 2#已领奖
end

#破阵操作结果
class EBattleArrayRet
	EBATTLEARRAYRET_SUCESS = 0#成功
	EBATTLEARRAYRET_LEVELLIMIT = 1#等级不够
	EBATTLEARRAYRET_PREID = 2#前置阵未破
	EBATTLEARRAYRET_POSLIMIT = 3#阵位只能一次
	EBATTLEARRAYRET_ATTACKLIMIT = 4#攻击次数限制
	EBATTLEARRAYRET_TOTALATTACKLIMIT = 5#总攻击次数一次
	EBATTLEARRAYRET_ERRORCFG = 6#配置错误
	EBATTLEARRAYRET_PRELEVEL = 7#阵图未解锁
	EBATTLEARRAYRET_NOPASS = 8#未破阵图
	EBATTLEARRAYRET_TAKEPRIZED = 9#已经领过奖励
	EBATTLEARRAYRET_PACKERROR = 10#背包格子不够
	EBATTLEARRAYRET_MONEYERROR = 11#钻石不够
	EBATTLEARRAYRET_MAXBUYCNT = 12#超过最大购买次数
	EBATTLEARRAYRET_ATTACKCD = 13#攻击cd
end

#获的物品的类型
class EBattleArrayGain
	EBATTLEARRAYGAIN_ATTACK = 0#攻击阵图
	EBATTLEARRAYGAIN_SWEEP = 1#扫荡(自动破阵)
end

#阵信息
class SBattleArray
	attr_accessor:wBattleArrayID #(UINT16)阵id
	attr_accessor:dwBattleArrayLevelID #(UINT32)破阵进度(阵图id)
	attr_accessor:eBattleArrayStatus #(枚举类型：EBattleArrayStatus)阵状态

	#构造函数
	def initialize
		@wBattleArrayID = 0
		@dwBattleArrayLevelID = 0
		@eBattleArrayStatus = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wBattleArrayID = @wBattleArrayID
		obj.dwBattleArrayLevelID = @dwBattleArrayLevelID
		obj.eBattleArrayStatus = @eBattleArrayStatus
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleArray.new
		s.wBattleArrayID = ByteUtil::readUINT16(data)
		s.dwBattleArrayLevelID = ByteUtil::readUINT32(data)
		s.eBattleArrayStatus = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleArray::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wBattleArrayID)
		ByteUtil::writeUINT32(data, @dwBattleArrayLevelID)
		ByteUtil::writeUINT8(data, @eBattleArrayStatus)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#攻击阵图信息
class SBattleArrayAttackCnt
	attr_accessor:dwBattleArrayLevelID #(UINT32)阵图id
	attr_accessor:wCount #(UINT16)次数
	attr_accessor:wMinTurn #(UINT16)最小回合数

	#构造函数
	def initialize
		@dwBattleArrayLevelID = 0
		@wCount = 0
		@wMinTurn = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwBattleArrayLevelID = @dwBattleArrayLevelID
		obj.wCount = @wCount
		obj.wMinTurn = @wMinTurn
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleArrayAttackCnt.new
		s.dwBattleArrayLevelID = ByteUtil::readUINT32(data)
		s.wCount = ByteUtil::readUINT16(data)
		s.wMinTurn = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleArrayAttackCnt::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwBattleArrayLevelID)
		ByteUtil::writeUINT16(data, @wCount)
		ByteUtil::writeUINT16(data, @wMinTurn)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetBattleArray:获取阵信息]的返回的参数组成的结构体
class SRetParam_GetBattleArray
	attr_accessor:vecBattleArray#(SBattleArray的数组)阵信息列表
	attr_accessor:vecBattleArrayAttackCnt#(SBattleArrayAttackCnt的数组)攻击阵图信息
	attr_accessor:dwBuyCnt#(UINT32)可用的次数
	attr_accessor:dwDayBuyCnt#(UINT32)当天购买次数
	attr_accessor:dwFailCd#(UINT32)战败cd

	#构造函数
	def initialize
		@vecBattleArray = Array.new
		@vecBattleArrayAttackCnt = Array.new
		@dwBuyCnt = 0
		@dwDayBuyCnt = 0
		@dwFailCd = 0
	end
end

#函数[AttackBattleArray:攻击阵图]的返回的参数组成的结构体
class SRetParam_AttackBattleArray
	attr_accessor:eBattleArrayRet#(枚举类型：EBattleArrayRet)操作结果
	attr_accessor:dwFailCd#(UINT32)战败cd

	#构造函数
	def initialize
		@eBattleArrayRet = 0
		@dwFailCd = 0
	end
end

#函数[SweepBattleArray:扫荡阵图]的返回的参数组成的结构体
class SRetParam_SweepBattleArray
	attr_accessor:eBattleArrayRet#(枚举类型：EBattleArrayRet)操作结果

	#构造函数
	def initialize
		@eBattleArrayRet = 0
	end
end

#函数[BattleArrayTakePrize:领取通关奖励]的返回的参数组成的结构体
class SRetParam_BattleArrayTakePrize
	attr_accessor:eBattleArrayRet#(枚举类型：EBattleArrayRet)操作结果

	#构造函数
	def initialize
		@eBattleArrayRet = 0
	end
end

#函数[GetBuyAtkCountPrice:获取当前购买价格]的返回的参数组成的结构体
class SRetParam_GetBuyAtkCountPrice
	attr_accessor:dwPrice#(UINT32)价格
	attr_accessor:dwBuyCount#(UINT32)当天已购买次数

	#构造函数
	def initialize
		@dwPrice = 0
		@dwBuyCount = 0
	end
end

#函数[BuyAtkCount:购买攻击阵图次数]的返回的参数组成的结构体
class SRetParam_BuyAtkCount
	attr_accessor:eRet#(枚举类型：EBattleArrayRet)结果
	attr_accessor:dwBuyCount#(UINT32)已购买次数
	attr_accessor:dwDayBuyCnt#(UINT32)当天购买次数

	#构造函数
	def initialize
		@eRet = 0
		@dwBuyCount = 0
		@dwDayBuyCnt = 0
	end
end

#协议类：破阵
class BattleArrayBase < ProtocolBase
	#以下为发送函数
	#发送：获取阵信息
	def send_GetBattleArray(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：攻击阵图
	def send_AttackBattleArray(
		dwBattleArrayLevelID #(UINT32)阵图id
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwBattleArrayLevelID)
		return @svrHandler.sendPacket(data)
	end

	#发送：扫荡阵图
	def send_SweepBattleArray(
		dwBattleArrayLevelID #(UINT32)阵图id
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwBattleArrayLevelID)
		return @svrHandler.sendPacket(data)
	end

	#发送：领取通关奖励
	def send_BattleArrayTakePrize(
		wBattleArrayID #(UINT16)阵id
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wBattleArrayID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取当前购买价格
	def send_GetBuyAtkCountPrice(
		dwCount #(UINT32)购买次数
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：购买攻击阵图次数
	def send_BuyAtkCount(
		dwCount #(UINT32)购买次数
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwCount)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：阵信息更新
	def onRecv_BattleArrayNotify(
		oBattleArray #(类类型：SBattleArray)阵信息
	)
		raise NotImplementedError
	end
	#接收：攻击阵图信息
	def onRecv_SBattleArrayAttackCntNotify(
		oBattleArrayAttackCnt #(类类型：SBattleArrayAttackCnt)攻击阵图信息
	)
		raise NotImplementedError
	end
	#接收：总攻击次数
	def onRecv_TotleAttackCntNotify(
		dwAttackCnt, #(UINT32)总攻击次数
		dwBuyCnt #(UINT32)剩余购买数
	)
		raise NotImplementedError
	end
	#接收：获得物品通知
	def onRecv_GainNotify(
		eBattleArrayGain, #(枚举类型：EBattleArrayGain)类型
		vecItemGenInfo #(SItemGenInfo的数组)物品
	)
		raise NotImplementedError
	end
	#接收：全部阵信息
	def onRecv_GetBattleArrayNotify(
		vecBattleArray, #(SBattleArray的数组)阵信息列表
		vecBattleArrayAttackCnt, #(SBattleArrayAttackCnt的数组)攻击阵图信息
		dwBuyCnt, #(UINT32)可用的次数
		dwDayBuyCnt #(UINT32)当天购买次数
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取阵信息
	def onReturn_GetBattleArray(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetBattleArray)返回的参数
	)
	end

	#返回：攻击阵图
	def onReturn_AttackBattleArray(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_AttackBattleArray)返回的参数
	)
	end

	#返回：扫荡阵图
	def onReturn_SweepBattleArray(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SweepBattleArray)返回的参数
	)
	end

	#返回：领取通关奖励
	def onReturn_BattleArrayTakePrize(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BattleArrayTakePrize)返回的参数
	)
	end

	#返回：获取当前购买价格
	def onReturn_GetBuyAtkCountPrice(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetBuyAtkCountPrice)返回的参数
	)
	end

	#返回：购买攻击阵图次数
	def onReturn_BuyAtkCount(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuyAtkCount)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：阵信息更新
	def _doRecv_BattleArrayNotify(data)
		oBattleArray = SBattleArray::fromStream(data)
		return onRecv_BattleArrayNotify(oBattleArray)
	end

	#接收处理：攻击阵图信息
	def _doRecv_SBattleArrayAttackCntNotify(data)
		oBattleArrayAttackCnt = SBattleArrayAttackCnt::fromStream(data)
		return onRecv_SBattleArrayAttackCntNotify(oBattleArrayAttackCnt)
	end

	#接收处理：总攻击次数
	def _doRecv_TotleAttackCntNotify(data)
		dwAttackCnt = ByteUtil::readUINT32(data)
		dwBuyCnt = ByteUtil::readUINT32(data)
		return onRecv_TotleAttackCntNotify(dwAttackCnt, dwBuyCnt)
	end

	#接收处理：获得物品通知
	def _doRecv_GainNotify(data)
		eBattleArrayGain = ByteUtil::readUINT8(data)
		vecItemGenInfo = SItemGenInfo::vectorFromStream(data)
		return onRecv_GainNotify(eBattleArrayGain, vecItemGenInfo)
	end

	#接收处理：全部阵信息
	def _doRecv_GetBattleArrayNotify(data)
		vecBattleArray = SBattleArray::vectorFromStream(data)
		vecBattleArrayAttackCnt = SBattleArrayAttackCnt::vectorFromStream(data)
		dwBuyCnt = ByteUtil::readUINT32(data)
		dwDayBuyCnt = ByteUtil::readUINT32(data)
		return onRecv_GetBattleArrayNotify(vecBattleArray, vecBattleArrayAttackCnt, dwBuyCnt, dwDayBuyCnt)
	end

#以下为返回处理函数
	#返回处理：获取阵信息
	def _doReturn_GetBattleArray(data)
		retParam = SRetParam_GetBattleArray.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecBattleArray = SBattleArray::vectorFromStream(data) #(SBattleArray的数组)阵信息列表
		vecBattleArrayAttackCnt = SBattleArrayAttackCnt::vectorFromStream(data) #(SBattleArrayAttackCnt的数组)攻击阵图信息
		dwBuyCnt = ByteUtil::readUINT32(data) #(UINT32)可用的次数
		dwDayBuyCnt = ByteUtil::readUINT32(data) #(UINT32)当天购买次数
		dwFailCd = ByteUtil::readUINT32(data) #(UINT32)战败cd
		retParam.vecBattleArray = vecBattleArray
		retParam.vecBattleArrayAttackCnt = vecBattleArrayAttackCnt
		retParam.dwBuyCnt = dwBuyCnt
		retParam.dwDayBuyCnt = dwDayBuyCnt
		retParam.dwFailCd = dwFailCd
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetBattleArray(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取阵信息
	def _onTimeOut_GetBattleArray(sessionID)
		retParam = SRetParam_GetBattleArray.new;
		onReturn_GetBattleArray(2, retParam)
	end

	#返回处理：攻击阵图
	def _doReturn_AttackBattleArray(data)
		retParam = SRetParam_AttackBattleArray.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eBattleArrayRet = ByteUtil::readUINT8(data) #(枚举类型：EBattleArrayRet)操作结果
		dwFailCd = ByteUtil::readUINT32(data) #(UINT32)战败cd
		retParam.eBattleArrayRet = eBattleArrayRet
		retParam.dwFailCd = dwFailCd
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_AttackBattleArray(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：攻击阵图
	def _onTimeOut_AttackBattleArray(sessionID)
		retParam = SRetParam_AttackBattleArray.new;
		onReturn_AttackBattleArray(2, retParam)
	end

	#返回处理：扫荡阵图
	def _doReturn_SweepBattleArray(data)
		retParam = SRetParam_SweepBattleArray.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eBattleArrayRet = ByteUtil::readUINT8(data) #(枚举类型：EBattleArrayRet)操作结果
		retParam.eBattleArrayRet = eBattleArrayRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SweepBattleArray(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：扫荡阵图
	def _onTimeOut_SweepBattleArray(sessionID)
		retParam = SRetParam_SweepBattleArray.new;
		onReturn_SweepBattleArray(2, retParam)
	end

	#返回处理：领取通关奖励
	def _doReturn_BattleArrayTakePrize(data)
		retParam = SRetParam_BattleArrayTakePrize.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eBattleArrayRet = ByteUtil::readUINT8(data) #(枚举类型：EBattleArrayRet)操作结果
		retParam.eBattleArrayRet = eBattleArrayRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BattleArrayTakePrize(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：领取通关奖励
	def _onTimeOut_BattleArrayTakePrize(sessionID)
		retParam = SRetParam_BattleArrayTakePrize.new;
		onReturn_BattleArrayTakePrize(2, retParam)
	end

	#返回处理：获取当前购买价格
	def _doReturn_GetBuyAtkCountPrice(data)
		retParam = SRetParam_GetBuyAtkCountPrice.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwPrice = ByteUtil::readUINT32(data) #(UINT32)价格
		dwBuyCount = ByteUtil::readUINT32(data) #(UINT32)当天已购买次数
		retParam.dwPrice = dwPrice
		retParam.dwBuyCount = dwBuyCount
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetBuyAtkCountPrice(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取当前购买价格
	def _onTimeOut_GetBuyAtkCountPrice(sessionID)
		retParam = SRetParam_GetBuyAtkCountPrice.new;
		onReturn_GetBuyAtkCountPrice(2, retParam)
	end

	#返回处理：购买攻击阵图次数
	def _doReturn_BuyAtkCount(data)
		retParam = SRetParam_BuyAtkCount.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EBattleArrayRet)结果
		dwBuyCount = ByteUtil::readUINT32(data) #(UINT32)已购买次数
		dwDayBuyCnt = ByteUtil::readUINT32(data) #(UINT32)当天购买次数
		retParam.eRet = eRet
		retParam.dwBuyCount = dwBuyCount
		retParam.dwDayBuyCnt = dwDayBuyCnt
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuyAtkCount(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：购买攻击阵图次数
	def _onTimeOut_BuyAtkCount(sessionID)
		retParam = SRetParam_BuyAtkCount.new;
		onReturn_BuyAtkCount(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 130;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_BattleArrayNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_SBattleArrayAttackCntNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_TotleAttackCntNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_GainNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_GetBattleArrayNotify' #FuncID: 5

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetBattleArray' #FuncID: 1
		@retFuncList[1] = '_doReturn_AttackBattleArray' #FuncID: 2
		@retFuncList[2] = '_doReturn_SweepBattleArray' #FuncID: 3
		@retFuncList[3] = '_doReturn_BattleArrayTakePrize' #FuncID: 4
		@retFuncList[4] = '_doReturn_GetBuyAtkCountPrice' #FuncID: 5
		@retFuncList[5] = '_doReturn_BuyAtkCount' #FuncID: 6

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetBattleArray' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_AttackBattleArray' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_SweepBattleArray' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_BattleArrayTakePrize' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_GetBuyAtkCountPrice' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_BuyAtkCount' #FuncID: 6
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

