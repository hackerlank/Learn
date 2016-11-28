/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDiscount.as
//  Purpose:      商城相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 商城折扣物品信息
	 */
	public final class SDiscount
	{
		public var byPos:uint; //(无符号8位整数)限购位置(0,1,2表示)
		public var qwMarkID:BigInteger; //(无符号64位整数)栏位版本ID
		public var vecDisItems:Vector.<SDiscountItem>; //限购道具
		public var byLimitType:uint; //(无符号8位整数)类型限制(0无条件、1充值限购、2消费限购)
		public var dwLimitValue:uint; //(无符号32位整数)达到的仙石数量限制(0无条件、1充值限购、2消费限购)
		public var wLimitCount:uint; //(无符号16位整数)购买道具个数限制
		public var dwBeginTime:uint; //(无符号32位整数)限购开始时间
		public var dwEndTime:uint; //(无符号32位整数)限购结束时间

		/**
		 * 辅助创建函数
		 */
		public static function create(byPos:uint, qwMarkID:BigInteger, vecDisItems:Vector.<SDiscountItem>, byLimitType:uint, dwLimitValue:uint, 
			wLimitCount:uint, dwBeginTime:uint, dwEndTime:uint):SDiscount
		{
			var s_:SDiscount = new SDiscount();
			s_.byPos = byPos;
			s_.qwMarkID = qwMarkID;
			s_.vecDisItems = vecDisItems;
			s_.byLimitType = byLimitType;
			s_.dwLimitValue = dwLimitValue;
			s_.wLimitCount = wLimitCount;
			s_.dwBeginTime = dwBeginTime;
			s_.dwEndTime = dwEndTime;
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
				topXml = <SDiscount _name_={name_} byPos={byPos} qwMarkID={qwMarkID} byLimitType={byLimitType} dwLimitValue={dwLimitValue}
				 wLimitCount={wLimitCount} dwBeginTime={dwBeginTime} dwEndTime={dwEndTime}/>;
			else
				topXml = <SDiscount byPos={byPos} qwMarkID={qwMarkID} byLimitType={byLimitType} dwLimitValue={dwLimitValue}
				 wLimitCount={wLimitCount} dwBeginTime={dwBeginTime} dwEndTime={dwEndTime}/>;
			if(vecDisItems != null)
			{
				var vecDisItemsXml:XML = <Vec_SDiscountItem _name_="vecDisItems"/>;
				for each(var s1:SDiscountItem in vecDisItems)
					vecDisItemsXml.appendChild(s1.toXML());
				topXml.appendChild(vecDisItemsXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byPos = byPos;
			obj_.qwMarkID = qwMarkID;
			obj_.vecDisItems = vecDisItems;
			obj_.byLimitType = byLimitType;
			obj_.dwLimitValue = dwLimitValue;
			obj_.wLimitCount = wLimitCount;
			obj_.dwBeginTime = dwBeginTime;
			obj_.dwEndTime = dwEndTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDiscount
		{
			var s_:SDiscount = new SDiscount();
			var byPos:uint = bytes.readUnsignedByte();
			s_.byPos = byPos;
			var qwMarkID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwMarkID = qwMarkID;
			var vecDisItems:Vector.<SDiscountItem> = SDiscountItem.vectorFromByteArray(bytes);
			s_.vecDisItems = vecDisItems;
			var byLimitType:uint = bytes.readUnsignedByte();
			s_.byLimitType = byLimitType;
			var dwLimitValue:uint = bytes.readUnsignedInt();
			s_.dwLimitValue = dwLimitValue;
			var wLimitCount:uint = bytes.readUnsignedShort();
			s_.wLimitCount = wLimitCount;
			var dwBeginTime:uint = bytes.readUnsignedInt();
			s_.dwBeginTime = dwBeginTime;
			var dwEndTime:uint = bytes.readUnsignedInt();
			s_.dwEndTime = dwEndTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDiscount>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDiscount> = new Vector.<SDiscount>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDiscount = SDiscount.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byPos);
			BytesUtil.writeUInt64(bytes, qwMarkID);
			SDiscountItem.vectorToByteArray(vecDisItems, bytes);
			bytes.writeByte(byLimitType);
			bytes.writeUnsignedInt(dwLimitValue);
			bytes.writeShort(wLimitCount);
			bytes.writeUnsignedInt(dwBeginTime);
			bytes.writeUnsignedInt(dwEndTime);
		}

		public static function vectorToByteArray(vec:Vector.<SDiscount>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDiscount in vec)
				s.toByteArray(bytes);
		}
	}
}
