#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    ProtoVersion.rb
#  Purpose:      协议版本号
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#协议版本
class EProtoVer
	EPROTOVERSION = 14080801#版本号，年2位(14),月2位(07),日2位，序号2位
end

#协议类：协议版本号
class ProtoVersionBase < ProtocolBase
	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 259;
		@recvFuncList = Array.new
	end

	def handleMessage(data)
		return true;
	end
end

