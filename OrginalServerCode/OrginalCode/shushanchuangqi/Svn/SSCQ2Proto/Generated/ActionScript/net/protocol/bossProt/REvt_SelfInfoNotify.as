/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SelfInfoNotify.as
//  Purpose:      协议:BOSS相关协议, 函数:个人信息通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.bossProt
{
	import flash.events.Event;

	/**
	 * 函数SelfInfoNotify[个人信息通知]的接收事件
	 */
	public final class REvt_SelfInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "BossProt_SelfInfoNotify";
		public static const DATA_ERROR:String = "BossProt_SelfInfoNotify_Error";

		public var oSelfInfo:SPlayerInfo; //玩家信息
		public var dwBeginTime:uint; //(无符号32位整数)开始时间
		public var dwEndTime:uint; //(无符号32位整数)结束时间
		public var dwReliveTime:uint; //(无符号32位整数)复活时间
		public var dwSilverBufferCdTime:uint; //(无符号32位整数)银币加持cd
		public var dwSilverBufferCnt:uint; //(无符号32位整数)银币加持次数
		public var dwGoldBufferCnt:uint; //(无符号32位整数)金币加持次数
		public var dwGoldAttackCnt:uint; //(无符号32位整数)直接攻击次数

		public function REvt_SelfInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SelfInfoNotify dwBeginTime={dwBeginTime} dwEndTime={dwEndTime} dwReliveTime={dwReliveTime} dwSilverBufferCdTime={dwSilverBufferCdTime}
				 dwSilverBufferCnt={dwSilverBufferCnt} dwGoldBufferCnt={dwGoldBufferCnt} dwGoldAttackCnt={dwGoldAttackCnt}/>;
			if(oSelfInfo != null)
				topXml.appendChild(oSelfInfo.toXML("oSelfInfo"));
			return topXml;
		}
	}
}
