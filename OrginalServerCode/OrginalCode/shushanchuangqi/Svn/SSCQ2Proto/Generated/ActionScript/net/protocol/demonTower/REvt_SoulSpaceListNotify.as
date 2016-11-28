/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SoulSpaceListNotify.as
//  Purpose:      协议:锁妖塔, 函数:魄空间列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTower
{
	import flash.events.Event;

	/**
	 * 函数SoulSpaceListNotify[魄空间列表]的接收事件
	 */
	public final class REvt_SoulSpaceListNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTower_SoulSpaceListNotify";
		public static const DATA_ERROR:String = "DemonTower_SoulSpaceListNotify_Error";

		public var vecSpaceInfo:Vector.<SSpaceInfo>; //魄空间列表

		public function REvt_SoulSpaceListNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SoulSpaceListNotify/>;
			if(vecSpaceInfo != null)
			{
				var vecSpaceInfoXml:XML = <Vec_SSpaceInfo _name_="vecSpaceInfo"/>;
				for each(var s1:SSpaceInfo in vecSpaceInfo)
					vecSpaceInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecSpaceInfoXml);
			}
			return topXml;
		}
	}
}
