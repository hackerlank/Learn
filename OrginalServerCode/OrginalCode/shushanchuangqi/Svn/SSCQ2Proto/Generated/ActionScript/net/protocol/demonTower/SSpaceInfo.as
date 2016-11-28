/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSpaceInfo.as
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTower
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 魄空间列表
	 */
	public final class SSpaceInfo
	{
		public var dwSoulSpaceID:uint; //(无符号32位整数)魄空间id
		public var dwSoulSpaceLevel:uint; //(无符号32位整数)魄空间等级

		/**
		 * 辅助创建函数
		 */
		public static function create(dwSoulSpaceID:uint, dwSoulSpaceLevel:uint):SSpaceInfo
		{
			var s_:SSpaceInfo = new SSpaceInfo();
			s_.dwSoulSpaceID = dwSoulSpaceID;
			s_.dwSoulSpaceLevel = dwSoulSpaceLevel;
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
				topXml = <SSpaceInfo _name_={name_} dwSoulSpaceID={dwSoulSpaceID} dwSoulSpaceLevel={dwSoulSpaceLevel}/>;
			else
				topXml = <SSpaceInfo dwSoulSpaceID={dwSoulSpaceID} dwSoulSpaceLevel={dwSoulSpaceLevel}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwSoulSpaceID = dwSoulSpaceID;
			obj_.dwSoulSpaceLevel = dwSoulSpaceLevel;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSpaceInfo
		{
			var s_:SSpaceInfo = new SSpaceInfo();
			var dwSoulSpaceID:uint = bytes.readUnsignedInt();
			s_.dwSoulSpaceID = dwSoulSpaceID;
			var dwSoulSpaceLevel:uint = bytes.readUnsignedInt();
			s_.dwSoulSpaceLevel = dwSoulSpaceLevel;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSpaceInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSpaceInfo> = new Vector.<SSpaceInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSpaceInfo = SSpaceInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwSoulSpaceID);
			bytes.writeUnsignedInt(dwSoulSpaceLevel);
		}

		public static function vectorToByteArray(vec:Vector.<SSpaceInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSpaceInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
