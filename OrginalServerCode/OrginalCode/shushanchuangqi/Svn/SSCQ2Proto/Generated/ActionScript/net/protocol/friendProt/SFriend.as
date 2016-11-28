/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFriend.as
//  Purpose:      好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 好友
	 */
	public final class SFriend
	{
		public var wMood:uint; //(无符号16位整数)我的心情表情
		public var strSign:String; //我的签名
		public var vecFriendEntry:Vector.<SFriendEntry>; //好友列表

		/**
		 * 辅助创建函数
		 */
		public static function create(wMood:uint, strSign:String, vecFriendEntry:Vector.<SFriendEntry>):SFriend
		{
			var s_:SFriend = new SFriend();
			s_.wMood = wMood;
			s_.strSign = strSign;
			s_.vecFriendEntry = vecFriendEntry;
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
				topXml = <SFriend _name_={name_} wMood={wMood} strSign={strSign}/>;
			else
				topXml = <SFriend wMood={wMood} strSign={strSign}/>;
			if(vecFriendEntry != null)
			{
				var vecFriendEntryXml:XML = <Vec_SFriendEntry _name_="vecFriendEntry"/>;
				for each(var s1:SFriendEntry in vecFriendEntry)
					vecFriendEntryXml.appendChild(s1.toXML());
				topXml.appendChild(vecFriendEntryXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wMood = wMood;
			obj_.strSign = strSign;
			obj_.vecFriendEntry = vecFriendEntry;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFriend
		{
			var s_:SFriend = new SFriend();
			var wMood:uint = bytes.readUnsignedShort();
			s_.wMood = wMood;
			var strSign:String = BytesUtil.readString(bytes);
			s_.strSign = strSign;
			var vecFriendEntry:Vector.<SFriendEntry> = SFriendEntry.vectorFromByteArray(bytes);
			s_.vecFriendEntry = vecFriendEntry;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFriend>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFriend> = new Vector.<SFriend>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFriend = SFriend.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wMood);
			BytesUtil.writeString(bytes, strSign);
			SFriendEntry.vectorToByteArray(vecFriendEntry, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SFriend>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFriend in vec)
				s.toByteArray(bytes);
		}
	}
}
