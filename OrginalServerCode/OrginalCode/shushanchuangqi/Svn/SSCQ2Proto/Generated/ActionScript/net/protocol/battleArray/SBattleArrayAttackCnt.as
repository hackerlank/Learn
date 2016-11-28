/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleArrayAttackCnt.as
//  Purpose:      破阵
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 攻击阵图信息
	 */
	public final class SBattleArrayAttackCnt
	{
		public var dwBattleArrayLevelID:uint; //(无符号32位整数)阵图id
		public var wCount:uint; //(无符号16位整数)次数
		public var wMinTurn:uint; //(无符号16位整数)最小回合数

		/**
		 * 辅助创建函数
		 */
		public static function create(dwBattleArrayLevelID:uint, wCount:uint, wMinTurn:uint):SBattleArrayAttackCnt
		{
			var s_:SBattleArrayAttackCnt = new SBattleArrayAttackCnt();
			s_.dwBattleArrayLevelID = dwBattleArrayLevelID;
			s_.wCount = wCount;
			s_.wMinTurn = wMinTurn;
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
				topXml = <SBattleArrayAttackCnt _name_={name_} dwBattleArrayLevelID={dwBattleArrayLevelID} wCount={wCount} wMinTurn={wMinTurn}/>;
			else
				topXml = <SBattleArrayAttackCnt dwBattleArrayLevelID={dwBattleArrayLevelID} wCount={wCount} wMinTurn={wMinTurn}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwBattleArrayLevelID = dwBattleArrayLevelID;
			obj_.wCount = wCount;
			obj_.wMinTurn = wMinTurn;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleArrayAttackCnt
		{
			var s_:SBattleArrayAttackCnt = new SBattleArrayAttackCnt();
			var dwBattleArrayLevelID:uint = bytes.readUnsignedInt();
			s_.dwBattleArrayLevelID = dwBattleArrayLevelID;
			var wCount:uint = bytes.readUnsignedShort();
			s_.wCount = wCount;
			var wMinTurn:uint = bytes.readUnsignedShort();
			s_.wMinTurn = wMinTurn;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleArrayAttackCnt>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleArrayAttackCnt> = new Vector.<SBattleArrayAttackCnt>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleArrayAttackCnt = SBattleArrayAttackCnt.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwBattleArrayLevelID);
			bytes.writeShort(wCount);
			bytes.writeShort(wMinTurn);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleArrayAttackCnt>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleArrayAttackCnt in vec)
				s.toByteArray(bytes);
		}
	}
}
