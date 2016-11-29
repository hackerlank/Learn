#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    Formation.rb
#  Purpose:      阵灵相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './RoleInfoDefineBase.rb'

#以下为类型定义

#阵型解锁属性
class EFormationAttr
	EFORMATTRNONE = 0#无加成
	EFORMATTRSPEED = 1#身法
	EFORMATTRHIT = 2#命中
	EFORMATTREVA = 3#闪避
	EFORMATTRCRIT = 4#暴击
	EFORMATTRANTICRIT = 5#抗暴
	EFORMATTRCOUNT = 6#反击
	EFORMATTRANTICOUNT = 7#抵抗
	EFORMATTRAP = 8#破击
	EFORMATTRMAX = 9#最大
end

#阵形、阵灵、兽魂操作结果
class EFormPetType
	EFORMPETSUCC = 0#成功
	EFORMPETFALIED = 1#失败
	EFORMPETMAINFIGHTERERR = 2#主将不能下阵
	EFORMPETITEMERR = 3#解锁道具不足
	EFORMPETPETLEVELITEMERR = 4#阵灵升级道具不足
end

#兽魂操作返回结果
class EBeastSoulResult
	EBEASTSOULSUCCES = 0#操作成功
	EBEASTSOULFAILED = 1#操作失败
	EBEASTSOULLACKOFMONEY = 2#对应货币不足
	EBEASTSOULRANKMAX = 3#已经是最大等级
	EBEASTSOULLEVELLIMIT = 4#玩家等级不足
end

#阵型信息
class SLineup
	attr_accessor:qwInstID #(UINT64)散仙唯一ID
	attr_accessor:iPos #(INT32)位置

	#构造函数
	def initialize
		@qwInstID = 0
		@iPos = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInstID = @qwInstID
		obj.iPos = @iPos
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SLineup.new
		s.qwInstID = ByteUtil::readUINT64(data)
		s.iPos = ByteUtil::readINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SLineup::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeINT32(data, @iPos)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#兽魂奖励道具信息
