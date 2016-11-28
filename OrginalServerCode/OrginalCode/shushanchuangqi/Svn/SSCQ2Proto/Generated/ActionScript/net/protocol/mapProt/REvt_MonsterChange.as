/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_MonsterChange.as
//  Purpose:      协议:地图相关功能的协议, 函数:通知怪物改变
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数MonsterChange[通知怪物改变]的接收事件
	 */
	public final class REvt_MonsterChange extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_MonsterChange";
		public static const DATA_ERROR:String = "MapProt_MonsterChange_Error";

		public var qwCreatureID:BigInteger; //(无符号64位整数)生物ID
		public var rMonsterAppear:SMonsterAppear; //怪物外观

		public function REvt_MonsterChange(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_MonsterChange qwCreatureID={qwCreatureID}/>;
			if(rMonsterAppear != null)
				topXml.appendChild(rMonsterAppear.toXML("rMonsterAppear"));
			return topXml;
		}
	}
}
