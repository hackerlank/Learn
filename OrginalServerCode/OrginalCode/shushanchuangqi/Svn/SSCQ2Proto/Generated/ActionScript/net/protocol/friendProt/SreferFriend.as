/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SreferFriend.as
//  Purpose:      好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 推荐好友
	 */
	public final class SreferFriend
	{
		public var qwUserID:BigInteger; //(无符号64位整数)帐号ID
		public var byLevel:uint; //(无符号8位整数)等级
		public var wHeroID:uint; //(无符号16位整数)主将ID
		public var strName:String; //用户名称

		/**
		 * 辅助创建函数
		 */
		public static function create(qwUserID:BigInteger, byLevel:uint, wHeroID:uint, strName:String):SreferFriend
		{
			var s_:SreferFriend = new SreferFriend();
			s_.qwUserID = qwUserID;
			s_.byLevel = byLevel;
			s_.wHeroID = wHeroID;
			s_.strName = strName;
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
				topXml = <SreferFriend _name_={name_} qwUserID={qwUserID} byLevel={byLevel} wHeroID={wHeroID} strName={strName}/>;
			else
				topXml = <SreferFriend qwUserID={qwUserID} byLevel={byLevel} wHeroID={wHeroID} strName={strName}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwUserID = qwUserID;
			obj_.byLevel = byLevel;
			obj_.wHeroID = wHeroID;
			obj_.strName = strName;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SreferFriend
		{
			var s_:SreferFriend = new SreferFriend();
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwUserID = qwUserID;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var wHeroID:uint = bytes.readUnsignedShort();
			s_.wHeroID = wHeroID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SreferFriend>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SreferFriend> = new Vector.<SreferFriend>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SreferFriend = SreferFriend.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwUserID);
			bytes.writeByte(byLevel);
			bytes.writeShort(wHeroID);
			BytesUtil.writeString(bytes, strName);
		}

		public static function vectorToByteArray(vec:Vector.<SreferFriend>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SreferFriend in vec)
				s.toByteArray(bytes);
		}
	}
}
