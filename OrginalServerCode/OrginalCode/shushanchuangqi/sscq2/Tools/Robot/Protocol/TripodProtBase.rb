#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    TripodProt.rb
#  Purpose:      九疑鼎相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ArenaGSBase.rb'
require_relative './ItemProtBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#九疑鼎操作结果
class ETripodType
	ETRIPODSUCC = 0#成功
	ETRIPODFAILED = 1#失败
	ETRIPODCONDIDERR = 2#激活条件不足
	ETRIPODITEMERR = 3#道具不足
	ETRIPODNOTFIRE = 4#未祈火
	ETRIPODNOENOUGHCNT = 5#剩余祈火次数不足
	ETRIPODYUANQINOTFULL = 6#元气值未满
	ETRIPODYUANQIFULL = 7#元气值已满
	ETRIPODNOTTIME = 8#时间未到
	ETRIPODSHANFENGFULL = 9#扇风次数已满
	ETRIPODHELPTIMESFULL = 10#协助次数已满
	ETRIPODNOTHELP = 11#不能协助
end

#九疑鼎日志类型
class ETripodLogType
	ETRIPODLOGNONE = 0#无效日志类型
	ETRIPODLOGHELP = 1#成员日志
	ETRIPODLOGMAX = 2#日志类型最大值
end

#玩家的九疑鼎数据
class STripodInfo
	attr_accessor:byTripodID #(UINT8)九疑鼎ID
	attr_accessor:byLevel #(UINT8)九疑鼎等级
	attr_accessor:dwExp #(UINT32)九疑鼎当前经验值
	attr_accessor:wFireID #(UINT16)火种ID
	attr_accessor:byFireLvl #(UINT8)火种等级(品质)
	attr_accessor:dwStartTime #(UINT32)上一次结算时间
	attr_accessor:dwShanfengTime #(UINT32)上一次扇风时间(为0未扇风)
	attr_accessor:dwSoul #(UINT32)当前已结算的总元气值
	attr_accessor:dwLine #(UINT32)产物加成系数（万分比）

	#构造函数
	def initialize
		@byTripodID = 0
		@byLevel = 0
		@dwExp = 0
		@wFireID = 0
		@byFireLvl = 0
		@dwStartTime = 0
		@dwShanfengTime = 0
		@dwSoul = 0
		@dwLine = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byTripodID = @byTripodID
		obj.byLevel = @byLevel
		obj.dwExp = @dwExp
		obj.wFireID = @wFireID
		obj.byFireLvl = @byFireLvl
		obj.dwStartTime = @dwStartTime
		obj.dwShanfengTime = @dwShanfengTime
		obj.dwSoul = @dwSoul
		obj.dwLine = @dwLine
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STripodInfo.new
		s.byTripodID = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.dwExp = ByteUtil::readUINT32(data)
		s.wFireID = ByteUtil::readUINT16(data)
		s.byFireLvl = ByteUtil::readUINT8(data)
		s.dwStartTime = ByteUtil::readUINT32(data)
		s.dwShanfengTime = ByteUtil::readUINT32(data)
		s.dwSoul = ByteUtil::readUINT32(data)
		s.dwLine = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STripodInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byTripodID)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwExp)
		ByteUtil::writeUINT16(data, @wFireID)
		ByteUtil::writeUINT8(data, @byFireLvl)
		ByteUtil::writeUINT32(data, @dwStartTime)
		ByteUtil::writeUINT32(data, @dwShanfengTime)
		ByteUtil::writeUINT32(data, @dwSoul)
		ByteUtil::writeUINT32(data, @dwLine)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#九疑鼎散仙协助
