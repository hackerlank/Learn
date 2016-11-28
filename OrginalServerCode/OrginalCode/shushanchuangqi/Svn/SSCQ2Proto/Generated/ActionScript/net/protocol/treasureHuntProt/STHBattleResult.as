/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STHBattleResult.as
//  Purpose:      寻宝协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战斗结果
	 */
	public final class STHBattleResult
	{
		public var byCopyID:uint; //(无符号8位整数)副本ID
		public var dwTotalTimes:uint; //(无符号32位整数)寻宝时间
		public var dwCurBossHP:uint; //(无符号32位整数)当前BOSS血量
		public var dwCurSilverNUm:uint; //(无符号32位整数)当前掉落银币数量
		public var dwCurItemNum:uint; //(无符号32位整数)当前掉落物品数量
		public var dwCurXFCYNum:uint; //(无符号32位整数)当前掉落心法残页数量

		/**
		 * 辅助创建函数
		 */
		public static function create(byCopyID:uint, dwTotalTimes:uint, dwCurBossHP:uint, dwCurSilverNUm:uint, dwCurItemNum:uint, 
			dwCurXFCYNum:uint):STHBattleResult
		{
			var s_:STHBattleResult = new STHBattleResult();
			s_.byCopyID = byCopyID;
			s_.dwTotalTimes = dwTotalTimes;
			s_.dwCurBossHP = dwCurBossHP;
			s_.dwCurSilverNUm = dwCurSilverNUm;
			s_.dwCurItemNum = dwCurItemNum;
			s_.dwCurXFCYNum = dwCurXFCYNum;
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
				topXml = <STHBattleResult _name_={name_} byCopyID={byCopyID} dwTotalTimes={dwTotalTimes} dwCurBossHP={dwCurBossHP} dwCurSilverNUm={dwCurSilverNUm} dwCurItemNum={dwCurItemNum}
				 dwCurXFCYNum={dwCurXFCYNum}/>;
			else
				topXml = <STHBattleResult byCopyID={byCopyID} dwTotalTimes={dwTotalTimes} dwCurBossHP={dwCurBossHP} dwCurSilverNUm={dwCurSilverNUm} dwCurItemNum={dwCurItemNum}
				 dwCurXFCYNum={dwCurXFCYNum}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byCopyID = byCopyID;
			obj_.dwTotalTimes = dwTotalTimes;
			obj_.dwCurBossHP = dwCurBossHP;
			obj_.dwCurSilverNUm = dwCurSilverNUm;
			obj_.dwCurItemNum = dwCurItemNum;
			obj_.dwCurXFCYNum = dwCurXFCYNum;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STHBattleResult
		{
			var s_:STHBattleResult = new STHBattleResult();
			var byCopyID:uint = bytes.readUnsignedByte();
			s_.byCopyID = byCopyID;
			var dwTotalTimes:uint = bytes.readUnsignedInt();
			s_.dwTotalTimes = dwTotalTimes;
			var dwCurBossHP:uint = bytes.readUnsignedInt();
			s_.dwCurBossHP = dwCurBossHP;
			var dwCurSilverNUm:uint = bytes.readUnsignedInt();
			s_.dwCurSilverNUm = dwCurSilverNUm;
			var dwCurItemNum:uint = bytes.readUnsignedInt();
			s_.dwCurItemNum = dwCurItemNum;
			var dwCurXFCYNum:uint = bytes.readUnsignedInt();
			s_.dwCurXFCYNum = dwCurXFCYNum;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STHBattleResult>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STHBattleResult> = new Vector.<STHBattleResult>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STHBattleResult = STHBattleResult.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byCopyID);
			bytes.writeUnsignedInt(dwTotalTimes);
			bytes.writeUnsignedInt(dwCurBossHP);
			bytes.writeUnsignedInt(dwCurSilverNUm);
			bytes.writeUnsignedInt(dwCurItemNum);
			bytes.writeUnsignedInt(dwCurXFCYNum);
		}

		public static function vectorToByteArray(vec:Vector.<STHBattleResult>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STHBattleResult in vec)
				s.toByteArray(bytes);
		}
	}
}
