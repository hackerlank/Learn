#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    Example.rb
#  Purpose:      通信协议示例
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#枚举类型示例
class EExTest
	EEXTEST1 = 0#枚举值1
	EEXTEST2 = 10#枚举值2
	EEXTEST3 = 32767#枚举值3
end

#结构体：SExBase的继承体系类型
class EType_SExBase
	ETYPE_SEXBASE = 0#类型：SExBase
	ETYPE_SEXDERIVED1 = 1#类型：SExDerived1
	ETYPE_SEXDERIVED2 = 2#类型：SExDerived2
	ETYPE_SEXDESCEND3 = 3#类型：SExDescend3
	ETYPE_SEXDESCEND4 = 4#类型：SExDescend4
end

#前置声明测试
class STest
	attr_accessor:pBase #(类类型：SExBase)父类指针
	attr_accessor:vecBase #(SExBase的数组)父类指针列表

	#构造函数
	def initialize
		@pBase = SExBase.new
		@vecBase = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.pBase = @pBase
		obj.vecBase = @vecBase
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STest.new
		s.pBase = SExBase::superFromStream(data)
		s.vecBase = SExBase::superVectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STest::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		@pBase.superToStream(data)
		SExBase::superVectorToStream(data, @vecBase)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#只在客户端生成
class SClient
	attr_accessor:dwValue #(UINT32)成员

	#构造函数
	def initialize
		@dwValue = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwValue = @dwValue
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SClient.new
		s.dwValue = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SClient::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwValue)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#按智能指针传递的结构体
class SPointer
	attr_accessor:dwValue #(UINT32)成员

	#构造函数
	def initialize
		@dwValue = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwValue = @dwValue
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPointer.new
		s.dwValue = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPointer::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwValue)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#结构体父类型示例
class SExBase
	attr_accessor:member1 #(UINT32)成员1
	attr_accessor:vecMember2 #(string数组)成员2

	#构造函数
	def initialize
		@member1 = 0
		@vecMember2 = Array.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SExBase::ETYPE_SEXBASE
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.member1 = @member1
		obj.vecMember2 = @vecMember2
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SExBase.new
		s.member1 = ByteUtil::readUINT32(data)
		s.vecMember2 = ByteUtil::readVecSTRING(data)
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_SExBase::ETYPE_SEXBASE
				s = SExBase::fromStream(data)
			when EType_SExBase::ETYPE_SEXDERIVED1
				s = SExDerived1::fromStream(data)
			when EType_SExBase::ETYPE_SEXDERIVED2
				s = SExDerived2::fromStream(data)
			when EType_SExBase::ETYPE_SEXDESCEND3
				s = SExDescend3::fromStream(data)
			when EType_SExBase::ETYPE_SEXDESCEND4
				s = SExDescend4::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SExBase::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SExBase::superFromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @member1)
		ByteUtil::writeVecSTRING(data, @vecMember2)
	end

	def superToStream(data)
		eType = getClassType()
		ByteUtil::writeUINT8(data, eType)
		toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end

	def self.superVectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.superToStream(data)
		end
	end
end

#结构体子类型1示例
class SExDerived1 < SExBase
	attr_accessor:byMember3 #(UINT16)成员3
	attr_accessor:qwMember4 #(INT64)成员4

	#构造函数
	def initialize
		super()
		@byMember3 = 0
		@qwMember4 = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SExBase::ETYPE_SEXDERIVED1
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.byMember3 = @byMember3
		obj.qwMember4 = @qwMember4
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SExDerived1.new
		base = SExBase::fromStream(data)
		base.copyTo(s)
		s.byMember3 = ByteUtil::readUINT16(data)
		s.qwMember4 = ByteUtil::readINT64(data)
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_SExBase::ETYPE_SEXDERIVED1
				s = SExDerived1::fromStream(data)
			when EType_SExBase::ETYPE_SEXDESCEND3
				s = SExDescend3::fromStream(data)
			when EType_SExBase::ETYPE_SEXDESCEND4
				s = SExDescend4::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SExDerived1::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SExDerived1::superFromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @byMember3)
		ByteUtil::writeINT64(data, @qwMember4)
	end

	def superToStream(data)
		eType = getClassType()
		ByteUtil::writeUINT8(data, eType)
		toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end

	def self.superVectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.superToStream(data)
		end
	end
end

