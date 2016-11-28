/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NewTurnBeginNotify.as
//  Purpose:      协议:灵山（改名秘境）寻宝, 函数:新一轮开始
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.events.Event;

	/**
	 * 函数NewTurnBeginNotify[新一轮开始]的接收事件
	 */
	public final class REvt_NewTurnBeginNotify extends Event
	{
		public static const DATA_RECEIVE:String = "LingShanProt_NewTurnBeginNotify";
		public static const DATA_ERROR:String = "LingShanProt_NewTurnBeginNotify_Error";

		public var bFreshBox:Boolean; //是否刷新宝箱
		public var wRoomID:uint; //(无符号16位整数)房间id
		public var dwFreshTurn:uint; //(无符号32位整数)至宝刷新剩余轮数

		public function REvt_NewTurnBeginNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NewTurnBeginNotify bFreshBox={bFreshBox} wRoomID={wRoomID} dwFreshTurn={dwFreshTurn}/>;
			return topXml;
		}
	}
}
