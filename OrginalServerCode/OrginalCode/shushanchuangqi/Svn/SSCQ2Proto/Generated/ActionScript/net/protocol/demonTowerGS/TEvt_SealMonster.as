/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_SealMonster.as
//  Purpose:      协议:锁妖塔, 函数:封印怪物(挑战?)
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.events.Event;

	/**
	 * 函数SealMonster[封印怪物(挑战?)]的返回事件
	 */
	public final class TEvt_SealMonster extends Event
	{
		public static const DATA_RETURN:String = "DemonTowerGS_SealMonster";
		public static const DATA_ERROR:String = "DemonTowerGS_SealMonster_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_SealMonster; //返回的参数

		public function TEvt_SealMonster(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_SealMonster ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
