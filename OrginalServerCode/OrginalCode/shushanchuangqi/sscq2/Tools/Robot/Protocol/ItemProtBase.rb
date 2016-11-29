#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    ItemProt.rb
#  Purpose:      道具相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#使用道具结果
class EItemResult
	EITEMSUCCEED = 0#成功
	EITEMFAILED = 1#失败
	EITEMNOTENOUGTH = 2#道具使用个数不足
	EITEMNOTEXIST = 3#道具不存在
	EITEMERRBIND = 4#道具为绑定
	EITEMERRUSE = 5#道具无法使用
	EITEMSTOREFULL = 6#包裹或仓库满
	EITEMSTOREERR = 7#包裹或仓库错误
	EITEMRANGEERR = 8#道具距离过远
	EITEMNOSTACK = 9#道具为非堆叠的
	EITEMNOCOIN = 10#游戏币不足
	EITEMCOINFULL = 11#游戏币超出上限
	EITEMNOMONEY = 12#仙石不足
	EITEMMONEYFULL = 13#充值货币超出上限
	EITEMERROPER = 14#操作非法
	EITEMERRCD = 15#CD时间未到
	EITEMERRSLOT = 16#装备位错误
	EITEMNOTNEED = 17#无需此操作
	EITEMERRNAME = 18#名字太长
	EITEMEXPIRED = 19#道具使用时间过期
	EITEMERRSELL = 20#道具无法出售
	EITEMERRDROP = 21#道具无法丢弃
	EITEMERRLEVEL = 22#使用等级不够
	EITEMERRJOB = 23#使用职业限制
	EITEMNOSTUFF = 24#材料不足
	EITEMERRDUNGEON = 25#副本中无法使用传送卷轴
	EITEMERRTRANSFMAP = 26#该地图中无法使用传送卷轴
	EITEMMOUNTEXIST = 27#已存在该坐骑
	EITEMMUTUALEQUIP = 28#属性类型
	EITEMMUTUAL = 29#属性类型
	EITEMNOTAKEOFF = 30#无法脱下
	EITEMSKILLEXIST = 31#该技能已存在
	EITEMFASHIONEXIST = 32#该时装已存在
	EITEMSTOREMAX = 33#背包已达上限
	EITEMDEPOTMAX = 34#仓库已达上限
	EITEMERROTHER = 35#其它错误
end

#心法操作结果
class ECittaResult
	ECITTASUCCESS = 0#心法操作成功
	ECITTAFAILED = 1#心法操作失败
	ECITTAPACKFULL = 2#心法操作时背包已满
	ECITTAMATERIALLACK = 3#材料不足
	ECITTASLOTNOTEMPTY = 4#心法槽已满
	ECITTASLOTEMPTY = 5#心法槽为空
	ECITTASILVERLACK = 6#银币不足
end

#装备养成结果
class ETrumpResult
	ETRUMPSUCCESS = 0#法宝养成成功
	ETRUMPFAILED = 1#法宝养成失败
	ETRUMPEXIST = 2#法宝已经存在
	ETRUMPNOTIFYFAILED = 3#法宝通知失败
	ETRUMPNOTACTIVED = 4#法宝未激活
	ETRUMPNOTEXIST = 5#法宝不存在
	ETRUMPUPGRADEMATERIALLACK = 6#法宝强化材料不足
	ETRUMPEVOLVEMATERIALLACK = 7#法宝升阶材料不足
	ETRUMPFULL = 8#法宝位已满
	ETRUMPISEQUIPED = 9#法宝已装备
	ETRUMPNOTEQUIPED = 10#法宝未装备
	ETRUMPACTIVEFAILED = 11#法宝解锁失败
end

#时装养成结果
class EFashionResult
	EFASHIONSUCC = 0#时装养成成功
	EFASHIONFAILED = 1#时装养成失败
	EFASHIONITEMERR = 2#时装养成时所需物品不足
end

#宝石操作
class EGemstoneResult
	EGEMSTONESUCCESS = 0#宝石操作成功
	EGEMSTONEFAILED = 1#宝石操作失败
	EGEMSTONESLOTNOTEMPTY = 2#宝石位置非空
	EGEMSTONESLOTEMPTY = 3#宝石位置空
	EGEMSTONEPACKFULL = 4#包裹满
	EGEMSTONEHEROERR = 5#将错误
	EGEMSTONENOSTONE = 6#没有找到宝石
	EGEMSTONEERRSTONE = 7#宝石合成目标不存在
	EGEMSTONEMATERIALLACK = 8#宝石材料不足
	EGEMSTONEHASSAMETYPE = 9#已经装备相同类型宝石
end

#道具品质
class EItemQuality
	ECOLORNONE = 0#无
	ECOLORGREEN = 1#绿
	ECOLORBLUE = 2#蓝
	ECOLORPURPLE = 3#紫
	ECOLORORANGE = 4#橙
	ECOLORBLACKGOLD = 5#暗金
	ECOLOREND = 6#结束
end

#存储类型
class EStoreType
	ESTORENONE = 0#无
	ESTOREPACK = 1#道具包裹
	ESTOREDEPOT = 2#角色仓库
	ESTOREPLAYERTRUMP = 3#法宝栏
	ESTOREPLAYERCITTA = 4#心法栏
	ESTOREFASHION = 5#时装栏
	ESTOREGEMSTONE = 6#宝石栏
	ESTOREEQUIPTRUMP = 7#装备法宝栏
end

#道具日志类型
class EItemLoggerType
	EITEMLOGGER1 = 0#试炼塔道具日志
end

#绑定类型
class EBindType
	EBINDNONE = 0#未绑定
	EBINDGET = 1#获取绑定
	EBINDSTREN = 2#强化后绑定
end

#绑定优先使用类型
class EBindUseType
	EBINDUSENONE = 0#只使用非绑定
	EBINDUSEBIND = 1#只使用绑定
	EBINDUSENONEFIRST = 2#优先使用非绑定
	EBINDUSEBINDFIRST = 3#优先使用绑定
end

#类型大类型
class EItemType
	EITEMNONE = 0#无类型
	EITEMRESOURCE = 1#资源道具
	EITEMNORMAL = 2#普通道具
	EITEMTRUMP = 3#法宝
	EITEMEQUIPTRUMP = 4#装备法宝
	EITEMFASHION = 5#时装
	EITEMFORMATION = 6#阵法
	EITEMCITTA = 7#心法
	EITEMINTENSIFY = 8#强化
	EITEMSKILLBOOK = 9#技能书
	EITEMSTONE = 10#宝石
	EITEMSTUFF = 11#材料
	EITEMTASK = 12#任务
	EITEMSPIRIT = 13#注灵
	EITEMSOUL = 14#元神
	EITEMNEIDAN = 15#灵宠内丹
	EITEMVIGOUR = 16#灵宠精魄
	EITEMOTHER = 17#其他
	EITEMEND = 18
end

#物品子类型
class EItemSubType
	EITEMSUBNONE = 0#无类型
	EITEMSUBRESOURCE = 1#资源
	EITEMSUBNORMAL = 2#普通
	EITEMSUBFASIONMATERIAL = 10#时装激活材料
	EITEMSUBZTMATERIAL = 20#本命法宝温养材料
	EITEMSUBWEPAON = 21#武器
	EITEMSUBRING = 22#戒指
	EITEMSUBNECK = 23#项链
	EITEMSUBHEAD = 24#头盔
	EITEMSUBCHEST = 25#胸甲
	EITEMSUBLEGGING = 26#护腿
	EITEMSUBMOUNTS = 30#坐骑
	EITEMSUBACTIVETRUMP = 32#主动法宝
	EITEMSUBPASSIVETRUMP = 33#被动法宝
	EITEMSUBFASHION = 51#时装-神器
	EITEMSUBFASHION2 = 52#时装-神衣
	EITEMSUBSPIRIT = 141#注灵
	EITEMSUBPETSOUL = 151#兽魂
	EITEMSUBEQUIPTRUMPINNATE = 205#先天
	EITEMSUBEQUIPTRUMPPASSIVE = 206#被动
	EITEMSUBEQUIPTRUMPTRANSFORM = 207#光环
	EITEMSUBEQUIPTRUMPHALO = 208#变身
end

#法宝位类型
class ETrumpSlotType
	ESLOTTRUMP1 = 0#法宝1
	ESLOTTRUMP2 = 1#法宝2
	ESLOTTRUMP3 = 2#法宝3
	ESLOTTRUMP4 = 3#法宝4
	ESLOTTRUMP5 = 4#法宝5
	ESLOTTRUMP6 = 5#法宝6
	ESLOTTRUMP7 = 6#法宝7
	ESLOTTRUMP8 = 7#法宝8
	ESLOTTRUMP9 = 8#法宝9
	ESLOTTRUMP10 = 9#法宝10
end

#心法位类型
class ECittaSlotType
	ESLOTCITTA1 = 0#心法1
	ESLOTCITTA2 = 1#心法2
	ESLOTCITTA3 = 2#心法3
	ESLOTCITTA4 = 3#心法4
	ESLOTCITTA5 = 4#心法5
	ESLOTCITTA6 = 5#心法6
	ESLOTCITTA7 = 6#心法7
	ESLOTCITTA8 = 7#心法8
end

#心法姓名前缀类型
class ECittaNameType
	ENAMENONE = 0#破烂之
	ENAMEATTACK = 1#力量之
	ENAMEDEFENCE = 2#坚固的
	ENAMEMGCDEFENCE = 3#道心之
	ENAMEHP = 4#长生的
	ENAMEHIT = 5#神佑的
	ENAMEDODGE = 6#灵猴的
	ENAMECRITICAL = 7#刺客的
	ENAMEANTICRI = 8#平衡的
	ENAMEPIECE = 9#破击之
	ENAMECOUNTER = 10#反击之
	ENAMERESIST = 11#压制的
end

#结构体：SItem的继承体系类型
class EType_SItem
	ETYPE_SITEM = 0#类型：SItem
	ETYPE_SSTACK = 1#类型：SStack
	ETYPE_SEQUIPTRUMP = 2#类型：SEquipTrump
	ETYPE_SCITTA = 3#类型：SCitta
	ETYPE_STRUMP = 4#类型：STrump
	ETYPE_SFASHION = 5#类型：SFashion
	ETYPE_SGEMSTONE = 6#类型：SGemstone
end

