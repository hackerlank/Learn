/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SHorseDB.as
//  Purpose:      坐骑
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 坐骑数据库数据
	 */
	public final class SHorseDB
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)角色id
		public var qwUserID:BigInteger; //(无符号64位整数)账号
		public var dwHorseID:uint; //(无符号32位整数)坐骑id
		public var dwHorseLevel:uint; //(无符号32位整数)坐骑等级
		public var dwPos:uint; //(无符号32位整数)坐骑位置1表示骑乘
		public var dwModelID:uint; //(无符号32位整数)坐骑模型id
		public var dwExp:uint; //(无符号32位整数)坐骑当前经验
		public var dwLock:uint; //(无符号32位整数)坐骑技能锁定
		public var strModel:String; //坐骑外观列表

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, qwUserID:BigInteger, dwHorseID:uint, dwHorseLevel:uint, dwPos:uint, 
			dwModelID:uint, dwExp:uint, dwLock:uint, strModel:String):SHorseDB
		{
			var s_:SHorseDB = new SHorseDB();
			s_.qwRoleID = qwRoleID;
			s_.qwUserID = qwUserID;
			s_.dwHorseID = dwHorseID;
			s_.dwHorseLevel = dwHorseLevel;
			s_.dwPos = dwPos;
			s_.dwModelID = dwModelID;
			s_.dwExp = dwExp;
			s_.dwLock = dwLock;
			s_.strModel = strModel;
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
				topXml = <SHorseDB _name_={name_} qwRoleID={qwRoleID} qwUserID={qwUserID} dwHorseID={dwHorseID} dwHorseLevel={dwHorseLevel} dwPos={dwPos}
				 dwModelID={dwModelID} dwExp={dwExp} dwLock={dwLock} strModel={strModel}/>;
			else
				topXml = <SHorseDB qwRoleID={qwRoleID} qwUserID={qwUserID} dwHorseID={dwHorseID} dwHorseLevel={dwHorseLevel} dwPos={dwPos}
				 dwModelID={dwModelID} dwExp={dwExp} dwLock={dwLock} strModel={strModel}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.qwUserID = qwUserID;
			obj_.dwHorseID = dwHorseID;
			obj_.dwHorseLevel = dwHorseLevel;
			obj_.dwPos = dwPos;
			obj_.dwModelID = dwModelID;
			obj_.dwExp = dwExp;
			obj_.dwLock = dwLock;
			obj_.strModel = strModel;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SHorseDB
		{
			var s_:SHorseDB = new SHorseDB();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwUserID = qwUserID;
			var dwHorseID:uint = bytes.readUnsignedInt();
			s_.dwHorseID = dwHorseID;
			var dwHorseLevel:uint = bytes.readUnsignedInt();
			s_.dwHorseLevel = dwHorseLevel;
			var dwPos:uint = bytes.readUnsignedInt();
			s_.dwPos = dwPos;
			var dwModelID:uint = bytes.readUnsignedInt();
			s_.dwModelID = dwModelID;
			var dwExp:uint = bytes.readUnsignedInt();
			s_.dwExp = dwExp;
			var dwLock:uint = bytes.readUnsignedInt();
			s_.dwLock = dwLock;
			var strModel:String = BytesUtil.readString(bytes);
			s_.strModel = strModel;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SHorseDB>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SHorseDB> = new Vector.<SHorseDB>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SHorseDB = SHorseDB.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeUInt64(bytes, qwUserID);
			bytes.writeUnsignedInt(dwHorseID);
			bytes.writeUnsignedInt(dwHorseLevel);
			bytes.writeUnsignedInt(dwPos);
			bytes.writeUnsignedInt(dwModelID);
			bytes.writeUnsignedInt(dwExp);
			bytes.writeUnsignedInt(dwLock);
			BytesUtil.writeString(bytes, strModel);
		}

		public static function vectorToByteArray(vec:Vector.<SHorseDB>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SHorseDB in vec)
				s.toByteArray(bytes);
		}
	}
}
