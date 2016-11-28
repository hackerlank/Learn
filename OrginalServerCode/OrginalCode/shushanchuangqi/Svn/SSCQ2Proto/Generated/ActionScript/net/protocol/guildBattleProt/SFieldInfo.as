/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFieldInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战场信息
	 */
	public final class SFieldInfo
	{
		public var strGuildNameA:String; //A方帮派名称
		public var strGuildNameB:String; //B方帮派名称
		public var vecSpotInfo:Vector.<SSpotInfo>; //据点详细信息

		/**
		 * 辅助创建函数
		 */
		public static function create(strGuildNameA:String, strGuildNameB:String, vecSpotInfo:Vector.<SSpotInfo>):SFieldInfo
		{
			var s_:SFieldInfo = new SFieldInfo();
			s_.strGuildNameA = strGuildNameA;
			s_.strGuildNameB = strGuildNameB;
			s_.vecSpotInfo = vecSpotInfo;
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
				topXml = <SFieldInfo _name_={name_} strGuildNameA={strGuildNameA} strGuildNameB={strGuildNameB}/>;
			else
				topXml = <SFieldInfo strGuildNameA={strGuildNameA} strGuildNameB={strGuildNameB}/>;
			if(vecSpotInfo != null)
			{
				var vecSpotInfoXml:XML = <Vec_SSpotInfo _name_="vecSpotInfo"/>;
				for each(var s1:SSpotInfo in vecSpotInfo)
					vecSpotInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecSpotInfoXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.strGuildNameA = strGuildNameA;
			obj_.strGuildNameB = strGuildNameB;
			obj_.vecSpotInfo = vecSpotInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFieldInfo
		{
			var s_:SFieldInfo = new SFieldInfo();
			var strGuildNameA:String = BytesUtil.readString(bytes);
			s_.strGuildNameA = strGuildNameA;
			var strGuildNameB:String = BytesUtil.readString(bytes);
			s_.strGuildNameB = strGuildNameB;
			var vecSpotInfo:Vector.<SSpotInfo> = SSpotInfo.superVectorFromByteArray(bytes);
			s_.vecSpotInfo = vecSpotInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFieldInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFieldInfo> = new Vector.<SFieldInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFieldInfo = SFieldInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeString(bytes, strGuildNameA);
			BytesUtil.writeString(bytes, strGuildNameB);
			SSpotInfo.superVectorToByteArray(vecSpotInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SFieldInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFieldInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
