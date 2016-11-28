/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPlayerRankInfo.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 排行榜个人信息
	 */
	public final class SPlayerRankInfo
	{
		public var wRank:uint; //(无符号16位整数)排名
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var strName:String; //玩家姓名
		public var dwScore:uint; //(无符号32位整数)战功

		/**
		 * 辅助创建函数
		 */
		public static function create(wRank:uint, qwRoleID:BigInteger, strName:String, dwScore:uint):SPlayerRankInfo
		{
			var s_:SPlayerRankInfo = new SPlayerRankInfo();
			s_.wRank = wRank;
			s_.qwRoleID = qwRoleID;
			s_.strName = strName;
			s_.dwScore = dwScore;
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
				topXml = <SPlayerRankInfo _name_={name_} wRank={wRank} qwRoleID={qwRoleID} strName={strName} dwScore={dwScore}/>;
			else
				topXml = <SPlayerRankInfo wRank={wRank} qwRoleID={qwRoleID} strName={strName} dwScore={dwScore}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wRank = wRank;
			obj_.qwRoleID = qwRoleID;
			obj_.strName = strName;
			obj_.dwScore = dwScore;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPlayerRankInfo
		{
			var s_:SPlayerRankInfo = new SPlayerRankInfo();
			var wRank:uint = bytes.readUnsignedShort();
			s_.wRank = wRank;
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var dwScore:uint = bytes.readUnsignedInt();
			s_.dwScore = dwScore;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPlayerRankInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPlayerRankInfo> = new Vector.<SPlayerRankInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPlayerRankInfo = SPlayerRankInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wRank);
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeUnsignedInt(dwScore);
		}

		public static function vectorToByteArray(vec:Vector.<SPlayerRankInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPlayerRankInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
