#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    DayActProt.rb
#  Purpose:      活动
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#活动ID（保留暂时不用）
class EActID
end

#活动类型
class EActType
	EACTTYPEINVALID = 0
	EACTTYPEWORLDBOSS = 1#boss活动
	EACTTYPELANGHUANBLESS = 2#LangHuanBless活动
	EACTTYPEGUILDBATTLE = 3#帮派战活动
	EACTTYPESHUSHANBATTLE = 4#蜀山论剑活动
	EACTTYPEENERGY = 5#剑气充盈活动
	EACTTYPETEAMREWARD = 6#组队副本奖励活动
	EACTTYPEANSWER = 7#答题活动
	EACTTYPELINGSHAN = 8#秘境寻宝
	EACTTYPENEWGUILDBATTLE = 9#新帮派战
	EACTTYPECHEST = 10#刷宝箱
	EACTTYPESHIPREWARD = 11#元江金船活动
	EACTTYPEEND = 12
end

#活动状态
class EDayActivityStatus
	EDAYACTIVITYSTATUSINIT = 0#活动初始化状态
	EDAYACTIVITYSTATUSALARM = 1#活动警戒状态
	EDAYACTIVITYSTATUSREADY = 2#活动准备状态
	EDAYACTIVITYSTATUSPROCESS = 3#活动进行状态
	EDAYACTIVITYSTATUSEND = 4#活动结束状态
end

#活动信息表
class SActInfo
	attr_accessor:dwActType #(UINT32)活动id
	attr_accessor:dwActStatus #(UINT32)活动状态

	#构造函数
	def initialize
		@dwActType = 0
		@dwActStatus = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwActType = @dwActType
		obj.dwActStatus = @dwActStatus
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SActInfo.new
		s.dwActType = ByteUtil::readUINT32(data)
		s.dwActStatus = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SActInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwActType)
		ByteUtil::writeUINT32(data, @dwActStatus)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetActList:获取活动列表]的返回的参数组成的结构体
class SRetParam_GetActList
	attr_accessor:vecActInfo#(SActInfo的数组)活动列表

	#构造函数
	def initialize
		@vecActInfo = Array.new
	end
end

#函数[GetFirstRechargeStatus:是否已领取首充礼包]的返回的参数组成的结构体
class SRetParam_GetFirstRechargeStatus
	attr_accessor:byRet#(UINT8)0未充值 1已充值但未领取 2已领取

	#构造函数
	def initialize
		@byRet = 0
	end
end

#函数[GetFirstRechargeAward:领取首充礼包]的返回的参数组成的结构体
class SRetParam_GetFirstRechargeAward
	attr_accessor:byRet#(UINT8)0失败 1成功 2未充值 3已领取

	#构造函数
	def initialize
		@byRet = 0
	end
end

#函数[BuyShushanFoundSelf:为自己购买蜀山基金]的返回的参数组成的结构体
class SRetParam_BuyShushanFoundSelf
	attr_accessor:byRet#(UINT8)0失败 1成功

	#构造函数
	def initialize
		@byRet = 0
	end
end

#函数[BuyShushanFoundFirend:为好友购买蜀山基金]的返回的参数组成的结构体
class SRetParam_BuyShushanFoundFirend
	attr_accessor:byRet#(UINT8)0失败 1成功

	#构造函数
	def initialize
		@byRet = 0
	end
end

#函数[GetShushanFoundAward:领取蜀山基金奖励]的返回的参数组成的结构体
class SRetParam_GetShushanFoundAward
	attr_accessor:byRet#(UINT8)0失败 1成功

	#构造函数
	def initialize
		@byRet = 0
	end
end

#函数[GetSecondRechargeStatus:获取二次充值礼包状态]的返回的参数组成的结构体
class SRetParam_GetSecondRechargeStatus
	attr_accessor:byRet#(UINT8)0未充值 1已充值但未领取 2已领取
	attr_accessor:dwSecondRechargeValue#(UINT32)二次充值累计金额

	#构造函数
	def initialize
		@byRet = 0
		@dwSecondRechargeValue = 0
	end
end

#函数[GetSecondRechargeAward:领取二次充值礼包]的返回的参数组成的结构体
class SRetParam_GetSecondRechargeAward
	attr_accessor:byRet#(UINT8)0失败 1成功 2未充值 3已领取

	#构造函数
	def initialize
		@byRet = 0
	end
end

#函数[GetOpenServerTime:获取开服时间]的返回的参数组成的结构体
class SRetParam_GetOpenServerTime
	attr_accessor:dwTime#(UINT32)时间

	#构造函数
	def initialize
		@dwTime = 0
	end
end

