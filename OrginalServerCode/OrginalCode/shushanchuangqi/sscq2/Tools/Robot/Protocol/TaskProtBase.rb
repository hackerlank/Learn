#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    TaskProt.rb
#  Purpose:      任务协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#任务的结果
class ETaskResult
	ETASKSUCCEED = 0#成功
	ETASKNOTEXIST = 1#任务不存在
	ETASKALREADYACCEPT = 2#任务已经接取
	ETASKERRFINISH = 3#任务不能完成
	ETASKERRGIVEUP = 4#任务不能取消
	ETASKERRACCEPT = 5#接取任务失败
	ETASKERRPACKFULL = 6#背包已满错误
	ETASKERRREPEAT = 7#不能接取重复任务
	ETASKERRFULL = 8#已接任务数已满
	ETASKERRSEX = 9#性别错误
	ETASKERRPREPTASK = 10#前置任务
	ETASKERRLEVEL = 11#等级不符
	ETASKERRNOSELOPTAWARD = 12#未选取奖励
	ETASKERRMAP = 13#所在地图不符
	ETASKNODIAMOND = 14#钻石不足
	ETASKNOGIFTCOIN = 15#礼金不足
	ETASKNOFAMILY = 16#无家族
	ETASKNOGUILD = 17#无公会
	ETASKERRCAMP = 18#阵营不对
	ETASKNOREPUTION = 19#声望不够
	ETASKNOJOB = 20#职业限制
	ETASKNORACE = 21#种族限制
	ETASKNOGOLD = 22#仙石不足
	ETASKNOSLIVER = 23#银币不足
	ETASKGROUPFULL = 24#师门任务只能接一个
	ETASKYAMENFULL = 25#衙门任务只能接一个
	ETASKCIRCLEFULL = 26#环任务只能接一个
	ETASKERROTHER = 27#其它错误
end

#任务的状态
class ETaskState
	ETASKNONE = 0#无
	ETASKACCEPT = 1#任务已接取
	ETASKFAIL = 2#任务失败
	ETASKFINISH = 3#任务完成
end

#任务NPC的状态
class ENpcTaskState
	ENPCTASKNONE = 0#无
	ENPCTASKACCEPT = 1#任务可接取
	ENPCTASKUNFINISH = 2#任务未完成
	ENPCTASKSUBMIT = 3#任务可交付
	ENPCTASKFUTURE = 4#将来可接取
end

#结构体：STaskInfo的继承体系类型
class EType_STaskInfo
	ETYPE_STASKINFO = 0#类型：STaskInfo
	ETYPE_STASKCOLLECTINFO = 1#类型：STaskCollectInfo
	ETYPE_STASKGATHERINFO = 2#类型：STaskGatherInfo
	ETYPE_STASKMONSTERINFO = 3#类型：STaskMonsterInfo
	ETYPE_STASKTALKINFO = 4#类型：STaskTalkInfo
	ETYPE_STASKPROBEINFO = 5#类型：STaskProbeInfo
	ETYPE_STASKBUILDINFO = 6#类型：STaskBuildInfo
	ETYPE_STASKSCIENCEINFO = 7#类型：STaskScienceInfo
	ETYPE_STASKACTIONINFO = 8#类型：STaskActionInfo
	ETYPE_STASKGROWINFO = 9#类型：STaskGrowInfo
end

#任务信息
class STaskInfo
	#构造函数
	def initialize
	end

	#获取继承类的类型
	def getClassType
		return EType_STaskInfo::ETYPE_STASKINFO
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STaskInfo.new
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_STaskInfo::ETYPE_STASKINFO
				s = STaskInfo::fromStream(data)
			when EType_STaskInfo::ETYPE_STASKCOLLECTINFO
				s = STaskCollectInfo::fromStream(data)
			when EType_STaskInfo::ETYPE_STASKGATHERINFO
				s = STaskGatherInfo::fromStream(data)
			when EType_STaskInfo::ETYPE_STASKMONSTERINFO
				s = STaskMonsterInfo::fromStream(data)
			when EType_STaskInfo::ETYPE_STASKTALKINFO
				s = STaskTalkInfo::fromStream(data)
			when EType_STaskInfo::ETYPE_STASKPROBEINFO
				s = STaskProbeInfo::fromStream(data)
			when EType_STaskInfo::ETYPE_STASKBUILDINFO
				s = STaskBuildInfo::fromStream(data)
			when EType_STaskInfo::ETYPE_STASKSCIENCEINFO
				s = STaskScienceInfo::fromStream(data)
			when EType_STaskInfo::ETYPE_STASKACTIONINFO
				s = STaskActionInfo::fromStream(data)
			when EType_STaskInfo::ETYPE_STASKGROWINFO
				s = STaskGrowInfo::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STaskInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STaskInfo::superFromStream(data)
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

