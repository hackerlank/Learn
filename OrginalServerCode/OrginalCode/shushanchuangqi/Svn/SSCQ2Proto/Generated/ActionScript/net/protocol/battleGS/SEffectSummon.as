/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEffectSummon.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 召唤效果
	 */
	public final class SEffectSummon extends SEffectBase
	{
		public var byGroupID:uint; //(无符号8位整数)组编号
		public var bySide:uint; //(无符号8位整数)方向编号
		public var byPos:uint; //(无符号8位整数)位置编号
		public var wFighterID:uint; //(无符号16位整数)散仙ID
		public var dwHpMax:uint; //(无符号32位整数)最大血量
		public var dwHp:uint; //(无符号32位整数)当前血量
		public var dwAura:uint; //(无符号32位整数)当前灵气
		public var dwAuraMax:uint; //(无符号32位整数)最大灵气

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SEffectBase.eType_SEffectSummon;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SEffectSummon _name_={name_} byGroupID={byGroupID} bySide={bySide} byPos={byPos} wFighterID={wFighterID} dwHpMax={dwHpMax}
				 dwHp={dwHp} dwAura={dwAura} dwAuraMax={dwAuraMax}/>;
			else
				topXml = <SEffectSummon byGroupID={byGroupID} bySide={bySide} byPos={byPos} wFighterID={wFighterID} dwHpMax={dwHpMax}
				 dwHp={dwHp} dwAura={dwAura} dwAuraMax={dwAuraMax}/>;
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
			obj_.byGroupID = byGroupID;
			obj_.bySide = bySide;
			obj_.byPos = byPos;
			obj_.wFighterID = wFighterID;
			obj_.dwHpMax = dwHpMax;
			obj_.dwHp = dwHp;
			obj_.dwAura = dwAura;
			obj_.dwAuraMax = dwAuraMax;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEffectSummon
		{
			var s_:SEffectSummon = new SEffectSummon();
			var base_:SEffectBase = SEffectBase.fromByteArray(bytes);
			base_.copyTo(s_);
			var byGroupID:uint = bytes.readUnsignedByte();
			s_.byGroupID = byGroupID;
			var bySide:uint = bytes.readUnsignedByte();
			s_.bySide = bySide;
			var byPos:uint = bytes.readUnsignedByte();
			s_.byPos = byPos;
			var wFighterID:uint = bytes.readUnsignedShort();
			s_.wFighterID = wFighterID;
			var dwHpMax:uint = bytes.readUnsignedInt();
			s_.dwHpMax = dwHpMax;
			var dwHp:uint = bytes.readUnsignedInt();
			s_.dwHp = dwHp;
			var dwAura:uint = bytes.readUnsignedInt();
			s_.dwAura = dwAura;
			var dwAuraMax:uint = bytes.readUnsignedInt();
			s_.dwAuraMax = dwAuraMax;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEffectSummon>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEffectSummon> = new Vector.<SEffectSummon>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEffectSummon = SEffectSummon.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeByte(byGroupID);
			bytes.writeByte(bySide);
			bytes.writeByte(byPos);
			bytes.writeShort(wFighterID);
			bytes.writeUnsignedInt(dwHpMax);
			bytes.writeUnsignedInt(dwHp);
			bytes.writeUnsignedInt(dwAura);
			bytes.writeUnsignedInt(dwAuraMax);
		}

		public static function vectorToByteArray(vec:Vector.<SEffectSummon>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEffectSummon in vec)
				s.toByteArray(bytes);
		}
	}
}
