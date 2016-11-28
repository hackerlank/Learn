/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildUser2DB.as
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
	public final class SGuildUser2DB
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)名字
		public var qwGuildID:BigInteger; //(无符号64位整数)职务
		public var dwFruit:uint; //(无符号32位整数)朱果数量
		public var dwScore:uint; //(无符号32位整数)积分
		public var dwTotalScore:uint; //(无符号32位整数)总积分

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, qwGuildID:BigInteger, dwFruit:uint, dwScore:uint, dwTotalScore:uint):SGuildUser2DB
		{
			var s_:SGuildUser2DB = new SGuildUser2DB();
			s_.qwRoleID = qwRoleID;
			s_.qwGuildID = qwGuildID;
			s_.dwFruit = dwFruit;
			s_.dwScore = dwScore;
			s_.dwTotalScore = dwTotalScore;
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
				topXml = <SGuildUser2DB _name_={name_} qwRoleID={qwRoleID} qwGuildID={qwGuildID} dwFruit={dwFruit} dwScore={dwScore} dwTotalScore={dwTotalScore}/>;
			else
				topXml = <SGuildUser2DB qwRoleID={qwRoleID} qwGuildID={qwGuildID} dwFruit={dwFruit} dwScore={dwScore} dwTotalScore={dwTotalScore}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.qwGuildID = qwGuildID;
			obj_.dwFruit = dwFruit;
			obj_.dwScore = dwScore;
			obj_.dwTotalScore = dwTotalScore;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildUser2DB
		{
			var s_:SGuildUser2DB = new SGuildUser2DB();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var qwGuildID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwGuildID = qwGuildID;
			var dwFruit:uint = bytes.readUnsignedInt();
			s_.dwFruit = dwFruit;
			var dwScore:uint = bytes.readUnsignedInt();
			s_.dwScore = dwScore;
			var dwTotalScore:uint = bytes.readUnsignedInt();
			s_.dwTotalScore = dwTotalScore;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildUser2DB>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildUser2DB> = new Vector.<SGuildUser2DB>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildUser2DB = SGuildUser2DB.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeUInt64(bytes, qwGuildID);
			bytes.writeUnsignedInt(dwFruit);
			bytes.writeUnsignedInt(dwScore);
			bytes.writeUnsignedInt(dwTotalScore);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildUser2DB>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildUser2DB in vec)
				s.toByteArray(bytes);
		}
	}
}
