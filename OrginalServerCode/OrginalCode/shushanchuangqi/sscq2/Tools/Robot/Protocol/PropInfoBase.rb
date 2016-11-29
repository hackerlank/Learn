#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    PropInfo.rb
#  Purpose:      属性相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#变更对象类型
class EPropClass
	ECLASSROLE = 0#角色
	ECLASSFIGHTER = 1#将
	ECLASSEQUIP = 2#装备
	ECLASSOROLE = 3#其他角色
end

#属性的类型
class EPropType
	EPROPNONE = 0#无
	EPROPGOLD = 1#仙石
	EPROPSILVER = 2#银币
	EPROPCOUPON = 3#礼券
	EPROPPGIFTCOIN = 4#金券
	EPROPEXPTEMP = 5#经验(占位)
	EPROPPRESTIGE = 6#声望
	EPROPSOUL = 7#魂魄
	EPROPHONOR = 8#荣誉
	EPROPPEXP = 9#修为
	EPROPSIGIL = 10#符印
	EPROPCENTSY = 11#仙元
	EPROPACTION = 12#体力
	EPROPSOP = 13#阅历
	EPROPTAOISM = 14#道术
	EPROPPOTEN = 15#渡劫点数
	EPROPREIKI = 16#副本星级
	EPROPHFP = 17#寻仙积分
	EPROPDEMONSOUL = 18#锁妖塔魂值
	EPROPSOULATTACK = 19#攻击之魂
	EPROPSOULHP = 20#生命之魂
	EPROPSOULCRITICAL = 21#暴击之魂
	EPROPSOULCOUNTER = 22#反击之魂
	EPROPSOULSPEED = 23#身法之魂
	EPROPSOULDEFENCE = 24#防御之魂
	EPROPSOULHIT = 25#命中之魂
	EPROPSOULDODGE = 26#闪避之魂
	EPROPACHIEVEMENTAP = 27#成就点
	EPROPCOLLECTAP = 28#收藏点
	EPROPGUILDCONTRIB = 29#帮派贡献
	EPROPSTAMPHUANG = 30#黄阶除魔印
	EPROPSTAMPXUAN = 31#玄阶除魔印
	EPROPSTAMPDI = 32#地阶除魔印
	EPROPSTAMPTIAN = 33#天阶除魔印
	EPROPSTAMPXING = 34#星阶除魔印
	EPROPSTAMPYUE = 35#月阶除魔印
	EPROPSTAMPDI2 = 36#帝阶除魔印
	EPROPSTAMPXIAN = 37#仙阶除魔印
	EPROPSTAMPSHENG = 38#圣阶除魔印
	EPROPSTAMPFO = 39#佛阶除魔印
	EPROPLOVEHEART = 40#爱心
	EPROPBLUEFAIRYFATE = 51#蓝色仙缘
	EPROPPURPLEFAIRYFATE = 52#紫色仙缘
	EPROPORANGEFAIRYFATE = 53#橙色仙缘
	EPROPDUJIEFU = 56#渡劫符
	EPROPLUCKYCOUPON = 57#抽奖券
	EPROPMONEYEND = 100#钱币属性结束标志
	EPROPCOMMON = 200#普通定义
	EPROPTOTALRECHARGE = 201#总充值数
	EPROPBTPOINT = 202#战斗力
	EPROPHERO = 300#将定义
	EPROPPOS = 301#将在阵型中的位置
	EPROPTROOPPOS = 302#将在队伍中的位置
	EPROPPOTENTIAL = 303#潜力
	EPROPCAPACITY = 304#资质
	EPROPLEVEL = 305#等级
	EPROPLUCKY = 306#机缘值
	EPROPEXP = 307#经验 -- UINT64
	EPROPLIANPI = 308#炼皮
	EPROPTONGJIN = 309#通筋
	EPROPQIANGJI = 310#强肌
	EPROPDUANGU = 311#锻骨
	EPROPMAX = 312#属性枚举最大值
end

#属性操作的结果
class EPropResult
	EPROPSUCCEED = 0#无
	EPROPGOLDERR = 1#仙石不够
	EPROPSILVERERR = 2#银币不够
	EPROPCOUPONERR = 3#礼券不够
	EPROPOTHERERR = 4#其它错误
