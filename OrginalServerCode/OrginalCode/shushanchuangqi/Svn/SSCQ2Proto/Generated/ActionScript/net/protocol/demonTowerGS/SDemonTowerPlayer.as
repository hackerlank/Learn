/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDemonTowerPlayer.as
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 镇守的玩家信息列表
	 */
	public final class SDemonTowerPlayer
	{
		public var qwUserID:BigInteger; //(无符号64位整数)uid
		public var qwRoleID:BigInteger; //(无符号64位整数)角色id
		public var strRoleName:String; //角色名
		public var bySex:uint; //(无符号8位整数)性别
		public var byLevel:uint; //(无符号16位整数)等级
		public var dwFloorID:uint; //(无符号32位整数)当前所在塔层
		public var dwGuardFloorID:uint; //(无符号32位整数)镇守塔层
		public var dwGuardPos:uint; //(无符号32位整数)镇守位置
		public var dwGuardStartTime:uint; //(无符号32位整数)镇守开始时间
		public var dwGuardEndTime:uint; //(无符号32位整数)镇守结束时间
		public var dwGuardNextPrizeTime:uint; //(无符号32位整数)下次奖励时间
		public var dwGuardNextReduceRateTime:uint; //(无符号32位整数)下次减弱时间
		public var dwGuardGatherSpeed:uint; //(无符号32位整数)聚魂速度
		public var dwGuardGatherSpeedEndTimer:uint; //(无符号32位整数)加速时间
		public var dwGuardReduceRate:uint; //(无符号32位整数)元神灵力(百分比1为1%)
		public var dwGuardNextAttackTime:uint; //(无符号32位整数)镇守可以攻击的时间
		public var dwPower:uint; //(无符号32位整数)战斗力
		public var dwBuyTime:uint; //(无符号32位整数)购买cd(服务器用)
		public var vecGatherSoulPrize:Vector.<MoneyInfo>; //当前聚集的魄奖励
		public var vecFailSoulPrize:Vector.<MoneyInfo>; //失败后的魄奖励
		public var vecDaySoulPrize:Vector.<MoneyInfo>; //7点结算的魄奖励
		public var dwTotalTime:uint; //(无符号32位整数)镇守时间(服务器用)
		public var dwFailFloorID:uint; //(无符号32位整数)失败镇守塔层
		public var dwFailPos:uint; //(无符号32位整数)失败镇守位置
		public var byColor:uint; //(无符号8位整数)角色颜色

		/**
		 * 辅助创建函数
		 */
		public static function create(qwUserID:BigInteger, qwRoleID:BigInteger, strRoleName:String, bySex:uint, byLevel:uint, 
			dwFloorID:uint, dwGuardFloorID:uint, dwGuardPos:uint, dwGuardStartTime:uint, dwGuardEndTime:uint, 
			dwGuardNextPrizeTime:uint, dwGuardNextReduceRateTime:uint, dwGuardGatherSpeed:uint, dwGuardGatherSpeedEndTimer:uint, dwGuardReduceRate:uint, 
			dwGuardNextAttackTime:uint, dwPower:uint, dwBuyTime:uint, vecGatherSoulPrize:Vector.<MoneyInfo>, vecFailSoulPrize:Vector.<MoneyInfo>, 
			vecDaySoulPrize:Vector.<MoneyInfo>, dwTotalTime:uint, dwFailFloorID:uint, dwFailPos:uint, byColor:uint):SDemonTowerPlayer
		{
			var s_:SDemonTowerPlayer = new SDemonTowerPlayer();
			s_.qwUserID = qwUserID;
			s_.qwRoleID = qwRoleID;
			s_.strRoleName = strRoleName;
			s_.bySex = bySex;
			s_.byLevel = byLevel;
			s_.dwFloorID = dwFloorID;
			s_.dwGuardFloorID = dwGuardFloorID;
			s_.dwGuardPos = dwGuardPos;
			s_.dwGuardStartTime = dwGuardStartTime;
			s_.dwGuardEndTime = dwGuardEndTime;
			s_.dwGuardNextPrizeTime = dwGuardNextPrizeTime;
			s_.dwGuardNextReduceRateTime = dwGuardNextReduceRateTime;
			s_.dwGuardGatherSpeed = dwGuardGatherSpeed;
			s_.dwGuardGatherSpeedEndTimer = dwGuardGatherSpeedEndTimer;
			s_.dwGuardReduceRate = dwGuardReduceRate;
			s_.dwGuardNextAttackTime = dwGuardNextAttackTime;
			s_.dwPower = dwPower;
			s_.dwBuyTime = dwBuyTime;
			s_.vecGatherSoulPrize = vecGatherSoulPrize;
			s_.vecFailSoulPrize = vecFailSoulPrize;
			s_.vecDaySoulPrize = vecDaySoulPrize;
			s_.dwTotalTime = dwTotalTime;
			s_.dwFailFloorID = dwFailFloorID;
			s_.dwFailPos = dwFailPos;
			s_.byColor = byColor;
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
				topXml = <SDemonTowerPlayer _name_={name_} qwUserID={qwUserID} qwRoleID={qwRoleID} strRoleName={strRoleName} bySex={bySex} byLevel={byLevel}
				 dwFloorID={dwFloorID} dwGuardFloorID={dwGuardFloorID} dwGuardPos={dwGuardPos} dwGuardStartTime={dwGuardStartTime} dwGuardEndTime={dwGuardEndTime}
				 dwGuardNextPrizeTime={dwGuardNextPrizeTime} dwGuardNextReduceRateTime={dwGuardNextReduceRateTime} dwGuardGatherSpeed={dwGuardGatherSpeed} dwGuardGatherSpeedEndTimer={dwGuardGatherSpeedEndTimer} dwGuardReduceRate={dwGuardReduceRate}
				 dwGuardNextAttackTime={dwGuardNextAttackTime} dwPower={dwPower} dwBuyTime={dwBuyTime} dwTotalTime={dwTotalTime} dwFailFloorID={dwFailFloorID} dwFailPos={dwFailPos} byColor={byColor}/>;
			else
				topXml = <SDemonTowerPlayer qwUserID={qwUserID} qwRoleID={qwRoleID} strRoleName={strRoleName} bySex={bySex} byLevel={byLevel}
				 dwFloorID={dwFloorID} dwGuardFloorID={dwGuardFloorID} dwGuardPos={dwGuardPos} dwGuardStartTime={dwGuardStartTime} dwGuardEndTime={dwGuardEndTime}
				 dwGuardNextPrizeTime={dwGuardNextPrizeTime} dwGuardNextReduceRateTime={dwGuardNextReduceRateTime} dwGuardGatherSpeed={dwGuardGatherSpeed} dwGuardGatherSpeedEndTimer={dwGuardGatherSpeedEndTimer} dwGuardReduceRate={dwGuardReduceRate}
				 dwGuardNextAttackTime={dwGuardNextAttackTime} dwPower={dwPower} dwBuyTime={dwBuyTime} dwTotalTime={dwTotalTime} dwFailFloorID={dwFailFloorID} dwFailPos={dwFailPos} byColor={byColor}/>;
			if(vecGatherSoulPrize != null)
			{
				var vecGatherSoulPrizeXml:XML = <Vec_MoneyInfo _name_="vecGatherSoulPrize"/>;
				for each(var s1:MoneyInfo in vecGatherSoulPrize)
					vecGatherSoulPrizeXml.appendChild(s1.toXML());
				topXml.appendChild(vecGatherSoulPrizeXml);
			}
			if(vecFailSoulPrize != null)
			{
				var vecFailSoulPrizeXml:XML = <Vec_MoneyInfo _name_="vecFailSoulPrize"/>;
				for each(var s2:MoneyInfo in vecFailSoulPrize)
					vecFailSoulPrizeXml.appendChild(s2.toXML());
				topXml.appendChild(vecFailSoulPrizeXml);
			}
			if(vecDaySoulPrize != null)
			{
				var vecDaySoulPrizeXml:XML = <Vec_MoneyInfo _name_="vecDaySoulPrize"/>;
				for each(var s3:MoneyInfo in vecDaySoulPrize)
					vecDaySoulPrizeXml.appendChild(s3.toXML());
				topXml.appendChild(vecDaySoulPrizeXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwUserID = qwUserID;
			obj_.qwRoleID = qwRoleID;
			obj_.strRoleName = strRoleName;
			obj_.bySex = bySex;
			obj_.byLevel = byLevel;
			obj_.dwFloorID = dwFloorID;
			obj_.dwGuardFloorID = dwGuardFloorID;
			obj_.dwGuardPos = dwGuardPos;
			obj_.dwGuardStartTime = dwGuardStartTime;
			obj_.dwGuardEndTime = dwGuardEndTime;
			obj_.dwGuardNextPrizeTime = dwGuardNextPrizeTime;
			obj_.dwGuardNextReduceRateTime = dwGuardNextReduceRateTime;
			obj_.dwGuardGatherSpeed = dwGuardGatherSpeed;
			obj_.dwGuardGatherSpeedEndTimer = dwGuardGatherSpeedEndTimer;
			obj_.dwGuardReduceRate = dwGuardReduceRate;
			obj_.dwGuardNextAttackTime = dwGuardNextAttackTime;
			obj_.dwPower = dwPower;
			obj_.dwBuyTime = dwBuyTime;
			obj_.vecGatherSoulPrize = vecGatherSoulPrize;
			obj_.vecFailSoulPrize = vecFailSoulPrize;
			obj_.vecDaySoulPrize = vecDaySoulPrize;
			obj_.dwTotalTime = dwTotalTime;
			obj_.dwFailFloorID = dwFailFloorID;
			obj_.dwFailPos = dwFailPos;
			obj_.byColor = byColor;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDemonTowerPlayer
		{
			var s_:SDemonTowerPlayer = new SDemonTowerPlayer();
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwUserID = qwUserID;
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var strRoleName:String = BytesUtil.readString(bytes);
			s_.strRoleName = strRoleName;
			var bySex:uint = bytes.readUnsignedByte();
			s_.bySex = bySex;
			var byLevel:uint = bytes.readUnsignedShort();
			s_.byLevel = byLevel;
			var dwFloorID:uint = bytes.readUnsignedInt();
			s_.dwFloorID = dwFloorID;
			var dwGuardFloorID:uint = bytes.readUnsignedInt();
			s_.dwGuardFloorID = dwGuardFloorID;
			var dwGuardPos:uint = bytes.readUnsignedInt();
			s_.dwGuardPos = dwGuardPos;
			var dwGuardStartTime:uint = bytes.readUnsignedInt();
			s_.dwGuardStartTime = dwGuardStartTime;
			var dwGuardEndTime:uint = bytes.readUnsignedInt();
			s_.dwGuardEndTime = dwGuardEndTime;
			var dwGuardNextPrizeTime:uint = bytes.readUnsignedInt();
			s_.dwGuardNextPrizeTime = dwGuardNextPrizeTime;
			var dwGuardNextReduceRateTime:uint = bytes.readUnsignedInt();
			s_.dwGuardNextReduceRateTime = dwGuardNextReduceRateTime;
			var dwGuardGatherSpeed:uint = bytes.readUnsignedInt();
			s_.dwGuardGatherSpeed = dwGuardGatherSpeed;
			var dwGuardGatherSpeedEndTimer:uint = bytes.readUnsignedInt();
			s_.dwGuardGatherSpeedEndTimer = dwGuardGatherSpeedEndTimer;
			var dwGuardReduceRate:uint = bytes.readUnsignedInt();
			s_.dwGuardReduceRate = dwGuardReduceRate;
			var dwGuardNextAttackTime:uint = bytes.readUnsignedInt();
			s_.dwGuardNextAttackTime = dwGuardNextAttackTime;
			var dwPower:uint = bytes.readUnsignedInt();
			s_.dwPower = dwPower;
			var dwBuyTime:uint = bytes.readUnsignedInt();
			s_.dwBuyTime = dwBuyTime;
			var vecGatherSoulPrize:Vector.<MoneyInfo> = MoneyInfo.vectorFromByteArray(bytes);
			s_.vecGatherSoulPrize = vecGatherSoulPrize;
			var vecFailSoulPrize:Vector.<MoneyInfo> = MoneyInfo.vectorFromByteArray(bytes);
			s_.vecFailSoulPrize = vecFailSoulPrize;
			var vecDaySoulPrize:Vector.<MoneyInfo> = MoneyInfo.vectorFromByteArray(bytes);
			s_.vecDaySoulPrize = vecDaySoulPrize;
			var dwTotalTime:uint = bytes.readUnsignedInt();
			s_.dwTotalTime = dwTotalTime;
			var dwFailFloorID:uint = bytes.readUnsignedInt();
			s_.dwFailFloorID = dwFailFloorID;
			var dwFailPos:uint = bytes.readUnsignedInt();
			s_.dwFailPos = dwFailPos;
			var byColor:uint = bytes.readUnsignedByte();
			s_.byColor = byColor;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDemonTowerPlayer>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDemonTowerPlayer> = new Vector.<SDemonTowerPlayer>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDemonTowerPlayer = SDemonTowerPlayer.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwUserID);
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeString(bytes, strRoleName);
			bytes.writeByte(bySex);
			bytes.writeShort(byLevel);
			bytes.writeUnsignedInt(dwFloorID);
			bytes.writeUnsignedInt(dwGuardFloorID);
			bytes.writeUnsignedInt(dwGuardPos);
			bytes.writeUnsignedInt(dwGuardStartTime);
			bytes.writeUnsignedInt(dwGuardEndTime);
			bytes.writeUnsignedInt(dwGuardNextPrizeTime);
			bytes.writeUnsignedInt(dwGuardNextReduceRateTime);
			bytes.writeUnsignedInt(dwGuardGatherSpeed);
			bytes.writeUnsignedInt(dwGuardGatherSpeedEndTimer);
			bytes.writeUnsignedInt(dwGuardReduceRate);
			bytes.writeUnsignedInt(dwGuardNextAttackTime);
			bytes.writeUnsignedInt(dwPower);
			bytes.writeUnsignedInt(dwBuyTime);
			MoneyInfo.vectorToByteArray(vecGatherSoulPrize, bytes);
			MoneyInfo.vectorToByteArray(vecFailSoulPrize, bytes);
			MoneyInfo.vectorToByteArray(vecDaySoulPrize, bytes);
			bytes.writeUnsignedInt(dwTotalTime);
			bytes.writeUnsignedInt(dwFailFloorID);
			bytes.writeUnsignedInt(dwFailPos);
			bytes.writeByte(byColor);
		}

		public static function vectorToByteArray(vec:Vector.<SDemonTowerPlayer>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDemonTowerPlayer in vec)
				s.toByteArray(bytes);
		}
	}
}
