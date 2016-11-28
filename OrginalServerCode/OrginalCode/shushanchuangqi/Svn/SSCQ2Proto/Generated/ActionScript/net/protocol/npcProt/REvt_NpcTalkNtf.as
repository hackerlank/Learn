/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NpcTalkNtf.as
//  Purpose:      协议:NPC相关协议, 函数:NPC对话通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.npcProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数NpcTalkNtf[NPC对话通知]的接收事件
	 */
	public final class REvt_NpcTalkNtf extends Event
	{
		public static const DATA_RECEIVE:String = "NpcProt_NpcTalkNtf";
		public static const DATA_ERROR:String = "NpcProt_NpcTalkNtf_Error";

		public var qwCreatureID:BigInteger; //(无符号64位整数)NPC的生物ID
		public var eResult:uint; //(枚举类型：ETalkResult)对话结果
		public var strContent:String; //对话内容

		public function REvt_NpcTalkNtf(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NpcTalkNtf qwCreatureID={qwCreatureID} eResult={eResult} strContent={strContent}/>;
			return topXml;
		}
	}
}
