#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    ShipProt.rb
#  Purpose:      元江金船协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './BattleGSBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#战斗原因
class EShipBattleSource
	EBS_OPENSHIP = 0#开船
	EBS_ROBWITHOWER = 1#打劫与船主战斗
	EBS_ROBWITHDEFENSE = 2#打劫与护卫战斗
	EBS_GRABBYOWER = 3#返抢与船主战斗
	EBS_GRABBYDEFENSE = 4#返抢与护卫战斗
	EBS_CLOSESHIP = 5#结束航运
end

#金船操作结果
class EShipResult
	ESHIP_SUC = 0#成功
	ESHIP_NOSHIP = 1#船不存在
	ESHIP_NOFLUSHSHIP = 2#你没有刷船
	ESHIP_NOFLUSHSHIP2 = 3#邀请你的人没有刷船
	ESHIP_DEFENSEISAGREE = 4#已经有人同意帮你护送
	ESHIP_DEFENSEISAGREE2 = 5#已经有人同意帮船主护送
	ESHIP_DRIVEHASSHIP = 6#你的船已开
	ESHIP_DRIVEHASSHIP2 = 7#邀请你的人的船已开
	ESHIP_INVITEDEFENSEOFFLINE = 8#你邀请的人不在线
	ESHIP_INVITEDEFENSEOFFLINE2 = 9#船主不在线
	ESHIP_DEFENSEAGREEOTHER = 10#你邀请的人答应护送其他船
	ESHIP_DEFENSEAGREEOTHER2 = 11#你已答应护送其他船
	ESHIP_DEFENSEOTHERSHIP = 12#你邀请的人在护送其他船
	ESHIP_DEFENSEOTHERSHIP2 = 13#你在护送其他船
	ESHIP_OTHERDEFENSETIMESOUT = 14#你邀请的人护送次数用完
	ESHIP_OTHERDEFENSETIMESOUT2 = 15#你的护送次数用完
	ESHIP_DEFENSEDISAGREE = 16#邀请的人不同意帮你护送
	ESHIP_DEFENSEDISAGREE2 = 17#邀请的人不同意帮你护送
	ESHIP_DEFENSEERRFRIEND = 18#他不是你的护卫
	ESHIP_BUYOPENGOLDLIMIT = 19#购买运船仙石不足
	ESHIP_BUYROBGOLDLIMIT = 20#购买抢劫仙石不足
	ESHIP_RELUSHGOLDLIMIT = 21#购买刷新次数仙石不足
	ESHIP_RELUSHSHIPUPLIMIT = 22#刷新次数用完
	ESHIP_DRIVEOVERLIMIT = 23#今日开船到达上限
	ESHIP_DRIVEGOLDLIMIT = 24#开船金币不足
	ESHIP_ROBOVERLIMIT = 25#今日抢劫次数到达上限
	ESHIP_ROBOVERSHIP = 26#这条船被抢劫次数到达上限
	ESHIP_ROBDONE = 27#这条船你已经打劫
	ESHIP_ROBSELF = 28#这条船被你护卫或者是你的，不可抢劫
	ESHIP_GRABERROWER = 29#这条船不是你的或者你不是护卫，不可返抢
	ESHIP_GRABERR = 30#返抢对手错误
	ESHIP_BATTLECOOL = 31#战斗冷却
	ESHIP_FINISHONEKEYNOGOLD = 32#一键完成运船金币不足
	ESHIP_GETSHIPONEKEYNOGOLD = 33#一键召唤Vip金币不足
	ESHIP_GETSHIPONEKEYNOVIP = 34#一键召唤Vip等级不足
	ESHIP_OTHERERR = 35#其他错误
end

