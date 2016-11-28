/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GuardInfoChangeNotify.as
//  Purpose:      协议:锁妖塔, 函数:锁妖塔镇守信息更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数GuardInfoChangeNotify[锁妖塔镇守信息更新]的接收事件
	 */
	public final class REvt_GuardInfoChangeNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTowerGS_GuardInfoChangeNotify";
		public static const DATA_ERROR:String = "DemonTowerGS_GuardInfoChangeNotify_Error";

		public var dwFloorID:uint; //(无符号32位整数)层数
		public var dwPos:uint; //(无符号32位整数)镇守玩家信息
		public var qwUserID:BigInteger; //(无符号64位整数)玩家ID 0 表示该位置放弃镇守
		public var oGuardInfo:GuardInfo; //镇守信息

		public function REvt_GuardInfoChangeNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GuardInfoChangeNotify dwFloorID={dwFloorID} dwPos={dwPos} qwUserID={qwUserID}/>;
			if(oGuardInfo != null)
				topXml.appendChild(oGuardInfo.toXML("oGuardInfo"));
			return topXml;
		}
	}
}
