#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    ServerCommon.rb
#  Purpose:      服务器通用类型定义
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#下线的类型
class ELeaveType
	ELEAVENONE = 0#无
	ELEAVEAWAY = 1#正常下线
	ELEAVEREPLACE = 2#替换帐号
	ELEAVEJUMP = 3#跳服
	ELEAVEKICK = 4#被踢
	EINDULGEKICK = 5#防沉迷系统已启动，请休息5小时
	EINDULGETIMEKICK = 6#防沉迷离线不足5小时，请休息5小时
	ELEAVEEXCEPT = 7#异常
end

#帐号信息请求类型
class EUserReqType
	EUSERREQNONE = 0#无
	EUSERREQMAIL = 1#邮件
	EUSERREQSHOPMALL = 2#商城
	EUSERREQFRIEND = 3#好友查询
	EUSERREQVIP = 4#赠送VIP
end

#账号ID,Name数据
class SUsrIDNameData
	attr_accessor:qwUsrID #(UINT64)账号ID
	attr_accessor:strName #(string)主英雄名
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:byJob #(UINT8)职业

	#构造函数
	def initialize
		@qwUsrID = 0
		@strName = ''
		@byLevel = 0
		@byJob = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwUsrID = @qwUsrID
		obj.strName = @strName
		obj.byLevel = @byLevel
		obj.byJob = @byJob
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SUsrIDNameData.new
		s.qwUsrID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.byJob = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SUsrIDNameData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwUsrID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT8(data, @byJob)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#协议类：服务器通用类型定义
class ServerCommonBase < ProtocolBase
	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 29;
		@recvFuncList = Array.new
	end

	def handleMessage(data)
		return true;
	end
end

