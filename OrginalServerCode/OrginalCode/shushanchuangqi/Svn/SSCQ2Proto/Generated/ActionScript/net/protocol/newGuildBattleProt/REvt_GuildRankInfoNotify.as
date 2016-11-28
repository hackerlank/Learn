/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GuildRankInfoNotify.as
//  Purpose:      协议:新帮派战相关协议, 函数:战功榜帮派排名信息广播
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.events.Event;

	/**
	 * 函数GuildRankInfoNotify[战功榜帮派排名信息广播]的接收事件
	 */
	public final class REvt_GuildRankInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "NewGuildBattleProt_GuildRankInfoNotify";
		public static const DATA_ERROR:String = "NewGuildBattleProt_GuildRankInfoNotify_Error";

		public var dwMaxCount:uint; //(无符号32位整数)最大排名数量
		public var dwCurIndex:uint; //(无符号32位整数)当前排名索引
		public var vecInfo:Vector.<SGuildRankInfo>; //排名信息

		public function REvt_GuildRankInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GuildRankInfoNotify dwMaxCount={dwMaxCount} dwCurIndex={dwCurIndex}/>;
			if(vecInfo != null)
			{
				var vecInfoXml:XML = <Vec_SGuildRankInfo _name_="vecInfo"/>;
				for each(var s1:SGuildRankInfo in vecInfo)
					vecInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecInfoXml);
			}
			return topXml;
		}
	}
}
