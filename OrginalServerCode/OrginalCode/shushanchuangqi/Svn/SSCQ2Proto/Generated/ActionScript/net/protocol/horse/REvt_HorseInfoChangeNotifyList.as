/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_HorseInfoChangeNotifyList.as
//  Purpose:      协议:坐骑, 函数:坐骑信息更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
{
	import flash.events.Event;

	/**
	 * 函数HorseInfoChangeNotifyList[坐骑信息更新]的接收事件
	 */
	public final class REvt_HorseInfoChangeNotifyList extends Event
	{
		public static const DATA_RECEIVE:String = "Horse_HorseInfoChangeNotifyList";
		public static const DATA_ERROR:String = "Horse_HorseInfoChangeNotifyList_Error";

		public var dwHorseOpType:uint; //(无符号32位整数)更新类型
		public var oHorseInfo:SHorseInfo; //坐骑信息更新

		public function REvt_HorseInfoChangeNotifyList(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_HorseInfoChangeNotifyList dwHorseOpType={dwHorseOpType}/>;
			if(oHorseInfo != null)
				topXml.appendChild(oHorseInfo.toXML("oHorseInfo"));
			return topXml;
		}
	}
}