#显示用的模板数据
class SItemGenInfo
	attr_accessor:wItemID #(UINT16)模板ID
	attr_accessor:dwCount #(UINT32)数量
	attr_accessor:byQuality #(UINT8)品质
	attr_accessor:eBindType #(枚举类型：EBindType)绑定类型
	attr_accessor:dwTimeID #(UINT32)时钟ID

	#构造函数
	def initialize
		@wItemID = 0
		@dwCount = 0
		@byQuality = 0
		@eBindType = 0
		@dwTimeID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wItemID = @wItemID
		obj.dwCount = @dwCount
		obj.byQuality = @byQuality
		obj.eBindType = @eBindType
		obj.dwTimeID = @dwTimeID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SItemGenInfo.new
		s.wItemID = ByteUtil::readUINT16(data)
		s.dwCount = ByteUtil::readUINT32(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.eBindType = ByteUtil::readUINT8(data)
		s.dwTimeID = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SItemGenInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeUINT32(data, @dwCount)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT8(data, @eBindType)
		ByteUtil::writeUINT32(data, @dwTimeID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#物品列表
class SInstCount
	attr_accessor:qwInstID #(UINT64)道具唯一ID
	attr_accessor:wCount #(UINT32)道具个数

	#构造函数
	def initialize
		@qwInstID = 0
		@wCount = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInstID = @qwInstID
		obj.wCount = @wCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SInstCount.new
		s.qwInstID = ByteUtil::readUINT64(data)
		s.wCount = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SInstCount::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT32(data, @wCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#物品列表
class SItemCount
	attr_accessor:wItemID #(UINT16)道具ID
	attr_accessor:wCount #(UINT32)道具个数

	#构造函数
	def initialize
		@wItemID = 0
		@wCount = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wItemID = @wItemID
		obj.wCount = @wCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SItemCount.new
		s.wItemID = ByteUtil::readUINT16(data)
		s.wCount = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SItemCount::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeUINT32(data, @wCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#资源列表
class SResource
	attr_accessor:_eRes #(枚类型：ProtoCommon::EMoneyType)资源(货币)类型
	attr_accessor:_dwValue #(UINT32)资源(货币)数量

	#构造函数
	def initialize
		@_eRes = 0
		@_dwValue = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj._eRes = @_eRes
		obj._dwValue = @_dwValue
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SResource.new
		s._eRes = ByteUtil::readUINT8(data)
		s._dwValue = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SResource::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @_eRes)
		ByteUtil::writeUINT32(data, @_dwValue)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#EDataType:eRoleItemInfo
class RoleItemInfo
	attr_accessor:qwInstID #(UINT64)物品唯一ID
	attr_accessor:wItemID #(UINT16)物品模板
	attr_accessor:byStoreType #(UINT8)背包类型-数据来源：EStoreType
	attr_accessor:wIndex #(INT16)所属背包的位置
	attr_accessor:wCount #(UINT16)具的堆叠数
	attr_accessor:byBind #(UINT8)绑定类型0非绑定，1绑定
	attr_accessor:byExpired #(UINT8)是否时效，>0 时效物品
	attr_accessor:dwExpireTime #(UINT32)时效过期时间
	attr_accessor:dwMark #(UINT32)标记为错误物品,存下标记时间

	#构造函数
	def initialize
		@qwInstID = 0
		@wItemID = 0
		@byStoreType = 0
		@wIndex = 0
		@wCount = 0
		@byBind = 0
		@byExpired = 0
		@dwExpireTime = 0
		@dwMark = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInstID = @qwInstID
		obj.wItemID = @wItemID
		obj.byStoreType = @byStoreType
		obj.wIndex = @wIndex
		obj.wCount = @wCount
		obj.byBind = @byBind
		obj.byExpired = @byExpired
		obj.dwExpireTime = @dwExpireTime
		obj.dwMark = @dwMark
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = RoleItemInfo.new
		s.qwInstID = ByteUtil::readUINT64(data)
		s.wItemID = ByteUtil::readUINT16(data)
		s.byStoreType = ByteUtil::readUINT8(data)
		s.wIndex = ByteUtil::readINT16(data)
		s.wCount = ByteUtil::readUINT16(data)
		s.byBind = ByteUtil::readUINT8(data)
		s.byExpired = ByteUtil::readUINT8(data)
		s.dwExpireTime = ByteUtil::readUINT32(data)
		s.dwMark = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = RoleItemInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeUINT8(data, @byStoreType)
		ByteUtil::writeINT16(data, @wIndex)
		ByteUtil::writeUINT16(data, @wCount)
		ByteUtil::writeUINT8(data, @byBind)
		ByteUtil::writeUINT8(data, @byExpired)
		ByteUtil::writeUINT32(data, @dwExpireTime)
		ByteUtil::writeUINT32(data, @dwMark)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#洗炼信息
class SShuffleInfo
	attr_accessor:dwType #(UINT32)洗炼类型
	attr_accessor:dwValue #(UINT32)洗炼数值

	#构造函数
	def initialize
		@dwType = 0
		@dwValue = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwType = @dwType
		obj.dwValue = @dwValue
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SShuffleInfo.new
		s.dwType = ByteUtil::readUINT32(data)
		s.dwValue = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SShuffleInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwType)
		ByteUtil::writeUINT32(data, @dwValue)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#道具的信息
class SItem
	attr_accessor:sItemInfo #(类类型：RoleItemInfo)道具信息

	#构造函数
	def initialize
		@sItemInfo = RoleItemInfo.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SItem::ETYPE_SITEM
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.sItemInfo = @sItemInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SItem.new
		s.sItemInfo = RoleItemInfo::fromStream(data)
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_SItem::ETYPE_SITEM
				s = SItem::fromStream(data)
			when EType_SItem::ETYPE_SSTACK
				s = SStack::fromStream(data)
			when EType_SItem::ETYPE_SEQUIPTRUMP
				s = SEquipTrump::fromStream(data)
			when EType_SItem::ETYPE_SCITTA
				s = SCitta::fromStream(data)
			when EType_SItem::ETYPE_STRUMP
				s = STrump::fromStream(data)
			when EType_SItem::ETYPE_SFASHION
				s = SFashion::fromStream(data)
			when EType_SItem::ETYPE_SGEMSTONE
				s = SGemstone::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SItem::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SItem::superFromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		@sItemInfo.toStream(data)
	end

	def superToStream(data)
		eType = getClassType()
		ByteUtil::writeUINT8(data, eType)
		toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end

	def self.superVectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.superToStream(data)
		end
	end
end

#堆叠道具的信息，只用于识别
class SStack < SItem
	#构造函数
	def initialize
		super()
	end

	#获取继承类的类型
	def getClassType
		return EType_SItem::ETYPE_SSTACK
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SStack.new
		base = SItem::fromStream(data)
		base.copyTo(s)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SStack::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#装备的信息
class SEquipTrump < SItem
	attr_accessor:qwOwnerID #(UINT64)散仙唯一ID，属于散仙的物品时有效
	attr_accessor:byIntensifyLvl #(UINT8)当前强化等级
	attr_accessor:byIntensifyLvlMax #(UINT8)可强的最高等级
	attr_accessor:dwBlessing #(UINT32)强化祝福值
	attr_accessor:vecShuffleInfo #(SShuffleInfo的数组)洗炼信息
	attr_accessor:vecNowReplace #(SShuffleInfo的数组)可替换的洗炼信息
	attr_accessor:dwXiLianBlessing #(UINT32)洗练祝福值

	#构造函数
	def initialize
		super()
		@qwOwnerID = 0
		@byIntensifyLvl = 0
		@byIntensifyLvlMax = 0
		@dwBlessing = 0
		@vecShuffleInfo = Array.new
		@vecNowReplace = Array.new
		@dwXiLianBlessing = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SItem::ETYPE_SEQUIPTRUMP
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.qwOwnerID = @qwOwnerID
		obj.byIntensifyLvl = @byIntensifyLvl
		obj.byIntensifyLvlMax = @byIntensifyLvlMax
		obj.dwBlessing = @dwBlessing
		obj.vecShuffleInfo = @vecShuffleInfo
		obj.vecNowReplace = @vecNowReplace
		obj.dwXiLianBlessing = @dwXiLianBlessing
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SEquipTrump.new
		base = SItem::fromStream(data)
		base.copyTo(s)
		s.qwOwnerID = ByteUtil::readUINT64(data)
		s.byIntensifyLvl = ByteUtil::readUINT8(data)
		s.byIntensifyLvlMax = ByteUtil::readUINT8(data)
		s.dwBlessing = ByteUtil::readUINT32(data)
		s.vecShuffleInfo = SShuffleInfo::vectorFromStream(data)
		s.vecNowReplace = SShuffleInfo::vectorFromStream(data)
		s.dwXiLianBlessing = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SEquipTrump::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT64(data, @qwOwnerID)
		ByteUtil::writeUINT8(data, @byIntensifyLvl)
		ByteUtil::writeUINT8(data, @byIntensifyLvlMax)
		ByteUtil::writeUINT32(data, @dwBlessing)
		SShuffleInfo::vectorToStream(data, @vecShuffleInfo)
		SShuffleInfo::vectorToStream(data, @vecNowReplace)
		ByteUtil::writeUINT32(data, @dwXiLianBlessing)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#心法的信息
class SCitta < SItem
	attr_accessor:qwOwnerID #(UINT64)散仙唯一ID，属于散仙的物品时有效
	attr_accessor:eCittaNameType #(枚举类型：ECittaNameType)心法姓名前缀
	attr_accessor:oAttrVec #(SFtAttrMod的数组)增加属性
	attr_accessor:dwSkillID #(UINT32)附加技能ID
	attr_accessor:dwSignetID #(UINT32)印记ID

	#构造函数
	def initialize
		super()
		@qwOwnerID = 0
		@eCittaNameType = 0
		@oAttrVec = Array.new
		@dwSkillID = 0
		@dwSignetID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SItem::ETYPE_SCITTA
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.qwOwnerID = @qwOwnerID
		obj.eCittaNameType = @eCittaNameType
		obj.oAttrVec = @oAttrVec
		obj.dwSkillID = @dwSkillID
		obj.dwSignetID = @dwSignetID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SCitta.new
		base = SItem::fromStream(data)
		base.copyTo(s)
		s.qwOwnerID = ByteUtil::readUINT64(data)
		s.eCittaNameType = ByteUtil::readUINT8(data)
		s.oAttrVec = SFtAttrMod::vectorFromStream(data)
		s.dwSkillID = ByteUtil::readUINT32(data)
		s.dwSignetID = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SCitta::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT64(data, @qwOwnerID)
		ByteUtil::writeUINT8(data, @eCittaNameType)
		SFtAttrMod::vectorToStream(data, @oAttrVec)
		ByteUtil::writeUINT32(data, @dwSkillID)
		ByteUtil::writeUINT32(data, @dwSignetID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#法宝信息
class STrump < SItem
	attr_accessor:qwRoleID #(UINT64)拥有者RoleID
	attr_accessor:byActived #(UINT8)
	attr_accessor:byUsed #(UINT8)法宝是否出战
	attr_accessor:dwExp #(UINT32)法宝祭炼值
	attr_accessor:wLevel #(UINT16)法宝祭炼等级
	attr_accessor:wRank #(UINT16)法宝祭炼阶数

	#构造函数
	def initialize
		super()
		@qwRoleID = 0
		@byActived = 0
		@byUsed = 0
		@dwExp = 0
		@wLevel = 0
		@wRank = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SItem::ETYPE_STRUMP
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.qwRoleID = @qwRoleID
		obj.byActived = @byActived
		obj.byUsed = @byUsed
		obj.dwExp = @dwExp
		obj.wLevel = @wLevel
		obj.wRank = @wRank
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STrump.new
		base = SItem::fromStream(data)
		base.copyTo(s)
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.byActived = ByteUtil::readUINT8(data)
		s.byUsed = ByteUtil::readUINT8(data)
		s.dwExp = ByteUtil::readUINT32(data)
		s.wLevel = ByteUtil::readUINT16(data)
		s.wRank = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STrump::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT8(data, @byActived)
		ByteUtil::writeUINT8(data, @byUsed)
		ByteUtil::writeUINT32(data, @dwExp)
		ByteUtil::writeUINT16(data, @wLevel)
		ByteUtil::writeUINT16(data, @wRank)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#时装信息
class SFashion < SItem
	attr_accessor:byLevel #(UINT8)时装等级
	attr_accessor:dwExp #(UINT32)时装经验
	attr_accessor:bySelected #(UINT8)是否选中
	attr_accessor:byHide #(UINT8)是否隐藏

	#构造函数
	def initialize
		super()
		@byLevel = 0
		@dwExp = 0
		@bySelected = 0
		@byHide = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SItem::ETYPE_SFASHION
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.byLevel = @byLevel
		obj.dwExp = @dwExp
		obj.bySelected = @bySelected
		obj.byHide = @byHide
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SFashion.new
		base = SItem::fromStream(data)
		base.copyTo(s)
		s.byLevel = ByteUtil::readUINT8(data)
		s.dwExp = ByteUtil::readUINT32(data)
		s.bySelected = ByteUtil::readUINT8(data)
		s.byHide = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SFashion::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT32(data, @dwExp)
		ByteUtil::writeUINT8(data, @bySelected)
		ByteUtil::writeUINT8(data, @byHide)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#宝石信息
class SGemstone < SItem
	attr_accessor:qwOwnerID #(UINT64)散仙唯一ID

	#构造函数
	def initialize
		super()
		@qwOwnerID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SItem::ETYPE_SGEMSTONE
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.qwOwnerID = @qwOwnerID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGemstone.new
		base = SItem::fromStream(data)
		base.copyTo(s)
		s.qwOwnerID = ByteUtil::readUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGemstone::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT64(data, @qwOwnerID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#背包信息
class SStoreStream
	attr_accessor:wCapacity #(UINT16)背包大小(不发最大值，最大值由两端的配置决定)
	attr_accessor:vecItem #(SItem的数组)物品信息

	#构造函数
	def initialize
		@wCapacity = 0
		@vecItem = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wCapacity = @wCapacity
		obj.vecItem = @vecItem
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SStoreStream.new
		s.wCapacity = ByteUtil::readUINT16(data)
		s.vecItem = SItem::superVectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SStoreStream::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wCapacity)
		SItem::superVectorToStream(data, @vecItem)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家道具冷却时间
class SItemColdTime
	attr_accessor:wID #(UINT16)冷却ID
	attr_accessor:dwTime #(UINT32)冷却到期时间

	#构造函数
	def initialize
		@wID = 0
		@dwTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wID = @wID
		obj.dwTime = @dwTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SItemColdTime.new
		s.wID = ByteUtil::readUINT16(data)
		s.dwTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SItemColdTime::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wID)
		ByteUtil::writeUINT32(data, @dwTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家获得道具
class SAddItemMsg
	attr_accessor:wItemID #(UINT16)道具的ID
	attr_accessor:wCount #(UINT16)道具个数
	attr_accessor:byQuality #(UINT8)道具品质

	#构造函数
	def initialize
		@wItemID = 0
		@wCount = 0
		@byQuality = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wItemID = @wItemID
		obj.wCount = @wCount
		obj.byQuality = @byQuality
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SAddItemMsg.new
		s.wItemID = ByteUtil::readUINT16(data)
		s.wCount = ByteUtil::readUINT16(data)
		s.byQuality = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SAddItemMsg::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeUINT16(data, @wCount)
		ByteUtil::writeUINT8(data, @byQuality)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#记录的道具
class SLoggedItem
	attr_accessor:wItemID #(UINT16)道具ID
	attr_accessor:byQuality #(UINT8)品质
	attr_accessor:dwCount #(UINT32)道具个数
	attr_accessor:bBind #(bool)是否绑定

	#构造函数
	def initialize
		@wItemID = 0
		@byQuality = 0
		@dwCount = 0
		@bBind = false
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wItemID = @wItemID
		obj.byQuality = @byQuality
		obj.dwCount = @dwCount
		obj.bBind = @bBind
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SLoggedItem.new
		s.wItemID = ByteUtil::readUINT16(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.dwCount = ByteUtil::readUINT32(data)
		s.bBind = ByteUtil::readBOOL(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SLoggedItem::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT32(data, @dwCount)
		ByteUtil::writeBOOL(data, @bBind)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#收件人信息
class SGMMailTarget
	attr_accessor:qwTargetID #(UINT64)收件人ID
	attr_accessor:strTarget #(string)收件人名

	#构造函数
	def initialize
		@qwTargetID = 0
		@strTarget = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwTargetID = @qwTargetID
		obj.strTarget = @strTarget
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGMMailTarget.new
		s.qwTargetID = ByteUtil::readUINT64(data)
		s.strTarget = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGMMailTarget::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwTargetID)
		ByteUtil::writeSTRING(data, @strTarget)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#道具信息
class SGMMailItem
	attr_accessor:wItemID #(UINT16)道具配置ID
	attr_accessor:wItemCount #(UINT32)道具数量

	#构造函数
	def initialize
		@wItemID = 0
		@wItemCount = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wItemID = @wItemID
		obj.wItemCount = @wItemCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGMMailItem.new
		s.wItemID = ByteUtil::readUINT16(data)
		s.wItemCount = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGMMailItem::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeUINT32(data, @wItemCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetStore:请求包裹信息(整个包裹)]的原来的参数组成的结构体
class SOrigParam_GetStore
	attr_accessor:eStoreType #(枚举类型：EStoreType)存储类型

	#构造函数
	def initialize
		@eStoreType = 0
	end
end

#函数[GetStore:请求包裹信息(整个包裹)]的返回的参数组成的结构体
class SRetParam_GetStore
	attr_accessor:stStoreStream#(类类型：SStoreStream)背包信息
	attr_accessor:dwNextUnlockTime#(UINT32)下一个解锁背包空间的时间 0-表示可解锁 0xFFFFFFFF-表示没有可解锁的了 其他为秒

	#构造函数
	def initialize
		@stStoreStream = SStoreStream.new
		@dwNextUnlockTime = 0
	end
end

#函数[UseItem:请求使用包裹中的道具]的原来的参数组成的结构体
class SOrigParam_UseItem
	attr_accessor:eStoreType #(枚举类型：EStoreType)存储类型
	attr_accessor:qwRoleID #(UINT64)针对的角色ID
	attr_accessor:qwMercenID #(UINT64)针对的佣兵ID
	attr_accessor:qwInstID #(UINT64)优先使用的物品实例ID
	attr_accessor:wStack #(UINT16)使用个数(只针对堆叠道具)

	#构造函数
	def initialize
		@eStoreType = 0
		@qwRoleID = 0
		@qwMercenID = 0
		@qwInstID = 0
		@wStack = 0
	end
end

#函数[UseItem:请求使用包裹中的道具]的返回的参数组成的结构体
class SRetParam_UseItem
	attr_accessor:eResult#(枚举类型：EItemResult)使用道具结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[ExpandStore:扩充包裹或仓库]的返回的参数组成的结构体
class SRetParam_ExpandStore
	attr_accessor:eResult#(枚举类型：EItemResult)扩充结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[RelocateStoreItem:包裹或仓库中道具换位置]的原来的参数组成的结构体
class SOrigParam_RelocateStoreItem
	attr_accessor:eStoreType #(枚举类型：EStoreType)存储类型
	attr_accessor:qwInstID #(UINT64)道具的实例ID

	#构造函数
	def initialize
		@eStoreType = 0
		@qwInstID = 0
	end
end

#函数[RelocateStoreItem:包裹或仓库中道具换位置]的返回的参数组成的结构体
class SRetParam_RelocateStoreItem
	attr_accessor:eResult#(枚举类型：EItemResult)换位置的结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[TidyupStore:整理包裹或仓库]的原来的参数组成的结构体
class SOrigParam_TidyupStore
	attr_accessor:eStoreType #(枚举类型：EStoreType)存储类型

	#构造函数
	def initialize
		@eStoreType = 0
	end
end

#函数[TidyupStore:整理包裹或仓库]的返回的参数组成的结构体
class SRetParam_TidyupStore
	attr_accessor:eResult#(枚举类型：EItemResult)整理的结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[SplitStackItem:拆分包裹或仓库中的堆叠类道具]的原来的参数组成的结构体
class SOrigParam_SplitStackItem
	attr_accessor:eStoreType #(枚举类型：EStoreType)存储类型
	attr_accessor:qwInstID #(UINT64)道具的实例ID

	#构造函数
	def initialize
		@eStoreType = 0
		@qwInstID = 0
	end
end

#函数[SplitStackItem:拆分包裹或仓库中的堆叠类道具]的返回的参数组成的结构体
class SRetParam_SplitStackItem
	attr_accessor:eResult#(枚举类型：EItemResult)拆分的结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[MergeStackItem:合并包裹或仓库中的堆叠类道具]的原来的参数组成的结构体
class SOrigParam_MergeStackItem
	attr_accessor:eStoreType #(枚举类型：EStoreType)存储类型
	attr_accessor:qwFromInstID #(UINT64)源道具的实例ID
	attr_accessor:qwToInstID #(UINT64)目的道具的实例ID

	#构造函数
	def initialize
		@eStoreType = 0
		@qwFromInstID = 0
		@qwToInstID = 0
	end
end

#函数[MergeStackItem:合并包裹或仓库中的堆叠类道具]的返回的参数组成的结构体
class SRetParam_MergeStackItem
	attr_accessor:eResult#(枚举类型：EItemResult)合并的结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[DestroyStoreItem:销毁包裹或仓库中的道具]的原来的参数组成的结构体
class SOrigParam_DestroyStoreItem
	attr_accessor:eStoreType #(枚举类型：EStoreType)存储类型
	attr_accessor:qwInstID #(UINT64)道具的实例ID

	#构造函数
	def initialize
		@eStoreType = 0
		@qwInstID = 0
	end
end

#函数[DestroyStoreItem:销毁包裹或仓库中的道具]的返回的参数组成的结构体
class SRetParam_DestroyStoreItem
	attr_accessor:eResult#(枚举类型：EItemResult)销毁的结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[TransferItem:在包裹和仓库之间移动道具]的返回的参数组成的结构体
class SRetParam_TransferItem
	attr_accessor:eResult#(枚举类型：EItemResult)移动的结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[SellItem:请求出售包裹中的道具-出售给系统]的原来的参数组成的结构体
class SOrigParam_SellItem
	attr_accessor:vecInstID #(UINT64数组)出售的道具实例ID集合

	#构造函数
	def initialize
		@vecInstID = Array.new
	end
end

#函数[SellItem:请求出售包裹中的道具-出售给系统]的返回的参数组成的结构体
class SRetParam_SellItem
	attr_accessor:eResult#(枚举类型：EItemResult)使用道具结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[SellItemWithCount:请求按个数出售包裹中的道具-出售给系统]的原来的参数组成的结构体
class SOrigParam_SellItemWithCount
	attr_accessor:eStoreType #(枚举类型：EStoreType)存储类型
	attr_accessor:qwInstID #(UINT64)优先卖出的物品实例ID
	attr_accessor:wStack #(UINT16)卖出个数

	#构造函数
	def initialize
		@eStoreType = 0
		@qwInstID = 0
		@wStack = 0
	end
end

#函数[SellItemWithCount:请求按个数出售包裹中的道具-出售给系统]的返回的参数组成的结构体
class SRetParam_SellItemWithCount
	attr_accessor:eResult#(枚举类型：EItemResult)卖出道具结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[UnlockPack:解锁背包格子]的返回的参数组成的结构体
class SRetParam_UnlockPack
	attr_accessor:eResult#(枚举类型：EItemResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[RecordTransfPoint:记录传送点]的返回的参数组成的结构体
class SRetParam_RecordTransfPoint
	attr_accessor:eResult#(枚举类型：EItemResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[TransfMapPoint:传送]的返回的参数组成的结构体
class SRetParam_TransfMapPoint
	attr_accessor:eResult#(枚举类型：EItemResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[WearCitta:请求装备心法]的原来的参数组成的结构体
class SOrigParam_WearCitta
	attr_accessor:qwInstID #(UINT64)装备的实例ID
	attr_accessor:eSlotType #(枚举类型：ECittaSlotType)装备位的类型

	#构造函数
	def initialize
		@qwInstID = 0
		@eSlotType = 0
	end
end

#函数[WearCitta:请求装备心法]的返回的参数组成的结构体
class SRetParam_WearCitta
	attr_accessor:eResult#(枚举类型：ECittaResult)穿上装备的结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[TakeoffCitta:请求卸下心法]的原来的参数组成的结构体
class SOrigParam_TakeoffCitta
	attr_accessor:eSlotType #(枚举类型：ECittaSlotType)装备位的类型
	attr_accessor:wIndex #(INT16)放入心法栏位置：-1表示右击脱下，非-1表示放入包裹的位置

	#构造函数
	def initialize
		@eSlotType = 0
		@wIndex = 0
	end
end

#函数[TakeoffCitta:请求卸下心法]的返回的参数组成的结构体
class SRetParam_TakeoffCitta
	attr_accessor:eResult#(枚举类型：ECittaResult)脱下装备的结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[MergeCitta:请求合成心法]的返回的参数组成的结构体
class SRetParam_MergeCitta
	attr_accessor:eResult#(枚举类型：ECittaResult)结果
	attr_accessor:vecItemCitta#(SItem的数组)新增的道具

	#构造函数
	def initialize
		@eResult = 0
		@vecItemCitta = Array.new
	end
end

#函数[BreakCitta:请求分解心法]的返回的参数组成的结构体
class SRetParam_BreakCitta
	attr_accessor:eResult#(枚举类型：ECittaResult)结果
	attr_accessor:vecItemInfo#(SItemGenInfo的数组)分解产生的道具

	#构造函数
	def initialize
		@eResult = 0
		@vecItemInfo = Array.new
	end
end

#函数[ActiveTrump:激活法宝]的返回的参数组成的结构体
class SRetParam_ActiveTrump
	attr_accessor:eResult#(枚举类型：ETrumpResult)结果
	attr_accessor:vecTrump#(STrump的数组)新法宝

	#构造函数
	def initialize
		@eResult = 0
		@vecTrump = Array.new
	end
end

#函数[EquipTrump:出战法宝]的返回的参数组成的结构体
class SRetParam_EquipTrump
	attr_accessor:eResult#(枚举类型：ETrumpResult)结果
	attr_accessor:vecTrump#(STrump的数组)新法宝

	#构造函数
	def initialize
		@eResult = 0
		@vecTrump = Array.new
	end
end

#函数[UnEquipTrump:卸下法宝]的返回的参数组成的结构体
class SRetParam_UnEquipTrump
	attr_accessor:eResult#(枚举类型：ETrumpResult)结果
	attr_accessor:vecTrump#(STrump的数组)新法宝

	#构造函数
	def initialize
		@eResult = 0
		@vecTrump = Array.new
	end
end

#函数[UpgradeTrump:祭炼法宝]的返回的参数组成的结构体
class SRetParam_UpgradeTrump
	attr_accessor:eResult#(枚举类型：ETrumpResult)结果
	attr_accessor:vecTrump#(STrump的数组)新法宝

	#构造函数
	def initialize
		@eResult = 0
		@vecTrump = Array.new
	end
end

#函数[EvolveTrump:提升法宝品级]的返回的参数组成的结构体
class SRetParam_EvolveTrump
	attr_accessor:eResult#(枚举类型：ETrumpResult)结果
	attr_accessor:vecTrump#(STrump的数组)新法宝

	#构造函数
	def initialize
		@eResult = 0
		@vecTrump = Array.new
	end
end

#函数[FashionActive:激活时装]的返回的参数组成的结构体
class SRetParam_FashionActive
	attr_accessor:eResult#(枚举类型：EFashionResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[FashionHide:隐藏所选时装]的返回的参数组成的结构体
class SRetParam_FashionHide
	attr_accessor:eResult#(枚举类型：EFashionResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[FashionChange:选择时装]的返回的参数组成的结构体
class SRetParam_FashionChange
	attr_accessor:eResult#(枚举类型：EFashionResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[FashionUpgrade:时装炼化]的返回的参数组成的结构体
class SRetParam_FashionUpgrade
	attr_accessor:eResult#(枚举类型：EFashionResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[WareGemStone:穿戴宝石]的返回的参数组成的结构体
class SRetParam_WareGemStone
	attr_accessor:eResult#(枚举类型：EGemstoneResult)结果
	attr_accessor:qwFighterID#(UINT64)将ID
	attr_accessor:byPos#(UINT8)穿戴位置
	attr_accessor:Item#(类类型：SGemstone)宝石

	#构造函数
	def initialize
		@eResult = 0
		@qwFighterID = 0
		@byPos = 0
		@Item = SGemstone.new
	end
end

#函数[TakeOffGemStone:取下宝石]的返回的参数组成的结构体
class SRetParam_TakeOffGemStone
	attr_accessor:eResult#(枚举类型：EGemstoneResult)结果
	attr_accessor:qwFighterID#(UINT64)将ID
	attr_accessor:byPos#(UINT8)穿戴位置

	#构造函数
	def initialize
		@eResult = 0
		@qwFighterID = 0
		@byPos = 0
	end
end

#函数[ComposeGemStone:合成宝石]的返回的参数组成的结构体
class SRetParam_ComposeGemStone
	attr_accessor:eResult#(枚举类型：EGemstoneResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[ComposeGemStoneOneKey:一键合成宝石]的返回的参数组成的结构体
class SRetParam_ComposeGemStoneOneKey
	attr_accessor:eResult#(枚举类型：EGemstoneResult)结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：道具相关协议
class ItemProtBase < ProtocolBase
	#以下为发送函数
	#发送：请求包裹信息(整个包裹)
	def send_GetStore(
		eStoreType #(枚举类型：EStoreType)存储类型
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		origParam = SOrigParam_GetStore.new
		origParam.eStoreType = eStoreType
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eStoreType)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求使用包裹中的道具
	def send_UseItem(
		eStoreType,  #(枚举类型：EStoreType)存储类型
		qwRoleID,  #(UINT64)针对的角色ID
		qwMercenID,  #(UINT64)针对的佣兵ID
		qwInstID,  #(UINT64)优先使用的物品实例ID
		wStack #(UINT16)使用个数(只针对堆叠道具)
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		origParam = SOrigParam_UseItem.new
		origParam.eStoreType = eStoreType
		origParam.qwRoleID = qwRoleID
		origParam.qwMercenID = qwMercenID
		origParam.qwInstID = qwInstID
		origParam.wStack = wStack
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eStoreType)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT64(data, qwMercenID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT16(data, wStack)
		return @svrHandler.sendPacket(data)
	end

	#发送：扩充包裹或仓库
	def send_ExpandStore(
		eStoreType,  #(枚举类型：EStoreType)存储类型
		byCount,  #(UINT8)扩充个数
		eCoinType #(枚类型：ProtoCommon::ECoinType)货币类型
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eStoreType)
		ByteUtil::writeUINT8(data, byCount)
		ByteUtil::writeUINT8(data, eCoinType)
		return @svrHandler.sendPacket(data)
	end

	#发送：包裹或仓库中道具换位置
	def send_RelocateStoreItem(
		eStoreType,  #(枚举类型：EStoreType)存储类型
		qwInstID,  #(UINT64)道具的实例ID
		wNewIndex #(INT16)道具在包裹中新的位置0开始
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		origParam = SOrigParam_RelocateStoreItem.new
		origParam.eStoreType = eStoreType
		origParam.qwInstID = qwInstID
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eStoreType)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeINT16(data, wNewIndex)
		return @svrHandler.sendPacket(data)
	end

	#发送：整理包裹或仓库
	def send_TidyupStore(
		eStoreType #(枚举类型：EStoreType)存储类型
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		origParam = SOrigParam_TidyupStore.new
		origParam.eStoreType = eStoreType
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eStoreType)
		return @svrHandler.sendPacket(data)
	end

	#发送：拆分包裹或仓库中的堆叠类道具
	def send_SplitStackItem(
		eStoreType,  #(枚举类型：EStoreType)存储类型
		qwInstID,  #(UINT64)道具的实例ID
		wStack,  #(UINT16)拆分出来的堆叠数量
		wIndex #(INT16)拆分出来的堆叠道具的存储位置(-1表示选第一个空位)
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		origParam = SOrigParam_SplitStackItem.new
		origParam.eStoreType = eStoreType
		origParam.qwInstID = qwInstID
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eStoreType)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT16(data, wStack)
		ByteUtil::writeINT16(data, wIndex)
		return @svrHandler.sendPacket(data)
	end

	#发送：合并包裹或仓库中的堆叠类道具
	def send_MergeStackItem(
		eStoreType,  #(枚举类型：EStoreType)存储类型
		qwFromInstID,  #(UINT64)源道具的实例ID
		qwToInstID #(UINT64)目的道具的实例ID
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		origParam = SOrigParam_MergeStackItem.new
		origParam.eStoreType = eStoreType
		origParam.qwFromInstID = qwFromInstID
		origParam.qwToInstID = qwToInstID
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eStoreType)
		ByteUtil::writeUINT64(data, qwFromInstID)
		ByteUtil::writeUINT64(data, qwToInstID)
		return @svrHandler.sendPacket(data)
	end

	#发送：销毁包裹或仓库中的道具
	def send_DestroyStoreItem(
		eStoreType,  #(枚举类型：EStoreType)存储类型
		qwInstID #(UINT64)道具的实例ID
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		origParam = SOrigParam_DestroyStoreItem.new
		origParam.eStoreType = eStoreType
		origParam.qwInstID = qwInstID
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eStoreType)
		ByteUtil::writeUINT64(data, qwInstID)
		return @svrHandler.sendPacket(data)
	end

	#发送：在包裹和仓库之间移动道具
	def send_TransferItem(
		eFromStoreType,  #(枚举类型：EStoreType)源存储类型
		eToStoreType,  #(枚举类型：EStoreType)目的存储类型
		qwInstID,  #(UINT64)道具的实例ID
		wIndex #(INT16)道具在目的存储中的位置(-1表示选第一个空位)
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eFromStoreType)
		ByteUtil::writeUINT8(data, eToStoreType)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeINT16(data, wIndex)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求出售包裹中的道具-出售给系统
	def send_SellItem(
		vecInstID #(UINT64数组)出售的道具实例ID集合
	)
		sessionID = @sessionMgr.getNewSession(self, 10);
		origParam = SOrigParam_SellItem.new
		origParam.vecInstID = vecInstID
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeVecUINT64(data, vecInstID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求按个数出售包裹中的道具-出售给系统
	def send_SellItemWithCount(
		eStoreType,  #(枚举类型：EStoreType)存储类型
		qwInstID,  #(UINT64)优先卖出的物品实例ID
		wStack #(UINT16)卖出个数
	)
		sessionID = @sessionMgr.getNewSession(self, 11);
		origParam = SOrigParam_SellItemWithCount.new
		origParam.eStoreType = eStoreType
		origParam.qwInstID = qwInstID
		origParam.wStack = wStack
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eStoreType)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT16(data, wStack)
		return @svrHandler.sendPacket(data)
	end

	#发送：解锁背包格子
	def send_UnlockPack(
	)
		sessionID = @sessionMgr.getNewSession(self, 12);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：打开道具日志
	def send_OpenItemLogger(
		eType #(枚举类型：EItemLoggerType)
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 13
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT8(data, eType)
		return @svrHandler.sendPacket(data)
	end

	#发送：记录传送点
	def send_RecordTransfPoint(
		qwInstID,  #(UINT64)道具ID
		wIndex #(UINT16)存储序号
	)
		sessionID = @sessionMgr.getNewSession(self, 13);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 14
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT16(data, wIndex)
		return @svrHandler.sendPacket(data)
	end

	#发送：传送
	def send_TransfMapPoint(
		qwInstID,  #(UINT64)道具ID
		wIndex,  #(UINT16)存储序号
		wMapID #(UINT16)地图ID
	)
		sessionID = @sessionMgr.getNewSession(self, 14);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 15
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT16(data, wIndex)
		ByteUtil::writeUINT16(data, wMapID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求装备心法
	def send_WearCitta(
		qwInstID,  #(UINT64)装备的实例ID
		eSlotType #(枚举类型：ECittaSlotType)装备位的类型
	)
		sessionID = @sessionMgr.getNewSession(self, 15);
		origParam = SOrigParam_WearCitta.new
		origParam.qwInstID = qwInstID
		origParam.eSlotType = eSlotType
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 16
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeINT8(data, eSlotType)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求卸下心法
	def send_TakeoffCitta(
		eSlotType,  #(枚举类型：ECittaSlotType)装备位的类型
		wIndex #(INT16)放入心法栏位置：-1表示右击脱下，非-1表示放入包裹的位置
	)
		sessionID = @sessionMgr.getNewSession(self, 16);
		origParam = SOrigParam_TakeoffCitta.new
		origParam.eSlotType = eSlotType
		origParam.wIndex = wIndex
		@sessionMgr.storeData(sessionID, origParam)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 17
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeINT8(data, eSlotType)
		ByteUtil::writeINT16(data, wIndex)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求合成心法
	def send_MergeCitta(
		eBindType,  #(枚举类型：EBindUseType)绑定使用方式
		wItemID,  #(UINT16)制作心法模版ID
		wCount #(UINT16)制作数量
	)
		sessionID = @sessionMgr.getNewSession(self, 17);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 18
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eBindType)
		ByteUtil::writeUINT16(data, wItemID)
		ByteUtil::writeUINT16(data, wCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求分解心法
	def send_BreakCitta(
		vecInstID #(UINT64数组)物品唯一ID
	)
		sessionID = @sessionMgr.getNewSession(self, 18);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 19
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeVecUINT64(data, vecInstID)
		return @svrHandler.sendPacket(data)
	end

	#发送：激活法宝
	def send_ActiveTrump(
		wItemID #(UINT16)法宝道具ID
	)
		sessionID = @sessionMgr.getNewSession(self, 19);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 20
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wItemID)
		return @svrHandler.sendPacket(data)
	end

	#发送：出战法宝
	def send_EquipTrump(
		qwInstID #(UINT64)法宝的实例ID
	)
		sessionID = @sessionMgr.getNewSession(self, 20);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 21
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		return @svrHandler.sendPacket(data)
	end

	#发送：卸下法宝
	def send_UnEquipTrump(
		qwInstID #(UINT64)法宝的实例ID
	)
		sessionID = @sessionMgr.getNewSession(self, 21);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 22
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		return @svrHandler.sendPacket(data)
	end

	#发送：祭炼法宝
	def send_UpgradeTrump(
		qwInstID,  #(UINT64)法宝的实例ID
		byOneKey #(UINT8)是否一键
	)
		sessionID = @sessionMgr.getNewSession(self, 22);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 23
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT8(data, byOneKey)
		return @svrHandler.sendPacket(data)
	end

	#发送：提升法宝品级
	def send_EvolveTrump(
		qwInstID #(UINT64)法宝的实例ID
	)
		sessionID = @sessionMgr.getNewSession(self, 23);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 24
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		return @svrHandler.sendPacket(data)
	end

	#发送：激活时装
	def send_FashionActive(
		wItemID #(UINT16)时装物品ID
	)
		sessionID = @sessionMgr.getNewSession(self, 24);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 25
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wItemID)
		return @svrHandler.sendPacket(data)
	end

	#发送：隐藏所选时装
	def send_FashionHide(
		byType,  #(UINT8)0-神器时装 1-神依时装
		byHide #(UINT8)0-显示 1-隐藏
	)
		sessionID = @sessionMgr.getNewSession(self, 25);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 26
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byType)
		ByteUtil::writeUINT8(data, byHide)
		return @svrHandler.sendPacket(data)
	end

	#发送：选择时装
	def send_FashionChange(
		qwInstID #(UINT64)时装唯一ID
	)
		sessionID = @sessionMgr.getNewSession(self, 26);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 27
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		return @svrHandler.sendPacket(data)
	end

	#发送：时装炼化
	def send_FashionUpgrade(
		qwInstID,  #(UINT64)时装物品ID
		byOneKey #(UINT8)是否一键
	)
		sessionID = @sessionMgr.getNewSession(self, 27);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 28
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwInstID)
		ByteUtil::writeUINT8(data, byOneKey)
		return @svrHandler.sendPacket(data)
	end

	#发送：穿戴宝石
	def send_WareGemStone(
		wItemID,  #(UINT16)宝石模板ID
		qwFighterID,  #(UINT64)将ID
		byPos #(UINT8)穿戴位置
	)
		sessionID = @sessionMgr.getNewSession(self, 28);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 29
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wItemID)
		ByteUtil::writeUINT64(data, qwFighterID)
		ByteUtil::writeUINT8(data, byPos)
		return @svrHandler.sendPacket(data)
	end

	#发送：取下宝石
	def send_TakeOffGemStone(
		qwFighterID,  #(UINT64)将ID
		byPos #(UINT8)穿戴位置0~5,6表示全部卸下
	)
		sessionID = @sessionMgr.getNewSession(self, 29);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 30
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwFighterID)
		ByteUtil::writeUINT8(data, byPos)
		return @svrHandler.sendPacket(data)
	end

	#发送：合成宝石
	def send_ComposeGemStone(
		wItemID,  #(UINT16)宝石模板ID
		dwNum #(UINT32)合成数量
	)
		sessionID = @sessionMgr.getNewSession(self, 30);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 31
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wItemID)
		ByteUtil::writeUINT32(data, dwNum)
		return @svrHandler.sendPacket(data)
	end

	#发送：一键合成宝石
	def send_ComposeGemStoneOneKey(
		vecStone #(SGMMailItem的数组)合成宝石列表
	)
		sessionID = @sessionMgr.getNewSession(self, 31);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 32
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		SGMMailItem::vectorToStream(data, vecStone)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：包裹或仓库道具通知
	def onRecv_StoreNotify(
		eStoreType, #(枚举类型：EStoreType)存储类型
		wStoreSize, #(UINT16)包裹或仓库的容量
		vecStoreItem #(SItem的数组)包裹或仓库中道具的列表
	)
		raise NotImplementedError
	end
	#接收：解锁格子还需要多少时间
	def onRecv_PackNextUnlockTime(
		dwTime #(UINT32)时间，单位秒
	)
		raise NotImplementedError
	end
	#接收：包裹或仓库容量改变通知
	def onRecv_StoreSizeChangeNotify(
		eStoreType, #(枚举类型：EStoreType)存储类型
		wStoreSize #(UINT16)包裹或仓库的容量
	)
		raise NotImplementedError
	end
	#接收：当前玩家的包裹或仓库中道具增加通知
	def onRecv_StoreItemAddNtf(
		eStoreType, #(枚举类型：EStoreType)存储类型
		vecStoreItem, #(SItem的数组)包裹或仓库中道具的列表
		bNew #(bool)是否新获得道具
	)
		raise NotImplementedError
	end
	#接收：当前玩家的包裹或仓库中道具删除通知
	def onRecv_StoreItemDelNtf(
		eStoreType, #(枚举类型：EStoreType)存储类型
		vecInstID #(UINT64数组)道具的实例ID列表
	)
		raise NotImplementedError
	end
	#接收：堆叠道具数量刷新通知
	def onRecv_StackItemUpdate(
		eStoreType, #(枚举类型：EStoreType)存储类型
		qwRoleID, #(UINT64)角色ID
		qwInstID, #(UINT64)堆叠道具的实例ID
		wStack #(UINT16)当前堆叠数
	)
		raise NotImplementedError
	end
	#接收：打开包裹或仓库
	def onRecv_OpenDepot(
		eStoreType #(枚举类型：EStoreType)存储类型
	)
		raise NotImplementedError
	end
	#接收：道具绑定改变通知
	def onRecv_ItemBindChangeNtf(
		eStoreType, #(枚举类型：EStoreType)存储类型
		qwInstID, #(UINT64)道具的实例ID
		eBindType, #(枚举类型：EBindType)道具的绑定类型
		bBind #(bool)道具是否绑定
	)
		raise NotImplementedError
	end
	#接收：道具CD时间通知
	def onRecv_ItemCDNtf(
		byType, #(UINT8)冷却类型0:ItemID 1:GroupID
		rItemCD #(类类型：SItemColdTime)道具CD
	)
		raise NotImplementedError
	end
	#接收：道具的到期时间通知
	def onRecv_ItemExpireTimeNtf(
		qwInstID, #(UINT64)道具的实例ID
		dwExpireTime #(UINT32)到期时间(1970年1月1日0时开始的秒数)
	)
		raise NotImplementedError
	end
	#接收：道具(装备)属性变化通知
	def onRecv_ItemChangeNotify(
		eStoreType, #(枚举类型：EStoreType)存储类型
		qwOwnerID, #(UINT64)所有者ID(可能是主将，副将，宠物...)
		rStoreItem #(类类型：SItem)装备更新后信息
	)
		raise NotImplementedError
	end
	#接收：清除道具使用冷却CD
	def onRecv_ClearAllItemCDNtf(
	)
		raise NotImplementedError
	end
	#接收：角色道具冷却通知
	def onRecv_SlotItemCDNotify(
		vecItemCold, #(SItemColdTime的数组)道具使用冷却时间
		vecGroupCold #(SItemColdTime的数组)道具公共冷却时间
	)
		raise NotImplementedError
	end
	#接收：角色获得道具提示
	def onRecv_AddItemSystemMsg(
		vecAddItemMsg #(SAddItemMsg的数组)道具获得提示
	)
		raise NotImplementedError
	end
	#接收：错误提示
	def onRecv_ItemErrNfg(
		eResult #(枚举类型：EItemResult)提示
	)
		raise NotImplementedError
	end
	#接收：再一次增加记录道具通知
	def onRecv_AgainAddloggedItemNotify(
		rVecLoggedItem #(SLoggedItem的数组)道具列表
	)
		raise NotImplementedError
	end
	#接收：增加记录道具通知
	def onRecv_AddLoggedItemNotify(
		rVecLoggedItem #(SLoggedItem的数组)道具列表
	)
		raise NotImplementedError
	end
	#接收：更新记录的堆叠道具通知
	def onRecv_UpdateLoggedStackItemNotify(
		wItemID, #(UINT16)ID
		byQuality, #(UINT8)品质
		dwCount #(UINT32)数目
	)
		raise NotImplementedError
	end
	#接收：当前玩家制造或者分解心法，包裹或仓库中道具增加通知
	def onRecv_CittaAddNtf(
		eStoreType, #(枚举类型：EStoreType)存储类型
		vecStoreItem, #(SItem的数组)包裹或仓库中道具的列表
		bNew #(bool)是否新获得道具
	)
		raise NotImplementedError
	end
	#接收：更新记录的堆叠道具通知
	def onRecv_NoticeUseItemNotify(
		wItemID, #(UINT16)ID
		dwNum, #(UINT32)使用物品数量
		vecRes, #(SResource的数组)资源
		vecItem #(SItemGenInfo的数组)物品
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：请求包裹信息(整个包裹)
	def onReturn_GetStore(
		ret, #0为成功，1为失败，2为超时
		origParam, #(类类型：SOrigParam_GetStore)原来的参数
		retParam #(类类型：SRetParam_GetStore)返回的参数
	)
	end

	#返回：请求使用包裹中的道具
	def onReturn_UseItem(
		ret, #0为成功，1为失败，2为超时
		origParam, #(类类型：SOrigParam_UseItem)原来的参数
		retParam #(类类型：SRetParam_UseItem)返回的参数
	)
	end

	#返回：扩充包裹或仓库
	def onReturn_ExpandStore(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ExpandStore)返回的参数
	)
	end

	#返回：包裹或仓库中道具换位置
	def onReturn_RelocateStoreItem(
		ret, #0为成功，1为失败，2为超时
		origParam, #(类类型：SOrigParam_RelocateStoreItem)原来的参数
		retParam #(类类型：SRetParam_RelocateStoreItem)返回的参数
	)
	end

	#返回：整理包裹或仓库
	def onReturn_TidyupStore(
		ret, #0为成功，1为失败，2为超时
		origParam, #(类类型：SOrigParam_TidyupStore)原来的参数
		retParam #(类类型：SRetParam_TidyupStore)返回的参数
	)
	end

	#返回：拆分包裹或仓库中的堆叠类道具
	def onReturn_SplitStackItem(
		ret, #0为成功，1为失败，2为超时
		origParam, #(类类型：SOrigParam_SplitStackItem)原来的参数
		retParam #(类类型：SRetParam_SplitStackItem)返回的参数
	)
	end

	#返回：合并包裹或仓库中的堆叠类道具
	def onReturn_MergeStackItem(
		ret, #0为成功，1为失败，2为超时
		origParam, #(类类型：SOrigParam_MergeStackItem)原来的参数
		retParam #(类类型：SRetParam_MergeStackItem)返回的参数
	)
	end

	#返回：销毁包裹或仓库中的道具
	def onReturn_DestroyStoreItem(
		ret, #0为成功，1为失败，2为超时
		origParam, #(类类型：SOrigParam_DestroyStoreItem)原来的参数
		retParam #(类类型：SRetParam_DestroyStoreItem)返回的参数
	)
	end

	#返回：在包裹和仓库之间移动道具
	def onReturn_TransferItem(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TransferItem)返回的参数
	)
	end

	#返回：请求出售包裹中的道具-出售给系统
	def onReturn_SellItem(
		ret, #0为成功，1为失败，2为超时
		origParam, #(类类型：SOrigParam_SellItem)原来的参数
		retParam #(类类型：SRetParam_SellItem)返回的参数
	)
	end

	#返回：请求按个数出售包裹中的道具-出售给系统
	def onReturn_SellItemWithCount(
		ret, #0为成功，1为失败，2为超时
		origParam, #(类类型：SOrigParam_SellItemWithCount)原来的参数
		retParam #(类类型：SRetParam_SellItemWithCount)返回的参数
	)
	end

	#返回：解锁背包格子
	def onReturn_UnlockPack(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UnlockPack)返回的参数
	)
	end

	#返回：记录传送点
	def onReturn_RecordTransfPoint(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_RecordTransfPoint)返回的参数
	)
	end

	#返回：传送
	def onReturn_TransfMapPoint(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TransfMapPoint)返回的参数
	)
	end

	#返回：请求装备心法
	def onReturn_WearCitta(
		ret, #0为成功，1为失败，2为超时
		origParam, #(类类型：SOrigParam_WearCitta)原来的参数
		retParam #(类类型：SRetParam_WearCitta)返回的参数
	)
	end

	#返回：请求卸下心法
	def onReturn_TakeoffCitta(
		ret, #0为成功，1为失败，2为超时
		origParam, #(类类型：SOrigParam_TakeoffCitta)原来的参数
		retParam #(类类型：SRetParam_TakeoffCitta)返回的参数
	)
	end

	#返回：请求合成心法
	def onReturn_MergeCitta(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_MergeCitta)返回的参数
	)
	end

	#返回：请求分解心法
	def onReturn_BreakCitta(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_BreakCitta)返回的参数
	)
	end

	#返回：激活法宝
	def onReturn_ActiveTrump(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ActiveTrump)返回的参数
	)
	end

	#返回：出战法宝
	def onReturn_EquipTrump(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_EquipTrump)返回的参数
	)
	end

	#返回：卸下法宝
	def onReturn_UnEquipTrump(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UnEquipTrump)返回的参数
	)
	end

	#返回：祭炼法宝
	def onReturn_UpgradeTrump(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UpgradeTrump)返回的参数
	)
	end

	#返回：提升法宝品级
	def onReturn_EvolveTrump(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_EvolveTrump)返回的参数
	)
	end

	#返回：激活时装
	def onReturn_FashionActive(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FashionActive)返回的参数
	)
	end

	#返回：隐藏所选时装
	def onReturn_FashionHide(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FashionHide)返回的参数
	)
	end

	#返回：选择时装
	def onReturn_FashionChange(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FashionChange)返回的参数
	)
	end

	#返回：时装炼化
	def onReturn_FashionUpgrade(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FashionUpgrade)返回的参数
	)
	end

	#返回：穿戴宝石
	def onReturn_WareGemStone(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_WareGemStone)返回的参数
	)
	end

	#返回：取下宝石
	def onReturn_TakeOffGemStone(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_TakeOffGemStone)返回的参数
	)
	end

	#返回：合成宝石
	def onReturn_ComposeGemStone(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ComposeGemStone)返回的参数
	)
	end

	#返回：一键合成宝石
	def onReturn_ComposeGemStoneOneKey(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ComposeGemStoneOneKey)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：包裹或仓库道具通知
	def _doRecv_StoreNotify(data)
		eStoreType = ByteUtil::readUINT8(data)
		wStoreSize = ByteUtil::readUINT16(data)
		vecStoreItem = SItem::superVectorFromStream(data)
		return onRecv_StoreNotify(eStoreType, wStoreSize, vecStoreItem)
	end

	#接收处理：解锁格子还需要多少时间
	def _doRecv_PackNextUnlockTime(data)
		dwTime = ByteUtil::readUINT32(data)
		return onRecv_PackNextUnlockTime(dwTime)
	end

	#接收处理：包裹或仓库容量改变通知
	def _doRecv_StoreSizeChangeNotify(data)
		eStoreType = ByteUtil::readUINT8(data)
		wStoreSize = ByteUtil::readUINT16(data)
		return onRecv_StoreSizeChangeNotify(eStoreType, wStoreSize)
	end

	#接收处理：当前玩家的包裹或仓库中道具增加通知
	def _doRecv_StoreItemAddNtf(data)
		eStoreType = ByteUtil::readUINT8(data)
		vecStoreItem = SItem::superVectorFromStream(data)
		bNew = ByteUtil::readBOOL(data)
		return onRecv_StoreItemAddNtf(eStoreType, vecStoreItem, bNew)
	end

	#接收处理：当前玩家的包裹或仓库中道具删除通知
	def _doRecv_StoreItemDelNtf(data)
		eStoreType = ByteUtil::readUINT8(data)
		vecInstID = ByteUtil::readVecUINT64(data)
		return onRecv_StoreItemDelNtf(eStoreType, vecInstID)
	end

	#接收处理：堆叠道具数量刷新通知
	def _doRecv_StackItemUpdate(data)
		eStoreType = ByteUtil::readUINT8(data)
		qwRoleID = ByteUtil::readUINT64(data)
		qwInstID = ByteUtil::readUINT64(data)
		wStack = ByteUtil::readUINT16(data)
		return onRecv_StackItemUpdate(eStoreType, qwRoleID, qwInstID, wStack)
	end

	#接收处理：打开包裹或仓库
	def _doRecv_OpenDepot(data)
		eStoreType = ByteUtil::readUINT8(data)
		return onRecv_OpenDepot(eStoreType)
	end

	#接收处理：道具绑定改变通知
	def _doRecv_ItemBindChangeNtf(data)
		eStoreType = ByteUtil::readUINT8(data)
		qwInstID = ByteUtil::readUINT64(data)
		eBindType = ByteUtil::readUINT8(data)
		bBind = ByteUtil::readBOOL(data)
		return onRecv_ItemBindChangeNtf(eStoreType, qwInstID, eBindType, bBind)
	end

	#接收处理：道具CD时间通知
	def _doRecv_ItemCDNtf(data)
		byType = ByteUtil::readUINT8(data)
		rItemCD = SItemColdTime::fromStream(data)
		return onRecv_ItemCDNtf(byType, rItemCD)
	end

	#接收处理：道具的到期时间通知
	def _doRecv_ItemExpireTimeNtf(data)
		qwInstID = ByteUtil::readUINT64(data)
		dwExpireTime = ByteUtil::readUINT32(data)
		return onRecv_ItemExpireTimeNtf(qwInstID, dwExpireTime)
	end

	#接收处理：道具(装备)属性变化通知
	def _doRecv_ItemChangeNotify(data)
		eStoreType = ByteUtil::readUINT8(data)
		qwOwnerID = ByteUtil::readUINT64(data)
		rStoreItem = SItem::superFromStream(data)
		return onRecv_ItemChangeNotify(eStoreType, qwOwnerID, rStoreItem)
	end

	#接收处理：清除道具使用冷却CD
	def _doRecv_ClearAllItemCDNtf(data)
		return onRecv_ClearAllItemCDNtf()
	end

	#接收处理：角色道具冷却通知
	def _doRecv_SlotItemCDNotify(data)
		vecItemCold = SItemColdTime::vectorFromStream(data)
		vecGroupCold = SItemColdTime::vectorFromStream(data)
		return onRecv_SlotItemCDNotify(vecItemCold, vecGroupCold)
	end

	#接收处理：角色获得道具提示
	def _doRecv_AddItemSystemMsg(data)
		vecAddItemMsg = SAddItemMsg::vectorFromStream(data)
		return onRecv_AddItemSystemMsg(vecAddItemMsg)
	end

	#接收处理：错误提示
	def _doRecv_ItemErrNfg(data)
		eResult = ByteUtil::readUINT8(data)
		return onRecv_ItemErrNfg(eResult)
	end

	#接收处理：再一次增加记录道具通知
	def _doRecv_AgainAddloggedItemNotify(data)
		rVecLoggedItem = SLoggedItem::vectorFromStream(data)
		return onRecv_AgainAddloggedItemNotify(rVecLoggedItem)
	end

	#接收处理：增加记录道具通知
	def _doRecv_AddLoggedItemNotify(data)
		rVecLoggedItem = SLoggedItem::vectorFromStream(data)
		return onRecv_AddLoggedItemNotify(rVecLoggedItem)
	end

	#接收处理：更新记录的堆叠道具通知
	def _doRecv_UpdateLoggedStackItemNotify(data)
		wItemID = ByteUtil::readUINT16(data)
		byQuality = ByteUtil::readUINT8(data)
		dwCount = ByteUtil::readUINT32(data)
		return onRecv_UpdateLoggedStackItemNotify(wItemID, byQuality, dwCount)
	end

	#接收处理：当前玩家制造或者分解心法，包裹或仓库中道具增加通知
	def _doRecv_CittaAddNtf(data)
		eStoreType = ByteUtil::readUINT8(data)
		vecStoreItem = SItem::superVectorFromStream(data)
		bNew = ByteUtil::readBOOL(data)
		return onRecv_CittaAddNtf(eStoreType, vecStoreItem, bNew)
	end

	#接收处理：更新记录的堆叠道具通知
	def _doRecv_NoticeUseItemNotify(data)
		wItemID = ByteUtil::readUINT16(data)
		dwNum = ByteUtil::readUINT32(data)
		vecRes = SResource::vectorFromStream(data)
		vecItem = SItemGenInfo::vectorFromStream(data)
		return onRecv_NoticeUseItemNotify(wItemID, dwNum, vecRes, vecItem)
	end

