/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    FightFormationInfo.as
//  Purpose:      新阵型相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fightFormation
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战斗阵型信息
	 */
	public final class FightFormationInfo
	{
		public var wFormationID:uint; //(无符号16位整数)当前阵形ID
		public var vecBattlePosInfo:Vector.<SBattlePosInfo>; //位置

		/**
		 * 辅助创建函数
		 */
		public static function create(wFormationID:uint, vecBattlePosInfo:Vector.<SBattlePosInfo>):FightFormationInfo
		{
			var s_:FightFormationInfo = new FightFormationInfo();
			s_.wFormationID = wFormationID;
			s_.vecBattlePosInfo = vecBattlePosInfo;
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
				topXml = <FightFormationInfo _name_={name_} wFormationID={wFormationID}/>;
			else
				topXml = <FightFormationInfo wFormationID={wFormationID}/>;
			if(vecBattlePosInfo != null)
			{
				var vecBattlePosInfoXml:XML = <Vec_SBattlePosInfo _name_="vecBattlePosInfo"/>;
				for each(var s1:SBattlePosInfo in vecBattlePosInfo)
					vecBattlePosInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecBattlePosInfoXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wFormationID = wFormationID;
			obj_.vecBattlePosInfo = vecBattlePosInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):FightFormationInfo
		{
			var s_:FightFormationInfo = new FightFormationInfo();
			var wFormationID:uint = bytes.readUnsignedShort();
			s_.wFormationID = wFormationID;
			var vecBattlePosInfo:Vector.<SBattlePosInfo> = SBattlePosInfo.vectorFromByteArray(bytes);
			s_.vecBattlePosInfo = vecBattlePosInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<FightFormationInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<FightFormationInfo> = new Vector.<FightFormationInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:FightFormationInfo = FightFormationInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wFormationID);
			SBattlePosInfo.vectorToByteArray(vecBattlePosInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<FightFormationInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:FightFormationInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
