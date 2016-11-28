/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_CancelSweeping.as
//  Purpose:      协议:副本相关协议, 函数:取消扫荡
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.events.Event;

	/**
	 * 函数CancelSweeping[取消扫荡]的返回事件
	 */
	public final class TEvt_CancelSweeping extends Event
	{
		public static const DATA_RETURN:String = "DungeonProt_CancelSweeping";
		public static const DATA_ERROR:String = "DungeonProt_CancelSweeping_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_CancelSweeping; //返回的参数

		public function TEvt_CancelSweeping(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_CancelSweeping ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
