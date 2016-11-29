#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    ViewInfoProt.rb
#  Purpose:      查看信息协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ItemProtBase.rb'
require_relative './ProtoCommonBase.rb'
require_relative './RoleInfoDefineBase.rb'

#以下为类型定义

#出战散仙信息
class SBattleFighterData
	attr_accessor:qwInstID #(UINT64)散仙唯一ID
	attr_accessor:wFighterID #(UINT16)散仙模版
	attr_accessor:byFighterLevel #(UINT8)散仙等级
	attr_accessor:byTemplateID #(UINT8)渡劫模版Id
	attr_accessor:byLevel #(UINT8)渡劫等级

	#构造函数
	def initialize
		@qwInstID = 0
		@wFighterID = 0
		@byFighterLevel = 0
		@byTemplateID = 0
		@byLevel = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInstID = @qwInstID
		obj.wFighterID = @wFighterID
		obj.byFighterLevel = @byFighterLevel
		obj.byTemplateID = @byTemplateID
		obj.byLevel = @byLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBattleFighterData.new
		s.qwInstID = ByteUtil::readUINT64(data)
		s.wFighterID = ByteUtil::readUINT16(data)
		s.byFighterLevel = ByteUtil::readUINT8(data)
		s.byTemplateID = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBattleFighterData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT8(data, @byFighterLevel)
		ByteUtil::writeUINT8(data, @byTemplateID)
		ByteUtil::writeUINT8(data, @byLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#渡劫信息
class SDujieData
	attr_accessor:byTemplateID #(UINT8)渡劫模版Id
	attr_accessor:byLevel #(UINT8)渡劫等级

	#构造函数
	def initialize
		@byTemplateID = 0
		@byLevel = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byTemplateID = @byTemplateID
		obj.byLevel = @byLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDujieData.new
		s.byTemplateID = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDujieData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byTemplateID)
		ByteUtil::writeUINT8(data, @byLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#淬体（装备）信息
class SCTData
	attr_accessor:byLianPi #(UINT8)炼皮
	attr_accessor:byTongJin #(UINT8)通筋
	attr_accessor:byQiangJi #(UINT8)强肌
	attr_accessor:byDuanGu #(UINT8)锻骨
	attr_accessor:byHuoLuo #(UINT8)活络
	attr_accessor:byXiSui #(UINT8)洗髓

	#构造函数
	def initialize
		@byLianPi = 0
		@byTongJin = 0
		@byQiangJi = 0
		@byDuanGu = 0
		@byHuoLuo = 0
		@byXiSui = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byLianPi = @byLianPi
		obj.byTongJin = @byTongJin
		obj.byQiangJi = @byQiangJi
		obj.byDuanGu = @byDuanGu
		obj.byHuoLuo = @byHuoLuo
		obj.byXiSui = @byXiSui
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SCTData.new
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
			s = SCTData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
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

#心法数据
class SCittaData
	attr_accessor:dwCittaID #(UINT32)心法ID
	attr_accessor:byLevel #(UINT8)等级

	#构造函数
	def initialize
		@dwCittaID = 0
		@byLevel = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwCittaID = @dwCittaID
		obj.byLevel = @byLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SCittaData.new
		s.dwCittaID = ByteUtil::readUINT32(data)
		s.byLevel = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SCittaData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwCittaID)
		ByteUtil::writeUINT8(data, @byLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#稀有的法宝信息
class SRareTrumpData
	attr_accessor:wItemID #(UINT16)法宝模板
	attr_accessor:byTrumpLvl #(UINT8)法宝等级
	attr_accessor:bySelected #(UINT8)是否出战

	#构造函数
	def initialize
		@wItemID = 0
		@byTrumpLvl = 0
		@bySelected = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wItemID = @wItemID
		obj.byTrumpLvl = @byTrumpLvl
		obj.bySelected = @bySelected
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRareTrumpData.new
		s.wItemID = ByteUtil::readUINT16(data)
		s.byTrumpLvl = ByteUtil::readUINT8(data)
		s.bySelected = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRareTrumpData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeUINT8(data, @byTrumpLvl)
		ByteUtil::writeUINT8(data, @bySelected)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#坐骑信息
class SHorseData
	attr_accessor:dwHorseID #(UINT32)坐骑id
	attr_accessor:byHorseLvl #(UINT8)坐骑等级
	attr_accessor:bySelected #(UINT8)0-不跟随 1-跟随

	#构造函数
	def initialize
		@dwHorseID = 0
		@byHorseLvl = 0
		@bySelected = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwHorseID = @dwHorseID
		obj.byHorseLvl = @byHorseLvl
		obj.bySelected = @bySelected
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SHorseData.new
		s.dwHorseID = ByteUtil::readUINT32(data)
		s.byHorseLvl = ByteUtil::readUINT8(data)
		s.bySelected = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SHorseData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwHorseID)
		ByteUtil::writeUINT8(data, @byHorseLvl)
		ByteUtil::writeUINT8(data, @bySelected)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#出战美女信息
