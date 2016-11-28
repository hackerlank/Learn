/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SLimitPrize.as
//  Purpose:      天元神兽协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.godMonsterProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 限购礼包
	 */
	public final class SLimitPrize
	{
		public var wPrizeID:uint; //(无符号16位整数)礼品ID
		public var wCurNum:uint; //(无符号16位整数)已经购买数量
		public var wMaxNum:uint; //(无符号16位整数)最大值

		/**
		 * 辅助创建函数
		 */
		public static function create(wPrizeID:uint, wCurNum:uint, wMaxNum:uint):SLimitPrize
		{
			var s_:SLimitPrize = new SLimitPrize();
			s_.wPrizeID = wPrizeID;
			s_.wCurNum = wCurNum;
			s_.wMaxNum = wMaxNum;
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
				topXml = <SLimitPrize _name_={name_} wPrizeID={wPrizeID} wCurNum={wCurNum} wMaxNum={wMaxNum}/>;
			else
				topXml = <SLimitPrize wPrizeID={wPrizeID} wCurNum={wCurNum} wMaxNum={wMaxNum}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wPrizeID = wPrizeID;
			obj_.wCurNum = wCurNum;
			obj_.wMaxNum = wMaxNum;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SLimitPrize
		{
			var s_:SLimitPrize = new SLimitPrize();
			var wPrizeID:uint = bytes.readUnsignedShort();
			s_.wPrizeID = wPrizeID;
			var wCurNum:uint = bytes.readUnsignedShort();
			s_.wCurNum = wCurNum;
			var wMaxNum:uint = bytes.readUnsignedShort();
			s_.wMaxNum = wMaxNum;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SLimitPrize>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SLimitPrize> = new Vector.<SLimitPrize>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SLimitPrize = SLimitPrize.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wPrizeID);
			bytes.writeShort(wCurNum);
			bytes.writeShort(wMaxNum);
		}

		public static function vectorToByteArray(vec:Vector.<SLimitPrize>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SLimitPrize in vec)
				s.toByteArray(bytes);
		}
	}
}
