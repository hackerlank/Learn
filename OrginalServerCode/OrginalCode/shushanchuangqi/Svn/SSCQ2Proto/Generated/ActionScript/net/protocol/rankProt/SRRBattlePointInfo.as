/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRRBattlePointInfo.as
//  Purpose:      排行榜相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战力信息
	 */
	public final class SRRBattlePointInfo extends SRoleRankInfo
	{
		public var dwBattlePoint:uint; //(无符号32位整数)战斗力
		public var strGuildName:String; //帮派名称

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_SRankInfo.eType_SRRBattlePointInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRRBattlePointInfo _name_={name_} dwBattlePoint={dwBattlePoint} strGuildName={strGuildName}/>;
			else
				topXml = <SRRBattlePointInfo dwBattlePoint={dwBattlePoint} strGuildName={strGuildName}/>;
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
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRRBattlePointInfo
		{
			var s_:SRRBattlePointInfo = new SRRBattlePointInfo();
			var base_:SRoleRankInfo = SRoleRankInfo.fromByteArray(bytes);
			base_.copyTo(s_);
			var dwBattlePoint:uint = bytes.readUnsignedInt();
			s_.dwBattlePoint = dwBattlePoint;
			var strGuildName:String = BytesUtil.readString(bytes);
			s_.strGuildName = strGuildName;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRRBattlePointInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRRBattlePointInfo> = new Vector.<SRRBattlePointInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRRBattlePointInfo = SRRBattlePointInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeUnsignedInt(dwBattlePoint);
			BytesUtil.writeString(bytes, strGuildName);
		}

		public static function vectorToByteArray(vec:Vector.<SRRBattlePointInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRRBattlePointInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
