/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetYDBagInfo.as
//  Purpose:      获取黄钻礼包领取信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yelloDiamondProt
{
	/**
	 * 获取黄钻礼包领取信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetYDBagInfo
	{
		public var ydInfo:SYDInfo; //黄钻信息

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetYDBagInfo _name_={name_}/>;
			else
				topXml = <SRetParam_GetYDBagInfo/>;
			if(ydInfo != null)
				topXml.appendChild(ydInfo.toXML("ydInfo"));
			return topXml;
		}
	}
}
