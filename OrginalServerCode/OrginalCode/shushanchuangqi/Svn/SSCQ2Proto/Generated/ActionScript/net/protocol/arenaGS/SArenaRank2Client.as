/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SArenaRank2Client.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 排行信息
	 */
	public final class SArenaRank2Client
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)ID
		public var dwRank:uint; //(无符号32位整数)名次
		public var dwScore:uint; //(无符号32位整数)积分
		public var stFighter:SArenaFighter; //其它信息
		public var dwFighterPower:uint; //(无符号32位整数)战斗力
		public var byQuality:uint; //(无符号8位整数)品质
		public var byVIPLevel:uint; //(无符号8位整数)品质
		public var dwLadderRank:uint; //(无符号32位整数)天梯排名

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, dwRank:uint, dwScore:uint, stFighter:SArenaFighter, dwFighterPower:uint, 
			byQuality:uint, byVIPLevel:uint, dwLadderRank:uint):SArenaRank2Client
		{
			var s_:SArenaRank2Client = new SArenaRank2Client();
			s_.qwRoleID = qwRoleID;
			s_.dwRank = dwRank;
			s_.dwScore = dwScore;
			s_.stFighter = stFighter;
			s_.dwFighterPower = dwFighterPower;
			s_.byQuality = byQuality;
			s_.byVIPLevel = byVIPLevel;
			s_.dwLadderRank = dwLadderRank;
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
				topXml = <SArenaRank2Client _name_={name_} qwRoleID={qwRoleID} dwRank={dwRank} dwScore={dwScore} dwFighterPower={dwFighterPower}
				 byQuality={byQuality} byVIPLevel={byVIPLevel} dwLadderRank={dwLadderRank}/>;
			else
				topXml = <SArenaRank2Client qwRoleID={qwRoleID} dwRank={dwRank} dwScore={dwScore} dwFighterPower={dwFighterPower}
				 byQuality={byQuality} byVIPLevel={byVIPLevel} dwLadderRank={dwLadderRank}/>;
			if(stFighter != null)
				topXml.appendChild(stFighter.toXML("stFighter"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.dwRank = dwRank;
			obj_.dwScore = dwScore;
			obj_.stFighter = stFighter;
			obj_.dwFighterPower = dwFighterPower;
			obj_.byQuality = byQuality;
			obj_.byVIPLevel = byVIPLevel;
			obj_.dwLadderRank = dwLadderRank;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SArenaRank2Client
		{
			var s_:SArenaRank2Client = new SArenaRank2Client();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var dwRank:uint = bytes.readUnsignedInt();
			s_.dwRank = dwRank;
			var dwScore:uint = bytes.readUnsignedInt();
			s_.dwScore = dwScore;
			var stFighter:SArenaFighter = SArenaFighter.fromByteArray(bytes);
			s_.stFighter = stFighter;
			var dwFighterPower:uint = bytes.readUnsignedInt();
			s_.dwFighterPower = dwFighterPower;
			var byQuality:uint = bytes.readUnsignedByte();
			s_.byQuality = byQuality;
			var byVIPLevel:uint = bytes.readUnsignedByte();
			s_.byVIPLevel = byVIPLevel;
			var dwLadderRank:uint = bytes.readUnsignedInt();
			s_.dwLadderRank = dwLadderRank;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SArenaRank2Client>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SArenaRank2Client> = new Vector.<SArenaRank2Client>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SArenaRank2Client = SArenaRank2Client.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeUnsignedInt(dwRank);
			bytes.writeUnsignedInt(dwScore);
			stFighter.toByteArray(bytes);
			bytes.writeUnsignedInt(dwFighterPower);
			bytes.writeByte(byQuality);
			bytes.writeByte(byVIPLevel);
			bytes.writeUnsignedInt(dwLadderRank);
		}

		public static function vectorToByteArray(vec:Vector.<SArenaRank2Client>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SArenaRank2Client in vec)
				s.toByteArray(bytes);
		}
	}
}
