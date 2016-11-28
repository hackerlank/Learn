/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_WareGemStone.as
//  Purpose:      协议:道具相关协议, 函数:穿戴宝石
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数WareGemStone[穿戴宝石]的返回事件
	 */
	public final class TEvt_WareGemStone extends Event
	{
		public static const DATA_RETURN:String = "ItemProt_WareGemStone";
		public static const DATA_ERROR:String = "ItemProt_WareGemStone_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_WareGemStone; //返回的参数

		public function TEvt_WareGemStone(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_WareGemStone ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
