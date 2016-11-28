/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SyncRechargeToday.as
//  Purpose:      协议:不好归类的小协议, 函数:同步今日冲值仙石总数
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	import flash.events.Event;

	/**
	 * 函数SyncRechargeToday[同步今日冲值仙石总数]的接收事件
	 */
	public final class REvt_SyncRechargeToday extends Event
	{
		public static const DATA_RECEIVE:String = "MiscProt_SyncRechargeToday";
		public static const DATA_ERROR:String = "MiscProt_SyncRechargeToday_Error";

		public var dwTotalRechargeToday:uint; //(无符号32位整数)仙石

		public function REvt_SyncRechargeToday(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SyncRechargeToday dwTotalRechargeToday={dwTotalRechargeToday}/>;
			return topXml;
		}
	}
}
