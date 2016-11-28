/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ItemErrNfg.as
//  Purpose:      协议:道具相关协议, 函数:错误提示
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数ItemErrNfg[错误提示]的接收事件
	 */
	public final class REvt_ItemErrNfg extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_ItemErrNfg";
		public static const DATA_ERROR:String = "ItemProt_ItemErrNfg_Error";

		public var eResult:uint; //(枚举类型：EItemResult)提示

		public function REvt_ItemErrNfg(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ItemErrNfg eResult={eResult}/>;
			return topXml;
		}
	}
}
