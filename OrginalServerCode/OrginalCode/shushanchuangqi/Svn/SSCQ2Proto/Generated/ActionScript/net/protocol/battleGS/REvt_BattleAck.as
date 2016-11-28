/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BattleAck.as
//  Purpose:      协议:战斗通信协议, 函数:战斗请求结果
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.events.Event;

	/**
	 * 函数BattleAck[战斗请求结果]的接收事件
	 */
	public final class REvt_BattleAck extends Event
	{
		public static const DATA_RECEIVE:String = "BattleGS_BattleAck";
		public static const DATA_ERROR:String = "BattleGS_BattleAck_Error";

		public var eResult:uint; //(枚举类型：EBattleReqResult)返回结果

		public function REvt_BattleAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BattleAck eResult={eResult}/>;
			return topXml;
		}
		public  function getMsg():String 
		{
			 return getDescription(eResult);
		}
		public  function getDescription(value:uint):String 
		{
			 return EBattleReqResult.getDescription( value );
		}
	}
}
