/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NotifyDgnAward.as
//  Purpose:      协议:副本相关协议, 函数:通知通关副本领奖
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;
	import net.protocol.itemProt.SItemGenInfo;
	import net.protocol.itemProt.SResource;

	/**
	 * 函数NotifyDgnAward[通知通关副本领奖]的接收事件
	 */
	public final class REvt_NotifyDgnAward extends Event
	{
		public static const DATA_RECEIVE:String = "DungeonProt_NotifyDgnAward";
		public static const DATA_ERROR:String = "DungeonProt_NotifyDgnAward_Error";

		public var qwDgnId:BigInteger; //(无符号64位整数)副本唯一实例
		public var wDgnType:uint; //(无符号16位整数)副本类型
		public var qwLastBattleID:BigInteger; //(无符号64位整数)最后战报
		public var byStar:uint; //(无符号8位整数)战斗评级
		public var vecItem:Vector.<SItemGenInfo>; //获得物品
		public var vecResSource:Vector.<SResource>; //获得资源

		public function REvt_NotifyDgnAward(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NotifyDgnAward qwDgnId={qwDgnId} wDgnType={wDgnType} qwLastBattleID={qwLastBattleID} byStar={byStar}/>;
			if(vecItem != null)
			{
				var vecItemXml:XML = <Vec_SItemGenInfo _name_="vecItem"/>;
				for each(var s1:SItemGenInfo in vecItem)
					vecItemXml.appendChild(s1.toXML());
				topXml.appendChild(vecItemXml);
			}
			if(vecResSource != null)
			{
				var vecResSourceXml:XML = <Vec_SResource _name_="vecResSource"/>;
				for each(var s2:SResource in vecResSource)
					vecResSourceXml.appendChild(s2.toXML());
				topXml.appendChild(vecResSourceXml);
			}
			return topXml;
		}
	}
}
