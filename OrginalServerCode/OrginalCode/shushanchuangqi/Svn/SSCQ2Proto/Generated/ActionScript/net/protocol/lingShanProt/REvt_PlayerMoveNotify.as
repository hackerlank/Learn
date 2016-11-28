/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PlayerMoveNotify.as
//  Purpose:      协议:灵山（改名秘境）寻宝, 函数:玩家移动结果通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.events.Event;

	/**
	 * 函数PlayerMoveNotify[玩家移动结果通知]的接收事件
	 */
	public final class REvt_PlayerMoveNotify extends Event
	{
		public static const DATA_RECEIVE:String = "LingShanProt_PlayerMoveNotify";
		public static const DATA_ERROR:String = "LingShanProt_PlayerMoveNotify_Error";

		public var vecPlayerMoveInfo:Vector.<SPlayerMoveInfo>; //玩家移动路径
		public var wRoomID:uint; //(无符号16位整数)房间id

		public function REvt_PlayerMoveNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PlayerMoveNotify wRoomID={wRoomID}/>;
			if(vecPlayerMoveInfo != null)
			{
				var vecPlayerMoveInfoXml:XML = <Vec_SPlayerMoveInfo _name_="vecPlayerMoveInfo"/>;
				for each(var s1:SPlayerMoveInfo in vecPlayerMoveInfo)
					vecPlayerMoveInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecPlayerMoveInfoXml);
			}
			return topXml;
		}
	}
}
