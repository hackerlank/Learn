/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRoleAttaked.as
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTower
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 被攻击列表
	 */
	public final class SRoleAttaked
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)角色ID
		public var dwPos:uint; //(无符号32位整数)存储位置
		public var qwAtkRoleID:BigInteger; //(无符号64位整数)攻击角色ID
		public var strRoleName:String; //角色名
		public var byLevel:uint; //(无符号8位整数)等级
		public var dwAttackedTime:uint; //(无符号32位整数)攻击时间
		public var dwFighterType:uint; //(无符号32位整数)战斗类型

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, dwPos:uint, qwAtkRoleID:BigInteger, strRoleName:String, byLevel:uint, 
			dwAttackedTime:uint, dwFighterType:uint):SRoleAttaked
		{
			var s_:SRoleAttaked = new SRoleAttaked();
			s_.qwRoleID = qwRoleID;
			s_.dwPos = dwPos;
			s_.qwAtkRoleID = qwAtkRoleID;
			s_.strRoleName = strRoleName;
			s_.byLevel = byLevel;
			s_.dwAttackedTime = dwAttackedTime;
			s_.dwFighterType = dwFighterType;
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
				topXml = <SRoleAttaked _name_={name_} qwRoleID={qwRoleID} dwPos={dwPos} qwAtkRoleID={qwAtkRoleID} strRoleName={strRoleName} byLevel={byLevel}
				 dwAttackedTime={dwAttackedTime} dwFighterType={dwFighterType}/>;
			else
				topXml = <SRoleAttaked qwRoleID={qwRoleID} dwPos={dwPos} qwAtkRoleID={qwAtkRoleID} strRoleName={strRoleName} byLevel={byLevel}
				 dwAttackedTime={dwAttackedTime} dwFighterType={dwFighterType}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.dwPos = dwPos;
			obj_.qwAtkRoleID = qwAtkRoleID;
			obj_.strRoleName = strRoleName;
			obj_.byLevel = byLevel;
			obj_.dwAttackedTime = dwAttackedTime;
			obj_.dwFighterType = dwFighterType;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRoleAttaked
		{
			var s_:SRoleAttaked = new SRoleAttaked();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var dwPos:uint = bytes.readUnsignedInt();
			s_.dwPos = dwPos;
			var qwAtkRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwAtkRoleID = qwAtkRoleID;
			var strRoleName:String = BytesUtil.readString(bytes);
			s_.strRoleName = strRoleName;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var dwAttackedTime:uint = bytes.readUnsignedInt();
			s_.dwAttackedTime = dwAttackedTime;
			var dwFighterType:uint = bytes.readUnsignedInt();
			s_.dwFighterType = dwFighterType;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRoleAttaked>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRoleAttaked> = new Vector.<SRoleAttaked>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRoleAttaked = SRoleAttaked.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeUnsignedInt(dwPos);
			BytesUtil.writeUInt64(bytes, qwAtkRoleID);
			BytesUtil.writeString(bytes, strRoleName);
			bytes.writeByte(byLevel);
			bytes.writeUnsignedInt(dwAttackedTime);
			bytes.writeUnsignedInt(dwFighterType);
		}

		public static function vectorToByteArray(vec:Vector.<SRoleAttaked>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRoleAttaked in vec)
				s.toByteArray(bytes);
		}
	}
}
