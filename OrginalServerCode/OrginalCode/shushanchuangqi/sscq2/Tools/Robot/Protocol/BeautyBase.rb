#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    Beauty.rb
#  Purpose:      美女系统
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ItemProtBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#美女系统操作结果
class EBeautyRet
	EBEAUTYRET_SUCESS = 0#成功
	EBEAUTYRET_LEVELLIMIT = 1#等级不够
	EBEAUTYRET_ERRORCFG = 2#配置错误
	EBEAUTYRET_PACKERROR = 3#背包格子不够
	EBEAUTYRET_MONEYERROR = 4#钱不够
	EBEAUTYRET_HEARTERROR = 5#爱心不够
	EBEAUTYRET_ERRORID = 6#美女ID错误
	EBEAUTYRET_CHATCD = 7#聊天cd限制
	EBEAUTYRET_LACKITEM = 8#物品不够
	EBEAUTYRET_EXISTBEAUTY = 9#已结识美女
	EBEAUTYRET_GONDERROR = 10#激活条件不满足
	EBEAUTYRET_LOTTERTYPEERROR = 11#抽奖类型错误
end

#抽奖类型
class ELotteryBeautyType
	ELOTTERYBEAUTYTYPE_ONESILVER = 1001#单次银币抽奖
	ELOTTERYBEAUTYTYPE_ONEGOLD = 1002#单次仙石抽奖
	ELOTTERYBEAUTYTYPE_ONELOVEHEART = 1003#单次爱心抽奖
	ELOTTERYBEAUTYTYPE_ONEFREEGOLD = 1004#单次仙石免费抽奖
	ELOTTERYBEAUTYTYPE_TENSILVER = 2001#10次银币抽奖
	ELOTTERYBEAUTYTYPE_TENGOLD = 2002#10次仙石抽奖
	ELOTTERYBEAUTYTYPE_TENLOVEHEART = 2003#10次爱心抽奖
end

#美女信息
class SBeauty
	attr_accessor:qwRoleID #(UINT64)玩家id
	attr_accessor:wBeautyID #(UINT16)美女id
	attr_accessor:wBeautyLevel #(UINT16)亲密等级
	attr_accessor:dwBeautyExp #(UINT32)亲密度
	attr_accessor:wDayLoveType #(UINT16)当天喜欢物品类型
	attr_accessor:dwChatTime #(UINT32)美女聊天cd(目前是共用cd次字段不用)
	attr_accessor:dwPrizeExp #(UINT32)已获得爱心的亲密度
	attr_accessor:bFight #(bool)是否出战

	#构造函数
	def initialize
		@qwRoleID = 0
		@wBeautyID = 0
		@wBeautyLevel = 0
		@dwBeautyExp = 0
		@wDayLoveType = 0
		@dwChatTime = 0
		@dwPrizeExp = 0
		@bFight = false
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wBeautyID = @wBeautyID
		obj.wBeautyLevel = @wBeautyLevel
		obj.dwBeautyExp = @dwBeautyExp
		obj.wDayLoveType = @wDayLoveType
		obj.dwChatTime = @dwChatTime
		obj.dwPrizeExp = @dwPrizeExp
		obj.bFight = @bFight
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBeauty.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wBeautyID = ByteUtil::readUINT16(data)
		s.wBeautyLevel = ByteUtil::readUINT16(data)
		s.dwBeautyExp = ByteUtil::readUINT32(data)
		s.wDayLoveType = ByteUtil::readUINT16(data)
		s.dwChatTime = ByteUtil::readUINT32(data)
		s.dwPrizeExp = ByteUtil::readUINT32(data)
		s.bFight = ByteUtil::readBOOL(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBeauty::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wBeautyID)
		ByteUtil::writeUINT16(data, @wBeautyLevel)
		ByteUtil::writeUINT32(data, @dwBeautyExp)
		ByteUtil::writeUINT16(data, @wDayLoveType)
		ByteUtil::writeUINT32(data, @dwChatTime)
		ByteUtil::writeUINT32(data, @dwPrizeExp)
		ByteUtil::writeBOOL(data, @bFight)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetBeatyInfo:获取美女信息]的返回的参数组成的结构体
