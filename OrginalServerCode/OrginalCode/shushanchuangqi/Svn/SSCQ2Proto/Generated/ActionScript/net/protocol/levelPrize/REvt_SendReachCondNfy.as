/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SendReachCondNfy.as
//  Purpose:      协议:等级奖励, 函数:可领状态通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.levelPrize
{
	import flash.events.Event;

	/**
	 * 函数SendReachCondNfy[可领状态通知]的接收事件
	 */
	public final class REvt_SendReachCondNfy extends Event
	{
		public static const DATA_RECEIVE:String = "LevelPrize_SendReachCondNfy";
		public static const DATA_ERROR:String = "LevelPrize_SendReachCondNfy_Error";

		public var wActID:uint; //(无符号16位整数)活动Id
		public var byIndex:uint; //(无符号8位整数)第几个奖励

		public function REvt_SendReachCondNfy(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SendReachCondNfy wActID={wActID} byIndex={byIndex}/>;
			return topXml;
		}
	}
}