end

#兑换结果
class EExchangeResult
	EEXCHANGERESULTSUCCESS = 0#兑换成功
	EEXCHANGERESULTFAILED = 1#兑换失败
	EEXCHANGERESULTLACK = 2#兑换数量不足
	EEXCHANGERESULTLIMIT = 3#兑换已达上限
	EEXCHANGERESULTMAX = 4#兑换结果最大值
end

#属性信息
class SPropValue
	attr_accessor:ePropType #(枚举类型：EPropType)属性类型
	attr_accessor:value #(UINT32)属性值，需要根据类型来转换

	#构造函数
	def initialize
		@ePropType = 0
		@value = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.ePropType = @ePropType
		obj.value = @value
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPropValue.new
		s.ePropType = ByteUtil::readUINT16(data)
		s.value = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPropValue::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @ePropType)
		ByteUtil::writeUINT32(data, @value)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#属性信息
class SPropQWValue
	attr_accessor:ePropType #(枚举类型：EPropType)属性类型
	attr_accessor:value #(UINT64)属性值，需要根据类型来转换

	#构造函数
	def initialize
		@ePropType = 0
		@value = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.ePropType = @ePropType
		obj.value = @value
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPropQWValue.new
		s.ePropType = ByteUtil::readUINT16(data)
		s.value = ByteUtil::readUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPropQWValue::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @ePropType)
		ByteUtil::writeUINT64(data, @value)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#扩展属性信息
class SPropValExt
	attr_accessor:ePropType #(枚举类型：EPropType)属性类型
	attr_accessor:value #(float)属性值，需要根据类型来转换
	attr_accessor:ext #(INT32)扩展值，不同用途作不同的解释

	#构造函数
	def initialize
		@ePropType = 0
		@value = 0
		@ext = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.ePropType = @ePropType
		obj.value = @value
		obj.ext = @ext
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPropValExt.new
		s.ePropType = ByteUtil::readUINT16(data)
		s.value = ByteUtil::readFLOAT(data)
		s.ext = ByteUtil::readINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPropValExt::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @ePropType)
		ByteUtil::writeFLOAT(data, @value)
		ByteUtil::writeINT32(data, @ext)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#扩展属性信息
class SPropQWValExt
	attr_accessor:ePropType #(枚举类型：EPropType)属性类型
	attr_accessor:value #(UINT64)属性值，需要根据类型来转换
	attr_accessor:ext #(INT32)扩展值，不同用途作不同的解释

	#构造函数
	def initialize
		@ePropType = 0
		@value = 0
		@ext = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.ePropType = @ePropType
		obj.value = @value
		obj.ext = @ext
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPropQWValExt.new
		s.ePropType = ByteUtil::readUINT16(data)
		s.value = ByteUtil::readUINT64(data)
		s.ext = ByteUtil::readINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPropQWValExt::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @ePropType)
		ByteUtil::writeUINT64(data, @value)
		ByteUtil::writeINT32(data, @ext)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[MoneyExchange:货币兑换]的返回的参数组成的结构体
class SRetParam_MoneyExchange
	attr_accessor:eResult#(枚举类型：EExchangeResult)兑换结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：属性相关协议
