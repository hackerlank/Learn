/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BossInfoNotify.as
//  Purpose:      协议:BOSS相关协议, 函数:世界BOSS信息通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.bossProt
{
	import flash.events.Event;

	/**
	 * 函数BossInfoNotify[世界BOSS信息通知]的接收事件
	 */
	public final class REvt_BossInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "BossProt_BossInfoNotify";
		public static const DATA_ERROR:String = "BossProt_BossInfoNotify_Error";

		public var dwBoosID:uint; //(无符号32位整数)bossID
		public var dwCurHP:uint; //(无符号32位整数)当前血量
		public var dwMaxHP:uint; //(无符号32位整数)最大血量
		public var dwPlayerCnt:uint; //(无符号32位整数)当前地图人数

		public function REvt_BossInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BossInfoNotify dwBoosID={dwBoosID} dwCurHP={dwCurHP} dwMaxHP={dwMaxHP} dwPlayerCnt={dwPlayerCnt}/>;
			return topXml;
		}
	}
}
