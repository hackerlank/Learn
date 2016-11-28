/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetTHAward.as
//  Purpose:      协议:寻宝协议, 函数:获取寻宝奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
{
	import flash.events.Event;

	/**
	 * 函数GetTHAward[获取寻宝奖励]的返回事件
	 */
	public final class TEvt_GetTHAward extends Event
	{
		public static const DATA_RETURN:String = "TreasureHuntProt_GetTHAward";
		public static const DATA_ERROR:String = "TreasureHuntProt_GetTHAward_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetTHAward; //返回的参数

		public function TEvt_GetTHAward(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetTHAward ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
