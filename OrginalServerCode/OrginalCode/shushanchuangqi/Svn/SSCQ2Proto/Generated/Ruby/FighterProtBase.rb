#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    FighterProt.rb
#  Purpose:      道具相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ItemProtBase.rb'
require_relative './PropInfoBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#将类型
class EFighterType
	EFIGHTER = 0#将
	EFIGHTERPLAYER = 1#主将
	EFIGHTERHERO = 2#散仙
	EFIGHTERMONSTER = 3#怪
	EFIGHTERMAX = 4#将类型结束
end

#技能操作结果
class ESkillResult
	ESKILLSUCC = 0#成功
	ESKILLFAILED = 1#失败
	ESKILLNOTEXIST = 2#没有此技能
	ESKILLLEVELMAX = 3#已达最高等级
	ESKILLLEVELERR = 4#玩家等级不足
	ESKILLNOTUP = 5#未装备此技能
	ESKILLPEXPERR = 6#修为不足
	ESKILLSOPERR = 7#阅历不足
	ESKILLSIGILERR = 8#符印不足
	ESKILLCENTSYERR = 9#仙元不足
	ESKILLPOTENERR = 10#潜力不足
	ERUNENOTEXIST = 11#符文不存在
	ERUNELEVELMAX = 12#符文已达最高等级
	ERUNELEVELERR = 13#玩家等级不足
	EADVNOTEXIST = 14#进阶不存在
	EADVLEVELGTSKILLLEVELERR = 15#进阶等级大于技能等级
	EITEMNOTENOUGH = 16#物品不足
end

#求签类型
class EDrawType
	EDRAWTYPENONE = 0#无效类型
	EDRAWTYPENORMAL = 1#普通求签(银币)
	EDRAWTYPEADVANCE = 2#高级求签(仙石)
	EDRAWTYPEMAX = 3#最大类型
end

#求签类型
class EDrawRewardType
	EDRAWREWARDTYPENONE = 0#无效类型
	EDRAWREWARDTYPEBLUE = 1#蓝色仙缘
	EDRAWREWARDTYPEPURPLE = 2#紫色仙缘
	EDRAWREWARDTYPEORANGE = 3#橙色仙缘
	EDRAWREWARDTYPEMAX = 4#最大类型
end

#求签结果
class EDrawResult
	EDRAWRESULTSUCCESS = 0#求签成功
	EDRAWRESULTFAILED = 1#求签失败
	EDRAWRESULTLACKOFCOUNT = 2#次数不足
	EDRAWRESULTLACKOFMONEY = 3#金钱不足
	EDRAWRESULTMAX = 4#求签结果最大值
end

#招募返回
class ERecruitResult
	ERECRUITSUCC = 0#成功
	ERECRUITFAILED = 1#失败
	ERECRUITALREADY = 2#已招募
	ERECRUITLACKOFMONEY = 3#货币不足
	ERECRUITLEVELLIMITED = 4#等级不足
end

#淬体
class ECuiTiType
	ECUITILIANPI = 0#炼皮-武器
	ECUITITONGJIN = 1#通筋-头盔
	ECUITIQIANGJI = 2#强肌-戒指
	ECUITIDUANGU = 3#锻骨-衣服
	ECUITIHUOLUO = 4#活络-鞋子
	ECUITIXISUI = 5#洗髓-项链
	ECUITIMAX = 6#淬体上限
end

#淬体
class ECuiTiResult
	ECUITIRESULTSUCC = 0#成功
	ECUITIRESULTFAILED = 1#失败
	ECUITIRESULTSILVERERR = 2#银币不足
	ECUITIRESULTLVLMAXERR = 3#已达最高等级
	ECUITIRESULTPLAYERLVLERR = 4#已达将最高等级
	ECUITIRESULTUNLOCK = 5#未解锁
end

#转移
class EShiftResult
	ESHIFTSUCC = 0#成功
	ESHIFTFAILED = 1#失败
	ESHIFTGOLDERR = 2#仙石不足
end

#散仙等级同步
class ESyncLevelResult
	ESYNCLEVELSUCC = 0#成功
	ESYNCLEVELFAILED = 1#失败
	ESYNCLEVELALREADY = 2#已是最高等级
	ESYNCLEVELMONEY = 3#同步等级所需银币不足
	ESYNCLEVELMONEYMORE = 4#同步等级成功但所需银币不足无法继续升级
end

#散仙渡劫
class EDujieResult
	EDUJIESUCC = 0#成功
	EDUJIEFAILED = 1#失败
	EDUJIEITEMERR = 2#渡劫符不足
	EDUJIELEVELMAXERR = 3#渡劫等级已是最高级
end

#心法返回
class EXinFaResult
	EXINFASUCC = 0#成功
	EXINFAFAILED = 1#失败
end

#散仙组合返回
class ECombinationResult
	ECOMBINATIONSUCC = 0#成功
	ECOMBINATIONFAILED = 1#失败
	ECOMBINATIONMAXLEVEL = 2#散仙组合已达最高等级
	ECOMBINATIONHAVED = 3#该散仙组合已激活
	ECOMBINATIONNOTHAVED = 4#该散仙组合未激活
	ECOMBINATIONFIGHTERERR = 5#散仙未招募满
	ECOMBINATIONITEMERR = 6#道具不足
	ECOMBINATIONMAINLEVELERR = 7#玩家主将等级不足
end

#散功返回
class EDismissResult
	EDISMISSSUCC = 0#成功
	EDISMISSFAILED = 1#失败
	ENEEDTAKEOFFSTONE = 2#需要卸下宝石
end

#购买散仙返回
class EFighterBuyResult
	EFIGHTERBUYSUCC = 0#成功
	EFIGHTERBUYFAILED = 1#失败
	EFIGHTERBUYALREADY = 2#已购买
	EFIGHTERBUYLACKOFMONEY = 3#货币不足
end

#玩家购买散仙信息
class SFighterBuyInfo
	attr_accessor:wFighterID #(UINT16)将类型ID
	attr_accessor:byFighterBuyStatus #(UINT8)购买状态（0：未购买；1：已购买）

	#构造函数
	def initialize
		@wFighterID = 0
		@byFighterBuyStatus = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wFighterID = @wFighterID
		obj.byFighterBuyStatus = @byFighterBuyStatus
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFighterBuyInfo.new
		s.wFighterID = ByteUtil::readUINT16(data)
		s.byFighterBuyStatus = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFighterBuyInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT8(data, @byFighterBuyStatus)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家的散仙组合信息
class SFighterCombination
	attr_accessor:byGroupID #(UINT8)散仙组合ID
	attr_accessor:byGroupLvl #(UINT8)散仙组合等级
	attr_accessor:dwGroupExp #(UINT32)散仙组合当前经验值
	attr_accessor:byInLineUp #(UINT8)是否出战在阵型(0未出战 1已出战)
	attr_accessor:byInEMei #(UINT8)是否出战在守卫峨眉(0未出战 1已出战)

	#构造函数
	def initialize
		@byGroupID = 0
		@byGroupLvl = 0
		@dwGroupExp = 0
		@byInLineUp = 0
		@byInEMei = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byGroupID = @byGroupID
		obj.byGroupLvl = @byGroupLvl
		obj.dwGroupExp = @dwGroupExp
		obj.byInLineUp = @byInLineUp
		obj.byInEMei = @byInEMei
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFighterCombination.new
		s.byGroupID = ByteUtil::readUINT8(data)
		s.byGroupLvl = ByteUtil::readUINT8(data)
		s.dwGroupExp = ByteUtil::readUINT32(data)
		s.byInLineUp = ByteUtil::readUINT8(data)
		s.byInEMei = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFighterCombination::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byGroupID)
		ByteUtil::writeUINT8(data, @byGroupLvl)
		ByteUtil::writeUINT32(data, @dwGroupExp)
		ByteUtil::writeUINT8(data, @byInLineUp)
		ByteUtil::writeUINT8(data, @byInEMei)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#数据库同步到游戏服务器的将信息
