/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SInstCount.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 物品列表
	 */
	public final class SInstCount
	{
		public var qwInstID:BigInteger; //(无符号64位整数)道具唯一ID
		public var wCount:uint; //(无符号32位整数)道具个数

		/**
		 * 辅助创建函数
		 */
		public static function create(qwInstID:BigInteger, wCount:uint):SInstCount
		{
			var s_:SInstCount = new SInstCount();
			s_.qwInstID = qwInstID;
			s_.wCount = wCount;
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
				topXml = <SInstCount _name_={name_} qwInstID={qwInstID} wCount={wCount}/>;
			else
				topXml = <SInstCount qwInstID={qwInstID} wCount={wCount}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwInstID = qwInstID;
			obj_.wCount = wCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SInstCount
		{
			var s_:SInstCount = new SInstCount();
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
			var wCount:uint = bytes.readUnsignedInt();
			s_.wCount = wCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SInstCount>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SInstCount> = new Vector.<SInstCount>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SInstCount = SInstCount.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwInstID);
			bytes.writeUnsignedInt(wCount);
		}

		public static function vectorToByteArray(vec:Vector.<SInstCount>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SInstCount in vec)
				s.toByteArray(bytes);
		}
	}
}
