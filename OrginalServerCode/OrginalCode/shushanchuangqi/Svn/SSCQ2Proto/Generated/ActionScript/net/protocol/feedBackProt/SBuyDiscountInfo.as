/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBuyDiscountInfo.as
//  Purpose:      消费回馈
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.feedBackProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 折扣限购信息
	 */
	public final class SBuyDiscountInfo
	{
		public var eType:uint; //(枚举类型：EFeedBackActType)消费回馈类型
		public var dwBuyCount:uint; //(无符号32位整数)已领购买次数

		/**
		 * 辅助创建函数
		 */
		public static function create(eType:uint, dwBuyCount:uint):SBuyDiscountInfo
		{
			var s_:SBuyDiscountInfo = new SBuyDiscountInfo();
			s_.eType = eType;
			s_.dwBuyCount = dwBuyCount;
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
				topXml = <SBuyDiscountInfo _name_={name_} eType={eType} dwBuyCount={dwBuyCount}/>;
			else
				topXml = <SBuyDiscountInfo eType={eType} dwBuyCount={dwBuyCount}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eType = eType;
			obj_.dwBuyCount = dwBuyCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBuyDiscountInfo
		{
			var s_:SBuyDiscountInfo = new SBuyDiscountInfo();
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
			var dwBuyCount:uint = bytes.readUnsignedInt();
			s_.dwBuyCount = dwBuyCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBuyDiscountInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBuyDiscountInfo> = new Vector.<SBuyDiscountInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBuyDiscountInfo = SBuyDiscountInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eType);
			bytes.writeUnsignedInt(dwBuyCount);
		}

		public static function vectorToByteArray(vec:Vector.<SBuyDiscountInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBuyDiscountInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
