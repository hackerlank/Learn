#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    MapProt.rb
#  Purpose:      地图相关功能的协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './BattleGSBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#地图结果
class EMapResult
	EMAPSUCCESS = 0#成功
	EMAPNOTGHOSTERR = 1#没处于灵魂状态
	EMAPCOINERR = 2#仙石不足
	EMAPNOTINDUNGEONERR = 3#不在副本
	EMAPOTHERERR = 4#其他错误
end

#地图附加数据
class EMapParam
	EMAPPARAMDEMONFLOORID = 0#镇妖塔层数
	EMAPPARAMEND = 3#数组最大长度，上面索引不同功能可以重复
end

#地图上生物的外观状态
class EAppearState
	EAPPEARNONE = 0#无
	EAPPEARFIGHT = 1#战斗状态
	EAPPEARGHOST = 2#灵魂状态
	EAPPEARDIE = 3#死亡状态
end

#传送阵开关类型
class ESwitcherType
	ESWITCHERNONE = 0#无
	ESWITCHERJUMP = 1#副本传送开关
	ESWITCHERCAMP = 2#阵营选择开关
	ESWITCHERTOWER = 3#试练之塔传送开关
	ESWITCHERUPTOWER = 4#锁妖塔塔上传开关
	ESWITCHERDOWNTOWER = 5#锁妖塔下传开关
end

#宝藏图操作结果
class ETreasureResult
	ETREASURESUCCESS = 0#成功
	ETREASUREFAIL = 1#失败
	ETREASURENOITEM = 2#没有藏宝图
	ETREASURELACKCOIN = 3#仙石不足
	ETREASURENOINAREA = 4#没有在指定区域挖掘
	ETREASUREDROPERR = 5#掉落物品错误
	ETREASUREDIAMOND = 6#钻石不足
	ETREASUREBUYINFOSUCCESS = 7#购买信息成功
end

#地图负载
class EMapOverLoad
	EMAPFREE = 0#空闲
	EMAPBUSY = 1#地图忙
	EMAPFULL = 2#地图满
end

#地图负载情况
class MapOverLoad
	attr_accessor:byIndex #(UINT8)地图序号
	attr_accessor:eLoadState #(枚举类型：EMapOverLoad)负载状况

	#构造函数
	def initialize
		@byIndex = 0
		@eLoadState = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byIndex = @byIndex
		obj.eLoadState = @eLoadState
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = MapOverLoad.new
		s.byIndex = ByteUtil::readUINT8(data)
		s.eLoadState = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = MapOverLoad::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byIndex)
		ByteUtil::writeUINT8(data, @eLoadState)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#地图上物体的位置
