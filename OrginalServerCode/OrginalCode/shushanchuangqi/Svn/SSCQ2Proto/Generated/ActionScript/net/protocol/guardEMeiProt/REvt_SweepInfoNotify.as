/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SweepInfoNotify.as
//  Purpose:      协议:守卫峨眉协议, 函数:扫荡信息通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	import flash.events.Event;

	/**
	 * 函数SweepInfoNotify[扫荡信息通知]的接收事件
	 */
	public final class REvt_SweepInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GuardEMeiProt_SweepInfoNotify";
		public static const DATA_ERROR:String = "GuardEMeiProt_SweepInfoNotify_Error";

		public var wCurProgress:uint; //(无符号16位整数)当前进度
		public var vecGEMSAwardInfo:Vector.<SGEMAwardInfo>; //守卫峨眉扫荡奖励信息

		public function REvt_SweepInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SweepInfoNotify wCurProgress={wCurProgress}/>;
			if(vecGEMSAwardInfo != null)
			{
				var vecGEMSAwardInfoXml:XML = <Vec_SGEMAwardInfo _name_="vecGEMSAwardInfo"/>;
				for each(var s1:SGEMAwardInfo in vecGEMSAwardInfo)
					vecGEMSAwardInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecGEMSAwardInfoXml);
			}
			return topXml;
		}
	}
}
