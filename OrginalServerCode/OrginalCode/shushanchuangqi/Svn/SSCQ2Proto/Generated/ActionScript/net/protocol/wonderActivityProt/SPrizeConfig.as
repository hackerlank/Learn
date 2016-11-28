/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPrizeConfig.as
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
	public final class SPrizeConfig
	{
		public var ePrizeType:uint; //(枚举类型：EWActPrizeType)奖励类型
		public var vecItems:Vector.<SItemConfig>; //道具

		/**
		 * 辅助创建函数
		 */
		public static function create(ePrizeType:uint, vecItems:Vector.<SItemConfig>):SPrizeConfig
		{
			var s_:SPrizeConfig = new SPrizeConfig();
			s_.ePrizeType = ePrizeType;
			s_.vecItems = vecItems;
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
				topXml = <SPrizeConfig _name_={name_} ePrizeType={ePrizeType}/>;
			else
				topXml = <SPrizeConfig ePrizeType={ePrizeType}/>;
			if(vecItems != null)
			{
				var vecItemsXml:XML = <Vec_SItemConfig _name_="vecItems"/>;
				for each(var s1:SItemConfig in vecItems)
					vecItemsXml.appendChild(s1.toXML());
				topXml.appendChild(vecItemsXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.ePrizeType = ePrizeType;
			obj_.vecItems = vecItems;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPrizeConfig
		{
			var s_:SPrizeConfig = new SPrizeConfig();
			var ePrizeType:uint = bytes.readUnsignedByte();
			s_.ePrizeType = ePrizeType;
			var vecItems:Vector.<SItemConfig> = SItemConfig.vectorFromByteArray(bytes);
			s_.vecItems = vecItems;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPrizeConfig>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPrizeConfig> = new Vector.<SPrizeConfig>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPrizeConfig = SPrizeConfig.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(ePrizeType);
			SItemConfig.vectorToByteArray(vecItems, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SPrizeConfig>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPrizeConfig in vec)
				s.toByteArray(bytes);
		}
	}
}
