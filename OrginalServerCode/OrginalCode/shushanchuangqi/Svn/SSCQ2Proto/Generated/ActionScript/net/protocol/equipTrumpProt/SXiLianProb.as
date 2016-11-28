/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SXiLianProb.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.equipTrumpProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 洗练区间属性
	 */
	public final class SXiLianProb
	{
		public var dwMinRate:uint; //(无符号32位整数)洗炼最小概率
		public var dwMaxRate:uint; //(无符号32位整数)洗炼最大概率
		public var dwRateValue:uint; //(无符号32位整数)洗炼权值空间

		/**
		 * 辅助创建函数
		 */
		public static function create(dwMinRate:uint, dwMaxRate:uint, dwRateValue:uint):SXiLianProb
		{
			var s_:SXiLianProb = new SXiLianProb();
			s_.dwMinRate = dwMinRate;
			s_.dwMaxRate = dwMaxRate;
			s_.dwRateValue = dwRateValue;
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
				topXml = <SXiLianProb _name_={name_} dwMinRate={dwMinRate} dwMaxRate={dwMaxRate} dwRateValue={dwRateValue}/>;
			else
				topXml = <SXiLianProb dwMinRate={dwMinRate} dwMaxRate={dwMaxRate} dwRateValue={dwRateValue}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwMinRate = dwMinRate;
			obj_.dwMaxRate = dwMaxRate;
			obj_.dwRateValue = dwRateValue;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SXiLianProb
		{
			var s_:SXiLianProb = new SXiLianProb();
			var dwMinRate:uint = bytes.readUnsignedInt();
			s_.dwMinRate = dwMinRate;
			var dwMaxRate:uint = bytes.readUnsignedInt();
			s_.dwMaxRate = dwMaxRate;
			var dwRateValue:uint = bytes.readUnsignedInt();
			s_.dwRateValue = dwRateValue;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SXiLianProb>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SXiLianProb> = new Vector.<SXiLianProb>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SXiLianProb = SXiLianProb.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwMinRate);
			bytes.writeUnsignedInt(dwMaxRate);
			bytes.writeUnsignedInt(dwRateValue);
		}

		public static function vectorToByteArray(vec:Vector.<SXiLianProb>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SXiLianProb in vec)
				s.toByteArray(bytes);
		}
	}
}
