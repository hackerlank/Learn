/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_TakeOffGemStone.as
//  Purpose:      协议:道具相关协议, 函数:取下宝石
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数TakeOffGemStone[取下宝石]的返回事件
	 */
	public final class TEvt_TakeOffGemStone extends Event
	{
		public static const DATA_RETURN:String = "ItemProt_TakeOffGemStone";
		public static const DATA_ERROR:String = "ItemProt_TakeOffGemStone_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_TakeOffGemStone; //返回的参数

		public function TEvt_TakeOffGemStone(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_TakeOffGemStone ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
