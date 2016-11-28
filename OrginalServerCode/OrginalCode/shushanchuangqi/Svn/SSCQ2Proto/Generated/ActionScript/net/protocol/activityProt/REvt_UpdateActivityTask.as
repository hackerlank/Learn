/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateActivityTask.as
//  Purpose:      协议:活力任务协议, 函数:活力监测点更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.activityProt
{
	import flash.events.Event;
	import net.protocol.roleInfoDefine.SActivityTaskInfo;

	/**
	 * 函数UpdateActivityTask[活力监测点更新]的接收事件
	 */
	public final class REvt_UpdateActivityTask extends Event
	{
		public static const DATA_RECEIVE:String = "ActivityProt_UpdateActivityTask";
		public static const DATA_ERROR:String = "ActivityProt_UpdateActivityTask_Error";

		public var stActivityTask:SActivityTaskInfo; //活力监测点更新
		public var dwTotolActivity:uint; //(无符号32位整数)活力总值
		public var wActivity:uint; //(无符号16位整数)今日活力值

		public function REvt_UpdateActivityTask(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateActivityTask dwTotolActivity={dwTotolActivity} wActivity={wActivity}/>;
			if(stActivityTask != null)
				topXml.appendChild(stActivityTask.toXML("stActivityTask"));
			return topXml;
		}
	}
}
