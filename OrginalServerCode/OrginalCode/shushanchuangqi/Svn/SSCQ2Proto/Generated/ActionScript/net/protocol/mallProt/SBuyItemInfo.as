/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBuyItemInfo.as
//  Purpose:      商城相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 物品购买信息
	 */
	public final class SBuyItemInfo
	{
		public var dwInstID:uint; //(无符号32位整数)实例ID
		public var dwCount:uint; //(无符号32位整数)物品数量

		/**
		 * 辅助创建函数
		 */
		public static function create(dwInstID:uint, dwCount:uint):SBuyItemInfo
		{
			var s_:SBuyItemInfo = new SBuyItemInfo();
			s_.dwInstID = dwInstID;
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
				topXml = <SBuyItemInfo _name_={name_} dwInstID={dwInstID} dwCount={dwCount}/>;
			else
				topXml = <SBuyItemInfo dwInstID={dwInstID} dwCount={dwCount}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwInstID = dwInstID;
			obj_.dwCount = dwCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBuyItemInfo
		{
			var s_:SBuyItemInfo = new SBuyItemInfo();
			var dwInstID:uint = bytes.readUnsignedInt();
			s_.dwInstID = dwInstID;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBuyItemInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBuyItemInfo> = new Vector.<SBuyItemInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBuyItemInfo = SBuyItemInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwInstID);
			bytes.writeUnsignedInt(dwCount);
		}

		public static function vectorToByteArray(vec:Vector.<SBuyItemInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBuyItemInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
