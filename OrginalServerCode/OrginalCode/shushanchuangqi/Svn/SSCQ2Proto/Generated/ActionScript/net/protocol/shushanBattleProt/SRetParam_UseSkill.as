/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_UseSkill.as
//  Purpose:      使用蜀山论剑技能
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	/**
	 * 使用蜀山论剑技能的返回的参数组成的结构体
	 */
	public final class SRetParam_UseSkill
	{
		public var bySkillID:uint; //(无符号8位整数)技能ID
		public var eResult:uint; //(枚举类型：ESSBattleResult)请求使用蜀山论剑技能返回

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_UseSkill _name_={name_} bySkillID={bySkillID} eResult={eResult}/>;
			else
				topXml = <SRetParam_UseSkill bySkillID={bySkillID} eResult={eResult}/>;
			return topXml;
		}
	}
}
