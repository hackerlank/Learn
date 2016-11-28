/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SItemGenInfo.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 显示用的模板数据
	 */
	public final class SItemGenInfo
	{
		public var wItemID:uint; //(无符号16位整数)模板ID
		public var dwCount:uint; //(无符号32位整数)数量
		public var byQuality:uint; //(无符号8位整数)品质
		public var eBindType:uint; //(枚举类型：EBindType)绑定类型
		public var dwTimeID:uint; //(无符号32位整数)时钟ID

		/**
		 * 辅助创建函数
		 */
		public static function create(wItemID:uint, dwCount:uint, byQuality:uint, eBindType:uint, dwTimeID:uint):SItemGenInfo
		{
			var s_:SItemGenInfo = new SItemGenInfo();
			s_.wItemID = wItemID;
			s_.dwCount = dwCount;
			s_.byQuality = byQuality;
			s_.eBindType = eBindType;
			s_.dwTimeID = dwTimeID;
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
				topXml = <SItemGenInfo _name_={name_} wItemID={wItemID} dwCount={dwCount} byQuality={byQuality} eBindType={eBindType} dwTimeID={dwTimeID}/>;
			else
				topXml = <SItemGenInfo wItemID={wItemID} dwCount={dwCount} byQuality={byQuality} eBindType={eBindType} dwTimeID={dwTimeID}/>;
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
			obj_.byQuality = byQuality;
			obj_.eBindType = eBindType;
			obj_.dwTimeID = dwTimeID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SItemGenInfo
		{
			var s_:SItemGenInfo = new SItemGenInfo();
			var wItemID:uint = bytes.readUnsignedShort();
			s_.wItemID = wItemID;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			var byQuality:uint = bytes.readUnsignedByte();
			s_.byQuality = byQuality;
			var eBindType:uint = bytes.readUnsignedByte();
			s_.eBindType = eBindType;
			var dwTimeID:uint = bytes.readUnsignedInt();
			s_.dwTimeID = dwTimeID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SItemGenInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SItemGenInfo> = new Vector.<SItemGenInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SItemGenInfo = SItemGenInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wItemID);
			bytes.writeUnsignedInt(dwCount);
			bytes.writeByte(byQuality);
			bytes.writeByte(eBindType);
			bytes.writeUnsignedInt(dwTimeID);
		}

		public static function vectorToByteArray(vec:Vector.<SItemGenInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SItemGenInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
