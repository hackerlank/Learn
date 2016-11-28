/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_UnLockHorseSkillAttr.as
//  Purpose:      解锁技能属性（暂时不用）
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
{
	/**
	 * 解锁技能属性（暂时不用）的返回的参数组成的结构体
	 */
	public final class SRetParam_UnLockHorseSkillAttr
	{
		public var bRet:Boolean; //结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_UnLockHorseSkillAttr _name_={name_} bRet={bRet}/>;
			else
				topXml = <SRetParam_UnLockHorseSkillAttr bRet={bRet}/>;
			return topXml;
		}
	}
}
