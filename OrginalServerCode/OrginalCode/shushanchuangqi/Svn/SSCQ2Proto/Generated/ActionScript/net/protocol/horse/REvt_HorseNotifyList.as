/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_HorseNotifyList.as
//  Purpose:      协议:坐骑, 函数:坐骑信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
{
	import flash.events.Event;

	/**
	 * 函数HorseNotifyList[坐骑信息]的接收事件
	 */
	public final class REvt_HorseNotifyList extends Event
	{
		public static const DATA_RECEIVE:String = "Horse_HorseNotifyList";
		public static const DATA_ERROR:String = "Horse_HorseNotifyList_Error";

		public var vecHorseInfo:Vector.<SHorseInfo>; //坐骑信息

		public function REvt_HorseNotifyList(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_HorseNotifyList/>;
			if(vecHorseInfo != null)
			{
				var vecHorseInfoXml:XML = <Vec_SHorseInfo _name_="vecHorseInfo"/>;
				for each(var s1:SHorseInfo in vecHorseInfo)
					vecHorseInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecHorseInfoXml);
			}
			return topXml;
		}
	}
}
