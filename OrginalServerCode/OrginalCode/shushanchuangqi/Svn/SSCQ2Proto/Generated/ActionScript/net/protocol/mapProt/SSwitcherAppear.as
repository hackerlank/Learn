/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SSwitcherAppear.as
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 传送阵开关的外观
	 */
	public final class SSwitcherAppear
	{
		public var dwSwitcherID:uint; //(无符号32位整数)开关配置ID
		public var eType:uint; //(枚举类型：ESwitcherType)开关类型
		public var bOpen:Boolean; //开关状态

		/**
		 * 辅助创建函数
		 */
		public static function create(dwSwitcherID:uint, eType:uint, bOpen:Boolean):SSwitcherAppear
		{
			var s_:SSwitcherAppear = new SSwitcherAppear();
			s_.dwSwitcherID = dwSwitcherID;
			s_.eType = eType;
			s_.bOpen = bOpen;
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
				topXml = <SSwitcherAppear _name_={name_} dwSwitcherID={dwSwitcherID} eType={eType} bOpen={bOpen}/>;
			else
				topXml = <SSwitcherAppear dwSwitcherID={dwSwitcherID} eType={eType} bOpen={bOpen}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwSwitcherID = dwSwitcherID;
			obj_.eType = eType;
			obj_.bOpen = bOpen;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SSwitcherAppear
		{
			var s_:SSwitcherAppear = new SSwitcherAppear();
			var dwSwitcherID:uint = bytes.readUnsignedInt();
			s_.dwSwitcherID = dwSwitcherID;
			var eType:uint = bytes.readUnsignedByte();
			s_.eType = eType;
			var bOpen:Boolean = bytes.readBoolean();
			s_.bOpen = bOpen;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SSwitcherAppear>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SSwitcherAppear> = new Vector.<SSwitcherAppear>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SSwitcherAppear = SSwitcherAppear.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwSwitcherID);
			bytes.writeByte(eType);
			bytes.writeBoolean(bOpen);
		}

		public static function vectorToByteArray(vec:Vector.<SSwitcherAppear>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SSwitcherAppear in vec)
				s.toByteArray(bytes);
		}
	}
}
