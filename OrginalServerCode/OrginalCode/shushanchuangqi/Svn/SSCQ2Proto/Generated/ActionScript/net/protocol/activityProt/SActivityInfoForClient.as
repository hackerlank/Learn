/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SActivityInfoForClient.as
//  Purpose:      活力任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.activityProt
{
	import net.protocol.roleInfoDefine.SActivityTaskInfo;
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 活力任务信息
	 */
	public final class SActivityInfoForClient
	{
		public var dwTotolActivity:uint; //(无符号32位整数)累计活力值
		public var wActivity:uint; //(无符号16位整数)当前活力
		public var vecActivityTask:Vector.<SActivityTaskInfo>; //活力监测点
		public var vecActivityAward:Vector.<SActivityAward>; //已领活力

		/**
		 * 辅助创建函数
		 */
		public static function create(dwTotolActivity:uint, wActivity:uint, vecActivityTask:Vector.<SActivityTaskInfo>, vecActivityAward:Vector.<SActivityAward>):SActivityInfoForClient
		{
			var s_:SActivityInfoForClient = new SActivityInfoForClient();
			s_.dwTotolActivity = dwTotolActivity;
			s_.wActivity = wActivity;
			s_.vecActivityTask = vecActivityTask;
			s_.vecActivityAward = vecActivityAward;
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
				topXml = <SActivityInfoForClient _name_={name_} dwTotolActivity={dwTotolActivity} wActivity={wActivity}/>;
			else
				topXml = <SActivityInfoForClient dwTotolActivity={dwTotolActivity} wActivity={wActivity}/>;
			if(vecActivityTask != null)
			{
				var vecActivityTaskXml:XML = <Vec_SActivityTaskInfo _name_="vecActivityTask"/>;
				for each(var s1:SActivityTaskInfo in vecActivityTask)
					vecActivityTaskXml.appendChild(s1.toXML());
				topXml.appendChild(vecActivityTaskXml);
			}
			if(vecActivityAward != null)
			{
				var vecActivityAwardXml:XML = <Vec_SActivityAward _name_="vecActivityAward"/>;
				for each(var s2:SActivityAward in vecActivityAward)
					vecActivityAwardXml.appendChild(s2.toXML());
				topXml.appendChild(vecActivityAwardXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.dwTotolActivity = dwTotolActivity;
			obj_.wActivity = wActivity;
			obj_.vecActivityTask = vecActivityTask;
			obj_.vecActivityAward = vecActivityAward;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SActivityInfoForClient
		{
			var s_:SActivityInfoForClient = new SActivityInfoForClient();
			var dwTotolActivity:uint = bytes.readUnsignedInt();
			s_.dwTotolActivity = dwTotolActivity;
			var wActivity:uint = bytes.readUnsignedShort();
			s_.wActivity = wActivity;
			var vecActivityTask:Vector.<SActivityTaskInfo> = SActivityTaskInfo.vectorFromByteArray(bytes);
			s_.vecActivityTask = vecActivityTask;
			var vecActivityAward:Vector.<SActivityAward> = SActivityAward.vectorFromByteArray(bytes);
			s_.vecActivityAward = vecActivityAward;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SActivityInfoForClient>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SActivityInfoForClient> = new Vector.<SActivityInfoForClient>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SActivityInfoForClient = SActivityInfoForClient.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeUnsignedInt(dwTotolActivity);
			bytes.writeShort(wActivity);
			SActivityTaskInfo.vectorToByteArray(vecActivityTask, bytes);
			SActivityAward.vectorToByteArray(vecActivityAward, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SActivityInfoForClient>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SActivityInfoForClient in vec)
				s.toByteArray(bytes);
		}
	}
}
