#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    LingShanProt.rb
#  Purpose:      灵山（改名秘境）寻宝
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#灵山操作结果
class ELingShanOP
	ELINGSHANOP_SUCESS = 0#成功
	ELINGSHANOP_FAIL = 1#失败
	ELINGSHANOP_CD = 2#cd
	ELINGSHANOP_ERRORPATH = 3#目标点错误,没有路径
	ELINGSHANOP_NOMOVE = 4#目前状态无法移动
	ELINGSHANOP_NOOPEN = 5#活动未开始
	ELINGSHANOP_NOREG = 6#未报名
	ELINGSHANOP_ERRORROOMID = 7#错误的房间
	ELINGSHANOP_MOVECD = 8#移动cd限制
	ELINGSHANOP_MAPCFG = 9#获取地图配置错误
	ELINGSHANOP_NOTINROOM = 10#不在比赛地图
	ELINGSHANOP_ERRORMODELID = 11#错误的模型ｉｄ
	ELINGSHANOP_ERRORCONDID = 12#开启条件不满足
	ELINGSHANOP_ACTENDED = 13#活动已结束
	ELINGSHANOP_CHATCD = 14#聊天ｃｄ
	ELINGSHANOP_END = 15
end

#玩家状态
class ELingShanStatus
	ELINGSHANSTATUS_INIT = 0#未报名状态
	ELINGSHANSTATUS_WAIT = 1#排队状态
	ELINGSHANSTATUS_MOVE = 2#可移动状态
	ELINGSHANSTATUS_PLAYMOVIE = 3#播放动画状态
	ELINGSHANSTATUS_END = 4#活动结束状态
end

#地图格子上单元类型（暂时不用）
class ELingShanObjType
	ELINGSHANOBJTYPE_INVALID = 0#无效类型
	ELINGSHANOBJTYPE_PLAYER = 1#玩家
	ELINGSHANOBJTYPE_BOX = 2#物品(宝箱)
	ELINGSHANOBJTYPE_MONSTER = 3#怪物
	EOBJTYPE_END = 4#活动结束状态
end

#玩家获取奖励类型
class ELingShanPrizeType
	ELINGSHANPRIZETYPE_INVALID = 0#无效类型
	ELINGSHANPRIZETYPE_PICKNORMALBOX = 1#拣普通宝箱
	ELINGSHANPRIZETYPE_PICKGODBOX = 2#拣大宝箱
	ELINGSHANPRIZETYPE_MOVEBYGODBOX = 3#带有大宝箱
	ELINGSHANPRIZETYPE_WIN = 4#击败玩家
	ELINGSHANPRIZETYPE_FAIL = 5#被击败
	ELINGSHANPRIZETYPE_END = 6
end

#碰撞类型
class ECollideType
	ECOLLIDETYPE_INVALID = 0#无效数据
	ECOLLIDETYPE_PATH = 1#路径碰撞
	ECOLLIDETYPE_GRID = 2#格子碰撞
end

#玩家获取奖励记录
class STakePrizeLog
	attr_accessor:eType #(枚举类型：ELingShanPrizeType)奖励类型
	attr_accessor:wTakeBoxCount #(UINT16)获得宝箱数量
	attr_accessor:strFailName #(string)敌对玩家
	attr_accessor:qwReportID #(UINT64)战报id
	attr_accessor:fHPRate #(float)最终血量
	attr_accessor:dwSuiYuan #(UINT32)增加的随缘值
	attr_accessor:eCollideType #(枚举类型：ECollideType)碰撞类型

	#构造函数
	def initialize
		@eType = 0
		@wTakeBoxCount = 0
		@strFailName = ''
		@qwReportID = 0
		@fHPRate = 0
		@dwSuiYuan = 0
		@eCollideType = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.eType = @eType
		obj.wTakeBoxCount = @wTakeBoxCount
		obj.strFailName = @strFailName
		obj.qwReportID = @qwReportID
		obj.fHPRate = @fHPRate
		obj.dwSuiYuan = @dwSuiYuan
		obj.eCollideType = @eCollideType
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STakePrizeLog.new
		s.eType = ByteUtil::readUINT8(data)
		s.wTakeBoxCount = ByteUtil::readUINT16(data)
		s.strFailName = ByteUtil::readSTRING(data)
		s.qwReportID = ByteUtil::readUINT64(data)
		s.fHPRate = ByteUtil::readFLOAT(data)
		s.dwSuiYuan = ByteUtil::readUINT32(data)
		s.eCollideType = ByteUtil::readUINT8(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STakePrizeLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT8(data, @eType)
		ByteUtil::writeUINT16(data, @wTakeBoxCount)
		ByteUtil::writeSTRING(data, @strFailName)
		ByteUtil::writeUINT64(data, @qwReportID)
		ByteUtil::writeFLOAT(data, @fHPRate)
		ByteUtil::writeUINT32(data, @dwSuiYuan)
		ByteUtil::writeUINT8(data, @eCollideType)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#地图箱子信息
class SBoxInfo
	attr_accessor:wPos #(UINT16)当前所在地图位置
	attr_accessor:dwModelID #(UINT16)物品id

	#构造函数
	def initialize
		@wPos = 0
		@dwModelID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wPos = @wPos
		obj.dwModelID = @dwModelID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBoxInfo.new
		s.wPos = ByteUtil::readUINT16(data)
		s.dwModelID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBoxInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wPos)
		ByteUtil::writeUINT16(data, @dwModelID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#比赛的玩家信息
class SRoomPlayInfo
	attr_accessor:qwRoleID #(UINT64)玩家id
	attr_accessor:dwModelID #(UINT32)模型id
	attr_accessor:dwKillCnt #(UINT16)击杀人数
	attr_accessor:bGodBox #(bool)是否带有大宝箱
	attr_accessor:wPos #(UINT16)当前所在地图位置

	#构造函数
	def initialize
		@qwRoleID = 0
		@dwModelID = 0
		@dwKillCnt = 0
		@bGodBox = false
		@wPos = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.dwModelID = @dwModelID
		obj.dwKillCnt = @dwKillCnt
		obj.bGodBox = @bGodBox
		obj.wPos = @wPos
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRoomPlayInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.dwModelID = ByteUtil::readUINT32(data)
		s.dwKillCnt = ByteUtil::readUINT16(data)
		s.bGodBox = ByteUtil::readBOOL(data)
		s.wPos = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRoomPlayInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT32(data, @dwModelID)
		ByteUtil::writeUINT16(data, @dwKillCnt)
		ByteUtil::writeBOOL(data, @bGodBox)
		ByteUtil::writeUINT16(data, @wPos)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#地图的怪物信息
class SRoomMonsterInfo
	attr_accessor:dwMonsterID #(UINT32)怪物组id
	attr_accessor:dwKillCnt #(UINT16)击杀人数
	attr_accessor:wPos #(UINT16)当前所在地图位置

	#构造函数
	def initialize
		@dwMonsterID = 0
		@dwKillCnt = 0
		@wPos = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwMonsterID = @dwMonsterID
		obj.dwKillCnt = @dwKillCnt
		obj.wPos = @wPos
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRoomMonsterInfo.new
		s.dwMonsterID = ByteUtil::readUINT32(data)
		s.dwKillCnt = ByteUtil::readUINT16(data)
		s.wPos = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRoomMonsterInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwMonsterID)
		ByteUtil::writeUINT16(data, @dwKillCnt)
		ByteUtil::writeUINT16(data, @wPos)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家移动信息
