/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SNpcAppear.as
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * NPC的外观
	 */
	public final class SNpcAppear
	{
		public var wNpcID:uint; //(无符号16位整数)NPC类型ID
		public var strName:String; //NPC名称

		/**
		 * 辅助创建函数
		 */
		public static function create(wNpcID:uint, strName:String):SNpcAppear
		{
			var s_:SNpcAppear = new SNpcAppear();
			s_.wNpcID = wNpcID;
			s_.strName = strName;
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
				topXml = <SNpcAppear _name_={name_} wNpcID={wNpcID} strName={strName}/>;
			else
				topXml = <SNpcAppear wNpcID={wNpcID} strName={strName}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wNpcID = wNpcID;
			obj_.strName = strName;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SNpcAppear
		{
			var s_:SNpcAppear = new SNpcAppear();
			var wNpcID:uint = bytes.readUnsignedShort();
			s_.wNpcID = wNpcID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SNpcAppear>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SNpcAppear> = new Vector.<SNpcAppear>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SNpcAppear = SNpcAppear.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wNpcID);
			BytesUtil.writeString(bytes, strName);
		}

		public static function vectorToByteArray(vec:Vector.<SNpcAppear>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SNpcAppear in vec)
				s.toByteArray(bytes);
		}
	}
}
