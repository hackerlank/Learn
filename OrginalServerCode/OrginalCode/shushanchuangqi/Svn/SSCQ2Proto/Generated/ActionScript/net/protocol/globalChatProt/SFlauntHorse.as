/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFlauntHorse.as
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 坐骑炫耀信息
	 */
	public final class SFlauntHorse
	{
		public var qwInstID:BigInteger; //(无符号64位整数)阵灵唯一ID
		public var wFighterID:uint; //(无符号16位整数)坐骑ID
		public var byLevel:uint; //(无符号8位整数)等级

		/**
		 * 辅助创建函数
		 */
		public static function create(qwInstID:BigInteger, wFighterID:uint, byLevel:uint):SFlauntHorse
		{
			var s_:SFlauntHorse = new SFlauntHorse();
			s_.qwInstID = qwInstID;
			s_.wFighterID = wFighterID;
			s_.byLevel = byLevel;
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
				topXml = <SFlauntHorse _name_={name_} qwInstID={qwInstID} wFighterID={wFighterID} byLevel={byLevel}/>;
			else
				topXml = <SFlauntHorse qwInstID={qwInstID} wFighterID={wFighterID} byLevel={byLevel}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwInstID = qwInstID;
			obj_.wFighterID = wFighterID;
			obj_.byLevel = byLevel;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFlauntHorse
		{
			var s_:SFlauntHorse = new SFlauntHorse();
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
			var wFighterID:uint = bytes.readUnsignedShort();
			s_.wFighterID = wFighterID;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFlauntHorse>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFlauntHorse> = new Vector.<SFlauntHorse>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFlauntHorse = SFlauntHorse.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwInstID);
			bytes.writeShort(wFighterID);
			bytes.writeByte(byLevel);
		}

		public static function vectorToByteArray(vec:Vector.<SFlauntHorse>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFlauntHorse in vec)
				s.toByteArray(bytes);
		}
	}
}