class SPosition
	attr_accessor:fX #(float)X坐标
	attr_accessor:fY #(float)Y坐标

	#构造函数
	def initialize
		@fX = 0
		@fY = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.fX = @fX
		obj.fY = @fY
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPosition.new
		s.fX = ByteUtil::readFLOAT(data)
		s.fY = ByteUtil::readFLOAT(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPosition::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeFLOAT(data, @fX)
		ByteUtil::writeFLOAT(data, @fY)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#角色的外观
class SPlayerAppear
	attr_accessor:strName #(string)角色名
	attr_accessor:eCareer #(枚类型：ProtoCommon::ECareerType)职业
	attr_accessor:eSex #(枚类型：ProtoCommon::ESexType)性别
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:dwSpeed #(UINT32)速度
	attr_accessor:pFeature #(类类型：BattleGS::SFeatureBase)外观信息
	attr_accessor:dwHorseID #(UINT32)坐骑
	attr_accessor:dwHorseLevel #(UINT32)坐骑等级
	attr_accessor:wPetID #(UINT16)阵灵ID
	attr_accessor:byPetLevel #(UINT8)阵灵等级
	attr_accessor:wBeautyID #(UINT16)美女ID
	attr_accessor:byBeautyLevel #(UINT8)美女等级
	attr_accessor:bIsSitting #(UINT8)是否打坐0,没有打坐，1单修，2双修
	attr_accessor:qwOtherSitID #(UINT64)双修玩家
	attr_accessor:vecPlatforms #(SPlatformParam的数组)平台信息

	#构造函数
	def initialize
		@strName = ''
		@eCareer = 0
		@eSex = 0
		@byLevel = 0
		@dwSpeed = 0
		@pFeature = SFeatureBase.new
		@dwHorseID = 0
		@dwHorseLevel = 0
		@wPetID = 0
		@byPetLevel = 0
		@wBeautyID = 0
		@byBeautyLevel = 0
		@bIsSitting = 0
		@qwOtherSitID = 0
		@vecPlatforms = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strName = @strName
		obj.eCareer = @eCareer
		obj.eSex = @eSex
		obj.byLevel = @byLevel
		obj.dwSpeed = @dwSpeed
		obj.pFeature = @pFeature
		obj.dwHorseID = @dwHorseID
		obj.dwHorseLevel = @dwHorseLevel
		obj.wPetID = @wPetID
		obj.byPetLevel = @byPetLevel
		obj.wBeautyID = @wBeautyID
		obj.byBeautyLevel = @byBeautyLevel
		obj.bIsSitting = @bIsSitting
		obj.qwOtherSitID = @qwOtherSitID
		obj.vecPlatforms = @vecPlatforms
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPlayerAppear.new
		s.strName = ByteUtil::readSTRING(data)
		s.eCareer = ByteUtil::readUINT8(data)
		s.eSex = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.dwSpeed = ByteUtil::readUINT32(data)
		s.pFeature = SFeatureBase::superFromStream(data)
		s.dwHorseID = ByteUtil::readUINT32(data)
		s.dwHorseLevel = ByteUtil::readUINT32(data)
		s.wPetID = ByteUtil::readUINT16(data)
		s.byPetLevel = ByteUtil::readUINT8(data)
		s.wBeautyID = ByteUtil::readUINT16(data)
		s.byBeautyLevel = ByteUtil::readUINT8(data)
		s.bIsSitting = ByteUtil::readUINT8(data)
		s.qwOtherSitID = ByteUtil::readUINT64(data)
		s.vecPlatforms = SPlatformParam::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPlayerAppear::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @eCareer)
		ByteUtil::writeUINT8(data, @eSex)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwSpeed)
		@pFeature.superToStream(data)
		ByteUtil::writeUINT32(data, @dwHorseID)
		ByteUtil::writeUINT32(data, @dwHorseLevel)
		ByteUtil::writeUINT16(data, @wPetID)
		ByteUtil::writeUINT8(data, @byPetLevel)
		ByteUtil::writeUINT16(data, @wBeautyID)
		ByteUtil::writeUINT8(data, @byBeautyLevel)
		ByteUtil::writeUINT8(data, @bIsSitting)
		ByteUtil::writeUINT64(data, @qwOtherSitID)
		SPlatformParam::vectorToStream(data, @vecPlatforms)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#怪物的外观
class SMonsterAppear
	attr_accessor:wMonsterID #(UINT16)怪物ID
	attr_accessor:strName #(string)怪物名称
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:dwSpeed #(UINT32)移动速度/200
	attr_accessor:dwCurHP #(UINT32)当前HP
	attr_accessor:dwMaxHP #(UINT32)最大HP
	attr_accessor:byCamp #(UINT8)阵营
	attr_accessor:wGroup #(UINT16)所属的组
	attr_accessor:bySight #(UINT8)视野
	attr_accessor:bySightAngle #(UINT8)视野角度
	attr_accessor:byFindEnemy #(UINT8)0,无目标：1有目标
	attr_accessor:pFeature #(类类型：BattleGS::SFeatureBase)外观信息

	#构造函数
	def initialize
		@wMonsterID = 0
		@strName = ''
		@byLevel = 0
		@dwSpeed = 0
		@dwCurHP = 0
		@dwMaxHP = 0
		@byCamp = 0
		@wGroup = 0
		@bySight = 0
		@bySightAngle = 0
		@byFindEnemy = 0
		@pFeature = SFeatureBase.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wMonsterID = @wMonsterID
		obj.strName = @strName
		obj.byLevel = @byLevel
		obj.dwSpeed = @dwSpeed
		obj.dwCurHP = @dwCurHP
		obj.dwMaxHP = @dwMaxHP
		obj.byCamp = @byCamp
		obj.wGroup = @wGroup
		obj.bySight = @bySight
		obj.bySightAngle = @bySightAngle
		obj.byFindEnemy = @byFindEnemy
		obj.pFeature = @pFeature
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMonsterAppear.new
		s.wMonsterID = ByteUtil::readUINT16(data)
		s.strName = ByteUtil::readSTRING(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.dwSpeed = ByteUtil::readUINT32(data)
		s.dwCurHP = ByteUtil::readUINT32(data)
		s.dwMaxHP = ByteUtil::readUINT32(data)
		s.byCamp = ByteUtil::readUINT8(data)
		s.wGroup = ByteUtil::readUINT16(data)
		s.bySight = ByteUtil::readUINT8(data)
		s.bySightAngle = ByteUtil::readUINT8(data)
		s.byFindEnemy = ByteUtil::readUINT8(data)
		s.pFeature = SFeatureBase::superFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMonsterAppear::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wMonsterID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwSpeed)
		ByteUtil::writeUINT32(data, @dwCurHP)
		ByteUtil::writeUINT32(data, @dwMaxHP)
		ByteUtil::writeUINT8(data, @byCamp)
		ByteUtil::writeUINT16(data, @wGroup)
		ByteUtil::writeUINT8(data, @bySight)
		ByteUtil::writeUINT8(data, @bySightAngle)
		ByteUtil::writeUINT8(data, @byFindEnemy)
		@pFeature.superToStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#NPC的外观
