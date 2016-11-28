/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetTotalInfo.as
//  Purpose:      获得玩家所有信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.langHuanBlessProt
{
	/**
	 * 获得玩家所有信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetTotalInfo
	{
		public var sTotalInfo:SLHBTotalInfo; //时间值
		public var bRet:Boolean; //结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetTotalInfo _name_={name_} bRet={bRet}/>;
			else
				topXml = <SRetParam_GetTotalInfo bRet={bRet}/>;
			if(sTotalInfo != null)
				topXml.appendChild(sTotalInfo.toXML("sTotalInfo"));
			return topXml;
		}
	}
}