class SBeautyData
	attr_accessor:wBeautyID #(UINT16)美女ID
	attr_accessor:byLevel #(UINT8)美女等级
	attr_accessor:vecAttr #(SFtAttrMod的数组)美女属性

	#构造函数
	def initialize
		@wBeautyID = 0
		@byLevel = 0
		@vecAttr = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wBeautyID = @wBeautyID
		obj.byLevel = @byLevel
		obj.vecAttr = @vecAttr
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBeautyData.new
		s.wBeautyID = ByteUtil::readUINT16(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.vecAttr = SFtAttrMod::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBeautyData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wBeautyID)
		ByteUtil::writeUINT8(data, @byLevel)
		SFtAttrMod::vectorToStream(data, @vecAttr)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#时装信息
class SFashionData
	attr_accessor:wItemID #(UINT16)时装模板
	attr_accessor:byFashionLvl #(UINT8)时装等级
	attr_accessor:bySelected #(UINT8)是否选中

	#构造函数
	def initialize
		@wItemID = 0
		@byFashionLvl = 0
		@bySelected = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wItemID = @wItemID
		obj.byFashionLvl = @byFashionLvl
		obj.bySelected = @bySelected
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFashionData.new
		s.wItemID = ByteUtil::readUINT16(data)
		s.byFashionLvl = ByteUtil::readUINT8(data)
		s.bySelected = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFashionData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeUINT8(data, @byFashionLvl)
		ByteUtil::writeUINT8(data, @bySelected)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#收集信息
class SCollectionData
	attr_accessor:byCollectionLevel #(UINT8)收藏等级
	attr_accessor:dwAP #(UINT32)收藏点

	#构造函数
	def initialize
		@byCollectionLevel = 0
		@dwAP = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byCollectionLevel = @byCollectionLevel
		obj.dwAP = @dwAP
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SCollectionData.new
		s.byCollectionLevel = ByteUtil::readUINT8(data)
		s.dwAP = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SCollectionData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byCollectionLevel)
		ByteUtil::writeUINT32(data, @dwAP)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#称号信息
class STitleData
	attr_accessor:wTitleID #(UINT16)称号ID
	attr_accessor:bySelected #(UINT8)是否选中

	#构造函数
	def initialize
		@wTitleID = 0
		@bySelected = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wTitleID = @wTitleID
		obj.bySelected = @bySelected
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STitleData.new
		s.wTitleID = ByteUtil::readUINT16(data)
		s.bySelected = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STitleData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wTitleID)
		ByteUtil::writeUINT8(data, @bySelected)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮派技能信息
class SGuildSkillData
	attr_accessor:dwGuildSkillID #(UINT32)技能id
	attr_accessor:byGuildSkillLvl #(UINT8)技能等级

	#构造函数
	def initialize
		@dwGuildSkillID = 0
		@byGuildSkillLvl = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwGuildSkillID = @dwGuildSkillID
		obj.byGuildSkillLvl = @byGuildSkillLvl
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildSkillData.new
		s.dwGuildSkillID = ByteUtil::readUINT32(data)
		s.byGuildSkillLvl = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildSkillData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwGuildSkillID)
		ByteUtil::writeUINT8(data, @byGuildSkillLvl)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮派信息
class SGuildData
	attr_accessor:strName #(string)帮派名称
	attr_accessor:byGuildLvl #(UINT8)帮派等级
	attr_accessor:vecGuildSkill #(SGuildSkillData的数组)帮派技能

	#构造函数
	def initialize
		@strName = ''
		@byGuildLvl = 0
		@vecGuildSkill = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strName = @strName
		obj.byGuildLvl = @byGuildLvl
		obj.vecGuildSkill = @vecGuildSkill
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildData.new
		s.strName = ByteUtil::readSTRING(data)
		s.byGuildLvl = ByteUtil::readUINT8(data)
		s.vecGuildSkill = SGuildSkillData::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @byGuildLvl)
		SGuildSkillData::vectorToStream(data, @vecGuildSkill)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#参与战斗的技能信息