#收集道具的信息
class STaskCollectInfo < STaskInfo
	attr_accessor:wItemID #(UINT16)道具的ID
	attr_accessor:wItemCount #(UINT16)已搜集道具的数量

	#构造函数
	def initialize
		super()
		@wItemID = 0
		@wItemCount = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_STaskInfo::ETYPE_STASKCOLLECTINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wItemID = @wItemID
		obj.wItemCount = @wItemCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STaskCollectInfo.new
		base = STaskInfo::fromStream(data)
		s.wItemID = ByteUtil::readUINT16(data)
		s.wItemCount = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STaskCollectInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wItemID)
		ByteUtil::writeUINT16(data, @wItemCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#采集的信息
class STaskGatherInfo < STaskInfo
	attr_accessor:wGatherID #(UINT16)采集的ID
	attr_accessor:wCount #(UINT16)已采集的次数

	#构造函数
	def initialize
		super()
		@wGatherID = 0
		@wCount = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_STaskInfo::ETYPE_STASKGATHERINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wGatherID = @wGatherID
		obj.wCount = @wCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STaskGatherInfo.new
		base = STaskInfo::fromStream(data)
		s.wGatherID = ByteUtil::readUINT16(data)
		s.wCount = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STaskGatherInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wGatherID)
		ByteUtil::writeUINT16(data, @wCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#杀死怪物的信息
class STaskMonsterInfo < STaskInfo
	attr_accessor:wMonsterID #(UINT16)怪物的ID
	attr_accessor:wMonsterCount #(UINT16)已杀怪物的数量

	#构造函数
	def initialize
		super()
		@wMonsterID = 0
		@wMonsterCount = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_STaskInfo::ETYPE_STASKMONSTERINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wMonsterID = @wMonsterID
		obj.wMonsterCount = @wMonsterCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STaskMonsterInfo.new
		base = STaskInfo::fromStream(data)
		s.wMonsterID = ByteUtil::readUINT16(data)
		s.wMonsterCount = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STaskMonsterInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wMonsterID)
		ByteUtil::writeUINT16(data, @wMonsterCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#NPC的对话信息
class STaskTalkInfo < STaskInfo
	attr_accessor:wNpcID #(UINT16)NPC的ID
	attr_accessor:wTalkCount #(UINT16)0:未完成1:已完成

	#构造函数
	def initialize
		super()
		@wNpcID = 0
		@wTalkCount = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_STaskInfo::ETYPE_STASKTALKINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wNpcID = @wNpcID
		obj.wTalkCount = @wTalkCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STaskTalkInfo.new
		base = STaskInfo::fromStream(data)
		s.wNpcID = ByteUtil::readUINT16(data)
		s.wTalkCount = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STaskTalkInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wNpcID)
		ByteUtil::writeUINT16(data, @wTalkCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#探索区域信息
class STaskProbeInfo < STaskInfo
	attr_accessor:byIndex #(UINT8)探索区域索引
	attr_accessor:bProbed #(bool)是否已探索

	#构造函数
	def initialize
		super()
		@byIndex = 0
		@bProbed = false
	end

	#获取继承类的类型
	def getClassType
		return EType_STaskInfo::ETYPE_STASKPROBEINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.byIndex = @byIndex
		obj.bProbed = @bProbed
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STaskProbeInfo.new
		base = STaskInfo::fromStream(data)
		s.byIndex = ByteUtil::readUINT8(data)
		s.bProbed = ByteUtil::readBOOL(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STaskProbeInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT8(data, @byIndex)
		ByteUtil::writeBOOL(data, @bProbed)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#建筑的信息
class STaskBuildInfo < STaskInfo
	attr_accessor:wBuildID #(UINT16)建筑ID
	attr_accessor:wLevel #(UINT16)等级

	#构造函数
	def initialize
		super()
		@wBuildID = 0
		@wLevel = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_STaskInfo::ETYPE_STASKBUILDINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wBuildID = @wBuildID
		obj.wLevel = @wLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STaskBuildInfo.new
		base = STaskInfo::fromStream(data)
		s.wBuildID = ByteUtil::readUINT16(data)
		s.wLevel = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STaskBuildInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wBuildID)
		ByteUtil::writeUINT16(data, @wLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#科技的信息
class STaskScienceInfo < STaskInfo
	attr_accessor:wScienceID #(UINT16)科技ID
	attr_accessor:wLevel #(UINT16)等级

	#构造函数
	def initialize
		super()
		@wScienceID = 0
		@wLevel = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_STaskInfo::ETYPE_STASKSCIENCEINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wScienceID = @wScienceID
		obj.wLevel = @wLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STaskScienceInfo.new
		base = STaskInfo::fromStream(data)
		s.wScienceID = ByteUtil::readUINT16(data)
		s.wLevel = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STaskScienceInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wScienceID)
		ByteUtil::writeUINT16(data, @wLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#行为的信息
class STaskActionInfo < STaskInfo
	attr_accessor:wAction #(UINT16)行为类型
	attr_accessor:wCount #(UINT16)次数

	#构造函数
	def initialize
		super()
		@wAction = 0
		@wCount = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_STaskInfo::ETYPE_STASKACTIONINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wAction = @wAction
		obj.wCount = @wCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STaskActionInfo.new
		base = STaskInfo::fromStream(data)
		s.wAction = ByteUtil::readUINT16(data)
		s.wCount = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STaskActionInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wAction)
		ByteUtil::writeUINT16(data, @wCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#成长的信息
class STaskGrowInfo < STaskInfo
	attr_accessor:wType #(UINT16)成长类型
	attr_accessor:wLevel #(UINT16)等级

	#构造函数
	def initialize
		super()
		@wType = 0
		@wLevel = 0
	end

	#获取继承类的类型
	def getClassType
		return EType_STaskInfo::ETYPE_STASKGROWINFO
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wType = @wType
		obj.wLevel = @wLevel
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STaskGrowInfo.new
		base = STaskInfo::fromStream(data)
		s.wType = ByteUtil::readUINT16(data)
		s.wLevel = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STaskGrowInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		ByteUtil::writeUINT16(data, @wType)
		ByteUtil::writeUINT16(data, @wLevel)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#任务的属性
class STask
	attr_accessor:wTaskID #(UINT16)任务的ID
	attr_accessor:eTaskState #(枚举类型：ETaskState)任务的状态
	attr_accessor:dwAcceptTime #(UINT32)接取时间
	attr_accessor:byRepeat #(UINT8)同时接取数
	attr_accessor:vecTaskInfo #(STaskInfo的数组)任务信息列表

	#构造函数
	def initialize
		@wTaskID = 0
		@eTaskState = 0
		@dwAcceptTime = 0
		@byRepeat = 0
		@vecTaskInfo = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.wTaskID = @wTaskID
		obj.eTaskState = @eTaskState
		obj.dwAcceptTime = @dwAcceptTime
		obj.byRepeat = @byRepeat
		obj.vecTaskInfo = @vecTaskInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = STask.new
		s.wTaskID = ByteUtil::readUINT16(data)
		s.eTaskState = ByteUtil::readUINT8(data)
		s.dwAcceptTime = ByteUtil::readUINT32(data)
		s.byRepeat = ByteUtil::readUINT8(data)
		s.vecTaskInfo = STaskInfo::superVectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = STask::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT16(data, @wTaskID)
		ByteUtil::writeUINT8(data, @eTaskState)
		ByteUtil::writeUINT32(data, @dwAcceptTime)
		ByteUtil::writeUINT8(data, @byRepeat)
		STaskInfo::superVectorToStream(data, @vecTaskInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#函数[AcceptTaskReq:接受任务请求]的返回的参数组成的结构体
class SRetParam_AcceptTaskReq
	attr_accessor:eResult#(枚举类型：ETaskResult)接受任务的结果
	attr_accessor:byCost#(UINT8)参数回传
	attr_accessor:wTaskID#(UINT16)任务ID

	#构造函数
	def initialize
		@eResult = 0
		@byCost = 0
		@wTaskID = 0
	end
end

#函数[GiveUpTask:放弃任务请求]的返回的参数组成的结构体
class SRetParam_GiveUpTask
	attr_accessor:eResult#(枚举类型：ETaskResult)放弃任务的结果
	attr_accessor:wTaskID#(UINT16)任务ID

	#构造函数
	def initialize
		@eResult = 0
		@wTaskID = 0
	end
end

#函数[FinishTask:完成任务请求(领取奖励)]的返回的参数组成的结构体
class SRetParam_FinishTask
	attr_accessor:eResult#(枚举类型：ETaskResult)完成任务的结果
	attr_accessor:byCost#(UINT8)参数回传
	attr_accessor:wTaskID#(UINT16)任务ID

	#构造函数
	def initialize
		@eResult = 0
		@byCost = 0
		@wTaskID = 0
	end
end

#函数[FinishCircleTaskOneKey:完成所有的环任务]的返回的参数组成的结构体
class SRetParam_FinishCircleTaskOneKey
	attr_accessor:eResult#(枚举类型：ETaskResult)完成任务的结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#函数[UpdateCircleTaskStar:提升环任务星级]的返回的参数组成的结构体
class SRetParam_UpdateCircleTaskStar
	attr_accessor:eResult#(枚举类型：ETaskResult)完成任务的结果

	#构造函数
	def initialize
		@eResult = 0
	end
end

#协议类：任务协议
class TaskProtBase < ProtocolBase
	#以下为发送函数
	#发送：接受任务请求
	def send_AcceptTaskReq(
		byCost,  #(UINT8)0,正常提交，1，付费提交，限未完成任务,支持师门,衙门任务
		wTaskID #(UINT16)任务ID
	)
		sessionID = @sessionMgr.getNewSession(self, 1);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byCost)
		ByteUtil::writeUINT16(data, wTaskID)
		return @svrHandler.sendPacket(data)
	end

	#发送：放弃任务请求
	def send_GiveUpTask(
		wTaskID #(UINT16)任务ID
	)
		sessionID = @sessionMgr.getNewSession(self, 2);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT16(data, wTaskID)
		return @svrHandler.sendPacket(data)
	end

	#发送：完成任务请求(领取奖励)
	def send_FinishTask(
		byCost,  #(UINT8)0,正常提交，1，付费提交，限未完成任务,支持师门,衙门任务
		wTaskID,  #(UINT16)任务ID
		byIndex #(UINT8)可选择的奖励索引
	)
		sessionID = @sessionMgr.getNewSession(self, 3);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		ByteUtil::writeUINT8(data, byCost)
		ByteUtil::writeUINT16(data, wTaskID)
		ByteUtil::writeUINT8(data, byIndex)
		return @svrHandler.sendPacket(data)
	end

	#发送：完成特殊任务请求
	def send_FinishSpeTask(
		wTaskID #(UINT16)任务ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT16(data, wTaskID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得任务列表
	def send_GetTaskList(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：获得环任务信息
	def send_GetCircleTaskInfo(
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		return @svrHandler.sendPacket(data)
	end

	#发送：完成所有的环任务
	def send_FinishCircleTaskOneKey(
	)
		sessionID = @sessionMgr.getNewSession(self, 4);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 7
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

	#发送：提升环任务星级
	def send_UpdateCircleTaskStar(
	)
		sessionID = @sessionMgr.getNewSession(self, 5);
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 8
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, sessionID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：任务列表通知
	def onRecv_TaskListNtf(
		vecTask #(STask的数组)任务列表
	)
		raise NotImplementedError
	end
	#接收：任务更新通知
	def onRecv_TaskUpdateNtf(
		rTask #(类类型：STask)任务
	)
		raise NotImplementedError
	end
	#接收：删除任务
	def onRecv_DelTaskAck(
		wTaskID #(UINT16)任务ID
	)
		raise NotImplementedError
	end
	#接收：添加任务
	def onRecv_AddTaskAck(
		byCost, #(UINT8)立即完成
		rTask #(类类型：STask)任务
	)
		raise NotImplementedError
	end
	#接收：任务记录
	def onRecv_NotifyTaskRecordAck(
		vecTaskID #(UINT16数组)任务完成记录
	)
		raise NotImplementedError
	end
	#接收：通知播放剧情
	def onRecv_NotifyStory(
		wStoryID, #(UINT16)剧情ID
		byType, #(UINT8)参数类型
		dwParam #(UINT32)参数
	)
		raise NotImplementedError
	end
	#接收：通知环任务信息
	def onRecv_SendCircleTaskInfo(
		byStar, #(UINT8)环任务星级
		byNum #(UINT8)环任务环数
	)
		raise NotImplementedError
	end
#以下的返回函数需要重载
	#返回：接受任务请求
	def onReturn_AcceptTaskReq(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_AcceptTaskReq)返回的参数
	)
	end

	#返回：放弃任务请求
	def onReturn_GiveUpTask(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_GiveUpTask)返回的参数
	)
	end

	#返回：完成任务请求(领取奖励)
	def onReturn_FinishTask(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FinishTask)返回的参数
	)
	end

	#返回：完成所有的环任务
	def onReturn_FinishCircleTaskOneKey(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_FinishCircleTaskOneKey)返回的参数
	)
	end

	#返回：提升环任务星级
	def onReturn_UpdateCircleTaskStar(
		ret, #0为成功，1为失败，2为超时
		retParam #(类类型：SRetParam_UpdateCircleTaskStar)返回的参数
	)
	end

#以下为接收处理函数
	#接收处理：任务列表通知
	def _doRecv_TaskListNtf(data)
		vecTask = STask::vectorFromStream(data)
		return onRecv_TaskListNtf(vecTask)
	end

	#接收处理：任务更新通知
	def _doRecv_TaskUpdateNtf(data)
		rTask = STask::fromStream(data)
		return onRecv_TaskUpdateNtf(rTask)
	end

	#接收处理：删除任务
	def _doRecv_DelTaskAck(data)
		wTaskID = ByteUtil::readUINT16(data)
		return onRecv_DelTaskAck(wTaskID)
	end

	#接收处理：添加任务
	def _doRecv_AddTaskAck(data)
		byCost = ByteUtil::readUINT8(data)
		rTask = STask::fromStream(data)
		return onRecv_AddTaskAck(byCost, rTask)
	end

	#接收处理：任务记录
	def _doRecv_NotifyTaskRecordAck(data)
		vecTaskID = ByteUtil::readVecUINT16(data)
		return onRecv_NotifyTaskRecordAck(vecTaskID)
	end

	#接收处理：通知播放剧情
	def _doRecv_NotifyStory(data)
		wStoryID = ByteUtil::readUINT16(data)
		byType = ByteUtil::readUINT8(data)
		dwParam = ByteUtil::readUINT32(data)
		return onRecv_NotifyStory(wStoryID, byType, dwParam)
	end

	#接收处理：通知环任务信息
	def _doRecv_SendCircleTaskInfo(data)
		byStar = ByteUtil::readUINT8(data)
		byNum = ByteUtil::readUINT8(data)
		return onRecv_SendCircleTaskInfo(byStar, byNum)
	end

#以下为返回处理函数
	#返回处理：接受任务请求
	def _doReturn_AcceptTaskReq(data)
		retParam = SRetParam_AcceptTaskReq.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETaskResult)接受任务的结果
		byCost = ByteUtil::readUINT8(data) #(UINT8)参数回传
		wTaskID = ByteUtil::readUINT16(data) #(UINT16)任务ID
		retParam.eResult = eResult
		retParam.byCost = byCost
		retParam.wTaskID = wTaskID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_AcceptTaskReq(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：接受任务请求
	def _onTimeOut_AcceptTaskReq(sessionID)
		retParam = SRetParam_AcceptTaskReq.new;
		onReturn_AcceptTaskReq(2, retParam)
	end

	#返回处理：放弃任务请求
	def _doReturn_GiveUpTask(data)
		retParam = SRetParam_GiveUpTask.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETaskResult)放弃任务的结果
		wTaskID = ByteUtil::readUINT16(data) #(UINT16)任务ID
		retParam.eResult = eResult
		retParam.wTaskID = wTaskID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_GiveUpTask(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：放弃任务请求
	def _onTimeOut_GiveUpTask(sessionID)
		retParam = SRetParam_GiveUpTask.new;
		onReturn_GiveUpTask(2, retParam)
	end

	#返回处理：完成任务请求(领取奖励)
	def _doReturn_FinishTask(data)
		retParam = SRetParam_FinishTask.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETaskResult)完成任务的结果
		byCost = ByteUtil::readUINT8(data) #(UINT8)参数回传
		wTaskID = ByteUtil::readUINT16(data) #(UINT16)任务ID
		retParam.eResult = eResult
		retParam.byCost = byCost
		retParam.wTaskID = wTaskID
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FinishTask(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：完成任务请求(领取奖励)
	def _onTimeOut_FinishTask(sessionID)
		retParam = SRetParam_FinishTask.new;
		onReturn_FinishTask(2, retParam)
	end

	#返回处理：完成所有的环任务
	def _doReturn_FinishCircleTaskOneKey(data)
		retParam = SRetParam_FinishCircleTaskOneKey.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETaskResult)完成任务的结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_FinishCircleTaskOneKey(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：完成所有的环任务
	def _onTimeOut_FinishCircleTaskOneKey(sessionID)
		retParam = SRetParam_FinishCircleTaskOneKey.new;
		onReturn_FinishCircleTaskOneKey(2, retParam)
	end

	#返回处理：提升环任务星级
	def _doReturn_UpdateCircleTaskStar(data)
		retParam = SRetParam_UpdateCircleTaskStar.new
		sessionID = ByteUtil::readUINT32(data)
		retVal = ByteUtil::readBOOL(data)
		eResult = ByteUtil::readUINT8(data) #(枚举类型：ETaskResult)完成任务的结果
		retParam.eResult = eResult
		ret = 0
		if(!retVal)
			ret = 1
		end
		result = onReturn_UpdateCircleTaskStar(ret, retParam)
		@sessionMgr.delSession(sessionID)
		return result
	end

	#超时处理：提升环任务星级
	def _onTimeOut_UpdateCircleTaskStar(sessionID)
		retParam = SRetParam_UpdateCircleTaskStar.new;
		onReturn_UpdateCircleTaskStar(2, retParam)
	end

	#以下为协议接口
	@recvFuncList
	@retFuncList
	@timeFuncList

	def initialize
		@protID = 15;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_TaskListNtf' #FuncID: 1
		@recvFuncList[1] = '_doRecv_TaskUpdateNtf' #FuncID: 2
		@recvFuncList[2] = '_doRecv_DelTaskAck' #FuncID: 3
		@recvFuncList[3] = '_doRecv_AddTaskAck' #FuncID: 4
		@recvFuncList[4] = '_doRecv_NotifyTaskRecordAck' #FuncID: 5
		@recvFuncList[5] = '_doRecv_NotifyStory' #FuncID: 6
		@recvFuncList[6] = '_doRecv_SendCircleTaskInfo' #FuncID: 7

		@retFuncList = Array.new
		@retFuncList[0] = '_doReturn_AcceptTaskReq' #FuncID: 1
		@retFuncList[1] = '_doReturn_GiveUpTask' #FuncID: 2
		@retFuncList[2] = '_doReturn_FinishTask' #FuncID: 3
		@retFuncList[3] = '_doReturn_FinishCircleTaskOneKey' #FuncID: 4
		@retFuncList[4] = '_doReturn_UpdateCircleTaskStar' #FuncID: 5

		@timeFuncList = Array.new
		@timeFuncList[0] = '_onTimeOut_AcceptTaskReq' #FuncID: 1
		@timeFuncList[1] = '_onTimeOut_GiveUpTask' #FuncID: 2
		@timeFuncList[2] = '_onTimeOut_FinishTask' #FuncID: 3
		@timeFuncList[3] = '_onTimeOut_FinishCircleTaskOneKey' #FuncID: 4
		@timeFuncList[4] = '_onTimeOut_UpdateCircleTaskStar' #FuncID: 5
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

