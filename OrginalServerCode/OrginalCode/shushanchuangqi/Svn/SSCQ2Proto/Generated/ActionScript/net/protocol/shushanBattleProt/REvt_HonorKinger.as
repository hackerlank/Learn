/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_HonorKinger.as
//  Purpose:      协议:蜀山论剑相关协议, 函数:广播荣誉王玩家信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	import flash.events.Event;

	/**
	 * 函数HonorKinger[广播荣誉王玩家信息]的接收事件
	 */
	public final class REvt_HonorKinger extends Event
	{
		public static const DATA_RECEIVE:String = "ShushanBattleProt_HonorKinger";
		public static const DATA_ERROR:String = "ShushanBattleProt_HonorKinger_Error";

		public var strName:String; //玩家名字
		public var wMaxHonor:uint; //(无符号16位整数)最高荣誉值

		public function REvt_HonorKinger(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_HonorKinger strName={strName} wMaxHonor={wMaxHonor}/>;
			return topXml;
		}
	}
}
