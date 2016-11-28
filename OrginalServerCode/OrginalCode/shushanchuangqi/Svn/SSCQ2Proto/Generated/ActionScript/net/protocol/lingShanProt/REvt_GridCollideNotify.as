/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GridCollideNotify.as
//  Purpose:      协议:灵山（改名秘境）寻宝, 函数:玩家格子碰撞结果通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.events.Event;

	/**
	 * 函数GridCollideNotify[玩家格子碰撞结果通知]的接收事件
	 */
	public final class REvt_GridCollideNotify extends Event
	{
		public static const DATA_RECEIVE:String = "LingShanProt_GridCollideNotify";
		public static const DATA_ERROR:String = "LingShanProt_GridCollideNotify_Error";

		public var vecGridCollideInfo:Vector.<SGridCollideInfo>; //格子碰撞
		public var wRoomID:uint; //(无符号16位整数)房间id

		public function REvt_GridCollideNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GridCollideNotify wRoomID={wRoomID}/>;
			if(vecGridCollideInfo != null)
			{
				var vecGridCollideInfoXml:XML = <Vec_SGridCollideInfo _name_="vecGridCollideInfo"/>;
				for each(var s1:SGridCollideInfo in vecGridCollideInfo)
					vecGridCollideInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecGridCollideInfoXml);
			}
			return topXml;
		}
	}
}
