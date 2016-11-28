/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    STaskInfo.as
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 任务信息
	 */
	public class STaskInfo
	{
		/**
		 * 获取继承类的类型
		 */
		public function getClassType():uint
		{
			return EType_STaskInfo.eType_STaskInfo;
		}

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <STaskInfo _name_={name_}/>;
			else
				topXml = <STaskInfo/>;
			return topXml;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):STaskInfo
		{
			var s_:STaskInfo = new STaskInfo();
			return s_;
		}

		public static function superFromByteArray(bytes:ByteArray):STaskInfo
		{
			var eType:uint = bytes.readUnsignedByte();
			var s:STaskInfo;
			switch(eType)
			{
				case EType_STaskInfo.eType_STaskInfo:
					s = STaskInfo.fromByteArray(bytes);
					break;
				case EType_STaskInfo.eType_STaskCollectInfo:
					s = STaskCollectInfo.fromByteArray(bytes);
					break;
				case EType_STaskInfo.eType_STaskGatherInfo:
					s = STaskGatherInfo.fromByteArray(bytes);
					break;
				case EType_STaskInfo.eType_STaskMonsterInfo:
					s = STaskMonsterInfo.fromByteArray(bytes);
					break;
				case EType_STaskInfo.eType_STaskTalkInfo:
					s = STaskTalkInfo.fromByteArray(bytes);
					break;
				case EType_STaskInfo.eType_STaskProbeInfo:
					s = STaskProbeInfo.fromByteArray(bytes);
					break;
				case EType_STaskInfo.eType_STaskBuildInfo:
					s = STaskBuildInfo.fromByteArray(bytes);
					break;
				case EType_STaskInfo.eType_STaskScienceInfo:
					s = STaskScienceInfo.fromByteArray(bytes);
					break;
				case EType_STaskInfo.eType_STaskActionInfo:
					s = STaskActionInfo.fromByteArray(bytes);
					break;
				case EType_STaskInfo.eType_STaskGrowInfo:
					s = STaskGrowInfo.fromByteArray(bytes);
					break;
				default:
					throw new Error("Unknown value for EType_STaskInfo:" + eType);
			}
			return s;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<STaskInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STaskInfo> = new Vector.<STaskInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STaskInfo = STaskInfo.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public static function superVectorFromByteArray(bytes:ByteArray):Vector.<STaskInfo>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<STaskInfo> = new Vector.<STaskInfo>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:STaskInfo = STaskInfo.superFromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
		}

		public function superToByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(getClassType());
			toByteArray(bytes);
		}

		public static function vectorToByteArray(vec:Vector.<STaskInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STaskInfo in vec)
				s.toByteArray(bytes);
		}

		public static function superVectorToByteArray(vec:Vector.<STaskInfo>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:STaskInfo in vec)
				s.superToByteArray(bytes);
		}
	}
}
