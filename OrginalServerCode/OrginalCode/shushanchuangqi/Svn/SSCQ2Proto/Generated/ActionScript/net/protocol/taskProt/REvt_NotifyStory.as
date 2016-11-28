/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NotifyStory.as
//  Purpose:      协议:任务协议, 函数:通知播放剧情
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.events.Event;

	/**
	 * 函数NotifyStory[通知播放剧情]的接收事件
	 */
	public final class REvt_NotifyStory extends Event
	{
		public static const DATA_RECEIVE:String = "TaskProt_NotifyStory";
		public static const DATA_ERROR:String = "TaskProt_NotifyStory_Error";

		public var wStoryID:uint; //(无符号16位整数)剧情ID
		public var byType:uint; //(无符号8位整数)参数类型
		public var dwParam:uint; //(无符号32位整数)参数

		public function REvt_NotifyStory(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NotifyStory wStoryID={wStoryID} byType={byType} dwParam={dwParam}/>;
			return topXml;
		}
	}
}
