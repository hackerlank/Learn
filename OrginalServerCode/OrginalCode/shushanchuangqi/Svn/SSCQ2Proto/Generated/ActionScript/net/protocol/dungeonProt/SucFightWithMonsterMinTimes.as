/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SucFightWithMonsterMinTimes.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 尽量不和怪物发生战斗
	 */
	public final class SucFightWithMonsterMinTimes extends DgnSucCond
	{
		public var wGroup:uint; //(无符号16位整数)怪物
		public var byTotalTimes:uint; //(无符号8位整数)总战斗次数
		public var byCurTimes:uint; //(无符号8位整数)当前战斗次数

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_DgnSucCond.eType_SucFightWithMonsterMinTimes;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SucFightWithMonsterMinTimes _name_={name_} wGroup={wGroup} byTotalTimes={byTotalTimes} byCurTimes={byCurTimes}/>;
			else
				topXml = <SucFightWithMonsterMinTimes wGroup={wGroup} byTotalTimes={byTotalTimes} byCurTimes={byCurTimes}/>;
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
			obj_.wGroup = wGroup;
			obj_.byTotalTimes = byTotalTimes;
			obj_.byCurTimes = byCurTimes;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SucFightWithMonsterMinTimes
		{
			var s_:SucFightWithMonsterMinTimes = new SucFightWithMonsterMinTimes();
			var base_:DgnSucCond = DgnSucCond.fromByteArray(bytes);
			base_.copyTo(s_);
			var wGroup:uint = bytes.readUnsignedShort();
			s_.wGroup = wGroup;
			var byTotalTimes:uint = bytes.readUnsignedByte();
			s_.byTotalTimes = byTotalTimes;
			var byCurTimes:uint = bytes.readUnsignedByte();
			s_.byCurTimes = byCurTimes;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SucFightWithMonsterMinTimes>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SucFightWithMonsterMinTimes> = new Vector.<SucFightWithMonsterMinTimes>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SucFightWithMonsterMinTimes = SucFightWithMonsterMinTimes.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wGroup);
			bytes.writeByte(byTotalTimes);
			bytes.writeByte(byCurTimes);
		}

		public static function vectorToByteArray(vec:Vector.<SucFightWithMonsterMinTimes>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SucFightWithMonsterMinTimes in vec)
				s.toByteArray(bytes);
		}
	}
}
