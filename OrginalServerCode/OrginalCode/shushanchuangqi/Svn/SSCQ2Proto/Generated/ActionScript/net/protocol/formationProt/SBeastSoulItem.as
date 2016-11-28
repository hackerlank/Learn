/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBeastSoulItem.as
//  Purpose:      阵灵相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.formationProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 兽魂奖励道具信息
	 */
	public final class SBeastSoulItem
	{
		public var wItemID:uint; //(无符号16位整数)模板ID
		public var dwCount:uint; //(无符号32位整数)数量

		/**
		 * 辅助创建函数
		 */
		public static function create(wItemID:uint, dwCount:uint):SBeastSoulItem
		{
			var s_:SBeastSoulItem = new SBeastSoulItem();
			s_.wItemID = wItemID;
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
				topXml = <SBeastSoulItem _name_={name_} wItemID={wItemID} dwCount={dwCount}/>;
			else
				topXml = <SBeastSoulItem wItemID={wItemID} dwCount={dwCount}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wItemID = wItemID;
			obj_.dwCount = dwCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBeastSoulItem
		{
			var s_:SBeastSoulItem = new SBeastSoulItem();
			var wItemID:uint = bytes.readUnsignedShort();
			s_.wItemID = wItemID;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBeastSoulItem>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBeastSoulItem> = new Vector.<SBeastSoulItem>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBeastSoulItem = SBeastSoulItem.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wItemID);
			bytes.writeUnsignedInt(dwCount);
		}

		public static function vectorToByteArray(vec:Vector.<SBeastSoulItem>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBeastSoulItem in vec)
				s.toByteArray(bytes);
		}
	}
}
