#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    GuildProt.rb
#  Purpose:      帮派相关协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ProtoCommonBase.rb'

#以下为类型定义

#帮派数据类型
class EGuildDataType
	EGDTBASEINFO = 0#帮派基本数据
	EGDTUSER = 1#帮派成员信息
	EGDTAPPLYINFO = 2#帮派申请列表信息
	EGDTAUTHORITY = 3#帮派职位可选权限
	EGDTBUILDING = 4#帮派建筑
	EGDTSTATUE = 5#帮派神像
	EGDTLOG = 6#帮派日志
	EGDTLSSBLOG = 7#帮派灵山商店购买日志
	EGDTMAX = 8#最大值
	EGDTTECH = 9#帮派科技
end

#公共帮派数据类型
class EGuildPubDataType
	EGPDTLISTINFO = 0#帮派列表信息
	EGPDTBATTLEINFO = 1#帮派战相关数据
	EGPDTMAX = 2#帮派信息最大值
end

#帮派操作返回结果
class EGuildResult
	EGUILDSUCCESS = 0#操作成功
	EGUILDFAILED = 1#操作失败
	EGUILDNOTEXISTED = 2#不存在帮派
	EGUILDEXISTED = 3#存在帮派
	EGUILDLOADING = 4#加载中
	EGUILDTRYAGAIN = 5#没加载到（已经开始加载了）稍等一会再试
	EGUILDLACKOFMONEY = 6#帮贡不足
end

#获取帮派信息返回结果
class EGuildInfoResult
	EGUILDINOFSUCCESS = 0#操作成功
	EGUILDINOFFAILED = 1#操作失败
	EGUILDINOFNOGUILD = 2#没有帮派
end

#创建帮派返回结果
class ECreateResult
	EGCREATESUCCESS = 0#操作成功
	EGCREATEFAILED = 1#操作失败
	EGCREATEINGUILD = 2#已经在帮派中
	EGCREATELACKOFGOLD = 3#银币不足
	EGCREATELACKOFLEVEL = 4#等级不足
	EGCREATENAMETOOSHORT = 5#名称太短
	EGCREATENAMETOOLONG = 6#名称太长
	EGCREATENAMEINVALID = 7#名称非法
	EGCREATENAMEEXISTED = 8#名称存在
	EGCREATEEXISTED = 9#帮派存在
	EGCREATELACKOFVIP = 10#御剑等级不足
end

#退出帮派返回结果
class EQuitResult
	EGQUITSUCCESS = 0#操作成功
	EGQUITFAILED = 1#操作失败
	EGQUITNOGUILD = 2#不在帮派中
	EGQUITOWNERQUIT = 3#帮主不能退出帮派
	EGQUITGUILDBATTLE = 4#帮派战期间无法执行此操作
end

#申请帮派返回结果
class EApplyResult
	EGAPPLYSUCCESS = 0#操作成功
	EGAPPLYFAILED = 1#操作失败
	EGAPPLYGUILDFULL = 2#帮派成员已满
	EGAPPLYOTHERGUILD = 3#已加入其他帮派
	EGAPPLYINGUILD = 4#已在帮派中
	EGAPPLYLISTFULL = 5#申请列表已满
	EGAPPLYNOAUTHORITY = 6#权限不足
	EGAPPLYNOGUILD = 7#没有帮派
	EGAPPLYNOUSER = 8#不存在的用户
	EGAPPLYNOTONLINE = 9#玩家不在线
	EGAPPLYALREADYAPPLYED = 10#您已经发送过该申请
	EGAPPLYLEVELLOW = 11#等级过低
	EGAPPLYNOSELF = 12#不能邀请自己
	EGAPPLYGUILDBATTLE = 13#帮派战期间无法执行此操作
end

#编辑公告返回结果
class EEditInfoResult
	EGEDITINFOSUCCESS = 0#操作成功
	EGEDITINFOFAILED = 1#操作失败
	EGEDITINFONOTINGUILD = 2#不在帮派中
	EGEDITINFONOAUTHORITY = 3#权限不足
	EGEDITINFOTOOLONG = 4#信息过长
end

#设置权限返回结果
class ESetAuthorityResult
	EGSETAUTHORITYSUCCESS = 0#操作成功
	EGSETAUTHORITYFAILED = 1#操作失败
	EGSETAUTHORITYNOTINGUILD = 2#不在帮派中
	EGSETAUTHORITYNOAUTHORITY = 3#权限不足
	EGSETAUTHORITYTOOHIGH = 4#只能提升至比自己低的职位
	EGSETAUTHORITYNOSELFRANK = 5#不能改变自身权限
end

#帮派成员操作类型
class EMemberOperateType
	EGMOPTYPENONE = 0#无效操作
	EGMOPTYPEUP = 1#提升职位
	EGMOPTYPEKICK = 2#踢出帮派
	EGMOPTYPEGIVEOWNER = 3#移交帮主
	EGMOPTYPEDOWN = 4#降低职位
	EGMOPTYPEFIRE = 5#免除职位
	EGMOPTYPEMAX = 6#最大操作
end

#帮派成员操作返回结果
class EMemberOperateResult
	EGMOPRESULTSUCCESS = 0#操作成功
	EGMOPRESULTFAILED = 1#操作失败
	EGMOPRESULTSELF = 2#不能对自己操作
	EGMOPRESULTNOTINGUILD = 3#不在帮派中
	EGMOPRESULTNOAUTHORITY = 4#权限不足
	EGMOPRESULTTOOHIGH = 5#只能提升至比自己低的职位
	EGMOPRESULTTOOLOW = 6#目标成员职位过低
	EGMOPRESULTTOOMANY = 7#目标职位成员数过多
	EGMOPRESULTHAVEIMPEACH = 8#弹劾发起者无法踢出
	EGMOPRESULTGUILDBATTLE = 9#帮派战期间无法执行此操作
end

#弹劾操作返回结果
class EImpeachResult
	EGIMPEACHRESULTSUCCESS = 0#操作成功
	EGIMPEACHRESULTFAILED = 1#操作失败
	EGIMPEACHRESULTSELF = 2#不能对自己操作
	EGIMPEACHRESULTNOTINGUILD = 3#不在帮派中
	EGIMPEACHRESULTWRONGGUILD = 4#不是该帮派
	EGIMPEACHRESULTNOAUTHORITY = 5#权限不足
	EGIMPEACHRESULTHASLAUNCHED = 6#已经存在弹劾
	EGIMPEACHRESULTHASREPLYED = 7#已经回应
	EGIMPEACHRESULTLACKOFGOLD = 8#仙石不足
end

#帮派职位
class EMemberRank
	EMEMBERNONE = 0#无效职位
	EMEMBERNORMAL = 1#成员
	EMEMBERELITE = 2#精英
	EMEMBERELDER = 3#长老
	EMEMBERVICEOWNER = 4#副帮主
	EMEMBEROWNER = 5#帮主
	EMEMBERMAX = 6#最高职位
end

#帮派建筑类型
class EBuildingType
	EBUILDINGNONE = 0#无效建筑
	EBUILDINGORACLE = 1#神谕塔
	EBUILDINGDEPOT = 2#仓库
	EBUILDINGSWORD = 3#剑阁
	EBUILDINGSTORE = 4#商店
	EBUILDINGBLOOD = 5#血池
	EBUILDINGMAX = 6#最高建筑
end

#帮派建筑操作返回结果
class EBuildingResult
	EGBUILDINGRESULTSUCCESS = 0#操作成功
	EGBUILDINGRESULTFAILED = 1#操作失败
	EGBUILDINGRESULTNOGUILD = 2#不存在帮派
	EGBUILDINGRESULTLACKOFSILVER = 3#银币不足
	EGBUILDINGRESULTLEVELMAX = 4#已经是最大等级
	EGBUILDINGRESULTNOAUTHORITY = 5#权限不足
	EGBUILDINGRESULTGUILDLEVELTOOLOW = 6#帮派等级过低
	EGBUILDINGRESULTORACLELEVELTOOLOW = 7#神谕塔等级过低
end

#帮派建筑类型
class ETechType
	ETECHNONE = 0#无效科技
	ETECHATTACK = 1#攻击之魂
	ETECHPHYDEF = 2#物防之魂
	ETECHMGCDEF = 3#魔防之魂
	ETECHHP = 4#生命之魂
	ETECHSPEED = 5#身法之魂
	ETECHHIT = 6#命中之魂
	ETECHDODGE = 7#闪避之魂
	ETECHCRITIAL = 8#暴击之魂
	ETECHANTICRITIAL = 9#稳固之魂
	ETECHPIERCE = 10#穿透之魂
	ETECHCOUNTER = 11#反击之魂
	ETECHRESIST = 12#压制之魂
	ETECHMAX = 13#最高科技
end

#帮派科技操作返回结果
class ETechResult
	EGTRESULTSUCCESS = 0#操作成功
	EGTRESULTFAILED = 1#操作失败
	EGTRESULTNOGUILD = 2#不存在帮派
	EGTRESULTLACKOFSILVER = 3#帮贡不足
	EGTRESULTLEVELMAX = 4#已经是最大等级
	EGTRESULTNOAUTHORITY = 5#权限不足
	EGTRESULTBUILDINGLEVELTOOLOW = 6#帮派建筑等级过低
	EGTRESULTUSERLEVELTOOLOW = 7#玩家等级过低
end

#帮派捐献操作返回结果
class EDonateResult
	EGDRESULTSUCCESS = 0#操作成功
	EGDRESULTFAILED = 1#操作失败
	EGDRESULTNOGUILD = 2#不存在帮派
	EGDRESULTLACKOFSILVER = 3#银币不足
	EGDRESULTNOAUTHORITY = 4#权限不足
	EGDRESULTFULL = 5#每日捐献已满
	EGDRESULTDEPOTFULL = 6#仓库已满
end

#帮派捐献操作返回结果
class EWorshipResult
	EGWRESULTSUCCESS = 0#操作成功
	EGWRESULTFAILED = 1#操作失败
	EGWRESULTNOGUILD = 2#不存在帮派
	EGWRESULTLACKOFSILVER = 3#银币不足
	EGWRESULTNOAUTHORITY = 4#权限不足
	EGWRESULTLEVELTOOLOW = 5#帮派等级过低
end

#日志类型
class ELogType
	ELOGNONE = 0#无效日志类型
	ELOGMEMBER = 1#成员日志
	ELOGDONATE = 2#捐献日志
	ELOGBUILDING = 3#建筑日志
	ELOGSTATUE = 4#神像日志
	ELOGMAX = 5#日志类型最大值
end

#捐献类型
class EWorshipType
	EWORSHIPNONE = 0#无效供奉类型
	EWORSHIPFLOWER = 1#鲜花供奉
	EWORSHIPREDFRUIT = 2#朱果供奉
	EWORSHIPPEACH = 3#蟠桃供奉
	EWORSHIPMAX = 4#供奉类型最大值
end

#帮派神像操作返回结果
class EStatueResult
	EGSRESULTSUCCESS = 0#操作成功
	EGSRESULTFAILED = 1#操作失败
	EGSRESULTNOGUILD = 2#不存在帮派
	EGSRESULTLACKOFSILVER = 3#银币不足
	EGSRESULTLACKOFGOLD = 4#仙石不足
	EGSRESULTLEVELMAX = 5#已经是最大等级
	EGSRESULTNOAUTHORITY = 6#权限不足
	EGSRESULTBUILDINGLEVELTOOLOW = 7#帮派建筑等级过低
	EGSRESULTWORSHIPED = 8#本日已经供奉过
	EGSRESULTTOOFAST = 9#操作过快
	EGSRESULTNOTTODAY = 10#进入当日无法操作
end

#羲和神车操作返回结果
class EGuildXiheResult
	EXIHERESULTSUCCESS = 0#操作成功
	EXIHERESULTFAILED = 1#操作失败
	EXIHERESULTNOGUILD = 2#不存在帮派
	EXIHERESULTUNFINISH = 3#货物未装满
	EXIHERESULTFINISH = 4#货物已装箱
	EXIHERESULTHASREQUEST = 5#货物已请求帮助
	EXIHERESULTNOTREQUEST = 6#货物未请求帮助
	EXIHERESULTNOTTRUCK = 7#不存在这个货物
	EXIHERESULTNOTITEM = 8#道具不足不能装货
	EXIHERESULTNOTGOLD = 9#仙石不足不能装货
	EXIHERESULTNOSAMEGUILD = 10#不是同一帮派
	EXIHERESULTFORHELPNUMMAX = 11#此次任务请求帮助次数已达上限
	EXIHERESULTNOTREQUESTLIMIT = 12#已装货物未达到4个不能请求帮助
end

#羲和神车任务阶段
class EXiheStage
	EXIHESTAGESHIPGOODS = 0#装货阶段
	EXIHESTAGETASKCOOL = 1#冷却阶段
	EXIHESTAGEWAITACESS = 2#等待玩家接取任务
end

