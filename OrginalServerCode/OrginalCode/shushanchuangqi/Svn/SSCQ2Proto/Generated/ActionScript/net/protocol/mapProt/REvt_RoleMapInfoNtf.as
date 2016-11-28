/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_RoleMapInfoNtf.as
//  Purpose:      协议:地图相关功能的协议, 函数:角色(非当前控制)地图信息通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数RoleMapInfoNtf[角色(非当前控制)地图信息通知]的接收事件
	 */
	public final class REvt_RoleMapInfoNtf extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_RoleMapInfoNtf";
		public static const DATA_ERROR:String = "MapProt_RoleMapInfoNtf_Error";

		public var qwRoleID:BigInteger; //(无符号64位整数)角色的ID
		public var wMapID:uint; //(无符号16位整数)地图ID

		public function REvt_RoleMapInfoNtf(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_RoleMapInfoNtf qwRoleID={qwRoleID} wMapID={wMapID}/>;
			return topXml;
		}
	}
}
