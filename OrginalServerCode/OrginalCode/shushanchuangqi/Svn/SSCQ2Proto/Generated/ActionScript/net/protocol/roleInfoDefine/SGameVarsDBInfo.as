/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGameVarsDBInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 系统变量数据
	 */
	public final class SGameVarsDBInfo
	{
		public var byServerType:uint; //(无符号8位整数)服务器类型
		public var wVar:uint; //(无符号16位整数)变量ID
		public var qwValue:BigInteger; //(无符号64位整数)变量值
		public var dwExpired:uint; //(无符号32位整数)过期时间

		/**
		 * 辅助创建函数
		 */
		public static function create(byServerType:uint, wVar:uint, qwValue:BigInteger, dwExpired:uint):SGameVarsDBInfo
		{
			var s_:SGameVarsDBInfo = new SGameVarsDBInfo();
			s_.byServerType = byServerType;
			s_.wVar = wVar;
			s_.qwValue = qwValue;
			s_.dwExpired = dwExpired;
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
				topXml = <SGameVarsDBInfo _name_={name_} byServerType={byServerType} wVar={wVar} qwValue={qwValue} dwExpired={dwExpired}/>;
			else
				topXml = <SGameVarsDBInfo byServerType={byServerType} wVar={wVar} qwValue={qwValue} dwExpired={dwExpired}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byServerType = byServerType;
			obj_.wVar = wVar;
			obj_.qwValue = qwValue;
			obj_.dwExpired = dwExpired;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGameVarsDBInfo
		{
			var s_:SGameVarsDBInfo = new SGameVarsDBInfo();
			var byServerType:uint = bytes.readUnsignedByte();
			s_.byServerType = byServerType;
			var wVar:uint = bytes.readUnsignedShort();
			s_.wVar = wVar;
			var qwValue:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwValue = qwValue;
			var dwExpired:uint = bytes.readUnsignedInt();
			s_.dwExpired = dwExpired;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGameVarsDBInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGameVarsDBInfo> = new Vector.<SGameVarsDBInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGameVarsDBInfo = SGameVarsDBInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byServerType);
			bytes.writeShort(wVar);
			BytesUtil.writeUInt64(bytes, qwValue);
			bytes.writeUnsignedInt(dwExpired);
		}

		public static function vectorToByteArray(vec:Vector.<SGameVarsDBInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGameVarsDBInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
