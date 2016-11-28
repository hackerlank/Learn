/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBattleRePort.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战报保存
	 */
	public final class SBattleRePort
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var qwBattleID:BigInteger; //(无符号64位整数)战报Id
		public var qwAttackID:BigInteger; //(无符号64位整数)对方ID
		public var strAttackID:String; //对方名字
		public var eActionType:uint; //(枚举类型：EBattleActionType)玩家战斗方式
		public var eType:uint; //(枚举类型：EBattleReportType)战报类型
		public var eSuc:uint; //(枚举类型：EBattleActionType)胜利方
		public var dwTime:uint; //(无符号32位整数)战报时间
		public var dwParam1:uint; //(无符号32位整数)参数1
		public var dwParam2:uint; //(无符号32位整数)参数2
		public var dwParam3:uint; //(无符号32位整数)参数3
		public var dwIndex:uint; //(无符号32位整数)类型流水

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, qwBattleID:BigInteger, qwAttackID:BigInteger, strAttackID:String, eActionType:uint, 
			eType:uint, eSuc:uint, dwTime:uint, dwParam1:uint, dwParam2:uint, 
			dwParam3:uint, dwIndex:uint):SBattleRePort
		{
			var s_:SBattleRePort = new SBattleRePort();
			s_.qwRoleID = qwRoleID;
			s_.qwBattleID = qwBattleID;
			s_.qwAttackID = qwAttackID;
			s_.strAttackID = strAttackID;
			s_.eActionType = eActionType;
			s_.eType = eType;
			s_.eSuc = eSuc;
			s_.dwTime = dwTime;
			s_.dwParam1 = dwParam1;
			s_.dwParam2 = dwParam2;
			s_.dwParam3 = dwParam3;
			s_.dwIndex = dwIndex;
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
				topXml = <SBattleRePort _name_={name_} qwRoleID={qwRoleID} qwBattleID={qwBattleID} qwAttackID={qwAttackID} strAttackID={strAttackID} eActionType={eActionType}
				 eType={eType} eSuc={eSuc} dwTime={dwTime} dwParam1={dwParam1} dwParam2={dwParam2}
				 dwParam3={dwParam3} dwIndex={dwIndex}/>;
			else
				topXml = <SBattleRePort qwRoleID={qwRoleID} qwBattleID={qwBattleID} qwAttackID={qwAttackID} strAttackID={strAttackID} eActionType={eActionType}
				 eType={eType} eSuc={eSuc} dwTime={dwTime} dwParam1={dwParam1} dwParam2={dwParam2}
				 dwParam3={dwParam3} dwIndex={dwIndex}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.qwBattleID = qwBattleID;
			obj_.qwAttackID = qwAttackID;
			obj_.strAttackID = strAttackID;
			obj_.eActionType = eActionType;
			obj_.eType = eType;
			obj_.eSuc = eSuc;
			obj_.dwTime = dwTime;
			obj_.dwParam1 = dwParam1;
			obj_.dwParam2 = dwParam2;
			obj_.dwParam3 = dwParam3;
			obj_.dwIndex = dwIndex;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBattleRePort
		{
			var s_:SBattleRePort = new SBattleRePort();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var qwBattleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwBattleID = qwBattleID;
			var qwAttackID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwAttackID = qwAttackID;
			var strAttackID:String = BytesUtil.readString(bytes);
			s_.strAttackID = strAttackID;
			var eActionType:uint = bytes.readUnsignedByte();
			s_.eActionType = eActionType;
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
			var eSuc:uint = bytes.readUnsignedByte();
			s_.eSuc = eSuc;
			var dwTime:uint = bytes.readUnsignedInt();
			s_.dwTime = dwTime;
			var dwParam1:uint = bytes.readUnsignedInt();
			s_.dwParam1 = dwParam1;
			var dwParam2:uint = bytes.readUnsignedInt();
			s_.dwParam2 = dwParam2;
			var dwParam3:uint = bytes.readUnsignedInt();
			s_.dwParam3 = dwParam3;
			var dwIndex:uint = bytes.readUnsignedInt();
			s_.dwIndex = dwIndex;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBattleRePort>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBattleRePort> = new Vector.<SBattleRePort>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBattleRePort = SBattleRePort.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeUInt64(bytes, qwBattleID);
			BytesUtil.writeUInt64(bytes, qwAttackID);
			BytesUtil.writeString(bytes, strAttackID);
			bytes.writeByte(eActionType);
			bytes.writeByte(eType);
			bytes.writeByte(eSuc);
			bytes.writeUnsignedInt(dwTime);
			bytes.writeUnsignedInt(dwParam1);
			bytes.writeUnsignedInt(dwParam2);
			bytes.writeUnsignedInt(dwParam3);
			bytes.writeUnsignedInt(dwIndex);
		}

		public static function vectorToByteArray(vec:Vector.<SBattleRePort>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBattleRePort in vec)
				s.toByteArray(bytes);
		}
	}
}
