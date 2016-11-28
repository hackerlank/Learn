/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_DemonTowerErrorNotify.as
//  Purpose:      协议:锁妖塔, 函数:镇妖塔错误信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.events.Event;

	/**
	 * 函数DemonTowerErrorNotify[镇妖塔错误信息]的接收事件
	 */
	public final class REvt_DemonTowerErrorNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTowerGS_DemonTowerErrorNotify";
		public static const DATA_ERROR:String = "DemonTowerGS_DemonTowerErrorNotify_Error";

		public var dwError:uint; //(无符号32位整数)错误码

		public function REvt_DemonTowerErrorNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_DemonTowerErrorNotify dwError={dwError}/>;
			return topXml;
		}
	}
}