class SNpcAppear
	attr_accessor:wNpcID #(UINT16)NPC类型ID
	attr_accessor:strName #(string)NPC名称

	#构造函数
	def initialize
		@wNpcID = 0
		@strName = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wNpcID = @wNpcID
		obj.strName = @strName
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SNpcAppear.new
		s.wNpcID = ByteUtil::readUINT16(data)
		s.strName = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SNpcAppear::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wNpcID)
		ByteUtil::writeSTRING(data, @strName)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#采集物的外观
class SGatherAppear
	attr_accessor:wGatherID #(UINT16)采集物类型ID
	attr_accessor:wTotalNum #(UINT16)采集总次数,特别的为-1表示，采集无数次,以下两个字段始终为0
	attr_accessor:wReserverNum #(UINT16)采集剩余次数
	attr_accessor:wGatheringNum #(UINT16)正在采集的人次

	#构造函数
	def initialize
		@wGatherID = 0
		@wTotalNum = 0
		@wReserverNum = 0
		@wGatheringNum = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wGatherID = @wGatherID
		obj.wTotalNum = @wTotalNum
		obj.wReserverNum = @wReserverNum
		obj.wGatheringNum = @wGatheringNum
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGatherAppear.new
		s.wGatherID = ByteUtil::readUINT16(data)
		s.wTotalNum = ByteUtil::readUINT16(data)
		s.wReserverNum = ByteUtil::readUINT16(data)
		s.wGatheringNum = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGatherAppear::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wGatherID)
		ByteUtil::writeUINT16(data, @wTotalNum)
		ByteUtil::writeUINT16(data, @wReserverNum)
		ByteUtil::writeUINT16(data, @wGatheringNum)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#传送阵开关的外观
class SSwitcherAppear
	attr_accessor:dwSwitcherID #(UINT32)开关配置ID
	attr_accessor:eType #(枚举类型：ESwitcherType)开关类型
	attr_accessor:bOpen #(bool)开关状态

	#构造函数
	def initialize
		@dwSwitcherID = 0
		@eType = 0
		@bOpen = false
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwSwitcherID = @dwSwitcherID
		obj.eType = @eType
		obj.bOpen = @bOpen
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSwitcherAppear.new
		s.dwSwitcherID = ByteUtil::readUINT32(data)
		s.eType = ByteUtil::readUINT8(data)
		s.bOpen = ByteUtil::readBOOL(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSwitcherAppear::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwSwitcherID)
		ByteUtil::writeUINT8(data, @eType)
		ByteUtil::writeBOOL(data, @bOpen)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#阻挡物外观
class SBlockerAppear
	attr_accessor:dwBlockerID #(UINT32)阻挡物类型ID,表格数据
	attr_accessor:vecPos #(SPosition的数组)阻挡物阻挡坐标点

	#构造函数
	def initialize
		@dwBlockerID = 0
		@vecPos = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwBlockerID = @dwBlockerID
		obj.vecPos = @vecPos
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBlockerAppear.new
		s.dwBlockerID = ByteUtil::readUINT32(data)
		s.vecPos = SPosition::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBlockerAppear::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwBlockerID)
		SPosition::vectorToStream(data, @vecPos)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#区域外观
class SAreaAppear
	attr_accessor:wAreaID #(UINT16)区域类型ID，表格数据

	#构造函数
	def initialize
		@wAreaID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wAreaID = @wAreaID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SAreaAppear.new
		s.wAreaID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SAreaAppear::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wAreaID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetPlayerAppear:获取玩家的外观信息]的返回的参数组成的结构体
class SRetParam_GetPlayerAppear
	attr_accessor:byRet#(UINT8)0 成功 1失败
	attr_accessor:rPlayerAppear#(类类型：SPlayerAppear)玩家的外观

	#构造函数
	def initialize
		@byRet = 0
		@rPlayerAppear = SPlayerAppear.new
	end
end

#函数[JumpMap:请求跳地图]的返回的参数组成的结构体
class SRetParam_JumpMap
	attr_accessor:byRet#(UINT8)0成功
	attr_accessor:wMapID#(UINT16)地图ID
	attr_accessor:byIndex#(UINT8)地图序号,255表示任意地图

	#构造函数
	def initialize
		@byRet = 0
		@wMapID = 0
		@byIndex = 0
	end
