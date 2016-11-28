/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STitle.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 头衔
	 */
	public final class STitle
	{
		public var wId:uint; //(无符号16位整数)头衔ID
		public var byEquipPos:uint; //(无符号8位整数)装备位,从1开始，0表示未装备
		public var dwValidTime:uint; //(无符号32位整数)有效截止时间,0表示永久

		/**
		 * 辅助创建函数
		 */
		public static function create(wId:uint, byEquipPos:uint, dwValidTime:uint):STitle
		{
			var s_:STitle = new STitle();
			s_.wId = wId;
			s_.byEquipPos = byEquipPos;
			s_.dwValidTime = dwValidTime;
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
				topXml = <STitle _name_={name_} wId={wId} byEquipPos={byEquipPos} dwValidTime={dwValidTime}/>;
			else
				topXml = <STitle wId={wId} byEquipPos={byEquipPos} dwValidTime={dwValidTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wId = wId;
			obj_.byEquipPos = byEquipPos;
			obj_.dwValidTime = dwValidTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STitle
		{
			var s_:STitle = new STitle();
			var wId:uint = bytes.readUnsignedShort();
			s_.wId = wId;
			var byEquipPos:uint = bytes.readUnsignedByte();
			s_.byEquipPos = byEquipPos;
			var dwValidTime:uint = bytes.readUnsignedInt();
			s_.dwValidTime = dwValidTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STitle>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STitle> = new Vector.<STitle>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STitle = STitle.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wId);
			bytes.writeByte(byEquipPos);
			bytes.writeUnsignedInt(dwValidTime);
		}

		public static function vectorToByteArray(vec:Vector.<STitle>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STitle in vec)
				s.toByteArray(bytes);
		}
	}
}
