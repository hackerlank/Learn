/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_StateNotify.as
//  Purpose:      协议:新帮派战相关协议, 函数:状态变更广播
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数StateNotify[状态变更广播]的接收事件
	 */
	public final class REvt_StateNotify extends Event
	{
		public static const DATA_RECEIVE:String = "NewGuildBattleProt_StateNotify";
		public static const DATA_ERROR:String = "NewGuildBattleProt_StateNotify_Error";

		public var eState:uint; //(枚举类型：ENGBState)当前帮派战状态
		public var dwRemainTime:uint; //(无符号32位整数)新帮派战剩余时间
		public var vecInfo:Vector.<SMountainPanelInfo>; //各个灵山信息

		public function REvt_StateNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_StateNotify eState={eState} dwRemainTime={dwRemainTime}/>;
			if(vecInfo != null)
			{
				var vecInfoXml:XML = <Vec_SMountainPanelInfo _name_="vecInfo"/>;
				for each(var s1:SMountainPanelInfo in vecInfo)
					vecInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecInfoXml);
			}
			return topXml;
		}
	}
}
