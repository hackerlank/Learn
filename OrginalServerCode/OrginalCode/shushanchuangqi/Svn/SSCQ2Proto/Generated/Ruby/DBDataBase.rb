#************************************************************************
#  工具自动生成的Ruby客户端协议代码
#  File Name:    DBData.rb
#  Purpose:      数据库序列化结构
#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
#*************************************************************************/

require_relative '../core/ByteUtil.rb'
require_relative '../core/ProtocolBase.rb'

#以下为类型定义

#帐号基本数据
class SUserPropStream
	attr_accessor:dwGoldCoin #(UINT32)仙石
	attr_accessor:dwHonour #(UINT32)荣誉
	attr_accessor:byCamp #(UINT8)阵营
	attr_accessor:dwLastLeaveTime #(UINT32)最后一次下线时间

	#构造函数
	def initialize
		@dwGoldCoin = 0
		@dwHonour = 0
		@byCamp = 0
		@dwLastLeaveTime = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwGoldCoin = @dwGoldCoin
		obj.dwHonour = @dwHonour
		obj.byCamp = @byCamp
		obj.dwLastLeaveTime = @dwLastLeaveTime
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SUserPropStream.new
		s.dwGoldCoin = ByteUtil::readUINT32(data)
		s.dwHonour = ByteUtil::readUINT32(data)
		s.byCamp = ByteUtil::readUINT8(data)
		s.dwLastLeaveTime = ByteUtil::readUINT32(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SUserPropStream::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwGoldCoin)
		ByteUtil::writeUINT32(data, @dwHonour)
		ByteUtil::writeUINT8(data, @byCamp)
		ByteUtil::writeUINT32(data, @dwLastLeaveTime)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#角色基本数据(战斗相关)
class SBasePropStream
	attr_accessor:dwCurHP #(UINT32)当前HP
	attr_accessor:dwCurMP #(UINT32)当前MP
	attr_accessor:byElement #(UINT8)元素属性
	attr_accessor:wUseTitleID #(UINT16)当前使用称号
	attr_accessor:wUseHorseID #(UINT16)当前骑乘坐骑

	#构造函数
	def initialize
		@dwCurHP = 0
		@dwCurMP = 0
		@byElement = 0
		@wUseTitleID = 0
		@wUseHorseID = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwCurHP = @dwCurHP
		obj.dwCurMP = @dwCurMP
		obj.byElement = @byElement
		obj.wUseTitleID = @wUseTitleID
		obj.wUseHorseID = @wUseHorseID
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SBasePropStream.new
		s.dwCurHP = ByteUtil::readUINT32(data)
		s.dwCurMP = ByteUtil::readUINT32(data)
		s.byElement = ByteUtil::readUINT8(data)
		s.wUseTitleID = ByteUtil::readUINT16(data)
		s.wUseHorseID = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SBasePropStream::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwCurHP)
		ByteUtil::writeUINT32(data, @dwCurMP)
		ByteUtil::writeUINT8(data, @byElement)
		ByteUtil::writeUINT16(data, @wUseTitleID)
		ByteUtil::writeUINT16(data, @wUseHorseID)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#角色附加数据
class SExtPropStream
	attr_accessor:dwExp #(UINT32)经验
	attr_accessor:dwDgnInstID #(UINT32)副本实例ID
	attr_accessor:dwDgnCreateTime #(UINT32)副本创建时间
	attr_accessor:wPreDgnMapID #(UINT16)进入副本之前的地图ID
	attr_accessor:fPreDgnX #(float)进入副本之前的X坐标
	attr_accessor:fPreDgnY #(float)进入副本之前的Y坐标

	#构造函数
	def initialize
		@dwExp = 0
		@dwDgnInstID = 0
		@dwDgnCreateTime = 0
		@wPreDgnMapID = 0
		@fPreDgnX = 0
		@fPreDgnY = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwExp = @dwExp
		obj.dwDgnInstID = @dwDgnInstID
		obj.dwDgnCreateTime = @dwDgnCreateTime
		obj.wPreDgnMapID = @wPreDgnMapID
		obj.fPreDgnX = @fPreDgnX
		obj.fPreDgnY = @fPreDgnY
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SExtPropStream.new
		s.dwExp = ByteUtil::readUINT32(data)
		s.dwDgnInstID = ByteUtil::readUINT32(data)
		s.dwDgnCreateTime = ByteUtil::readUINT32(data)
		s.wPreDgnMapID = ByteUtil::readUINT16(data)
		s.fPreDgnX = ByteUtil::readFLOAT(data)
		s.fPreDgnY = ByteUtil::readFLOAT(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SExtPropStream::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT32(data, @dwExp)
		ByteUtil::writeUINT32(data, @dwDgnInstID)
		ByteUtil::writeUINT32(data, @dwDgnCreateTime)
		ByteUtil::writeUINT16(data, @wPreDgnMapID)
		ByteUtil::writeFLOAT(data, @fPreDgnX)
		ByteUtil::writeFLOAT(data, @fPreDgnY)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#各种槽（物品槽，心法槽）
class SSlotPropStream
	attr_accessor:dwRoleID #(UINT64)角色ID
	attr_accessor:dwOwnerID #(UINT64)拥有者实例ID
	attr_accessor:byStoreType #(UINT8)槽类型
	attr_accessor:wSlotCount #(UINT16)当前槽的数量

	#构造函数
	def initialize
		@dwRoleID = 0
		@dwOwnerID = 0
		@byStoreType = 0
		@wSlotCount = 0
	end

	#拷贝到另一个对象
	def copyTo(obj)
		obj.dwRoleID = @dwRoleID
		obj.dwOwnerID = @dwOwnerID
		obj.byStoreType = @byStoreType
		obj.wSlotCount = @wSlotCount
	end

	#以下为序列化函数
	def self.fromStream(data)
		s = SSlotPropStream.new
		s.dwRoleID = ByteUtil::readUINT64(data)
		s.dwOwnerID = ByteUtil::readUINT64(data)
		s.byStoreType = ByteUtil::readUINT8(data)
		s.wSlotCount = ByteUtil::readUINT16(data)
		return s
	end

	def self.vectorFromStream(data)
		length = ByteUtil::readVectorLength(data)
		arr = Array.new
		length.times do |i|
			s = SSlotPropStream::fromStream(data)
			arr[i] = s
		end
		return arr
	end

	def toStream(data)
		ByteUtil::writeUINT64(data, @dwRoleID)
		ByteUtil::writeUINT64(data, @dwOwnerID)
		ByteUtil::writeUINT8(data, @byStoreType)
		ByteUtil::writeUINT16(data, @wSlotCount)
	end

	def self.vectorToStream(data, arr)
		ByteUtil::writeVectorLength(data, arr.length)
		arr.each do |s|
			s.toStream(data)
		end
	end
end

#协议类：数据库序列化结构
class DBDataBase < ProtocolBase
	#以下为协议接口
	@recvFuncList

	def initialize
		@protID = 64;
		@recvFuncList = Array.new
	end

	def handleMessage(data)
		return true;
	end
end

