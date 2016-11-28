/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateStudyAward.as
//  Purpose:      协议:衙门任务协议, 函数:更新今日清修领奖次数
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yaMenTaskProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateStudyAward[更新今日清修领奖次数]的接收事件
	 */
	public final class REvt_UpdateStudyAward extends Event
	{
		public static const DATA_RECEIVE:String = "YaMenTaskProt_UpdateStudyAward";
		public static const DATA_ERROR:String = "YaMenTaskProt_UpdateStudyAward_Error";

		public var byStudyAward:uint; //(无符号8位整数)今日领取的清修次数

		public function REvt_UpdateStudyAward(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateStudyAward byStudyAward={byStudyAward}/>;
			return topXml;
		}
	}
}