#协议类：活动
class DayActProtBase < ProtocolBase
	#以下为发送函数
	#发送：获取活动列表
	def send_GetActList(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：是否已领取首充礼包
	def send_GetFirstRechargeStatus(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：领取首充礼包
	def send_GetFirstRechargeAward(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：为自己购买蜀山基金
	def send_BuyShushanFoundSelf(
		byType #(UINT8)基金类型(1成长基金 2修为投资计划 3银币投资计划 4宝物投资计划)
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byType)
		return @svrHandler.sendPacket(data)
	end

	#发送：为好友购买蜀山基金
	def send_BuyShushanFoundFirend(
		qwFriendID,  #(UINT64)好友ID
		byType #(UINT8)基金类型(1成长基金 2修为投资计划 3银币投资计划 4宝物投资计划)
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwFriendID)
		ByteUtil::writeUINT8(data, byType)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取玩家购买及领取蜀山基金的信息
	def send_GetShushanFoundInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：领取蜀山基金奖励
	def send_GetShushanFoundAward(
		byType,  #(UINT8)基金类型(1成长基金 2修为投资计划 3银币投资计划 4宝物投资计划)
		byDay #(UINT8)领取第几个(1~7)
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byType)
		ByteUtil::writeUINT8(data, byDay)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取二次充值礼包状态
	def send_GetSecondRechargeStatus(
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：领取二次充值礼包
	def send_GetSecondRechargeAward(
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取开服时间
	def send_GetOpenServerTime(
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：活动状态改变通知
	def onRecv_ActChangeNotify(
		dwActType, #(UINT32)活动id
		dwActStatus #(UINT32)活动状态
	)
		raise NotImplementedError
	end
	#接收：蜀山基金活动改变通知
	def onRecv_ShushanFoundChangeNotify(
		wGrowFoundInfo, #(UINT16)成长基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		wPExpFoundInfo, #(UINT16)修为基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		wSilverFoundInfo, #(UINT16)银币基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		wItemFoundInfo, #(UINT16)宝物基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		dwLoginDays #(UINT32)玩家累计登陆天数(按低到高顺序,成长/修为/银币宝物)
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取活动列表
	def onReturn_GetActList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetActList)返回的参数
	)
	end

	#返回：是否已领取首充礼包
	def onReturn_GetFirstRechargeStatus(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetFirstRechargeStatus)返回的参数
	)
	end

	#返回：领取首充礼包
	def onReturn_GetFirstRechargeAward(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetFirstRechargeAward)返回的参数
	)
	end

	#返回：为自己购买蜀山基金
	def onReturn_BuyShushanFoundSelf(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuyShushanFoundSelf)返回的参数
	)
	end

	#返回：为好友购买蜀山基金
	def onReturn_BuyShushanFoundFirend(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuyShushanFoundFirend)返回的参数
	)
	end

	#返回：领取蜀山基金奖励
	def onReturn_GetShushanFoundAward(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetShushanFoundAward)返回的参数
	)
	end

	#返回：获取二次充值礼包状态
	def onReturn_GetSecondRechargeStatus(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetSecondRechargeStatus)返回的参数
	)
	end

	#返回：领取二次充值礼包
	def onReturn_GetSecondRechargeAward(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetSecondRechargeAward)返回的参数
	)
	end

	#返回：获取开服时间
	def onReturn_GetOpenServerTime(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetOpenServerTime)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：活动状态改变通知
	def _doRecv_ActChangeNotify(data)
		dwActType = ByteUtil::readUINT32(data)
		dwActStatus = ByteUtil::readUINT32(data)
		return onRecv_ActChangeNotify(dwActType, dwActStatus)
	end

	#接收处理：蜀山基金活动改变通知
	def _doRecv_ShushanFoundChangeNotify(data)
		wGrowFoundInfo = ByteUtil::readUINT16(data)
		wPExpFoundInfo = ByteUtil::readUINT16(data)
		wSilverFoundInfo = ByteUtil::readUINT16(data)
		wItemFoundInfo = ByteUtil::readUINT16(data)
		dwLoginDays = ByteUtil::readUINT32(data)
		return onRecv_ShushanFoundChangeNotify(wGrowFoundInfo, wPExpFoundInfo, wSilverFoundInfo, wItemFoundInfo, dwLoginDays)
	end

