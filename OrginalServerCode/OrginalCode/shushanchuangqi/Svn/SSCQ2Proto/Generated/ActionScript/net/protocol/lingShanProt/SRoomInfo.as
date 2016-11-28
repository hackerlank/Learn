/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRoomInfo.as
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 房间信息
	 */
	public final class SRoomInfo
	{
		public var wRoomID:uint; //(无符号16位整数)房间编号
		public var wPlayerCnt:uint; //(无符号16位整数)房间人数

		/**
		 * 辅助创建函数
		 */
		public static function create(wRoomID:uint, wPlayerCnt:uint):SRoomInfo
		{
			var s_:SRoomInfo = new SRoomInfo();
			s_.wRoomID = wRoomID;
			s_.wPlayerCnt = wPlayerCnt;
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
				topXml = <SRoomInfo _name_={name_} wRoomID={wRoomID} wPlayerCnt={wPlayerCnt}/>;
			else
				topXml = <SRoomInfo wRoomID={wRoomID} wPlayerCnt={wPlayerCnt}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wRoomID = wRoomID;
			obj_.wPlayerCnt = wPlayerCnt;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRoomInfo
		{
			var s_:SRoomInfo = new SRoomInfo();
			var wRoomID:uint = bytes.readUnsignedShort();
			s_.wRoomID = wRoomID;
			var wPlayerCnt:uint = bytes.readUnsignedShort();
			s_.wPlayerCnt = wPlayerCnt;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRoomInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRoomInfo> = new Vector.<SRoomInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRoomInfo = SRoomInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wRoomID);
			bytes.writeShort(wPlayerCnt);
		}

		public static function vectorToByteArray(vec:Vector.<SRoomInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRoomInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
