/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SMonsterPrize.as
//  Purpose:      天元神兽协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.godMonsterProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 排行榜
	 */
	public final class SMonsterPrize
	{
		public var eType:uint; //(枚举类型：EMonsterPrizeType)奖励类型
		public var byType:uint; //(无符号8位整数)0表示条件未达到，1表示可以领取，2表示已经领取

		/**
		 * 辅助创建函数
		 */
		public static function create(eType:uint, byType:uint):SMonsterPrize
		{
			var s_:SMonsterPrize = new SMonsterPrize();
			s_.eType = eType;
			s_.byType = byType;
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
				topXml = <SMonsterPrize _name_={name_} eType={eType} byType={byType}/>;
			else
				topXml = <SMonsterPrize eType={eType} byType={byType}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eType = eType;
			obj_.byType = byType;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SMonsterPrize
		{
			var s_:SMonsterPrize = new SMonsterPrize();
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
			var byType:uint = bytes.readUnsignedByte();
			s_.byType = byType;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SMonsterPrize>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SMonsterPrize> = new Vector.<SMonsterPrize>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SMonsterPrize = SMonsterPrize.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eType);
			bytes.writeByte(byType);
		}

		public static function vectorToByteArray(vec:Vector.<SMonsterPrize>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SMonsterPrize in vec)
				s.toByteArray(bytes);
		}
	}
}