class SFighterDBInfo
	attr_accessor:qwInstID #(UINT64)将唯一ID
	attr_accessor:qwRoleID #(UINT64)所属玩家ID
	attr_accessor:wFighterID #(UINT16)将类型ID
	attr_accessor:byRecruited #(UINT8)是否已招募
	attr_accessor:byStar #(UINT8)当前星级
	attr_accessor:iSlot #(INT32)将位置
	attr_accessor:iPos #(INT32)阵型中的位置
	attr_accessor:fPotential #(float)潜力
	attr_accessor:fCapacity #(float)资质
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:qwExp #(UINT64)经验
	attr_accessor:byLianPi #(UINT8)炼皮
	attr_accessor:byTongJin #(UINT8)通筋
	attr_accessor:byQiangJi #(UINT8)强肌
	attr_accessor:byDuanGu #(UINT8)锻骨
	attr_accessor:byHuoLuo #(UINT8)活络
	attr_accessor:byXiSui #(UINT8)洗髓
	attr_accessor:dwDujieExp #(UINT32)散仙渡劫经验
	attr_accessor:dwSpiritPower #(UINT32)元神力

	#构造函数
	def initialize
		@qwInstID = 0
		@qwRoleID = 0
		@wFighterID = 0
		@byRecruited = 0
		@byStar = 0
		@iSlot = 0
		@iPos = 0
		@fPotential = 0
		@fCapacity = 0
		@byLevel = 0
		@qwExp = 0
		@byLianPi = 0
		@byTongJin = 0
		@byQiangJi = 0
		@byDuanGu = 0
		@byHuoLuo = 0
		@byXiSui = 0
		@dwDujieExp = 0
		@dwSpiritPower = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInstID = @qwInstID
		obj.qwRoleID = @qwRoleID
		obj.wFighterID = @wFighterID
		obj.byRecruited = @byRecruited
		obj.byStar = @byStar
		obj.iSlot = @iSlot
		obj.iPos = @iPos
		obj.fPotential = @fPotential
		obj.fCapacity = @fCapacity
		obj.byLevel = @byLevel
		obj.qwExp = @qwExp
		obj.byLianPi = @byLianPi
		obj.byTongJin = @byTongJin
		obj.byQiangJi = @byQiangJi
		obj.byDuanGu = @byDuanGu
		obj.byHuoLuo = @byHuoLuo
		obj.byXiSui = @byXiSui
		obj.dwDujieExp = @dwDujieExp
		obj.dwSpiritPower = @dwSpiritPower
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFighterDBInfo.new
		s.qwInstID = ByteUtil::readUINT64(data)
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wFighterID = ByteUtil::readUINT16(data)
		s.byRecruited = ByteUtil::readUINT8(data)
		s.byStar = ByteUtil::readUINT8(data)
		s.iSlot = ByteUtil::readINT32(data)
		s.iPos = ByteUtil::readINT32(data)
		s.fPotential = ByteUtil::readFLOAT(data)
		s.fCapacity = ByteUtil::readFLOAT(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.qwExp = ByteUtil::readUINT64(data)
		s.byLianPi = ByteUtil::readUINT8(data)
		s.byTongJin = ByteUtil::readUINT8(data)
		s.byQiangJi = ByteUtil::readUINT8(data)
		s.byDuanGu = ByteUtil::readUINT8(data)
		s.byHuoLuo = ByteUtil::readUINT8(data)
		s.byXiSui = ByteUtil::readUINT8(data)
		s.dwDujieExp = ByteUtil::readUINT32(data)
		s.dwSpiritPower = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFighterDBInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT8(data, @byRecruited)
		ByteUtil::writeUINT8(data, @byStar)
		ByteUtil::writeINT32(data, @iSlot)
		ByteUtil::writeINT32(data, @iPos)
		ByteUtil::writeFLOAT(data, @fPotential)
		ByteUtil::writeFLOAT(data, @fCapacity)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT64(data, @qwExp)
		ByteUtil::writeUINT8(data, @byLianPi)
		ByteUtil::writeUINT8(data, @byTongJin)
		ByteUtil::writeUINT8(data, @byQiangJi)
		ByteUtil::writeUINT8(data, @byDuanGu)
		ByteUtil::writeUINT8(data, @byHuoLuo)
		ByteUtil::writeUINT8(data, @byXiSui)
		ByteUtil::writeUINT32(data, @dwDujieExp)
		ByteUtil::writeUINT32(data, @dwSpiritPower)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#数据库同步到游戏服务器的技能信息
class SSkillDBInfo
	attr_accessor:qwOwnerID #(UINT64)将唯一ID
	attr_accessor:dwUpSkill1 #(UINT32)使用中的技能1
	attr_accessor:dwUpSkill2 #(UINT32)使用中的技能2
	attr_accessor:dwUpSkill3 #(UINT32)使用中的技能3
	attr_accessor:dwUpSkill4 #(UINT32)使用中的技能4
	attr_accessor:dwUpSkill5 #(UINT32)使用中的技能5
	attr_accessor:dwUpSkill6 #(UINT32)使用中的技能6
	attr_accessor:dwSkill1 #(UINT32)技能1
	attr_accessor:dwSkill2 #(UINT32)技能2
	attr_accessor:dwSkill3 #(UINT32)技能3
	attr_accessor:dwSkill4 #(UINT32)技能4
	attr_accessor:dwSkill5 #(UINT32)技能5
	attr_accessor:dwSkill6 #(UINT32)技能6
	attr_accessor:dwSkill7 #(UINT32)技能7
	attr_accessor:dwSkill8 #(UINT32)技能8
	attr_accessor:dwSkill9 #(UINT32)技能9
	attr_accessor:dwRune1 #(UINT32)符文1
	attr_accessor:dwRune2 #(UINT32)符文2
	attr_accessor:dwRune3 #(UINT32)符文3
	attr_accessor:dwRune4 #(UINT32)符文4
	attr_accessor:dwRune5 #(UINT32)符文5
	attr_accessor:dwRune6 #(UINT32)符文6
	attr_accessor:dwRune7 #(UINT32)符文7
	attr_accessor:dwRune8 #(UINT32)符文8
	attr_accessor:dwRune9 #(UINT32)符文9
	attr_accessor:dwSkillAdv1 #(UINT32)技能进阶1
	attr_accessor:dwSkillAdv2 #(UINT32)技能进阶2
	attr_accessor:dwSkillAdv3 #(UINT32)技能进阶3
	attr_accessor:dwSkillAdv4 #(UINT32)技能进阶4
	attr_accessor:dwSkillAdv5 #(UINT32)技能进阶5
	attr_accessor:dwSkillAdv6 #(UINT32)技能进阶6
	attr_accessor:dwSkillAdv7 #(UINT32)技能进阶7
	attr_accessor:dwSkillAdv8 #(UINT32)技能进阶8
	attr_accessor:dwSkillAdv9 #(UINT32)技能进阶9

	#构造函数
	def initialize
		@qwOwnerID = 0
		@dwUpSkill1 = 0
		@dwUpSkill2 = 0
		@dwUpSkill3 = 0
		@dwUpSkill4 = 0
		@dwUpSkill5 = 0
		@dwUpSkill6 = 0
		@dwSkill1 = 0
		@dwSkill2 = 0
		@dwSkill3 = 0
		@dwSkill4 = 0
		@dwSkill5 = 0
		@dwSkill6 = 0
		@dwSkill7 = 0
		@dwSkill8 = 0
		@dwSkill9 = 0
		@dwRune1 = 0
		@dwRune2 = 0
		@dwRune3 = 0
		@dwRune4 = 0
		@dwRune5 = 0
		@dwRune6 = 0
		@dwRune7 = 0
		@dwRune8 = 0
		@dwRune9 = 0
		@dwSkillAdv1 = 0
		@dwSkillAdv2 = 0
		@dwSkillAdv3 = 0
		@dwSkillAdv4 = 0
		@dwSkillAdv5 = 0
		@dwSkillAdv6 = 0
		@dwSkillAdv7 = 0
		@dwSkillAdv8 = 0
		@dwSkillAdv9 = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwOwnerID = @qwOwnerID
		obj.dwUpSkill1 = @dwUpSkill1
		obj.dwUpSkill2 = @dwUpSkill2
		obj.dwUpSkill3 = @dwUpSkill3
		obj.dwUpSkill4 = @dwUpSkill4
		obj.dwUpSkill5 = @dwUpSkill5
		obj.dwUpSkill6 = @dwUpSkill6
		obj.dwSkill1 = @dwSkill1
		obj.dwSkill2 = @dwSkill2
		obj.dwSkill3 = @dwSkill3
		obj.dwSkill4 = @dwSkill4
		obj.dwSkill5 = @dwSkill5
		obj.dwSkill6 = @dwSkill6
		obj.dwSkill7 = @dwSkill7
		obj.dwSkill8 = @dwSkill8
		obj.dwSkill9 = @dwSkill9
		obj.dwRune1 = @dwRune1
		obj.dwRune2 = @dwRune2
		obj.dwRune3 = @dwRune3
		obj.dwRune4 = @dwRune4
		obj.dwRune5 = @dwRune5
		obj.dwRune6 = @dwRune6
		obj.dwRune7 = @dwRune7
		obj.dwRune8 = @dwRune8
		obj.dwRune9 = @dwRune9
		obj.dwSkillAdv1 = @dwSkillAdv1
		obj.dwSkillAdv2 = @dwSkillAdv2
		obj.dwSkillAdv3 = @dwSkillAdv3
		obj.dwSkillAdv4 = @dwSkillAdv4
		obj.dwSkillAdv5 = @dwSkillAdv5
		obj.dwSkillAdv6 = @dwSkillAdv6
		obj.dwSkillAdv7 = @dwSkillAdv7
		obj.dwSkillAdv8 = @dwSkillAdv8
		obj.dwSkillAdv9 = @dwSkillAdv9
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSkillDBInfo.new
		s.qwOwnerID = ByteUtil::readUINT64(data)
		s.dwUpSkill1 = ByteUtil::readUINT32(data)
		s.dwUpSkill2 = ByteUtil::readUINT32(data)
		s.dwUpSkill3 = ByteUtil::readUINT32(data)
		s.dwUpSkill4 = ByteUtil::readUINT32(data)
		s.dwUpSkill5 = ByteUtil::readUINT32(data)
		s.dwUpSkill6 = ByteUtil::readUINT32(data)
		s.dwSkill1 = ByteUtil::readUINT32(data)
		s.dwSkill2 = ByteUtil::readUINT32(data)
		s.dwSkill3 = ByteUtil::readUINT32(data)
		s.dwSkill4 = ByteUtil::readUINT32(data)
		s.dwSkill5 = ByteUtil::readUINT32(data)
		s.dwSkill6 = ByteUtil::readUINT32(data)
		s.dwSkill7 = ByteUtil::readUINT32(data)
		s.dwSkill8 = ByteUtil::readUINT32(data)
		s.dwSkill9 = ByteUtil::readUINT32(data)
		s.dwRune1 = ByteUtil::readUINT32(data)
		s.dwRune2 = ByteUtil::readUINT32(data)
		s.dwRune3 = ByteUtil::readUINT32(data)
		s.dwRune4 = ByteUtil::readUINT32(data)
		s.dwRune5 = ByteUtil::readUINT32(data)
		s.dwRune6 = ByteUtil::readUINT32(data)
		s.dwRune7 = ByteUtil::readUINT32(data)
		s.dwRune8 = ByteUtil::readUINT32(data)
		s.dwRune9 = ByteUtil::readUINT32(data)
		s.dwSkillAdv1 = ByteUtil::readUINT32(data)
		s.dwSkillAdv2 = ByteUtil::readUINT32(data)
		s.dwSkillAdv3 = ByteUtil::readUINT32(data)
		s.dwSkillAdv4 = ByteUtil::readUINT32(data)
		s.dwSkillAdv5 = ByteUtil::readUINT32(data)
		s.dwSkillAdv6 = ByteUtil::readUINT32(data)
		s.dwSkillAdv7 = ByteUtil::readUINT32(data)
		s.dwSkillAdv8 = ByteUtil::readUINT32(data)
		s.dwSkillAdv9 = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSkillDBInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwOwnerID)
		ByteUtil::writeUINT32(data, @dwUpSkill1)
		ByteUtil::writeUINT32(data, @dwUpSkill2)
		ByteUtil::writeUINT32(data, @dwUpSkill3)
		ByteUtil::writeUINT32(data, @dwUpSkill4)
		ByteUtil::writeUINT32(data, @dwUpSkill5)
		ByteUtil::writeUINT32(data, @dwUpSkill6)
		ByteUtil::writeUINT32(data, @dwSkill1)
		ByteUtil::writeUINT32(data, @dwSkill2)
		ByteUtil::writeUINT32(data, @dwSkill3)
		ByteUtil::writeUINT32(data, @dwSkill4)
		ByteUtil::writeUINT32(data, @dwSkill5)
		ByteUtil::writeUINT32(data, @dwSkill6)
		ByteUtil::writeUINT32(data, @dwSkill7)
		ByteUtil::writeUINT32(data, @dwSkill8)
		ByteUtil::writeUINT32(data, @dwSkill9)
		ByteUtil::writeUINT32(data, @dwRune1)
		ByteUtil::writeUINT32(data, @dwRune2)
		ByteUtil::writeUINT32(data, @dwRune3)
		ByteUtil::writeUINT32(data, @dwRune4)
		ByteUtil::writeUINT32(data, @dwRune5)
		ByteUtil::writeUINT32(data, @dwRune6)
		ByteUtil::writeUINT32(data, @dwRune7)
		ByteUtil::writeUINT32(data, @dwRune8)
		ByteUtil::writeUINT32(data, @dwRune9)
		ByteUtil::writeUINT32(data, @dwSkillAdv1)
		ByteUtil::writeUINT32(data, @dwSkillAdv2)
		ByteUtil::writeUINT32(data, @dwSkillAdv3)
		ByteUtil::writeUINT32(data, @dwSkillAdv4)
		ByteUtil::writeUINT32(data, @dwSkillAdv5)
		ByteUtil::writeUINT32(data, @dwSkillAdv6)
		ByteUtil::writeUINT32(data, @dwSkillAdv7)
		ByteUtil::writeUINT32(data, @dwSkillAdv8)
		ByteUtil::writeUINT32(data, @dwSkillAdv9)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#数据库同步到游戏服务器的技能信息
