/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_Draw.as
//  Purpose:      玩家抽奖
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	/**
	 * 玩家抽奖的返回的参数组成的结构体
	 */
	public final class SRetParam_Draw
	{
		public var wLotteryID:uint; //(无符号16位整数)抽奖号码
		public var eResult:uint; //(枚举类型：ELotteryRes)操作结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_Draw _name_={name_} wLotteryID={wLotteryID} eResult={eResult}/>;
			else
				topXml = <SRetParam_Draw wLotteryID={wLotteryID} eResult={eResult}/>;
			return topXml;
		}
	}
}
