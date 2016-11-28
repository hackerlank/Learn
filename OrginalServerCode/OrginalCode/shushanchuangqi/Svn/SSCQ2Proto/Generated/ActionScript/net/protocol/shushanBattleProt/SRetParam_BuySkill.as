/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_BuySkill.as
//  Purpose:      购买蜀山论剑霸气or怒气
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	/**
	 * 购买蜀山论剑霸气or怒气的返回的参数组成的结构体
	 */
	public final class SRetParam_BuySkill
	{
		public var byFlag:uint; //(无符号8位整数)购买类型:0霸气 1怒气
		public var eResult:uint; //(枚举类型：ESSBattleResult)购买蜀山论剑霸气or怒气返回

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_BuySkill _name_={name_} byFlag={byFlag} eResult={eResult}/>;
			else
				topXml = <SRetParam_BuySkill byFlag={byFlag} eResult={eResult}/>;
			return topXml;
		}
	}
}
