/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPrepaid.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * DB存储玩家未创角预先充值仙石的结构体
	 */
	public final class SPrepaid
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)用户ID
		public var dwGold:uint; //(无符号32位整数)预先充值的仙石总数量

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, dwGold:uint):SPrepaid
		{
			var s_:SPrepaid = new SPrepaid();
			s_.qwRoleID = qwRoleID;
			s_.dwGold = dwGold;
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
				topXml = <SPrepaid _name_={name_} qwRoleID={qwRoleID} dwGold={dwGold}/>;
			else
				topXml = <SPrepaid qwRoleID={qwRoleID} dwGold={dwGold}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.dwGold = dwGold;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPrepaid
		{
			var s_:SPrepaid = new SPrepaid();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var dwGold:uint = bytes.readUnsignedInt();
			s_.dwGold = dwGold;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPrepaid>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPrepaid> = new Vector.<SPrepaid>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPrepaid = SPrepaid.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeUnsignedInt(dwGold);
		}

		public static function vectorToByteArray(vec:Vector.<SPrepaid>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPrepaid in vec)
				s.toByteArray(bytes);
		}
	}
}
