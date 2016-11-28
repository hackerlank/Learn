#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    Center2DBComm.rb
#  Purpose:      CenterServer到DBServer的通信协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ArenaGSBase.rb'
require_relative './DemonTowerGSBase.rb'
require_relative './GlobalChatProtBase.rb'
require_relative './GodMonsterProtBase.rb'
require_relative './MailProtBase.rb'
require_relative './PHPProtBase.rb'
require_relative './ProtoCommonBase.rb'
require_relative './RankProtBase.rb'
require_relative './RoleInfoDefineBase.rb'
require_relative './ServerCommonBase.rb'
require_relative './ShipProtBase.rb'
require_relative './TripodProtBase.rb'
require_relative './WonderActivityProtBase.rb'

#以下为类型定义

#中心服数据类型
class ECenterData
	ECENTERDATE_BEAUTYLOG = 1#美女log
	ECENTERDATE_INVITEFRIEND = 2#邀请好友数据
	ECENTERDATE_INVITETASK = 3#邀请好友任务数据
	ECENTERDATE_DEMONTOWER_MINRONDS = 4#镇妖塔最小回数
	ECENTERDATE_DEMONTOWER_MINBATTLEPOINT = 5#镇妖塔最小战斗力
end

#中心服存储数据
class SCenterData
	attr_accessor:wType #(UINT16)类型 ECenterData
	attr_accessor:qwInstID #(UINT64)keyid1
	attr_accessor:qwInstID2 #(UINT64)keyid2
	attr_accessor:qwParam #(UINT64)64位参数
	attr_accessor:strParam #(string)整形参数
	attr_accessor:dwParam1 #(UINT32)32位参数1
	attr_accessor:dwParam2 #(UINT32)32位参数2
	attr_accessor:dwParam3 #(UINT32)32位参数3
	attr_accessor:qwParam4 #(UINT64)64位参数4

	#构造函数
	def initialize
		@wType = 0
		@qwInstID = 0
		@qwInstID2 = 0
		@qwParam = 0
		@strParam = ''
		@dwParam1 = 0
		@dwParam2 = 0
		@dwParam3 = 0
		@qwParam4 = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wType = @wType
		obj.qwInstID = @qwInstID
		obj.qwInstID2 = @qwInstID2
		obj.qwParam = @qwParam
		obj.strParam = @strParam
		obj.dwParam1 = @dwParam1
		obj.dwParam2 = @dwParam2
		obj.dwParam3 = @dwParam3
		obj.qwParam4 = @qwParam4
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SCenterData.new
		s.wType = ByteUtil::readUINT16(data)
		s.qwInstID = ByteUtil::readUINT64(data)
		s.qwInstID2 = ByteUtil::readUINT64(data)
		s.qwParam = ByteUtil::readUINT64(data)
		s.strParam = ByteUtil::readSTRING(data)
		s.dwParam1 = ByteUtil::readUINT32(data)
		s.dwParam2 = ByteUtil::readUINT32(data)
		s.dwParam3 = ByteUtil::readUINT32(data)
		s.qwParam4 = ByteUtil::readUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SCenterData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wType)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT64(data, @qwInstID2)
		ByteUtil::writeUINT64(data, @qwParam)
		ByteUtil::writeSTRING(data, @strParam)
		ByteUtil::writeUINT32(data, @dwParam1)
		ByteUtil::writeUINT32(data, @dwParam2)
		ByteUtil::writeUINT32(data, @dwParam3)
		ByteUtil::writeUINT64(data, @qwParam4)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#系统邮件信息
class SSystemMailTargetInfo
	attr_accessor:qwMailID #(UINT64)邮件ID
	attr_accessor:qwReceiveID #(UINT64)接受者ID

	#构造函数
	def initialize
		@qwMailID = 0
		@qwReceiveID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwMailID = @qwMailID
		obj.qwReceiveID = @qwReceiveID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSystemMailTargetInfo.new
		s.qwMailID = ByteUtil::readUINT64(data)
		s.qwReceiveID = ByteUtil::readUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSystemMailTargetInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwMailID)
		ByteUtil::writeUINT64(data, @qwReceiveID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#邮件删除提示结构
class MailDelData
	attr_accessor:qwMailID #(UINT64)邮件ID
	attr_accessor:byGet #(UINT8)邮件的附件状态

	#构造函数
	def initialize
		@qwMailID = 0
		@byGet = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwMailID = @qwMailID
		obj.byGet = @byGet
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = MailDelData.new
		s.qwMailID = ByteUtil::readUINT64(data)
		s.byGet = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = MailDelData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwMailID)
		ByteUtil::writeUINT8(data, @byGet)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#系统邮件信息
class SSystemMailInfo
	attr_accessor:eMailType #(枚类型：MailProt::EMailType)邮件类型
	attr_accessor:eMailState #(枚类型：MailProt::EMailState)邮件状态
	attr_accessor:dwSendTime #(UINT32)发送时间
	attr_accessor:strTitle #(string)标题
	attr_accessor:strSender #(string)发送者
	attr_accessor:strMsg #(string)邮件内容
	attr_accessor:byGet #(UINT8)附件状态
	attr_accessor:vecMailAttachment #(SMailBaseAttachment的数组)附件

	#构造函数
	def initialize
		@eMailType = 0
		@eMailState = 0
		@dwSendTime = 0
		@strTitle = ''
		@strSender = ''
		@strMsg = ''
		@byGet = 0
		@vecMailAttachment = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eMailType = @eMailType
		obj.eMailState = @eMailState
		obj.dwSendTime = @dwSendTime
		obj.strTitle = @strTitle
		obj.strSender = @strSender
		obj.strMsg = @strMsg
		obj.byGet = @byGet
		obj.vecMailAttachment = @vecMailAttachment
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSystemMailInfo.new
		s.eMailType = ByteUtil::readUINT8(data)
		s.eMailState = ByteUtil::readUINT8(data)
		s.dwSendTime = ByteUtil::readUINT32(data)
		s.strTitle = ByteUtil::readSTRING(data)
		s.strSender = ByteUtil::readSTRING(data)
		s.strMsg = ByteUtil::readSTRING(data)
		s.byGet = ByteUtil::readUINT8(data)
		s.vecMailAttachment = SMailBaseAttachment::superVectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSystemMailInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eMailType)
		ByteUtil::writeUINT8(data, @eMailState)
		ByteUtil::writeUINT32(data, @dwSendTime)
		ByteUtil::writeSTRING(data, @strTitle)
		ByteUtil::writeSTRING(data, @strSender)
		ByteUtil::writeSTRING(data, @strMsg)
		ByteUtil::writeUINT8(data, @byGet)
		SMailBaseAttachment::superVectorToStream(data, @vecMailAttachment)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#数据库查询基本条件
class SBaseCond
	attr_accessor:byLevel #(UINT8)等级

	#构造函数
	def initialize
		@byLevel = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byLevel = @byLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBaseCond.new
		s.byLevel = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBaseCond::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#数据库查询返回
