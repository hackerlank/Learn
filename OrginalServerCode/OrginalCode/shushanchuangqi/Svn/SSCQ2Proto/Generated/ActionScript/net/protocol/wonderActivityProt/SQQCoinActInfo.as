/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SQQCoinActInfo.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * Q币养成活动信息
	 */
	public final class SQQCoinActInfo
	{
		public var dwTime:uint; //(无符号32位整数)活动剩余时间
		public var byLevel:uint; //(无符号8位整数)当前兑换的等级
		public var dwMaxValue:uint; //(无符号32位整数)奖励最大值
		public var dwCurValue:uint; //(无符号32位整数)当前值

		/**
		 * 辅助创建函数
		 */
		public static function create(dwTime:uint, byLevel:uint, dwMaxValue:uint, dwCurValue:uint):SQQCoinActInfo
		{
			var s_:SQQCoinActInfo = new SQQCoinActInfo();
			s_.dwTime = dwTime;
			s_.byLevel = byLevel;
			s_.dwMaxValue = dwMaxValue;
			s_.dwCurValue = dwCurValue;
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
				topXml = <SQQCoinActInfo _name_={name_} dwTime={dwTime} byLevel={byLevel} dwMaxValue={dwMaxValue} dwCurValue={dwCurValue}/>;
			else
				topXml = <SQQCoinActInfo dwTime={dwTime} byLevel={byLevel} dwMaxValue={dwMaxValue} dwCurValue={dwCurValue}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwTime = dwTime;
			obj_.byLevel = byLevel;
			obj_.dwMaxValue = dwMaxValue;
			obj_.dwCurValue = dwCurValue;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SQQCoinActInfo
		{
			var s_:SQQCoinActInfo = new SQQCoinActInfo();
			var dwTime:uint = bytes.readUnsignedInt();
			s_.dwTime = dwTime;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var dwMaxValue:uint = bytes.readUnsignedInt();
			s_.dwMaxValue = dwMaxValue;
			var dwCurValue:uint = bytes.readUnsignedInt();
			s_.dwCurValue = dwCurValue;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SQQCoinActInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SQQCoinActInfo> = new Vector.<SQQCoinActInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SQQCoinActInfo = SQQCoinActInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwTime);
			bytes.writeByte(byLevel);
			bytes.writeUnsignedInt(dwMaxValue);
			bytes.writeUnsignedInt(dwCurValue);
		}

		public static function vectorToByteArray(vec:Vector.<SQQCoinActInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SQQCoinActInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
