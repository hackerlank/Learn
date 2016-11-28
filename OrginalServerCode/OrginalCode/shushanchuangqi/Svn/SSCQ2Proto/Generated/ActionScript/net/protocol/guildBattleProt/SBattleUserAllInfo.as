/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleUserAllInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import net.protocol.mapProt.SPlayerAppear;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 帮派战玩家详细信息（包括战斗相关属性）
	 */
	public final class SBattleUserAllInfo extends SBattleUserInfo
	{
		public var sAppear:SPlayerAppear; //外观
		public var byHPP:uint; //(无符号8位整数)剩余HP百分比
		public var byPosIndex:uint; //(无符号8位整数)据点站位编号
		public var dwBattlePoint:uint; //(无符号32位整数)战斗力

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SBattleUserInfo.eType_SBattleUserAllInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SBattleUserAllInfo _name_={name_} byHPP={byHPP} byPosIndex={byPosIndex} dwBattlePoint={dwBattlePoint}/>;
			else
				topXml = <SBattleUserAllInfo byHPP={byHPP} byPosIndex={byPosIndex} dwBattlePoint={dwBattlePoint}/>;
			if(sAppear != null)
				topXml.appendChild(sAppear.toXML("sAppear"));
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
			obj_.sAppear = sAppear;
			obj_.byHPP = byHPP;
			obj_.byPosIndex = byPosIndex;
			obj_.dwBattlePoint = dwBattlePoint;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleUserAllInfo
		{
			var s_:SBattleUserAllInfo = new SBattleUserAllInfo();
			var base_:SBattleUserInfo = SBattleUserInfo.fromByteArray(bytes);
			base_.copyTo(s_);
			var sAppear:SPlayerAppear = SPlayerAppear.fromByteArray(bytes);
			s_.sAppear = sAppear;
			var byHPP:uint = bytes.readUnsignedByte();
			s_.byHPP = byHPP;
			var byPosIndex:uint = bytes.readUnsignedByte();
			s_.byPosIndex = byPosIndex;
			var dwBattlePoint:uint = bytes.readUnsignedInt();
			s_.dwBattlePoint = dwBattlePoint;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleUserAllInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleUserAllInfo> = new Vector.<SBattleUserAllInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleUserAllInfo = SBattleUserAllInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			sAppear.toByteArray(bytes);
			bytes.writeByte(byHPP);
			bytes.writeByte(byPosIndex);
			bytes.writeUnsignedInt(dwBattlePoint);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleUserAllInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleUserAllInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
