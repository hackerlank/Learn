/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    MoneyInfo.as
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 钱币列表
	 */
	public final class MoneyInfo
	{
		public var dwMoneyType:uint; //(无符号32位整数)钱币类型
		public var dwMoneyValue:uint; //(无符号32位整数)钱数

		/**
		 * 辅助创建函数
		 */
		public static function create(dwMoneyType:uint, dwMoneyValue:uint):MoneyInfo
		{
			var s_:MoneyInfo = new MoneyInfo();
			s_.dwMoneyType = dwMoneyType;
			s_.dwMoneyValue = dwMoneyValue;
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
				topXml = <MoneyInfo _name_={name_} dwMoneyType={dwMoneyType} dwMoneyValue={dwMoneyValue}/>;
			else
				topXml = <MoneyInfo dwMoneyType={dwMoneyType} dwMoneyValue={dwMoneyValue}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwMoneyType = dwMoneyType;
			obj_.dwMoneyValue = dwMoneyValue;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):MoneyInfo
		{
			var s_:MoneyInfo = new MoneyInfo();
			var dwMoneyType:uint = bytes.readUnsignedInt();
			s_.dwMoneyType = dwMoneyType;
			var dwMoneyValue:uint = bytes.readUnsignedInt();
			s_.dwMoneyValue = dwMoneyValue;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<MoneyInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<MoneyInfo> = new Vector.<MoneyInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:MoneyInfo = MoneyInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwMoneyType);
			bytes.writeUnsignedInt(dwMoneyValue);
		}

		public static function vectorToByteArray(vec:Vector.<MoneyInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:MoneyInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