class SPlayerMoveInfo
	attr_accessor:qwRoleID #(UINT64)玩家id
	attr_accessor:wSrcPos #(UINT16)当前位置
	attr_accessor:wDstPos #(UINT16)目标位置

	#构造函数
	def initialize
		@qwRoleID = 0
		@wSrcPos = 0
		@wDstPos = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwRoleID = @qwRoleID
		obj.wSrcPos = @wSrcPos
		obj.wDstPos = @wDstPos
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPlayerMoveInfo.new
		s.qwRoleID = ByteUtil::readUINT64(data)
		s.wSrcPos = ByteUtil::readUINT16(data)
		s.wDstPos = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPlayerMoveInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwRoleID)
		ByteUtil::writeUINT16(data, @wSrcPos)
		ByteUtil::writeUINT16(data, @wDstPos)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家路径碰撞信息
class SPathCollideInfo
	attr_accessor:wMinPos #(UINT16)小编号位置
	attr_accessor:wMaxtPos #(UINT16)大编号位置
	attr_accessor:qwWinPlayer #(UINT64)胜利玩家
	attr_accessor:dwWinKillCnt #(UINT32)胜利击杀数目
	attr_accessor:qwFailPlayer #(UINT64)失败玩家

	#构造函数
	def initialize
		@wMinPos = 0
		@wMaxtPos = 0
		@qwWinPlayer = 0
		@dwWinKillCnt = 0
		@qwFailPlayer = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wMinPos = @wMinPos
		obj.wMaxtPos = @wMaxtPos
		obj.qwWinPlayer = @qwWinPlayer
		obj.dwWinKillCnt = @dwWinKillCnt
		obj.qwFailPlayer = @qwFailPlayer
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPathCollideInfo.new
		s.wMinPos = ByteUtil::readUINT16(data)
		s.wMaxtPos = ByteUtil::readUINT16(data)
		s.qwWinPlayer = ByteUtil::readUINT64(data)
		s.dwWinKillCnt = ByteUtil::readUINT32(data)
		s.qwFailPlayer = ByteUtil::readUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPathCollideInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wMinPos)
		ByteUtil::writeUINT16(data, @wMaxtPos)
		ByteUtil::writeUINT64(data, @qwWinPlayer)
		ByteUtil::writeUINT32(data, @dwWinKillCnt)
		ByteUtil::writeUINT64(data, @qwFailPlayer)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家格子碰撞信息
class SGridCollideInfo
	attr_accessor:wPos #(UINT16)碰撞位置
	attr_accessor:qwWinPlayer #(UINT64)胜利玩家
	attr_accessor:dwWinKillCnt #(UINT32)击杀数目
	attr_accessor:vecFailPlayer #(UINT64数组)失败玩家列表

	#构造函数
	def initialize
		@wPos = 0
		@qwWinPlayer = 0
		@dwWinKillCnt = 0
		@vecFailPlayer = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wPos = @wPos
		obj.qwWinPlayer = @qwWinPlayer
		obj.dwWinKillCnt = @dwWinKillCnt
		obj.vecFailPlayer = @vecFailPlayer
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SGridCollideInfo.new
		s.wPos = ByteUtil::readUINT16(data)
		s.qwWinPlayer = ByteUtil::readUINT64(data)
		s.dwWinKillCnt = ByteUtil::readUINT32(data)
		s.vecFailPlayer = ByteUtil::readVecUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SGridCollideInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wPos)
		ByteUtil::writeUINT64(data, @qwWinPlayer)
		ByteUtil::writeUINT32(data, @dwWinKillCnt)
		ByteUtil::writeVecUINT64(data, @vecFailPlayer)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#玩家战斗信息（目前不需要战斗日志)
