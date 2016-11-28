#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    Game2DBComm.rb
#  Purpose:      GameServer到DBServer的通信协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './MallProtBase.rb'
require_relative './ProtoCommonBase.rb'
require_relative './RoleInfoDefineBase.rb'
require_relative './ServerCommonBase.rb'
require_relative './ShengLingProtBase.rb'

#以下为类型定义

#保存请求的类型
class ESaveType
	ESAVENONE = 0#无
	ESAVEAWAY = 1#暂时离开
	ESAVEOFF = 2#下线离开
	ESAVEJUMP = 3#跳线
	ESAVEKICK = 4#被踢
	ESAVEEXCEPT = 5#异常
	ESAVEDATA = 6#定时保存
	ESAVETOCROSS = 7#跳到跨服服务器
	ESAVEFROMCROSS = 8#从跨服服务器跳回
end

#进入GameServer的类型
class EEnterType
	EENTERNONE = 0#无
	EENTERLOGIN = 1#正常上线
	EENTERJUMP = 2#跳线
	EENTERTOCROSS = 3#跳到跨服服务器
	EENTERFROMCROSS = 4#从跨服服务器跳回
end

#EDataType:eTypeWorldBossInfo
class SWBossDBInfo
	attr_accessor:wBossID #(UINT16)BOSSID
	attr_accessor:dwLast #(UINT32)次被击杀所用时长，单位秒
	attr_accessor:dwHP #(UINT32)上次最大血量
	attr_accessor:dwAtk #(UINT32)上次物理攻击力
	attr_accessor:dwMAtk #(UINT32)上次魔法攻击力
	attr_accessor:dwLastEndTime #(UINT32)上次结束时间

	#构造函数
	def initialize
		@wBossID = 0
		@dwLast = 0
		@dwHP = 0
		@dwAtk = 0
		@dwMAtk = 0
		@dwLastEndTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wBossID = @wBossID
		obj.dwLast = @dwLast
		obj.dwHP = @dwHP
		obj.dwAtk = @dwAtk
		obj.dwMAtk = @dwMAtk
		obj.dwLastEndTime = @dwLastEndTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SWBossDBInfo.new
		s.wBossID = ByteUtil::readUINT16(data)
		s.dwLast = ByteUtil::readUINT32(data)
		s.dwHP = ByteUtil::readUINT32(data)
		s.dwAtk = ByteUtil::readUINT32(data)
		s.dwMAtk = ByteUtil::readUINT32(data)
		s.dwLastEndTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SWBossDBInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wBossID)
		ByteUtil::writeUINT32(data, @dwLast)
		ByteUtil::writeUINT32(data, @dwHP)
		ByteUtil::writeUINT32(data, @dwAtk)
		ByteUtil::writeUINT32(data, @dwMAtk)
		ByteUtil::writeUINT32(data, @dwLastEndTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#数据库加载的新帮派战历史信息
class SDBGuildNewBattleHistoryInfo
	attr_accessor:byMountainType #(UINT8)灵山类型
	attr_accessor:qwGuildID #(UINT64)当前占领帮派ID
	attr_accessor:strGuildName #(string)当前占领帮派名称
	attr_accessor:strGuildOwnerName #(string)当前占领帮派帮主名称
	attr_accessor:dwTime #(UINT32)占领时间

	#构造函数
	def initialize
		@byMountainType = 0
		@qwGuildID = 0
		@strGuildName = ''
		@strGuildOwnerName = ''
		@dwTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byMountainType = @byMountainType
		obj.qwGuildID = @qwGuildID
		obj.strGuildName = @strGuildName
		obj.strGuildOwnerName = @strGuildOwnerName
		obj.dwTime = @dwTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDBGuildNewBattleHistoryInfo.new
		s.byMountainType = ByteUtil::readUINT8(data)
		s.qwGuildID = ByteUtil::readUINT64(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		s.strGuildOwnerName = ByteUtil::readSTRING(data)
		s.dwTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDBGuildNewBattleHistoryInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byMountainType)
		ByteUtil::writeUINT64(data, @qwGuildID)
		ByteUtil::writeSTRING(data, @strGuildName)
		ByteUtil::writeSTRING(data, @strGuildOwnerName)
		ByteUtil::writeUINT32(data, @dwTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[SaveUserDataReq:请求保存账号数据]的原来的参数组成的结构体
class SOrigParam_SaveUserDataReq
	attr_accessor:qwUsrID #(UINT64)账号ID
	attr_accessor:eSaveType #(枚举类型：ESaveType)保存类型

	#构造函数
	def initialize
		@qwUsrID = 0
		@eSaveType = 0
	end
end

#函数[SaveOffLineDgnInfo:副本结束时候，玩家不在gameserver的数据保存]的原来的参数组成的结构体
class SOrigParam_SaveOffLineDgnInfo
	attr_accessor:qwUsrID #(UINT64)账号ID
	attr_accessor:dwDgnType #(UINT32)副本类型

	#构造函数
	def initialize
		@qwUsrID = 0
		@dwDgnType = 0
	end
end

#函数[LoadOffLineUserData:加载离线玩家数据]的返回的参数组成的结构体
class SRetParam_LoadOffLineUserData
	attr_accessor:byRet#(UINT8)0表示成功
	attr_accessor:RoleData#(类类型：RoleInfoDefine::RoleDataInfo)玩家数据

	#构造函数
	def initialize
		@byRet = 0
		@RoleData = RoleDataInfo.new
	end
end

#函数[LoadWorldBossInfo:加载世界BOSS信息请求]的返回的参数组成的结构体
class SRetParam_LoadWorldBossInfo
	attr_accessor:vecWorldBossInfo#(SWBossDBInfo的数组)世界BOSS信息

	#构造函数
	def initialize
		@vecWorldBossInfo = Array.new
	end
end

#函数[GetUserIDFromName:根据名字获取ID请求]的返回的参数组成的结构体
class SRetParam_GetUserIDFromName
	attr_accessor:qwUsrID#(UINT64)用户ID

	#构造函数
	def initialize
		@qwUsrID = 0
	end
end

#函数[GetBattleReport:获得玩家战报信息]的返回的参数组成的结构体
class SRetParam_GetBattleReport
	attr_accessor:vecReport#(SBattleRePort的数组)返回的数据

	#构造函数
	def initialize
		@vecReport = Array.new
	end
end

#函数[AddBattleReport:增加玩家战报信息]的返回的参数组成的结构体
class SRetParam_AddBattleReport
	attr_accessor:vecBattleID#(UINT64数组)删除的战报

	#构造函数
	def initialize
		@vecBattleID = Array.new
	end
end

#函数[LoadMallDiscount:加载商城限购信息]的返回的参数组成的结构体
class SRetParam_LoadMallDiscount
	attr_accessor:vecDisItems#(SDiscount的数组)限购道具信息

	#构造函数
	def initialize
		@vecDisItems = Array.new
	end
end

#协议类：GameServer到DBServer的通信协议
class Game2DBCommBase < ProtocolBase
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

	#发送：DBServer状态请求
	def send_GetStatus(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新玩家充值仙石信息
	def send_UpdateRecharge(
		oRecharge #(类类型：RoleInfoDefine::SRecharge)充值仙石的数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		oRecharge.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：一行数据更新
	def send_RoleDataUpdate(
		qwRoleId,  #(UINT64)角色Id
		eDataType,  #(枚类型：RoleInfoDefine::EDataType)更新数据块
		eUpdateType,  #(枚类型：ProtoCommon::EDataChange)更新类型，增加，删除，修改
		strData #(string)更新数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleId)
		ByteUtil::writeUINT8(data, eDataType)
		ByteUtil::writeUINT8(data, eUpdateType)
		ByteUtil::writeSTRING(data, strData)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求保存账号数据
	def send_SaveUserDataReq(
		qwUsrID,  #(UINT64)账号ID
		eSaveType,  #(枚举类型：ESaveType)保存类型
		vecPlatformParam #(SPlatformParam的数组)平台参数列表
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		origParam = SOrigParam_SaveUserDataReq.new
		origParam.qwUsrID = qwUsrID
		origParam.eSaveType = eSaveType
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeUINT8(data, eSaveType)
		SPlatformParam::vectorToStream(data, vecPlatformParam)
		return @svrHandler.sendPacket(data)
	end

	#发送：副本结束时候，玩家不在gameserver的数据保存
	def send_SaveOffLineDgnInfo(
		qwUsrID,  #(UINT64)账号ID
		dwDgnType,  #(UINT32)副本类型
		byIsFail #(UINT8)0:表示成功保存，1：表示失败保存
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		origParam = SOrigParam_SaveOffLineDgnInfo.new
		origParam.qwUsrID = qwUsrID
		origParam.dwDgnType = dwDgnType
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeUINT32(data, dwDgnType)
		ByteUtil::writeUINT8(data, byIsFail)
		return @svrHandler.sendPacket(data)
	end

	#发送：加载离线玩家数据
	def send_LoadOffLineUserData(
		qwUsrID #(UINT64)账号ID
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwUsrID)
		return @svrHandler.sendPacket(data)
	end

	#发送：加载世界BOSS信息请求
	def send_LoadWorldBossInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：存储世界BOSS信息
	def send_SaveWorldBossInfo(
		sWorldBossInfo #(类类型：SWBossDBInfo)世界BOSS信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		sWorldBossInfo.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：根据名字获取ID请求
	def send_GetUserIDFromName(
		strName #(string)主角色名称
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeSTRING(data, strName)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得玩家战报信息
	def send_GetBattleReport(
		qwRoleID,  #(UINT64)玩家的ID
		eBattleType,  #(枚类型：RoleInfoDefine::EBattleReportType)战斗类型
		eAction #(枚类型：RoleInfoDefine::EBattleActionType)战斗的发起
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT8(data, eBattleType)
		ByteUtil::writeUINT8(data, eAction)
		return @svrHandler.sendPacket(data)
	end

	#发送：增加玩家战报信息
	def send_AddBattleReport(
		qwRoleID,  #(UINT64)
		sReport,  #(类类型：RoleInfoDefine::SBattleRePort)战斗数据
		byNum #(UINT8)超过byNum，返回删除的旧的战报,0表示不删除
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		sReport.toStream(data)
		ByteUtil::writeUINT8(data, byNum)
		return @svrHandler.sendPacket(data)
	end

	#发送：增加离线事件
	def send_AddOffLineEvent(
		vecRoleID,  #(UINT64数组)
		sEventData #(类类型：RoleInfoDefine::SEventOffLine)事件类型
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 13
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeVecUINT64(data, vecRoleID)
		sEventData.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：删除离线事件
	def send_DelOffLineEvent(
		qwRoleID,  #(UINT64)
		vecEventType #(SEventOffLine的数组)事件类型
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 14
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		SEventOffLine::vectorToStream(data, vecEventType)
		return @svrHandler.sendPacket(data)
	end

	#发送：加载商城限购信息
	def send_LoadMallDiscount(
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 15
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新商城限购
	def send_UpdateMallDiscount(
		eUpdateType,  #(枚类型：ProtoCommon::EDataChange)更新类型，增加，删除，修改
		vecDisItems #(SDiscount的数组)限购道具
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 16
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eUpdateType)
		SDiscount::vectorToStream(data, vecDisItems)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取新帮派战历史
	def send_GetNewGuildBattleHistory(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 17
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：新增新帮派战历史
	def send_AddNewGuildBattleHistory(
		vecInfo #(SDBGuildNewBattleHistoryInfo的数组)更新信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 18
		ByteUtil::writeINT8(data, funcID)
		SDBGuildNewBattleHistoryInfo::vectorToStream(data, vecInfo)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：帐号协议代理发送请求
	def onRecv_UserPackageProxy(
		qwUsrID, #(UINT64)帐号ID
		dwGateID, #(UINT32)所在网关服务器ID
		vecPackage #(string数组)协议包列表
	)
		raise NotImplementedError
	end
	#接收：DB向GameSever推送角色信息/
	def onRecv_UserLoginNtf(
		eEnterType, #(枚举类型：EEnterType)进入的类型
		vecPlatformParam, #(SPlatformParam的数组)平台参数列表
		vecEnterString, #(string数组)平台相关参数
		dwGateId, #(UINT32)网关Id
		qwUserId, #(UINT64)用户Id
		RoleData #(类类型：RoleInfoDefine::RoleDataInfo)玩家数据
	)
		raise NotImplementedError
	end
	#接收：账号重新进入通知
	def onRecv_UserReEnterNotify(
		qwUsrID, #(UINT64)账号ID
		dwGateID, #(UINT32)所在网关服务器ID
		vecPlatformParam, #(SPlatformParam的数组)平台参数列表
		vecEnterString #(string数组)平台相关参数
	)
		raise NotImplementedError
	end
	#接收：账号退出DBServer通知
	def onRecv_UserLogoutNtf(
		qwUsrID, #(UINT64)账号ID
		eLeaveType #(枚类型：ServerCommon::ELeaveType)下线类型
	)
		raise NotImplementedError
	end
	#接收：离线事件通知
	def onRecv_NewOffEventNotice(
		qwUsrID, #(UINT64)账号ID
		sEventData #(类类型：RoleInfoDefine::SEventOffLine)事件类型
	)
		raise NotImplementedError
	end
	#接收：新帮派战历史记录获取返回
	def onRecv_NewGuildBattleHistoryNotify(
		dwCurSize, #(UINT32)已发送条数
		dwTotalSize, #(UINT32)总条数
		vecInfo #(SDBGuildNewBattleHistoryInfo的数组)更新信息
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：DBServer状态请求
	def onReturn_GetStatus(
		ret #0为成功，1为失败，2为超时
	)
	end

	#返回：请求保存账号数据
	def onReturn_SaveUserDataReq(
		ret, #0为成功，1为失败，2为超时
		origParam #(类类型：SOrigParam_SaveUserDataReq)原来的参数
	)
	end

	#返回：副本结束时候，玩家不在gameserver的数据保存
	def onReturn_SaveOffLineDgnInfo(
		ret, #0为成功，1为失败，2为超时
		origParam #(类类型：SOrigParam_SaveOffLineDgnInfo)原来的参数
	)
	end

	#返回：加载离线玩家数据
	def onReturn_LoadOffLineUserData(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LoadOffLineUserData)返回的参数
	)
	end

	#返回：加载世界BOSS信息请求
	def onReturn_LoadWorldBossInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LoadWorldBossInfo)返回的参数
	)
	end

	#返回：根据名字获取ID请求
	def onReturn_GetUserIDFromName(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetUserIDFromName)返回的参数
	)
	end

	#返回：获得玩家战报信息
	def onReturn_GetBattleReport(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetBattleReport)返回的参数
	)
	end

	#返回：增加玩家战报信息
	def onReturn_AddBattleReport(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_AddBattleReport)返回的参数
	)
	end

	#返回：加载商城限购信息
	def onReturn_LoadMallDiscount(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LoadMallDiscount)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：帐号协议代理发送请求
	def _doRecv_UserPackageProxy(data)
		qwUsrID = ByteUtil::readUINT64(data)
		dwGateID = ByteUtil::readUINT32(data)
		vecPackage = ByteUtil::readVecSTRING(data)
		return onRecv_UserPackageProxy(qwUsrID, dwGateID, vecPackage)
	end

	#接收处理：DB向GameSever推送角色信息/
	def _doRecv_UserLoginNtf(data)
		eEnterType = ByteUtil::readUINT8(data)
		vecPlatformParam = SPlatformParam::vectorFromStream(data)
		vecEnterString = ByteUtil::readVecSTRING(data)
		dwGateId = ByteUtil::readUINT32(data)
		qwUserId = ByteUtil::readUINT64(data)
		RoleData = RoleDataInfo::fromStream(data)
		return onRecv_UserLoginNtf(eEnterType, vecPlatformParam, vecEnterString, dwGateId, qwUserId, RoleData)
	end

	#接收处理：账号重新进入通知
	def _doRecv_UserReEnterNotify(data)
		qwUsrID = ByteUtil::readUINT64(data)
		dwGateID = ByteUtil::readUINT32(data)
		vecPlatformParam = SPlatformParam::vectorFromStream(data)
		vecEnterString = ByteUtil::readVecSTRING(data)
		return onRecv_UserReEnterNotify(qwUsrID, dwGateID, vecPlatformParam, vecEnterString)
	end

	#接收处理：账号退出DBServer通知
	def _doRecv_UserLogoutNtf(data)
		qwUsrID = ByteUtil::readUINT64(data)
		eLeaveType = ByteUtil::readUINT8(data)
		return onRecv_UserLogoutNtf(qwUsrID, eLeaveType)
	end

	#接收处理：离线事件通知
	def _doRecv_NewOffEventNotice(data)
		qwUsrID = ByteUtil::readUINT64(data)
		sEventData = SEventOffLine::fromStream(data)
		return onRecv_NewOffEventNotice(qwUsrID, sEventData)
	end

	#接收处理：新帮派战历史记录获取返回
	def _doRecv_NewGuildBattleHistoryNotify(data)
		dwCurSize = ByteUtil::readUINT32(data)
		dwTotalSize = ByteUtil::readUINT32(data)
		vecInfo = SDBGuildNewBattleHistoryInfo::vectorFromStream(data)
		return onRecv_NewGuildBattleHistoryNotify(dwCurSize, dwTotalSize, vecInfo)
	end

#以下为返回处理函数
	#返回处理：DBServer状态请求
	def _doReturn_GetStatus(data)
		retParam = SRetParam_GetStatus.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetStatus(ret)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：DBServer状态请求
	def _onTimeOut_GetStatus(sessionID)
		onReturn_GetStatus(2)
	end

	#返回处理：请求保存账号数据
	def _doReturn_SaveUserDataReq(data)
		retParam = SRetParam_SaveUserDataReq.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_SaveUserDataReq(ret, origParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求保存账号数据
	def _onTimeOut_SaveUserDataReq(sessionID)
		origParam = @sessionMgr.getData(sessionID)
		onReturn_SaveUserDataReq(2, origParam)
	end

	#返回处理：副本结束时候，玩家不在gameserver的数据保存
	def _doReturn_SaveOffLineDgnInfo(data)
		retParam = SRetParam_SaveOffLineDgnInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_SaveOffLineDgnInfo(ret, origParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：副本结束时候，玩家不在gameserver的数据保存
	def _onTimeOut_SaveOffLineDgnInfo(sessionID)
		origParam = @sessionMgr.getData(sessionID)
		onReturn_SaveOffLineDgnInfo(2, origParam)
	end

	#返回处理：加载离线玩家数据
	def _doReturn_LoadOffLineUserData(data)
		retParam = SRetParam_LoadOffLineUserData.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readUINT8(data) #(UINT8)0表示成功
		RoleData = RoleDataInfo::fromStream(data) #(类类型：RoleInfoDefine::RoleDataInfo)玩家数据
		retParam.byRet = byRet
		retParam.RoleData = RoleData
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LoadOffLineUserData(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：加载离线玩家数据
	def _onTimeOut_LoadOffLineUserData(sessionID)
		retParam = SRetParam_LoadOffLineUserData.new;
		onReturn_LoadOffLineUserData(2, retParam)
	end

	#返回处理：加载世界BOSS信息请求
	def _doReturn_LoadWorldBossInfo(data)
		retParam = SRetParam_LoadWorldBossInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecWorldBossInfo = SWBossDBInfo::vectorFromStream(data) #(SWBossDBInfo的数组)世界BOSS信息
		retParam.vecWorldBossInfo = vecWorldBossInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LoadWorldBossInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：加载世界BOSS信息请求
	def _onTimeOut_LoadWorldBossInfo(sessionID)
		retParam = SRetParam_LoadWorldBossInfo.new;
		onReturn_LoadWorldBossInfo(2, retParam)
	end

	#返回处理：根据名字获取ID请求
	def _doReturn_GetUserIDFromName(data)
		retParam = SRetParam_GetUserIDFromName.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		qwUsrID = ByteUtil::readUINT64(data) #(UINT64)用户ID
		retParam.qwUsrID = qwUsrID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetUserIDFromName(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：根据名字获取ID请求
	def _onTimeOut_GetUserIDFromName(sessionID)
		retParam = SRetParam_GetUserIDFromName.new;
		onReturn_GetUserIDFromName(2, retParam)
	end

	#返回处理：获得玩家战报信息
	def _doReturn_GetBattleReport(data)
		retParam = SRetParam_GetBattleReport.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecReport = SBattleRePort::vectorFromStream(data) #(SBattleRePort的数组)返回的数据
		retParam.vecReport = vecReport
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetBattleReport(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获得玩家战报信息
	def _onTimeOut_GetBattleReport(sessionID)
		retParam = SRetParam_GetBattleReport.new;
		onReturn_GetBattleReport(2, retParam)
	end

	#返回处理：增加玩家战报信息
	def _doReturn_AddBattleReport(data)
		retParam = SRetParam_AddBattleReport.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecBattleID = ByteUtil::readVecUINT64(data) #(UINT64数组)删除的战报
		retParam.vecBattleID = vecBattleID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_AddBattleReport(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：增加玩家战报信息
	def _onTimeOut_AddBattleReport(sessionID)
		retParam = SRetParam_AddBattleReport.new;
		onReturn_AddBattleReport(2, retParam)
	end

	#返回处理：加载商城限购信息
	def _doReturn_LoadMallDiscount(data)
		retParam = SRetParam_LoadMallDiscount.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecDisItems = SDiscount::vectorFromStream(data) #(SDiscount的数组)限购道具信息
		retParam.vecDisItems = vecDisItems
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LoadMallDiscount(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：加载商城限购信息
	def _onTimeOut_LoadMallDiscount(sessionID)
		retParam = SRetParam_LoadMallDiscount.new;
		onReturn_LoadMallDiscount(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 4;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_UserPackageProxy' #FuncID: 1
		@recvFuncList[1] = '_doRecv_UserLoginNtf' #FuncID: 2
		@recvFuncList[2] = '_doRecv_UserReEnterNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_UserLogoutNtf' #FuncID: 4
		@recvFuncList[4] = '_doRecv_NewOffEventNotice' #FuncID: 5
		@recvFuncList[5] = '_doRecv_NewGuildBattleHistoryNotify' #FuncID: 6

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetStatus' #FuncID: 1
		@retFuncList[1] = '_doReturn_SaveUserDataReq' #FuncID: 2
		@retFuncList[2] = '_doReturn_SaveOffLineDgnInfo' #FuncID: 3
		@retFuncList[3] = '_doReturn_LoadOffLineUserData' #FuncID: 4
		@retFuncList[4] = '_doReturn_LoadWorldBossInfo' #FuncID: 5
		@retFuncList[5] = '_doReturn_GetUserIDFromName' #FuncID: 6
		@retFuncList[6] = '_doReturn_GetBattleReport' #FuncID: 7
		@retFuncList[7] = '_doReturn_AddBattleReport' #FuncID: 8
		@retFuncList[8] = '_doReturn_LoadMallDiscount' #FuncID: 9

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetStatus' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_SaveUserDataReq' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_SaveOffLineDgnInfo' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_LoadOffLineUserData' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_LoadWorldBossInfo' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_GetUserIDFromName' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_GetBattleReport' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_AddBattleReport' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_LoadMallDiscount' #FuncID: 9
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

