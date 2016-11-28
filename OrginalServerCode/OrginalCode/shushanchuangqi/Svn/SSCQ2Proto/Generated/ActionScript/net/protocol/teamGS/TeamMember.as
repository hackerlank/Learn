/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    TeamMember.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SPlatformParam;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 队伍玩家
	 */
	public final class TeamMember
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var byPos:uint; //(无符号8位整数)位置
		public var strName:String; //名字
		public var eStatus:uint; //(枚举类型：EMemberStatus)玩家状态
		public var byVIPLevel:uint; //(无符号8位整数)vip等级
		public var oPlatformParam:SPlatformParam; //qq平台信息
		public var vecFighter:Vector.<TeamFighter>; //战斗对象

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, byPos:uint, strName:String, eStatus:uint, byVIPLevel:uint, 
			oPlatformParam:SPlatformParam, vecFighter:Vector.<TeamFighter>):TeamMember
		{
			var s_:TeamMember = new TeamMember();
			s_.qwRoleID = qwRoleID;
			s_.byPos = byPos;
			s_.strName = strName;
			s_.eStatus = eStatus;
			s_.byVIPLevel = byVIPLevel;
			s_.oPlatformParam = oPlatformParam;
			s_.vecFighter = vecFighter;
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
				topXml = <TeamMember _name_={name_} qwRoleID={qwRoleID} byPos={byPos} strName={strName} eStatus={eStatus} byVIPLevel={byVIPLevel}/>;
			else
				topXml = <TeamMember qwRoleID={qwRoleID} byPos={byPos} strName={strName} eStatus={eStatus} byVIPLevel={byVIPLevel}/>;
			if(oPlatformParam != null)
				topXml.appendChild(oPlatformParam.toXML("oPlatformParam"));
			if(vecFighter != null)
			{
				var vecFighterXml:XML = <Vec_TeamFighter _name_="vecFighter"/>;
				for each(var s2:TeamFighter in vecFighter)
					vecFighterXml.appendChild(s2.toXML());
				topXml.appendChild(vecFighterXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.byPos = byPos;
			obj_.strName = strName;
			obj_.eStatus = eStatus;
			obj_.byVIPLevel = byVIPLevel;
			obj_.oPlatformParam = oPlatformParam;
			obj_.vecFighter = vecFighter;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):TeamMember
		{
			var s_:TeamMember = new TeamMember();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var byPos:uint = bytes.readUnsignedByte();
			s_.byPos = byPos;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var eStatus:uint = bytes.readUnsignedByte();
			s_.eStatus = eStatus;
			var byVIPLevel:uint = bytes.readUnsignedByte();
			s_.byVIPLevel = byVIPLevel;
			var oPlatformParam:SPlatformParam = SPlatformParam.fromByteArray(bytes);
			s_.oPlatformParam = oPlatformParam;
			var vecFighter:Vector.<TeamFighter> = TeamFighter.superVectorFromByteArray(bytes);
			s_.vecFighter = vecFighter;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<TeamMember>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<TeamMember> = new Vector.<TeamMember>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:TeamMember = TeamMember.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeByte(byPos);
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(eStatus);
			bytes.writeByte(byVIPLevel);
			oPlatformParam.toByteArray(bytes);
			TeamFighter.superVectorToByteArray(vecFighter, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<TeamMember>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:TeamMember in vec)
				s.toByteArray(bytes);
		}
	}
}
