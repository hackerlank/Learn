/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateYaMenReputeLevel.as
//  Purpose:      协议:衙门任务协议, 函数:更新声望等级
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yaMenTaskProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateYaMenReputeLevel[更新声望等级]的接收事件
	 */
	public final class REvt_UpdateYaMenReputeLevel extends Event
	{
		public static const DATA_RECEIVE:String = "YaMenTaskProt_UpdateYaMenReputeLevel";
		public static const DATA_ERROR:String = "YaMenTaskProt_UpdateYaMenReputeLevel_Error";

		public var dwYaMenLevel:uint; //(无符号8位整数)声望等级

		public function REvt_UpdateYaMenReputeLevel(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateYaMenReputeLevel dwYaMenLevel={dwYaMenLevel}/>;
			return topXml;
		}
	}
}
