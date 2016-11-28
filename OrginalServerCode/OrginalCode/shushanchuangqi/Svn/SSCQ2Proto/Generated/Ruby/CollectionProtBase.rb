#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    CollectionProt.rb
#  Purpose:      收藏协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#EDataType:eTypeCollectionInfo
class SCollectionInfo
	attr_accessor:qwRoleID #(UINT64)角色ID
	attr_accessor:wCollectionID #(UINT16)收藏ID
	attr_accessor:dwCount #(UINT32)0是否完成
	attr_accessor:dwProcess #(UINT32)当前进度(持续型事件记录数据)
	attr_accessor:dwFinishTime #(UINT32)完成时间

	#构造函数
	def initialize
		@qwRoleID = 0
		@wCollectionID = 0
		@dwCount = 0
		@dwProcess = 0
		@dwFinishTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wCollectionID = @wCollectionID
		obj.dwCount = @dwCount
		obj.dwProcess = @dwProcess
		obj.dwFinishTime = @dwFinishTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SCollectionInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wCollectionID = ByteUtil::readUINT16(data)
		s.dwCount = ByteUtil::readUINT32(data)
		s.dwProcess = ByteUtil::readUINT32(data)
		s.dwFinishTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SCollectionInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wCollectionID)
		ByteUtil::writeUINT32(data, @dwCount)
		ByteUtil::writeUINT32(data, @dwProcess)
		ByteUtil::writeUINT32(data, @dwFinishTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GeCollectionInfo:获取收藏信息]的返回的参数组成的结构体
class SRetParam_GeCollectionInfo
	attr_accessor:vecCollectionInfo#(SCollectionInfo的数组)收藏榜信息
	attr_accessor:wLevel#(UINT16)收藏等级
	attr_accessor:dwAP#(UINT32)收藏点

	#构造函数
	def initialize
		@vecCollectionInfo = Array.new
		@wLevel = 0
		@dwAP = 0
	end
end

#协议类：收藏协议
class CollectionProtBase < ProtocolBase
	#以下为发送函数
	#发送：获取收藏信息
	def send_GeCollectionInfo(
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
	#接收：收藏点通知
	def onRecv_APNotify(
		dwAP #(UINT32)收藏点
	)
		raise NotImplementedError
	end
	#接收：收藏等级通知
	def onRecv_CollectionLevelNotify(
		wLevel #(UINT16)收藏等级
	)
		raise NotImplementedError
	end
	#接收：收藏等级通知
	def onRecv_CollectionInfoNotify(
		oCollectionInfo #(类类型：SCollectionInfo)收藏信息
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取收藏信息
	def onReturn_GeCollectionInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GeCollectionInfo)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：收藏点通知
	def _doRecv_APNotify(data)
		dwAP = ByteUtil::readUINT32(data)
		return onRecv_APNotify(dwAP)
	end

	#接收处理：收藏等级通知
	def _doRecv_CollectionLevelNotify(data)
		wLevel = ByteUtil::readUINT16(data)
		return onRecv_CollectionLevelNotify(wLevel)
	end

	#接收处理：收藏等级通知
	def _doRecv_CollectionInfoNotify(data)
		oCollectionInfo = SCollectionInfo::fromStream(data)
		return onRecv_CollectionInfoNotify(oCollectionInfo)
	end

#以下为返回处理函数
	#返回处理：获取收藏信息
	def _doReturn_GeCollectionInfo(data)
		retParam = SRetParam_GeCollectionInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecCollectionInfo = SCollectionInfo::vectorFromStream(data) #(SCollectionInfo的数组)收藏榜信息
		wLevel = ByteUtil::readUINT16(data) #(UINT16)收藏等级
		dwAP = ByteUtil::readUINT32(data) #(UINT32)收藏点
		retParam.vecCollectionInfo = vecCollectionInfo
		retParam.wLevel = wLevel
		retParam.dwAP = dwAP
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GeCollectionInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取收藏信息
	def _onTimeOut_GeCollectionInfo(sessionID)
		retParam = SRetParam_GeCollectionInfo.new;
		onReturn_GeCollectionInfo(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 78;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_APNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_CollectionLevelNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_CollectionInfoNotify' #FuncID: 3

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GeCollectionInfo' #FuncID: 1

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GeCollectionInfo' #FuncID: 1
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