#结构体子类型3示例
class SExDescend3 < SExDerived1
	attr_accessor:base #(类类型：SExBase)成员5
	attr_accessor:s #(类类型：SExDerived1)成员6
	attr_accessor:vecExDerive #(SExDerived1的数组)成员7
	attr_accessor:vecExBase #(SExBase的数组)成员8

	#构造函数
	def initialize
		super()
		@base = SExBase.new
		@s = SExDerived1.new
		@vecExDerive = Array.new
		@vecExBase = Array.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SExBase::ETYPE_SEXDESCEND3
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.base = @base
		obj.s = @s
		obj.vecExDerive = @vecExDerive
		obj.vecExBase = @vecExBase
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SExDescend3.new
		base = SExDerived1::fromStream(data)
		base.copyTo(s)
		s.base = SExBase::superFromStream(data)
		s.s = SExDerived1::superFromStream(data)
		s.vecExDerive = SExDerived1::superVectorFromStream(data)
		s.vecExBase = SExBase::superVectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SExDescend3::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		@base.superToStream(data)
		@s.superToStream(data)
		SExDerived1::superVectorToStream(data, @vecExDerive)
		SExBase::superVectorToStream(data, @vecExBase)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#结构体子类型4示例
class SExDescend4 < SExDerived1
	attr_accessor:wMember5 #(UINT16)成员5
	attr_accessor:qwMember6 #(INT64)成员6
	attr_accessor:vecExDesc #(SExDescend3的数组)成员7

	#构造函数
	def initialize
		super()
		@wMember5 = 0
		@qwMember6 = 0
		@vecExDesc = Array.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SExBase::ETYPE_SEXDESCEND4
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wMember5 = @wMember5
		obj.qwMember6 = @qwMember6
		obj.vecExDesc = @vecExDesc
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SExDescend4.new
		base = SExDerived1::fromStream(data)
		base.copyTo(s)
		s.wMember5 = ByteUtil::readUINT16(data)
		s.qwMember6 = ByteUtil::readINT64(data)
		s.vecExDesc = SExDescend3::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SExDescend4::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wMember5)
		ByteUtil::writeINT64(data, @qwMember6)
		SExDescend3::vectorToStream(data, @vecExDesc)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#结构体子类型2示例
