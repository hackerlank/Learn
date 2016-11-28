/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SFormationInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 阵型信息
	 */
	public final class SFormationInfo
	{
		public var wFormationID:uint; //(无符号16位整数)阵型ID
		public var bySelected:uint; //(无符号8位整数)是否启用

		/**
		 * 辅助创建函数
		 */
		public static function create(wFormationID:uint, bySelected:uint):SFormationInfo
		{
			var s_:SFormationInfo = new SFormationInfo();
			s_.wFormationID = wFormationID;
			s_.bySelected = bySelected;
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
				topXml = <SFormationInfo _name_={name_} wFormationID={wFormationID} bySelected={bySelected}/>;
			else
				topXml = <SFormationInfo wFormationID={wFormationID} bySelected={bySelected}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wFormationID = wFormationID;
			obj_.bySelected = bySelected;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SFormationInfo
		{
			var s_:SFormationInfo = new SFormationInfo();
			var wFormationID:uint = bytes.readUnsignedShort();
			s_.wFormationID = wFormationID;
			var bySelected:uint = bytes.readUnsignedByte();
			s_.bySelected = bySelected;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SFormationInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SFormationInfo> = new Vector.<SFormationInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SFormationInfo = SFormationInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wFormationID);
			bytes.writeByte(bySelected);
		}

		public static function vectorToByteArray(vec:Vector.<SFormationInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SFormationInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
