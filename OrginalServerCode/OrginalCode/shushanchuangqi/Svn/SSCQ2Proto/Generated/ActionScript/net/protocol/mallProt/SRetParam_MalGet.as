/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_MalGet.as
//  Purpose:      预览商城信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
{
	/**
	 * 预览商城信息的返回的参数组成的结构体
	 */
	public final class SRetParam_MalGet
	{
		public var vecMallInfo:Vector.<SMallInfo>; //商场信息列表

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_MalGet _name_={name_}/>;
			else
				topXml = <SRetParam_MalGet/>;
			if(vecMallInfo != null)
			{
				var vecMallInfoXml:XML = <Vec_SMallInfo _name_="vecMallInfo"/>;
				for each(var s1:SMallInfo in vecMallInfo)
					vecMallInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecMallInfoXml);
			}
			return topXml;
		}
	}
}