class SSkillData
	attr_accessor:dwSkillID #(UINT32)技能id
	attr_accessor:bySkillLvl #(UINT8)技能等级
	attr_accessor:bySkillQuality #(UINT8)技能品质

	#构造函数
	def initialize
		@dwSkillID = 0
		@bySkillLvl = 0
		@bySkillQuality = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwSkillID = @dwSkillID
		obj.bySkillLvl = @bySkillLvl
		obj.bySkillQuality = @bySkillQuality
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSkillData.new
		s.dwSkillID = ByteUtil::readUINT32(data)
		s.bySkillLvl = ByteUtil::readUINT8(data)
		s.bySkillQuality = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSkillData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwSkillID)
		ByteUtil::writeUINT8(data, @bySkillLvl)
		ByteUtil::writeUINT8(data, @bySkillQuality)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#兽魂
class SBeastSoulData
	attr_accessor:vecBeasSoulInfo #(SBeastSoulInfo的数组)兽魂
	attr_accessor:vecAttr #(SFtAttrMod的数组)兽魂属性

	#构造函数
	def initialize
		@vecBeasSoulInfo = Array.new
		@vecAttr = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.vecBeasSoulInfo = @vecBeasSoulInfo
		obj.vecAttr = @vecAttr
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBeastSoulData.new
		s.vecBeasSoulInfo = SBeastSoulInfo::vectorFromStream(data)
		s.vecAttr = SFtAttrMod::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBeastSoulData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		SBeastSoulInfo::vectorToStream(data, @vecBeasSoulInfo)
		SFtAttrMod::vectorToStream(data, @vecAttr)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#组合
class SCombData
	attr_accessor:byGroupID #(UINT8)组合ID
	attr_accessor:byLevel #(UINT8)组合等级
	attr_accessor:bySelected #(UINT8)是否出战

	#构造函数
	def initialize
		@byGroupID = 0
		@byLevel = 0
		@bySelected = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byGroupID = @byGroupID
		obj.byLevel = @byLevel
		obj.bySelected = @bySelected
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SCombData.new
		s.byGroupID = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.bySelected = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SCombData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byGroupID)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT8(data, @bySelected)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#主角信息
