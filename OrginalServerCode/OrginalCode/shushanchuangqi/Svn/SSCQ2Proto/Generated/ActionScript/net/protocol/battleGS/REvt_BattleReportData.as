/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BattleReportData.as
//  Purpose:      协议:战斗通信协议, 函数:战报
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;
	import flash.utils.ByteArray;
	import net.util.BytesUtil;

	/**
	 * 函数BattleReportData[战报]的接收事件
	 */
	public final class REvt_BattleReportData extends Event
	{
		public static const DATA_RECEIVE:String = "BattleGS_BattleReportData";
		public static const DATA_ERROR:String = "BattleGS_BattleReportData_Error";

		public var strBattleReport:ByteArray; //战报
		public var qwMasterID:BigInteger; //(无符号64位整数)视角角色ID
		public var wFighterID:uint; //(无符号16位整数)主将ID

		public function REvt_BattleReportData(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BattleReportData strBattleReport={BytesUtil.bytes2String(strBattleReport)} qwMasterID={qwMasterID} wFighterID={wFighterID}/>;
			return topXml;
		}
	}
}