class SPlayerFighterLog
	attr_accessor:qwEnemy #(UINT64)战斗玩家
	attr_accessor:qwReportID #(UINT64)战斗日志
	attr_accessor:bWin #(bool)是否胜利

	#构造函数
	def initialize
		@qwEnemy = 0
		@qwReportID = 0
		@bWin = false
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwEnemy = @qwEnemy
		obj.qwReportID = @qwReportID
		obj.bWin = @bWin
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPlayerFighterLog.new
		s.qwEnemy = ByteUtil::readUINT64(data)
		s.qwReportID = ByteUtil::readUINT64(data)
		s.bWin = ByteUtil::readBOOL(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPlayerFighterLog::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwEnemy)
		ByteUtil::writeUINT64(data, @qwReportID)
		ByteUtil::writeBOOL(data, @bWin)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#房间信息
class SRoomInfo
	attr_accessor:wRoomID #(UINT16)房间编号
	attr_accessor:wPlayerCnt #(UINT16)房间人数

	#构造函数
	def initialize
		@wRoomID = 0
		@wPlayerCnt = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wRoomID = @wRoomID
		obj.wPlayerCnt = @wPlayerCnt
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SRoomInfo.new
		s.wRoomID = ByteUtil::readUINT16(data)
		s.wPlayerCnt = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SRoomInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wRoomID)
		ByteUtil::writeUINT16(data, @wPlayerCnt)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#动画播放信息
