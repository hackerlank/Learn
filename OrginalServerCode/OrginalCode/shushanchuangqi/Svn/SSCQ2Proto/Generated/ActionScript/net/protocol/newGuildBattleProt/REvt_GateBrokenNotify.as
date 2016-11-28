/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GateBrokenNotify.as
//  Purpose:      协议:新帮派战相关协议, 函数:城门被攻破广播
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数GateBrokenNotify[城门被攻破广播]的接收事件
	 */
	public final class REvt_GateBrokenNotify extends Event
	{
		public static const DATA_RECEIVE:String = "NewGuildBattleProt_GateBrokenNotify";
		public static const DATA_ERROR:String = "NewGuildBattleProt_GateBrokenNotify_Error";

		public var eMountainType:uint; //(枚举类型：ENGBMountain)灵山类型
		public var vecAttackGuildID:Vector.<BigInteger>; //(无符号64位整数)（洞府战）攻击帮派ID

		public function REvt_GateBrokenNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GateBrokenNotify eMountainType={eMountainType}/>;
			if(vecAttackGuildID != null)
			{
				var vecAttackGuildIDXml:XML = <Vec_UINT64 _name_="vecAttackGuildID"/>;
				var text1:String = "";
				for each(var value1:BigInteger in vecAttackGuildID)
					text1 += "[" + value1 + "]";
				vecAttackGuildIDXml.appendChild(text1);
				topXml.appendChild(vecAttackGuildIDXml);
			}
			return topXml;
		}
	}
}
