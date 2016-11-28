#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    MailProt.rb
#  Purpose:      邮件CenterServer通讯协议
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'
require_relative './ItemProtBase.rb'

#以下为类型定义

#邮件状态
class EMailQueryType
	EQUERYNEW = 0#新邮件
	EQUERYREADED = 1#已读
	EQUERYTOTAL = 2#全部
	EQUERYPERSON = 3#个人
	EQUERYSYSTEM = 4#系统
	EQUERYATTCH = 5#附件
end

#邮件状态
class EMailState
	ESTATENEW = 0#新邮件
	ESTATEREADED = 1#已读
	ESTATEDELETE = 2#已删
end

#邮件状态
class EMailErrorResult
	EMAIL_SENDOK = 1#发送成功
	EMAIL_SENDFAIL = 2#发送失败
	EMAIL_DELETEOK = 3#删除成功
	EMAIL_DELETEFAIL = 4#删除失败
	EMAIL_OVERMAXCOUNT = 5#超过最大上限
end

#邮件类型
class EMailType
	EMAILTYPE_NORMAL = 0#普通邮件
	EMAILTYPE_SYSTEM = 1#系统邮件
end

#附件类型
class EMailAttachType
	ATTACH_ITEM = 0#有模板物品
	ATTACH_INSTANCE = 1#有实例物品
	ATTACH_MAX = 255#不当位处理，作为附件已经领取的特殊标记
end

#附件提取结果
class EMailDRawResult
	DRAW_SUC = 0#提取成功
	PACK_FULL = 1#包裹满
end

#结构体：SMailBaseAttachment的继承体系类型
class EType_SMailBaseAttachment
	ETYPE_SMAILBASEATTACHMENT = 0#类型：SMailBaseAttachment
	ETYPE_SITEMATTACHMENT = 1#类型：SItemAttachment
	ETYPE_SITEMBASECT = 2#类型：SItemBaseCT
end

#系统邮件标题，及其内容
class SysMailSendTxt
	attr_accessor:dwstrMsgID #(UINT32)消息ID
	attr_accessor:vecParam #(string数组)参数列表

	#构造函数
	def initialize
		@dwstrMsgID = 0
		@vecParam = Array.new
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwstrMsgID = @dwstrMsgID
		obj.vecParam = @vecParam
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SysMailSendTxt.new
		s.dwstrMsgID = ByteUtil::readUINT32(data)
		s.vecParam = ByteUtil::readVecSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SysMailSendTxt::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwstrMsgID)
		ByteUtil::writeVecSTRING(data, @vecParam)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#邮件摘要列表
class SMailSummary
	attr_accessor:uMailID #(UINT64)邮件ID
	attr_accessor:eMailType #(枚举类型：EMailType)邮件类型
	attr_accessor:eMailState #(枚举类型：EMailState)邮件状态
	attr_accessor:uSendTime #(UINT32)邮件发送时间
	attr_accessor:byHasAttachment #(UINT8)0:没有   1:有
	attr_accessor:strTitle #(string)邮件标题
	attr_accessor:strSendName #(string)发送者

	#构造函数
	def initialize
		@uMailID = 0
		@eMailType = 0
		@eMailState = 0
		@uSendTime = 0
		@byHasAttachment = 0
		@strTitle = ''
		@strSendName = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.uMailID = @uMailID
		obj.eMailType = @eMailType
		obj.eMailState = @eMailState
		obj.uSendTime = @uSendTime
		obj.byHasAttachment = @byHasAttachment
		obj.strTitle = @strTitle
		obj.strSendName = @strSendName
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMailSummary.new
		s.uMailID = ByteUtil::readUINT64(data)
		s.eMailType = ByteUtil::readUINT8(data)
		s.eMailState = ByteUtil::readUINT8(data)
		s.uSendTime = ByteUtil::readUINT32(data)
		s.byHasAttachment = ByteUtil::readUINT8(data)
		s.strTitle = ByteUtil::readSTRING(data)
		s.strSendName = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMailSummary::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @uMailID)
		ByteUtil::writeUINT8(data, @eMailType)
		ByteUtil::writeUINT8(data, @eMailState)
		ByteUtil::writeUINT32(data, @uSendTime)
		ByteUtil::writeUINT8(data, @byHasAttachment)
		ByteUtil::writeSTRING(data, @strTitle)
		ByteUtil::writeSTRING(data, @strSendName)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#道具格式
