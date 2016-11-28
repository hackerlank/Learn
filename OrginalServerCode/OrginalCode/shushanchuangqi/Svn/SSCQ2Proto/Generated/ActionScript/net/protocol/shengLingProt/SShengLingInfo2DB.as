/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SShengLingInfo2DB.as
//  Purpose:      圣陵协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 数据库信息
	 */
	public final class SShengLingInfo2DB
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var byLevel:uint; //(无符号8位整数)玩家所在层
		public var byIndex:uint; //(无符号8位整数)格子ID
		public var byType:uint; //(无符号8位整数)格子类型
		public var wNoteID:uint; //(无符号16位整数)格子中记录ID
		public var byRandom:uint; //(无符号8位整数)是否随机格子
		public var byFinish:uint; //(无符号8位整数)是否完成

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, byLevel:uint, byIndex:uint, byType:uint, wNoteID:uint, 
			byRandom:uint, byFinish:uint):SShengLingInfo2DB
		{
			var s_:SShengLingInfo2DB = new SShengLingInfo2DB();
			s_.qwRoleID = qwRoleID;
			s_.byLevel = byLevel;
			s_.byIndex = byIndex;
			s_.byType = byType;
			s_.wNoteID = wNoteID;
			s_.byRandom = byRandom;
			s_.byFinish = byFinish;
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
				topXml = <SShengLingInfo2DB _name_={name_} qwRoleID={qwRoleID} byLevel={byLevel} byIndex={byIndex} byType={byType} wNoteID={wNoteID}
				 byRandom={byRandom} byFinish={byFinish}/>;
			else
				topXml = <SShengLingInfo2DB qwRoleID={qwRoleID} byLevel={byLevel} byIndex={byIndex} byType={byType} wNoteID={wNoteID}
				 byRandom={byRandom} byFinish={byFinish}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.byLevel = byLevel;
			obj_.byIndex = byIndex;
			obj_.byType = byType;
			obj_.wNoteID = wNoteID;
			obj_.byRandom = byRandom;
			obj_.byFinish = byFinish;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SShengLingInfo2DB
		{
			var s_:SShengLingInfo2DB = new SShengLingInfo2DB();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var byIndex:uint = bytes.readUnsignedByte();
			s_.byIndex = byIndex;
			var byType:uint = bytes.readUnsignedByte();
			s_.byType = byType;
			var wNoteID:uint = bytes.readUnsignedShort();
			s_.wNoteID = wNoteID;
			var byRandom:uint = bytes.readUnsignedByte();
			s_.byRandom = byRandom;
			var byFinish:uint = bytes.readUnsignedByte();
			s_.byFinish = byFinish;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SShengLingInfo2DB>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SShengLingInfo2DB> = new Vector.<SShengLingInfo2DB>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SShengLingInfo2DB = SShengLingInfo2DB.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeByte(byLevel);
			bytes.writeByte(byIndex);
			bytes.writeByte(byType);
			bytes.writeShort(wNoteID);
			bytes.writeByte(byRandom);
			bytes.writeByte(byFinish);
		}

		public static function vectorToByteArray(vec:Vector.<SShengLingInfo2DB>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SShengLingInfo2DB in vec)
				s.toByteArray(bytes);
		}
	}
}
