/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_StateNotify.as
//  Purpose:      协议:帮派相关协议, 函数:帮派战状态通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数StateNotify[帮派战状态通知]的接收事件
	 */
	public final class REvt_StateNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuildBattleProt_StateNotify";
		public static const DATA_ERROR:String = "GuildBattleProt_StateNotify_Error";

		public var eState:uint; //(枚举类型：EGBState)当前帮派战状态
		public var byBattleCount:uint; //(无符号8位整数)当前已经战斗的数量
		public var dwRemainTime:uint; //(无符号32位整数)当前状态剩余时间
		public var eSpotType:uint; //(枚举类型：EGBSpot)自己所在据点(报名的据点或者目前被调整到的据点)
		public var eSelfSide:uint; //(枚举类型：EGBSide)自己所在帮派方向

		public function REvt_StateNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_StateNotify eState={eState} byBattleCount={byBattleCount} dwRemainTime={dwRemainTime} eSpotType={eSpotType} eSelfSide={eSelfSide}/>;
			return topXml;
		}
	}
}
