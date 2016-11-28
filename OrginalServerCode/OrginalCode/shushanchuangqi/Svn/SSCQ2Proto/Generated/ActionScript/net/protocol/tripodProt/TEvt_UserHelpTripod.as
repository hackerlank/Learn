/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_UserHelpTripod.as
//  Purpose:      协议:九疑鼎相关协议, 函数:玩家协助九疑鼎
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	import flash.events.Event;

	/**
	 * 函数UserHelpTripod[玩家协助九疑鼎]的返回事件
	 */
	public final class TEvt_UserHelpTripod extends Event
	{
		public static const DATA_RETURN:String = "TripodProt_UserHelpTripod";
		public static const DATA_ERROR:String = "TripodProt_UserHelpTripod_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_UserHelpTripod; //返回的参数

		public function TEvt_UserHelpTripod(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_UserHelpTripod ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