#羲和神车任务完成状态
class EXiheTaskStatus
	EXIHETASKUNFINISH = 0#未完成装货也未请求帮助
	EXIHETASKREQUEST = 1#未完成装货已请求帮助
	EXIHETASKFINISHURE = 2#未请求帮助但已完成装货
	EXIHETASKFINISHRE = 3#已请求帮助但已完成装货
end

#帮派兑换错误码
class EGuildExchangeRet
	EGUILDEXCHANGE_FAILED = 0#失败
	EGUILDEXCHANGE_SUCESS = 1#成功
	EGUILDEXCHANGE_ERRORPACK = 2#背包满无法添加物品
	EGUILDEXCHANGE_MONEYLIMIT = 3#钱币不够
	EGUILDEXCHANGE_CONDLIMITA = 4#商品剩余数量为0
	EGUILDEXCHANGE_CONDLIMITB = 5#帮派成员每天购买次数达到上限
	EGUILDEXCHANGE_CONDLIMITC = 6#帮派所有成员每天购买次数达到上限
	EGUILDEXCHANGE_NOLINGSHAN = 7#要占领该据点才可兑换
end

#结构体：SGuildInfoBase的继承体系类型
class EType_SGuildInfoBase
	ETYPE_SGUILDINFOBASE = 0#类型：SGuildInfoBase
	ETYPE_SGUILDBASEINFO = 1#类型：SGuildBaseInfo
	ETYPE_SGUILDUSERINFO = 2#类型：SGuildUserInfo
	ETYPE_SGUILDAPPLYINFO = 3#类型：SGuildApplyInfo
	ETYPE_SGUILDBUILDINGINFO = 4#类型：SGuildBuildingInfo
	ETYPE_SGUILDAUTHORITYINFO = 5#类型：SGuildAuthorityInfo
	ETYPE_SGUILDTECHINFO = 6#类型：SGuildTechInfo
	ETYPE_SGUILDLOGINFO = 7#类型：SGuildLogInfo
	ETYPE_SGUILDSTATUEINFO = 8#类型：SGuildStatueInfo
end

#结构体：SGetGuildInfoBase的继承体系类型
class EType_SGetGuildInfoBase
	ETYPE_SGETGUILDINFOBASE = 0#类型：SGetGuildInfoBase
	ETYPE_SOTHERGUILDLISTINFO = 1#类型：SOtherGuildListInfo
	ETYPE_SSELFGUILDINFO = 2#类型：SSelfGuildInfo
end

#帮派信息基本类
class SGuildInfoBase
	attr_accessor:qwGuildID #(UINT64)帮派唯一ID

	#构造函数
	def initialize
		@qwGuildID = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SGuildInfoBase::ETYPE_SGUILDINFOBASE
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwGuildID = @qwGuildID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildInfoBase.new
		s.qwGuildID = ByteUtil::readUINT64(data)
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_SGuildInfoBase::ETYPE_SGUILDINFOBASE
				s = SGuildInfoBase::fromStream(data)
			when EType_SGuildInfoBase::ETYPE_SGUILDBASEINFO
				s = SGuildBaseInfo::fromStream(data)
			when EType_SGuildInfoBase::ETYPE_SGUILDUSERINFO
				s = SGuildUserInfo::fromStream(data)
			when EType_SGuildInfoBase::ETYPE_SGUILDAPPLYINFO
				s = SGuildApplyInfo::fromStream(data)
			when EType_SGuildInfoBase::ETYPE_SGUILDBUILDINGINFO
				s = SGuildBuildingInfo::fromStream(data)
			when EType_SGuildInfoBase::ETYPE_SGUILDAUTHORITYINFO
				s = SGuildAuthorityInfo::fromStream(data)
			when EType_SGuildInfoBase::ETYPE_SGUILDTECHINFO
				s = SGuildTechInfo::fromStream(data)
			when EType_SGuildInfoBase::ETYPE_SGUILDLOGINFO
				s = SGuildLogInfo::fromStream(data)
			when EType_SGuildInfoBase::ETYPE_SGUILDSTATUEINFO
				s = SGuildStatueInfo::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildInfoBase::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildInfoBase::superFromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwGuildID)
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

#帮派基本信息
class SGuildBaseInfo < SGuildInfoBase
	attr_accessor:strName #(string)帮派名称
	attr_accessor:qwOwnerID #(UINT64)帮主角色ID
	attr_accessor:strOwnerName #(string)帮主名称
	attr_accessor:strInfo #(string)帮派公告
	attr_accessor:qwQQGroupID #(UINT64)帮派Q群群号
	attr_accessor:wUserCount #(UINT16)成员数量
	attr_accessor:wMaxUserCount #(UINT16)最大成员数量
	attr_accessor:dwMoney #(UINT32)帮派资金
	attr_accessor:eSelfRank #(枚举类型：EMemberRank)本人职位
	attr_accessor:dwContribution #(UINT32)本人贡献值
	attr_accessor:dwRemainDonate #(UINT32)剩余捐献额
	attr_accessor:wPlayerFighterID #(UINT16)帮主ID
	attr_accessor:byQuality #(UINT8)帮主品质
	attr_accessor:dwScore #(UINT32)天元神兽积分
	attr_accessor:dwCount #(UINT32)帮派所有成员兑换物品数量
	attr_accessor:strLingShan #(string)占领灵山

	#构造函数
	def initialize
		super()
		@strName = ''
		@qwOwnerID = 0
		@strOwnerName = ''
		@strInfo = ''
		@qwQQGroupID = 0
		@wUserCount = 0
		@wMaxUserCount = 0
		@dwMoney = 0
		@eSelfRank = 0
		@dwContribution = 0
		@dwRemainDonate = 0
		@wPlayerFighterID = 0
		@byQuality = 0
		@dwScore = 0
		@dwCount = 0
		@strLingShan = ''
	end

	#获取继承类的类型
	def getClassType
		return EType_SGuildInfoBase::ETYPE_SGUILDBASEINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.strName = @strName
		obj.qwOwnerID = @qwOwnerID
		obj.strOwnerName = @strOwnerName
		obj.strInfo = @strInfo
		obj.qwQQGroupID = @qwQQGroupID
		obj.wUserCount = @wUserCount
		obj.wMaxUserCount = @wMaxUserCount
		obj.dwMoney = @dwMoney
		obj.eSelfRank = @eSelfRank
		obj.dwContribution = @dwContribution
		obj.dwRemainDonate = @dwRemainDonate
		obj.wPlayerFighterID = @wPlayerFighterID
		obj.byQuality = @byQuality
		obj.dwScore = @dwScore
		obj.dwCount = @dwCount
		obj.strLingShan = @strLingShan
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildBaseInfo.new
		base = SGuildInfoBase::fromStream(data)
		base.copyTo(s)
		s.strName = ByteUtil::readSTRING(data)
		s.qwOwnerID = ByteUtil::readUINT64(data)
		s.strOwnerName = ByteUtil::readSTRING(data)
		s.strInfo = ByteUtil::readSTRING(data)
		s.qwQQGroupID = ByteUtil::readUINT64(data)
		s.wUserCount = ByteUtil::readUINT16(data)
		s.wMaxUserCount = ByteUtil::readUINT16(data)
		s.dwMoney = ByteUtil::readUINT32(data)
		s.eSelfRank = ByteUtil::readUINT8(data)
		s.dwContribution = ByteUtil::readUINT32(data)
		s.dwRemainDonate = ByteUtil::readUINT32(data)
		s.wPlayerFighterID = ByteUtil::readUINT16(data)
		s.byQuality = ByteUtil::readUINT8(data)
		s.dwScore = ByteUtil::readUINT32(data)
		s.dwCount = ByteUtil::readUINT32(data)
		s.strLingShan = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildBaseInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT64(data, @qwOwnerID)
		ByteUtil::writeSTRING(data, @strOwnerName)
		ByteUtil::writeSTRING(data, @strInfo)
		ByteUtil::writeUINT64(data, @qwQQGroupID)
		ByteUtil::writeUINT16(data, @wUserCount)
		ByteUtil::writeUINT16(data, @wMaxUserCount)
		ByteUtil::writeUINT32(data, @dwMoney)
		ByteUtil::writeUINT8(data, @eSelfRank)
		ByteUtil::writeUINT32(data, @dwContribution)
		ByteUtil::writeUINT32(data, @dwRemainDonate)
		ByteUtil::writeUINT16(data, @wPlayerFighterID)
		ByteUtil::writeUINT8(data, @byQuality)
		ByteUtil::writeUINT32(data, @dwScore)
		ByteUtil::writeUINT32(data, @dwCount)
		ByteUtil::writeSTRING(data, @strLingShan)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮派成员信息
class SGuildUserInfo < SGuildInfoBase
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:strName #(string)玩家姓名
	attr_accessor:wLevel #(UINT16)玩家等级
	attr_accessor:dwContribution #(UINT32)贡献值
	attr_accessor:dwLastOnlineTime #(UINT32)最后在线时间
	attr_accessor:dwJoinTime #(UINT32)入帮时间
	attr_accessor:eMemberRank #(枚举类型：EMemberRank)帮派职位
	attr_accessor:eMemberLastRank #(枚举类型：EMemberRank)帮派上一次职位
	attr_accessor:dwAuthority #(UINT32)帮派权限
	attr_accessor:byVIPLevel #(UINT8)御剑等级
	attr_accessor:vecPlatforms #(SPlatformParam的数组)平台信息

	#构造函数
	def initialize
		super()
		@qwRoleID = 0
		@strName = ''
		@wLevel = 0
		@dwContribution = 0
		@dwLastOnlineTime = 0
		@dwJoinTime = 0
		@eMemberRank = 0
		@eMemberLastRank = 0
		@dwAuthority = 0
		@byVIPLevel = 0
		@vecPlatforms = Array.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SGuildInfoBase::ETYPE_SGUILDUSERINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.qwRoleID = @qwRoleID
		obj.strName = @strName
		obj.wLevel = @wLevel
		obj.dwContribution = @dwContribution
		obj.dwLastOnlineTime = @dwLastOnlineTime
		obj.dwJoinTime = @dwJoinTime
		obj.eMemberRank = @eMemberRank
		obj.eMemberLastRank = @eMemberLastRank
		obj.dwAuthority = @dwAuthority
		obj.byVIPLevel = @byVIPLevel
		obj.vecPlatforms = @vecPlatforms
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildUserInfo.new
		base = SGuildInfoBase::fromStream(data)
		base.copyTo(s)
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.wLevel = ByteUtil::readUINT16(data)
		s.dwContribution = ByteUtil::readUINT32(data)
		s.dwLastOnlineTime = ByteUtil::readUINT32(data)
		s.dwJoinTime = ByteUtil::readUINT32(data)
		s.eMemberRank = ByteUtil::readUINT8(data)
		s.eMemberLastRank = ByteUtil::readUINT8(data)
		s.dwAuthority = ByteUtil::readUINT32(data)
		s.byVIPLevel = ByteUtil::readUINT8(data)
		s.vecPlatforms = SPlatformParam::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildUserInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT16(data, @wLevel)
		ByteUtil::writeUINT32(data, @dwContribution)
		ByteUtil::writeUINT32(data, @dwLastOnlineTime)
		ByteUtil::writeUINT32(data, @dwJoinTime)
		ByteUtil::writeUINT8(data, @eMemberRank)
		ByteUtil::writeUINT8(data, @eMemberLastRank)
		ByteUtil::writeUINT32(data, @dwAuthority)
		ByteUtil::writeUINT8(data, @byVIPLevel)
		SPlatformParam::vectorToStream(data, @vecPlatforms)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮派申请列表信息
class SGuildApplyInfo < SGuildInfoBase
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:strName #(string)玩家姓名
	attr_accessor:wLevel #(UINT16)玩家等级
	attr_accessor:dwBattlePoint #(UINT32)玩家战斗力

	#构造函数
	def initialize
		super()
		@qwRoleID = 0
		@strName = ''
		@wLevel = 0
		@dwBattlePoint = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SGuildInfoBase::ETYPE_SGUILDAPPLYINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.qwRoleID = @qwRoleID
		obj.strName = @strName
		obj.wLevel = @wLevel
		obj.dwBattlePoint = @dwBattlePoint
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildApplyInfo.new
		base = SGuildInfoBase::fromStream(data)
		base.copyTo(s)
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.wLevel = ByteUtil::readUINT16(data)
		s.dwBattlePoint = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildApplyInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT16(data, @wLevel)
		ByteUtil::writeUINT32(data, @dwBattlePoint)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮派建筑信息
