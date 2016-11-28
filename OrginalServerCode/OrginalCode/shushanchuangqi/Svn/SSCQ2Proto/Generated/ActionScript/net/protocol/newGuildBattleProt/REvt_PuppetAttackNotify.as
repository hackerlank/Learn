/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PuppetAttackNotify.as
//  Purpose:      协议:新帮派战相关协议, 函数:战斗日志通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数PuppetAttackNotify[战斗日志通知]的接收事件
	 */
	public final class REvt_PuppetAttackNotify extends Event
	{
		public static const DATA_RECEIVE:String = "NewGuildBattleProt_PuppetAttackNotify";
		public static const DATA_ERROR:String = "NewGuildBattleProt_PuppetAttackNotify_Error";

		public var byIndex:uint; //(无符号8位整数)所属站位(0,1,2; 0为系统战争傀儡)

		public function REvt_PuppetAttackNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PuppetAttackNotify byIndex={byIndex}/>;
			return topXml;
		}
	}
}
