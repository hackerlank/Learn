/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STaskTalkInfo.as
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * NPC的对话信息
	 */
	public final class STaskTalkInfo extends STaskInfo
	{
		public var wNpcID:uint; //(无符号16位整数)NPC的ID
		public var wTalkCount:uint; //(无符号16位整数)0:未完成1:已完成

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_STaskInfo.eType_STaskTalkInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <STaskTalkInfo _name_={name_} wNpcID={wNpcID} wTalkCount={wTalkCount}/>;
			else
				topXml = <STaskTalkInfo wNpcID={wNpcID} wTalkCount={wTalkCount}/>;
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wNpcID = wNpcID;
			obj_.wTalkCount = wTalkCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STaskTalkInfo
		{
			var s_:STaskTalkInfo = new STaskTalkInfo();
			var base_:STaskInfo = STaskInfo.fromByteArray(bytes);
			var wNpcID:uint = bytes.readUnsignedShort();
			s_.wNpcID = wNpcID;
			var wTalkCount:uint = bytes.readUnsignedShort();
			s_.wTalkCount = wTalkCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STaskTalkInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STaskTalkInfo> = new Vector.<STaskTalkInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STaskTalkInfo = STaskTalkInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wNpcID);
			bytes.writeShort(wTalkCount);
		}

		public static function vectorToByteArray(vec:Vector.<STaskTalkInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STaskTalkInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
