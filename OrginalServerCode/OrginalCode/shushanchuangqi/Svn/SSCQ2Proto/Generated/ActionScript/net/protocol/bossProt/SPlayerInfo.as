/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPlayerInfo.as
//  Purpose:      BOSS相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.bossProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 排行帮信息
	 */
	public final class SPlayerInfo
	{
		public var dwNo:uint; //(无符号32位整数)名次
		public var qwUserID:BigInteger; //(无符号64位整数)uid
		public var strUserName:String; //玩家名字
		public var dwDamageHP:uint; //(无符号32位整数)伤害的总血量
		public var dwBossMaxHP:uint; //(无符号32位整数)Boss的总血量

		/**
		 * 辅助创建函数
		 */
		public static function create(dwNo:uint, qwUserID:BigInteger, strUserName:String, dwDamageHP:uint, dwBossMaxHP:uint):SPlayerInfo
		{
			var s_:SPlayerInfo = new SPlayerInfo();
			s_.dwNo = dwNo;
			s_.qwUserID = qwUserID;
			s_.strUserName = strUserName;
			s_.dwDamageHP = dwDamageHP;
			s_.dwBossMaxHP = dwBossMaxHP;
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
				topXml = <SPlayerInfo _name_={name_} dwNo={dwNo} qwUserID={qwUserID} strUserName={strUserName} dwDamageHP={dwDamageHP} dwBossMaxHP={dwBossMaxHP}/>;
			else
				topXml = <SPlayerInfo dwNo={dwNo} qwUserID={qwUserID} strUserName={strUserName} dwDamageHP={dwDamageHP} dwBossMaxHP={dwBossMaxHP}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwNo = dwNo;
			obj_.qwUserID = qwUserID;
			obj_.strUserName = strUserName;
			obj_.dwDamageHP = dwDamageHP;
			obj_.dwBossMaxHP = dwBossMaxHP;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPlayerInfo
		{
			var s_:SPlayerInfo = new SPlayerInfo();
			var dwNo:uint = bytes.readUnsignedInt();
			s_.dwNo = dwNo;
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwUserID = qwUserID;
			var strUserName:String = BytesUtil.readString(bytes);
			s_.strUserName = strUserName;
			var dwDamageHP:uint = bytes.readUnsignedInt();
			s_.dwDamageHP = dwDamageHP;
			var dwBossMaxHP:uint = bytes.readUnsignedInt();
			s_.dwBossMaxHP = dwBossMaxHP;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPlayerInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPlayerInfo> = new Vector.<SPlayerInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPlayerInfo = SPlayerInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwNo);
			BytesUtil.writeUInt64(bytes, qwUserID);
			BytesUtil.writeString(bytes, strUserName);
			bytes.writeUnsignedInt(dwDamageHP);
			bytes.writeUnsignedInt(dwBossMaxHP);
		}

		public static function vectorToByteArray(vec:Vector.<SPlayerInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPlayerInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