class SBeastSoulItem
	attr_accessor:wItemID #(UINT16)模板ID
	attr_accessor:dwCount #(UINT32)数量

	#构造函数
	def initialize
		@wItemID = 0
		@dwCount = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wItemID = @wItemID
		obj.dwCount = @dwCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBeastSoulItem.new
		s.wItemID = ByteUtil::readUINT16(data)
		s.dwCount = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBeastSoulItem::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeUINT32(data, @dwCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[FormationUp:上阵/下阵]的返回的参数组成的结构体
class SRetParam_FormationUp
	attr_accessor:eResult#(枚举类型：EFormPetType)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[SetFormation:设置阵形]的返回的参数组成的结构体
class SRetParam_SetFormation
	attr_accessor:bRet#(bool)结果

	#构造函数
	def initialize
		@bRet = false
	end
end

#函数[PetsGet:取得所有阵灵信息]的返回的参数组成的结构体
class SRetParam_PetsGet
	attr_accessor:vecPets#(SPetDataInfo的数组)阵灵信息列表

	#构造函数
	def initialize
		@vecPets = Array.new
	end
end

#函数[PetsActive:激活阵灵]的返回的参数组成的结构体
class SRetParam_PetsActive
	attr_accessor:eResult#(枚举类型：EFormPetType)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[PetsStatus:设置阵灵状态]的返回的参数组成的结构体
class SRetParam_PetsStatus
	attr_accessor:eResult#(枚举类型：EFormPetType)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[PetsUpgrade:阵灵幻化]的返回的参数组成的结构体
class SRetParam_PetsUpgrade
	attr_accessor:eResult#(枚举类型：EFormPetType)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[PetsLevelUp:阵灵升级]的返回的参数组成的结构体
class SRetParam_PetsLevelUp
	attr_accessor:eResult#(枚举类型：EFormPetType)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[QuickPetsLevelUp:阵灵一键升级]的返回的参数组成的结构体
class SRetParam_QuickPetsLevelUp
	attr_accessor:eResult#(枚举类型：EFormPetType)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetBeastSoul:获取兽魂信息]的返回的参数组成的结构体
class SRetParam_GetBeastSoul
	attr_accessor:eResult#(枚举类型：EBeastSoulResult)获取结果
	attr_accessor:vecBeastSoul#(SBeastSoulInfo的数组)兽魂信息

	#构造函数
	def initialize
		@eResult = 0
		@vecBeastSoul = Array.new
	end
end

#函数[UpgradeBeastSoul:升级兽魂]的返回的参数组成的结构体
class SRetParam_UpgradeBeastSoul
	attr_accessor:eResult#(枚举类型：EBeastSoulResult)获取结果
	attr_accessor:vecBeastSoul#(SBeastSoulInfo的数组)兽魂信息
	attr_accessor:vecItem#(SBeastSoulItem的数组)包裹或仓库中道具的列表

	#构造函数
	def initialize
		@eResult = 0
		@vecBeastSoul = Array.new
		@vecItem = Array.new
	end
end

#协议类：阵灵相关协议
class FormationProtBase < ProtocolBase
	#以下为发送函数
	#发送：上阵/下阵
	def send_FormationUp(
		qwInstID,  #(UINT64)散仙唯一ID
		iPos #(INT32)目标位置: [0-8]为上阵 <-1时为下阵
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeINT32(data, iPos)
		return @svrHandler.sendPacket(data)
	end

	#发送：设置阵形
	def send_SetFormation(
		vecSLineup #(SLineup的数组)阵形列表
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		SLineup::vectorToStream(data, vecSLineup)
		return @svrHandler.sendPacket(data)
	end

	#发送：取得所有阵灵信息
	def send_PetsGet(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：激活阵灵
	def send_PetsActive(
		wPetID #(UINT16)阵灵ID
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wPetID)
		return @svrHandler.sendPacket(data)
	end

	#发送：设置阵灵状态
	def send_PetsStatus(
		wPetID,  #(UINT16)阵灵ID
		byType #(UINT8)状态: 1-出战且显示 2-出战隐藏
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wPetID)
		ByteUtil::writeUINT8(data, byType)
		return @svrHandler.sendPacket(data)
	end

	#发送：阵灵幻化
	def send_PetsUpgrade(
		wPetID #(UINT16)阵灵ID
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wPetID)
		return @svrHandler.sendPacket(data)
	end

	#发送：阵灵升级
	def send_PetsLevelUp(
		wPetID,  #(UINT16)阵灵ID
		byType #(UINT8)升级消耗类型 0-朱果 1-蟠桃
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wPetID)
		ByteUtil::writeUINT8(data, byType)
		return @svrHandler.sendPacket(data)
	end

	#发送：阵灵一键升级
	def send_QuickPetsLevelUp(
		wPetID #(UINT16)阵灵ID
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wPetID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取兽魂信息
	def send_GetBeastSoul(
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：升级兽魂
	def send_UpgradeBeastSoul(
		eType #(枚类型：RoleInfoDefine::EBeastSoulType)兽魂种类
	)
		sessionID = @sessionMgr.getNewSession(self, 10);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eType)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：阵形信息
	def onRecv_FormationNotify(
		wFormationID, #(UINT16)阵形ID
		bySelected #(UINT8)状态: 0-未启用 1-未启用
	)
		raise NotImplementedError
	end
	#接收：阵灵信息
	def onRecv_PetDataNotify(
		wPetID, #(UINT16)阵灵ID
		bySelected, #(UINT8)状态: 0-未启用 1-出战且显示 2-出战隐藏
		byLevel, #(UINT8)阵灵等级
		dwExp #(UINT32)经验
	)
		raise NotImplementedError
	end
	#接收：全局阵灵信息
	def onRecv_RolePetNotify(
		sRolePetInfo #(类类型：RoleInfoDefine::SRolePetInfo)阵灵全局信息
	)
		raise NotImplementedError
	end
	#接收：兽魂信息
	def onRecv_BeastNotify(
		wBeastID #(UINT16)兽魂ID
	)
		raise NotImplementedError
	end
	#接收：兽魂信息
	def onRecv_BeastSoulNotify(
		vecBeastSoul #(SBeastSoulInfo的数组)兽魂信息
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：上阵/下阵
	def onReturn_FormationUp(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FormationUp)返回的参数
	)
	end

	#返回：设置阵形
	def onReturn_SetFormation(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SetFormation)返回的参数
	)
	end

	#返回：取得所有阵灵信息
	def onReturn_PetsGet(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_PetsGet)返回的参数
	)
	end

	#返回：激活阵灵
	def onReturn_PetsActive(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_PetsActive)返回的参数
	)
	end

	#返回：设置阵灵状态
	def onReturn_PetsStatus(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_PetsStatus)返回的参数
	)
	end

	#返回：阵灵幻化
	def onReturn_PetsUpgrade(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_PetsUpgrade)返回的参数
	)
	end

	#返回：阵灵升级
	def onReturn_PetsLevelUp(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_PetsLevelUp)返回的参数
	)
	end

	#返回：阵灵一键升级
	def onReturn_QuickPetsLevelUp(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_QuickPetsLevelUp)返回的参数
	)
	end

	#返回：获取兽魂信息
	def onReturn_GetBeastSoul(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetBeastSoul)返回的参数
	)
	end

	#返回：升级兽魂
	def onReturn_UpgradeBeastSoul(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UpgradeBeastSoul)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：阵形信息
	def _doRecv_FormationNotify(data)
		wFormationID = ByteUtil::readUINT16(data)
		bySelected = ByteUtil::readUINT8(data)
		return onRecv_FormationNotify(wFormationID, bySelected)
	end

	#接收处理：阵灵信息
	def _doRecv_PetDataNotify(data)
		wPetID = ByteUtil::readUINT16(data)
		bySelected = ByteUtil::readUINT8(data)
		byLevel = ByteUtil::readUINT8(data)
		dwExp = ByteUtil::readUINT32(data)
		return onRecv_PetDataNotify(wPetID, bySelected, byLevel, dwExp)
	end

	#接收处理：全局阵灵信息
	def _doRecv_RolePetNotify(data)
		sRolePetInfo = SRolePetInfo::fromStream(data)
		return onRecv_RolePetNotify(sRolePetInfo)
	end

	#接收处理：兽魂信息
	def _doRecv_BeastNotify(data)
		wBeastID = ByteUtil::readUINT16(data)
		return onRecv_BeastNotify(wBeastID)
	end

	#接收处理：兽魂信息
	def _doRecv_BeastSoulNotify(data)
		vecBeastSoul = SBeastSoulInfo::vectorFromStream(data)
		return onRecv_BeastSoulNotify(vecBeastSoul)
	end

