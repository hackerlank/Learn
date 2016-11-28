/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpgradeSoulSpaceNotify.as
//  Purpose:      协议:锁妖塔, 函数:升级魄空间通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTower
{
	import flash.events.Event;

	/**
	 * 函数UpgradeSoulSpaceNotify[升级魄空间通知]的接收事件
	 */
	public final class REvt_UpgradeSoulSpaceNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTower_UpgradeSoulSpaceNotify";
		public static const DATA_ERROR:String = "DemonTower_UpgradeSoulSpaceNotify_Error";

		public var dwSoulSpaceID:uint; //(无符号32位整数)魄空间类型ID(升级结果)
		public var dwSoulSpaceLevel:uint; //(无符号32位整数)魄空间等级(升级结果)

		public function REvt_UpgradeSoulSpaceNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpgradeSoulSpaceNotify dwSoulSpaceID={dwSoulSpaceID} dwSoulSpaceLevel={dwSoulSpaceLevel}/>;
			return topXml;
		}
	}
}
