/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetXiheRequestInfo.as
//  Purpose:      获取自己帮派成员的羲和神车请求帮助列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
{
	/**
	 * 获取自己帮派成员的羲和神车请求帮助列表的返回的参数组成的结构体
	 */
	public final class SRetParam_GetXiheRequestInfo
	{
		public var vecXiheRequest:Vector.<SXiheRequest>; //玩家羲和神车请求帮助的信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetXiheRequestInfo _name_={name_}/>;
			else
				topXml = <SRetParam_GetXiheRequestInfo/>;
			if(vecXiheRequest != null)
			{
				var vecXiheRequestXml:XML = <Vec_SXiheRequest _name_="vecXiheRequest"/>;
				for each(var s1:SXiheRequest in vecXiheRequest)
					vecXiheRequestXml.appendChild(s1.toXML());
				topXml.appendChild(vecXiheRequestXml);
			}
			return topXml;
		}
	}
}
