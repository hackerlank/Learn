/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPrizeIteminfo.as
//  Purpose:      BOSS相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.bossProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 货币列表
	 */
	public final class SPrizeIteminfo
	{
		public var dwItemID:uint; //(无符号32位整数)物品id
		public var dwItemCount:uint; //(无符号32位整数)物品数量

		/**
		 * 辅助创建函数
		 */
		public static function create(dwItemID:uint, dwItemCount:uint):SPrizeIteminfo
		{
			var s_:SPrizeIteminfo = new SPrizeIteminfo();
			s_.dwItemID = dwItemID;
			s_.dwItemCount = dwItemCount;
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
				topXml = <SPrizeIteminfo _name_={name_} dwItemID={dwItemID} dwItemCount={dwItemCount}/>;
			else
				topXml = <SPrizeIteminfo dwItemID={dwItemID} dwItemCount={dwItemCount}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwItemID = dwItemID;
			obj_.dwItemCount = dwItemCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPrizeIteminfo
		{
			var s_:SPrizeIteminfo = new SPrizeIteminfo();
			var dwItemID:uint = bytes.readUnsignedInt();
			s_.dwItemID = dwItemID;
			var dwItemCount:uint = bytes.readUnsignedInt();
			s_.dwItemCount = dwItemCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPrizeIteminfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPrizeIteminfo> = new Vector.<SPrizeIteminfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPrizeIteminfo = SPrizeIteminfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwItemID);
			bytes.writeUnsignedInt(dwItemCount);
		}

		public static function vectorToByteArray(vec:Vector.<SPrizeIteminfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPrizeIteminfo in vec)
				s.toByteArray(bytes);
		}
	}
}
