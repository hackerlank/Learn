/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GuardInfoNotify.as
//  Purpose:      协议:锁妖塔, 函数:锁妖塔镇守信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.events.Event;

	/**
	 * 函数GuardInfoNotify[锁妖塔镇守信息]的接收事件
	 */
	public final class REvt_GuardInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTowerGS_GuardInfoNotify";
		public static const DATA_ERROR:String = "DemonTowerGS_GuardInfoNotify_Error";

		public var dwFloorID:uint; //(无符号32位整数)层数
		public var vecGuardInfo:Vector.<GuardInfo>; //镇守玩家信息

		public function REvt_GuardInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GuardInfoNotify dwFloorID={dwFloorID}/>;
			if(vecGuardInfo != null)
			{
				var vecGuardInfoXml:XML = <Vec_GuardInfo _name_="vecGuardInfo"/>;
				for each(var s1:GuardInfo in vecGuardInfo)
					vecGuardInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecGuardInfoXml);
			}
			return topXml;
		}
	}
}
