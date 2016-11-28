/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    TeamInfoForList.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 房间列表信息
	 */
	public final class TeamInfoForList
	{
		public var TeamID:uint; //(无符号32位整数)队伍ID
		public var DgnType:uint; //(无符号16位整数)房间ID
		public var stSetting:TeamSetting; //队伍设置密码0 或 1，1表示有密码
		public var stLeader:TeamFighter; //队长信息
		public var strLeaderName:String; //队长名字
		public var bySize:uint; //(无符号8位整数)当前人数

		/**
		 * 辅助创建函数
		 */
		public static function create(TeamID:uint, DgnType:uint, stSetting:TeamSetting, stLeader:TeamFighter, strLeaderName:String, 
			bySize:uint):TeamInfoForList
		{
			var s_:TeamInfoForList = new TeamInfoForList();
			s_.TeamID = TeamID;
			s_.DgnType = DgnType;
			s_.stSetting = stSetting;
			s_.stLeader = stLeader;
			s_.strLeaderName = strLeaderName;
			s_.bySize = bySize;
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
				topXml = <TeamInfoForList _name_={name_} TeamID={TeamID} DgnType={DgnType} strLeaderName={strLeaderName}
				 bySize={bySize}/>;
			else
				topXml = <TeamInfoForList TeamID={TeamID} DgnType={DgnType} strLeaderName={strLeaderName}
				 bySize={bySize}/>;
			if(stSetting != null)
				topXml.appendChild(stSetting.toXML("stSetting"));
			if(stLeader != null)
				topXml.appendChild(stLeader.toXML("stLeader"));
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
			obj_.stSetting = stSetting;
			obj_.stLeader = stLeader;
			obj_.strLeaderName = strLeaderName;
			obj_.bySize = bySize;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):TeamInfoForList
		{
			var s_:TeamInfoForList = new TeamInfoForList();
			var TeamID:uint = bytes.readUnsignedInt();
			s_.TeamID = TeamID;
			var DgnType:uint = bytes.readUnsignedShort();
			s_.DgnType = DgnType;
			var stSetting:TeamSetting = TeamSetting.fromByteArray(bytes);
			s_.stSetting = stSetting;
			var stLeader:TeamFighter = TeamFighter.superFromByteArray(bytes);
			s_.stLeader = stLeader;
			var strLeaderName:String = BytesUtil.readString(bytes);
			s_.strLeaderName = strLeaderName;
			var bySize:uint = bytes.readUnsignedByte();
			s_.bySize = bySize;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<TeamInfoForList>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<TeamInfoForList> = new Vector.<TeamInfoForList>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:TeamInfoForList = TeamInfoForList.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(TeamID);
			bytes.writeShort(DgnType);
			stSetting.toByteArray(bytes);
			stLeader.superToByteArray(bytes);
			BytesUtil.writeString(bytes, strLeaderName);
			bytes.writeByte(bySize);
		}

		public static function vectorToByteArray(vec:Vector.<TeamInfoForList>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:TeamInfoForList in vec)
				s.toByteArray(bytes);
		}
	}
}