class SBaseResult
	attr_accessor:vecPlayerID #(UINT64数组)玩家ID
	attr_accessor:dwResult #(UINT32)查询结果

	#构造函数
	def initialize
		@vecPlayerID = Array.new
		@dwResult = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.vecPlayerID = @vecPlayerID
		obj.dwResult = @dwResult
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBaseResult.new
		s.vecPlayerID = ByteUtil::readVecUINT64(data)
		s.dwResult = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBaseResult::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeVecUINT64(data, @vecPlayerID)
		ByteUtil::writeUINT32(data, @dwResult)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家等级
class SRoleLevel
	attr_accessor:dwID #(UINT32)条件ID
	attr_accessor:dwCount #(UINT32)数量
	attr_accessor:vecRole #(UINT64数组)玩家ID

	#构造函数
	def initialize
		@dwID = 0
		@dwCount = 0
		@vecRole = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwID = @dwID
		obj.dwCount = @dwCount
		obj.vecRole = @vecRole
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRoleLevel.new
		s.dwID = ByteUtil::readUINT32(data)
		s.dwCount = ByteUtil::readUINT32(data)
		s.vecRole = ByteUtil::readVecUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRoleLevel::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwID)
		ByteUtil::writeUINT32(data, @dwCount)
		ByteUtil::writeVecUINT64(data, @vecRole)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[LoadPrepaid:加载玩家未创角预先充值的仙石信息]的返回的参数组成的结构体
class SRetParam_LoadPrepaid
	attr_accessor:vecPrepaid#(SPrepaid的数组)玩家未创角预先值信息

	#构造函数
	def initialize
		@vecPrepaid = Array.new
	end
end

#函数[ReplaceUser:替换帐号]的原来的参数组成的结构体
class SOrigParam_ReplaceUser
	attr_accessor:qwUsrID #(UINT64)帐号ID

	#构造函数
	def initialize
		@qwUsrID = 0
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

#函数[GetUserIDFromName:根据名字获取ID请求]的返回的参数组成的结构体
class SRetParam_GetUserIDFromName
	attr_accessor:qwUsrID#(UINT64)用户ID

	#构造函数
	def initialize
		@qwUsrID = 0
	end
end

#函数[GetAllMailList:获得邮件列表]的返回的参数组成的结构体
class SRetParam_GetAllMailList
	attr_accessor:vecMails#(SMailDetail的数组)邮件列表

	#构造函数
	def initialize
		@vecMails = Array.new
	end
end

#函数[SaveMail:保存邮件]的返回的参数组成的结构体
class SRetParam_SaveMail
	attr_accessor:byRet#(INT8)非0表示失败

	#构造函数
	def initialize
		@byRet = 0
	end
end

#函数[DeleteMail:删除邮件]的返回的参数组成的结构体
class SRetParam_DeleteMail
	attr_accessor:byRet#(INT8)非0表示失败

	#构造函数
	def initialize
		@byRet = 0
	end
end

#函数[SaveSystemMail:保存系统邮件]的返回的参数组成的结构体
class SRetParam_SaveSystemMail
	attr_accessor:byRet#(INT8)非0表示失败

	#构造函数
	def initialize
		@byRet = 0
	end
end

#函数[UpdateMailStatus:更新邮件状态]的返回的参数组成的结构体
class SRetParam_UpdateMailStatus
	attr_accessor:byRet#(INT8)非0表示失败

	#构造函数
	def initialize
		@byRet = 0
	end
end

#函数[DelMailAttach:删除邮件附件]的返回的参数组成的结构体
class SRetParam_DelMailAttach
	attr_accessor:byRet#(INT8)非0表示失败

	#构造函数
	def initialize
		@byRet = 0
	end
end

#函数[GetPrizeStatus:查询玩家奖励状态]的返回的参数组成的结构体
class SRetParam_GetPrizeStatus
	attr_accessor:vecRet#(SWonderPrize2DB的数组)查询结果

	#构造函数
	def initialize
		@vecRet = Array.new
	end
end

#函数[GetAllRoleLevel:查询所有玩家信息]的返回的参数组成的结构体
class SRetParam_GetAllRoleLevel
	attr_accessor:byTypeRet#(UINT8)类型
	attr_accessor:vecRoleLevel#(SRoleLevel的数组)返回玩家等级

	#构造函数
	def initialize
		@byTypeRet = 0
		@vecRoleLevel = Array.new
	end
end

#函数[GetRetain:查询玩家保留信息]的返回的参数组成的结构体
class SRetParam_GetRetain
	attr_accessor:vecRet#(SRetain的数组)查询结果

	#构造函数
	def initialize
		@vecRet = Array.new
	end
end

#函数[GetGameVar:请求系统Var数据]的返回的参数组成的结构体
class SRetParam_GetGameVar
	attr_accessor:vecVar#(SGameVarsDBInfo的数组)返回的Var

	#构造函数
	def initialize
		@vecVar = Array.new
	end
end

#函数[GetArenaFighterByID:根据玩家ID获得竞技基本数据]的返回的参数组成的结构体
class SRetParam_GetArenaFighterByID
	attr_accessor:stFighter#(类类型：ArenaGS::SArenaFighter)返回的数据

	#构造函数
	def initialize
		@stFighter = SArenaFighter.new
	end
end

#函数[GetDemonTowerInfo:获取镇妖塔信息（启动预加载调用）]的返回的参数组成的结构体
class SRetParam_GetDemonTowerInfo
	attr_accessor:vecDemonTowerPlayer#(SDemonTowerPlayer的数组)镇妖塔玩家信息

	#构造函数
	def initialize
		@vecDemonTowerPlayer = Array.new
	end
end

#函数[GetCenterData:获取中心服数据]的返回的参数组成的结构体
class SRetParam_GetCenterData
	attr_accessor:vecCenterData#(SCenterData的数组)中心服数据

	#构造函数
	def initialize
		@vecCenterData = Array.new
	end
end

#函数[GetWhisperInfo:查看玩家私聊信息]的返回的参数组成的结构体
class SRetParam_GetWhisperInfo
	attr_accessor:whisperInfo#(类类型：GlobalChatProt::SWhisperInfo)返回的数据

	#构造函数
	def initialize
		@whisperInfo = SWhisperInfo.new
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

#函数[GetGodMonsterInfo:获取天元神兽信息（启动预加载调用）]的返回的参数组成的结构体
class SRetParam_GetGodMonsterInfo
	attr_accessor:vecUser#(SGuildUser2DB的数组)天元神兽玩家信息

	#构造函数
	def initialize
		@vecUser = Array.new
	end
end

#函数[GetLimitPrizeInfo:获取天元神兽玩家限购礼包信息（启动预加载调用）]的返回的参数组成的结构体
class SRetParam_GetLimitPrizeInfo
	attr_accessor:vecLimitPrize#(SLimitPrize2DB的数组)数据

	#构造函数
	def initialize
		@vecLimitPrize = Array.new
	end
end

#函数[GetActivityCenterInfo:运营活动中心操作（启动预加载调用）]的返回的参数组成的结构体
class SRetParam_GetActivityCenterInfo
	attr_accessor:vecActOpt#(SActivityOpt的数组)数据

	#构造函数
	def initialize
		@vecActOpt = Array.new
	end
end

