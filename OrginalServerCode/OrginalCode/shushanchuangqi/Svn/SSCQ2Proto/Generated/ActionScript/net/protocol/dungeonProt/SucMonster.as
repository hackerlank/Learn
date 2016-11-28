/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SucMonster.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 杀怪条件
	 */
	public final class SucMonster extends DgnSucCond
	{
		public var wMonsterGroup:uint; //(无符号16位整数)怪物组ID
		public var byTotalNum:uint; //(无符号8位整数)怪物总数
		public var byCurNum:uint; //(无符号8位整数)当前数量

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_DgnSucCond.eType_SucMonster;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SucMonster _name_={name_} wMonsterGroup={wMonsterGroup} byTotalNum={byTotalNum} byCurNum={byCurNum}/>;
			else
				topXml = <SucMonster wMonsterGroup={wMonsterGroup} byTotalNum={byTotalNum} byCurNum={byCurNum}/>;
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
			obj_.wMonsterGroup = wMonsterGroup;
			obj_.byTotalNum = byTotalNum;
			obj_.byCurNum = byCurNum;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SucMonster
		{
			var s_:SucMonster = new SucMonster();
			var base_:DgnSucCond = DgnSucCond.fromByteArray(bytes);
			base_.copyTo(s_);
			var wMonsterGroup:uint = bytes.readUnsignedShort();
			s_.wMonsterGroup = wMonsterGroup;
			var byTotalNum:uint = bytes.readUnsignedByte();
			s_.byTotalNum = byTotalNum;
			var byCurNum:uint = bytes.readUnsignedByte();
			s_.byCurNum = byCurNum;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SucMonster>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SucMonster> = new Vector.<SucMonster>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SucMonster = SucMonster.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wMonsterGroup);
			bytes.writeByte(byTotalNum);
			bytes.writeByte(byCurNum);
		}

		public static function vectorToByteArray(vec:Vector.<SucMonster>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SucMonster in vec)
				s.toByteArray(bytes);
		}
	}
}
