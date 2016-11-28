/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleSlotInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战斗场信息
	 */
	public final class SBattleSlotInfo
	{
		public var byIndex:uint; //(无符号8位整数)战斗场编号(1~3)
		public var qwBattleID:BigInteger; //(无符号64位整数)战报ID
		public var sUserAllInfoA:SBattleUserAllInfo; //A方成员信息
		public var sUserAllInfoB:SBattleUserAllInfo; //B方成员信息

		/**
		 * 辅助创建函数
		 */
		public static function create(byIndex:uint, qwBattleID:BigInteger, sUserAllInfoA:SBattleUserAllInfo, sUserAllInfoB:SBattleUserAllInfo):SBattleSlotInfo
		{
			var s_:SBattleSlotInfo = new SBattleSlotInfo();
			s_.byIndex = byIndex;
			s_.qwBattleID = qwBattleID;
			s_.sUserAllInfoA = sUserAllInfoA;
			s_.sUserAllInfoB = sUserAllInfoB;
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
				topXml = <SBattleSlotInfo _name_={name_} byIndex={byIndex} qwBattleID={qwBattleID}/>;
			else
				topXml = <SBattleSlotInfo byIndex={byIndex} qwBattleID={qwBattleID}/>;
			if(sUserAllInfoA != null)
				topXml.appendChild(sUserAllInfoA.toXML("sUserAllInfoA"));
			if(sUserAllInfoB != null)
				topXml.appendChild(sUserAllInfoB.toXML("sUserAllInfoB"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byIndex = byIndex;
			obj_.qwBattleID = qwBattleID;
			obj_.sUserAllInfoA = sUserAllInfoA;
			obj_.sUserAllInfoB = sUserAllInfoB;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleSlotInfo
		{
			var s_:SBattleSlotInfo = new SBattleSlotInfo();
			var byIndex:uint = bytes.readUnsignedByte();
			s_.byIndex = byIndex;
			var qwBattleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwBattleID = qwBattleID;
			var sUserAllInfoA:SBattleUserAllInfo = SBattleUserAllInfo.fromByteArray(bytes);
			s_.sUserAllInfoA = sUserAllInfoA;
			var sUserAllInfoB:SBattleUserAllInfo = SBattleUserAllInfo.fromByteArray(bytes);
			s_.sUserAllInfoB = sUserAllInfoB;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleSlotInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleSlotInfo> = new Vector.<SBattleSlotInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleSlotInfo = SBattleSlotInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byIndex);
			BytesUtil.writeUInt64(bytes, qwBattleID);
			sUserAllInfoA.toByteArray(bytes);
			sUserAllInfoB.toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleSlotInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleSlotInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
