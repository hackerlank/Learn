/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetain.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家在活动中的保留值
	 */
	public final class SRetain
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var strName:String; //玩家名字
		public var byCareer:uint; //(无符号8位整数)玩家职业
		public var bySex:uint; //(无符号8位整数)性别
		public var wActID:uint; //(无符号16位整数)活动ID
		public var wID:uint; //(无符号16位整数)保留值（散仙ID,帮派ID,阵灵ID.....)
		public var strGuildName:String; //帮派名字
		public var wType:uint; //(无符号16位整数)保留类型
		public var dwValue:uint; //(无符号32位整数)保留值
		public var dwTime:uint; //(无符号32位整数)时间

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, strName:String, byCareer:uint, bySex:uint, wActID:uint, 
			wID:uint, strGuildName:String, wType:uint, dwValue:uint, dwTime:uint):SRetain
		{
			var s_:SRetain = new SRetain();
			s_.qwRoleID = qwRoleID;
			s_.strName = strName;
			s_.byCareer = byCareer;
			s_.bySex = bySex;
			s_.wActID = wActID;
			s_.wID = wID;
			s_.strGuildName = strGuildName;
			s_.wType = wType;
			s_.dwValue = dwValue;
			s_.dwTime = dwTime;
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
				topXml = <SRetain _name_={name_} qwRoleID={qwRoleID} strName={strName} byCareer={byCareer} bySex={bySex} wActID={wActID}
				 wID={wID} strGuildName={strGuildName} wType={wType} dwValue={dwValue} dwTime={dwTime}/>;
			else
				topXml = <SRetain qwRoleID={qwRoleID} strName={strName} byCareer={byCareer} bySex={bySex} wActID={wActID}
				 wID={wID} strGuildName={strGuildName} wType={wType} dwValue={dwValue} dwTime={dwTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.strName = strName;
			obj_.byCareer = byCareer;
			obj_.bySex = bySex;
			obj_.wActID = wActID;
			obj_.wID = wID;
			obj_.strGuildName = strGuildName;
			obj_.wType = wType;
			obj_.dwValue = dwValue;
			obj_.dwTime = dwTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SRetain
		{
			var s_:SRetain = new SRetain();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var byCareer:uint = bytes.readUnsignedByte();
			s_.byCareer = byCareer;
			var bySex:uint = bytes.readUnsignedByte();
			s_.bySex = bySex;
			var wActID:uint = bytes.readUnsignedShort();
			s_.wActID = wActID;
			var wID:uint = bytes.readUnsignedShort();
			s_.wID = wID;
			var strGuildName:String = BytesUtil.readString(bytes);
			s_.strGuildName = strGuildName;
			var wType:uint = bytes.readUnsignedShort();
			s_.wType = wType;
			var dwValue:uint = bytes.readUnsignedInt();
			s_.dwValue = dwValue;
			var dwTime:uint = bytes.readUnsignedInt();
			s_.dwTime = dwTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SRetain>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SRetain> = new Vector.<SRetain>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SRetain = SRetain.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeByte(byCareer);
			bytes.writeByte(bySex);
			bytes.writeShort(wActID);
			bytes.writeShort(wID);
			BytesUtil.writeString(bytes, strGuildName);
			bytes.writeShort(wType);
			bytes.writeUnsignedInt(dwValue);
			bytes.writeUnsignedInt(dwTime);
		}

		public static function vectorToByteArray(vec:Vector.<SRetain>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SRetain in vec)
				s.toByteArray(bytes);
		}
	}
}