end

#函数[GetMapOverLoad:请求地图负载]的返回的参数组成的结构体
class SRetParam_GetMapOverLoad
	attr_accessor:wMapID#(UINT16)地图ID
	attr_accessor:vecLoad#(MapOverLoad的数组)地图ID

	#构造函数
	def initialize
		@wMapID = 0
		@vecLoad = Array.new
	end
end

#协议类：地图相关功能的协议
class MapProtBase < ProtocolBase
	#以下为发送函数
	#发送：角色移动请求
	def send_PlayerMoveReq(
		wMapID,  #(UINT16)地图ID
		vecPosition #(SPosition的数组)移动位置列表
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT16(data, wMapID)
		SPosition::vectorToStream(data, vecPosition)
		return @svrHandler.sendPacket(data)
	end

	#发送：角色停止移动
	def send_PlayerStopReq(
		wMapID,  #(UINT16)地图ID
		StopPos #(类类型：SPosition)停止点
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT16(data, wMapID)
		StopPos.toStream(data)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取玩家的外观信息
	def send_GetPlayerAppear(
		qwUserID #(UINT64)目标玩家ID
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwUserID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求跳地图
	def send_JumpMap(
		wMapID,  #(UINT16)地图ID
		byIndex #(UINT8)地图序号,255表示任意地图
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wMapID)
		ByteUtil::writeUINT8(data, byIndex)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求地图负载
	def send_GetMapOverLoad(
		wMapID #(UINT16)地图ID
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wMapID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：通知玩家进入地图
	def onRecv_UserEnterMapNtf(
		wMapID, #(UINT16)地图ID
		qwRoleID, #(UINT64)当前的角色ID
		byIndex, #(UINT8)地图序号,非主城返回255
		byTotal, #(UINT8)同Id地图总数,非主城返回0
		rPosition, #(类类型：SPosition)进入位置
		fDir #(float)方向
	)
		raise NotImplementedError
	end
	#接收：新地图产生，通知同地图玩家
	def onRecv_NoticeNewMap(
		vecLoad #(MapOverLoad的数组)地图负载
	)
		raise NotImplementedError
	end
	#接收：角色(非当前控制)地图信息通知
	def onRecv_RoleMapInfoNtf(
		qwRoleID, #(UINT64)角色的ID
		wMapID #(UINT16)地图ID
	)
		raise NotImplementedError
	end
	#接收：通知角色移动失败
	def onRecv_PlayerMoveFail(
		qwRoleID, #(UINT64)角色ID
		rLastPosition, #(类类型：SPosition)上一个位置
		vecPosition #(SPosition的数组)移动位置列表
	)
		raise NotImplementedError
	end
	#接收：通知自己的玩家角色出现
	def onRecv_NotifyAppear(
		qwRoleID, #(UINT64)角色ID
		rPlayerAppear, #(类类型：SPlayerAppear)玩家的外观
		rPosition, #(类类型：SPosition)出现位置
		fDir, #(float)方向(弧度)
		dwAppearState #(UINT32)当前状态(EAppearState按位或的结果)
	)
		raise NotImplementedError
	end
	#接收：通知别的玩家角色出现
	def onRecv_PlayerAppear(
		qwRoleID, #(UINT64)角色ID
		rPlayerAppear, #(类类型：SPlayerAppear)玩家的外观
		rPosition, #(类类型：SPosition)出现位置
		fDir, #(float)方向(弧度)
		dwAppearState, #(UINT32)当前状态(EAppearState按位或的结果)
		bBorn #(bool)true为出生，false为进入视野
	)
		raise NotImplementedError
	end
	#接收：通知Creature移动
	def onRecv_NotifyCreatureMove(
		qwCreatureID, #(UINT64)生物ID
		vecPosition #(SPosition的数组)移动位置列表
	)
		raise NotImplementedError
	end
	#接收：通知Creature跳点
	def onRecv_NotifyCreatureJump(
		qwCreatureID, #(UINT64)Creature ID
		rPosition, #(类类型：SPosition)跳点目的位置
		wJumpId #(UINT16)跳点ID
	)
		raise NotImplementedError
	end
	#接收：通知Creature当前状态
	def onRecv_NotifyCreatureState(
		qwCreatureID, #(UINT64)Creature ID
		dwAppearState #(UINT32)当前状态(EAppearState按位或的结果)
	)
		raise NotImplementedError
	end
	#接收：通知Creature停止
	def onRecv_NotifyCreatureStop(
		qwCreatureID, #(UINT64)生物ID
		rDestPosition #(类类型：SPosition)最终位置
	)
		raise NotImplementedError
	end
	#接收：通知地图上生物消失
	def onRecv_CreatureDisappear(
		qwCreatureID, #(UINT64)生物ID
		bDieFade #(bool)true为死亡消失，false为移出视野
	)
		raise NotImplementedError
	end
	#接收：通知NPC出现
	def onRecv_NpcAppear(
		qwCreatureID, #(UINT64)生物ID
		rNpcAppear, #(类类型：SNpcAppear)NPC外观
		rPosition, #(类类型：SPosition)出现位置
		fDir, #(float)方向(弧度)
		bBorn #(bool)true为出生，false为进入视野
	)
		raise NotImplementedError
	end
	#接收：通知怪物出现
	def onRecv_MonsterAppear(
		qwCreatureID, #(UINT64)生物ID
		rMonsterAppear, #(类类型：SMonsterAppear)怪物外观
		rPosition, #(类类型：SPosition)出现位置
		fDir, #(float)方向(弧度)
		dwAppearState, #(UINT32)当前状态(EAppearState按位或的结果)
		bBorn #(bool)true为出生，false为进入视野
	)
		raise NotImplementedError
	end
	#接收：通知开关出现
	def onRecv_SwitcherAppear(
		dwInstID, #(UINT32)唯一实例ID
		rSwitcherAppear, #(类类型：SSwitcherAppear)开关外观
		rPosition, #(类类型：SPosition)出现位置
		fDir, #(float)方向(弧度)
		bBorn #(bool)true为出生，false为进入视野
	)
		raise NotImplementedError
	end
	#接收：通知地图上开关消失
	def onRecv_SwitcherDisappear(
		dwInstID #(UINT32)开关唯一ID
	)
		raise NotImplementedError
	end
	#接收：通知开关当前状态
	def onRecv_NotifySwitcherState(
		dwInstID, #(UINT32)开关唯一实例ID
		bOpen #(bool)当前开关是否开启
	)
		raise NotImplementedError
	end
	#接收：通知采集物出现
	def onRecv_GatherAppear(
		dwGatherID, #(UINT32)生物ID
		rGatherAppear, #(类类型：SGatherAppear)采集物外观
		rPosition, #(类类型：SPosition)出现位置
		fDir, #(float)方向(弧度)
		bBorn #(bool)true为出生，false为进入视野
	)
		raise NotImplementedError
	end
	#接收：通知地图上采集物消失
	def onRecv_GatherDisappear(
		dwGatherID, #(UINT32)采集物ID
		bDieFade #(bool)true为采集后消失，false为移出视野
	)
		raise NotImplementedError
	end
	#接收：通知地图上采集物改变
	def onRecv_GatherChange(
		dwGatherID, #(UINT32)采集物ID
		rGatherAppear #(类类型：SGatherAppear)采集物外观
	)
		raise NotImplementedError
	end
	#接收：阻挡物出现
	def onRecv_BlockerAppear(
		dwInstID, #(UINT32)唯一ID
		rBlockerAppear, #(类类型：SBlockerAppear)阻挡物开关
		rPosition, #(类类型：SPosition)出现位置
		fDir, #(float)方向(弧度)
		bBorn #(bool)true为出生，false为进入视野
	)
		raise NotImplementedError
	end
	#接收：通知地图上阻挡物消失
	def onRecv_BlockerDisappear(
		dwInstID #(UINT32)阻挡物唯一ID
	)
		raise NotImplementedError
	end
	#接收：通知怪物改变
	def onRecv_MonsterChange(
		qwCreatureID, #(UINT64)生物ID
		rMonsterAppear #(类类型：SMonsterAppear)怪物外观
	)
		raise NotImplementedError
	end
	#接收：通知区域出现
	def onRecv_AreaAppear(
		dwAreaID, #(UINT32)区域实例ID
		rAreaAppear, #(类类型：SAreaAppear)区域外观
		rPosition #(类类型：SPosition)出现位置
	)
		raise NotImplementedError
	end
	#接收：通知地图上区域消失
	def onRecv_AreaDisappear(
		dwAreaID #(UINT32)区域实例ID
	)
		raise NotImplementedError
	end
	#接收：怪物发现敌人
	def onRecv_MonsterTargetChange(
		qwMonsterID, #(UINT64)怪物ID
		qwTargetID #(UINT64)目标ID
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取玩家的外观信息
	def onReturn_GetPlayerAppear(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetPlayerAppear)返回的参数
	)
	end

	#返回：请求跳地图
	def onReturn_JumpMap(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_JumpMap)返回的参数
	)
	end

	#返回：请求地图负载
	def onReturn_GetMapOverLoad(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetMapOverLoad)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：通知玩家进入地图
	def _doRecv_UserEnterMapNtf(data)
		wMapID = ByteUtil::readUINT16(data)
		qwRoleID = ByteUtil::readUINT64(data)
		byIndex = ByteUtil::readUINT8(data)
		byTotal = ByteUtil::readUINT8(data)
		rPosition = SPosition::fromStream(data)
		fDir = ByteUtil::readFLOAT(data)
		return onRecv_UserEnterMapNtf(wMapID, qwRoleID, byIndex, byTotal, rPosition, fDir)
	end

	#接收处理：新地图产生，通知同地图玩家
	def _doRecv_NoticeNewMap(data)
		vecLoad = MapOverLoad::vectorFromStream(data)
		return onRecv_NoticeNewMap(vecLoad)
	end

	#接收处理：角色(非当前控制)地图信息通知
	def _doRecv_RoleMapInfoNtf(data)
		qwRoleID = ByteUtil::readUINT64(data)
		wMapID = ByteUtil::readUINT16(data)
		return onRecv_RoleMapInfoNtf(qwRoleID, wMapID)
	end

	#接收处理：通知角色移动失败
	def _doRecv_PlayerMoveFail(data)
		qwRoleID = ByteUtil::readUINT64(data)
		rLastPosition = SPosition::fromStream(data)
		vecPosition = SPosition::vectorFromStream(data)
		return onRecv_PlayerMoveFail(qwRoleID, rLastPosition, vecPosition)
	end

	#接收处理：通知自己的玩家角色出现
	def _doRecv_NotifyAppear(data)
		qwRoleID = ByteUtil::readUINT64(data)
		rPlayerAppear = SPlayerAppear::fromStream(data)
		rPosition = SPosition::fromStream(data)
		fDir = ByteUtil::readFLOAT(data)
		dwAppearState = ByteUtil::readUINT32(data)
		return onRecv_NotifyAppear(qwRoleID, rPlayerAppear, rPosition, fDir, dwAppearState)
	end

	#接收处理：通知别的玩家角色出现
	def _doRecv_PlayerAppear(data)
		qwRoleID = ByteUtil::readUINT64(data)
		rPlayerAppear = SPlayerAppear::fromStream(data)
		rPosition = SPosition::fromStream(data)
		fDir = ByteUtil::readFLOAT(data)
		dwAppearState = ByteUtil::readUINT32(data)
		bBorn = ByteUtil::readBOOL(data)
		return onRecv_PlayerAppear(qwRoleID, rPlayerAppear, rPosition, fDir, dwAppearState, bBorn)
	end

	#接收处理：通知Creature移动
	def _doRecv_NotifyCreatureMove(data)
		qwCreatureID = ByteUtil::readUINT64(data)
		vecPosition = SPosition::vectorFromStream(data)
		return onRecv_NotifyCreatureMove(qwCreatureID, vecPosition)
	end

	#接收处理：通知Creature跳点
	def _doRecv_NotifyCreatureJump(data)
		qwCreatureID = ByteUtil::readUINT64(data)
		rPosition = SPosition::fromStream(data)
		wJumpId = ByteUtil::readUINT16(data)
		return onRecv_NotifyCreatureJump(qwCreatureID, rPosition, wJumpId)
	end

	#接收处理：通知Creature当前状态
	def _doRecv_NotifyCreatureState(data)
		qwCreatureID = ByteUtil::readUINT64(data)
		dwAppearState = ByteUtil::readUINT32(data)
		return onRecv_NotifyCreatureState(qwCreatureID, dwAppearState)
	end

	#接收处理：通知Creature停止
	def _doRecv_NotifyCreatureStop(data)
		qwCreatureID = ByteUtil::readUINT64(data)
		rDestPosition = SPosition::fromStream(data)
		return onRecv_NotifyCreatureStop(qwCreatureID, rDestPosition)
	end

	#接收处理：通知地图上生物消失
	def _doRecv_CreatureDisappear(data)
		qwCreatureID = ByteUtil::readUINT64(data)
		bDieFade = ByteUtil::readBOOL(data)
		return onRecv_CreatureDisappear(qwCreatureID, bDieFade)
	end

	#接收处理：通知NPC出现
	def _doRecv_NpcAppear(data)
		qwCreatureID = ByteUtil::readUINT64(data)
		rNpcAppear = SNpcAppear::fromStream(data)
		rPosition = SPosition::fromStream(data)
		fDir = ByteUtil::readFLOAT(data)
		bBorn = ByteUtil::readBOOL(data)
		return onRecv_NpcAppear(qwCreatureID, rNpcAppear, rPosition, fDir, bBorn)
	end

	#接收处理：通知怪物出现
	def _doRecv_MonsterAppear(data)
		qwCreatureID = ByteUtil::readUINT64(data)
		rMonsterAppear = SMonsterAppear::fromStream(data)
		rPosition = SPosition::fromStream(data)
		fDir = ByteUtil::readFLOAT(data)
		dwAppearState = ByteUtil::readUINT32(data)
		bBorn = ByteUtil::readBOOL(data)
		return onRecv_MonsterAppear(qwCreatureID, rMonsterAppear, rPosition, fDir, dwAppearState, bBorn)
	end

	#接收处理：通知开关出现
	def _doRecv_SwitcherAppear(data)
		dwInstID = ByteUtil::readUINT32(data)
		rSwitcherAppear = SSwitcherAppear::fromStream(data)
		rPosition = SPosition::fromStream(data)
		fDir = ByteUtil::readFLOAT(data)
		bBorn = ByteUtil::readBOOL(data)
		return onRecv_SwitcherAppear(dwInstID, rSwitcherAppear, rPosition, fDir, bBorn)
	end

	#接收处理：通知地图上开关消失
	def _doRecv_SwitcherDisappear(data)
		dwInstID = ByteUtil::readUINT32(data)
		return onRecv_SwitcherDisappear(dwInstID)
	end

	#接收处理：通知开关当前状态
	def _doRecv_NotifySwitcherState(data)
		dwInstID = ByteUtil::readUINT32(data)
		bOpen = ByteUtil::readBOOL(data)
		return onRecv_NotifySwitcherState(dwInstID, bOpen)
	end

	#接收处理：通知采集物出现
	def _doRecv_GatherAppear(data)
		dwGatherID = ByteUtil::readUINT32(data)
		rGatherAppear = SGatherAppear::fromStream(data)
		rPosition = SPosition::fromStream(data)
		fDir = ByteUtil::readFLOAT(data)
		bBorn = ByteUtil::readBOOL(data)
		return onRecv_GatherAppear(dwGatherID, rGatherAppear, rPosition, fDir, bBorn)
	end

	#接收处理：通知地图上采集物消失
	def _doRecv_GatherDisappear(data)
		dwGatherID = ByteUtil::readUINT32(data)
		bDieFade = ByteUtil::readBOOL(data)
		return onRecv_GatherDisappear(dwGatherID, bDieFade)
	end

	#接收处理：通知地图上采集物改变
	def _doRecv_GatherChange(data)
		dwGatherID = ByteUtil::readUINT32(data)
		rGatherAppear = SGatherAppear::fromStream(data)
		return onRecv_GatherChange(dwGatherID, rGatherAppear)
	end

	#接收处理：阻挡物出现
	def _doRecv_BlockerAppear(data)
		dwInstID = ByteUtil::readUINT32(data)
		rBlockerAppear = SBlockerAppear::fromStream(data)
		rPosition = SPosition::fromStream(data)
		fDir = ByteUtil::readFLOAT(data)
		bBorn = ByteUtil::readBOOL(data)
		return onRecv_BlockerAppear(dwInstID, rBlockerAppear, rPosition, fDir, bBorn)
	end

	#接收处理：通知地图上阻挡物消失
	def _doRecv_BlockerDisappear(data)
		dwInstID = ByteUtil::readUINT32(data)
		return onRecv_BlockerDisappear(dwInstID)
	end

	#接收处理：通知怪物改变
	def _doRecv_MonsterChange(data)
		qwCreatureID = ByteUtil::readUINT64(data)
		rMonsterAppear = SMonsterAppear::fromStream(data)
		return onRecv_MonsterChange(qwCreatureID, rMonsterAppear)
	end

	#接收处理：通知区域出现
	def _doRecv_AreaAppear(data)
		dwAreaID = ByteUtil::readUINT32(data)
		rAreaAppear = SAreaAppear::fromStream(data)
		rPosition = SPosition::fromStream(data)
		return onRecv_AreaAppear(dwAreaID, rAreaAppear, rPosition)
	end

	#接收处理：通知地图上区域消失
	def _doRecv_AreaDisappear(data)
		dwAreaID = ByteUtil::readUINT32(data)
		return onRecv_AreaDisappear(dwAreaID)
	end

	#接收处理：怪物发现敌人
	def _doRecv_MonsterTargetChange(data)
		qwMonsterID = ByteUtil::readUINT64(data)
		qwTargetID = ByteUtil::readUINT64(data)
		return onRecv_MonsterTargetChange(qwMonsterID, qwTargetID)
	end

#以下为返回处理函数
	#返回处理：获取玩家的外观信息
	def _doReturn_GetPlayerAppear(data)
		retParam = SRetParam_GetPlayerAppear.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readUINT8(data) #(UINT8)0 成功 1失败
		rPlayerAppear = SPlayerAppear::fromStream(data) #(类类型：SPlayerAppear)玩家的外观
		retParam.byRet = byRet
		retParam.rPlayerAppear = rPlayerAppear
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetPlayerAppear(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取玩家的外观信息
	def _onTimeOut_GetPlayerAppear(sessionID)
		retParam = SRetParam_GetPlayerAppear.new;
		onReturn_GetPlayerAppear(2, retParam)
	end

	#返回处理：请求跳地图
	def _doReturn_JumpMap(data)
		retParam = SRetParam_JumpMap.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		byRet = ByteUtil::readUINT8(data) #(UINT8)0成功
		wMapID = ByteUtil::readUINT16(data) #(UINT16)地图ID
		byIndex = ByteUtil::readUINT8(data) #(UINT8)地图序号,255表示任意地图
		retParam.byRet = byRet
		retParam.wMapID = wMapID
		retParam.byIndex = byIndex
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_JumpMap(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求跳地图
	def _onTimeOut_JumpMap(sessionID)
		retParam = SRetParam_JumpMap.new;
		onReturn_JumpMap(2, retParam)
	end

	#返回处理：请求地图负载
	def _doReturn_GetMapOverLoad(data)
		retParam = SRetParam_GetMapOverLoad.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		wMapID = ByteUtil::readUINT16(data) #(UINT16)地图ID
		vecLoad = MapOverLoad::vectorFromStream(data) #(MapOverLoad的数组)地图ID
		retParam.wMapID = wMapID
		retParam.vecLoad = vecLoad
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetMapOverLoad(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求地图负载
	def _onTimeOut_GetMapOverLoad(sessionID)
		retParam = SRetParam_GetMapOverLoad.new;
		onReturn_GetMapOverLoad(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 5;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_UserEnterMapNtf' #FuncID: 1
		@recvFuncList[1] = '_doRecv_NoticeNewMap' #FuncID: 2
		@recvFuncList[2] = '_doRecv_RoleMapInfoNtf' #FuncID: 3
		@recvFuncList[3] = '_doRecv_PlayerMoveFail' #FuncID: 4
		@recvFuncList[4] = '_doRecv_NotifyAppear' #FuncID: 5
		@recvFuncList[5] = '_doRecv_PlayerAppear' #FuncID: 6
		@recvFuncList[6] = '_doRecv_NotifyCreatureMove' #FuncID: 7
		@recvFuncList[7] = '_doRecv_NotifyCreatureJump' #FuncID: 8
		@recvFuncList[8] = '_doRecv_NotifyCreatureState' #FuncID: 9
		@recvFuncList[9] = '_doRecv_NotifyCreatureStop' #FuncID: 10
		@recvFuncList[10] = '_doRecv_CreatureDisappear' #FuncID: 11
		@recvFuncList[11] = '_doRecv_NpcAppear' #FuncID: 12
		@recvFuncList[12] = '_doRecv_MonsterAppear' #FuncID: 13
		@recvFuncList[13] = '_doRecv_SwitcherAppear' #FuncID: 14
		@recvFuncList[14] = '_doRecv_SwitcherDisappear' #FuncID: 15
		@recvFuncList[15] = '_doRecv_NotifySwitcherState' #FuncID: 16
		@recvFuncList[16] = '_doRecv_GatherAppear' #FuncID: 17
		@recvFuncList[17] = '_doRecv_GatherDisappear' #FuncID: 18
		@recvFuncList[18] = '_doRecv_GatherChange' #FuncID: 19
		@recvFuncList[19] = '_doRecv_BlockerAppear' #FuncID: 20
		@recvFuncList[20] = '_doRecv_BlockerDisappear' #FuncID: 21
		@recvFuncList[21] = '_doRecv_MonsterChange' #FuncID: 22
		@recvFuncList[22] = '_doRecv_AreaAppear' #FuncID: 23
		@recvFuncList[23] = '_doRecv_AreaDisappear' #FuncID: 24
		@recvFuncList[24] = '_doRecv_MonsterTargetChange' #FuncID: 25

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetPlayerAppear' #FuncID: 1
		@retFuncList[1] = '_doReturn_JumpMap' #FuncID: 2
		@retFuncList[2] = '_doReturn_GetMapOverLoad' #FuncID: 3

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetPlayerAppear' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_JumpMap' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GetMapOverLoad' #FuncID: 3
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

