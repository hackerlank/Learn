/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SActivityTaskInfo.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 活跃任务
	 */
	public final class SActivityTaskInfo
	{
		public var wId:uint; //(无符号16位整数)活跃触发点ID
		public var byTimes:uint; //(无符号8位整数)完成次数
		public var byIsSpecial:uint; //(无符号8位整数)是否特别任务

		/**
		 * 辅助创建函数
		 */
		public static function create(wId:uint, byTimes:uint, byIsSpecial:uint):SActivityTaskInfo
		{
			var s_:SActivityTaskInfo = new SActivityTaskInfo();
			s_.wId = wId;
			s_.byTimes = byTimes;
			s_.byIsSpecial = byIsSpecial;
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
				topXml = <SActivityTaskInfo _name_={name_} wId={wId} byTimes={byTimes} byIsSpecial={byIsSpecial}/>;
			else
				topXml = <SActivityTaskInfo wId={wId} byTimes={byTimes} byIsSpecial={byIsSpecial}/>;
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wId = wId;
			obj_.byTimes = byTimes;
			obj_.byIsSpecial = byIsSpecial;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SActivityTaskInfo
		{
			var s_:SActivityTaskInfo = new SActivityTaskInfo();
			var wId:uint = bytes.readUnsignedShort();
			s_.wId = wId;
			var byTimes:uint = bytes.readUnsignedByte();
			s_.byTimes = byTimes;
			var byIsSpecial:uint = bytes.readUnsignedByte();
			s_.byIsSpecial = byIsSpecial;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SActivityTaskInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SActivityTaskInfo> = new Vector.<SActivityTaskInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SActivityTaskInfo = SActivityTaskInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeShort(wId);
			bytes.writeByte(byTimes);
			bytes.writeByte(byIsSpecial);
		}

		public static function vectorToByteArray(vec:Vector.<SActivityTaskInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SActivityTaskInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