#金船信息
class PlayerShip
	attr_accessor:qwInsID #(UINT64)金船唯一ID
	attr_accessor:qwOwer #(UINT64)金船拥有者
	attr_accessor:dwOwerPoint #(UINT32)金船拥有者战斗力
	attr_accessor:byOwerLevel #(UINT8)拥有者等级
	attr_accessor:byOwerColor #(UINT8)拥有者颜色
	attr_accessor:byChannel #(UINT8)航道
	attr_accessor:wShipId #(UINT16)金船模板
	attr_accessor:qwDefense #(UINT64)护送者ID
	attr_accessor:dwDefensePoint #(UINT32)护送者战斗力
	attr_accessor:byDefenseLevel #(UINT8)护送者等级
	attr_accessor:byDefenseColor #(UINT8)护送者颜色
	attr_accessor:qwRoBId1 #(UINT64)打劫者1
	attr_accessor:byRoB1Color #(UINT8)打劫者1颜色
	attr_accessor:dwRoB1Point #(UINT32)打劫者1战斗力
	attr_accessor:byRoB1Level #(UINT8)打劫者1等级
	attr_accessor:qwRoBId2 #(UINT64)打劫者2
	attr_accessor:byRoB2Color #(UINT8)打劫者2颜色
	attr_accessor:dwRoB2Point #(UINT32)打劫者2战斗力
	attr_accessor:byRoB2Level #(UINT8)打劫者2等级
	attr_accessor:qwRoBId3 #(UINT64)打劫者3
	attr_accessor:byRoB3Color #(UINT8)打劫者3颜色
	attr_accessor:dwRoB3Point #(UINT32)打劫者3战斗力
	attr_accessor:byRoB3Level #(UINT8)打劫者3等级
	attr_accessor:dwBeginTimer #(UINT32)开船时间
	attr_accessor:dwEndTimer #(UINT32)结束时间
	attr_accessor:dwAwardRate #(UINT32)奖励倍率

	#构造函数
	def initialize
		@qwInsID = 0
		@qwOwer = 0
		@dwOwerPoint = 0
		@byOwerLevel = 0
		@byOwerColor = 0
		@byChannel = 0
		@wShipId = 0
		@qwDefense = 0
		@dwDefensePoint = 0
		@byDefenseLevel = 0
		@byDefenseColor = 0
		@qwRoBId1 = 0
		@byRoB1Color = 0
		@dwRoB1Point = 0
		@byRoB1Level = 0
		@qwRoBId2 = 0
		@byRoB2Color = 0
		@dwRoB2Point = 0
		@byRoB2Level = 0
		@qwRoBId3 = 0
		@byRoB3Color = 0
		@dwRoB3Point = 0
		@byRoB3Level = 0
		@dwBeginTimer = 0
		@dwEndTimer = 0
		@dwAwardRate = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInsID = @qwInsID
		obj.qwOwer = @qwOwer
		obj.dwOwerPoint = @dwOwerPoint
		obj.byOwerLevel = @byOwerLevel
		obj.byOwerColor = @byOwerColor
		obj.byChannel = @byChannel
		obj.wShipId = @wShipId
		obj.qwDefense = @qwDefense
		obj.dwDefensePoint = @dwDefensePoint
		obj.byDefenseLevel = @byDefenseLevel
		obj.byDefenseColor = @byDefenseColor
		obj.qwRoBId1 = @qwRoBId1
		obj.byRoB1Color = @byRoB1Color
		obj.dwRoB1Point = @dwRoB1Point
		obj.byRoB1Level = @byRoB1Level
		obj.qwRoBId2 = @qwRoBId2
		obj.byRoB2Color = @byRoB2Color
		obj.dwRoB2Point = @dwRoB2Point
		obj.byRoB2Level = @byRoB2Level
		obj.qwRoBId3 = @qwRoBId3
		obj.byRoB3Color = @byRoB3Color
		obj.dwRoB3Point = @dwRoB3Point
		obj.byRoB3Level = @byRoB3Level
		obj.dwBeginTimer = @dwBeginTimer
		obj.dwEndTimer = @dwEndTimer
		obj.dwAwardRate = @dwAwardRate
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = PlayerShip.new
		s.qwInsID = ByteUtil::readUINT64(data)
		s.qwOwer = ByteUtil::readUINT64(data)
		s.dwOwerPoint = ByteUtil::readUINT32(data)
		s.byOwerLevel = ByteUtil::readUINT8(data)
		s.byOwerColor = ByteUtil::readUINT8(data)
		s.byChannel = ByteUtil::readUINT8(data)
		s.wShipId = ByteUtil::readUINT16(data)
		s.qwDefense = ByteUtil::readUINT64(data)
		s.dwDefensePoint = ByteUtil::readUINT32(data)
		s.byDefenseLevel = ByteUtil::readUINT8(data)
		s.byDefenseColor = ByteUtil::readUINT8(data)
		s.qwRoBId1 = ByteUtil::readUINT64(data)
		s.byRoB1Color = ByteUtil::readUINT8(data)
		s.dwRoB1Point = ByteUtil::readUINT32(data)
		s.byRoB1Level = ByteUtil::readUINT8(data)
		s.qwRoBId2 = ByteUtil::readUINT64(data)
		s.byRoB2Color = ByteUtil::readUINT8(data)
		s.dwRoB2Point = ByteUtil::readUINT32(data)
		s.byRoB2Level = ByteUtil::readUINT8(data)
		s.qwRoBId3 = ByteUtil::readUINT64(data)
		s.byRoB3Color = ByteUtil::readUINT8(data)
		s.dwRoB3Point = ByteUtil::readUINT32(data)
		s.byRoB3Level = ByteUtil::readUINT8(data)
		s.dwBeginTimer = ByteUtil::readUINT32(data)
		s.dwEndTimer = ByteUtil::readUINT32(data)
		s.dwAwardRate = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = PlayerShip::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInsID)
		ByteUtil::writeUINT64(data, @qwOwer)
		ByteUtil::writeUINT32(data, @dwOwerPoint)
		ByteUtil::writeUINT8(data, @byOwerLevel)
		ByteUtil::writeUINT8(data, @byOwerColor)
		ByteUtil::writeUINT8(data, @byChannel)
		ByteUtil::writeUINT16(data, @wShipId)
		ByteUtil::writeUINT64(data, @qwDefense)
		ByteUtil::writeUINT32(data, @dwDefensePoint)
		ByteUtil::writeUINT8(data, @byDefenseLevel)
		ByteUtil::writeUINT8(data, @byDefenseColor)
		ByteUtil::writeUINT64(data, @qwRoBId1)
		ByteUtil::writeUINT8(data, @byRoB1Color)
		ByteUtil::writeUINT32(data, @dwRoB1Point)
		ByteUtil::writeUINT8(data, @byRoB1Level)
		ByteUtil::writeUINT64(data, @qwRoBId2)
		ByteUtil::writeUINT8(data, @byRoB2Color)
		ByteUtil::writeUINT32(data, @dwRoB2Point)
		ByteUtil::writeUINT8(data, @byRoB2Level)
		ByteUtil::writeUINT64(data, @qwRoBId3)
		ByteUtil::writeUINT8(data, @byRoB3Color)
		ByteUtil::writeUINT32(data, @dwRoB3Point)
		ByteUtil::writeUINT8(data, @byRoB3Level)
		ByteUtil::writeUINT32(data, @dwBeginTimer)
		ByteUtil::writeUINT32(data, @dwEndTimer)
		ByteUtil::writeUINT32(data, @dwAwardRate)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#金船战报
