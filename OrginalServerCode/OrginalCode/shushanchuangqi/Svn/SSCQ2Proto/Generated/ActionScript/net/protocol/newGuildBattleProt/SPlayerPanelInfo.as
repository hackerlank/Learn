/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPlayerPanelInfo.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 面板玩家信息
	 */
	public final class SPlayerPanelInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var strName:String; //玩家姓名
		public var byLevel:uint; //(无符号8位整数)玩家等级
		public var byQuality:uint; //(无符号8位整数)品质
		public var qwGuildID:BigInteger; //(无符号64位整数)帮派ID
		public var eSide:uint; //(枚举类型：ENGBSide)自己所在方向
		public var strGuildName:String; //帮派名称
		public var byHPP:uint; //(无符号8位整数)剩余生命值百分比
		public var dwMaxHP:uint; //(无符号32位整数)最大血量
		public var dwHP:uint; //(无符号32位整数)当前血量

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, strName:String, byLevel:uint, byQuality:uint, qwGuildID:BigInteger, 
			eSide:uint, strGuildName:String, byHPP:uint, dwMaxHP:uint, dwHP:uint):SPlayerPanelInfo
		{
			var s_:SPlayerPanelInfo = new SPlayerPanelInfo();
			s_.qwRoleID = qwRoleID;
			s_.strName = strName;
			s_.byLevel = byLevel;
			s_.byQuality = byQuality;
			s_.qwGuildID = qwGuildID;
			s_.eSide = eSide;
			s_.strGuildName = strGuildName;
			s_.byHPP = byHPP;
			s_.dwMaxHP = dwMaxHP;
			s_.dwHP = dwHP;
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
				topXml = <SPlayerPanelInfo _name_={name_} qwRoleID={qwRoleID} strName={strName} byLevel={byLevel} byQuality={byQuality} qwGuildID={qwGuildID}
				 eSide={eSide} strGuildName={strGuildName} byHPP={byHPP} dwMaxHP={dwMaxHP} dwHP={dwHP}/>;
			else
				topXml = <SPlayerPanelInfo qwRoleID={qwRoleID} strName={strName} byLevel={byLevel} byQuality={byQuality} qwGuildID={qwGuildID}
				 eSide={eSide} strGuildName={strGuildName} byHPP={byHPP} dwMaxHP={dwMaxHP} dwHP={dwHP}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.strName = strName;
			obj_.byLevel = byLevel;
			obj_.byQuality = byQuality;
			obj_.qwGuildID = qwGuildID;
			obj_.eSide = eSide;
			obj_.strGuildName = strGuildName;
			obj_.byHPP = byHPP;
			obj_.dwMaxHP = dwMaxHP;
			obj_.dwHP = dwHP;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPlayerPanelInfo
		{
			var s_:SPlayerPanelInfo = new SPlayerPanelInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var byQuality:uint = bytes.readUnsignedByte();
			s_.byQuality = byQuality;
			var qwGuildID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwGuildID = qwGuildID;
			var eSide:uint = bytes.readUnsignedByte();
			s_.eSide = eSide;
			var strGuildName:String = BytesUtil.readString(bytes);
			s_.strGuildName = strGuildName;
			var byHPP:uint = bytes.readUnsignedByte();
			s_.byHPP = byHPP;
			var dwMaxHP:uint = bytes.readUnsignedInt();
			s_.dwMaxHP = dwMaxHP;
			var dwHP:uint = bytes.readUnsignedInt();
			s_.dwHP = dwHP;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPlayerPanelInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPlayerPanelInfo> = new Vector.<SPlayerPanelInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPlayerPanelInfo = SPlayerPanelInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(byLevel);
			bytes.writeByte(byQuality);
			BytesUtil.writeUInt64(bytes, qwGuildID);
			bytes.writeByte(eSide);
			BytesUtil.writeString(bytes, strGuildName);
			bytes.writeByte(byHPP);
			bytes.writeUnsignedInt(dwMaxHP);
			bytes.writeUnsignedInt(dwHP);
		}

		public static function vectorToByteArray(vec:Vector.<SPlayerPanelInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPlayerPanelInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
