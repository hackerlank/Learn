/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SActInfo.as
//  Purpose:      活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayActProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 活动信息表
	 */
	public final class SActInfo
	{
		public var dwActType:uint; //(无符号32位整数)活动id
		public var dwActStatus:uint; //(无符号32位整数)活动状态

		/**
		 * 辅助创建函数
		 */
		public static function create(dwActType:uint, dwActStatus:uint):SActInfo
		{
			var s_:SActInfo = new SActInfo();
			s_.dwActType = dwActType;
			s_.dwActStatus = dwActStatus;
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
				topXml = <SActInfo _name_={name_} dwActType={dwActType} dwActStatus={dwActStatus}/>;
			else
				topXml = <SActInfo dwActType={dwActType} dwActStatus={dwActStatus}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwActType = dwActType;
			obj_.dwActStatus = dwActStatus;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SActInfo
		{
			var s_:SActInfo = new SActInfo();
			var dwActType:uint = bytes.readUnsignedInt();
			s_.dwActType = dwActType;
			var dwActStatus:uint = bytes.readUnsignedInt();
			s_.dwActStatus = dwActStatus;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SActInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SActInfo> = new Vector.<SActInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SActInfo = SActInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwActType);
			bytes.writeUnsignedInt(dwActStatus);
		}

		public static function vectorToByteArray(vec:Vector.<SActInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SActInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
