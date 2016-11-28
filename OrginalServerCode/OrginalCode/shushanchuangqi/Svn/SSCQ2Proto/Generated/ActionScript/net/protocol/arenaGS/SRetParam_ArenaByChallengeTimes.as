/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ArenaByChallengeTimes.as
//  Purpose:      请求购买挑战次数
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	/**
	 * 请求购买挑战次数的返回的参数组成的结构体
	 */
	public final class SRetParam_ArenaByChallengeTimes
	{
		public var eResult:uint; //(枚举类型：EArenaResult)请求挑战返回
		public var wChallenge:uint; //(无符号16位整数)今日挑战次数
		public var wChallengeBuyTimes:uint; //(无符号16位整数)购买的挑战次数

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ArenaByChallengeTimes _name_={name_} eResult={eResult} wChallenge={wChallenge} wChallengeBuyTimes={wChallengeBuyTimes}/>;
			else
				topXml = <SRetParam_ArenaByChallengeTimes eResult={eResult} wChallenge={wChallenge} wChallengeBuyTimes={wChallengeBuyTimes}/>;
			return topXml;
		}
	}
}
