/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BubbleUpdate.as
//  Purpose:      协议:聊天协议, 函数:气泡提示信息更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.chatProt
{
	import flash.events.Event;
	import net.protocol.roleInfoDefine.SBubbleInfo;

	/**
	 * 函数BubbleUpdate[气泡提示信息更新]的接收事件
	 */
	public final class REvt_BubbleUpdate extends Event
	{
		public static const DATA_RECEIVE:String = "ChatProt_BubbleUpdate";
		public static const DATA_ERROR:String = "ChatProt_BubbleUpdate_Error";

		public var eType:uint; //(枚举类型：protoCommon.EDataChange)更新类型，增加，删除，修改
		public var sBubbleInfo:SBubbleInfo; //受影响的气泡信息

		public function REvt_BubbleUpdate(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BubbleUpdate eType={eType}/>;
			if(sBubbleInfo != null)
				topXml.appendChild(sBubbleInfo.toXML("sBubbleInfo"));
			return topXml;
		}
	}
}
