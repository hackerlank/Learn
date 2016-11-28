/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SItem.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 道具的信息
	 */
	public class SItem
	{
		public var sItemInfo:RoleItemInfo; //道具信息

		/**
		 * 获取继承类的类型
		 */
		public function getClassType():uint
		{
			return EType_SItem.eType_SItem;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SItem _name_={name_}/>;
			else
				topXml = <SItem/>;
			if(sItemInfo != null)
				topXml.appendChild(sItemInfo.toXML("sItemInfo"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.sItemInfo = sItemInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SItem
		{
			var s_:SItem = new SItem();
			var sItemInfo:RoleItemInfo = RoleItemInfo.fromByteArray(bytes);
			s_.sItemInfo = sItemInfo;
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):SItem
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:SItem;
			switch(eType)
			{
				case EType_SItem.eType_SItem:
					s = SItem.fromByteArray(bytes);
					break;
				case EType_SItem.eType_SStack:
					s = SStack.fromByteArray(bytes);
					break;
				case EType_SItem.eType_SEquipTrump:
					s = SEquipTrump.fromByteArray(bytes);
					break;
				case EType_SItem.eType_SCitta:
					s = SCitta.fromByteArray(bytes);
					break;
				case EType_SItem.eType_STrump:
					s = STrump.fromByteArray(bytes);
					break;
				case EType_SItem.eType_SFashion:
					s = SFashion.fromByteArray(bytes);
					break;
				case EType_SItem.eType_SGemstone:
					s = SGemstone.fromByteArray(bytes);
					break;
				default:
					throw new Error("Unknown value for EType_SItem:" + eType);
			}
			return s;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SItem>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SItem> = new Vector.<SItem>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SItem = SItem.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<SItem>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SItem> = new Vector.<SItem>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SItem = SItem.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			sItemInfo.toByteArray(bytes);
		}

		public function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SItem>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SItem in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<SItem>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SItem in vec)
				s.superToByteArray(bytes);
		}
	}
}
