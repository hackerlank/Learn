/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STaskActionInfo.as
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 行为的信息
	 */
	public final class STaskActionInfo extends STaskInfo
	{
		public var wAction:uint; //(无符号16位整数)行为类型
		public var wCount:uint; //(无符号16位整数)次数

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_STaskInfo.eType_STaskActionInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <STaskActionInfo _name_={name_} wAction={wAction} wCount={wCount}/>;
			else
				topXml = <STaskActionInfo wAction={wAction} wCount={wCount}/>;
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wAction = wAction;
			obj_.wCount = wCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STaskActionInfo
		{
			var s_:STaskActionInfo = new STaskActionInfo();
			var base_:STaskInfo = STaskInfo.fromByteArray(bytes);
			var wAction:uint = bytes.readUnsignedShort();
			s_.wAction = wAction;
			var wCount:uint = bytes.readUnsignedShort();
			s_.wCount = wCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STaskActionInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STaskActionInfo> = new Vector.<STaskActionInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STaskActionInfo = STaskActionInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wAction);
			bytes.writeShort(wCount);
		}

		public static function vectorToByteArray(vec:Vector.<STaskActionInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STaskActionInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
