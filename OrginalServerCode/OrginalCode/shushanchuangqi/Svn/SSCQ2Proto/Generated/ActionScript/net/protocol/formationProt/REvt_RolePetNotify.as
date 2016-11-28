/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_RolePetNotify.as
//  Purpose:      协议:阵灵相关协议, 函数:全局阵灵信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.formationProt
{
	import flash.events.Event;
	import net.protocol.roleInfoDefine.SRolePetInfo;

	/**
	 * 函数RolePetNotify[全局阵灵信息]的接收事件
	 */
	public final class REvt_RolePetNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FormationProt_RolePetNotify";
		public static const DATA_ERROR:String = "FormationProt_RolePetNotify_Error";

		public var sRolePetInfo:SRolePetInfo; //阵灵全局信息

		public function REvt_RolePetNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_RolePetNotify/>;
			if(sRolePetInfo != null)
				topXml.appendChild(sRolePetInfo.toXML("sRolePetInfo"));
			return topXml;
		}
	}
}
