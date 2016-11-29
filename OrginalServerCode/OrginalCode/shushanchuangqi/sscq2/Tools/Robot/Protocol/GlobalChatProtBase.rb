#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    GlobalChatProt.rb
#  Purpose:      全局聊天协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#获取展示道具结果
class EChatShowResult
	ECHATSHOWSUCCEED = 0#成功
	ECHATSHOWNOTEXIST = 1#展示道具不存在
	ECHATSHOWERROTHER = 2#其他错误
end

#通道类型
class EChannelType
	ECHANNELNONE = 0#None
	ECHANNELALL = 1#综合
	ECHANNELWORLD = 2#世界
	ECHANNELGUILD = 3#帮派
	ECHANNELSYS = 4#系统
	ECHANNELTEAM = 5#组队
	ECHANNELNOLABELSYS = 6#无字系统消息
end

#消息额外类型
class EChannelSubType
	ESUBNONE = 0#无
	ESUBBULLETIN = 1#公告区域
	ESUBBROADCAST = 2#广播区域
	ESUBHORN = 3#喇叭区域
	ESUBSUSPENSION = 4#悬浮区域
	ESUBPROMPT = 5#提示区域
	ESUBEND = 6#结束
end

#展示类型
class EChatShowType
	ESHOWITEM = 0#道具
	ESHOWROLE = 1#角色
	ESHOWPET = 2#阵灵
	ESHOWHORSE = 3#坐骑
end

#私聊错误类型
class EWhisperErrorType
	EWHISPERTOOFASTERR = 0#太快
	EWHISPEROFFLINEERR = 1#目标不在线
	EWHISPERLENGTHERR = 2#信息长度不对
end

#炫耀类型
class ESShowInfoType
	EFLAUNTGOOD = 0#物品，使用SItem解析
	EFLAUNTHERO = 1#散仙，使用SFlauntHero解析
	EFLAUNTPET = 2#阵灵，使用SFlauntPet解析
	EFLAUNTHORSE = 3#坐骑，使用SFlauntHorse解析
	ESHOWACHIEVEMENT = 4#成就
	EFLAUNTFASHION = 5#时装，使用SFlauntFashion解析
end

