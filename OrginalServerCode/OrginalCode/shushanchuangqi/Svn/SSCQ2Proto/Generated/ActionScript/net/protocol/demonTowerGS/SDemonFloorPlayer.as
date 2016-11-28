/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDemonFloorPlayer.as
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 镇守层的玩家信息
	 */
	public final class SDemonFloorPlayer
	{
		public var dwFloorID:uint; //(无符号32位整数)当前所在塔层
		public var qwUserID:BigInteger; //(无符号64位整数)uid
		public var strRoleName:String; //角色名
		public var bySex:uint; //(无符号8位整数)性别
		public var byLevel:uint; //(无符号16位整数)等级
		public var dwPower:uint; //(无符号32位整数)战斗力
		public var dwGuardStartTime:uint; //(无符号32位整数)镇守开始时间
		public var dwGuardReduceRate:uint; //(无符号32位整数)减弱比例(百分比1为%1)
		public var vecSoulPrize:Vector.<MoneyInfo>; //当前获得魄奖励

		/**
		 * 辅助创建函数
		 */
		public static function create(dwFloorID:uint, qwUserID:BigInteger, strRoleName:String, bySex:uint, byLevel:uint, 
			dwPower:uint, dwGuardStartTime:uint, dwGuardReduceRate:uint, vecSoulPrize:Vector.<MoneyInfo>):SDemonFloorPlayer
		{
			var s_:SDemonFloorPlayer = new SDemonFloorPlayer();
			s_.dwFloorID = dwFloorID;
			s_.qwUserID = qwUserID;
			s_.strRoleName = strRoleName;
			s_.bySex = bySex;
			s_.byLevel = byLevel;
			s_.dwPower = dwPower;
			s_.dwGuardStartTime = dwGuardStartTime;
			s_.dwGuardReduceRate = dwGuardReduceRate;
			s_.vecSoulPrize = vecSoulPrize;
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
				topXml = <SDemonFloorPlayer _name_={name_} dwFloorID={dwFloorID} qwUserID={qwUserID} strRoleName={strRoleName} bySex={bySex} byLevel={byLevel}
				 dwPower={dwPower} dwGuardStartTime={dwGuardStartTime} dwGuardReduceRate={dwGuardReduceRate}/>;
			else
				topXml = <SDemonFloorPlayer dwFloorID={dwFloorID} qwUserID={qwUserID} strRoleName={strRoleName} bySex={bySex} byLevel={byLevel}
				 dwPower={dwPower} dwGuardStartTime={dwGuardStartTime} dwGuardReduceRate={dwGuardReduceRate}/>;
			if(vecSoulPrize != null)
			{
				var vecSoulPrizeXml:XML = <Vec_MoneyInfo _name_="vecSoulPrize"/>;
				for each(var s1:MoneyInfo in vecSoulPrize)
					vecSoulPrizeXml.appendChild(s1.toXML());
				topXml.appendChild(vecSoulPrizeXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwFloorID = dwFloorID;
			obj_.qwUserID = qwUserID;
			obj_.strRoleName = strRoleName;
			obj_.bySex = bySex;
			obj_.byLevel = byLevel;
			obj_.dwPower = dwPower;
			obj_.dwGuardStartTime = dwGuardStartTime;
			obj_.dwGuardReduceRate = dwGuardReduceRate;
			obj_.vecSoulPrize = vecSoulPrize;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDemonFloorPlayer
		{
			var s_:SDemonFloorPlayer = new SDemonFloorPlayer();
			var dwFloorID:uint = bytes.readUnsignedInt();
			s_.dwFloorID = dwFloorID;
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwUserID = qwUserID;
			var strRoleName:String = BytesUtil.readString(bytes);
			s_.strRoleName = strRoleName;
			var bySex:uint = bytes.readUnsignedByte();
			s_.bySex = bySex;
			var byLevel:uint = bytes.readUnsignedShort();
			s_.byLevel = byLevel;
			var dwPower:uint = bytes.readUnsignedInt();
			s_.dwPower = dwPower;
			var dwGuardStartTime:uint = bytes.readUnsignedInt();
			s_.dwGuardStartTime = dwGuardStartTime;
			var dwGuardReduceRate:uint = bytes.readUnsignedInt();
			s_.dwGuardReduceRate = dwGuardReduceRate;
			var vecSoulPrize:Vector.<MoneyInfo> = MoneyInfo.vectorFromByteArray(bytes);
			s_.vecSoulPrize = vecSoulPrize;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDemonFloorPlayer>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDemonFloorPlayer> = new Vector.<SDemonFloorPlayer>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDemonFloorPlayer = SDemonFloorPlayer.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwFloorID);
			BytesUtil.writeUInt64(bytes, qwUserID);
			BytesUtil.writeString(bytes, strRoleName);
			bytes.writeByte(bySex);
			bytes.writeShort(byLevel);
			bytes.writeUnsignedInt(dwPower);
			bytes.writeUnsignedInt(dwGuardStartTime);
			bytes.writeUnsignedInt(dwGuardReduceRate);
			MoneyInfo.vectorToByteArray(vecSoulPrize, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SDemonFloorPlayer>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDemonFloorPlayer in vec)
				s.toByteArray(bytes);
		}
	}
}
