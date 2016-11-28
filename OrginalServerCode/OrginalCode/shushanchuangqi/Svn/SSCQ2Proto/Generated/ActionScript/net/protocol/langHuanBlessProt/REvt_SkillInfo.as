/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SkillInfo.as
//  Purpose:      协议:中午挂机活动, 函数:发送技能信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.langHuanBlessProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数SkillInfo[发送技能信息]的接收事件
	 */
	public final class REvt_SkillInfo extends Event
	{
		public static const DATA_RECEIVE:String = "LangHuanBlessProt_SkillInfo";
		public static const DATA_ERROR:String = "LangHuanBlessProt_SkillInfo_Error";

		public var qwAtkPlayerID:BigInteger; //(无符号64位整数)攻击者
		public var qwDfePlayerID:BigInteger; //(无符号64位整数)被攻击者
		public var eLHBSkillType:uint; //(枚举类型：ELHBSkillType)使用的技能ID

		public function REvt_SkillInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SkillInfo qwAtkPlayerID={qwAtkPlayerID} qwDfePlayerID={qwDfePlayerID} eLHBSkillType={eLHBSkillType}/>;
			return topXml;
		}
	}
}
