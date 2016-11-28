#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    FriendProt.rb
#  Purpose:      好友相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#好友相关的结果
class EFriendResult
	EFRIENDSUCCESS = 0#成功
	EFRIENDFAILED = 1#失败
	EFRIENDDUPLICATEERR = 2#已经存在
	EFRIENDOTHERDUPLICATEERR = 3#已存在于目标的好友列表
	EFRIENDMAXNUMERR = 4#好友达到上限
	EFRIENDOTHERMAXNUMERR = 5#对方好友达到上限
	EFRIENDOFFLINEERR = 6#对方不在线
	EFRIENDREFUSEERR = 7#对方拒绝
	EFRIENDNOTEXISTERR = 8#目标不存在
	EFRIENDGROUPIDERR = 9#分组ID错误
	EFRIENDONBLACKLIST = 10#对方已在你的黑名单中
	EFRIENDONTARBLACKLIST = 11#对方已把你拉入黑名单
	EFRIENDSIGN = 12#修改签名成功
	EFRIENDSIGNLENERR = 13#签名过长
	EFRIENDMOOD = 14#修改表情成功
	EFRIENDOTHERERR = 15#其他错误
end

#好友组别
class EFriendGroupType
	EGROUPNONE = 0#无
	ECLOSEFRIEND = 1#亲密好友
	ECOMMONFRIEND = 2#普通好友
	EBLACKFRIEND = 3#黑名单
	EGROUPEND = 4#结尾
end

#好友条目
class SFriendDBInfo
	attr_accessor:byGroup #(UINT8)分组ID
	attr_accessor:qwUserID #(UINT64)帐号ID
	attr_accessor:strName #(string)名字 XXX: 如果主将改名需要修改此处
	attr_accessor:wFighterID #(UINT16)主将ID
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:wMood #(UINT16)心情表情
	attr_accessor:byVIPLevel #(UINT8)VIP等级
	attr_accessor:strSign #(string)签名
	attr_accessor:byColor #(UINT8)好友颜色

	#构造函数
	def initialize
		@byGroup = 0
		@qwUserID = 0
		@strName = ''
		@wFighterID = 0
		@byLevel = 0
		@wMood = 0
		@byVIPLevel = 0
		@strSign = ''
		@byColor = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byGroup = @byGroup
		obj.qwUserID = @qwUserID
		obj.strName = @strName
		obj.wFighterID = @wFighterID
		obj.byLevel = @byLevel
		obj.wMood = @wMood
		obj.byVIPLevel = @byVIPLevel
		obj.strSign = @strSign
		obj.byColor = @byColor
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFriendDBInfo.new
		s.byGroup = ByteUtil::readUINT8(data)
		s.qwUserID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.wFighterID = ByteUtil::readUINT16(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.wMood = ByteUtil::readUINT16(data)
		s.byVIPLevel = ByteUtil::readUINT8(data)
		s.strSign = ByteUtil::readSTRING(data)
		s.byColor = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFriendDBInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byGroup)
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT16(data, @wMood)
		ByteUtil::writeUINT8(data, @byVIPLevel)
		ByteUtil::writeSTRING(data, @strSign)
		ByteUtil::writeUINT8(data, @byColor)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#好友条目