class SPassiveSkillDBInfo
	attr_accessor:qwOwnerID #(UINT64)将唯一ID
	attr_accessor:qwRoleID #(UINT64)玩家一ID
	attr_accessor:dwSkillID #(UINT32)技能ID
	attr_accessor:dwSkillQuality #(UINT32)技能品质
	attr_accessor:dwSkillLevel #(UINT32)技能等级

	#构造函数
	def initialize
		@qwOwnerID = 0
		@qwRoleID = 0
		@dwSkillID = 0
		@dwSkillQuality = 0
		@dwSkillLevel = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwOwnerID = @qwOwnerID
		obj.qwRoleID = @qwRoleID
		obj.dwSkillID = @dwSkillID
		obj.dwSkillQuality = @dwSkillQuality
		obj.dwSkillLevel = @dwSkillLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPassiveSkillDBInfo.new
		s.qwOwnerID = ByteUtil::readUINT64(data)
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.dwSkillID = ByteUtil::readUINT32(data)
		s.dwSkillQuality = ByteUtil::readUINT32(data)
		s.dwSkillLevel = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPassiveSkillDBInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwOwnerID)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT32(data, @dwSkillID)
		ByteUtil::writeUINT32(data, @dwSkillQuality)
		ByteUtil::writeUINT32(data, @dwSkillLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#客栈散仙信息
class SHeroFighterInTavernInfo
	attr_accessor:wID #(UINT16)散仙ID
	attr_accessor:bHired #(bool)是否已招募

	#构造函数
	def initialize
		@wID = 0
		@bHired = false
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wID = @wID
		obj.bHired = @bHired
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SHeroFighterInTavernInfo.new
		s.wID = ByteUtil::readUINT16(data)
		s.bHired = ByteUtil::readBOOL(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SHeroFighterInTavernInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wID)
		ByteUtil::writeBOOL(data, @bHired)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#客栈信息
class STavernInfo
	attr_accessor:wID #(UINT16)客栈ID
	attr_accessor:vecFighterInfo #(SHeroFighterInTavernInfo的数组)客栈中散仙信息

	#构造函数
	def initialize
		@wID = 0
		@vecFighterInfo = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wID = @wID
		obj.vecFighterInfo = @vecFighterInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STavernInfo.new
		s.wID = ByteUtil::readUINT16(data)
		s.vecFighterInfo = SHeroFighterInTavernInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STavernInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wID)
		SHeroFighterInTavernInfo::vectorToStream(data, @vecFighterInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战斗者除了外观之外的杂七杂八的基本信息
class SFighterBaseInfo
	attr_accessor:qwInstID #(UINT64)将唯一ID
	attr_accessor:wFighterID #(UINT16)将类型ID
	attr_accessor:byRecruited #(UINT8)是否已招募
	attr_accessor:byStar #(UINT8)当前星级
	attr_accessor:iSlot #(INT32)将位置
	attr_accessor:iPos #(INT32)阵型中的位置
	attr_accessor:byLevel #(UINT8)等级
	attr_accessor:qwExp #(UINT64)总经验
	attr_accessor:strName #(string)将名字
	attr_accessor:dwHpMax #(UINT32)最大血量
	attr_accessor:dwHp #(UINT32)当前血量
	attr_accessor:dwAura #(UINT32)当前灵气
	attr_accessor:dwAuraMax #(UINT32)最大灵气
	attr_accessor:byLianPi #(UINT8)炼皮
	attr_accessor:byTongJin #(UINT8)通筋
	attr_accessor:byQiangJi #(UINT8)强肌
	attr_accessor:byDuanGu #(UINT8)锻骨
	attr_accessor:byHuoLuo #(UINT8)活络
	attr_accessor:byXiSui #(UINT8)洗髓
	attr_accessor:byDujieLevel #(UINT8)散仙渡劫等级
	attr_accessor:dwDujieExp #(UINT32)散仙渡劫经验
	attr_accessor:byQuality #(UINT8)散仙品质(颜色)
	attr_accessor:dwSpiritPower #(UINT32)元神力

	#构造函数
	def initialize
		@qwInstID = 0
		@wFighterID = 0
		@byRecruited = 0
		@byStar = 0
		@iSlot = 0
		@iPos = 0
		@byLevel = 0
		@qwExp = 0
		@strName = ''
		@dwHpMax = 0
		@dwHp = 0
		@dwAura = 0
		@dwAuraMax = 0
		@byLianPi = 0
		@byTongJin = 0
		@byQiangJi = 0
		@byDuanGu = 0
		@byHuoLuo = 0
		@byXiSui = 0
		@byDujieLevel = 0
		@dwDujieExp = 0
		@byQuality = 0
		@dwSpiritPower = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInstID = @qwInstID
		obj.wFighterID = @wFighterID
		obj.byRecruited = @byRecruited
		obj.byStar = @byStar
		obj.iSlot = @iSlot
		obj.iPos = @iPos
		obj.byLevel = @byLevel
		obj.qwExp = @qwExp
		obj.strName = @strName
		obj.dwHpMax = @dwHpMax
		obj.dwHp = @dwHp
		obj.dwAura = @dwAura
		obj.dwAuraMax = @dwAuraMax
		obj.byLianPi = @byLianPi
		obj.byTongJin = @byTongJin
		obj.byQiangJi = @byQiangJi
		obj.byDuanGu = @byDuanGu
		obj.byHuoLuo = @byHuoLuo
		obj.byXiSui = @byXiSui
		obj.byDujieLevel = @byDujieLevel
		obj.dwDujieExp = @dwDujieExp
		obj.byQuality = @byQuality
		obj.dwSpiritPower = @dwSpiritPower
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFighterBaseInfo.new
		s.qwInstID = ByteUtil::readUINT64(data)
		s.wFighterID = ByteUtil::readUINT16(data)
		s.byRecruited = ByteUtil::readUINT8(data)
		s.byStar = ByteUtil::readUINT8(data)
		s.iSlot = ByteUtil::readINT32(data)
		s.iPos = ByteUtil::readINT32(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.qwExp = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.dwHpMax = ByteUtil::readUINT32(data)
		s.dwHp = ByteUtil::readUINT32(data)
		s.dwAura = ByteUtil::readUINT32(data)
		s.dwAuraMax = ByteUtil::readUINT32(data)
		s.byLianPi = ByteUtil::readUINT8(data)
		s.byTongJin = ByteUtil::readUINT8(data)
		s.byQiangJi = ByteUtil::readUINT8(data)
		s.byDuanGu = ByteUtil::readUINT8(data)
		s.byHuoLuo = ByteUtil::readUINT8(data)
		s.byXiSui = ByteUtil::readUINT8(data)
		s.byDujieLevel = ByteUtil::readUINT8(data)
		s.dwDujieExp = ByteUtil::readUINT32(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.dwSpiritPower = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFighterBaseInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT16(data, @wFighterID)
		ByteUtil::writeUINT8(data, @byRecruited)
		ByteUtil::writeUINT8(data, @byStar)
		ByteUtil::writeINT32(data, @iSlot)
		ByteUtil::writeINT32(data, @iPos)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT64(data, @qwExp)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT32(data, @dwHpMax)
		ByteUtil::writeUINT32(data, @dwHp)
		ByteUtil::writeUINT32(data, @dwAura)
		ByteUtil::writeUINT32(data, @dwAuraMax)
		ByteUtil::writeUINT8(data, @byLianPi)
		ByteUtil::writeUINT8(data, @byTongJin)
		ByteUtil::writeUINT8(data, @byQiangJi)
		ByteUtil::writeUINT8(data, @byDuanGu)
		ByteUtil::writeUINT8(data, @byHuoLuo)
		ByteUtil::writeUINT8(data, @byXiSui)
		ByteUtil::writeUINT8(data, @byDujieLevel)
		ByteUtil::writeUINT32(data, @dwDujieExp)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT32(data, @dwSpiritPower)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#参与战斗的技能信息
class SFightSkillInfo
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
		s = SFightSkillInfo.new
		s.byIdx = ByteUtil::readUINT8(data)
		s.dwSkillID = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFightSkillInfo::fromStream(data)
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

#心法信息
class SXinFaInfo
	attr_accessor:dwXinFaID #(UINT32)心法ID
	attr_accessor:byXinFaLvl #(UINT8)心法等级
	attr_accessor:iSlot #(INT32)心法槽 -1表示心法没装备

	#构造函数
	def initialize
		@dwXinFaID = 0
		@byXinFaLvl = 0
		@iSlot = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwXinFaID = @dwXinFaID
		obj.byXinFaLvl = @byXinFaLvl
		obj.iSlot = @iSlot
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SXinFaInfo.new
		s.dwXinFaID = ByteUtil::readUINT32(data)
		s.byXinFaLvl = ByteUtil::readUINT8(data)
		s.iSlot = ByteUtil::readINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SXinFaInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwXinFaID)
		ByteUtil::writeUINT8(data, @byXinFaLvl)
		ByteUtil::writeINT32(data, @iSlot)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#数据库同步到游戏服务器的心法信息
class SXinFaDBInfo
	attr_accessor:qwRoleID #(UINT64)所属角色唯一ID
	attr_accessor:qwOwnerID #(UINT64)所属散仙ID
	attr_accessor:dwXinFaID #(UINT32)心法ID
	attr_accessor:byXinFaLvl #(UINT8)心法等级
	attr_accessor:iSlot #(INT32)心法槽 -1表示心法没装备

	#构造函数
	def initialize
		@qwRoleID = 0
		@qwOwnerID = 0
		@dwXinFaID = 0
		@byXinFaLvl = 0
		@iSlot = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.qwOwnerID = @qwOwnerID
		obj.dwXinFaID = @dwXinFaID
		obj.byXinFaLvl = @byXinFaLvl
		obj.iSlot = @iSlot
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SXinFaDBInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.qwOwnerID = ByteUtil::readUINT64(data)
		s.dwXinFaID = ByteUtil::readUINT32(data)
		s.byXinFaLvl = ByteUtil::readUINT8(data)
		s.iSlot = ByteUtil::readINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SXinFaDBInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT64(data, @qwOwnerID)
		ByteUtil::writeUINT32(data, @dwXinFaID)
		ByteUtil::writeUINT8(data, @byXinFaLvl)
		ByteUtil::writeINT32(data, @iSlot)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#战斗者信息
class SFighterInfo
	attr_accessor:oBaseInfo #(类类型：SFighterBaseInfo)基本信息
	attr_accessor:oAttrVec #(SFtAttrMod的数组)将属性
	attr_accessor:vActiveSkill #(SFightSkillInfo的数组)装备的主动技能
	attr_accessor:vPassiveSkill #(SFightSkillInfo的数组)被动技能
	attr_accessor:oPeerLees #(类类型：SFightSkillInfo)无双技能
	attr_accessor:vecXinFa #(SXinFaInfo的数组)散仙已经学会的心法信息(注：供客户端计算属性百分比加成)
	attr_accessor:vecStoneItem #(SItem的数组)宝石信息
	attr_accessor:vecEquipTrump #(SEquipTrump的数组)装备法宝信息

	#构造函数
	def initialize
		@oBaseInfo = SFighterBaseInfo.new
		@oAttrVec = Array.new
		@vActiveSkill = Array.new
		@vPassiveSkill = Array.new
		@oPeerLees = SFightSkillInfo.new
		@vecXinFa = Array.new
		@vecStoneItem = Array.new
		@vecEquipTrump = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.oBaseInfo = @oBaseInfo
		obj.oAttrVec = @oAttrVec
		obj.vActiveSkill = @vActiveSkill
		obj.vPassiveSkill = @vPassiveSkill
		obj.oPeerLees = @oPeerLees
		obj.vecXinFa = @vecXinFa
		obj.vecStoneItem = @vecStoneItem
		obj.vecEquipTrump = @vecEquipTrump
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFighterInfo.new
		s.oBaseInfo = SFighterBaseInfo::fromStream(data)
		s.oAttrVec = SFtAttrMod::vectorFromStream(data)
		s.vActiveSkill = SFightSkillInfo::vectorFromStream(data)
		s.vPassiveSkill = SFightSkillInfo::vectorFromStream(data)
		s.oPeerLees = SFightSkillInfo::fromStream(data)
		s.vecXinFa = SXinFaInfo::vectorFromStream(data)
		s.vecStoneItem = SItem::superVectorFromStream(data)
		s.vecEquipTrump = SEquipTrump::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFighterInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		@oBaseInfo.toStream(data)
		SFtAttrMod::vectorToStream(data, @oAttrVec)
		SFightSkillInfo::vectorToStream(data, @vActiveSkill)
		SFightSkillInfo::vectorToStream(data, @vPassiveSkill)
		@oPeerLees.toStream(data)
		SXinFaInfo::vectorToStream(data, @vecXinFa)
		SItem::superVectorToStream(data, @vecStoneItem)
		SEquipTrump::vectorToStream(data, @vecEquipTrump)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#阵型位置信息
class SFighterPos
	attr_accessor:qwInstID #(UINT64)将唯一ID
	attr_accessor:iPos #(INT32)将在阵型中的位置：-1表示下阵型

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
		s = SFighterPos.new
		s.qwInstID = ByteUtil::readUINT64(data)
		s.iPos = ByteUtil::readINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFighterPos::fromStream(data)
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

#散仙技能信息
class SFighterSkill
	attr_accessor:dwSkillID #(UINT32)技能ID

	#构造函数
	def initialize
		@dwSkillID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwSkillID = @dwSkillID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFighterSkill.new
		s.dwSkillID = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFighterSkill::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwSkillID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[FighterSkillEquipTo:散仙装备主动技能]的返回的参数组成的结构体
class SRetParam_FighterSkillEquipTo
	attr_accessor:eResult#(枚举类型：ESkillResult)结果
	attr_accessor:vActiveSkill#(SFightSkillInfo的数组)装备的主动技能

	#构造函数
	def initialize
		@eResult = 0
		@vActiveSkill = Array.new
	end
end

#函数[FighterSkillLevelUp:散仙技能升级]的返回的参数组成的结构体
class SRetParam_FighterSkillLevelUp
	attr_accessor:eResult#(枚举类型：ESkillResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[FighterPassiveSkillLevelUp:散仙被动技能升级]的返回的参数组成的结构体
class SRetParam_FighterPassiveSkillLevelUp
	attr_accessor:eResult#(枚举类型：ESkillResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetTavernInfo:获取客栈信息]的返回的参数组成的结构体
class SRetParam_GetTavernInfo
	attr_accessor:dwDrawCount#(UINT32)免费求签次数
	attr_accessor:vecTavernInfo#(STavernInfo的数组)具体客栈信息

	#构造函数
	def initialize
		@dwDrawCount = 0
		@vecTavernInfo = Array.new
	end
end

#函数[Draw:求签]的返回的参数组成的结构体
class SRetParam_Draw
	attr_accessor:eResult#(枚举类型：EDrawResult)返回结果
	attr_accessor:vecItemGet#(SItemCount的数组)求签获得物品

	#构造函数
	def initialize
		@eResult = 0
		@vecItemGet = Array.new
	end
end

#函数[FighterRecruit:招募]的返回的参数组成的结构体
class SRetParam_FighterRecruit
	attr_accessor:eResult#(枚举类型：ERecruitResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[CuiTiUpgrade:淬体升级]的返回的参数组成的结构体
class SRetParam_CuiTiUpgrade
	attr_accessor:eResult#(枚举类型：ECuiTiResult)结果
	attr_accessor:byLevel#(UINT8)当前淬体等级

	#构造函数
	def initialize
		@eResult = 0
		@byLevel = 0
	end
end

#函数[CuiTiAllUpgrade:散仙淬体全体(六种)升级一次]的返回的参数组成的结构体
class SRetParam_CuiTiAllUpgrade
	attr_accessor:eResult#(枚举类型：ECuiTiResult)结果
	attr_accessor:vecLevel#(UINT8数组)当前全体淬体等级(按炼皮/通筋/强肌/锻骨/活络/洗髓顺序)

	#构造函数
	def initialize
		@eResult = 0
		@vecLevel = Array.new
	end
end

#函数[FighterShift:转移]的返回的参数组成的结构体
class SRetParam_FighterShift
	attr_accessor:eResult#(枚举类型：EShiftResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[FighterSyncLevel:同步等级]的返回的参数组成的结构体
class SRetParam_FighterSyncLevel
	attr_accessor:eResult#(枚举类型：ESyncLevelResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[UpgradeDujie:渡劫升级]的返回的参数组成的结构体
class SRetParam_UpgradeDujie
	attr_accessor:eResult#(枚举类型：EDujieResult)结果
	attr_accessor:qwInstID#(UINT64)将唯一ID

	#构造函数
	def initialize
		@eResult = 0
		@qwInstID = 0
	end
end

#函数[ReqFighterXinFaInfo:请求散仙心法]的返回的参数组成的结构体
class SRetParam_ReqFighterXinFaInfo
	attr_accessor:vecFighterXinFa#(SXinFaInfo的数组)散仙已经学会的心法信息

	#构造函数
	def initialize
		@vecFighterXinFa = Array.new
	end
end

#函数[FighterActiveXinFa:散仙学习心法]的返回的参数组成的结构体
class SRetParam_FighterActiveXinFa
	attr_accessor:eResult#(枚举类型：EXinFaResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[FighterXinFaLevelUp:散仙心法升级]的返回的参数组成的结构体
class SRetParam_FighterXinFaLevelUp
	attr_accessor:eResult#(枚举类型：EXinFaResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[FighterXinFaDisperse:散仙心法散功]的返回的参数组成的结构体
class SRetParam_FighterXinFaDisperse
	attr_accessor:eResult#(枚举类型：EXinFaResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetAllFighterCombination:获取玩家的所有散仙组合]的返回的参数组成的结构体
class SRetParam_GetAllFighterCombination
	attr_accessor:vecCombinationInfo#(SFighterCombination的数组)玩家的散仙组合信息

	#构造函数
	def initialize
		@vecCombinationInfo = Array.new
	end
end

#函数[ActiveCombination:激活散仙组合]的返回的参数组成的结构体
class SRetParam_ActiveCombination
	attr_accessor:eResult#(枚举类型：ECombinationResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[UpgradeCombination:升级散仙组合]的返回的参数组成的结构体
class SRetParam_UpgradeCombination
	attr_accessor:oCombinationInfo#(类类型：SFighterCombination)当前升级的散仙组合信息
	attr_accessor:eResult#(枚举类型：ECombinationResult)结果

	#构造函数
	def initialize
		@oCombinationInfo = SFighterCombination.new
		@eResult = 0
	end
end

#函数[EquipToCombinationSkill:装备散仙组合技能(连携技)]的返回的参数组成的结构体
class SRetParam_EquipToCombinationSkill
	attr_accessor:eResult#(枚举类型：ECombinationResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[FighterDismiss:散仙散功]的返回的参数组成的结构体
class SRetParam_FighterDismiss
	attr_accessor:eResult#(枚举类型：EDismissResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetFighterBuyInfo:获取购买散仙信息]的返回的参数组成的结构体
class SRetParam_GetFighterBuyInfo
	attr_accessor:vecFighterBuyInfo#(SFighterBuyInfo的数组)购买散仙信息

	#构造函数
	def initialize
		@vecFighterBuyInfo = Array.new
	end
end

#函数[FighterBuy:散仙购买]的返回的参数组成的结构体
class SRetParam_FighterBuy
	attr_accessor:eResult#(枚举类型：EFighterBuyResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：道具相关协议
class FighterProtBase < ProtocolBase
	#以下为发送函数
	#发送：散仙装备主动技能
	def send_FighterSkillEquipTo(
		qwInstID,  #(UINT64)散仙唯一ID
		dwSkillID,  #(UINT32)技能ID
		iSlot #(INT32)技能槽 -1表示卸下技能
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT32(data, dwSkillID)
		ByteUtil::writeINT32(data, iSlot)
		return @svrHandler.sendPacket(data)
	end

	#发送：散仙技能升级
	def send_FighterSkillLevelUp(
		qwInstID,  #(UINT64)散仙唯一ID
		dwSkillID #(UINT32)技能ID
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT32(data, dwSkillID)
		return @svrHandler.sendPacket(data)
	end

	#发送：散仙被动技能升级
	def send_FighterPassiveSkillLevelUp(
		qwInstID,  #(UINT64)散仙唯一ID
		dwSkillID #(UINT32)技能ID
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT32(data, dwSkillID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取客栈信息
	def send_GetTavernInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：求签
	def send_Draw(
		eType #(枚举类型：EDrawType)求签类型
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eType)
		return @svrHandler.sendPacket(data)
	end

	#发送：招募
	def send_FighterRecruit(
		wFighterID #(UINT16)将ID
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wFighterID)
		return @svrHandler.sendPacket(data)
	end

	#发送：淬体升级
	def send_CuiTiUpgrade(
		qwInstID,  #(UINT64)将唯一ID
		eCuiTiType,  #(枚举类型：ECuiTiType)淬体类型
		byTimes #(UINT8)次数
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT8(data, eCuiTiType)
		ByteUtil::writeUINT8(data, byTimes)
		return @svrHandler.sendPacket(data)
	end

	#发送：散仙淬体全体(六种)升级一次
	def send_CuiTiAllUpgrade(
		qwInstID #(UINT64)将唯一ID
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		return @svrHandler.sendPacket(data)
	end

	#发送：转移
	def send_FighterShift(
		qwInstIDSrc,  #(UINT64)将唯一ID
		qwInstIDDst #(UINT64)将唯一ID
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstIDSrc)
		ByteUtil::writeUINT64(data, qwInstIDDst)
		return @svrHandler.sendPacket(data)
	end

	#发送：同步等级
	def send_FighterSyncLevel(
		qwInstID,  #(UINT64)将唯一ID
		byGoalLvl #(UINT8)同步的目标等级
	)
		sessionID = @sessionMgr.getNewSession(self, 10);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT8(data, byGoalLvl)
		return @svrHandler.sendPacket(data)
	end

	#发送：渡劫升级
	def send_UpgradeDujie(
		qwInstID,  #(UINT64)将唯一ID
		byOneKey #(UINT8)是否一键(是>0 否=0)
	)
		sessionID = @sessionMgr.getNewSession(self, 11);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT8(data, byOneKey)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求散仙心法
	def send_ReqFighterXinFaInfo(
		qwInstID #(UINT64)散仙唯一ID
	)
		sessionID = @sessionMgr.getNewSession(self, 12);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		return @svrHandler.sendPacket(data)
	end

	#发送：散仙学习心法
	def send_FighterActiveXinFa(
		qwInstID,  #(UINT64)散仙唯一ID
		dwXinFaID #(UINT32)心法ID
	)
		sessionID = @sessionMgr.getNewSession(self, 13);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 13
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT32(data, dwXinFaID)
		return @svrHandler.sendPacket(data)
	end

	#发送：散仙心法升级
	def send_FighterXinFaLevelUp(
		qwInstID,  #(UINT64)散仙唯一ID
		dwXinFaID #(UINT32)心法ID
	)
		sessionID = @sessionMgr.getNewSession(self, 14);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 14
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT32(data, dwXinFaID)
		return @svrHandler.sendPacket(data)
	end

	#发送：散仙心法散功
	def send_FighterXinFaDisperse(
		qwInstID,  #(UINT64)散仙唯一ID
		dwXinFaID #(UINT32)心法ID
	)
		sessionID = @sessionMgr.getNewSession(self, 15);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 15
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT32(data, dwXinFaID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取玩家的所有散仙组合
	def send_GetAllFighterCombination(
	)
		sessionID = @sessionMgr.getNewSession(self, 16);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 16
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：激活散仙组合
	def send_ActiveCombination(
		byGroupID #(UINT8)散仙组合ID
	)
		sessionID = @sessionMgr.getNewSession(self, 17);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 17
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byGroupID)
		return @svrHandler.sendPacket(data)
	end

	#发送：升级散仙组合
	def send_UpgradeCombination(
		byGroupID,  #(UINT8)散仙组合ID
		byOneKey #(UINT8)是否一键(是>0 否=0)
	)
		sessionID = @sessionMgr.getNewSession(self, 18);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 18
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byGroupID)
		ByteUtil::writeUINT8(data, byOneKey)
		return @svrHandler.sendPacket(data)
	end

	#发送：装备散仙组合技能(连携技)
	def send_EquipToCombinationSkill(
		byGroupID,  #(UINT8)散仙组合ID
		byType #(UINT8)1出战在阵型 2出战在守卫峨眉
	)
		sessionID = @sessionMgr.getNewSession(self, 19);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 19
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byGroupID)
		ByteUtil::writeUINT8(data, byType)
		return @svrHandler.sendPacket(data)
	end

	#发送：散仙散功
	def send_FighterDismiss(
		qwInstID #(UINT64)散仙唯一ID
	)
		sessionID = @sessionMgr.getNewSession(self, 20);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 20
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取购买散仙信息
	def send_GetFighterBuyInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 21);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 21
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：散仙购买
	def send_FighterBuy(
		wFighterID #(UINT16)将ID
	)
		sessionID = @sessionMgr.getNewSession(self, 22);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 22
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wFighterID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：装备技能返回
	def onRecv_SkillUpNotify(
		dwSkillID, #(UINT32)技能ID
		iSlot #(INT32)技能槽 -1表示卸下技能
	)
		raise NotImplementedError
	end
	#接收：增加新技能
	def onRecv_SkillAddNotify(
		dwSkillID #(UINT32)技能ID
	)
		raise NotImplementedError
	end
	#接收：散仙血脉激活
	def onRecv_InstinctActiveNotify(
		qwInstID, #(UINT64)散仙唯一ID
		vecInstinctIDRandom, #(UINT16数组)血脉随机结果
		vecInstinctIDRet #(UINT16数组)血脉最终结果
	)
		raise NotImplementedError
	end
	#接收：招募散仙成功的弹框通知
	def onRecv_RecruitSuccNotify(
		wFighterID #(UINT16)散仙ID
	)
		raise NotImplementedError
	end
	#接收：阵型位置变更
	def onRecv_FighterPosNotify(
		vecPos #(SFighterPos的数组)阵型位置
	)
		raise NotImplementedError
	end
	#接收：更新散仙的渡劫数据
	def onRecv_UpdateDujieValue(
		qwInstID, #(UINT64)将唯一ID
		byDujieLevel, #(UINT8)当前渡劫等级
		dwDujieExp, #(UINT32)当前渡劫经验
		dwSpiritPower #(UINT32)元神力
	)
		raise NotImplementedError
	end
	#接收：心法数据更新通知
	def onRecv_XinFaNotify(
		qwInstID, #(UINT64)将唯一ID
		dwXinFaID, #(UINT32)心法ID
		byXinFaLvl, #(UINT8)心法等级
		iSlot #(INT32)心法槽 -1表示心法没装备
	)
		raise NotImplementedError
	end
	#接收：散仙心法主卷等级满了添加一个天赋技能更新通知
	def onRecv_AddTalentSkillNotify(
		qwInstID, #(UINT64)将唯一ID
		byIdx, #(UINT8)技能槽idx
		dwSkillID #(UINT32)技能ID
	)
		raise NotImplementedError
	end
	#接收：散仙技能列表返回
	def onRecv_SkillListNotify(
		qwInstID, #(UINT64)将唯一ID
		VecFighterSkill #(SFighterSkill的数组)技能ID
	)
		raise NotImplementedError
	end
	#接收：玩家的散仙组合列表返回
	def onRecv_FighterCombinationNotify(
		VecCombination #(SFighterCombination的数组)散仙组合列表
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：散仙装备主动技能
	def onReturn_FighterSkillEquipTo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FighterSkillEquipTo)返回的参数
	)
	end

	#返回：散仙技能升级
	def onReturn_FighterSkillLevelUp(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FighterSkillLevelUp)返回的参数
	)
	end

	#返回：散仙被动技能升级
	def onReturn_FighterPassiveSkillLevelUp(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FighterPassiveSkillLevelUp)返回的参数
	)
	end

	#返回：获取客栈信息
	def onReturn_GetTavernInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetTavernInfo)返回的参数
	)
	end

	#返回：求签
	def onReturn_Draw(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Draw)返回的参数
	)
	end

	#返回：招募
	def onReturn_FighterRecruit(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FighterRecruit)返回的参数
	)
	end

	#返回：淬体升级
	def onReturn_CuiTiUpgrade(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_CuiTiUpgrade)返回的参数
	)
	end

	#返回：散仙淬体全体(六种)升级一次
	def onReturn_CuiTiAllUpgrade(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_CuiTiAllUpgrade)返回的参数
	)
	end

	#返回：转移
	def onReturn_FighterShift(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FighterShift)返回的参数
	)
	end

	#返回：同步等级
	def onReturn_FighterSyncLevel(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FighterSyncLevel)返回的参数
	)
	end

	#返回：渡劫升级
	def onReturn_UpgradeDujie(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UpgradeDujie)返回的参数
	)
	end

	#返回：请求散仙心法
	def onReturn_ReqFighterXinFaInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqFighterXinFaInfo)返回的参数
	)
	end

	#返回：散仙学习心法
	def onReturn_FighterActiveXinFa(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FighterActiveXinFa)返回的参数
	)
	end

	#返回：散仙心法升级
	def onReturn_FighterXinFaLevelUp(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FighterXinFaLevelUp)返回的参数
	)
	end

	#返回：散仙心法散功
	def onReturn_FighterXinFaDisperse(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FighterXinFaDisperse)返回的参数
	)
	end

	#返回：获取玩家的所有散仙组合
	def onReturn_GetAllFighterCombination(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetAllFighterCombination)返回的参数
	)
	end

	#返回：激活散仙组合
	def onReturn_ActiveCombination(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ActiveCombination)返回的参数
	)
	end

	#返回：升级散仙组合
	def onReturn_UpgradeCombination(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UpgradeCombination)返回的参数
	)
	end

	#返回：装备散仙组合技能(连携技)
	def onReturn_EquipToCombinationSkill(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_EquipToCombinationSkill)返回的参数
	)
	end

	#返回：散仙散功
	def onReturn_FighterDismiss(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FighterDismiss)返回的参数
	)
	end

	#返回：获取购买散仙信息
	def onReturn_GetFighterBuyInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetFighterBuyInfo)返回的参数
	)
	end

	#返回：散仙购买
	def onReturn_FighterBuy(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FighterBuy)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：装备技能返回
	def _doRecv_SkillUpNotify(data)
		dwSkillID = ByteUtil::readUINT32(data)
		iSlot = ByteUtil::readINT32(data)
		return onRecv_SkillUpNotify(dwSkillID, iSlot)
	end

	#接收处理：增加新技能
	def _doRecv_SkillAddNotify(data)
		dwSkillID = ByteUtil::readUINT32(data)
		return onRecv_SkillAddNotify(dwSkillID)
	end

	#接收处理：散仙血脉激活
	def _doRecv_InstinctActiveNotify(data)
		qwInstID = ByteUtil::readUINT64(data)
		vecInstinctIDRandom = ByteUtil::readVecUINT16(data)
		vecInstinctIDRet = ByteUtil::readVecUINT16(data)
		return onRecv_InstinctActiveNotify(qwInstID, vecInstinctIDRandom, vecInstinctIDRet)
	end

	#接收处理：招募散仙成功的弹框通知
	def _doRecv_RecruitSuccNotify(data)
		wFighterID = ByteUtil::readUINT16(data)
		return onRecv_RecruitSuccNotify(wFighterID)
	end

	#接收处理：阵型位置变更
	def _doRecv_FighterPosNotify(data)
		vecPos = SFighterPos::vectorFromStream(data)
		return onRecv_FighterPosNotify(vecPos)
	end

	#接收处理：更新散仙的渡劫数据
	def _doRecv_UpdateDujieValue(data)
		qwInstID = ByteUtil::readUINT64(data)
		byDujieLevel = ByteUtil::readUINT8(data)
		dwDujieExp = ByteUtil::readUINT32(data)
		dwSpiritPower = ByteUtil::readUINT32(data)
		return onRecv_UpdateDujieValue(qwInstID, byDujieLevel, dwDujieExp, dwSpiritPower)
	end

	#接收处理：心法数据更新通知
	def _doRecv_XinFaNotify(data)
		qwInstID = ByteUtil::readUINT64(data)
		dwXinFaID = ByteUtil::readUINT32(data)
		byXinFaLvl = ByteUtil::readUINT8(data)
		iSlot = ByteUtil::readINT32(data)
		return onRecv_XinFaNotify(qwInstID, dwXinFaID, byXinFaLvl, iSlot)
	end

	#接收处理：散仙心法主卷等级满了添加一个天赋技能更新通知
	def _doRecv_AddTalentSkillNotify(data)
		qwInstID = ByteUtil::readUINT64(data)
		byIdx = ByteUtil::readUINT8(data)
		dwSkillID = ByteUtil::readUINT32(data)
		return onRecv_AddTalentSkillNotify(qwInstID, byIdx, dwSkillID)
	end

	#接收处理：散仙技能列表返回
	def _doRecv_SkillListNotify(data)
		qwInstID = ByteUtil::readUINT64(data)
		VecFighterSkill = SFighterSkill::vectorFromStream(data)
		return onRecv_SkillListNotify(qwInstID, VecFighterSkill)
	end

	#接收处理：玩家的散仙组合列表返回
	def _doRecv_FighterCombinationNotify(data)
		VecCombination = SFighterCombination::vectorFromStream(data)
		return onRecv_FighterCombinationNotify(VecCombination)
	end