class SRoleData
	attr_accessor:strName #(string)玩家名字
	attr_accessor:eCareer #(枚类型：ProtoCommon::ECareerType)职业
	attr_accessor:byLevel #(UINT8)玩家等级
	attr_accessor:dwBTPoint #(UINT32)战斗力
	attr_accessor:vecAttr #(SFtAttrMod的数组)总属性
	attr_accessor:vecBattleFighter #(SBattleFighterData的数组)出战的散仙
	attr_accessor:sDujie #(类类型：SDujieData)渡劫
	attr_accessor:sCuiTi #(类类型：SCTData)淬体(装备)
	attr_accessor:vecBaoshi #(UINT32数组)宝石
	attr_accessor:vecCitta #(SCittaData的数组)心法
	attr_accessor:vecTrump #(SEquipTrump的数组)法宝
	attr_accessor:vecRareTrump #(SRareTrumpData的数组)稀有(被动）法宝
	attr_accessor:sBeauty #(类类型：SBeautyData)美女
	attr_accessor:sBeastSoul #(类类型：SBeastSoulData)魂魄
	attr_accessor:vecComb #(SCombData的数组)组合
	attr_accessor:vecSkill #(SSkillData的数组)技能
	attr_accessor:vecHorse #(SHorseData的数组)坐骑
	attr_accessor:vecFashion #(SFashionData的数组)已激活的时装
	attr_accessor:vecTitle #(STitleData的数组)已激活的称号
	attr_accessor:vecGuild #(SGuildData的数组)帮派
	attr_accessor:vecTianBookAttr #(SFtAttrMod的数组)天书属性

	#构造函数
	def initialize
		@strName = ''
		@eCareer = 0
		@byLevel = 0
		@dwBTPoint = 0
		@vecAttr = Array.new
		@vecBattleFighter = Array.new
		@sDujie = SDujieData.new
		@sCuiTi = SCTData.new
		@vecBaoshi = Array.new
		@vecCitta = Array.new
		@vecTrump = Array.new
		@vecRareTrump = Array.new
		@sBeauty = SBeautyData.new
		@sBeastSoul = SBeastSoulData.new
		@vecComb = Array.new
		@vecSkill = Array.new
		@vecHorse = Array.new
		@vecFashion = Array.new
		@vecTitle = Array.new
		@vecGuild = Array.new
		@vecTianBookAttr = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.strName = @strName
		obj.eCareer = @eCareer
		obj.byLevel = @byLevel
		obj.dwBTPoint = @dwBTPoint
		obj.vecAttr = @vecAttr
		obj.vecBattleFighter = @vecBattleFighter
		obj.sDujie = @sDujie
		obj.sCuiTi = @sCuiTi
		obj.vecBaoshi = @vecBaoshi
		obj.vecCitta = @vecCitta
		obj.vecTrump = @vecTrump
		obj.vecRareTrump = @vecRareTrump
		obj.sBeauty = @sBeauty
		obj.sBeastSoul = @sBeastSoul
		obj.vecComb = @vecComb
		obj.vecSkill = @vecSkill
		obj.vecHorse = @vecHorse
		obj.vecFashion = @vecFashion
		obj.vecTitle = @vecTitle
		obj.vecGuild = @vecGuild
		obj.vecTianBookAttr = @vecTianBookAttr
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRoleData.new
		s.strName = ByteUtil::readSTRING(data)
		s.eCareer = ByteUtil::readUINT8(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.dwBTPoint = ByteUtil::readUINT32(data)
		s.vecAttr = SFtAttrMod::vectorFromStream(data)
		s.vecBattleFighter = SBattleFighterData::vectorFromStream(data)
		s.sDujie = SDujieData::fromStream(data)
		s.sCuiTi = SCTData::fromStream(data)
		s.vecBaoshi = ByteUtil::readVecUINT32(data)
		s.vecCitta = SCittaData::vectorFromStream(data)
		s.vecTrump = SEquipTrump::vectorFromStream(data)
		s.vecRareTrump = SRareTrumpData::vectorFromStream(data)
		s.sBeauty = SBeautyData::fromStream(data)
		s.sBeastSoul = SBeastSoulData::fromStream(data)
		s.vecComb = SCombData::vectorFromStream(data)
		s.vecSkill = SSkillData::vectorFromStream(data)
		s.vecHorse = SHorseData::vectorFromStream(data)
		s.vecFashion = SFashionData::vectorFromStream(data)
		s.vecTitle = STitleData::vectorFromStream(data)
		s.vecGuild = SGuildData::vectorFromStream(data)
		s.vecTianBookAttr = SFtAttrMod::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRoleData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @eCareer)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwBTPoint)
		SFtAttrMod::vectorToStream(data, @vecAttr)
		SBattleFighterData::vectorToStream(data, @vecBattleFighter)
		@sDujie.toStream(data)
		@sCuiTi.toStream(data)
		ByteUtil::writeVecUINT32(data, @vecBaoshi)
		SCittaData::vectorToStream(data, @vecCitta)
		SEquipTrump::vectorToStream(data, @vecTrump)
		SRareTrumpData::vectorToStream(data, @vecRareTrump)
		@sBeauty.toStream(data)
		@sBeastSoul.toStream(data)
		SCombData::vectorToStream(data, @vecComb)
		SSkillData::vectorToStream(data, @vecSkill)
		SHorseData::vectorToStream(data, @vecHorse)
		SFashionData::vectorToStream(data, @vecFashion)
		STitleData::vectorToStream(data, @vecTitle)
		SGuildData::vectorToStream(data, @vecGuild)
		SFtAttrMod::vectorToStream(data, @vecTianBookAttr)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#散仙信息
