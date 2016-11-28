/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_TakePrizeForQQAlarm.as
//  Purpose:      协议:等级奖励, 函数:QQAlarm获取奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.levelPrize
{
	import flash.events.Event;

	/**
	 * 函数TakePrizeForQQAlarm[QQAlarm获取奖励]的返回事件
	 */
	public final class TEvt_TakePrizeForQQAlarm extends Event
	{
		public static const DATA_RETURN:String = "LevelPrize_TakePrizeForQQAlarm";
		public static const DATA_ERROR:String = "LevelPrize_TakePrizeForQQAlarm_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_TakePrizeForQQAlarm; //返回的参数

		public function TEvt_TakePrizeForQQAlarm(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_TakePrizeForQQAlarm ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
