/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SCreateRoleInfo.as
//  Purpose:      角色信息相关操作协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEnterGameProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 角色信息
	 */
	public final class SCreateRoleInfo
	{
		public var strName:String; //角色名
		public var eCareer:uint; //(枚举类型：protoCommon.ECareerType)职业
		public var eSex:uint; //(枚举类型：protoCommon.ESexType)性别
		public var strInviteRoleID:String; //好友邀请id
		public var strIP:String; //创角时ip

		/**
		 * 辅助创建函数
		 */
		public static function create(strName:String, eCareer:uint, eSex:uint, strInviteRoleID:String, strIP:String):SCreateRoleInfo
		{
			var s_:SCreateRoleInfo = new SCreateRoleInfo();
			s_.strName = strName;
			s_.eCareer = eCareer;
			s_.eSex = eSex;
			s_.strInviteRoleID = strInviteRoleID;
			s_.strIP = strIP;
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
				topXml = <SCreateRoleInfo _name_={name_} strName={strName} eCareer={eCareer} eSex={eSex} strInviteRoleID={strInviteRoleID} strIP={strIP}/>;
			else
				topXml = <SCreateRoleInfo strName={strName} eCareer={eCareer} eSex={eSex} strInviteRoleID={strInviteRoleID} strIP={strIP}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.strName = strName;
			obj_.eCareer = eCareer;
			obj_.eSex = eSex;
			obj_.strInviteRoleID = strInviteRoleID;
			obj_.strIP = strIP;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SCreateRoleInfo
		{
			var s_:SCreateRoleInfo = new SCreateRoleInfo();
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var eCareer:uint = bytes.readUnsignedByte();
			s_.eCareer = eCareer;
			var eSex:uint = bytes.readUnsignedByte();
			s_.eSex = eSex;
			var strInviteRoleID:String = BytesUtil.readString(bytes);
			s_.strInviteRoleID = strInviteRoleID;
			var strIP:String = BytesUtil.readString(bytes);
			s_.strIP = strIP;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SCreateRoleInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SCreateRoleInfo> = new Vector.<SCreateRoleInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SCreateRoleInfo = SCreateRoleInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(eCareer);
			bytes.writeByte(eSex);
			BytesUtil.writeString(bytes, strInviteRoleID);
			BytesUtil.writeString(bytes, strIP);
		}

		public static function vectorToByteArray(vec:Vector.<SCreateRoleInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SCreateRoleInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
