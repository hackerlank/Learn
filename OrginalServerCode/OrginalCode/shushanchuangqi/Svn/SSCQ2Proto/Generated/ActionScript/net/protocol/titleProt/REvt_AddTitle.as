/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AddTitle.as
//  Purpose:      协议:称号协议, 函数:获得称号
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.titleProt
{
	import flash.events.Event;
	import net.protocol.roleInfoDefine.STitle;

	/**
	 * 函数AddTitle[获得称号]的接收事件
	 */
	public final class REvt_AddTitle extends Event
	{
		public static const DATA_RECEIVE:String = "TitleProt_AddTitle";
		public static const DATA_ERROR:String = "TitleProt_AddTitle_Error";

		public var stTitleInfo:STitle; //称号详情

		public function REvt_AddTitle(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AddTitle/>;
			if(stTitleInfo != null)
				topXml.appendChild(stTitleInfo.toXML("stTitleInfo"));
			return topXml;
		}
	}
}
