/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PlayerRamdomNameAck.as
//  Purpose:      协议:角色信息相关操作协议, 函数:玩家请求推荐名字返回
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEnterGameProt
{
	import flash.events.Event;

	/**
	 * 函数PlayerRamdomNameAck[玩家请求推荐名字返回]的接收事件
	 */
	public final class REvt_PlayerRamdomNameAck extends Event
	{
		public static const DATA_RECEIVE:String = "RoleEnterGameProt_PlayerRamdomNameAck";
		public static const DATA_ERROR:String = "RoleEnterGameProt_PlayerRamdomNameAck_Error";

		public var strName:String; //空表示没有得到

		public function REvt_PlayerRamdomNameAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PlayerRamdomNameAck strName={strName}/>;
			return topXml;
		}
	}
}
