/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDemonToweAttackedInfo.as
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTower
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 锁妖塔被攻击列表
	 */
	public final class SDemonToweAttackedInfo
	{
		public var qwAtkRoleID:BigInteger; //(无符号64位整数)攻击角色ID
		public var strRoleName:String; //角色名
		public var dwLayerID:uint; //(无符号32位整数)层数
		public var byLevel:uint; //(无符号8位整数)等级
		public var dwAttackedTime:uint; //(无符号32位整数)攻击时间

		/**
		 * 辅助创建函数
		 */
		public static function create(qwAtkRoleID:BigInteger, strRoleName:String, dwLayerID:uint, byLevel:uint, dwAttackedTime:uint):SDemonToweAttackedInfo
		{
			var s_:SDemonToweAttackedInfo = new SDemonToweAttackedInfo();
			s_.qwAtkRoleID = qwAtkRoleID;
			s_.strRoleName = strRoleName;
			s_.dwLayerID = dwLayerID;
			s_.byLevel = byLevel;
			s_.dwAttackedTime = dwAttackedTime;
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
				topXml = <SDemonToweAttackedInfo _name_={name_} qwAtkRoleID={qwAtkRoleID} strRoleName={strRoleName} dwLayerID={dwLayerID} byLevel={byLevel} dwAttackedTime={dwAttackedTime}/>;
			else
				topXml = <SDemonToweAttackedInfo qwAtkRoleID={qwAtkRoleID} strRoleName={strRoleName} dwLayerID={dwLayerID} byLevel={byLevel} dwAttackedTime={dwAttackedTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwAtkRoleID = qwAtkRoleID;
			obj_.strRoleName = strRoleName;
			obj_.dwLayerID = dwLayerID;
			obj_.byLevel = byLevel;
			obj_.dwAttackedTime = dwAttackedTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDemonToweAttackedInfo
		{
			var s_:SDemonToweAttackedInfo = new SDemonToweAttackedInfo();
			var qwAtkRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwAtkRoleID = qwAtkRoleID;
			var strRoleName:String = BytesUtil.readString(bytes);
			s_.strRoleName = strRoleName;
			var dwLayerID:uint = bytes.readUnsignedInt();
			s_.dwLayerID = dwLayerID;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var dwAttackedTime:uint = bytes.readUnsignedInt();
			s_.dwAttackedTime = dwAttackedTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDemonToweAttackedInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDemonToweAttackedInfo> = new Vector.<SDemonToweAttackedInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDemonToweAttackedInfo = SDemonToweAttackedInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwAtkRoleID);
			BytesUtil.writeString(bytes, strRoleName);
			bytes.writeUnsignedInt(dwLayerID);
			bytes.writeByte(byLevel);
			bytes.writeUnsignedInt(dwAttackedTime);
		}

		public static function vectorToByteArray(vec:Vector.<SDemonToweAttackedInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDemonToweAttackedInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
