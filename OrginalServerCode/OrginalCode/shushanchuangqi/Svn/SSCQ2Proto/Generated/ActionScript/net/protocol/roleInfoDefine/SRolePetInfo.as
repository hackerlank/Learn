/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRolePetInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 阵灵全局信息
	 */
	public final class SRolePetInfo
	{
		public var dwExp:uint; //(无符号32位整数)阵灵经验
		public var byLevel:uint; //(无符号8位整数)阵灵等级
		public var dwSpirit:uint; //(无符号32位整数)阵灵灵力值

		/**
		 * 辅助创建函数
		 */
		public static function create(dwExp:uint, byLevel:uint, dwSpirit:uint):SRolePetInfo
		{
			var s_:SRolePetInfo = new SRolePetInfo();
			s_.dwExp = dwExp;
			s_.byLevel = byLevel;
			s_.dwSpirit = dwSpirit;
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
				topXml = <SRolePetInfo _name_={name_} dwExp={dwExp} byLevel={byLevel} dwSpirit={dwSpirit}/>;
			else
				topXml = <SRolePetInfo dwExp={dwExp} byLevel={byLevel} dwSpirit={dwSpirit}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwExp = dwExp;
			obj_.byLevel = byLevel;
			obj_.dwSpirit = dwSpirit;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRolePetInfo
		{
			var s_:SRolePetInfo = new SRolePetInfo();
			var dwExp:uint = bytes.readUnsignedInt();
			s_.dwExp = dwExp;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var dwSpirit:uint = bytes.readUnsignedInt();
			s_.dwSpirit = dwSpirit;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRolePetInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRolePetInfo> = new Vector.<SRolePetInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRolePetInfo = SRolePetInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwExp);
			bytes.writeByte(byLevel);
			bytes.writeUnsignedInt(dwSpirit);
		}

		public static function vectorToByteArray(vec:Vector.<SRolePetInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRolePetInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