class SFighterHelpInfo
	attr_accessor:wFighterID #(UINT16)散仙ID
	attr_accessor:byPos #(UINT8)协助位置(0,1)
	attr_accessor:byColor #(UINT8)散仙协助时的品质
	attr_accessor:dwStartTime #(UINT32)开始协助的时间

	#构造函数
	def initialize
		@wFighterID = 0
		@byPos = 0
		@byColor = 0
		@dwStartTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wFighterID = @wFighterID
		obj.byPos = @byPos
		obj.byColor = @byColor
		obj.dwStartTime = @dwStartTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFighterHelpInfo.new
		s.wFighterID = ByteUtil::readUINT16(data)
		s.byPos = ByteUtil::readUINT8(data)
		s.byColor = ByteUtil::readUINT8(data)
		s.dwStartTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFighterHelpInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT8(data, @byPos)
		ByteUtil::writeUINT8(data, @byColor)
		ByteUtil::writeUINT32(data, @dwStartTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#九疑鼎玩家协助
class SPlayerHelpInfo
	attr_accessor:qwRoleID #(UINT64)协助者(玩家)ID
	attr_accessor:byPos #(UINT8)协助位置(0,1,2)
	attr_accessor:byLevel #(UINT8)玩家协助时的等级
	attr_accessor:dwStartTime #(UINT32)开始协助的时间
	attr_accessor:stPlayer #(类类型：ArenaGS::SArenaFighter)玩家的基础信息(外观)
	attr_accessor:vecPlatforms #(SPlatformParam的数组)平台信息

	#构造函数
	def initialize
		@qwRoleID = 0
		@byPos = 0
		@byLevel = 0
		@dwStartTime = 0
		@stPlayer = SArenaFighter.new
		@vecPlatforms = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.byPos = @byPos
		obj.byLevel = @byLevel
		obj.dwStartTime = @dwStartTime
		obj.stPlayer = @stPlayer
		obj.vecPlatforms = @vecPlatforms
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPlayerHelpInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.byPos = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.dwStartTime = ByteUtil::readUINT32(data)
		s.stPlayer = SArenaFighter::fromStream(data)
		s.vecPlatforms = SPlatformParam::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPlayerHelpInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT8(data, @byPos)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwStartTime)
		@stPlayer.toStream(data)
		SPlatformParam::vectorToStream(data, @vecPlatforms)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#九疑鼎的协助信息
class STripodHelp
	attr_accessor:qwRoleID #(UINT64)九疑鼎的所属玩家的ID
	attr_accessor:vecFighterHelp #(SFighterHelpInfo的数组)散仙协助信息
	attr_accessor:vecPlayerHelp #(SPlayerHelpInfo的数组)玩家协助信息

	#构造函数
	def initialize
		@qwRoleID = 0
		@vecFighterHelp = Array.new
		@vecPlayerHelp = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.vecFighterHelp = @vecFighterHelp
		obj.vecPlayerHelp = @vecPlayerHelp
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STripodHelp.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.vecFighterHelp = SFighterHelpInfo::vectorFromStream(data)
		s.vecPlayerHelp = SPlayerHelpInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STripodHelp::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		SFighterHelpInfo::vectorToStream(data, @vecFighterHelp)
		SPlayerHelpInfo::vectorToStream(data, @vecPlayerHelp)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#九疑鼎历史日志
