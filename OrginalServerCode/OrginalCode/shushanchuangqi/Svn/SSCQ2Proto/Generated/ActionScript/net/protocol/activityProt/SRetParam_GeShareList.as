/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GeShareList.as
//  Purpose:      获取成就分享信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.activityProt
{
	/**
	 * 获取成就分享信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GeShareList
	{
		public var vecActivityShare:Vector.<SActivityShare>; //成就分享信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GeShareList _name_={name_}/>;
			else
				topXml = <SRetParam_GeShareList/>;
			if(vecActivityShare != null)
			{
				var vecActivityShareXml:XML = <Vec_SActivityShare _name_="vecActivityShare"/>;
				for each(var s1:SActivityShare in vecActivityShare)
					vecActivityShareXml.appendChild(s1.toXML());
				topXml.appendChild(vecActivityShareXml);
			}
			return topXml;
		}
	}
}