class SGuildBuildingInfo < SGuildInfoBase
	attr_accessor:eBuildingType #(枚举类型：EBuildingType)帮派建筑类型
	attr_accessor:wLevel #(UINT16)帮派建筑等级

	#构造函数
	def initialize
		super()
		@eBuildingType = 0
		@wLevel = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SGuildInfoBase::ETYPE_SGUILDBUILDINGINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.eBuildingType = @eBuildingType
		obj.wLevel = @wLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildBuildingInfo.new
		base = SGuildInfoBase::fromStream(data)
		base.copyTo(s)
		s.eBuildingType = ByteUtil::readUINT8(data)
		s.wLevel = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildBuildingInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @eBuildingType)
		ByteUtil::writeUINT16(data, @wLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮派可选权限信息
class SGuildAuthorityInfo < SGuildInfoBase
	attr_accessor:eMemberRank #(枚举类型：EMemberRank)帮派职位
	attr_accessor:dwAuthority #(UINT32)可选权限 0x01:指挥帮战 0x02:升级建筑 0x04:开启血池 0x08:指挥末日之战 0x10:创建遗迹攻击小队

	#构造函数
	def initialize
		super()
		@eMemberRank = 0
		@dwAuthority = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SGuildInfoBase::ETYPE_SGUILDAUTHORITYINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.eMemberRank = @eMemberRank
		obj.dwAuthority = @dwAuthority
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildAuthorityInfo.new
		base = SGuildInfoBase::fromStream(data)
		base.copyTo(s)
		s.eMemberRank = ByteUtil::readUINT8(data)
		s.dwAuthority = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildAuthorityInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @eMemberRank)
		ByteUtil::writeUINT32(data, @dwAuthority)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮派科技
