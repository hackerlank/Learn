/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SEventOffLine.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 离线事件
	 */
	public final class SEventOffLine
	{
		public var byServerType:uint; //(无符号8位整数)服务器类型
		public var dwEventType:uint; //(无符号32位整数)事件类型
		public var dwTime:uint; //(无符号32位整数)发生时间
		public var strParam1:String; //TVecUINT32
		public var strParam2:String; //字符参数

		/**
		 * 辅助创建函数
		 */
		public static function create(byServerType:uint, dwEventType:uint, dwTime:uint, strParam1:String, strParam2:String):SEventOffLine
		{
			var s_:SEventOffLine = new SEventOffLine();
			s_.byServerType = byServerType;
			s_.dwEventType = dwEventType;
			s_.dwTime = dwTime;
			s_.strParam1 = strParam1;
			s_.strParam2 = strParam2;
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
				topXml = <SEventOffLine _name_={name_} byServerType={byServerType} dwEventType={dwEventType} dwTime={dwTime} strParam1={strParam1} strParam2={strParam2}/>;
			else
				topXml = <SEventOffLine byServerType={byServerType} dwEventType={dwEventType} dwTime={dwTime} strParam1={strParam1} strParam2={strParam2}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byServerType = byServerType;
			obj_.dwEventType = dwEventType;
			obj_.dwTime = dwTime;
			obj_.strParam1 = strParam1;
			obj_.strParam2 = strParam2;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SEventOffLine
		{
			var s_:SEventOffLine = new SEventOffLine();
			var byServerType:uint = bytes.readUnsignedByte();
			s_.byServerType = byServerType;
			var dwEventType:uint = bytes.readUnsignedInt();
			s_.dwEventType = dwEventType;
			var dwTime:uint = bytes.readUnsignedInt();
			s_.dwTime = dwTime;
			var strParam1:String = BytesUtil.readString(bytes);
			s_.strParam1 = strParam1;
			var strParam2:String = BytesUtil.readString(bytes);
			s_.strParam2 = strParam2;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SEventOffLine>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SEventOffLine> = new Vector.<SEventOffLine>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SEventOffLine = SEventOffLine.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(byServerType);
			bytes.writeUnsignedInt(dwEventType);
			bytes.writeUnsignedInt(dwTime);
			BytesUtil.writeString(bytes, strParam1);
			BytesUtil.writeString(bytes, strParam2);
		}

		public static function vectorToByteArray(vec:Vector.<SEventOffLine>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SEventOffLine in vec)
				s.toByteArray(bytes);
		}
	}
}