class SRetParam_GetBeatyInfo
	attr_accessor:vecBeauty#(SBeauty的数组)美女信息列表
	attr_accessor:dwLoveCnt#(UINT32)爱心个数
	attr_accessor:dwNextChatTime#(UINT32)下次聊天冷却时间
	attr_accessor:dwNextGoldLotteryTime#(UINT32)下次免费金币抽奖冷却时间
	attr_accessor:dwNextSilverLotterTime#(UINT32)下次免费银币冷却时间
	attr_accessor:wBeautyID#(UINT16)出战美女ID

	#构造函数
	def initialize
		@vecBeauty = Array.new
		@dwLoveCnt = 0
		@dwNextChatTime = 0
		@dwNextGoldLotteryTime = 0
		@dwNextSilverLotterTime = 0
		@wBeautyID = 0
	end
end

#函数[MeetBeauty:结识美女]的返回的参数组成的结构体
class SRetParam_MeetBeauty
	attr_accessor:eRet#(枚举类型：EBeautyRet)操作结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#函数[ChatBeauty:和美女聊天]的返回的参数组成的结构体
class SRetParam_ChatBeauty
	attr_accessor:eRet#(枚举类型：EBeautyRet)操作结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#函数[SendPrizeBeauty:送美女礼品]的返回的参数组成的结构体
class SRetParam_SendPrizeBeauty
	attr_accessor:eRet#(枚举类型：EBeautyRet)操作结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#函数[LotteryBeauty:抽奖]的返回的参数组成的结构体
class SRetParam_LotteryBeauty
	attr_accessor:eRet#(枚举类型：EBeautyRet)操作结果
	attr_accessor:vecItemGenInfo#(SItemGenInfo的数组)物品列表

	#构造函数
	def initialize
		@eRet = 0
		@vecItemGenInfo = Array.new
	end
end

#函数[BeautyFight:美女出战]的返回的参数组成的结构体
class SRetParam_BeautyFight
	attr_accessor:eRet#(枚举类型：EBeautyRet)操作结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#函数[GetRareItemList:获取稀有物品列表]的返回的参数组成的结构体
class SRetParam_GetRareItemList
	attr_accessor:vecItemID#(UINT16数组)稀有物品列表

	#构造函数
	def initialize
		@vecItemID = Array.new
	end
end

