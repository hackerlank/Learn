/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_PlayerRankInfoNotify.as
//  Purpose:      协议:新帮派战相关协议, 函数:战功榜个人排名信息广播
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数PlayerRankInfoNotify[战功榜个人排名信息广播]的接收事件
	 */
	public final class REvt_PlayerRankInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "NewGuildBattleProt_PlayerRankInfoNotify";
		public static const DATA_ERROR:String = "NewGuildBattleProt_PlayerRankInfoNotify_Error";

		public var dwMaxCount:uint; //(无符号32位整数)最大排名数量
		public var dwCurIndex:uint; //(无符号32位整数)当前排名索引
		public var vecInfo:Vector.<SPlayerRankInfo>; //排名信息

		public function REvt_PlayerRankInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_PlayerRankInfoNotify dwMaxCount={dwMaxCount} dwCurIndex={dwCurIndex}/>;
			if(vecInfo != null)
			{
				var vecInfoXml:XML = <Vec_SPlayerRankInfo _name_="vecInfo"/>;
				for each(var s1:SPlayerRankInfo in vecInfo)
					vecInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecInfoXml);
			}
			return topXml;
		}
	}
}
