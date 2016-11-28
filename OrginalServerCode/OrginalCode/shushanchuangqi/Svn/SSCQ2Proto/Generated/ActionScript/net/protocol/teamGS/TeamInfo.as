/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    TeamInfo.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 队伍信息
	 */
	public final class TeamInfo
	{
		public var TeamID:uint; //(无符号32位整数)队伍ID
		public var DgnType:uint; //(无符号16位整数)副本模板
		public var TeamLeader:BigInteger; //(无符号64位整数)队长ID
		public var qwPetOwner:BigInteger; //(无符号64位整数)出战阵灵的拥有者
		public var stSetting:TeamSetting; //队伍设置
		public var vecMember:Vector.<TeamMember>; //队伍成员

		/**
		 * 辅助创建函数
		 */
		public static function create(TeamID:uint, DgnType:uint, TeamLeader:BigInteger, qwPetOwner:BigInteger, stSetting:TeamSetting, 
			vecMember:Vector.<TeamMember>):TeamInfo
		{
			var s_:TeamInfo = new TeamInfo();
			s_.TeamID = TeamID;
			s_.DgnType = DgnType;
			s_.TeamLeader = TeamLeader;
			s_.qwPetOwner = qwPetOwner;
			s_.stSetting = stSetting;
			s_.vecMember = vecMember;
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
				topXml = <TeamInfo _name_={name_} TeamID={TeamID} DgnType={DgnType} TeamLeader={TeamLeader} qwPetOwner={qwPetOwner}/>;
			else
				topXml = <TeamInfo TeamID={TeamID} DgnType={DgnType} TeamLeader={TeamLeader} qwPetOwner={qwPetOwner}/>;
			if(stSetting != null)
				topXml.appendChild(stSetting.toXML("stSetting"));
			if(vecMember != null)
			{
				var vecMemberXml:XML = <Vec_TeamMember _name_="vecMember"/>;
				for each(var s2:TeamMember in vecMember)
					vecMemberXml.appendChild(s2.toXML());
				topXml.appendChild(vecMemberXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.TeamID = TeamID;
			obj_.DgnType = DgnType;
			obj_.TeamLeader = TeamLeader;
			obj_.qwPetOwner = qwPetOwner;
			obj_.stSetting = stSetting;
			obj_.vecMember = vecMember;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):TeamInfo
		{
			var s_:TeamInfo = new TeamInfo();
			var TeamID:uint = bytes.readUnsignedInt();
			s_.TeamID = TeamID;
			var DgnType:uint = bytes.readUnsignedShort();
			s_.DgnType = DgnType;
			var TeamLeader:BigInteger = BytesUtil.readUInt64(bytes);
			s_.TeamLeader = TeamLeader;
			var qwPetOwner:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwPetOwner = qwPetOwner;
			var stSetting:TeamSetting = TeamSetting.fromByteArray(bytes);
			s_.stSetting = stSetting;
			var vecMember:Vector.<TeamMember> = TeamMember.vectorFromByteArray(bytes);
			s_.vecMember = vecMember;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<TeamInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<TeamInfo> = new Vector.<TeamInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:TeamInfo = TeamInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(TeamID);
			bytes.writeShort(DgnType);
			BytesUtil.writeUInt64(bytes, TeamLeader);
			BytesUtil.writeUInt64(bytes, qwPetOwner);
			stSetting.toByteArray(bytes);
			TeamMember.vectorToByteArray(vecMember, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<TeamInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:TeamInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
