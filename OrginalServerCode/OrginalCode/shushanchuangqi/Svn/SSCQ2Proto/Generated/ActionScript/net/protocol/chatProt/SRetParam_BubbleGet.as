/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_BubbleGet.as
//  Purpose:      气泡信息获取
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.chatProt
{
	import net.protocol.roleInfoDefine.SBubbleInfo;

	/**
	 * 气泡信息获取的返回的参数组成的结构体
	 */
	public final class SRetParam_BubbleGet
	{
		public var vecBubbleInfo:Vector.<SBubbleInfo>; //气泡列表信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_BubbleGet _name_={name_}/>;
			else
				topXml = <SRetParam_BubbleGet/>;
			if(vecBubbleInfo != null)
			{
				var vecBubbleInfoXml:XML = <Vec_SBubbleInfo _name_="vecBubbleInfo"/>;
				for each(var s1:SBubbleInfo in vecBubbleInfo)
					vecBubbleInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecBubbleInfoXml);
			}
			return topXml;
		}
	}
}
