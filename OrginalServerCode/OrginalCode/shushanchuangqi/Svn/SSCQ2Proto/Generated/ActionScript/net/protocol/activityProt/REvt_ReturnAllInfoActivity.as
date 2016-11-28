/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ReturnAllInfoActivity.as
//  Purpose:      协议:活力任务协议, 函数:获取活力任务详情
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.activityProt
{
	import flash.events.Event;

	/**
	 * 函数ReturnAllInfoActivity[获取活力任务详情]的接收事件
	 */
	public final class REvt_ReturnAllInfoActivity extends Event
	{
		public static const DATA_RECEIVE:String = "ActivityProt_ReturnAllInfoActivity";
		public static const DATA_ERROR:String = "ActivityProt_ReturnAllInfoActivity_Error";

		public var stActivityInfo:SActivityInfoForClient; //活力任务详情

		public function REvt_ReturnAllInfoActivity(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ReturnAllInfoActivity/>;
			if(stActivityInfo != null)
				topXml.appendChild(stActivityInfo.toXML("stActivityInfo"));
			return topXml;
		}
	}
}
