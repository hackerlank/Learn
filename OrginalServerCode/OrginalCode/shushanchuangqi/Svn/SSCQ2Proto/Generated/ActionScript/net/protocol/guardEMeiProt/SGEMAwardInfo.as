/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGEMAwardInfo.as
//  Purpose:      守卫峨眉协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 守卫峨眉奖励信息
	 */
	public final class SGEMAwardInfo
	{
		public var wItemID:uint; //(无符号16位整数)物品ID
		public var dwCount:uint; //(无符号32位整数)堆叠数

		/**
		 * 辅助创建函数
		 */
		public static function create(wItemID:uint, dwCount:uint):SGEMAwardInfo
		{
			var s_:SGEMAwardInfo = new SGEMAwardInfo();
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
				topXml = <SGEMAwardInfo _name_={name_} wItemID={wItemID} dwCount={dwCount}/>;
			else
				topXml = <SGEMAwardInfo wItemID={wItemID} dwCount={dwCount}/>;
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

		public static function fromByteArray(bytes:ByteArray):SGEMAwardInfo
		{
			var s_:SGEMAwardInfo = new SGEMAwardInfo();
			var wItemID:uint = bytes.readUnsignedShort();
			s_.wItemID = wItemID;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGEMAwardInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGEMAwardInfo> = new Vector.<SGEMAwardInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGEMAwardInfo = SGEMAwardInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wItemID);
			bytes.writeUnsignedInt(dwCount);
		}

		public static function vectorToByteArray(vec:Vector.<SGEMAwardInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGEMAwardInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
