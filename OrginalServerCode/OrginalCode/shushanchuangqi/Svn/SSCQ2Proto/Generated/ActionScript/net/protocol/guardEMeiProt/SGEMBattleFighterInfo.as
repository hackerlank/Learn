/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGEMBattleFighterInfo.as
//  Purpose:      守卫峨眉协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 守卫峨眉参战散仙信息
	 */
	public final class SGEMBattleFighterInfo
	{
		public var dwFighterID:uint; //(无符号32位整数)将模版ID
		public var byFighterLevel:uint; //(无符号8位整数)将等级
		public var byFighterColour:uint; //(无符号8位整数)将颜色
		public var dwFighterCurHP:uint; //(无符号32位整数)将当前血量
		public var dwFighterMaxHP:uint; //(无符号32位整数)将最大血量
		public var dwFighterCurAnima:uint; //(无符号32位整数)将当前灵气
		public var dwFighterMaxAnima:uint; //(无符号32位整数)将最大灵气

		/**
		 * 辅助创建函数
		 */
		public static function create(dwFighterID:uint, byFighterLevel:uint, byFighterColour:uint, dwFighterCurHP:uint, dwFighterMaxHP:uint, 
			dwFighterCurAnima:uint, dwFighterMaxAnima:uint):SGEMBattleFighterInfo
		{
			var s_:SGEMBattleFighterInfo = new SGEMBattleFighterInfo();
			s_.dwFighterID = dwFighterID;
			s_.byFighterLevel = byFighterLevel;
			s_.byFighterColour = byFighterColour;
			s_.dwFighterCurHP = dwFighterCurHP;
			s_.dwFighterMaxHP = dwFighterMaxHP;
			s_.dwFighterCurAnima = dwFighterCurAnima;
			s_.dwFighterMaxAnima = dwFighterMaxAnima;
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
				topXml = <SGEMBattleFighterInfo _name_={name_} dwFighterID={dwFighterID} byFighterLevel={byFighterLevel} byFighterColour={byFighterColour} dwFighterCurHP={dwFighterCurHP} dwFighterMaxHP={dwFighterMaxHP}
				 dwFighterCurAnima={dwFighterCurAnima} dwFighterMaxAnima={dwFighterMaxAnima}/>;
			else
				topXml = <SGEMBattleFighterInfo dwFighterID={dwFighterID} byFighterLevel={byFighterLevel} byFighterColour={byFighterColour} dwFighterCurHP={dwFighterCurHP} dwFighterMaxHP={dwFighterMaxHP}
				 dwFighterCurAnima={dwFighterCurAnima} dwFighterMaxAnima={dwFighterMaxAnima}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwFighterID = dwFighterID;
			obj_.byFighterLevel = byFighterLevel;
			obj_.byFighterColour = byFighterColour;
			obj_.dwFighterCurHP = dwFighterCurHP;
			obj_.dwFighterMaxHP = dwFighterMaxHP;
			obj_.dwFighterCurAnima = dwFighterCurAnima;
			obj_.dwFighterMaxAnima = dwFighterMaxAnima;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGEMBattleFighterInfo
		{
			var s_:SGEMBattleFighterInfo = new SGEMBattleFighterInfo();
			var dwFighterID:uint = bytes.readUnsignedInt();
			s_.dwFighterID = dwFighterID;
			var byFighterLevel:uint = bytes.readUnsignedByte();
			s_.byFighterLevel = byFighterLevel;
			var byFighterColour:uint = bytes.readUnsignedByte();
			s_.byFighterColour = byFighterColour;
			var dwFighterCurHP:uint = bytes.readUnsignedInt();
			s_.dwFighterCurHP = dwFighterCurHP;
			var dwFighterMaxHP:uint = bytes.readUnsignedInt();
			s_.dwFighterMaxHP = dwFighterMaxHP;
			var dwFighterCurAnima:uint = bytes.readUnsignedInt();
			s_.dwFighterCurAnima = dwFighterCurAnima;
			var dwFighterMaxAnima:uint = bytes.readUnsignedInt();
			s_.dwFighterMaxAnima = dwFighterMaxAnima;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGEMBattleFighterInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGEMBattleFighterInfo> = new Vector.<SGEMBattleFighterInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGEMBattleFighterInfo = SGEMBattleFighterInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwFighterID);
			bytes.writeByte(byFighterLevel);
			bytes.writeByte(byFighterColour);
			bytes.writeUnsignedInt(dwFighterCurHP);
			bytes.writeUnsignedInt(dwFighterMaxHP);
			bytes.writeUnsignedInt(dwFighterCurAnima);
			bytes.writeUnsignedInt(dwFighterMaxAnima);
		}

		public static function vectorToByteArray(vec:Vector.<SGEMBattleFighterInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGEMBattleFighterInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
