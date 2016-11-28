/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetSkillInfo.as
//  Purpose:      获得技能使用信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.langHuanBlessProt
{
	/**
	 * 获得技能使用信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetSkillInfo
	{
		public var vecLHBSkillInfo:Vector.<SLHBSkillInfo>; //技能使用信息
		public var eLHBResult:uint; //(枚举类型：ELHBResult)结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetSkillInfo _name_={name_} eLHBResult={eLHBResult}/>;
			else
				topXml = <SRetParam_GetSkillInfo eLHBResult={eLHBResult}/>;
			if(vecLHBSkillInfo != null)
			{
				var vecLHBSkillInfoXml:XML = <Vec_SLHBSkillInfo _name_="vecLHBSkillInfo"/>;
				for each(var s1:SLHBSkillInfo in vecLHBSkillInfo)
					vecLHBSkillInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecLHBSkillInfoXml);
			}
			return topXml;
		}
	}
}
