/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_UpgradeSoulSpace.as
//  Purpose:      协议:锁妖塔, 函数:升级魄空间
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTower
{
	import flash.events.Event;

	/**
	 * 函数UpgradeSoulSpace[升级魄空间]的返回事件
	 */
	public final class TEvt_UpgradeSoulSpace extends Event
	{
		public static const DATA_RETURN:String = "DemonTower_UpgradeSoulSpace";
		public static const DATA_ERROR:String = "DemonTower_UpgradeSoulSpace_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_UpgradeSoulSpace; //返回的参数

		public function TEvt_UpgradeSoulSpace(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_UpgradeSoulSpace ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
