/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_BattleArrayTakePrize.as
//  Purpose:      领取通关奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
{
	/**
	 * 领取通关奖励的返回的参数组成的结构体
	 */
	public final class SRetParam_BattleArrayTakePrize
	{
		public var eBattleArrayRet:uint; //(枚举类型：EBattleArrayRet)操作结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_BattleArrayTakePrize _name_={name_} eBattleArrayRet={eBattleArrayRet}/>;
			else
				topXml = <SRetParam_BattleArrayTakePrize eBattleArrayRet={eBattleArrayRet}/>;
			return topXml;
		}
	}
}