class ShipReport
	attr_accessor:qwInsID #(UINT64)金船唯一ID
	attr_accessor:eSource #(枚举类型：EShipBattleSource)战斗原因
	attr_accessor:qwOwer #(UINT64)金船拥有者
	attr_accessor:byOwerColor #(UINT8)拥有者颜色
	attr_accessor:wShipId #(UINT16)金船模板
	attr_accessor:qwDefense #(UINT64)护送者ID
	attr_accessor:byDefenseColor #(UINT8)护送者颜色
	attr_accessor:qwRoBId #(UINT64)打劫者
	attr_accessor:byRoBColor #(UINT8)打劫者颜色
	attr_accessor:qwBattleID #(UINT64)战报ID
	attr_accessor:dwFinishTimer #(UINT32)该船到达时间
	attr_accessor:dwTimer #(UINT32)发生时间
	attr_accessor:byRobTimes #(UINT8)被抢劫次数
	attr_accessor:dwAwardRate #(UINT32)奖励倍率

	#构造函数
	def initialize
		@qwInsID = 0
		@eSource = 0
		@qwOwer = 0
		@byOwerColor = 0
		@wShipId = 0
		@qwDefense = 0
		@byDefenseColor = 0
		@qwRoBId = 0
		@byRoBColor = 0
		@qwBattleID = 0
		@dwFinishTimer = 0
		@dwTimer = 0
		@byRobTimes = 0
		@dwAwardRate = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInsID = @qwInsID
		obj.eSource = @eSource
		obj.qwOwer = @qwOwer
		obj.byOwerColor = @byOwerColor
		obj.wShipId = @wShipId
		obj.qwDefense = @qwDefense
		obj.byDefenseColor = @byDefenseColor
		obj.qwRoBId = @qwRoBId
		obj.byRoBColor = @byRoBColor
		obj.qwBattleID = @qwBattleID
		obj.dwFinishTimer = @dwFinishTimer
		obj.dwTimer = @dwTimer
		obj.byRobTimes = @byRobTimes
		obj.dwAwardRate = @dwAwardRate
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = ShipReport.new
		s.qwInsID = ByteUtil::readUINT64(data)
		s.eSource = ByteUtil::readUINT8(data)
		s.qwOwer = ByteUtil::readUINT64(data)
		s.byOwerColor = ByteUtil::readUINT8(data)
		s.wShipId = ByteUtil::readUINT16(data)
		s.qwDefense = ByteUtil::readUINT64(data)
		s.byDefenseColor = ByteUtil::readUINT8(data)
		s.qwRoBId = ByteUtil::readUINT64(data)
		s.byRoBColor = ByteUtil::readUINT8(data)
		s.qwBattleID = ByteUtil::readUINT64(data)
		s.dwFinishTimer = ByteUtil::readUINT32(data)
		s.dwTimer = ByteUtil::readUINT32(data)
		s.byRobTimes = ByteUtil::readUINT8(data)
		s.dwAwardRate = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = ShipReport::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInsID)
		ByteUtil::writeUINT8(data, @eSource)
		ByteUtil::writeUINT64(data, @qwOwer)
		ByteUtil::writeUINT8(data, @byOwerColor)
		ByteUtil::writeUINT16(data, @wShipId)
		ByteUtil::writeUINT64(data, @qwDefense)
		ByteUtil::writeUINT8(data, @byDefenseColor)
		ByteUtil::writeUINT64(data, @qwRoBId)
		ByteUtil::writeUINT8(data, @byRoBColor)
		ByteUtil::writeUINT64(data, @qwBattleID)
		ByteUtil::writeUINT32(data, @dwFinishTimer)
		ByteUtil::writeUINT32(data, @dwTimer)
		ByteUtil::writeUINT8(data, @byRobTimes)
		ByteUtil::writeUINT32(data, @dwAwardRate)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#金船客户端信息
class PlayerShipForClient
	attr_accessor:stInfo #(类类型：PlayerShip)金船信息
	attr_accessor:strOwerName #(string)金船拥有者名字
	attr_accessor:strGuipName #(string)金船拥有者帮派
	attr_accessor:strDefenseName #(string)金船护卫名字
	attr_accessor:strRoBIdName1 #(string)金船抢劫者1名字
	attr_accessor:strRoBIdName2 #(string)金船抢劫者2名字
	attr_accessor:strRoBIdName3 #(string)金船抢劫者3名字

	#构造函数
	def initialize
		@stInfo = PlayerShip.new
		@strOwerName = ''
		@strGuipName = ''
		@strDefenseName = ''
		@strRoBIdName1 = ''
		@strRoBIdName2 = ''
		@strRoBIdName3 = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.stInfo = @stInfo
		obj.strOwerName = @strOwerName
		obj.strGuipName = @strGuipName
		obj.strDefenseName = @strDefenseName
		obj.strRoBIdName1 = @strRoBIdName1
		obj.strRoBIdName2 = @strRoBIdName2
		obj.strRoBIdName3 = @strRoBIdName3
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = PlayerShipForClient.new
		s.stInfo = PlayerShip::fromStream(data)
		s.strOwerName = ByteUtil::readSTRING(data)
		s.strGuipName = ByteUtil::readSTRING(data)
		s.strDefenseName = ByteUtil::readSTRING(data)
		s.strRoBIdName1 = ByteUtil::readSTRING(data)
		s.strRoBIdName2 = ByteUtil::readSTRING(data)
		s.strRoBIdName3 = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = PlayerShipForClient::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		@stInfo.toStream(data)
		ByteUtil::writeSTRING(data, @strOwerName)
		ByteUtil::writeSTRING(data, @strGuipName)
		ByteUtil::writeSTRING(data, @strDefenseName)
		ByteUtil::writeSTRING(data, @strRoBIdName1)
		ByteUtil::writeSTRING(data, @strRoBIdName2)
		ByteUtil::writeSTRING(data, @strRoBIdName3)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家数据库信息
