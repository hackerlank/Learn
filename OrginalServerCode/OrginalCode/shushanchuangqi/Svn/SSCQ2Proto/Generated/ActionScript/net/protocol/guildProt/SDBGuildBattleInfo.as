/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SDBGuildBattleInfo.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 数据库加载用帮派玩家数据
	 */
	public final class SDBGuildBattleInfo
	{
		public var qwGuildID:BigInteger; //(无符号64位整数)帮派唯一ID
		public var dwScore:uint; //(无符号32位整数)帮派战积分

		/**
		 * 辅助创建函数
		 */
		public static function create(qwGuildID:BigInteger, dwScore:uint):SDBGuildBattleInfo
		{
			var s_:SDBGuildBattleInfo = new SDBGuildBattleInfo();
			s_.qwGuildID = qwGuildID;
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
				topXml = <SDBGuildBattleInfo _name_={name_} qwGuildID={qwGuildID} dwScore={dwScore}/>;
			else
				topXml = <SDBGuildBattleInfo qwGuildID={qwGuildID} dwScore={dwScore}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwGuildID = qwGuildID;
			obj_.dwScore = dwScore;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SDBGuildBattleInfo
		{
			var s_:SDBGuildBattleInfo = new SDBGuildBattleInfo();
			var qwGuildID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwGuildID = qwGuildID;
			var dwScore:uint = bytes.readUnsignedInt();
			s_.dwScore = dwScore;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SDBGuildBattleInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SDBGuildBattleInfo> = new Vector.<SDBGuildBattleInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SDBGuildBattleInfo = SDBGuildBattleInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwGuildID);
			bytes.writeUnsignedInt(dwScore);
		}

		public static function vectorToByteArray(vec:Vector.<SDBGuildBattleInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SDBGuildBattleInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
