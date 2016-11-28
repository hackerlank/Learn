/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleGroup.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战斗小队
	 */
	public final class SBattleGroup
	{
		public var byGroupID:uint; //(无符号8位整数)组ID
		public var qwCreatrueID:BigInteger; //(无符号64位整数)玩家ID，地图上跑的时候用的那个ID，怪物为0
		public var qwLeaderID:BigInteger; //(无符号64位整数)队伍主将ID
		public var wLevel:uint; //(无符号16位整数)队伍等级
		public var vFighters:Vector.<SBattleFighter>; //队伍里面的所有fighter
		public var vecCombineSkillInfo:Vector.<STeamSkillInfo>; //队伍中的连携技能
		public var pMainFeature:SFeatureBase; //主将外观信息(用于显示头像用)
		public var dwBattlePoint:uint; //(无符号32位整数)战斗力

		/**
		 * 辅助创建函数
		 */
		public static function create(byGroupID:uint, qwCreatrueID:BigInteger, qwLeaderID:BigInteger, wLevel:uint, vFighters:Vector.<SBattleFighter>, 
			vecCombineSkillInfo:Vector.<STeamSkillInfo>, pMainFeature:SFeatureBase, dwBattlePoint:uint):SBattleGroup
		{
			var s_:SBattleGroup = new SBattleGroup();
			s_.byGroupID = byGroupID;
			s_.qwCreatrueID = qwCreatrueID;
			s_.qwLeaderID = qwLeaderID;
			s_.wLevel = wLevel;
			s_.vFighters = vFighters;
			s_.vecCombineSkillInfo = vecCombineSkillInfo;
			s_.pMainFeature = pMainFeature;
			s_.dwBattlePoint = dwBattlePoint;
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
				topXml = <SBattleGroup _name_={name_} byGroupID={byGroupID} qwCreatrueID={qwCreatrueID} qwLeaderID={qwLeaderID} wLevel={wLevel} dwBattlePoint={dwBattlePoint}/>;
			else
				topXml = <SBattleGroup byGroupID={byGroupID} qwCreatrueID={qwCreatrueID} qwLeaderID={qwLeaderID} wLevel={wLevel} dwBattlePoint={dwBattlePoint}/>;
			if(vFighters != null)
			{
				var vFightersXml:XML = <Vec_SBattleFighter _name_="vFighters"/>;
				for each(var s1:SBattleFighter in vFighters)
					vFightersXml.appendChild(s1.toXML());
				topXml.appendChild(vFightersXml);
			}
			if(vecCombineSkillInfo != null)
			{
				var vecCombineSkillInfoXml:XML = <Vec_STeamSkillInfo _name_="vecCombineSkillInfo"/>;
				for each(var s2:STeamSkillInfo in vecCombineSkillInfo)
					vecCombineSkillInfoXml.appendChild(s2.toXML());
				topXml.appendChild(vecCombineSkillInfoXml);
			}
			if(pMainFeature != null)
				topXml.appendChild(pMainFeature.toXML("pMainFeature"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byGroupID = byGroupID;
			obj_.qwCreatrueID = qwCreatrueID;
			obj_.qwLeaderID = qwLeaderID;
			obj_.wLevel = wLevel;
			obj_.vFighters = vFighters;
			obj_.vecCombineSkillInfo = vecCombineSkillInfo;
			obj_.pMainFeature = pMainFeature;
			obj_.dwBattlePoint = dwBattlePoint;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleGroup
		{
			var s_:SBattleGroup = new SBattleGroup();
			var byGroupID:uint = bytes.readUnsignedByte();
			s_.byGroupID = byGroupID;
			var qwCreatrueID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwCreatrueID = qwCreatrueID;
			var qwLeaderID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwLeaderID = qwLeaderID;
			var wLevel:uint = bytes.readUnsignedShort();
			s_.wLevel = wLevel;
			var vFighters:Vector.<SBattleFighter> = SBattleFighter.vectorFromByteArray(bytes);
			s_.vFighters = vFighters;
			var vecCombineSkillInfo:Vector.<STeamSkillInfo> = STeamSkillInfo.vectorFromByteArray(bytes);
			s_.vecCombineSkillInfo = vecCombineSkillInfo;
			var pMainFeature:SFeatureBase = SFeatureBase.superFromByteArray(bytes);
			s_.pMainFeature = pMainFeature;
			var dwBattlePoint:uint = bytes.readUnsignedInt();
			s_.dwBattlePoint = dwBattlePoint;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleGroup>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleGroup> = new Vector.<SBattleGroup>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleGroup = SBattleGroup.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byGroupID);
			BytesUtil.writeUInt64(bytes, qwCreatrueID);
			BytesUtil.writeUInt64(bytes, qwLeaderID);
			bytes.writeShort(wLevel);
			SBattleFighter.vectorToByteArray(vFighters, bytes);
			STeamSkillInfo.vectorToByteArray(vecCombineSkillInfo, bytes);
			pMainFeature.superToByteArray(bytes);
			bytes.writeUnsignedInt(dwBattlePoint);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleGroup>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleGroup in vec)
				s.toByteArray(bytes);
		}
	}
}
