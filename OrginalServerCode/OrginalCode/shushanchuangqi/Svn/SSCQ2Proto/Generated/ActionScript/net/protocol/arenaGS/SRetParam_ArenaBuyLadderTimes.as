/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_ArenaBuyLadderTimes.as
//  Purpose:      请求购买天梯挑战次数
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	/**
	 * 请求购买天梯挑战次数的返回的参数组成的结构体
	 */
	public final class SRetParam_ArenaBuyLadderTimes
	{
		public var eResult:uint; //(枚举类型：EArenaResult)请求购买返回
		public var dwLadderBuyTimesToday:uint; //(无符号32位整数)今日购买天梯挑战次数
		public var dwLadderBuyTimes:uint; //(无符号32位整数)购买的天梯挑战次数

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_ArenaBuyLadderTimes _name_={name_} eResult={eResult} dwLadderBuyTimesToday={dwLadderBuyTimesToday} dwLadderBuyTimes={dwLadderBuyTimes}/>;
			else
				topXml = <SRetParam_ArenaBuyLadderTimes eResult={eResult} dwLadderBuyTimesToday={dwLadderBuyTimesToday} dwLadderBuyTimes={dwLadderBuyTimes}/>;
			return topXml;
		}
	}
}
