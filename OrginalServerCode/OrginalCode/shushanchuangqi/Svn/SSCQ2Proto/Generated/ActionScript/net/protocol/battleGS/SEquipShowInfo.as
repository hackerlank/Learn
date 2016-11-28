/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEquipShowInfo.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 发给前端用的显示外形的装备信息
	 */
	public final class SEquipShowInfo
	{
		public var wEquipID:uint; //(无符号16位整数)装备TypeID
		public var byStrengthenLevel:uint; //(无符号8位整数)强化等级
		public var byPos:uint; //(无符号8位整数)装备位置

		/**
		 * 辅助创建函数
		 */
		public static function create(wEquipID:uint, byStrengthenLevel:uint, byPos:uint):SEquipShowInfo
		{
			var s_:SEquipShowInfo = new SEquipShowInfo();
			s_.wEquipID = wEquipID;
			s_.byStrengthenLevel = byStrengthenLevel;
			s_.byPos = byPos;
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
				topXml = <SEquipShowInfo _name_={name_} wEquipID={wEquipID} byStrengthenLevel={byStrengthenLevel} byPos={byPos}/>;
			else
				topXml = <SEquipShowInfo wEquipID={wEquipID} byStrengthenLevel={byStrengthenLevel} byPos={byPos}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wEquipID = wEquipID;
			obj_.byStrengthenLevel = byStrengthenLevel;
			obj_.byPos = byPos;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEquipShowInfo
		{
			var s_:SEquipShowInfo = new SEquipShowInfo();
			var wEquipID:uint = bytes.readUnsignedShort();
			s_.wEquipID = wEquipID;
			var byStrengthenLevel:uint = bytes.readUnsignedByte();
			s_.byStrengthenLevel = byStrengthenLevel;
			var byPos:uint = bytes.readUnsignedByte();
			s_.byPos = byPos;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEquipShowInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEquipShowInfo> = new Vector.<SEquipShowInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEquipShowInfo = SEquipShowInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wEquipID);
			bytes.writeByte(byStrengthenLevel);
			bytes.writeByte(byPos);
		}

		public static function vectorToByteArray(vec:Vector.<SEquipShowInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEquipShowInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
