/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleReport.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import com.hurlant.math.BigInteger;
	import net.protocol.itemProt.SItemGenInfo;
	import net.protocol.itemProt.SResource;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战报
	 */
	public final class SBattleReport
	{
		public var qwBattleID:BigInteger; //(无符号64位整数)战报ID
		public var qwNextBattleID:BigInteger; //(无符号64位整数)next战报ID
		public var wSceneID:uint; //(无符号16位整数)战斗场景ID
		public var by1Vs1:uint; //(无符号8位整数)0:普通一打多，1：普通一打一，2：boss一打多， 3：boss一打一
		public var eType:uint; //(枚举类型：EBattleType)战斗模式：PVP/PVE
		public var vAGroups:Vector.<SBattleGroup>; //A队伍里的所有小组
		public var vBGroups:Vector.<SBattleGroup>; //B队伍里的所有小组
		public var vSummons:Vector.<SBattleFighter>; //战斗中可能召唤的散仙
		public var vRound:Vector.<SBattleRound>; //所有的出手回合
		public var byAWaves:uint; //(无符号8位整数)A队剩余波数
		public var byBWaves:uint; //(无符号8位整数)B队剩余波数
		public var eResult:uint; //(枚举类型：EBattleResult)战斗结果
		public var vecItem:Vector.<SItemGenInfo>; //获得物品
		public var vecResSource:Vector.<SResource>; //获得资源

		/**
		 * 辅助创建函数
		 */
		public static function create(qwBattleID:BigInteger, qwNextBattleID:BigInteger, wSceneID:uint, by1Vs1:uint, eType:uint, 
			vAGroups:Vector.<SBattleGroup>, vBGroups:Vector.<SBattleGroup>, vSummons:Vector.<SBattleFighter>, vRound:Vector.<SBattleRound>, byAWaves:uint, 
			byBWaves:uint, eResult:uint, vecItem:Vector.<SItemGenInfo>, vecResSource:Vector.<SResource>):SBattleReport
		{
			var s_:SBattleReport = new SBattleReport();
			s_.qwBattleID = qwBattleID;
			s_.qwNextBattleID = qwNextBattleID;
			s_.wSceneID = wSceneID;
			s_.by1Vs1 = by1Vs1;
			s_.eType = eType;
			s_.vAGroups = vAGroups;
			s_.vBGroups = vBGroups;
			s_.vSummons = vSummons;
			s_.vRound = vRound;
			s_.byAWaves = byAWaves;
			s_.byBWaves = byBWaves;
			s_.eResult = eResult;
			s_.vecItem = vecItem;
			s_.vecResSource = vecResSource;
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
				topXml = <SBattleReport _name_={name_} qwBattleID={qwBattleID} qwNextBattleID={qwNextBattleID} wSceneID={wSceneID} by1Vs1={by1Vs1} eType={eType} byAWaves={byAWaves}
				 byBWaves={byBWaves} eResult={eResult}/>;
			else
				topXml = <SBattleReport qwBattleID={qwBattleID} qwNextBattleID={qwNextBattleID} wSceneID={wSceneID} by1Vs1={by1Vs1} eType={eType} byAWaves={byAWaves}
				 byBWaves={byBWaves} eResult={eResult}/>;
			if(vAGroups != null)
			{
				var vAGroupsXml:XML = <Vec_SBattleGroup _name_="vAGroups"/>;
				for each(var s1:SBattleGroup in vAGroups)
					vAGroupsXml.appendChild(s1.toXML());
				topXml.appendChild(vAGroupsXml);
			}
			if(vBGroups != null)
			{
				var vBGroupsXml:XML = <Vec_SBattleGroup _name_="vBGroups"/>;
				for each(var s2:SBattleGroup in vBGroups)
					vBGroupsXml.appendChild(s2.toXML());
				topXml.appendChild(vBGroupsXml);
			}
			if(vSummons != null)
			{
				var vSummonsXml:XML = <Vec_SBattleFighter _name_="vSummons"/>;
				for each(var s3:SBattleFighter in vSummons)
					vSummonsXml.appendChild(s3.toXML());
				topXml.appendChild(vSummonsXml);
			}
			if(vRound != null)
			{
				var vRoundXml:XML = <Vec_SBattleRound _name_="vRound"/>;
				for each(var s4:SBattleRound in vRound)
					vRoundXml.appendChild(s4.toXML());
				topXml.appendChild(vRoundXml);
			}
			if(vecItem != null)
			{
				var vecItemXml:XML = <Vec_SItemGenInfo _name_="vecItem"/>;
				for each(var s5:SItemGenInfo in vecItem)
					vecItemXml.appendChild(s5.toXML());
				topXml.appendChild(vecItemXml);
			}
			if(vecResSource != null)
			{
				var vecResSourceXml:XML = <Vec_SResource _name_="vecResSource"/>;
				for each(var s6:SResource in vecResSource)
					vecResSourceXml.appendChild(s6.toXML());
				topXml.appendChild(vecResSourceXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwBattleID = qwBattleID;
			obj_.qwNextBattleID = qwNextBattleID;
			obj_.wSceneID = wSceneID;
			obj_.by1Vs1 = by1Vs1;
			obj_.eType = eType;
			obj_.vAGroups = vAGroups;
			obj_.vBGroups = vBGroups;
			obj_.vSummons = vSummons;
			obj_.vRound = vRound;
			obj_.byAWaves = byAWaves;
			obj_.byBWaves = byBWaves;
			obj_.eResult = eResult;
			obj_.vecItem = vecItem;
			obj_.vecResSource = vecResSource;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleReport
		{
			var s_:SBattleReport = new SBattleReport();
			var qwBattleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwBattleID = qwBattleID;
			var qwNextBattleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwNextBattleID = qwNextBattleID;
			var wSceneID:uint = bytes.readUnsignedShort();
			s_.wSceneID = wSceneID;
			var by1Vs1:uint = bytes.readUnsignedByte();
			s_.by1Vs1 = by1Vs1;
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
			var vAGroups:Vector.<SBattleGroup> = SBattleGroup.vectorFromByteArray(bytes);
			s_.vAGroups = vAGroups;
			var vBGroups:Vector.<SBattleGroup> = SBattleGroup.vectorFromByteArray(bytes);
			s_.vBGroups = vBGroups;
			var vSummons:Vector.<SBattleFighter> = SBattleFighter.vectorFromByteArray(bytes);
			s_.vSummons = vSummons;
			var vRound:Vector.<SBattleRound> = SBattleRound.vectorFromByteArray(bytes);
			s_.vRound = vRound;
			var byAWaves:uint = bytes.readUnsignedByte();
			s_.byAWaves = byAWaves;
			var byBWaves:uint = bytes.readUnsignedByte();
			s_.byBWaves = byBWaves;
			var eResult:uint = bytes.readUnsignedByte();
			s_.eResult = eResult;
			var vecItem:Vector.<SItemGenInfo> = SItemGenInfo.vectorFromByteArray(bytes);
			s_.vecItem = vecItem;
			var vecResSource:Vector.<SResource> = SResource.vectorFromByteArray(bytes);
			s_.vecResSource = vecResSource;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleReport>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleReport> = new Vector.<SBattleReport>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleReport = SBattleReport.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwBattleID);
			BytesUtil.writeUInt64(bytes, qwNextBattleID);
			bytes.writeShort(wSceneID);
			bytes.writeByte(by1Vs1);
			bytes.writeByte(eType);
			SBattleGroup.vectorToByteArray(vAGroups, bytes);
			SBattleGroup.vectorToByteArray(vBGroups, bytes);
			SBattleFighter.vectorToByteArray(vSummons, bytes);
			SBattleRound.vectorToByteArray(vRound, bytes);
			bytes.writeByte(byAWaves);
			bytes.writeByte(byBWaves);
			bytes.writeByte(eResult);
			SItemGenInfo.vectorToByteArray(vecItem, bytes);
			SResource.vectorToByteArray(vecResSource, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleReport>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleReport in vec)
				s.toByteArray(bytes);
		}
	}
}
