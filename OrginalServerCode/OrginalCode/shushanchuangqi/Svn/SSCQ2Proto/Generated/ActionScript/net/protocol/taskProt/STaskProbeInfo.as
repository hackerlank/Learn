/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STaskProbeInfo.as
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 探索区域信息
	 */
	public final class STaskProbeInfo extends STaskInfo
	{
		public var byIndex:uint; //(无符号8位整数)探索区域索引
		public var bProbed:Boolean; //是否已探索

		/**
		 * 获取继承类的类型
		 */
		public override function getClassType():uint
		{
			return EType_STaskInfo.eType_STaskProbeInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public override function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <STaskProbeInfo _name_={name_} byIndex={byIndex} bProbed={bProbed}/>;
			else
				topXml = <STaskProbeInfo byIndex={byIndex} bProbed={bProbed}/>;
			topXml.appendChild(super.toXML(name_));
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.byIndex = byIndex;
			obj_.bProbed = bProbed;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STaskProbeInfo
		{
			var s_:STaskProbeInfo = new STaskProbeInfo();
			var base_:STaskInfo = STaskInfo.fromByteArray(bytes);
			var byIndex:uint = bytes.readUnsignedByte();
			s_.byIndex = byIndex;
			var bProbed:Boolean = bytes.readBoolean();
			s_.bProbed = bProbed;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STaskProbeInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STaskProbeInfo> = new Vector.<STaskProbeInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STaskProbeInfo = STaskProbeInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public override function toByteArray(bytes:ByteArray):void
		{
			super.toByteArray(bytes);
			bytes.writeByte(byIndex);
			bytes.writeBoolean(bProbed);
		}

		public static function vectorToByteArray(vec:Vector.<STaskProbeInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STaskProbeInfo in vec)
				s.toByteArray(bytes);
		}
	}
}
