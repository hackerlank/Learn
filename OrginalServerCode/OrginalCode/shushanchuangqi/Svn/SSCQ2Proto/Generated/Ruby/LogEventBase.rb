#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    LogEvent.rb
#  Purpose:      日志协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './LogDataDefineBase.rb'

#以下为类型定义

#日志的类型
class ELogType
	ELOGNONE = 0#无
	ELOGSYSTEM = 1#系统日志
	ELOGITEM = 2#道具日志
	ELOGMONEY = 3#金钱日志
	ELOGLOGINOUT = 4#登陆登出日志
	ELOGMALL = 5#商城日志
	ELOGLEVELUP = 6#升级日志
	ELOGRECRUIT = 7#招募日志
	ELOGPROP = 8#属性日志
	ELOGSKILL = 9#技能日志
	ELOGTASK = 10#任务日志
	ELOGBATTLE = 11#战斗日志
	ELOGEQUIPREPLACE = 12#装备替换日志
	ELOGEQUIPOPEATOR = 13#装备操作日志
	ELOGALCHEMY = 14#圣物操作日志
	ELOGDUNGEON = 15#副本日志
	ELOGACTIVITY = 16#活动日志
	ELOGPVPRANK = 17#PVP排行
	ELOGBUILDING = 18#建筑日志
	ELOGGUILD = 19#公会日志
	ELOGFAMILY = 20#家族日志
	ELOGVIP = 21#VIP日志
	ELOGUDPLOG = 22#UDPLog日志
	ELOGMAIL = 23#邮件日志
	ELOGACTIVE = 24#活跃度日志
	ELOGEND = 25
end

#协议类：日志协议
class LogEventBase < ProtocolBase
	#以下为发送函数
	#发送：心跳
	def send_KeepAlive(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：写日志请求
	def send_WriteLogReq(
		eLogType,  #(枚举类型：ELogType)日志类型
		strLog #(string)日志信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eLogType)
		ByteUtil::writeSTRING(data, strLog)
		return @svrHandler.sendPacket(data)
	end

	#发送：写日志请求
	def send_WriteLogToDB(
		vecLog #(LogDataBase的数组)日志数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		LogDataBase::superVectorToStream(data, vecLog)
		return @svrHandler.sendPacket(data)
	end

	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 50;
		@recvFuncList = Array.new
	end

	def handleMessage(data)
		return true;
	end
end