class PlayerSelfShipData
	attr_accessor:dwBuyOpenShipTimes #(UINT32)购买的运船次数
	attr_accessor:dwBuyRoBShipTimes #(UINT32)购买的抢劫次数
	attr_accessor:dwBuyReflushShipTimes #(UINT32)购买的刷新次数
	attr_accessor:wReflushShip #(UINT16)刷出来的船
	attr_accessor:dwReflushShipTimer #(UINT32)刷船的时间
	attr_accessor:qwInviteDefense #(UINT64)邀请的护送者
	attr_accessor:dwInviteDefenseAgreeTime #(UINT32)别人同意护送的时间
	attr_accessor:dwInviteDefensePoint #(UINT32)护送者战斗力
	attr_accessor:byInviteDefenseLevel #(UINT8)护送者等级
	attr_accessor:byInviteDefenseColor #(UINT8)护送者颜色
	attr_accessor:qwAgreeDefenseShipOwer #(UINT64)我同意护送的船
	attr_accessor:dwAgreeDefenseShipOwerTime #(UINT32)我同意护送的时间

	#构造函数
	def initialize
		@dwBuyOpenShipTimes = 0
		@dwBuyRoBShipTimes = 0
		@dwBuyReflushShipTimes = 0
		@wReflushShip = 0
		@dwReflushShipTimer = 0
		@qwInviteDefense = 0
		@dwInviteDefenseAgreeTime = 0
		@dwInviteDefensePoint = 0
		@byInviteDefenseLevel = 0
		@byInviteDefenseColor = 0
		@qwAgreeDefenseShipOwer = 0
		@dwAgreeDefenseShipOwerTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwBuyOpenShipTimes = @dwBuyOpenShipTimes
		obj.dwBuyRoBShipTimes = @dwBuyRoBShipTimes
		obj.dwBuyReflushShipTimes = @dwBuyReflushShipTimes
		obj.wReflushShip = @wReflushShip
		obj.dwReflushShipTimer = @dwReflushShipTimer
		obj.qwInviteDefense = @qwInviteDefense
		obj.dwInviteDefenseAgreeTime = @dwInviteDefenseAgreeTime
		obj.dwInviteDefensePoint = @dwInviteDefensePoint
		obj.byInviteDefenseLevel = @byInviteDefenseLevel
		obj.byInviteDefenseColor = @byInviteDefenseColor
		obj.qwAgreeDefenseShipOwer = @qwAgreeDefenseShipOwer
		obj.dwAgreeDefenseShipOwerTime = @dwAgreeDefenseShipOwerTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = PlayerSelfShipData.new
		s.dwBuyOpenShipTimes = ByteUtil::readUINT32(data)
		s.dwBuyRoBShipTimes = ByteUtil::readUINT32(data)
		s.dwBuyReflushShipTimes = ByteUtil::readUINT32(data)
		s.wReflushShip = ByteUtil::readUINT16(data)
		s.dwReflushShipTimer = ByteUtil::readUINT32(data)
		s.qwInviteDefense = ByteUtil::readUINT64(data)
		s.dwInviteDefenseAgreeTime = ByteUtil::readUINT32(data)
		s.dwInviteDefensePoint = ByteUtil::readUINT32(data)
		s.byInviteDefenseLevel = ByteUtil::readUINT8(data)
		s.byInviteDefenseColor = ByteUtil::readUINT8(data)
		s.qwAgreeDefenseShipOwer = ByteUtil::readUINT64(data)
		s.dwAgreeDefenseShipOwerTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = PlayerSelfShipData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwBuyOpenShipTimes)
		ByteUtil::writeUINT32(data, @dwBuyRoBShipTimes)
		ByteUtil::writeUINT32(data, @dwBuyReflushShipTimes)
		ByteUtil::writeUINT16(data, @wReflushShip)
		ByteUtil::writeUINT32(data, @dwReflushShipTimer)
		ByteUtil::writeUINT64(data, @qwInviteDefense)
		ByteUtil::writeUINT32(data, @dwInviteDefenseAgreeTime)
		ByteUtil::writeUINT32(data, @dwInviteDefensePoint)
		ByteUtil::writeUINT8(data, @byInviteDefenseLevel)
		ByteUtil::writeUINT8(data, @byInviteDefenseColor)
		ByteUtil::writeUINT64(data, @qwAgreeDefenseShipOwer)
		ByteUtil::writeUINT32(data, @dwAgreeDefenseShipOwerTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#列表信息
class PlayerShipForList
	attr_accessor:qwInsID #(UINT64)金船唯一ID
	attr_accessor:qwOwer #(UINT64)金船拥有者
	attr_accessor:wShipId #(UINT16)船模板
	attr_accessor:byChannel #(UINT8)航道
	attr_accessor:dwBeginTimer #(UINT32)开船时间
	attr_accessor:dwEndTimer #(UINT32)结束时间

	#构造函数
	def initialize
		@qwInsID = 0
		@qwOwer = 0
		@wShipId = 0
		@byChannel = 0
		@dwBeginTimer = 0
		@dwEndTimer = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInsID = @qwInsID
		obj.qwOwer = @qwOwer
		obj.wShipId = @wShipId
		obj.byChannel = @byChannel
		obj.dwBeginTimer = @dwBeginTimer
		obj.dwEndTimer = @dwEndTimer
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = PlayerShipForList.new
		s.qwInsID = ByteUtil::readUINT64(data)
		s.qwOwer = ByteUtil::readUINT64(data)
		s.wShipId = ByteUtil::readUINT16(data)
		s.byChannel = ByteUtil::readUINT8(data)
		s.dwBeginTimer = ByteUtil::readUINT32(data)
		s.dwEndTimer = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = PlayerShipForList::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInsID)
		ByteUtil::writeUINT64(data, @qwOwer)
		ByteUtil::writeUINT16(data, @wShipId)
		ByteUtil::writeUINT8(data, @byChannel)
		ByteUtil::writeUINT32(data, @dwBeginTimer)
		ByteUtil::writeUINT32(data, @dwEndTimer)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家信息