class SPlayMovieInfo
	attr_accessor:vecPlayerMoveInfo #(SPlayerMoveInfo的数组)玩家移动路径
	attr_accessor:vecPathCollideInfo #(SPathCollideInfo的数组)路径碰撞
	attr_accessor:vecGridCollideInfo #(SGridCollideInfo的数组)格子碰撞
	attr_accessor:vecRoomPlayInfo #(SRoomPlayInfo的数组)玩家信息

	#构造函数
	def initialize
		@vecPlayerMoveInfo = Array.new
		@vecPathCollideInfo = Array.new
		@vecGridCollideInfo = Array.new
		@vecRoomPlayInfo = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.vecPlayerMoveInfo = @vecPlayerMoveInfo
		obj.vecPathCollideInfo = @vecPathCollideInfo
		obj.vecGridCollideInfo = @vecGridCollideInfo
		obj.vecRoomPlayInfo = @vecRoomPlayInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SPlayMovieInfo.new
		s.vecPlayerMoveInfo = SPlayerMoveInfo::vectorFromStream(data)
		s.vecPathCollideInfo = SPathCollideInfo::vectorFromStream(data)
		s.vecGridCollideInfo = SGridCollideInfo::vectorFromStream(data)
		s.vecRoomPlayInfo = SRoomPlayInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SPlayMovieInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		SPlayerMoveInfo::vectorToStream(data, @vecPlayerMoveInfo)
		SPathCollideInfo::vectorToStream(data, @vecPathCollideInfo)
		SGridCollideInfo::vectorToStream(data, @vecGridCollideInfo)
		SRoomPlayInfo::vectorToStream(data, @vecRoomPlayInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[Reg:活动报名]的返回的参数组成的结构体
class SRetParam_Reg
	attr_accessor:eRet#(枚举类型：ELingShanOP)报名结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#函数[GetMatchInfo:当前棋盘状态]的返回的参数组成的结构体
class SRetParam_GetMatchInfo
	attr_accessor:eRet#(枚举类型：ELingShanOP)结果
	attr_accessor:vecBoxInfo#(SBoxInfo的数组)地图箱子信息
	attr_accessor:vecRoomPlayInfo#(SRoomPlayInfo的数组)地图玩家信息
	attr_accessor:vecRoomMonsterInfo#(SRoomMonsterInfo的数组)地图怪物信息
	attr_accessor:wRoomID#(UINT16)房间id
	attr_accessor:dwFreshTurn#(UINT32)至宝刷新剩余轮数
	attr_accessor:eStatus#(枚举类型：ELingShanStatus)当前状态
	attr_accessor:dwParam#(UINT32)排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
	attr_accessor:dwTime#(UINT32)服务器时间戳
	attr_accessor:oPlayMovieInfo#(类类型：SPlayMovieInfo)动画播放信息
	attr_accessor:vecTakePrizeLog#(STakePrizeLog的数组)玩家奖励log列表
	attr_accessor:dwTurn#(UINT32)当前轮数

	#构造函数
	def initialize
		@eRet = 0
		@vecBoxInfo = Array.new
		@vecRoomPlayInfo = Array.new
		@vecRoomMonsterInfo = Array.new
		@wRoomID = 0
		@dwFreshTurn = 0
		@eStatus = 0
		@dwParam = 0
		@dwTime = 0
		@oPlayMovieInfo = SPlayMovieInfo.new
		@vecTakePrizeLog = Array.new
		@dwTurn = 0
	end
end

#函数[GetMathSelInfo:获取自己的比赛信息]的返回的参数组成的结构体
class SRetParam_GetMathSelInfo
	attr_accessor:eRet#(枚举类型：ELingShanOP)结果
	attr_accessor:eStatus#(枚举类型：ELingShanStatus)当前状态
	attr_accessor:oRoomPlayInfo#(类类型：SRoomPlayInfo)玩家地图信息
	attr_accessor:fHPRate#(float)血量百分比
	attr_accessor:dwBoxCnt#(UINT16)宝箱数量
	attr_accessor:dwSuiYuan#(UINT32)随缘值
	attr_accessor:dwRoomID#(UINT32)房间号
	attr_accessor:dwFreshTurn#(UINT32)至宝刷新剩余轮数
	attr_accessor:dwModelID#(UINT32)模型id

	#构造函数
	def initialize
		@eRet = 0
		@eStatus = 0
		@oRoomPlayInfo = SRoomPlayInfo.new
		@fHPRate = 0
		@dwBoxCnt = 0
		@dwSuiYuan = 0
		@dwRoomID = 0
		@dwFreshTurn = 0
		@dwModelID = 0
	end
end

#函数[ChangeModel:更换模型信息]的返回的参数组成的结构体
class SRetParam_ChangeModel
	attr_accessor:eRet#(枚举类型：ELingShanOP)
	attr_accessor:dwModelID#(UINT32)模型id

	#构造函数
	def initialize
		@eRet = 0
		@dwModelID = 0
	end
end

#函数[MoveSelect:移动选择]的返回的参数组成的结构体
class SRetParam_MoveSelect
	attr_accessor:eRet#(枚举类型：ELingShanOP)结果
	attr_accessor:dwCdTime#(UINT32)cd

	#构造函数
	def initialize
		@eRet = 0
		@dwCdTime = 0
	end
end

#函数[GetActInfo:获取活动信息]的返回的参数组成的结构体
class SRetParam_GetActInfo
	attr_accessor:eRet#(枚举类型：ELingShanOP)结果
	attr_accessor:dwBeginTime#(UINT32)比赛开启时间
	attr_accessor:dwEndTime#(UINT32)比赛结束时间

	#构造函数
	def initialize
		@eRet = 0
		@dwBeginTime = 0
		@dwEndTime = 0
	end
end

#函数[Chat:聊天]的返回的参数组成的结构体
class SRetParam_Chat
	attr_accessor:eRet#(枚举类型：ELingShanOP)结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#函数[GetRoomList:获取房间信息]的返回的参数组成的结构体
class SRetParam_GetRoomList
	attr_accessor:eRet#(枚举类型：ELingShanOP)结果
	attr_accessor:vecRoomInfo#(SRoomInfo的数组)房间信息

	#构造函数
	def initialize
		@eRet = 0
		@vecRoomInfo = Array.new
	end
end

#函数[EnterVisitRoom:进入参观房间]的返回的参数组成的结构体
class SRetParam_EnterVisitRoom
	attr_accessor:eRet#(枚举类型：ELingShanOP)结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#函数[LeaveVisitRoom:离开参观房间]的返回的参数组成的结构体
class SRetParam_LeaveVisitRoom
	attr_accessor:eRet#(枚举类型：ELingShanOP)结果

	#构造函数
	def initialize
		@eRet = 0
	end
end

#函数[GetPlayMovieInfo:获取动画播放信息]的返回的参数组成的结构体
class SRetParam_GetPlayMovieInfo
	attr_accessor:eRet#(枚举类型：ELingShanOP)结果
	attr_accessor:oPlayMovieInfo#(类类型：SPlayMovieInfo)动画播放信息
	attr_accessor:vecTakePrizeLog#(STakePrizeLog的数组)玩家奖励log列表
	attr_accessor:wRoomID#(UINT16)房间id
	attr_accessor:dwTurn#(UINT32)当前轮数

	#构造函数
	def initialize
		@eRet = 0
		@oPlayMovieInfo = SPlayMovieInfo.new
		@vecTakePrizeLog = Array.new
		@wRoomID = 0
		@dwTurn = 0
	end
end

#协议类：灵山（改名秘境）寻宝
class LingShanProtBase < ProtocolBase
	#以下为发送函数
	#发送：获取状态（回StatusNotify通知）
	def send_GetStatus(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：活动报名
	def send_Reg(
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：当前棋盘状态
	def send_GetMatchInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取自己的比赛信息
	def send_GetMathSelInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：更换模型信息
	def send_ChangeModel(
		dwModelID #(UINT32)模型id
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT32(data, dwModelID)
		return @svrHandler.sendPacket(data)
	end

	#发送：移动选择
	def send_MoveSelect(
		wPos #(UINT16)位置
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wPos)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取活动信息
	def send_GetActInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 6);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：聊天
	def send_Chat(
		strChatMsg #(string)聊天内容
	)
		sessionID = @sessionMgr.getNewSession(self, 7);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeSTRING(data, strChatMsg)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取房间信息
	def send_GetRoomList(
	)
		sessionID = @sessionMgr.getNewSession(self, 8);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 9
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：进入参观房间
	def send_EnterVisitRoom(
		wRoomID #(UINT16)房间id
	)
		sessionID = @sessionMgr.getNewSession(self, 9);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 10
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wRoomID)
		return @svrHandler.sendPacket(data)
	end

	#发送：离开参观房间
	def send_LeaveVisitRoom(
	)
		sessionID = @sessionMgr.getNewSession(self, 10);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 11
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获取动画播放信息
	def send_GetPlayMovieInfo(
	)
		sessionID = @sessionMgr.getNewSession(self, 11);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 12
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：玩家个人血量通知
	def onRecv_SelHPRateNotify(
		fHPRate #(float)血量百分比
	)
		raise NotImplementedError
	end
	#接收：玩家自己当前状态通知
	def onRecv_StatusNotify(
		eRet, #(枚举类型：ELingShanStatus)当前状态
		dwParam, #(UINT32)排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
		dwTime, #(UINT32)服务器时间戳
		wRoomID #(UINT16)房间id
	)
		raise NotImplementedError
	end
	#接收：观看房间当前状态通知
	def onRecv_VisitRoomStatusNotify(
		eRet, #(枚举类型：ELingShanStatus)当前状态
		dwParam, #(UINT32)排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
		dwTime #(UINT32)服务器时间戳
	)
		raise NotImplementedError
	end
	#接收：玩家移动结果通知
	def onRecv_PlayerMoveNotify(
		vecPlayerMoveInfo, #(SPlayerMoveInfo的数组)玩家移动路径
		wRoomID #(UINT16)房间id
	)
		raise NotImplementedError
	end
	#接收：玩家路径碰撞结果通知
	def onRecv_PathCollideNotify(
		vecPathCollideInfo, #(SPathCollideInfo的数组)路径碰撞
		wRoomID #(UINT16)房间id
	)
		raise NotImplementedError
	end
	#接收：玩家格子碰撞结果通知
	def onRecv_GridCollideNotify(
		vecGridCollideInfo, #(SGridCollideInfo的数组)格子碰撞
		wRoomID #(UINT16)房间id
	)
		raise NotImplementedError
	end
	#接收：新玩家进入
	def onRecv_NewPlayerEnterNotify(
		vecRoomPlayInfo, #(SRoomPlayInfo的数组)玩家列表
		wRoomID #(UINT16)房间id
	)
		raise NotImplementedError
	end
	#接收：新一轮开始
	def onRecv_NewTurnBeginNotify(
		bFreshBox, #(bool)是否刷新宝箱
		wRoomID, #(UINT16)房间id
		dwFreshTurn #(UINT32)至宝刷新剩余轮数
	)
		raise NotImplementedError
	end
	#接收：模型修改
	def onRecv_PlayerChangeModelNotify(
		qwRoleID, #(UINT64)玩家id
		dwModelID, #(UINT32)模型id
		wRoomID #(UINT16)房间id
	)
		raise NotImplementedError
	end
	#接收：玩家奖励log
	def onRecv_PlayerPrizeLogNotify(
		vecTakePrizeLog #(STakePrizeLog的数组)玩家奖励log列表
	)
		raise NotImplementedError
	end
	#接收：聊天
	def onRecv_ChatNotify(
		qwRoleID, #(UINT64)结果
		strChatMsg, #(string)聊天内容
		wRoomID #(UINT16)房间id
	)
		raise NotImplementedError
	end
	#接收：玩家数据更新
	def onRecv_PlayerUpdateNotify(
		vecRoomPlayInfo, #(SRoomPlayInfo的数组)玩家列表
		wRoomID #(UINT16)房间id
	)
		raise NotImplementedError
	end
	#接收：从观察者房间踢掉
	def onRecv_KickViewNotify(
		wRoomID #(UINT16)进入的房间id
	)
		raise NotImplementedError
	end
	#接收：从房间离开
	def onRecv_KickPlayerNotify(
		qwRoleID, #(UINT64)进入的房间id
		wRoomID #(UINT16)进入的房间id
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：活动报名
	def onReturn_Reg(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Reg)返回的参数
	)
	end

	#返回：当前棋盘状态
	def onReturn_GetMatchInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetMatchInfo)返回的参数
	)
	end

	#返回：获取自己的比赛信息
	def onReturn_GetMathSelInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetMathSelInfo)返回的参数
	)
	end

	#返回：更换模型信息
	def onReturn_ChangeModel(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_ChangeModel)返回的参数
	)
	end

	#返回：移动选择
	def onReturn_MoveSelect(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_MoveSelect)返回的参数
	)
	end

	#返回：获取活动信息
	def onReturn_GetActInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetActInfo)返回的参数
	)
	end

	#返回：聊天
	def onReturn_Chat(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_Chat)返回的参数
	)
	end

	#返回：获取房间信息
	def onReturn_GetRoomList(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetRoomList)返回的参数
	)
	end

	#返回：进入参观房间
	def onReturn_EnterVisitRoom(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_EnterVisitRoom)返回的参数
	)
	end

	#返回：离开参观房间
	def onReturn_LeaveVisitRoom(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_LeaveVisitRoom)返回的参数
	)
	end

	#返回：获取动画播放信息
	def onReturn_GetPlayMovieInfo(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GetPlayMovieInfo)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：玩家个人血量通知
	def _doRecv_SelHPRateNotify(data)
		fHPRate = ByteUtil::readFLOAT(data)
		return onRecv_SelHPRateNotify(fHPRate)
	end

	#接收处理：玩家自己当前状态通知
	def _doRecv_StatusNotify(data)
		eRet = ByteUtil::readUINT8(data)
		dwParam = ByteUtil::readUINT32(data)
		dwTime = ByteUtil::readUINT32(data)
		wRoomID = ByteUtil::readUINT16(data)
		return onRecv_StatusNotify(eRet, dwParam, dwTime, wRoomID)
	end

	#接收处理：观看房间当前状态通知
	def _doRecv_VisitRoomStatusNotify(data)
		eRet = ByteUtil::readUINT8(data)
		dwParam = ByteUtil::readUINT32(data)
		dwTime = ByteUtil::readUINT32(data)
		return onRecv_VisitRoomStatusNotify(eRet, dwParam, dwTime)
	end

	#接收处理：玩家移动结果通知
	def _doRecv_PlayerMoveNotify(data)
		vecPlayerMoveInfo = SPlayerMoveInfo::vectorFromStream(data)
		wRoomID = ByteUtil::readUINT16(data)
		return onRecv_PlayerMoveNotify(vecPlayerMoveInfo, wRoomID)
	end

	#接收处理：玩家路径碰撞结果通知
	def _doRecv_PathCollideNotify(data)
		vecPathCollideInfo = SPathCollideInfo::vectorFromStream(data)
		wRoomID = ByteUtil::readUINT16(data)
		return onRecv_PathCollideNotify(vecPathCollideInfo, wRoomID)
	end

	#接收处理：玩家格子碰撞结果通知
	def _doRecv_GridCollideNotify(data)
		vecGridCollideInfo = SGridCollideInfo::vectorFromStream(data)
		wRoomID = ByteUtil::readUINT16(data)
		return onRecv_GridCollideNotify(vecGridCollideInfo, wRoomID)
	end

	#接收处理：新玩家进入
	def _doRecv_NewPlayerEnterNotify(data)
		vecRoomPlayInfo = SRoomPlayInfo::vectorFromStream(data)
		wRoomID = ByteUtil::readUINT16(data)
		return onRecv_NewPlayerEnterNotify(vecRoomPlayInfo, wRoomID)
	end

	#接收处理：新一轮开始
	def _doRecv_NewTurnBeginNotify(data)
		bFreshBox = ByteUtil::readBOOL(data)
		wRoomID = ByteUtil::readUINT16(data)
		dwFreshTurn = ByteUtil::readUINT32(data)
		return onRecv_NewTurnBeginNotify(bFreshBox, wRoomID, dwFreshTurn)
	end

	#接收处理：模型修改
	def _doRecv_PlayerChangeModelNotify(data)
		qwRoleID = ByteUtil::readUINT64(data)
		dwModelID = ByteUtil::readUINT32(data)
		wRoomID = ByteUtil::readUINT16(data)
		return onRecv_PlayerChangeModelNotify(qwRoleID, dwModelID, wRoomID)
	end

	#接收处理：玩家奖励log
	def _doRecv_PlayerPrizeLogNotify(data)
		vecTakePrizeLog = STakePrizeLog::vectorFromStream(data)
		return onRecv_PlayerPrizeLogNotify(vecTakePrizeLog)
	end

	#接收处理：聊天
	def _doRecv_ChatNotify(data)
		qwRoleID = ByteUtil::readUINT64(data)
		strChatMsg = ByteUtil::readSTRING(data)
		wRoomID = ByteUtil::readUINT16(data)
		return onRecv_ChatNotify(qwRoleID, strChatMsg, wRoomID)
	end

	#接收处理：玩家数据更新
	def _doRecv_PlayerUpdateNotify(data)
		vecRoomPlayInfo = SRoomPlayInfo::vectorFromStream(data)
		wRoomID = ByteUtil::readUINT16(data)
		return onRecv_PlayerUpdateNotify(vecRoomPlayInfo, wRoomID)
	end

	#接收处理：从观察者房间踢掉
	def _doRecv_KickViewNotify(data)
		wRoomID = ByteUtil::readUINT16(data)
		return onRecv_KickViewNotify(wRoomID)
	end

	#接收处理：从房间离开
	def _doRecv_KickPlayerNotify(data)
		qwRoleID = ByteUtil::readUINT64(data)
		wRoomID = ByteUtil::readUINT16(data)
		return onRecv_KickPlayerNotify(qwRoleID, wRoomID)
	end

