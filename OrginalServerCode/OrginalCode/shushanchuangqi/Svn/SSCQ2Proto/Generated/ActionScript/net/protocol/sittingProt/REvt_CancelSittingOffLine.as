/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_CancelSittingOffLine.as
//  Purpose:      协议:打坐协议, 函数:玩家打坐结算
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.sittingProt
{
	import flash.events.Event;
	import net.protocol.itemProt.SResource;

	/**
	 * 函数CancelSittingOffLine[玩家打坐结算]的接收事件
	 */
	public final class REvt_CancelSittingOffLine extends Event
	{
		public static const DATA_RECEIVE:String = "SittingProt_CancelSittingOffLine";
		public static const DATA_ERROR:String = "SittingProt_CancelSittingOffLine_Error";

		public var byType:uint; //(无符号8位整数)0,表示单修，1表示双修
		public var vecRes:Vector.<SResource>; //获得的资源
		public var dwSittingTimer:uint; //(无符号32位整数)开始时间

		public function REvt_CancelSittingOffLine(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_CancelSittingOffLine byType={byType} dwSittingTimer={dwSittingTimer}/>;
			if(vecRes != null)
			{
				var vecResXml:XML = <Vec_SResource _name_="vecRes"/>;
				for each(var s1:SResource in vecRes)
					vecResXml.appendChild(s1.toXML());
				topXml.appendChild(vecResXml);
			}
			return topXml;
		}
	}
}
