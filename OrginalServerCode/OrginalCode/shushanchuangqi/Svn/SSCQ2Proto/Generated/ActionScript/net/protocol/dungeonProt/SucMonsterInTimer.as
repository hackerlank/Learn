/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SucMonsterInTimer.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 定时杀怪
	 */
	public final class SucMonsterInTimer extends DgnSucCond
	{
		public var dwTotalTimer:uint; //(无符号32位整数)总计时间
		public var dwBeginTimer:uint; //(无符号32位整数)起始时间
		public var wMonsterGroup:uint; //(无符号16位整数)怪物组ID
		public var byTotalNum:uint; //(无符号8位整数)怪物总数
		public var byCurNum:uint; //(无符号8位整数)当前数量

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_DgnSucCond.eType_SucMonsterInTimer;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SucMonsterInTimer _name_={name_} dwTotalTimer={dwTotalTimer} dwBeginTimer={dwBeginTimer} wMonsterGroup={wMonsterGroup} byTotalNum={byTotalNum} byCurNum={byCurNum}/>;
			else
				topXml = <SucMonsterInTimer dwTotalTimer={dwTotalTimer} dwBeginTimer={dwBeginTimer} wMonsterGroup={wMonsterGroup} byTotalNum={byTotalNum} byCurNum={byCurNum}/>;
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
			obj_.dwTotalTimer = dwTotalTimer;
			obj_.dwBeginTimer = dwBeginTimer;
			obj_.wMonsterGroup = wMonsterGroup;
			obj_.byTotalNum = byTotalNum;
			obj_.byCurNum = byCurNum;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SucMonsterInTimer
		{
			var s_:SucMonsterInTimer = new SucMonsterInTimer();
			var base_:DgnSucCond = DgnSucCond.fromByteArray(bytes);
			base_.copyTo(s_);
			var dwTotalTimer:uint = bytes.readUnsignedInt();
			s_.dwTotalTimer = dwTotalTimer;
			var dwBeginTimer:uint = bytes.readUnsignedInt();
			s_.dwBeginTimer = dwBeginTimer;
			var wMonsterGroup:uint = bytes.readUnsignedShort();
			s_.wMonsterGroup = wMonsterGroup;
			var byTotalNum:uint = bytes.readUnsignedByte();
			s_.byTotalNum = byTotalNum;
			var byCurNum:uint = bytes.readUnsignedByte();
			s_.byCurNum = byCurNum;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SucMonsterInTimer>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SucMonsterInTimer> = new Vector.<SucMonsterInTimer>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SucMonsterInTimer = SucMonsterInTimer.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeUnsignedInt(dwTotalTimer);
			bytes.writeUnsignedInt(dwBeginTimer);
			bytes.writeShort(wMonsterGroup);
			bytes.writeByte(byTotalNum);
			bytes.writeByte(byCurNum);
		}

		public static function vectorToByteArray(vec:Vector.<SucMonsterInTimer>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SucMonsterInTimer in vec)
				s.toByteArray(bytes);
		}
	}
}
