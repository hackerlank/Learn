/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSpotInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 据点信息
	 */
	public class SSpotInfo
	{
		public var eSpotType:uint; //(枚举类型：EGBSpot)据点类型

		/**
		 * 获取继承类的类型
		 */
		public function getClassType():uint
		{
			return EType_SSpotInfo.eType_SSpotInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SSpotInfo _name_={name_} eSpotType={eSpotType}/>;
			else
				topXml = <SSpotInfo eSpotType={eSpotType}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eSpotType = eSpotType;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSpotInfo
		{
			var s_:SSpotInfo = new SSpotInfo();
			var eSpotType:uint = bytes.readUnsignedByte();
			s_.eSpotType = eSpotType;
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):SSpotInfo
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:SSpotInfo;
			switch(eType)
			{
				case EType_SSpotInfo.eType_SSpotInfo:
					s = SSpotInfo.fromByteArray(bytes);
					break;
				case EType_SSpotInfo.eType_SSpotAllInfo:
					s = SSpotAllInfo.fromByteArray(bytes);
					break;
				case EType_SSpotInfo.eType_SSpotBriefInfo:
					s = SSpotBriefInfo.fromByteArray(bytes);
					break;
				case EType_SSpotInfo.eType_SSpotReadyInfo:
					s = SSpotReadyInfo.fromByteArray(bytes);
					break;
				default:
					throw new Error("Unknown value for EType_SSpotInfo:" + eType);
			}
			return s;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSpotInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSpotInfo> = new Vector.<SSpotInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSpotInfo = SSpotInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<SSpotInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSpotInfo> = new Vector.<SSpotInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSpotInfo = SSpotInfo.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eSpotType);
		}

		public function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SSpotInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSpotInfo in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<SSpotInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSpotInfo in vec)
				s.superToByteArray(bytes);
		}
	}
}