class SFriendEntry
	attr_accessor:eGroupType #(枚举类型：EFriendGroupType)分组ID
	attr_accessor:qwUserID #(UINT64)帐号ID
	attr_accessor:strName #(string)名字 XXX: 如果主将改名需要修改此处
	attr_accessor:wFighterID #(UINT16)主将ID
	attr_accessor:eSex #(枚类型：ProtoCommon::ESexType)性别
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:byVIPLevel #(UINT8)VIP等级
	attr_accessor:byColor #(UINT8)好友颜色
	attr_accessor:wMood #(UINT16)心情表情
	attr_accessor:strSign #(string)签名
	attr_accessor:dwTotalRecharge #(UINT32)总充值
	attr_accessor:bOnlineStatus #(bool)在线状态
	attr_accessor:vecPlatforms #(SPlatformParam的数组)平台信息

	#构造函数
	def initialize
		@eGroupType = 0
		@qwUserID = 0
		@strName = ''
		@wFighterID = 0
		@eSex = 0
		@byLevel = 0
		@byVIPLevel = 0
		@byColor = 0
		@wMood = 0
		@strSign = ''
		@dwTotalRecharge = 0
		@bOnlineStatus = false
		@vecPlatforms = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eGroupType = @eGroupType
		obj.qwUserID = @qwUserID
		obj.strName = @strName
		obj.wFighterID = @wFighterID
		obj.eSex = @eSex
		obj.byLevel = @byLevel
		obj.byVIPLevel = @byVIPLevel
		obj.byColor = @byColor
		obj.wMood = @wMood
		obj.strSign = @strSign
		obj.dwTotalRecharge = @dwTotalRecharge
		obj.bOnlineStatus = @bOnlineStatus
		obj.vecPlatforms = @vecPlatforms
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFriendEntry.new
		s.eGroupType = ByteUtil::readUINT8(data)
		s.qwUserID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.wFighterID = ByteUtil::readUINT16(data)
		s.eSex = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.byVIPLevel = ByteUtil::readUINT8(data)
		s.byColor = ByteUtil::readUINT8(data)
		s.wMood = ByteUtil::readUINT16(data)
		s.strSign = ByteUtil::readSTRING(data)
		s.dwTotalRecharge = ByteUtil::readUINT32(data)
		s.bOnlineStatus = ByteUtil::readBOOL(data)
		s.vecPlatforms = SPlatformParam::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFriendEntry::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eGroupType)
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT8(data, @eSex)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT8(data, @byVIPLevel)
		ByteUtil::writeUINT8(data, @byColor)
		ByteUtil::writeUINT16(data, @wMood)
		ByteUtil::writeSTRING(data, @strSign)
		ByteUtil::writeUINT32(data, @dwTotalRecharge)
		ByteUtil::writeBOOL(data, @bOnlineStatus)
		SPlatformParam::vectorToStream(data, @vecPlatforms)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#好友
class SFriend
	attr_accessor:wMood #(UINT16)我的心情表情
	attr_accessor:strSign #(string)我的签名
	attr_accessor:vecFriendEntry #(SFriendEntry的数组)好友列表

	#构造函数
	def initialize
		@wMood = 0
		@strSign = ''
		@vecFriendEntry = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wMood = @wMood
		obj.strSign = @strSign
		obj.vecFriendEntry = @vecFriendEntry
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFriend.new
		s.wMood = ByteUtil::readUINT16(data)
		s.strSign = ByteUtil::readSTRING(data)
		s.vecFriendEntry = SFriendEntry::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFriend::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wMood)
		ByteUtil::writeSTRING(data, @strSign)
		SFriendEntry::vectorToStream(data, @vecFriendEntry)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#推荐好友
