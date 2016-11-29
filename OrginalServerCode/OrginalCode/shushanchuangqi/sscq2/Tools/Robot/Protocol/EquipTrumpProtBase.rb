#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    EquipTrumpProt.rb
#  Purpose:      道具相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ItemProtBase.rb'

#以下为类型定义

#装备法宝操作结果
class EEquipTrumpResult
	EETRSUCCESS = 0#成功
	EETRFAILED = 1#失败
	EETRNOTEXIST = 2#不存在
	EETRINOTHERS = 3#在其他人身上
	EETRSLOTFULL = 4#槽位已满
	EETRSLOTLOCK = 5#槽位未开启
	EETRSLOTCONFLICT = 6#法宝冲突
	EETRMAX = 7#最大值
end

#装备法宝强化结果
class EEquipTrumpIntensifyResult
	EETIRSUCCESS = 0#装备法宝强化成功
	EETIRFAILED = 1#未知错误
	EETIRCRIT = 2#装备法宝强化成功并暴击
	EETIRMAXERR = 3#已达最大强化等级
	EETIRSILVERERR = 4#强化时银币不足
	EETIRITEMERR = 5#强化时物品不足
	EETIRCFGERR = 6#强化配置错误
	EETIRTYPEERR = 7#强化参数错误
	EETIRRANDOMFAILERR = 8#强化失败
end

#装备法宝合成结果
class EEquipTrumpMergeResult
	EETMRSUCCESS = 0#成功
	EETMRFAILED = 1#失败
	EETMRLACKOFMATERIAL = 2#材料不足
	EETMRLACKOFSILVER = 3#银币不足
	EETMRPACKFULL = 4#背包已满
	EETMRMAX = 5#最大值
end

#装备法宝分解结果
class EEquipTrumpBreakResult
	EETBRSUCCESS = 0#成功
	EETBRFAILED = 1#失败
	EETBRPACKFULL = 2#背包已满
	EETBREQUIPED = 3#仍在装备中
	EETBRMAX = 4#最大值
end

#装备法宝洗炼结果
class EEquipTrumpShuffleResult
	EETSRSUCCESS = 0#装备法宝洗炼成功
	EETSRFAILED = 1#装备法宝洗炼失败
	EETSRLEVELERR = 2#装备法宝洗炼时玩家等级不足
	EETSRSILVERERR = 3#洗炼时银币不足
	EETSRMATERIALERR = 4#洗炼时材料不足
end

#能装备法宝的道具类型
class EEquipTrumpType
	EETTNONE = 0#无
	EETTINNATE = 1#先天法宝
	EETTPASSIVE = 2#被动法宝
	EETTHALO = 3#光环法宝
	EETTTRANSFORM = 4#变身法宝
	EETTEND = 5#结束
end

#装备法宝位类型
class EEquipTrumpSlotType
	EETSTNONE = 0#无
	EETSTINNATE = 1#先天法宝
	EETSTPASSIVE = 2#被动
	EETSTHALO = 3#光环
	EETSTTRANSFORM = 4#变身
	EETSTMAX = 5#结束
end

#装备法宝强化类型
class ETIntensifyType
	EETINTENSIFY_NONE = 0#无
	EETINTENSIFY_NORMALGOLD = 1#太乙真金
	EETINTENSIFY_GODGOLD = 2#太乙精金
	EETINTENSIFY_MAX = 3#结束
end

#最大洗练属性
class SMaxShuffleInfo
	attr_accessor:dwType #(UINT32)洗炼类型
	attr_accessor:dwValue #(UINT32)洗炼数值

	#构造函数
	def initialize
		@dwType = 0
		@dwValue = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwType = @dwType
		obj.dwValue = @dwValue
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMaxShuffleInfo.new
		s.dwType = ByteUtil::readUINT32(data)
		s.dwValue = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMaxShuffleInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwType)
		ByteUtil::writeUINT32(data, @dwValue)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#洗练区间属性
class SXiLianProb
	attr_accessor:dwMinRate #(UINT32)洗炼最小概率
	attr_accessor:dwMaxRate #(UINT32)洗炼最大概率
	attr_accessor:dwRateValue #(UINT32)洗炼权值空间

	#构造函数
	def initialize
		@dwMinRate = 0
		@dwMaxRate = 0
		@dwRateValue = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwMinRate = @dwMinRate
		obj.dwMaxRate = @dwMaxRate
		obj.dwRateValue = @dwRateValue
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SXiLianProb.new
		s.dwMinRate = ByteUtil::readUINT32(data)
		s.dwMaxRate = ByteUtil::readUINT32(data)
		s.dwRateValue = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SXiLianProb::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwMinRate)
		ByteUtil::writeUINT32(data, @dwMaxRate)
		ByteUtil::writeUINT32(data, @dwRateValue)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetAllEquipTrump:获得所有装备法宝]的返回的参数组成的结构体
