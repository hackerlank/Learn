/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SystemFormatMsgIDNotifyWithShow.as
//  Purpose:      协议:聊天协议, 函数:系统MsgID通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.chatProt
{
	import flash.events.Event;
	import net.protocol.globalChatProt.SShowInfo;

	/**
	 * 函数SystemFormatMsgIDNotifyWithShow[系统MsgID通知]的接收事件
	 */
	public final class REvt_SystemFormatMsgIDNotifyWithShow extends Event
	{
		public static const DATA_RECEIVE:String = "ChatProt_SystemFormatMsgIDNotifyWithShow";
		public static const DATA_ERROR:String = "ChatProt_SystemFormatMsgIDNotifyWithShow_Error";

		public var wMsgID:uint; //(无符号16位整数)消息ID
		public var vecStr:Vector.<String>; //聊天信息参数
		public var vecShow:Vector.<SShowInfo>; //炫耀信息

		public function REvt_SystemFormatMsgIDNotifyWithShow(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SystemFormatMsgIDNotifyWithShow wMsgID={wMsgID}/>;
			if(vecStr != null)
			{
				var vecStrXml:XML = <Vec_string _name_="vecStr"/>;
				var text1:String = "";
				for each(var value1:String in vecStr)
					text1 += "[" + value1 + "]";
				vecStrXml.appendChild(text1);
				topXml.appendChild(vecStrXml);
			}
			if(vecShow != null)
			{
				var vecShowXml:XML = <Vec_SShowInfo _name_="vecShow"/>;
				for each(var s2:SShowInfo in vecShow)
					vecShowXml.appendChild(s2.toXML());
				topXml.appendChild(vecShowXml);
			}
			return topXml;
		}
	}
}
