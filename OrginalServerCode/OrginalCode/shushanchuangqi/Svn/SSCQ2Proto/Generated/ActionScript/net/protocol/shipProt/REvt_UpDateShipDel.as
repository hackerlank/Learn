/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpDateShipDel.as
//  Purpose:      协议:元江金船协议, 函数:发送船只删除消息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数UpDateShipDel[发送船只删除消息]的接收事件
	 */
	public final class REvt_UpDateShipDel extends Event
	{
		public static const DATA_RECEIVE:String = "ShipProt_UpDateShipDel";
		public static const DATA_ERROR:String = "ShipProt_UpDateShipDel_Error";

		public var qwInsID:BigInteger; //(无符号64位整数)金船唯一ID

		public function REvt_UpDateShipDel(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpDateShipDel qwInsID={qwInsID}/>;
			return topXml;
		}
	}
}