#以下为返回处理函数
	#返回处理：活动报名
	def _doReturn_Reg(data)
		retParam = SRetParam_Reg.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：ELingShanOP)报名结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_Reg(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：活动报名
	def _onTimeOut_Reg(sessionID)
		retParam = SRetParam_Reg.new;
		onReturn_Reg(2, retParam)
	end

	#返回处理：当前棋盘状态
	def _doReturn_GetMatchInfo(data)
		retParam = SRetParam_GetMatchInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：ELingShanOP)结果
		vecBoxInfo = SBoxInfo::vectorFromStream(data) #(SBoxInfo的数组)地图箱子信息
		vecRoomPlayInfo = SRoomPlayInfo::vectorFromStream(data) #(SRoomPlayInfo的数组)地图玩家信息
		vecRoomMonsterInfo = SRoomMonsterInfo::vectorFromStream(data) #(SRoomMonsterInfo的数组)地图怪物信息
		wRoomID = ByteUtil::readUINT16(data) #(UINT16)房间id
		dwFreshTurn = ByteUtil::readUINT32(data) #(UINT32)至宝刷新剩余轮数
		eStatus = ByteUtil::readUINT8(data) #(枚举类型：ELingShanStatus)当前状态
		dwParam = ByteUtil::readUINT32(data) #(UINT32)排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
		dwTime = ByteUtil::readUINT32(data) #(UINT32)服务器时间戳
		oPlayMovieInfo = SPlayMovieInfo::fromStream(data) #(类类型：SPlayMovieInfo)动画播放信息
		vecTakePrizeLog = STakePrizeLog::vectorFromStream(data) #(STakePrizeLog的数组)玩家奖励log列表
		dwTurn = ByteUtil::readUINT32(data) #(UINT32)当前轮数
		retParam.eRet = eRet
		retParam.vecBoxInfo = vecBoxInfo
		retParam.vecRoomPlayInfo = vecRoomPlayInfo
		retParam.vecRoomMonsterInfo = vecRoomMonsterInfo
		retParam.wRoomID = wRoomID
		retParam.dwFreshTurn = dwFreshTurn
		retParam.eStatus = eStatus
		retParam.dwParam = dwParam
		retParam.dwTime = dwTime
		retParam.oPlayMovieInfo = oPlayMovieInfo
		retParam.vecTakePrizeLog = vecTakePrizeLog
		retParam.dwTurn = dwTurn
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetMatchInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：当前棋盘状态
	def _onTimeOut_GetMatchInfo(sessionID)
		retParam = SRetParam_GetMatchInfo.new;
		onReturn_GetMatchInfo(2, retParam)
	end

	#返回处理：获取自己的比赛信息
	def _doReturn_GetMathSelInfo(data)
		retParam = SRetParam_GetMathSelInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：ELingShanOP)结果
		eStatus = ByteUtil::readUINT8(data) #(枚举类型：ELingShanStatus)当前状态
		oRoomPlayInfo = SRoomPlayInfo::fromStream(data) #(类类型：SRoomPlayInfo)玩家地图信息
		fHPRate = ByteUtil::readFLOAT(data) #(float)血量百分比
		dwBoxCnt = ByteUtil::readUINT16(data) #(UINT16)宝箱数量
		dwSuiYuan = ByteUtil::readUINT32(data) #(UINT32)随缘值
		dwRoomID = ByteUtil::readUINT32(data) #(UINT32)房间号
		dwFreshTurn = ByteUtil::readUINT32(data) #(UINT32)至宝刷新剩余轮数
		dwModelID = ByteUtil::readUINT32(data) #(UINT32)模型id
		retParam.eRet = eRet
		retParam.eStatus = eStatus
		retParam.oRoomPlayInfo = oRoomPlayInfo
		retParam.fHPRate = fHPRate
		retParam.dwBoxCnt = dwBoxCnt
		retParam.dwSuiYuan = dwSuiYuan
		retParam.dwRoomID = dwRoomID
		retParam.dwFreshTurn = dwFreshTurn
		retParam.dwModelID = dwModelID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetMathSelInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取自己的比赛信息
	def _onTimeOut_GetMathSelInfo(sessionID)
		retParam = SRetParam_GetMathSelInfo.new;
		onReturn_GetMathSelInfo(2, retParam)
	end

	#返回处理：更换模型信息
	def _doReturn_ChangeModel(data)
		retParam = SRetParam_ChangeModel.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：ELingShanOP)
		dwModelID = ByteUtil::readUINT32(data) #(UINT32)模型id
		retParam.eRet = eRet
		retParam.dwModelID = dwModelID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_ChangeModel(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：更换模型信息
	def _onTimeOut_ChangeModel(sessionID)
		retParam = SRetParam_ChangeModel.new;
		onReturn_ChangeModel(2, retParam)
	end

	#返回处理：移动选择
	def _doReturn_MoveSelect(data)
		retParam = SRetParam_MoveSelect.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：ELingShanOP)结果
		dwCdTime = ByteUtil::readUINT32(data) #(UINT32)cd
		retParam.eRet = eRet
		retParam.dwCdTime = dwCdTime
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_MoveSelect(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：移动选择
	def _onTimeOut_MoveSelect(sessionID)
		retParam = SRetParam_MoveSelect.new;
		onReturn_MoveSelect(2, retParam)
	end

	#返回处理：获取活动信息
	def _doReturn_GetActInfo(data)
		retParam = SRetParam_GetActInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：ELingShanOP)结果
		dwBeginTime = ByteUtil::readUINT32(data) #(UINT32)比赛开启时间
		dwEndTime = ByteUtil::readUINT32(data) #(UINT32)比赛结束时间
		retParam.eRet = eRet
		retParam.dwBeginTime = dwBeginTime
		retParam.dwEndTime = dwEndTime
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetActInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取活动信息
	def _onTimeOut_GetActInfo(sessionID)
		retParam = SRetParam_GetActInfo.new;
		onReturn_GetActInfo(2, retParam)
	end

	#返回处理：聊天
	def _doReturn_Chat(data)
		retParam = SRetParam_Chat.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：ELingShanOP)结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_Chat(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：聊天
	def _onTimeOut_Chat(sessionID)
		retParam = SRetParam_Chat.new;
		onReturn_Chat(2, retParam)
	end

	#返回处理：获取房间信息
	def _doReturn_GetRoomList(data)
		retParam = SRetParam_GetRoomList.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：ELingShanOP)结果
		vecRoomInfo = SRoomInfo::vectorFromStream(data) #(SRoomInfo的数组)房间信息
		retParam.eRet = eRet
		retParam.vecRoomInfo = vecRoomInfo
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetRoomList(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取房间信息
	def _onTimeOut_GetRoomList(sessionID)
		retParam = SRetParam_GetRoomList.new;
		onReturn_GetRoomList(2, retParam)
	end

	#返回处理：进入参观房间
	def _doReturn_EnterVisitRoom(data)
		retParam = SRetParam_EnterVisitRoom.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：ELingShanOP)结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_EnterVisitRoom(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：进入参观房间
	def _onTimeOut_EnterVisitRoom(sessionID)
		retParam = SRetParam_EnterVisitRoom.new;
		onReturn_EnterVisitRoom(2, retParam)
	end

	#返回处理：离开参观房间
	def _doReturn_LeaveVisitRoom(data)
		retParam = SRetParam_LeaveVisitRoom.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：ELingShanOP)结果
		retParam.eRet = eRet
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_LeaveVisitRoom(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：离开参观房间
	def _onTimeOut_LeaveVisitRoom(sessionID)
		retParam = SRetParam_LeaveVisitRoom.new;
		onReturn_LeaveVisitRoom(2, retParam)
	end

	#返回处理：获取动画播放信息
	def _doReturn_GetPlayMovieInfo(data)
		retParam = SRetParam_GetPlayMovieInfo.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eRet = ByteUtil::readUINT8(data) #(枚举类型：ELingShanOP)结果
		oPlayMovieInfo = SPlayMovieInfo::fromStream(data) #(类类型：SPlayMovieInfo)动画播放信息
		vecTakePrizeLog = STakePrizeLog::vectorFromStream(data) #(STakePrizeLog的数组)玩家奖励log列表
		wRoomID = ByteUtil::readUINT16(data) #(UINT16)房间id
		dwTurn = ByteUtil::readUINT32(data) #(UINT32)当前轮数
		retParam.eRet = eRet
		retParam.oPlayMovieInfo = oPlayMovieInfo
		retParam.vecTakePrizeLog = vecTakePrizeLog
		retParam.wRoomID = wRoomID
		retParam.dwTurn = dwTurn
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GetPlayMovieInfo(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：获取动画播放信息
	def _onTimeOut_GetPlayMovieInfo(sessionID)
		retParam = SRetParam_GetPlayMovieInfo.new;
		onReturn_GetPlayMovieInfo(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 135;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_SelHPRateNotify' #FuncID: 1
		@recvFuncList[1] = '_doRecv_StatusNotify' #FuncID: 2
		@recvFuncList[2] = '_doRecv_VisitRoomStatusNotify' #FuncID: 3
		@recvFuncList[3] = '_doRecv_PlayerMoveNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_PathCollideNotify' #FuncID: 5
		@recvFuncList[5] = '_doRecv_GridCollideNotify' #FuncID: 6
		@recvFuncList[6] = '_doRecv_NewPlayerEnterNotify' #FuncID: 7
		@recvFuncList[7] = '_doRecv_NewTurnBeginNotify' #FuncID: 8
		@recvFuncList[8] = '_doRecv_PlayerChangeModelNotify' #FuncID: 9
		@recvFuncList[9] = '_doRecv_PlayerPrizeLogNotify' #FuncID: 10
		@recvFuncList[10] = '_doRecv_ChatNotify' #FuncID: 11
		@recvFuncList[11] = '_doRecv_PlayerUpdateNotify' #FuncID: 12
		@recvFuncList[12] = '_doRecv_KickViewNotify' #FuncID: 13
		@recvFuncList[13] = '_doRecv_KickPlayerNotify' #FuncID: 14

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_Reg' #FuncID: 1
		@retFuncList[1] = '_doReturn_GetMatchInfo' #FuncID: 2
		@retFuncList[2] = '_doReturn_GetMathSelInfo' #FuncID: 3
		@retFuncList[3] = '_doReturn_ChangeModel' #FuncID: 4
		@retFuncList[4] = '_doReturn_MoveSelect' #FuncID: 5
		@retFuncList[5] = '_doReturn_GetActInfo' #FuncID: 6
		@retFuncList[6] = '_doReturn_Chat' #FuncID: 7
		@retFuncList[7] = '_doReturn_GetRoomList' #FuncID: 8
		@retFuncList[8] = '_doReturn_EnterVisitRoom' #FuncID: 9
		@retFuncList[9] = '_doReturn_LeaveVisitRoom' #FuncID: 10
		@retFuncList[10] = '_doReturn_GetPlayMovieInfo' #FuncID: 11

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_Reg' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GetMatchInfo' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_GetMathSelInfo' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_ChangeModel' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_MoveSelect' #FuncID: 5
		@timeFuncList[5] = '_onTimeOut_GetActInfo' #FuncID: 6
		@timeFuncList[6] = '_onTimeOut_Chat' #FuncID: 7
		@timeFuncList[7] = '_onTimeOut_GetRoomList' #FuncID: 8
		@timeFuncList[8] = '_onTimeOut_EnterVisitRoom' #FuncID: 9
		@timeFuncList[9] = '_onTimeOut_LeaveVisitRoom' #FuncID: 10
		@timeFuncList[10] = '_onTimeOut_GetPlayMovieInfo' #FuncID: 11
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

