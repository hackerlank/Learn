/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    FightHeroInfo.as
//  Purpose:      新阵型相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fightFormation
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 战斗散仙信息
	 */
	public final class FightHeroInfo
	{
		public var qwInstID:BigInteger; //(无符号64位整数)散仙InstID
		public var dwHP:uint; //(无符号32位整数)当前生命值
		public var dwMaxHP:uint; //(无符号32位整数)最大生命值（可能用到）
		public var dwAura:uint; //(无符号32位整数)灵气值
		public var dwMaxAura:uint; //(无符号32位整数)最大灵气值

		/**
		 * 辅助创建函数
		 */
		public static function create(qwInstID:BigInteger, dwHP:uint, dwMaxHP:uint, dwAura:uint, dwMaxAura:uint):FightHeroInfo
		{
			var s_:FightHeroInfo = new FightHeroInfo();
			s_.qwInstID = qwInstID;
			s_.dwHP = dwHP;
			s_.dwMaxHP = dwMaxHP;
			s_.dwAura = dwAura;
			s_.dwMaxAura = dwMaxAura;
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
				topXml = <FightHeroInfo _name_={name_} qwInstID={qwInstID} dwHP={dwHP} dwMaxHP={dwMaxHP} dwAura={dwAura} dwMaxAura={dwMaxAura}/>;
			else
				topXml = <FightHeroInfo qwInstID={qwInstID} dwHP={dwHP} dwMaxHP={dwMaxHP} dwAura={dwAura} dwMaxAura={dwMaxAura}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwInstID = qwInstID;
			obj_.dwHP = dwHP;
			obj_.dwMaxHP = dwMaxHP;
			obj_.dwAura = dwAura;
			obj_.dwMaxAura = dwMaxAura;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):FightHeroInfo
		{
			var s_:FightHeroInfo = new FightHeroInfo();
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwInstID = qwInstID;
			var dwHP:uint = bytes.readUnsignedInt();
			s_.dwHP = dwHP;
			var dwMaxHP:uint = bytes.readUnsignedInt();
			s_.dwMaxHP = dwMaxHP;
			var dwAura:uint = bytes.readUnsignedInt();
			s_.dwAura = dwAura;
			var dwMaxAura:uint = bytes.readUnsignedInt();
			s_.dwMaxAura = dwMaxAura;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<FightHeroInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<FightHeroInfo> = new Vector.<FightHeroInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:FightHeroInfo = FightHeroInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwInstID);
			bytes.writeUnsignedInt(dwHP);
			bytes.writeUnsignedInt(dwMaxHP);
			bytes.writeUnsignedInt(dwAura);
			bytes.writeUnsignedInt(dwMaxAura);
		}

		public static function vectorToByteArray(vec:Vector.<FightHeroInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:FightHeroInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
