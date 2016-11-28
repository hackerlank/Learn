/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPrize2DB.as
//  Purpose:      等级奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.levelPrize
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 数据操作
	 */
	public final class SPrize2DB
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var wActID:uint; //(无符号16位整数)活动ID
		public var wLevel:uint; //(无符号16位整数)奖励NO
		public var wStatus:uint; //(无符号16位整数)奖励状态

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wActID:uint, wLevel:uint, wStatus:uint):SPrize2DB
		{
			var s_:SPrize2DB = new SPrize2DB();
			s_.qwRoleID = qwRoleID;
			s_.wActID = wActID;
			s_.wLevel = wLevel;
			s_.wStatus = wStatus;
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
				topXml = <SPrize2DB _name_={name_} qwRoleID={qwRoleID} wActID={wActID} wLevel={wLevel} wStatus={wStatus}/>;
			else
				topXml = <SPrize2DB qwRoleID={qwRoleID} wActID={wActID} wLevel={wLevel} wStatus={wStatus}/>;
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
			obj_.wLevel = wLevel;
			obj_.wStatus = wStatus;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPrize2DB
		{
			var s_:SPrize2DB = new SPrize2DB();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wActID:uint = bytes.readUnsignedShort();
			s_.wActID = wActID;
			var wLevel:uint = bytes.readUnsignedShort();
			s_.wLevel = wLevel;
			var wStatus:uint = bytes.readUnsignedShort();
			s_.wStatus = wStatus;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPrize2DB>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPrize2DB> = new Vector.<SPrize2DB>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPrize2DB = SPrize2DB.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wActID);
			bytes.writeShort(wLevel);
			bytes.writeShort(wStatus);
		}

		public static function vectorToByteArray(vec:Vector.<SPrize2DB>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPrize2DB in vec)
				s.toByteArray(bytes);
		}
	}
}