class SRetParam_GetAllEquipTrump
	attr_accessor:vecEquipTrump#(SEquipTrump的数组)当前装备法宝的列表

	#构造函数
	def initialize
		@vecEquipTrump = Array.new
	end
end

#函数[Wear:请求穿上装备法宝]的返回的参数组成的结构体
class SRetParam_Wear
	attr_accessor:eResult#(枚举类型：EEquipTrumpResult)穿上装备法宝的结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[WearOneKey:请求一键穿上装备法宝]的返回的参数组成的结构体
class SRetParam_WearOneKey
	attr_accessor:eResult#(枚举类型：EEquipTrumpResult)穿上装备法宝的结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[TakeOff:请求脱下装备法宝]的返回的参数组成的结构体
class SRetParam_TakeOff
	attr_accessor:eResult#(枚举类型：EEquipTrumpResult)脱下装备法宝的结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[Swap:交换法宝]的返回的参数组成的结构体
class SRetParam_Swap
	attr_accessor:eResult#(枚举类型：EEquipTrumpResult)换位置的结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[MergeEquipTrump:请求合成装备法宝]的返回的参数组成的结构体
class SRetParam_MergeEquipTrump
	attr_accessor:eResult#(枚举类型：EEquipTrumpMergeResult)结果
	attr_accessor:vecItem#(SItem的数组)新增的道具

	#构造函数
	def initialize
		@eResult = 0
		@vecItem = Array.new
	end
end

#函数[BreakEquipTrump:请求分解装备法宝]的返回的参数组成的结构体
class SRetParam_BreakEquipTrump
	attr_accessor:eResult#(枚举类型：EEquipTrumpBreakResult)结果
	attr_accessor:vecItem#(SItemGenInfo的数组)分解产生的道具

	#构造函数
	def initialize
		@eResult = 0
		@vecItem = Array.new
	end
end

#函数[Intensify:装备法宝强化]的返回的参数组成的结构体
class SRetParam_Intensify
	attr_accessor:bSucess#(bool)成功/失败
	attr_accessor:eResult#(枚举类型：EEquipTrumpIntensifyResult)结果

	#构造函数
	def initialize
		@bSucess = false
		@eResult = 0
	end
end

#函数[IntensifyOneKey:装备法宝一键强化]的返回的参数组成的结构体
class SRetParam_IntensifyOneKey
	attr_accessor:bSucess#(bool)成功/失败
	attr_accessor:dwIntensifyCount#(UINT32)强化次数（包括成功
	attr_accessor:eResult#(枚举类型：EEquipTrumpIntensifyResult)结果

	#构造函数
	def initialize
		@bSucess = false
		@dwIntensifyCount = 0
		@eResult = 0
	end
end

#函数[ShuffleResult:装备法宝洗炼]的返回的参数组成的结构体
class SRetParam_ShuffleResult
	attr_accessor:eResult#(枚举类型：EEquipTrumpShuffleResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：道具相关协议
