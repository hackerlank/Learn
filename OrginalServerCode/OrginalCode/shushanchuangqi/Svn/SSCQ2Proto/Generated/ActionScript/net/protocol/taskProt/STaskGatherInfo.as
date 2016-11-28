/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STaskGatherInfo.as
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 采集的信息
	 */
	public final class STaskGatherInfo extends STaskInfo
	{
		public var wGatherID:uint; //(无符号16位整数)采集的ID
		public var wCount:uint; //(无符号16位整数)已采集的次数

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_STaskInfo.eType_STaskGatherInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <STaskGatherInfo _name_={name_} wGatherID={wGatherID} wCount={wCount}/>;
			else
				topXml = <STaskGatherInfo wGatherID={wGatherID} wCount={wCount}/>;
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.wGatherID = wGatherID;
			obj_.wCount = wCount;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STaskGatherInfo
		{
			var s_:STaskGatherInfo = new STaskGatherInfo();
			var base_:STaskInfo = STaskInfo.fromByteArray(bytes);
			var wGatherID:uint = bytes.readUnsignedShort();
			s_.wGatherID = wGatherID;
			var wCount:uint = bytes.readUnsignedShort();
			s_.wCount = wCount;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STaskGatherInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STaskGatherInfo> = new Vector.<STaskGatherInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STaskGatherInfo = STaskGatherInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeShort(wGatherID);
			bytes.writeShort(wCount);
		}

		public static function vectorToByteArray(vec:Vector.<STaskGatherInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STaskGatherInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
