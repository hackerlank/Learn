/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BattleReportAck.as
//  Purpose:      协议:战斗通信协议, 函数:请求战报结果
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.events.Event;

	/**
	 * 函数BattleReportAck[请求战报结果]的接收事件
	 */
	public final class REvt_BattleReportAck extends Event
	{
		public static const DATA_RECEIVE:String = "BattleGS_BattleReportAck";
		public static const DATA_ERROR:String = "BattleGS_BattleReportAck_Error";

		public var eResult:uint; //(枚举类型：EReportReqResult)战报请求结果

		public function REvt_BattleReportAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BattleReportAck eResult={eResult}/>;
			return topXml;
		}
		public  function getMsg():String 
		{
			 return getDescription(eResult);
		}
		public  function getDescription(value:uint):String 
		{
			 return EReportReqResult.getDescription( value );
		}
	}
}