class EquipTrumpProtBase < ProtocolBase
	#以下为发送函数
	#发送：获得所有装备法宝
	def send_GetAllEquipTrump(
		qwOwnerID #(UINT64)散仙唯一ID（0表示获取所有散仙法宝）
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwOwnerID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求穿上装备法宝
	def send_Wear(
		qwOwnerID,  #(UINT64)散仙唯一ID
		qwInstID #(UINT64)装备法宝唯一ID
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwOwnerID)
		ByteUtil::writeUINT64(data, qwInstID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求一键穿上装备法宝
	def send_WearOneKey(
		qwOwnerID #(UINT64)散仙唯一ID
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwOwnerID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求脱下装备法宝
	def send_TakeOff(
		qwInstID,  #(UINT64)装备法宝唯一ID
		wIndex #(INT16)-1：右击脱下；其他：包裹的位置
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeINT16(data, wIndex)
		return @svrHandler.sendPacket(data)
	end

	#发送：交换法宝
	def send_Swap(
		qwOwnerID,  #(UINT64)散仙唯一ID
		qwInstID,  #(UINT64)装备法宝唯一ID
		wIndex #(INT16)-1：右击脱下；其他：包裹的位置
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwOwnerID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeINT16(data, wIndex)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求合成装备法宝
	def send_MergeEquipTrump(
		wItemID,  #(UINT16)制作装备法宝模版ID
		wCount #(UINT16)数量
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wItemID)
		ByteUtil::writeUINT16(data, wCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求分解装备法宝
	def send_BreakEquipTrump(
		vecInstID #(UINT64数组)物品唯一ID
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeVecUINT64(data, vecInstID)
		return @svrHandler.sendPacket(data)
	end

	#发送：装备法宝强化
	def send_Intensify(
		qwInstID,  #(UINT64)装备法宝唯一ID
		eType #(枚举类型：ETIntensifyType)强化类型
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeINT8(data, eType)
		return @svrHandler.sendPacket(data)
	end

	#发送：装备法宝一键强化
	def send_IntensifyOneKey(
		qwInstID,  #(UINT64)装备法宝唯一ID
		eType #(枚举类型：ETIntensifyType)强化类型
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeINT8(data, eType)
		return @svrHandler.sendPacket(data)
	end

	#发送：装备法宝洗炼
	def send_ShuffleResult(
		qwInstID,  #(UINT64)装备法宝唯一ID
		dwLock #(UINT32)锁定属性（按位锁定 0x110 锁定2，3位）
	)
		sessionID = @sessionMgr.getNewSession(self, 10);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT32(data, dwLock)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：当前玩家角色的装备法宝通知
	def onRecv_EquipTrumpNotify(
		qwOwnerID, #(UINT64)散仙唯一ID
		eSlotType, #(枚举类型：EEquipTrumpSlotType)装备法宝位类型
		vecEquipTrump #(SEquipTrump的数组)当前装备法宝的列表
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获得所有装备法宝
	def onReturn_GetAllEquipTrump(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAllEquipTrump)返回的参数
	)
	end

	#返回：请求穿上装备法宝
	def onReturn_Wear(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Wear)返回的参数
	)
	end

	#返回：请求一键穿上装备法宝
	def onReturn_WearOneKey(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_WearOneKey)返回的参数
	)
	end

	#返回：请求脱下装备法宝
	def onReturn_TakeOff(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakeOff)返回的参数
	)
	end

	#返回：交换法宝
	def onReturn_Swap(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Swap)返回的参数
	)
	end

	#返回：请求合成装备法宝
	def onReturn_MergeEquipTrump(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_MergeEquipTrump)返回的参数
	)
	end

	#返回：请求分解装备法宝
	def onReturn_BreakEquipTrump(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BreakEquipTrump)返回的参数
	)
	end

	#返回：装备法宝强化
	def onReturn_Intensify(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Intensify)返回的参数
	)
	end

	#返回：装备法宝一键强化
	def onReturn_IntensifyOneKey(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_IntensifyOneKey)返回的参数
	)
	end

	#返回：装备法宝洗炼
	def onReturn_ShuffleResult(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ShuffleResult)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：当前玩家角色的装备法宝通知
	def _doRecv_EquipTrumpNotify(data)
		qwOwnerID = ByteUtil::readUINT64(data)
		eSlotType = ByteUtil::readINT8(data)
		vecEquipTrump = SEquipTrump::vectorFromStream(data)
		return onRecv_EquipTrumpNotify(qwOwnerID, eSlotType, vecEquipTrump)
	end

#以下为返回处理函数
	#返回处理：获得所有装备法宝
	def _doReturn_GetAllEquipTrump(data)
		retParam = SRetParam_GetAllEquipTrump.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecEquipTrump = SEquipTrump::vectorFromStream(data) #(SEquipTrump的数组)当前装备法宝的列表
		retParam.vecEquipTrump = vecEquipTrump
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAllEquipTrump(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获得所有装备法宝
	def _onTimeOut_GetAllEquipTrump(sessionID)
		retParam = SRetParam_GetAllEquipTrump.new;
		onReturn_GetAllEquipTrump(2, retParam)
	end

	#返回处理：请求穿上装备法宝
	def _doReturn_Wear(data)
		retParam = SRetParam_Wear.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EEquipTrumpResult)穿上装备法宝的结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_Wear(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求穿上装备法宝
	def _onTimeOut_Wear(sessionID)
		retParam = SRetParam_Wear.new;
		onReturn_Wear(2, retParam)
	end

	#返回处理：请求一键穿上装备法宝
	def _doReturn_WearOneKey(data)
		retParam = SRetParam_WearOneKey.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EEquipTrumpResult)穿上装备法宝的结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_WearOneKey(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求一键穿上装备法宝
	def _onTimeOut_WearOneKey(sessionID)
		retParam = SRetParam_WearOneKey.new;
		onReturn_WearOneKey(2, retParam)
	end

	#返回处理：请求脱下装备法宝
	def _doReturn_TakeOff(data)
		retParam = SRetParam_TakeOff.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EEquipTrumpResult)脱下装备法宝的结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakeOff(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求脱下装备法宝
	def _onTimeOut_TakeOff(sessionID)
		retParam = SRetParam_TakeOff.new;
		onReturn_TakeOff(2, retParam)
	end

	#返回处理：交换法宝
	def _doReturn_Swap(data)
		retParam = SRetParam_Swap.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EEquipTrumpResult)换位置的结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_Swap(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：交换法宝
	def _onTimeOut_Swap(sessionID)
		retParam = SRetParam_Swap.new;
		onReturn_Swap(2, retParam)
	end

	#返回处理：请求合成装备法宝
	def _doReturn_MergeEquipTrump(data)
		retParam = SRetParam_MergeEquipTrump.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EEquipTrumpMergeResult)结果
		vecItem = SItem::superVectorFromStream(data) #(SItem的数组)新增的道具
		retParam.eResult = eResult
		retParam.vecItem = vecItem
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_MergeEquipTrump(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求合成装备法宝
	def _onTimeOut_MergeEquipTrump(sessionID)
		retParam = SRetParam_MergeEquipTrump.new;
		onReturn_MergeEquipTrump(2, retParam)
	end

	#返回处理：请求分解装备法宝
	def _doReturn_BreakEquipTrump(data)
		retParam = SRetParam_BreakEquipTrump.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EEquipTrumpBreakResult)结果
		vecItem = SItemGenInfo::vectorFromStream(data) #(SItemGenInfo的数组)分解产生的道具
		retParam.eResult = eResult
		retParam.vecItem = vecItem
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BreakEquipTrump(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求分解装备法宝
	def _onTimeOut_BreakEquipTrump(sessionID)
		retParam = SRetParam_BreakEquipTrump.new;
		onReturn_BreakEquipTrump(2, retParam)
	end

	#返回处理：装备法宝强化
	def _doReturn_Intensify(data)
		retParam = SRetParam_Intensify.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		bSucess = ByteUtil::readBOOL(data) #(bool)成功/失败
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EEquipTrumpIntensifyResult)结果
		retParam.bSucess = bSucess
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_Intensify(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：装备法宝强化
	def _onTimeOut_Intensify(sessionID)
		retParam = SRetParam_Intensify.new;
		onReturn_Intensify(2, retParam)
	end

	#返回处理：装备法宝一键强化
	def _doReturn_IntensifyOneKey(data)
		retParam = SRetParam_IntensifyOneKey.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		bSucess = ByteUtil::readBOOL(data) #(bool)成功/失败
		dwIntensifyCount = ByteUtil::readUINT32(data) #(UINT32)强化次数（包括成功
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EEquipTrumpIntensifyResult)结果
		retParam.bSucess = bSucess
		retParam.dwIntensifyCount = dwIntensifyCount
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_IntensifyOneKey(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：装备法宝一键强化
	def _onTimeOut_IntensifyOneKey(sessionID)
		retParam = SRetParam_IntensifyOneKey.new;
		onReturn_IntensifyOneKey(2, retParam)
	end

	#返回处理：装备法宝洗炼
	def _doReturn_ShuffleResult(data)
		retParam = SRetParam_ShuffleResult.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EEquipTrumpShuffleResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ShuffleResult(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：装备法宝洗炼
	def _onTimeOut_ShuffleResult(sessionID)
		retParam = SRetParam_ShuffleResult.new;
		onReturn_ShuffleResult(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 30;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_EquipTrumpNotify' #FuncID: 1

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetAllEquipTrump' #FuncID: 1
		@retFuncList[1] = '_doReturn_Wear' #FuncID: 2
		@retFuncList[2] = '_doReturn_WearOneKey' #FuncID: 3
		@retFuncList[3] = '_doReturn_TakeOff' #FuncID: 4
		@retFuncList[4] = '_doReturn_Swap' #FuncID: 5
		@retFuncList[5] = '_doReturn_MergeEquipTrump' #FuncID: 6
		@retFuncList[6] = '_doReturn_BreakEquipTrump' #FuncID: 7
		@retFuncList[7] = '_doReturn_Intensify' #FuncID: 8
		@retFuncList[8] = '_doReturn_IntensifyOneKey' #FuncID: 9
		@retFuncList[9] = '_doReturn_ShuffleResult' #FuncID: 10

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetAllEquipTrump' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_Wear' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_WearOneKey' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_TakeOff' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_Swap' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_MergeEquipTrump' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_BreakEquipTrump' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_Intensify' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_IntensifyOneKey' #FuncID: 9
		@timeFuncList[9] = '_onTimeOut_ShuffleResult' #FuncID: 10
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

