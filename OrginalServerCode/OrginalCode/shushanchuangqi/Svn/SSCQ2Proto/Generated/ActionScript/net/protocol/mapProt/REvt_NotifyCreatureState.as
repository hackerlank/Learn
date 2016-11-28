/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NotifyCreatureState.as
//  Purpose:      协议:地图相关功能的协议, 函数:通知Creature当前状态
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数NotifyCreatureState[通知Creature当前状态]的接收事件
	 */
	public final class REvt_NotifyCreatureState extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_NotifyCreatureState";
		public static const DATA_ERROR:String = "MapProt_NotifyCreatureState_Error";

		public var qwCreatureID:BigInteger; //(无符号64位整数)Creature ID
		public var dwAppearState:uint; //(无符号32位整数)当前状态(EAppearState按位或的结果)

		public function REvt_NotifyCreatureState(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NotifyCreatureState qwCreatureID={qwCreatureID} dwAppearState={dwAppearState}/>;
			return topXml;
		}
	}
}
