/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SLadderReport.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战报
	 */
	public final class SLadderReport
	{
		public var qwBattleID:BigInteger; //(无符号64位整数)战报ID
		public var qwEmemyID:BigInteger; //(无符号64位整数)对手ID
		public var strName:String; //对手名字
		public var dwMonsterId:uint; //(无符号32位整数)对手是机器人,机器人ID
		public var byAttack:uint; //(无符号8位整数)0,表示挑战别人，1表示别人挑战自己
		public var bySuc:uint; //(无符号8位整数)0,自己失败，1，自己胜利
		public var dwPreRank:uint; //(无符号32位整数)挑战之前的排名
		public var dwNowRank:uint; //(无符号32位整数)挑战之后的排名
		public var dwTimer:uint; //(无符号32位整数)战报时间

		/**
		 * 辅助创建函数
		 */
		public static function create(qwBattleID:BigInteger, qwEmemyID:BigInteger, strName:String, dwMonsterId:uint, byAttack:uint, 
			bySuc:uint, dwPreRank:uint, dwNowRank:uint, dwTimer:uint):SLadderReport
		{
			var s_:SLadderReport = new SLadderReport();
			s_.qwBattleID = qwBattleID;
			s_.qwEmemyID = qwEmemyID;
			s_.strName = strName;
			s_.dwMonsterId = dwMonsterId;
			s_.byAttack = byAttack;
			s_.bySuc = bySuc;
			s_.dwPreRank = dwPreRank;
			s_.dwNowRank = dwNowRank;
			s_.dwTimer = dwTimer;
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
				topXml = <SLadderReport _name_={name_} qwBattleID={qwBattleID} qwEmemyID={qwEmemyID} strName={strName} dwMonsterId={dwMonsterId} byAttack={byAttack}
				 bySuc={bySuc} dwPreRank={dwPreRank} dwNowRank={dwNowRank} dwTimer={dwTimer}/>;
			else
				topXml = <SLadderReport qwBattleID={qwBattleID} qwEmemyID={qwEmemyID} strName={strName} dwMonsterId={dwMonsterId} byAttack={byAttack}
				 bySuc={bySuc} dwPreRank={dwPreRank} dwNowRank={dwNowRank} dwTimer={dwTimer}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwBattleID = qwBattleID;
			obj_.qwEmemyID = qwEmemyID;
			obj_.strName = strName;
			obj_.dwMonsterId = dwMonsterId;
			obj_.byAttack = byAttack;
			obj_.bySuc = bySuc;
			obj_.dwPreRank = dwPreRank;
			obj_.dwNowRank = dwNowRank;
			obj_.dwTimer = dwTimer;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SLadderReport
		{
			var s_:SLadderReport = new SLadderReport();
			var qwBattleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwBattleID = qwBattleID;
			var qwEmemyID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwEmemyID = qwEmemyID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var dwMonsterId:uint = bytes.readUnsignedInt();
			s_.dwMonsterId = dwMonsterId;
			var byAttack:uint = bytes.readUnsignedByte();
			s_.byAttack = byAttack;
			var bySuc:uint = bytes.readUnsignedByte();
			s_.bySuc = bySuc;
			var dwPreRank:uint = bytes.readUnsignedInt();
			s_.dwPreRank = dwPreRank;
			var dwNowRank:uint = bytes.readUnsignedInt();
			s_.dwNowRank = dwNowRank;
			var dwTimer:uint = bytes.readUnsignedInt();
			s_.dwTimer = dwTimer;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SLadderReport>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SLadderReport> = new Vector.<SLadderReport>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SLadderReport = SLadderReport.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwBattleID);
			BytesUtil.writeUInt64(bytes, qwEmemyID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeUnsignedInt(dwMonsterId);
			bytes.writeByte(byAttack);
			bytes.writeByte(bySuc);
			bytes.writeUnsignedInt(dwPreRank);
			bytes.writeUnsignedInt(dwNowRank);
			bytes.writeUnsignedInt(dwTimer);
		}

		public static function vectorToByteArray(vec:Vector.<SLadderReport>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SLadderReport in vec)
				s.toByteArray(bytes);
		}
	}
}
