/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BattleLogNotify.as
//  Purpose:      协议:新帮派战相关协议, 函数:战斗日志通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数BattleLogNotify[战斗日志通知]的接收事件
	 */
	public final class REvt_BattleLogNotify extends Event
	{
		public static const DATA_RECEIVE:String = "NewGuildBattleProt_BattleLogNotify";
		public static const DATA_ERROR:String = "NewGuildBattleProt_BattleLogNotify_Error";

		public var wMsgID:uint; //(无符号16位整数)消息ID
		public var vecStr:Vector.<String>; //聊天信息参数

		public function REvt_BattleLogNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BattleLogNotify wMsgID={wMsgID}/>;
			if(vecStr != null)
			{
				var vecStrXml:XML = <Vec_string _name_="vecStr"/>;
				var text1:String = "";
				for each(var value1:String in vecStr)
					text1 += "[" + value1 + "]";
				vecStrXml.appendChild(text1);
				topXml.appendChild(vecStrXml);
			}
			return topXml;
		}
	}
}
