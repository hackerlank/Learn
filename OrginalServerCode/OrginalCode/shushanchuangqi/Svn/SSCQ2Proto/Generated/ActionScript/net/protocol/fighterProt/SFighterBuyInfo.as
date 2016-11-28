/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFighterBuyInfo.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家购买散仙信息
	 */
	public final class SFighterBuyInfo
	{
		public var wFighterID:uint; //(无符号16位整数)将类型ID
		public var byFighterBuyStatus:uint; //(无符号8位整数)购买状态（0：未购买；1：已购买）

		/**
		 * 辅助创建函数
		 */
		public static function create(wFighterID:uint, byFighterBuyStatus:uint):SFighterBuyInfo
		{
			var s_:SFighterBuyInfo = new SFighterBuyInfo();
			s_.wFighterID = wFighterID;
			s_.byFighterBuyStatus = byFighterBuyStatus;
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
				topXml = <SFighterBuyInfo _name_={name_} wFighterID={wFighterID} byFighterBuyStatus={byFighterBuyStatus}/>;
			else
				topXml = <SFighterBuyInfo wFighterID={wFighterID} byFighterBuyStatus={byFighterBuyStatus}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wFighterID = wFighterID;
			obj_.byFighterBuyStatus = byFighterBuyStatus;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFighterBuyInfo
		{
			var s_:SFighterBuyInfo = new SFighterBuyInfo();
			var wFighterID:uint = bytes.readUnsignedShort();
			s_.wFighterID = wFighterID;
			var byFighterBuyStatus:uint = bytes.readUnsignedByte();
			s_.byFighterBuyStatus = byFighterBuyStatus;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFighterBuyInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFighterBuyInfo> = new Vector.<SFighterBuyInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFighterBuyInfo = SFighterBuyInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wFighterID);
			bytes.writeByte(byFighterBuyStatus);
		}

		public static function vectorToByteArray(vec:Vector.<SFighterBuyInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFighterBuyInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
