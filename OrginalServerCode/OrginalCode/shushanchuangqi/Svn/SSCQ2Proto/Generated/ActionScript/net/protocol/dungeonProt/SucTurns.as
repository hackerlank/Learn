/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SucTurns.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 回合数判定
	 */
	public final class SucTurns extends DgnSucCond
	{
		public var byTotalTurns:uint; //(无符号8位整数)总回合数
		public var byCurTurns:uint; //(无符号8位整数)当前回合数

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_DgnSucCond.eType_SucTurns;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SucTurns _name_={name_} byTotalTurns={byTotalTurns} byCurTurns={byCurTurns}/>;
			else
				topXml = <SucTurns byTotalTurns={byTotalTurns} byCurTurns={byCurTurns}/>;
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
			obj_.byTotalTurns = byTotalTurns;
			obj_.byCurTurns = byCurTurns;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SucTurns
		{
			var s_:SucTurns = new SucTurns();
			var base_:DgnSucCond = DgnSucCond.fromByteArray(bytes);
			base_.copyTo(s_);
			var byTotalTurns:uint = bytes.readUnsignedByte();
			s_.byTotalTurns = byTotalTurns;
			var byCurTurns:uint = bytes.readUnsignedByte();
			s_.byCurTurns = byCurTurns;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SucTurns>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SucTurns> = new Vector.<SucTurns>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SucTurns = SucTurns.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeByte(byTotalTurns);
			bytes.writeByte(byCurTurns);
		}

		public static function vectorToByteArray(vec:Vector.<SucTurns>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SucTurns in vec)
				s.toByteArray(bytes);
		}
	}
}