class STripodLog
	attr_accessor:qwRoleID #(UINT64)九疑鼎的所属玩家的ID
	attr_accessor:wMsgID #(UINT16)对应日志ID（详见Message）
	attr_accessor:vecParam #(INT64数组)整型变量
	attr_accessor:vecString #(string数组)字符串型变量
	attr_accessor:dwTime #(UINT32)日志时间

	#构造函数
	def initialize
		@qwRoleID = 0
		@wMsgID = 0
		@vecParam = Array.new
		@vecString = Array.new
		@dwTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wMsgID = @wMsgID
		obj.vecParam = @vecParam
		obj.vecString = @vecString
		obj.dwTime = @dwTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STripodLog.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wMsgID = ByteUtil::readUINT16(data)
		s.vecParam = ByteUtil::readVecINT64(data)
		s.vecString = ByteUtil::readVecSTRING(data)
		s.dwTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STripodLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wMsgID)
		ByteUtil::writeVecINT64(data, @vecParam)
		ByteUtil::writeVecSTRING(data, @vecString)
		ByteUtil::writeUINT32(data, @dwTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家九疑鼎信息
class STripodData
	attr_accessor:qwRoleID #(UINT64)玩家的ID
	attr_accessor:stPlayer #(类类型：ArenaGS::SArenaFighter)九疑鼎所属玩家的基础信息
	attr_accessor:tripodHelpData #(类类型：STripodHelp)玩家九疑鼎的协助数据
	attr_accessor:vecTripods #(STripodInfo的数组)玩家的所有九疑鼎数据
	attr_accessor:vecTripodLog #(STripodLog的数组)九疑鼎日志

	#构造函数
	def initialize
		@qwRoleID = 0
		@stPlayer = SArenaFighter.new
		@tripodHelpData = STripodHelp.new
		@vecTripods = Array.new
		@vecTripodLog = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.stPlayer = @stPlayer
		obj.tripodHelpData = @tripodHelpData
		obj.vecTripods = @vecTripods
		obj.vecTripodLog = @vecTripodLog
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STripodData.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.stPlayer = SArenaFighter::fromStream(data)
		s.tripodHelpData = STripodHelp::fromStream(data)
		s.vecTripods = STripodInfo::vectorFromStream(data)
		s.vecTripodLog = STripodLog::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STripodData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		@stPlayer.toStream(data)
		@tripodHelpData.toStream(data)
		STripodInfo::vectorToStream(data, @vecTripods)
		STripodLog::vectorToStream(data, @vecTripodLog)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家的九疑鼎火种数据
class SFireInfo
	attr_accessor:wFireID #(UINT16)九疑鼎火种ID
	attr_accessor:dwSucceed #(UINT32)火种祈火成功次数
	attr_accessor:dwRemain #(UINT32)火种剩余祈火次数

	#构造函数
	def initialize
		@wFireID = 0
		@dwSucceed = 0
		@dwRemain = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wFireID = @wFireID
		obj.dwSucceed = @dwSucceed
		obj.dwRemain = @dwRemain
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFireInfo.new
		s.wFireID = ByteUtil::readUINT16(data)
		s.dwSucceed = ByteUtil::readUINT32(data)
		s.dwRemain = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFireInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wFireID)
		ByteUtil::writeUINT32(data, @dwSucceed)
		ByteUtil::writeUINT32(data, @dwRemain)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家九疑鼎的扇火、协助状态
class STripodStatus
	attr_accessor:qwRoleID #(UINT64)玩家的ID
	attr_accessor:byShanfengst #(UINT8)是否可以扇火(1是 0否)
	attr_accessor:byHelpst #(UINT8)是否可以协助(1是 0否)

	#构造函数
	def initialize
		@qwRoleID = 0
		@byShanfengst = 0
		@byHelpst = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.byShanfengst = @byShanfengst
		obj.byHelpst = @byHelpst
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STripodStatus.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.byShanfengst = ByteUtil::readUINT8(data)
		s.byHelpst = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STripodStatus::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT8(data, @byShanfengst)
		ByteUtil::writeUINT8(data, @byHelpst)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetAllTripods:取得玩家所有九疑鼎信息]的返回的参数组成的结构体
class SRetParam_GetAllTripods
	attr_accessor:oTripodData#(类类型：STripodData)九疑鼎数据列表
	attr_accessor:byShanfeng#(UINT8)玩家今日已扇风次数
	attr_accessor:byHelpTimes#(UINT8)玩家今日已协助次数(玩家协助)

	#构造函数
	def initialize
		@oTripodData = STripodData.new
		@byShanfeng = 0
		@byHelpTimes = 0
	end
end

#函数[GetAllFires:取得玩家所有九疑鼎的火种信息]的返回的参数组成的结构体
class SRetParam_GetAllFires
	attr_accessor:vecFires#(SFireInfo的数组)九疑鼎信息列表

	#构造函数
	def initialize
		@vecFires = Array.new
	end
end

#函数[GetTripodData:取得其他玩家所有九疑鼎信息]的返回的参数组成的结构体
class SRetParam_GetTripodData
	attr_accessor:oTripodData#(类类型：STripodData)九疑鼎数据列表

	#构造函数
	def initialize
		@oTripodData = STripodData.new
	end
end

#函数[ActiveTripod:激活九疑鼎]的返回的参数组成的结构体
class SRetParam_ActiveTripod
	attr_accessor:byTripodID#(UINT8)九疑鼎ID
	attr_accessor:eResult#(枚举类型：ETripodType)结果

	#构造函数
	def initialize
		@byTripodID = 0
		@eResult = 0
	end
end

