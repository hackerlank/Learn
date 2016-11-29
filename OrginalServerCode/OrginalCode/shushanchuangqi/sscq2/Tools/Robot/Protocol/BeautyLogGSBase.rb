#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    BeautyLogGS.rb
#  Purpose:      美女log
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#美女log
class EBeautyLog
	EBEAUTYLOG_SUCESS = 0#成功
	EBEAUTYLOG_ERROR = 1#失败
end

#美女log信息
class SBeautyLog
	attr_accessor:qwUserID #(UINT64)uid
	attr_accessor:strRoleName #(string)角色名
	attr_accessor:byColor #(UINT8)角色颜色
	attr_accessor:wItemID #(UINT16)物品id
	attr_accessor:dwCount #(UINT32)物品数量

	#构造函数
	def initialize
		@qwUserID = 0
		@strRoleName = ''
		@byColor = 0
		@wItemID = 0
		@dwCount = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwUserID = @qwUserID
		obj.strRoleName = @strRoleName
		obj.byColor = @byColor
		obj.wItemID = @wItemID
		obj.dwCount = @dwCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBeautyLog.new
		s.qwUserID = ByteUtil::readUINT64(data)
		s.strRoleName = ByteUtil::readSTRING(data)
		s.byColor = ByteUtil::readUINT8(data)
		s.wItemID = ByteUtil::readUINT16(data)
		s.dwCount = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBeautyLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeSTRING(data, @strRoleName)
		ByteUtil::writeUINT8(data, @byColor)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeUINT32(data, @dwCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetBeautyLog:获取美女log信息]的返回的参数组成的结构体
class SRetParam_GetBeautyLog
	attr_accessor:vecBeautyLog#(SBeautyLog的数组)美女log信息

	#构造函数
	def initialize
		@vecBeautyLog = Array.new
	end
end

#协议类：美女log
class BeautyLogGSBase < ProtocolBase
	#以下为发送函数
	#发送：获取美女log信息
	def send_GetBeautyLog(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：美女log添加
	def onRecv_AddBeautyLogNotify(
		oAddBeautyLog #(类类型：SBeautyLog)美女log信息
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取美女log信息
	def onReturn_GetBeautyLog(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetBeautyLog)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：美女log添加
	def _doRecv_AddBeautyLogNotify(data)
		oAddBeautyLog = SBeautyLog::fromStream(data)
		return onRecv_AddBeautyLogNotify(oAddBeautyLog)
	end

#以下为返回处理函数
	#返回处理：获取美女log信息
	def _doReturn_GetBeautyLog(data)
		retParam = SRetParam_GetBeautyLog.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecBeautyLog = SBeautyLog::vectorFromStream(data) #(SBeautyLog的数组)美女log信息
		retParam.vecBeautyLog = vecBeautyLog
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetBeautyLog(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取美女log信息
	def _onTimeOut_GetBeautyLog(sessionID)
		retParam = SRetParam_GetBeautyLog.new;
		onReturn_GetBeautyLog(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 133;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_AddBeautyLogNotify' #FuncID: 1

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetBeautyLog' #FuncID: 1

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetBeautyLog' #FuncID: 1
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