class PlayerSelfView
	attr_accessor:stData #(类类型：PlayerSelfShipData)基本信息
	attr_accessor:dwRobTimes #(UINT32)抢劫次数
	attr_accessor:byDefenseTimes #(UINT8)护送次数
	attr_accessor:dwOpenShipTimes #(UINT32)开船次数
	attr_accessor:dwReFluseTimes #(UINT32)刷新次数
	attr_accessor:dwBuyRobTimes #(UINT32)今日购买的抢劫次数
	attr_accessor:dwBuyOpenShipTimesToday #(UINT32)今日购买的运船次数
	attr_accessor:dwBuyRlushShipTimesToday #(UINT32)今日购买的刷新次数
	attr_accessor:dwFreezBattleTime #(UINT32)金船战斗冷却时间
	attr_accessor:dwBeginTimer #(UINT32)自己开船时间
	attr_accessor:dwEndTimer #(UINT32)自己船结束时间
	attr_accessor:qwDefenseShip #(UINT64)我护送的船
	attr_accessor:qwSelfShip #(UINT64)我自己的船
	attr_accessor:strInviteDefenseName #(string)同意护送者名字

	#构造函数
	def initialize
		@stData = PlayerSelfShipData.new
		@dwRobTimes = 0
		@byDefenseTimes = 0
		@dwOpenShipTimes = 0
		@dwReFluseTimes = 0
		@dwBuyRobTimes = 0
		@dwBuyOpenShipTimesToday = 0
		@dwBuyRlushShipTimesToday = 0
		@dwFreezBattleTime = 0
		@dwBeginTimer = 0
		@dwEndTimer = 0
		@qwDefenseShip = 0
		@qwSelfShip = 0
		@strInviteDefenseName = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.stData = @stData
		obj.dwRobTimes = @dwRobTimes
		obj.byDefenseTimes = @byDefenseTimes
		obj.dwOpenShipTimes = @dwOpenShipTimes
		obj.dwReFluseTimes = @dwReFluseTimes
		obj.dwBuyRobTimes = @dwBuyRobTimes
		obj.dwBuyOpenShipTimesToday = @dwBuyOpenShipTimesToday
		obj.dwBuyRlushShipTimesToday = @dwBuyRlushShipTimesToday
		obj.dwFreezBattleTime = @dwFreezBattleTime
		obj.dwBeginTimer = @dwBeginTimer
		obj.dwEndTimer = @dwEndTimer
		obj.qwDefenseShip = @qwDefenseShip
		obj.qwSelfShip = @qwSelfShip
		obj.strInviteDefenseName = @strInviteDefenseName
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = PlayerSelfView.new
		s.stData = PlayerSelfShipData::fromStream(data)
		s.dwRobTimes = ByteUtil::readUINT32(data)
		s.byDefenseTimes = ByteUtil::readUINT8(data)
		s.dwOpenShipTimes = ByteUtil::readUINT32(data)
		s.dwReFluseTimes = ByteUtil::readUINT32(data)
		s.dwBuyRobTimes = ByteUtil::readUINT32(data)
		s.dwBuyOpenShipTimesToday = ByteUtil::readUINT32(data)
		s.dwBuyRlushShipTimesToday = ByteUtil::readUINT32(data)
		s.dwFreezBattleTime = ByteUtil::readUINT32(data)
		s.dwBeginTimer = ByteUtil::readUINT32(data)
		s.dwEndTimer = ByteUtil::readUINT32(data)
		s.qwDefenseShip = ByteUtil::readUINT64(data)
		s.qwSelfShip = ByteUtil::readUINT64(data)
		s.strInviteDefenseName = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = PlayerSelfView::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		@stData.toStream(data)
		ByteUtil::writeUINT32(data, @dwRobTimes)
		ByteUtil::writeUINT8(data, @byDefenseTimes)
		ByteUtil::writeUINT32(data, @dwOpenShipTimes)
		ByteUtil::writeUINT32(data, @dwReFluseTimes)
		ByteUtil::writeUINT32(data, @dwBuyRobTimes)
		ByteUtil::writeUINT32(data, @dwBuyOpenShipTimesToday)
		ByteUtil::writeUINT32(data, @dwBuyRlushShipTimesToday)
		ByteUtil::writeUINT32(data, @dwFreezBattleTime)
		ByteUtil::writeUINT32(data, @dwBeginTimer)
		ByteUtil::writeUINT32(data, @dwEndTimer)
		ByteUtil::writeUINT64(data, @qwDefenseShip)
		ByteUtil::writeUINT64(data, @qwSelfShip)
		ByteUtil::writeSTRING(data, @strInviteDefenseName)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#金船战报客户端信息
class ShipReportForClient
	attr_accessor:stInfo #(类类型：ShipReport)战报信息
	attr_accessor:eResult #(枚类型：BattleGS::EBattleResult)
	attr_accessor:strOwerName #(string)金船拥有者名字
	attr_accessor:strDefenseName #(string)金船护卫名字
	attr_accessor:strRoBIdName #(string)金船抢劫者名字

	#构造函数
	def initialize
		@stInfo = ShipReport.new
		@eResult = 0
		@strOwerName = ''
		@strDefenseName = ''
		@strRoBIdName = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.stInfo = @stInfo
		obj.eResult = @eResult
		obj.strOwerName = @strOwerName
		obj.strDefenseName = @strDefenseName
		obj.strRoBIdName = @strRoBIdName
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = ShipReportForClient.new
		s.stInfo = ShipReport::fromStream(data)
		s.eResult = ByteUtil::readUINT8(data)
		s.strOwerName = ByteUtil::readSTRING(data)
		s.strDefenseName = ByteUtil::readSTRING(data)
		s.strRoBIdName = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = ShipReportForClient::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		@stInfo.toStream(data)
		ByteUtil::writeUINT8(data, @eResult)
		ByteUtil::writeSTRING(data, @strOwerName)
		ByteUtil::writeSTRING(data, @strDefenseName)
		ByteUtil::writeSTRING(data, @strRoBIdName)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetShipList:获取所有金船显示信息]的返回的参数组成的结构体
class SRetParam_GetShipList
	attr_accessor:vecShip#(PlayerShipForList的数组)获取结果

	#构造函数
	def initialize
		@vecShip = Array.new
	end
end

