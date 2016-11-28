/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_EnterMap.as
//  Purpose:      协议:BOSS相关协议, 函数:进入boss地图
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.bossProt
{
	import flash.events.Event;

	/**
	 * 函数EnterMap[进入boss地图]的返回事件
	 */
	public final class TEvt_EnterMap extends Event
	{
		public static const DATA_RETURN:String = "BossProt_EnterMap";
		public static const DATA_ERROR:String = "BossProt_EnterMap_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_EnterMap; //返回的参数

		public function TEvt_EnterMap(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_EnterMap ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
