/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_UseSkill.as
//  Purpose:      玩家使用技能
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
{
	/**
	 * 玩家使用技能的返回的参数组成的结构体
	 */
	public final class SRetParam_UseSkill
	{
		public var eSkillTypeRet:uint; //(枚举类型：EAnswerSkill)技能ID
		public var byAnswer1:uint; //(无符号8位整数)答案1
		public var byAnswer2:uint; //(无符号8位整数)答案2
		public var eResult:uint; //(枚举类型：EAnswerResult)结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_UseSkill _name_={name_} eSkillTypeRet={eSkillTypeRet} byAnswer1={byAnswer1} byAnswer2={byAnswer2} eResult={eResult}/>;
			else
				topXml = <SRetParam_UseSkill eSkillTypeRet={eSkillTypeRet} byAnswer1={byAnswer1} byAnswer2={byAnswer2} eResult={eResult}/>;
			return topXml;
		}
	}
}