#函数[UpgradeTripod:升级九疑鼎]的返回的参数组成的结构体
class SRetParam_UpgradeTripod
	attr_accessor:vecTripods#(STripodInfo的数组)九疑鼎信息列表
	attr_accessor:eResult#(枚举类型：ETripodType)结果

	#构造函数
	def initialize
		@vecTripods = Array.new
		@eResult = 0
	end
end

#函数[MakeFireTripod:九疑鼎祈火(炼丹)]的返回的参数组成的结构体
class SRetParam_MakeFireTripod
	attr_accessor:vecTripods#(STripodInfo的数组)九疑鼎信息列表
	attr_accessor:eResult#(枚举类型：ETripodType)结果

	#构造函数
	def initialize
		@vecTripods = Array.new
		@eResult = 0
	end
end

#函数[ClearFireTripod:清除九疑鼎祈火记录]的返回的参数组成的结构体
class SRetParam_ClearFireTripod
	attr_accessor:byTripodID#(UINT8)九疑鼎ID
	attr_accessor:eResult#(枚举类型：ETripodType)结果

	#构造函数
	def initialize
		@byTripodID = 0
		@eResult = 0
	end
end

#函数[GetTripodAward:获取九疑鼎炼丹果实]的返回的参数组成的结构体
class SRetParam_GetTripodAward
	attr_accessor:vecTripods#(STripodInfo的数组)九疑鼎信息列表
	attr_accessor:eResult#(枚举类型：ETripodType)结果

	#构造函数
	def initialize
		@vecTripods = Array.new
		@eResult = 0
	end
end

#函数[SpeedTripod:加速九疑鼎炼丹(道具入鼎)]的返回的参数组成的结构体
class SRetParam_SpeedTripod
	attr_accessor:vecTripods#(STripodInfo的数组)九疑鼎信息列表
	attr_accessor:eResult#(枚举类型：ETripodType)结果

	#构造函数
	def initialize
		@vecTripods = Array.new
		@eResult = 0
	end
end

#函数[AddTripodExtraSoul:扇火九疑鼎]的返回的参数组成的结构体
class SRetParam_AddTripodExtraSoul
	attr_accessor:vecTripods#(STripodInfo的数组)所属者的九疑鼎信息列表
	attr_accessor:eResult#(枚举类型：ETripodType)结果

	#构造函数
	def initialize
		@vecTripods = Array.new
		@eResult = 0
	end
end

#函数[FighterHelpTripod:散仙协助九疑鼎]的返回的参数组成的结构体
class SRetParam_FighterHelpTripod
	attr_accessor:oFighterHelp#(类类型：SFighterHelpInfo)散仙协助信息
	attr_accessor:eResult#(枚举类型：ETripodType)结果

	#构造函数
	def initialize
		@oFighterHelp = SFighterHelpInfo.new
		@eResult = 0
	end
end

#函数[UserHelpTripod:玩家协助九疑鼎]的返回的参数组成的结构体
class SRetParam_UserHelpTripod
	attr_accessor:oPlayerHelp#(类类型：SPlayerHelpInfo)玩家协助信息
	attr_accessor:eResult#(枚举类型：ETripodType)结果

	#构造函数
	def initialize
		@oPlayerHelp = SPlayerHelpInfo.new
		@eResult = 0
	end
end

#函数[ShotOffHelpTripod:踢出九疑鼎协助者]的返回的参数组成的结构体
class SRetParam_ShotOffHelpTripod
	attr_accessor:eResult#(枚举类型：ETripodType)结果
	attr_accessor:byPos#(UINT8)协助位置(0,1,2)
	attr_accessor:byType#(UINT8)0散仙 1玩家

	#构造函数
	def initialize
		@eResult = 0
		@byPos = 0
		@byType = 0
	end
end

#函数[GetTripodStatus:请求玩家九疑鼎的能被扇火、协助信息]的返回的参数组成的结构体
class SRetParam_GetTripodStatus
	attr_accessor:vecStatus#(STripodStatus的数组)玩家九疑鼎的扇火、协助状态

	#构造函数
	def initialize
		@vecStatus = Array.new
	end
end

