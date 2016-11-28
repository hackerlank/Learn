#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    DBProt.rb
#  Purpose:      数据库查询协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#查询参数的类型
class EParamType
	ETYPEINT8 = 1#INT8类型
	ETYPEUINT8 = 2#UINT8类型
	ETYPEINT16 = 3#INT16类型
	ETYPEUINT16 = 4#UINT16类型
	ETYPEINT32 = 5#INT32类型
	ETYPEUINT32 = 6#UINT32类型
	ETYPEINT64 = 7#INT64类型
	ETYPEUINT64 = 8#UINT64类型
	ETYPEFLOAT = 9#float类型
	ETYPEDOUBLE = 10#double类型
	ETYPESTRING = 11#string类型
	ETYPEBLOB = 12#Blob类型
	ETYPEDATETIME = 13#DateTime类型
	ETYPEDATE = 14#Date类型
	ETYPETIME = 15#Time类型
end

#查询的类型
class EQueryType
	EQUERYNORMAL = 0#普通的查询
	EQUERYSAVE0 = 1#保存玩家数据的查询
	EQUERYSAVE1 = 2#保存玩家数据的查询
	EQUERYSAVE2 = 3#保存玩家数据的查询
	EQUERYSAVE3 = 4#保存玩家数据的查询
	EQUERYSAVEMAX = 5#保存玩家数据的查询最大
	EQUERYMAIL = 6#邮件相关的查询
	EQUERYARENA = 7#斗剑相关查询
	EQUERYGUILD = 8#帮派相关查询
	EQUERYRANK = 9#排行榜相关查询
	EQUERYRECHARGE = 10#充值相关查询
	EQUERYEND = 11#结束
end

#查询的参数
class SParam
	attr_accessor:eType #(枚举类型：EParamType)类型
	attr_accessor:strVal #(string)序列化后的值

	#构造函数
	def initialize
		@eType = 0
		@strVal = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eType = @eType
		obj.strVal = @strVal
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SParam.new
		s.eType = ByteUtil::readUINT8(data)
		s.strVal = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SParam::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eType)
		ByteUtil::writeSTRING(data, @strVal)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#查询
class SQuery
	attr_accessor:strQuery #(string)查询字符串
	attr_accessor:vecParam #(SParam的数组)参数列表
	attr_accessor:bHasResult #(bool)是否有结果集

	#构造函数
	def initialize
		@strQuery = ''
		@vecParam = Array.new
		@bHasResult = false
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strQuery = @strQuery
		obj.vecParam = @vecParam
		obj.bHasResult = @bHasResult
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SQuery.new
		s.strQuery = ByteUtil::readSTRING(data)
		s.vecParam = SParam::vectorFromStream(data)
		s.bHasResult = ByteUtil::readBOOL(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SQuery::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeSTRING(data, @strQuery)
		SParam::vectorToStream(data, @vecParam)
		ByteUtil::writeBOOL(data, @bHasResult)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#查询的一个属性的结果
class SRes
	attr_accessor:strVal #(string)序列化后的值

	#构造函数
	def initialize
		@strVal = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strVal = @strVal
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRes.new
		s.strVal = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRes::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeSTRING(data, @strVal)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#查询的一行结果集
class SRow
	attr_accessor:vecRes #(SRes的数组)属性结果的列表

	#构造函数
	def initialize
		@vecRes = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.vecRes = @vecRes
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRow.new
		s.vecRes = SRes::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRow::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		SRes::vectorToStream(data, @vecRes)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#查询的多行结果组成的一张表
class STable
	attr_accessor:byIndex #(UINT8)结果表对应查询中SQL语句的索引(从0开始)
	attr_accessor:bMore #(bool)是否有更多的结果
	attr_accessor:vecRow #(SRow的数组)所有行结果的列表

	#构造函数
	def initialize
		@byIndex = 0
		@bMore = false
		@vecRow = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byIndex = @byIndex
		obj.bMore = @bMore
		obj.vecRow = @vecRow
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STable.new
		s.byIndex = ByteUtil::readUINT8(data)
		s.bMore = ByteUtil::readBOOL(data)
		s.vecRow = SRow::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STable::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byIndex)
		ByteUtil::writeBOOL(data, @bMore)
		SRow::vectorToStream(data, @vecRow)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#协议类：数据库查询协议
class DBProtBase < ProtocolBase
	#以下为发送函数
	#发送：查询请求
	def send_QueryReq(
		dwTransID,  #(UINT32)事务的ID
		eQueryType,  #(枚举类型：EQueryType)查询类型
		query #(类类型：SQuery)查询
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, dwTransID)
		ByteUtil::writeUINT8(data, eQueryType)
		query.toStream(data)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：无结果集的返回
	def onRecv_ResultRet(
		dwTransID, #(UINT32)事务的ID
		byRet, #(INT8)返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
		dwAffectRow #(UINT32)影响的行数
	)
		raise NotImplementedError
	end
	#接收：有结果集的返回
	def onRecv_ResultDataRet(
		dwTransID, #(UINT32)事务的ID
		byRet, #(INT8)返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
		vecTable, #(STable的数组)返回的结果表集
		byCount #(UINT8)结果表数量
	)
		raise NotImplementedError
	end
#以下为接收处理函数
	#接收处理：无结果集的返回
	def _doRecv_ResultRet(data)
		dwTransID = ByteUtil::readUINT32(data)
		byRet = ByteUtil::readINT8(data)
		dwAffectRow = ByteUtil::readUINT32(data)
		return onRecv_ResultRet(dwTransID, byRet, dwAffectRow)
	end

	#接收处理：有结果集的返回
	def _doRecv_ResultDataRet(data)
		dwTransID = ByteUtil::readUINT32(data)
		byRet = ByteUtil::readINT8(data)
		vecTable = STable::vectorFromStream(data)
		byCount = ByteUtil::readUINT8(data)
		return onRecv_ResultDataRet(dwTransID, byRet, vecTable, byCount)
	end

	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 9;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_ResultRet' #FuncID: 1
		@recvFuncList[1] = '_doRecv_ResultDataRet' #FuncID: 2
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