#以下为返回处理函数
	#返回处理：请求包裹信息(整个包裹)
	def _doReturn_GetStore(data)
		retParam = SRetParam_GetStore.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		stStoreStream = SStoreStream::fromStream(data) #(类类型：SStoreStream)背包信息
		dwNextUnlockTime = ByteUtil::readUINT32(data) #(UINT32)下一个解锁背包空间的时间 0-表示可解锁 0xFFFFFFFF-表示没有可解锁的了 其他为秒
		retParam.stStoreStream = stStoreStream
		retParam.dwNextUnlockTime = dwNextUnlockTime
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_GetStore(ret, origParam, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求包裹信息(整个包裹)
	def _onTimeOut_GetStore(sessionID)
		retParam = SRetParam_GetStore.new;
		origParam = @sessionMgr.getData(sessionID)
		onReturn_GetStore(2, origParam, retParam)
	end

	#返回处理：请求使用包裹中的道具
	def _doReturn_UseItem(data)
		retParam = SRetParam_UseItem.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EItemResult)使用道具结果
		retParam.eResult = eResult
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_UseItem(ret, origParam, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求使用包裹中的道具
	def _onTimeOut_UseItem(sessionID)
		retParam = SRetParam_UseItem.new;
		origParam = @sessionMgr.getData(sessionID)
		onReturn_UseItem(2, origParam, retParam)
	end

	#返回处理：扩充包裹或仓库
	def _doReturn_ExpandStore(data)
		retParam = SRetParam_ExpandStore.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EItemResult)扩充结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ExpandStore(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：扩充包裹或仓库
	def _onTimeOut_ExpandStore(sessionID)
		retParam = SRetParam_ExpandStore.new;
		onReturn_ExpandStore(2, retParam)
	end

	#返回处理：包裹或仓库中道具换位置
	def _doReturn_RelocateStoreItem(data)
		retParam = SRetParam_RelocateStoreItem.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EItemResult)换位置的结果
		retParam.eResult = eResult
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_RelocateStoreItem(ret, origParam, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：包裹或仓库中道具换位置
	def _onTimeOut_RelocateStoreItem(sessionID)
		retParam = SRetParam_RelocateStoreItem.new;
		origParam = @sessionMgr.getData(sessionID)
		onReturn_RelocateStoreItem(2, origParam, retParam)
	end

	#返回处理：整理包裹或仓库
	def _doReturn_TidyupStore(data)
		retParam = SRetParam_TidyupStore.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EItemResult)整理的结果
		retParam.eResult = eResult
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_TidyupStore(ret, origParam, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：整理包裹或仓库
	def _onTimeOut_TidyupStore(sessionID)
		retParam = SRetParam_TidyupStore.new;
		origParam = @sessionMgr.getData(sessionID)
		onReturn_TidyupStore(2, origParam, retParam)
	end

	#返回处理：拆分包裹或仓库中的堆叠类道具
	def _doReturn_SplitStackItem(data)
		retParam = SRetParam_SplitStackItem.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EItemResult)拆分的结果
		retParam.eResult = eResult
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_SplitStackItem(ret, origParam, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：拆分包裹或仓库中的堆叠类道具
	def _onTimeOut_SplitStackItem(sessionID)
		retParam = SRetParam_SplitStackItem.new;
		origParam = @sessionMgr.getData(sessionID)
		onReturn_SplitStackItem(2, origParam, retParam)
	end

	#返回处理：合并包裹或仓库中的堆叠类道具
	def _doReturn_MergeStackItem(data)
		retParam = SRetParam_MergeStackItem.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EItemResult)合并的结果
		retParam.eResult = eResult
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_MergeStackItem(ret, origParam, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：合并包裹或仓库中的堆叠类道具
	def _onTimeOut_MergeStackItem(sessionID)
		retParam = SRetParam_MergeStackItem.new;
		origParam = @sessionMgr.getData(sessionID)
		onReturn_MergeStackItem(2, origParam, retParam)
	end

	#返回处理：销毁包裹或仓库中的道具
	def _doReturn_DestroyStoreItem(data)
		retParam = SRetParam_DestroyStoreItem.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EItemResult)销毁的结果
		retParam.eResult = eResult
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_DestroyStoreItem(ret, origParam, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：销毁包裹或仓库中的道具
	def _onTimeOut_DestroyStoreItem(sessionID)
		retParam = SRetParam_DestroyStoreItem.new;
		origParam = @sessionMgr.getData(sessionID)
		onReturn_DestroyStoreItem(2, origParam, retParam)
	end

	#返回处理：在包裹和仓库之间移动道具
	def _doReturn_TransferItem(data)
		retParam = SRetParam_TransferItem.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EItemResult)移动的结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TransferItem(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：在包裹和仓库之间移动道具
	def _onTimeOut_TransferItem(sessionID)
		retParam = SRetParam_TransferItem.new;
		onReturn_TransferItem(2, retParam)
	end

	#返回处理：请求出售包裹中的道具-出售给系统
	def _doReturn_SellItem(data)
		retParam = SRetParam_SellItem.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EItemResult)使用道具结果
		retParam.eResult = eResult
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_SellItem(ret, origParam, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求出售包裹中的道具-出售给系统
	def _onTimeOut_SellItem(sessionID)
		retParam = SRetParam_SellItem.new;
		origParam = @sessionMgr.getData(sessionID)
		onReturn_SellItem(2, origParam, retParam)
	end

	#返回处理：请求按个数出售包裹中的道具-出售给系统
	def _doReturn_SellItemWithCount(data)
		retParam = SRetParam_SellItemWithCount.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EItemResult)卖出道具结果
		retParam.eResult = eResult
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_SellItemWithCount(ret, origParam, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求按个数出售包裹中的道具-出售给系统
	def _onTimeOut_SellItemWithCount(sessionID)
		retParam = SRetParam_SellItemWithCount.new;
		origParam = @sessionMgr.getData(sessionID)
		onReturn_SellItemWithCount(2, origParam, retParam)
	end

	#返回处理：解锁背包格子
	def _doReturn_UnlockPack(data)
		retParam = SRetParam_UnlockPack.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EItemResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UnlockPack(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：解锁背包格子
	def _onTimeOut_UnlockPack(sessionID)
		retParam = SRetParam_UnlockPack.new;
		onReturn_UnlockPack(2, retParam)
	end

	#返回处理：记录传送点
	def _doReturn_RecordTransfPoint(data)
		retParam = SRetParam_RecordTransfPoint.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EItemResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_RecordTransfPoint(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：记录传送点
	def _onTimeOut_RecordTransfPoint(sessionID)
		retParam = SRetParam_RecordTransfPoint.new;
		onReturn_RecordTransfPoint(2, retParam)
	end

	#返回处理：传送
	def _doReturn_TransfMapPoint(data)
		retParam = SRetParam_TransfMapPoint.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EItemResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TransfMapPoint(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：传送
	def _onTimeOut_TransfMapPoint(sessionID)
		retParam = SRetParam_TransfMapPoint.new;
		onReturn_TransfMapPoint(2, retParam)
	end

	#返回处理：请求装备心法
	def _doReturn_WearCitta(data)
		retParam = SRetParam_WearCitta.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ECittaResult)穿上装备的结果
		retParam.eResult = eResult
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_WearCitta(ret, origParam, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求装备心法
	def _onTimeOut_WearCitta(sessionID)
		retParam = SRetParam_WearCitta.new;
		origParam = @sessionMgr.getData(sessionID)
		onReturn_WearCitta(2, origParam, retParam)
	end

	#返回处理：请求卸下心法
	def _doReturn_TakeoffCitta(data)
		retParam = SRetParam_TakeoffCitta.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ECittaResult)脱下装备的结果
		retParam.eResult = eResult
		origParam = @sessionMgr.getData(sessionID)
		ret = 0
		if origParam == nil 
			ret = 3 #确认已超时但又收到返回
		elsif(!retVal)
			ret = 1
		end
		result = onReturn_TakeoffCitta(ret, origParam, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求卸下心法
	def _onTimeOut_TakeoffCitta(sessionID)
		retParam = SRetParam_TakeoffCitta.new;
		origParam = @sessionMgr.getData(sessionID)
		onReturn_TakeoffCitta(2, origParam, retParam)
	end

	#返回处理：请求合成心法
	def _doReturn_MergeCitta(data)
		retParam = SRetParam_MergeCitta.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ECittaResult)结果
		vecItemCitta = SItem::superVectorFromStream(data) #(SItem的数组)新增的道具
		retParam.eResult = eResult
		retParam.vecItemCitta = vecItemCitta
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_MergeCitta(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求合成心法
	def _onTimeOut_MergeCitta(sessionID)
		retParam = SRetParam_MergeCitta.new;
		onReturn_MergeCitta(2, retParam)
	end

	#返回处理：请求分解心法
	def _doReturn_BreakCitta(data)
		retParam = SRetParam_BreakCitta.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ECittaResult)结果
		vecItemInfo = SItemGenInfo::vectorFromStream(data) #(SItemGenInfo的数组)分解产生的道具
		retParam.eResult = eResult
		retParam.vecItemInfo = vecItemInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_BreakCitta(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求分解心法
	def _onTimeOut_BreakCitta(sessionID)
		retParam = SRetParam_BreakCitta.new;
		onReturn_BreakCitta(2, retParam)
	end

	#返回处理：激活法宝
	def _doReturn_ActiveTrump(data)
		retParam = SRetParam_ActiveTrump.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETrumpResult)结果
		vecTrump = STrump::vectorFromStream(data) #(STrump的数组)新法宝
		retParam.eResult = eResult
		retParam.vecTrump = vecTrump
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ActiveTrump(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：激活法宝
	def _onTimeOut_ActiveTrump(sessionID)
		retParam = SRetParam_ActiveTrump.new;
		onReturn_ActiveTrump(2, retParam)
	end

	#返回处理：出战法宝
	def _doReturn_EquipTrump(data)
		retParam = SRetParam_EquipTrump.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETrumpResult)结果
		vecTrump = STrump::vectorFromStream(data) #(STrump的数组)新法宝
		retParam.eResult = eResult
		retParam.vecTrump = vecTrump
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_EquipTrump(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：出战法宝
	def _onTimeOut_EquipTrump(sessionID)
		retParam = SRetParam_EquipTrump.new;
		onReturn_EquipTrump(2, retParam)
	end

	#返回处理：卸下法宝
	def _doReturn_UnEquipTrump(data)
		retParam = SRetParam_UnEquipTrump.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETrumpResult)结果
		vecTrump = STrump::vectorFromStream(data) #(STrump的数组)新法宝
		retParam.eResult = eResult
		retParam.vecTrump = vecTrump
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UnEquipTrump(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：卸下法宝
	def _onTimeOut_UnEquipTrump(sessionID)
		retParam = SRetParam_UnEquipTrump.new;
		onReturn_UnEquipTrump(2, retParam)
	end

	#返回处理：祭炼法宝
	def _doReturn_UpgradeTrump(data)
		retParam = SRetParam_UpgradeTrump.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETrumpResult)结果
		vecTrump = STrump::vectorFromStream(data) #(STrump的数组)新法宝
		retParam.eResult = eResult
		retParam.vecTrump = vecTrump
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UpgradeTrump(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：祭炼法宝
	def _onTimeOut_UpgradeTrump(sessionID)
		retParam = SRetParam_UpgradeTrump.new;
		onReturn_UpgradeTrump(2, retParam)
	end

	#返回处理：提升法宝品级
	def _doReturn_EvolveTrump(data)
		retParam = SRetParam_EvolveTrump.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETrumpResult)结果
		vecTrump = STrump::vectorFromStream(data) #(STrump的数组)新法宝
		retParam.eResult = eResult
		retParam.vecTrump = vecTrump
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_EvolveTrump(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：提升法宝品级
	def _onTimeOut_EvolveTrump(sessionID)
		retParam = SRetParam_EvolveTrump.new;
		onReturn_EvolveTrump(2, retParam)
	end

	#返回处理：激活时装
	def _doReturn_FashionActive(data)
		retParam = SRetParam_FashionActive.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EFashionResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FashionActive(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：激活时装
	def _onTimeOut_FashionActive(sessionID)
		retParam = SRetParam_FashionActive.new;
		onReturn_FashionActive(2, retParam)
	end

	#返回处理：隐藏所选时装
	def _doReturn_FashionHide(data)
		retParam = SRetParam_FashionHide.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EFashionResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FashionHide(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：隐藏所选时装
	def _onTimeOut_FashionHide(sessionID)
		retParam = SRetParam_FashionHide.new;
		onReturn_FashionHide(2, retParam)
	end

	#返回处理：选择时装
	def _doReturn_FashionChange(data)
		retParam = SRetParam_FashionChange.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EFashionResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FashionChange(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：选择时装
	def _onTimeOut_FashionChange(sessionID)
		retParam = SRetParam_FashionChange.new;
		onReturn_FashionChange(2, retParam)
	end

	#返回处理：时装炼化
	def _doReturn_FashionUpgrade(data)
		retParam = SRetParam_FashionUpgrade.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EFashionResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FashionUpgrade(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：时装炼化
	def _onTimeOut_FashionUpgrade(sessionID)
		retParam = SRetParam_FashionUpgrade.new;
		onReturn_FashionUpgrade(2, retParam)
	end

	#返回处理：穿戴宝石
	def _doReturn_WareGemStone(data)
		retParam = SRetParam_WareGemStone.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGemstoneResult)结果
		qwFighterID = ByteUtil::readUINT64(data) #(UINT64)将ID
		byPos = ByteUtil::readUINT8(data) #(UINT8)穿戴位置
		Item = SGemstone::fromStream(data) #(类类型：SGemstone)宝石
		retParam.eResult = eResult
		retParam.qwFighterID = qwFighterID
		retParam.byPos = byPos
		retParam.Item = Item
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_WareGemStone(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：穿戴宝石
	def _onTimeOut_WareGemStone(sessionID)
		retParam = SRetParam_WareGemStone.new;
		onReturn_WareGemStone(2, retParam)
	end

	#返回处理：取下宝石
	def _doReturn_TakeOffGemStone(data)
		retParam = SRetParam_TakeOffGemStone.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGemstoneResult)结果
		qwFighterID = ByteUtil::readUINT64(data) #(UINT64)将ID
		byPos = ByteUtil::readUINT8(data) #(UINT8)穿戴位置
		retParam.eResult = eResult
		retParam.qwFighterID = qwFighterID
		retParam.byPos = byPos
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_TakeOffGemStone(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：取下宝石
	def _onTimeOut_TakeOffGemStone(sessionID)
		retParam = SRetParam_TakeOffGemStone.new;
		onReturn_TakeOffGemStone(2, retParam)
	end

	#返回处理：合成宝石
	def _doReturn_ComposeGemStone(data)
		retParam = SRetParam_ComposeGemStone.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGemstoneResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ComposeGemStone(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：合成宝石
	def _onTimeOut_ComposeGemStone(sessionID)
		retParam = SRetParam_ComposeGemStone.new;
		onReturn_ComposeGemStone(2, retParam)
	end

	#返回处理：一键合成宝石
	def _doReturn_ComposeGemStoneOneKey(data)
		retParam = SRetParam_ComposeGemStoneOneKey.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGemstoneResult)结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ComposeGemStoneOneKey(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：一键合成宝石
	def _onTimeOut_ComposeGemStoneOneKey(sessionID)
		retParam = SRetParam_ComposeGemStoneOneKey.new;
		onReturn_ComposeGemStoneOneKey(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 18;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_StoreNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_PackNextUnlockTime' #FuncID: 2
		@recvFuncList[2] = '_doRecv_StoreSizeChangeNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_StoreItemAddNtf' #FuncID: 4
		@recvFuncList[4] = '_doRecv_StoreItemDelNtf' #FuncID: 5
		@recvFuncList[5] = '_doRecv_StackItemUpdate' #FuncID: 6
		@recvFuncList[6] = '_doRecv_OpenDepot' #FuncID: 7
		@recvFuncList[7] = '_doRecv_ItemBindChangeNtf' #FuncID: 8
		@recvFuncList[8] = '_doRecv_ItemCDNtf' #FuncID: 9
		@recvFuncList[9] = '_doRecv_ItemExpireTimeNtf' #FuncID: 10
		@recvFuncList[10] = '_doRecv_ItemChangeNotify' #FuncID: 11
		@recvFuncList[11] = '_doRecv_ClearAllItemCDNtf' #FuncID: 12
		@recvFuncList[12] = '_doRecv_SlotItemCDNotify' #FuncID: 13
		@recvFuncList[13] = '_doRecv_AddItemSystemMsg' #FuncID: 14
		@recvFuncList[14] = '_doRecv_ItemErrNfg' #FuncID: 15
		@recvFuncList[15] = '_doRecv_AgainAddloggedItemNotify' #FuncID: 16
		@recvFuncList[16] = '_doRecv_AddLoggedItemNotify' #FuncID: 17
		@recvFuncList[17] = '_doRecv_UpdateLoggedStackItemNotify' #FuncID: 18
		@recvFuncList[18] = '_doRecv_CittaAddNtf' #FuncID: 19
		@recvFuncList[19] = '_doRecv_NoticeUseItemNotify' #FuncID: 20

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetStore' #FuncID: 1
		@retFuncList[1] = '_doReturn_UseItem' #FuncID: 2
		@retFuncList[2] = '_doReturn_ExpandStore' #FuncID: 3
		@retFuncList[3] = '_doReturn_RelocateStoreItem' #FuncID: 4
		@retFuncList[4] = '_doReturn_TidyupStore' #FuncID: 5
		@retFuncList[5] = '_doReturn_SplitStackItem' #FuncID: 6
		@retFuncList[6] = '_doReturn_MergeStackItem' #FuncID: 7
		@retFuncList[7] = '_doReturn_DestroyStoreItem' #FuncID: 8
		@retFuncList[8] = '_doReturn_TransferItem' #FuncID: 9
		@retFuncList[9] = '_doReturn_SellItem' #FuncID: 10
		@retFuncList[10] = '_doReturn_SellItemWithCount' #FuncID: 11
		@retFuncList[11] = '_doReturn_UnlockPack' #FuncID: 12
		@retFuncList[12] = '_doReturn_RecordTransfPoint' #FuncID: 13
		@retFuncList[13] = '_doReturn_TransfMapPoint' #FuncID: 14
		@retFuncList[14] = '_doReturn_WearCitta' #FuncID: 15
		@retFuncList[15] = '_doReturn_TakeoffCitta' #FuncID: 16
		@retFuncList[16] = '_doReturn_MergeCitta' #FuncID: 17
		@retFuncList[17] = '_doReturn_BreakCitta' #FuncID: 18
		@retFuncList[18] = '_doReturn_ActiveTrump' #FuncID: 19
		@retFuncList[19] = '_doReturn_EquipTrump' #FuncID: 20
		@retFuncList[20] = '_doReturn_UnEquipTrump' #FuncID: 21
		@retFuncList[21] = '_doReturn_UpgradeTrump' #FuncID: 22
		@retFuncList[22] = '_doReturn_EvolveTrump' #FuncID: 23
		@retFuncList[23] = '_doReturn_FashionActive' #FuncID: 24
		@retFuncList[24] = '_doReturn_FashionHide' #FuncID: 25
		@retFuncList[25] = '_doReturn_FashionChange' #FuncID: 26
		@retFuncList[26] = '_doReturn_FashionUpgrade' #FuncID: 27
		@retFuncList[27] = '_doReturn_WareGemStone' #FuncID: 28
		@retFuncList[28] = '_doReturn_TakeOffGemStone' #FuncID: 29
		@retFuncList[29] = '_doReturn_ComposeGemStone' #FuncID: 30
		@retFuncList[30] = '_doReturn_ComposeGemStoneOneKey' #FuncID: 31

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetStore' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_UseItem' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_ExpandStore' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_RelocateStoreItem' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_TidyupStore' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_SplitStackItem' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_MergeStackItem' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_DestroyStoreItem' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_TransferItem' #FuncID: 9
		@timeFuncList[9] = '_onTimeOut_SellItem' #FuncID: 10
		@timeFuncList[10] = '_onTimeOut_SellItemWithCount' #FuncID: 11
		@timeFuncList[11] = '_onTimeOut_UnlockPack' #FuncID: 12
		@timeFuncList[12] = '_onTimeOut_RecordTransfPoint' #FuncID: 13
		@timeFuncList[13] = '_onTimeOut_TransfMapPoint' #FuncID: 14
		@timeFuncList[14] = '_onTimeOut_WearCitta' #FuncID: 15
		@timeFuncList[15] = '_onTimeOut_TakeoffCitta' #FuncID: 16
		@timeFuncList[16] = '_onTimeOut_MergeCitta' #FuncID: 17
		@timeFuncList[17] = '_onTimeOut_BreakCitta' #FuncID: 18
		@timeFuncList[18] = '_onTimeOut_ActiveTrump' #FuncID: 19
		@timeFuncList[19] = '_onTimeOut_EquipTrump' #FuncID: 20
		@timeFuncList[20] = '_onTimeOut_UnEquipTrump' #FuncID: 21
		@timeFuncList[21] = '_onTimeOut_UpgradeTrump' #FuncID: 22
		@timeFuncList[22] = '_onTimeOut_EvolveTrump' #FuncID: 23
		@timeFuncList[23] = '_onTimeOut_FashionActive' #FuncID: 24
		@timeFuncList[24] = '_onTimeOut_FashionHide' #FuncID: 25
		@timeFuncList[25] = '_onTimeOut_FashionChange' #FuncID: 26
		@timeFuncList[26] = '_onTimeOut_FashionUpgrade' #FuncID: 27
		@timeFuncList[27] = '_onTimeOut_WareGemStone' #FuncID: 28
		@timeFuncList[28] = '_onTimeOut_TakeOffGemStone' #FuncID: 29
		@timeFuncList[29] = '_onTimeOut_ComposeGemStone' #FuncID: 30
		@timeFuncList[30] = '_onTimeOut_ComposeGemStoneOneKey' #FuncID: 31
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

