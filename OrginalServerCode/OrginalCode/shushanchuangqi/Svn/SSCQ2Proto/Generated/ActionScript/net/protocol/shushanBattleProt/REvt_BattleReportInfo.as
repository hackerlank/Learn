/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BattleReportInfo.as
//  Purpose:      协议:蜀山论剑相关协议, 函数:蜀山论剑玩家的战报信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	import flash.events.Event;

	/**
	 * 函数BattleReportInfo[蜀山论剑玩家的战报信息]的接收事件
	 */
	public final class REvt_BattleReportInfo extends Event
	{
		public static const DATA_RECEIVE:String = "ShushanBattleProt_BattleReportInfo";
		public static const DATA_ERROR:String = "ShushanBattleProt_BattleReportInfo_Error";

		public var byType:uint; //(无符号8位整数)0表示个人战报 1表示全部
		public var vecReport:Vector.<SSSBattleReport>; //玩家的战斗信息

		public function REvt_BattleReportInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BattleReportInfo byType={byType}/>;
			if(vecReport != null)
			{
				var vecReportXml:XML = <Vec_SSSBattleReport _name_="vecReport"/>;
				for each(var s1:SSSBattleReport in vecReport)
					vecReportXml.appendChild(s1.toXML());
				topXml.appendChild(vecReportXml);
			}
			return topXml;
		}
	}
}
