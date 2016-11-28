/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SWonderPrize2DB.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 数据库信息
	 */
	public final class SWonderPrize2DB
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var wActID:uint; //(无符号16位整数)活动ID
		public var wActType:uint; //(无符号16位整数)活动类型
		public var wCond:uint; //(无符号32位整数)活动条件
		public var byStatus:uint; //(无符号8位整数)活动状态

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wActID:uint, wActType:uint, wCond:uint, byStatus:uint):SWonderPrize2DB
		{
			var s_:SWonderPrize2DB = new SWonderPrize2DB();
			s_.qwRoleID = qwRoleID;
			s_.wActID = wActID;
			s_.wActType = wActType;
			s_.wCond = wCond;
			s_.byStatus = byStatus;
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
				topXml = <SWonderPrize2DB _name_={name_} qwRoleID={qwRoleID} wActID={wActID} wActType={wActType} wCond={wCond} byStatus={byStatus}/>;
			else
				topXml = <SWonderPrize2DB qwRoleID={qwRoleID} wActID={wActID} wActType={wActType} wCond={wCond} byStatus={byStatus}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wActID = wActID;
			obj_.wActType = wActType;
			obj_.wCond = wCond;
			obj_.byStatus = byStatus;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SWonderPrize2DB
		{
			var s_:SWonderPrize2DB = new SWonderPrize2DB();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wActID:uint = bytes.readUnsignedShort();
			s_.wActID = wActID;
			var wActType:uint = bytes.readUnsignedShort();
			s_.wActType = wActType;
			var wCond:uint = bytes.readUnsignedInt();
			s_.wCond = wCond;
			var byStatus:uint = bytes.readUnsignedByte();
			s_.byStatus = byStatus;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SWonderPrize2DB>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SWonderPrize2DB> = new Vector.<SWonderPrize2DB>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SWonderPrize2DB = SWonderPrize2DB.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wActID);
			bytes.writeShort(wActType);
			bytes.writeUnsignedInt(wCond);
			bytes.writeByte(byStatus);
		}

		public static function vectorToByteArray(vec:Vector.<SWonderPrize2DB>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SWonderPrize2DB in vec)
				s.toByteArray(bytes);
		}
	}
}
