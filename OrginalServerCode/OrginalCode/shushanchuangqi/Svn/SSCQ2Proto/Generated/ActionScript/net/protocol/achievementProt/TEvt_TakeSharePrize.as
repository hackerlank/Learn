/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_TakeSharePrize.as
//  Purpose:      协议:成就相关协议, 函数:获取成就分享奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.achievementProt
{
	import flash.events.Event;

	/**
	 * 函数TakeSharePrize[获取成就分享奖励]的返回事件
	 */
	public final class TEvt_TakeSharePrize extends Event
	{
		public static const DATA_RETURN:String = "AchievementProt_TakeSharePrize";
		public static const DATA_ERROR:String = "AchievementProt_TakeSharePrize_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_TakeSharePrize; //返回的参数

		public function TEvt_TakeSharePrize(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_TakeSharePrize ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
