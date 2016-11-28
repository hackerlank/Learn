/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDBGuildUserInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 数据库加载用帮派玩家数据
	 */
	public final class SDBGuildUserInfo
	{
		public var sBaseInfo:SGuildUserInfo; //帮派用户基本信息
		public var vecTechInfo:Vector.<SGuildTechInfo>; //帮派科技信息
		public var dwBattleScore:uint; //(无符号32位整数)帮派战积分
		public var wPlayerFighterID:uint; //(无符号16位整数)主将ID
		public var byQuality:uint; //(无符号8位整数)主将品质

		/**
		 * 辅助创建函数
		 */
		public static function create(sBaseInfo:SGuildUserInfo, vecTechInfo:Vector.<SGuildTechInfo>, dwBattleScore:uint, wPlayerFighterID:uint, byQuality:uint):SDBGuildUserInfo
		{
			var s_:SDBGuildUserInfo = new SDBGuildUserInfo();
			s_.sBaseInfo = sBaseInfo;
			s_.vecTechInfo = vecTechInfo;
			s_.dwBattleScore = dwBattleScore;
			s_.wPlayerFighterID = wPlayerFighterID;
			s_.byQuality = byQuality;
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
				topXml = <SDBGuildUserInfo _name_={name_} dwBattleScore={dwBattleScore} wPlayerFighterID={wPlayerFighterID} byQuality={byQuality}/>;
			else
				topXml = <SDBGuildUserInfo dwBattleScore={dwBattleScore} wPlayerFighterID={wPlayerFighterID} byQuality={byQuality}/>;
			if(sBaseInfo != null)
				topXml.appendChild(sBaseInfo.toXML("sBaseInfo"));
			if(vecTechInfo != null)
			{
				var vecTechInfoXml:XML = <Vec_SGuildTechInfo _name_="vecTechInfo"/>;
				for each(var s2:SGuildTechInfo in vecTechInfo)
					vecTechInfoXml.appendChild(s2.toXML());
				topXml.appendChild(vecTechInfoXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.sBaseInfo = sBaseInfo;
			obj_.vecTechInfo = vecTechInfo;
			obj_.dwBattleScore = dwBattleScore;
			obj_.wPlayerFighterID = wPlayerFighterID;
			obj_.byQuality = byQuality;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDBGuildUserInfo
		{
			var s_:SDBGuildUserInfo = new SDBGuildUserInfo();
			var sBaseInfo:SGuildUserInfo = SGuildUserInfo.fromByteArray(bytes);
			s_.sBaseInfo = sBaseInfo;
			var vecTechInfo:Vector.<SGuildTechInfo> = SGuildTechInfo.vectorFromByteArray(bytes);
			s_.vecTechInfo = vecTechInfo;
			var dwBattleScore:uint = bytes.readUnsignedInt();
			s_.dwBattleScore = dwBattleScore;
			var wPlayerFighterID:uint = bytes.readUnsignedShort();
			s_.wPlayerFighterID = wPlayerFighterID;
			var byQuality:uint = bytes.readUnsignedByte();
			s_.byQuality = byQuality;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDBGuildUserInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDBGuildUserInfo> = new Vector.<SDBGuildUserInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDBGuildUserInfo = SDBGuildUserInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			sBaseInfo.toByteArray(bytes);
			SGuildTechInfo.vectorToByteArray(vecTechInfo, bytes);
			bytes.writeUnsignedInt(dwBattleScore);
			bytes.writeShort(wPlayerFighterID);
			bytes.writeByte(byQuality);
		}

		public static function vectorToByteArray(vec:Vector.<SDBGuildUserInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDBGuildUserInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