class SMailItemInfo
	attr_accessor:qwInstID #(UINT64)道具类型ID
	attr_accessor:wItemID #(UINT32)物品模板
	attr_accessor:eItemQuelity #(枚类型：ItemProt::EItemQuality)物品品质
	attr_accessor:wCount #(UINT32)道具数量
	attr_accessor:eBindType #(枚类型：ItemProt::EBindType)绑定类型
	attr_accessor:byExpired #(UINT8)是否时效，>0 时效物品
	attr_accessor:dwExpireTime #(UINT32)过期时间
	attr_accessor:qwOPID #(UINT64)操作ID

	#构造函数
	def initialize
		@qwInstID = 0
		@wItemID = 0
		@eItemQuelity = 0
		@wCount = 0
		@eBindType = 0
		@byExpired = 0
		@dwExpireTime = 0
		@qwOPID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwInstID = @qwInstID
		obj.wItemID = @wItemID
		obj.eItemQuelity = @eItemQuelity
		obj.wCount = @wCount
		obj.eBindType = @eBindType
		obj.byExpired = @byExpired
		obj.dwExpireTime = @dwExpireTime
		obj.qwOPID = @qwOPID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMailItemInfo.new
		s.qwInstID = ByteUtil::readUINT64(data)
		s.wItemID = ByteUtil::readUINT32(data)
		s.eItemQuelity = ByteUtil::readUINT8(data)
		s.wCount = ByteUtil::readUINT32(data)
		s.eBindType = ByteUtil::readUINT8(data)
		s.byExpired = ByteUtil::readUINT8(data)
		s.dwExpireTime = ByteUtil::readUINT32(data)
		s.qwOPID = ByteUtil::readUINT64(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMailItemInfo::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwInstID)
		ByteUtil::writeUINT32(data, @wItemID)
		ByteUtil::writeUINT8(data, @eItemQuelity)
		ByteUtil::writeUINT32(data, @wCount)
		ByteUtil::writeUINT8(data, @eBindType)
		ByteUtil::writeUINT8(data, @byExpired)
		ByteUtil::writeUINT32(data, @dwExpireTime)
		ByteUtil::writeUINT64(data, @qwOPID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#邮件附件
class SMailBaseAttachment
	#构造函数
	def initialize
	end

	#获取继承类的类型
	def getClassType
		return EType_SMailBaseAttachment::ETYPE_SMAILBASEATTACHMENT
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMailBaseAttachment.new
		return s
	end

	def self.superFromStream(data)
		eType = ByteUtil::readUINT8(data)
		case eType
			when EType_SMailBaseAttachment::ETYPE_SMAILBASEATTACHMENT
				s = SMailBaseAttachment::fromStream(data)
			when EType_SMailBaseAttachment::ETYPE_SITEMATTACHMENT
				s = SItemAttachment::fromStream(data)
			when EType_SMailBaseAttachment::ETYPE_SITEMBASECT
				s = SItemBaseCT::fromStream(data)
		end
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMailBaseAttachment::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def self.superVectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMailBaseAttachment::superFromStream(data)
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

#物品附件
class SItemAttachment < SMailBaseAttachment
	attr_accessor:vecItemInfo #(SMailItemInfo的数组)物品

	#构造函数
	def initialize
		super()
		@vecItemInfo = Array.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SMailBaseAttachment::ETYPE_SITEMATTACHMENT
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.vecItemInfo = @vecItemInfo
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SItemAttachment.new
		base = SMailBaseAttachment::fromStream(data)
		s.vecItemInfo = SMailItemInfo::vectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SItemAttachment::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		SMailItemInfo::vectorToStream(data, @vecItemInfo)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#物品附件:具体物品对象
class SItemBaseCT < SMailBaseAttachment
	attr_accessor:vecItems #(SItem的数组)物品

	#构造函数
	def initialize
		super()
		@vecItems = Array.new
	end

	#获取继承类的类型
	def getClassType
		return EType_SMailBaseAttachment::ETYPE_SITEMBASECT
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.vecItems = @vecItems
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SItemBaseCT.new
		base = SMailBaseAttachment::fromStream(data)
		s.vecItems = SItem::superVectorFromStream(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SItemBaseCT::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		super::toStream(data)
		SItem::superVectorToStream(data, @vecItems)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#邮件详细信息
class SMailDetail
	attr_accessor:qwMailID #(UINT64)邮件ID
	attr_accessor:eMailState #(枚举类型：EMailState)邮件状态
	attr_accessor:dwSendTime #(UINT32)邮件发送时间
	attr_accessor:byGeted #(UINT8)255表示有附件，并且已经领取，其他为按位表示有附件的类型
	attr_accessor:eMailType #(枚举类型：EMailType)邮件类型
	attr_accessor:vecMailAttachment #(SMailBaseAttachment的数组)附件
	attr_accessor:strTitle #(string)邮件标题
	attr_accessor:strSendName #(string)发送者
	attr_accessor:strMessage #(string)信息

	#构造函数
	def initialize
		@qwMailID = 0
		@eMailState = 0
		@dwSendTime = 0
		@byGeted = 0
		@eMailType = 0
		@vecMailAttachment = Array.new
		@strTitle = ''
		@strSendName = ''
		@strMessage = ''
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.qwMailID = @qwMailID
		obj.eMailState = @eMailState
		obj.dwSendTime = @dwSendTime
		obj.byGeted = @byGeted
		obj.eMailType = @eMailType
		obj.vecMailAttachment = @vecMailAttachment
		obj.strTitle = @strTitle
		obj.strSendName = @strSendName
		obj.strMessage = @strMessage
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SMailDetail.new
		s.qwMailID = ByteUtil::readUINT64(data)
		s.eMailState = ByteUtil::readUINT8(data)
		s.dwSendTime = ByteUtil::readUINT32(data)
		s.byGeted = ByteUtil::readUINT8(data)
		s.eMailType = ByteUtil::readUINT8(data)
		s.vecMailAttachment = SMailBaseAttachment::superVectorFromStream(data)
		s.strTitle = ByteUtil::readSTRING(data)
		s.strSendName = ByteUtil::readSTRING(data)
		s.strMessage = ByteUtil::readSTRING(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SMailDetail::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @qwMailID)
		ByteUtil::writeUINT8(data, @eMailState)
		ByteUtil::writeUINT32(data, @dwSendTime)
		ByteUtil::writeUINT8(data, @byGeted)
		ByteUtil::writeUINT8(data, @eMailType)
		SMailBaseAttachment::superVectorToStream(data, @vecMailAttachment)
		ByteUtil::writeSTRING(data, @strTitle)
		ByteUtil::writeSTRING(data, @strSendName)
		ByteUtil::writeSTRING(data, @strMessage)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#协议类：邮件CenterServer通讯协议
class MailProtBase < ProtocolBase
	#以下为发送函数
	#发送：邮件ID请求
	def send_MailPageIDReq(
		uStartIndex,  #(UINT32)请求开始序号
		uiMailNum,  #(UINT32)请求邮件数量
		eQueryType #(枚举类型：EMailQueryType)邮件类型
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 1
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT32(data, uStartIndex)
		ByteUtil::writeUINT32(data, uiMailNum)
		ByteUtil::writeUINT8(data, eQueryType)
		return @svrHandler.sendPacket(data)
	end

	#发送：页邮件列表信息请求
	def send_MailSummaryListReq(
		vecMailIDList #(UINT64数组)请求ID列表
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 2
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeVecUINT64(data, vecMailIDList)
		return @svrHandler.sendPacket(data)
	end

	#发送：单邮件信息请求
	def send_MailDetailReq(
		uiMailID #(UINT64)邮件ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 3
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, uiMailID)
		return @svrHandler.sendPacket(data)
	end

	#发送：发送邮件
	def send_SendMail(
		strReceiveName,  #(string)接受者姓名
		strTitle,  #(string)邮件标题
		strMsg #(string)邮件内容
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 4
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeSTRING(data, strReceiveName)
		ByteUtil::writeSTRING(data, strTitle)
		ByteUtil::writeSTRING(data, strMsg)
		return @svrHandler.sendPacket(data)
	end

	#发送：删除邮件
	def send_DeleteMail(
		vecMailIDList #(UINT64数组)请求ID列表
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 5
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeVecUINT64(data, vecMailIDList)
		return @svrHandler.sendPacket(data)
	end

	#发送：收取附件
	def send_MailAttachmentGetReq(
		qwMailID #(UINT64)邮件ID
	)
		data = ''
		ByteUtil::writeINT8(data, @protID)
		funcID = 6
		ByteUtil::writeINT8(data, funcID)
		ByteUtil::writeUINT64(data, qwMailID)
		return @svrHandler.sendPacket(data)
	end

#以下的接收函数需要重载
	#接收：页邮件ID回答
	def onRecv_MailPageIDAck(
		vecMailIDList, #(UINT64数组)页面ID列表
		uStartIndex, #(UINT32)当前请求索引
		uMailTotalNum, #(UINT32)邮件总数量
		eQueryType #(枚举类型：EMailQueryType)邮件类型
	)
		raise NotImplementedError
	end
	#接收：页邮件列表信息回答
	def onRecv_MailSummaryListAck(
		vecMailList #(SMailSummary的数组)邮件列表
	)
		raise NotImplementedError
	end
	#接收：页邮件列表信息回答
	def onRecv_MailDetailAck(
		rMailDetail #(类类型：SMailDetail)邮件详细信息
	)
		raise NotImplementedError
	end
	#接收：新邮件通知
	def onRecv_NewMailNotify(
		byIsFrameNotify #(UINT8)1:需要弹框显示 0:不需要弹框显示(邮件闪烁)
	)
		raise NotImplementedError
	end
	#接收：邮件发送结果
	def onRecv_MailSendResult(
		eErrorResult #(枚举类型：EMailErrorResult)返回结果
	)
		raise NotImplementedError
	end
	#接收：邮件发送结果
	def onRecv_MailDeleteResult(
		vecMailIDList, #(UINT64数组)请求ID列表
		eErrorResult #(枚举类型：EMailErrorResult)返回结果
	)
		raise NotImplementedError
	end
	#接收：收取附件结果
	def onRecv_MailAttachmentGetAck(
		qwMailID, #(UINT64)邮件ID
		eReSult #(枚举类型：EMailDRawResult)提取附件结果
	)
		raise NotImplementedError
	end
#以下为接收处理函数
	#接收处理：页邮件ID回答
	def _doRecv_MailPageIDAck(data)
		vecMailIDList = ByteUtil::readVecUINT64(data)
		uStartIndex = ByteUtil::readUINT32(data)
		uMailTotalNum = ByteUtil::readUINT32(data)
		eQueryType = ByteUtil::readUINT8(data)
		return onRecv_MailPageIDAck(vecMailIDList, uStartIndex, uMailTotalNum, eQueryType)
	end

	#接收处理：页邮件列表信息回答
	def _doRecv_MailSummaryListAck(data)
		vecMailList = SMailSummary::vectorFromStream(data)
		return onRecv_MailSummaryListAck(vecMailList)
	end

	#接收处理：页邮件列表信息回答
	def _doRecv_MailDetailAck(data)
		rMailDetail = SMailDetail::fromStream(data)
		return onRecv_MailDetailAck(rMailDetail)
	end

	#接收处理：新邮件通知
	def _doRecv_NewMailNotify(data)
		byIsFrameNotify = ByteUtil::readUINT8(data)
		return onRecv_NewMailNotify(byIsFrameNotify)
	end

	#接收处理：邮件发送结果
	def _doRecv_MailSendResult(data)
		eErrorResult = ByteUtil::readUINT8(data)
		return onRecv_MailSendResult(eErrorResult)
	end

	#接收处理：邮件发送结果
	def _doRecv_MailDeleteResult(data)
		vecMailIDList = ByteUtil::readVecUINT64(data)
		eErrorResult = ByteUtil::readUINT8(data)
		return onRecv_MailDeleteResult(vecMailIDList, eErrorResult)
	end

	#接收处理：收取附件结果
	def _doRecv_MailAttachmentGetAck(data)
		qwMailID = ByteUtil::readUINT64(data)
		eReSult = ByteUtil::readUINT8(data)
		return onRecv_MailAttachmentGetAck(qwMailID, eReSult)
	end

	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 19;
		@recvFuncList = Array.new
		@recvFuncList[0] = '_doRecv_MailPageIDAck' #FuncID: 1
		@recvFuncList[1] = '_doRecv_MailSummaryListAck' #FuncID: 2
		@recvFuncList[2] = '_doRecv_MailDetailAck' #FuncID: 3
		@recvFuncList[3] = '_doRecv_NewMailNotify' #FuncID: 4
		@recvFuncList[4] = '_doRecv_MailSendResult' #FuncID: 5
		@recvFuncList[5] = '_doRecv_MailDeleteResult' #FuncID: 6
		@recvFuncList[6] = '_doRecv_MailAttachmentGetAck' #FuncID: 7
	end

	def handleMessage(data)
		funcID = ByteUtil::readINT8(data);
		if funcID == 0 || funcID > @recvFuncList.length
			return false
		end
		if funcID > 0 
			func = @recvFuncList[funcID - 1]
		end
		if func
			 send(func, data)
		end
		#if func != nil
			#return call_user_func(Array.new(self, func), data)
		#end
		return true
	end
end

