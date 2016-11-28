/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGEMPrepareBattleInfo.as
//  Purpose:      守卫峨眉协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 守卫峨眉准备战斗信息
	 */
	public final class SGEMPrepareBattleInfo
	{
		public var wCurProgress:uint; //(无符号16位整数)当前进度
		public var dwMonsterID:uint; //(无符号32位整数)怪物ID
		public var dwBattlePoint:uint; //(无符号32位整数)参战散仙战斗力
		public var vecGEMBuffInfo:Vector.<SGEMBuffInfo>; //守卫峨眉Buff信息
		public var vecGEMBattleFighterInfo:Vector.<SGEMBattleFighterInfo>; //守卫峨眉参战散仙信息

		/**
		 * 辅助创建函数
		 */
		public static function create(wCurProgress:uint, dwMonsterID:uint, dwBattlePoint:uint, vecGEMBuffInfo:Vector.<SGEMBuffInfo>, vecGEMBattleFighterInfo:Vector.<SGEMBattleFighterInfo>):SGEMPrepareBattleInfo
		{
			var s_:SGEMPrepareBattleInfo = new SGEMPrepareBattleInfo();
			s_.wCurProgress = wCurProgress;
			s_.dwMonsterID = dwMonsterID;
			s_.dwBattlePoint = dwBattlePoint;
			s_.vecGEMBuffInfo = vecGEMBuffInfo;
			s_.vecGEMBattleFighterInfo = vecGEMBattleFighterInfo;
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
				topXml = <SGEMPrepareBattleInfo _name_={name_} wCurProgress={wCurProgress} dwMonsterID={dwMonsterID} dwBattlePoint={dwBattlePoint}/>;
			else
				topXml = <SGEMPrepareBattleInfo wCurProgress={wCurProgress} dwMonsterID={dwMonsterID} dwBattlePoint={dwBattlePoint}/>;
			if(vecGEMBuffInfo != null)
			{
				var vecGEMBuffInfoXml:XML = <Vec_SGEMBuffInfo _name_="vecGEMBuffInfo"/>;
				for each(var s1:SGEMBuffInfo in vecGEMBuffInfo)
					vecGEMBuffInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecGEMBuffInfoXml);
			}
			if(vecGEMBattleFighterInfo != null)
			{
				var vecGEMBattleFighterInfoXml:XML = <Vec_SGEMBattleFighterInfo _name_="vecGEMBattleFighterInfo"/>;
				for each(var s2:SGEMBattleFighterInfo in vecGEMBattleFighterInfo)
					vecGEMBattleFighterInfoXml.appendChild(s2.toXML());
				topXml.appendChild(vecGEMBattleFighterInfoXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wCurProgress = wCurProgress;
			obj_.dwMonsterID = dwMonsterID;
			obj_.dwBattlePoint = dwBattlePoint;
			obj_.vecGEMBuffInfo = vecGEMBuffInfo;
			obj_.vecGEMBattleFighterInfo = vecGEMBattleFighterInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGEMPrepareBattleInfo
		{
			var s_:SGEMPrepareBattleInfo = new SGEMPrepareBattleInfo();
			var wCurProgress:uint = bytes.readUnsignedShort();
			s_.wCurProgress = wCurProgress;
			var dwMonsterID:uint = bytes.readUnsignedInt();
			s_.dwMonsterID = dwMonsterID;
			var dwBattlePoint:uint = bytes.readUnsignedInt();
			s_.dwBattlePoint = dwBattlePoint;
			var vecGEMBuffInfo:Vector.<SGEMBuffInfo> = SGEMBuffInfo.vectorFromByteArray(bytes);
			s_.vecGEMBuffInfo = vecGEMBuffInfo;
			var vecGEMBattleFighterInfo:Vector.<SGEMBattleFighterInfo> = SGEMBattleFighterInfo.vectorFromByteArray(bytes);
			s_.vecGEMBattleFighterInfo = vecGEMBattleFighterInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGEMPrepareBattleInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGEMPrepareBattleInfo> = new Vector.<SGEMPrepareBattleInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGEMPrepareBattleInfo = SGEMPrepareBattleInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wCurProgress);
			bytes.writeUnsignedInt(dwMonsterID);
			bytes.writeUnsignedInt(dwBattlePoint);
			SGEMBuffInfo.vectorToByteArray(vecGEMBuffInfo, bytes);
			SGEMBattleFighterInfo.vectorToByteArray(vecGEMBattleFighterInfo, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SGEMPrepareBattleInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGEMPrepareBattleInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
