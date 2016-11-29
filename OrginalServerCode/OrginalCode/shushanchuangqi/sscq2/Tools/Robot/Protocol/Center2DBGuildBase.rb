#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    Center2DBGuild.rb
#  Purpose:      CenterServer到DBServer有关帮派的通信协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './GuildProtBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#帮派神像供奉人数信息
class SGSWorshipInfo
	attr_accessor:qwGuildID #(UINT64)帮派ID
	attr_accessor:byWorshipCount #(UINT8)供奉人数
	attr_accessor:vecMemberID #(UINT64数组)帮派成员ID

	#构造函数
	def initialize
		@qwGuildID = 0
		@byWorshipCount = 0
		@vecMemberID = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwGuildID = @qwGuildID
		obj.byWorshipCount = @byWorshipCount
		obj.vecMemberID = @vecMemberID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGSWorshipInfo.new
		s.qwGuildID = ByteUtil::readUINT64(data)
		s.byWorshipCount = ByteUtil::readUINT8(data)
		s.vecMemberID = ByteUtil::readVecUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGSWorshipInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwGuildID)
		ByteUtil::writeUINT8(data, @byWorshipCount)
		ByteUtil::writeVecUINT64(data, @vecMemberID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#协议类：CenterServer到DBServer有关帮派的通信协议
class Center2DBGuildBase < ProtocolBase
	#以下为发送函数
	#发送：帮派数据更新
	def send_GuildDataUpdate(
		qwGuildID,  #(UINT64)帮派ID
		eDataType,  #(枚类型：GuildProt::EGuildDataType)更新数据类型
		eUpdateType,  #(枚类型：ProtoCommon::EDataChange)更新方式，增加，删除，修改
		strData #(string)更新数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwGuildID)
		ByteUtil::writeUINT8(data, eDataType)
		ByteUtil::writeUINT8(data, eUpdateType)
		ByteUtil::writeSTRING(data, strData)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派公共信息更新
	def send_GuildPubDataUpdate(
		qwGuildID,  #(UINT64)帮派ID
		eDataType,  #(枚类型：GuildProt::EGuildPubDataType)更新数据类型
		eUpdateType,  #(枚类型：ProtoCommon::EDataChange)更新方式，增加，删除，修改
		strData #(string)更新数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwGuildID)
		ByteUtil::writeUINT8(data, eDataType)
		ByteUtil::writeUINT8(data, eUpdateType)
		ByteUtil::writeSTRING(data, strData)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取帮派公共信息（启动预加载调用）
	def send_GetGuildPubInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取所有帮派信息
	def send_GetAllGuildInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派登录（通常是涉及到有关帮派的操作需要加载登录）
	def send_GuildLogin(
		qwGuildID #(UINT64)帮派ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwGuildID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家登录，拉取可能存在的帮派信息
	def send_GuildUserLogin(
		qwRoleID #(UINT64)玩家ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派神像奖励结算
	def send_GuildStatueReward(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求所有羲和神车信息
	def send_GetAllGuildXihe(
		dwPageSize #(UINT32)发送条数
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, dwPageSize)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新玩家羲和神车信息
	def send_UpdateGuildXihe(
		oGuildXihe,  #(类类型：GuildProt::SGuildXihe)玩家羲和神车的数据
		eUpdateType #(枚类型：ProtoCommon::EDataChange)更新方式，增加，删除，修改
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		oGuildXihe.toStream(data)
		ByteUtil::writeUINT8(data, eUpdateType)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取帮派战兑换物品
	def send_GetAllGuildExchangedItem(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新帮派战兑换物品信息
	def send_UpdateGuildExchangedItem(
		sGuildExchangedItem,  #(类类型：GuildProt::SGuildExchangedItem)帮派战兑换物品信息
		eUpdateType #(枚类型：ProtoCommon::EDataChange)更新方式，增加，删除，修改
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		sGuildExchangedItem.toStream(data)
		ByteUtil::writeUINT8(data, eUpdateType)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：帮派公共信息加载返回
	def onRecv_GuildPubInfoNotify(
		dwCurSize, #(UINT32)已发送条数
		dwTotalSize, #(UINT32)总条数
		vecPubGuildAllInfo #(SPubGuildAllInfo的数组)更新信息
	)
		raise NotImplementedError
	end
	#接收：帮派
	def onRecv_AllGuildLoginNotify(
		dwCurSize, #(UINT32)已发送条数
		dwTotalSize, #(UINT32)总条数
		vecData #(SDBGuildAllInfo的数组)帮派具体数据
	)
		raise NotImplementedError
	end
	#接收：帮派
	def onRecv_GuildLoginNotify(
		qwGuildID, #(UINT64)帮派ID
		sData #(类类型：GuildProt::SDBGuildAllInfo)帮派具体数据
	)
		raise NotImplementedError
	end
	#接收：帮派用户登录返回
	def onRecv_GuildUserLoginNotify(
		qwRoleID, #(UINT64)玩家ID
		vecGuildUserInfo #(SDBGuildUserInfo的数组)用户信息，数量为0表示完全没有在或者加入过帮派
	)
		raise NotImplementedError
	end
	#接收：返回请求帮派供奉人数
	def onRecv_SendAllGuildStatueWorshipCount(
		vecGSWorshiInfo #(SGSWorshipInfo的数组)供奉人数信息
	)
		raise NotImplementedError
	end
	#接收：返回所有羲和神车信息
	def onRecv_SendAllGuildXihe(
		dwPageSize, #(UINT32)已发送条数
		dwTotalSize, #(UINT32)总条数
		vecSendData #(SGuildXihe的数组)更新信息
	)
		raise NotImplementedError
	end
	#接收：所有帮派兑换物品加载返回
	def onRecv_SendAllGuildExchangedItem(
		vecGuildExchangedItem #(SGuildExchangedItem的数组)派兑换物品信息
	)
		raise NotImplementedError
	end
#以下为接收处理函数
	#接收处理：帮派公共信息加载返回
	def _doRecv_GuildPubInfoNotify(data)
		dwCurSize = ByteUtil::readUINT32(data)
		dwTotalSize = ByteUtil::readUINT32(data)
		vecPubGuildAllInfo = SPubGuildAllInfo::vectorFromStream(data)
		return onRecv_GuildPubInfoNotify(dwCurSize, dwTotalSize, vecPubGuildAllInfo)
	end

	#接收处理：帮派
	def _doRecv_AllGuildLoginNotify(data)
		dwCurSize = ByteUtil::readUINT32(data)
		dwTotalSize = ByteUtil::readUINT32(data)
		vecData = SDBGuildAllInfo::vectorFromStream(data)
		return onRecv_AllGuildLoginNotify(dwCurSize, dwTotalSize, vecData)
	end

	#接收处理：帮派
	def _doRecv_GuildLoginNotify(data)
		qwGuildID = ByteUtil::readUINT64(data)
		sData = SDBGuildAllInfo::fromStream(data)
		return onRecv_GuildLoginNotify(qwGuildID, sData)
	end

	#接收处理：帮派用户登录返回
	def _doRecv_GuildUserLoginNotify(data)
		qwRoleID = ByteUtil::readUINT64(data)
		vecGuildUserInfo = SDBGuildUserInfo::vectorFromStream(data)
		return onRecv_GuildUserLoginNotify(qwRoleID, vecGuildUserInfo)
	end

	#接收处理：返回请求帮派供奉人数
	def _doRecv_SendAllGuildStatueWorshipCount(data)
		vecGSWorshiInfo = SGSWorshipInfo::vectorFromStream(data)
		return onRecv_SendAllGuildStatueWorshipCount(vecGSWorshiInfo)
	end

	#接收处理：返回所有羲和神车信息
	def _doRecv_SendAllGuildXihe(data)
		dwPageSize = ByteUtil::readUINT32(data)
		dwTotalSize = ByteUtil::readUINT32(data)
		vecSendData = SGuildXihe::vectorFromStream(data)
		return onRecv_SendAllGuildXihe(dwPageSize, dwTotalSize, vecSendData)
	end

	#接收处理：所有帮派兑换物品加载返回
	def _doRecv_SendAllGuildExchangedItem(data)
		vecGuildExchangedItem = SGuildExchangedItem::vectorFromStream(data)
		return onRecv_SendAllGuildExchangedItem(vecGuildExchangedItem)
	end

	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 32;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_GuildPubInfoNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_AllGuildLoginNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_GuildLoginNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_GuildUserLoginNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_SendAllGuildStatueWorshipCount' #FuncID: 5
		@recvFuncList[5] = '_doRecv_SendAllGuildXihe' #FuncID: 6
		@recvFuncList[6] = '_doRecv_SendAllGuildExchangedItem' #FuncID: 7
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

