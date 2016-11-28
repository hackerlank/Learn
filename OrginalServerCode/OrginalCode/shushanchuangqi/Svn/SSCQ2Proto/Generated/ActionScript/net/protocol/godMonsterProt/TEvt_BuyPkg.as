/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_BuyPkg.as
//  Purpose:      协议:天元神兽协议, 函数:购买限购礼包
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.godMonsterProt
{
	import flash.events.Event;

	/**
	 * 函数BuyPkg[购买限购礼包]的返回事件
	 */
	public final class TEvt_BuyPkg extends Event
	{
		public static const DATA_RETURN:String = "GodMonsterProt_BuyPkg";
		public static const DATA_ERROR:String = "GodMonsterProt_BuyPkg_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_BuyPkg; //返回的参数

		public function TEvt_BuyPkg(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_BuyPkg ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
