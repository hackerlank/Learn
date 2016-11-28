/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UserEnterMapNtf.as
//  Purpose:      协议:地图相关功能的协议, 函数:通知玩家进入地图
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数UserEnterMapNtf[通知玩家进入地图]的接收事件
	 */
	public final class REvt_UserEnterMapNtf extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_UserEnterMapNtf";
		public static const DATA_ERROR:String = "MapProt_UserEnterMapNtf_Error";

		public var wMapID:uint; //(无符号16位整数)地图ID
		public var qwRoleID:BigInteger; //(无符号64位整数)当前的角色ID
		public var byIndex:uint; //(无符号8位整数)地图序号,非主城返回255
		public var byTotal:uint; //(无符号8位整数)同Id地图总数,非主城返回0
		public var rPosition:SPosition; //进入位置
		public var fDir:Number; //(Float)方向

		public function REvt_UserEnterMapNtf(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UserEnterMapNtf wMapID={wMapID} qwRoleID={qwRoleID} byIndex={byIndex} byTotal={byTotal}
				 fDir={fDir}/>;
			if(rPosition != null)
				topXml.appendChild(rPosition.toXML("rPosition"));
			return topXml;
		}
	}
}
