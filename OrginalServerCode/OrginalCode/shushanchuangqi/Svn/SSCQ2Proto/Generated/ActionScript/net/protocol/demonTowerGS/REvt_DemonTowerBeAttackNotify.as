/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_DemonTowerBeAttackNotify.as
//  Purpose:      协议:锁妖塔, 函数:镇妖塔被抢通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数DemonTowerBeAttackNotify[镇妖塔被抢通知]的接收事件
	 */
	public final class REvt_DemonTowerBeAttackNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTowerGS_DemonTowerBeAttackNotify";
		public static const DATA_ERROR:String = "DemonTowerGS_DemonTowerBeAttackNotify_Error";

		public var dwFloorID:uint; //(无符号32位整数)层数
		public var dwPos:uint; //(无符号32位整数)位置
		public var qwAtkUserID:BigInteger; //(无符号64位整数)抢夺人的Id
		public var strRole:String; //抢夺人的名字
		public var vecFailSoulPrize:Vector.<MoneyInfo>; //失败后的魄奖励

		public function REvt_DemonTowerBeAttackNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_DemonTowerBeAttackNotify dwFloorID={dwFloorID} dwPos={dwPos} qwAtkUserID={qwAtkUserID} strRole={strRole}/>;
			if(vecFailSoulPrize != null)
			{
				var vecFailSoulPrizeXml:XML = <Vec_MoneyInfo _name_="vecFailSoulPrize"/>;
				for each(var s1:MoneyInfo in vecFailSoulPrize)
					vecFailSoulPrizeXml.appendChild(s1.toXML());
				topXml.appendChild(vecFailSoulPrizeXml);
			}
			return topXml;
		}
	}
}
