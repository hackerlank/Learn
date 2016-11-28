/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_FighterSkillEquipTo.as
//  Purpose:      散仙装备主动技能
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
{
	/**
	 * 散仙装备主动技能的返回的参数组成的结构体
	 */
	public final class SRetParam_FighterSkillEquipTo
	{
		public var eResult:uint; //(枚举类型：ESkillResult)结果
		public var vActiveSkill:Vector.<SFightSkillInfo>; //装备的主动技能

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_FighterSkillEquipTo _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_FighterSkillEquipTo eResult={eResult}/>;
			if(vActiveSkill != null)
			{
				var vActiveSkillXml:XML = <Vec_SFightSkillInfo _name_="vActiveSkill"/>;
				for each(var s1:SFightSkillInfo in vActiveSkill)
					vActiveSkillXml.appendChild(s1.toXML());
				topXml.appendChild(vActiveSkillXml);
			}
			return topXml;
		}
	}
}
