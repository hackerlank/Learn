/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetFightFormation.as
//  Purpose:      取得阵形信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fightFormation
{
	/**
	 * 取得阵形信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetFightFormation
	{
		public var oFightFormation:FightFormationInfo; //战斗阵形信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetFightFormation _name_={name_}/>;
			else
				topXml = <SRetParam_GetFightFormation/>;
			if(oFightFormation != null)
				topXml.appendChild(oFightFormation.toXML("oFightFormation"));
			return topXml;
		}
	}
}
