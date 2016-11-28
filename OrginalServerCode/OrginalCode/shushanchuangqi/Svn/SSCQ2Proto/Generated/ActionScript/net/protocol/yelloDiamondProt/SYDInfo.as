/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SYDInfo.as
//  Purpose:      QQ黄钻协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yelloDiamondProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * QQ黄钻信息
	 */
	public final class SYDInfo
	{
		public var bGainDayBag:Boolean; //是否领取每日礼包
		public var bGainYearBag:Boolean; //是否领取年费礼包
		public var bGainLuxuryBag:Boolean; //是否领取豪华礼包
		public var bGainHorseBag:Boolean; //是否领取座机礼包
		public var dGrowBag:uint; //(无符号16位整数)已领取成长礼包等级 从低位开始向高位 1表示领取，0表示未领取
		public var bGainNewBag:Boolean; //是否领取新手礼包

		/**
		 * 辅助创建函数
		 */
		public static function create(bGainDayBag:Boolean, bGainYearBag:Boolean, bGainLuxuryBag:Boolean, bGainHorseBag:Boolean, dGrowBag:uint, 
			bGainNewBag:Boolean):SYDInfo
		{
			var s_:SYDInfo = new SYDInfo();
			s_.bGainDayBag = bGainDayBag;
			s_.bGainYearBag = bGainYearBag;
			s_.bGainLuxuryBag = bGainLuxuryBag;
			s_.bGainHorseBag = bGainHorseBag;
			s_.dGrowBag = dGrowBag;
			s_.bGainNewBag = bGainNewBag;
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
				topXml = <SYDInfo _name_={name_} bGainDayBag={bGainDayBag} bGainYearBag={bGainYearBag} bGainLuxuryBag={bGainLuxuryBag} bGainHorseBag={bGainHorseBag} dGrowBag={dGrowBag}
				 bGainNewBag={bGainNewBag}/>;
			else
				topXml = <SYDInfo bGainDayBag={bGainDayBag} bGainYearBag={bGainYearBag} bGainLuxuryBag={bGainLuxuryBag} bGainHorseBag={bGainHorseBag} dGrowBag={dGrowBag}
				 bGainNewBag={bGainNewBag}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.bGainDayBag = bGainDayBag;
			obj_.bGainYearBag = bGainYearBag;
			obj_.bGainLuxuryBag = bGainLuxuryBag;
			obj_.bGainHorseBag = bGainHorseBag;
			obj_.dGrowBag = dGrowBag;
			obj_.bGainNewBag = bGainNewBag;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SYDInfo
		{
			var s_:SYDInfo = new SYDInfo();
			var bGainDayBag:Boolean = bytes.readBoolean();
			s_.bGainDayBag = bGainDayBag;
			var bGainYearBag:Boolean = bytes.readBoolean();
			s_.bGainYearBag = bGainYearBag;
			var bGainLuxuryBag:Boolean = bytes.readBoolean();
			s_.bGainLuxuryBag = bGainLuxuryBag;
			var bGainHorseBag:Boolean = bytes.readBoolean();
			s_.bGainHorseBag = bGainHorseBag;
			var dGrowBag:uint = bytes.readUnsignedShort();
			s_.dGrowBag = dGrowBag;
			var bGainNewBag:Boolean = bytes.readBoolean();
			s_.bGainNewBag = bGainNewBag;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SYDInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SYDInfo> = new Vector.<SYDInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SYDInfo = SYDInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeBoolean(bGainDayBag);
			bytes.writeBoolean(bGainYearBag);
			bytes.writeBoolean(bGainLuxuryBag);
			bytes.writeBoolean(bGainHorseBag);
			bytes.writeShort(dGrowBag);
			bytes.writeBoolean(bGainNewBag);
		}

		public static function vectorToByteArray(vec:Vector.<SYDInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SYDInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
