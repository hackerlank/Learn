/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_SelectSkill.as
//  Purpose:      选择问道
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.langHuanBlessProt
{
	/**
	 * 选择问道的返回的参数组成的结构体
	 */
	public final class SRetParam_SelectSkill
	{
		public var eRetLHBSkillType:uint; //(枚举类型：ELHBSkillType)返回使用技能
		public var eLHBResult:uint; //(枚举类型：ELHBResult)结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_SelectSkill _name_={name_} eRetLHBSkillType={eRetLHBSkillType} eLHBResult={eLHBResult}/>;
			else
				topXml = <SRetParam_SelectSkill eRetLHBSkillType={eRetLHBSkillType} eLHBResult={eLHBResult}/>;
			return topXml;
		}
	}
}
