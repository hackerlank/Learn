/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SCoinValue.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 货币信息
	 */
	public final class SCoinValue
	{
		public var eCoinType:uint; //(枚举类型：ECoinType)货币类型
		public var dwValue:uint; //(无符号32位整数)值

		/**
		 * 辅助创建函数
		 */
		public static function create(eCoinType:uint, dwValue:uint):SCoinValue
		{
			var s_:SCoinValue = new SCoinValue();
			s_.eCoinType = eCoinType;
			s_.dwValue = dwValue;
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
				topXml = <SCoinValue _name_={name_} eCoinType={eCoinType} dwValue={dwValue}/>;
			else
				topXml = <SCoinValue eCoinType={eCoinType} dwValue={dwValue}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eCoinType = eCoinType;
			obj_.dwValue = dwValue;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SCoinValue
		{
			var s_:SCoinValue = new SCoinValue();
			var eCoinType:uint = bytes.readUnsignedByte();
			s_.eCoinType = eCoinType;
			var dwValue:uint = bytes.readUnsignedInt();
			s_.dwValue = dwValue;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SCoinValue>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SCoinValue> = new Vector.<SCoinValue>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SCoinValue = SCoinValue.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eCoinType);
			bytes.writeUnsignedInt(dwValue);
		}

		public static function vectorToByteArray(vec:Vector.<SCoinValue>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SCoinValue in vec)
				s.toByteArray(bytes);
		}
	}
}