class SGuildTechInfo < SGuildInfoBase
	attr_accessor:eType #(枚举类型：ETechType)科技类型
	attr_accessor:wLevel #(UINT16)科技等级

	#构造函数
	def initialize
		super()
		@eType = 0
		@wLevel = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SGuildInfoBase::ETYPE_SGUILDTECHINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.eType = @eType
		obj.wLevel = @wLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildTechInfo.new
		base = SGuildInfoBase::fromStream(data)
		base.copyTo(s)
		s.eType = ByteUtil::readUINT8(data)
		s.wLevel = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildTechInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @eType)
		ByteUtil::writeUINT16(data, @wLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#日志
class SGuildLogInfo < SGuildInfoBase
	attr_accessor:qwInstID #(UINT64)唯一流水ID
	attr_accessor:eType #(枚举类型：ELogType)日志类型
	attr_accessor:wMsgID #(UINT16)消息ID
	attr_accessor:vecParam #(INT64数组)整型变量
	attr_accessor:vecString #(string数组)字符串型变量
	attr_accessor:dwTime #(UINT32)日志时间

	#构造函数
	def initialize
		super()
		@qwInstID = 0
		@eType = 0
		@wMsgID = 0
		@vecParam = Array.new
		@vecString = Array.new
		@dwTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SGuildInfoBase::ETYPE_SGUILDLOGINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.qwInstID = @qwInstID
		obj.eType = @eType
		obj.wMsgID = @wMsgID
		obj.vecParam = @vecParam
		obj.vecString = @vecString
		obj.dwTime = @dwTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildLogInfo.new
		base = SGuildInfoBase::fromStream(data)
		base.copyTo(s)
		s.qwInstID = ByteUtil::readUINT64(data)
		s.eType = ByteUtil::readUINT8(data)
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
			s = SGuildLogInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT8(data, @eType)
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

#帮派神像
class SGuildStatueInfo < SGuildInfoBase
	attr_accessor:wLevel #(UINT16)神像等级
	attr_accessor:dwExp #(UINT32)神像经验值
	attr_accessor:vecLogInfo #(SGuildLogInfo的数组)神像日志
	attr_accessor:byWorshipCount #(UINT8)供奉人数
	attr_accessor:byWorshipBit #(UINT8)当前供奉（第N位表示第N种供奉类型）
	attr_accessor:dwTime #(UINT32)操作时间

	#构造函数
	def initialize
		super()
		@wLevel = 0
		@dwExp = 0
		@vecLogInfo = Array.new
		@byWorshipCount = 0
		@byWorshipBit = 0
		@dwTime = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_SGuildInfoBase::ETYPE_SGUILDSTATUEINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		super(obj)
		obj.wLevel = @wLevel
		obj.dwExp = @dwExp
		obj.vecLogInfo = @vecLogInfo
		obj.byWorshipCount = @byWorshipCount
		obj.byWorshipBit = @byWorshipBit
		obj.dwTime = @dwTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildStatueInfo.new
		base = SGuildInfoBase::fromStream(data)
		base.copyTo(s)
		s.wLevel = ByteUtil::readUINT16(data)
		s.dwExp = ByteUtil::readUINT32(data)
		s.vecLogInfo = SGuildLogInfo::vectorFromStream(data)
		s.byWorshipCount = ByteUtil::readUINT8(data)
		s.byWorshipBit = ByteUtil::readUINT8(data)
		s.dwTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildStatueInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wLevel)
		ByteUtil::writeUINT32(data, @dwExp)
		SGuildLogInfo::vectorToStream(data, @vecLogInfo)
		ByteUtil::writeUINT8(data, @byWorshipCount)
		ByteUtil::writeUINT8(data, @byWorshipBit)
		ByteUtil::writeUINT32(data, @dwTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#数据库加载用帮派玩家数据
class SDBGuildUserInfo
	attr_accessor:sBaseInfo #(类类型：SGuildUserInfo)帮派用户基本信息
	attr_accessor:vecTechInfo #(SGuildTechInfo的数组)帮派科技信息
	attr_accessor:dwBattleScore #(UINT32)帮派战积分
	attr_accessor:wPlayerFighterID #(UINT16)主将ID
	attr_accessor:byQuality #(UINT8)主将品质

	#构造函数
	def initialize
		@sBaseInfo = SGuildUserInfo.new
		@vecTechInfo = Array.new
		@dwBattleScore = 0
		@wPlayerFighterID = 0
		@byQuality = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.sBaseInfo = @sBaseInfo
		obj.vecTechInfo = @vecTechInfo
		obj.dwBattleScore = @dwBattleScore
		obj.wPlayerFighterID = @wPlayerFighterID
		obj.byQuality = @byQuality
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDBGuildUserInfo.new
		s.sBaseInfo = SGuildUserInfo::fromStream(data)
		s.vecTechInfo = SGuildTechInfo::vectorFromStream(data)
		s.dwBattleScore = ByteUtil::readUINT32(data)
		s.wPlayerFighterID = ByteUtil::readUINT16(data)
		s.byQuality = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDBGuildUserInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		@sBaseInfo.toStream(data)
		SGuildTechInfo::vectorToStream(data, @vecTechInfo)
		ByteUtil::writeUINT32(data, @dwBattleScore)
		ByteUtil::writeUINT16(data, @wPlayerFighterID)
		ByteUtil::writeUINT8(data, @byQuality)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮派完整信息
class SGuildAllInfo
	attr_accessor:sBaseInfo #(类类型：SGuildBaseInfo)基本信息
	attr_accessor:vecMemberInfo #(SGuildUserInfo的数组)帮派成员信息
	attr_accessor:vecApplyInfo #(SGuildApplyInfo的数组)帮派申请信息
	attr_accessor:vecBuildingInfo #(SGuildBuildingInfo的数组)帮派建筑信息
	attr_accessor:vecAuthority #(SGuildAuthorityInfo的数组)帮派可选权限信息
	attr_accessor:vecTech #(SGuildTechInfo的数组)帮派科技信息
	attr_accessor:sStatueInfo #(类类型：SGuildStatueInfo)帮派神像信息
	attr_accessor:vecLogInfo #(SGuildLogInfo的数组)帮派日志信息

	#构造函数
	def initialize
		@sBaseInfo = SGuildBaseInfo.new
		@vecMemberInfo = Array.new
		@vecApplyInfo = Array.new
		@vecBuildingInfo = Array.new
		@vecAuthority = Array.new
		@vecTech = Array.new
		@sStatueInfo = SGuildStatueInfo.new
		@vecLogInfo = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.sBaseInfo = @sBaseInfo
		obj.vecMemberInfo = @vecMemberInfo
		obj.vecApplyInfo = @vecApplyInfo
		obj.vecBuildingInfo = @vecBuildingInfo
		obj.vecAuthority = @vecAuthority
		obj.vecTech = @vecTech
		obj.sStatueInfo = @sStatueInfo
		obj.vecLogInfo = @vecLogInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildAllInfo.new
		s.sBaseInfo = SGuildBaseInfo::fromStream(data)
		s.vecMemberInfo = SGuildUserInfo::vectorFromStream(data)
		s.vecApplyInfo = SGuildApplyInfo::vectorFromStream(data)
		s.vecBuildingInfo = SGuildBuildingInfo::vectorFromStream(data)
		s.vecAuthority = SGuildAuthorityInfo::vectorFromStream(data)
		s.vecTech = SGuildTechInfo::vectorFromStream(data)
		s.sStatueInfo = SGuildStatueInfo::fromStream(data)
		s.vecLogInfo = SGuildLogInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildAllInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		@sBaseInfo.toStream(data)
		SGuildUserInfo::vectorToStream(data, @vecMemberInfo)
		SGuildApplyInfo::vectorToStream(data, @vecApplyInfo)
		SGuildBuildingInfo::vectorToStream(data, @vecBuildingInfo)
		SGuildAuthorityInfo::vectorToStream(data, @vecAuthority)
		SGuildTechInfo::vectorToStream(data, @vecTech)
		@sStatueInfo.toStream(data)
		SGuildLogInfo::vectorToStream(data, @vecLogInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮派完整信息(数据库传来的内部协议)
class SDBGuildAllInfo
	attr_accessor:sBaseInfo #(类类型：SGuildBaseInfo)基本信息
	attr_accessor:vecMemberInfo #(SDBGuildUserInfo的数组)帮派成员信息
	attr_accessor:vecApplyInfo #(SGuildApplyInfo的数组)帮派申请信息
	attr_accessor:vecBuildingInfo #(SGuildBuildingInfo的数组)帮派建筑信息
	attr_accessor:vecAuthority #(SGuildAuthorityInfo的数组)帮派可选权限信息
	attr_accessor:sStatueInfo #(类类型：SGuildStatueInfo)帮派神像信息
	attr_accessor:vecLogInfo #(SGuildLogInfo的数组)帮派日志信息
	attr_accessor:vecLingShanShopBuyLogInfo #(SGuildLogInfo的数组)帮派灵山商店购买日志信息

	#构造函数
	def initialize
		@sBaseInfo = SGuildBaseInfo.new
		@vecMemberInfo = Array.new
		@vecApplyInfo = Array.new
		@vecBuildingInfo = Array.new
		@vecAuthority = Array.new
		@sStatueInfo = SGuildStatueInfo.new
		@vecLogInfo = Array.new
		@vecLingShanShopBuyLogInfo = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.sBaseInfo = @sBaseInfo
		obj.vecMemberInfo = @vecMemberInfo
		obj.vecApplyInfo = @vecApplyInfo
		obj.vecBuildingInfo = @vecBuildingInfo
		obj.vecAuthority = @vecAuthority
		obj.sStatueInfo = @sStatueInfo
		obj.vecLogInfo = @vecLogInfo
		obj.vecLingShanShopBuyLogInfo = @vecLingShanShopBuyLogInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDBGuildAllInfo.new
		s.sBaseInfo = SGuildBaseInfo::fromStream(data)
		s.vecMemberInfo = SDBGuildUserInfo::vectorFromStream(data)
		s.vecApplyInfo = SGuildApplyInfo::vectorFromStream(data)
		s.vecBuildingInfo = SGuildBuildingInfo::vectorFromStream(data)
		s.vecAuthority = SGuildAuthorityInfo::vectorFromStream(data)
		s.sStatueInfo = SGuildStatueInfo::fromStream(data)
		s.vecLogInfo = SGuildLogInfo::vectorFromStream(data)
		s.vecLingShanShopBuyLogInfo = SGuildLogInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDBGuildAllInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		@sBaseInfo.toStream(data)
		SDBGuildUserInfo::vectorToStream(data, @vecMemberInfo)
		SGuildApplyInfo::vectorToStream(data, @vecApplyInfo)
		SGuildBuildingInfo::vectorToStream(data, @vecBuildingInfo)
		SGuildAuthorityInfo::vectorToStream(data, @vecAuthority)
		@sStatueInfo.toStream(data)
		SGuildLogInfo::vectorToStream(data, @vecLogInfo)
		SGuildLogInfo::vectorToStream(data, @vecLingShanShopBuyLogInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮派列表信息
class SGuildListInfo
	attr_accessor:qwGuildID #(UINT64)帮派唯一ID
	attr_accessor:strName #(string)帮派名称
	attr_accessor:strInfo #(string)帮派公告
	attr_accessor:qwOwnerID #(UINT64)帮主ID
	attr_accessor:strOwnerName #(string)帮主名称
	attr_accessor:byLevel #(UINT8)帮派等级
	attr_accessor:wUserCount #(UINT16)成员数量
	attr_accessor:wMaxUserCount #(UINT16)最大成员数量

	#构造函数
	def initialize
		@qwGuildID = 0
		@strName = ''
		@strInfo = ''
		@qwOwnerID = 0
		@strOwnerName = ''
		@byLevel = 0
		@wUserCount = 0
		@wMaxUserCount = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwGuildID = @qwGuildID
		obj.strName = @strName
		obj.strInfo = @strInfo
		obj.qwOwnerID = @qwOwnerID
		obj.strOwnerName = @strOwnerName
		obj.byLevel = @byLevel
		obj.wUserCount = @wUserCount
		obj.wMaxUserCount = @wMaxUserCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildListInfo.new
		s.qwGuildID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.strInfo = ByteUtil::readSTRING(data)
		s.qwOwnerID = ByteUtil::readUINT64(data)
		s.strOwnerName = ByteUtil::readSTRING(data)
		s.byLevel = ByteUtil::readUINT8(data)
		s.wUserCount = ByteUtil::readUINT16(data)
		s.wMaxUserCount = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildListInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwGuildID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeSTRING(data, @strInfo)
		ByteUtil::writeUINT64(data, @qwOwnerID)
		ByteUtil::writeSTRING(data, @strOwnerName)
		ByteUtil::writeUINT8(data, @byLevel)
		ByteUtil::writeUINT16(data, @wUserCount)
		ByteUtil::writeUINT16(data, @wMaxUserCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#数据库加载用帮派玩家数据
class SDBGuildBattleInfo
	attr_accessor:qwGuildID #(UINT64)帮派唯一ID
	attr_accessor:dwScore #(UINT32)帮派战积分

	#构造函数
	def initialize
		@qwGuildID = 0
		@dwScore = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwGuildID = @qwGuildID
		obj.dwScore = @dwScore
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SDBGuildBattleInfo.new
		s.qwGuildID = ByteUtil::readUINT64(data)
		s.dwScore = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SDBGuildBattleInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwGuildID)
		ByteUtil::writeUINT32(data, @dwScore)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#
class SGetGuildInfoBase
	#构造函数
	def initialize
	end

	#获取继承类的类型
	def getClassType
		return EType_SGetGuildInfoBase::ETYPE_SGETGUILDINFOBASE
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGetGuildInfoBase.new
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_SGetGuildInfoBase::ETYPE_SGETGUILDINFOBASE
				s = SGetGuildInfoBase::fromStream(data)
			when EType_SGetGuildInfoBase::ETYPE_SOTHERGUILDLISTINFO
				s = SOtherGuildListInfo::fromStream(data)
			when EType_SGetGuildInfoBase::ETYPE_SSELFGUILDINFO
				s = SSelfGuildInfo::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGetGuildInfoBase::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGetGuildInfoBase::superFromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
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

#没有帮派返回的其他帮派列表信息
class SOtherGuildListInfo < SGetGuildInfoBase
	attr_accessor:dwMaxGuildCount #(UINT32)最大帮派
	attr_accessor:dwCurGuildCount #(UINT32)当前帮派索引
	attr_accessor:vecGuildListInfo #(SGuildListInfo的数组)帮派列表信息
	attr_accessor:vecApplyGuildID #(UINT64数组)已申请列表帮派ID

	#构造函数
	def initialize
		super()
		@dwMaxGuildCount = 0
		@dwCurGuildCount = 0
		@vecGuildListInfo = Array.new
		@vecApplyGuildID = Array.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SGetGuildInfoBase::ETYPE_SOTHERGUILDLISTINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwMaxGuildCount = @dwMaxGuildCount
		obj.dwCurGuildCount = @dwCurGuildCount
		obj.vecGuildListInfo = @vecGuildListInfo
		obj.vecApplyGuildID = @vecApplyGuildID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SOtherGuildListInfo.new
		base = SGetGuildInfoBase::fromStream(data)
		s.dwMaxGuildCount = ByteUtil::readUINT32(data)
		s.dwCurGuildCount = ByteUtil::readUINT32(data)
		s.vecGuildListInfo = SGuildListInfo::vectorFromStream(data)
		s.vecApplyGuildID = ByteUtil::readVecUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SOtherGuildListInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT32(data, @dwMaxGuildCount)
		ByteUtil::writeUINT32(data, @dwCurGuildCount)
		SGuildListInfo::vectorToStream(data, @vecGuildListInfo)
		ByteUtil::writeVecUINT64(data, @vecApplyGuildID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#存在帮派的本帮信息
class SSelfGuildInfo < SGetGuildInfoBase
	attr_accessor:sAllInfo #(类类型：SGuildAllInfo)帮派完整信息

	#构造函数
	def initialize
		super()
		@sAllInfo = SGuildAllInfo.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SGetGuildInfoBase::ETYPE_SSELFGUILDINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.sAllInfo = @sAllInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSelfGuildInfo.new
		base = SGetGuildInfoBase::fromStream(data)
		s.sAllInfo = SGuildAllInfo::fromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSelfGuildInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		@sAllInfo.toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮派公共数据（用于服务端读取加载常驻内存的基础数据）
class SPubGuildAllInfo
	attr_accessor:sGuildListInfo #(类类型：SGuildListInfo)帮派列表数据
	attr_accessor:sGuildBattleInfo #(类类型：SDBGuildBattleInfo)帮派战数据

	#构造函数
	def initialize
		@sGuildListInfo = SGuildListInfo.new
		@sGuildBattleInfo = SDBGuildBattleInfo.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.sGuildListInfo = @sGuildListInfo
		obj.sGuildBattleInfo = @sGuildBattleInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPubGuildAllInfo.new
		s.sGuildListInfo = SGuildListInfo::fromStream(data)
		s.sGuildBattleInfo = SDBGuildBattleInfo::fromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPubGuildAllInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		@sGuildListInfo.toStream(data)
		@sGuildBattleInfo.toStream(data)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#羲和神车的货号信息
class STruckInfo
	attr_accessor:byTruckID #(UINT8)货号id
	attr_accessor:byStatus #(UINT8)EXiheTaskStatus货号状态(0未完成装货 1已请求帮助 2已完成装货)
	attr_accessor:byPos #(UINT8)货物顺序索引(0~7)
	attr_accessor:strName #(string)status为3时,完成装货的玩家名字(注:自己完成为空,不存储)
	attr_accessor:byColor #(UINT8)帮助者玩家颜色

	#构造函数
	def initialize
		@byTruckID = 0
		@byStatus = 0
		@byPos = 0
		@strName = ''
		@byColor = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byTruckID = @byTruckID
		obj.byStatus = @byStatus
		obj.byPos = @byPos
		obj.strName = @strName
		obj.byColor = @byColor
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STruckInfo.new
		s.byTruckID = ByteUtil::readUINT8(data)
		s.byStatus = ByteUtil::readUINT8(data)
		s.byPos = ByteUtil::readUINT8(data)
		s.strName = ByteUtil::readSTRING(data)
		s.byColor = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STruckInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @byTruckID)
		ByteUtil::writeUINT8(data, @byStatus)
		ByteUtil::writeUINT8(data, @byPos)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @byColor)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家羲和神车信息
class SGuildXihe
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:vecTruckInfo #(STruckInfo的数组)货号信息
	attr_accessor:byStage #(UINT8)EXiheStage当前阶段(0装货阶段 1任务冷却阶段 2等待玩家接取任务)
	attr_accessor:dwEndTime #(UINT32)当前阶段的结束时间
	attr_accessor:byRequest #(UINT8)已请求帮助的次数

	#构造函数
	def initialize
		@qwRoleID = 0
		@vecTruckInfo = Array.new
		@byStage = 0
		@dwEndTime = 0
		@byRequest = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.vecTruckInfo = @vecTruckInfo
		obj.byStage = @byStage
		obj.dwEndTime = @dwEndTime
		obj.byRequest = @byRequest
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildXihe.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.vecTruckInfo = STruckInfo::vectorFromStream(data)
		s.byStage = ByteUtil::readUINT8(data)
		s.dwEndTime = ByteUtil::readUINT32(data)
		s.byRequest = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildXihe::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		STruckInfo::vectorToStream(data, @vecTruckInfo)
		ByteUtil::writeUINT8(data, @byStage)
		ByteUtil::writeUINT32(data, @dwEndTime)
		ByteUtil::writeUINT8(data, @byRequest)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#羲和神车的请求帮助信息
class SXiheRequest
	attr_accessor:qwRoleID #(UINT64)玩家ID
	attr_accessor:strName #(string)请求玩家的名字
	attr_accessor:byReqColor #(UINT8)请求玩家的名字颜色
	attr_accessor:byPos #(UINT8)货物顺序索引(0~7)
	attr_accessor:byTruckID #(UINT8)货号ID
	attr_accessor:bystatus #(UINT8)状态
	attr_accessor:strHelpName #(string)帮助玩家的名字
	attr_accessor:byHelpColor #(UINT8)帮助者名字颜色

	#构造函数
	def initialize
		@qwRoleID = 0
		@strName = ''
		@byReqColor = 0
		@byPos = 0
		@byTruckID = 0
		@bystatus = 0
		@strHelpName = ''
		@byHelpColor = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.strName = @strName
		obj.byReqColor = @byReqColor
		obj.byPos = @byPos
		obj.byTruckID = @byTruckID
		obj.bystatus = @bystatus
		obj.strHelpName = @strHelpName
		obj.byHelpColor = @byHelpColor
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SXiheRequest.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.strName = ByteUtil::readSTRING(data)
		s.byReqColor = ByteUtil::readUINT8(data)
		s.byPos = ByteUtil::readUINT8(data)
		s.byTruckID = ByteUtil::readUINT8(data)
		s.bystatus = ByteUtil::readUINT8(data)
		s.strHelpName = ByteUtil::readSTRING(data)
		s.byHelpColor = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SXiheRequest::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeSTRING(data, @strName)
		ByteUtil::writeUINT8(data, @byReqColor)
		ByteUtil::writeUINT8(data, @byPos)
		ByteUtil::writeUINT8(data, @byTruckID)
		ByteUtil::writeUINT8(data, @bystatus)
		ByteUtil::writeSTRING(data, @strHelpName)
		ByteUtil::writeUINT8(data, @byHelpColor)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#帮派兑换物品
class SGuildExchangedItem
	attr_accessor:qwGuildID #(UINT64)帮派唯一ID
	attr_accessor:dwExchangeID #(UINT32)兑换ID
	attr_accessor:dwCount #(UINT32)兑换数量

	#构造函数
	def initialize
		@qwGuildID = 0
		@dwExchangeID = 0
		@dwCount = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwGuildID = @qwGuildID
		obj.dwExchangeID = @dwExchangeID
		obj.dwCount = @dwCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGuildExchangedItem.new
		s.qwGuildID = ByteUtil::readUINT64(data)
		s.dwExchangeID = ByteUtil::readUINT32(data)
		s.dwCount = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGuildExchangedItem::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwGuildID)
		ByteUtil::writeUINT32(data, @dwExchangeID)
		ByteUtil::writeUINT32(data, @dwCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[GetGuildInfo:获取帮派面板信息]的返回的参数组成的结构体
class SRetParam_GetGuildInfo
	attr_accessor:sGuildInfoBase#(类类型：SGetGuildInfoBase)返回结果

	#构造函数
	def initialize
		@sGuildInfoBase = SGetGuildInfoBase.new
	end
end

#函数[GetGuildList:获得帮派列表]的返回的参数组成的结构体
class SRetParam_GetGuildList
	attr_accessor:eResult#(枚举类型：EGuildResult)返回结果
	attr_accessor:sListInfo#(类类型：SOtherGuildListInfo)帮派列表信息

	#构造函数
	def initialize
		@eResult = 0
		@sListInfo = SOtherGuildListInfo.new
	end
end

#函数[GetGuildApplyInfo:获取帮派申请列表信息]的返回的参数组成的结构体
class SRetParam_GetGuildApplyInfo
	attr_accessor:eResult#(枚举类型：EGuildResult)返回结果
	attr_accessor:vecApplyInfo#(SGuildApplyInfo的数组)申请列表

	#构造函数
	def initialize
		@eResult = 0
		@vecApplyInfo = Array.new
	end
end

#函数[CreateGuild:创建帮派]的返回的参数组成的结构体
class SRetParam_CreateGuild
	attr_accessor:eResult#(枚举类型：ECreateResult)创建结果
	attr_accessor:vecGuildInfo#(SGuildAllInfo的数组)帮派信息(大小为0或者1)

	#构造函数
	def initialize
		@eResult = 0
		@vecGuildInfo = Array.new
	end
end

#函数[ApplyGuild:申请加入帮派]的返回的参数组成的结构体
class SRetParam_ApplyGuild
	attr_accessor:eResult#(枚举类型：EApplyResult)申请列表信息

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[AgreeApply:通过加入申请]的返回的参数组成的结构体
class SRetParam_AgreeApply
	attr_accessor:eResult#(枚举类型：EApplyResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[AgreeApplyAll:全部同意]的返回的参数组成的结构体
class SRetParam_AgreeApplyAll
	attr_accessor:eResult#(枚举类型：EApplyResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[RejectApply:拒绝加入申请]的返回的参数组成的结构体
class SRetParam_RejectApply
	attr_accessor:eResult#(枚举类型：EApplyResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[RejectApplyAll:全部拒绝]的返回的参数组成的结构体
class SRetParam_RejectApplyAll
	attr_accessor:eResult#(枚举类型：EApplyResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[InviteApply:邀请加入]的返回的参数组成的结构体
class SRetParam_InviteApply
	attr_accessor:eResult#(枚举类型：EApplyResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetGuildApplyList:获得已申请帮派列表]的返回的参数组成的结构体
class SRetParam_GetGuildApplyList
	attr_accessor:eResult#(枚举类型：EApplyResult)返回结果
	attr_accessor:vecGuildListInfo#(SGuildListInfo的数组)帮派列表信息

	#构造函数
	def initialize
		@eResult = 0
		@vecGuildListInfo = Array.new
	end
end

#函数[CancelApply:撤销帮派申请]的返回的参数组成的结构体
class SRetParam_CancelApply
	attr_accessor:eResult#(枚举类型：EApplyResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[InviteReply:邀请回应]的返回的参数组成的结构体
class SRetParam_InviteReply
	attr_accessor:eResult#(枚举类型：EApplyResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[QuitGuild:退出帮派]的返回的参数组成的结构体
class SRetParam_QuitGuild
	attr_accessor:eResult#(枚举类型：EQuitResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[SetAuthority:设置权限]的返回的参数组成的结构体
class SRetParam_SetAuthority
	attr_accessor:eResult#(枚举类型：ESetAuthorityResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[EditInfo:编辑公告]的返回的参数组成的结构体
class SRetParam_EditInfo
	attr_accessor:eResult#(枚举类型：EEditInfoResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[MemberOperate:帮派成员操作]的返回的参数组成的结构体
class SRetParam_MemberOperate
	attr_accessor:eResult#(枚举类型：EMemberOperateResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[ImpeachReply:弹劾回应]的返回的参数组成的结构体
class SRetParam_ImpeachReply
	attr_accessor:eResult#(枚举类型：EImpeachResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[LaunchImpeach:发起弹劾]的返回的参数组成的结构体
class SRetParam_LaunchImpeach
	attr_accessor:eResult#(枚举类型：EImpeachResult)弹劾结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[SearchGuildByName:搜索帮派]的返回的参数组成的结构体
class SRetParam_SearchGuildByName
	attr_accessor:eResult#(枚举类型：EGuildResult)返回结果
	attr_accessor:vecGuildListInfo#(SGuildListInfo的数组)帮派列表信息

	#构造函数
	def initialize
		@eResult = 0
		@vecGuildListInfo = Array.new
	end
end

#函数[SearchGuildByOwnerName:根据帮主搜索帮派]的返回的参数组成的结构体
class SRetParam_SearchGuildByOwnerName
	attr_accessor:eResult#(枚举类型：EGuildResult)返回结果
	attr_accessor:vecGuildListInfo#(SGuildListInfo的数组)帮派列表信息

	#构造函数
	def initialize
		@eResult = 0
		@vecGuildListInfo = Array.new
	end
end

#函数[SearchGuildByBothName:根据帮主搜索帮派]的返回的参数组成的结构体
class SRetParam_SearchGuildByBothName
	attr_accessor:eResult#(枚举类型：EGuildResult)返回结果
	attr_accessor:vecGuildListInfo#(SGuildListInfo的数组)帮派列表信息

	#构造函数
	def initialize
		@eResult = 0
		@vecGuildListInfo = Array.new
	end
end

#函数[UpgradeBuilding:提升帮派建筑等级]的返回的参数组成的结构体
class SRetParam_UpgradeBuilding
	attr_accessor:eResult#(枚举类型：EBuildingResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[UpgradeTech:提升帮派科技等级]的返回的参数组成的结构体
class SRetParam_UpgradeTech
	attr_accessor:eResult#(枚举类型：ETechResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[Donate:帮派捐献]的返回的参数组成的结构体
class SRetParam_Donate
	attr_accessor:eResult#(枚举类型：EDonateResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[Worship:帮派供奉]的返回的参数组成的结构体
class SRetParam_Worship
	attr_accessor:eResult#(枚举类型：EStatueResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[Muster:募集帮众]的返回的参数组成的结构体
class SRetParam_Muster
	attr_accessor:eResult#(枚举类型：EGuildResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[GetXiheRequestInfo:获取自己帮派成员的羲和神车请求帮助列表]的返回的参数组成的结构体
class SRetParam_GetXiheRequestInfo
	attr_accessor:vecXiheRequest#(SXiheRequest的数组)玩家羲和神车请求帮助的信息

	#构造函数
	def initialize
		@vecXiheRequest = Array.new
	end
end

#函数[ShipGoods:羲和神车装货]的返回的参数组成的结构体
class SRetParam_ShipGoods
	attr_accessor:eResult#(枚举类型：EGuildXiheResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[DeliveryGoods:羲和神车发货]的返回的参数组成的结构体
class SRetParam_DeliveryGoods
	attr_accessor:eResult#(枚举类型：EGuildXiheResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[RequestForHelp:羲和神车请求帮助装货]的返回的参数组成的结构体
class SRetParam_RequestForHelp
	attr_accessor:eResult#(枚举类型：EGuildXiheResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[HelpShipGoods:羲和神车帮众成员帮助装货]的返回的参数组成的结构体
class SRetParam_HelpShipGoods
	attr_accessor:eResult#(枚举类型：EGuildXiheResult)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[ReqGuildExchangedItemInfo:请求帮派兑换物品信息]的返回的参数组成的结构体
class SRetParam_ReqGuildExchangedItemInfo
	attr_accessor:vecLingShanType#(UINT8数组)灵山类型
	attr_accessor:vecGuildExchangedItem#(SGuildExchangedItem的数组)兑换物品信息
	attr_accessor:dwGUildAllMemberExchangedItemNum#(UINT32)帮派所有成员兑换物品总数量
	attr_accessor:dwPlayerExchangedItemNum#(UINT32)玩家兑换物品总数量
	attr_accessor:eMemberLastRank#(枚举类型：EMemberRank)玩家上一次帮派职位

	#构造函数
	def initialize
		@vecLingShanType = Array.new
		@vecGuildExchangedItem = Array.new
		@dwGUildAllMemberExchangedItemNum = 0
		@dwPlayerExchangedItemNum = 0
		@eMemberLastRank = 0
	end
end

#函数[ReqGuildExchangeItem:请求帮派兑换物品]的返回的参数组成的结构体
class SRetParam_ReqGuildExchangeItem
	attr_accessor:eResult#(枚举类型：EGuildExchangeRet)返回结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[ReqGuildExchangeItemLogInfo:请求帮派兑换物品日志信息]的返回的参数组成的结构体
class SRetParam_ReqGuildExchangeItemLogInfo
	attr_accessor:vecGuildLogInfo#(SGuildLogInfo的数组)兑换物品日志信息

	#构造函数
	def initialize
		@vecGuildLogInfo = Array.new
	end
end

#协议类：帮派相关协议
class GuildProtBase < ProtocolBase
	#以下为发送函数
	#发送：获取帮派面板信息
	def send_GetGuildInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得帮派列表
	def send_GetGuildList(
		dwIndex,  #(UINT32)帮派索引
		dwCount #(UINT32)帮派个数
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwIndex)
		ByteUtil::writeUINT32(data, dwCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取帮派申请列表信息
	def send_GetGuildApplyInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：创建帮派
	def send_CreateGuild(
		strName #(string)帮派名称
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeSTRING(data, strName)
		return @svrHandler.sendPacket(data)
	end

	#发送：申请加入帮派
	def send_ApplyGuild(
		qwGuildID #(UINT64)帮派ID
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwGuildID)
		return @svrHandler.sendPacket(data)
	end

	#发送：通过加入申请
	def send_AgreeApply(
		qwRoleID #(UINT64)申请者ID
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：全部同意
	def send_AgreeApplyAll(
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：拒绝加入申请
	def send_RejectApply(
		qwRoleID #(UINT64)申请者ID
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		return @svrHandler.sendPacket(data)
	end

	#发送：全部拒绝
	def send_RejectApplyAll(
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：邀请加入
	def send_InviteApply(
		strName #(string)被邀请者名字
	)
		sessionID = @sessionMgr.getNewSession(self, 10);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeSTRING(data, strName)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得已申请帮派列表
	def send_GetGuildApplyList(
	)
		sessionID = @sessionMgr.getNewSession(self, 11);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：撤销帮派申请
	def send_CancelApply(
		qwGuildID #(UINT64)帮派ID
	)
		sessionID = @sessionMgr.getNewSession(self, 12);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwGuildID)
		return @svrHandler.sendPacket(data)
	end

	#发送：邀请回应
	def send_InviteReply(
		qwGuildID,  #(UINT64)帮派ID
		bAgree #(bool)同意/拒绝
	)
		sessionID = @sessionMgr.getNewSession(self, 13);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 13
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwGuildID)
		ByteUtil::writeBOOL(data, bAgree)
		return @svrHandler.sendPacket(data)
	end

	#发送：退出帮派
	def send_QuitGuild(
	)
		sessionID = @sessionMgr.getNewSession(self, 14);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 14
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：设置权限
	def send_SetAuthority(
		eRank,  #(枚举类型：EMemberRank)职位
		dwAuthority #(UINT32)可选权限
	)
		sessionID = @sessionMgr.getNewSession(self, 15);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 15
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eRank)
		ByteUtil::writeUINT32(data, dwAuthority)
		return @svrHandler.sendPacket(data)
	end

	#发送：编辑公告
	def send_EditInfo(
		strInfo #(string)公告信息
	)
		sessionID = @sessionMgr.getNewSession(self, 16);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 16
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeSTRING(data, strInfo)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派成员操作
	def send_MemberOperate(
		qwRoleID,  #(UINT64)被设置者ID
		eOpType #(枚举类型：EMemberOperateType)操作类型
	)
		sessionID = @sessionMgr.getNewSession(self, 17);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 17
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwRoleID)
		ByteUtil::writeUINT8(data, eOpType)
		return @svrHandler.sendPacket(data)
	end

	#发送：弹劾回应
	def send_ImpeachReply(
		qwGuildID,  #(UINT64)帮派ID
		bAgree #(bool)同意/拒绝
	)
		sessionID = @sessionMgr.getNewSession(self, 18);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 18
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT64(data, qwGuildID)
		ByteUtil::writeBOOL(data, bAgree)
		return @svrHandler.sendPacket(data)
	end

	#发送：发起弹劾
	def send_LaunchImpeach(
	)
		sessionID = @sessionMgr.getNewSession(self, 19);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 19
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：搜索帮派
	def send_SearchGuildByName(
		strName #(string)帮派名称
	)
		sessionID = @sessionMgr.getNewSession(self, 20);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 20
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeSTRING(data, strName)
		return @svrHandler.sendPacket(data)
	end

	#发送：根据帮主搜索帮派
	def send_SearchGuildByOwnerName(
		strOwnerName #(string)帮主名称
	)
		sessionID = @sessionMgr.getNewSession(self, 21);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 21
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeSTRING(data, strOwnerName)
		return @svrHandler.sendPacket(data)
	end

	#发送：根据帮主搜索帮派
	def send_SearchGuildByBothName(
		strName,  #(string)帮派名称
		strOwnerName #(string)帮主名称
	)
		sessionID = @sessionMgr.getNewSession(self, 22);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 22
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeSTRING(data, strName)
		ByteUtil::writeSTRING(data, strOwnerName)
		return @svrHandler.sendPacket(data)
	end

	#发送：提升帮派建筑等级
	def send_UpgradeBuilding(
		eBuildingType #(枚举类型：EBuildingType)帮派建筑类型
	)
		sessionID = @sessionMgr.getNewSession(self, 23);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 23
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eBuildingType)
		return @svrHandler.sendPacket(data)
	end

	#发送：提升帮派科技等级
	def send_UpgradeTech(
		eType #(枚举类型：ETechType)帮派科技类型
	)
		sessionID = @sessionMgr.getNewSession(self, 24);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 24
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eType)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派捐献
	def send_Donate(
		dwMoney #(UINT32)捐献数量
	)
		sessionID = @sessionMgr.getNewSession(self, 25);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 25
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwMoney)
		return @svrHandler.sendPacket(data)
	end

	#发送：帮派供奉
	def send_Worship(
		eType #(枚举类型：EWorshipType)供奉类型
	)
		sessionID = @sessionMgr.getNewSession(self, 26);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 26
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, eType)
		return @svrHandler.sendPacket(data)
	end

	#发送：募集帮众
	def send_Muster(
	)
		sessionID = @sessionMgr.getNewSession(self, 27);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 27
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取玩家的羲和神车信息
	def send_GetXiheInfo(
		qwUserID #(UINT64)玩家ID(可为自己ID也可为帮派成员ID)
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 28
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwUserID)
		return @svrHandler.sendPacket(data)
	end

	#发送：玩家接受羲和神车任务
	def send_AcceptXiheTask(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 29
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取自己帮派成员的羲和神车请求帮助列表
	def send_GetXiheRequestInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 28);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 30
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：羲和神车装货
	def send_ShipGoods(
		byType,  #(UINT8)0:用道具装货 1:用仙石装货
		byPos #(UINT8)货物顺序索引(0~7)
	)
		sessionID = @sessionMgr.getNewSession(self, 29);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 31
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byType)
		ByteUtil::writeUINT8(data, byPos)
		return @svrHandler.sendPacket(data)
	end

	#发送：羲和神车发货
	def send_DeliveryGoods(
	)
		sessionID = @sessionMgr.getNewSession(self, 30);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 32
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：羲和神车请求帮助装货
	def send_RequestForHelp(
		byPos #(UINT8)货物顺序索引(0~7)
	)
		sessionID = @sessionMgr.getNewSession(self, 31);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 33
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byPos)
		return @svrHandler.sendPacket(data)
	end

	#发送：羲和神车帮众成员帮助装货
	def send_HelpShipGoods(
		byType,  #(UINT8)0:用道具装货 1:用仙石装货
		qwOtherID,  #(UINT64)玩家ID
		byPos #(UINT8)货物顺序索引(0~7)
	)
		sessionID = @sessionMgr.getNewSession(self, 32);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 34
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byType)
		ByteUtil::writeUINT64(data, qwOtherID)
		ByteUtil::writeUINT8(data, byPos)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求帮派兑换物品信息
	def send_ReqGuildExchangedItemInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 33);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 35
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求帮派兑换物品
	def send_ReqGuildExchangeItem(
		dwExchangeID,  #(UINT32)兑换id
		dwCount #(UINT32)兑换数量
	)
		sessionID = @sessionMgr.getNewSession(self, 34);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 36
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwExchangeID)
		ByteUtil::writeUINT32(data, dwCount)
		return @svrHandler.sendPacket(data)
	end

	#发送：请求帮派兑换物品日志信息
	def send_ReqGuildExchangeItemLogInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 35);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 37
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：帮派创建结果通知
	def onRecv_GuildCreateNotify(
		eResult, #(枚举类型：ECreateResult)创建结果
		vecGuildInfo #(SGuildAllInfo的数组)帮派信息(大小为0或者1)
	)
		raise NotImplementedError
	end
	#接收：帮派信息更新
	def onRecv_GuildInfoNotify(
		eDataType, #(枚举类型：EGuildDataType)帮派信息类型
		vecGuildInfoBase #(SGuildInfoBase的数组)帮派信息
	)
		raise NotImplementedError
	end
	#接收：帮派列表信息
	def onRecv_GuildListInfoNotify(
		dwMaxGuildCount, #(UINT32)最大帮派
		dwCurGuildCount, #(UINT32)当前帮派索引
		vecGuildListInfo #(SGuildListInfo的数组)帮派列表信息
	)
		raise NotImplementedError
	end
	#接收：帮派申请通过通知
	def onRecv_GuildApplyPassedNotify(
		sGuildAllInfo #(类类型：SGuildAllInfo)帮派信息
	)
		raise NotImplementedError
	end
	#接收：帮派申请拒绝通知
	def onRecv_GuildApplyRejectNotify(
		qwGuildID #(UINT64)帮派ID
	)
		raise NotImplementedError
	end
	#接收：帮派被踢出通知
	def onRecv_GuildKickNotify(
		qwGuildID, #(UINT64)帮派ID
		strName, #(string)帮派名称
		strKickName #(string)踢人者姓名
	)
		raise NotImplementedError
	end
	#接收：玩家被邀请进入帮派通知
	def onRecv_GuildInviteNotify(
		qwGuildID, #(UINT64)帮派ID
		strGuildName, #(string)帮派名称
		strInviterName #(string)邀请者名称
	)
		raise NotImplementedError
	end
	#接收：帮派弹劾通知
	def onRecv_GuildImpeachNotify(
		qwGuildID, #(UINT64)帮派ID
		strLauncherName, #(string)发起者姓名
		strOwnerName #(string)帮主姓名
	)
		raise NotImplementedError
	end
	#接收：帮派弹劾取消通知
	def onRecv_GuildImpeachSucceedNotify(
	)
		raise NotImplementedError
	end
	#接收：帮派弹劾取消通知
	def onRecv_GuildImpeachFailedNotify(
	)
		raise NotImplementedError
	end
	#接收：帮派弹劾取消通知
	def onRecv_GuildImpeachCancelNotify(
	)
		raise NotImplementedError
	end
	#接收：更新玩家羲和神车信息
	def onRecv_UpdateGuildXiheInfo(
		sGuildXihe #(类类型：SGuildXihe)玩家羲和神车信息
	)
		raise NotImplementedError
	end
	#接收：更新玩家羲和神车帮助信息
	def onRecv_GuildXiheHelpNotify(
		byType, #(UINT8)0增加请求帮助信息 1删除帮助列表的信息 2删除请求帮助信息添加XX帮助信息
		sXiheRequest #(类类型：SXiheRequest)玩家羲和神车请求帮助的信息
	)
		raise NotImplementedError
	end
	#接收：帮派兑换物品更新
	def onRecv_GuildExchangedItemNotify(
		vecGuildExchangedItem, #(SGuildExchangedItem的数组)兑换物品信息
		dwGUildAllMemberExchangedItemNum, #(UINT32)帮派所有成员兑换物品总数量
		dwPlayerExchangedItemNum #(UINT32)玩家兑换物品总数量
	)
		raise NotImplementedError
	end
	#接收：帮派战兑换物品开始
	def onRecv_GuildExchangedItemBeginNotify(
		vecLingShanType #(UINT8数组)灵山类型
	)
		raise NotImplementedError
	end
	#接收：帮派兑换物品日志更新
	def onRecv_GuildExchangeItemLogNotify(
		sGuildLogInfo #(类类型：SGuildLogInfo)兑换物品日志信息
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：获取帮派面板信息
	def onReturn_GetGuildInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetGuildInfo)返回的参数
	)
	end

	#返回：获得帮派列表
	def onReturn_GetGuildList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetGuildList)返回的参数
	)
	end

	#返回：获取帮派申请列表信息
	def onReturn_GetGuildApplyInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetGuildApplyInfo)返回的参数
	)
	end

	#返回：创建帮派
	def onReturn_CreateGuild(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_CreateGuild)返回的参数
	)
	end

	#返回：申请加入帮派
	def onReturn_ApplyGuild(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ApplyGuild)返回的参数
	)
	end

	#返回：通过加入申请
	def onReturn_AgreeApply(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_AgreeApply)返回的参数
	)
	end

	#返回：全部同意
	def onReturn_AgreeApplyAll(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_AgreeApplyAll)返回的参数
	)
	end

	#返回：拒绝加入申请
	def onReturn_RejectApply(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_RejectApply)返回的参数
	)
	end

	#返回：全部拒绝
	def onReturn_RejectApplyAll(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_RejectApplyAll)返回的参数
	)
	end

	#返回：邀请加入
	def onReturn_InviteApply(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_InviteApply)返回的参数
	)
	end

	#返回：获得已申请帮派列表
	def onReturn_GetGuildApplyList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetGuildApplyList)返回的参数
	)
	end

	#返回：撤销帮派申请
	def onReturn_CancelApply(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_CancelApply)返回的参数
	)
	end

	#返回：邀请回应
	def onReturn_InviteReply(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_InviteReply)返回的参数
	)
	end

	#返回：退出帮派
	def onReturn_QuitGuild(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_QuitGuild)返回的参数
	)
	end

	#返回：设置权限
	def onReturn_SetAuthority(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SetAuthority)返回的参数
	)
	end

	#返回：编辑公告
	def onReturn_EditInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_EditInfo)返回的参数
	)
	end

	#返回：帮派成员操作
	def onReturn_MemberOperate(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_MemberOperate)返回的参数
	)
	end

	#返回：弹劾回应
	def onReturn_ImpeachReply(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ImpeachReply)返回的参数
	)
	end

	#返回：发起弹劾
	def onReturn_LaunchImpeach(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LaunchImpeach)返回的参数
	)
	end

	#返回：搜索帮派
	def onReturn_SearchGuildByName(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SearchGuildByName)返回的参数
	)
	end

	#返回：根据帮主搜索帮派
	def onReturn_SearchGuildByOwnerName(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SearchGuildByOwnerName)返回的参数
	)
	end

	#返回：根据帮主搜索帮派
	def onReturn_SearchGuildByBothName(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_SearchGuildByBothName)返回的参数
	)
	end

	#返回：提升帮派建筑等级
	def onReturn_UpgradeBuilding(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UpgradeBuilding)返回的参数
	)
	end

	#返回：提升帮派科技等级
	def onReturn_UpgradeTech(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UpgradeTech)返回的参数
	)
	end

	#返回：帮派捐献
	def onReturn_Donate(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Donate)返回的参数
	)
	end

	#返回：帮派供奉
	def onReturn_Worship(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Worship)返回的参数
	)
	end

	#返回：募集帮众
	def onReturn_Muster(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Muster)返回的参数
	)
	end

	#返回：获取自己帮派成员的羲和神车请求帮助列表
	def onReturn_GetXiheRequestInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetXiheRequestInfo)返回的参数
	)
	end

	#返回：羲和神车装货
	def onReturn_ShipGoods(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ShipGoods)返回的参数
	)
	end

	#返回：羲和神车发货
	def onReturn_DeliveryGoods(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_DeliveryGoods)返回的参数
	)
	end

	#返回：羲和神车请求帮助装货
	def onReturn_RequestForHelp(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_RequestForHelp)返回的参数
	)
	end

	#返回：羲和神车帮众成员帮助装货
	def onReturn_HelpShipGoods(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_HelpShipGoods)返回的参数
	)
	end

	#返回：请求帮派兑换物品信息
	def onReturn_ReqGuildExchangedItemInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqGuildExchangedItemInfo)返回的参数
	)
	end

	#返回：请求帮派兑换物品
	def onReturn_ReqGuildExchangeItem(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqGuildExchangeItem)返回的参数
	)
	end

	#返回：请求帮派兑换物品日志信息
	def onReturn_ReqGuildExchangeItemLogInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ReqGuildExchangeItemLogInfo)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：帮派创建结果通知
	def _doRecv_GuildCreateNotify(data)
		eResult = ByteUtil::readUINT8(data)
		vecGuildInfo = SGuildAllInfo::vectorFromStream(data)
		return onRecv_GuildCreateNotify(eResult, vecGuildInfo)
	end

	#接收处理：帮派信息更新
	def _doRecv_GuildInfoNotify(data)
		eDataType = ByteUtil::readUINT8(data)
		vecGuildInfoBase = SGuildInfoBase::superVectorFromStream(data)
		return onRecv_GuildInfoNotify(eDataType, vecGuildInfoBase)
	end

	#接收处理：帮派列表信息
	def _doRecv_GuildListInfoNotify(data)
		dwMaxGuildCount = ByteUtil::readUINT32(data)
		dwCurGuildCount = ByteUtil::readUINT32(data)
		vecGuildListInfo = SGuildListInfo::vectorFromStream(data)
		return onRecv_GuildListInfoNotify(dwMaxGuildCount, dwCurGuildCount, vecGuildListInfo)
	end

	#接收处理：帮派申请通过通知
	def _doRecv_GuildApplyPassedNotify(data)
		sGuildAllInfo = SGuildAllInfo::fromStream(data)
		return onRecv_GuildApplyPassedNotify(sGuildAllInfo)
	end

	#接收处理：帮派申请拒绝通知
	def _doRecv_GuildApplyRejectNotify(data)
		qwGuildID = ByteUtil::readUINT64(data)
		return onRecv_GuildApplyRejectNotify(qwGuildID)
	end

	#接收处理：帮派被踢出通知
	def _doRecv_GuildKickNotify(data)
		qwGuildID = ByteUtil::readUINT64(data)
		strName = ByteUtil::readSTRING(data)
		strKickName = ByteUtil::readSTRING(data)
		return onRecv_GuildKickNotify(qwGuildID, strName, strKickName)
	end

	#接收处理：玩家被邀请进入帮派通知
	def _doRecv_GuildInviteNotify(data)
		qwGuildID = ByteUtil::readUINT64(data)
		strGuildName = ByteUtil::readSTRING(data)
		strInviterName = ByteUtil::readSTRING(data)
		return onRecv_GuildInviteNotify(qwGuildID, strGuildName, strInviterName)
	end

	#接收处理：帮派弹劾通知
	def _doRecv_GuildImpeachNotify(data)
		qwGuildID = ByteUtil::readUINT64(data)
		strLauncherName = ByteUtil::readSTRING(data)
		strOwnerName = ByteUtil::readSTRING(data)
		return onRecv_GuildImpeachNotify(qwGuildID, strLauncherName, strOwnerName)
	end

	#接收处理：帮派弹劾取消通知
	def _doRecv_GuildImpeachSucceedNotify(data)
		return onRecv_GuildImpeachSucceedNotify()
	end

	#接收处理：帮派弹劾取消通知
	def _doRecv_GuildImpeachFailedNotify(data)
		return onRecv_GuildImpeachFailedNotify()
	end

	#接收处理：帮派弹劾取消通知
	def _doRecv_GuildImpeachCancelNotify(data)
		return onRecv_GuildImpeachCancelNotify()
	end

	#接收处理：更新玩家羲和神车信息
	def _doRecv_UpdateGuildXiheInfo(data)
		sGuildXihe = SGuildXihe::fromStream(data)
		return onRecv_UpdateGuildXiheInfo(sGuildXihe)
	end

	#接收处理：更新玩家羲和神车帮助信息
	def _doRecv_GuildXiheHelpNotify(data)
		byType = ByteUtil::readUINT8(data)
		sXiheRequest = SXiheRequest::fromStream(data)
		return onRecv_GuildXiheHelpNotify(byType, sXiheRequest)
	end

	#接收处理：帮派兑换物品更新
	def _doRecv_GuildExchangedItemNotify(data)
		vecGuildExchangedItem = SGuildExchangedItem::vectorFromStream(data)
		dwGUildAllMemberExchangedItemNum = ByteUtil::readUINT32(data)
		dwPlayerExchangedItemNum = ByteUtil::readUINT32(data)
		return onRecv_GuildExchangedItemNotify(vecGuildExchangedItem, dwGUildAllMemberExchangedItemNum, dwPlayerExchangedItemNum)
	end

	#接收处理：帮派战兑换物品开始
	def _doRecv_GuildExchangedItemBeginNotify(data)
		vecLingShanType = ByteUtil::readVecUINT8(data)
		return onRecv_GuildExchangedItemBeginNotify(vecLingShanType)
	end

	#接收处理：帮派兑换物品日志更新
	def _doRecv_GuildExchangeItemLogNotify(data)
		sGuildLogInfo = SGuildLogInfo::fromStream(data)
		return onRecv_GuildExchangeItemLogNotify(sGuildLogInfo)
	end