#函数[GetShipInfo:获取某条船的信息]的返回的参数组成的结构体
class SRetParam_GetShipInfo
	attr_accessor:eResult#(枚举类型：EShipResult)获取结果
	attr_accessor:stShipInfo#(类类型：PlayerShipForClient)金船信息

	#构造函数
	def initialize
		@eResult = 0
		@stShipInfo = PlayerShipForClient.new
	end
end

#函数[OpenShip:雇佣船只,开始运船]的返回的参数组成的结构体
class SRetParam_OpenShip
	attr_accessor:eResult#(枚举类型：EShipResult)操作结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[BuyOpenShipTimes:购买运船次数]的返回的参数组成的结构体
class SRetParam_BuyOpenShipTimes
	attr_accessor:eResult#(枚举类型：EShipResult)操作结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[BuyRoBShipTimes:购买抢劫次数]的返回的参数组成的结构体
class SRetParam_BuyRoBShipTimes
	attr_accessor:eResult#(枚举类型：EShipResult)操作结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[BuyReflushShipTimes:购买刷新次数]的返回的参数组成的结构体
class SRetParam_BuyReflushShipTimes
	attr_accessor:eResult#(枚举类型：EShipResult)操作结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[ReFlushShip:刷新船只]的返回的参数组成的结构体
class SRetParam_ReFlushShip
	attr_accessor:eResult#(枚举类型：EShipResult)操作结果
	attr_accessor:wShipId#(UINT16)金船模板

	#构造函数
	def initialize
		@eResult = 0
		@wShipId = 0
	end
end

#函数[InViteFriend:邀请护送船只]的返回的参数组成的结构体
class SRetParam_InViteFriend
	attr_accessor:eResult#(枚举类型：EShipResult)操作结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[InViteOtherAgree:回应邀请护送船只]的返回的参数组成的结构体
class SRetParam_InViteOtherAgree
	attr_accessor:eResult#(枚举类型：EShipResult)操作结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[FireDefense:船主踢出护送者]的返回的参数组成的结构体
class SRetParam_FireDefense
	attr_accessor:eResult#(枚举类型：EShipResult)操作结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[DoRoBShip:打劫船只]的返回的参数组成的结构体
class SRetParam_DoRoBShip
	attr_accessor:eResult#(枚举类型：EShipResult)操作结果
	attr_accessor:bySuc#(UINT8)0,失败，1胜利

	#构造函数
	def initialize
		@eResult = 0
		@bySuc = 0
	end
end

#函数[DoGrapShip:返抢]的返回的参数组成的结构体
class SRetParam_DoGrapShip
	attr_accessor:eResult#(枚举类型：EShipResult)操作结果
	attr_accessor:bySuc#(UINT8)0,失败，1胜利

	#构造函数
	def initialize
		@eResult = 0
		@bySuc = 0
	end
end

#函数[FinishShipOneKey:一键完成运送]的返回的参数组成的结构体
class SRetParam_FinishShipOneKey
	attr_accessor:eResult#(枚举类型：EShipResult)操作结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：元江金船协议
