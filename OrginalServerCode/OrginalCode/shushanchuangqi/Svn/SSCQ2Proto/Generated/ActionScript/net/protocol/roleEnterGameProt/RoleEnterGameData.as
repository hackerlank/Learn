/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    RoleEnterGameData.as
//  Purpose:      角色信息相关操作协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEnterGameProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 查询角色消息
	 */
	public final class RoleEnterGameData
	{
		public var byIsUser:uint; //(无符号8位整数)0表示不存在
		public var sBaseInfo:PlayerBaseData; //基础信息

		/**
		 * 辅助创建函数
		 */
		public static function create(byIsUser:uint, sBaseInfo:PlayerBaseData):RoleEnterGameData
		{
			var s_:RoleEnterGameData = new RoleEnterGameData();
			s_.byIsUser = byIsUser;
			s_.sBaseInfo = sBaseInfo;
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
				topXml = <RoleEnterGameData _name_={name_} byIsUser={byIsUser}/>;
			else
				topXml = <RoleEnterGameData byIsUser={byIsUser}/>;
			if(sBaseInfo != null)
				topXml.appendChild(sBaseInfo.toXML("sBaseInfo"));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byIsUser = byIsUser;
			obj_.sBaseInfo = sBaseInfo;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):RoleEnterGameData
		{
			var s_:RoleEnterGameData = new RoleEnterGameData();
			var byIsUser:uint = bytes.readUnsignedByte();
			s_.byIsUser = byIsUser;
			var sBaseInfo:PlayerBaseData = PlayerBaseData.fromByteArray(bytes);
			s_.sBaseInfo = sBaseInfo;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<RoleEnterGameData>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<RoleEnterGameData> = new Vector.<RoleEnterGameData>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:RoleEnterGameData = RoleEnterGameData.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byIsUser);
			sBaseInfo.toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<RoleEnterGameData>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:RoleEnterGameData in vec)
				s.toByteArray(bytes);
		}
	}
}
