/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SLimitPrize2DB.as
//  Purpose:      天元神兽协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.godMonsterProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * DB Operator
	 */
	public final class SLimitPrize2DB
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var wPrizeID:uint; //(无符号16位整数)礼品ID
		public var wNum:uint; //(无符号16位整数)购买数量

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, wPrizeID:uint, wNum:uint):SLimitPrize2DB
		{
			var s_:SLimitPrize2DB = new SLimitPrize2DB();
			s_.qwRoleID = qwRoleID;
			s_.wPrizeID = wPrizeID;
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
				topXml = <SLimitPrize2DB _name_={name_} qwRoleID={qwRoleID} wPrizeID={wPrizeID} wNum={wNum}/>;
			else
				topXml = <SLimitPrize2DB qwRoleID={qwRoleID} wPrizeID={wPrizeID} wNum={wNum}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.wPrizeID = wPrizeID;
			obj_.wNum = wNum;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SLimitPrize2DB
		{
			var s_:SLimitPrize2DB = new SLimitPrize2DB();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var wPrizeID:uint = bytes.readUnsignedShort();
			s_.wPrizeID = wPrizeID;
			var wNum:uint = bytes.readUnsignedShort();
			s_.wNum = wNum;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SLimitPrize2DB>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SLimitPrize2DB> = new Vector.<SLimitPrize2DB>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SLimitPrize2DB = SLimitPrize2DB.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeShort(wPrizeID);
			bytes.writeShort(wNum);
		}

		public static function vectorToByteArray(vec:Vector.<SLimitPrize2DB>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SLimitPrize2DB in vec)
				s.toByteArray(bytes);
		}
	}
}
