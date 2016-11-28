/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_CritNotify.as
//  Purpose:      协议:玩家在GameServer的消息处理, 函数:暴击通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEvent
{
	import flash.events.Event;

	/**
	 * 函数CritNotify[暴击通知]的接收事件
	 */
	public final class REvt_CritNotify extends Event
	{
		public static const DATA_RECEIVE:String = "RoleEvent_CritNotify";
		public static const DATA_ERROR:String = "RoleEvent_CritNotify_Error";

		public var eCritType:int; //(枚举类型：ECritType)暴击类型
		public var eCritMultiple:int; //(枚举类型：ECritMultiple)暴击倍数

		public function REvt_CritNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_CritNotify eCritType={eCritType} eCritMultiple={eCritMultiple}/>;
			return topXml;
		}
	}
}
