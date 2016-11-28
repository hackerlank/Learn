/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SCard.as
//  Purpose:      圣陵协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 卡片信息
	 */
	public final class SCard
	{
		public var eCardType:uint; //(枚举类型：ECardType)卡片类型
		public var byBuy:uint; //(无符号8位整数)玩家购买次数
		public var byUse:uint; //(无符号8位整数)当日使用次数
		public var byBuyForToday:uint; //(无符号8位整数)当日购买次数

		/**
		 * 辅助创建函数
		 */
		public static function create(eCardType:uint, byBuy:uint, byUse:uint, byBuyForToday:uint):SCard
		{
			var s_:SCard = new SCard();
			s_.eCardType = eCardType;
			s_.byBuy = byBuy;
			s_.byUse = byUse;
			s_.byBuyForToday = byBuyForToday;
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
				topXml = <SCard _name_={name_} eCardType={eCardType} byBuy={byBuy} byUse={byUse} byBuyForToday={byBuyForToday}/>;
			else
				topXml = <SCard eCardType={eCardType} byBuy={byBuy} byUse={byUse} byBuyForToday={byBuyForToday}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eCardType = eCardType;
			obj_.byBuy = byBuy;
			obj_.byUse = byUse;
			obj_.byBuyForToday = byBuyForToday;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SCard
		{
			var s_:SCard = new SCard();
			var eCardType:uint = bytes.readUnsignedByte();
			s_.eCardType = eCardType;
			var byBuy:uint = bytes.readUnsignedByte();
			s_.byBuy = byBuy;
			var byUse:uint = bytes.readUnsignedByte();
			s_.byUse = byUse;
			var byBuyForToday:uint = bytes.readUnsignedByte();
			s_.byBuyForToday = byBuyForToday;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SCard>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SCard> = new Vector.<SCard>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SCard = SCard.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eCardType);
			bytes.writeByte(byBuy);
			bytes.writeByte(byUse);
			bytes.writeByte(byBuyForToday);
		}

		public static function vectorToByteArray(vec:Vector.<SCard>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SCard in vec)
				s.toByteArray(bytes);
		}
	}
}
