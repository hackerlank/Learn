/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SCaveAttackGuildInfo.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 洞府战攻击帮派信息
	 */
	public final class SCaveAttackGuildInfo
	{
		public var qwGuildID:BigInteger; //(无符号64位整数)帮派ID
		public var strName:String; //帮派姓名
		public var dwMaxEnergy:uint; //(无符号32位整数)能量上限
		public var dwEnergy:uint; //(无符号32位整数)当前能量

		/**
		 * 辅助创建函数
		 */
		public static function create(qwGuildID:BigInteger, strName:String, dwMaxEnergy:uint, dwEnergy:uint):SCaveAttackGuildInfo
		{
			var s_:SCaveAttackGuildInfo = new SCaveAttackGuildInfo();
			s_.qwGuildID = qwGuildID;
			s_.strName = strName;
			s_.dwMaxEnergy = dwMaxEnergy;
			s_.dwEnergy = dwEnergy;
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
				topXml = <SCaveAttackGuildInfo _name_={name_} qwGuildID={qwGuildID} strName={strName} dwMaxEnergy={dwMaxEnergy} dwEnergy={dwEnergy}/>;
			else
				topXml = <SCaveAttackGuildInfo qwGuildID={qwGuildID} strName={strName} dwMaxEnergy={dwMaxEnergy} dwEnergy={dwEnergy}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwGuildID = qwGuildID;
			obj_.strName = strName;
			obj_.dwMaxEnergy = dwMaxEnergy;
			obj_.dwEnergy = dwEnergy;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SCaveAttackGuildInfo
		{
			var s_:SCaveAttackGuildInfo = new SCaveAttackGuildInfo();
			var qwGuildID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwGuildID = qwGuildID;
			var strName:String = BytesUtil.readString(bytes);
			s_.strName = strName;
			var dwMaxEnergy:uint = bytes.readUnsignedInt();
			s_.dwMaxEnergy = dwMaxEnergy;
			var dwEnergy:uint = bytes.readUnsignedInt();
			s_.dwEnergy = dwEnergy;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SCaveAttackGuildInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SCaveAttackGuildInfo> = new Vector.<SCaveAttackGuildInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SCaveAttackGuildInfo = SCaveAttackGuildInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwGuildID);
			BytesUtil.writeString(bytes, strName);
			bytes.writeUnsignedInt(dwMaxEnergy);
			bytes.writeUnsignedInt(dwEnergy);
		}

		public static function vectorToByteArray(vec:Vector.<SCaveAttackGuildInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SCaveAttackGuildInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
