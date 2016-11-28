/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPrizeMoneyInfo.as
//  Purpose:      BOSS相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.bossProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 货币列表
	 */
	public final class SPrizeMoneyInfo
	{
		public var dwMoneyType:uint; //(无符号32位整数)货币类型
		public var dwMoneyValue:uint; //(无符号32位整数)货币值

		/**
		 * 辅助创建函数
		 */
		public static function create(dwMoneyType:uint, dwMoneyValue:uint):SPrizeMoneyInfo
		{
			var s_:SPrizeMoneyInfo = new SPrizeMoneyInfo();
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
				topXml = <SPrizeMoneyInfo _name_={name_} dwMoneyType={dwMoneyType} dwMoneyValue={dwMoneyValue}/>;
			else
				topXml = <SPrizeMoneyInfo dwMoneyType={dwMoneyType} dwMoneyValue={dwMoneyValue}/>;
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

		public static function fromByteArray(bytes:ByteArray):SPrizeMoneyInfo
		{
			var s_:SPrizeMoneyInfo = new SPrizeMoneyInfo();
			var dwMoneyType:uint = bytes.readUnsignedInt();
			s_.dwMoneyType = dwMoneyType;
			var dwMoneyValue:uint = bytes.readUnsignedInt();
			s_.dwMoneyValue = dwMoneyValue;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPrizeMoneyInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPrizeMoneyInfo> = new Vector.<SPrizeMoneyInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPrizeMoneyInfo = SPrizeMoneyInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwMoneyType);
			bytes.writeUnsignedInt(dwMoneyValue);
		}

		public static function vectorToByteArray(vec:Vector.<SPrizeMoneyInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPrizeMoneyInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
