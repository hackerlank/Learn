/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPlayerPrize.as
//  Purpose:      BOSS相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.bossProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 排行帮信息
	 */
	public final class SPlayerPrize
	{
		public var dwPrizeType:uint; //(无符号8位整数)奖励类型
		public var vecPrizeMoneyInfo:Vector.<SPrizeMoneyInfo>; //货币奖励
		public var vecPrizeItemInfo:Vector.<SPrizeIteminfo>; //物品奖励

		/**
		 * 辅助创建函数
		 */
		public static function create(dwPrizeType:uint, vecPrizeMoneyInfo:Vector.<SPrizeMoneyInfo>, vecPrizeItemInfo:Vector.<SPrizeIteminfo>):SPlayerPrize
		{
			var s_:SPlayerPrize = new SPlayerPrize();
			s_.dwPrizeType = dwPrizeType;
			s_.vecPrizeMoneyInfo = vecPrizeMoneyInfo;
			s_.vecPrizeItemInfo = vecPrizeItemInfo;
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
				topXml = <SPlayerPrize _name_={name_} dwPrizeType={dwPrizeType}/>;
			else
				topXml = <SPlayerPrize dwPrizeType={dwPrizeType}/>;
			if(vecPrizeMoneyInfo != null)
			{
				var vecPrizeMoneyInfoXml:XML = <Vec_SPrizeMoneyInfo _name_="vecPrizeMoneyInfo"/>;
				for each(var s1:SPrizeMoneyInfo in vecPrizeMoneyInfo)
					vecPrizeMoneyInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecPrizeMoneyInfoXml);
			}
			if(vecPrizeItemInfo != null)
			{
				var vecPrizeItemInfoXml:XML = <Vec_SPrizeIteminfo _name_="vecPrizeItemInfo"/>;
				for each(var s2:SPrizeIteminfo in vecPrizeItemInfo)
					vecPrizeItemInfoXml.appendChild(s2.toXML());
				topXml.appendChild(vecPrizeItemInfoXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwPrizeType = dwPrizeType;
			obj_.vecPrizeMoneyInfo = vecPrizeMoneyInfo;
			obj_.vecPrizeItemInfo = vecPrizeItemInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPlayerPrize
		{
			var s_:SPlayerPrize = new SPlayerPrize();
			var dwPrizeType:uint = bytes.readUnsignedByte();
			s_.dwPrizeType = dwPrizeType;
			var vecPrizeMoneyInfo:Vector.<SPrizeMoneyInfo> = SPrizeMoneyInfo.vectorFromByteArray(bytes);
			s_.vecPrizeMoneyInfo = vecPrizeMoneyInfo;
			var vecPrizeItemInfo:Vector.<SPrizeIteminfo> = SPrizeIteminfo.vectorFromByteArray(bytes);
			s_.vecPrizeItemInfo = vecPrizeItemInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPlayerPrize>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPlayerPrize> = new Vector.<SPlayerPrize>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPlayerPrize = SPlayerPrize.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(dwPrizeType);
			SPrizeMoneyInfo.vectorToByteArray(vecPrizeMoneyInfo, bytes);
			SPrizeIteminfo.vectorToByteArray(vecPrizeItemInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SPlayerPrize>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPlayerPrize in vec)
				s.toByteArray(bytes);
		}
	}
}
