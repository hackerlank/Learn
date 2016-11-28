/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SItemConfig.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 奖励道具信息
	 */
	public final class SItemConfig
	{
		public var dwItemID:uint; //(无符号32位整数)道具ID
		public var dwCount:uint; //(无符号32位整数)道具数量

		/**
		 * 辅助创建函数
		 */
		public static function create(dwItemID:uint, dwCount:uint):SItemConfig
		{
			var s_:SItemConfig = new SItemConfig();
			s_.dwItemID = dwItemID;
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
				topXml = <SItemConfig _name_={name_} dwItemID={dwItemID} dwCount={dwCount}/>;
			else
				topXml = <SItemConfig dwItemID={dwItemID} dwCount={dwCount}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwItemID = dwItemID;
			obj_.dwCount = dwCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SItemConfig
		{
			var s_:SItemConfig = new SItemConfig();
			var dwItemID:uint = bytes.readUnsignedInt();
			s_.dwItemID = dwItemID;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SItemConfig>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SItemConfig> = new Vector.<SItemConfig>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SItemConfig = SItemConfig.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwItemID);
			bytes.writeUnsignedInt(dwCount);
		}

		public static function vectorToByteArray(vec:Vector.<SItemConfig>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SItemConfig in vec)
				s.toByteArray(bytes);
		}
	}
}