#以下为返回处理函数
	#返回处理：获取帮派面板信息
	def _doReturn_GetGuildInfo(data)
		retParam = SRetParam_GetGuildInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		sGuildInfoBase = SGetGuildInfoBase::superFromStream(data) #(类类型：SGetGuildInfoBase)返回结果
		retParam.sGuildInfoBase = sGuildInfoBase
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetGuildInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取帮派面板信息
	def _onTimeOut_GetGuildInfo(sessionID)
		retParam = SRetParam_GetGuildInfo.new;
		onReturn_GetGuildInfo(2, retParam)
	end

	#返回处理：获得帮派列表
	def _doReturn_GetGuildList(data)
		retParam = SRetParam_GetGuildList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGuildResult)返回结果
		sListInfo = SOtherGuildListInfo::fromStream(data) #(类类型：SOtherGuildListInfo)帮派列表信息
		retParam.eResult = eResult
		retParam.sListInfo = sListInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetGuildList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获得帮派列表
	def _onTimeOut_GetGuildList(sessionID)
		retParam = SRetParam_GetGuildList.new;
		onReturn_GetGuildList(2, retParam)
	end

	#返回处理：获取帮派申请列表信息
	def _doReturn_GetGuildApplyInfo(data)
		retParam = SRetParam_GetGuildApplyInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGuildResult)返回结果
		vecApplyInfo = SGuildApplyInfo::vectorFromStream(data) #(SGuildApplyInfo的数组)申请列表
		retParam.eResult = eResult
		retParam.vecApplyInfo = vecApplyInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetGuildApplyInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取帮派申请列表信息
	def _onTimeOut_GetGuildApplyInfo(sessionID)
		retParam = SRetParam_GetGuildApplyInfo.new;
		onReturn_GetGuildApplyInfo(2, retParam)
	end

	#返回处理：创建帮派
	def _doReturn_CreateGuild(data)
		retParam = SRetParam_CreateGuild.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ECreateResult)创建结果
		vecGuildInfo = SGuildAllInfo::vectorFromStream(data) #(SGuildAllInfo的数组)帮派信息(大小为0或者1)
		retParam.eResult = eResult
		retParam.vecGuildInfo = vecGuildInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_CreateGuild(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：创建帮派
	def _onTimeOut_CreateGuild(sessionID)
		retParam = SRetParam_CreateGuild.new;
		onReturn_CreateGuild(2, retParam)
	end

	#返回处理：申请加入帮派
	def _doReturn_ApplyGuild(data)
		retParam = SRetParam_ApplyGuild.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EApplyResult)申请列表信息
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ApplyGuild(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：申请加入帮派
	def _onTimeOut_ApplyGuild(sessionID)
		retParam = SRetParam_ApplyGuild.new;
		onReturn_ApplyGuild(2, retParam)
	end

	#返回处理：通过加入申请
	def _doReturn_AgreeApply(data)
		retParam = SRetParam_AgreeApply.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EApplyResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_AgreeApply(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：通过加入申请
	def _onTimeOut_AgreeApply(sessionID)
		retParam = SRetParam_AgreeApply.new;
		onReturn_AgreeApply(2, retParam)
	end

	#返回处理：全部同意
	def _doReturn_AgreeApplyAll(data)
		retParam = SRetParam_AgreeApplyAll.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EApplyResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_AgreeApplyAll(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：全部同意
	def _onTimeOut_AgreeApplyAll(sessionID)
		retParam = SRetParam_AgreeApplyAll.new;
		onReturn_AgreeApplyAll(2, retParam)
	end

	#返回处理：拒绝加入申请
	def _doReturn_RejectApply(data)
		retParam = SRetParam_RejectApply.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EApplyResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_RejectApply(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：拒绝加入申请
	def _onTimeOut_RejectApply(sessionID)
		retParam = SRetParam_RejectApply.new;
		onReturn_RejectApply(2, retParam)
	end

	#返回处理：全部拒绝
	def _doReturn_RejectApplyAll(data)
		retParam = SRetParam_RejectApplyAll.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EApplyResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_RejectApplyAll(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：全部拒绝
	def _onTimeOut_RejectApplyAll(sessionID)
		retParam = SRetParam_RejectApplyAll.new;
		onReturn_RejectApplyAll(2, retParam)
	end

	#返回处理：邀请加入
	def _doReturn_InviteApply(data)
		retParam = SRetParam_InviteApply.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EApplyResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_InviteApply(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：邀请加入
	def _onTimeOut_InviteApply(sessionID)
		retParam = SRetParam_InviteApply.new;
		onReturn_InviteApply(2, retParam)
	end

	#返回处理：获得已申请帮派列表
	def _doReturn_GetGuildApplyList(data)
		retParam = SRetParam_GetGuildApplyList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EApplyResult)返回结果
		vecGuildListInfo = SGuildListInfo::vectorFromStream(data) #(SGuildListInfo的数组)帮派列表信息
		retParam.eResult = eResult
		retParam.vecGuildListInfo = vecGuildListInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetGuildApplyList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获得已申请帮派列表
	def _onTimeOut_GetGuildApplyList(sessionID)
		retParam = SRetParam_GetGuildApplyList.new;
		onReturn_GetGuildApplyList(2, retParam)
	end

	#返回处理：撤销帮派申请
	def _doReturn_CancelApply(data)
		retParam = SRetParam_CancelApply.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EApplyResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_CancelApply(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：撤销帮派申请
	def _onTimeOut_CancelApply(sessionID)
		retParam = SRetParam_CancelApply.new;
		onReturn_CancelApply(2, retParam)
	end

	#返回处理：邀请回应
	def _doReturn_InviteReply(data)
		retParam = SRetParam_InviteReply.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EApplyResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_InviteReply(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：邀请回应
	def _onTimeOut_InviteReply(sessionID)
		retParam = SRetParam_InviteReply.new;
		onReturn_InviteReply(2, retParam)
	end

	#返回处理：退出帮派
	def _doReturn_QuitGuild(data)
		retParam = SRetParam_QuitGuild.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EQuitResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_QuitGuild(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：退出帮派
	def _onTimeOut_QuitGuild(sessionID)
		retParam = SRetParam_QuitGuild.new;
		onReturn_QuitGuild(2, retParam)
	end

	#返回处理：设置权限
	def _doReturn_SetAuthority(data)
		retParam = SRetParam_SetAuthority.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ESetAuthorityResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SetAuthority(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：设置权限
	def _onTimeOut_SetAuthority(sessionID)
		retParam = SRetParam_SetAuthority.new;
		onReturn_SetAuthority(2, retParam)
	end

	#返回处理：编辑公告
	def _doReturn_EditInfo(data)
		retParam = SRetParam_EditInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EEditInfoResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_EditInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：编辑公告
	def _onTimeOut_EditInfo(sessionID)
		retParam = SRetParam_EditInfo.new;
		onReturn_EditInfo(2, retParam)
	end

	#返回处理：帮派成员操作
	def _doReturn_MemberOperate(data)
		retParam = SRetParam_MemberOperate.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EMemberOperateResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_MemberOperate(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：帮派成员操作
	def _onTimeOut_MemberOperate(sessionID)
		retParam = SRetParam_MemberOperate.new;
		onReturn_MemberOperate(2, retParam)
	end

	#返回处理：弹劾回应
	def _doReturn_ImpeachReply(data)
		retParam = SRetParam_ImpeachReply.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EImpeachResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ImpeachReply(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：弹劾回应
	def _onTimeOut_ImpeachReply(sessionID)
		retParam = SRetParam_ImpeachReply.new;
		onReturn_ImpeachReply(2, retParam)
	end

	#返回处理：发起弹劾
	def _doReturn_LaunchImpeach(data)
		retParam = SRetParam_LaunchImpeach.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EImpeachResult)弹劾结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LaunchImpeach(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：发起弹劾
	def _onTimeOut_LaunchImpeach(sessionID)
		retParam = SRetParam_LaunchImpeach.new;
		onReturn_LaunchImpeach(2, retParam)
	end

	#返回处理：搜索帮派
	def _doReturn_SearchGuildByName(data)
		retParam = SRetParam_SearchGuildByName.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGuildResult)返回结果
		vecGuildListInfo = SGuildListInfo::vectorFromStream(data) #(SGuildListInfo的数组)帮派列表信息
		retParam.eResult = eResult
		retParam.vecGuildListInfo = vecGuildListInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SearchGuildByName(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：搜索帮派
	def _onTimeOut_SearchGuildByName(sessionID)
		retParam = SRetParam_SearchGuildByName.new;
		onReturn_SearchGuildByName(2, retParam)
	end

	#返回处理：根据帮主搜索帮派
	def _doReturn_SearchGuildByOwnerName(data)
		retParam = SRetParam_SearchGuildByOwnerName.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGuildResult)返回结果
		vecGuildListInfo = SGuildListInfo::vectorFromStream(data) #(SGuildListInfo的数组)帮派列表信息
		retParam.eResult = eResult
		retParam.vecGuildListInfo = vecGuildListInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SearchGuildByOwnerName(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：根据帮主搜索帮派
	def _onTimeOut_SearchGuildByOwnerName(sessionID)
		retParam = SRetParam_SearchGuildByOwnerName.new;
		onReturn_SearchGuildByOwnerName(2, retParam)
	end

	#返回处理：根据帮主搜索帮派
	def _doReturn_SearchGuildByBothName(data)
		retParam = SRetParam_SearchGuildByBothName.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGuildResult)返回结果
		vecGuildListInfo = SGuildListInfo::vectorFromStream(data) #(SGuildListInfo的数组)帮派列表信息
		retParam.eResult = eResult
		retParam.vecGuildListInfo = vecGuildListInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_SearchGuildByBothName(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：根据帮主搜索帮派
	def _onTimeOut_SearchGuildByBothName(sessionID)
		retParam = SRetParam_SearchGuildByBothName.new;
		onReturn_SearchGuildByBothName(2, retParam)
	end

	#返回处理：提升帮派建筑等级
	def _doReturn_UpgradeBuilding(data)
		retParam = SRetParam_UpgradeBuilding.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EBuildingResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UpgradeBuilding(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：提升帮派建筑等级
	def _onTimeOut_UpgradeBuilding(sessionID)
		retParam = SRetParam_UpgradeBuilding.new;
		onReturn_UpgradeBuilding(2, retParam)
	end

	#返回处理：提升帮派科技等级
	def _doReturn_UpgradeTech(data)
		retParam = SRetParam_UpgradeTech.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETechResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UpgradeTech(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：提升帮派科技等级
	def _onTimeOut_UpgradeTech(sessionID)
		retParam = SRetParam_UpgradeTech.new;
		onReturn_UpgradeTech(2, retParam)
	end

	#返回处理：帮派捐献
	def _doReturn_Donate(data)
		retParam = SRetParam_Donate.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EDonateResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_Donate(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：帮派捐献
	def _onTimeOut_Donate(sessionID)
		retParam = SRetParam_Donate.new;
		onReturn_Donate(2, retParam)
	end

	#返回处理：帮派供奉
	def _doReturn_Worship(data)
		retParam = SRetParam_Worship.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EStatueResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_Worship(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：帮派供奉
	def _onTimeOut_Worship(sessionID)
		retParam = SRetParam_Worship.new;
		onReturn_Worship(2, retParam)
	end

	#返回处理：募集帮众
	def _doReturn_Muster(data)
		retParam = SRetParam_Muster.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGuildResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_Muster(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：募集帮众
	def _onTimeOut_Muster(sessionID)
		retParam = SRetParam_Muster.new;
		onReturn_Muster(2, retParam)
	end

	#返回处理：获取自己帮派成员的羲和神车请求帮助列表
	def _doReturn_GetXiheRequestInfo(data)
		retParam = SRetParam_GetXiheRequestInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecXiheRequest = SXiheRequest::vectorFromStream(data) #(SXiheRequest的数组)玩家羲和神车请求帮助的信息
		retParam.vecXiheRequest = vecXiheRequest
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetXiheRequestInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取自己帮派成员的羲和神车请求帮助列表
	def _onTimeOut_GetXiheRequestInfo(sessionID)
		retParam = SRetParam_GetXiheRequestInfo.new;
		onReturn_GetXiheRequestInfo(2, retParam)
	end

	#返回处理：羲和神车装货
	def _doReturn_ShipGoods(data)
		retParam = SRetParam_ShipGoods.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGuildXiheResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ShipGoods(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：羲和神车装货
	def _onTimeOut_ShipGoods(sessionID)
		retParam = SRetParam_ShipGoods.new;
		onReturn_ShipGoods(2, retParam)
	end

	#返回处理：羲和神车发货
	def _doReturn_DeliveryGoods(data)
		retParam = SRetParam_DeliveryGoods.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGuildXiheResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_DeliveryGoods(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：羲和神车发货
	def _onTimeOut_DeliveryGoods(sessionID)
		retParam = SRetParam_DeliveryGoods.new;
		onReturn_DeliveryGoods(2, retParam)
	end

	#返回处理：羲和神车请求帮助装货
	def _doReturn_RequestForHelp(data)
		retParam = SRetParam_RequestForHelp.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGuildXiheResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_RequestForHelp(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：羲和神车请求帮助装货
	def _onTimeOut_RequestForHelp(sessionID)
		retParam = SRetParam_RequestForHelp.new;
		onReturn_RequestForHelp(2, retParam)
	end

	#返回处理：羲和神车帮众成员帮助装货
	def _doReturn_HelpShipGoods(data)
		retParam = SRetParam_HelpShipGoods.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGuildXiheResult)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_HelpShipGoods(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：羲和神车帮众成员帮助装货
	def _onTimeOut_HelpShipGoods(sessionID)
		retParam = SRetParam_HelpShipGoods.new;
		onReturn_HelpShipGoods(2, retParam)
	end

	#返回处理：请求帮派兑换物品信息
	def _doReturn_ReqGuildExchangedItemInfo(data)
		retParam = SRetParam_ReqGuildExchangedItemInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecLingShanType = ByteUtil::readVecUINT8(data) #(UINT8数组)灵山类型
		vecGuildExchangedItem = SGuildExchangedItem::vectorFromStream(data) #(SGuildExchangedItem的数组)兑换物品信息
		dwGUildAllMemberExchangedItemNum = ByteUtil::readUINT32(data) #(UINT32)帮派所有成员兑换物品总数量
		dwPlayerExchangedItemNum = ByteUtil::readUINT32(data) #(UINT32)玩家兑换物品总数量
		eMemberLastRank = ByteUtil::readUINT8(data) #(枚举类型：EMemberRank)玩家上一次帮派职位
		retParam.vecLingShanType = vecLingShanType
		retParam.vecGuildExchangedItem = vecGuildExchangedItem
		retParam.dwGUildAllMemberExchangedItemNum = dwGUildAllMemberExchangedItemNum
		retParam.dwPlayerExchangedItemNum = dwPlayerExchangedItemNum
		retParam.eMemberLastRank = eMemberLastRank
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqGuildExchangedItemInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求帮派兑换物品信息
	def _onTimeOut_ReqGuildExchangedItemInfo(sessionID)
		retParam = SRetParam_ReqGuildExchangedItemInfo.new;
		onReturn_ReqGuildExchangedItemInfo(2, retParam)
	end

	#返回处理：请求帮派兑换物品
	def _doReturn_ReqGuildExchangeItem(data)
		retParam = SRetParam_ReqGuildExchangeItem.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：EGuildExchangeRet)返回结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqGuildExchangeItem(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求帮派兑换物品
	def _onTimeOut_ReqGuildExchangeItem(sessionID)
		retParam = SRetParam_ReqGuildExchangeItem.new;
		onReturn_ReqGuildExchangeItem(2, retParam)
	end

	#返回处理：请求帮派兑换物品日志信息
	def _doReturn_ReqGuildExchangeItemLogInfo(data)
		retParam = SRetParam_ReqGuildExchangeItemLogInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		vecGuildLogInfo = SGuildLogInfo::vectorFromStream(data) #(SGuildLogInfo的数组)兑换物品日志信息
		retParam.vecGuildLogInfo = vecGuildLogInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ReqGuildExchangeItemLogInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：请求帮派兑换物品日志信息
	def _onTimeOut_ReqGuildExchangeItemLogInfo(sessionID)
		retParam = SRetParam_ReqGuildExchangeItemLogInfo.new;
		onReturn_ReqGuildExchangeItemLogInfo(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 16;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_GuildCreateNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_GuildInfoNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_GuildListInfoNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_GuildApplyPassedNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_GuildApplyRejectNotify' #FuncID: 5
		@recvFuncList[5] = '_doRecv_GuildKickNotify' #FuncID: 6
		@recvFuncList[6] = '_doRecv_GuildInviteNotify' #FuncID: 7
		@recvFuncList[7] = '_doRecv_GuildImpeachNotify' #FuncID: 8
		@recvFuncList[8] = '_doRecv_GuildImpeachSucceedNotify' #FuncID: 9
		@recvFuncList[9] = '_doRecv_GuildImpeachFailedNotify' #FuncID: 10
		@recvFuncList[10] = '_doRecv_GuildImpeachCancelNotify' #FuncID: 11
		@recvFuncList[11] = '_doRecv_UpdateGuildXiheInfo' #FuncID: 12
		@recvFuncList[12] = '_doRecv_GuildXiheHelpNotify' #FuncID: 13
		@recvFuncList[13] = '_doRecv_GuildExchangedItemNotify' #FuncID: 14
		@recvFuncList[14] = '_doRecv_GuildExchangedItemBeginNotify' #FuncID: 15
		@recvFuncList[15] = '_doRecv_GuildExchangeItemLogNotify' #FuncID: 16

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_GetGuildInfo' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetGuildList' #FuncID: 2
		@retFuncList[2] = '_doReturn_GetGuildApplyInfo' #FuncID: 3
		@retFuncList[3] = '_doReturn_CreateGuild' #FuncID: 4
		@retFuncList[4] = '_doReturn_ApplyGuild' #FuncID: 5
		@retFuncList[5] = '_doReturn_AgreeApply' #FuncID: 6
		@retFuncList[6] = '_doReturn_AgreeApplyAll' #FuncID: 7
		@retFuncList[7] = '_doReturn_RejectApply' #FuncID: 8
		@retFuncList[8] = '_doReturn_RejectApplyAll' #FuncID: 9
		@retFuncList[9] = '_doReturn_InviteApply' #FuncID: 10
		@retFuncList[10] = '_doReturn_GetGuildApplyList' #FuncID: 11
		@retFuncList[11] = '_doReturn_CancelApply' #FuncID: 12
		@retFuncList[12] = '_doReturn_InviteReply' #FuncID: 13
		@retFuncList[13] = '_doReturn_QuitGuild' #FuncID: 14
		@retFuncList[14] = '_doReturn_SetAuthority' #FuncID: 15
		@retFuncList[15] = '_doReturn_EditInfo' #FuncID: 16
		@retFuncList[16] = '_doReturn_MemberOperate' #FuncID: 17
		@retFuncList[17] = '_doReturn_ImpeachReply' #FuncID: 18
		@retFuncList[18] = '_doReturn_LaunchImpeach' #FuncID: 19
		@retFuncList[19] = '_doReturn_SearchGuildByName' #FuncID: 20
		@retFuncList[20] = '_doReturn_SearchGuildByOwnerName' #FuncID: 21
		@retFuncList[21] = '_doReturn_SearchGuildByBothName' #FuncID: 22
		@retFuncList[22] = '_doReturn_UpgradeBuilding' #FuncID: 23
		@retFuncList[23] = '_doReturn_UpgradeTech' #FuncID: 24
		@retFuncList[24] = '_doReturn_Donate' #FuncID: 25
		@retFuncList[25] = '_doReturn_Worship' #FuncID: 26
		@retFuncList[26] = '_doReturn_Muster' #FuncID: 27
		@retFuncList[27] = '_doReturn_GetXiheRequestInfo' #FuncID: 28
		@retFuncList[28] = '_doReturn_ShipGoods' #FuncID: 29
		@retFuncList[29] = '_doReturn_DeliveryGoods' #FuncID: 30
		@retFuncList[30] = '_doReturn_RequestForHelp' #FuncID: 31
		@retFuncList[31] = '_doReturn_HelpShipGoods' #FuncID: 32
		@retFuncList[32] = '_doReturn_ReqGuildExchangedItemInfo' #FuncID: 33
		@retFuncList[33] = '_doReturn_ReqGuildExchangeItem' #FuncID: 34
		@retFuncList[34] = '_doReturn_ReqGuildExchangeItemLogInfo' #FuncID: 35

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_GetGuildInfo' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetGuildList' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GetGuildApplyInfo' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_CreateGuild' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_ApplyGuild' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_AgreeApply' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_AgreeApplyAll' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_RejectApply' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_RejectApplyAll' #FuncID: 9
		@timeFuncList[9] = '_onTimeOut_InviteApply' #FuncID: 10
		@timeFuncList[10] = '_onTimeOut_GetGuildApplyList' #FuncID: 11
		@timeFuncList[11] = '_onTimeOut_CancelApply' #FuncID: 12
		@timeFuncList[12] = '_onTimeOut_InviteReply' #FuncID: 13
		@timeFuncList[13] = '_onTimeOut_QuitGuild' #FuncID: 14
		@timeFuncList[14] = '_onTimeOut_SetAuthority' #FuncID: 15
		@timeFuncList[15] = '_onTimeOut_EditInfo' #FuncID: 16
		@timeFuncList[16] = '_onTimeOut_MemberOperate' #FuncID: 17
		@timeFuncList[17] = '_onTimeOut_ImpeachReply' #FuncID: 18
		@timeFuncList[18] = '_onTimeOut_LaunchImpeach' #FuncID: 19
		@timeFuncList[19] = '_onTimeOut_SearchGuildByName' #FuncID: 20
		@timeFuncList[20] = '_onTimeOut_SearchGuildByOwnerName' #FuncID: 21
		@timeFuncList[21] = '_onTimeOut_SearchGuildByBothName' #FuncID: 22
		@timeFuncList[22] = '_onTimeOut_UpgradeBuilding' #FuncID: 23
		@timeFuncList[23] = '_onTimeOut_UpgradeTech' #FuncID: 24
		@timeFuncList[24] = '_onTimeOut_Donate' #FuncID: 25
		@timeFuncList[25] = '_onTimeOut_Worship' #FuncID: 26
		@timeFuncList[26] = '_onTimeOut_Muster' #FuncID: 27
		@timeFuncList[27] = '_onTimeOut_GetXiheRequestInfo' #FuncID: 28
		@timeFuncList[28] = '_onTimeOut_ShipGoods' #FuncID: 29
		@timeFuncList[29] = '_onTimeOut_DeliveryGoods' #FuncID: 30
		@timeFuncList[30] = '_onTimeOut_RequestForHelp' #FuncID: 31
		@timeFuncList[31] = '_onTimeOut_HelpShipGoods' #FuncID: 32
		@timeFuncList[32] = '_onTimeOut_ReqGuildExchangedItemInfo' #FuncID: 33
		@timeFuncList[33] = '_onTimeOut_ReqGuildExchangeItem' #FuncID: 34
		@timeFuncList[34] = '_onTimeOut_ReqGuildExchangeItemLogInfo' #FuncID: 35
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

