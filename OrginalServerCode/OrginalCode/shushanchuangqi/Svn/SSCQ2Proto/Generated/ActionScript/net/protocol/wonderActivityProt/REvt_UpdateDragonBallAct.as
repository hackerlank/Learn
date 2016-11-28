/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateDragonBallAct.as
//  Purpose:      协议:精彩活动, 函数:更新七星龙珠活动信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateDragonBallAct[更新七星龙珠活动信息]的接收事件
	 */
	public final class REvt_UpdateDragonBallAct extends Event
	{
		public static const DATA_RECEIVE:String = "WonderActivityProt_UpdateDragonBallAct";
		public static const DATA_ERROR:String = "WonderActivityProt_UpdateDragonBallAct_Error";

		public var oDragonBallAct:SDragonBallAct; //七星龙珠活动信息

		public function REvt_UpdateDragonBallAct(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateDragonBallAct/>;
			if(oDragonBallAct != null)
				topXml.appendChild(oDragonBallAct.toXML("oDragonBallAct"));
			return topXml;
		}
	}
}
