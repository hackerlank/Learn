/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGuildRankInfo.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 排行榜帮派信息
	 */
	public final class SGuildRankInfo
	{
		public var wRank:uint; //(无符号16位整数)排名
		public var qwGuildID:BigInteger; //(无符号64位整数)帮派ID
		public var strName:String; //帮派姓名
		public var dwScore:uint; //(无符号32位整数)战功

		/**
		 * 辅助创建函数
		 */
		public static function create(wRank:uint, qwGuildID:BigInteger, strName:String, dwScore:uint):SGuildRankInfo
		{
			var s_:SGuildRankInfo = new SGuildRankInfo();
			s_.wRank = wRank;
			s_.qwGuildID = qwGuildID;
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
				topXml = <SGuildRankInfo _name_={name_} wRank={wRank} qwGuildID={qwGuildID} strName={strName} dwScore={dwScore}/>;
			else
				topXml = <SGuildRankInfo wRank={wRank} qwGuildID={qwGuildID} strName={strName} dwScore={dwScore}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wRank = wRank;
			obj_.qwGuildID = qwGuildID;
			obj_.strName = strName;
			obj_.dwScore = dwScore;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGuildRankInfo
		{
			var s_:SGuildRankInfo = new SGuildRankInfo();
			var wRank:uint = bytes.readUnsignedShort();
			s_.wRank = wRank;
			var qwGuildID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwGuildID = qwGuildID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var dwScore:uint = bytes.readUnsignedInt();
			s_.dwScore = dwScore;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGuildRankInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGuildRankInfo> = new Vector.<SGuildRankInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGuildRankInfo = SGuildRankInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wRank);
			BytesUtil.writeUInt64(bytes, qwGuildID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeUnsignedInt(dwScore);
		}

		public static function vectorToByteArray(vec:Vector.<SGuildRankInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGuildRankInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
