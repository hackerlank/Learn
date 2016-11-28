/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetConfigTime.as
//  Purpose:      获得活动时间配置
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	/**
	 * 获得活动时间配置的返回的参数组成的结构体
	 */
	public final class SRetParam_GetConfigTime
	{
		public var sTimes:STime; //时间
		public var eRet:uint; //(枚举类型：EWActResult)操作结果

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetConfigTime _name_={name_} eRet={eRet}/>;
			else
				topXml = <SRetParam_GetConfigTime eRet={eRet}/>;
			if(sTimes != null)
				topXml.appendChild(sTimes.toXML("sTimes"));
			return topXml;
		}
	}
}
