/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateMallDiscountInfoByPos.as
//  Purpose:      协议:商城相关协议, 函数:通过栏位通知玩家商城限购信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateMallDiscountInfoByPos[通过栏位通知玩家商城限购信息]的接收事件
	 */
	public final class REvt_UpdateMallDiscountInfoByPos extends Event
	{
		public static const DATA_RECEIVE:String = "MallProt_UpdateMallDiscountInfoByPos";
		public static const DATA_ERROR:String = "MallProt_UpdateMallDiscountInfoByPos_Error";

		public var oDiscount:SDiscount; //限购信息列表

		public function REvt_UpdateMallDiscountInfoByPos(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateMallDiscountInfoByPos/>;
			if(oDiscount != null)
				topXml.appendChild(oDiscount.toXML("oDiscount"));
			return topXml;
		}
	}
}
