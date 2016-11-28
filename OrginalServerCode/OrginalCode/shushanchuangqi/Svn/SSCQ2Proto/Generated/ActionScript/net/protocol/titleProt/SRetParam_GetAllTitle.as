/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetAllTitle.as
//  Purpose:      得到当前所有称号
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.titleProt
{
	import net.protocol.roleInfoDefine.STitle;

	/**
	 * 得到当前所有称号的返回的参数组成的结构体
	 */
	public final class SRetParam_GetAllTitle
	{
		public var vecTitle:Vector.<STitle>; //当前所有称号

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetAllTitle _name_={name_}/>;
			else
				topXml = <SRetParam_GetAllTitle/>;
			if(vecTitle != null)
			{
				var vecTitleXml:XML = <Vec_STitle _name_="vecTitle"/>;
				for each(var s1:STitle in vecTitle)
					vecTitleXml.appendChild(s1.toXML());
				topXml.appendChild(vecTitleXml);
			}
			return topXml;
		}
	}
}
