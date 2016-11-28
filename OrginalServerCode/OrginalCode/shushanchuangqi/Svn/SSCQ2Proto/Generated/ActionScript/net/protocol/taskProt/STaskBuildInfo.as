/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STaskBuildInfo.as
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 建筑的信息
	 */
	public final class STaskBuildInfo extends STaskInfo
	{
		public var wBuildID:uint; //(无符号16位整数)建筑ID
		public var wLevel:uint; //(无符号16位整数)等级

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_STaskInfo.eType_STaskBuildInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <STaskBuildInfo _name_={name_} wBuildID={wBuildID} wLevel={wLevel}/>;
			else
				topXml = <STaskBuildInfo wBuildID={wBuildID} wLevel={wLevel}/>;
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wBuildID = wBuildID;
			obj_.wLevel = wLevel;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STaskBuildInfo
		{
			var s_:STaskBuildInfo = new STaskBuildInfo();
			var base_:STaskInfo = STaskInfo.fromByteArray(bytes);
			var wBuildID:uint = bytes.readUnsignedShort();
			s_.wBuildID = wBuildID;
			var wLevel:uint = bytes.readUnsignedShort();
			s_.wLevel = wLevel;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STaskBuildInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STaskBuildInfo> = new Vector.<STaskBuildInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STaskBuildInfo = STaskBuildInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wBuildID);
			bytes.writeShort(wLevel);
		}

		public static function vectorToByteArray(vec:Vector.<STaskBuildInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STaskBuildInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
