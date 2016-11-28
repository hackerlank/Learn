/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPuppetInfo.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 傀儡信息
	 */
	public final class SPuppetInfo
	{
		public var byIndex:uint; //(无符号8位整数)所属站位(0,1,2; 0为系统战争傀儡)
		public var qwOwnerID:BigInteger; //(无符号64位整数)拥有者ID
		public var dwNextAttackTime:uint; //(无符号32位整数)下一次攻击时间

		/**
		 * 辅助创建函数
		 */
		public static function create(byIndex:uint, qwOwnerID:BigInteger, dwNextAttackTime:uint):SPuppetInfo
		{
			var s_:SPuppetInfo = new SPuppetInfo();
			s_.byIndex = byIndex;
			s_.qwOwnerID = qwOwnerID;
			s_.dwNextAttackTime = dwNextAttackTime;
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
				topXml = <SPuppetInfo _name_={name_} byIndex={byIndex} qwOwnerID={qwOwnerID} dwNextAttackTime={dwNextAttackTime}/>;
			else
				topXml = <SPuppetInfo byIndex={byIndex} qwOwnerID={qwOwnerID} dwNextAttackTime={dwNextAttackTime}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byIndex = byIndex;
			obj_.qwOwnerID = qwOwnerID;
			obj_.dwNextAttackTime = dwNextAttackTime;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPuppetInfo
		{
			var s_:SPuppetInfo = new SPuppetInfo();
			var byIndex:uint = bytes.readUnsignedByte();
			s_.byIndex = byIndex;
			var qwOwnerID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwOwnerID = qwOwnerID;
			var dwNextAttackTime:uint = bytes.readUnsignedInt();
			s_.dwNextAttackTime = dwNextAttackTime;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPuppetInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPuppetInfo> = new Vector.<SPuppetInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPuppetInfo = SPuppetInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byIndex);
			BytesUtil.writeUInt64(bytes, qwOwnerID);
			bytes.writeUnsignedInt(dwNextAttackTime);
		}

		public static function vectorToByteArray(vec:Vector.<SPuppetInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPuppetInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