class SFighterData
	attr_accessor:wFighterID #(UINT16)散仙模版
	attr_accessor:byLevel #(UINT8)散仙等级
	attr_accessor:dwBTPoint #(UINT32)战斗力
	attr_accessor:vecAttr #(SFtAttrMod的数组)将属性
	attr_accessor:sDujie #(类类型：SDujieData)渡劫
	attr_accessor:vecSkill #(SSkillData的数组)技能
	attr_accessor:sCuiTi #(类类型：SCTData)淬体
	attr_accessor:vecBaoshi #(UINT32数组)宝石
	attr_accessor:vecCitta #(SCittaData的数组)心法
	attr_accessor:vecTrump #(SEquipTrump的数组)法宝

	#构造函数
	def initialize
		@wFighterID = 0
		@byLevel = 0
		@dwBTPoint = 0
		@vecAttr = Array.new
		@sDujie = SDujieData.new
		@vecSkill = Array.new
		@sCuiTi = SCTData.new
		@vecBaoshi = Array.new
		@vecCitta = Array.new
		@vecTrump = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wFighterID = @wFighterID
		obj.byLevel = @byLevel
		obj.dwBTPoint = @dwBTPoint
		obj.vecAttr = @vecAttr
		obj.sDujie = @sDujie
		obj.vecSkill = @vecSkill
		obj.sCuiTi = @sCuiTi
		obj.vecBaoshi = @vecBaoshi
		obj.vecCitta = @vecCitta
		obj.vecTrump = @vecTrump
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFighterData.new
		s.wFighterID = ByteUtil::readUINT16(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.dwBTPoint = ByteUtil::readUINT32(data)
		s.vecAttr = SFtAttrMod::vectorFromStream(data)
		s.sDujie = SDujieData::fromStream(data)
		s.vecSkill = SSkillData::vectorFromStream(data)
		s.sCuiTi = SCTData::fromStream(data)
		s.vecBaoshi = ByteUtil::readVecUINT32(data)
		s.vecCitta = SCittaData::vectorFromStream(data)
		s.vecTrump = SEquipTrump::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFighterData::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwBTPoint)
		SFtAttrMod::vectorToStream(data, @vecAttr)
		@sDujie.toStream(data)
		SSkillData::vectorToStream(data, @vecSkill)
		@sCuiTi.toStream(data)
		ByteUtil::writeVecUINT32(data, @vecBaoshi)
		SCittaData::vectorToStream(data, @vecCitta)
		SEquipTrump::vectorToStream(data, @vecTrump)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetRoleInfo:获取对方主角信息]的返回的参数组成的结构体
class SRetParam_GetRoleInfo
	attr_accessor:RoleData#(类类型：SRoleData)对方主角信息

	#构造函数
	def initialize
		@RoleData = SRoleData.new
	end
end

#函数[GetFighterInfo:获取散仙信息]的返回的参数组成的结构体
class SRetParam_GetFighterInfo
	attr_accessor:FighterData#(类类型：SFighterData)对方散仙信息

	#构造函数
	def initialize
		@FighterData = SFighterData.new
	end
end

#协议类：查看信息协议
class ViewInfoProtBase < ProtocolBase
	#以下为发送函数
	#发送：获取对方主角信息
	def send_GetRoleInfo(
		strReceiveName #(string)对方玩家名字
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeSTRING(data, strReceiveName)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取散仙信息
	def send_GetFighterInfo(
		strReceiveName,  #(string)对方玩家名字
		qwInstID #(UINT64)散仙唯一ID
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeSTRING(data, strReceiveName)
		ByteUtil::writeUINT64(data, qwInstID)
		return @svrHandler.sendPacket(data)
	end

#以下的返回函数需要重载
	#返回：获取对方主角信息
	def onReturn_GetRoleInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetRoleInfo)返回的参数
	)
	end

	#返回：获取散仙信息
	def onReturn_GetFighterInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetFighterInfo)返回的参数
	)
	end

	#返回处理：获取对方主角信息
	def _doReturn_GetRoleInfo(data)
		retParam = SRetParam_GetRoleInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		RoleData = SRoleData::fromStream(data) #(类类型：SRoleData)对方主角信息
		retParam.RoleData = RoleData
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetRoleInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取对方主角信息
	def _onTimeOut_GetRoleInfo(sessionID)
		retParam = SRetParam_GetRoleInfo.new;
		onReturn_GetRoleInfo(2, retParam)
	end

	#返回处理：获取散仙信息
	def _doReturn_GetFighterInfo(data)
		retParam = SRetParam_GetFighterInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		FighterData = SFighterData::fromStream(data) #(类类型：SFighterData)对方散仙信息
		retParam.FighterData = FighterData
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetFighterInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取散仙信息
	def _onTimeOut_GetFighterInfo(sessionID)
		retParam = SRetParam_GetFighterInfo.new;
		onReturn_GetFighterInfo(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 82;
		@recvFuncList = Array.new

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetRoleInfo' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetFighterInfo' #FuncID: 2

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetRoleInfo' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetFighterInfo' #FuncID: 2
	end

	def handleMessage(data)
		funcID = ByteUtil::readINT8(data);
		if funcID == 0 || funcID < -@retFuncList.length
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