#协议类：美女系统
class BeautyBase < ProtocolBase
	#以下为发送函数
	#发送：获取美女信息
	def send_GetBeatyInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：结识美女
	def send_MeetBeauty(
		wBeautyID #(UINT16)美女id
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wBeautyID)
		return @svrHandler.sendPacket(data)
	end

	#发送：和美女聊天
	def send_ChatBeauty(
		wBeautyID #(UINT16)美女id
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wBeautyID)
		return @svrHandler.sendPacket(data)
	end

	#发送：送美女礼品
	def send_SendPrizeBeauty(
		wBeautyID,  #(UINT16)美女id
		vecItemCount #(SItemCount的数组)物品列表
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wBeautyID)
		SItemCount::vectorToStream(data, vecItemCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：抽奖
	def send_LotteryBeauty(
		eLotteryBeautyType #(枚举类型：ELotteryBeautyType)抽奖类型
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, eLotteryBeautyType)
		return @svrHandler.sendPacket(data)
	end

	#发送：美女出战
	def send_BeautyFight(
		wBeautyID #(UINT16)美女id
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wBeautyID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取稀有物品列表
	def send_GetRareItemList(
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取当前已免费抽奖次数
	def send_GetLotteryFreeCnt(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：美女信息更新
	def onRecv_BeautyNotify(
		oBeauty #(类类型：SBeauty)美女信息
	)
		raise NotImplementedError
	end
	#接收：爱心数目更新
	def onRecv_LoveHeartCntNotify(
		dwLoveCnt #(UINT32)爱心个数
	)
		raise NotImplementedError
	end
	#接收：聊天cd
	def onRecv_ChatCdNotify(
		dwNextChatTime #(UINT32)下次聊天冷却时间
	)
		raise NotImplementedError
	end
	#接收：免费抽奖cd
	def onRecv_FreeMoneyCdNotify(
		eLotteryBeautyType, #(枚举类型：ELotteryBeautyType)抽奖类型,只有单次金币，银币两种类型
		dwNextChatTime #(UINT32)下次聊天冷却时间
	)
		raise NotImplementedError
	end
	#接收：当前已免费抽奖次数
	def onRecv_LotteryFreeCntNotify(
		byFreeCnt #(UINT8)已免费抽奖次数
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取美女信息
	def onReturn_GetBeatyInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetBeatyInfo)返回的参数
	)
	end

	#返回：结识美女
	def onReturn_MeetBeauty(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_MeetBeauty)返回的参数
	)
	end

	#返回：和美女聊天
	def onReturn_ChatBeauty(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ChatBeauty)返回的参数
	)
	end

	#返回：送美女礼品
	def onReturn_SendPrizeBeauty(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SendPrizeBeauty)返回的参数
	)
	end

	#返回：抽奖
	def onReturn_LotteryBeauty(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LotteryBeauty)返回的参数
	)
	end

	#返回：美女出战
	def onReturn_BeautyFight(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BeautyFight)返回的参数
	)
	end

	#返回：获取稀有物品列表
	def onReturn_GetRareItemList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetRareItemList)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：美女信息更新
	def _doRecv_BeautyNotify(data)
		oBeauty = SBeauty::fromStream(data)
		return onRecv_BeautyNotify(oBeauty)
	end

	#接收处理：爱心数目更新
	def _doRecv_LoveHeartCntNotify(data)
		dwLoveCnt = ByteUtil::readUINT32(data)
		return onRecv_LoveHeartCntNotify(dwLoveCnt)
	end

	#接收处理：聊天cd
	def _doRecv_ChatCdNotify(data)
		dwNextChatTime = ByteUtil::readUINT32(data)
		return onRecv_ChatCdNotify(dwNextChatTime)
	end

	#接收处理：免费抽奖cd
	def _doRecv_FreeMoneyCdNotify(data)
		eLotteryBeautyType = ByteUtil::readUINT16(data)
		dwNextChatTime = ByteUtil::readUINT32(data)
		return onRecv_FreeMoneyCdNotify(eLotteryBeautyType, dwNextChatTime)
	end

	#接收处理：当前已免费抽奖次数
	def _doRecv_LotteryFreeCntNotify(data)
		byFreeCnt = ByteUtil::readUINT8(data)
		return onRecv_LotteryFreeCntNotify(byFreeCnt)
	end

