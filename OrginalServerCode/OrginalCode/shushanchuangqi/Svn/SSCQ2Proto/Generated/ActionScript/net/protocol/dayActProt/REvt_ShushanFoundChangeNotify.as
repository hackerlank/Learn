/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ShushanFoundChangeNotify.as
//  Purpose:      协议:活动, 函数:蜀山基金活动改变通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayActProt
{
	import flash.events.Event;

	/**
	 * 函数ShushanFoundChangeNotify[蜀山基金活动改变通知]的接收事件
	 */
	public final class REvt_ShushanFoundChangeNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DayActProt_ShushanFoundChangeNotify";
		public static const DATA_ERROR:String = "DayActProt_ShushanFoundChangeNotify_Error";

		public var wGrowFoundInfo:uint; //(无符号16位整数)成长基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		public var wPExpFoundInfo:uint; //(无符号16位整数)修为基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		public var wSilverFoundInfo:uint; //(无符号16位整数)银币基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		public var wItemFoundInfo:uint; //(无符号16位整数)宝物基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		public var dwLoginDays:uint; //(无符号32位整数)玩家累计登陆天数(按低到高顺序,成长/修为/银币宝物)

		public function REvt_ShushanFoundChangeNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ShushanFoundChangeNotify wGrowFoundInfo={wGrowFoundInfo} wPExpFoundInfo={wPExpFoundInfo} wSilverFoundInfo={wSilverFoundInfo} wItemFoundInfo={wItemFoundInfo} dwLoginDays={dwLoginDays}/>;
			return topXml;
		}
	}
}