#发送者信息
class SSenderInfo
	attr_accessor:byVIPType #(UINT8)VIP特权类型
	attr_accessor:qwUsrID #(UINT64)帐号ID
	attr_accessor:strName #(string)发送者名
	attr_accessor:strGuildName #(string)帮派名称
	attr_accessor:byQuality #(UINT8)玩家品质（颜色）
	attr_accessor:byNation #(UINT8)发送者国家
	attr_accessor:vecPlatforms #(SPlatformParam的数组)平台相关参数

	#构造函数
	def initialize
		@byVIPType = 0
		@qwUsrID = 0
		@strName = ''
		@strGuildName = ''
		@byQuality = 0
		@byNation = 0
		@vecPlatforms = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byVIPType = @byVIPType
		obj.qwUsrID = @qwUsrID
		obj.strName = @strName
		obj.strGuildName = @strGuildName
		obj.byQuality = @byQuality
		obj.byNation = @byNation
		obj.vecPlatforms = @vecPlatforms
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSenderInfo.new
		s.byVIPType = ByteUtil::readUINT8(data)
		s.qwUsrID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.byNation = ByteUtil::readUINT8(data)
		s.vecPlatforms = SPlatformParam::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSenderInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byVIPType)
		ByteUtil::writeUINT64(data, @qwUsrID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeSTRING(data, @strGuildName)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT8(data, @byNation)
		SPlatformParam::vectorToStream(data, @vecPlatforms)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#炫耀信息
class SShowInfo
	attr_accessor:qwInstID #(UINT64)唯一ID
	attr_accessor:strShowInfo #(string)展示信息序列化

	#构造函数
	def initialize
		@qwInstID = 0
		@strShowInfo = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInstID = @qwInstID
		obj.strShowInfo = @strShowInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SShowInfo.new
		s.qwInstID = ByteUtil::readUINT64(data)
		s.strShowInfo = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SShowInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeSTRING(data, @strShowInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#私聊对方信息
class SWhisperInfo
	attr_accessor:qwUserID #(UINT64)帐号ID
	attr_accessor:strName #(string)名字 XXX: 如果主将改名需要修改此处
	attr_accessor:byVIPType #(UINT8)VIP特权类型
	attr_accessor:strGuildName #(string)帮派名称
	attr_accessor:vecPlatforms #(SPlatformParam的数组)平台相关参数
	attr_accessor:wFighterID #(UINT16)主将ID
	attr_accessor:eSex #(枚类型：ProtoCommon::ESexType)性别
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:wMood #(UINT16)心情表情
	attr_accessor:strSign #(string)签名
	attr_accessor:byQuality #(UINT8)品质

	#构造函数
	def initialize
		@qwUserID = 0
		@strName = ''
		@byVIPType = 0
		@strGuildName = ''
		@vecPlatforms = Array.new
		@wFighterID = 0
		@eSex = 0
		@byLevel = 0
		@wMood = 0
		@strSign = ''
		@byQuality = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwUserID = @qwUserID
		obj.strName = @strName
		obj.byVIPType = @byVIPType
		obj.strGuildName = @strGuildName
		obj.vecPlatforms = @vecPlatforms
		obj.wFighterID = @wFighterID
		obj.eSex = @eSex
		obj.byLevel = @byLevel
		obj.wMood = @wMood
		obj.strSign = @strSign
		obj.byQuality = @byQuality
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SWhisperInfo.new
		s.qwUserID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.byVIPType = ByteUtil::readUINT8(data)
		s.strGuildName = ByteUtil::readSTRING(data)
		s.vecPlatforms = SPlatformParam::vectorFromStream(data)
		s.wFighterID = ByteUtil::readUINT16(data)
		s.eSex = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.wMood = ByteUtil::readUINT16(data)
		s.strSign = ByteUtil::readSTRING(data)
		s.byQuality = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SWhisperInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwUserID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @byVIPType)
		ByteUtil::writeSTRING(data, @strGuildName)
		SPlatformParam::vectorToStream(data, @vecPlatforms)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT8(data, @eSex)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT16(data, @wMood)
		ByteUtil::writeSTRING(data, @strSign)
		ByteUtil::writeUINT8(data, @byQuality)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#炫耀参与战斗的技能信息
class SFlauntSkill
	attr_accessor:byIdx #(UINT8)技能槽idx
	attr_accessor:dwSkillID #(UINT32)技能ID

	#构造函数
	def initialize
		@byIdx = 0
		@dwSkillID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byIdx = @byIdx
		obj.dwSkillID = @dwSkillID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFlauntSkill.new
		s.byIdx = ByteUtil::readUINT8(data)
		s.dwSkillID = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFlauntSkill::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byIdx)
		ByteUtil::writeUINT32(data, @dwSkillID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#炫耀装备信息
class SFlauntEquip
	attr_accessor:wEquipID #(UINT16)装备TypeID
	attr_accessor:byStrengthenLevel #(UINT8)强化等级
	attr_accessor:byPos #(UINT8)装备位置

	#构造函数
	def initialize
		@wEquipID = 0
		@byStrengthenLevel = 0
		@byPos = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wEquipID = @wEquipID
		obj.byStrengthenLevel = @byStrengthenLevel
		obj.byPos = @byPos
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFlauntEquip.new
		s.wEquipID = ByteUtil::readUINT16(data)
		s.byStrengthenLevel = ByteUtil::readUINT8(data)
		s.byPos = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFlauntEquip::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wEquipID)
		ByteUtil::writeUINT8(data, @byStrengthenLevel)
		ByteUtil::writeUINT8(data, @byPos)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#散仙炫耀信息
