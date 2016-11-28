/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_MissionPassSuccNotify.as
//  Purpose:      协议:守卫峨眉协议, 函数:关卡通关成功通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	import flash.events.Event;

	/**
	 * 函数MissionPassSuccNotify[关卡通关成功通知]的接收事件
	 */
	public final class REvt_MissionPassSuccNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuardEMeiProt_MissionPassSuccNotify";
		public static const DATA_ERROR:String = "GuardEMeiProt_MissionPassSuccNotify_Error";


		public function REvt_MissionPassSuccNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_MissionPassSuccNotify/>;
			return topXml;
		}
	}
}
