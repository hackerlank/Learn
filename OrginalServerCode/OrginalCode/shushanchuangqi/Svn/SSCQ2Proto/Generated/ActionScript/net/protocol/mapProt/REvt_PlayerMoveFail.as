/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PlayerMoveFail.as
//  Purpose:      协议:地图相关功能的协议, 函数:通知角色移动失败
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数PlayerMoveFail[通知角色移动失败]的接收事件
	 */
	public final class REvt_PlayerMoveFail extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_PlayerMoveFail";
		public static const DATA_ERROR:String = "MapProt_PlayerMoveFail_Error";

		public var qwRoleID:BigInteger; //(无符号64位整数)角色ID
		public var rLastPosition:SPosition; //上一个位置
		public var vecPosition:Vector.<SPosition>; //移动位置列表

		public function REvt_PlayerMoveFail(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PlayerMoveFail qwRoleID={qwRoleID}/>;
			if(rLastPosition != null)
				topXml.appendChild(rLastPosition.toXML("rLastPosition"));
			if(vecPosition != null)
			{
				var vecPositionXml:XML = <Vec_SPosition _name_="vecPosition"/>;
				for each(var s2:SPosition in vecPosition)
					vecPositionXml.appendChild(s2.toXML());
				topXml.appendChild(vecPositionXml);
			}
			return topXml;
		}
	}
}
