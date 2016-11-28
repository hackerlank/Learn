/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_StatusNotify.as
//  Purpose:      协议:灵山（改名秘境）寻宝, 函数:玩家自己当前状态通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.events.Event;

	/**
	 * 函数StatusNotify[玩家自己当前状态通知]的接收事件
	 */
	public final class REvt_StatusNotify extends Event
	{
		public static const DATA_RECEIVE:String = "LingShanProt_StatusNotify";
		public static const DATA_ERROR:String = "LingShanProt_StatusNotify_Error";

		public var eRet:uint; //(枚举类型：ELingShanStatus)当前状态
		public var dwParam:uint; //(无符号32位整数)排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
		public var dwTime:uint; //(无符号32位整数)服务器时间戳
		public var wRoomID:uint; //(无符号16位整数)房间id

		public function REvt_StatusNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_StatusNotify eRet={eRet} dwParam={dwParam} dwTime={dwTime} wRoomID={wRoomID}/>;
			return topXml;
		}
	}
}