class ShipProtBase < ProtocolBase
	#以下为发送函数
	#发送：获取自己显示信息
	def send_GetShipSelfView(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取所有金船显示信息
	def send_GetShipList(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：不再关注列表
	def send_DelList(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取某条船的信息
	def send_GetShipInfo(
		qwInsID #(UINT64)金船唯一ID
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInsID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取历史信息
	def send_GetShipReport(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：雇佣船只,开始运船
	def send_OpenShip(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：购买运船次数
	def send_BuyOpenShipTimes(
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：购买抢劫次数
	def send_BuyRoBShipTimes(
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：购买刷新次数
	def send_BuyReflushShipTimes(
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：刷新船只
	def send_ReFlushShip(
		byVip #(UINT8)0,表示非vip ,非0表示vip
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byVip)
		return @svrHandler.sendPacket(data)
	end

	#发送：邀请护送船只
	def send_InViteFriend(
		qwFriend #(UINT64)好友
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwFriend)
		return @svrHandler.sendPacket(data)
	end

	#发送：回应邀请护送船只
	def send_InViteOtherAgree(
		bySuc,  #(UINT8)0,同意，1拒绝
		qwFriend,  #(UINT64)好友
		dwCode #(UINT32)验证码
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, bySuc)
		ByteUtil::writeUINT64(data, qwFriend)
		ByteUtil::writeUINT32(data, dwCode)
		return @svrHandler.sendPacket(data)
	end

	#发送：船主踢出护送者
	def send_FireDefense(
		qwFriend #(UINT64)好友
	)
		sessionID = @sessionMgr.getNewSession(self, 10);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 13
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwFriend)
		return @svrHandler.sendPacket(data)
	end

	#发送：打劫船只
	def send_DoRoBShip(
		qwInsID #(UINT64)金船唯一ID
	)
		sessionID = @sessionMgr.getNewSession(self, 11);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 14
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInsID)
		return @svrHandler.sendPacket(data)
	end

	#发送：返抢
	def send_DoGrapShip(
		qwShipID,  #(UINT64)金船唯一ID
		qwRoBID #(UINT64)打劫者ID
	)
		sessionID = @sessionMgr.getNewSession(self, 12);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 15
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwShipID)
		ByteUtil::writeUINT64(data, qwRoBID)
		return @svrHandler.sendPacket(data)
	end

	#发送：一键完成运送
	def send_FinishShipOneKey(
	)
		sessionID = @sessionMgr.getNewSession(self, 13);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 16
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：发送玩家信息
	def onRecv_SendView(
		stViewInfo #(类类型：PlayerSelfView)玩家信息
	)
		raise NotImplementedError
	end
	#接收：发送船只增加消息
	def onRecv_UpDateShipAdd(
		stShipInfo #(类类型：PlayerShipForList)船只信息
	)
		raise NotImplementedError
	end
	#接收：发送船只删除消息
	def onRecv_UpDateShipDel(
		qwInsID #(UINT64)金船唯一ID
	)
		raise NotImplementedError
	end
	#接收：发送玩家战报信息
	def onRecv_SendRePort(
		vecReportInfo #(ShipReportForClient的数组)玩家战报信息
	)
		raise NotImplementedError
	end
	#接收：发送记录增加消息
	def onRecv_UpDateShipReportAdd(
		stReport #(类类型：ShipReportForClient)记录信息
	)
		raise NotImplementedError
	end
	#接收：邀请别人的回复
	def onRecv_InviteAnswer(
		qwDefense, #(UINT64)护卫者ID
		strName, #(string)护卫者的名字
		byColor, #(UINT8)护卫者的颜色
		eResult #(枚举类型：EShipResult)操作结果
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取所有金船显示信息
	def onReturn_GetShipList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetShipList)返回的参数
	)
	end

	#返回：获取某条船的信息
	def onReturn_GetShipInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetShipInfo)返回的参数
	)
	end

	#返回：雇佣船只,开始运船
	def onReturn_OpenShip(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_OpenShip)返回的参数
	)
	end

	#返回：购买运船次数
	def onReturn_BuyOpenShipTimes(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuyOpenShipTimes)返回的参数
	)
	end

	#返回：购买抢劫次数
	def onReturn_BuyRoBShipTimes(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuyRoBShipTimes)返回的参数
	)
	end

	#返回：购买刷新次数
	def onReturn_BuyReflushShipTimes(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BuyReflushShipTimes)返回的参数
	)
	end

	#返回：刷新船只
	def onReturn_ReFlushShip(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReFlushShip)返回的参数
	)
	end

	#返回：邀请护送船只
	def onReturn_InViteFriend(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_InViteFriend)返回的参数
	)
	end

	#返回：回应邀请护送船只
	def onReturn_InViteOtherAgree(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_InViteOtherAgree)返回的参数
	)
	end

	#返回：船主踢出护送者
	def onReturn_FireDefense(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FireDefense)返回的参数
	)
	end

	#返回：打劫船只
	def onReturn_DoRoBShip(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_DoRoBShip)返回的参数
	)
	end

	#返回：返抢
	def onReturn_DoGrapShip(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_DoGrapShip)返回的参数
	)
	end

	#返回：一键完成运送
	def onReturn_FinishShipOneKey(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FinishShipOneKey)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：发送玩家信息
	def _doRecv_SendView(data)
		stViewInfo = PlayerSelfView::fromStream(data)
		return onRecv_SendView(stViewInfo)
	end

	#接收处理：发送船只增加消息
	def _doRecv_UpDateShipAdd(data)
		stShipInfo = PlayerShipForList::fromStream(data)
		return onRecv_UpDateShipAdd(stShipInfo)
	end

	#接收处理：发送船只删除消息
	def _doRecv_UpDateShipDel(data)
		qwInsID = ByteUtil::readUINT64(data)
		return onRecv_UpDateShipDel(qwInsID)
	end

	#接收处理：发送玩家战报信息
	def _doRecv_SendRePort(data)
		vecReportInfo = ShipReportForClient::vectorFromStream(data)
		return onRecv_SendRePort(vecReportInfo)
	end

	#接收处理：发送记录增加消息
	def _doRecv_UpDateShipReportAdd(data)
		stReport = ShipReportForClient::fromStream(data)
		return onRecv_UpDateShipReportAdd(stReport)
	end

	#接收处理：邀请别人的回复
	def _doRecv_InviteAnswer(data)
		qwDefense = ByteUtil::readUINT64(data)
		strName = ByteUtil::readSTRING(data)
		byColor = ByteUtil::readUINT8(data)
		eResult = ByteUtil::readUINT8(data)
		return onRecv_InviteAnswer(qwDefense, strName, byColor, eResult)
	end