class SFlauntHero
	attr_accessor:strName #(string)名字
	attr_accessor:qwInstID #(UINT64)散仙唯一ID
	attr_accessor:wFighterID #(UINT16)散仙ID
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:byQuilty #(UINT8)品质 0,1,2,3,4,5,6【黑白绿蓝紫黄橙】
	attr_accessor:dwPower #(UINT32)散仙战斗力
	attr_accessor:oAttrVec #(SFtAttrMod的数组)最终属性
	attr_accessor:byDujieLevel #(UINT8)散仙渡劫等级
	attr_accessor:vActiveSkill #(SFlauntSkill的数组)主动技能
	attr_accessor:vPassiveSkill #(SFlauntSkill的数组)被动技能
	attr_accessor:sPeerLessSkill #(类类型：SFlauntSkill)无双技能
	attr_accessor:vecFlauntEquip #(SFlauntEquip的数组)时装
	attr_accessor:byLianPi #(UINT8)炼皮
	attr_accessor:byTongJin #(UINT8)通筋
	attr_accessor:byQiangJi #(UINT8)强肌
	attr_accessor:byDuanGu #(UINT8)锻骨
	attr_accessor:byHuoLuo #(UINT8)活络
	attr_accessor:byXiSui #(UINT8)洗髓

	#构造函数
	def initialize
		@strName = ''
		@qwInstID = 0
		@wFighterID = 0
		@byLevel = 0
		@byQuilty = 0
		@dwPower = 0
		@oAttrVec = Array.new
		@byDujieLevel = 0
		@vActiveSkill = Array.new
		@vPassiveSkill = Array.new
		@sPeerLessSkill = SFlauntSkill.new
		@vecFlauntEquip = Array.new
		@byLianPi = 0
		@byTongJin = 0
		@byQiangJi = 0
		@byDuanGu = 0
		@byHuoLuo = 0
		@byXiSui = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strName = @strName
		obj.qwInstID = @qwInstID
		obj.wFighterID = @wFighterID
		obj.byLevel = @byLevel
		obj.byQuilty = @byQuilty
		obj.dwPower = @dwPower
		obj.oAttrVec = @oAttrVec
		obj.byDujieLevel = @byDujieLevel
		obj.vActiveSkill = @vActiveSkill
		obj.vPassiveSkill = @vPassiveSkill
		obj.sPeerLessSkill = @sPeerLessSkill
		obj.vecFlauntEquip = @vecFlauntEquip
		obj.byLianPi = @byLianPi
		obj.byTongJin = @byTongJin
		obj.byQiangJi = @byQiangJi
		obj.byDuanGu = @byDuanGu
		obj.byHuoLuo = @byHuoLuo
		obj.byXiSui = @byXiSui
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFlauntHero.new
		s.strName = ByteUtil::readSTRING(data)
		s.qwInstID = ByteUtil::readUINT64(data)
		s.wFighterID = ByteUtil::readUINT16(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.byQuilty = ByteUtil::readUINT8(data)
		s.dwPower = ByteUtil::readUINT32(data)
		s.oAttrVec = SFtAttrMod::vectorFromStream(data)
		s.byDujieLevel = ByteUtil::readUINT8(data)
		s.vActiveSkill = SFlauntSkill::vectorFromStream(data)
		s.vPassiveSkill = SFlauntSkill::vectorFromStream(data)
		s.sPeerLessSkill = SFlauntSkill::fromStream(data)
		s.vecFlauntEquip = SFlauntEquip::vectorFromStream(data)
		s.byLianPi = ByteUtil::readUINT8(data)
		s.byTongJin = ByteUtil::readUINT8(data)
		s.byQiangJi = ByteUtil::readUINT8(data)
		s.byDuanGu = ByteUtil::readUINT8(data)
		s.byHuoLuo = ByteUtil::readUINT8(data)
		s.byXiSui = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFlauntHero::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT8(data, @byQuilty)
		ByteUtil::writeUINT32(data, @dwPower)
		SFtAttrMod::vectorToStream(data, @oAttrVec)
		ByteUtil::writeUINT8(data, @byDujieLevel)
		SFlauntSkill::vectorToStream(data, @vActiveSkill)
		SFlauntSkill::vectorToStream(data, @vPassiveSkill)
		@sPeerLessSkill.toStream(data)
		SFlauntEquip::vectorToStream(data, @vecFlauntEquip)
		ByteUtil::writeUINT8(data, @byLianPi)
		ByteUtil::writeUINT8(data, @byTongJin)
		ByteUtil::writeUINT8(data, @byQiangJi)
		ByteUtil::writeUINT8(data, @byDuanGu)
		ByteUtil::writeUINT8(data, @byHuoLuo)
		ByteUtil::writeUINT8(data, @byXiSui)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#时装炫耀
class SFlauntFashion
	attr_accessor:wFighterID #(UINT16)主将ID
	attr_accessor:byLevel #(UINT8)时装等级
	attr_accessor:byType #(UINT8)类型(0武器,1衣服)
	attr_accessor:weaponID #(UINT16)武器ID
	attr_accessor:armorID #(UINT16)衣服ID

	#构造函数
	def initialize
		@wFighterID = 0
		@byLevel = 0
		@byType = 0
		@weaponID = 0
		@armorID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wFighterID = @wFighterID
		obj.byLevel = @byLevel
		obj.byType = @byType
		obj.weaponID = @weaponID
		obj.armorID = @armorID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFlauntFashion.new
		s.wFighterID = ByteUtil::readUINT16(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.byType = ByteUtil::readUINT8(data)
		s.weaponID = ByteUtil::readUINT16(data)
		s.armorID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFlauntFashion::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT8(data, @byType)
		ByteUtil::writeUINT16(data, @weaponID)
		ByteUtil::writeUINT16(data, @armorID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#阵灵炫耀信息
class SFlauntPet
	attr_accessor:qwInstID #(UINT64)阵灵唯一ID
	attr_accessor:wFighterID #(UINT16)阵灵ID
	attr_accessor:byLevel #(UINT8)等级

	#构造函数
	def initialize
		@qwInstID = 0
		@wFighterID = 0
		@byLevel = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInstID = @qwInstID
		obj.wFighterID = @wFighterID
		obj.byLevel = @byLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFlauntPet.new
		s.qwInstID = ByteUtil::readUINT64(data)
		s.wFighterID = ByteUtil::readUINT16(data)
		s.byLevel = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFlauntPet::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT8(data, @byLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#坐骑炫耀信息
class SFlauntHorse
	attr_accessor:qwInstID #(UINT64)阵灵唯一ID
	attr_accessor:wFighterID #(UINT16)坐骑ID
	attr_accessor:byLevel #(UINT8)等级

	#构造函数
	def initialize
		@qwInstID = 0
		@wFighterID = 0
		@byLevel = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInstID = @qwInstID
		obj.wFighterID = @wFighterID
		obj.byLevel = @byLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFlauntHorse.new
		s.qwInstID = ByteUtil::readUINT64(data)
		s.wFighterID = ByteUtil::readUINT16(data)
		s.byLevel = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFlauntHorse::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT8(data, @byLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#成就炫耀信息
class SFlauntAchievement
	attr_accessor:qwInstID #(UINT64)成就唯一ID
	attr_accessor:wAchievementID #(UINT16)成就ID

	#构造函数
	def initialize
		@qwInstID = 0
		@wAchievementID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInstID = @qwInstID
		obj.wAchievementID = @wAchievementID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFlauntAchievement.new
		s.qwInstID = ByteUtil::readUINT64(data)
		s.wAchievementID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFlauntAchievement::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT16(data, @wAchievementID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[Whisper:私聊]的返回的参数组成的结构体
class SRetParam_Whisper
	attr_accessor:wMsgID#(UINT16)返回错误码（0为没有错误）

	#构造函数
	def initialize
		@wMsgID = 0
	end
end

#函数[GetShowInfo:获取炫耀信息]的返回的参数组成的结构体
class SRetParam_GetShowInfo
	attr_accessor:rSenderInfo#(类类型：SSenderInfo)发送者信息
	attr_accessor:strShowInfo#(string)展示信息序列化

	#构造函数
	def initialize
		@rSenderInfo = SSenderInfo.new
		@strShowInfo = ''
	end
end

#函数[ReqWhisperInfo:请求私聊信息]的返回的参数组成的结构体
class SRetParam_ReqWhisperInfo
	attr_accessor:whisperInfo#(类类型：SWhisperInfo)获取私聊对方信息返回

	#构造函数
	def initialize
		@whisperInfo = SWhisperInfo.new
	end
end

#协议类：全局聊天协议
class GlobalChatProtBase < ProtocolBase
	#以下为发送函数
	#发送：聊天
	def send_Chat(
		eChannelType,  #(枚举类型：EChannelType)通道类型
		strInfo,  #(string)聊天信息
		vecShowInfo #(SShowInfo的数组)炫耀物品信息
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eChannelType)
		ByteUtil::writeSTRING(data, strInfo)
		SShowInfo::vectorToStream(data, vecShowInfo)
		return @svrHandler.sendPacket(data)
	end

	#发送：私聊
	def send_Whisper(
		qwUsrID,  #(UINT64)帐号ID
		strInfo,  #(string)聊天信息
		vecShowInfo #(SShowInfo的数组)炫耀物品信息
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwUsrID)
		ByteUtil::writeSTRING(data, strInfo)
		SShowInfo::vectorToStream(data, vecShowInfo)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取炫耀信息
	def send_GetShowInfo(
		qwInstID #(UINT64)唯一ID
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求私聊信息
	def send_ReqWhisperInfo(
		strReceiveName #(string)玩家名字
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeSTRING(data, strReceiveName)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：聊天信息通知
	def onRecv_ChatInfoNotify(
		eChannelType, #(枚举类型：EChannelType)通道类型
		rSenderInfo, #(类类型：SSenderInfo)发送者信息
		strInfo, #(string)聊天信息
		vecShowInfo #(SShowInfo的数组)炫耀物品信息
	)
		raise NotImplementedError
	end
	#接收：私聊错误通知
	def onRecv_WhisperErrorNotify(
		eErrType, #(枚举类型：EWhisperErrorType)错误类型
		qwUsrID #(UINT64)帐号ID
	)
		raise NotImplementedError
	end
	#接收：私聊信息通知
	def onRecv_WhisperInfoNotify(
		rSenderInfo, #(类类型：SSenderInfo)发送者信息
		strInfo, #(string)私聊信息
		vecShowInfo #(SShowInfo的数组)炫耀物品信息
	)
		raise NotImplementedError
	end
	#接收：系统信息通知
	def onRecv_SystemMsgNotify(
		eChannelType, #(枚举类型：EChannelType)通道类型
		strInfo, #(string)聊天信息
		eSubType #(枚举类型：EChannelSubType)额外信息
	)
		raise NotImplementedError
	end
	#接收：系统MsgID通知
	def onRecv_SystemMsgIDNotify(
		wMsgID #(UINT16)消息ID
	)
		raise NotImplementedError
	end
	#接收：系统MsgID通知
	def onRecv_SystemFormatMsgIDNotify(
		wMsgID, #(UINT16)消息ID
		vecStr #(string数组)聊天信息参数
	)
		raise NotImplementedError
	end
	#接收：系统弹窗和公告更新通知
	def onRecv_SysDialogAndNoticeUpdateNotify(
		byNotifyType #(UINT8)通知类型1:系统弹窗通知；2、公告更新通知
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：私聊
	def onReturn_Whisper(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Whisper)返回的参数
	)
	end

	#返回：获取炫耀信息
	def onReturn_GetShowInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetShowInfo)返回的参数
	)
	end

	#返回：请求私聊信息
	def onReturn_ReqWhisperInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqWhisperInfo)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：聊天信息通知
	def _doRecv_ChatInfoNotify(data)
		eChannelType = ByteUtil::readUINT8(data)
		rSenderInfo = SSenderInfo::fromStream(data)
		strInfo = ByteUtil::readSTRING(data)
		vecShowInfo = SShowInfo::vectorFromStream(data)
		return onRecv_ChatInfoNotify(eChannelType, rSenderInfo, strInfo, vecShowInfo)
	end

	#接收处理：私聊错误通知
	def _doRecv_WhisperErrorNotify(data)
		eErrType = ByteUtil::readUINT8(data)
		qwUsrID = ByteUtil::readUINT64(data)
		return onRecv_WhisperErrorNotify(eErrType, qwUsrID)
	end

	#接收处理：私聊信息通知
	def _doRecv_WhisperInfoNotify(data)
		rSenderInfo = SSenderInfo::fromStream(data)
		strInfo = ByteUtil::readSTRING(data)
		vecShowInfo = SShowInfo::vectorFromStream(data)
		return onRecv_WhisperInfoNotify(rSenderInfo, strInfo, vecShowInfo)
	end

	#接收处理：系统信息通知
	def _doRecv_SystemMsgNotify(data)
		eChannelType = ByteUtil::readUINT8(data)
		strInfo = ByteUtil::readSTRING(data)
		eSubType = ByteUtil::readUINT8(data)
		return onRecv_SystemMsgNotify(eChannelType, strInfo, eSubType)
	end

	#接收处理：系统MsgID通知
	def _doRecv_SystemMsgIDNotify(data)
		wMsgID = ByteUtil::readUINT16(data)
		return onRecv_SystemMsgIDNotify(wMsgID)
	end

	#接收处理：系统MsgID通知
	def _doRecv_SystemFormatMsgIDNotify(data)
		wMsgID = ByteUtil::readUINT16(data)
		vecStr = ByteUtil::readVecSTRING(data)
		return onRecv_SystemFormatMsgIDNotify(wMsgID, vecStr)
	end

	#接收处理：系统弹窗和公告更新通知
	def _doRecv_SysDialogAndNoticeUpdateNotify(data)
		byNotifyType = ByteUtil::readUINT8(data)
		return onRecv_SysDialogAndNoticeUpdateNotify(byNotifyType)
	end

#以下为返回处理函数
	#返回处理：私聊
	def _doReturn_Whisper(data)
		retParam = SRetParam_Whisper.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		wMsgID = ByteUtil::readUINT16(data) #(UINT16)返回错误码（0为没有错误）
		retParam.wMsgID = wMsgID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_Whisper(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：私聊
	def _onTimeOut_Whisper(sessionID)
		retParam = SRetParam_Whisper.new;
		onReturn_Whisper(2, retParam)
	end

	#返回处理：获取炫耀信息
	def _doReturn_GetShowInfo(data)
		retParam = SRetParam_GetShowInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		rSenderInfo = SSenderInfo::fromStream(data) #(类类型：SSenderInfo)发送者信息
		strShowInfo = ByteUtil::readSTRING(data) #(string)展示信息序列化
		retParam.rSenderInfo = rSenderInfo
		retParam.strShowInfo = strShowInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetShowInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取炫耀信息
	def _onTimeOut_GetShowInfo(sessionID)
		retParam = SRetParam_GetShowInfo.new;
		onReturn_GetShowInfo(2, retParam)
	end

	#返回处理：请求私聊信息
	def _doReturn_ReqWhisperInfo(data)
		retParam = SRetParam_ReqWhisperInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		whisperInfo = SWhisperInfo::fromStream(data) #(类类型：SWhisperInfo)获取私聊对方信息返回
		retParam.whisperInfo = whisperInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqWhisperInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求私聊信息
	def _onTimeOut_ReqWhisperInfo(sessionID)
		retParam = SRetParam_ReqWhisperInfo.new;
		onReturn_ReqWhisperInfo(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 28;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_ChatInfoNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_WhisperErrorNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_WhisperInfoNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_SystemMsgNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_SystemMsgIDNotify' #FuncID: 5
		@recvFuncList[5] = '_doRecv_SystemFormatMsgIDNotify' #FuncID: 6
		@recvFuncList[6] = '_doRecv_SysDialogAndNoticeUpdateNotify' #FuncID: 7

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_Whisper' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetShowInfo' #FuncID: 2
		@retFuncList[2] = '_doReturn_ReqWhisperInfo' #FuncID: 3

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_Whisper' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetShowInfo' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_ReqWhisperInfo' #FuncID: 3
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