#以下为返回处理函数
	#返回处理：散仙装备主动技能
	def _doReturn_FighterSkillEquipTo(data)
		retParam = SRetParam_FighterSkillEquipTo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ESkillResult)结果
		vActiveSkill = SFightSkillInfo::vectorFromStream(data) #(SFightSkillInfo的数组)装备的主动技能
		retParam.eResult = eResult
		retParam.vActiveSkill = vActiveSkill
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FighterSkillEquipTo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：散仙装备主动技能
	def _onTimeOut_FighterSkillEquipTo(sessionID)
		retParam = SRetParam_FighterSkillEquipTo.new;
		onReturn_FighterSkillEquipTo(2, retParam)
	end

	#返回处理：散仙技能升级
	def _doReturn_FighterSkillLevelUp(data)
		retParam = SRetParam_FighterSkillLevelUp.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ESkillResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FighterSkillLevelUp(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：散仙技能升级
	def _onTimeOut_FighterSkillLevelUp(sessionID)
		retParam = SRetParam_FighterSkillLevelUp.new;
		onReturn_FighterSkillLevelUp(2, retParam)
	end

	#返回处理：散仙被动技能升级
	def _doReturn_FighterPassiveSkillLevelUp(data)
		retParam = SRetParam_FighterPassiveSkillLevelUp.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ESkillResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FighterPassiveSkillLevelUp(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：散仙被动技能升级
	def _onTimeOut_FighterPassiveSkillLevelUp(sessionID)
		retParam = SRetParam_FighterPassiveSkillLevelUp.new;
		onReturn_FighterPassiveSkillLevelUp(2, retParam)
	end

	#返回处理：获取客栈信息
	def _doReturn_GetTavernInfo(data)
		retParam = SRetParam_GetTavernInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		dwDrawCount = ByteUtil::readUINT32(data) #(UINT32)免费求签次数
		vecTavernInfo = STavernInfo::vectorFromStream(data) #(STavernInfo的数组)具体客栈信息
		retParam.dwDrawCount = dwDrawCount
		retParam.vecTavernInfo = vecTavernInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetTavernInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取客栈信息
	def _onTimeOut_GetTavernInfo(sessionID)
		retParam = SRetParam_GetTavernInfo.new;
		onReturn_GetTavernInfo(2, retParam)
	end

	#返回处理：求签
	def _doReturn_Draw(data)
		retParam = SRetParam_Draw.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EDrawResult)返回结果
		vecItemGet = SItemCount::vectorFromStream(data) #(SItemCount的数组)求签获得物品
		retParam.eResult = eResult
		retParam.vecItemGet = vecItemGet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_Draw(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：求签
	def _onTimeOut_Draw(sessionID)
		retParam = SRetParam_Draw.new;
		onReturn_Draw(2, retParam)
	end

	#返回处理：招募
	def _doReturn_FighterRecruit(data)
		retParam = SRetParam_FighterRecruit.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ERecruitResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FighterRecruit(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：招募
	def _onTimeOut_FighterRecruit(sessionID)
		retParam = SRetParam_FighterRecruit.new;
		onReturn_FighterRecruit(2, retParam)
	end

	#返回处理：淬体升级
	def _doReturn_CuiTiUpgrade(data)
		retParam = SRetParam_CuiTiUpgrade.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ECuiTiResult)结果
		byLevel = ByteUtil::readUINT8(data) #(UINT8)当前淬体等级
		retParam.eResult = eResult
		retParam.byLevel = byLevel
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_CuiTiUpgrade(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：淬体升级
	def _onTimeOut_CuiTiUpgrade(sessionID)
		retParam = SRetParam_CuiTiUpgrade.new;
		onReturn_CuiTiUpgrade(2, retParam)
	end

	#返回处理：散仙淬体全体(六种)升级一次
	def _doReturn_CuiTiAllUpgrade(data)
		retParam = SRetParam_CuiTiAllUpgrade.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ECuiTiResult)结果
		vecLevel = ByteUtil::readVecUINT8(data) #(UINT8数组)当前全体淬体等级(按炼皮/通筋/强肌/锻骨/活络/洗髓顺序)
		retParam.eResult = eResult
		retParam.vecLevel = vecLevel
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_CuiTiAllUpgrade(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：散仙淬体全体(六种)升级一次
	def _onTimeOut_CuiTiAllUpgrade(sessionID)
		retParam = SRetParam_CuiTiAllUpgrade.new;
		onReturn_CuiTiAllUpgrade(2, retParam)
	end

	#返回处理：转移
	def _doReturn_FighterShift(data)
		retParam = SRetParam_FighterShift.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EShiftResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FighterShift(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：转移
	def _onTimeOut_FighterShift(sessionID)
		retParam = SRetParam_FighterShift.new;
		onReturn_FighterShift(2, retParam)
	end

	#返回处理：同步等级
	def _doReturn_FighterSyncLevel(data)
		retParam = SRetParam_FighterSyncLevel.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ESyncLevelResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FighterSyncLevel(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：同步等级
	def _onTimeOut_FighterSyncLevel(sessionID)
		retParam = SRetParam_FighterSyncLevel.new;
		onReturn_FighterSyncLevel(2, retParam)
	end

	#返回处理：渡劫升级
	def _doReturn_UpgradeDujie(data)
		retParam = SRetParam_UpgradeDujie.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EDujieResult)结果
		qwInstID = ByteUtil::readUINT64(data) #(UINT64)将唯一ID
		retParam.eResult = eResult
		retParam.qwInstID = qwInstID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UpgradeDujie(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：渡劫升级
	def _onTimeOut_UpgradeDujie(sessionID)
		retParam = SRetParam_UpgradeDujie.new;
		onReturn_UpgradeDujie(2, retParam)
	end

	#返回处理：请求散仙心法
	def _doReturn_ReqFighterXinFaInfo(data)
		retParam = SRetParam_ReqFighterXinFaInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecFighterXinFa = SXinFaInfo::vectorFromStream(data) #(SXinFaInfo的数组)散仙已经学会的心法信息
		retParam.vecFighterXinFa = vecFighterXinFa
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqFighterXinFaInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求散仙心法
	def _onTimeOut_ReqFighterXinFaInfo(sessionID)
		retParam = SRetParam_ReqFighterXinFaInfo.new;
		onReturn_ReqFighterXinFaInfo(2, retParam)
	end

	#返回处理：散仙学习心法
	def _doReturn_FighterActiveXinFa(data)
		retParam = SRetParam_FighterActiveXinFa.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EXinFaResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FighterActiveXinFa(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：散仙学习心法
	def _onTimeOut_FighterActiveXinFa(sessionID)
		retParam = SRetParam_FighterActiveXinFa.new;
		onReturn_FighterActiveXinFa(2, retParam)
	end

	#返回处理：散仙心法升级
	def _doReturn_FighterXinFaLevelUp(data)
		retParam = SRetParam_FighterXinFaLevelUp.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EXinFaResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FighterXinFaLevelUp(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：散仙心法升级
	def _onTimeOut_FighterXinFaLevelUp(sessionID)
		retParam = SRetParam_FighterXinFaLevelUp.new;
		onReturn_FighterXinFaLevelUp(2, retParam)
	end

	#返回处理：散仙心法散功
	def _doReturn_FighterXinFaDisperse(data)
		retParam = SRetParam_FighterXinFaDisperse.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EXinFaResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FighterXinFaDisperse(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：散仙心法散功
	def _onTimeOut_FighterXinFaDisperse(sessionID)
		retParam = SRetParam_FighterXinFaDisperse.new;
		onReturn_FighterXinFaDisperse(2, retParam)
	end

	#返回处理：获取玩家的所有散仙组合
	def _doReturn_GetAllFighterCombination(data)
		retParam = SRetParam_GetAllFighterCombination.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecCombinationInfo = SFighterCombination::vectorFromStream(data) #(SFighterCombination的数组)玩家的散仙组合信息
		retParam.vecCombinationInfo = vecCombinationInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetAllFighterCombination(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取玩家的所有散仙组合
	def _onTimeOut_GetAllFighterCombination(sessionID)
		retParam = SRetParam_GetAllFighterCombination.new;
		onReturn_GetAllFighterCombination(2, retParam)
	end

	#返回处理：激活散仙组合
	def _doReturn_ActiveCombination(data)
		retParam = SRetParam_ActiveCombination.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ECombinationResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ActiveCombination(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：激活散仙组合
	def _onTimeOut_ActiveCombination(sessionID)
		retParam = SRetParam_ActiveCombination.new;
		onReturn_ActiveCombination(2, retParam)
	end

	#返回处理：升级散仙组合
	def _doReturn_UpgradeCombination(data)
		retParam = SRetParam_UpgradeCombination.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		oCombinationInfo = SFighterCombination::fromStream(data) #(类类型：SFighterCombination)当前升级的散仙组合信息
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ECombinationResult)结果
		retParam.oCombinationInfo = oCombinationInfo
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UpgradeCombination(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：升级散仙组合
	def _onTimeOut_UpgradeCombination(sessionID)
		retParam = SRetParam_UpgradeCombination.new;
		onReturn_UpgradeCombination(2, retParam)
	end

	#返回处理：装备散仙组合技能(连携技)
	def _doReturn_EquipToCombinationSkill(data)
		retParam = SRetParam_EquipToCombinationSkill.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ECombinationResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_EquipToCombinationSkill(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：装备散仙组合技能(连携技)
	def _onTimeOut_EquipToCombinationSkill(sessionID)
		retParam = SRetParam_EquipToCombinationSkill.new;
		onReturn_EquipToCombinationSkill(2, retParam)
	end

	#返回处理：散仙散功
	def _doReturn_FighterDismiss(data)
		retParam = SRetParam_FighterDismiss.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EDismissResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FighterDismiss(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：散仙散功
	def _onTimeOut_FighterDismiss(sessionID)
		retParam = SRetParam_FighterDismiss.new;
		onReturn_FighterDismiss(2, retParam)
	end

	#返回处理：获取购买散仙信息
	def _doReturn_GetFighterBuyInfo(data)
		retParam = SRetParam_GetFighterBuyInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecFighterBuyInfo = SFighterBuyInfo::vectorFromStream(data) #(SFighterBuyInfo的数组)购买散仙信息
		retParam.vecFighterBuyInfo = vecFighterBuyInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetFighterBuyInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取购买散仙信息
	def _onTimeOut_GetFighterBuyInfo(sessionID)
		retParam = SRetParam_GetFighterBuyInfo.new;
		onReturn_GetFighterBuyInfo(2, retParam)
	end

	#返回处理：散仙购买
	def _doReturn_FighterBuy(data)
		retParam = SRetParam_FighterBuy.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EFighterBuyResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FighterBuy(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：散仙购买
	def _onTimeOut_FighterBuy(sessionID)
		retParam = SRetParam_FighterBuy.new;
		onReturn_FighterBuy(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 20;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_SkillUpNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_SkillAddNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_InstinctActiveNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_RecruitSuccNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_FighterPosNotify' #FuncID: 5
		@recvFuncList[5] = '_doRecv_UpdateDujieValue' #FuncID: 6
		@recvFuncList[6] = '_doRecv_XinFaNotify' #FuncID: 7
		@recvFuncList[7] = '_doRecv_AddTalentSkillNotify' #FuncID: 8
		@recvFuncList[8] = '_doRecv_SkillListNotify' #FuncID: 9
		@recvFuncList[9] = '_doRecv_FighterCombinationNotify' #FuncID: 10

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_FighterSkillEquipTo' #FuncID: 1
		@retFuncList[1] = '_doReturn_FighterSkillLevelUp' #FuncID: 2
		@retFuncList[2] = '_doReturn_FighterPassiveSkillLevelUp' #FuncID: 3
		@retFuncList[3] = '_doReturn_GetTavernInfo' #FuncID: 4
		@retFuncList[4] = '_doReturn_Draw' #FuncID: 5
		@retFuncList[5] = '_doReturn_FighterRecruit' #FuncID: 6
		@retFuncList[6] = '_doReturn_CuiTiUpgrade' #FuncID: 7
		@retFuncList[7] = '_doReturn_CuiTiAllUpgrade' #FuncID: 8
		@retFuncList[8] = '_doReturn_FighterShift' #FuncID: 9
		@retFuncList[9] = '_doReturn_FighterSyncLevel' #FuncID: 10
		@retFuncList[10] = '_doReturn_UpgradeDujie' #FuncID: 11
		@retFuncList[11] = '_doReturn_ReqFighterXinFaInfo' #FuncID: 12
		@retFuncList[12] = '_doReturn_FighterActiveXinFa' #FuncID: 13
		@retFuncList[13] = '_doReturn_FighterXinFaLevelUp' #FuncID: 14
		@retFuncList[14] = '_doReturn_FighterXinFaDisperse' #FuncID: 15
		@retFuncList[15] = '_doReturn_GetAllFighterCombination' #FuncID: 16
		@retFuncList[16] = '_doReturn_ActiveCombination' #FuncID: 17
		@retFuncList[17] = '_doReturn_UpgradeCombination' #FuncID: 18
		@retFuncList[18] = '_doReturn_EquipToCombinationSkill' #FuncID: 19
		@retFuncList[19] = '_doReturn_FighterDismiss' #FuncID: 20
		@retFuncList[20] = '_doReturn_GetFighterBuyInfo' #FuncID: 21
		@retFuncList[21] = '_doReturn_FighterBuy' #FuncID: 22

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_FighterSkillEquipTo' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_FighterSkillLevelUp' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_FighterPassiveSkillLevelUp' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_GetTavernInfo' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_Draw' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_FighterRecruit' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_CuiTiUpgrade' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_CuiTiAllUpgrade' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_FighterShift' #FuncID: 9
		@timeFuncList[9] = '_onTimeOut_FighterSyncLevel' #FuncID: 10
		@timeFuncList[10] = '_onTimeOut_UpgradeDujie' #FuncID: 11
		@timeFuncList[11] = '_onTimeOut_ReqFighterXinFaInfo' #FuncID: 12
		@timeFuncList[12] = '_onTimeOut_FighterActiveXinFa' #FuncID: 13
		@timeFuncList[13] = '_onTimeOut_FighterXinFaLevelUp' #FuncID: 14
		@timeFuncList[14] = '_onTimeOut_FighterXinFaDisperse' #FuncID: 15
		@timeFuncList[15] = '_onTimeOut_GetAllFighterCombination' #FuncID: 16
		@timeFuncList[16] = '_onTimeOut_ActiveCombination' #FuncID: 17
		@timeFuncList[17] = '_onTimeOut_UpgradeCombination' #FuncID: 18
		@timeFuncList[18] = '_onTimeOut_EquipToCombinationSkill' #FuncID: 19
		@timeFuncList[19] = '_onTimeOut_FighterDismiss' #FuncID: 20
		@timeFuncList[20] = '_onTimeOut_GetFighterBuyInfo' #FuncID: 21
		@timeFuncList[21] = '_onTimeOut_FighterBuy' #FuncID: 22
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

