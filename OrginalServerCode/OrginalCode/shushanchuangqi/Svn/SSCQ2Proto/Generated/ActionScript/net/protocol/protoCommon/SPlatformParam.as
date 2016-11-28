/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPlatformParam.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 平台相关参数
	 */
	public final class SPlatformParam
	{
		public var byPtType:uint; //(枚举类型：EPtType)平台类型
		public var byQQPtType:uint; //(枚举类型：EQQPtType)QQ平台类型
		public var byQQPtLv:uint; //(无符号8位整数)QQ平台类型等级
		public var bySPType:uint; //(无符号8位整数)Bit位定义见EPlatformBitType

		/**
		 * 辅助创建函数
		 */
		public static function create(byPtType:uint, byQQPtType:uint, byQQPtLv:uint, bySPType:uint):SPlatformParam
		{
			var s_:SPlatformParam = new SPlatformParam();
			s_.byPtType = byPtType;
			s_.byQQPtType = byQQPtType;
			s_.byQQPtLv = byQQPtLv;
			s_.bySPType = bySPType;
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
				topXml = <SPlatformParam _name_={name_} byPtType={byPtType} byQQPtType={byQQPtType} byQQPtLv={byQQPtLv} bySPType={bySPType}/>;
			else
				topXml = <SPlatformParam byPtType={byPtType} byQQPtType={byQQPtType} byQQPtLv={byQQPtLv} bySPType={bySPType}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byPtType = byPtType;
			obj_.byQQPtType = byQQPtType;
			obj_.byQQPtLv = byQQPtLv;
			obj_.bySPType = bySPType;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPlatformParam
		{
			var s_:SPlatformParam = new SPlatformParam();
			var byPtType:uint = bytes.readUnsignedByte();
			s_.byPtType = byPtType;
			var byQQPtType:uint = bytes.readUnsignedByte();
			s_.byQQPtType = byQQPtType;
			var byQQPtLv:uint = bytes.readUnsignedByte();
			s_.byQQPtLv = byQQPtLv;
			var bySPType:uint = bytes.readUnsignedByte();
			s_.bySPType = bySPType;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPlatformParam>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPlatformParam> = new Vector.<SPlatformParam>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPlatformParam = SPlatformParam.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byPtType);
			bytes.writeByte(byQQPtType);
			bytes.writeByte(byQQPtLv);
			bytes.writeByte(bySPType);
		}

		public static function vectorToByteArray(vec:Vector.<SPlatformParam>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPlatformParam in vec)
				s.toByteArray(bytes);
		}
	}
}
