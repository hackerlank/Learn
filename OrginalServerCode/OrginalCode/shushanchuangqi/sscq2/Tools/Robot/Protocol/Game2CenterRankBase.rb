#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    Game2CenterRank.rb
#  Purpose:      排行榜相关内部协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './BattleGSBase.rb'
require_relative './RankProtBase.rb'

#协议类：排行榜相关内部协议
class Game2CenterRankBase < ProtocolBase
	#以下为发送函数
	#发送：更新排名信息
	def send_UpdateRankInfo(
		eType,  #(枚类型：RankProt::ERankType)更新类型
		qwInstID,  #(UINT64)唯一ID(玩家ID/帮派ID)
		vecRankInfo #(SRankInfo的数组)玩家信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eType)
		ByteUtil::writeUINT64(data, qwInstID)
		SRankInfo::superVectorToStream(data, vecRankInfo)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新所有待更新的等级信息
	def send_UpdateAllLevelInfo(
		vecRoleID,  #(UINT64数组)玩家ID
		vecRankInfo #(SRankInfo的数组)玩家信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeVecUINT64(data, vecRoleID)
		SRankInfo::superVectorToStream(data, vecRankInfo)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：获取玩家的外观信息
	def onRecv_GetFeature(
		qwRoleID #(UINT64)玩家唯一ID
	)
		raise NotImplementedError
	end
#以下为接收处理函数
	#接收处理：获取玩家的外观信息
	def _doRecv_GetFeature(data)
		qwRoleID = ByteUtil::readUINT64(data)
		return onRecv_GetFeature(qwRoleID)
	end

	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 81;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_GetFeature' #FuncID: 1
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

