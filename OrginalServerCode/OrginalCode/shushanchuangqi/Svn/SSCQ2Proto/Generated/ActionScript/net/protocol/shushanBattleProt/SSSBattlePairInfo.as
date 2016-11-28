/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSSBattlePairInfo.as
//  Purpose:      蜀山论剑相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 论剑场玩家的配对信息，也是发给前端用的信息
	 */
	public final class SSSBattlePairInfo
	{
		public var byRound:uint; //(无符号8位整数)当前轮次
		public var wTimeLeft:uint; //(无符号16位整数)距离下一场【或者开始】时间(秒)
		public var byCurrKill:uint; //(无符号8位整数)当前连杀数
		public var byMaxKill:uint; //(无符号8位整数)最高连杀数
		public var byTotalWin:uint; //(无符号8位整数)胜利场数
		public var byTotalLose:uint; //(无符号8位整数)失败场数
		public var wHonor:uint; //(无符号16位整数)总荣誉值
		public var byDomineer:uint; //(无符号8位整数)霸气值
		public var byAnger:uint; //(无符号8位整数)怒气值
		public var wSkillFlags:uint; //(无符号16位整数)技能使用位域,对应位表示技能是否已使用(低8位)
		public var vecTaskData:Vector.<SBattleTaskData>; //任务数据vec
		public var dwMaxHp:uint; //(无符号32位整数)自己总血量
		public var dwCurHp:uint; //(无符号32位整数)自己当前血量
		public var dwBattlePower:uint; //(无符号32位整数)自己总战斗力
		public var vecOtherPlayer:Vector.<SOtherPlayer>; //对方玩家数据

		/**
		 * 辅助创建函数
		 */
		public static function create(byRound:uint, wTimeLeft:uint, byCurrKill:uint, byMaxKill:uint, byTotalWin:uint, 
			byTotalLose:uint, wHonor:uint, byDomineer:uint, byAnger:uint, wSkillFlags:uint, 
			vecTaskData:Vector.<SBattleTaskData>, dwMaxHp:uint, dwCurHp:uint, dwBattlePower:uint, vecOtherPlayer:Vector.<SOtherPlayer>):SSSBattlePairInfo
		{
			var s_:SSSBattlePairInfo = new SSSBattlePairInfo();
			s_.byRound = byRound;
			s_.wTimeLeft = wTimeLeft;
			s_.byCurrKill = byCurrKill;
			s_.byMaxKill = byMaxKill;
			s_.byTotalWin = byTotalWin;
			s_.byTotalLose = byTotalLose;
			s_.wHonor = wHonor;
			s_.byDomineer = byDomineer;
			s_.byAnger = byAnger;
			s_.wSkillFlags = wSkillFlags;
			s_.vecTaskData = vecTaskData;
			s_.dwMaxHp = dwMaxHp;
			s_.dwCurHp = dwCurHp;
			s_.dwBattlePower = dwBattlePower;
			s_.vecOtherPlayer = vecOtherPlayer;
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
				topXml = <SSSBattlePairInfo _name_={name_} byRound={byRound} wTimeLeft={wTimeLeft} byCurrKill={byCurrKill} byMaxKill={byMaxKill} byTotalWin={byTotalWin}
				 byTotalLose={byTotalLose} wHonor={wHonor} byDomineer={byDomineer} byAnger={byAnger} wSkillFlags={wSkillFlags} dwMaxHp={dwMaxHp} dwCurHp={dwCurHp} dwBattlePower={dwBattlePower}/>;
			else
				topXml = <SSSBattlePairInfo byRound={byRound} wTimeLeft={wTimeLeft} byCurrKill={byCurrKill} byMaxKill={byMaxKill} byTotalWin={byTotalWin}
				 byTotalLose={byTotalLose} wHonor={wHonor} byDomineer={byDomineer} byAnger={byAnger} wSkillFlags={wSkillFlags} dwMaxHp={dwMaxHp} dwCurHp={dwCurHp} dwBattlePower={dwBattlePower}/>;
			if(vecTaskData != null)
			{
				var vecTaskDataXml:XML = <Vec_SBattleTaskData _name_="vecTaskData"/>;
				for each(var s1:SBattleTaskData in vecTaskData)
					vecTaskDataXml.appendChild(s1.toXML());
				topXml.appendChild(vecTaskDataXml);
			}
			if(vecOtherPlayer != null)
			{
				var vecOtherPlayerXml:XML = <Vec_SOtherPlayer _name_="vecOtherPlayer"/>;
				for each(var s2:SOtherPlayer in vecOtherPlayer)
					vecOtherPlayerXml.appendChild(s2.toXML());
				topXml.appendChild(vecOtherPlayerXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byRound = byRound;
			obj_.wTimeLeft = wTimeLeft;
			obj_.byCurrKill = byCurrKill;
			obj_.byMaxKill = byMaxKill;
			obj_.byTotalWin = byTotalWin;
			obj_.byTotalLose = byTotalLose;
			obj_.wHonor = wHonor;
			obj_.byDomineer = byDomineer;
			obj_.byAnger = byAnger;
			obj_.wSkillFlags = wSkillFlags;
			obj_.vecTaskData = vecTaskData;
			obj_.dwMaxHp = dwMaxHp;
			obj_.dwCurHp = dwCurHp;
			obj_.dwBattlePower = dwBattlePower;
			obj_.vecOtherPlayer = vecOtherPlayer;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSSBattlePairInfo
		{
			var s_:SSSBattlePairInfo = new SSSBattlePairInfo();
			var byRound:uint = bytes.readUnsignedByte();
			s_.byRound = byRound;
			var wTimeLeft:uint = bytes.readUnsignedShort();
			s_.wTimeLeft = wTimeLeft;
			var byCurrKill:uint = bytes.readUnsignedByte();
			s_.byCurrKill = byCurrKill;
			var byMaxKill:uint = bytes.readUnsignedByte();
			s_.byMaxKill = byMaxKill;
			var byTotalWin:uint = bytes.readUnsignedByte();
			s_.byTotalWin = byTotalWin;
			var byTotalLose:uint = bytes.readUnsignedByte();
			s_.byTotalLose = byTotalLose;
			var wHonor:uint = bytes.readUnsignedShort();
			s_.wHonor = wHonor;
			var byDomineer:uint = bytes.readUnsignedByte();
			s_.byDomineer = byDomineer;
			var byAnger:uint = bytes.readUnsignedByte();
			s_.byAnger = byAnger;
			var wSkillFlags:uint = bytes.readUnsignedShort();
			s_.wSkillFlags = wSkillFlags;
			var vecTaskData:Vector.<SBattleTaskData> = SBattleTaskData.vectorFromByteArray(bytes);
			s_.vecTaskData = vecTaskData;
			var dwMaxHp:uint = bytes.readUnsignedInt();
			s_.dwMaxHp = dwMaxHp;
			var dwCurHp:uint = bytes.readUnsignedInt();
			s_.dwCurHp = dwCurHp;
			var dwBattlePower:uint = bytes.readUnsignedInt();
			s_.dwBattlePower = dwBattlePower;
			var vecOtherPlayer:Vector.<SOtherPlayer> = SOtherPlayer.vectorFromByteArray(bytes);
			s_.vecOtherPlayer = vecOtherPlayer;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSSBattlePairInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSSBattlePairInfo> = new Vector.<SSSBattlePairInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSSBattlePairInfo = SSSBattlePairInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byRound);
			bytes.writeShort(wTimeLeft);
			bytes.writeByte(byCurrKill);
			bytes.writeByte(byMaxKill);
			bytes.writeByte(byTotalWin);
			bytes.writeByte(byTotalLose);
			bytes.writeShort(wHonor);
			bytes.writeByte(byDomineer);
			bytes.writeByte(byAnger);
			bytes.writeShort(wSkillFlags);
			SBattleTaskData.vectorToByteArray(vecTaskData, bytes);
			bytes.writeUnsignedInt(dwMaxHp);
			bytes.writeUnsignedInt(dwCurHp);
			bytes.writeUnsignedInt(dwBattlePower);
			SOtherPlayer.vectorToByteArray(vecOtherPlayer, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SSSBattlePairInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSSBattlePairInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
