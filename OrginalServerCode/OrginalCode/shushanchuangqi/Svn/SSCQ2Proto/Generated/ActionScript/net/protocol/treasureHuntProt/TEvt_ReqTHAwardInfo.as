/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_ReqTHAwardInfo.as
//  Purpose:      协议:寻宝协议, 函数:请求寻宝奖励信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
{
	import flash.events.Event;

	/**
	 * 函数ReqTHAwardInfo[请求寻宝奖励信息]的返回事件
	 */
	public final class TEvt_ReqTHAwardInfo extends Event
	{
		public static const DATA_RETURN:String = "TreasureHuntProt_ReqTHAwardInfo";
		public static const DATA_ERROR:String = "TreasureHuntProt_ReqTHAwardInfo_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_ReqTHAwardInfo; //返回的参数

		public function TEvt_ReqTHAwardInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_ReqTHAwardInfo ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
