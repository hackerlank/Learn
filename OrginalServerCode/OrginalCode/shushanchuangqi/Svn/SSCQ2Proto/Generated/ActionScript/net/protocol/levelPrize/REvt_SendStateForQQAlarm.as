/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SendStateForQQAlarm.as
//  Purpose:      协议:等级奖励, 函数:QQAlarm奖励状态通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.levelPrize
{
	import flash.events.Event;

	/**
	 * 函数SendStateForQQAlarm[QQAlarm奖励状态通知]的接收事件
	 */
	public final class REvt_SendStateForQQAlarm extends Event
	{
		public static const DATA_RECEIVE:String = "LevelPrize_SendStateForQQAlarm";
		public static const DATA_ERROR:String = "LevelPrize_SendStateForQQAlarm_Error";

		public var wActID:uint; //(无符号16位整数)活动ID
		public var eRet:uint; //(枚举类型：ELevelActStatus)结果

		public function REvt_SendStateForQQAlarm(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SendStateForQQAlarm wActID={wActID} eRet={eRet}/>;
			return topXml;
		}
	}
}
