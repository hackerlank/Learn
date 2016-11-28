/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateTripod.as
//  Purpose:      协议:九疑鼎相关协议, 函数:更新玩家的九疑鼎数据
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateTripod[更新玩家的九疑鼎数据]的接收事件
	 */
	public final class REvt_UpdateTripod extends Event
	{
		public static const DATA_RECEIVE:String = "TripodProt_UpdateTripod";
		public static const DATA_ERROR:String = "TripodProt_UpdateTripod_Error";

		public var oTripodData:STripodData; //九疑鼎数据列表
		public var byShanfeng:uint; //(无符号8位整数)玩家今日已扇风次数
		public var byHelpTimes:uint; //(无符号8位整数)玩家今日已协助次数(玩家协助)

		public function REvt_UpdateTripod(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateTripod byShanfeng={byShanfeng} byHelpTimes={byHelpTimes}/>;
			if(oTripodData != null)
				topXml.appendChild(oTripodData.toXML("oTripodData"));
			return topXml;
		}
	}
}
