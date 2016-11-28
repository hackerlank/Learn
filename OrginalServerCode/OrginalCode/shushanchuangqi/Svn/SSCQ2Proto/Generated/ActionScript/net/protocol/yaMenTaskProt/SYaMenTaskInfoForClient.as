/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SYaMenTaskInfoForClient.as
//  Purpose:      衙门任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yaMenTaskProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 衙门任务信息
	 */
	public final class SYaMenTaskInfoForClient
	{
		public var eStudyState:uint; //(枚举类型：EYaMenStudyState)清修状态
		public var dwYaMenRepute:uint; //(无符号32位整数)声望
		public var dwYaMenLevel:uint; //(无符号8位整数)声望等级
		public var byFinishTask:uint; //(无符号8位整数)今日完成的衙门任务数
		public var byAcceptTaskTimes:uint; //(无符号8位整数)剩余可接任务数
		public var byBuyTimesToday:uint; //(无符号8位整数)今日购买的任务数
		public var byVIPTaskTimes:uint; //(无符号8位整数)购买的可接任务数
		public var byFlushTask:uint; //(无符号8位整数)今日刷新任务列表次数
		public var byStudyAward:uint; //(无符号8位整数)今日领取的清修次数
		public var vecTask:Vector.<SYaMenTask>; //推的任务列表

		/**
		 * 辅助创建函数
		 */
		public static function create(eStudyState:uint, dwYaMenRepute:uint, dwYaMenLevel:uint, byFinishTask:uint, byAcceptTaskTimes:uint, 
			byBuyTimesToday:uint, byVIPTaskTimes:uint, byFlushTask:uint, byStudyAward:uint, vecTask:Vector.<SYaMenTask>):SYaMenTaskInfoForClient
		{
			var s_:SYaMenTaskInfoForClient = new SYaMenTaskInfoForClient();
			s_.eStudyState = eStudyState;
			s_.dwYaMenRepute = dwYaMenRepute;
			s_.dwYaMenLevel = dwYaMenLevel;
			s_.byFinishTask = byFinishTask;
			s_.byAcceptTaskTimes = byAcceptTaskTimes;
			s_.byBuyTimesToday = byBuyTimesToday;
			s_.byVIPTaskTimes = byVIPTaskTimes;
			s_.byFlushTask = byFlushTask;
			s_.byStudyAward = byStudyAward;
			s_.vecTask = vecTask;
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
				topXml = <SYaMenTaskInfoForClient _name_={name_} eStudyState={eStudyState} dwYaMenRepute={dwYaMenRepute} dwYaMenLevel={dwYaMenLevel} byFinishTask={byFinishTask} byAcceptTaskTimes={byAcceptTaskTimes}
				 byBuyTimesToday={byBuyTimesToday} byVIPTaskTimes={byVIPTaskTimes} byFlushTask={byFlushTask} byStudyAward={byStudyAward}/>;
			else
				topXml = <SYaMenTaskInfoForClient eStudyState={eStudyState} dwYaMenRepute={dwYaMenRepute} dwYaMenLevel={dwYaMenLevel} byFinishTask={byFinishTask} byAcceptTaskTimes={byAcceptTaskTimes}
				 byBuyTimesToday={byBuyTimesToday} byVIPTaskTimes={byVIPTaskTimes} byFlushTask={byFlushTask} byStudyAward={byStudyAward}/>;
			if(vecTask != null)
			{
				var vecTaskXml:XML = <Vec_SYaMenTask _name_="vecTask"/>;
				for each(var s1:SYaMenTask in vecTask)
					vecTaskXml.appendChild(s1.toXML());
				topXml.appendChild(vecTaskXml);
			}
			return topXml;
		}

		/**
		 * 拷贝到另一个对象
		 * @param obj_ 另一个对象
		 */
		public function copyTo(obj_:*):void
		{
			obj_.eStudyState = eStudyState;
			obj_.dwYaMenRepute = dwYaMenRepute;
			obj_.dwYaMenLevel = dwYaMenLevel;
			obj_.byFinishTask = byFinishTask;
			obj_.byAcceptTaskTimes = byAcceptTaskTimes;
			obj_.byBuyTimesToday = byBuyTimesToday;
			obj_.byVIPTaskTimes = byVIPTaskTimes;
			obj_.byFlushTask = byFlushTask;
			obj_.byStudyAward = byStudyAward;
			obj_.vecTask = vecTask;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SYaMenTaskInfoForClient
		{
			var s_:SYaMenTaskInfoForClient = new SYaMenTaskInfoForClient();
			var eStudyState:uint = bytes.readUnsignedByte();
			s_.eStudyState = eStudyState;
			var dwYaMenRepute:uint = bytes.readUnsignedInt();
			s_.dwYaMenRepute = dwYaMenRepute;
			var dwYaMenLevel:uint = bytes.readUnsignedByte();
			s_.dwYaMenLevel = dwYaMenLevel;
			var byFinishTask:uint = bytes.readUnsignedByte();
			s_.byFinishTask = byFinishTask;
			var byAcceptTaskTimes:uint = bytes.readUnsignedByte();
			s_.byAcceptTaskTimes = byAcceptTaskTimes;
			var byBuyTimesToday:uint = bytes.readUnsignedByte();
			s_.byBuyTimesToday = byBuyTimesToday;
			var byVIPTaskTimes:uint = bytes.readUnsignedByte();
			s_.byVIPTaskTimes = byVIPTaskTimes;
			var byFlushTask:uint = bytes.readUnsignedByte();
			s_.byFlushTask = byFlushTask;
			var byStudyAward:uint = bytes.readUnsignedByte();
			s_.byStudyAward = byStudyAward;
			var vecTask:Vector.<SYaMenTask> = SYaMenTask.vectorFromByteArray(bytes);
			s_.vecTask = vecTask;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SYaMenTaskInfoForClient>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SYaMenTaskInfoForClient> = new Vector.<SYaMenTaskInfoForClient>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SYaMenTaskInfoForClient = SYaMenTaskInfoForClient.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eStudyState);
			bytes.writeUnsignedInt(dwYaMenRepute);
			bytes.writeByte(dwYaMenLevel);
			bytes.writeByte(byFinishTask);
			bytes.writeByte(byAcceptTaskTimes);
			bytes.writeByte(byBuyTimesToday);
			bytes.writeByte(byVIPTaskTimes);
			bytes.writeByte(byFlushTask);
			bytes.writeByte(byStudyAward);
			SYaMenTask.vectorToByteArray(vecTask, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SYaMenTaskInfoForClient>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SYaMenTaskInfoForClient in vec)
				s.toByteArray(bytes);
		}
	}
}