class SreferFriend
	attr_accessor:qwUserID #(UINT64)帐号ID
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:wHeroID #(UINT16)主将ID
	attr_accessor:strName #(string)用户名称

	#构造函数
	def initialize
		@qwUserID = 0
		@byLevel = 0
		@wHeroID = 0
		@strName = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwUserID = @qwUserID
		obj.byLevel = @byLevel
		obj.wHeroID = @wHeroID
		obj.strName = @strName
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SreferFriend.new
		s.qwUserID = ByteUtil::readUINT64(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.wHeroID = ByteUtil::readUINT16(data)
		s.strName = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SreferFriend::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT16(data, @wHeroID)
		ByteUtil::writeSTRING(data, @strName)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[MoveFriend:移动好友]的原来的参数组成的结构体
class SOrigParam_MoveFriend
	attr_accessor:qwUserID #(UINT64)帐号ID
	attr_accessor:eGroupType #(枚举类型：EFriendGroupType)分组ID

	#构造函数
	def initialize
		@qwUserID = 0
		@eGroupType = 0
	end
end

#函数[MoveFriend:移动好友]的返回的参数组成的结构体
class SRetParam_MoveFriend
	attr_accessor:eResult#(枚举类型：EFriendResult)移动好友的结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[FindReferFriendReq:获取推荐好友]的返回的参数组成的结构体
class SRetParam_FindReferFriendReq
	attr_accessor:vecReferFriend#(SreferFriend的数组)推荐好友

	#构造函数
	def initialize
		@vecReferFriend = Array.new
	end
end

#函数[SetSign:修改签名]的返回的参数组成的结构体
class SRetParam_SetSign
	attr_accessor:eResult#(枚举类型：EFriendResult)修改签名结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[SetMood:设置心情表情]的返回的参数组成的结构体
class SRetParam_SetMood
	attr_accessor:eResult#(枚举类型：EFriendResult)修改心情表情结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：好友相关协议
class FriendProtBase < ProtocolBase
	#以下为发送函数
	#发送：增加好友/黑名单请求
	def send_AddFriendReq1(
		eGroupType,  #(枚举类型：EFriendGroupType)组别
		vecUserID,  #(UINT64数组)玩家ID
		byNeedRet #(UINT8)0-不需要返回消息 1-需要返回消息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eGroupType)
		ByteUtil::writeVecUINT64(data, vecUserID)
		ByteUtil::writeUINT8(data, byNeedRet)
		return @svrHandler.sendPacket(data)
	end

	#发送：增加好友/黑名单请求
	def send_AddFriendReq2(
		eGroupType,  #(枚举类型：EFriendGroupType)组别
		strName,  #(string)用户名
		byNeedRet #(UINT8)0-不需要返回消息 1-需要返回消息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eGroupType)
		ByteUtil::writeSTRING(data, strName)
		ByteUtil::writeUINT8(data, byNeedRet)
		return @svrHandler.sendPacket(data)
	end

	#发送：回答增加好友
	def send_AnswerAddFriend(
		bAgree,  #(bool)是否同意
		qwUserID #(UINT64)帐号ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeBOOL(data, bAgree)
		ByteUtil::writeUINT64(data, qwUserID)
		return @svrHandler.sendPacket(data)
	end

	#发送：删除好友/黑名单
	def send_RemoveFriendReq(
		vecUserID #(UINT64数组)玩家ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeVecUINT64(data, vecUserID)
		return @svrHandler.sendPacket(data)
	end

	#发送：移动好友
	def send_MoveFriend(
		qwUserID,  #(UINT64)帐号ID
		eGroupType #(枚举类型：EFriendGroupType)分组ID
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		origParam = SOrigParam_MoveFriend.new
		origParam.qwUserID = qwUserID
		origParam.eGroupType = eGroupType
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeUINT8(data, eGroupType)
		return @svrHandler.sendPacket(data)
	end

	#发送：私聊
	def send_Whisper(
		qwUserID #(UINT64)帐号ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUserID)
		return @svrHandler.sendPacket(data)
	end

	#发送：查询玩家
	def send_FindUserIDNameReq(
		qwUserID,  #(UINT64)帐号ID
		strRoleName #(string)主角色名
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUserID)
		ByteUtil::writeSTRING(data, strRoleName)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取推荐好友
	def send_FindReferFriendReq(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：取得所有好友信息
	def send_GetFriendInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：修改签名
	def send_SetSign(
		strSign #(string)签名文字：最多不超过255个字符
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeSTRING(data, strSign)
		return @svrHandler.sendPacket(data)
	end

	#发送：设置心情表情
	def send_SetMood(
		wMood #(UINT16)心情表情
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wMood)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：询问增加好友
	def onRecv_AskAddFriend(
		strRoleName, #(string)角色名字
		qwUserID, #(UINT64)帐号ID
		wFighterID, #(UINT16)主将ID
		eSex, #(枚类型：ProtoCommon::ESexType)性别
		byLevel #(UINT8)等级
	)
		raise NotImplementedError
	end
	#接收：增加好友/黑名单回应
	def onRecv_AddFriendAck(
		eResult, #(枚举类型：EFriendResult)增加好友的结果
		strName, #(string)名字 XXX: 如果主将改名需要修改此处
		eSex #(枚类型：ProtoCommon::ESexType)性别
	)
		raise NotImplementedError
	end
	#接收：增加好友/黑名单回应Ex
	def onRecv_AddFriendAckEx(
		rFriendEntry #(类类型：SFriendEntry)增加的好友
	)
		raise NotImplementedError
	end
	#接收：删除好友/黑名单回应
	def onRecv_RemoveFriendAck(
		eResult, #(枚举类型：EFriendResult)删除好友的结果
		qwUserID #(UINT64)删除的好友帐号ID
	)
		raise NotImplementedError
	end
	#接收：私聊失败通知
	def onRecv_WhisperFailNotify(
		eResult #(枚举类型：EFriendResult)私聊通知的结果，成功不通知
	)
		raise NotImplementedError
	end
	#接收：私聊成功通知
	def onRecv_WhisperSuccessNotify(
		qwUserID, #(UINT64)帐号ID
		strBaseInfo #(string)聊天基本信息
	)
		raise NotImplementedError
	end
	#接收：好友信息通知
	def onRecv_FriendInfoNotify(
		rFriend #(类类型：SFriend)好友信息
	)
		raise NotImplementedError
	end
	#接收：状态通知
	def onRecv_OnlineStatusNotify(
		qwUserID, #(UINT64)帐号ID
		bOnlineStatus #(bool)在线状态
	)
		raise NotImplementedError
	end
	#接收：等级变化通知
	def onRecv_LevelChangeNotify(
		qwUserID, #(UINT64)帐号ID
		byLevel #(UINT8)当前等级
	)
		raise NotImplementedError
	end
	#接收：VIP变化通知
	def onRecv_VIPChangeNotify(
		qwUserID, #(UINT64)帐号ID
		byLevel #(UINT8)当前等级
	)
		raise NotImplementedError
	end
	#接收：品质变化通知
	def onRecv_ColorChangeNotify(
		qwUserID, #(UINT64)帐号ID
		byColor #(UINT8)当前品质
	)
		raise NotImplementedError
	end
	#接收：QQ黄钻好友通知
	def onRecv_YellowDiamondNotify(
		qwUserID, #(UINT64)帐号ID
		byLevel, #(UINT8)等级
		bYearlyPay #(bool)是否年费黄钻
	)
		raise NotImplementedError
	end
	#接收：签名改变通知
	def onRecv_SignChangeNotify(
		qwUserID, #(UINT64)帐号ID
		strSign #(string)签名
	)
		raise NotImplementedError
	end
	#接收：签名改变通知
	def onRecv_MoodChangeNotify(
		qwUserID, #(UINT64)帐号ID
		wMood #(UINT16)心情表情
	)
		raise NotImplementedError
	end
	#接收：签名改变通知
	def onRecv_VIPLevelChangeNotify(
		qwUserID, #(UINT64)帐号ID
		byVIPLevel #(UINT8)VIP等级
	)
		raise NotImplementedError
	end
	#接收：角色查询
	def onRecv_FindUserIDNameAck(
		eResult, #(枚举类型：EFriendResult)查询返回
		qwUserID, #(UINT64)帐号ID
		strRoleName, #(string)主角色名
		wHeroID, #(UINT16)主将ID
		byLevel, #(UINT8)用户等级
		bOnlineStatus #(bool)在线状态
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：移动好友
	def onReturn_MoveFriend(
		ret, #0为成功，1为失败，2为超时
		origParam, #(类类型：SOrigParam_MoveFriend)原来的参数
		retParam #(类类型：SRetParam_MoveFriend)返回的参数
	)
	end

	#返回：获取推荐好友
	def onReturn_FindReferFriendReq(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FindReferFriendReq)返回的参数
	)
	end

	#返回：修改签名
	def onReturn_SetSign(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SetSign)返回的参数
	)
	end

	#返回：设置心情表情
	def onReturn_SetMood(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SetMood)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：询问增加好友
	def _doRecv_AskAddFriend(data)
		strRoleName = ByteUtil::readSTRING(data)
		qwUserID = ByteUtil::readUINT64(data)
		wFighterID = ByteUtil::readUINT16(data)
		eSex = ByteUtil::readUINT8(data)
		byLevel = ByteUtil::readUINT8(data)
		return onRecv_AskAddFriend(strRoleName, qwUserID, wFighterID, eSex, byLevel)
	end

	#接收处理：增加好友/黑名单回应
	def _doRecv_AddFriendAck(data)
		eResult = ByteUtil::readUINT8(data)
		strName = ByteUtil::readSTRING(data)
		eSex = ByteUtil::readUINT8(data)
		return onRecv_AddFriendAck(eResult, strName, eSex)
	end

	#接收处理：增加好友/黑名单回应Ex
	def _doRecv_AddFriendAckEx(data)
		rFriendEntry = SFriendEntry::fromStream(data)
		return onRecv_AddFriendAckEx(rFriendEntry)
	end

	#接收处理：删除好友/黑名单回应
	def _doRecv_RemoveFriendAck(data)
		eResult = ByteUtil::readUINT8(data)
		qwUserID = ByteUtil::readUINT64(data)
		return onRecv_RemoveFriendAck(eResult, qwUserID)
	end

	#接收处理：私聊失败通知
	def _doRecv_WhisperFailNotify(data)
		eResult = ByteUtil::readUINT8(data)
		return onRecv_WhisperFailNotify(eResult)
	end

	#接收处理：私聊成功通知
	def _doRecv_WhisperSuccessNotify(data)
		qwUserID = ByteUtil::readUINT64(data)
		strBaseInfo = ByteUtil::readSTRING(data)
		return onRecv_WhisperSuccessNotify(qwUserID, strBaseInfo)
	end

	#接收处理：好友信息通知
	def _doRecv_FriendInfoNotify(data)
		rFriend = SFriend::fromStream(data)
		return onRecv_FriendInfoNotify(rFriend)
	end

	#接收处理：状态通知
	def _doRecv_OnlineStatusNotify(data)
		qwUserID = ByteUtil::readUINT64(data)
		bOnlineStatus = ByteUtil::readBOOL(data)
		return onRecv_OnlineStatusNotify(qwUserID, bOnlineStatus)
	end

	#接收处理：等级变化通知
	def _doRecv_LevelChangeNotify(data)
		qwUserID = ByteUtil::readUINT64(data)
		byLevel = ByteUtil::readUINT8(data)
		return onRecv_LevelChangeNotify(qwUserID, byLevel)
	end

	#接收处理：VIP变化通知
	def _doRecv_VIPChangeNotify(data)
		qwUserID = ByteUtil::readUINT64(data)
		byLevel = ByteUtil::readUINT8(data)
		return onRecv_VIPChangeNotify(qwUserID, byLevel)
	end

	#接收处理：品质变化通知
	def _doRecv_ColorChangeNotify(data)
		qwUserID = ByteUtil::readUINT64(data)
		byColor = ByteUtil::readUINT8(data)
		return onRecv_ColorChangeNotify(qwUserID, byColor)
	end

	#接收处理：QQ黄钻好友通知
	def _doRecv_YellowDiamondNotify(data)
		qwUserID = ByteUtil::readUINT64(data)
		byLevel = ByteUtil::readUINT8(data)
		bYearlyPay = ByteUtil::readBOOL(data)
		return onRecv_YellowDiamondNotify(qwUserID, byLevel, bYearlyPay)
	end

	#接收处理：签名改变通知
	def _doRecv_SignChangeNotify(data)
		qwUserID = ByteUtil::readUINT64(data)
		strSign = ByteUtil::readSTRING(data)
		return onRecv_SignChangeNotify(qwUserID, strSign)
	end

	#接收处理：签名改变通知
	def _doRecv_MoodChangeNotify(data)
		qwUserID = ByteUtil::readUINT64(data)
		wMood = ByteUtil::readUINT16(data)
		return onRecv_MoodChangeNotify(qwUserID, wMood)
	end

	#接收处理：签名改变通知
	def _doRecv_VIPLevelChangeNotify(data)
		qwUserID = ByteUtil::readUINT64(data)
		byVIPLevel = ByteUtil::readUINT8(data)
		return onRecv_VIPLevelChangeNotify(qwUserID, byVIPLevel)
	end

	#接收处理：角色查询
	def _doRecv_FindUserIDNameAck(data)
		eResult = ByteUtil::readUINT8(data)
		qwUserID = ByteUtil::readUINT64(data)
		strRoleName = ByteUtil::readSTRING(data)
		wHeroID = ByteUtil::readUINT16(data)
		byLevel = ByteUtil::readUINT8(data)
		bOnlineStatus = ByteUtil::readBOOL(data)
		return onRecv_FindUserIDNameAck(eResult, qwUserID, strRoleName, wHeroID, byLevel, bOnlineStatus)
	end

#以下为返回处理函数
	#返回处理：移动好友
	def _doReturn_MoveFriend(data)
		retParam = SRetParam_MoveFriend.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EFriendResult)移动好友的结果
		retParam.eResult = eResult
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_MoveFriend(ret, origParam, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：移动好友
	def _onTimeOut_MoveFriend(sessionID)
		retParam = SRetParam_MoveFriend.new;
		origParam = @sessionMgr.getData(sessionID)
		onReturn_MoveFriend(2, origParam, retParam)
	end

	#返回处理：获取推荐好友
	def _doReturn_FindReferFriendReq(data)
		retParam = SRetParam_FindReferFriendReq.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecReferFriend = SreferFriend::vectorFromStream(data) #(SreferFriend的数组)推荐好友
		retParam.vecReferFriend = vecReferFriend
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FindReferFriendReq(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取推荐好友
	def _onTimeOut_FindReferFriendReq(sessionID)
		retParam = SRetParam_FindReferFriendReq.new;
		onReturn_FindReferFriendReq(2, retParam)
	end

	#返回处理：修改签名
	def _doReturn_SetSign(data)
		retParam = SRetParam_SetSign.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EFriendResult)修改签名结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SetSign(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：修改签名
	def _onTimeOut_SetSign(sessionID)
		retParam = SRetParam_SetSign.new;
		onReturn_SetSign(2, retParam)
	end

	#返回处理：设置心情表情
	def _doReturn_SetMood(data)
		retParam = SRetParam_SetMood.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EFriendResult)修改心情表情结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SetMood(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：设置心情表情
	def _onTimeOut_SetMood(sessionID)
		retParam = SRetParam_SetMood.new;
		onReturn_SetMood(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 24;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_AskAddFriend' #FuncID: 1
		@recvFuncList[1] = '_doRecv_AddFriendAck' #FuncID: 2
		@recvFuncList[2] = '_doRecv_AddFriendAckEx' #FuncID: 3
		@recvFuncList[3] = '_doRecv_RemoveFriendAck' #FuncID: 4
		@recvFuncList[4] = '_doRecv_WhisperFailNotify' #FuncID: 5
		@recvFuncList[5] = '_doRecv_WhisperSuccessNotify' #FuncID: 6
		@recvFuncList[6] = '_doRecv_FriendInfoNotify' #FuncID: 7
		@recvFuncList[7] = '_doRecv_OnlineStatusNotify' #FuncID: 8
		@recvFuncList[8] = '_doRecv_LevelChangeNotify' #FuncID: 9
		@recvFuncList[9] = '_doRecv_VIPChangeNotify' #FuncID: 10
		@recvFuncList[10] = '_doRecv_ColorChangeNotify' #FuncID: 11
		@recvFuncList[11] = '_doRecv_YellowDiamondNotify' #FuncID: 12
		@recvFuncList[12] = '_doRecv_SignChangeNotify' #FuncID: 13
		@recvFuncList[13] = '_doRecv_MoodChangeNotify' #FuncID: 14
		@recvFuncList[14] = '_doRecv_VIPLevelChangeNotify' #FuncID: 15
		@recvFuncList[15] = '_doRecv_FindUserIDNameAck' #FuncID: 16

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_MoveFriend' #FuncID: 1
		@retFuncList[1] = '_doReturn_FindReferFriendReq' #FuncID: 2
		@retFuncList[2] = '_doReturn_SetSign' #FuncID: 3
		@retFuncList[3] = '_doReturn_SetMood' #FuncID: 4

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_MoveFriend' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_FindReferFriendReq' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_SetSign' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_SetMood' #FuncID: 4
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

