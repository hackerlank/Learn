/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NpcTaskStateNtf.as
//  Purpose:      协议:NPC相关协议, 函数:NPC任务状态通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.npcProt
{
	import flash.events.Event;

	/**
	 * 函数NpcTaskStateNtf[NPC任务状态通知]的接收事件
	 */
	public final class REvt_NpcTaskStateNtf extends Event
	{
		public static const DATA_RECEIVE:String = "NpcProt_NpcTaskStateNtf";
		public static const DATA_ERROR:String = "NpcProt_NpcTaskStateNtf_Error";

		public var rVecNpcTask:Vector.<SNpcTaskState>; //NPC任务状态列表

		public function REvt_NpcTaskStateNtf(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NpcTaskStateNtf/>;
			if(rVecNpcTask != null)
			{
				var rVecNpcTaskXml:XML = <Vec_SNpcTaskState _name_="rVecNpcTask"/>;
				for each(var s1:SNpcTaskState in rVecNpcTask)
					rVecNpcTaskXml.appendChild(s1.toXML());
				topXml.appendChild(rVecNpcTaskXml);
			}
			return topXml;
		}
	}
}
