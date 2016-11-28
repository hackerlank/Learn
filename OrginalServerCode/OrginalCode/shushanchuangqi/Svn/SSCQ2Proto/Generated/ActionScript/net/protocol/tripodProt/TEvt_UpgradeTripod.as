/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_UpgradeTripod.as
//  Purpose:      协议:九疑鼎相关协议, 函数:升级九疑鼎
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	import flash.events.Event;

	/**
	 * 函数UpgradeTripod[升级九疑鼎]的返回事件
	 */
	public final class TEvt_UpgradeTripod extends Event
	{
		public static const DATA_RETURN:String = "TripodProt_UpgradeTripod";
		public static const DATA_ERROR:String = "TripodProt_UpgradeTripod_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_UpgradeTripod; //返回的参数

		public function TEvt_UpgradeTripod(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_UpgradeTripod ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