#以下为返回处理函数
	#返回处理：获取美女信息
	def _doReturn_GetBeatyInfo(data)
		retParam = SRetParam_GetBeatyInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecBeauty = SBeauty::vectorFromStream(data) #(SBeauty的数组)美女信息列表
		dwLoveCnt = ByteUtil::readUINT32(data) #(UINT32)爱心个数
		dwNextChatTime = ByteUtil::readUINT32(data) #(UINT32)下次聊天冷却时间
		dwNextGoldLotteryTime = ByteUtil::readUINT32(data) #(UINT32)下次免费金币抽奖冷却时间
		dwNextSilverLotterTime = ByteUtil::readUINT32(data) #(UINT32)下次免费银币冷却时间
		wBeautyID = ByteUtil::readUINT16(data) #(UINT16)出战美女ID
		retParam.vecBeauty = vecBeauty
		retParam.dwLoveCnt = dwLoveCnt
		retParam.dwNextChatTime = dwNextChatTime
		retParam.dwNextGoldLotteryTime = dwNextGoldLotteryTime
		retParam.dwNextSilverLotterTime = dwNextSilverLotterTime
		retParam.wBeautyID = wBeautyID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetBeatyInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取美女信息
	def _onTimeOut_GetBeatyInfo(sessionID)
		retParam = SRetParam_GetBeatyInfo.new;
		onReturn_GetBeatyInfo(2, retParam)
	end

	#返回处理：结识美女
	def _doReturn_MeetBeauty(data)
		retParam = SRetParam_MeetBeauty.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EBeautyRet)操作结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_MeetBeauty(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：结识美女
	def _onTimeOut_MeetBeauty(sessionID)
		retParam = SRetParam_MeetBeauty.new;
		onReturn_MeetBeauty(2, retParam)
	end

	#返回处理：和美女聊天
	def _doReturn_ChatBeauty(data)
		retParam = SRetParam_ChatBeauty.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EBeautyRet)操作结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ChatBeauty(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：和美女聊天
	def _onTimeOut_ChatBeauty(sessionID)
		retParam = SRetParam_ChatBeauty.new;
		onReturn_ChatBeauty(2, retParam)
	end

	#返回处理：送美女礼品
	def _doReturn_SendPrizeBeauty(data)
		retParam = SRetParam_SendPrizeBeauty.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EBeautyRet)操作结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SendPrizeBeauty(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：送美女礼品
	def _onTimeOut_SendPrizeBeauty(sessionID)
		retParam = SRetParam_SendPrizeBeauty.new;
		onReturn_SendPrizeBeauty(2, retParam)
	end

	#返回处理：抽奖
	def _doReturn_LotteryBeauty(data)
		retParam = SRetParam_LotteryBeauty.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EBeautyRet)操作结果
		vecItemGenInfo = SItemGenInfo::vectorFromStream(data) #(SItemGenInfo的数组)物品列表
		retParam.eRet = eRet
		retParam.vecItemGenInfo = vecItemGenInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LotteryBeauty(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：抽奖
	def _onTimeOut_LotteryBeauty(sessionID)
		retParam = SRetParam_LotteryBeauty.new;
		onReturn_LotteryBeauty(2, retParam)
	end

	#返回处理：美女出战
	def _doReturn_BeautyFight(data)
		retParam = SRetParam_BeautyFight.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：EBeautyRet)操作结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BeautyFight(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：美女出战
	def _onTimeOut_BeautyFight(sessionID)
		retParam = SRetParam_BeautyFight.new;
		onReturn_BeautyFight(2, retParam)
	end

	#返回处理：获取稀有物品列表
	def _doReturn_GetRareItemList(data)
		retParam = SRetParam_GetRareItemList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecItemID = ByteUtil::readVecUINT16(data) #(UINT16数组)稀有物品列表
		retParam.vecItemID = vecItemID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetRareItemList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取稀有物品列表
	def _onTimeOut_GetRareItemList(sessionID)
		retParam = SRetParam_GetRareItemList.new;
		onReturn_GetRareItemList(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 131;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_BeautyNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_LoveHeartCntNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_ChatCdNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_FreeMoneyCdNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_LotteryFreeCntNotify' #FuncID: 5

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetBeatyInfo' #FuncID: 1
		@retFuncList[1] = '_doReturn_MeetBeauty' #FuncID: 2
		@retFuncList[2] = '_doReturn_ChatBeauty' #FuncID: 3
		@retFuncList[3] = '_doReturn_SendPrizeBeauty' #FuncID: 4
		@retFuncList[4] = '_doReturn_LotteryBeauty' #FuncID: 5
		@retFuncList[5] = '_doReturn_BeautyFight' #FuncID: 6
		@retFuncList[6] = '_doReturn_GetRareItemList' #FuncID: 7

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetBeatyInfo' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_MeetBeauty' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_ChatBeauty' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_SendPrizeBeauty' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_LotteryBeauty' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_BeautyFight' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_GetRareItemList' #FuncID: 7
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

