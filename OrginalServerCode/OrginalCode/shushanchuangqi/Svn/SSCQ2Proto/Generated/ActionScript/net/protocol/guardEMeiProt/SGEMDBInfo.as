/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGEMDBInfo.as
//  Purpose:      守卫峨眉协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 守卫峨眉DB信息
	 */
	public final class SGEMDBInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)RoleID
		public var wMissionID:uint; //(无符号16位整数)关卡ID
		public var byGEMType:uint; //(无符号8位整数)正在进行的类型（注：0表示没有；1：守卫；2：扫荡）
		public var wCurProgress:uint; //(无符号16位整数)当前进度
		public var wGuardProgress:uint; //(无符号16位整数)守卫进度
		public var dwGuardMonsterGroupID:uint; //(无符号32位整数)怪物组ID
		public var dwSweepEndTime:uint; //(无符号32位整数)扫荡结束时间
		public var strBuff:String; //守卫峨眉Buff

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wMissionID:uint, byGEMType:uint, wCurProgress:uint, wGuardProgress:uint, 
			dwGuardMonsterGroupID:uint, dwSweepEndTime:uint, strBuff:String):SGEMDBInfo
		{
			var s_:SGEMDBInfo = new SGEMDBInfo();
			s_.qwRoleID = qwRoleID;
			s_.wMissionID = wMissionID;
			s_.byGEMType = byGEMType;
			s_.wCurProgress = wCurProgress;
			s_.wGuardProgress = wGuardProgress;
			s_.dwGuardMonsterGroupID = dwGuardMonsterGroupID;
			s_.dwSweepEndTime = dwSweepEndTime;
			s_.strBuff = strBuff;
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
				topXml = <SGEMDBInfo _name_={name_} qwRoleID={qwRoleID} wMissionID={wMissionID} byGEMType={byGEMType} wCurProgress={wCurProgress} wGuardProgress={wGuardProgress}
				 dwGuardMonsterGroupID={dwGuardMonsterGroupID} dwSweepEndTime={dwSweepEndTime} strBuff={strBuff}/>;
			else
				topXml = <SGEMDBInfo qwRoleID={qwRoleID} wMissionID={wMissionID} byGEMType={byGEMType} wCurProgress={wCurProgress} wGuardProgress={wGuardProgress}
				 dwGuardMonsterGroupID={dwGuardMonsterGroupID} dwSweepEndTime={dwSweepEndTime} strBuff={strBuff}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wMissionID = wMissionID;
			obj_.byGEMType = byGEMType;
			obj_.wCurProgress = wCurProgress;
			obj_.wGuardProgress = wGuardProgress;
			obj_.dwGuardMonsterGroupID = dwGuardMonsterGroupID;
			obj_.dwSweepEndTime = dwSweepEndTime;
			obj_.strBuff = strBuff;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGEMDBInfo
		{
			var s_:SGEMDBInfo = new SGEMDBInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wMissionID:uint = bytes.readUnsignedShort();
			s_.wMissionID = wMissionID;
			var byGEMType:uint = bytes.readUnsignedByte();
			s_.byGEMType = byGEMType;
			var wCurProgress:uint = bytes.readUnsignedShort();
			s_.wCurProgress = wCurProgress;
			var wGuardProgress:uint = bytes.readUnsignedShort();
			s_.wGuardProgress = wGuardProgress;
			var dwGuardMonsterGroupID:uint = bytes.readUnsignedInt();
			s_.dwGuardMonsterGroupID = dwGuardMonsterGroupID;
			var dwSweepEndTime:uint = bytes.readUnsignedInt();
			s_.dwSweepEndTime = dwSweepEndTime;
			var strBuff:String = BytesUtil.readString(bytes);
			s_.strBuff = strBuff;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGEMDBInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGEMDBInfo> = new Vector.<SGEMDBInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGEMDBInfo = SGEMDBInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wMissionID);
			bytes.writeByte(byGEMType);
			bytes.writeShort(wCurProgress);
			bytes.writeShort(wGuardProgress);
			bytes.writeUnsignedInt(dwGuardMonsterGroupID);
			bytes.writeUnsignedInt(dwSweepEndTime);
			BytesUtil.writeString(bytes, strBuff);
		}

		public static function vectorToByteArray(vec:Vector.<SGEMDBInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGEMDBInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
