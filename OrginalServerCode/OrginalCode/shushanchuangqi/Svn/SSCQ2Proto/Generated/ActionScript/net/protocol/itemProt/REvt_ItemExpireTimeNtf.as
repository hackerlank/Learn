/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ItemExpireTimeNtf.as
//  Purpose:      协议:道具相关协议, 函数:道具的到期时间通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数ItemExpireTimeNtf[道具的到期时间通知]的接收事件
	 */
	public final class REvt_ItemExpireTimeNtf extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_ItemExpireTimeNtf";
		public static const DATA_ERROR:String = "ItemProt_ItemExpireTimeNtf_Error";

		public var qwInstID:BigInteger; //(无符号64位整数)道具的实例ID
		public var dwExpireTime:uint; //(无符号32位整数)到期时间(1970年1月1日0时开始的秒数)

		public function REvt_ItemExpireTimeNtf(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ItemExpireTimeNtf qwInstID={qwInstID} dwExpireTime={dwExpireTime}/>;
			return topXml;
		}
	}
}
