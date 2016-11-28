/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STripodStatus.as
//  Purpose:      九疑鼎相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 玩家九疑鼎的扇火、协助状态
	 */
	public final class STripodStatus
	{
		public var qwRoleID:BigInteger; //(无符号64位整数)玩家的ID
		public var byShanfengst:uint; //(无符号8位整数)是否可以扇火(1是 0否)
		public var byHelpst:uint; //(无符号8位整数)是否可以协助(1是 0否)

		/**
		 * 辅助创建函数
		 */
		public static function create(qwRoleID:BigInteger, byShanfengst:uint, byHelpst:uint):STripodStatus
		{
			var s_:STripodStatus = new STripodStatus();
			s_.qwRoleID = qwRoleID;
			s_.byShanfengst = byShanfengst;
			s_.byHelpst = byHelpst;
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
				topXml = <STripodStatus _name_={name_} qwRoleID={qwRoleID} byShanfengst={byShanfengst} byHelpst={byHelpst}/>;
			else
				topXml = <STripodStatus qwRoleID={qwRoleID} byShanfengst={byShanfengst} byHelpst={byHelpst}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.qwRoleID = qwRoleID;
			obj_.byShanfengst = byShanfengst;
			obj_.byHelpst = byHelpst;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STripodStatus
		{
			var s_:STripodStatus = new STripodStatus();
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes);
			s_.qwRoleID = qwRoleID;
			var byShanfengst:uint = bytes.readUnsignedByte();
			s_.byShanfengst = byShanfengst;
			var byHelpst:uint = bytes.readUnsignedByte();
			s_.byHelpst = byHelpst;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STripodStatus>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STripodStatus> = new Vector.<STripodStatus>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STripodStatus = STripodStatus.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			BytesUtil.writeUInt64(bytes, qwRoleID);
			bytes.writeByte(byShanfengst);
			bytes.writeByte(byHelpst);
		}

		public static function vectorToByteArray(vec:Vector.<STripodStatus>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STripodStatus in vec)
				s.toByteArray(bytes);
		}
	}
}
