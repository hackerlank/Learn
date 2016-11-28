/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GeShareList.as
//  Purpose:      协议:活力任务协议, 函数:获取成就分享信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.activityProt
{
	import flash.events.Event;

	/**
	 * 函数GeShareList[获取成就分享信息]的返回事件
	 */
	public final class TEvt_GeShareList extends Event
	{
		public static const DATA_RETURN:String = "ActivityProt_GeShareList";
		public static const DATA_ERROR:String = "ActivityProt_GeShareList_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GeShareList; //返回的参数

		public function TEvt_GeShareList(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GeShareList ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
