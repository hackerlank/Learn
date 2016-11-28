/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SucGather.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 采集条件
	 */
	public final class SucGather extends DgnSucCond
	{
		public var wGather:uint; //(无符号16位整数)采集ID
		public var byTotalNum:uint; //(无符号8位整数)采集总数
		public var byCurNum:uint; //(无符号8位整数)当前数量

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_DgnSucCond.eType_SucGather;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SucGather _name_={name_} wGather={wGather} byTotalNum={byTotalNum} byCurNum={byCurNum}/>;
			else
				topXml = <SucGather wGather={wGather} byTotalNum={byTotalNum} byCurNum={byCurNum}/>;
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public override function copyTo(obj_:*):void
		{
			super.copyTo(obj_);
			obj_.wGather = wGather;
			obj_.byTotalNum = byTotalNum;
			obj_.byCurNum = byCurNum;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SucGather
		{
			var s_:SucGather = new SucGather();
			var base_:DgnSucCond = DgnSucCond.fromByteArray(bytes);
			base_.copyTo(s_);
			var wGather:uint = bytes.readUnsignedShort();
			s_.wGather = wGather;
			var byTotalNum:uint = bytes.readUnsignedByte();
			s_.byTotalNum = byTotalNum;
			var byCurNum:uint = bytes.readUnsignedByte();
			s_.byCurNum = byCurNum;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SucGather>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SucGather> = new Vector.<SucGather>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SucGather = SucGather.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wGather);
			bytes.writeByte(byTotalNum);
			bytes.writeByte(byCurNum);
		}

		public static function vectorToByteArray(vec:Vector.<SucGather>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SucGather in vec)
				s.toByteArray(bytes);
		}
	}
}
