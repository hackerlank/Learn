/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFlauntFashion.as
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 时装炫耀
	 */
	public final class SFlauntFashion
	{
		public var wFighterID:uint; //(无符号16位整数)主将ID
		public var byLevel:uint; //(无符号8位整数)时装等级
		public var byType:uint; //(无符号8位整数)类型(0武器,1衣服)
		public var weaponID:uint; //(无符号16位整数)武器ID
		public var armorID:uint; //(无符号16位整数)衣服ID

		/**
		 * 辅助创建函数
		 */
		public static function create(wFighterID:uint, byLevel:uint, byType:uint, weaponID:uint, armorID:uint):SFlauntFashion
		{
			var s_:SFlauntFashion = new SFlauntFashion();
			s_.wFighterID = wFighterID;
			s_.byLevel = byLevel;
			s_.byType = byType;
			s_.weaponID = weaponID;
			s_.armorID = armorID;
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
				topXml = <SFlauntFashion _name_={name_} wFighterID={wFighterID} byLevel={byLevel} byType={byType} weaponID={weaponID} armorID={armorID}/>;
			else
				topXml = <SFlauntFashion wFighterID={wFighterID} byLevel={byLevel} byType={byType} weaponID={weaponID} armorID={armorID}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wFighterID = wFighterID;
			obj_.byLevel = byLevel;
			obj_.byType = byType;
			obj_.weaponID = weaponID;
			obj_.armorID = armorID;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFlauntFashion
		{
			var s_:SFlauntFashion = new SFlauntFashion();
			var wFighterID:uint = bytes.readUnsignedShort();
			s_.wFighterID = wFighterID;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var byType:uint = bytes.readUnsignedByte();
			s_.byType = byType;
			var weaponID:uint = bytes.readUnsignedShort();
			s_.weaponID = weaponID;
			var armorID:uint = bytes.readUnsignedShort();
			s_.armorID = armorID;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFlauntFashion>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFlauntFashion> = new Vector.<SFlauntFashion>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFlauntFashion = SFlauntFashion.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wFighterID);
			bytes.writeByte(byLevel);
			bytes.writeByte(byType);
			bytes.writeShort(weaponID);
			bytes.writeShort(armorID);
		}

		public static function vectorToByteArray(vec:Vector.<SFlauntFashion>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFlauntFashion in vec)
				s.toByteArray(bytes);
		}
	}
}
