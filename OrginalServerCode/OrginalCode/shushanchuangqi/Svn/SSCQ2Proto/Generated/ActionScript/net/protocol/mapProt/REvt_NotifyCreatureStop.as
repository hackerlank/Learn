/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NotifyCreatureStop.as
//  Purpose:      协议:地图相关功能的协议, 函数:通知Creature停止
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数NotifyCreatureStop[通知Creature停止]的接收事件
	 */
	public final class REvt_NotifyCreatureStop extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_NotifyCreatureStop";
		public static const DATA_ERROR:String = "MapProt_NotifyCreatureStop_Error";

		public var qwCreatureID:BigInteger; //(无符号64位整数)生物ID
		public var rDestPosition:SPosition; //最终位置

		public function REvt_NotifyCreatureStop(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NotifyCreatureStop qwCreatureID={qwCreatureID}/>;
			if(rDestPosition != null)
				topXml.appendChild(rDestPosition.toXML("rDestPosition"));
			return topXml;
		}
	}
}
