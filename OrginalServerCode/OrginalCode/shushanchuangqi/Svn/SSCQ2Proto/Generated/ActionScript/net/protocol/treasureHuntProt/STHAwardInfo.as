/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STHAwardInfo.as
//  Purpose:      寻宝协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 寻宝奖励信息
	 */
	public final class STHAwardInfo
	{
		public var wItemID:uint; //(无符号16位整数)物品ID
		public var dwCount:uint; //(无符号32位整数)堆叠数

		/**
		 * 辅助创建函数
		 */
		public static function create(wItemID:uint, dwCount:uint):STHAwardInfo
		{
			var s_:STHAwardInfo = new STHAwardInfo();
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
				topXml = <STHAwardInfo _name_={name_} wItemID={wItemID} dwCount={dwCount}/>;
			else
				topXml = <STHAwardInfo wItemID={wItemID} dwCount={dwCount}/>;
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

		public static function fromByteArray(bytes:ByteArray):STHAwardInfo
		{
			var s_:STHAwardInfo = new STHAwardInfo();
			var wItemID:uint = bytes.readUnsignedShort();
			s_.wItemID = wItemID;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STHAwardInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STHAwardInfo> = new Vector.<STHAwardInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STHAwardInfo = STHAwardInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wItemID);
			bytes.writeUnsignedInt(dwCount);
		}

		public static function vectorToByteArray(vec:Vector.<STHAwardInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STHAwardInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
