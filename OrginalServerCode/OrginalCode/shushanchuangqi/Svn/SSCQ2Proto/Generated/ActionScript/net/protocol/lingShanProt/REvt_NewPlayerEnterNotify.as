/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NewPlayerEnterNotify.as
//  Purpose:      协议:灵山（改名秘境）寻宝, 函数:新玩家进入
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.events.Event;

	/**
	 * 函数NewPlayerEnterNotify[新玩家进入]的接收事件
	 */
	public final class REvt_NewPlayerEnterNotify extends Event
	{
		public static const DATA_RECEIVE:String = "LingShanProt_NewPlayerEnterNotify";
		public static const DATA_ERROR:String = "LingShanProt_NewPlayerEnterNotify_Error";

		public var vecRoomPlayInfo:Vector.<SRoomPlayInfo>; //玩家列表
		public var wRoomID:uint; //(无符号16位整数)房间id

		public function REvt_NewPlayerEnterNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NewPlayerEnterNotify wRoomID={wRoomID}/>;
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
