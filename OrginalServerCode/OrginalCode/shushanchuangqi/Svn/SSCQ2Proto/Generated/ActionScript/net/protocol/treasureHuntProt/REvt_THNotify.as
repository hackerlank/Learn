/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_THNotify.as
//  Purpose:      协议:寻宝协议, 函数:寻宝开始/结束通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
{
	import flash.events.Event;

	/**
	 * 函数THNotify[寻宝开始/结束通知]的接收事件
	 */
	public final class REvt_THNotify extends Event
	{
		public static const DATA_RECEIVE:String = "TreasureHuntProt_THNotify";
		public static const DATA_ERROR:String = "TreasureHuntProt_THNotify_Error";

		public var eTHNotify:int; //(枚举类型：ETHNotify)开始/结束
		public var byKillNum:uint; //(无符号8位整数)今日已击杀BOSS次数
		public var vecTHBuffInfo:Vector.<STHBuffInfo>; //Buff信息

		public function REvt_THNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_THNotify eTHNotify={eTHNotify} byKillNum={byKillNum}/>;
			if(vecTHBuffInfo != null)
			{
				var vecTHBuffInfoXml:XML = <Vec_STHBuffInfo _name_="vecTHBuffInfo"/>;
				for each(var s1:STHBuffInfo in vecTHBuffInfo)
					vecTHBuffInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecTHBuffInfoXml);
			}
			return topXml;
		}
	}
}
