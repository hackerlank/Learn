/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildInfoBase.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派信息基本类
	 */
	public class SGuildInfoBase
	{
		public var qwGuildID:BigInteger; //(无符号64位整数)帮派唯一ID

		/**
		 * 获取继承类的类型
		 */
		public function getClassType():uint
		{
			return EType_SGuildInfoBase.eType_SGuildInfoBase;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SGuildInfoBase _name_={name_} qwGuildID={qwGuildID}/>;
			else
				topXml = <SGuildInfoBase qwGuildID={qwGuildID}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwGuildID = qwGuildID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildInfoBase
		{
			var s_:SGuildInfoBase = new SGuildInfoBase();
			var qwGuildID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwGuildID = qwGuildID;
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):SGuildInfoBase
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:SGuildInfoBase;
			switch(eType)
			{
				case EType_SGuildInfoBase.eType_SGuildInfoBase:
					s = SGuildInfoBase.fromByteArray(bytes);
					break;
				case EType_SGuildInfoBase.eType_SGuildBaseInfo:
					s = SGuildBaseInfo.fromByteArray(bytes);
					break;
				case EType_SGuildInfoBase.eType_SGuildUserInfo:
					s = SGuildUserInfo.fromByteArray(bytes);
					break;
				case EType_SGuildInfoBase.eType_SGuildApplyInfo:
					s = SGuildApplyInfo.fromByteArray(bytes);
					break;
				case EType_SGuildInfoBase.eType_SGuildBuildingInfo:
					s = SGuildBuildingInfo.fromByteArray(bytes);
					break;
				case EType_SGuildInfoBase.eType_SGuildAuthorityInfo:
					s = SGuildAuthorityInfo.fromByteArray(bytes);
					break;
				case EType_SGuildInfoBase.eType_SGuildTechInfo:
					s = SGuildTechInfo.fromByteArray(bytes);
					break;
				case EType_SGuildInfoBase.eType_SGuildLogInfo:
					s = SGuildLogInfo.fromByteArray(bytes);
					break;
				case EType_SGuildInfoBase.eType_SGuildStatueInfo:
					s = SGuildStatueInfo.fromByteArray(bytes);
					break;
				default:
					throw new Error("Unknown value for EType_SGuildInfoBase:" + eType);
			}
			return s;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildInfoBase>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildInfoBase> = new Vector.<SGuildInfoBase>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildInfoBase = SGuildInfoBase.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<SGuildInfoBase>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildInfoBase> = new Vector.<SGuildInfoBase>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildInfoBase = SGuildInfoBase.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwGuildID);
		}

		public function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildInfoBase>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildInfoBase in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<SGuildInfoBase>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildInfoBase in vec)
				s.superToByteArray(bytes);
		}
	}
}
