/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SGroupTaskInfoForClient.as
//  Purpose:      师门任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.groupTaskProt
{
	import flash.utils.ByteArray;
	import net.util.*;

	/**
	 * 师门任务信息
	 */
	public final class SGroupTaskInfoForClient
	{
		public var eStudyState:uint; //(枚举类型：EGroupStudyState)清修状态
		public var dwGroupRepute:uint; //(无符号32位整数)声望
		public var dwGroupLevel:uint; //(无符号8位整数)声望等级
		public var byFinishTask:uint; //(无符号8位整数)今日完成的师门任务数
		public var byAcceptTaskTimes:uint; //(无符号8位整数)剩余可接任务数
		public var byBuyTimesToday:uint; //(无符号8位整数)今日购买的任务数
		public var byVIPTaskTimes:uint; //(无符号8位整数)购买的可接任务数
		public var byFlushTask:uint; //(无符号8位整数)今日刷新任务列表次数
		public var byStudyAward:uint; //(无符号8位整数)今日领取的清修次数
		public var vecTask:Vector.<SGroupTask>; //推的任务列表

		/**
		 * 辅助创建函数
		 */
		public static function create(eStudyState:uint, dwGroupRepute:uint, dwGroupLevel:uint, byFinishTask:uint, byAcceptTaskTimes:uint, 
			byBuyTimesToday:uint, byVIPTaskTimes:uint, byFlushTask:uint, byStudyAward:uint, vecTask:Vector.<SGroupTask>):SGroupTaskInfoForClient
		{
			var s_:SGroupTaskInfoForClient = new SGroupTaskInfoForClient();
			s_.eStudyState = eStudyState;
			s_.dwGroupRepute = dwGroupRepute;
			s_.dwGroupLevel = dwGroupLevel;
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
				topXml = <SGroupTaskInfoForClient _name_={name_} eStudyState={eStudyState} dwGroupRepute={dwGroupRepute} dwGroupLevel={dwGroupLevel} byFinishTask={byFinishTask} byAcceptTaskTimes={byAcceptTaskTimes}
				 byBuyTimesToday={byBuyTimesToday} byVIPTaskTimes={byVIPTaskTimes} byFlushTask={byFlushTask} byStudyAward={byStudyAward}/>;
			else
				topXml = <SGroupTaskInfoForClient eStudyState={eStudyState} dwGroupRepute={dwGroupRepute} dwGroupLevel={dwGroupLevel} byFinishTask={byFinishTask} byAcceptTaskTimes={byAcceptTaskTimes}
				 byBuyTimesToday={byBuyTimesToday} byVIPTaskTimes={byVIPTaskTimes} byFlushTask={byFlushTask} byStudyAward={byStudyAward}/>;
			if(vecTask != null)
			{
				var vecTaskXml:XML = <Vec_SGroupTask _name_="vecTask"/>;
				for each(var s1:SGroupTask in vecTask)
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
			obj_.dwGroupRepute = dwGroupRepute;
			obj_.dwGroupLevel = dwGroupLevel;
			obj_.byFinishTask = byFinishTask;
			obj_.byAcceptTaskTimes = byAcceptTaskTimes;
			obj_.byBuyTimesToday = byBuyTimesToday;
			obj_.byVIPTaskTimes = byVIPTaskTimes;
			obj_.byFlushTask = byFlushTask;
			obj_.byStudyAward = byStudyAward;
			obj_.vecTask = vecTask;
		}

		/////////////////////以下为序列化函数/////////////////////

		public static function fromByteArray(bytes:ByteArray):SGroupTaskInfoForClient
		{
			var s_:SGroupTaskInfoForClient = new SGroupTaskInfoForClient();
			var eStudyState:uint = bytes.readUnsignedByte();
			s_.eStudyState = eStudyState;
			var dwGroupRepute:uint = bytes.readUnsignedInt();
			s_.dwGroupRepute = dwGroupRepute;
			var dwGroupLevel:uint = bytes.readUnsignedByte();
			s_.dwGroupLevel = dwGroupLevel;
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
			var vecTask:Vector.<SGroupTask> = SGroupTask.vectorFromByteArray(bytes);
			s_.vecTask = vecTask;
			return s_;
		}

		public static function vectorFromByteArray(bytes:ByteArray):Vector.<SGroupTaskInfoForClient>
		{
			var length:uint = BytesUtil.readVectorLength(bytes);
			var vec:Vector.<SGroupTaskInfoForClient> = new Vector.<SGroupTaskInfoForClient>();
			for(var i:uint = 0; i < length; ++i)
			{
				var s:SGroupTaskInfoForClient = SGroupTaskInfoForClient.fromByteArray(bytes);
				vec.push(s);
			}
			return vec;
		}

		public function toByteArray(bytes:ByteArray):void
		{
			bytes.writeByte(eStudyState);
			bytes.writeUnsignedInt(dwGroupRepute);
			bytes.writeByte(dwGroupLevel);
			bytes.writeByte(byFinishTask);
			bytes.writeByte(byAcceptTaskTimes);
			bytes.writeByte(byBuyTimesToday);
			bytes.writeByte(byVIPTaskTimes);
			bytes.writeByte(byFlushTask);
			bytes.writeByte(byStudyAward);
			SGroupTask.vectorToByteArray(vecTask, bytes);
		}

		public static function vectorToByteArray(vec:Vector.<SGroupTaskInfoForClient>, bytes:ByteArray):void
		{
			BytesUtil.writeVectorLength(bytes, vec.length);
			for each(var s:SGroupTaskInfoForClient in vec)
				s.toByteArray(bytes);
		}
	}
}
