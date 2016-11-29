#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    CenterMiscProt.rb
#  Purpose:      CenterServer不好归类的小协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#协议类：CenterServer不好归类的小协议
class CenterMiscProtBase < ProtocolBase
	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 94;
		@recvFuncList = Array.new
	end

	def handleMessage(data)
		return true;
	end
end

