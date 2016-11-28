/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SOrigParam_UnLockHorseSkillAttr.as
//  Purpose:      解锁技能属性（暂时不用）
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
{
	/**
	 * 解锁技能属性（暂时不用）的原来的参数组成的结构体
	 */
	public final class SOrigParam_UnLockHorseSkillAttr
	{
		public var callback:Function;

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SOrigParam_UnLockHorseSkillAttr _name_={name_}/>;
			else
				topXml = <SOrigParam_UnLockHorseSkillAttr/>;
			return topXml;
		}
	}
}
