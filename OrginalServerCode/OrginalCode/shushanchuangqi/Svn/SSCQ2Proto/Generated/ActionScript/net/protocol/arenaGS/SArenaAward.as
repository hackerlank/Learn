/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SArenaAward.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家奖励信息
	 */
	public final class SArenaAward
	{
		public var eType:uint; //(枚举类型：EArenaAwardType)奖励包类型
		public var byDraw:uint; //(无符号8位整数)0,表示未领取；1，表示已领取
		public var dwDrawID:uint; //(无符号32位整数)掉落包ID

		/**
		 * 辅助创建函数
		 */
		public static function create(eType:uint, byDraw:uint, dwDrawID:uint):SArenaAward
		{
			var s_:SArenaAward = new SArenaAward();
			s_.eType = eType;
			s_.byDraw = byDraw;
			s_.dwDrawID = dwDrawID;
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
				topXml = <SArenaAward _name_={name_} eType={eType} byDraw={byDraw} dwDrawID={dwDrawID}/>;
			else
				topXml = <SArenaAward eType={eType} byDraw={byDraw} dwDrawID={dwDrawID}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eType = eType;
			obj_.byDraw = byDraw;
			obj_.dwDrawID = dwDrawID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SArenaAward
		{
			var s_:SArenaAward = new SArenaAward();
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
			var byDraw:uint = bytes.readUnsignedByte();
			s_.byDraw = byDraw;
			var dwDrawID:uint = bytes.readUnsignedInt();
			s_.dwDrawID = dwDrawID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SArenaAward>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SArenaAward> = new Vector.<SArenaAward>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SArenaAward = SArenaAward.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eType);
			bytes.writeByte(byDraw);
			bytes.writeUnsignedInt(dwDrawID);
		}

		public static function vectorToByteArray(vec:Vector.<SArenaAward>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SArenaAward in vec)
				s.toByteArray(bytes);
		}
	}
}
