/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_MonsterTargetChange.as
//  Purpose:      协议:地图相关功能的协议, 函数:怪物发现敌人
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数MonsterTargetChange[怪物发现敌人]的接收事件
	 */
	public final class REvt_MonsterTargetChange extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_MonsterTargetChange";
		public static const DATA_ERROR:String = "MapProt_MonsterTargetChange_Error";

		public var qwMonsterID:BigInteger; //(无符号64位整数)怪物ID
		public var qwTargetID:BigInteger; //(无符号64位整数)目标ID

		public function REvt_MonsterTargetChange(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_MonsterTargetChange qwMonsterID={qwMonsterID} qwTargetID={qwTargetID}/>;
			return topXml;
		}
	}
}
