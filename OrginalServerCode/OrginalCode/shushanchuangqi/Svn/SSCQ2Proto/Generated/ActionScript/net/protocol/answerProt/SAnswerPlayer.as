/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SAnswerPlayer.as
//  Purpose:      答题协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家信息
	 */
	public final class SAnswerPlayer
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var bRight:Boolean; //本次答题是否正确
		public var dwThisScore:uint; //(无符号32位整数)本题玩家获得积分
		public var dwScore:uint; //(无符号32位整数)玩家积分
		public var dwRank:uint; //(无符号32位整数)玩家排名
		public var dwRight:uint; //(无符号32位整数)玩家答对题目数
		public var dwUntilFail:uint; //(无符号32位整数)连续答对题目数
		public var vecSkillInfo:Vector.<SAnswerSkill>; //技能信息

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, bRight:Boolean, dwThisScore:uint, dwScore:uint, dwRank:uint, 
			dwRight:uint, dwUntilFail:uint, vecSkillInfo:Vector.<SAnswerSkill>):SAnswerPlayer
		{
			var s_:SAnswerPlayer = new SAnswerPlayer();
			s_.qwRoleID = qwRoleID;
			s_.bRight = bRight;
			s_.dwThisScore = dwThisScore;
			s_.dwScore = dwScore;
			s_.dwRank = dwRank;
			s_.dwRight = dwRight;
			s_.dwUntilFail = dwUntilFail;
			s_.vecSkillInfo = vecSkillInfo;
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
				topXml = <SAnswerPlayer _name_={name_} qwRoleID={qwRoleID} bRight={bRight} dwThisScore={dwThisScore} dwScore={dwScore} dwRank={dwRank}
				 dwRight={dwRight} dwUntilFail={dwUntilFail}/>;
			else
				topXml = <SAnswerPlayer qwRoleID={qwRoleID} bRight={bRight} dwThisScore={dwThisScore} dwScore={dwScore} dwRank={dwRank}
				 dwRight={dwRight} dwUntilFail={dwUntilFail}/>;
			if(vecSkillInfo != null)
			{
				var vecSkillInfoXml:XML = <Vec_SAnswerSkill _name_="vecSkillInfo"/>;
				for each(var s1:SAnswerSkill in vecSkillInfo)
					vecSkillInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecSkillInfoXml);
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
			obj_.bRight = bRight;
			obj_.dwThisScore = dwThisScore;
			obj_.dwScore = dwScore;
			obj_.dwRank = dwRank;
			obj_.dwRight = dwRight;
			obj_.dwUntilFail = dwUntilFail;
			obj_.vecSkillInfo = vecSkillInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SAnswerPlayer
		{
			var s_:SAnswerPlayer = new SAnswerPlayer();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var bRight:Boolean = bytes.readBoolean();
			s_.bRight = bRight;
			var dwThisScore:uint = bytes.readUnsignedInt();
			s_.dwThisScore = dwThisScore;
			var dwScore:uint = bytes.readUnsignedInt();
			s_.dwScore = dwScore;
			var dwRank:uint = bytes.readUnsignedInt();
			s_.dwRank = dwRank;
			var dwRight:uint = bytes.readUnsignedInt();
			s_.dwRight = dwRight;
			var dwUntilFail:uint = bytes.readUnsignedInt();
			s_.dwUntilFail = dwUntilFail;
			var vecSkillInfo:Vector.<SAnswerSkill> = SAnswerSkill.vectorFromByteArray(bytes);
			s_.vecSkillInfo = vecSkillInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SAnswerPlayer>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SAnswerPlayer> = new Vector.<SAnswerPlayer>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SAnswerPlayer = SAnswerPlayer.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeBoolean(bRight);
			bytes.writeUnsignedInt(dwThisScore);
			bytes.writeUnsignedInt(dwScore);
			bytes.writeUnsignedInt(dwRank);
			bytes.writeUnsignedInt(dwRight);
			bytes.writeUnsignedInt(dwUntilFail);
			SAnswerSkill.vectorToByteArray(vecSkillInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SAnswerPlayer>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SAnswerPlayer in vec)
				s.toByteArray(bytes);
		}
	}
}
