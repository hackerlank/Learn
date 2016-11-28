/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SShengLingPrize2DB.as
//  Purpose:      圣陵协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 数据库奖励信息
	 */
	public final class SShengLingPrize2DB
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var wItemID:uint; //(无符号16位整数)物品
		public var wNum:uint; //(无符号16位整数)数量

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wItemID:uint, wNum:uint):SShengLingPrize2DB
		{
			var s_:SShengLingPrize2DB = new SShengLingPrize2DB();
			s_.qwRoleID = qwRoleID;
			s_.wItemID = wItemID;
			s_.wNum = wNum;
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
				topXml = <SShengLingPrize2DB _name_={name_} qwRoleID={qwRoleID} wItemID={wItemID} wNum={wNum}/>;
			else
				topXml = <SShengLingPrize2DB qwRoleID={qwRoleID} wItemID={wItemID} wNum={wNum}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wItemID = wItemID;
			obj_.wNum = wNum;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SShengLingPrize2DB
		{
			var s_:SShengLingPrize2DB = new SShengLingPrize2DB();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wItemID:uint = bytes.readUnsignedShort();
			s_.wItemID = wItemID;
			var wNum:uint = bytes.readUnsignedShort();
			s_.wNum = wNum;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SShengLingPrize2DB>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SShengLingPrize2DB> = new Vector.<SShengLingPrize2DB>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SShengLingPrize2DB = SShengLingPrize2DB.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wItemID);
			bytes.writeShort(wNum);
		}

		public static function vectorToByteArray(vec:Vector.<SShengLingPrize2DB>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SShengLingPrize2DB in vec)
				s.toByteArray(bytes);
		}
	}
}
