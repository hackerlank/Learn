/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STaskGrowInfo.as
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 成长的信息
	 */
	public final class STaskGrowInfo extends STaskInfo
	{
		public var wType:uint; //(无符号16位整数)成长类型
		public var wLevel:uint; //(无符号16位整数)等级

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_STaskInfo.eType_STaskGrowInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <STaskGrowInfo _name_={name_} wType={wType} wLevel={wLevel}/>;
			else
				topXml = <STaskGrowInfo wType={wType} wLevel={wLevel}/>;
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wType = wType;
			obj_.wLevel = wLevel;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STaskGrowInfo
		{
			var s_:STaskGrowInfo = new STaskGrowInfo();
			var base_:STaskInfo = STaskInfo.fromByteArray(bytes);
			var wType:uint = bytes.readUnsignedShort();
			s_.wType = wType;
			var wLevel:uint = bytes.readUnsignedShort();
			s_.wLevel = wLevel;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STaskGrowInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STaskGrowInfo> = new Vector.<STaskGrowInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STaskGrowInfo = STaskGrowInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wType);
			bytes.writeShort(wLevel);
		}

		public static function vectorToByteArray(vec:Vector.<STaskGrowInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STaskGrowInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