#协议类：九疑鼎相关协议
class TripodProtBase < ProtocolBase
	#以下为发送函数
	#发送：取得玩家所有九疑鼎信息
	def send_GetAllTripods(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：取得玩家所有九疑鼎的火种信息
	def send_GetAllFires(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：取得其他玩家所有九疑鼎信息
	def send_GetTripodData(
		qwRoleID #(UINT64)玩家ID(九疑鼎所属者)
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：激活九疑鼎
	def send_ActiveTripod(
		byTripodID #(UINT8)九疑鼎ID
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byTripodID)
		return @svrHandler.sendPacket(data)
	end

	#发送：升级九疑鼎
	def send_UpgradeTripod(
		byTripodID,  #(UINT8)九疑鼎ID
		byOneKey #(UINT8)是否一键
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byTripodID)
		ByteUtil::writeUINT8(data, byOneKey)
		return @svrHandler.sendPacket(data)
	end

	#发送：九疑鼎祈火(炼丹)
	def send_MakeFireTripod(
		byTripodID,  #(UINT8)九疑鼎ID
		wFireID #(UINT16)火种ID
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byTripodID)
		ByteUtil::writeUINT16(data, wFireID)
		return @svrHandler.sendPacket(data)
	end

	#发送：清除九疑鼎祈火记录
	def send_ClearFireTripod(
		byTripodID #(UINT8)九疑鼎ID
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byTripodID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取九疑鼎炼丹果实
	def send_GetTripodAward(
		byTripodID #(UINT8)九疑鼎ID
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byTripodID)
		return @svrHandler.sendPacket(data)
	end

	#发送：加速九疑鼎炼丹(道具入鼎)
	def send_SpeedTripod(
		byTripodID,  #(UINT8)九疑鼎ID
		vecItems #(SItemCount的数组)入鼎道具列表
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byTripodID)
		SItemCount::vectorToStream(data, vecItems)
		return @svrHandler.sendPacket(data)
	end

	#发送：扇火九疑鼎
	def send_AddTripodExtraSoul(
		qwRoleID,  #(UINT64)玩家ID(九疑鼎所属者)
		byTripodID #(UINT8)九疑鼎ID
	)
		sessionID = @sessionMgr.getNewSession(self, 10);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT8(data, byTripodID)
		return @svrHandler.sendPacket(data)
	end

	#发送：散仙协助九疑鼎
	def send_FighterHelpTripod(
		wFighterID,  #(UINT16)自己的散仙ID
		byPos #(UINT8)协助位置
	)
		sessionID = @sessionMgr.getNewSession(self, 11);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wFighterID)
		ByteUtil::writeUINT8(data, byPos)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家协助九疑鼎
	def send_UserHelpTripod(
		qwRoleID,  #(UINT64)对方玩家ID
		byPos #(UINT8)协助位置
	)
		sessionID = @sessionMgr.getNewSession(self, 12);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT8(data, byPos)
		return @svrHandler.sendPacket(data)
	end

	#发送：踢出九疑鼎协助者
	def send_ShotOffHelpTripod(
		byPos,  #(UINT8)协助位置(0,1,2)
		byType #(UINT8)0散仙 1玩家
	)
		sessionID = @sessionMgr.getNewSession(self, 13);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 13
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byPos)
		ByteUtil::writeUINT8(data, byType)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求玩家九疑鼎的能被扇火、协助信息
	def send_GetTripodStatus(
		vecRoleID #(UINT64数组)好友玩家ID列表
	)
		sessionID = @sessionMgr.getNewSession(self, 14);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 14
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeVecUINT64(data, vecRoleID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：更新玩家的九疑鼎数据
	def onRecv_UpdateTripod(
		oTripodData, #(类类型：STripodData)九疑鼎数据列表
		byShanfeng, #(UINT8)玩家今日已扇风次数
		byHelpTimes #(UINT8)玩家今日已协助次数(玩家协助)
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：取得玩家所有九疑鼎信息
	def onReturn_GetAllTripods(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAllTripods)返回的参数
	)
	end

	#返回：取得玩家所有九疑鼎的火种信息
	def onReturn_GetAllFires(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAllFires)返回的参数
	)
	end

	#返回：取得其他玩家所有九疑鼎信息
	def onReturn_GetTripodData(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetTripodData)返回的参数
	)
	end

	#返回：激活九疑鼎
	def onReturn_ActiveTripod(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ActiveTripod)返回的参数
	)
	end

	#返回：升级九疑鼎
	def onReturn_UpgradeTripod(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UpgradeTripod)返回的参数
	)
	end

	#返回：九疑鼎祈火(炼丹)
	def onReturn_MakeFireTripod(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_MakeFireTripod)返回的参数
	)
	end

	#返回：清除九疑鼎祈火记录
	def onReturn_ClearFireTripod(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ClearFireTripod)返回的参数
	)
	end

	#返回：获取九疑鼎炼丹果实
	def onReturn_GetTripodAward(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetTripodAward)返回的参数
	)
	end

	#返回：加速九疑鼎炼丹(道具入鼎)
	def onReturn_SpeedTripod(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SpeedTripod)返回的参数
	)
	end

	#返回：扇火九疑鼎
	def onReturn_AddTripodExtraSoul(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_AddTripodExtraSoul)返回的参数
	)
	end

	#返回：散仙协助九疑鼎
	def onReturn_FighterHelpTripod(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FighterHelpTripod)返回的参数
	)
	end

	#返回：玩家协助九疑鼎
	def onReturn_UserHelpTripod(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UserHelpTripod)返回的参数
	)
	end

	#返回：踢出九疑鼎协助者
	def onReturn_ShotOffHelpTripod(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ShotOffHelpTripod)返回的参数
	)
	end

	#返回：请求玩家九疑鼎的能被扇火、协助信息
	def onReturn_GetTripodStatus(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetTripodStatus)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：更新玩家的九疑鼎数据
	def _doRecv_UpdateTripod(data)
		oTripodData = STripodData::fromStream(data)
		byShanfeng = ByteUtil::readUINT8(data)
		byHelpTimes = ByteUtil::readUINT8(data)
		return onRecv_UpdateTripod(oTripodData, byShanfeng, byHelpTimes)
	end

