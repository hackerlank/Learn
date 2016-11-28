/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_TotalInfo.as
//  Purpose:      协议:中午挂机活动, 函数:发送玩家在副本中的信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.langHuanBlessProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数TotalInfo[发送玩家在副本中的信息]的接收事件
	 */
	public final class REvt_TotalInfo extends Event
	{
		public static const DATA_RECEIVE:String = "LangHuanBlessProt_TotalInfo";
		public static const DATA_ERROR:String = "LangHuanBlessProt_TotalInfo_Error";

		public var qwPlayerID:BigInteger; //(无符号64位整数)玩家ID
		public var sTotalInfo:SLHBTotalInfo; //玩家信息

		public function REvt_TotalInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_TotalInfo qwPlayerID={qwPlayerID}/>;
			if(sTotalInfo != null)
				topXml.appendChild(sTotalInfo.toXML("sTotalInfo"));
			return topXml;
		}
	}
}