#以下为返回处理函数
	#返回处理：获取所有金船显示信息
	def _doReturn_GetShipList(data)
		retParam = SRetParam_GetShipList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecShip = PlayerShipForList::vectorFromStream(data) #(PlayerShipForList的数组)获取结果
		retParam.vecShip = vecShip
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetShipList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取所有金船显示信息
	def _onTimeOut_GetShipList(sessionID)
		retParam = SRetParam_GetShipList.new;
		onReturn_GetShipList(2, retParam)
	end

	#返回处理：获取某条船的信息
	def _doReturn_GetShipInfo(data)
		retParam = SRetParam_GetShipInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShipResult)获取结果
		stShipInfo = PlayerShipForClient::fromStream(data) #(类类型：PlayerShipForClient)金船信息
		retParam.eResult = eResult
		retParam.stShipInfo = stShipInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetShipInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取某条船的信息
	def _onTimeOut_GetShipInfo(sessionID)
		retParam = SRetParam_GetShipInfo.new;
		onReturn_GetShipInfo(2, retParam)
	end

	#返回处理：雇佣船只,开始运船
	def _doReturn_OpenShip(data)
		retParam = SRetParam_OpenShip.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShipResult)操作结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_OpenShip(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：雇佣船只,开始运船
	def _onTimeOut_OpenShip(sessionID)
		retParam = SRetParam_OpenShip.new;
		onReturn_OpenShip(2, retParam)
	end

	#返回处理：购买运船次数
	def _doReturn_BuyOpenShipTimes(data)
		retParam = SRetParam_BuyOpenShipTimes.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShipResult)操作结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuyOpenShipTimes(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：购买运船次数
	def _onTimeOut_BuyOpenShipTimes(sessionID)
		retParam = SRetParam_BuyOpenShipTimes.new;
		onReturn_BuyOpenShipTimes(2, retParam)
	end

	#返回处理：购买抢劫次数
	def _doReturn_BuyRoBShipTimes(data)
		retParam = SRetParam_BuyRoBShipTimes.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShipResult)操作结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuyRoBShipTimes(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：购买抢劫次数
	def _onTimeOut_BuyRoBShipTimes(sessionID)
		retParam = SRetParam_BuyRoBShipTimes.new;
		onReturn_BuyRoBShipTimes(2, retParam)
	end

	#返回处理：购买刷新次数
	def _doReturn_BuyReflushShipTimes(data)
		retParam = SRetParam_BuyReflushShipTimes.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShipResult)操作结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BuyReflushShipTimes(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：购买刷新次数
	def _onTimeOut_BuyReflushShipTimes(sessionID)
		retParam = SRetParam_BuyReflushShipTimes.new;
		onReturn_BuyReflushShipTimes(2, retParam)
	end

	#返回处理：刷新船只
	def _doReturn_ReFlushShip(data)
		retParam = SRetParam_ReFlushShip.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShipResult)操作结果
		wShipId = ByteUtil::readUINT16(data) #(UINT16)金船模板
		retParam.eResult = eResult
		retParam.wShipId = wShipId
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReFlushShip(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：刷新船只
	def _onTimeOut_ReFlushShip(sessionID)
		retParam = SRetParam_ReFlushShip.new;
		onReturn_ReFlushShip(2, retParam)
	end

	#返回处理：邀请护送船只
	def _doReturn_InViteFriend(data)
		retParam = SRetParam_InViteFriend.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShipResult)操作结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_InViteFriend(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：邀请护送船只
	def _onTimeOut_InViteFriend(sessionID)
		retParam = SRetParam_InViteFriend.new;
		onReturn_InViteFriend(2, retParam)
	end

	#返回处理：回应邀请护送船只
	def _doReturn_InViteOtherAgree(data)
		retParam = SRetParam_InViteOtherAgree.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShipResult)操作结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_InViteOtherAgree(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：回应邀请护送船只
	def _onTimeOut_InViteOtherAgree(sessionID)
		retParam = SRetParam_InViteOtherAgree.new;
		onReturn_InViteOtherAgree(2, retParam)
	end

	#返回处理：船主踢出护送者
	def _doReturn_FireDefense(data)
		retParam = SRetParam_FireDefense.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShipResult)操作结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FireDefense(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：船主踢出护送者
	def _onTimeOut_FireDefense(sessionID)
		retParam = SRetParam_FireDefense.new;
		onReturn_FireDefense(2, retParam)
	end

	#返回处理：打劫船只
	def _doReturn_DoRoBShip(data)
		retParam = SRetParam_DoRoBShip.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShipResult)操作结果
		bySuc = ByteUtil::readUINT8(data) #(UINT8)0,失败，1胜利
		retParam.eResult = eResult
		retParam.bySuc = bySuc
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_DoRoBShip(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：打劫船只
	def _onTimeOut_DoRoBShip(sessionID)
		retParam = SRetParam_DoRoBShip.new;
		onReturn_DoRoBShip(2, retParam)
	end

	#返回处理：返抢
	def _doReturn_DoGrapShip(data)
		retParam = SRetParam_DoGrapShip.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShipResult)操作结果
		bySuc = ByteUtil::readUINT8(data) #(UINT8)0,失败，1胜利
		retParam.eResult = eResult
		retParam.bySuc = bySuc
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_DoGrapShip(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：返抢
	def _onTimeOut_DoGrapShip(sessionID)
		retParam = SRetParam_DoGrapShip.new;
		onReturn_DoGrapShip(2, retParam)
	end

	#返回处理：一键完成运送
	def _doReturn_FinishShipOneKey(data)
		retParam = SRetParam_FinishShipOneKey.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShipResult)操作结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FinishShipOneKey(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：一键完成运送
	def _onTimeOut_FinishShipOneKey(sessionID)
		retParam = SRetParam_FinishShipOneKey.new;
		onReturn_FinishShipOneKey(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 84;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_SendView' #FuncID: 1
		@recvFuncList[1] = '_doRecv_UpDateShipAdd' #FuncID: 2
		@recvFuncList[2] = '_doRecv_UpDateShipDel' #FuncID: 3
		@recvFuncList[3] = '_doRecv_SendRePort' #FuncID: 4
		@recvFuncList[4] = '_doRecv_UpDateShipReportAdd' #FuncID: 5
		@recvFuncList[5] = '_doRecv_InviteAnswer' #FuncID: 6

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetShipList' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetShipInfo' #FuncID: 2
		@retFuncList[2] = '_doReturn_OpenShip' #FuncID: 3
		@retFuncList[3] = '_doReturn_BuyOpenShipTimes' #FuncID: 4
		@retFuncList[4] = '_doReturn_BuyRoBShipTimes' #FuncID: 5
		@retFuncList[5] = '_doReturn_BuyReflushShipTimes' #FuncID: 6
		@retFuncList[6] = '_doReturn_ReFlushShip' #FuncID: 7
		@retFuncList[7] = '_doReturn_InViteFriend' #FuncID: 8
		@retFuncList[8] = '_doReturn_InViteOtherAgree' #FuncID: 9
		@retFuncList[9] = '_doReturn_FireDefense' #FuncID: 10
		@retFuncList[10] = '_doReturn_DoRoBShip' #FuncID: 11
		@retFuncList[11] = '_doReturn_DoGrapShip' #FuncID: 12
		@retFuncList[12] = '_doReturn_FinishShipOneKey' #FuncID: 13

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetShipList' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetShipInfo' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_OpenShip' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_BuyOpenShipTimes' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_BuyRoBShipTimes' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_BuyReflushShipTimes' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_ReFlushShip' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_InViteFriend' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_InViteOtherAgree' #FuncID: 9
		@timeFuncList[9] = '_onTimeOut_FireDefense' #FuncID: 10
		@timeFuncList[10] = '_onTimeOut_DoRoBShip' #FuncID: 11
		@timeFuncList[11] = '_onTimeOut_DoGrapShip' #FuncID: 12
		@timeFuncList[12] = '_onTimeOut_FinishShipOneKey' #FuncID: 13
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

