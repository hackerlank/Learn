/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetActList.as
//  Purpose:      获取活动列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayActProt
{
	/**
	 * 获取活动列表的返回的参数组成的结构体
	 */
	public final class SRetParam_GetActList
	{
		public var vecActInfo:Vector.<SActInfo>; //活动列表

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetActList _name_={name_}/>;
			else
				topXml = <SRetParam_GetActList/>;
			if(vecActInfo != null)
			{
				var vecActInfoXml:XML = <Vec_SActInfo _name_="vecActInfo"/>;
				for each(var s1:SActInfo in vecActInfo)
					vecActInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecActInfoXml);
			}
			return topXml;
		}
	}
}
