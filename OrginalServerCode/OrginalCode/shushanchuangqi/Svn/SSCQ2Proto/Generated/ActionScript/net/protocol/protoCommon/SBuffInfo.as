/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBuffInfo.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * Buff详细信息
	 */
	public final class SBuffInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)对应玩家ID
		public var qwOwnerID:BigInteger; //(无符号64位整数)所属实例ID(Role/Fighter/...
		public var wBuffID:uint; //(无符号16位整数)Buff种类
		public var eBuffState:uint; //(枚举类型：EBuffState)Buff当前状态
		public var vecBuffData:Vector.<uint>; //(无符号32位整数)Buff数值
		public var dwBuffCount:uint; //(无符号32位整数)Buff叠加层数
		public var dwBuffTime:uint; //(无符号32位整数)Buff失效时间

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, qwOwnerID:BigInteger, wBuffID:uint, eBuffState:uint, vecBuffData:Vector.<uint>, 
			dwBuffCount:uint, dwBuffTime:uint):SBuffInfo
		{
			var s_:SBuffInfo = new SBuffInfo();
			s_.qwRoleID = qwRoleID;
			s_.qwOwnerID = qwOwnerID;
			s_.wBuffID = wBuffID;
			s_.eBuffState = eBuffState;
			s_.vecBuffData = vecBuffData;
			s_.dwBuffCount = dwBuffCount;
			s_.dwBuffTime = dwBuffTime;
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
				topXml = <SBuffInfo _name_={name_} qwRoleID={qwRoleID} qwOwnerID={qwOwnerID} wBuffID={wBuffID} eBuffState={eBuffState}
				 dwBuffCount={dwBuffCount} dwBuffTime={dwBuffTime}/>;
			else
				topXml = <SBuffInfo qwRoleID={qwRoleID} qwOwnerID={qwOwnerID} wBuffID={wBuffID} eBuffState={eBuffState}
				 dwBuffCount={dwBuffCount} dwBuffTime={dwBuffTime}/>;
			if(vecBuffData != null)
			{
				var vecBuffDataXml:XML = <Vec_UINT32 _name_="vecBuffData"/>;
				var text1:String = "";
				for each(var value1:uint in vecBuffData)
					text1 += "[" + value1 + "]";
				vecBuffDataXml.appendChild(text1);
				topXml.appendChild(vecBuffDataXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.qwOwnerID = qwOwnerID;
			obj_.wBuffID = wBuffID;
			obj_.eBuffState = eBuffState;
			obj_.vecBuffData = vecBuffData;
			obj_.dwBuffCount = dwBuffCount;
			obj_.dwBuffTime = dwBuffTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBuffInfo
		{
			var s_:SBuffInfo = new SBuffInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var qwOwnerID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOwnerID = qwOwnerID;
			var wBuffID:uint = bytes.readUnsignedShort();
			s_.wBuffID = wBuffID;
			var eBuffState:uint = bytes.readUnsignedByte();
			s_.eBuffState = eBuffState;
			var vecBuffData:Vector.<uint> = BytesUtil.readVecUInt(bytes);
			s_.vecBuffData = vecBuffData;
			var dwBuffCount:uint = bytes.readUnsignedInt();
			s_.dwBuffCount = dwBuffCount;
			var dwBuffTime:uint = bytes.readUnsignedInt();
			s_.dwBuffTime = dwBuffTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBuffInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBuffInfo> = new Vector.<SBuffInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBuffInfo = SBuffInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeUInt64(bytes, qwOwnerID);
			bytes.writeShort(wBuffID);
			bytes.writeByte(eBuffState);
			BytesUtil.writeVecUInt(bytes, vecBuffData);
			bytes.writeUnsignedInt(dwBuffCount);
			bytes.writeUnsignedInt(dwBuffTime);
		}

		public static function vectorToByteArray(vec:Vector.<SBuffInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBuffInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