class SExDerived2 < SExBase
	attr_accessor:dMember3 #(double)成员3
	attr_accessor:bMember4 #(bool)成员4

	#构造函数
	def initialize
		super()
		@dMember3 = 0
		@bMember4 = false
	end

	#获取继承类的类型
	def getClassType
		return EType_SExBase::ETYPE_SEXDERIVED2
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.dMember3 = @dMember3
		obj.bMember4 = @bMember4
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SExDerived2.new
		base = SExBase::fromStream(data)
		base.copyTo(s)
		s.dMember3 = ByteUtil::readDOUBLE(data)
		s.bMember4 = ByteUtil::readBOOL(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SExDerived2::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeDOUBLE(data, @dMember3)
		ByteUtil::writeBOOL(data, @bMember4)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[SampleRetFunc2:C->S有返回值的示例函数]的原来的参数组成的结构体
class SOrigParam_SampleRetFunc2
	attr_accessor:qwParam2 #(UINT64)参数2，保存
	attr_accessor:loc_derived #(类类型：SExDerived2)结构体，本地保存

	#构造函数
	def initialize
		@qwParam2 = 0
		@derived = SExDerived2.new
	end
end

#函数[SampleRetFunc2:C->S有返回值的示例函数]的返回的参数组成的结构体
class SRetParam_SampleRetFunc2
	attr_accessor:vecExDescend#(SExDescend3的数组)结构体列表，返回值
	attr_accessor:strRet#(string)字符串，返回值

	#构造函数
	def initialize
		@vecExDescend = Array.new
		@strRet = ''
	end
end

#协议类：通信协议示例
class ExampleBase < ProtocolBase
	#以下为发送函数
	#发送：C->S示例函数1
	def send_SampleFunc1(
		byParam1,  #(INT8)8位有符号整数
		wParam2,  #(INT16)16位有符号整数
		dwParam3,  #(INT32)32位有符号整数
		qwParam4,  #(INT64)64位有符号整数
		byParam5,  #(UINT8)8位无符号整数
		wParam6,  #(UINT16)16位无符号整数
		dwParam7,  #(UINT32)32位无符号整数
		qwParam8,  #(UINT64)64位无符号整数
		bParam9,  #(bool)布尔值
		fParam10,  #(float)单精度浮点数
		dParam11,  #(double)双精度浮点数
		strParam12,  #(string)字符串
		strParam13,  #(string)AS字节数组
		eTest14,  #(枚举类型：EExTest)枚举值
		vecExDesc15 #(SExDescend4的数组)继承结构体列表
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeINT8(data, byParam1)
		ByteUtil::writeINT16(data, wParam2)
		ByteUtil::writeINT32(data, dwParam3)
		ByteUtil::writeINT64(data, qwParam4)
		ByteUtil::writeUINT8(data, byParam5)
		ByteUtil::writeUINT16(data, wParam6)
		ByteUtil::writeUINT32(data, dwParam7)
		ByteUtil::writeUINT64(data, qwParam8)
		ByteUtil::writeBOOL(data, bParam9)
		ByteUtil::writeFLOAT(data, fParam10)
		ByteUtil::writeDOUBLE(data, dParam11)
		ByteUtil::writeSTRING(data, strParam12)
		ByteUtil::writeSTRING(data, strParam13)
		ByteUtil::writeINT16(data, eTest14)
		SExDescend4::vectorToStream(data, vecExDesc15)
		return @svrHandler.sendPacket(data)
	end

	#发送：C->S有返回值的示例函数
	def send_SampleRetFunc2(
		byParam1,  #(UINT8)参数1，不保存
		qwParam2,  #(UINT64)参数2，保存
		loc_derived #(类类型：SExDerived2)结构体，本地保存
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		origParam = SOrigParam_SampleRetFunc2.new
		origParam.qwParam2 = qwParam2
		origParam.loc_derived = loc_derived
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byParam1)
		ByteUtil::writeUINT64(data, qwParam2)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：S->C示例函数1
	def onRecv_SampleFuncAck1(
		byParam1, #(INT8)8位有符号整数
		wParam2, #(INT16)16位有符号整数
		dwParam3, #(INT32)32位有符号整数
		qwParam4, #(INT64)64位有符号整数
		byParam5, #(UINT8)8位无符号整数
		wParam6, #(UINT16)16位无符号整数
		dwParam7, #(UINT32)32位无符号整数
		qwParam8, #(UINT64)64位无符号整数
		bParam9, #(bool)布尔值
		fParam10, #(float)单精度浮点数
		dParam11, #(double)双精度浮点数
		strParam12, #(string)字符串
		strParam13, #(string)AS字节数组
		eTest14, #(枚举类型：EExTest)枚举值
		vecExDesc15 #(SExDescend4的数组)继承结构体列表
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：C->S有返回值的示例函数
	def onReturn_SampleRetFunc2(
		ret, #0为成功，1为失败，2为超时
		origParam, #(类类型：SOrigParam_SampleRetFunc2)原来的参数
		retParam #(类类型：SRetParam_SampleRetFunc2)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：S->C示例函数1
	def _doRecv_SampleFuncAck1(data)
		byParam1 = ByteUtil::readINT8(data)
		wParam2 = ByteUtil::readINT16(data)
		dwParam3 = ByteUtil::readINT32(data)
		qwParam4 = ByteUtil::readINT64(data)
		byParam5 = ByteUtil::readUINT8(data)
		wParam6 = ByteUtil::readUINT16(data)
		dwParam7 = ByteUtil::readUINT32(data)
		qwParam8 = ByteUtil::readUINT64(data)
		bParam9 = ByteUtil::readBOOL(data)
		fParam10 = ByteUtil::readFLOAT(data)
		dParam11 = ByteUtil::readDOUBLE(data)
		strParam12 = ByteUtil::readSTRING(data)
		strParam13 = ByteUtil::readSTRING(data)
		eTest14 = ByteUtil::readINT16(data)
		vecExDesc15 = SExDescend4::vectorFromStream(data)
		return onRecv_SampleFuncAck1(byParam1, wParam2, dwParam3, qwParam4, byParam5, wParam6, dwParam7, qwParam8, bParam9, fParam10, dParam11, strParam12, strParam13, eTest14, vecExDesc15)
	end

#以下为返回处理函数
	#返回处理：C->S有返回值的示例函数
	def _doReturn_SampleRetFunc2(data)
		retParam = SRetParam_SampleRetFunc2.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecExDescend = SExDescend3::vectorFromStream(data) #(SExDescend3的数组)结构体列表，返回值
		strRet = ByteUtil::readSTRING(data) #(string)字符串，返回值
		retParam.vecExDescend = vecExDescend
		retParam.strRet = strRet
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_SampleRetFunc2(ret, origParam, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：C->S有返回值的示例函数
	def _onTimeOut_SampleRetFunc2(sessionID)
		retParam = SRetParam_SampleRetFunc2.new;
		origParam = @sessionMgr.getData(sessionID)
		onReturn_SampleRetFunc2(2, origParam, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 255;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_SampleFuncAck1' #FuncID: 1

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_SampleRetFunc2' #FuncID: 1

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_SampleRetFunc2' #FuncID: 1
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

