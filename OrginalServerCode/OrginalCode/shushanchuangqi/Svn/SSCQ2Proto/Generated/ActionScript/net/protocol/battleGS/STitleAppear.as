/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STitleAppear.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 装备的头衔外观
	 */
	public final class STitleAppear
	{
		public var byPos:uint; //(无符号8位整数)装备位置
		public var wID:uint; //(无符号16位整数)头衔ID

		/**
		 * 辅助创建函数
		 */
		public static function create(byPos:uint, wID:uint):STitleAppear
		{
			var s_:STitleAppear = new STitleAppear();
			s_.byPos = byPos;
			s_.wID = wID;
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
				topXml = <STitleAppear _name_={name_} byPos={byPos} wID={wID}/>;
			else
				topXml = <STitleAppear byPos={byPos} wID={wID}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byPos = byPos;
			obj_.wID = wID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STitleAppear
		{
			var s_:STitleAppear = new STitleAppear();
			var byPos:uint = bytes.readUnsignedByte();
			s_.byPos = byPos;
			var wID:uint = bytes.readUnsignedShort();
			s_.wID = wID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STitleAppear>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STitleAppear> = new Vector.<STitleAppear>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STitleAppear = STitleAppear.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byPos);
			bytes.writeShort(wID);
		}

		public static function vectorToByteArray(vec:Vector.<STitleAppear>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STitleAppear in vec)
				s.toByteArray(bytes);
		}
	}
}
