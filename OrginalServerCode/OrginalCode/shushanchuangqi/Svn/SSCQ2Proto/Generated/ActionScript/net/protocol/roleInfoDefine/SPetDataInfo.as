/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPetDataInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 阵灵信息
	 */
	public final class SPetDataInfo
	{
		public var wPetID:uint; //(无符号16位整数)阵灵ID
		public var bySelected:uint; //(无符号8位整数)是否启用: 0-未启用 1-出战跟随 2-出战不跟随
		public var byLevel:uint; //(无符号8位整数)阵灵等级
		public var dwExp:uint; //(无符号32位整数)阵灵经验

		/**
		 * 辅助创建函数
		 */
		public static function create(wPetID:uint, bySelected:uint, byLevel:uint, dwExp:uint):SPetDataInfo
		{
			var s_:SPetDataInfo = new SPetDataInfo();
			s_.wPetID = wPetID;
			s_.bySelected = bySelected;
			s_.byLevel = byLevel;
			s_.dwExp = dwExp;
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
				topXml = <SPetDataInfo _name_={name_} wPetID={wPetID} bySelected={bySelected} byLevel={byLevel} dwExp={dwExp}/>;
			else
				topXml = <SPetDataInfo wPetID={wPetID} bySelected={bySelected} byLevel={byLevel} dwExp={dwExp}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wPetID = wPetID;
			obj_.bySelected = bySelected;
			obj_.byLevel = byLevel;
			obj_.dwExp = dwExp;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPetDataInfo
		{
			var s_:SPetDataInfo = new SPetDataInfo();
			var wPetID:uint = bytes.readUnsignedShort();
			s_.wPetID = wPetID;
			var bySelected:uint = bytes.readUnsignedByte();
			s_.bySelected = bySelected;
			var byLevel:uint = bytes.readUnsignedByte();
			s_.byLevel = byLevel;
			var dwExp:uint = bytes.readUnsignedInt();
			s_.dwExp = dwExp;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPetDataInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPetDataInfo> = new Vector.<SPetDataInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPetDataInfo = SPetDataInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wPetID);
			bytes.writeByte(bySelected);
			bytes.writeByte(byLevel);
			bytes.writeUnsignedInt(dwExp);
		}

		public static function vectorToByteArray(vec:Vector.<SPetDataInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPetDataInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
