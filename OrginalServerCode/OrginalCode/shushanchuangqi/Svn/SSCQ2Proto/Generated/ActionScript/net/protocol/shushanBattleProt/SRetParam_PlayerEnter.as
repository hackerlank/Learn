/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_PlayerEnter.as
//  Purpose:      参加蜀山论剑活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	/**
	 * 参加蜀山论剑活动的返回的参数组成的结构体
	 */
	public final class SRetParam_PlayerEnter
	{
		public var eResult:uint; //(枚举类型：ESSBattleResult)请求参加蜀山论剑返回

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_PlayerEnter _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_PlayerEnter eResult={eResult}/>;
			return topXml;
		}
	}
}
