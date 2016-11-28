/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_DelTitle.as
//  Purpose:      协议:称号协议, 函数:删除称号
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.titleProt
{
	import flash.events.Event;

	/**
	 * 函数DelTitle[删除称号]的接收事件
	 */
	public final class REvt_DelTitle extends Event
	{
		public static const DATA_RECEIVE:String = "TitleProt_DelTitle";
		public static const DATA_ERROR:String = "TitleProt_DelTitle_Error";

		public var wId:uint; //(无符号16位整数)称号ID

		public function REvt_DelTitle(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_DelTitle wId={wId}/>;
			return topXml;
		}
	}
}
