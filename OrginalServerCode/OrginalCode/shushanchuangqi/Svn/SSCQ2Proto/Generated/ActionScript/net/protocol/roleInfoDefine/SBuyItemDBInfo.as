/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SBuyItemDBInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 物品购买数量db信息
	 */
	public final class SBuyItemDBInfo
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家ID
		public var dwInstID:uint; //(无符号32位整数)实例ID
		public var dwCount:uint; //(无符号32位整数)物品数量

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, dwInstID:uint, dwCount:uint):SBuyItemDBInfo
		{
			var s_:SBuyItemDBInfo = new SBuyItemDBInfo();
			s_.qwRoleID = qwRoleID;
			s_.dwInstID = dwInstID;
			s_.dwCount = dwCount;
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
				topXml = <SBuyItemDBInfo _name_={name_} qwRoleID={qwRoleID} dwInstID={dwInstID} dwCount={dwCount}/>;
			else
				topXml = <SBuyItemDBInfo qwRoleID={qwRoleID} dwInstID={dwInstID} dwCount={dwCount}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.dwInstID = dwInstID;
			obj_.dwCount = dwCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SBuyItemDBInfo
		{
			var s_:SBuyItemDBInfo = new SBuyItemDBInfo();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var dwInstID:uint = bytes.readUnsignedInt();
			s_.dwInstID = dwInstID;
			var dwCount:uint = bytes.readUnsignedInt();
			s_.dwCount = dwCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SBuyItemDBInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SBuyItemDBInfo> = new Vector.<SBuyItemDBInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SBuyItemDBInfo = SBuyItemDBInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeUnsignedInt(dwInstID);
			bytes.writeUnsignedInt(dwCount);
		}

		public static function vectorToByteArray(vec:Vector.<SBuyItemDBInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SBuyItemDBInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
