/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRRHeroFighterInfo.as
//  Purpose:      排行榜相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 散仙信息
	 */
	public final class SRRHeroFighterInfo extends SRoleRankInfo
	{
		public var dwBattlePoint:uint; //(无符号32位整数)战斗力
		public var strGuildName:String; //帮派名称
		public var wID:uint; //(无符号16位整数)散仙类型
		public var byInfoQuality:uint; //(无符号8位整数)散仙品质(颜色)

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SRankInfo.eType_SRRHeroFighterInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRRHeroFighterInfo _name_={name_} dwBattlePoint={dwBattlePoint} strGuildName={strGuildName} wID={wID} byInfoQuality={byInfoQuality}/>;
			else
				topXml = <SRRHeroFighterInfo dwBattlePoint={dwBattlePoint} strGuildName={strGuildName} wID={wID} byInfoQuality={byInfoQuality}/>;
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
			obj_.dwBattlePoint = dwBattlePoint;
			obj_.strGuildName = strGuildName;
			obj_.wID = wID;
			obj_.byInfoQuality = byInfoQuality;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRRHeroFighterInfo
		{
			var s_:SRRHeroFighterInfo = new SRRHeroFighterInfo();
			var base_:SRoleRankInfo = SRoleRankInfo.fromByteArray(bytes);
			base_.copyTo(s_);
			var dwBattlePoint:uint = bytes.readUnsignedInt();
			s_.dwBattlePoint = dwBattlePoint;
			var strGuildName:String = BytesUtil.readString(bytes);
			s_.strGuildName = strGuildName;
			var wID:uint = bytes.readUnsignedShort();
			s_.wID = wID;
			var byInfoQuality:uint = bytes.readUnsignedByte();
			s_.byInfoQuality = byInfoQuality;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRRHeroFighterInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRRHeroFighterInfo> = new Vector.<SRRHeroFighterInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRRHeroFighterInfo = SRRHeroFighterInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeUnsignedInt(dwBattlePoint);
			BytesUtil.writeString(bytes, strGuildName);
			bytes.writeShort(wID);
			bytes.writeByte(byInfoQuality);
		}

		public static function vectorToByteArray(vec:Vector.<SRRHeroFighterInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRRHeroFighterInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
