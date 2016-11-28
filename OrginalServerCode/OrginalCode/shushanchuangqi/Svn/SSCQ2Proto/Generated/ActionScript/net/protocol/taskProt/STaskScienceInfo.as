/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STaskScienceInfo.as
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 科技的信息
	 */
	public final class STaskScienceInfo extends STaskInfo
	{
		public var wScienceID:uint; //(无符号16位整数)科技ID
		public var wLevel:uint; //(无符号16位整数)等级

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_STaskInfo.eType_STaskScienceInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <STaskScienceInfo _name_={name_} wScienceID={wScienceID} wLevel={wLevel}/>;
			else
				topXml = <STaskScienceInfo wScienceID={wScienceID} wLevel={wLevel}/>;
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wScienceID = wScienceID;
			obj_.wLevel = wLevel;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STaskScienceInfo
		{
			var s_:STaskScienceInfo = new STaskScienceInfo();
			var base_:STaskInfo = STaskInfo.fromByteArray(bytes);
			var wScienceID:uint = bytes.readUnsignedShort();
			s_.wScienceID = wScienceID;
			var wLevel:uint = bytes.readUnsignedShort();
			s_.wLevel = wLevel;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STaskScienceInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STaskScienceInfo> = new Vector.<STaskScienceInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STaskScienceInfo = STaskScienceInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wScienceID);
			bytes.writeShort(wLevel);
		}

		public static function vectorToByteArray(vec:Vector.<STaskScienceInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STaskScienceInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