#以下为返回处理函数
	#返回处理：取得玩家所有九疑鼎信息
	def _doReturn_GetAllTripods(data)
		retParam = SRetParam_GetAllTripods.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		oTripodData = STripodData::fromStream(data) #(类类型：STripodData)九疑鼎数据列表
		byShanfeng = ByteUtil::readUINT8(data) #(UINT8)玩家今日已扇风次数
		byHelpTimes = ByteUtil::readUINT8(data) #(UINT8)玩家今日已协助次数(玩家协助)
		retParam.oTripodData = oTripodData
		retParam.byShanfeng = byShanfeng
		retParam.byHelpTimes = byHelpTimes
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAllTripods(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：取得玩家所有九疑鼎信息
	def _onTimeOut_GetAllTripods(sessionID)
		retParam = SRetParam_GetAllTripods.new;
		onReturn_GetAllTripods(2, retParam)
	end

	#返回处理：取得玩家所有九疑鼎的火种信息
	def _doReturn_GetAllFires(data)
		retParam = SRetParam_GetAllFires.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecFires = SFireInfo::vectorFromStream(data) #(SFireInfo的数组)九疑鼎信息列表
		retParam.vecFires = vecFires
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAllFires(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：取得玩家所有九疑鼎的火种信息
	def _onTimeOut_GetAllFires(sessionID)
		retParam = SRetParam_GetAllFires.new;
		onReturn_GetAllFires(2, retParam)
	end

	#返回处理：取得其他玩家所有九疑鼎信息
	def _doReturn_GetTripodData(data)
		retParam = SRetParam_GetTripodData.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		oTripodData = STripodData::fromStream(data) #(类类型：STripodData)九疑鼎数据列表
		retParam.oTripodData = oTripodData
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetTripodData(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：取得其他玩家所有九疑鼎信息
	def _onTimeOut_GetTripodData(sessionID)
		retParam = SRetParam_GetTripodData.new;
		onReturn_GetTripodData(2, retParam)
	end

	#返回处理：激活九疑鼎
	def _doReturn_ActiveTripod(data)
		retParam = SRetParam_ActiveTripod.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byTripodID = ByteUtil::readUINT8(data) #(UINT8)九疑鼎ID
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETripodType)结果
		retParam.byTripodID = byTripodID
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ActiveTripod(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：激活九疑鼎
	def _onTimeOut_ActiveTripod(sessionID)
		retParam = SRetParam_ActiveTripod.new;
		onReturn_ActiveTripod(2, retParam)
	end

	#返回处理：升级九疑鼎
	def _doReturn_UpgradeTripod(data)
		retParam = SRetParam_UpgradeTripod.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecTripods = STripodInfo::vectorFromStream(data) #(STripodInfo的数组)九疑鼎信息列表
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETripodType)结果
		retParam.vecTripods = vecTripods
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UpgradeTripod(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：升级九疑鼎
	def _onTimeOut_UpgradeTripod(sessionID)
		retParam = SRetParam_UpgradeTripod.new;
		onReturn_UpgradeTripod(2, retParam)
	end

	#返回处理：九疑鼎祈火(炼丹)
	def _doReturn_MakeFireTripod(data)
		retParam = SRetParam_MakeFireTripod.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecTripods = STripodInfo::vectorFromStream(data) #(STripodInfo的数组)九疑鼎信息列表
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETripodType)结果
		retParam.vecTripods = vecTripods
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_MakeFireTripod(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：九疑鼎祈火(炼丹)
	def _onTimeOut_MakeFireTripod(sessionID)
		retParam = SRetParam_MakeFireTripod.new;
		onReturn_MakeFireTripod(2, retParam)
	end

	#返回处理：清除九疑鼎祈火记录
	def _doReturn_ClearFireTripod(data)
		retParam = SRetParam_ClearFireTripod.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byTripodID = ByteUtil::readUINT8(data) #(UINT8)九疑鼎ID
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETripodType)结果
		retParam.byTripodID = byTripodID
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ClearFireTripod(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：清除九疑鼎祈火记录
	def _onTimeOut_ClearFireTripod(sessionID)
		retParam = SRetParam_ClearFireTripod.new;
		onReturn_ClearFireTripod(2, retParam)
	end

	#返回处理：获取九疑鼎炼丹果实
	def _doReturn_GetTripodAward(data)
		retParam = SRetParam_GetTripodAward.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecTripods = STripodInfo::vectorFromStream(data) #(STripodInfo的数组)九疑鼎信息列表
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETripodType)结果
		retParam.vecTripods = vecTripods
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetTripodAward(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取九疑鼎炼丹果实
	def _onTimeOut_GetTripodAward(sessionID)
		retParam = SRetParam_GetTripodAward.new;
		onReturn_GetTripodAward(2, retParam)
	end

	#返回处理：加速九疑鼎炼丹(道具入鼎)
	def _doReturn_SpeedTripod(data)
		retParam = SRetParam_SpeedTripod.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecTripods = STripodInfo::vectorFromStream(data) #(STripodInfo的数组)九疑鼎信息列表
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETripodType)结果
		retParam.vecTripods = vecTripods
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SpeedTripod(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：加速九疑鼎炼丹(道具入鼎)
	def _onTimeOut_SpeedTripod(sessionID)
		retParam = SRetParam_SpeedTripod.new;
		onReturn_SpeedTripod(2, retParam)
	end

	#返回处理：扇火九疑鼎
	def _doReturn_AddTripodExtraSoul(data)
		retParam = SRetParam_AddTripodExtraSoul.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecTripods = STripodInfo::vectorFromStream(data) #(STripodInfo的数组)所属者的九疑鼎信息列表
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETripodType)结果
		retParam.vecTripods = vecTripods
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_AddTripodExtraSoul(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：扇火九疑鼎
	def _onTimeOut_AddTripodExtraSoul(sessionID)
		retParam = SRetParam_AddTripodExtraSoul.new;
		onReturn_AddTripodExtraSoul(2, retParam)
	end

	#返回处理：散仙协助九疑鼎
	def _doReturn_FighterHelpTripod(data)
		retParam = SRetParam_FighterHelpTripod.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		oFighterHelp = SFighterHelpInfo::fromStream(data) #(类类型：SFighterHelpInfo)散仙协助信息
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETripodType)结果
		retParam.oFighterHelp = oFighterHelp
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FighterHelpTripod(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：散仙协助九疑鼎
	def _onTimeOut_FighterHelpTripod(sessionID)
		retParam = SRetParam_FighterHelpTripod.new;
		onReturn_FighterHelpTripod(2, retParam)
	end

	#返回处理：玩家协助九疑鼎
	def _doReturn_UserHelpTripod(data)
		retParam = SRetParam_UserHelpTripod.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		oPlayerHelp = SPlayerHelpInfo::fromStream(data) #(类类型：SPlayerHelpInfo)玩家协助信息
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETripodType)结果
		retParam.oPlayerHelp = oPlayerHelp
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UserHelpTripod(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：玩家协助九疑鼎
	def _onTimeOut_UserHelpTripod(sessionID)
		retParam = SRetParam_UserHelpTripod.new;
		onReturn_UserHelpTripod(2, retParam)
	end

	#返回处理：踢出九疑鼎协助者
	def _doReturn_ShotOffHelpTripod(data)
		retParam = SRetParam_ShotOffHelpTripod.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETripodType)结果
		byPos = ByteUtil::readUINT8(data) #(UINT8)协助位置(0,1,2)
		byType = ByteUtil::readUINT8(data) #(UINT8)0散仙 1玩家
		retParam.eResult = eResult
		retParam.byPos = byPos
		retParam.byType = byType
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ShotOffHelpTripod(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：踢出九疑鼎协助者
	def _onTimeOut_ShotOffHelpTripod(sessionID)
		retParam = SRetParam_ShotOffHelpTripod.new;
		onReturn_ShotOffHelpTripod(2, retParam)
	end

	#返回处理：请求玩家九疑鼎的能被扇火、协助信息
	def _doReturn_GetTripodStatus(data)
		retParam = SRetParam_GetTripodStatus.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecStatus = STripodStatus::vectorFromStream(data) #(STripodStatus的数组)玩家九疑鼎的扇火、协助状态
		retParam.vecStatus = vecStatus
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetTripodStatus(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求玩家九疑鼎的能被扇火、协助信息
	def _onTimeOut_GetTripodStatus(sessionID)
		retParam = SRetParam_GetTripodStatus.new;
		onReturn_GetTripodStatus(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 63;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_UpdateTripod' #FuncID: 1

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetAllTripods' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetAllFires' #FuncID: 2
		@retFuncList[2] = '_doReturn_GetTripodData' #FuncID: 3
		@retFuncList[3] = '_doReturn_ActiveTripod' #FuncID: 4
		@retFuncList[4] = '_doReturn_UpgradeTripod' #FuncID: 5
		@retFuncList[5] = '_doReturn_MakeFireTripod' #FuncID: 6
		@retFuncList[6] = '_doReturn_ClearFireTripod' #FuncID: 7
		@retFuncList[7] = '_doReturn_GetTripodAward' #FuncID: 8
		@retFuncList[8] = '_doReturn_SpeedTripod' #FuncID: 9
		@retFuncList[9] = '_doReturn_AddTripodExtraSoul' #FuncID: 10
		@retFuncList[10] = '_doReturn_FighterHelpTripod' #FuncID: 11
		@retFuncList[11] = '_doReturn_UserHelpTripod' #FuncID: 12
		@retFuncList[12] = '_doReturn_ShotOffHelpTripod' #FuncID: 13
		@retFuncList[13] = '_doReturn_GetTripodStatus' #FuncID: 14

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetAllTripods' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetAllFires' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GetTripodData' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_ActiveTripod' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_UpgradeTripod' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_MakeFireTripod' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_ClearFireTripod' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_GetTripodAward' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_SpeedTripod' #FuncID: 9
		@timeFuncList[9] = '_onTimeOut_AddTripodExtraSoul' #FuncID: 10
		@timeFuncList[10] = '_onTimeOut_FighterHelpTripod' #FuncID: 11
		@timeFuncList[11] = '_onTimeOut_UserHelpTripod' #FuncID: 12
		@timeFuncList[12] = '_onTimeOut_ShotOffHelpTripod' #FuncID: 13
		@timeFuncList[13] = '_onTimeOut_GetTripodStatus' #FuncID: 14
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

