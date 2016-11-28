/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBoxInfo.as
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 地图箱子信息
	 */
	public final class SBoxInfo
	{
		public var wPos:uint; //(无符号16位整数)当前所在地图位置
		public var dwModelID:uint; //(无符号16位整数)物品id

		/**
		 * 辅助创建函数
		 */
		public static function create(wPos:uint, dwModelID:uint):SBoxInfo
		{
			var s_:SBoxInfo = new SBoxInfo();
			s_.wPos = wPos;
			s_.dwModelID = dwModelID;
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
				topXml = <SBoxInfo _name_={name_} wPos={wPos} dwModelID={dwModelID}/>;
			else
				topXml = <SBoxInfo wPos={wPos} dwModelID={dwModelID}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wPos = wPos;
			obj_.dwModelID = dwModelID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBoxInfo
		{
			var s_:SBoxInfo = new SBoxInfo();
			var wPos:uint = bytes.readUnsignedShort();
			s_.wPos = wPos;
			var dwModelID:uint = bytes.readUnsignedShort();
			s_.dwModelID = dwModelID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBoxInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBoxInfo> = new Vector.<SBoxInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBoxInfo = SBoxInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wPos);
			bytes.writeShort(dwModelID);
		}

		public static function vectorToByteArray(vec:Vector.<SBoxInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBoxInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
