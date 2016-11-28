#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    ActivityIDProt.rb
#  Purpose:      活动ID统一管理
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#活动ID
class EActivityID
	EACTIVITYID_NONE = 0#无
	EQQCOINACTIVITY = 1#汇灵盏
	EOPENACTACTIVITY = 2#七日七天购买礼包
	ESEVENCONSUMEACT = 3#七日消费活动
	EDRAGONBALLACT = 4#七龙珠活动
	EACTIVITYID_MAX = 5#无
end

#协议类：活动ID统一管理
class ActivityIDProtBase < ProtocolBase
	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 97;
		@recvFuncList = Array.new
	end

	def handleMessage(data)
		return true;
	end
end

