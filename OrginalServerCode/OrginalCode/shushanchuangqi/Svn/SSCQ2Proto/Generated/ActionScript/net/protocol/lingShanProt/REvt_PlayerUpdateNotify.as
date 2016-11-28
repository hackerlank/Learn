/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PlayerUpdateNotify.as
//  Purpose:      协议:灵山（改名秘境）寻宝, 函数:玩家数据更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.events.Event;

	/**
	 * 函数PlayerUpdateNotify[玩家数据更新]的接收事件
	 */
	public final class REvt_PlayerUpdateNotify extends Event
	{
		public static const DATA_RECEIVE:String = "LingShanProt_PlayerUpdateNotify";
		public static const DATA_ERROR:String = "LingShanProt_PlayerUpdateNotify_Error";

		public var vecRoomPlayInfo:Vector.<SRoomPlayInfo>; //玩家列表
		public var wRoomID:uint; //(无符号16位整数)房间id

		public function REvt_PlayerUpdateNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PlayerUpdateNotify wRoomID={wRoomID}/>;
			if(vecRoomPlayInfo != null)
			{
				var vecRoomPlayInfoXml:XML = <Vec_SRoomPlayInfo _name_="vecRoomPlayInfo"/>;
				for each(var s1:SRoomPlayInfo in vecRoomPlayInfo)
					vecRoomPlayInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecRoomPlayInfoXml);
			}
			return topXml;
		}
	}
}
