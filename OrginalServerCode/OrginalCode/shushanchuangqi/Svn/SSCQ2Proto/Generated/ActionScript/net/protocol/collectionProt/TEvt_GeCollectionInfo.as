/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GeCollectionInfo.as
//  Purpose:      协议:收藏协议, 函数:获取收藏信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.collectionProt
{
	import flash.events.Event;

	/**
	 * 函数GeCollectionInfo[获取收藏信息]的返回事件
	 */
	public final class TEvt_GeCollectionInfo extends Event
	{
		public static const DATA_RETURN:String = "CollectionProt_GeCollectionInfo";
		public static const DATA_ERROR:String = "CollectionProt_GeCollectionInfo_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GeCollectionInfo; //返回的参数

		public function TEvt_GeCollectionInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GeCollectionInfo ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
