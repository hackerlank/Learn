/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SendAnswerInfo.as
//  Purpose:      协议:答题协议, 函数:答完一题信息发送
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
{
	import flash.events.Event;

	/**
	 * 函数SendAnswerInfo[答完一题信息发送]的接收事件
	 */
	public final class REvt_SendAnswerInfo extends Event
	{
		public static const DATA_RECEIVE:String = "AnswerProt_SendAnswerInfo";
		public static const DATA_ERROR:String = "AnswerProt_SendAnswerInfo_Error";

		public var sPlayerInfo:SAnswerPlayer; //玩家信息
		public var vecRankInfo:Vector.<SAnswerRank>; //排名列表

		public function REvt_SendAnswerInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SendAnswerInfo/>;
			if(sPlayerInfo != null)
				topXml.appendChild(sPlayerInfo.toXML("sPlayerInfo"));
			if(vecRankInfo != null)
			{
				var vecRankInfoXml:XML = <Vec_SAnswerRank _name_="vecRankInfo"/>;
				for each(var s2:SAnswerRank in vecRankInfo)
					vecRankInfoXml.appendChild(s2.toXML());
				topXml.appendChild(vecRankInfoXml);
			}
			return topXml;
		}
	}
}