class PropInfoBase < ProtocolBase
	#以下为发送函数
	#发送：货币兑换
	def send_MoneyExchange(
		eSrcProp,  #(枚举类型：EPropType)源货币
		eDestProp,  #(枚举类型：EPropType)目标货币
		dwCount #(UINT32)数量
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, eSrcProp)
		ByteUtil::writeUINT16(data, eDestProp)
		ByteUtil::writeUINT32(data, dwCount)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：属性列表通知(改变后通知)
	def onRecv_PropListNotify(
		qwInstID, #(UINT64)变更对象ID
		eClass, #(枚举类型：EPropClass)变更对象类型
		vecPropValue #(SPropValue的数组)属性列表
	)
		raise NotImplementedError
	end
	#接收：属性列表通知(改变后通知)
	def onRecv_PropNotify(
		qwInstID, #(UINT64)变更对象ID
		eClass, #(枚举类型：EPropClass)变更对象类型
		vecPropValue, #(SPropValue的数组)属性列表
		bType #(bool)是否飘字
	)
		raise NotImplementedError
	end
	#接收：扩展属性列表通知(改变后通知)
	def onRecv_PropExtListNotify(
		qwInstID, #(UINT64)变更对象ID
		eClass, #(枚举类型：EPropClass)变更对象类型
		vecPropValExt #(SPropValExt的数组)扩展属性列表
	)
		raise NotImplementedError
	end
	#接收：属性列表通知(改变后通知)
	def onRecv_PropQWListNotify(
		qwInstID, #(UINT64)变更对象ID
		eClass, #(枚举类型：EPropClass)变更对象类型
		vecPropValue #(SPropQWValue的数组)属性列表
	)
		raise NotImplementedError
	end
	#接收：扩展属性列表通知(改变后通知)
	def onRecv_PropQWExtListNotify(
		qwInstID, #(UINT64)变更对象ID
		eClass, #(枚举类型：EPropClass)变更对象类型
		vecPropValExt #(SPropQWValExt的数组)扩展属性列表
	)
		raise NotImplementedError
	end
	#接收：Creature的名字改变通知
	def onRecv_NameChangeNotify(
		qwCreatureID, #(UINT64)生物ID
		strName #(string)新名字
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：货币兑换
	def onReturn_MoneyExchange(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_MoneyExchange)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：属性列表通知(改变后通知)
	def _doRecv_PropListNotify(data)
		qwInstID = ByteUtil::readUINT64(data)
		eClass = ByteUtil::readUINT8(data)
		vecPropValue = SPropValue::vectorFromStream(data)
		return onRecv_PropListNotify(qwInstID, eClass, vecPropValue)
	end

	#接收处理：属性列表通知(改变后通知)
	def _doRecv_PropNotify(data)
		qwInstID = ByteUtil::readUINT64(data)
		eClass = ByteUtil::readUINT8(data)
		vecPropValue = SPropValue::vectorFromStream(data)
		bType = ByteUtil::readBOOL(data)
		return onRecv_PropNotify(qwInstID, eClass, vecPropValue, bType)
	end

	#接收处理：扩展属性列表通知(改变后通知)
	def _doRecv_PropExtListNotify(data)
		qwInstID = ByteUtil::readUINT64(data)
		eClass = ByteUtil::readUINT8(data)
		vecPropValExt = SPropValExt::vectorFromStream(data)
		return onRecv_PropExtListNotify(qwInstID, eClass, vecPropValExt)
	end

	#接收处理：属性列表通知(改变后通知)
	def _doRecv_PropQWListNotify(data)
		qwInstID = ByteUtil::readUINT64(data)
		eClass = ByteUtil::readUINT8(data)
		vecPropValue = SPropQWValue::vectorFromStream(data)
		return onRecv_PropQWListNotify(qwInstID, eClass, vecPropValue)
	end

	#接收处理：扩展属性列表通知(改变后通知)
	def _doRecv_PropQWExtListNotify(data)
		qwInstID = ByteUtil::readUINT64(data)
		eClass = ByteUtil::readUINT8(data)
		vecPropValExt = SPropQWValExt::vectorFromStream(data)
		return onRecv_PropQWExtListNotify(qwInstID, eClass, vecPropValExt)
	end

	#接收处理：Creature的名字改变通知
	def _doRecv_NameChangeNotify(data)
		qwCreatureID = ByteUtil::readUINT64(data)
		strName = ByteUtil::readSTRING(data)
		return onRecv_NameChangeNotify(qwCreatureID, strName)
	end

#以下为返回处理函数
	#返回处理：货币兑换
	def _doReturn_MoneyExchange(data)
		retParam = SRetParam_MoneyExchange.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EExchangeResult)兑换结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_MoneyExchange(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：货币兑换
	def _onTimeOut_MoneyExchange(sessionID)
		retParam = SRetParam_MoneyExchange.new;
		onReturn_MoneyExchange(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 17;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_PropListNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_PropNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_PropExtListNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_PropQWListNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_PropQWExtListNotify' #FuncID: 5
		@recvFuncList[5] = '_doRecv_NameChangeNotify' #FuncID: 6

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_MoneyExchange' #FuncID: 1

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_MoneyExchange' #FuncID: 1
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

