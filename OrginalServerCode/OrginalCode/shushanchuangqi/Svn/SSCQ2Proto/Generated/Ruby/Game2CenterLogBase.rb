#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    Game2CenterLog.rb
#  Purpose:      GameServer到CenterServer的数据中心log协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#操作类型
class EOpType
	EOPTYPEGM = 0#GM操作
	EOPTYPEITEMCHANGE = 1#道具获得与使用操作
	EOPTYPEMONEYCHANGE = 2#货币获得与使用操作
	EOPTYPEEND = 3#结束
end

#帐号金钱变化信息
class SUserMoneyChange
	attr_accessor:eMoneyType #(枚类型：ProtoCommon::EMoneyType)货币类型
	attr_accessor:dwValue #(INT32)值
	attr_accessor:wFromTo #(UINT16)货币来源or消耗类型(dwValue>0来源 dwValue<0消耗)

	#构造函数
	def initialize
		@eMoneyType = 0
		@dwValue = 0
		@wFromTo = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eMoneyType = @eMoneyType
		obj.dwValue = @dwValue
		obj.wFromTo = @wFromTo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SUserMoneyChange.new
		s.eMoneyType = ByteUtil::readUINT8(data)
		s.dwValue = ByteUtil::readINT32(data)
		s.wFromTo = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SUserMoneyChange::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eMoneyType)
		ByteUtil::writeINT32(data, @dwValue)
		ByteUtil::writeUINT16(data, @wFromTo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帐号道具变化信息
class SUserItemChange
	attr_accessor:wItemID #(UINT16)道具ID
	attr_accessor:dwCount #(INT32)数量
	attr_accessor:dwPrice #(float)价格
	attr_accessor:wFromTo #(UINT16)道具来源or消耗类型(dwCount>0来源 dwCount<0消耗)

	#构造函数
	def initialize
		@wItemID = 0
		@dwCount = 0
		@dwPrice = 0
		@wFromTo = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wItemID = @wItemID
		obj.dwCount = @dwCount
		obj.dwPrice = @dwPrice
		obj.wFromTo = @wFromTo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SUserItemChange.new
		s.wItemID = ByteUtil::readUINT16(data)
		s.dwCount = ByteUtil::readINT32(data)
		s.dwPrice = ByteUtil::readFLOAT(data)
		s.wFromTo = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SUserItemChange::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeINT32(data, @dwCount)
		ByteUtil::writeFLOAT(data, @dwPrice)
		ByteUtil::writeUINT16(data, @wFromTo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#协议类：GameServer到CenterServer的数据中心log协议
class Game2CenterLogBase < ProtocolBase
	#以下为发送函数
	#发送：log注册记录
	def send_LogRegister(
		qwUsrID,  #(UINT64)帐号ID
		vecStrInfo #(string数组)用户登陆平台信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeVecSTRING(data, vecStrInfo)
		return @svrHandler.sendPacket(data)
	end

	#发送：log登陆
	def send_LogUserLogin(
		qwUsrID,  #(UINT64)帐号ID
		vecStrInfo #(string数组)用户登陆平台信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeVecSTRING(data, vecStrInfo)
		return @svrHandler.sendPacket(data)
	end

	#发送：log登出
	def send_LogPlayerLogout(
		dwTime,  #(UINT32)时间
		qwUsrID #(UINT64)帐号ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, dwTime)
		ByteUtil::writeUINT64(data, qwUsrID)
		return @svrHandler.sendPacket(data)
	end

	#发送：log玩家充值
	def send_LogRecharge(
		qwUsrID,  #(UINT64)帐号ID
		strUdp1,  #(string)udpLog参数1(平台传来的)
		strUdp2,  #(string)udpLog参数2(平台传来的)
		dwGold #(UINT32)仙石数量
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeSTRING(data, strUdp1)
		ByteUtil::writeSTRING(data, strUdp2)
		ByteUtil::writeUINT32(data, dwGold)
		return @svrHandler.sendPacket(data)
	end

	#发送：log金钱变化
	def send_LogMoneyChange(
		qwUsrID,  #(UINT64)帐号ID
		eType,  #(枚举类型：EOpType)类型
		vecMoney #(SUserMoneyChange的数组)货币
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeUINT8(data, eType)
		SUserMoneyChange::vectorToStream(data, vecMoney)
		return @svrHandler.sendPacket(data)
	end

	#发送：log道具变化
	def send_LogItemChange(
		qwUsrID,  #(UINT64)帐号ID
		eType,  #(枚举类型：EOpType)类型
		vecItem #(SUserItemChange的数组)道具
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeUINT8(data, eType)
		SUserItemChange::vectorToStream(data, vecItem)
		return @svrHandler.sendPacket(data)
	end

	#发送：log新手引导变化
	def send_LogGuideChange(
		qwUsrID,  #(UINT64)帐号ID
		strCategory,  #(string)引导类 load或guide
		strStep #(string)引导ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeSTRING(data, strCategory)
		ByteUtil::writeSTRING(data, strStep)
		return @svrHandler.sendPacket(data)
	end

	#发送：log自定义行为变化
	def send_LogActiveChange(
		qwUsrID,  #(UINT64)帐号ID
		strCategory,  #(string)行为分类
		strAction,  #(string)用户行为
		dwCount #(UINT32)
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeSTRING(data, strCategory)
		ByteUtil::writeSTRING(data, strAction)
		ByteUtil::writeUINT32(data, dwCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：log自定义行为变化
	def send_LogAct(
		qwUsrID,  #(UINT64)帐号ID
		strCategory,  #(string)行为分类
		strAction,  #(string)用户行为
		strParam3,  #(string)用户行为
		strParam4,  #(string)用户行为
		strParam5,  #(string)用户行为
		strParam6,  #(string)用户行为
		dwCount #(UINT32)
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeSTRING(data, strCategory)
		ByteUtil::writeSTRING(data, strAction)
		ByteUtil::writeSTRING(data, strParam3)
		ByteUtil::writeSTRING(data, strParam4)
		ByteUtil::writeSTRING(data, strParam5)
		ByteUtil::writeSTRING(data, strParam6)
		ByteUtil::writeUINT32(data, dwCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：log服务器变化
	def send_LogServerInfo(
		dwTime,  #(UINT32)时间
		strType,  #(string)记录类型
		strSubType,  #(string)记录分类型
		dwNum #(UINT32)记录数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, dwTime)
		ByteUtil::writeSTRING(data, strType)
		ByteUtil::writeSTRING(data, strSubType)
		ByteUtil::writeUINT32(data, dwNum)
		return @svrHandler.sendPacket(data)
	end

	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 61;
		@recvFuncList = Array.new
	end

	def handleMessage(data)
		return true;
	end
end

