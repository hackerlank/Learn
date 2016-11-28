/************************************************************************
//  工具自动生成的Flash客户端协议代码(结构体类型)
//  File Name:    SRetParam_GetSevenConsumeAct.as
//  Purpose:      请求七日消费活动信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	/**
	 * 请求七日消费活动信息的返回的参数组成的结构体
	 */
	public final class SRetParam_GetSevenConsumeAct
	{
		public var byRet:uint; //(无符号8位整数)0活动未开启 >0活动已开启

		/**
		 * 转换为XML
		 * @param name_ 此类型作为成员变量时的变量名
		 */
		public function toXML(name_:String = null):XML
		{
			var topXml:XML
			if(name_ != null && name_ != "")
				topXml = <SRetParam_GetSevenConsumeAct _name_={name_} byRet={byRet}/>;
			else
				topXml = <SRetParam_GetSevenConsumeAct byRet={byRet}/>;
			return topXml;
		}
	}
}
