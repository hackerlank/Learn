/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SXinFaDBInfo.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 数据库同步到游戏服务器的心法信息
	 */
	public final class SXinFaDBInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)所属角色唯一ID
		public var qwOwnerID:BigInteger; //(无符号64位整数)所属散仙ID
		public var dwXinFaID:uint; //(无符号32位整数)心法ID
		public var byXinFaLvl:uint; //(无符号8位整数)心法等级
		public var iSlot:int; //(有符号32位整数)心法槽 -1表示心法没装备

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, qwOwnerID:BigInteger, dwXinFaID:uint, byXinFaLvl:uint, iSlot:int):SXinFaDBInfo
		{
			var s_:SXinFaDBInfo = new SXinFaDBInfo();
			s_.qwRoleID = qwRoleID;
			s_.qwOwnerID = qwOwnerID;
			s_.dwXinFaID = dwXinFaID;
			s_.byXinFaLvl = byXinFaLvl;
			s_.iSlot = iSlot;
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
				topXml = <SXinFaDBInfo _name_={name_} qwRoleID={qwRoleID} qwOwnerID={qwOwnerID} dwXinFaID={dwXinFaID} byXinFaLvl={byXinFaLvl} iSlot={iSlot}/>;
			else
				topXml = <SXinFaDBInfo qwRoleID={qwRoleID} qwOwnerID={qwOwnerID} dwXinFaID={dwXinFaID} byXinFaLvl={byXinFaLvl} iSlot={iSlot}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.qwOwnerID = qwOwnerID;
			obj_.dwXinFaID = dwXinFaID;
			obj_.byXinFaLvl = byXinFaLvl;
			obj_.iSlot = iSlot;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SXinFaDBInfo
		{
			var s_:SXinFaDBInfo = new SXinFaDBInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var qwOwnerID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOwnerID = qwOwnerID;
			var dwXinFaID:uint = bytes.readUnsignedInt();
			s_.dwXinFaID = dwXinFaID;
			var byXinFaLvl:uint = bytes.readUnsignedByte();
			s_.byXinFaLvl = byXinFaLvl;
			var iSlot:int = bytes.readInt();
			s_.iSlot = iSlot;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SXinFaDBInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SXinFaDBInfo> = new Vector.<SXinFaDBInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SXinFaDBInfo = SXinFaDBInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeUInt64(bytes, qwOwnerID);
			bytes.writeUnsignedInt(dwXinFaID);
			bytes.writeByte(byXinFaLvl);
			bytes.writeInt(iSlot);
		}

		public static function vectorToByteArray(vec:Vector.<SXinFaDBInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SXinFaDBInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
