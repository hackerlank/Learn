/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_ReqTHBattlePrepareInfo.as
//  Purpose:      协议:寻宝协议, 函数:请求寻宝准备战斗信息(注：离线寻宝，重新登录游戏时请求此消息)
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
{
	import flash.events.Event;

	/**
	 * 函数ReqTHBattlePrepareInfo[请求寻宝准备战斗信息(注：离线寻宝，重新登录游戏时请求此消息)]的返回事件
	 */
	public final class TEvt_ReqTHBattlePrepareInfo extends Event
	{
		public static const DATA_RETURN:String = "TreasureHuntProt_ReqTHBattlePrepareInfo";
		public static const DATA_ERROR:String = "TreasureHuntProt_ReqTHBattlePrepareInfo_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_ReqTHBattlePrepareInfo; //返回的参数

		public function TEvt_ReqTHBattlePrepareInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_ReqTHBattlePrepareInfo ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
