/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_BeautyFight.as
//  Purpose:      协议:美女系统, 函数:美女出战
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beauty
{
	import flash.events.Event;

	/**
	 * 函数BeautyFight[美女出战]的返回事件
	 */
	public final class TEvt_BeautyFight extends Event
	{
		public static const DATA_RETURN:String = "Beauty_BeautyFight";
		public static const DATA_ERROR:String = "Beauty_BeautyFight_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_BeautyFight; //返回的参数

		public function TEvt_BeautyFight(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_BeautyFight ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
