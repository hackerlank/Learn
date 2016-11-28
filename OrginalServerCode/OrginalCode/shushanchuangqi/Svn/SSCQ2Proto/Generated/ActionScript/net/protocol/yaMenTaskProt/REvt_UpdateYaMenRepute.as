/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateYaMenRepute.as
//  Purpose:      协议:衙门任务协议, 函数:更新声望
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yaMenTaskProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateYaMenRepute[更新声望]的接收事件
	 */
	public final class REvt_UpdateYaMenRepute extends Event
	{
		public static const DATA_RECEIVE:String = "YaMenTaskProt_UpdateYaMenRepute";
		public static const DATA_ERROR:String = "YaMenTaskProt_UpdateYaMenRepute_Error";

		public var dwYaMenRepute:uint; //(无符号32位整数)声望

		public function REvt_UpdateYaMenRepute(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateYaMenRepute dwYaMenRepute={dwYaMenRepute}/>;
			return topXml;
		}
	}
}