#协议类：CenterServer到DBServer的通信协议
class Center2DBCommBase < ProtocolBase
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

	#发送：插入玩家充值仙石信息(未创角预先充值)
	def send_InsertRecharge(
		oRecharge #(类类型：RoleInfoDefine::SRecharge)充值仙石的数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		oRecharge.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：加载玩家未创角预先充值的仙石信息
	def send_LoadPrepaid(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新玩家未创角预先充值信息
	def send_UpdatePrepaid(
		eUpdateType,  #(枚类型：ProtoCommon::EDataChange)更新类型，增加，删除，修改
		qwRoleID,  #(UINT64)玩家ID
		dwGold #(UINT32)仙石数量
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eUpdateType)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT32(data, dwGold)
		return @svrHandler.sendPacket(data)
	end

	#发送：替换帐号
	def send_ReplaceUser(
		qwUsrID #(UINT64)帐号ID
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		origParam = SOrigParam_ReplaceUser.new
		origParam.qwUsrID = qwUsrID
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwUsrID)
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

	#发送：一行数据更新
	def send_RoleDataUpdate(
		qwRoleId,  #(UINT64)角色Id
		eDataType,  #(枚类型：RoleInfoDefine::EDataType)更新数据块
		eUpdateType,  #(枚类型：ProtoCommon::EDataChange)更新类型，增加，删除，修改
		strData #(string)更新数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleId)
		ByteUtil::writeUINT8(data, eDataType)
		ByteUtil::writeUINT8(data, eUpdateType)
		ByteUtil::writeSTRING(data, strData)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取排名信息
	def send_GetRankInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：排行榜数据更新
	def send_RankDataUpdate(
		qwInstID,  #(UINT64)唯一ID
		eDataType,  #(枚类型：RankProt::ERankType)更新数据类型
		eUpdateType,  #(枚类型：ProtoCommon::EDataChange)更新方式，增加，删除，修改
		strData #(string)更新数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT8(data, eDataType)
		ByteUtil::writeUINT8(data, eUpdateType)
		ByteUtil::writeSTRING(data, strData)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取崇拜信息
	def send_GetAdoreInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：崇拜数据更新
	def send_AdoreDataUpdate(
		qwInstID,  #(UINT64)唯一ID
		eUpdateType,  #(枚类型：ProtoCommon::EDataChange)更新方式，增加，删除，修改
		strData #(string)更新数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT8(data, eUpdateType)
		ByteUtil::writeSTRING(data, strData)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取账号ID或主角色名请求
	def send_UserIDNameReq(
		eType,  #(枚类型：ServerCommon::EUserReqType)类型
		qwUsrID,  #(UINT64)帐号ID
		strName,  #(string)主角色名称
		qwUsrData #(UINT64)用户数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 13
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eType)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeSTRING(data, strName)
		ByteUtil::writeUINT64(data, qwUsrData)
		return @svrHandler.sendPacket(data)
	end

	#发送：根据名字获取ID请求
	def send_GetUserIDFromName(
		strName #(string)主角色名称
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 14
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeSTRING(data, strName)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得邮件列表
	def send_GetAllMailList(
		qwRoleID,  #(UINT64)玩家ID
		dwOverTime #(UINT32)过期时间
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 15
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT32(data, dwOverTime)
		return @svrHandler.sendPacket(data)
	end

	#发送：保存邮件
	def send_SaveMail(
		qwMailID,  #(UINT64)邮件ID
		qwReceiveID,  #(UINT64)接受者ID
		qwSenderID,  #(UINT64)发送者ID
		strSenderName,  #(string)发送者名字
		eMailType,  #(枚类型：MailProt::EMailType)邮件类型
		eMailState,  #(枚类型：MailProt::EMailState)邮件状态
		dwSendTime,  #(UINT32)发送时间
		strTitle,  #(string)标题
		strMsg #(string)邮件内容
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 16
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwMailID)
		ByteUtil::writeUINT64(data, qwReceiveID)
		ByteUtil::writeUINT64(data, qwSenderID)
		ByteUtil::writeSTRING(data, strSenderName)
		ByteUtil::writeUINT8(data, eMailType)
		ByteUtil::writeUINT8(data, eMailState)
		ByteUtil::writeUINT32(data, dwSendTime)
		ByteUtil::writeSTRING(data, strTitle)
		ByteUtil::writeSTRING(data, strMsg)
		return @svrHandler.sendPacket(data)
	end

	#发送：删除邮件
	def send_DeleteMail(
		qwRoleID,  #(UINT64)玩家ID
		vecMailIDs #(MailDelData的数组)邮件ID列表
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 17
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		MailDelData::vectorToStream(data, vecMailIDs)
		return @svrHandler.sendPacket(data)
	end

	#发送：保存系统邮件
	def send_SaveSystemMail(
		vecSystemMailTargetInfo,  #(SSystemMailTargetInfo的数组)邮件目标
		rSystemMailInfo #(类类型：SSystemMailInfo)系统邮件信息
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 18
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		SSystemMailTargetInfo::vectorToStream(data, vecSystemMailTargetInfo)
		rSystemMailInfo.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新邮件状态
	def send_UpdateMailStatus(
		qwMailID,  #(UINT64)邮件ID
		eMailState #(枚类型：MailProt::EMailState)邮件状态
	)
		sessionID = @sessionMgr.getNewSession(self, 10);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 19
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwMailID)
		ByteUtil::writeUINT8(data, eMailState)
		return @svrHandler.sendPacket(data)
	end

	#发送：删除邮件附件
	def send_DelMailAttach(
		stDelData #(类类型：MailDelData)删除提示
	)
		sessionID = @sessionMgr.getNewSession(self, 11);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 20
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		stDelData.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：查询玩家奖励状态
	def send_GetPrizeStatus(
	)
		sessionID = @sessionMgr.getNewSession(self, 12);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 21
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：删除玩家数据
	def send_DelActPrizeData(
		wActID #(UINT16)活动ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 22
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT16(data, wActID)
		return @svrHandler.sendPacket(data)
	end

	#发送：查询所有玩家信息
	def send_GetAllRoleLevel(
		byType #(UINT8)类型
	)
		sessionID = @sessionMgr.getNewSession(self, 13);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 23
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byType)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新玩家奖励状态
	def send_UpdatePrizeStatus(
		sPrize2DB,  #(类类型：WonderActivityProt::SWonderPrize2DB)玩家信息
		eUpdateType #(枚类型：ProtoCommon::EDataChange)更新方式，增加，删除，修改
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 24
		ByteUtil::writeINT8(data, funcID)
		sPrize2DB.toStream(data)
		ByteUtil::writeUINT8(data, eUpdateType)
		return @svrHandler.sendPacket(data)
	end

	#发送：查询玩家保留信息
	def send_GetRetain(
	)
		sessionID = @sessionMgr.getNewSession(self, 14);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 25
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新玩家保留信息
	def send_UpdateRetain(
		sRetain,  #(类类型：WonderActivityProt::SRetain)玩家保留信息
		eUpdateType #(枚类型：ProtoCommon::EDataChange)更新方式，增加，删除，修改
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 26
		ByteUtil::writeINT8(data, funcID)
		sRetain.toStream(data)
		ByteUtil::writeUINT8(data, eUpdateType)
		return @svrHandler.sendPacket(data)
	end

	#发送：删除玩家保留数据
	def send_DelActRetainData(
		wActID #(UINT16)活动ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 27
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT16(data, wActID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求所有UserID和name
	def send_GetAllUserIDAndName(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 28
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求所有公告
	def send_GetAllNotice(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 29
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：增加公告
	def send_AddNotice(
		sNotice #(类类型：PHPProt::SNotice)公告内容
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 30
		ByteUtil::writeINT8(data, funcID)
		sNotice.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：删除公告
	def send_DelNotice(
		dwNoticeID #(UINT32)公告ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 31
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, dwNoticeID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求斗剑信息
	def send_GetAllArena(
		dwPageSize #(UINT32)发送条数
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 32
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, dwPageSize)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新斗剑数据
	def send_UpdateAllArena(
		vecUpdate #(SArenaPlayerBaseDataUpdate的数组)更新信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 33
		ByteUtil::writeINT8(data, funcID)
		SArenaPlayerBaseDataUpdate::vectorToStream(data, vecUpdate)
		return @svrHandler.sendPacket(data)
	end

	#发送：删除玩家斗剑数据
	def send_DelPlayerArena(
		vecDel #(UINT64数组)删除玩家斗剑信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 34
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeVecUINT64(data, vecDel)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求系统Var数据
	def send_GetGameVar(
	)
		sessionID = @sessionMgr.getNewSession(self, 15);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 35
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新系统Var数据
	def send_UpdateGameVar(
		Var #(类类型：RoleInfoDefine::SGameVarsDBInfo)更新的Var
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 36
		ByteUtil::writeINT8(data, funcID)
		Var.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：增加系统Var数据
	def send_AddGameVar(
		Var #(类类型：RoleInfoDefine::SGameVarsDBInfo)增加的Var
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 37
		ByteUtil::writeINT8(data, funcID)
		Var.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：删除Var数据
	def send_DelGameVar(
		wVarID #(UINT16)删除的VarID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 38
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT16(data, wVarID)
		return @svrHandler.sendPacket(data)
	end

	#发送：根据玩家ID获得竞技基本数据
	def send_GetArenaFighterByID(
		qwRoleID #(UINT64)玩家的ID
	)
		sessionID = @sessionMgr.getNewSession(self, 16);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 39
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取镇妖塔信息（启动预加载调用）
	def send_GetDemonTowerInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 17);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 40
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新镇妖塔玩家信息
	def send_UpateDemonTowerInfo(
		eDbType,  #(枚类型：DemonTowerGS::EDemonTowerDB)更新类型
		oDemonTowerPlayer #(类类型：DemonTowerGS::SDemonTowerPlayer)镇妖塔玩家信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 41
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eDbType)
		oDemonTowerPlayer.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取中心服数据
	def send_GetCenterData(
	)
		sessionID = @sessionMgr.getNewSession(self, 18);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 42
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新中心服数据
	def send_UpateCenterData(
		oCenterData,  #(类类型：SCenterData)中心服数据
		bDelete #(bool)删除/更新
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 43
		ByteUtil::writeINT8(data, funcID)
		oCenterData.toStream(data)
		ByteUtil::writeBOOL(data, bDelete)
		return @svrHandler.sendPacket(data)
	end

	#发送：查看玩家私聊信息
	def send_GetWhisperInfo(
		qwRoleID #(UINT64)玩家的ID
	)
		sessionID = @sessionMgr.getNewSession(self, 19);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 44
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得玩家战报信息
	def send_GetBattleReport(
		qwRoleID,  #(UINT64)玩家的ID
		eBattleType,  #(枚类型：RoleInfoDefine::EBattleReportType)战斗类型
		eAction #(枚类型：RoleInfoDefine::EBattleActionType)战斗的发起
	)
		sessionID = @sessionMgr.getNewSession(self, 20);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 45
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT8(data, eBattleType)
		ByteUtil::writeUINT8(data, eAction)
		return @svrHandler.sendPacket(data)
	end

	#发送：增加玩家战报信息
	def send_AddBattleReport(
		qwRoleID,  #(UINT64)玩家的ID
		sReport,  #(类类型：RoleInfoDefine::SBattleRePort)战斗数据
		byNum #(UINT8)超过byNum，返回删除的旧的战报,0表示不删除
	)
		sessionID = @sessionMgr.getNewSession(self, 21);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 46
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		sReport.toStream(data)
		ByteUtil::writeUINT8(data, byNum)
		return @svrHandler.sendPacket(data)
	end

	#发送：重新加载表格
	def send_ReloadTable(
		vecTableName #(string数组)表格名字
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 47
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeVecSTRING(data, vecTableName)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求所有九疑鼎信息
	def send_GetAllTripod(
		dwPageSize #(UINT32)发送条数
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 48
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, dwPageSize)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求所有九疑鼎的协助信息
	def send_GetAllTripodHelper(
		dwPageSize #(UINT32)发送条数
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 49
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, dwPageSize)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求所有九疑鼎的动态信息
	def send_GetAllTripodLog(
		dwPageSize #(UINT32)发送条数
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 50
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, dwPageSize)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新玩家九疑鼎信息
	def send_UpdateTripod(
		qwRoleID,  #(UINT64)玩家的ID
		oTripodInfo #(类类型：TripodProt::STripodInfo)九疑鼎的数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 51
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		oTripodInfo.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新玩家九疑鼎协助信息
	def send_UpateTripodHelp(
		eUpdateType,  #(枚类型：ProtoCommon::EDataChange)更新类型，增加，删除，修改
		oTripodHelp #(类类型：TripodProt::STripodHelp)九疑鼎协助的信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 52
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eUpdateType)
		oTripodHelp.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新玩家九疑鼎动态信息
	def send_UpdateTripodLog(
		qwRoleID,  #(UINT64)玩家的ID
		eUpdateType,  #(枚类型：ProtoCommon::EDataChange)更新类型，增加，删除，修改
		oTripodLog #(类类型：TripodProt::STripodLog)九疑鼎动态的信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 53
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT8(data, eUpdateType)
		oTripodLog.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：增加离线事件
	def send_AddOffLineEvent(
		vecRoleID,  #(UINT64数组)玩家的ID
		sEventData #(类类型：RoleInfoDefine::SEventOffLine)事件
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 54
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeVecUINT64(data, vecRoleID)
		sEventData.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：对玩家封号
	def send_FreezePlayer(
		qwRoleID,  #(UINT64)玩家的ID
		dwFreezeTimer #(UINT32)封号
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 55
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT32(data, dwFreezeTimer)
		return @svrHandler.sendPacket(data)
	end

	#发送：对玩家禁言
	def send_ForbitChat(
		qwRoleID,  #(UINT64)玩家的ID
		dwForbitTimer #(UINT32)禁言时间
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 56
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT32(data, dwForbitTimer)
		return @svrHandler.sendPacket(data)
	end

	#发送：将玩家登录时IP写入数据库
	def send_UpdateLoginIP(
		qwUserID,  #(UINT64)玩家的ID
		strLoginIP #(string)登录时IP
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 57
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeSTRING(data, strLoginIP)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求拉取进入参数
	def send_GetPlatformParam(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 58
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：数据库查询
	def send_GetResult2DB(
		sBaseCond #(类类型：SBaseCond)查询条件
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 59
		ByteUtil::writeINT8(data, funcID)
		sBaseCond.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求金船信息
	def send_GetAllShip(
		dwPageSize #(UINT32)发送条数
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 60
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, dwPageSize)
		return @svrHandler.sendPacket(data)
	end

	#发送：更新金船数据
	def send_UpdateShip(
		UpdateInfo #(类类型：ShipProt::PlayerShip)更新信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 61
		ByteUtil::writeINT8(data, funcID)
		UpdateInfo.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：删除金船数据
	def send_DelShip(
		qwInsID #(UINT64)删除金船信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 62
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwInsID)
		return @svrHandler.sendPacket(data)
	end

	#发送：增加金船报告
	def send_AddShipReport(
		qwRoleID,  #(UINT64)报告拥有者
		sReport #(类类型：ShipProt::ShipReport)报告内容
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 63
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		sReport.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：删除金船报告
	def send_DelShipReport(
		qwRoleID,  #(UINT64)报告拥有者
		qwInsID #(UINT64)金船唯一ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 64
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT64(data, qwInsID)
		return @svrHandler.sendPacket(data)
	end

	#发送：天元神兽同步玩家信息
	def send_SyncMonsterUserInfo(
		eUpdateType,  #(枚类型：ProtoCommon::EDataChange)更新类型，增加，删除，修改
		sUser #(类类型：GodMonsterProt::SGuildUser2DB)数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 65
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eUpdateType)
		sUser.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取天元神兽信息（启动预加载调用）
	def send_GetGodMonsterInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 22);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 66
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：天元神兽同步玩家限购礼包信息
	def send_SyncLimitPrizeInfo(
		eUpdateType,  #(枚类型：ProtoCommon::EDataChange)更新类型，增加，删除，修改
		oLimitPrize #(类类型：GodMonsterProt::SLimitPrize2DB)数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 67
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eUpdateType)
		oLimitPrize.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取天元神兽玩家限购礼包信息（启动预加载调用）
	def send_GetLimitPrizeInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 23);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 68
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：运营活动中心同步信息
	def send_SyncActivityCenterInfo(
		eUpdateType,  #(枚类型：ProtoCommon::EDataChange)更新类型，增加，删除，修改
		oActOpt #(类类型：ProtoCommon::SActivityOpt)数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 69
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eUpdateType)
		oActOpt.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：运营活动中心操作（启动预加载调用）
	def send_GetActivityCenterInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 24);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 70
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：增加机器人新信息
	def send_AddLadderRobot(
		vecData #(SLadderRobot的数组)数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 71
		ByteUtil::writeINT8(data, funcID)
		SLadderRobot::vectorToStream(data, vecData)
		return @svrHandler.sendPacket(data)
	end

	#发送：增加机器人新信息
	def send_UpdateLadderRobot(
		SData #(类类型：ArenaGS::SLadderRobot)数据
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 72
		ByteUtil::writeINT8(data, funcID)
		SData.toStream(data)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：返回查询结果
	def onRecv_SendResult2Cent(
		sCond, #(类类型：SBaseCond)查询条件
		sResult #(类类型：SBaseResult)查询结果
	)
		raise NotImplementedError
	end
	#接收：返回所有玩家ID和名字
	def onRecv_SendAllUserIDAndName(
		dwTotalSize, #(UINT32)总条数
		vecUserIDAndName #(SUserIDAndName的数组)玩家ID和名字
	)
		raise NotImplementedError
	end
	#接收：返回所有公告
	def onRecv_SendAllNotice(
		vecNotice #(SNotice的数组)公告内容
	)
		raise NotImplementedError
	end
	#接收：返回请求斗剑信息
	def onRecv_SendAllArena(
		dwPageSize, #(UINT32)已发送条数
		dwTotalSize, #(UINT32)总条数
		vecSendDate #(SArenaPlayerData的数组)更新信息
	)
		raise NotImplementedError
	end
	#接收：返回机器人天梯排行信息
	def onRecv_SendAllRobot(
		vecRobot #(SLadderRobot的数组)机器人排行信息
	)
		raise NotImplementedError
	end
	#接收：返回请求排行榜数据
	def onRecv_RankInitNotify(
		dwCurSize, #(UINT32)已发送条数
		dwTotalSize, #(UINT32)总条数
		vecRankInfo #(SRankInfo的数组)更新信息
	)
		raise NotImplementedError
	end
	#接收：返回请求崇拜数据
	def onRecv_AdoreInitNotify(
		dwCurSize, #(UINT32)已发送条数
		dwTotalSize, #(UINT32)总条数
		vecAdoreInfo #(SDBAdoreInfo的数组)更新信息
	)
		raise NotImplementedError
	end
	#接收：返回所有九疑鼎信息
	def onRecv_SendAllTripod(
		dwPageSize, #(UINT32)已发送条数
		dwTotalSize, #(UINT32)总条数
		vecSendData #(STripodData的数组)更新信息
	)
		raise NotImplementedError
	end
	#接收：返回所有九疑鼎的协助信息
	def onRecv_SendAllTripodHelper(
		dwPageSize, #(UINT32)已发送条数
		dwTotalSize, #(UINT32)总条数
		vecSendData #(STripodHelp的数组)更新信息
	)
		raise NotImplementedError
	end
	#接收：返回所有九疑鼎的动态信息
	def onRecv_SendAllTripodLog(
		dwPageSize, #(UINT32)已发送条数
		dwTotalSize, #(UINT32)总条数
		vecSendData #(STripodLog的数组)更新信息
	)
		raise NotImplementedError
	end
	#接收：平台参数加载返回
	def onRecv_PlatformParamInfoNotify(
		dwCurSize, #(UINT32)已发送条数
		dwTotalSize, #(UINT32)总条数
		vecRoleID, #(UINT64数组)玩家ID
		vecPlatformParam #(SPlatformParam的数组)更新信息
	)
		raise NotImplementedError
	end
	#接收：返回请求金船信息
	def onRecv_SendAllShip(
		dwPageSize, #(UINT32)已发送条数
		dwTotalSize, #(UINT32)总条数
		vecSendDate #(PlayerShip的数组)更新信息
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：DBServer状态请求
	def onReturn_GetStatus(
		ret #0为成功，1为失败，2为超时
	)
	end

	#返回：加载玩家未创角预先充值的仙石信息
	def onReturn_LoadPrepaid(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LoadPrepaid)返回的参数
	)
	end

	#返回：替换帐号
	def onReturn_ReplaceUser(
		ret, #0为成功，1为失败，2为超时
		origParam #(类类型：SOrigParam_ReplaceUser)原来的参数
	)
	end

	#返回：加载离线玩家数据
	def onReturn_LoadOffLineUserData(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LoadOffLineUserData)返回的参数
	)
	end

	#返回：根据名字获取ID请求
	def onReturn_GetUserIDFromName(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetUserIDFromName)返回的参数
	)
	end

	#返回：获得邮件列表
	def onReturn_GetAllMailList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAllMailList)返回的参数
	)
	end

	#返回：保存邮件
	def onReturn_SaveMail(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SaveMail)返回的参数
	)
	end

	#返回：删除邮件
	def onReturn_DeleteMail(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_DeleteMail)返回的参数
	)
	end

	#返回：保存系统邮件
	def onReturn_SaveSystemMail(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SaveSystemMail)返回的参数
	)
	end

	#返回：更新邮件状态
	def onReturn_UpdateMailStatus(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UpdateMailStatus)返回的参数
	)
	end

	#返回：删除邮件附件
	def onReturn_DelMailAttach(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_DelMailAttach)返回的参数
	)
	end

	#返回：查询玩家奖励状态
	def onReturn_GetPrizeStatus(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetPrizeStatus)返回的参数
	)
	end

	#返回：查询所有玩家信息
	def onReturn_GetAllRoleLevel(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAllRoleLevel)返回的参数
	)
	end

	#返回：查询玩家保留信息
	def onReturn_GetRetain(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetRetain)返回的参数
	)
	end

	#返回：请求系统Var数据
	def onReturn_GetGameVar(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetGameVar)返回的参数
	)
	end

	#返回：根据玩家ID获得竞技基本数据
	def onReturn_GetArenaFighterByID(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetArenaFighterByID)返回的参数
	)
	end

	#返回：获取镇妖塔信息（启动预加载调用）
	def onReturn_GetDemonTowerInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetDemonTowerInfo)返回的参数
	)
	end

	#返回：获取中心服数据
	def onReturn_GetCenterData(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetCenterData)返回的参数
	)
	end

	#返回：查看玩家私聊信息
	def onReturn_GetWhisperInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetWhisperInfo)返回的参数
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

	#返回：获取天元神兽信息（启动预加载调用）
	def onReturn_GetGodMonsterInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetGodMonsterInfo)返回的参数
	)
	end

	#返回：获取天元神兽玩家限购礼包信息（启动预加载调用）
	def onReturn_GetLimitPrizeInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetLimitPrizeInfo)返回的参数
	)
	end

	#返回：运营活动中心操作（启动预加载调用）
	def onReturn_GetActivityCenterInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetActivityCenterInfo)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：返回查询结果
	def _doRecv_SendResult2Cent(data)
		sCond = SBaseCond::fromStream(data)
		sResult = SBaseResult::fromStream(data)
		return onRecv_SendResult2Cent(sCond, sResult)
	end

	#接收处理：返回所有玩家ID和名字
	def _doRecv_SendAllUserIDAndName(data)
		dwTotalSize = ByteUtil::readUINT32(data)
		vecUserIDAndName = SUserIDAndName::vectorFromStream(data)
		return onRecv_SendAllUserIDAndName(dwTotalSize, vecUserIDAndName)
	end

	#接收处理：返回所有公告
	def _doRecv_SendAllNotice(data)
		vecNotice = SNotice::vectorFromStream(data)
		return onRecv_SendAllNotice(vecNotice)
	end

	#接收处理：返回请求斗剑信息
	def _doRecv_SendAllArena(data)
		dwPageSize = ByteUtil::readUINT32(data)
		dwTotalSize = ByteUtil::readUINT32(data)
		vecSendDate = SArenaPlayerData::vectorFromStream(data)
		return onRecv_SendAllArena(dwPageSize, dwTotalSize, vecSendDate)
	end

	#接收处理：返回机器人天梯排行信息
	def _doRecv_SendAllRobot(data)
		vecRobot = SLadderRobot::vectorFromStream(data)
		return onRecv_SendAllRobot(vecRobot)
	end

	#接收处理：返回请求排行榜数据
	def _doRecv_RankInitNotify(data)
		dwCurSize = ByteUtil::readUINT32(data)
		dwTotalSize = ByteUtil::readUINT32(data)
		vecRankInfo = SRankInfo::superVectorFromStream(data)
		return onRecv_RankInitNotify(dwCurSize, dwTotalSize, vecRankInfo)
	end

	#接收处理：返回请求崇拜数据
	def _doRecv_AdoreInitNotify(data)
		dwCurSize = ByteUtil::readUINT32(data)
		dwTotalSize = ByteUtil::readUINT32(data)
		vecAdoreInfo = SDBAdoreInfo::vectorFromStream(data)
		return onRecv_AdoreInitNotify(dwCurSize, dwTotalSize, vecAdoreInfo)
	end

	#接收处理：返回所有九疑鼎信息
	def _doRecv_SendAllTripod(data)
		dwPageSize = ByteUtil::readUINT32(data)
		dwTotalSize = ByteUtil::readUINT32(data)
		vecSendData = STripodData::vectorFromStream(data)
		return onRecv_SendAllTripod(dwPageSize, dwTotalSize, vecSendData)
	end

	#接收处理：返回所有九疑鼎的协助信息
	def _doRecv_SendAllTripodHelper(data)
		dwPageSize = ByteUtil::readUINT32(data)
		dwTotalSize = ByteUtil::readUINT32(data)
		vecSendData = STripodHelp::vectorFromStream(data)
		return onRecv_SendAllTripodHelper(dwPageSize, dwTotalSize, vecSendData)
	end

	#接收处理：返回所有九疑鼎的动态信息
	def _doRecv_SendAllTripodLog(data)
		dwPageSize = ByteUtil::readUINT32(data)
		dwTotalSize = ByteUtil::readUINT32(data)
		vecSendData = STripodLog::vectorFromStream(data)
		return onRecv_SendAllTripodLog(dwPageSize, dwTotalSize, vecSendData)
	end

	#接收处理：平台参数加载返回
	def _doRecv_PlatformParamInfoNotify(data)
		dwCurSize = ByteUtil::readUINT32(data)
		dwTotalSize = ByteUtil::readUINT32(data)
		vecRoleID = ByteUtil::readVecUINT64(data)
		vecPlatformParam = SPlatformParam::vectorFromStream(data)
		return onRecv_PlatformParamInfoNotify(dwCurSize, dwTotalSize, vecRoleID, vecPlatformParam)
	end

	#接收处理：返回请求金船信息
	def _doRecv_SendAllShip(data)
		dwPageSize = ByteUtil::readUINT32(data)
		dwTotalSize = ByteUtil::readUINT32(data)
		vecSendDate = PlayerShip::vectorFromStream(data)
		return onRecv_SendAllShip(dwPageSize, dwTotalSize, vecSendDate)
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

	#返回处理：加载玩家未创角预先充值的仙石信息
	def _doReturn_LoadPrepaid(data)
		retParam = SRetParam_LoadPrepaid.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecPrepaid = SPrepaid::vectorFromStream(data) #(SPrepaid的数组)玩家未创角预先值信息
		retParam.vecPrepaid = vecPrepaid
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LoadPrepaid(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：加载玩家未创角预先充值的仙石信息
	def _onTimeOut_LoadPrepaid(sessionID)
		retParam = SRetParam_LoadPrepaid.new;
		onReturn_LoadPrepaid(2, retParam)
	end

	#返回处理：替换帐号
	def _doReturn_ReplaceUser(data)
		retParam = SRetParam_ReplaceUser.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_ReplaceUser(ret, origParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：替换帐号
	def _onTimeOut_ReplaceUser(sessionID)
		origParam = @sessionMgr.getData(sessionID)
		onReturn_ReplaceUser(2, origParam)
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

	#返回处理：获得邮件列表
	def _doReturn_GetAllMailList(data)
		retParam = SRetParam_GetAllMailList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecMails = SMailDetail::vectorFromStream(data) #(SMailDetail的数组)邮件列表
		retParam.vecMails = vecMails
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAllMailList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获得邮件列表
	def _onTimeOut_GetAllMailList(sessionID)
		retParam = SRetParam_GetAllMailList.new;
		onReturn_GetAllMailList(2, retParam)
	end

	#返回处理：保存邮件
	def _doReturn_SaveMail(data)
		retParam = SRetParam_SaveMail.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readINT8(data) #(INT8)非0表示失败
		retParam.byRet = byRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SaveMail(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：保存邮件
	def _onTimeOut_SaveMail(sessionID)
		retParam = SRetParam_SaveMail.new;
		onReturn_SaveMail(2, retParam)
	end

	#返回处理：删除邮件
	def _doReturn_DeleteMail(data)
		retParam = SRetParam_DeleteMail.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readINT8(data) #(INT8)非0表示失败
		retParam.byRet = byRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_DeleteMail(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：删除邮件
	def _onTimeOut_DeleteMail(sessionID)
		retParam = SRetParam_DeleteMail.new;
		onReturn_DeleteMail(2, retParam)
	end

	#返回处理：保存系统邮件
	def _doReturn_SaveSystemMail(data)
		retParam = SRetParam_SaveSystemMail.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readINT8(data) #(INT8)非0表示失败
		retParam.byRet = byRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SaveSystemMail(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：保存系统邮件
	def _onTimeOut_SaveSystemMail(sessionID)
		retParam = SRetParam_SaveSystemMail.new;
		onReturn_SaveSystemMail(2, retParam)
	end

	#返回处理：更新邮件状态
	def _doReturn_UpdateMailStatus(data)
		retParam = SRetParam_UpdateMailStatus.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readINT8(data) #(INT8)非0表示失败
		retParam.byRet = byRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UpdateMailStatus(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：更新邮件状态
	def _onTimeOut_UpdateMailStatus(sessionID)
		retParam = SRetParam_UpdateMailStatus.new;
		onReturn_UpdateMailStatus(2, retParam)
	end

	#返回处理：删除邮件附件
	def _doReturn_DelMailAttach(data)
		retParam = SRetParam_DelMailAttach.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readINT8(data) #(INT8)非0表示失败
		retParam.byRet = byRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_DelMailAttach(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：删除邮件附件
	def _onTimeOut_DelMailAttach(sessionID)
		retParam = SRetParam_DelMailAttach.new;
		onReturn_DelMailAttach(2, retParam)
	end

	#返回处理：查询玩家奖励状态
	def _doReturn_GetPrizeStatus(data)
		retParam = SRetParam_GetPrizeStatus.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecRet = SWonderPrize2DB::vectorFromStream(data) #(SWonderPrize2DB的数组)查询结果
		retParam.vecRet = vecRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetPrizeStatus(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：查询玩家奖励状态
	def _onTimeOut_GetPrizeStatus(sessionID)
		retParam = SRetParam_GetPrizeStatus.new;
		onReturn_GetPrizeStatus(2, retParam)
	end

	#返回处理：查询所有玩家信息
	def _doReturn_GetAllRoleLevel(data)
		retParam = SRetParam_GetAllRoleLevel.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byTypeRet = ByteUtil::readUINT8(data) #(UINT8)类型
		vecRoleLevel = SRoleLevel::vectorFromStream(data) #(SRoleLevel的数组)返回玩家等级
		retParam.byTypeRet = byTypeRet
		retParam.vecRoleLevel = vecRoleLevel
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAllRoleLevel(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：查询所有玩家信息
	def _onTimeOut_GetAllRoleLevel(sessionID)
		retParam = SRetParam_GetAllRoleLevel.new;
		onReturn_GetAllRoleLevel(2, retParam)
	end

	#返回处理：查询玩家保留信息
	def _doReturn_GetRetain(data)
		retParam = SRetParam_GetRetain.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecRet = SRetain::vectorFromStream(data) #(SRetain的数组)查询结果
		retParam.vecRet = vecRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetRetain(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：查询玩家保留信息
	def _onTimeOut_GetRetain(sessionID)
		retParam = SRetParam_GetRetain.new;
		onReturn_GetRetain(2, retParam)
	end

	#返回处理：请求系统Var数据
	def _doReturn_GetGameVar(data)
		retParam = SRetParam_GetGameVar.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecVar = SGameVarsDBInfo::vectorFromStream(data) #(SGameVarsDBInfo的数组)返回的Var
		retParam.vecVar = vecVar
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetGameVar(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求系统Var数据
	def _onTimeOut_GetGameVar(sessionID)
		retParam = SRetParam_GetGameVar.new;
		onReturn_GetGameVar(2, retParam)
	end

	#返回处理：根据玩家ID获得竞技基本数据
	def _doReturn_GetArenaFighterByID(data)
		retParam = SRetParam_GetArenaFighterByID.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		stFighter = SArenaFighter::fromStream(data) #(类类型：ArenaGS::SArenaFighter)返回的数据
		retParam.stFighter = stFighter
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetArenaFighterByID(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：根据玩家ID获得竞技基本数据
	def _onTimeOut_GetArenaFighterByID(sessionID)
		retParam = SRetParam_GetArenaFighterByID.new;
		onReturn_GetArenaFighterByID(2, retParam)
	end

	#返回处理：获取镇妖塔信息（启动预加载调用）
	def _doReturn_GetDemonTowerInfo(data)
		retParam = SRetParam_GetDemonTowerInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecDemonTowerPlayer = SDemonTowerPlayer::vectorFromStream(data) #(SDemonTowerPlayer的数组)镇妖塔玩家信息
		retParam.vecDemonTowerPlayer = vecDemonTowerPlayer
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetDemonTowerInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取镇妖塔信息（启动预加载调用）
	def _onTimeOut_GetDemonTowerInfo(sessionID)
		retParam = SRetParam_GetDemonTowerInfo.new;
		onReturn_GetDemonTowerInfo(2, retParam)
	end

	#返回处理：获取中心服数据
	def _doReturn_GetCenterData(data)
		retParam = SRetParam_GetCenterData.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecCenterData = SCenterData::vectorFromStream(data) #(SCenterData的数组)中心服数据
		retParam.vecCenterData = vecCenterData
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetCenterData(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取中心服数据
	def _onTimeOut_GetCenterData(sessionID)
		retParam = SRetParam_GetCenterData.new;
		onReturn_GetCenterData(2, retParam)
	end

	#返回处理：查看玩家私聊信息
	def _doReturn_GetWhisperInfo(data)
		retParam = SRetParam_GetWhisperInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		whisperInfo = SWhisperInfo::fromStream(data) #(类类型：GlobalChatProt::SWhisperInfo)返回的数据
		retParam.whisperInfo = whisperInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetWhisperInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：查看玩家私聊信息
	def _onTimeOut_GetWhisperInfo(sessionID)
		retParam = SRetParam_GetWhisperInfo.new;
		onReturn_GetWhisperInfo(2, retParam)
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

	#返回处理：获取天元神兽信息（启动预加载调用）
	def _doReturn_GetGodMonsterInfo(data)
		retParam = SRetParam_GetGodMonsterInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecUser = SGuildUser2DB::vectorFromStream(data) #(SGuildUser2DB的数组)天元神兽玩家信息
		retParam.vecUser = vecUser
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetGodMonsterInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取天元神兽信息（启动预加载调用）
	def _onTimeOut_GetGodMonsterInfo(sessionID)
		retParam = SRetParam_GetGodMonsterInfo.new;
		onReturn_GetGodMonsterInfo(2, retParam)
	end

	#返回处理：获取天元神兽玩家限购礼包信息（启动预加载调用）
	def _doReturn_GetLimitPrizeInfo(data)
		retParam = SRetParam_GetLimitPrizeInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecLimitPrize = SLimitPrize2DB::vectorFromStream(data) #(SLimitPrize2DB的数组)数据
		retParam.vecLimitPrize = vecLimitPrize
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetLimitPrizeInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取天元神兽玩家限购礼包信息（启动预加载调用）
	def _onTimeOut_GetLimitPrizeInfo(sessionID)
		retParam = SRetParam_GetLimitPrizeInfo.new;
		onReturn_GetLimitPrizeInfo(2, retParam)
	end

	#返回处理：运营活动中心操作（启动预加载调用）
	def _doReturn_GetActivityCenterInfo(data)
		retParam = SRetParam_GetActivityCenterInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecActOpt = SActivityOpt::vectorFromStream(data) #(SActivityOpt的数组)数据
		retParam.vecActOpt = vecActOpt
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetActivityCenterInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：运营活动中心操作（启动预加载调用）
	def _onTimeOut_GetActivityCenterInfo(sessionID)
		retParam = SRetParam_GetActivityCenterInfo.new;
		onReturn_GetActivityCenterInfo(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 31;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_SendResult2Cent' #FuncID: 1
		@recvFuncList[1] = '_doRecv_SendAllUserIDAndName' #FuncID: 2
		@recvFuncList[2] = '_doRecv_SendAllNotice' #FuncID: 3
		@recvFuncList[3] = '_doRecv_SendAllArena' #FuncID: 4
		@recvFuncList[4] = '_doRecv_SendAllRobot' #FuncID: 5
		@recvFuncList[5] = '_doRecv_RankInitNotify' #FuncID: 6
		@recvFuncList[6] = '_doRecv_AdoreInitNotify' #FuncID: 7
		@recvFuncList[7] = '_doRecv_SendAllTripod' #FuncID: 8
		@recvFuncList[8] = '_doRecv_SendAllTripodHelper' #FuncID: 9
		@recvFuncList[9] = '_doRecv_SendAllTripodLog' #FuncID: 10
		@recvFuncList[10] = '_doRecv_PlatformParamInfoNotify' #FuncID: 11
		@recvFuncList[11] = '_doRecv_SendAllShip' #FuncID: 12

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetStatus' #FuncID: 1
		@retFuncList[1] = '_doReturn_LoadPrepaid' #FuncID: 2
		@retFuncList[2] = '_doReturn_ReplaceUser' #FuncID: 3
		@retFuncList[3] = '_doReturn_LoadOffLineUserData' #FuncID: 4
		@retFuncList[4] = '_doReturn_GetUserIDFromName' #FuncID: 5
		@retFuncList[5] = '_doReturn_GetAllMailList' #FuncID: 6
		@retFuncList[6] = '_doReturn_SaveMail' #FuncID: 7
		@retFuncList[7] = '_doReturn_DeleteMail' #FuncID: 8
		@retFuncList[8] = '_doReturn_SaveSystemMail' #FuncID: 9
		@retFuncList[9] = '_doReturn_UpdateMailStatus' #FuncID: 10
		@retFuncList[10] = '_doReturn_DelMailAttach' #FuncID: 11
		@retFuncList[11] = '_doReturn_GetPrizeStatus' #FuncID: 12
		@retFuncList[12] = '_doReturn_GetAllRoleLevel' #FuncID: 13
		@retFuncList[13] = '_doReturn_GetRetain' #FuncID: 14
		@retFuncList[14] = '_doReturn_GetGameVar' #FuncID: 15
		@retFuncList[15] = '_doReturn_GetArenaFighterByID' #FuncID: 16
		@retFuncList[16] = '_doReturn_GetDemonTowerInfo' #FuncID: 17
		@retFuncList[17] = '_doReturn_GetCenterData' #FuncID: 18
		@retFuncList[18] = '_doReturn_GetWhisperInfo' #FuncID: 19
		@retFuncList[19] = '_doReturn_GetBattleReport' #FuncID: 20
		@retFuncList[20] = '_doReturn_AddBattleReport' #FuncID: 21
		@retFuncList[21] = '_doReturn_GetGodMonsterInfo' #FuncID: 22
		@retFuncList[22] = '_doReturn_GetLimitPrizeInfo' #FuncID: 23
		@retFuncList[23] = '_doReturn_GetActivityCenterInfo' #FuncID: 24

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetStatus' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_LoadPrepaid' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_ReplaceUser' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_LoadOffLineUserData' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_GetUserIDFromName' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_GetAllMailList' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_SaveMail' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_DeleteMail' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_SaveSystemMail' #FuncID: 9
		@timeFuncList[9] = '_onTimeOut_UpdateMailStatus' #FuncID: 10
		@timeFuncList[10] = '_onTimeOut_DelMailAttach' #FuncID: 11
		@timeFuncList[11] = '_onTimeOut_GetPrizeStatus' #FuncID: 12
		@timeFuncList[12] = '_onTimeOut_GetAllRoleLevel' #FuncID: 13
		@timeFuncList[13] = '_onTimeOut_GetRetain' #FuncID: 14
		@timeFuncList[14] = '_onTimeOut_GetGameVar' #FuncID: 15
		@timeFuncList[15] = '_onTimeOut_GetArenaFighterByID' #FuncID: 16
		@timeFuncList[16] = '_onTimeOut_GetDemonTowerInfo' #FuncID: 17
		@timeFuncList[17] = '_onTimeOut_GetCenterData' #FuncID: 18
		@timeFuncList[18] = '_onTimeOut_GetWhisperInfo' #FuncID: 19
		@timeFuncList[19] = '_onTimeOut_GetBattleReport' #FuncID: 20
		@timeFuncList[20] = '_onTimeOut_AddBattleReport' #FuncID: 21
		@timeFuncList[21] = '_onTimeOut_GetGodMonsterInfo' #FuncID: 22
		@timeFuncList[22] = '_onTimeOut_GetLimitPrizeInfo' #FuncID: 23
		@timeFuncList[23] = '_onTimeOut_GetActivityCenterInfo' #FuncID: 24
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

