/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetGuardInfo.as
//  Purpose:      协议:锁妖塔, 函数:获取镇守信息信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.events.Event;

	/**
	 * 函数GetGuardInfo[获取镇守信息信息]的返回事件
	 */
	public final class TEvt_GetGuardInfo extends Event
	{
		public static const DATA_RETURN:String = "DemonTowerGS_GetGuardInfo";
		public static const DATA_ERROR:String = "DemonTowerGS_GetGuardInfo_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetGuardInfo; //返回的参数

		public function TEvt_GetGuardInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetGuardInfo ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
