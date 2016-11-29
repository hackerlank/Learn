#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    GameSvrComm.rb
#  Purpose:      GameServer之间的通信协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#测试结构体
class STest
	attr_accessor:dwParam #(UINT32)成员1

	#构造函数
	def initialize
		@dwParam = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwParam = @dwParam
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STest.new
		s.dwParam = ByteUtil::readUINT32(data)
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
		ByteUtil::writeUINT32(data, @dwParam)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[TestRetFuncReq:测试返回函数请求]的原来的参数组成的结构体
class SOrigParam_TestRetFuncReq
	attr_accessor:rTest #(类类型：STest)参数1

	#构造函数
	def initialize
		@rTest = STest.new
	end
end

#函数[TestRetFuncReq:测试返回函数请求]的返回的参数组成的结构体
class SRetParam_TestRetFuncReq
	attr_accessor:dwRetParam#(UINT32)返回参数1

	#构造函数
	def initialize
		@dwRetParam = 0
	end
end

#协议类：GameServer之间的通信协议
class GameSvrCommBase < ProtocolBase
	#以下为发送函数
	#发送：测试函数请求
	def send_TestFuncReq(
		rTest #(类类型：STest)参数1
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		rTest.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：测试返回函数请求
	def send_TestRetFuncReq(
		rTest #(类类型：STest)参数1
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		origParam = SOrigParam_TestRetFuncReq.new
		origParam.rTest = rTest
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		rTest.toStream(data)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：测试函数返回
	def onRecv_TestFuncAck(
		rTest #(类类型：STest)参数1
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：测试返回函数请求
	def onReturn_TestRetFuncReq(
		ret, #0为成功，1为失败，2为超时
		origParam, #(类类型：SOrigParam_TestRetFuncReq)原来的参数
		retParam #(类类型：SRetParam_TestRetFuncReq)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：测试函数返回
	def _doRecv_TestFuncAck(data)
		rTest = STest::fromStream(data)
		return onRecv_TestFuncAck(rTest)
	end

#以下为返回处理函数
	#返回处理：测试返回函数请求
	def _doReturn_TestRetFuncReq(data)
		retParam = SRetParam_TestRetFuncReq.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwRetParam = ByteUtil::readUINT32(data) #(UINT32)返回参数1
		retParam.dwRetParam = dwRetParam
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_TestRetFuncReq(ret, origParam, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：测试返回函数请求
	def _onTimeOut_TestRetFuncReq(sessionID)
		retParam = SRetParam_TestRetFuncReq.new;
		origParam = @sessionMgr.getData(sessionID)
		onReturn_TestRetFuncReq(2, origParam, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 67;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_TestFuncAck' #FuncID: 1

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_TestRetFuncReq' #FuncID: 1

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_TestRetFuncReq' #FuncID: 1
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

