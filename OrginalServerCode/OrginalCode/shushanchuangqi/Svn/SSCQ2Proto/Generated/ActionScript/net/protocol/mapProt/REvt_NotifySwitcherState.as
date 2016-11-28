/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NotifySwitcherState.as
//  Purpose:      协议:地图相关功能的协议, 函数:通知开关当前状态
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;

	/**
	 * 函数NotifySwitcherState[通知开关当前状态]的接收事件
	 */
	public final class REvt_NotifySwitcherState extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_NotifySwitcherState";
		public static const DATA_ERROR:String = "MapProt_NotifySwitcherState_Error";

		public var dwInstID:uint; //(无符号32位整数)开关唯一实例ID
		public var bOpen:Boolean; //当前开关是否开启

		public function REvt_NotifySwitcherState(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NotifySwitcherState dwInstID={dwInstID} bOpen={bOpen}/>;
			return topXml;
		}
	}
}
