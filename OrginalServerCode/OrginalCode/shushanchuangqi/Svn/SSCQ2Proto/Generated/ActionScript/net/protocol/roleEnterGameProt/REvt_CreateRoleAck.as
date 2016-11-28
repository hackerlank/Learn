/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_CreateRoleAck.as
//  Purpose:      协议:角色信息相关操作协议, 函数:创建角色应答
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEnterGameProt
{
	import flash.events.Event;

	/**
	 * 函数CreateRoleAck[创建角色应答]的接收事件
	 */
	public final class REvt_CreateRoleAck extends Event
	{
		public static const DATA_RECEIVE:String = "RoleEnterGameProt_CreateRoleAck";
		public static const DATA_ERROR:String = "RoleEnterGameProt_CreateRoleAck_Error";

		public var eCreateRoleResult:uint; //(枚举类型：ECreateRoleResult)创建结果

		public function REvt_CreateRoleAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_CreateRoleAck eCreateRoleResult={eCreateRoleResult}/>;
			return topXml;
		}
		public  function getMsg():String 
		{
			 return getDescription(eCreateRoleResult);
		}
		public  function getDescription(value:uint):String 
		{
			 return ECreateRoleResult.getDescription( value );
		}
	}
}
