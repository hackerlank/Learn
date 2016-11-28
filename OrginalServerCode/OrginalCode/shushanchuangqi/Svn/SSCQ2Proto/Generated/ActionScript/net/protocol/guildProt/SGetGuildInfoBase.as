/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGetGuildInfoBase.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 
	 */
	public class SGetGuildInfoBase
	{
		/**
		 * 获取继承类的类型
		 */
		public function getClassType():uint
		{
			return EType_SGetGuildInfoBase.eType_SGetGuildInfoBase;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SGetGuildInfoBase _name_={name_}/>;
			else
				topXml = <SGetGuildInfoBase/>;
			return topXml;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGetGuildInfoBase
		{
			var s_:SGetGuildInfoBase = new SGetGuildInfoBase();
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):SGetGuildInfoBase
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:SGetGuildInfoBase;
			switch(eType)
			{
				case EType_SGetGuildInfoBase.eType_SGetGuildInfoBase:
					s = SGetGuildInfoBase.fromByteArray(bytes);
					break;
				case EType_SGetGuildInfoBase.eType_SOtherGuildListInfo:
					s = SOtherGuildListInfo.fromByteArray(bytes);
					break;
				case EType_SGetGuildInfoBase.eType_SSelfGuildInfo:
					s = SSelfGuildInfo.fromByteArray(bytes);
					break;
				default:
					throw new Error("Unknown value for EType_SGetGuildInfoBase:" + eType);
			}
			return s;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGetGuildInfoBase>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGetGuildInfoBase> = new Vector.<SGetGuildInfoBase>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGetGuildInfoBase = SGetGuildInfoBase.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<SGetGuildInfoBase>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGetGuildInfoBase> = new Vector.<SGetGuildInfoBase>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGetGuildInfoBase = SGetGuildInfoBase.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
		}

		public function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SGetGuildInfoBase>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGetGuildInfoBase in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<SGetGuildInfoBase>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGetGuildInfoBase in vec)
				s.superToByteArray(bytes);
		}
	}
}