#以下为返回处理函数
	#返回处理：获取活动列表
	def _doReturn_GetActList(data)
		retParam = SRetParam_GetActList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecActInfo = SActInfo::vectorFromStream(data) #(SActInfo的数组)活动列表
		retParam.vecActInfo = vecActInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetActList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取活动列表
	def _onTimeOut_GetActList(sessionID)
		retParam = SRetParam_GetActList.new;
		onReturn_GetActList(2, retParam)
	end

	#返回处理：是否已领取首充礼包
	def _doReturn_GetFirstRechargeStatus(data)
		retParam = SRetParam_GetFirstRechargeStatus.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readUINT8(data) #(UINT8)0未充值 1已充值但未领取 2已领取
		retParam.byRet = byRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetFirstRechargeStatus(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：是否已领取首充礼包
	def _onTimeOut_GetFirstRechargeStatus(sessionID)
		retParam = SRetParam_GetFirstRechargeStatus.new;
		onReturn_GetFirstRechargeStatus(2, retParam)
	end

	#返回处理：领取首充礼包
	def _doReturn_GetFirstRechargeAward(data)
		retParam = SRetParam_GetFirstRechargeAward.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readUINT8(data) #(UINT8)0失败 1成功 2未充值 3已领取
		retParam.byRet = byRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetFirstRechargeAward(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：领取首充礼包
	def _onTimeOut_GetFirstRechargeAward(sessionID)
		retParam = SRetParam_GetFirstRechargeAward.new;
		onReturn_GetFirstRechargeAward(2, retParam)
	end

	#返回处理：为自己购买蜀山基金
	def _doReturn_BuyShushanFoundSelf(data)
		retParam = SRetParam_BuyShushanFoundSelf.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readUINT8(data) #(UINT8)0失败 1成功
		retParam.byRet = byRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuyShushanFoundSelf(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：为自己购买蜀山基金
	def _onTimeOut_BuyShushanFoundSelf(sessionID)
		retParam = SRetParam_BuyShushanFoundSelf.new;
		onReturn_BuyShushanFoundSelf(2, retParam)
	end

	#返回处理：为好友购买蜀山基金
	def _doReturn_BuyShushanFoundFirend(data)
		retParam = SRetParam_BuyShushanFoundFirend.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readUINT8(data) #(UINT8)0失败 1成功
		retParam.byRet = byRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuyShushanFoundFirend(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：为好友购买蜀山基金
	def _onTimeOut_BuyShushanFoundFirend(sessionID)
		retParam = SRetParam_BuyShushanFoundFirend.new;
		onReturn_BuyShushanFoundFirend(2, retParam)
	end

	#返回处理：领取蜀山基金奖励
	def _doReturn_GetShushanFoundAward(data)
		retParam = SRetParam_GetShushanFoundAward.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readUINT8(data) #(UINT8)0失败 1成功
		retParam.byRet = byRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetShushanFoundAward(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：领取蜀山基金奖励
	def _onTimeOut_GetShushanFoundAward(sessionID)
		retParam = SRetParam_GetShushanFoundAward.new;
		onReturn_GetShushanFoundAward(2, retParam)
	end

	#返回处理：获取二次充值礼包状态
	def _doReturn_GetSecondRechargeStatus(data)
		retParam = SRetParam_GetSecondRechargeStatus.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readUINT8(data) #(UINT8)0未充值 1已充值但未领取 2已领取
		dwSecondRechargeValue = ByteUtil::readUINT32(data) #(UINT32)二次充值累计金额
		retParam.byRet = byRet
		retParam.dwSecondRechargeValue = dwSecondRechargeValue
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetSecondRechargeStatus(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取二次充值礼包状态
	def _onTimeOut_GetSecondRechargeStatus(sessionID)
		retParam = SRetParam_GetSecondRechargeStatus.new;
		onReturn_GetSecondRechargeStatus(2, retParam)
	end

	#返回处理：领取二次充值礼包
	def _doReturn_GetSecondRechargeAward(data)
		retParam = SRetParam_GetSecondRechargeAward.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readUINT8(data) #(UINT8)0失败 1成功 2未充值 3已领取
		retParam.byRet = byRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetSecondRechargeAward(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：领取二次充值礼包
	def _onTimeOut_GetSecondRechargeAward(sessionID)
		retParam = SRetParam_GetSecondRechargeAward.new;
		onReturn_GetSecondRechargeAward(2, retParam)
	end

	#返回处理：获取开服时间
	def _doReturn_GetOpenServerTime(data)
		retParam = SRetParam_GetOpenServerTime.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwTime = ByteUtil::readUINT32(data) #(UINT32)时间
		retParam.dwTime = dwTime
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetOpenServerTime(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取开服时间
	def _onTimeOut_GetOpenServerTime(sessionID)
		retParam = SRetParam_GetOpenServerTime.new;
		onReturn_GetOpenServerTime(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 69;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_ActChangeNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_ShushanFoundChangeNotify' #FuncID: 2

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetActList' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetFirstRechargeStatus' #FuncID: 2
		@retFuncList[2] = '_doReturn_GetFirstRechargeAward' #FuncID: 3
		@retFuncList[3] = '_doReturn_BuyShushanFoundSelf' #FuncID: 4
		@retFuncList[4] = '_doReturn_BuyShushanFoundFirend' #FuncID: 5
		@retFuncList[5] = '_doReturn_GetShushanFoundAward' #FuncID: 6
		@retFuncList[6] = '_doReturn_GetSecondRechargeStatus' #FuncID: 7
		@retFuncList[7] = '_doReturn_GetSecondRechargeAward' #FuncID: 8
		@retFuncList[8] = '_doReturn_GetOpenServerTime' #FuncID: 9

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetActList' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetFirstRechargeStatus' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GetFirstRechargeAward' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_BuyShushanFoundSelf' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_BuyShushanFoundFirend' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_GetShushanFoundAward' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_GetSecondRechargeStatus' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_GetSecondRechargeAward' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_GetOpenServerTime' #FuncID: 9
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