#以下为返回处理函数
	#返回处理：上阵/下阵
	def _doReturn_FormationUp(data)
		retParam = SRetParam_FormationUp.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EFormPetType)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FormationUp(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：上阵/下阵
	def _onTimeOut_FormationUp(sessionID)
		retParam = SRetParam_FormationUp.new;
		onReturn_FormationUp(2, retParam)
	end

	#返回处理：设置阵形
	def _doReturn_SetFormation(data)
		retParam = SRetParam_SetFormation.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		bRet = ByteUtil::readBOOL(data) #(bool)结果
		retParam.bRet = bRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SetFormation(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：设置阵形
	def _onTimeOut_SetFormation(sessionID)
		retParam = SRetParam_SetFormation.new;
		onReturn_SetFormation(2, retParam)
	end

	#返回处理：取得所有阵灵信息
	def _doReturn_PetsGet(data)
		retParam = SRetParam_PetsGet.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecPets = SPetDataInfo::vectorFromStream(data) #(SPetDataInfo的数组)阵灵信息列表
		retParam.vecPets = vecPets
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_PetsGet(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：取得所有阵灵信息
	def _onTimeOut_PetsGet(sessionID)
		retParam = SRetParam_PetsGet.new;
		onReturn_PetsGet(2, retParam)
	end

	#返回处理：激活阵灵
	def _doReturn_PetsActive(data)
		retParam = SRetParam_PetsActive.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EFormPetType)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_PetsActive(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：激活阵灵
	def _onTimeOut_PetsActive(sessionID)
		retParam = SRetParam_PetsActive.new;
		onReturn_PetsActive(2, retParam)
	end

	#返回处理：设置阵灵状态
	def _doReturn_PetsStatus(data)
		retParam = SRetParam_PetsStatus.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EFormPetType)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_PetsStatus(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：设置阵灵状态
	def _onTimeOut_PetsStatus(sessionID)
		retParam = SRetParam_PetsStatus.new;
		onReturn_PetsStatus(2, retParam)
	end

	#返回处理：阵灵幻化
	def _doReturn_PetsUpgrade(data)
		retParam = SRetParam_PetsUpgrade.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EFormPetType)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_PetsUpgrade(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：阵灵幻化
	def _onTimeOut_PetsUpgrade(sessionID)
		retParam = SRetParam_PetsUpgrade.new;
		onReturn_PetsUpgrade(2, retParam)
	end

	#返回处理：阵灵升级
	def _doReturn_PetsLevelUp(data)
		retParam = SRetParam_PetsLevelUp.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EFormPetType)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_PetsLevelUp(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：阵灵升级
	def _onTimeOut_PetsLevelUp(sessionID)
		retParam = SRetParam_PetsLevelUp.new;
		onReturn_PetsLevelUp(2, retParam)
	end

	#返回处理：阵灵一键升级
	def _doReturn_QuickPetsLevelUp(data)
		retParam = SRetParam_QuickPetsLevelUp.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EFormPetType)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_QuickPetsLevelUp(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：阵灵一键升级
	def _onTimeOut_QuickPetsLevelUp(sessionID)
		retParam = SRetParam_QuickPetsLevelUp.new;
		onReturn_QuickPetsLevelUp(2, retParam)
	end

	#返回处理：获取兽魂信息
	def _doReturn_GetBeastSoul(data)
		retParam = SRetParam_GetBeastSoul.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EBeastSoulResult)获取结果
		vecBeastSoul = SBeastSoulInfo::vectorFromStream(data) #(SBeastSoulInfo的数组)兽魂信息
		retParam.eResult = eResult
		retParam.vecBeastSoul = vecBeastSoul
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetBeastSoul(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取兽魂信息
	def _onTimeOut_GetBeastSoul(sessionID)
		retParam = SRetParam_GetBeastSoul.new;
		onReturn_GetBeastSoul(2, retParam)
	end

	#返回处理：升级兽魂
	def _doReturn_UpgradeBeastSoul(data)
		retParam = SRetParam_UpgradeBeastSoul.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EBeastSoulResult)获取结果
		vecBeastSoul = SBeastSoulInfo::vectorFromStream(data) #(SBeastSoulInfo的数组)兽魂信息
		vecItem = SBeastSoulItem::vectorFromStream(data) #(SBeastSoulItem的数组)包裹或仓库中道具的列表
		retParam.eResult = eResult
		retParam.vecBeastSoul = vecBeastSoul
		retParam.vecItem = vecItem
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UpgradeBeastSoul(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：升级兽魂
	def _onTimeOut_UpgradeBeastSoul(sessionID)
		retParam = SRetParam_UpgradeBeastSoul.new;
		onReturn_UpgradeBeastSoul(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 22;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_FormationNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_PetDataNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_RolePetNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_BeastNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_BeastSoulNotify' #FuncID: 5

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_FormationUp' #FuncID: 1
		@retFuncList[1] = '_doReturn_SetFormation' #FuncID: 2
		@retFuncList[2] = '_doReturn_PetsGet' #FuncID: 3
		@retFuncList[3] = '_doReturn_PetsActive' #FuncID: 4
		@retFuncList[4] = '_doReturn_PetsStatus' #FuncID: 5
		@retFuncList[5] = '_doReturn_PetsUpgrade' #FuncID: 6
		@retFuncList[6] = '_doReturn_PetsLevelUp' #FuncID: 7
		@retFuncList[7] = '_doReturn_QuickPetsLevelUp' #FuncID: 8
		@retFuncList[8] = '_doReturn_GetBeastSoul' #FuncID: 9
		@retFuncList[9] = '_doReturn_UpgradeBeastSoul' #FuncID: 10

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_FormationUp' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_SetFormation' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_PetsGet' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_PetsActive' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_PetsStatus' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_PetsUpgrade' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_PetsLevelUp' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_QuickPetsLevelUp' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_GetBeastSoul' #FuncID: 9
		@timeFuncList[9] = '_onTimeOut_UpgradeBeastSoul' #FuncID: 10
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

