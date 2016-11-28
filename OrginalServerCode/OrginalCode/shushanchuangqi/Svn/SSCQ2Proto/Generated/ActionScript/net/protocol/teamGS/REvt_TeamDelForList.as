/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_TeamDelForList.as
//  Purpose:      协议:竞技场协议, 函数:队伍解散
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	import flash.events.Event;

	/**
	 * 函数TeamDelForList[队伍解散]的接收事件
	 */
	public final class REvt_TeamDelForList extends Event
	{
		public static const DATA_RECEIVE:String = "TeamGS_TeamDelForList";
		public static const DATA_ERROR:String = "TeamGS_TeamDelForList_Error";

		public var dwTeamID:uint; //(无符号32位整数)队伍ID

		public function REvt_TeamDelForList(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_TeamDelForList dwTeamID={dwTeamID}/>;
			return topXml;
		}
	}
}
