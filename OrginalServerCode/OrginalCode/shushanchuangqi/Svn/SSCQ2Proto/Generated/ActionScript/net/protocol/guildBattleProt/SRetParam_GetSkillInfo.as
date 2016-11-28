/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetSkillInfo.as
//  Purpose:      帮派战技能信息获取
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	/**
	 * 帮派战技能信息获取的返回的参数组成的结构体
	 */
	public final class SRetParam_GetSkillInfo
	{
		public var eResult:uint; //(枚举类型：EGBSkillResult)购买结果
		public var vecSkillInfo:Vector.<SSkillInfo>; //具体已购买技能

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetSkillInfo _name_={name_} eResult={eResult}/>;
			else
				topXml = <SRetParam_GetSkillInfo eResult={eResult}/>;
			if(vecSkillInfo != null)
			{
				var vecSkillInfoXml:XML = <Vec_SSkillInfo _name_="vecSkillInfo"/>;
				for each(var s1:SSkillInfo in vecSkillInfo)
					vecSkillInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecSkillInfoXml);
			}
			return topXml;
		}
	}
}
