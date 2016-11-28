/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战斗信息
	 */
	public final class SBattleInfo
	{
		public var qwBattleID:BigInteger; //(无符号64位整数)战报ID
		public var strNameA:String; //A方名字
		public var qwRoleIDA:BigInteger; //(无符号64位整数)A方ID
		public var strNameB:String; //B方名字
		public var qwRoleIDB:BigInteger; //(无符号64位整数)B方ID
		public var eWinnerSide:uint; //(枚举类型：EGBSide)获胜方

		/**
		 * 辅助创建函数
		 */
		public static function create(qwBattleID:BigInteger, strNameA:String, qwRoleIDA:BigInteger, strNameB:String, qwRoleIDB:BigInteger, 
			eWinnerSide:uint):SBattleInfo
		{
			var s_:SBattleInfo = new SBattleInfo();
			s_.qwBattleID = qwBattleID;
			s_.strNameA = strNameA;
			s_.qwRoleIDA = qwRoleIDA;
			s_.strNameB = strNameB;
			s_.qwRoleIDB = qwRoleIDB;
			s_.eWinnerSide = eWinnerSide;
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
				topXml = <SBattleInfo _name_={name_} qwBattleID={qwBattleID} strNameA={strNameA} qwRoleIDA={qwRoleIDA} strNameB={strNameB} qwRoleIDB={qwRoleIDB}
				 eWinnerSide={eWinnerSide}/>;
			else
				topXml = <SBattleInfo qwBattleID={qwBattleID} strNameA={strNameA} qwRoleIDA={qwRoleIDA} strNameB={strNameB} qwRoleIDB={qwRoleIDB}
				 eWinnerSide={eWinnerSide}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwBattleID = qwBattleID;
			obj_.strNameA = strNameA;
			obj_.qwRoleIDA = qwRoleIDA;
			obj_.strNameB = strNameB;
			obj_.qwRoleIDB = qwRoleIDB;
			obj_.eWinnerSide = eWinnerSide;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleInfo
		{
			var s_:SBattleInfo = new SBattleInfo();
			var qwBattleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwBattleID = qwBattleID;
			var strNameA:String = BytesUtil.readString(bytes);
			s_.strNameA = strNameA;
			var qwRoleIDA:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleIDA = qwRoleIDA;
			var strNameB:String = BytesUtil.readString(bytes);
			s_.strNameB = strNameB;
			var qwRoleIDB:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleIDB = qwRoleIDB;
			var eWinnerSide:uint = bytes.readUnsignedByte();
			s_.eWinnerSide = eWinnerSide;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleInfo> = new Vector.<SBattleInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleInfo = SBattleInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwBattleID);
			BytesUtil.writeString(bytes, strNameA);
			BytesUtil.writeUInt64(bytes, qwRoleIDA);
			BytesUtil.writeString(bytes, strNameB);
			BytesUtil.writeUInt64(bytes, qwRoleIDB);
			bytes.writeByte(eWinnerSide);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
