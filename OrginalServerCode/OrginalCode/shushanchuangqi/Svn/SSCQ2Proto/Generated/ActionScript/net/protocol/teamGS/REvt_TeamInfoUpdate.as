/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_TeamInfoUpdate.as
//  Purpose:      协议:竞技场协议, 函数:房间信息更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	import flash.events.Event;

	/**
	 * 函数TeamInfoUpdate[房间信息更新]的接收事件
	 */
	public final class REvt_TeamInfoUpdate extends Event
	{
		public static const DATA_RECEIVE:String = "TeamGS_TeamInfoUpdate";
		public static const DATA_ERROR:String = "TeamGS_TeamInfoUpdate_Error";

		public var stInfo:TeamInfo; //房间信息

		public function REvt_TeamInfoUpdate(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_TeamInfoUpdate/>;
			if(stInfo != null)
				topXml.appendChild(stInfo.toXML("stInfo"));
			return topXml;
		}
	}
}
