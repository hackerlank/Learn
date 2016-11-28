/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_EnterGameAck.as
//  Purpose:      协议:角色信息相关操作协议, 函数:请求进入游戏应答
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEnterGameProt
{
	import flash.events.Event;

	/**
	 * 函数EnterGameAck[请求进入游戏应答]的接收事件
	 */
	public final class REvt_EnterGameAck extends Event
	{
		public static const DATA_RECEIVE:String = "RoleEnterGameProt_EnterGameAck";
		public static const DATA_ERROR:String = "RoleEnterGameProt_EnterGameAck_Error";

		public var eEnterResult:uint; //(枚举类型：EEnterResult)登陆结果
		public var dwNowTimer:uint; //(无符号32位整数)目前服务器的时间

		public function REvt_EnterGameAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_EnterGameAck eEnterResult={eEnterResult} dwNowTimer={dwNowTimer}/>;
			return topXml;
		}
		public  function getMsg():String 
		{
			 return getDescription(eEnterResult);
		}
		public  function getDescription(value:uint):String 
		{
			 return EEnterResult.getDescription( value );
		}
	}
}
