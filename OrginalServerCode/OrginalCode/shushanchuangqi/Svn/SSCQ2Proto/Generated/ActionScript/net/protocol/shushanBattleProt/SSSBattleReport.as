/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSSBattleReport.as
//  Purpose:      蜀山论剑相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战斗战报数据结构
	 */
	public final class SSSBattleReport
	{
		public var byRound:uint; //(无符号8位整数)当前轮次
		public var strNameA:String; //攻方玩家名字
		public var qwRoleA:BigInteger; //(无符号64位整数)攻方玩家ID
		public var strNameB:String; //守方玩家名字
		public var qwRoleB:BigInteger; //(无符号64位整数)守方玩家ID
		public var byResult:uint; //(无符号8位整数)结果(0是攻方胜利,1是守方胜利,2是攻方逃跑,3守方逃跑,4攻方轮空)
		public var qwBattleID:BigInteger; //(无符号64位整数)战报ID
		public var byCurrKill:uint; //(无符号8位整数)当前连杀数(若个人战报即表明个人连杀数,若全部战报即表明攻方连杀数)
		public var wHonor:uint; //(无符号16位整数)当场获得荣誉值(若个人战报即表明个人获得荣誉值,若全部战报即表明攻方获得荣誉值)

		/**
		 * 辅助创建函数
		 */
		public static function create(byRound:uint, strNameA:String, qwRoleA:BigInteger, strNameB:String, qwRoleB:BigInteger, 
			byResult:uint, qwBattleID:BigInteger, byCurrKill:uint, wHonor:uint):SSSBattleReport
		{
			var s_:SSSBattleReport = new SSSBattleReport();
			s_.byRound = byRound;
			s_.strNameA = strNameA;
			s_.qwRoleA = qwRoleA;
			s_.strNameB = strNameB;
			s_.qwRoleB = qwRoleB;
			s_.byResult = byResult;
			s_.qwBattleID = qwBattleID;
			s_.byCurrKill = byCurrKill;
			s_.wHonor = wHonor;
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
				topXml = <SSSBattleReport _name_={name_} byRound={byRound} strNameA={strNameA} qwRoleA={qwRoleA} strNameB={strNameB} qwRoleB={qwRoleB}
				 byResult={byResult} qwBattleID={qwBattleID} byCurrKill={byCurrKill} wHonor={wHonor}/>;
			else
				topXml = <SSSBattleReport byRound={byRound} strNameA={strNameA} qwRoleA={qwRoleA} strNameB={strNameB} qwRoleB={qwRoleB}
				 byResult={byResult} qwBattleID={qwBattleID} byCurrKill={byCurrKill} wHonor={wHonor}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byRound = byRound;
			obj_.strNameA = strNameA;
			obj_.qwRoleA = qwRoleA;
			obj_.strNameB = strNameB;
			obj_.qwRoleB = qwRoleB;
			obj_.byResult = byResult;
			obj_.qwBattleID = qwBattleID;
			obj_.byCurrKill = byCurrKill;
			obj_.wHonor = wHonor;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSSBattleReport
		{
			var s_:SSSBattleReport = new SSSBattleReport();
			var byRound:uint = bytes.readUnsignedByte();
			s_.byRound = byRound;
			var strNameA:String = BytesUtil.readString(bytes);
			s_.strNameA = strNameA;
			var qwRoleA:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleA = qwRoleA;
			var strNameB:String = BytesUtil.readString(bytes);
			s_.strNameB = strNameB;
			var qwRoleB:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleB = qwRoleB;
			var byResult:uint = bytes.readUnsignedByte();
			s_.byResult = byResult;
			var qwBattleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwBattleID = qwBattleID;
			var byCurrKill:uint = bytes.readUnsignedByte();
			s_.byCurrKill = byCurrKill;
			var wHonor:uint = bytes.readUnsignedShort();
			s_.wHonor = wHonor;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSSBattleReport>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSSBattleReport> = new Vector.<SSSBattleReport>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSSBattleReport = SSSBattleReport.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byRound);
			BytesUtil.writeString(bytes, strNameA);
			BytesUtil.writeUInt64(bytes, qwRoleA);
			BytesUtil.writeString(bytes, strNameB);
			BytesUtil.writeUInt64(bytes, qwRoleB);
			bytes.writeByte(byResult);
			BytesUtil.writeUInt64(bytes, qwBattleID);
			bytes.writeByte(byCurrKill);
			bytes.writeShort(wHonor);
		}

		public static function vectorToByteArray(vec:Vector.<SSSBattleReport>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSSBattleReport in vec)
				s.toByteArray(bytes);
		}
	}
}
