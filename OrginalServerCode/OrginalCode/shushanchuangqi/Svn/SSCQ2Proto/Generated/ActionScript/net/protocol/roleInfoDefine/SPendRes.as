/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SPendRes.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 暂存信息
	 */
	public final class SPendRes
	{
		public var byResType:uint; //(无符号8位整数)类型
		public var dwValue:uint; //(无符号32位整数)数据
		public var bySource:uint; //(无符号8位整数)暂存原因0,战斗，1副本
		public var dwParam:uint; //(无符号32位整数)参数

		/**
		 * 辅助创建函数
		 */
		public static function create(byResType:uint, dwValue:uint, bySource:uint, dwParam:uint):SPendRes
		{
			var s_:SPendRes = new SPendRes();
			s_.byResType = byResType;
			s_.dwValue = dwValue;
			s_.bySource = bySource;
			s_.dwParam = dwParam;
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
				topXml = <SPendRes _name_={name_} byResType={byResType} dwValue={dwValue} bySource={bySource} dwParam={dwParam}/>;
			else
				topXml = <SPendRes byResType={byResType} dwValue={dwValue} bySource={bySource} dwParam={dwParam}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byResType = byResType;
			obj_.dwValue = dwValue;
			obj_.bySource = bySource;
			obj_.dwParam = dwParam;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SPendRes
		{
			var s_:SPendRes = new SPendRes();
			var byResType:uint = bytes.readUnsignedByte();
			s_.byResType = byResType;
			var dwValue:uint = bytes.readUnsignedInt();
			s_.dwValue = dwValue;
			var bySource:uint = bytes.readUnsignedByte();
			s_.bySource = bySource;
			var dwParam:uint = bytes.readUnsignedInt();
			s_.dwParam = dwParam;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SPendRes>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SPendRes> = new Vector.<SPendRes>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SPendRes = SPendRes.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byResType);
			bytes.writeUnsignedInt(dwValue);
			bytes.writeByte(bySource);
			bytes.writeUnsignedInt(dwParam);
		}

		public static function vectorToByteArray(vec:Vector.<SPendRes>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SPendRes in vec)
				s.toByteArray(bytes);
		}
	}
}
