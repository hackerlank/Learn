/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateLadderMinRank.as
//  Purpose:      协议:竞技场协议, 函数:通告获得最好天梯排名
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	import flash.events.Event;

	/**
	 * 函数UpdateLadderMinRank[通告获得最好天梯排名]的接收事件
	 */
	public final class REvt_UpdateLadderMinRank extends Event
	{
		public static const DATA_RECEIVE:String = "ArenaGS_UpdateLadderMinRank";
		public static const DATA_ERROR:String = "ArenaGS_UpdateLadderMinRank_Error";

		public var dwLastRank:uint; //(无符号32位整数)前排名,0表示无排名
		public var dwNowRank:uint; //(无符号32位整数)现排名

		public function REvt_UpdateLadderMinRank(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateLadderMinRank dwLastRank={dwLastRank} dwNowRank={dwNowRank}/>;
			return topXml;
		}
	}
}
