/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SMoneyCount.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 货币列表
	 */
	public final class SMoneyCount
	{
		public var eMoneyType:uint; //(枚举类型：EMoneyType)货币类型
		public var dwCount:uint; //(无符号32位整数)货币量

		/**
		 * 辅助创建函数
		 */
		public static function create(eMoneyType:uint, dwCount:uint):SMoneyCount
		{
			var s_:SMoneyCount = new SMoneyCount();
			s_.eMoneyType = eMoneyType;
			s_.dwCount = dwCount;
			return s_;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SMoneyCount _name_={name_} eMoneyType={eMoneyType} dwCount={dwCount}/>;
			else
				topXml = <SMoneyCount eMoneyType={eMoneyType} dwCount={dwCount}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eMoneyType = eMoneyType;
			obj_.dwCount = dwCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SMoneyCount
		{
			var s_:SMoneyCount = new SMoneyCount();
			var eMoneyType:uint = bytes.readUnsignedByte();
			s_.eMoneyType = eMoneyType;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SMoneyCount>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SMoneyCount> = new Vector.<SMoneyCount>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SMoneyCount = SMoneyCount.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eMoneyType);
			bytes.writeUnsignedInt(dwCount);
		}

		public static function vectorToByteArray(vec:Vector.<SMoneyCount>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SMoneyCount in vec)
				s.toByteArray(bytes);
		}
	}
}
