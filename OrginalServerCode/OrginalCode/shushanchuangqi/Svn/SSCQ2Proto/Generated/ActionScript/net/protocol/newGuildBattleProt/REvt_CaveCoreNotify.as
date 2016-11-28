/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_CaveCoreNotify.as
//  Purpose:      协议:新帮派战相关协议, 函数:洞府战阵眼信息通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数CaveCoreNotify[洞府战阵眼信息通知]的接收事件
	 */
	public final class REvt_CaveCoreNotify extends Event
	{
		public static const DATA_RECEIVE:String = "NewGuildBattleProt_CaveCoreNotify";
		public static const DATA_ERROR:String = "NewGuildBattleProt_CaveCoreNotify_Error";

		public var vecCaveCoreInfo:Vector.<SCaveCoreInfo>; //阵眼信息

		public function REvt_CaveCoreNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_CaveCoreNotify/>;
			if(vecCaveCoreInfo != null)
			{
				var vecCaveCoreInfoXml:XML = <Vec_SCaveCoreInfo _name_="vecCaveCoreInfo"/>;
				for each(var s1:SCaveCoreInfo in vecCaveCoreInfo)
					vecCaveCoreInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecCaveCoreInfoXml);
			}
			return topXml;
		}
	}
}
